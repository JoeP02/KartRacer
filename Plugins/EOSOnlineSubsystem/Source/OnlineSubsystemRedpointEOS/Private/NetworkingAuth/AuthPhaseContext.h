// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "OnlineSubsystemRedpointEOS/Private/EOSControlChannel.h"
#include "OnlineSubsystemRedpointEOS/Private/NetworkingAuth/AuthPhaseFailureCode.h"
#include "OnlineSubsystemRedpointEOS/Private/NetworkingAuth/NetworkHelpers.h"
#include "OnlineSubsystemRedpointEOS/Shared/AntiCheat/AntiCheat.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "RedpointEOSConfig/Config.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSNetDriver.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineSubsystemRedpointEOS.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FAuthPhasesCompleted, EAuthPhaseFailureCode, const FString &ErrorMessage);

#if defined(UE_5_0_OR_LATER)
#define EOS_NO_DISCARD [[nodiscard]]
#else
#define EOS_NO_DISCARD
#endif

class IAuthPhaseContext
{
public:
    EOS_NO_DISCARD virtual bool GetControlChannel(UEOSControlChannel *&OutControlChannel) const = 0;
    EOS_NO_DISCARD virtual bool GetConnection(UNetConnection *&OutConnection) const = 0;
    EOS_NO_DISCARD virtual bool GetOSS(FOnlineSubsystemEOS *&OutOSS) = 0;
    EOS_NO_DISCARD virtual bool GetConfig(const Redpoint::EOS::Config::IConfig *&OutConfig) = 0;
    EOS_NO_DISCARD virtual bool GetRole(EEOSNetDriverRole &OutRole) = 0;
    EOS_NO_DISCARD virtual bool GetSocketSubsystem(ISocketSubsystem *&OutSocketSubsystem) = 0;
    virtual void Finish(EAuthPhaseFailureCode ErrorCode) = 0;
};

// @hack: This intentionally does not inherit from TSharedFromThis, because Clang makes bad tail call
// optimizations that result in AsShared() being unusable anyway.
template <typename TPhase, typename TDerivedContext> class FAuthPhaseContext : public IAuthPhaseContext
{
    friend class UEOSControlChannel;

private:
    TSharedPtr<TDerivedContext> SelfRef;
    TSoftObjectPtr<class UEOSControlChannel> ControlChannel;
    FAuthPhasesCompleted OnCompletedInternal;
    TArray<TSharedRef<TPhase>> Phases;

protected:
    FAuthPhaseContext(class UEOSControlChannel *InControlChannel)
        : SelfRef(nullptr)
        , ControlChannel(InControlChannel)
        , OnCompletedInternal()
        , Phases(){};

    virtual FString GetIdentifier() const = 0;
    virtual FString GetPhaseGroup() const = 0;

public:
    UE_NONCOPYABLE(FAuthPhaseContext);
    virtual ~FAuthPhaseContext(){};

    EOS_NO_DISCARD virtual bool GetControlChannel(UEOSControlChannel *&OutControlChannel) const override
    {
        if (this->ControlChannel.IsValid())
        {
            OutControlChannel = this->ControlChannel.Get();
            return true;
        }
        return false;
    }

    EOS_NO_DISCARD virtual bool GetConnection(UNetConnection *&OutConnection) const override
    {
        if (this->ControlChannel.IsValid() && IsValid(this->ControlChannel->Connection))
        {
            OutConnection = this->ControlChannel->Connection;
            return true;
        }
        return false;
    }

    EOS_NO_DISCARD virtual bool GetOSS(FOnlineSubsystemEOS *&OutOSS) override
    {
        UNetConnection *Connection;
        if (GetConnection(Connection))
        {
            OutOSS = FNetworkHelpers::GetOSS(Connection);
            return true;
        }
        return false;
    }

    EOS_NO_DISCARD virtual bool GetConfig(const Redpoint::EOS::Config::IConfig *&OutConfig) override
    {
        UNetConnection *Connection;
        if (GetConnection(Connection))
        {
            OutConfig = FNetworkHelpers::GetConfig(Connection);
            return true;
        }
        return false;
    }

    EOS_NO_DISCARD virtual bool GetRole(EEOSNetDriverRole &OutRole) override
    {
        UNetConnection *Connection;
        if (GetConnection(Connection))
        {
            OutRole = FNetworkHelpers::GetRole(Connection);
            return true;
        }
        return false;
    }

    EOS_NO_DISCARD virtual bool GetSocketSubsystem(ISocketSubsystem *&OutSocketSubsystem) override
    {
        UNetConnection *Connection;
        if (GetConnection(Connection))
        {
            OutSocketSubsystem = FNetworkHelpers::GetSocketSubsystem(Connection);
            return true;
        }
        return false;
    }

    EOS_NO_DISCARD bool GetAntiCheat(
        TSharedPtr<IAntiCheat> &OutAntiCheat,
        TSharedPtr<FAntiCheatSession> &OutAntiCheatSession,
        bool &OutIsBeacon) const
    {
        UNetConnection *Connection;
        if (GetConnection(Connection))
        {
            FNetworkHelpers::GetAntiCheat(Connection, OutAntiCheat, OutAntiCheatSession, OutIsBeacon);
            return true;
        }
        return false;
    }

    template <typename TDerivedPhase> TSharedPtr<TDerivedPhase> GetPhase(const FName &InPhaseName)
    {
        for (const auto &Entry : this->Phases)
        {
            if (Entry->GetName().IsEqual(InPhaseName))
            {
                return StaticCastSharedRef<TDerivedPhase>(Entry);
            }
        }
        return nullptr;
    }

    FAuthPhasesCompleted &OnCompleted()
    {
        return this->OnCompletedInternal;
    }

    /** Log a verbose message from the current phase. */
    void Log(const FString &Message)
    {
        if (this->Phases.Num() == 0)
        {
            UE_LOG(LogRedpointEOSNetworkAuth, Verbose, TEXT("%s: %s: %s"), *GetIdentifier(), *GetPhaseGroup(), *Message);
        }
        else
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Verbose,
                TEXT("%s: %s: %s: %s"),
                *GetIdentifier(),
                *GetPhaseGroup(),
                *this->Phases[0]->GetName().ToString(),
                *Message);
        }
    }

    /** Register phases for client routing. Does not execute phases. */
    void RegisterPhasesForClientRouting(const TArray<TSharedRef<TPhase>> &InPhases)
    {
        UNetConnection *Connection;
        verifyf(
            this->GetConnection(Connection),
            TEXT("RegisterPhasesForClientRouting must only be called on code paths that have already checked that the "
                 "connection is still valid."));
        EEOSNetDriverRole Role = FNetworkHelpers::GetRole(Connection);
        checkf(
            Role == EEOSNetDriverRole::ClientConnectedToDedicatedServer ||
                Role == EEOSNetDriverRole::ClientConnectedToListenServer,
            TEXT("RegisterPhasesForClientRouting can only be called on clients!"));
        this->Phases = InPhases;
    }

    /** Start the first authentication phase. This must be called from the server. */
    void Start(
        // @hack: For some reason, Clang makes a bad TCO that results in AsShared() being unset, so
        // we have to pass the value that would be in AsShared() directly into Start() and store it
        // ourselves. I tried many alternatives to get it to keep the value in AsShared() properly,
        // but it refused to do so. :/
        TSharedRef<FAuthPhaseContext<TPhase, TDerivedContext>> ThisRef,
        const TArray<TSharedRef<TPhase>> &InPhases)
    {
        checkf(!this->SelfRef.IsValid(), TEXT("Start() called multiple times on same context!"));
        TSharedRef<TDerivedContext> DowncastedThisRef = StaticCastSharedRef<TDerivedContext>(ThisRef);
        this->SelfRef = DowncastedThisRef;

        EEOSNetDriverRole Role;
        if (!this->GetRole(Role))
        {
            this->Finish(EAuthPhaseFailureCode::All_ConnectionHasGoneAway);
            return;
        }
        checkf(
            Role == EEOSNetDriverRole::DedicatedServer || Role == EEOSNetDriverRole::ListenServer,
            TEXT("Start can only be called on servers!"));

        this->Phases = InPhases;
        if (this->Phases.Num() == 0)
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Verbose,
                TEXT("%s: %s: Immediately finishing as there are no phases to run."),
                *GetIdentifier(),
                *GetPhaseGroup());
            this->Finish(EAuthPhaseFailureCode::Success);
        }
        else
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Verbose,
                TEXT("%s: %s: %s: Starting..."),
                *GetIdentifier(),
                *GetPhaseGroup(),
                *this->Phases[0]->GetName().ToString());
            this->Phases[0]->Start(DowncastedThisRef);
        }
    }

    /** Finish the authentication phase and proceed to the next one. This must be called from the server. */
    virtual void Finish(EAuthPhaseFailureCode ErrorCode) override
    {
        FString CurrentPhaseName = TEXT("");

        // This sometimes gets called because there are no phases to run, so
        // don't try and remove index 0 if we don't actually have phases.
        if (this->Phases.Num() > 0)
        {
            CurrentPhaseName = this->Phases[0]->GetName().ToString();
            this->Phases.RemoveAt(0);
        }

        if (ErrorCode != EAuthPhaseFailureCode::Success)
        {
            if (CurrentPhaseName.IsEmpty())
            {
                UE_LOG(
                    LogRedpointEOSNetworkAuth,
                    Error,
                    TEXT("%s: %s: Finished with failure code (0x%04x), connection will be terminated."),
                    *GetIdentifier(),
                    *GetPhaseGroup());
            }
            else
            {
                UE_LOG(
                    LogRedpointEOSNetworkAuth,
                    Error,
                    TEXT("%s: %s: %s: Finished with failure code (0x%04x), connection will be terminated."),
                    *GetIdentifier(),
                    *GetPhaseGroup(),
                    *CurrentPhaseName,
                    ErrorCode);
            }

            OnCompleted().Broadcast(ErrorCode, GetAuthPhaseFailureCodeString(ErrorCode));
            this->SelfRef.Reset();
            return;
        }

        if (CurrentPhaseName.IsEmpty())
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Verbose,
                TEXT("%s: %s: Finished successfully."),
                *GetIdentifier(),
                *GetPhaseGroup());
        }
        else
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Verbose,
                TEXT("%s: %s: %s: Finished successfully."),
                *GetIdentifier(),
                *GetPhaseGroup(),
                *CurrentPhaseName);
        }

        if (this->Phases.Num() == 0)
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Verbose,
                TEXT("%s: %s: All phases finished successfully."),
                *GetIdentifier(),
                *GetPhaseGroup());

            // Finished all phases.
            OnCompleted().Broadcast(ErrorCode, GetAuthPhaseFailureCodeString(ErrorCode));
            this->SelfRef.Reset();
        }
        else
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Verbose,
                TEXT("%s: %s: %s: Starting..."),
                *GetIdentifier(),
                *GetPhaseGroup(),
                *this->Phases[0]->GetName().ToString());

            // Start next phase.
            this->Phases[0]->Start(this->SelfRef.ToSharedRef());
        }
    }
};

#undef EOS_NO_DISCARD
// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_HAS_AUTHENTICATION

#include "CoreMinimal.h"

#include "Containers/Array.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlinePartyInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystemRedpointEOS/Shared/UniqueNetIdEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/UniqueNetIdEOSSession.h"
#include "RedpointEOSConfig/Config.h"
#include "RedpointEOSCore/RuntimePlatform.h"

EOS_ENABLE_STRICT_WARNINGS

DECLARE_DELEGATE_OneParam(FSyntheticPartySessionOnComplete, const FOnlineError & /* Error */);

class FSyntheticPartySessionManager : public TSharedFromThis<FSyntheticPartySessionManager>
{
    friend class FOnlineSubsystemEOS;

private:
    struct FWrappedSubsystem
    {
        FName SubsystemName;
        TWeakPtr<IOnlineIdentity, ESPMode::ThreadSafe> Identity;
        TWeakPtr<IOnlineSession, ESPMode::ThreadSafe> Session;
    };

    TSharedRef<Redpoint::EOS::Core::IRuntimePlatform> RuntimePlatform;
    TSharedRef<Redpoint::EOS::Config::IConfig> Config;
    TWeakPtr<class FOnlinePartySystemEOS, ESPMode::ThreadSafe> EOSPartySystem;
    TWeakPtr<class FOnlineSessionInterfaceEOS, ESPMode::ThreadSafe> EOSSession;
    TWeakPtr<class FOnlineIdentityInterfaceEOS, ESPMode::ThreadSafe> EOSIdentitySystem;
    TArray<FWrappedSubsystem> WrappedSubsystems;
    TMap<TWeakPtr<IOnlineSession, ESPMode::ThreadSafe>, FDelegateHandle> SessionUserInviteAcceptedDelegateHandles;
    TMap<FString, FDelegateHandle> HandlesPendingRemoval;

public:
    FSyntheticPartySessionManager(
        FName InInstanceName,
        TWeakPtr<class FOnlinePartySystemEOS, ESPMode::ThreadSafe> InEOSPartySystem,
        TWeakPtr<class FOnlineSessionInterfaceEOS, ESPMode::ThreadSafe> InEOSSession,
        TWeakPtr<class FOnlineIdentityInterfaceEOS, ESPMode::ThreadSafe> InEOSIdentitySystem,
        const TSharedRef<Redpoint::EOS::Core::IRuntimePlatform> &InRuntimePlatform,
        const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig);
    UE_NONCOPYABLE(FSyntheticPartySessionManager);
    ~FSyntheticPartySessionManager();

    FName GetSyntheticSessionNativeSessionName(
        const FName &InSubsystemName,
        const TSharedPtr<const FUniqueNetIdEOSSession> &InSessionId);
    FName GetSyntheticSessionNativePartyName(
        const FName &InSubsystemName,
        const TSharedPtr<const FOnlinePartyId> &InPartyId);

private:
    void RegisterEvents();

    void HandlePartyInviteAccept(int32 ControllerId, const FString &EOSPartyId);
    void HandleSessionInviteAccept(int32 ControllerId, const FString &EOSSessionId);

public:
    void CreateSyntheticParty(
        const TSharedPtr<const FOnlinePartyId> &PartyId,
        const FSyntheticPartySessionOnComplete &OnComplete);
    void DeleteSyntheticParty(
        const TSharedPtr<const FOnlinePartyId> &PartyId,
        const FSyntheticPartySessionOnComplete &OnComplete);
    bool HasSyntheticParty(const TSharedPtr<const FOnlinePartyId> &PartyId);
    void CreateSyntheticSession(
        const TSharedPtr<const FUniqueNetIdEOSSession> &SessionId,
        const FSyntheticPartySessionOnComplete &OnComplete);
    void DeleteSyntheticSession(
        const TSharedPtr<const FUniqueNetIdEOSSession> &SessionId,
        const FSyntheticPartySessionOnComplete &OnComplete);
    bool HasSyntheticSession(const TSharedPtr<const FUniqueNetIdEOSSession> &SessionId);
    bool HasSyntheticSession(const FName &SubsystemName, const TSharedPtr<const FUniqueNetIdEOSSession> &SessionId);
    void SendInvitationToParty(
        int32 LocalUserNum,
        const TSharedPtr<const FOnlinePartyId> &PartyId,
        const TSharedPtr<const FUniqueNetId> &RecipientId,
        const FSyntheticPartySessionOnComplete &Delegate);
    void SendInvitationToSession(
        int32 LocalUserNum,
        const TSharedPtr<const FUniqueNetIdEOSSession> &SessionId,
        const TSharedPtr<const FUniqueNetId> &RecipientId,
        const FSyntheticPartySessionOnComplete &Delegate);
};

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
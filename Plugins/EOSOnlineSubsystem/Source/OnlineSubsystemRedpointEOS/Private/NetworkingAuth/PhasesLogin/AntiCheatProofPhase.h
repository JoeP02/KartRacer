// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemRedpointEOS/Private/NetworkingAuth/AuthLoginPhase.h"
#include "OnlineSubsystemRedpointEOS/Private/NetworkingAuth/AuthLoginPhaseContext.h"
#include "OnlineSubsystemRedpointEOS/Shared/AntiCheat/AntiCheatImplementationType.h"

#define AUTH_PHASE_ANTI_CHEAT_PROOF FName(TEXT("AntiCheatProof"))

class FAntiCheatProofPhase : public IAuthLoginPhase
{
private:
    FString PendingNonceCheck;
    bool bReceivedRemoteAuthForListenServerFromClient;
    bool bWaitingForClientToAcceptOurProof;

    void InitializeNonceForRequestProof();
    void RequestProofFromPeer(
        const TSharedRef<FAuthLoginPhaseContext> &Context,
        const TSharedPtr<IAntiCheat> &AntiCheat,
        UNetConnection *Connection,
        const FUniqueNetIdRepl &UserIdRepl);
    void DeliverProofToPeer(
        const TSharedRef<FAuthLoginPhaseContext> &Context,
        const TSharedPtr<IAntiCheat> &AntiCheat,
        const Redpoint::EOS::Config::IConfig *Config,
        UNetConnection *Connection,
        const FString &EncodedNonce,
        FOnlineSubsystemEOS *OSS,
        bool bRequestingTrustedClientProofFromListenServer);

public:
    FAntiCheatProofPhase()
        : PendingNonceCheck()
        , bReceivedRemoteAuthForListenServerFromClient(false)
        , bWaitingForClientToAcceptOurProof(false){};
    UE_NONCOPYABLE(FAntiCheatProofPhase);
    virtual ~FAntiCheatProofPhase(){};

    virtual FName GetName() const override
    {
        return AUTH_PHASE_ANTI_CHEAT_PROOF;
    }

    static void RegisterRoutes(class UEOSControlChannel *ControlChannel);
    virtual void Start(const TSharedRef<FAuthLoginPhaseContext> &Context) override;

    virtual void OnAntiCheatPlayerAuthStatusChanged(
        const TSharedRef<FAuthLoginPhaseContext> &Context,
        EOS_EAntiCheatCommonClientAuthStatus NewAuthStatus) override;

private:
    void On_NMT_EOS_RequestTrustedClientProof(
        const TSharedRef<FAuthLoginPhaseContext> &Context,
        const FString &EncodedNonce,
        EAntiCheatImplementationType AntiCheatImplementationType);
    void On_NMT_EOS_DeliverTrustedClientProof(
        const TSharedRef<FAuthLoginPhaseContext> &Context,
        bool bCanProvideProof,
        const FString &EncodedProof,
        const FString &PlatformString,
        bool bRequestMutualProofFromListenServer,
        FString EncodedNonceForListenServer,
        bool bSkipPeerRegistration);
    void On_NMT_EOS_AcceptedMutualTrustedClientProof(const TSharedRef<FAuthLoginPhaseContext> &Context);
};
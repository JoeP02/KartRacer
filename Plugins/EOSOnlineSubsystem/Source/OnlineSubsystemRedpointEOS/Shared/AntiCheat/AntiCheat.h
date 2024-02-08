// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "OnlineSubsystemRedpointEOS/Shared/AntiCheat/AntiCheatImplementationType.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "OnlineSubsystemRedpointEOS/Shared/UniqueNetIdEOS.h"
#if defined(UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

class FAntiCheatSession : public TSharedFromThis<FAntiCheatSession>
{
private:
    FGuid SessionInstanceGuid;

public:
    FAntiCheatSession();
    virtual ~FAntiCheatSession(){};
    UE_NONCOPYABLE(FAntiCheatSession);

    const FGuid &GetInstanceGuid() const;
    FString ToString() const;
};

FString EOS_EAntiCheatCommonClientActionReason_ToString(const EOS_EAntiCheatCommonClientActionReason &Reason);

DECLARE_DELEGATE_FiveParams(
    FOnAntiCheatSendNetworkMessage,
    const TSharedRef<FAntiCheatSession> & /* Session */,
    const FUniqueNetIdEOS & /* SourceUserId */,
    const FUniqueNetIdEOS & /* TargetUserId */,
    const uint8 * /* Data */,
    uint32_t /* Size */);
DECLARE_MULTICAST_DELEGATE_TwoParams(
    FOnAntiCheatPlayerAuthStatusChanged,
    const FUniqueNetIdEOS & /* TargetUserId */,
    EOS_EAntiCheatCommonClientAuthStatus /* NewAuthStatus */);
DECLARE_MULTICAST_DELEGATE_FourParams(
    FOnAntiCheatPlayerActionRequired,
    const FUniqueNetIdEOS & /* TargetUserId */,
    EOS_EAntiCheatCommonClientAction /* ClientAction */,
    EOS_EAntiCheatCommonClientActionReason /* ActionReasonCode */,
    const FString & /* ActionReasonDetailsString */);

class IAntiCheat : public FExec
{
public:
    virtual ~IAntiCheat(){};

    virtual bool Init() = 0;
    virtual void Shutdown() = 0;

    virtual EAntiCheatImplementationType GetImplementationType() const = 0;

    /**
     * If true and this is a trusted client, remote servers and peers are instructed
     * to not register this client at all, rather than using EOS_ACCCT_UnprotectedClient.
     * This is necessary for systems where EOS_HAntiCheatClient is null when running
     * without EAC, instead of where EOS_HAntiCheatClient is provided as an implementation
     * that can handle network messages.
     */
    virtual bool ShouldRemoteSkipPeerRegistration() const = 0;

    virtual TSharedPtr<FAntiCheatSession> CreateSession(
        bool bIsServer,
        const FUniqueNetIdEOS &HostUserId,
        bool bIsDedicatedServerSession,
        TSharedPtr<const FUniqueNetIdEOS> ListenServerUserId,
        FString ServerConnectionUrlOnClient) = 0;
    virtual bool DestroySession(FAntiCheatSession &Session) = 0;

    virtual bool RegisterPlayer(
        FAntiCheatSession &Session,
        const FUniqueNetIdEOS &UserId,
        EOS_EAntiCheatCommonClientType ClientType,
        EOS_EAntiCheatCommonClientPlatform ClientPlatform) = 0;
    virtual bool UnregisterPlayer(FAntiCheatSession &Session, const FUniqueNetIdEOS &UserId) = 0;

    /** Called by the IAntiCheat implementation when a network message needs to be sent. */
    FOnAntiCheatSendNetworkMessage OnSendNetworkMessage;
    virtual bool ReceiveNetworkMessage(
        FAntiCheatSession &Session,
        const FUniqueNetIdEOS &SourceUserId,
        const FUniqueNetIdEOS &TargetUserId,
        const uint8 *Data,
        uint32_t Size) = 0;

    /** Called by the IAntiCheat implementation when a player's auth status has been verified. */
    FOnAntiCheatPlayerAuthStatusChanged OnPlayerAuthStatusChanged;

    /** Called by the IAntiCheat implementation when a player needs to be kicked. */
    FOnAntiCheatPlayerActionRequired OnPlayerActionRequired;
};
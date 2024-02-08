// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "./IMessagingHub.h"

class ONLINESUBSYSTEMREDPOINTEOS_API FP2PMessagingHub : public IMessagingHub, public TSharedFromThis<FP2PMessagingHub>
{
private:
    struct FConnectedSocketPair
    {
        int32 LocalUserNum;
        TSharedRef<const FUniqueNetIdEOS> OwnerId;
        TSharedRef<class ISocketEOS> Socket;
        FDateTime ExpiresAt;
        FConnectedSocketPair(
            int32 InLocalUserNum,
            TSharedRef<const FUniqueNetIdEOS> InOwnerId,
            TSharedRef<class ISocketEOS> InSocket)
            : LocalUserNum(InLocalUserNum)
            , OwnerId(MoveTemp(InOwnerId))
            , Socket(MoveTemp(InSocket))
            , ExpiresAt(FDateTime::UtcNow() + FTimespan::FromMinutes(3)){};
    };
    struct FMessageAckData
    {
        TSharedRef<const FUniqueNetIdEOS> SenderId;
        TSharedRef<const FUniqueNetIdEOS> ReceiverId;
        TSharedRef<class ISocketEOS> Socket;
        FOnMessagingHubSent Callback;
        FMessageAckData(
            TSharedRef<const FUniqueNetIdEOS> InSenderId,
            TSharedRef<const FUniqueNetIdEOS> InReceiverId,
            TSharedRef<class ISocketEOS> InSocket,
            FOnMessagingHubSent InCallback)
            : SenderId(MoveTemp(InSenderId))
            , ReceiverId(MoveTemp(InReceiverId))
            , Socket(MoveTemp(InSocket))
            , Callback(MoveTemp(InCallback)){};
    };

    FOnMessagingHubReceived OnMessageReceivedDelegate;
    TSharedRef<class FOnlineIdentityInterfaceEOS, ESPMode::ThreadSafe> Identity;
    TSharedRef<class ISocketSubsystemEOS> SocketSubsystem;
    TMap<int32, TSharedRef<ISocketEOS>> LocalUserSockets;
    TMap<int32, FMessageAckData> MessagesPendingAck;
    TArray<FConnectedSocketPair> ConnectedSockets;
    uint8 *RecvBuffer;
    int32 NextMsgId;
    FTSTicker::FDelegateHandle TickHandle;

    void OnLoginStatusChanged(
        int32 LocalUserNum,
        ELoginStatus::Type OldStatus,
        ELoginStatus::Type NewStatus,
        const FUniqueNetId &NewId);
    bool Tick(float DeltaSeconds);
    void OnConnectionClosed(
        const TSharedRef<class ISocketEOS> &ListeningSocket,
        const TSharedRef<class ISocketEOS> &ClosedSocket);
    void OnConnectionAccepted(
        const TSharedRef<class ISocketEOS> &ListeningSocket,
        const TSharedRef<class ISocketEOS> &AcceptedSocket,
        const TSharedRef<class FUniqueNetIdEOS> &LocalUser,
        const TSharedRef<class FUniqueNetIdEOS> &RemoteUser,
        int32 LocalUserNum);

public:
    FP2PMessagingHub(
        const TSharedRef<class FOnlineIdentityInterfaceEOS, ESPMode::ThreadSafe> &InIdentity,
        const TSharedRef<class ISocketSubsystemEOS> &InSocketSubsystem);
    UE_NONCOPYABLE(FP2PMessagingHub);
    virtual ~FP2PMessagingHub();
    void RegisterEvents();

    virtual FOnMessagingHubReceived &OnMessageReceived() override;

    virtual void SendMessage(
        const FUniqueNetIdEOS &SenderId,
        const FUniqueNetIdEOS &ReceiverId,
        const FString &MessageType,
        const FString &MessageData,
        const FOnMessagingHubSent &Delegate = FOnMessagingHubSent()) override;
};
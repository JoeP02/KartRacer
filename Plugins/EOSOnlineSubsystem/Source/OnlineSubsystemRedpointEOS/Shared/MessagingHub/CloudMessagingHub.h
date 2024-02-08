// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "./IMessagingHub.h"

#include "RedpointEOSAPI/Platform.h"
#include "RedpointEOSConfig/Config.h"

class ONLINESUBSYSTEMREDPOINTEOS_API FCloudMessagingHub : public IMessagingHub,
                                                          public TSharedFromThis<FCloudMessagingHub>
{
private:
    class FPendingOutboundMessage
    {
    public:
        TSharedRef<const FUniqueNetIdEOS> ReceiverId;
        FString MessageType;
        FString MessageData;
        FOnMessagingHubSent Delegate;
    };

	class FPartialInboundMessage
    {
    public:
        uint8_t* Buffer;
        size_t Size;
        size_t Offset;

		FPartialInboundMessage(size_t TotalSize)
            : Buffer((uint8_t*)FMemory::MallocZeroed(TotalSize))
            , Size(TotalSize)
            , Offset(0)
        {
		}
        UE_NONCOPYABLE(FPartialInboundMessage);
		~FPartialInboundMessage()
		{
			if (this->Buffer != nullptr)
			{
                FMemory::Free(this->Buffer);
			}
		}
	};

    Redpoint::EOS::API::FPlatformHandle PlatformHandle;
    TSharedRef<Redpoint::EOS::Config::IConfig> Config;
    FOnMessagingHubReceived OnMessageReceivedDelegate;
    TUserIdMap<TSharedRef<class IWebSocket>> ConnectedLocalUserSockets;
    int32_t NextMessageId;
    TMap<int32_t, FOnMessagingHubSent> OnMessageAcked;
    TMap<int32_t, FTSTicker::FDelegateHandle> OnMessageAckedTimeout;
    TUserIdMap<TArray<FPendingOutboundMessage>> PendingOutboundMessages;
    TUserIdMap<TSharedRef<FPartialInboundMessage>> PartialInboundMessages;

    void OnWebSocketConnected(TSharedRef<const FUniqueNetIdEOS> UserId);
    void OnWebSocketConnectionError(const FString &Error, TSharedRef<const FUniqueNetIdEOS> UserId);
    void OnWebSocketClosed(
        int32 StatusCode,
        const FString &Reason,
        bool bWasClean,
        TSharedRef<const FUniqueNetIdEOS> UserId);
    void OnCompleteWebSocketMessageReceived(
        const void *Data,
        SIZE_T Size,
        TSharedRef<const FUniqueNetIdEOS> UserId);
    void OnWebSocketMessageReceived(
        const void *Data,
        SIZE_T Size,
        SIZE_T BytesRemaining,
        TSharedRef<const FUniqueNetIdEOS> UserId);
    bool OnWebSocketSendTimeout(float DeltaSeconds, int32_t MessageId);

public:
    FCloudMessagingHub(
        const Redpoint::EOS::API::FPlatformHandle &InPlatformHandle,
        const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig);
    UE_NONCOPYABLE(FCloudMessagingHub);
    virtual ~FCloudMessagingHub();

    virtual void LocalUserSignedIn(const FUniqueNetIdEOS &UserId) override;

    virtual void LocalUserSignedOut(const FUniqueNetIdEOS &UserId) override;

    virtual FOnMessagingHubReceived &OnMessageReceived() override;

    virtual void SendMessage(
        const FUniqueNetIdEOS &SenderId,
        const FUniqueNetIdEOS &ReceiverId,
        const FString &MessageType,
        const FString &MessageData,
        const FOnMessagingHubSent &Delegate = FOnMessagingHubSent()) override;
};
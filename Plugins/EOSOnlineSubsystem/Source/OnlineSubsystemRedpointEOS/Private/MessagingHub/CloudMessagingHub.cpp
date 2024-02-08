// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Shared/MessagingHub/CloudMessagingHub.h"

#include "IWebSocket.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "RedpointEOSConfig/Config.h"
#include "WebSocketsModule.h"

#include "RedpointEOSAPI/Connect/CopyIdToken.h"

FCloudMessagingHub::FCloudMessagingHub(
    const Redpoint::EOS::API::FPlatformHandle &InPlatformHandle,
    const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig)
    : PlatformHandle(InPlatformHandle)
    , Config(InConfig)
    , OnMessageReceivedDelegate()
    , ConnectedLocalUserSockets()
    , NextMessageId(1000)
    , OnMessageAcked()
    , OnMessageAckedTimeout()
{
}

FCloudMessagingHub::~FCloudMessagingHub()
{
}

void FCloudMessagingHub::OnWebSocketConnected(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    TSharedRef<const FUniqueNetIdEOS> UserId)
{
    UE_LOG(
        LogRedpointEOSCloudMessagingHub,
        Verbose,
        TEXT("Successfully connected to the Cloud Messaging Hub for user: %s"),
        *UserId->GetProductUserIdString());
    if (this->PendingOutboundMessages.Contains(*UserId))
    {
        auto MessagesToSendNow = this->PendingOutboundMessages[*UserId];
        this->PendingOutboundMessages.Remove(*UserId);
        for (const auto &Message : MessagesToSendNow)
        {
            this->SendMessage(*UserId, *Message.ReceiverId, Message.MessageType, Message.MessageData, Message.Delegate);
        }
    }
}

void FCloudMessagingHub::OnWebSocketConnectionError(
    const FString &Error,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    TSharedRef<const FUniqueNetIdEOS> UserId)
{
    UE_LOG(
        LogRedpointEOSCloudMessagingHub,
        Error,
        TEXT("Failed to connect to the Cloud Messaging Hub for user: %s. Received error: '%s'. This user will remain "
             "disconnected and not receive events."),
        *UserId->GetProductUserIdString(),
        *Error);
}

void FCloudMessagingHub::OnWebSocketClosed(
    int32 StatusCode,
    const FString &Reason,
    bool bWasClean,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    TSharedRef<const FUniqueNetIdEOS> UserId)
{
    if (this->ConnectedLocalUserSockets.Contains(*UserId))
    {
        UE_LOG(
            LogRedpointEOSCloudMessagingHub,
            Warning,
            TEXT("Reconnecting to Cloud Messaging Hub due to unexpected disconnection for user: %s"),
            *UserId->GetProductUserIdString());
        this->ConnectedLocalUserSockets[*UserId]->Connect();
    }
}

void FCloudMessagingHub::OnCompleteWebSocketMessageReceived(
    const void *Data,
    SIZE_T Size,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    TSharedRef<const FUniqueNetIdEOS> UserId)
{
    uint8_t ProtocolMessageType = ((uint8_t *)Data)[0];
    if (ProtocolMessageType == 0 && Size >= 1 + 32)
    {
        // This is a message from another user.
        ANSICHAR UserIdBuffer[32 + 1] = {};
        FMemory::Memcpy(UserIdBuffer, ((uint8_t *)Data) + 1, 32);
        UserIdBuffer[32] = '\0';
        FString SourceUserId = ANSI_TO_TCHAR(UserIdBuffer);
        TCHAR *DataBuffer = (TCHAR *)FMemory::MallocZeroed((((Size - 32 - 1) / 2) + 1) * 2);
        FMemory::Memcpy(DataBuffer, ((uint8_t *)Data) + 1 + 32, Size - 32 - 1);
        FString MessageRawData = FString(DataBuffer, ((Size - 32 - 1) / 2) * 2);
        FString MessageType;
        FString MessageData;
        if (MessageRawData.Split(TEXT("|"), &MessageType, &MessageData))
        {
            auto SourceUserIdParsed = FUniqueNetIdEOS::ParseFromString(SourceUserId);
            if (SourceUserIdParsed.IsValid())
            {
                UE_LOG(
                    LogRedpointEOSCloudMessagingHub,
                    VeryVerbose,
                    TEXT("(recv) %s -> %s: %s: %s"),
                    *SourceUserIdParsed->ToString(),
                    *UserId->ToString(),
                    *MessageType,
                    *MessageData);
                this->OnMessageReceivedDelegate.Broadcast(*SourceUserIdParsed, *UserId, MessageType, MessageData);
            }
        }
        FMemory::Free(DataBuffer);
    }
    else if (ProtocolMessageType == 1 && Size >= 5)
    {
        // This is a message acknowledging that Cloud Messaging Hub has stored
        // one of our outbound messages.
        int32_t MessageId = ((int32_t *)(((uint8_t *)Data) + 1))[0];
        if (this->OnMessageAcked.Contains(MessageId))
        {
            this->OnMessageAckedTimeout.Remove(MessageId);
            this->OnMessageAcked[MessageId].ExecuteIfBound(true);
            this->OnMessageAcked.Remove(MessageId);
        }
        else
        {
            UE_LOG(
                LogRedpointEOSCloudMessagingHub,
                Warning,
                TEXT("Got acknowledgement for unknown message ID: %d (size: %d)"),
                MessageId,
                Size);
        }
    }
    else
    {
        // This is an unknown message.
        return;
    }
}

void FCloudMessagingHub::OnWebSocketMessageReceived(
    const void *PartialData,
    SIZE_T Size,
    SIZE_T BytesRemaining,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    TSharedRef<const FUniqueNetIdEOS> UserId)
{
    // Set up partial inbound message state.
    if (!this->PartialInboundMessages.Contains(*UserId))
    {
        this->PartialInboundMessages.Add(*UserId, MakeShared<FPartialInboundMessage>(Size + BytesRemaining));
    }
    auto &InboundMessage = this->PartialInboundMessages[*UserId];

    // Copy data to the inbound message state.
    checkf(
        InboundMessage->Offset + Size <= InboundMessage->Size,
        TEXT("Overflow in WebSocket message reconstruction!"));
    FMemory::Memcpy(InboundMessage->Buffer + InboundMessage->Offset, (uint8_t *)PartialData, Size);
    InboundMessage->Offset += Size;

    // If there are still bytes remaining, then we aren't finished yet.
    if (BytesRemaining != 0)
    {
        return;
    }

    // Otherwise, decode the message.
    this->OnCompleteWebSocketMessageReceived((void *)InboundMessage->Buffer, InboundMessage->Size, UserId);

    // Release the memory associated with the partial message state.
    this->PartialInboundMessages.Remove(*UserId);
}

bool FCloudMessagingHub::OnWebSocketSendTimeout(float DeltaSeconds, int32_t MessageId)
{
    if (this->OnMessageAcked.Contains(MessageId))
    {
        UE_LOG(
            LogRedpointEOSCloudMessagingHub,
            Warning,
            TEXT("Timeout when waiting on acknowledgement of message ID %d when sending via Cloud Messaging Hub."),
            MessageId);
        this->OnMessageAckedTimeout.Remove(MessageId);
        this->OnMessageAcked[MessageId].ExecuteIfBound(false);
        this->OnMessageAcked.Remove(MessageId);
    }
    return false;
}

void FCloudMessagingHub::LocalUserSignedIn(const FUniqueNetIdEOS &UserId)
{
    using namespace Redpoint::EOS::API::Connect;

    auto &WebSocketsModule = FModuleManager::LoadModuleChecked<FWebSocketsModule>("WebSockets");

    EOS_EResult ResultCode;
    FCopyIdToken::Result Result;
    FCopyIdToken::Execute(this->PlatformHandle, FCopyIdToken::Options{UserId.GetProductUserId()}, ResultCode, Result);
    if (ResultCode != EOS_EResult::EOS_Success)
    {
        UE_LOG(
            LogRedpointEOSCloudMessagingHub,
            Warning,
            TEXT("Unable to retrieve ID token for local user. They will not receive notifications via the Cloud "
                 "Messaging Hub."));
        return;
    }
    TArray<FString> Protocols;
    Protocols.Add("wss");
    TMap<FString, FString> Headers;
    Headers.Add("Authorization", FString::Printf(TEXT("Bearer %s"), *Result.JsonWebToken));
    FString Url = Config->GetCloudMessagingHubUrl();
    TSharedRef<IWebSocket> WebSocketForUser = WebSocketsModule.CreateWebSocket(Url, Protocols, Headers);
    this->ConnectedLocalUserSockets.Add(UserId, WebSocketForUser);
    WebSocketForUser->OnConnected().AddSP(
        this,
        &FCloudMessagingHub::OnWebSocketConnected,
        StaticCastSharedRef<const FUniqueNetIdEOS>(UserId.AsShared()));
    WebSocketForUser->OnConnectionError().AddSP(
        this,
        &FCloudMessagingHub::OnWebSocketConnectionError,
        StaticCastSharedRef<const FUniqueNetIdEOS>(UserId.AsShared()));
    WebSocketForUser->OnClosed().AddSP(
        this,
        &FCloudMessagingHub::OnWebSocketClosed,
        StaticCastSharedRef<const FUniqueNetIdEOS>(UserId.AsShared()));
    WebSocketForUser->OnRawMessage().AddSP(
        this,
        &FCloudMessagingHub::OnWebSocketMessageReceived,
        StaticCastSharedRef<const FUniqueNetIdEOS>(UserId.AsShared()));
    WebSocketForUser->Connect();
}

void FCloudMessagingHub::LocalUserSignedOut(const FUniqueNetIdEOS &UserId)
{
    if (this->ConnectedLocalUserSockets.Contains(UserId))
    {
        TSharedRef<IWebSocket> WebSocket = this->ConnectedLocalUserSockets[UserId];
        this->ConnectedLocalUserSockets.Remove(UserId);
        WebSocket->Close(1000, "Local user signed out of EOS.");
    }
}

FOnMessagingHubReceived &FCloudMessagingHub::OnMessageReceived()
{
    return this->OnMessageReceivedDelegate;
}

void FCloudMessagingHub::SendMessage(
    const FUniqueNetIdEOS &SenderId,
    const FUniqueNetIdEOS &ReceiverId,
    const FString &MessageType,
    const FString &MessageData,
    const FOnMessagingHubSent &Delegate)
{
    if (!this->ConnectedLocalUserSockets.Contains(SenderId) ||
        !this->ConnectedLocalUserSockets[SenderId]->IsConnected())
    {
        // Can't initiate the send at this time, because the WebSocket isn't connected at the
        // moment. Add it to the pending outbound messages.
        if (!this->PendingOutboundMessages.Contains(SenderId))
        {
            this->PendingOutboundMessages.Add(SenderId, TArray<FPendingOutboundMessage>());
        }
        this->PendingOutboundMessages[SenderId].Add(FPendingOutboundMessage{
            StaticCastSharedRef<const FUniqueNetIdEOS>(ReceiverId.AsShared()),
            MessageType,
            MessageData,
            Delegate});
        return;
    }

    FString ReceiverIdStr = ReceiverId.ToString();
    checkf(ReceiverIdStr.Len() == 32, TEXT("Expected recipient user ID to be exactly 32 characters long!"));
    int32_t MessageId = this->NextMessageId++;
    FString MessageRawData = FString::Printf(TEXT("%s|%s"), *MessageType, *MessageData);
    size_t DataBufferLen = sizeof(int32_t) + 32 + ((size_t)MessageRawData.Len() * 2);
    uint8_t *DataBuffer = (uint8_t *)FMemory::MallocZeroed(DataBufferLen);
    auto ReceiverIdStrAnsi = StringCast<ANSICHAR>(*ReceiverIdStr);
    FMemory::Memcpy(DataBuffer, &MessageId, sizeof(int32_t));
    FMemory::Memcpy(DataBuffer + sizeof(int32_t), ReceiverIdStrAnsi.Get(), 32);
    FMemory::Memcpy(DataBuffer + sizeof(int32_t) + 32, *MessageRawData, (size_t)MessageRawData.Len() * 2);
    this->OnMessageAcked.Add(MessageId, Delegate);
    this->OnMessageAckedTimeout.Add(
        MessageId,
        FTSTicker::GetCoreTicker().AddTicker(
            FTickerDelegate::CreateSP(this, &FCloudMessagingHub::OnWebSocketSendTimeout, MessageId),
            5.0f));
    UE_LOG(
        LogRedpointEOSCloudMessagingHub,
        VeryVerbose,
        TEXT("(send) %s -> %s: %s: %s"),
        *SenderId.ToString(),
        *ReceiverId.ToString(),
        *MessageType,
        *MessageData);
    this->ConnectedLocalUserSockets[SenderId]->Send(DataBuffer, DataBufferLen, true);
}
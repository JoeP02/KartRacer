// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "OnlineSubsystemRedpointEOS/Shared/UniqueNetIdEOS.h"

DECLARE_MULTICAST_DELEGATE_FourParams(
    FOnMessagingHubReceived,
    const FUniqueNetIdEOS & /* SenderId */,
    const FUniqueNetIdEOS & /* ReceiverId */,
    const FString & /* MessageType */,
    const FString & /* MessageData */);

DECLARE_DELEGATE_OneParam(FOnMessagingHubSent, bool /* bWasReceived */);

class ONLINESUBSYSTEMREDPOINTEOS_API IMessagingHub
{
public:
    /**
	 * Called by the online subsystem when a local user is signed in.
	 */
    virtual void LocalUserSignedIn(const FUniqueNetIdEOS &UserId){};

	/**
	 * Called by the online subsystem when a local user is signed out.
	 */
    virtual void LocalUserSignedOut(const FUniqueNetIdEOS &UserId){};

    /**
     * The delegate that is fired whenever a message arrives from another EOS user.
     */
    virtual FOnMessagingHubReceived &OnMessageReceived() = 0;

    /**
     * Send a message to another EOS user.
     */
    virtual void SendMessage(
        const FUniqueNetIdEOS &SenderId,
        const FUniqueNetIdEOS &ReceiverId,
        const FString &MessageType,
        const FString &MessageData,
        const FOnMessagingHubSent &Delegate = FOnMessagingHubSent()) = 0;
};
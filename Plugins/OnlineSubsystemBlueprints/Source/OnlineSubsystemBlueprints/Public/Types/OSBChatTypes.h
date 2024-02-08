// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Interfaces/OnlineChatInterface.h"
#include "OSBSessionTypes.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBChatTypes.generated.h"

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FChatRoomConfigBP
{
    GENERATED_BODY()

public:
	/** Should this room be rejoined on disconnection */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Chat")
    bool bRejoinOnDisconnect = false;

	/** Is there a password required to join the room (owner only) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Chat")
    bool bPasswordRequired = false;

	/** Password to join the room (owner only) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Chat")
    FString Password;

	/** Should we announce members joining and leaving? This may incur a performance cost if members need to be validated. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Chat")
    bool bAnnounceMembers = false;

    static FChatRoomConfigBP FromNative(const FChatRoomConfig &InObj);
    FChatRoomConfig ToNative() const;
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FChatRoomInfoBP
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    bool bIsValid = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    FString RoomId;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    FUniqueNetIdRepl OwnerId;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    FString Subject;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    bool bPrivate = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    bool bJoined = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    FChatRoomConfigBP RoomConfig;

    static FChatRoomInfoBP FromNative(const FChatRoomInfo &InObj);

    static FChatRoomInfoBP FromNative(const TSharedPtr<FChatRoomInfo> &InObj);
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FChatRoomMemberBP
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    bool bIsValid = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    FUniqueNetIdRepl UserId;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    FString Nickname;

    static FChatRoomMemberBP FromNative(const FChatRoomMember &InObj);

    static FChatRoomMemberBP FromNative(const TSharedPtr<FChatRoomMember> &InObj);
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FChatMessageBP
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    FUniqueNetIdRepl UserId;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    FString Nickname;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    FString Body;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Chat")
    FDateTime Timestamp;

    static FChatMessageBP FromNative(const FChatMessage &InObj);
};
// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Interfaces/OnlinePresenceInterface.h"

#include "OSBOnlineUserPresenceData.generated.h"

// Uh, why is this FOnlineUserPresenceStatusState and not EOnlineUserPresenceStatusState_ ?
UENUM(BlueprintType, Meta = (ScriptName = "EOnlinePresenceState"))
enum class FOnlineUserPresenceStatusState : uint8
{
    Online,
    Offline,
    Away,
    ExtendedAway,
    DoNotDisturb,
    Chat,
};

UENUM(BlueprintType, Meta = (ScriptName = "EOnlineCachedResult"))
enum class EOnlineCachedResult_ : uint8
{
    /** The requested data was found and returned successfully. */
    Success,
    /** The requested data was not found in the cache, and the out parameter was not modified. */
    NotFound
};

USTRUCT(BlueprintType, Meta = (ScriptName = "FOnlineUserPresenceStatus"))
struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineUserPresenceStatusData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    FString Status;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    FOnlineUserPresenceStatusState State = FOnlineUserPresenceStatusState::Online;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    TMap<FString, FString> Properties;

    static FOnlineUserPresenceStatusData FromNative(const FOnlineUserPresenceStatus &InObj);
    FOnlineUserPresenceStatus ToNative() const;
};

USTRUCT(BlueprintType, Meta = (ScriptName = "FOnlineUserPresence"))
struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineUserPresenceData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    FUniqueNetIdRepl SessionId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    bool IsOnline = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    bool IsPlaying = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    bool IsPlayingThisGame = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    bool IsJoinable = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    bool HasVoiceSupport = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    FDateTime LastOnline;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Online")
    FOnlineUserPresenceStatusData Status;

    static FOnlineUserPresenceData FromNative(TSharedPtr<FOnlineUserPresence> InObj);
    static FOnlineUserPresenceData FromNative(const FOnlineUserPresence &InObj);
    FOnlineUserPresence ToNative() const;
};
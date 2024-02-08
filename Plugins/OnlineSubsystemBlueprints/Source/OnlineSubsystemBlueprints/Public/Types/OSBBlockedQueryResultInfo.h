// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IMessageSanitizerInterface.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBBlockedQueryResultInfo.generated.h"

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FBlockedQueryResultInfo
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool Blocked = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool BlockedNonFriends = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString UserId;

    static FBlockedQueryResultInfo FromNative(const FBlockedQueryResult &InObj);
    FBlockedQueryResult ToNative();
};
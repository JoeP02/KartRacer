// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineError.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBOnlineErrorInfo.generated.h"

/**
 * Represents the result from an online operation.
 */
USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineErrorInfo
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool Successful = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString ErrorRaw;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString ErrorCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FText ErrorMessage;

    static FOnlineErrorInfo FromNative(const FOnlineError &Obj);
    FOnlineError ToNative();
};
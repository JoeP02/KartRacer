// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Interfaces/OnlineGameActivityInterface.h"
#include "OSBSessionTypes.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBGameActivityTypes.generated.h"

UENUM(BlueprintType, Meta = (ScriptName = "EOnlineActivityOutcome"))
enum class EOnlineActivityOutcome_ : uint8
{
    /** Activity has been completed successfully */
    Completed,
    /** Activity attempt failed to be completed */
    Failed,
    /** The activity was cancelled */
    Cancelled
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineActivityTasksToResetBP
{
    GENERATED_BODY()

public:
    /** If the structure values are set */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|GameActivity")
    bool bSet = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|GameActivity")
    TArray<FString> InProgressTasks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|GameActivity")
    TArray<FString> CompletedTasks;

#if defined(REDPOINT_OSB_UE_4_25_OR_LATER)
    static FOnlineActivityTasksToResetBP FromNative(const TOptional<FOnlineActivityTasksToReset> &InObj);
    TOptional<FOnlineActivityTasksToReset> ToNative() const;
#endif
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineActivityPlayerLocationBP
{
    GENERATED_BODY()

public:
    /** If the structure values are set */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|GameActivity")
    bool bSet = false;

    /** Current reported zone*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|GameActivity")
    FString ZoneId;

    /** Coordinates */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|GameActivity")
    FVector Coordinates = FVector(0, 0, 0);

#if defined(REDPOINT_OSB_UE_4_25_OR_LATER)
    static FOnlineActivityPlayerLocationBP FromNative(const TOptional<FOnlineActivityPlayerLocation> &InObj);
    TOptional<FOnlineActivityPlayerLocation> ToNative() const;
#endif
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FOptionalOnlineSessionSearchResultBP
{
    GENERATED_BODY()

public:
    /** If the search result is available */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|GameActivity")
    bool bSet = false;

    /** The search result data, if available */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|GameActivity")
    FOnlineSessionSearchResultBP SearchResult;

#if defined(REDPOINT_OSB_UE_4_25_OR_LATER)
    static FOptionalOnlineSessionSearchResultBP FromNative(const FOnlineSessionSearchResult *InObj);
#endif
};

#if defined(REDPOINT_OSB_UE_4_25_OR_LATER)
FOnlineEventParms ConvertMapToEventParams(const TMap<FString, FVariantDataBP> &EventParams);
TMap<FString, FVariantDataBP> ConvertEventParamsToMap(const FOnlineEventParms &EventParams);
#endif
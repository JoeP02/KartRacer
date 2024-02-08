// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "OSBSessionTypes.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBAchievementTypes.generated.h"

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineAchievementBP
{
    GENERATED_BODY()

public:
    /** The id of the achievement */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Achievements")
    FString Id;

    /** The progress towards completing this achievement: 0.0-100.0 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Achievements")
    float Progress = 0.0f;

    static FOnlineAchievementBP FromNative(FOnlineAchievement Achievement);
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineAchievementDescBP
{
    GENERATED_BODY()

public:
    /** The localized title of the achievement */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Achievements")
    FText Title;

    /** The localized locked description of the achievement */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Achievements")
    FText LockedDesc;

    /** The localized unlocked description of the achievement */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Achievements")
    FText UnlockedDesc;

    /** Flag for whether the achievement is hidden */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Achievements")
    bool bIsHidden = false;

    /** The date/time the achievement was unlocked */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Online|Achievements")
    FDateTime UnlockTime;

    static FOnlineAchievementDescBP FromNative(FOnlineAchievementDesc AchievementDescription);
};

/**
 * The achievement writing object. WARNING: OSS implementations differ wildly in their implementation of WriteAchievements. This class is only meant to be used with OSS implementations that misuse the WriteAchievements function to do direct achievement unlocks. If you are using Epic's EOS implementation, you must use UpdateStats on the Online Stats subsystem instead!
 */
UCLASS(BlueprintType, Meta = (IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineAchievementsWrite : public UObject
{
    GENERATED_BODY()

public:
    UOnlineAchievementsWrite()
        : UObject(), AchievementsWrite(MakeShared<FOnlineAchievementsWrite, ESPMode::ThreadSafe>())
    {
    }

    UOnlineAchievementsWrite(const FObjectInitializer &ObjectInitializer)
        : UObject(ObjectInitializer), AchievementsWrite(MakeShared<FOnlineAchievementsWrite, ESPMode::ThreadSafe>())
    {
    }

    FOnlineAchievementsWriteRef AchievementsWrite;

    /** Sets an achievement to be unlocked via it's ID or name. WARNING: OSS implementations differ wildly in their implementation of WriteAchievements. This function is only meant to be used with OSS implementations that misuse the WriteAchievements function to do direct achievement unlocks. If you are using Epic's EOS implementation, you must use UpdateStats on the Online Stats subsystem instead! */
    UFUNCTION(
        BlueprintCallable,
        Category = "Online|Achievements",
        meta = (DisplayName = "Set Achievement Progress (READ WARNING IN FUNCTION DESCRIPTION)"))
    void SetAchievementProgress(FName AchievementId, float AchievementProgress);

public:
    FOnlineAchievementsWriteRef &GetAchievementsWrite();
};
// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Engine/GameInstance.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Types/OSBOnlineUserRef.h"
#include "Types/OSBFriendTypes.h"
#include "Types/OSBOnlineAccountCredential.h"
#include "Types/OSBOnlineErrorInfo.h"
#include "Types/OSBOnlineRecentPlayerRef.h"
#include "Types/OSBOnlineLoginStatus.h"
#include "Types/OSBBlockedQueryResultInfo.h"
#include "Types/OSBOnlineUserPrivilege.h"
#include "Types/OSBMessageTypes.h"
#include "Types/OSBChatTypes.h"
#include "Types/OSBExternalUITypes.h"
#include "Types/OSBFileTypes.h"
#include "Types/OSBPartyTypes.h"
#include "Types/OSBLobbyTypes.h"
#include "Types/OSBSessionTypes.h"
#include "Types/OSBLeaderboardTypes.h"
#include "Types/OSBStatsTypes.h"
#include "Types/OSBStoreV2Types.h"
#include "Types/OSBPurchaseTypes.h"
#include "Types/OSBEntitlementTypes.h"
#include "Types/OSBAchievementTypes.h"
#include "Types/OSBVoiceChatTypes.h"
#include "Types/OSBGameActivityTypes.h"
#include "Helpers/ArrayConversion.h"
#include "Helpers/UniqueNetIdConversion.h"
#include "Interfaces/OnlineAchievementsInterface.h"

#include "OnlineAchievementsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAchievements_AchievementUnlocked_BP, FUniqueNetIdRepl, Param1, FString, Param2);

UCLASS(BlueprintType)
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineAchievementsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    friend class UOnlineHelpers;

private:
    struct FWorldContext* WorldContext;
    TWeakPtr<class IOnlineAchievements, ESPMode::ThreadSafe> HandleWk;
    TSharedPtr<class IOnlineAchievements, ESPMode::ThreadSafe> GetHandle();
    bool IsHandleValid(const TSharedPtr<class IOnlineAchievements, ESPMode::ThreadSafe>& InHandle);
    FDelegateHandle DelegateHandle_OnAchievementUnlocked;

public:
    // When async functions use global events as callbacks (such as in identity and session),
    // we need to prevent multiple requests running at the same time where those results would
    // have the same identifying data in the callback (because then we don't know which result
    // belongs to which request). For these types of async functions, they use this set to make
    // sure that only one unique request runs at a time.
    TSet<FString> __InFlightRequests;

    static FName OSSNameToAssignDuringConstruction;
    FName OSSName = NAME_Default;
    UOnlineAchievementsSubsystem();
    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "Online|Achievements")
    bool IsSubsystemAvailable();

    UPROPERTY(BlueprintAssignable, Category = "Online|Achievements")
    FAchievements_AchievementUnlocked_BP OnAchievementUnlocked;

    friend class UOnlineAchievementsSubsystemWriteAchievements;

    friend class UOnlineAchievementsSubsystemQueryAchievements;

    friend class UOnlineAchievementsSubsystemQueryAchievementDescriptions;

    UFUNCTION(BlueprintCallable, Category = "Online|Achievements")
    EOnlineCachedResult_ GetCachedAchievement(FUniqueNetIdRepl PlayerId, FString AchievementId, FOnlineAchievementBP& OutAchievement);

    UFUNCTION(BlueprintCallable, Category = "Online|Achievements")
    EOnlineCachedResult_ GetCachedAchievements(FUniqueNetIdRepl PlayerId, TArray<FOnlineAchievementBP>& OutAchievements);

    UFUNCTION(BlueprintCallable, Category = "Online|Achievements")
    EOnlineCachedResult_ GetCachedAchievementDescription(FString AchievementId, FOnlineAchievementDescBP& OutAchievementDesc);
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineAchievementsSubsystemWriteAchievementsCallbackPin, FUniqueNetIdRepl, Param1, bool, Param2);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineAchievementsSubsystemWriteAchievements : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineAchievementsSubsystemWriteAchievementsCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineAchievementsSubsystemWriteAchievementsCallbackPin OnAchievementsWritten;

    UFUNCTION(BlueprintCallable, Category = "Online|Achievements", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineAchievementsSubsystemWriteAchievements* WriteAchievements(
        UOnlineAchievementsSubsystem* Subsystem
        ,FUniqueNetIdRepl PlayerId, UOnlineAchievementsWrite* WriteObject
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineAchievementsSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnAchievementsWritten(const FUniqueNetId& Param1, bool Param2);

    UPROPERTY()
    FUniqueNetIdRepl __Store__PlayerId;

UPROPERTY()
    UOnlineAchievementsWrite* __Store__WriteObject;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineAchievementsSubsystemQueryAchievementsCallbackPin, FUniqueNetIdRepl, LocalUserId, bool, bWasSuccessful);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineAchievementsSubsystemQueryAchievements : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineAchievementsSubsystemQueryAchievementsCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineAchievementsSubsystemQueryAchievementsCallbackPin OnQueryAchievementsComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|Achievements", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineAchievementsSubsystemQueryAchievements* QueryAchievements(
        UOnlineAchievementsSubsystem* Subsystem
        ,FUniqueNetIdRepl PlayerId
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineAchievementsSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnQueryAchievementsComplete(const FUniqueNetId& LocalUserId, const bool bWasSuccessful);

    UPROPERTY()
    FUniqueNetIdRepl __Store__PlayerId;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineAchievementsSubsystemQueryAchievementDescriptionsCallbackPin, FUniqueNetIdRepl, LocalUserId, bool, bWasSuccessful);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineAchievementsSubsystemQueryAchievementDescriptions : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineAchievementsSubsystemQueryAchievementDescriptionsCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineAchievementsSubsystemQueryAchievementDescriptionsCallbackPin OnQueryAchievementsComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|Achievements", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineAchievementsSubsystemQueryAchievementDescriptions* QueryAchievementDescriptions(
        UOnlineAchievementsSubsystem* Subsystem
        ,FUniqueNetIdRepl PlayerId
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineAchievementsSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnQueryAchievementsComplete(const FUniqueNetId& LocalUserId, const bool bWasSuccessful);

    UPROPERTY()
    FUniqueNetIdRepl __Store__PlayerId;
};
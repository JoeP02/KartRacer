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
#include "Interfaces/OnlineGameActivityInterface.h"
#include "Interfaces/OnlineEventsInterface.h"

#include "OnlineGameActivitySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGameActivity_GameActivityActivationRequested_BP, FUniqueNetIdRepl, LocalUserId, FString, ActivityId, FOptionalOnlineSessionSearchResultBP, SessionInfo);

UCLASS(BlueprintType)
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineGameActivitySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    friend class UOnlineHelpers;

private:
    struct FWorldContext* WorldContext;
    TWeakPtr<class IOnlineGameActivity, ESPMode::ThreadSafe> HandleWk;
    TSharedPtr<class IOnlineGameActivity, ESPMode::ThreadSafe> GetHandle();
    bool IsHandleValid(const TSharedPtr<class IOnlineGameActivity, ESPMode::ThreadSafe>& InHandle);
    FDelegateHandle DelegateHandle_OnGameActivityActivationRequested;

public:
    // When async functions use global events as callbacks (such as in identity and session),
    // we need to prevent multiple requests running at the same time where those results would
    // have the same identifying data in the callback (because then we don't know which result
    // belongs to which request). For these types of async functions, they use this set to make
    // sure that only one unique request runs at a time.
    TSet<FString> __InFlightRequests;

    static FName OSSNameToAssignDuringConstruction;
    FName OSSName = NAME_Default;
    UOnlineGameActivitySubsystem();
    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "Online|GameActivity")
    bool IsSubsystemAvailable();

    UPROPERTY(BlueprintAssignable, Category = "Online|GameActivity")
    FGameActivity_GameActivityActivationRequested_BP OnGameActivityActivationRequested;

    friend class UOnlineGameActivitySubsystemStartActivity;

    friend class UOnlineGameActivitySubsystemEndActivity;

    friend class UOnlineGameActivitySubsystemResetAllActiveActivities;

    friend class UOnlineGameActivitySubsystemResumeActivity;

    friend class UOnlineGameActivitySubsystemSetActivityAvailability;

    friend class UOnlineGameActivitySubsystemSetActivityPriority;

    // @generator-incompatible
    // bool QueryActivitiesForUsers(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& UserAccounts, TOptional<int32> MaxUserActivitiesReturned, const FOnQueryUserActivitiesComplete& CompletionDelegate);

    UFUNCTION(BlueprintCallable, Category = "Online|GameActivity")
    void UpdatePlayerLocation(FUniqueNetIdRepl LocalUserId, FOnlineActivityPlayerLocationBP& ActivityPlayerLocation);
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnlineGameActivitySubsystemStartActivityCallbackPin, FUniqueNetIdRepl, LocalUserId, FString, ActivityId, FOnlineErrorInfo, Status);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineGameActivitySubsystemStartActivity : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemStartActivityCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemStartActivityCallbackPin OnStartActivityComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|GameActivity", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineGameActivitySubsystemStartActivity* StartActivity(
        UOnlineGameActivitySubsystem* Subsystem
        ,FUniqueNetIdRepl LocalUserId, FString ActivityId, TMap<FString, FVariantDataBP> Params
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineGameActivitySubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnStartActivityComplete(const FUniqueNetId& LocalUserId, const FString& ActivityId, const FOnlineError& Status);

    UPROPERTY()
    FUniqueNetIdRepl __Store__LocalUserId;

UPROPERTY()
    FString __Store__ActivityId;

UPROPERTY()
    TMap<FString, FVariantDataBP> __Store__Parms;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnlineGameActivitySubsystemEndActivityCallbackPin, FUniqueNetIdRepl, LocalUserId, FString, ActivityId, EOnlineActivityOutcome_, Outcome, FOnlineErrorInfo, Status);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineGameActivitySubsystemEndActivity : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemEndActivityCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemEndActivityCallbackPin OnEndActivityComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|GameActivity", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineGameActivitySubsystemEndActivity* EndActivity(
        UOnlineGameActivitySubsystem* Subsystem
        ,FUniqueNetIdRepl LocalUserId, FString ActivityId, EOnlineActivityOutcome_ ActivityOutcome, TMap<FString, FVariantDataBP> Params
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineGameActivitySubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnEndActivityComplete(const FUniqueNetId& LocalUserId, const FString& ActivityId, const EOnlineActivityOutcome& Outcome, const FOnlineError& Status);

    UPROPERTY()
    FUniqueNetIdRepl __Store__LocalUserId;

UPROPERTY()
    FString __Store__ActivityId;

UPROPERTY()
    EOnlineActivityOutcome_ __Store__ActivityOutcome;

UPROPERTY()
    TMap<FString, FVariantDataBP> __Store__Parms;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineGameActivitySubsystemResetAllActiveActivitiesCallbackPin, FUniqueNetIdRepl, LocalUserId, FOnlineErrorInfo, Status);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineGameActivitySubsystemResetAllActiveActivities : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemResetAllActiveActivitiesCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemResetAllActiveActivitiesCallbackPin OnResetAllActiveActivitiesComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|GameActivity", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineGameActivitySubsystemResetAllActiveActivities* ResetAllActiveActivities(
        UOnlineGameActivitySubsystem* Subsystem
        ,FUniqueNetIdRepl LocalUserId
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineGameActivitySubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnResetAllActiveActivitiesComplete(const FUniqueNetId& LocalUserId, const FOnlineError& Status);

    UPROPERTY()
    FUniqueNetIdRepl __Store__LocalUserId;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnlineGameActivitySubsystemResumeActivityCallbackPin, FUniqueNetIdRepl, LocalUserId, FString, ActivityId, FOnlineErrorInfo, Status);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineGameActivitySubsystemResumeActivity : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemResumeActivityCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemResumeActivityCallbackPin OnResumeActivityComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|GameActivity", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineGameActivitySubsystemResumeActivity* ResumeActivity(
        UOnlineGameActivitySubsystem* Subsystem
        ,FUniqueNetIdRepl LocalUserId, FString ActivityId, FOnlineActivityTasksToResetBP TasksToReset
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineGameActivitySubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnResumeActivityComplete(const FUniqueNetId& LocalUserId, const FString& ActivityId, const FOnlineError& Status);

    UPROPERTY()
    FUniqueNetIdRepl __Store__LocalUserId;

UPROPERTY()
    FString __Store__ActivityId;

UPROPERTY()
    FOnlineActivityTasksToResetBP __Store__TasksToReset;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineGameActivitySubsystemSetActivityAvailabilityCallbackPin, FUniqueNetIdRepl, LocalUserId, FOnlineErrorInfo, Status);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineGameActivitySubsystemSetActivityAvailability : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemSetActivityAvailabilityCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemSetActivityAvailabilityCallbackPin OnSetActivityAvailabilityComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|GameActivity", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineGameActivitySubsystemSetActivityAvailability* SetActivityAvailability(
        UOnlineGameActivitySubsystem* Subsystem
        ,FUniqueNetIdRepl LocalUserId, FString ActivityId, bool bEnabled
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineGameActivitySubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnSetActivityAvailabilityComplete(const FUniqueNetId& LocalUserId, const FOnlineError& Status);

    UPROPERTY()
    FUniqueNetIdRepl __Store__LocalUserId;

UPROPERTY()
    FString __Store__ActivityId;

UPROPERTY()
    bool __Store__bEnabled;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineGameActivitySubsystemSetActivityPriorityCallbackPin, FUniqueNetIdRepl, LocalUserId, FOnlineErrorInfo, Status);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineGameActivitySubsystemSetActivityPriority : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemSetActivityPriorityCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineGameActivitySubsystemSetActivityPriorityCallbackPin OnSetActivityPriorityComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|GameActivity", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineGameActivitySubsystemSetActivityPriority* SetActivityPriority(
        UOnlineGameActivitySubsystem* Subsystem
        ,FUniqueNetIdRepl LocalUserId, TMap<FString, int32> PrioritizedActivities
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineGameActivitySubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnSetActivityPriorityComplete(const FUniqueNetId& LocalUserId, const FOnlineError& Status);

    UPROPERTY()
    FUniqueNetIdRepl __Store__LocalUserId;

UPROPERTY()
    TMap<FString, int32> __Store__PrioritizedActivities;
};
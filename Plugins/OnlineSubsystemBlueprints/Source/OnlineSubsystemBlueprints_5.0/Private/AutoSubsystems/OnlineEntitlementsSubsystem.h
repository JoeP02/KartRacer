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
#include "Interfaces/OnlineEntitlementsInterface.h"

#include "OnlineEntitlementsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FEntitlements_QueryEntitlementsComplete_BP, bool, bWasSuccessful, FUniqueNetIdRepl, UserId, FString, Namespace, FString, Error);

UCLASS(BlueprintType)
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineEntitlementsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    friend class UOnlineHelpers;

private:
    struct FWorldContext* WorldContext;
    TWeakPtr<class IOnlineEntitlements, ESPMode::ThreadSafe> HandleWk;
    TSharedPtr<class IOnlineEntitlements, ESPMode::ThreadSafe> GetHandle();
    bool IsHandleValid(const TSharedPtr<class IOnlineEntitlements, ESPMode::ThreadSafe>& InHandle);
    FDelegateHandle DelegateHandle_OnQueryEntitlementsComplete;

public:
    // When async functions use global events as callbacks (such as in identity and session),
    // we need to prevent multiple requests running at the same time where those results would
    // have the same identifying data in the callback (because then we don't know which result
    // belongs to which request). For these types of async functions, they use this set to make
    // sure that only one unique request runs at a time.
    TSet<FString> __InFlightRequests;

    static FName OSSNameToAssignDuringConstruction;
    FName OSSName = NAME_Default;
    UOnlineEntitlementsSubsystem();
    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "Online|Entitlements")
    bool IsSubsystemAvailable();

    UPROPERTY(BlueprintAssignable, Category = "Online|Entitlements")
    FEntitlements_QueryEntitlementsComplete_BP OnQueryEntitlementsComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|Entitlements")
    UOnlineEntitlement* GetEntitlement(FUniqueNetIdRepl UserId, FString EntitlementId);

    UFUNCTION(BlueprintCallable, Category = "Online|Entitlements")
    UOnlineEntitlement* GetItemEntitlement(FUniqueNetIdRepl UserId, FString ItemId);

    UFUNCTION(BlueprintCallable, Category = "Online|Entitlements")
    void GetAllEntitlements(FUniqueNetIdRepl UserId, FString Namespace, TArray<UOnlineEntitlement*>& OutUserEntitlements);

    friend class UOnlineEntitlementsSubsystemQueryEntitlements;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnlineEntitlementsSubsystemQueryEntitlementsCallbackPin, bool, bWasSuccessful, FUniqueNetIdRepl, UserId, FString, Namespace, FString, Error);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineEntitlementsSubsystemQueryEntitlements : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineEntitlementsSubsystemQueryEntitlementsCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineEntitlementsSubsystemQueryEntitlementsCallbackPin OnQueryEntitlementsComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|Entitlements", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineEntitlementsSubsystemQueryEntitlements* QueryEntitlements(
        UOnlineEntitlementsSubsystem* Subsystem
        ,FUniqueNetIdRepl UserId, FString Namespace, FPagedQueryBP Page
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineEntitlementsSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    FDelegateHandle DelegateHandle_OnQueryEntitlementsComplete;
    void HandleCallback_OnQueryEntitlementsComplete(bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Namespace, const FString& Error);

    UPROPERTY()
    FUniqueNetIdRepl __Store__UserId;

UPROPERTY()
    FString __Store__Namespace;

UPROPERTY()
    FPagedQueryBP __Store__Page;
};
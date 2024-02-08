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
#include "Interfaces/OnlineStoreInterfaceV2.h"

#include "OnlineStoreV2Subsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoreV2_QueryForAvailablePurchasesComplete_BP, bool, Param1);

UCLASS(BlueprintType)
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineStoreV2Subsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    friend class UOnlineHelpers;

private:
    struct FWorldContext* WorldContext;
    TWeakPtr<class IOnlineStoreV2, ESPMode::ThreadSafe> HandleWk;
    TSharedPtr<class IOnlineStoreV2, ESPMode::ThreadSafe> GetHandle();
    bool IsHandleValid(const TSharedPtr<class IOnlineStoreV2, ESPMode::ThreadSafe>& InHandle);
    FDelegateHandle DelegateHandle_OnQueryForAvailablePurchasesComplete;

public:
    // When async functions use global events as callbacks (such as in identity and session),
    // we need to prevent multiple requests running at the same time where those results would
    // have the same identifying data in the callback (because then we don't know which result
    // belongs to which request). For these types of async functions, they use this set to make
    // sure that only one unique request runs at a time.
    TSet<FString> __InFlightRequests;

    static FName OSSNameToAssignDuringConstruction;
    FName OSSName = NAME_Default;
    UOnlineStoreV2Subsystem();
    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "Online|StoreV2")
    bool IsSubsystemAvailable();

    UPROPERTY(BlueprintAssignable, Category = "Online|StoreV2")
    FStoreV2_QueryForAvailablePurchasesComplete_BP OnQueryForAvailablePurchasesComplete;

    friend class UOnlineStoreV2SubsystemQueryCategories;

    UFUNCTION(BlueprintCallable, Category = "Online|StoreV2")
    void GetCategories(TArray<FOnlineStoreCategoryBP>& OutCategories);

    friend class UOnlineStoreV2SubsystemQueryOffersByFilter;

    friend class UOnlineStoreV2SubsystemQueryOffersById;

    UFUNCTION(BlueprintCallable, Category = "Online|StoreV2")
    void GetOffers(TArray<UOnlineStoreOffer*>& OutOffers);

    UFUNCTION(BlueprintPure, Category = "Online|StoreV2")
    UOnlineStoreOffer* GetOffer(FString OfferId);
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineStoreV2SubsystemQueryCategoriesCallbackPin, bool, bWasSuccessful, FString, Error);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineStoreV2SubsystemQueryCategories : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineStoreV2SubsystemQueryCategoriesCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineStoreV2SubsystemQueryCategoriesCallbackPin OnQueryOnlineStoreCategoriesComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|StoreV2", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineStoreV2SubsystemQueryCategories* QueryCategories(
        UOnlineStoreV2Subsystem* Subsystem
        ,FUniqueNetIdRepl UserId
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineStoreV2Subsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnQueryOnlineStoreCategoriesComplete(bool bWasSuccessful, const FString& Error);

    UPROPERTY()
    FUniqueNetIdRepl __Store__UserId;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnlineStoreV2SubsystemQueryOffersByFilterCallbackPin, bool, bWasSuccessful, const TArray<FString>&, OfferIds, FString, Error);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineStoreV2SubsystemQueryOffersByFilter : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineStoreV2SubsystemQueryOffersByFilterCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineStoreV2SubsystemQueryOffersByFilterCallbackPin OnQueryOnlineStoreOffersComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|StoreV2", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineStoreV2SubsystemQueryOffersByFilter* QueryOffersByFilter(
        UOnlineStoreV2Subsystem* Subsystem
        ,FUniqueNetIdRepl UserId, FOnlineStoreFilterBP Filter
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineStoreV2Subsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnQueryOnlineStoreOffersComplete(bool bWasSuccessful, const TArray<FUniqueOfferId>& OfferIds, const FString& Error);

    UPROPERTY()
    FUniqueNetIdRepl __Store__UserId;

UPROPERTY()
    FOnlineStoreFilterBP __Store__Filter;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnlineStoreV2SubsystemQueryOffersByIdCallbackPin, bool, bWasSuccessful, const TArray<FString>&, OfferIds, FString, Error);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineStoreV2SubsystemQueryOffersById : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineStoreV2SubsystemQueryOffersByIdCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineStoreV2SubsystemQueryOffersByIdCallbackPin OnQueryOnlineStoreOffersComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|StoreV2", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineStoreV2SubsystemQueryOffersById* QueryOffersById(
        UOnlineStoreV2Subsystem* Subsystem
        ,FUniqueNetIdRepl UserId, TArray<FString> OfferIds
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineStoreV2Subsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnQueryOnlineStoreOffersComplete(bool bWasSuccessful, const TArray<FUniqueOfferId>& OfferIds, const FString& Error);

    UPROPERTY()
    FUniqueNetIdRepl __Store__UserId;

UPROPERTY()
    TArray<FString> __Store__OfferIds;
};
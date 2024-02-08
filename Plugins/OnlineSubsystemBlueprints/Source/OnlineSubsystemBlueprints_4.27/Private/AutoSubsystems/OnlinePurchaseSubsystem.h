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
#include "Interfaces/OnlinePurchaseInterface.h"

#include "OnlinePurchaseSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPurchase_UnexpectedPurchaseReceipt_BP, FUniqueNetIdRepl, UserId);

UCLASS(BlueprintType)
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlinePurchaseSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    friend class UOnlineHelpers;

private:
    struct FWorldContext* WorldContext;
    TWeakPtr<class IOnlinePurchase, ESPMode::ThreadSafe> HandleWk;
    TSharedPtr<class IOnlinePurchase, ESPMode::ThreadSafe> GetHandle();
    bool IsHandleValid(const TSharedPtr<class IOnlinePurchase, ESPMode::ThreadSafe>& InHandle);
    FDelegateHandle DelegateHandle_OnUnexpectedPurchaseReceipt;

public:
    // When async functions use global events as callbacks (such as in identity and session),
    // we need to prevent multiple requests running at the same time where those results would
    // have the same identifying data in the callback (because then we don't know which result
    // belongs to which request). For these types of async functions, they use this set to make
    // sure that only one unique request runs at a time.
    TSet<FString> __InFlightRequests;

    static FName OSSNameToAssignDuringConstruction;
    FName OSSName = NAME_Default;
    UOnlinePurchaseSubsystem();
    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "Online|Purchase")
    bool IsSubsystemAvailable();

    UPROPERTY(BlueprintAssignable, Category = "Online|Purchase")
    FPurchase_UnexpectedPurchaseReceipt_BP OnUnexpectedPurchaseReceipt;

    UFUNCTION(BlueprintCallable, Category = "Online|Purchase")
    bool IsAllowedToPurchase(FUniqueNetIdRepl UserId);

    friend class UOnlinePurchaseSubsystemCheckout;

    // @generator-excluded-with-pick
    // void FinalizePurchase(const FUniqueNetId& UserId, const FString& ReceiptId);

    UFUNCTION(BlueprintCallable, Category = "Online|Purchase")
    void FinalizePurchase(FUniqueNetIdRepl UserId, FString ReceiptId, FString ReceiptInfo);

    friend class UOnlinePurchaseSubsystemRedeemCode;

    friend class UOnlinePurchaseSubsystemQueryReceipts;

    UFUNCTION(BlueprintCallable, Category = "Online|Purchase")
    void GetReceipts(FUniqueNetIdRepl UserId, TArray<UPurchaseReceipt*>& OutReceipts);

    friend class UOnlinePurchaseSubsystemFinalizeReceiptValidationInfo;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlinePurchaseSubsystemCheckoutCallbackPin, FOnlineErrorInfo, Result, UPurchaseReceipt*, Receipt);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlinePurchaseSubsystemCheckout : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlinePurchaseSubsystemCheckoutCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlinePurchaseSubsystemCheckoutCallbackPin OnPurchaseCheckoutComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|Purchase", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlinePurchaseSubsystemCheckout* Checkout(
        UOnlinePurchaseSubsystem* Subsystem
        ,FUniqueNetIdRepl UserId, FPurchaseCheckoutRequestBP CheckoutRequest
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlinePurchaseSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnPurchaseCheckoutComplete(const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt);

    UPROPERTY()
    FUniqueNetIdRepl __Store__UserId;

UPROPERTY()
    FPurchaseCheckoutRequestBP __Store__CheckoutRequest;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlinePurchaseSubsystemRedeemCodeCallbackPin, FOnlineErrorInfo, Result, UPurchaseReceipt*, Receipt);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlinePurchaseSubsystemRedeemCode : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlinePurchaseSubsystemRedeemCodeCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlinePurchaseSubsystemRedeemCodeCallbackPin OnPurchaseRedeemCodeComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|Purchase", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlinePurchaseSubsystemRedeemCode* RedeemCode(
        UOnlinePurchaseSubsystem* Subsystem
        ,FUniqueNetIdRepl UserId, FRedeemCodeRequestBP RedeemCodeRequest
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlinePurchaseSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnPurchaseRedeemCodeComplete(const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt);

    UPROPERTY()
    FUniqueNetIdRepl __Store__UserId;

UPROPERTY()
    FRedeemCodeRequestBP __Store__RedeemCodeRequest;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlinePurchaseSubsystemQueryReceiptsCallbackPin, FOnlineErrorInfo, Result);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlinePurchaseSubsystemQueryReceipts : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlinePurchaseSubsystemQueryReceiptsCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlinePurchaseSubsystemQueryReceiptsCallbackPin OnQueryReceiptsComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|Purchase", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlinePurchaseSubsystemQueryReceipts* QueryReceipts(
        UOnlinePurchaseSubsystem* Subsystem
        ,FUniqueNetIdRepl UserId, bool bRestoreReceipts
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlinePurchaseSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnQueryReceiptsComplete(const FOnlineError& Result);

    UPROPERTY()
    FUniqueNetIdRepl __Store__UserId;

UPROPERTY()
    bool __Store__bRestoreReceipts;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlinePurchaseSubsystemFinalizeReceiptValidationInfoCallbackPin, FOnlineErrorInfo, Result, FString, ValidationInfo);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlinePurchaseSubsystemFinalizeReceiptValidationInfo : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlinePurchaseSubsystemFinalizeReceiptValidationInfoCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlinePurchaseSubsystemFinalizeReceiptValidationInfoCallbackPin OnFinalizeReceiptValidationInfoComplete;

    UFUNCTION(BlueprintCallable, Category = "Online|Purchase", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlinePurchaseSubsystemFinalizeReceiptValidationInfo* FinalizeReceiptValidationInfo(
        UOnlinePurchaseSubsystem* Subsystem
        ,FUniqueNetIdRepl UserId, FString InReceiptValidationInfo
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlinePurchaseSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnFinalizeReceiptValidationInfoComplete(const FOnlineError& Result, const FString& ValidationInfo);

    UPROPERTY()
    FUniqueNetIdRepl __Store__UserId;

UPROPERTY()
    FString __Store__InReceiptValidationInfo;
};
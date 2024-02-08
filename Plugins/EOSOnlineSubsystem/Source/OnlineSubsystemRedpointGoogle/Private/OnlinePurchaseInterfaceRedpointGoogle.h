// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#include "RedpointGooglePurchase.h"
#include "RedpointGooglePurchaseReceipt.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlinePurchaseInterfaceSynthetic.h"

#if EOS_GOOGLE_ENABLED

#include "OnlineIdentityInterfaceRedpointGoogle.h"

class FOnlinePurchaseInterfaceRedpointGoogle
    : public IOnlinePurchaseWithFinalizePurchaseCallback,
      public TSharedFromThis<FOnlinePurchaseInterfaceRedpointGoogle, ESPMode::ThreadSafe>
{
public:
    TSharedRef<FOnlineIdentityInterfaceRedpointGoogle> IdentityGooglePlay;
    TMap<FString, TSharedPtr<FRedpointGooglePurchaseReceipt>> KnownReceipts;

    FOnlinePurchaseInterfaceRedpointGoogle(
        const TSharedRef<FOnlineIdentityInterfaceRedpointGoogle> &InIdentityGooglePlay);
    virtual ~FOnlinePurchaseInterfaceRedpointGoogle();
    UE_NONCOPYABLE(FOnlinePurchaseInterfaceRedpointGoogle);

    virtual bool IsAllowedToPurchase(const FUniqueNetId &UserId) override;
    virtual void Checkout(
        const FUniqueNetId &UserId,
        const FPurchaseCheckoutRequest &CheckoutRequest,
        const FOnPurchaseCheckoutComplete &Delegate) override;
#if defined(UE_5_1_OR_LATER)
    virtual void Checkout(
        const FUniqueNetId &UserId,
        const FPurchaseCheckoutRequest &CheckoutRequest,
        const FOnPurchaseReceiptlessCheckoutComplete &Delegate) override;
#endif
    virtual void FinalizePurchase(const FUniqueNetId &UserId, const FString &ReceiptId) override;
    virtual void FinalizePurchase(const FUniqueNetId &UserId, const FString &ReceiptId, const FString &ReceiptInfo)
        override;
    virtual void FinalizePurchaseWithCallback(
        const FUniqueNetId &UserId,
        const FString &ReceiptId,
        const IOnlinePurchaseWithFinalizePurchaseCallback::FOnFinalizeReceiptComplete &Delegate) override;
    virtual void RedeemCode(
        const FUniqueNetId &UserId,
        const FRedeemCodeRequest &RedeemCodeRequest,
        const FOnPurchaseRedeemCodeComplete &Delegate) override;
    virtual void QueryReceipts(
        const FUniqueNetId &UserId,
        bool bRestoreReceipts,
        const FOnQueryReceiptsComplete &Delegate) override;
    virtual void GetReceipts(const FUniqueNetId &UserId, TArray<FPurchaseReceipt> &OutReceipts) const override;
    virtual void FinalizeReceiptValidationInfo(
        const FUniqueNetId &UserId,
        FString &InReceiptValidationInfo,
        const FOnFinalizeReceiptValidationInfoComplete &Delegate) override;

    void OnOutOfBandPurchasesNotification(FString JsonData, bool bWasSuccessfulReceipts, FString ErrorMessage);

private:
    void ProcessOutOfBandPurchases(
        bool WasSuccessful,
        bool WasCancelled,
        FString ErrorMessage,
        TArray<TSharedRef<const FRedpointGooglePurchase>> Purchases);
};

#endif
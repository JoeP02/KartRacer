// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_HAS_AUTHENTICATION

#include "CoreMinimal.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/PurchaseReceiptEAS.h"

EOS_ENABLE_STRICT_WARNINGS

class FOnlinePurchaseInterfaceEAS : public IOnlinePurchase,
                                    public TSharedFromThis<FOnlinePurchaseInterfaceEAS, ESPMode::ThreadSafe>
{
private:
    EOS_HEcom Ecom;
    TSharedRef<class FOnlineStoreInterfaceV2EAS, ESPMode::ThreadSafe> Store;
    TSharedRef<class FOnlineEntitlementsInterfaceEAS, ESPMode::ThreadSafe> Entitlements;
    TMap<FString, TSharedPtr<FPurchaseReceiptEAS>> KnownReceipts;

public:
    FOnlinePurchaseInterfaceEAS(
        EOS_HEcom InEcom,
        const TSharedRef<class FOnlineStoreInterfaceV2EAS, ESPMode::ThreadSafe> &InStore,
        const TSharedRef<class FOnlineEntitlementsInterfaceEAS, ESPMode::ThreadSafe> &InEntitlements)
        : Ecom(InEcom)
        , Store(InStore)
        , Entitlements(InEntitlements)
        , KnownReceipts(){};
    UE_NONCOPYABLE(FOnlinePurchaseInterfaceEAS);
    virtual ~FOnlinePurchaseInterfaceEAS() override = default;

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
};

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
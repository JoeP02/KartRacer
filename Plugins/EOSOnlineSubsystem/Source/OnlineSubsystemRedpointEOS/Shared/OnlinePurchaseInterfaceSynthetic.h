// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#include "UserIdMap.h"

EOS_ENABLE_STRICT_WARNINGS

#if PLATFORM_ANDROID
/**
 * @note: Do not use this interface in game code. It only exists to support certain automation
 * tests that need to know when FinalizePurchase completes asynchronously. There is absolutely
 * no support for using this interface.
 */
class ONLINESUBSYSTEMREDPOINTEOS_API IOnlinePurchaseWithFinalizePurchaseCallback : public IOnlinePurchase {
public:
    DECLARE_DELEGATE_OneParam(FOnFinalizeReceiptComplete, const FOnlineError &);

    virtual void FinalizePurchaseWithCallback(
        const FUniqueNetId &UserId,
        const FString &ReceiptId,
        const IOnlinePurchaseWithFinalizePurchaseCallback::FOnFinalizeReceiptComplete &Delegate) = 0;
};
#endif // #if PLATFORM_ANDROID

class ONLINESUBSYSTEMREDPOINTEOS_API FOnlinePurchaseInterfaceSynthetic
    :
#if PLATFORM_ANDROID
      public IOnlinePurchaseWithFinalizePurchaseCallback,
#else  // #if PLATFORM_ANDROID
      public IOnlinePurchase,
#endif // #if PLATFORM_ANDROID
      public TSharedFromThis<FOnlinePurchaseInterfaceSynthetic, ESPMode::ThreadSafe>
{
private:
    TSharedRef<class FOnlineIdentityInterfaceEOS, ESPMode::ThreadSafe> IdentityEOS;
    TUserIdMap<TSharedPtr<struct FNativeEventBinding>> NativeEventBindingsRegisteredPerUser;

    void OnNativeUnexpectedPurchaseReceipt(
        const FUniqueNetId &UserId,
        TSharedPtr<struct FNativeEventBinding> NativeEventBinding);
    void OnLoginStatusChanged(
        int32 LocalUserNum,
        ELoginStatus::Type OldStatus,
        ELoginStatus::Type NewStatus,
        const FUniqueNetId &UserId);

public:
    FOnlinePurchaseInterfaceSynthetic(TSharedRef<class FOnlineIdentityInterfaceEOS, ESPMode::ThreadSafe> InIdentityEOS)
        : IdentityEOS(MoveTemp(InIdentityEOS)){};
    void RegisterEvents();
    UE_NONCOPYABLE(FOnlinePurchaseInterfaceSynthetic);
    virtual ~FOnlinePurchaseInterfaceSynthetic() override = default;

    virtual bool IsAllowedToPurchase(const FUniqueNetId &UserId) override;
    virtual void Checkout(
        const FUniqueNetId &UserId,
        const FPurchaseCheckoutRequest &CheckoutRequest,
        const FOnPurchaseCheckoutComplete &Delegate) override;
    virtual void FinalizePurchase(const FUniqueNetId &UserId, const FString &ReceiptId) override;
    virtual void FinalizePurchase(const FUniqueNetId &UserId, const FString &ReceiptId, const FString &ReceiptInfo)
        override;
#if PLATFORM_ANDROID
    virtual void FinalizePurchaseWithCallback(
        const FUniqueNetId &UserId,
        const FString &ReceiptId,
        const IOnlinePurchaseWithFinalizePurchaseCallback::FOnFinalizeReceiptComplete &Delegate) override;
#endif // #if PLATFORM_ANDROID
#if defined(UE_5_1_OR_LATER)
    virtual void Checkout(
        const FUniqueNetId &UserId,
        const FPurchaseCheckoutRequest &CheckoutRequest,
        const FOnPurchaseReceiptlessCheckoutComplete &Delegate) override;
#endif
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
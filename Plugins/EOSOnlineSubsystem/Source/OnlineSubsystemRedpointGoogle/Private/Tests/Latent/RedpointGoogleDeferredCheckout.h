// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)

#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#include "Interfaces/OnlineStoreInterfaceV2.h"
#include "Misc/AutomationTest.h"
#include "OnlineSubsystemRedpointGoogle.h"
#include "OnlineSubsystemRedpointGoogleConstants.h"
#include "Tests/AutomationCommon.h"
#include "OnlineError.h"
#include "LogRedpointGoogle.h"

class FRedpointGoogleDeferredCheckout : public IAutomationLatentCommand
{
private:
    FAutomationTestBase *TestBase;
    FName SubsystemName;
    bool bHasInit;
    bool bIsDone;
    IOnlineIdentityPtr Identity;
    IOnlinePurchasePtr Purchase;
    FPurchaseCheckoutRequest CheckoutRequest;
    EPurchaseTransactionState ExpectedTransactionState;
    FDelegateHandle UnexpectedPurchaseDelegateHandle;

    void OnFinalizeComplete(const FOnlineError &Result, FString TransactionId);
    void OnUnexpectedPurchaseReceipt(const FUniqueNetId& UserId, FString TransactionId);
    void OnPurchaseComplete(const FOnlineError &Result, const TSharedRef<FPurchaseReceipt> &Receipt);

public:
    FRedpointGoogleDeferredCheckout(
        FAutomationTestBase *InTestBase,
        FName InSubsystemName,
        const FPurchaseCheckoutRequest &InCheckoutRequest,
        EPurchaseTransactionState bInExpectedTransactionState)
        : TestBase(InTestBase)
        , SubsystemName(InSubsystemName)
        , bHasInit(false)
        , bIsDone(false)
        , Identity()
        , Purchase()
        , CheckoutRequest(InCheckoutRequest)
        , ExpectedTransactionState(bInExpectedTransactionState){};
    virtual ~FRedpointGoogleDeferredCheckout(){};
    virtual bool Update() override;
};

#endif // #if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)
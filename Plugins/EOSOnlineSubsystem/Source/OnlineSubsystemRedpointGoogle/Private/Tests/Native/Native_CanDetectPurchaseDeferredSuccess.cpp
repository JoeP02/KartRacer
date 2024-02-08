// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)

#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#include "Interfaces/OnlineStoreInterfaceV2.h"
#include "Misc/AutomationTest.h"
#include "OnlineSubsystemRedpointGoogle.h"
#include "OnlineSubsystemRedpointGoogleConstants.h"
#include "Tests/AutomationCommon.h"
#include "Tests/Latent/RedpointGoogleLoginOnAndroid.h"
#include "Tests/Latent/RedpointGoogleDeferredCheckout.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FOnlineSubsystemRedpointGoogle_Native_CanDetectPurchaseDeferredSuccess,
    "OnlineSubsystemRedpointGoogle.Native.CanDetectPurchaseDeferredSuccess",
    EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter);

bool FOnlineSubsystemRedpointGoogle_Native_CanDetectPurchaseDeferredSuccess::RunTest(const FString &InParam)
{
    FAutomationTestFramework::Get().SetRequestedTestFilter(EAutomationTestFlags::ProductFilter);
    FAutomationTestFramework::Get().EnqueueLatentCommand(MakeShareable(new FRedpointGoogleLoginOnAndroid(this, REDPOINT_GOOGLE_SUBSYSTEM)));

    FPurchaseCheckoutRequest CheckoutWithItem;
    CheckoutWithItem.AddPurchaseOffer(TEXT(""), TEXT("test_iap"), 1);
    FAutomationTestFramework::Get().EnqueueLatentCommand(
        MakeShareable(new FRedpointGoogleDeferredCheckout(this, REDPOINT_GOOGLE_SUBSYSTEM, CheckoutWithItem, EPurchaseTransactionState::Purchased)));

    return true;
}

#endif // #if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)
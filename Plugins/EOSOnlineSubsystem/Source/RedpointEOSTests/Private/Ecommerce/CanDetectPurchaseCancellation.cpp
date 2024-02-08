// Copyright June Rhodes 2024. All Rights Reserved.

#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#include "Misc/AutomationTest.h"
#include "OnlineError.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "RedpointEOSTestsModule.h"
#include "TestHelpers.h"
#include "Tests/AutomationCommon.h"

IMPLEMENT_ASYNC_AUTOMATION_TEST(
    FOnlineSubsystemRedpointEAS_CanDetectPurchaseCancellation,
    "OnlineSubsystemRedpointEAS.CanDetectPurchaseCancellation",
    EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter);

void FOnlineSubsystemRedpointEAS_CanDetectPurchaseCancellation::RunAsyncTest(const std::function<void()> &OnDone)
{
    // NOLINTNEXTLINE(unreal-ionlinesubsystem-get)
    IOnlineSubsystem *OSS = IOnlineSubsystem::Get(FName(TEXT("RedpointEOS")));

    auto TestCode = [this, OSS, OnDone](const TSharedRef<const FUniqueNetId> &UserId) {
        auto Purchase = OSS->GetPurchaseInterface();

        FPurchaseCheckoutRequest CheckoutRequest;
        CheckoutRequest.AddPurchaseOffer(TEXT(""), TEXT("aeb7bca974bb4085b3be31eda50aa805"), 1);

        Purchase->Checkout(
            *UserId,
            CheckoutRequest,
            FOnPurchaseCheckoutComplete::CreateLambda(
                [this, OnDone](const FOnlineError &Result, const TSharedRef<FPurchaseReceipt> &Receipt) {
                    {
                        if (Result.WasSuccessful())
                        {
                            this->TestFalse("Purchase call was unexpectedly successful", Result.WasSuccessful());
                            OnDone();
                            return;
                        }

                        this->TestTrue(
                            "Receipt status is not in expected status",
                            Receipt->TransactionState == EPurchaseTransactionState::Canceled);
                        OnDone();
                    }
                }));
    };

    auto Identity = OSS->GetIdentityInterface();

    if (Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
    {
        TestCode(Identity->GetUniquePlayerId(0).ToSharedRef());
    }
    else
    {
        auto CancelLogin = RegisterOSSCallback(
            this,
            Identity,
            0,
            &IOnlineIdentity::AddOnLoginCompleteDelegate_Handle,
            &IOnlineIdentity::ClearOnLoginCompleteDelegate_Handle,
            std::function<void(int32, bool, const FUniqueNetId &, const FString &)>(
                [this,
                 OSS,
                 OnDone,
                 TestCode](int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId &UserId, const FString &Error) {
                    if (!this->TestTrue("Login must be successful", bWasSuccessful))
                    {
                        OnDone();
                        return;
                    }

                    TestCode(UserId.AsShared());
                }));

        if (!Identity->AutoLogin(0))
        {
            CancelLogin();
            OnDone();
        }
    }
}
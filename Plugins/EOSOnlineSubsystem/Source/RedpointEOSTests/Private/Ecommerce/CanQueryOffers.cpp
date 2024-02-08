// Copyright June Rhodes 2024. All Rights Reserved.

#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineStoreInterfaceV2.h"
#include "Misc/AutomationTest.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "RedpointEOSTestsModule.h"
#include "TestHelpers.h"
#include "Tests/AutomationCommon.h"

IMPLEMENT_ASYNC_AUTOMATION_TEST(
    FOnlineSubsystemRedpointEAS_CanQueryOffers,
    "OnlineSubsystemRedpointEAS.CanQueryOffers",
    EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter);

void FOnlineSubsystemRedpointEAS_CanQueryOffers::RunAsyncTest(const std::function<void()> &OnDone)
{
    // NOLINTNEXTLINE(unreal-ionlinesubsystem-get)
    IOnlineSubsystem *OSS = IOnlineSubsystem::Get(FName(TEXT("RedpointEOS")));

    auto TestCode = [this, OSS, OnDone](const TSharedRef<const FUniqueNetId> &UserId) {
        auto StoreV2 = OSS->GetStoreV2Interface();

        StoreV2->QueryOffersByFilter(
            *UserId,
            FOnlineStoreFilter(),
            FOnQueryOnlineStoreOffersComplete::CreateLambda(
                [this, OnDone](bool bWasSuccessful, const TArray<FUniqueOfferId> &OfferIds, const FString &Error) {
                    this->TestTrue("Offer query call was successful", bWasSuccessful);
                    this->TestTrue("At least one offer was retrived", OfferIds.Num() > 0);
                    OnDone();
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
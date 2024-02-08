// Copyright June Rhodes 2024. All Rights Reserved.

#include "Interfaces/OnlineEntitlementsInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Misc/AutomationTest.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "RedpointEOSTestsModule.h"
#include "TestHelpers.h"
#include "Tests/AutomationCommon.h"

IMPLEMENT_ASYNC_AUTOMATION_TEST(
    FOnlineSubsystemRedpointEAS_CanQueryEntitlements,
    "OnlineSubsystemRedpointEAS.CanQueryEntitlements",
    EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter);

void FOnlineSubsystemRedpointEAS_CanQueryEntitlements::RunAsyncTest(const std::function<void()> &OnDone)
{
    // NOLINTNEXTLINE(unreal-ionlinesubsystem-get)
    IOnlineSubsystem *OSS = IOnlineSubsystem::Get(FName(TEXT("RedpointEOS")));

    auto TestCode = [this, OSS, OnDone](const TSharedRef<const FUniqueNetId> &UserId) {
        auto Entitlements = OSS->GetEntitlementsInterface();

        auto CancelCallback = RegisterOSSCallback(
            this,
            Entitlements,
            &IOnlineEntitlements::AddOnQueryEntitlementsCompleteDelegate_Handle,
            &IOnlineEntitlements::ClearOnQueryEntitlementsCompleteDelegate_Handle,
            std::function<void(bool, const FUniqueNetId &, const FString &, const FString &)>(
                [this, OnDone](
                    bool bWasSuccessful,
                    const FUniqueNetId &UserId,
                    const FString &Namespace,
                    const FString &Error) {
                    if (!this->TestTrue("Should be able to query entitlements", bWasSuccessful))
                    {
                        OnDone();
                        return;
                    }

                    // @note: We don't try to assert what entitlements are present.

                    OnDone();
                }));

        if (!this->TestTrue(
                "QueryEntitlements call should succeed",
                Entitlements->QueryEntitlements(*UserId, TEXT(""), FPagedQuery())))
        {
            CancelCallback();
            OnDone();
        }
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
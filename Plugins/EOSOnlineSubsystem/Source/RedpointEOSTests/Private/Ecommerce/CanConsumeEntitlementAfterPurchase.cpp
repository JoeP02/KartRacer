// Copyright June Rhodes 2024. All Rights Reserved.

#include "Interfaces/OnlineEntitlementsInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#include "Misc/AutomationTest.h"
#include "OnlineError.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "RedpointEOSTestsModule.h"
#include "TestHelpers.h"
#include "Tests/AutomationCommon.h"

IMPLEMENT_MANAGED_ASYNC_AUTOMATION_TEST(
    FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase,
    "OnlineSubsystemRedpointEAS.CanConsumeEntitlementAfterPurchase",
    EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter,
    FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager);

class FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager
    : public TSharedFromThis<FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager>
{
public:
    UE_NONCOPYABLE(FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager);
    virtual ~FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager() = default;

    typedef FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager TThisClass;

    class FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase *T;
    IOnlineSubsystem *OSS;
    TSharedPtr<const FUniqueNetId> UserId;
    std::function<void()> OnDone;

    void StartLogin();

    void OnLoginComplete(const TSharedRef<const FUniqueNetId> &InUserId);

    void OnPurchaseComplete(const FOnlineError &Result, const TSharedRef<FPurchaseReceipt> &Receipt);

    void ConsumeEntitlementsOrDone(TArray<FUniqueEntitlementId> RemainingEntitlements);

    void OnFinalizedReceipt(
        const FOnlineError &Result,
        const FString &ValidationInfo,
        TArray<FUniqueEntitlementId> RemainingEntitlements);

    FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager(
        FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase *InT,
        const std::function<void()> &InOnDone)
        : T(InT)
        , OSS(nullptr)
        , UserId(nullptr)
        , OnDone(InOnDone)
    {
        // NOLINTNEXTLINE(unreal-ionlinesubsystem-get)
        this->OSS = IOnlineSubsystem::Get(FName(TEXT("RedpointEOS")));
    }
};

void FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager::StartLogin()
{
    auto Identity = this->OSS->GetIdentityInterface();

    if (Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
    {
        this->OnLoginComplete(Identity->GetUniquePlayerId(0).ToSharedRef());
    }
    else
    {
        auto CancelLogin = RegisterOSSCallback(
            this->T,
            Identity,
            0,
            &IOnlineIdentity::AddOnLoginCompleteDelegate_Handle,
            &IOnlineIdentity::ClearOnLoginCompleteDelegate_Handle,
            std::function<void(int32, bool, const FUniqueNetId &, const FString &)>(
                [this](int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId &ReceivedUserId, const FString &Error) {
                    if (!this->T->TestTrue("Login must be successful", bWasSuccessful))
                    {
                        this->OnDone();
                        return;
                    }

                    this->OnLoginComplete(ReceivedUserId.AsShared());
                }));

        if (!Identity->AutoLogin(0))
        {
            CancelLogin();
            this->OnDone();
        }
    }
}

void FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager::OnLoginComplete(
    const TSharedRef<const FUniqueNetId> &InUserId)
{
    auto Purchase = this->OSS->GetPurchaseInterface();

    this->UserId = InUserId;

    FPurchaseCheckoutRequest CheckoutRequest;
    CheckoutRequest.AddPurchaseOffer(TEXT(""), TEXT("aeb7bca974bb4085b3be31eda50aa805"), 1);

    Purchase->Checkout(
        *this->UserId,
        CheckoutRequest,
        FOnPurchaseCheckoutComplete::CreateSP(
            this,
            &FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager::OnPurchaseComplete));
}

void FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager::OnPurchaseComplete(
    const FOnlineError &Result,
    const TSharedRef<FPurchaseReceipt> &Receipt)
{
    auto Entitlements = this->OSS->GetEntitlementsInterface();

    if (!Result.WasSuccessful())
    {
        this->T->TestTrue("Purchase call should have been successful", Result.WasSuccessful());
        this->OnDone();
        return;
    }

    this->T->TestTrue(
        "Receipt status is not in expected status",
        Receipt->TransactionState == EPurchaseTransactionState::Purchased);

    // Entitlements are automatically refreshed after Checkout.
    this->T->TestTrue(
        "Entitlement should exist for item",
        Entitlements->GetItemEntitlement(*this->UserId, TEXT("40cd6ad8ab024cc88e24c3d1f67b232b")).IsValid());

    // Make the list of entitlements we want to consume. There might be more than
    // one for this item if there has been manual testing on this account, so make
    // sure this test goes through and consumes all of them.
    TArray<TSharedRef<FOnlineEntitlement>> EntitlementsArray;
    Entitlements->GetAllEntitlements(*this->UserId, TEXT(""), EntitlementsArray);
    this->T->TestTrue("GetAllEntitlements returns at least one entitlement", EntitlementsArray.Num() > 0);
    TArray<FUniqueEntitlementId> EntitlementIdsToConsume;
    for (const auto &Entitlement : EntitlementsArray)
    {
        if (Entitlement->ItemId == TEXT("40cd6ad8ab024cc88e24c3d1f67b232b") && Entitlement->RemainingCount > 0)
        {
            EntitlementIdsToConsume.Add(Entitlement->Id);
        }
    }

    this->ConsumeEntitlementsOrDone(EntitlementIdsToConsume);
}

void FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager::ConsumeEntitlementsOrDone(
    TArray<FUniqueEntitlementId> RemainingEntitlements)
{
    if (RemainingEntitlements.Num() == 0)
    {
        this->OnDone();
        return;
    }

    FUniqueEntitlementId NextEntitlement = RemainingEntitlements.Pop(true);

    auto Purchase = this->OSS->GetPurchaseInterface();

    Purchase->FinalizeReceiptValidationInfo(
        *this->UserId,
        NextEntitlement,
        FOnFinalizeReceiptValidationInfoComplete::CreateSP(
            this,
            &FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager::OnFinalizedReceipt,
            RemainingEntitlements));
}

void FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager::OnFinalizedReceipt(
    const FOnlineError &Result,
    const FString &ValidationInfo,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    TArray<FUniqueEntitlementId> RemainingEntitlements)
{
    if (!Result.WasSuccessful())
    {
        this->T->TestTrue("Expected consumption request to succeed", Result.WasSuccessful());
        this->OnDone();
        return;
    }

    this->ConsumeEntitlementsOrDone(MoveTemp(RemainingEntitlements));
}

void FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase::CreateManagingInstance(
    const std::function<void()> &OnDone,
    const std::function<void(
        const TSharedRef<FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager> &)> &OnInstanceCreated)
{
    auto Manager = MakeShared<FOnlineSubsystemRedpointEAS_CanConsumeEntitlementAfterPurchase_Manager>(this, OnDone);
    Manager->StartLogin();
    OnInstanceCreated(Manager);
}
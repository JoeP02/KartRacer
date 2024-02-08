// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)

#include "Tests/Latent/RedpointGoogleCheckout.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlinePurchaseInterfaceSynthetic.h"

void FRedpointGoogleCheckout::OnFinalizeComplete(
    const FOnlineError &Result,
    FString TransactionId)
{
    if (!Result.WasSuccessful())
    {
        this->TestBase->TestTrue("FinalizeReceipt call was successful", Result.WasSuccessful());
        this->bIsDone = true;
        return;
    }

    TArray<FPurchaseReceipt> Receipts;
    this->Purchase->GetReceipts(*this->Identity->GetUniquePlayerId(0), Receipts);

    bool bHasReceipt = false;
    for (const auto &ReceiptIter : Receipts)
    {
        if (ReceiptIter.TransactionId == TransactionId)
        {
            bHasReceipt = true;
        }
    }

    this->TestBase->TestFalse("Receipt should not be present after finalizing", bHasReceipt);
    this->bIsDone = true;
    return;
}

void FRedpointGoogleCheckout::OnPurchaseComplete(
    const FOnlineError &Result,
    const TSharedRef<FPurchaseReceipt> & Receipt)
{
    if (this->ExpectedTransactionState == EPurchaseTransactionState::Purchased ||
        this->ExpectedTransactionState == EPurchaseTransactionState::Deferred)
    {
        if (!Result.WasSuccessful())
        {
            this->TestBase->TestTrue("Purchase call was successful", Result.WasSuccessful());
            this->bIsDone = true;
            return;
        }

        this->TestBase->TestTrue(
            "Receipt status is not in expected state",
            Receipt->TransactionState == this->ExpectedTransactionState);

        TArray<FPurchaseReceipt> Receipts;
        this->Purchase->GetReceipts(*this->Identity->GetUniquePlayerId(0), Receipts);

        bool bHasReceipt = false;
        for (const auto& ReceiptIter : Receipts)
        {
            if (ReceiptIter.TransactionId == Receipt->TransactionId)
            {
                bHasReceipt = true;
                this->TestBase->TestTrue(
                    "Receipt status in GetReceipts is not in expected state",
                    ReceiptIter.TransactionState == this->ExpectedTransactionState);
            }
        }

        this->TestBase->TestTrue("Receipt is returned by GetReceipts", bHasReceipt);
        if (!bHasReceipt)
        {
            this->bIsDone = true;
            return;
        }

        // @note: We have to use a specific overload because FinalizePurchase does not actually
        // have a callback in the public APIs.
        TSharedPtr<IOnlinePurchaseWithFinalizePurchaseCallback, ESPMode::ThreadSafe> PurchaseRedpoint =
            StaticCastSharedPtr<IOnlinePurchaseWithFinalizePurchaseCallback>(this->Purchase);
        PurchaseRedpoint->FinalizePurchaseWithCallback(
            *this->Identity->GetUniquePlayerId(0),
            Receipt->TransactionId,
            IOnlinePurchaseWithFinalizePurchaseCallback::FOnFinalizeReceiptComplete::CreateSP(
                this,
                &FRedpointGoogleCheckout::OnFinalizeComplete,
                Receipt->TransactionId));

        UE_LOG(LogRedpointGoogle, Verbose, TEXT("OnPurchaseComplete finished successfully."));
        return;
    }
    else
    {
        if (Result.WasSuccessful())
        {
            this->TestBase->TestFalse("Purchase call was unexpectedly successful", Result.WasSuccessful());
            this->bIsDone = true;
            return;
        }

        this->TestBase->TestTrue(
            "Receipt status is not in expected state",
            Receipt->TransactionState == this->ExpectedTransactionState);

        UE_LOG(LogRedpointGoogle, Verbose, TEXT("OnPurchaseComplete expectedly failed for tests."));
        this->bIsDone = true;
        return;
    }
}

bool FRedpointGoogleCheckout::Update()
{
    if (!this->bHasInit)
    {
        UE_LOG(LogRedpointGoogle, Verbose, TEXT("Starting purchase latent command"));

        IOnlineSubsystem *OSS = IOnlineSubsystem::Get(this->SubsystemName);
        if (!this->TestBase->TestTrue(TEXT("OSS is not null"), OSS != nullptr))
        {
            return true;
        }
        this->Identity = OSS->GetIdentityInterface();
        if (!this->TestBase->TestTrue(TEXT("Identity is not null"), this->Identity.IsValid()))
        {
            return true;
        }
        this->Purchase = OSS->GetPurchaseInterface();
        if (!this->TestBase->TestTrue(TEXT("Purchase is not null"), this->Purchase.IsValid()))
        {
            return true;
        }
        TSharedPtr<const FUniqueNetId> UserId = this->Identity->GetUniquePlayerId(0);
        if (!this->TestBase->TestTrue(TEXT("Local user ID 0 is not null"), UserId.IsValid()))
        {
            return true;
        }

        this->Purchase->Checkout(
            *UserId,
            this->CheckoutRequest,
            FOnPurchaseCheckoutComplete::CreateSP(this, &FRedpointGoogleCheckout::OnPurchaseComplete));
        this->bHasInit = true;
    }

    return this->bIsDone;
}

#endif // #if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)
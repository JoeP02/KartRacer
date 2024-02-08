// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)

#include "Tests/Latent/RedpointGoogleDeferredCheckout.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlinePurchaseInterfaceSynthetic.h"

void FRedpointGoogleDeferredCheckout::OnFinalizeComplete(const FOnlineError &Result, FString TransactionId)
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

void FRedpointGoogleDeferredCheckout::OnUnexpectedPurchaseReceipt(const FUniqueNetId &UserId, FString TransactionId)
{
    TArray<FPurchaseReceipt> Receipts;
    this->Purchase->GetReceipts(*this->Identity->GetUniquePlayerId(0), Receipts);

    bool bHasReceipt = false;
    bool bHasReceiptInExpectedStatus = false;
    bool bHasReceiptStillDeferred = false;
    for (const auto &ReceiptIter : Receipts)
    {
        if (ReceiptIter.TransactionId == TransactionId)
        {
            bHasReceipt = true;
            if (ReceiptIter.TransactionState == this->ExpectedTransactionState)
            {
                bHasReceiptInExpectedStatus = true;
            }
            else if (ReceiptIter.TransactionState == EPurchaseTransactionState::Deferred)
            {
                bHasReceiptStillDeferred = true;
            }
        }
    }

    this->TestBase->TestTrue("GetReceipts has receipt", bHasReceipt);
    if (bHasReceiptInExpectedStatus)
    {
        if (this->ExpectedTransactionState == EPurchaseTransactionState::Purchased)
        {
            // Move to consuming if purchased.
            UE_LOG(
                LogRedpointGoogle,
                Verbose,
                TEXT("Got expected receipt update for deferred checkout, moving to consume."));
            this->Purchase->ClearOnUnexpectedPurchaseReceiptDelegate_Handle(this->UnexpectedPurchaseDelegateHandle);
            TSharedPtr<IOnlinePurchaseWithFinalizePurchaseCallback, ESPMode::ThreadSafe> PurchaseRedpoint =
                StaticCastSharedPtr<IOnlinePurchaseWithFinalizePurchaseCallback>(this->Purchase);
            PurchaseRedpoint->FinalizePurchaseWithCallback(
                *this->Identity->GetUniquePlayerId(0),
                TransactionId,
                IOnlinePurchaseWithFinalizePurchaseCallback::FOnFinalizeReceiptComplete::CreateSP(
                    this,
                    &FRedpointGoogleDeferredCheckout::OnFinalizeComplete,
                    TransactionId));
        }
        else
        {
            // Just finish up if not expecting a success.
            UE_LOG(
                LogRedpointGoogle,
                Verbose,
                TEXT("Got expected receipt update for deferred checkout, all done because this was an expected "
                     "failure."));
            this->Purchase->ClearOnUnexpectedPurchaseReceiptDelegate_Handle(this->UnexpectedPurchaseDelegateHandle);
            this->bIsDone = true;
        }
        return;
    }

    // If we don't have it in the expected status, then it must at least still
    // be deferred.
    if (!this->TestBase->TestTrue("Receipt should still be deferred if not complete", bHasReceiptStillDeferred))
    {
        UE_LOG(
            LogRedpointGoogle,
            Verbose,
            TEXT("Got receipt update for deferred checkout, but it wasn't to the correct status."));
        this->Purchase->ClearOnUnexpectedPurchaseReceiptDelegate_Handle(this->UnexpectedPurchaseDelegateHandle);
        this->bIsDone = true;
        return;
    }

    // Otherwise the target receipt is still deferred and we're still waiting on
    // it to change status.
    UE_LOG(
        LogRedpointGoogle,
        Verbose,
        TEXT("Got updated receipts, but the target receipt was still deferred, waiting on another update..."));
}

void FRedpointGoogleDeferredCheckout::OnPurchaseComplete(
    const FOnlineError &Result,
    const TSharedRef<FPurchaseReceipt> &Receipt)
{
    if (!Result.WasSuccessful())
    {
        this->TestBase->TestTrue("Purchase call was successful", Result.WasSuccessful());
        this->bIsDone = true;
        return;
    }

    this->TestBase->TestTrue(
        "Receipt status is not in deferred state",
        Receipt->TransactionState == EPurchaseTransactionState::Deferred);

    TArray<FPurchaseReceipt> Receipts;
    this->Purchase->GetReceipts(*this->Identity->GetUniquePlayerId(0), Receipts);

    bool bHasReceipt = false;
    for (const auto &ReceiptIter : Receipts)
    {
        if (ReceiptIter.TransactionId == Receipt->TransactionId)
        {
            bHasReceipt = true;
        }
    }

    this->TestBase->TestTrue("Receipt is returned by GetReceipts", bHasReceipt);
    if (!bHasReceipt)
    {
        this->bIsDone = true;
        return;
    }

    UE_LOG(
        LogRedpointGoogle,
        Verbose,
        TEXT("Now waiting on deferred receipt to update (should happen after a few minutes)"));
    this->UnexpectedPurchaseDelegateHandle =
        this->Purchase->AddOnUnexpectedPurchaseReceiptDelegate_Handle(FOnUnexpectedPurchaseReceiptDelegate::CreateSP(
            this,
            &FRedpointGoogleDeferredCheckout::OnUnexpectedPurchaseReceipt,
            Receipt->TransactionId));
}

bool FRedpointGoogleDeferredCheckout::Update()
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
        if (!this->TestBase->TestTrue(TEXT("Identity is not null"), this->Identity != nullptr))
        {
            return true;
        }
        this->Purchase = OSS->GetPurchaseInterface();
        if (!this->TestBase->TestTrue(TEXT("Purchase is not null"), this->Purchase != nullptr))
        {
            return true;
        }

        this->Purchase->Checkout(
            *this->Identity->GetUniquePlayerId(0),
            this->CheckoutRequest,
            FOnPurchaseCheckoutComplete::CreateSP(this, &FRedpointGoogleDeferredCheckout::OnPurchaseComplete));
        this->bHasInit = true;
    }

    return this->bIsDone;
}

#endif // #if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)
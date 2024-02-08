// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointGooglePurchaseReceipt.h"

#if EOS_GOOGLE_ENABLED

FRedpointGooglePurchaseReceipt::FRedpointGooglePurchaseReceipt()
{
}

TSharedRef<FRedpointGooglePurchaseReceipt> FRedpointGooglePurchaseReceipt::CreateReceiptForCheckout(
    const FPurchaseCheckoutRequest &InCheckoutRequest)
{
    TSharedRef<FRedpointGooglePurchaseReceipt> Receipt = MakeShareable(new FRedpointGooglePurchaseReceipt());
    Receipt->TransactionId = FGuid::NewGuid().ToString();
    Receipt->TransactionState = EPurchaseTransactionState::NotStarted;
    for (const auto &PurchaseOffer : InCheckoutRequest.PurchaseOffers)
    {
        Receipt->AddReceiptOffer(TEXT(""), PurchaseOffer.OfferId, PurchaseOffer.Quantity);
    }
    return Receipt;
}

TSharedRef<FRedpointGooglePurchaseReceipt> FRedpointGooglePurchaseReceipt::CreateReceiptForError()
{
    TSharedRef<FRedpointGooglePurchaseReceipt> Receipt = MakeShareable(new FRedpointGooglePurchaseReceipt());
    Receipt->TransactionId = FGuid::NewGuid().ToString();
    Receipt->TransactionState = EPurchaseTransactionState::Invalid;
    return Receipt;
}

TSharedRef<FRedpointGooglePurchaseReceipt> FRedpointGooglePurchaseReceipt::CreateReceiptForPurchase(
    const TSharedRef<const FRedpointGooglePurchase> &InPurchase)
{
    TSharedRef<FRedpointGooglePurchaseReceipt> Receipt = MakeShareable(new FRedpointGooglePurchaseReceipt());
    Receipt->TransactionId = FGuid::NewGuid().ToString();
    Receipt->AttachPurchase(InPurchase);
    return Receipt;
}

FRedpointGooglePurchaseReceipt::~FRedpointGooglePurchaseReceipt()
{
}

void FRedpointGooglePurchaseReceipt::AttachPurchase(const TSharedRef<const FRedpointGooglePurchase> &InPurchase)
{
    if (InPurchase->PurchaseState == TEXT("PENDING"))
    {
        this->TransactionState = EPurchaseTransactionState::Deferred;
    }
    else
    {
        this->TransactionState = EPurchaseTransactionState::Purchased;
    }
    this->RedpointPurchase = InPurchase;
    this->ReceiptOffers.Empty();
    TMap<FString, int> ProductCounts;
    for (const auto &ProductId : InPurchase->ProductIds)
    {
        if (!ProductCounts.Contains(ProductId))
        {
            ProductCounts.Add(ProductId, 1);
        }
        else
        {
            ProductCounts[ProductId]++;
        }
    }
    for (const auto &ProductCount : ProductCounts)
    {
        this->AddReceiptOffer(TEXT(""), ProductCount.Key, ProductCount.Value);
    }
}

TSharedPtr<const FRedpointGooglePurchase> FRedpointGooglePurchaseReceipt::GetPurchase() const
{
    return this->RedpointPurchase;
}

void FRedpointGooglePurchaseReceipt::AttachCancellation()
{
    this->TransactionState = EPurchaseTransactionState::Canceled;
}

void FRedpointGooglePurchaseReceipt::AttachError(const FOnlineError &InError, bool bPurchaseWasAttempted)
{
    if (bPurchaseWasAttempted)
    {
        this->TransactionState = EPurchaseTransactionState::Failed;
    }
    else
    {
        this->TransactionState = EPurchaseTransactionState::Invalid;
    }
}

#endif
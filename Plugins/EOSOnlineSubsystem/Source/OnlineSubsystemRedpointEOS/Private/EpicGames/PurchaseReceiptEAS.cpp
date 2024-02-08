// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_HAS_AUTHENTICATION

#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/PurchaseReceiptEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSErrorConv.h"

EOS_ENABLE_STRICT_WARNINGS

FPurchaseReceiptEAS::FPurchaseReceiptEAS()
{
}

TSharedRef<FPurchaseReceiptEAS> FPurchaseReceiptEAS::CreateReceiptForCheckout(
    const FPurchaseCheckoutRequest &InCheckoutRequest)
{
    TSharedRef<FPurchaseReceiptEAS> Receipt = MakeShareable(new FPurchaseReceiptEAS());
    Receipt->TransactionId = FGuid::NewGuid().ToString();
    Receipt->TransactionState = EPurchaseTransactionState::NotStarted;
    for (const auto &PurchaseOffer : InCheckoutRequest.PurchaseOffers)
    {
        Receipt->AddReceiptOffer(TEXT(""), PurchaseOffer.OfferId, PurchaseOffer.Quantity);
    }
    return Receipt;
}

TSharedRef<FPurchaseReceiptEAS> FPurchaseReceiptEAS::CreateReceiptForError()
{
    TSharedRef<FPurchaseReceiptEAS> Receipt = MakeShareable(new FPurchaseReceiptEAS());
    Receipt->TransactionId = FGuid::NewGuid().ToString();
    Receipt->TransactionState = EPurchaseTransactionState::Invalid;
    return Receipt;
}

FPurchaseReceiptEAS::~FPurchaseReceiptEAS()
{
}

void FPurchaseReceiptEAS::AttachTransaction(
    EOS_HEcom InEcom,
    const FString &InTransactionId,
    EOS_Ecom_HTransaction InTransaction)
{
    this->TransactionId = InTransactionId;

    EOS_Ecom_Transaction_GetEntitlementsCountOptions CountOpts = {};
    CountOpts.ApiVersion = EOS_ECOM_TRANSACTION_GETENTITLEMENTSCOUNT_API_LATEST;
    uint32_t Count = EOS_Ecom_Transaction_GetEntitlementsCount(InTransaction, &CountOpts);
    for (uint32_t i = 0; i < Count; i++)
    {
        EOS_Ecom_Transaction_CopyEntitlementByIndexOptions CopyOpts = {};
        CopyOpts.ApiVersion = EOS_ECOM_TRANSACTION_COPYENTITLEMENTBYINDEX_API_LATEST;
        CopyOpts.EntitlementIndex = i;
        EOS_Ecom_Entitlement *Entitlement = nullptr;
        EOS_EResult CopyResult = EOS_Ecom_Transaction_CopyEntitlementByIndex(InTransaction, &CopyOpts, &Entitlement);
        if (CopyResult != EOS_EResult::EOS_Success)
        {
            UE_LOG(
                LogRedpointEOS,
                Error,
                TEXT("%s"),
                *ConvertError(
                     TEXT("FPurchaseReceiptEAS::AttachTransaction"),
                     FString::Printf(TEXT("Failed to copy entitlement at index %u."), i),
                     CopyResult)
                     .ToLogString());
            continue;
        }

        // @todo

        EOS_Ecom_Entitlement_Release(Entitlement);
    }

    this->TransactionState = EPurchaseTransactionState::Purchased;
}

void FPurchaseReceiptEAS::AttachCancellation()
{
    this->TransactionState = EPurchaseTransactionState::Canceled;
}

void FPurchaseReceiptEAS::AttachError(const FOnlineError &InError, bool bPurchaseWasAttempted)
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

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
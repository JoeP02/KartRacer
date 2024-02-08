// Copyright June Rhodes 2023. All Rights Reserved.

#include "Types/OSBPurchaseTypes.h"

FRedeemCodeRequestBP FRedeemCodeRequestBP::FromNative(const FRedeemCodeRequest &InObj)
{
    FRedeemCodeRequestBP Result;
    Result.Code = InObj.Code;
    Result.CodeUseId = InObj.CodeUseId;
    Result.FulfillmentSource = InObj.FulfillmentSource;
    return Result;
}

FRedeemCodeRequest FRedeemCodeRequestBP::ToNative() const
{
    FRedeemCodeRequest Result;
    Result.Code = this->Code;
    Result.CodeUseId = this->CodeUseId;
    Result.FulfillmentSource = this->FulfillmentSource;
    return Result;
}

FLineItemInfoBP FLineItemInfoBP::FromNative(const FPurchaseReceipt::FLineItemInfo &InObj)
{
    FLineItemInfoBP Result;
    Result.ItemName = InObj.ItemName;
    Result.UniqueId = InObj.UniqueId;
    Result.ValidationInfo = InObj.ValidationInfo;
    return Result;
}

FPurchaseReceipt::FLineItemInfo FLineItemInfoBP::ToNative() const
{
    FPurchaseReceipt::FLineItemInfo Result;
    Result.ItemName = this->ItemName;
    Result.UniqueId = this->UniqueId;
    Result.ValidationInfo = this->ValidationInfo;
    return Result;
}

FReceiptOfferEntryBP FReceiptOfferEntryBP::FromNative(const FPurchaseReceipt::FReceiptOfferEntry &InObj)
{
    FReceiptOfferEntryBP Result;
    Result.Namespace = InObj.Namespace;
    Result.OfferId = InObj.OfferId;
    Result.Quantity = InObj.Quantity;
    for (const auto &Entry : InObj.LineItems)
    {
        Result.LineItems.Add(FLineItemInfoBP::FromNative(Entry));
    }
    return Result;
}

FPurchaseReceipt::FReceiptOfferEntry FReceiptOfferEntryBP::ToNative() const
{
    FPurchaseReceipt::FReceiptOfferEntry Result;
    Result.Namespace = this->Namespace;
    Result.OfferId = this->OfferId;
    Result.Quantity = this->Quantity;
    for (const auto &Entry : this->LineItems)
    {
        Result.LineItems.Add(Entry.ToNative());
    }
    return Result;
}

FString UPurchaseReceipt::GetTransactionId()
{
    if (auto Pinned = this->Receipt.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->TransactionId;
        }
    }

    return TEXT("");
}

EPurchaseTransactionState_ UPurchaseReceipt::GetPurchaseTransactionState()
{
    if (auto Pinned = this->Receipt.Pin())
    {
        if (Pinned.IsValid())
        {
            return (EPurchaseTransactionState_)Pinned->TransactionState;
        }
    }

    return EPurchaseTransactionState_::NotStarted;
}

TArray<FReceiptOfferEntryBP> UPurchaseReceipt::GetReceiptOffers()
{
    if (auto Pinned = this->Receipt.Pin())
    {
        if (Pinned.IsValid())
        {
            TArray<FReceiptOfferEntryBP> Offers;
            for (const auto &Entry : Pinned->ReceiptOffers)
            {
                Offers.Add(FReceiptOfferEntryBP::FromNative(Entry));
            }
            return Offers;
        }
    }

    return TArray<FReceiptOfferEntryBP>();
}

UPurchaseReceipt *UPurchaseReceipt::FromNative(const TSharedRef<FPurchaseReceipt> &InObj)
{
    UPurchaseReceipt *Receipt = NewObject<UPurchaseReceipt>();
    Receipt->Receipt = InObj;
    return Receipt;
}

UPurchaseReceipt *UPurchaseReceipt::FromNative(const FPurchaseReceipt &InObj)
{
    UPurchaseReceipt *Receipt = NewObject<UPurchaseReceipt>();
    Receipt->Receipt = MakeShared<FPurchaseReceipt>(InObj);
    return Receipt;
}

TSharedRef<FPurchaseReceipt> UPurchaseReceipt::ToNative() const
{
    if (auto Pinned = this->Receipt.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned.ToSharedRef();
        }
    }

    return MakeShared<FPurchaseReceipt>();
}
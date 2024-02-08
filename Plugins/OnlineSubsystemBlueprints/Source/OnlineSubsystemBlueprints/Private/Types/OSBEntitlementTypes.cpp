// Copyright June Rhodes 2023. All Rights Reserved.

#include "Types/OSBEntitlementTypes.h"

FPurchaseOfferEntryBP FPurchaseOfferEntryBP::FromNative(const FPurchaseCheckoutRequest::FPurchaseOfferEntry &InObj)
{
    FPurchaseOfferEntryBP Result;
    Result.OfferId = InObj.OfferId;
    Result.OfferNamespace = InObj.OfferNamespace;
    Result.Quantity = InObj.Quantity;
    return Result;
}

FPurchaseCheckoutRequest::FPurchaseOfferEntry FPurchaseOfferEntryBP::ToNative() const
{
    return FPurchaseCheckoutRequest::FPurchaseOfferEntry(
        this->OfferNamespace,
        this->OfferId,
        this->Quantity,
        false /* Set only, so no way to surface it in blueprints. */);
}

FPurchaseCheckoutRequestBP FPurchaseCheckoutRequestBP::FromNative(const FPurchaseCheckoutRequest &InObj)
{
    FPurchaseCheckoutRequestBP Result;
    Result.AccountId = InObj.AccountId.IsSet() ? InObj.AccountId.GetValue() : TEXT("");
    for (const auto &Entry : InObj.PurchaseOffers)
    {
        Result.PurchaseOffers.Add(FPurchaseOfferEntryBP::FromNative(Entry));
    }
    return Result;
}

FPurchaseCheckoutRequest FPurchaseCheckoutRequestBP::ToNative() const
{
    FPurchaseCheckoutRequest Result;
    Result.AccountId = this->AccountId;
    for (const auto &Entry : this->PurchaseOffers)
    {
        Result.PurchaseOffers.Add(Entry.ToNative());
    }
    return Result;
}

FString UOnlineEntitlement::GetId()
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->Id;
        }
    }

    return TEXT("");
}

FString UOnlineEntitlement::GetName()
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->Name;
        }
    }

    return TEXT("");
}

FString UOnlineEntitlement::GetItemId()
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->ItemId;
        }
    }

    return TEXT("");
}

FString UOnlineEntitlement::GetNamespace()
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->Namespace;
        }
    }

    return TEXT("");
}

bool UOnlineEntitlement::IsConsumable()
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->bIsConsumable;
        }
    }

    return false;
}

int32 UOnlineEntitlement::GetRemainingCount()
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->RemainingCount;
        }
    }

    return 0;
}

int32 UOnlineEntitlement::GetConsumedCount()
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->ConsumedCount;
        }
    }

    return 0;
}

FString UOnlineEntitlement::GetStartDate()
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->StartDate;
        }
    }

    return TEXT("");
}

FString UOnlineEntitlement::GetEndDate()
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->EndDate;
        }
    }

    return TEXT("");
}

FString UOnlineEntitlement::GetStatus()
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned->Status;
        }
    }

    return TEXT("");
}

UOnlineEntitlement *UOnlineEntitlement::FromNative(const TSharedPtr<FOnlineEntitlement> &InObj)
{
    if (!InObj.IsValid())
    {
        return nullptr;
    }

    UOnlineEntitlement *Entitlement = NewObject<UOnlineEntitlement>();
    Entitlement->Entitlement = InObj;
    return Entitlement;
}

TSharedPtr<FOnlineEntitlement> UOnlineEntitlement::ToNative() const
{
    if (auto Pinned = this->Entitlement.Pin())
    {
        if (Pinned.IsValid())
        {
            return Pinned;
        }
    }

    return nullptr;
}
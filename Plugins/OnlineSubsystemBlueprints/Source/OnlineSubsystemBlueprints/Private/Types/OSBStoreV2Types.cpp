// Copyright June Rhodes 2023. All Rights Reserved.

#include "Types/OSBStoreV2Types.h"

FOnlineStoreCategoryBP FOnlineStoreCategoryBP::FromNative(const FOnlineStoreCategory &InObj)
{
    FOnlineStoreCategoryBP Result;
    Result.Id = InObj.Id;
    Result.Description = InObj.Description;
    return Result;
}

FOnlineStoreCategory FOnlineStoreCategoryBP::ToNative() const
{
    FOnlineStoreCategory Result;
    Result.Id = this->Id;
    Result.Description = this->Description;
    return Result;
}

FOnlineStoreFilterBP FOnlineStoreFilterBP::FromNative(const FOnlineStoreFilter &InObj)
{
    FOnlineStoreFilterBP Result;
    Result.Keywords = InObj.Keywords;
    for (const auto &Entry : InObj.IncludeCategories)
    {
        Result.IncludeCategories.Add(FOnlineStoreCategoryBP::FromNative(Entry));
    }
    for (const auto &Entry : InObj.ExcludeCategories)
    {
        Result.ExcludeCategories.Add(FOnlineStoreCategoryBP::FromNative(Entry));
    }
    return Result;
}

FOnlineStoreFilter FOnlineStoreFilterBP::ToNative() const
{
    FOnlineStoreFilter Result;
    Result.Keywords = this->Keywords;
    for (const auto &Entry : this->IncludeCategories)
    {
        Result.IncludeCategories.Add(Entry.ToNative());
    }
    for (const auto &Entry : this->ExcludeCategories)
    {
        Result.ExcludeCategories.Add(Entry.ToNative());
    }
    return Result;
}

FString UOnlineStoreOffer::GetOfferId()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->OfferId;
        }
    }
    return TEXT("");
}

FText UOnlineStoreOffer::GetTitle()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->Title;
        }
    }
    return FText::GetEmpty();
}

FText UOnlineStoreOffer::GetDescription()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->Description;
        }
    }
    return FText::GetEmpty();
}

FText UOnlineStoreOffer::GetLongDescription()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->LongDescription;
        }
    }
    return FText::GetEmpty();
}

FText UOnlineStoreOffer::GetDisplayRegularPrice()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->GetDisplayRegularPrice();
        }
    }
    return FText::GetEmpty();
}

FText UOnlineStoreOffer::GetDisplayPrice()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->GetDisplayPrice();
        }
    }
    return FText::GetEmpty();
}

int64 UOnlineStoreOffer::GetRegularPrice()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->RegularPrice;
        }
    }
    return -1;
}

int64 UOnlineStoreOffer::GetNumericPrice()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->NumericPrice;
        }
    }
    return -1;
}

FString UOnlineStoreOffer::GetCurrencyCode()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->CurrencyCode;
        }
    }
    return TEXT("");
}

FDateTime UOnlineStoreOffer::GetReleaseDate()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->ReleaseDate;
        }
    }
    return FDateTime::MinValue();
}

FDateTime UOnlineStoreOffer::GetExpirationDate()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->ExpirationDate;
        }
    }
    return FDateTime::MaxValue();
}

TMap<FString, FString> UOnlineStoreOffer::GetDynamicFields()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->DynamicFields;
        }
    }
    return TMap<FString, FString>();
}

bool UOnlineStoreOffer::IsPurchasable()
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned->IsPurchaseable();
        }
    }
    return false;
}

UOnlineStoreOffer *UOnlineStoreOffer::FromNative(TSharedPtr<FOnlineStoreOffer> InObj)
{
    auto Ref = NewObject<UOnlineStoreOffer>();
    Ref->Offer = InObj;
    return Ref;
}

TSharedPtr<FOnlineStoreOffer> UOnlineStoreOffer::ToNative() const
{
    if (auto OfferPinned = this->Offer.Pin())
    {
        if (OfferPinned.IsValid())
        {
            return OfferPinned;
        }
    }
    return nullptr;
}
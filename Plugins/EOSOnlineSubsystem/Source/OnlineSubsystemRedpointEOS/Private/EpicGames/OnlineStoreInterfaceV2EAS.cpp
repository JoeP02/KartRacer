// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_HAS_AUTHENTICATION

#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreInterfaceV2EAS.h"

#include "OnlineJsonSerializer.h"
#include "OnlineSubsystemRedpointEOS/Public/EOSError.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSErrorConv.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreOfferEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreOfferItemEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreOfferItemType.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/UniqueNetIdEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

EOS_ENABLE_STRICT_WARNINGS

void FOnlineStoreInterfaceV2EAS::QueryCategories(
    const FUniqueNetId &UserId,
    const FOnQueryOnlineStoreCategoriesComplete &Delegate)
{
    // Epic Games e-commerce doesn't support categories, so we just return true. There
    // are no categories for offers.
    Delegate.ExecuteIfBound(true, TEXT(""));
}

void FOnlineStoreInterfaceV2EAS::GetCategories(TArray<FOnlineStoreCategory> &OutCategories) const
{
    // Epic Games e-commerce doesn't support categories, so we just return true. There
    // are no categories for offers.
    OutCategories.Reset();
}

void FOnlineStoreInterfaceV2EAS::QueryOffersByFilter(
    const FUniqueNetId &UserId,
    const FOnlineStoreFilter &Filter,
    const FOnQueryOnlineStoreOffersComplete &Delegate)
{
    EOS_EpicAccountId AccountId = StaticCastSharedRef<const FUniqueNetIdEAS>(UserId.AsShared())->GetEpicAccountId();

    EOS_Ecom_QueryOffersOptions Opts = {};
    Opts.ApiVersion = EOS_ECOM_QUERYOFFERS_API_LATEST;
    Opts.LocalUserId = AccountId;
    Opts.OverrideCatalogNamespace = nullptr;

    EOSRunOperation<EOS_HEcom, EOS_Ecom_QueryOffersOptions, EOS_Ecom_QueryOffersCallbackInfo>(
        this->Ecom,
        &Opts,
        &EOS_Ecom_QueryOffers,
        [WeakThis = GetWeakThis(this), AccountId, Delegate](const EOS_Ecom_QueryOffersCallbackInfo *Info) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (Info->ResultCode != EOS_EResult::EOS_Success)
                {
                    Delegate.ExecuteIfBound(
                        false,
                        TArray<FUniqueOfferId>(),
                        ConvertError(
                            TEXT("FOnlineStoreInterfaceV2EAS::QueryOffersByFilter"),
                            TEXT("Failed to query store offers."),
                            Info->ResultCode)
                            .ToLogString());
                    return;
                }

                TMap<FUniqueOfferId, TSharedPtr<FOnlineStoreOffer>> Offers;
                TMap<FString, TSharedRef<class FOnlineStoreOfferItemEAS>> Items;

                EOS_Ecom_GetOfferCountOptions CountOpts = {};
                CountOpts.ApiVersion = EOS_ECOM_GETOFFERCOUNT_API_LATEST;
                CountOpts.LocalUserId = AccountId;
                uint32_t OfferCount = EOS_Ecom_GetOfferCount(This->Ecom, &CountOpts);
                for (uint32_t i = 0; i < OfferCount; i++)
                {
                    EOS_Ecom_CopyOfferByIndexOptions CopyOpts = {};
                    CopyOpts.ApiVersion = EOS_ECOM_COPYOFFERBYINDEX_API_LATEST;
                    CopyOpts.LocalUserId = AccountId;
                    CopyOpts.OfferIndex = i;
                    EOS_Ecom_CatalogOffer *OfferData = nullptr;
                    EOS_EResult CopyResult = EOS_Ecom_CopyOfferByIndex(This->Ecom, &CopyOpts, &OfferData);
                    if (CopyResult != EOS_EResult::EOS_Success)
                    {
                        UE_LOG(
                            LogRedpointEOS,
                            Error,
                            TEXT("%s"),
                            *ConvertError(
                                 TEXT("FOnlineStoreInterfaceV2EAS::QueryOffersByFilter"),
                                 FString::Printf(TEXT("Failed to copy offer at index %u."), i),
                                 CopyResult)
                                 .ToLogString());
                        continue;
                    }

                    TSharedRef<FOnlineStoreOfferEAS> Offer = MakeShared<FOnlineStoreOfferEAS>();
                    Offer->OfferId = EOSString_Ecom_CatalogOfferId::FromAnsiString(OfferData->Id);

                    Offer->Title = FText::FromString(EOSString_Utf8Unlimited::FromUtf8String(OfferData->TitleText));
                    Offer->Description =
                        FText::FromString(EOSString_Utf8Unlimited::FromUtf8String(OfferData->DescriptionText));
                    Offer->LongDescription =
                        FText::FromString(EOSString_Utf8Unlimited::FromUtf8String(OfferData->LongDescriptionText));

                    if (OfferData->PriceResult == EOS_EResult::EOS_Success)
                    {
                        Offer->RegularPriceText = FText::GetEmpty();
#if !defined(UE_4_27_OR_LATER)
                        Offer->RegularPrice = (int32)OfferData->OriginalPrice64;
#else
                        Offer->RegularPrice = OfferData->OriginalPrice64;
#endif

                        Offer->PriceText = FText::GetEmpty();
#if !defined(UE_4_27_OR_LATER)
                        Offer->NumericPrice = (int32)OfferData->CurrentPrice64;
#else
                        Offer->NumericPrice = OfferData->CurrentPrice64;
#endif

                        Offer->bAvailableForPurchase = OfferData->bAvailableForPurchase == EOS_TRUE;
                    }
                    else
                    {
                        // Could not retrieve pricing data.
                        Offer->bAvailableForPurchase = false;
                    }

                    Offer->CurrencyCode = EOSString_Utf8Unlimited::FromUtf8String(OfferData->CurrencyCode);

                    // Epic Games doesn't surface the release date of e-commerce items.
                    Offer->ReleaseDate = FDateTime::MinValue();
                    Offer->ExpirationDate = OfferData->ExpirationTimestamp == -1
                                                ? FDateTime::MaxValue()
                                                : FDateTime::FromUnixTimestamp(OfferData->ExpirationTimestamp);
                    Offer->DiscountType = Offer->RegularPrice == Offer->NumericPrice
                                              ? EOnlineStoreOfferDiscountType::NotOnSale
                                              : EOnlineStoreOfferDiscountType::Percentage;

                    Offer->CatalogNamespace =
                        EOSString_Ecom_CatalogNamespace::FromAnsiString(OfferData->CatalogNamespace);
                    Offer->DiscountPercentage = OfferData->DiscountPercentage;
                    Offer->PurchaseLimit = OfferData->PurchaseLimit;
                    Offer->DecimalPoint = OfferData->DecimalPoint;

                    EOS_Ecom_GetOfferItemCountOptions CountItemOpts = {};
                    CountItemOpts.ApiVersion = EOS_ECOM_GETOFFERITEMCOUNT_API_LATEST;
                    CountItemOpts.LocalUserId = AccountId;
                    CountItemOpts.OfferId = OfferData->Id;

                    uint32_t ItemCount = EOS_Ecom_GetOfferItemCount(This->Ecom, &CountItemOpts);
                    for (uint32_t ii = 0; ii < ItemCount; ii++)
                    {
                        EOS_Ecom_CopyOfferItemByIndexOptions CopyItemOpts = {};
                        CopyItemOpts.ApiVersion = EOS_ECOM_COPYOFFERITEMBYINDEX_API_LATEST;
                        CopyItemOpts.LocalUserId = AccountId;
                        CopyItemOpts.OfferId = OfferData->Id;
                        CopyItemOpts.ItemIndex = ii;
                        EOS_Ecom_CatalogItem *ItemData = nullptr;
                        EOS_EResult CopyItemResult =
                            EOS_Ecom_CopyOfferItemByIndex(This->Ecom, &CopyItemOpts, &ItemData);
                        if (CopyItemResult != EOS_EResult::EOS_Success)
                        {
                            UE_LOG(
                                LogRedpointEOS,
                                Error,
                                TEXT("%s"),
                                *ConvertError(
                                     TEXT("FOnlineStoreInterfaceV2EAS::QueryOffersByFilter"),
                                     FString::Printf(TEXT("Failed to copy item at index %u."), i),
                                     CopyItemResult)
                                     .ToLogString());
                            continue;
                        }

                        TSharedRef<FOnlineStoreOfferItemEAS> Item = MakeShared<FOnlineStoreOfferItemEAS>();
                        Item->ItemId = EOSString_Ecom_CatalogItemId::FromAnsiString(ItemData->Id);
                        Item->EntitlementName =
                            EOSString_Ecom_EntitlementName::FromAnsiString(ItemData->EntitlementName);
                        Item->Title = FText::FromString(EOSString_Utf8Unlimited::FromUtf8String(ItemData->TitleText));
                        Item->Description =
                            FText::FromString(EOSString_Utf8Unlimited::FromUtf8String(ItemData->DescriptionText));
                        Item->LongDescription =
                            FText::FromString(EOSString_Utf8Unlimited::FromUtf8String(ItemData->LongDescriptionText));
                        Item->TechnicalDetails =
                            FText::FromString(EOSString_Utf8Unlimited::FromUtf8String(ItemData->TechnicalDetailsText));
                        Item->Developer =
                            FText::FromString(EOSString_Utf8Unlimited::FromUtf8String(ItemData->DeveloperText));
                        Item->ItemType = EOnlineStoreOfferItemType::Other;
                        switch (ItemData->ItemType)
                        {
                        case EOS_EEcomItemType::EOS_EIT_Consumable:
                            Item->ItemType = EOnlineStoreOfferItemType::Consumable;
                            break;
                        case EOS_EEcomItemType::EOS_EIT_Durable:
                            Item->ItemType = EOnlineStoreOfferItemType::Durable;
                            break;
                        }
                        Item->EntitlementEndTimestamp.Reset();
                        if (ItemData->EntitlementEndTimestamp != EOS_ECOM_ENTITLEMENT_ENDTIMESTAMP_UNDEFINED)
                        {
                            Item->EntitlementEndTimestamp =
                                FDateTime::FromUnixTimestamp(ItemData->EntitlementEndTimestamp);
                        }
                        Items.Add(Item->ItemId, Item);
                        Offer->Items.Add(Item);

                        EOS_Ecom_CatalogItem_Release(ItemData);
                    }

                    // Now we need to add the dynamic catalog data that we don't
                    // have fields for in the base type.
                    Offer->DynamicFields.Reset();
                    Offer->DynamicFields.Add(TEXT("CatalogNamespace"), Offer->CatalogNamespace);
                    Offer->DynamicFields.Add(
                        TEXT("DiscountPercentage"),
                        FString::Printf(TEXT("%u"), Offer->DiscountPercentage));
                    Offer->DynamicFields.Add(TEXT("PurchaseLimit"), FString::Printf(TEXT("%d"), Offer->PurchaseLimit));
                    Offer->DynamicFields.Add(TEXT("DecimalPoint"), FString::Printf(TEXT("%u"), Offer->DecimalPoint));
                    FString OutputString;
                    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
                    FJsonSerializerWriter<> Serializer = FJsonSerializerWriter<>(Writer);
                    Writer->WriteArrayStart();
                    for (const auto &Item : Offer->Items)
                    {
                        Item->Serialize(Serializer, false);
                    }
                    Writer->WriteArrayEnd();
                    Writer->Close();
                    Offer->DynamicFields.Add(TEXT("Items"), OutputString);

                    Offers.Add(Offer->OfferId, Offer);
                }

                TArray<FUniqueOfferId> Ids;
                for (const auto &KV : Offers)
                {
                    Ids.Add(KV.Key);
                }

                This->CachedOffers = Offers;
                This->CachedItems = Items;
                Delegate.ExecuteIfBound(true, Ids, TEXT(""));
            }
        });
}

void FOnlineStoreInterfaceV2EAS::QueryOffersById(
    const FUniqueNetId &UserId,
    const TArray<FUniqueOfferId> &OfferIds,
    const FOnQueryOnlineStoreOffersComplete &Delegate)
{
    if (OfferIds.Num() == 0)
    {
        Delegate.ExecuteIfBound(
            false,
            TArray<FUniqueOfferId>(),
            OnlineRedpointEOS::Errors::InvalidRequest(
                TEXT("FOnlineStoreInterfaceV2EAS::QueryOffersById"),
                TEXT("You must pass at least one offer ID to query by offer IDs."))
                .ToLogString());
        return;
    }

    this->QueryOffersByFilter(
        UserId,
        FOnlineStoreFilter(),
        FOnQueryOnlineStoreOffersComplete::CreateLambda(
            [OfferIds,
             Delegate](bool bWasSuccessful, const TArray<FUniqueOfferId> &ReturnedOfferIds, const FString &Error) {
                TSet<FUniqueOfferId> RequestedIds = TSet<FUniqueOfferId>(OfferIds);
                TArray<FUniqueOfferId> ResultIds;
                for (const auto &Id : ReturnedOfferIds)
                {
                    if (RequestedIds.Contains(Id))
                    {
                        ResultIds.Add(Id);
                    }
                }
                if (ResultIds.Num() == 0 && RequestedIds.Num() > 0)
                {
                    Delegate.ExecuteIfBound(
                        false,
                        ResultIds,
                        OnlineRedpointEOS::Errors::NotFound(
                            TEXT("FOnlineStoreInterfaceV2EAS::QueryOffersById"),
                            TEXT("None of the requested offer IDs could be found."))
                            .ToLogString());
                    return;
                }
                Delegate.ExecuteIfBound(true, ResultIds, TEXT(""));
            }));
}

void FOnlineStoreInterfaceV2EAS::GetOffers(TArray<FOnlineStoreOfferRef> &OutOffers) const
{
    for (const auto &KV : this->CachedOffers)
    {
        OutOffers.Add(KV.Value.ToSharedRef());
    }
}

TSharedPtr<FOnlineStoreOffer> FOnlineStoreInterfaceV2EAS::GetOffer(const FUniqueOfferId &OfferId) const
{
    if (this->CachedOffers.Contains(OfferId))
    {
        return this->CachedOffers[OfferId];
    }

    return nullptr;
}

void FOnlineStoreInterfaceV2EAS::GetItems(TArray<TSharedRef<class FOnlineStoreOfferItemEAS>> &OutItems) const
{
    OutItems.Empty();
    for (const auto &KV : this->CachedItems)
    {
        OutItems.Add(KV.Value);
    }
}

TSharedPtr<FOnlineStoreOfferItemEAS> FOnlineStoreInterfaceV2EAS::GetItem(const FString &ItemId) const
{
    if (this->CachedItems.Contains(ItemId))
    {
        return this->CachedItems[ItemId];
    }

    return nullptr;
}

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
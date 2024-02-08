// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_HAS_AUTHENTICATION

#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineEntitlementsInterfaceEAS.h"

#include "OnlineSubsystemRedpointEOS/Public/EOSError.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSErrorConv.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreInterfaceV2EAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreOfferEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreOfferItemEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreOfferItemType.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/UniqueNetIdEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

EOS_ENABLE_STRICT_WARNINGS

class FOnlineEntitlementEAS : public FOnlineEntitlement, public TSharedFromThis<FOnlineEntitlementEAS>
{
public:
    FOnlineEntitlementEAS() = default;
    UE_NONCOPYABLE(FOnlineEntitlementEAS);
    virtual ~FOnlineEntitlementEAS() = default;

    TMap<FString, FString> Attributes;
    virtual bool GetAttribute(const FString &AttrName, FString &OutAttrValue) const override
    {
        if (this->Attributes.Contains(AttrName))
        {
            OutAttrValue = this->Attributes[AttrName];
            return true;
        }
        return false;
    }
};

TSharedPtr<FOnlineEntitlement> FOnlineEntitlementsInterfaceEAS::GetEntitlement(
    const FUniqueNetId &UserId,
    const FUniqueEntitlementId &EntitlementId)
{
    if (!this->CachedEntitlementsMapByEntitlementId.Contains(UserId) ||
        !this->CachedEntitlementsMapByEntitlementId[UserId].Contains(EntitlementId))
    {
        return nullptr;
    }

    return this->CachedEntitlementsMapByEntitlementId[UserId][EntitlementId];
}

TSharedPtr<FOnlineEntitlement> FOnlineEntitlementsInterfaceEAS::GetItemEntitlement(
    const FUniqueNetId &UserId,
    const FString &ItemId)
{
    if (!this->CachedEntitlementsMapByItemId.Contains(UserId) ||
        !this->CachedEntitlementsMapByItemId[UserId].Contains(ItemId))
    {
        return nullptr;
    }

    return this->CachedEntitlementsMapByItemId[UserId][ItemId];
}

void FOnlineEntitlementsInterfaceEAS::GetAllEntitlements(
    const FUniqueNetId &UserId,
    const FString &Namespace,
    TArray<TSharedRef<FOnlineEntitlement>> &OutUserEntitlements)
{
    if (!this->CachedEntitlementsArray.Contains(UserId) || !Namespace.IsEmpty())
    {
        OutUserEntitlements.Empty();
        return;
    }

    OutUserEntitlements = this->CachedEntitlementsArray[UserId];
}

bool FOnlineEntitlementsInterfaceEAS::QueryEntitlements(
    const FUniqueNetId &UserId,
    const FString &Namespace,
    const FPagedQuery &Page)
{
    return this->QueryEntitlements(
        UserId,
        Namespace,
        Page,
        FOnQueryEntitlementsComplete::FDelegate::CreateLambda([WeakThis = GetWeakThis(this)](
                                                                  bool bWasSuccessful,
                                                                  const FUniqueNetId &UserId,
                                                                  const FString &Namespace,
                                                                  const FString &Error) {
            if (auto This = PinWeakThis(WeakThis))
            {
                This->TriggerOnQueryEntitlementsCompleteDelegates(bWasSuccessful, UserId, Namespace, Error);
            }
        }));
}

bool FOnlineEntitlementsInterfaceEAS::QueryEntitlements(
    const FUniqueNetId &UserId,
    const FString &Namespace,
    const FPagedQuery &Page,
    const FOnQueryEntitlementsComplete::FDelegate &Delegate)
{
    TSharedRef<const FUniqueNetIdEAS> UserIdEAS = StaticCastSharedRef<const FUniqueNetIdEAS>(UserId.AsShared());

    this->Store->QueryOffersByFilter(
        UserId,
        FOnlineStoreFilter(),
        FOnQueryOnlineStoreOffersComplete::CreateLambda([WeakThis = GetWeakThis(this), UserIdEAS, Namespace, Delegate](
                                                            bool bWasSuccessful,
                                                            const TArray<FUniqueOfferId> &OfferIds,
                                                            const FString &Error) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (!bWasSuccessful)
                {
                    FOnlineError ErrorParam = OnlineRedpointEOS::Errors::UnexpectedError(
                        TEXT("FOnlineEntitlementsInterfaceEAS::QueryEntitlements"),
                        *FString::Printf(
                            TEXT("Failed to query offers to get related entitlement information: %s"),
                            *Error));
                    Delegate.ExecuteIfBound(false, *UserIdEAS, Namespace, ErrorParam.ToLogString());
                    return;
                }

                EOS_Ecom_QueryEntitlementsOptions Opts = {};
                Opts.ApiVersion = EOS_ECOM_QUERYENTITLEMENTS_API_LATEST;
                Opts.LocalUserId = UserIdEAS->GetEpicAccountId();
                Opts.bIncludeRedeemed = true;
                Opts.EntitlementNameCount = 0;
                Opts.EntitlementNames = nullptr;

                EOSRunOperation<EOS_HEcom, EOS_Ecom_QueryEntitlementsOptions, EOS_Ecom_QueryEntitlementsCallbackInfo>(
                    This->Ecom,
                    &Opts,
                    &EOS_Ecom_QueryEntitlements,
                    [WeakThis = GetWeakThis(This), UserIdEAS, Namespace, Delegate](
                        const EOS_Ecom_QueryEntitlementsCallbackInfo *Info) {
                        if (auto This = PinWeakThis(WeakThis))
                        {
                            if (Info->ResultCode != EOS_EResult::EOS_Success)
                            {
                                FOnlineError Error = ConvertError(
                                    TEXT("FOnlineEntitlementsInterfaceEAS::QueryEntitlements"),
                                    TEXT("Failed to query entitlements."),
                                    Info->ResultCode);
                                Delegate.ExecuteIfBound(false, *UserIdEAS, Namespace, Error.ToLogString());
                                return;
                            }

                            TArray<TSharedRef<FOnlineEntitlement>> EntitlementsArray;
                            TMap<FString, TSharedPtr<FOnlineEntitlement>> EntitlementsMapByItemId;
                            TMap<FUniqueEntitlementId, TSharedPtr<FOnlineEntitlement>> EntitlementsMapByEntitlementId;

                            EOS_Ecom_GetEntitlementsCountOptions CountOpts = {};
                            CountOpts.ApiVersion = EOS_ECOM_GETENTITLEMENTSCOUNT_API_LATEST;
                            CountOpts.LocalUserId = UserIdEAS->GetEpicAccountId();
                            uint32_t EntitlementCount = EOS_Ecom_GetEntitlementsCount(This->Ecom, &CountOpts);
                            for (uint32_t i = 0; i < EntitlementCount; i++)
                            {
                                EOS_Ecom_CopyEntitlementByIndexOptions CopyOpts = {};
                                CopyOpts.ApiVersion = EOS_ECOM_COPYENTITLEMENTBYINDEX_API_LATEST;
                                CopyOpts.LocalUserId = UserIdEAS->GetEpicAccountId();
                                CopyOpts.EntitlementIndex = i;
                                EOS_Ecom_Entitlement *EntitlementData = nullptr;
                                EOS_EResult CopyResult =
                                    EOS_Ecom_CopyEntitlementByIndex(This->Ecom, &CopyOpts, &EntitlementData);
                                if (CopyResult != EOS_EResult::EOS_Success)
                                {
                                    UE_LOG(
                                        LogRedpointEOS,
                                        Error,
                                        TEXT("%s"),
                                        *ConvertError(
                                             TEXT("FOnlineEntitlementsInterfaceEAS::QueryEntitlements"),
                                             FString::Printf(TEXT("Failed to copy entitlement at index %u."), i),
                                             CopyResult)
                                             .ToLogString());
                                    continue;
                                }

                                FString ItemId =
                                    EOSString_Ecom_CatalogOfferId::FromAnsiString(EntitlementData->CatalogItemId);

                                TSharedPtr<FOnlineStoreOfferItemEAS> Item = This->Store->GetItem(ItemId);

                                TSharedRef<FOnlineEntitlementEAS> Entitlement = MakeShared<FOnlineEntitlementEAS>();
                                Entitlement->Id =
                                    EOSString_Ecom_EntitlementId::FromAnsiString(EntitlementData->EntitlementId);
                                FString EntitlementName =
                                    EOSString_Utf8Unlimited::FromUtf8String(EntitlementData->EntitlementName);
                                Entitlement->Attributes.Add(
                                    TEXT("EntitlementName"),
                                    EntitlementName);
                                Entitlement->ItemId = ItemId;
                                Entitlement->Namespace = TEXT("");
                                if (Item.IsValid())
                                {
                                    if (Item->ItemType == EOnlineStoreOfferItemType::Consumable)
                                    {
                                        // Report whether this item has been consumed.
                                        Entitlement->bIsConsumable = true;
                                        if (EntitlementData->bRedeemed)
                                        {
                                            Entitlement->RemainingCount = 0;
                                            Entitlement->ConsumedCount = 1;
                                        }
                                        else
                                        {
                                            Entitlement->RemainingCount = 1;
                                            Entitlement->ConsumedCount = 0;
                                        }
                                    }
                                    else
                                    {
                                        // This item isn't consumable.
                                        Entitlement->bIsConsumable = false;
                                        Entitlement->RemainingCount = 1;
                                        Entitlement->ConsumedCount = 0;
                                    }

                                    Entitlement->Name = Item->Title.ToString();
                                    Entitlement->Attributes.Add(TEXT("ItemDescription"), Item->Description.ToString());
                                    Entitlement->Attributes.Add(
                                        TEXT("ItemLongDescription"),
                                        Item->LongDescription.ToString());
                                    Entitlement->Attributes.Add(
                                        TEXT("ItemTechnicalDetails"),
                                        Item->TechnicalDetails.ToString());
                                    Entitlement->Attributes.Add(TEXT("ItemDeveloper"), Item->Developer.ToString());
                                    switch (Item->ItemType)
                                    {
                                    case EOnlineStoreOfferItemType::Consumable:
                                        Entitlement->Attributes.Add(TEXT("ItemType"), TEXT("Consumable"));
                                        break;
                                    case EOnlineStoreOfferItemType::Durable:
                                        Entitlement->Attributes.Add(TEXT("ItemType"), TEXT("Durable"));
                                        break;
                                    case EOnlineStoreOfferItemType::Other:
                                    default:
                                        Entitlement->Attributes.Add(TEXT("ItemType"), TEXT("Other"));
                                        break;
                                    }
                                    if (Item->EntitlementEndTimestamp.IsSet())
                                    {
                                        Entitlement->Attributes.Add(
                                            TEXT("ItemEntitlementEndTimestamp"),
                                            FString::Printf(
                                                TEXT("%llu"),
                                                Item->EntitlementEndTimestamp.GetValue().ToUnixTimestamp()));
                                    }
                                }
                                else
                                {
                                    // There's no information about this item any more.
                                    Entitlement->Name = EntitlementName;
                                    Entitlement->bIsConsumable = false;
                                    Entitlement->RemainingCount = 1;
                                    Entitlement->ConsumedCount = 0;
                                }
                                Entitlement->StartDate = TEXT("");
                                Entitlement->EndDate = TEXT("");
                                if (EntitlementData->EndTimestamp != -1)
                                {
                                    Entitlement->EndDate =
                                        FDateTime::FromUnixTimestamp(EntitlementData->EndTimestamp).ToString();
                                }
                                Entitlement->Status = TEXT("Active");
                                if (EntitlementData->EndTimestamp > FDateTime::UtcNow().ToUnixTimestamp())
                                {
                                    Entitlement->Status = TEXT("Expired");
                                }
                                else if (EntitlementData->bRedeemed == EOS_TRUE)
                                {
                                    Entitlement->Status = TEXT("Redeemed");
                                }

                                EntitlementsMapByEntitlementId.Add(
                                    Entitlement->Id,
                                    StaticCastSharedRef<FOnlineEntitlement>(Entitlement));
                                EntitlementsMapByItemId.Add(
                                    Entitlement->ItemId,
                                    StaticCastSharedRef<FOnlineEntitlement>(Entitlement));
                                EntitlementsArray.Add(StaticCastSharedRef<FOnlineEntitlement>(Entitlement));

                                EOS_Ecom_Entitlement_Release(EntitlementData);
                            }

                            This->CachedEntitlementsMapByEntitlementId.Add(*UserIdEAS, EntitlementsMapByEntitlementId);
                            This->CachedEntitlementsMapByItemId.Add(*UserIdEAS, EntitlementsMapByItemId);
                            This->CachedEntitlementsArray.Add(*UserIdEAS, EntitlementsArray);
                            Delegate.ExecuteIfBound(true, *UserIdEAS, Namespace, TEXT(""));
                        }
                    });
            }
        }));
    return true;
}

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_HAS_AUTHENTICATION

#include "CoreMinimal.h"
#include "OnlineJsonSerializer.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreOfferItemType.h"

EOS_ENABLE_STRICT_WARNINGS

class FOnlineStoreOfferItemEAS : public TSharedFromThis<FOnlineStoreOfferItemEAS>, public FOnlineJsonSerializable
{
public:
    FOnlineStoreOfferItemEAS() = default;
    UE_NONCOPYABLE(FOnlineStoreOfferItemEAS);
    virtual ~FOnlineStoreOfferItemEAS() = default;

    FString ItemId;

    FString EntitlementName;

    FText Title;

    FText Description;

    FText LongDescription;

    FText TechnicalDetails;

    FText Developer;

    EOnlineStoreOfferItemType ItemType;

    TOptional<FDateTime> EntitlementEndTimestamp;

    BEGIN_ONLINE_JSON_SERIALIZER
    ONLINE_JSON_SERIALIZE("ItemId", ItemId);
    ONLINE_JSON_SERIALIZE("EntitlementName", EntitlementName);
    ONLINE_JSON_SERIALIZE("Title", Title);
    ONLINE_JSON_SERIALIZE("Description", Description);
    ONLINE_JSON_SERIALIZE("LongDescription", LongDescription);
    ONLINE_JSON_SERIALIZE("TechnicalDetails", TechnicalDetails);
    ONLINE_JSON_SERIALIZE("Developer", Developer);
    if (Serializer.IsLoading())
    {
        // @note: We don't need to implement this.
    }
    else
    {
        FString ItemTypeString;
        switch (ItemType)
        {
        case EOnlineStoreOfferItemType::Durable:
            ItemTypeString = TEXT("Durable");
            break;
        case EOnlineStoreOfferItemType::Consumable:
            ItemTypeString = TEXT("Consumable");
            break;
        case EOnlineStoreOfferItemType::Other:
            ItemTypeString = TEXT("Other");
            break;
        }
        Serializer.Serialize(TEXT("ItemType"), ItemTypeString);
        if (EntitlementEndTimestamp.IsSet())
        {
            Serializer.Serialize(TEXT("EntitlementEndTimestamp"), EntitlementEndTimestamp.GetValue());
        }
    }
    END_ONLINE_JSON_SERIALIZER
};

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
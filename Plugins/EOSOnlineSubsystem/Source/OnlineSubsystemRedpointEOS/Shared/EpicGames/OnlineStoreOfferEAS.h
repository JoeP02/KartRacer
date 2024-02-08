// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_HAS_AUTHENTICATION

#include "CoreMinimal.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreOfferItemEAS.h"

EOS_ENABLE_STRICT_WARNINGS

class FOnlineStoreOfferEAS : public FOnlineStoreOffer, public TSharedFromThis<FOnlineStoreOfferEAS>
{
public:
    TArray<TSharedRef<FOnlineStoreOfferItemEAS>> Items;

    FOnlineStoreOfferEAS() = default;
    UE_NONCOPYABLE(FOnlineStoreOfferEAS);
    virtual ~FOnlineStoreOfferEAS() = default;

    bool bAvailableForPurchase;
    virtual bool IsPurchaseable() const override
    {
        return this->bAvailableForPurchase;
    }

    FString CatalogNamespace;

    uint8 DiscountPercentage;

    int32 PurchaseLimit;

    uint32 DecimalPoint;
};

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
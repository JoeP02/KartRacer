// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineStoreInterfaceV2.h"

#if EOS_GOOGLE_ENABLED

#include "OnlineIdentityInterfaceRedpointGoogle.h"

class FOnlineStoreInterfaceV2RedpointGoogle
    : public IOnlineStoreV2,
      public TSharedFromThis<FOnlineStoreInterfaceV2RedpointGoogle, ESPMode::ThreadSafe>
{
public:
    TSharedRef<FOnlineIdentityInterfaceRedpointGoogle> IdentityGooglePlay;
    bool bQueriedOffers;
    TArray<FOnlineStoreOfferRef> CachedOffers;
    TMap<FUniqueOfferId, FOnlineStoreOfferRef> CachedOffersById;

    FOnlineStoreInterfaceV2RedpointGoogle(
        const TSharedRef<FOnlineIdentityInterfaceRedpointGoogle> &InIdentityGooglePlay);
    virtual ~FOnlineStoreInterfaceV2RedpointGoogle();
    UE_NONCOPYABLE(FOnlineStoreInterfaceV2RedpointGoogle);

    virtual void QueryCategories(const FUniqueNetId &UserId, const FOnQueryOnlineStoreCategoriesComplete &Delegate)
        override;
    virtual void GetCategories(TArray<FOnlineStoreCategory> &OutCategories) const override;
    virtual void QueryOffersByFilter(
        const FUniqueNetId &UserId,
        const FOnlineStoreFilter &Filter,
        const FOnQueryOnlineStoreOffersComplete &Delegate) override;
    virtual void QueryOffersById(
        const FUniqueNetId &UserId,
        const TArray<FUniqueOfferId> &OfferIds,
        const FOnQueryOnlineStoreOffersComplete &Delegate) override;
    virtual void GetOffers(TArray<FOnlineStoreOfferRef> &OutOffers) const override;
    virtual TSharedPtr<FOnlineStoreOffer> GetOffer(const FUniqueOfferId &OfferId) const override;
};

#endif
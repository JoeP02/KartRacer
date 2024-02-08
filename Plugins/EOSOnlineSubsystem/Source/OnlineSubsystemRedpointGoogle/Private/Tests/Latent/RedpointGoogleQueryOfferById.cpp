// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)

#include "Tests/Latent/RedpointGoogleQueryOfferById.h"

void FRedpointGoogleQueryOfferById::OnOffersQueried(
    bool bWasSuccessful,
    const TArray<FUniqueOfferId> &OfferIds,
    const FString &Error)
{
    if (!bWasSuccessful)
    {
        this->TestBase->TestTrue("QueryOffersById call was successful", bWasSuccessful);
        this->bIsDone = true;
        return;
    }

    TArray<FOnlineStoreOfferRef> Offers;
    this->StoreV2->GetOffers(Offers);

    bool bHasAllExpectedOffers = true;
    for (const auto &ExpectedOffer : this->ExpectedOfferIds)
    {
        bool bHasOffer = false;
        for (const auto &Offer : Offers)
        {
            if (Offer->OfferId == TEXT("test_iap"))
            {
                bHasOffer = true;
                break;
            }
        }
        if (!bHasOffer)
        {
            bHasAllExpectedOffers = false;
            break;
        }
    }

    this->TestBase->TestTrue("All expected offers were found", bHasAllExpectedOffers);

    UE_LOG(LogRedpointGoogle, Verbose, TEXT("OnOffersQueried finished successfully."));
    this->bIsDone = true;
    return;
}

bool FRedpointGoogleQueryOfferById::Update()
{
    if (!this->bHasInit)
    {
        UE_LOG(LogRedpointGoogle, Verbose, TEXT("Starting query offer latent command"));

        IOnlineSubsystem *OSS = IOnlineSubsystem::Get(this->SubsystemName);
        if (!this->TestBase->TestTrue(TEXT("OSS is not null"), OSS != nullptr))
        {
            return true;
        }
        this->Identity = OSS->GetIdentityInterface();
        if (!this->TestBase->TestTrue(TEXT("Identity is not null"), this->Identity != nullptr))
        {
            return true;
        }
        this->StoreV2 = OSS->GetStoreV2Interface();
        if (!this->TestBase->TestTrue(TEXT("StoreV2 is not null"), this->StoreV2 != nullptr))
        {
            return true;
        }

        this->StoreV2->QueryOffersById(
            *this->Identity->GetUniquePlayerId(0),
            this->ExpectedOfferIds,
            FOnQueryOnlineStoreOffersComplete::CreateSP(this, &FRedpointGoogleQueryOfferById::OnOffersQueried));
        this->bHasInit = true;
    }

    return this->bIsDone;
}

#endif // #if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)
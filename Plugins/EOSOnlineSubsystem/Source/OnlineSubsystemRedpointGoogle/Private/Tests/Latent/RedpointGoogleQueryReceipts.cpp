// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)

#include "Tests/Latent/RedpointGoogleQueryReceipts.h"

void FRedpointGoogleQueryReceipts::OnReceiptsQueried(const FOnlineError& Result)
{
    this->TestBase->TestTrue("QueryReceipts call was successful", Result.WasSuccessful());
    this->bIsDone = true;
    return;
}

bool FRedpointGoogleQueryReceipts::Update()
{
    if (!this->bHasInit)
    {
        UE_LOG(LogRedpointGoogle, Verbose, TEXT("Starting query receipt latent command"));

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
        this->Purchase = OSS->GetPurchaseInterface();
        if (!this->TestBase->TestTrue(TEXT("Purchase is not null"), this->Purchase != nullptr))
        {
            return true;
        }

        this->Purchase->QueryReceipts(
            *this->Identity->GetUniquePlayerId(0),
            true,
            FOnQueryReceiptsComplete::CreateSP(this, &FRedpointGoogleQueryReceipts::OnReceiptsQueried));
        this->bHasInit = true;
    }

    return this->bIsDone;
}

#endif // #if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)
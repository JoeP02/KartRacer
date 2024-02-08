// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_APPLE_ENABLED

#include "CoreMinimal.h"
#include "RedpointEOSCore/RuntimePlatformIntegration.h"

class FEOSRuntimePlatformIntegrationApple : public Redpoint::EOS::Core::IRuntimePlatformIntegration
{
public:
    virtual TSharedPtr<const class FUniqueNetId> GetUserId(
        TSoftObjectPtr<class UWorld> InWorld,
        EOS_Connect_ExternalAccountInfo *InExternalInfo) override;
    virtual bool CanProvideExternalAccountId(const FUniqueNetId &InUserId) override;
    virtual Redpoint::EOS::Core::FExternalAccountIdInfo GetExternalAccountId(const FUniqueNetId &InUserId) override;
};

#endif
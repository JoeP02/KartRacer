// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

#if EOS_ITCH_IO_ENABLED

#include "RedpointEOSCore/RuntimePlatformIntegration.h"

class FEOSRuntimePlatformIntegrationItchIo : public Redpoint::EOS::Core::IRuntimePlatformIntegration
{
public:
    virtual TSharedPtr<const class FUniqueNetId> GetUserId(
        TSoftObjectPtr<class UWorld> InWorld,
        EOS_Connect_ExternalAccountInfo *InExternalInfo) override;
    virtual bool CanProvideExternalAccountId(const FUniqueNetId &InUserId) override;
    virtual Redpoint::EOS::Core::FExternalAccountIdInfo GetExternalAccountId(const FUniqueNetId &InUserId) override;
};

#endif
// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "IEOSCheck.h"
#include "RedpointEOSConfig/Config.h"

class FEOSDedicatedServerMissingSettingsCheck : public IEOSCheck
{
private:
    TSharedRef<Redpoint::EOS::Config::IConfig> Config;

public:
    FEOSDedicatedServerMissingSettingsCheck();
    UE_NONCOPYABLE(FEOSDedicatedServerMissingSettingsCheck);
    virtual ~FEOSDedicatedServerMissingSettingsCheck(){};

    virtual bool ShouldTick() const override
    {
        return true;
    }

    virtual const TArray<FEOSCheckEntry> Tick(float DeltaSeconds) const override;

    virtual void HandleAction(const FString &CheckId, const FString &ActionId) const override;
};
// Copyright June Rhodes. All Rights Reserved.

#pragma once

#include "IEOSCheck.h"
#include "RedpointEOSConfig/Config.h"

class FEOSIncompatibleGooglePluginsAreNotEnabledCheck : public IEOSCheck
{
private:
    TSharedRef<Redpoint::EOS::Config::IConfig> Config;

public:
    FEOSIncompatibleGooglePluginsAreNotEnabledCheck();
    UE_NONCOPYABLE(FEOSIncompatibleGooglePluginsAreNotEnabledCheck);
    virtual ~FEOSIncompatibleGooglePluginsAreNotEnabledCheck(){};

    virtual bool ShouldTick() const override
    {
        return true;
    }

    virtual const TArray<FEOSCheckEntry> Tick(float DeltaSeconds) const override;

    virtual void HandleAction(const FString &CheckId, const FString &ActionId) const override;
};
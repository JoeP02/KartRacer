// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "EOSRuntimePlatformDesktopBase.h"

#if PLATFORM_MAC

class FEOSRuntimePlatformMac : public FEOSRuntimePlatformDesktopBase
{
public:
    FEOSRuntimePlatformMac() = default;
    virtual ~FEOSRuntimePlatformMac() = default;

    virtual bool ShouldPollLifecycleApplicationStatus() const override;
    virtual bool ShouldPollLifecycleNetworkStatus() const override;
    virtual bool PollLifecycleApplicationStatus(EOS_EApplicationStatus &OutApplicationStatus) const override;
    virtual bool PollLifecycleNetworkStatus(EOS_ENetworkStatus &OutNetworkStatus) const override;
};

#endif
// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "EOSRuntimePlatformDesktopBase.h"

#if PLATFORM_WINDOWS

class FEOSRuntimePlatformWindows : public FEOSRuntimePlatformDesktopBase
{
public:
    FEOSRuntimePlatformWindows() = default;
    virtual ~FEOSRuntimePlatformWindows() = default;

#if !defined(UE_SERVER) || !UE_SERVER
    virtual bool ShouldPollLifecycleApplicationStatus() const override;
    virtual bool ShouldPollLifecycleNetworkStatus() const override;
    virtual bool PollLifecycleApplicationStatus(EOS_EApplicationStatus &OutApplicationStatus) const override;
    virtual bool PollLifecycleNetworkStatus(EOS_ENetworkStatus &OutNetworkStatus) const override;
#else
    virtual void SetLifecycleForNewPlatformInstance(Redpoint::EOS::API::FPlatformHandle InPlatform) override;
#endif
};

#endif
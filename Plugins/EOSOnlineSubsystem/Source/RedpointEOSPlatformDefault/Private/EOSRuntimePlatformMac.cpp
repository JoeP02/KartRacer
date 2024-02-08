// Copyright June Rhodes 2024. All Rights Reserved.

#include "EOSRuntimePlatformMac.h"

#if PLATFORM_MAC

#include "HAL/PlatformApplicationMisc.h"

bool FEOSRuntimePlatformMac::ShouldPollLifecycleApplicationStatus() const
{
    return true;
}

bool FEOSRuntimePlatformMac::ShouldPollLifecycleNetworkStatus() const
{
    return false;
}

bool FEOSRuntimePlatformMac::PollLifecycleApplicationStatus(EOS_EApplicationStatus &OutApplicationStatus) const
{
    // Desktop platforms always run applications in the foreground, regardless of whether the
    // application is the active focus.
    OutApplicationStatus = EOS_EApplicationStatus::EOS_AS_Foreground;
    return true;
}

bool FEOSRuntimePlatformMac::PollLifecycleNetworkStatus(EOS_ENetworkStatus &OutNetworkStatus) const
{
    return false;
}

#endif
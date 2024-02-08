// Copyright June Rhodes 2024. All Rights Reserved.

#include "EOSRuntimePlatformLinux.h"

#if PLATFORM_LINUX

#include "HAL/PlatformApplicationMisc.h"

#if !defined(UE_SERVER) || !UE_SERVER

bool FEOSRuntimePlatformLinux::ShouldPollLifecycleApplicationStatus() const
{
    return true;
}

bool FEOSRuntimePlatformLinux::ShouldPollLifecycleNetworkStatus() const
{
    return false;
}

bool FEOSRuntimePlatformLinux::PollLifecycleApplicationStatus(EOS_EApplicationStatus &OutApplicationStatus) const
{
    // Desktop platforms always run applications in the foreground, regardless of whether the
    // application is the active focus.
    OutApplicationStatus = EOS_EApplicationStatus::EOS_AS_Foreground;
    return true;
}

bool FEOSRuntimePlatformLinux::PollLifecycleNetworkStatus(EOS_ENetworkStatus &OutNetworkStatus) const
{
    return false;
}

#else

void FEOSRuntimePlatformLinux::SetLifecycleForNewPlatformInstance(Redpoint::EOS::API::FPlatformHandle InPlatform)
{
    EOS_Platform_SetApplicationStatus(InPlatform->Handle(), EOS_EApplicationStatus::EOS_AS_Foreground);
    EOS_Platform_SetNetworkStatus(InPlatform->Handle(), EOS_ENetworkStatus::EOS_NS_Online);
}

#endif

#endif
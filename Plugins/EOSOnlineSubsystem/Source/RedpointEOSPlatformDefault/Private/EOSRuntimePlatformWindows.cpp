// Copyright June Rhodes 2024. All Rights Reserved.

#include "EOSRuntimePlatformWindows.h"

#if PLATFORM_WINDOWS

#include "HAL/PlatformApplicationMisc.h"
#include "Misc/App.h"

#if !defined(UE_SERVER) || !UE_SERVER

bool FEOSRuntimePlatformWindows::ShouldPollLifecycleApplicationStatus() const
{
    return true;
}

bool FEOSRuntimePlatformWindows::ShouldPollLifecycleNetworkStatus() const
{
    return false;
}

bool FEOSRuntimePlatformWindows::PollLifecycleApplicationStatus(EOS_EApplicationStatus &OutApplicationStatus) const
{
    // Desktop platforms always run applications in the foreground, regardless of whether the
    // application is the active focus.
    OutApplicationStatus = EOS_EApplicationStatus::EOS_AS_Foreground;
    return true;
}

bool FEOSRuntimePlatformWindows::PollLifecycleNetworkStatus(EOS_ENetworkStatus &OutNetworkStatus) const
{
    return false;
}

#else

void FEOSRuntimePlatformWindows::SetLifecycleForNewPlatformInstance(Redpoint::EOS::API::FPlatformHandle InPlatform)
{
    EOS_Platform_SetApplicationStatus(InPlatform->Handle(), EOS_EApplicationStatus::EOS_AS_Foreground);
    EOS_Platform_SetNetworkStatus(InPlatform->Handle(), EOS_ENetworkStatus::EOS_NS_Online);
}

#endif

#endif
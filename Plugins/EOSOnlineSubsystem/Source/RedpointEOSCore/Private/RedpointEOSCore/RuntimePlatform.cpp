// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSCore/RuntimePlatform.h"

namespace Redpoint::EOS::Core
{

EOS_Platform_RTCOptions *IRuntimePlatform::GetRTCOptions()
{
    return nullptr;
}

FString IRuntimePlatform::GetAntiCheatPlatformName() const
{
    return TEXT("Unknown");
};

bool IRuntimePlatform::UseCrossPlatformFriendStorage() const
{
    return false;
};

#if REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT

void IRuntimePlatform::RegisterLifecycleHandlers(const TWeakPtr<Core::ILifecycleManager> &InLifecycleManager)
{
}

void IRuntimePlatform::SetLifecycleForNewPlatformInstance(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    API::FPlatformHandle InPlatform)
{
}

bool IRuntimePlatform::ShouldPollLifecycleApplicationStatus() const
{
    return false;
}

bool IRuntimePlatform::ShouldPollLifecycleNetworkStatus() const
{
    return false;
}

bool IRuntimePlatform::PollLifecycleApplicationStatus(EOS_EApplicationStatus &OutApplicationStatus) const
{
    OutApplicationStatus = EOS_EApplicationStatus::EOS_AS_Foreground;
    return true;
};

bool IRuntimePlatform::PollLifecycleNetworkStatus(EOS_ENetworkStatus &OutNetworkStatus) const
{
    OutNetworkStatus = EOS_ENetworkStatus::EOS_NS_Online;
    return true;
};

#endif

} // namespace Redpoint::EOS::Core
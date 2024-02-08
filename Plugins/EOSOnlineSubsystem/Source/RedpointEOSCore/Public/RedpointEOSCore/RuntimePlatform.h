// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "RedpointEOSAPI/Platform.h"
#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSCore/LifecycleManager.h"
#include "RedpointEOSCore/RuntimePlatformIntegration.h"

namespace Redpoint::EOS::Core
{

class REDPOINTEOSCORE_API IRuntimePlatform
{
public:
    /**
     * Load the EOS SDK runtime library.
     */
    virtual void Load() = 0;

    /**
     * Unload the EOS SDK runtime library.
     */
    virtual void Unload() = 0;

    /**
     * Return true if the EOS SDK runtime library could be loaded, and EOS can be used.
     */
    virtual bool IsValid() = 0;

    /**
     * Returns the system initialization options that are passed to EOS_InitializeOptions.
     */
    virtual void *GetSystemInitializeOptions() = 0;

    /**
     * Returns the RTC options that are passed to EOS_Platform_Options.
     */
    virtual EOS_Platform_RTCOptions *GetRTCOptions();

    /**
     * Returns the path to cache directory that is passed to EOS_Platform_Options.
     */
    virtual FString GetCacheDirectory() = 0;

    /**
     * DEPRECATED.
     */
    virtual void ClearStoredEASRefreshToken(int32 LocalUserNum) = 0;

    /**
     * Returns the path to the Epic Games account credentials used for automated testing.
     */
#if !UE_BUILD_SHIPPING
    virtual FString GetPathToEASAutomatedTestingCredentials() = 0;
#endif

    /**
     * Returns all platform integrations available on this platform.
     */
    virtual const TArray<TSharedPtr<IRuntimePlatformIntegration>> &GetIntegrations() const = 0;

    /**
     * Returns the name of the platform as a string (as per the EOS_EAntiCheatCommonClientPlatform enumeration). This
     * value is only used on trusted platforms like consoles.
     */
    virtual FString GetAntiCheatPlatformName() const;

    /**
     * Returns whether this platform is allowed to cache friends in
     * Player Data Storage and read friends from Player Data Storage.
     *
     * If this is false, friends are not synced to Player Data Storage,
     * and the synthetic friends interface will not return them as part
     * of ReadFriendsList.
     *
     * Note that sending friend invites for pure EOS friends is still
     * permitted; this just controls whether or not friends from other
     * platform's social graphs will be visible.
     */
    virtual bool UseCrossPlatformFriendStorage() const;

#if REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT
    /**
     * Called during startup to register code that will handle calling EOS_Platform_SetApplicationStatus and
     * EOS_Platform_SetNetworkStatus in response to operating system events. If you need to poll, this implementation
     * should be empty and you should implement ShouldPollLifecycleStatus and PollLifecycleStatus instead.
     */
    virtual void RegisterLifecycleHandlers(const TWeakPtr<Core::ILifecycleManager> &InLifecycleManager);

    /**
     * Called after a new platform instance is successfully created, and should be used to set the initial application
     * and network lifecycle of the instance.
     */
    virtual void SetLifecycleForNewPlatformInstance(API::FPlatformHandle InPlatform);

    /**
     * Called during startup to see if this platform should poll every tick for the application status. The
     * implementation of PollLifecycleApplicationStatus must be very quick as it will be called every frame.
     */
    virtual bool ShouldPollLifecycleApplicationStatus() const;

    /**
     * Called during startup to see if this platform should poll every tick for the application status. The
     * implementation of PollLifecycleNetworkStatus must be very quick as it will be called every frame.
     */
    virtual bool ShouldPollLifecycleNetworkStatus() const;

    /**
     * Polls the current application status and returns it. Only called if you override
     * ShouldPollLifecycleApplicationStatus and make it return true. Returns true if the
     * returned application status should be set as the current application status.
     */
    virtual bool PollLifecycleApplicationStatus(EOS_EApplicationStatus &OutApplicationStatus) const;

    /**
     * Polls the current network status and returns it. Only called if you override
     * ShouldPollLifecycleApplicationStatus and make it return true. Returns true if the
     * returned network status should be set as the current network status.
     */
    virtual bool PollLifecycleNetworkStatus(EOS_ENetworkStatus &OutNetworkStatus) const;
#endif
};

} // namespace Redpoint::EOS::Core
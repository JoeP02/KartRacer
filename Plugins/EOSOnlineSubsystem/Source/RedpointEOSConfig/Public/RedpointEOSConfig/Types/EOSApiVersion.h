// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "EOSApiVersion.generated.h"

/**
 * When new versions of the plugin are released, sometimes the default behaviour changes. When you first use the plugin,
 * it sets the current latest API version in the configuration so that when you upgrade, the behaviour does not change
 * for you until you decide to upgrade.
 */
UENUM()
enum class EEOSApiVersion : uint8
{
    // NOTE: When a new version is added here, it *MUST* be added to the top of
    // the enum so it becomes value 0.

    /**
     * Behaviour as of 2023-10-27. As of this release, IsPlayerMuted in voice chat only reports the local mute status
	 * of remote players instead of the remote mute status.
     */
    v2023_10_27 UMETA(DisplayName = "2023-10-27"),

    /**
     * Behaviour as of 2022-10-28. As of this release, WriteAchievements will unlock achievements directly instead of
     * forwarding requests to IOnlineStats.
     */
    v2022_10_28 UMETA(DisplayName = "2022-10-28"),

    /**
     * Behaviour as of 2022-05-20. As of this release, the default network authentication mode was set to ID Token. On
     * 2022-11-30 the legacy User Credentials mode was entirely removed and all games use ID Token unless network
     * authentication is turned Off.
     */
    v2022_05_20 UMETA(DisplayName = "2022-05-20"),

    /**
     * Behaviour as of 2022-02-11. As of this release, "minslotsavailable" in session searches is set to >= 1 by
     * default, as this was the expected behaviour for a lot of users.
     */
    v2022_02_11 UMETA(DisplayName = "2022-02-11"),
};
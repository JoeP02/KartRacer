// Copyright June Rhodes. All Rights Reserved.

#include "EOSIncompatibleGooglePluginsAreNotEnabledCheck.h"

#include "Interfaces/IPluginManager.h"
#include "RedpointEOSConfig/IniConfig.h"

FEOSIncompatibleGooglePluginsAreNotEnabledCheck::FEOSIncompatibleGooglePluginsAreNotEnabledCheck()
    : Config(MakeShared<Redpoint::EOS::Config::FIniConfig>())
{
}

const TArray<FEOSCheckEntry> FEOSIncompatibleGooglePluginsAreNotEnabledCheck::Tick(float DeltaSeconds) const
{
    if (IPluginManager::Get().FindPlugin("OnlineSubsystemGoogle")->IsEnabled() ||
        IPluginManager::Get().FindPlugin("OnlineSubsystemGooglePlay")->IsEnabled())
    {
        return TArray<FEOSCheckEntry>{FEOSCheckEntry(
            "FEOSIncompatibleGooglePluginsAreNotEnabledCheck::Enabled",
            "The \"OnlineSubsystemGoogle\" or \"OnlineSubsystemGooglePlay\" plugins are currently enabled in your "
            "project. These plugins are incompatible with EOS on Android and must be turned off.",
            TArray<FEOSCheckAction>{FEOSCheckAction(
                "FEOSIncompatibleGooglePluginsAreNotEnabledCheck::OpenDocumentation",
                "Read documentation")})};
    }

    return IEOSCheck::EmptyEntries;
}

void FEOSIncompatibleGooglePluginsAreNotEnabledCheck::HandleAction(const FString &CheckId, const FString &ActionId)
    const
{
    if (CheckId == "FEOSIncompatibleGooglePluginsAreNotEnabledCheck::Enabled")
    {
        if (ActionId == "FEOSIncompatibleGooglePluginsAreNotEnabledCheck::OpenDocumentation")
        {
            FPlatformProcess::LaunchURL(
                TEXT("https://docs.redpoint.games/eos-online-subsystem/docs/auth_platform_google"),
                nullptr,
                nullptr);
        }
    }
}
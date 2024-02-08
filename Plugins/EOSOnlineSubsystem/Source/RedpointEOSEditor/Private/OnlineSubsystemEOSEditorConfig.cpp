// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemEOSEditorConfig.h"

#include "EOSConfiguration.h"
#include "EOSConfigurationReader.h"
#include "EOSConfigurationWriter.h"
#include "EOSConfigurerRegistry.h"
#include "ISettingsContainer.h"
#include "ISettingsModule.h"
#include "Misc/Base64.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"

#include "OnlineSubsystemRedpointEOS/Shared/EOSDefines.h"
#include "PlatformHelpers.h"
#include "RedpointEOSEditorModule.h"
#include "SourceControlHelpers.h"
#include "UObject/UObjectGlobals.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "OnlineSubsystemEOSEditorModule"

#define EOS_SECTION TEXT("EpicOnlineServices")

UOnlineSubsystemEOSEditorConfig::UOnlineSubsystemEOSEditorConfig()
{
    FEOSConfigurerContext Context;
    FEOSConfigurerRegistry::InitDefaults(Context, this);

    FEOSConfigurationReader Reader;
    FEOSConfigurerRegistry::Load(Context, Reader, this);
}

void UOnlineSubsystemEOSEditorConfig::LoadEOSConfig()
{
    FEOSConfigurerContext Context;
    FEOSConfigurationReader Reader;
    FEOSConfigurerRegistry::Load(Context, Reader, this);

    if (!IsRunningCommandlet())
    {
        if (FEOSConfigurerRegistry::Validate(Context, this))
        {
            if (!USourceControlHelpers::IsEnabled() && !USourceControlHelpers::IsAvailable() &&
                USourceControlHelpers::CurrentProvider().Equals(TEXT("Perforce"), ESearchCase::IgnoreCase))
            {
                // @note: Attempt to workaround a Perforce issue where the engine is aware that it
                // is configured for Perforce, but has not yet connected to the Perforce depot. In this
                // case, we won't be able to check out configuration files to issue fixups. Delay
                // the fixups for a few seconds to allow the engine to connect.
                FTSTicker::GetCoreTicker().AddTicker(
                    FTickerDelegate::CreateWeakLambda(
                        this,
                        [this](float DeltaSeconds) {
                            this->FixupEOSConfig();
                            return false;
                        }),
                    5.0f);
            }
            else
            {
                this->FixupEOSConfig();
            }
        }
    }
}

void UOnlineSubsystemEOSEditorConfig::FixupEOSConfig()
{
    FEOSConfigurerContext Context;
    FEOSConfigurationWriter Writer;
    FEOSConfigurerRegistry::Save(Context, Writer, this);

    switch (Writer.FlushChanges())
    {
    case FEOSConfigurationWriter::EFlushChangesResult::Success:
        break;
    case FEOSConfigurationWriter::EFlushChangesResult::FailedToCheckOutFiles:
        UE_LOG(
            LogRedpointEOSEditor,
            Warning,
            TEXT("Failed to re-validate and save configuration changes when the configuration was loaded. The "
                 "current state of the configuration in Project Settings may not reflect the configuration on "
                 "disk. To resolve this issue, manually check out the 'Config' and 'Platforms' folders in your "
                 "source control provider."));
        break;
    }
}

void UOnlineSubsystemEOSEditorConfig::SaveEOSConfig()
{
    FEOSConfigurerContext Context;
    FEOSConfigurerRegistry::Validate(Context, this);

    FEOSConfigurationWriter Writer;
    FEOSConfigurerRegistry::Save(Context, Writer, this);

    switch (Writer.FlushChanges())
    {
    case FEOSConfigurationWriter::EFlushChangesResult::Success:
        break;
    case FEOSConfigurationWriter::EFlushChangesResult::FailedToCheckOutFiles:
        UE_LOG(
            LogRedpointEOSEditor,
            Warning,
            TEXT("Failed to save the configuration changes to disk. The current state of the configuration in Project "
                 "Settings may not reflect the configuration on disk. To resolve this issue, manually check out the "
                 "'Config' and 'Platforms' folders in your source control provider."));
        break;
    }
}

const FName UOnlineSubsystemEOSEditorConfig::GetEditorAuthenticationGraphPropertyName()
{
    static const FName PropertyName =
        GET_MEMBER_NAME_CHECKED(UOnlineSubsystemEOSEditorConfig, EditorAuthenticationGraph);
    return PropertyName;
}

const FName UOnlineSubsystemEOSEditorConfig::GetAuthenticationGraphPropertyName()
{
    static const FName PropertyName = GET_MEMBER_NAME_CHECKED(UOnlineSubsystemEOSEditorConfig, AuthenticationGraph);
    return PropertyName;
}

const FName UOnlineSubsystemEOSEditorConfig::GetCrossPlatformAccountProviderPropertyName()
{
    static const FName PropertyName =
        GET_MEMBER_NAME_CHECKED(UOnlineSubsystemEOSEditorConfig, CrossPlatformAccountProvider);
    return PropertyName;
}

bool FOnlineSubsystemEOSEditorConfig::HandleSettingsSaved()
{
    this->Config->SaveEOSConfig();

    // Prevent the section that gets automatically added by the config serialization system from being added now.
    return false;
}

void FOnlineSubsystemEOSEditorConfig::RegisterSettings()
{
    if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        // Make the instanced version of the config (required so OverridePerObjectConfigSection will be called).
#if defined(EOS_IS_FREE_EDITION)
        this->Config = NewObject<UOnlineSubsystemEOSEditorConfigFreeEdition>();
#else
        this->Config = NewObject<UOnlineSubsystemEOSEditorConfig>();
#endif
        this->Config->AddToRoot();

        this->Config->LoadEOSConfig();

        // Register the settings
        this->SettingsSection = SettingsModule->RegisterSettings(
            "Project",
            "Game",
            "Epic Online Services",
            LOCTEXT("EOSSettingsName", "Epic Online Services"),
            LOCTEXT("EOSSettingsDescription", "Configure Epic Online Services in your game."),
            this->Config);

        if (SettingsSection.IsValid())
        {
            SettingsSection->OnModified().BindRaw(this, &FOnlineSubsystemEOSEditorConfig::HandleSettingsSaved);
        }
    }
}

void FOnlineSubsystemEOSEditorConfig::UnregisterSettings()
{
    if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Game", "Epic Online Services");
    }
}

#undef LOCTEXT_NAMESPACE
// Copyright June Rhodes 2024. All Rights Reserved.

#include "IOSEOSConfigurer.h"

#include "../PlatformHelpers.h"

void FIOSEOSConfigurer::InitDefaults(FEOSConfigurerContext &Context, UOnlineSubsystemEOSEditorConfig *Instance)
{
}

void FIOSEOSConfigurer::Load(
    FEOSConfigurerContext &Context,
    FEOSConfigurationReader &Reader,
    UOnlineSubsystemEOSEditorConfig *Instance)
{
    // This value isn't stored in the instance.
    this->ShipForBitcode = true;
    Reader.GetBool(
        TEXT("bShipForBitcode"),
        this->ShipForBitcode,
        TEXT("/Script/IOSRuntimeSettings.IOSRuntimeSettings"),
        EEOSConfigurationFileType::Engine,
        FName(TEXT("IOS")));
}

bool FIOSEOSConfigurer::Validate(FEOSConfigurerContext &Context, UOnlineSubsystemEOSEditorConfig *Instance)
{
    if (Context.bAutomaticallyConfigureEngineLevelSettings)
    {
        // We must fix up IOS settings.
        return this->ShipForBitcode;
    }

    return false;
}

void FIOSEOSConfigurer::Save(
    FEOSConfigurerContext &Context,
    FEOSConfigurationWriter &Writer,
    UOnlineSubsystemEOSEditorConfig *Instance)
{
    if (Context.bAutomaticallyConfigureEngineLevelSettings)
    {
        // IOS required settings.
        Writer.SetBool(
            TEXT("bShipForBitcode"),
            false,
            TEXT("/Script/IOSRuntimeSettings.IOSRuntimeSettings"),
            EEOSConfigurationFileType::Engine,
            FName(TEXT("IOS")));
        // Set in DefaultEngine.ini as well since it's a build-time thing.
        Writer.SetBool(
            TEXT("bShipForBitcode"),
            false,
            TEXT("/Script/IOSRuntimeSettings.IOSRuntimeSettings"),
            EEOSConfigurationFileType::Engine);
        this->ShipForBitcode = false;
    }
}
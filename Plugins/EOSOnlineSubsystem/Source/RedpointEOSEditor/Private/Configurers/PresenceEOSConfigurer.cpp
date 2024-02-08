// Copyright June Rhodes 2024. All Rights Reserved.

#include "PresenceEOSConfigurer.h"

void FPresenceEOSConfigurer::InitDefaults(FEOSConfigurerContext &Context, UOnlineSubsystemEOSEditorConfig *Instance)
{
    Instance->PresenceAdvertises = EPresenceAdvertisementType::Party;
}

void FPresenceEOSConfigurer::Load(
    FEOSConfigurerContext &Context,
    FEOSConfigurationReader &Reader,
    UOnlineSubsystemEOSEditorConfig *Instance)
{
    Reader.GetEnum<EPresenceAdvertisementType>(
        TEXT("PresenceAdvertises"),
        TEXT("EPresenceAdvertisementType"),
        Instance->PresenceAdvertises);
}

void FPresenceEOSConfigurer::Save(
    FEOSConfigurerContext &Context,
    FEOSConfigurationWriter &Writer,
    UOnlineSubsystemEOSEditorConfig *Instance)
{
    Writer.SetEnum<EPresenceAdvertisementType>(
        TEXT("PresenceAdvertises"),
        TEXT("EPresenceAdvertisementType"),
        Instance->PresenceAdvertises);
}
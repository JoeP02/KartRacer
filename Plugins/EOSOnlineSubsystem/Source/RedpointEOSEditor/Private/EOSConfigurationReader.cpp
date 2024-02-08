// Copyright June Rhodes 2024. All Rights Reserved.

#include "EOSConfigurationReader.h"

#include "OnlineSubsystemRedpointEOS/Public/OnlineSubsystemRedpointEOSModule.h"

#include "RedpointEOSConfig/EngineConfigHelpers.h"
#include "UObject/Class.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectGlobals.h"

FEOSConfigurationReader::FEOSConfigurationReader()
{
}

bool FEOSConfigurationReader::GetBool(
    const FString &Key,
    bool &OutValue,
    const FString &Section,
    EEOSConfigurationFileType File,
    FName Platform)
{
    FConfigFile *F =
        Redpoint::EOS::Config::FEngineConfigHelpers::FindByName(EOSConfiguration::GetFilePath(File, Platform));
    if (!F)
    {
        return false;
    }
    return F->GetBool(*Section, *Key, OutValue);
}

bool FEOSConfigurationReader::GetString(
    const FString &Key,
    FString &OutValue,
    const FString &Section,
    EEOSConfigurationFileType File,
    FName Platform)
{
    FConfigFile *F =
        Redpoint::EOS::Config::FEngineConfigHelpers::FindByName(EOSConfiguration::GetFilePath(File, Platform));
    if (!F)
    {
        return false;
    }
    return F->GetString(*Section, *Key, OutValue);
}

bool FEOSConfigurationReader::GetArray(
    const FString &Key,
    TArray<FString> &OutValue,
    const FString &Section,
    EEOSConfigurationFileType File,
    FName Platform)
{
    FConfigFile *F =
        Redpoint::EOS::Config::FEngineConfigHelpers::FindByName(EOSConfiguration::GetFilePath(File, Platform));
    if (!F)
    {
        return false;
    }
    // Try loading with the + prefix, which is now the correct way to read things
    // from a raw (not virtualized) config file.
    if (F->GetArray(*Section, *FString::Printf(TEXT("+%s"), *Key), OutValue) == 0)
    {
        // We didn't get anything with the proper way. Try legacy configuration values
        // so that we import them correctly.
        return F->GetArray(*Section, *Key, OutValue) > 0;
    }
    else
    {
        return true;
    }
}

bool FEOSConfigurationReader::GetEnumInternal(
    const FString &Key,
    const FString &EnumClass,
    uint8 &OutValue,
    const FString &Section,
    EEOSConfigurationFileType File,
    FName Platform)
{
    FConfigFile *F =
        Redpoint::EOS::Config::FEngineConfigHelpers::FindByName(EOSConfiguration::GetFilePath(File, Platform));
    if (!F)
    {
        return false;
    }
    FString EnumValue;
    if (!F->GetString(*Section, *Key, EnumValue))
    {
        return false;
    }
#if defined(UE_5_1_OR_LATER)
    const UEnum *Enum =
        FindObject<UEnum>(FTopLevelAssetPath(ONLINESUBSYSTEMREDPOINTEOS_PACKAGE_PATH, *EnumClass), true);
#else
    const UEnum *Enum = FindObject<UEnum>((UObject *)ANY_PACKAGE, *EnumClass, true);
    OutValue = (uint8)Enum->GetValueByName(FName(*EnumValue), EGetByNameFlags::ErrorIfNotFound);
#endif
    return true;
}
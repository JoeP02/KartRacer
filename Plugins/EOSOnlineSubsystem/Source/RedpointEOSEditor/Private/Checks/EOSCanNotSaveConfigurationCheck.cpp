// Copyright June Rhodes 2024. All Rights Reserved.

#include "EOSCanNotSaveConfigurationCheck.h"

#include "Containers/UnrealString.h"

const TArray<FEOSCheckEntry> FEOSCanNotSaveConfigurationCheck::ProcessCustomSignal(
    const FString &Context,
    const FString &SignalId) const
{
    if (Context == TEXT("Configuration") && SignalId == TEXT("SourceControlPreventingConfigSave"))
    {
        return TArray<FEOSCheckEntry>{FEOSCheckEntry(
            "FEOSCanNotSaveConfigurationCheck::UnableToSave",
            "EOS Online Subsystem either tried to save your changes to configuration files, or tried to update "
            "configuration files to ensure EOS works correctly. However, your source control provider prevented the "
            "plugin from checking out the files. This can happen if someone else in your team has the configuration "
            "files currently locked. Please check out the 'Config' and 'Platforms' folders manually in source control "
            "and try again.",
            TArray<FEOSCheckAction>{})};
    }
    return IEOSCheck::EmptyEntries;
}

void FEOSCanNotSaveConfigurationCheck::HandleAction(const FString &CheckId, const FString &ActionId) const
{
}
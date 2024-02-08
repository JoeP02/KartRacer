// Copyright June Rhodes 2024. All Rights Reserved.

#include "EOSStaleLibraryPresentCheck.h"

const TArray<FEOSCheckEntry> FEOSStaleLibraryPresentCheck::ProcessLogMessage(
    EOS_ELogLevel InLogLevel,
    const FString &Category,
    const FString &Message) const
{
    if (Message.Contains("incompatible") && Message.Contains("version specified"))
    {
        return TArray<FEOSCheckEntry>{FEOSCheckEntry(
            "FEOSStaleLibraryPresentCheck::Detected",
            "There is a stale EOS SDK DLL somewhere in your library search path, which is causing the editor to "
            "load a version of the EOS SDK older than what it was built with. Please close the editor, search your "
            "project folder for all copies of EOSSDK-Win64-Shipping.dll and delete them, then start the editor again.",
            TArray<FEOSCheckAction>{})};
    }
    return IEOSCheck::EmptyEntries;
}

void FEOSStaleLibraryPresentCheck::HandleAction(const FString &CheckId, const FString &ActionId) const
{
    if (CheckId == "FEOSStaleLibraryPresentCheck::Detected")
    {
        // No actions we can automatically take here.
    }
}
// Copyright June Rhodes 2024. All Rights Reserved.

#include "LaunchDevAuthToolCommandlet.h"

#include "DevAuthToolLauncher.h"
#include "RedpointEOSEditorModule.h"

ULaunchDevAuthToolCommandlet::ULaunchDevAuthToolCommandlet(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
    IsClient = false;
    IsServer = false;
    IsEditor = true;

    LogToConsole = true;
    ShowErrorCount = true;
    ShowProgress = true;
}

int32 ULaunchDevAuthToolCommandlet::Main(const FString &Params)
{
    UE_LOG(LogRedpointEOSEditor, Verbose, TEXT("EOS DevAuthTool Commandlet Started"));
    return FDevAuthToolLauncher::Launch(false) ? 0 : 1;
}
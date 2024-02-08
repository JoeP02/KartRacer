// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "Containers/UnrealString.h"
#include "CoreMinimal.h"


#if PLATFORM_WINDOWS || PLATFORM_MAC

class FDevAuthToolLauncher
{
public:
    static bool bNeedsToCheckIfDevToolRunning;
    static bool bIsDevToolRunning;
    static FTSTicker::FDelegateHandle ResetCheckHandle;

    static FString GetPathToToolsFolder();
    static bool IsDevAuthToolRunning();

    static bool Launch(bool bInteractive);
};

#endif
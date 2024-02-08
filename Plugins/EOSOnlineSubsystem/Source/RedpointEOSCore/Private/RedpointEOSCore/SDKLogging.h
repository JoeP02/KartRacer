// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSAPI/SDK.h"

namespace Redpoint::EOS::Core
{

class FSDKLogging
{
public:
#if WITH_EDITOR
    typedef TDelegate<void(int32_t, const FString &, const FString &)> FOnLogForwardedForEditor;
    static FOnLogForwardedForEditor EditorLogHandler;
#endif

    static void Log(const EOS_LogMessage *Message);
};

}
// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "RedpointEOSConfig/Config.h"

namespace Redpoint::EOS::Config
{

class REDPOINTEOSCONFIG_API FEngineConfigHelpers
{
public:
    static FConfigFile* FindByName(const FString& InFilename);
};

}
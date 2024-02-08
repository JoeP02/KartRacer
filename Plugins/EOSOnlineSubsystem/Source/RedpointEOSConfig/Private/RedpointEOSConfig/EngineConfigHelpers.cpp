// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSConfig/EngineConfigHelpers.h"

#include "Misc/ConfigCacheIni.h"

namespace Redpoint::EOS::Config
{

FConfigFile* FEngineConfigHelpers::FindByName(const FString& InFilename)
{
    return GConfig->Find(FConfigCacheIni::NormalizeConfigIniPath(InFilename));
}

}
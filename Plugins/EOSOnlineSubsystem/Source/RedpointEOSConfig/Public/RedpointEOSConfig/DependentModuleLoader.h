// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "RedpointEOSConfig/Config.h"

namespace Redpoint::EOS::Config
{

class REDPOINTEOSCONFIG_API FDependentModuleLoader
{
public:
    static void LoadConfigDependentModules(IConfig &InConfig);
    static void LoadPlatformDependentModules();
};

} // namespace Redpoint::EOS::Config
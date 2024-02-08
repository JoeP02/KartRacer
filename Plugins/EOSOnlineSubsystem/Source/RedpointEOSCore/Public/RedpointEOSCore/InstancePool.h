// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSAPI/Platform.h"
#include "RedpointEOSConfig/Config.h"

namespace Redpoint::EOS::Core
{

class REDPOINTEOSCORE_API IInstancePool
{
public:
    static IInstancePool &Pool();

    virtual API::FPlatformRefCountedHandle Create(FName InstanceName) = 0;
    virtual API::FPlatformRefCountedHandle CreateWithConfig(FName InstanceName, TSharedRef<Config::IConfig> Config) = 0;
};

} // namespace Redpoint::EOS::Core
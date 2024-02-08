// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSAPI/Platform.h"
#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSConfig/Config.h"

namespace Redpoint::EOS::Core
{

class FInstanceFactory
{
private:
    static bool IsTrueDedicated(const FName &InInstanceName);

public:
    static API::FPlatformHandle Create(const FName &InInstanceName, const TSharedRef<Config::IConfig> &InConfig);
};

} // namespace Redpoint::EOS::API
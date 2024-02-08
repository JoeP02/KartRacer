// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace Redpoint::EOS::API::RTCAudio
{

class REDPOINTEOSAPI_API FDeviceInformation
{
public:
    FString Id;
    FString DisplayName;
    bool bIsDefaultDevice;
    bool bIsInputDevice;
};

} // namespace Redpoint::EOS::API::RTCAudio
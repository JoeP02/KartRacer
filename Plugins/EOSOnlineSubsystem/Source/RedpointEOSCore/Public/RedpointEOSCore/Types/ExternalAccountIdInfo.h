// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "RedpointEOSAPI/SDK.h"

namespace Redpoint::EOS::Core
{

struct REDPOINTEOSCORE_API FExternalAccountIdInfo
{
public:
    EOS_EExternalAccountType AccountIdType;
    FString AccountId;
};

} // namespace Redpoint::EOS::Core
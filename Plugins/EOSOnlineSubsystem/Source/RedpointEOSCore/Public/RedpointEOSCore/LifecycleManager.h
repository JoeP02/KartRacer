// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSAPI/SDK.h"

#define REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT EOS_VERSION_AT_LEAST(1, 15, 0)

namespace Redpoint::EOS::Core
{

#if REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT

class REDPOINTEOSCORE_API ILifecycleManager
{
public:
    virtual void UpdateApplicationStatus(const EOS_EApplicationStatus &InNewStatus) = 0;
    virtual void UpdateNetworkStatus(const EOS_ENetworkStatus &InNewStatus) = 0;
};

#endif

} // namespace Redpoint::EOS::Core
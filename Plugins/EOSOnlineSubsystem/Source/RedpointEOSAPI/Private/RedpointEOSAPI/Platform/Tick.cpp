// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/Platform/Tick.h"

#include "RedpointEOSAPI/Error.h"
#include "RedpointEOSAPI/Logging.h"

namespace Redpoint::EOS::API::Platform
{

void FTick::Execute(const FPlatformHandle &InHandle)
{
    DECLARE_CYCLE_STAT(StatCallName(), STAT_Call, STATGROUP_RedpointEOS);
    SCOPE_CYCLE_COUNTER(STAT_Call);

    // @note: We do not emit VeryVerbose logs for the Tick operation because it is
    // called extremely frequently.

    NativeHandle Handle = InHandle->Handle();

    if (Handle == nullptr)
    {
        return;
    }

    NativeFunction(Handle);
}

} // namespace Redpoint::EOS::API::Platform
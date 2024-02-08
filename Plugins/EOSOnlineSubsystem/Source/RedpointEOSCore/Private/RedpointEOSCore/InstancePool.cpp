// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSCore/InstancePool.h"

#include "RedpointEOSCore/InstancePoolImpl.h"

namespace Redpoint::EOS::Core
{

TSharedPtr<IInstancePool, ESPMode::ThreadSafe> GRedpointEOSPlatformInstance;
static FCriticalSection GRedpointEOSPlatformInstancePoolLock;
IInstancePool &IInstancePool::Pool()
{
    // Optimistic check outside the lock.
    if (GRedpointEOSPlatformInstance.IsValid())
    {
        return *GRedpointEOSPlatformInstance.Get();
    }

    {
        // @note: Ensures we don't race on the initialisation of the platform pool.
        FScopeLock Lock(&GRedpointEOSPlatformInstancePoolLock);
        if (GRedpointEOSPlatformInstance.IsValid())
        {
            return *GRedpointEOSPlatformInstance.Get();
        }
        GRedpointEOSPlatformInstance = MakeShared<FInstancePoolImpl>();
        return *GRedpointEOSPlatformInstance.Get();
    }
}

} // namespace Redpoint::EOS::Core
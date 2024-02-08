// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSAPI/Platform.h"
#include "RedpointEOSCore/InstancePool.h"
#include "RedpointEOSCore/LifecycleManager.h"
#include "RedpointEOSCore/RuntimePlatform.h"

namespace Redpoint::EOS::Core
{

class FInstancePoolImpl : public IInstancePool,
#if REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT
                          public ILifecycleManager,
#endif
                          public TSharedFromThis<FInstancePoolImpl>
{
private:
    FDelegateHandle TickerHandle;
    TMap<FName, API::FPlatformWeakRefCountedHandle> Instances;
    bool bIsInShutdown;
#if REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT
    TSharedPtr<IRuntimePlatform> RuntimePlatform;
    bool bShouldPollForApplicationStatus;
    bool bShouldPollForNetworkStatus;
#endif

    bool Tick(float DeltaSeconds) const;

public:
    FInstancePoolImpl();
    UE_NONCOPYABLE(FInstancePoolImpl);
    virtual ~FInstancePoolImpl();

	void ShutdownAll();

    virtual API::FPlatformRefCountedHandle Create(FName InstanceName) override;
    virtual API::FPlatformRefCountedHandle CreateWithConfig(FName InstanceName, TSharedRef<Config::IConfig> Config)
        override;

#if REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT
    virtual void UpdateApplicationStatus(const EOS_EApplicationStatus &InNewStatus) override;
    virtual void UpdateNetworkStatus(const EOS_ENetworkStatus &InNewStatus) override;
#endif
};

} // namespace Redpoint::EOS::Core
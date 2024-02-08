// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemRedpointEOS/Shared/UniqueNetIdEOS.h"
#include "TestHelpers.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

class FChainedTaskContext
{
    friend class FChainedTaskExecutor;

public:
    // @todo: Hide this and make it available only to the register/wait/unregister classes.
    TMap<FString, TSharedRef<class FChainedTaskRegisteredEventBase>> RegisteredEvents;

private:
    TSharedPtr<class FChainedTaskExecutor> Executor;
    TArray<FMultiplayerScenarioInstance> Instances;

    FChainedTaskContext(const TSharedRef<class FChainedTaskExecutor> &InExecutor);

    void AttachInstances(const TArray<FMultiplayerScenarioInstance> &InInstances);

public:
    UE_NONCOPYABLE(FChainedTaskContext);
    ~FChainedTaskContext() = default;

    FAutomationTestBase &Assert() const;
    IOnlineSubsystem &Instance(int Index);
    const FUniqueNetIdEOS &User(int Index);
};

typedef TSharedRef<FChainedTaskContext> FChainedTaskContextRef;

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
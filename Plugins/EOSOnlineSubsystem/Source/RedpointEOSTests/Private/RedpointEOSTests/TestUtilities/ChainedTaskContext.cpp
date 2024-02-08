// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSTests/TestUtilities/ChainedTaskContext.h"

#include "RedpointEOSTests/TestUtilities/ChainedTaskExecutor.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

FChainedTaskContext::FChainedTaskContext(const TSharedRef<class FChainedTaskExecutor> &InExecutor)
    : Executor(InExecutor)
    , Instances()
{
}

void FChainedTaskContext::AttachInstances(const TArray<FMultiplayerScenarioInstance> &InInstances)
{
    this->Instances = InInstances;
}

FAutomationTestBase &FChainedTaskContext::Assert() const
{
    return *this->Executor->Test;
}

IOnlineSubsystem &FChainedTaskContext::Instance(int Index)
{
    IOnlineSubsystemPtr Ptr = this->Instances[Index].Subsystem.Pin();
    checkf(Ptr.IsValid(), TEXT("Expected online subsystem to be valid!"));
    return *Ptr.Get();
}

const FUniqueNetIdEOS &FChainedTaskContext::User(int Index)
{
    return *this->Instances[Index].UserId.Get();
}

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
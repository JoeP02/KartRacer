// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSTests/TestUtilities/ChainedTaskExecutor.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/ChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTaskContext.h"
#include "TestHelpers.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

void FChainedTaskExecutor::OnStepComplete(
    bool bContinueTesting,
    TSharedRef<FChainedTaskContext> InContext,
    TSharedRef<FChainedTaskExecutor> InSelf)
{
    if (this->Steps.Num() == 0 || !bContinueTesting)
    {
        // We're done testing.
        this->OnDone();
        return;
    }

    auto Next = this->Steps[0];
    this->Steps.RemoveAt(0);
    Next->ExecuteAsync(
        InContext,
        ChainedTask::FChainedTask::FOnComplete::CreateSP(
            this,
            &FChainedTaskExecutor::OnStepComplete,
            InContext,
            InSelf));
}

FChainedTaskExecutor::FChainedTaskExecutor(
    FAsyncHotReloadableAutomationTestBase *InTest,
    std::function<void()> InOnDone)
    : Test(InTest)
    , OnDone(MoveTemp(InOnDone))
    , Steps()
    , bExecuting(false)
{
}

void FChainedTaskExecutor::Execute()
{
    checkf(!this->bExecuting, TEXT("Chained task already executing!"));
    TSharedRef<FChainedTaskExecutor> This = this->AsShared();
    checkf(this->Steps.Num() > 0, TEXT("Expected at least one step in the chained task executor!"));
    TSharedRef<FChainedTaskContext> Context = MakeShareable(new FChainedTaskContext(This));
    int HighestInstanceIndex = 0;
    for (const auto &Step : this->Steps)
    {
        int StepHighestInstanceIndex = Step->GetHighestInstanceIndex();
        if (StepHighestInstanceIndex > HighestInstanceIndex)
        {
            HighestInstanceIndex = StepHighestInstanceIndex;
        }
    }
    checkf(HighestInstanceIndex > 0, TEXT("Expected at least one instance count in the steps."));
    CreateSubsystemsForTest_CreateOnDemand(
        this->Test,
        HighestInstanceIndex,
        this->OnDone,
        [This, Context](const TArray<FMultiplayerScenarioInstance> &Instances, const FOnDone &_Unused) {
            auto First = This->Steps[0];
            This->Steps.RemoveAt(0);
            Context->AttachInstances(Instances);
            First->ExecuteAsync(
                Context,
                ChainedTask::FChainedTask::FOnComplete::CreateSP(
                    This,
                    &FChainedTaskExecutor::OnStepComplete,
                    Context,
                    This));
        });
}

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSTests/TestUtilities/ChainedTask/PeriodicLambdaChainedTask.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

void FPeriodicLambdaChainedTask::ReceiveIterationDone(
    bool bContinueTesting,
    TSharedRef<FPeriodicLambdaChainedTask> This,
    FChainedTaskContextRef Context)
{
    this->CurrentIteration++;

    if (!bContinueTesting)
    {
        this->OnDone.ExecuteIfBound(false);
        return;
    }

    if (this->CurrentIteration >= this->TotalIterations)
    {
        // We're actually done.
        this->OnDone.ExecuteIfBound(true);
    }
    else
    {
        FTSTicker::GetCoreTicker().AddTicker(
            FTickerDelegate::CreateSP(this, &FPeriodicLambdaChainedTask::ReceiveDelayComplete, This, Context),
            this->DelaySeconds);
    }
}

bool FPeriodicLambdaChainedTask::ReceiveDelayComplete(
    float DeltaSeconds,
    TSharedRef<FPeriodicLambdaChainedTask> This,
    FChainedTaskContextRef Context)
{
    // Start the next loop iteration.
    this->OnExecute.Execute(
        Context,
        this->CurrentIteration,
        FOnComplete::CreateSP(this, &FPeriodicLambdaChainedTask::ReceiveIterationDone, This, Context));

    // This always only fires once.
    return false;
}

int FPeriodicLambdaChainedTask::GetHighestInstanceIndex() const
{
    return 0;
}

void FPeriodicLambdaChainedTask::ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &InOnDone)
{
    if (!this->OnExecute.IsBound())
    {
        Context->Assert().TestTrue("OnExecute was not bound for PeriodicLambdaChainedTask!", false);
        InOnDone.ExecuteIfBound(false);
        return;
    }

    this->OnDone = InOnDone;
    this->CurrentIteration = 0;
    this->OnExecute.Execute(
        Context,
        this->CurrentIteration,
        FOnComplete::CreateSP(this, &FPeriodicLambdaChainedTask::ReceiveIterationDone, this->AsShared(), Context));
}

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
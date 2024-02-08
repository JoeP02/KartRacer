// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSTests/TestUtilities/ChainedTask/DelayChainedTask.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

bool FDelayChainedTask::ReceiveDelayComplete(
    float DeltaSeconds,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    TSharedRef<FDelayChainedTask> This,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    FOnComplete OnDone)
{
    OnDone.ExecuteIfBound(true);
    return false;
}

FDelayChainedTask::FDelayChainedTask(float InDelaySeconds)
    : DelaySeconds(InDelaySeconds)
{
}

int FDelayChainedTask::GetHighestInstanceIndex() const
{
    return 0;
}

void FDelayChainedTask::ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &InOnDone)
{
    FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateSP(this, &FDelayChainedTask::ReceiveDelayComplete, this->AsShared(), InOnDone),
        this->DelaySeconds);
}

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
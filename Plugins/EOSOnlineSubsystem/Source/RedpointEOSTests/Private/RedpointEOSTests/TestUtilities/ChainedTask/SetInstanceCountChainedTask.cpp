// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSTests/TestUtilities/ChainedTask/SetInstanceCountChainedTask.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

FSetInstanceCountChainedTask::FSetInstanceCountChainedTask(int InHighestInstanceIndex)
    : HighestInstanceIndex(InHighestInstanceIndex)
{
}

int FSetInstanceCountChainedTask::GetHighestInstanceIndex() const
{
    return this->HighestInstanceIndex;
}

void FSetInstanceCountChainedTask::ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone)
{
    OnDone.ExecuteIfBound(true);
}

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
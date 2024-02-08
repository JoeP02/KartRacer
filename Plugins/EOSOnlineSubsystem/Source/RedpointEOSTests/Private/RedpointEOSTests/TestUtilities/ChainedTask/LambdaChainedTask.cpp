// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSTests/TestUtilities/ChainedTask/LambdaChainedTask.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

FLambdaChainedTask::FLambdaChainedTask(const FOnExecute &InOnExecute)
    : OnExecute(InOnExecute)
{
}

int FLambdaChainedTask::GetHighestInstanceIndex() const
{
    return 0;
}

void FLambdaChainedTask::ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone)
{
    if (this->OnExecute.IsBound())
    {
        this->OnExecute.Execute(Context, OnDone);
    }
	else
	{
        Context->Assert().TestTrue("OnExecute was not bound for LambdaChainedTask!", false);
        OnDone.ExecuteIfBound(false);
	}
}

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
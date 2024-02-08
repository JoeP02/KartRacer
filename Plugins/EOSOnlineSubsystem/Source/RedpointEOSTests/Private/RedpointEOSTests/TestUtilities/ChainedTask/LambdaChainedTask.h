// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/ChainedTask.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

class FLambdaChainedTask : public FChainedTask
{
public:
    typedef TDelegate<void(const FChainedTaskContextRef &Context, const FOnComplete &OnDone)> FOnExecute;

private:
    FOnExecute OnExecute;

public:
    FLambdaChainedTask(const FOnExecute &InOnExecute);

    template <typename FunctorType, typename... VarTypes>
	FLambdaChainedTask(FunctorType&& InFunctor, VarTypes &&...Vars)
		: OnExecute(FLambdaChainedTask::FOnExecute::CreateLambda(InFunctor, Vars...))
	{
	}

    UE_NONCOPYABLE(FLambdaChainedTask);
    virtual ~FLambdaChainedTask() = default;

    virtual int GetHighestInstanceIndex() const;

    virtual void ExecuteAsync(const FChainedTaskContextRef& Context, const FOnComplete &OnDone);
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
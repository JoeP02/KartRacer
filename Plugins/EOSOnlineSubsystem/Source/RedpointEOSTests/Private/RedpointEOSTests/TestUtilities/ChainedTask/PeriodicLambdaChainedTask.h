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

class FPeriodicLambdaChainedTask : public FChainedTask, public TSharedFromThis<FPeriodicLambdaChainedTask>
{
public:
    typedef TDelegate<void(const FChainedTaskContextRef &Context, int Iteration, const FOnComplete &OnDone)> FOnExecute;

private:
    float DelaySeconds;
    int CurrentIteration;
    int TotalIterations;
    FOnExecute OnExecute;

    FOnComplete OnDone;

    void ReceiveIterationDone(
        bool bContinueTesting,
        TSharedRef<FPeriodicLambdaChainedTask> This,
        FChainedTaskContextRef Context);
    bool ReceiveDelayComplete(
        float DeltaSeconds,
        TSharedRef<FPeriodicLambdaChainedTask> This,
        FChainedTaskContextRef Context);

public:
    template <typename FunctorType, typename... VarTypes>
    FPeriodicLambdaChainedTask(float InDelaySeconds, int InIterations, FunctorType &&InFunctor, VarTypes &&...Vars)
        : DelaySeconds(InDelaySeconds)
        , CurrentIteration(0)
        , TotalIterations(InIterations)
        , OnExecute(FPeriodicLambdaChainedTask::FOnExecute::CreateLambda(InFunctor, Vars...))
        , OnDone()
    {
    }

    UE_NONCOPYABLE(FPeriodicLambdaChainedTask);
    virtual ~FPeriodicLambdaChainedTask() = default;

    virtual int GetHighestInstanceIndex() const;

    virtual void ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone);
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
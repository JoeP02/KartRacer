// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/ChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTaskRegisteredEvent.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

template <typename FEventHandlerType> class FWaitForEventChainedTask : public FChainedTask
{
public:
    typedef typename FChainedTaskRegisteredEventHelper<FEventHandlerType>::RegisteredEventType FRegisteredEventType;
    typedef typename FRegisteredEventType::FOnFilter FOnFilter;

private:
    FString EventName;
    float TimeoutSeconds;
    FOnFilter OnFilter;

public:
    FWaitForEventChainedTask(const FString &InEventName, float InTimeoutSeconds, const FOnFilter &InOnFilter)
        : EventName(InEventName)
        , TimeoutSeconds(InTimeoutSeconds)
        , OnFilter(InOnFilter)
    {
    }

    template <typename FunctorType, typename... VarTypes>
    FWaitForEventChainedTask(
        const FString &InEventName,
        float InTimeoutSeconds,
        FunctorType &&InFunctor,
        VarTypes &&...Vars)
        : EventName(InEventName)
        , TimeoutSeconds(InTimeoutSeconds)
        , OnFilter(FOnFilter::CreateLambda(InFunctor, Vars...))
    {
    }

    UE_NONCOPYABLE(FWaitForEventChainedTask);
    virtual ~FWaitForEventChainedTask() = default;

    virtual int GetHighestInstanceIndex() const
    {
        return 0;
    }

    virtual void ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone)
    {
        auto RegisteredEvent = StaticCastSharedRef<FRegisteredEventType>(Context->RegisteredEvents[this->EventName]);
        checkf(OnDone.IsBound(), TEXT("OnDone should be bound!"));
        RegisteredEvent->WaitAndProcessEvents(Context, this->EventName, this->OnFilter, this->TimeoutSeconds, OnDone);
    }
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
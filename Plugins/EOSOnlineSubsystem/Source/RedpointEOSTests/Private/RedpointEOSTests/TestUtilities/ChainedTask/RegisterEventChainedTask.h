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

template <typename FEventHandlerType> class FRegisterEventChainedTask : public FChainedTask
{
public:
    typedef TDelegate<FDelegateHandle(const FChainedTaskContextRef &Context, const FEventHandlerType &OnEventRaised)>
        FOnRegister;
    typedef TDelegate<void(const FChainedTaskContextRef &, FDelegateHandle)> FOnUnregister;
    typedef typename FChainedTaskRegisteredEventHelper<FEventHandlerType>::RegisteredEventType FRegisteredEventType;

private:
    FString EventName;
    FOnRegister OnRegister;
    FOnUnregister OnUnregister;

public:
    FRegisterEventChainedTask(
        const FString &InEventName,
        const FOnRegister &InOnRegister,
        const FOnUnregister &InOnUnregister)
        : EventName(InEventName)
        , OnRegister(InOnRegister)
        , OnUnregister(InOnUnregister)
    {
    }

    template <typename RegisterFunctorType, typename UnregisterFunctorType>
    FRegisterEventChainedTask(
        const FString &InEventName,
        RegisterFunctorType &&InOnRegister,
        UnregisterFunctorType &&InOnUnregister)
        : EventName(InEventName)
        , OnRegister(FRegisterEventChainedTask::FOnRegister::CreateLambda(InOnRegister))
        , OnUnregister(FRegisterEventChainedTask::FOnUnregister::CreateLambda(InOnUnregister))
    {
    }

    UE_NONCOPYABLE(FRegisterEventChainedTask);
    virtual ~FRegisterEventChainedTask() = default;

    virtual int GetHighestInstanceIndex() const
    {
        return 0;
    }

    virtual void ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone)
    {
        auto RegisteredEvent = MakeShared<FRegisteredEventType>(this->OnUnregister);
        this->OnRegister.Execute(Context, RegisteredEvent->GetDelegateForRegistration());
        Context->RegisteredEvents.Add(this->EventName, RegisteredEvent);
        OnDone.Execute(true);
    }
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
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

class FUnregisterEventChainedTask : public FChainedTask
{
private:
    FString EventName;

public:
    FUnregisterEventChainedTask(
        const FString &InEventName)
        : EventName(InEventName)
    {
    }
    UE_NONCOPYABLE(FUnregisterEventChainedTask);
    virtual ~FUnregisterEventChainedTask() = default;

    virtual int GetHighestInstanceIndex() const
    {
        return 0;
    }

    virtual void ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone)
    {
        Context->RegisteredEvents[this->EventName]->Unregister(Context);
        Context->RegisteredEvents.Remove(this->EventName);
        OnDone.Execute(true);
    }
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
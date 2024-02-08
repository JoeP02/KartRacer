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

class FDelayChainedTask : public FChainedTask, public TSharedFromThis<FDelayChainedTask>
{
private:
    float DelaySeconds;
    bool ReceiveDelayComplete(float DeltaSeconds, TSharedRef<FDelayChainedTask> This, FOnComplete OnDone);

public:
    FDelayChainedTask(float InDelaySeconds);
    UE_NONCOPYABLE(FDelayChainedTask);
    virtual ~FDelayChainedTask() = default;

    virtual int GetHighestInstanceIndex() const;

    virtual void ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone);
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
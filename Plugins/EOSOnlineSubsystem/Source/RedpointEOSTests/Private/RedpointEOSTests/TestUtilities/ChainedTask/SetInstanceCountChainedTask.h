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

class FSetInstanceCountChainedTask : public FChainedTask
{
private:
    int HighestInstanceIndex;

public:
    FSetInstanceCountChainedTask(int InHighestInstanceIndex);
    UE_NONCOPYABLE(FSetInstanceCountChainedTask);
    virtual ~FSetInstanceCountChainedTask() = default;

    virtual int GetHighestInstanceIndex() const;

    virtual void ExecuteAsync(const FChainedTaskContextRef &, const FOnComplete &OnDone);
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
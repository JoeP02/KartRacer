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

class FVerifyFriendIsNotPresentChainedTask : public FChainedTask
{
private:
    int SourceInstanceIndex;
    int TargetInstanceIndex;

public:
    FVerifyFriendIsNotPresentChainedTask(
        int InSourceInstanceIndex,
        int InTargetInstanceIndex);
    UE_NONCOPYABLE(FVerifyFriendIsNotPresentChainedTask);
    virtual ~FVerifyFriendIsNotPresentChainedTask() = default;

    virtual int GetHighestInstanceIndex() const;

    virtual void ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone);
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
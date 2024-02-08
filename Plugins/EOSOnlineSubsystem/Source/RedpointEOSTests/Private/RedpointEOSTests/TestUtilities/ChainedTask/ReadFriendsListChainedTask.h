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

class FReadFriendsListChainedTask : public FChainedTask
{
private:
    int InstanceIndex;

public:
    FReadFriendsListChainedTask(int InInstanceIndex);
    UE_NONCOPYABLE(FReadFriendsListChainedTask);
    virtual ~FReadFriendsListChainedTask() = default;

    virtual int GetHighestInstanceIndex() const;

    virtual void ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone);
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
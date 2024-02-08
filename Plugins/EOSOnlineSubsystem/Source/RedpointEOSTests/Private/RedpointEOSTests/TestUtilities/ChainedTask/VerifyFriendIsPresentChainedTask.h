// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/ChainedTask.h"

#include "Interfaces/OnlineFriendsInterface.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

class FVerifyFriendIsPresentChainedTask : public FChainedTask
{
private:
    int SourceInstanceIndex;
    int TargetInstanceIndex;
    EInviteStatus::Type InviteStatus;

public:
    FVerifyFriendIsPresentChainedTask(
        int InSourceInstanceIndex,
        int InTargetInstanceIndex,
        EInviteStatus::Type InInviteStatus);
    UE_NONCOPYABLE(FVerifyFriendIsPresentChainedTask);
    virtual ~FVerifyFriendIsPresentChainedTask() = default;

    virtual int GetHighestInstanceIndex() const;

    virtual void ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone);
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
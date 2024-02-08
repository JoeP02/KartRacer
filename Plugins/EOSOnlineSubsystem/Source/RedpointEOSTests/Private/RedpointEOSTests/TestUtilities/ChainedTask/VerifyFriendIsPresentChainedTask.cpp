// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSTests/TestUtilities/ChainedTask/VerifyFriendIsPresentChainedTask.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

FVerifyFriendIsPresentChainedTask::FVerifyFriendIsPresentChainedTask(
    int InSourceInstanceIndex,
    int InTargetInstanceIndex,
    EInviteStatus::Type InInviteStatus)
    : SourceInstanceIndex(InSourceInstanceIndex)
    , TargetInstanceIndex(InTargetInstanceIndex)
    , InviteStatus(InInviteStatus)
{
}

int FVerifyFriendIsPresentChainedTask::GetHighestInstanceIndex() const
{
    return FMath::Max(this->SourceInstanceIndex, this->TargetInstanceIndex);
}

void FVerifyFriendIsPresentChainedTask::ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone)
{
    // Get all of the user's friends.
    TArray<TSharedRef<FOnlineFriend>> Friends;
    if (!Context->Assert().TestTrue(
            TEXT("Expected GetFriendsList to succeed"),
            Context->Instance(this->SourceInstanceIndex).GetFriendsInterface()->GetFriendsList(0, TEXT(""), Friends)))
    {
        OnDone.ExecuteIfBound(false);
        return;
    }

    // Make sure the friend is in there.
    bool bFound = false;
    for (const auto &Friend : Friends)
    {
        if (*Friend->GetUserId() == Context->User(this->TargetInstanceIndex) && Friend->GetInviteStatus() == this->InviteStatus)
        {
            bFound = true;
        }
    }
    Context->Assert().TestTrue("Expected friend to be present on friends list", bFound);
    OnDone.ExecuteIfBound(true);
}

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
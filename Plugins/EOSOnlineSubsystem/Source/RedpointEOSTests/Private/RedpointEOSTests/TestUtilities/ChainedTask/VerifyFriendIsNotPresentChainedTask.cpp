// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSTests/TestUtilities/ChainedTask/VerifyFriendIsNotPresentChainedTask.h"

#include "Interfaces/OnlineFriendsInterface.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

FVerifyFriendIsNotPresentChainedTask::FVerifyFriendIsNotPresentChainedTask(
    int InSourceInstanceIndex,
    int InTargetInstanceIndex)
    : SourceInstanceIndex(InSourceInstanceIndex)
    , TargetInstanceIndex(InTargetInstanceIndex)
{
}

int FVerifyFriendIsNotPresentChainedTask::GetHighestInstanceIndex() const
{
    return FMath::Max(this->SourceInstanceIndex, this->TargetInstanceIndex);
}

void FVerifyFriendIsNotPresentChainedTask::ExecuteAsync(const FChainedTaskContextRef &Context, const FOnComplete &OnDone)
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

    // Make sure the friend is not in there.
    bool bFound = false;
    for (const auto &Friend : Friends)
    {
        if (*Friend->GetUserId() == Context->User(this->TargetInstanceIndex))
        {
            bFound = true;
        }
    }
    Context->Assert().TestFalse("Expected friend not to be present on friends list", bFound);
    OnDone.ExecuteIfBound(true);
}

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
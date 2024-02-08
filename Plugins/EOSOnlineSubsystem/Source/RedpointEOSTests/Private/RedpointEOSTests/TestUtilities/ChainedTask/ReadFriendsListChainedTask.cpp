// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSTests/TestUtilities/ChainedTask/ReadFriendsListChainedTask.h"

#include "Interfaces/OnlineFriendsInterface.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

FReadFriendsListChainedTask::FReadFriendsListChainedTask(int InInstanceIndex)
    : InstanceIndex(InInstanceIndex)
{
}

int FReadFriendsListChainedTask::GetHighestInstanceIndex() const
{
    return this->InstanceIndex;
}

void FReadFriendsListChainedTask::ExecuteAsync(const FChainedTaskContextRef& Context, const FOnComplete& OnDone)
{
    Context->Instance(this->InstanceIndex).GetFriendsInterface()->ReadFriendsList(
        0,
        TEXT(""),
        FOnReadFriendsListComplete::CreateLambda(
            [Context,
             OnDone](int32 LocalUserNum, bool bWasSuccessful, const FString &ListName, const FString &ErrorStr) {
                OnDone.ExecuteIfBound(Context->Assert().TestTrue(
                    FString::Printf(TEXT("Expected ReadFriendsList to succeed, got error: %s"), *ErrorStr),
                    bWasSuccessful));
            }));
}

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
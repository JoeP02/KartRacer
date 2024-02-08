// Copyright June Rhodes 2024. All Rights Reserved.

#include "CoreMinimal.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/LambdaChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/ReadFriendsListChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/RegisterEventChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/SetInstanceCountChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/UnregisterEventChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/VerifyFriendIsPresentChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/WaitForEventChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTaskExecutor.h"
#include "TestHelpers.h"

IMPLEMENT_ASYNC_AUTOMATION_TEST(
    FOnlineSubsystemEOS_Friends_SendInviteAndAcceptWorks,
    "OnlineSubsystemEOS.Friends.SendInviteAndAcceptWorks",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

void FOnlineSubsystemEOS_Friends_SendInviteAndAcceptWorks::RunAsyncTest(const std::function<void()> &OnDone)
{
    using namespace Redpoint::EOS::Tests::TestUtilities;
    using namespace Redpoint::EOS::Tests::TestUtilities::ChainedTask;

    TSharedRef<FChainedTaskExecutor> Executor = MakeShareable(new FChainedTaskExecutor(this, OnDone));

    // We want two instances.
    Executor->Then<FSetInstanceCountChainedTask>(2);

    // We need to call ReadFriendsList before sending an invite to a user.
    Executor->Then<FReadFriendsListChainedTask>(0);

    // Register "invite received" event on instance 1.
    Executor->Then<FRegisterEventChainedTask<FOnInviteReceivedDelegate>>(
        "InviteReceived",
        [](const FChainedTaskContextRef &Context, const FOnInviteReceivedDelegate &OnEventRaised) {
            return Context->Instance(1).GetFriendsInterface()->AddOnInviteReceivedDelegate_Handle(OnEventRaised);
        },
        [](const FChainedTaskContextRef &Context, FDelegateHandle Handle) {
            return Context->Instance(1).GetFriendsInterface()->ClearOnInviteReceivedDelegate_Handle(Handle);
        });

    // Send the invite from user 0 to user 1.
    Executor->Then<FLambdaChainedTask>(
        [](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            Context->Instance(0).GetFriendsInterface()->SendInvite(
                0,
                Context->User(1),
                TEXT(""),
                FOnSendInviteComplete::CreateLambda([Context, OnDone](
                                                        int32 LocalUserNum,
                                                        bool bWasSuccessful,
                                                        const FUniqueNetId &FriendId,
                                                        const FString &ListName,
                                                        const FString &ErrorStr) {
                    // Continue testing only if the assert passes.
                    OnDone.ExecuteIfBound(Context->Assert().TestTrue(
                        FString::Printf(TEXT("Expected SendInvite to succeed, got error: %s"), *ErrorStr),
                        bWasSuccessful));
                }));
        });

    // Wait for the "invite received" event to fire.
    Executor->Then<FWaitForEventChainedTask<FOnInviteReceivedDelegate>>(
        "InviteReceived",
        60.0f,
        [](const FChainedTaskContextRef &Context, const FUniqueNetId &UserId, const FUniqueNetId &FriendId) {
            return Context->User(1) == UserId && Context->User(0) == FriendId;
        });

    // Deregister the "invite received event".
    Executor->Then<FUnregisterEventChainedTask>("InviteReceived");

    // Make sure the friends lists are in expected state.
    Executor->Then<FReadFriendsListChainedTask>(0);
    Executor->Then<FReadFriendsListChainedTask>(1);
    Executor->Then<FVerifyFriendIsPresentChainedTask>(0, 1, EInviteStatus::PendingOutbound);
    Executor->Then<FVerifyFriendIsPresentChainedTask>(1, 0, EInviteStatus::PendingInbound);

    // Register the "invite accepted" event on instance 0.
    Executor->Then<FRegisterEventChainedTask<FOnInviteAcceptedDelegate>>(
        "InviteAccepted",
        [](const FChainedTaskContextRef &Context, const FOnInviteAcceptedDelegate &OnEventRaised) {
            return Context->Instance(0).GetFriendsInterface()->AddOnInviteAcceptedDelegate_Handle(OnEventRaised);
        },
        [](const FChainedTaskContextRef &Context, FDelegateHandle Handle) {
            return Context->Instance(0).GetFriendsInterface()->ClearOnInviteAcceptedDelegate_Handle(Handle);
        });

    // Accept the invite on instance 1.
    Executor->Then<FLambdaChainedTask>(
        [](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            Context->Instance(1).GetFriendsInterface()->AcceptInvite(
                0,
                Context->User(0),
                TEXT(""),
                FOnAcceptInviteComplete::CreateLambda([Context, OnDone](
                                                          int32 LocalUserNum,
                                                          bool bWasSuccessful,
                                                          const FUniqueNetId &FriendId,
                                                          const FString &ListName,
                                                          const FString &ErrorStr) {
                    // Continue testing only if the assert passes.
                    OnDone.ExecuteIfBound(Context->Assert().TestTrue(
                        FString::Printf(TEXT("Expected AcceptInvite to succeed, got error: %s"), *ErrorStr),
                        bWasSuccessful));
                }));
        });

    // Wait for the "invite accepted" event to fire.
    Executor->Then<FWaitForEventChainedTask<FOnInviteAcceptedDelegate>>(
        "InviteAccepted",
        60.0f,
        [](const FChainedTaskContextRef &Context, const FUniqueNetId &UserId, const FUniqueNetId &FriendId) {
            return Context->User(0) == UserId && Context->User(1) == FriendId;
        });

    // Deregister the "invite accepted event".
    Executor->Then<FUnregisterEventChainedTask>("InviteAccepted");

    // Make sure that user 1 appears as a friend on user 0's friends list.
    Executor->Then<FReadFriendsListChainedTask>(0);
    Executor->Then<FReadFriendsListChainedTask>(1);
    Executor->Then<FVerifyFriendIsPresentChainedTask>(0, 1, EInviteStatus::Accepted);
    Executor->Then<FVerifyFriendIsPresentChainedTask>(1, 0, EInviteStatus::Accepted);

    // Run the test.
    Executor->Execute();
}
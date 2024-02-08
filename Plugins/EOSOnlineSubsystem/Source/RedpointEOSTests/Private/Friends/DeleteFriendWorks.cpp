// Copyright June Rhodes 2024. All Rights Reserved.

#include "CoreMinimal.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/LambdaChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/ReadFriendsListChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/RegisterEventChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/SetInstanceCountChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/UnregisterEventChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/VerifyFriendIsPresentChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/VerifyFriendIsNotPresentChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/WaitForEventChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTaskExecutor.h"
#include "TestHelpers.h"

IMPLEMENT_ASYNC_AUTOMATION_TEST(
    FOnlineSubsystemEOS_Friends_DeleteFriendWorks,
    "OnlineSubsystemEOS.Friends.DeleteFriendWorks",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

void FOnlineSubsystemEOS_Friends_DeleteFriendWorks::RunAsyncTest(const std::function<void()> &OnDone)
{
    using namespace Redpoint::EOS::Tests::TestUtilities;
    using namespace Redpoint::EOS::Tests::TestUtilities::ChainedTask;

    TSharedRef<FChainedTaskExecutor> Executor = MakeShareable(new FChainedTaskExecutor(this, OnDone));

    // We want two instances.
    Executor->Then<FSetInstanceCountChainedTask>(2);

    // All of these steps are from SendAndAcceptInviteWorks and are just so we can get
	// the friend database in the correct state.
    Executor->Then<FReadFriendsListChainedTask>(0);
    Executor->Then<FRegisterEventChainedTask<FOnInviteReceivedDelegate>>(
        "InviteReceived",
        [](const FChainedTaskContextRef &Context, const FOnInviteReceivedDelegate &OnEventRaised) {
            return Context->Instance(1).GetFriendsInterface()->AddOnInviteReceivedDelegate_Handle(OnEventRaised);
        },
        [](const FChainedTaskContextRef &Context, FDelegateHandle Handle) {
            return Context->Instance(1).GetFriendsInterface()->ClearOnInviteReceivedDelegate_Handle(Handle);
        });
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
    Executor->Then<FWaitForEventChainedTask<FOnInviteReceivedDelegate>>(
        "InviteReceived",
        60.0f,
        [](const FChainedTaskContextRef &Context, const FUniqueNetId &UserId, const FUniqueNetId &FriendId) {
            return Context->User(1) == UserId && Context->User(0) == FriendId;
        });
    Executor->Then<FUnregisterEventChainedTask>("InviteReceived");
    Executor->Then<FRegisterEventChainedTask<FOnInviteAcceptedDelegate>>(
        "InviteAccepted",
        [](const FChainedTaskContextRef &Context, const FOnInviteAcceptedDelegate &OnEventRaised) {
            return Context->Instance(0).GetFriendsInterface()->AddOnInviteAcceptedDelegate_Handle(OnEventRaised);
        },
        [](const FChainedTaskContextRef &Context, FDelegateHandle Handle) {
            return Context->Instance(0).GetFriendsInterface()->ClearOnInviteAcceptedDelegate_Handle(Handle);
        });
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
    Executor->Then<FWaitForEventChainedTask<FOnInviteAcceptedDelegate>>(
        "InviteAccepted",
        60.0f,
        [](const FChainedTaskContextRef &Context, const FUniqueNetId &UserId, const FUniqueNetId &FriendId) {
            return Context->User(0) == UserId && Context->User(1) == FriendId;
        });
    Executor->Then<FUnregisterEventChainedTask>("InviteAccepted");

    // Make sure the users see each other as friends.
    Executor->Then<FReadFriendsListChainedTask>(0);
    Executor->Then<FReadFriendsListChainedTask>(1);
    Executor->Then<FVerifyFriendIsPresentChainedTask>(0, 1, EInviteStatus::Accepted);
    Executor->Then<FVerifyFriendIsPresentChainedTask>(1, 0, EInviteStatus::Accepted);

	// Register "friend removed" event on instance 0.
    Executor->Then<FRegisterEventChainedTask<FOnFriendRemovedDelegate>>(
        "FriendRemoved",
        [](const FChainedTaskContextRef &Context, const FOnFriendRemovedDelegate &OnEventRaised) {
            return Context->Instance(0).GetFriendsInterface()->AddOnFriendRemovedDelegate_Handle(OnEventRaised);
        },
        [](const FChainedTaskContextRef &Context, FDelegateHandle Handle) {
            return Context->Instance(0).GetFriendsInterface()->ClearOnFriendRemovedDelegate_Handle(Handle);
        });

    // Register "delete friend complete" event on instance 1.
    Executor->Then<FRegisterEventChainedTask<FOnDeleteFriendCompleteDelegate>>(
        "DeleteFriendComplete",
        [](const FChainedTaskContextRef &Context, const FOnDeleteFriendCompleteDelegate &OnEventRaised) {
            return Context->Instance(1).GetFriendsInterface()->AddOnDeleteFriendCompleteDelegate_Handle(0, OnEventRaised);
        },
        [](const FChainedTaskContextRef &Context, FDelegateHandle Handle) {
            return Context->Instance(1).GetFriendsInterface()->ClearOnDeleteFriendCompleteDelegate_Handle(0, Handle);
        });

    // Get user 1 to remove user 0 from their friend's list.
    Executor->Then<FLambdaChainedTask>(
        [](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            Context->Assert().TestTrue(
                "DeleteFriend call should start",
                Context->Instance(1).GetFriendsInterface()->DeleteFriend(0, Context->User(0), TEXT("")));
            OnDone.Execute(true);
        });

    // Wait for the "delete friend complete" event to fire, then unregister it.
    Executor->Then<FWaitForEventChainedTask<FOnDeleteFriendCompleteDelegate>>(
        "DeleteFriendComplete",
        60.0f,
        [](const FChainedTaskContextRef &Context,
           int32 LocalUserNum,
           bool bWasSuccessful,
           const FUniqueNetId & FriendId,
           const FString & ListName,
           const FString & ErrorStr) {
            Context->Assert().TestEqual("LocalUserNum is 0", LocalUserNum, 0);
            Context->Assert().TestEqual("bWasSuccessful", bWasSuccessful, true);
            Context->Assert().TestEqual<FUniqueNetId>("FriendId is user 0", FriendId, Context->User(0));
            Context->Assert().TestEqual("ListName was empty", ListName, TEXT(""));
            Context->Assert().TestEqual("ErrorStr was empty", ListName, TEXT(""));
            return true;
        });
    Executor->Then<FUnregisterEventChainedTask>("DeleteFriendComplete");

    // Wait for the "friend removed" event to fire, then unregister it.
    Executor->Then<FWaitForEventChainedTask<FOnFriendRemovedDelegate>>(
        "FriendRemoved",
        60.0f,
        [](const FChainedTaskContextRef &Context, const FUniqueNetId &UserId, const FUniqueNetId &FriendId) {
            return Context->User(0) == UserId && Context->User(1) == FriendId;
        });
    Executor->Then<FUnregisterEventChainedTask>("FriendRemoved");

    // Make sure the friends lists are in expected state.
    Executor->Then<FReadFriendsListChainedTask>(0);
    Executor->Then<FReadFriendsListChainedTask>(1);
    Executor->Then<FVerifyFriendIsNotPresentChainedTask>(0, 1);
    Executor->Then<FVerifyFriendIsNotPresentChainedTask>(1, 0);

    // Run the test.
    Executor->Execute();
}
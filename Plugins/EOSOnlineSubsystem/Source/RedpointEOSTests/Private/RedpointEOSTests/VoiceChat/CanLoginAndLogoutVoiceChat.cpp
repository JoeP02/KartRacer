// Copyright June Rhodes 2024. All Rights Reserved.

#include "CoreMinimal.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/LambdaChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/SetInstanceCountChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTaskExecutor.h"
#include "RedpointEOSTests/VoiceChat/VoiceChatUserHolder.h"
#include "TestHelpers.h"
#include "VoiceChat.h"

namespace Redpoint::EOS::Tests
{

namespace VoiceChat
{

IMPLEMENT_ASYNC_AUTOMATION_TEST(
    FOnlineSubsystemEOS_VoiceChat_CanLoginAndLogoutVoiceChat,
    "OnlineSubsystemEOS.VoiceChat.CanLoginAndLogoutVoiceChat",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

void FOnlineSubsystemEOS_VoiceChat_CanLoginAndLogoutVoiceChat::RunAsyncTest(const std::function<void()> &OnDone)
{
    using namespace Redpoint::EOS::Tests::TestUtilities;
    using namespace Redpoint::EOS::Tests::TestUtilities::ChainedTask;

    TSharedRef<FChainedTaskExecutor> Executor = MakeShareable(new FChainedTaskExecutor(this, OnDone));

    // Create a shared pointer that we can use to store the IVoiceChatUser*.
    auto VoiceChatUser = MakeShared<FVoiceChatUserHolder>();

    // We want one instance.
    Executor->Then<FSetInstanceCountChainedTask>(1);

    // Login in the user to the voice chat system.
    Executor->Then<FLambdaChainedTask>(
        [VoiceChatUser](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            IVoiceChat *VoiceChat = IVoiceChat::Get();
            *VoiceChatUser = VoiceChat->CreateUser();

            FPlatformUserId PlatformUserId =
                Context->Instance(0).GetIdentityInterface()->GetPlatformUserIdFromUniqueNetId(Context->User(0));

            (*VoiceChatUser)
                ->Login(
                    PlatformUserId,
                    Context->Instance(0).GetIdentityInterface()->GetUniquePlayerId(0)->ToString(),
                    TEXT(""),
                    FOnVoiceChatLoginCompleteDelegate::CreateLambda(
                        [Context, OnDone](const FString &PlayerName, const FVoiceChatResult &Result) {
                            Context->Assert().TestTrue(
                                TEXT("Expected voice chat to login successfully."),
                                Result.IsSuccess());
                            OnDone.ExecuteIfBound(true);
                        }));
        });

    // Log the user out of the voice chat system.
    Executor->Then<FLambdaChainedTask>([VoiceChatUser](
                                           const FChainedTaskContextRef &Context,
                                           const FLambdaChainedTask::FOnComplete &OnDone) {
        (*VoiceChatUser)
            ->Logout(FOnVoiceChatLogoutCompleteDelegate::CreateLambda(
                [Context, OnDone, VoiceChatUser /* unused but keeps shared ptr alive */](
                    const FString &PlayerName,
                    const FVoiceChatResult &Result) {
                    Context->Assert().TestTrue(TEXT("Expected voice chat to logout successfully."), Result.IsSuccess());
                    OnDone.ExecuteIfBound(true);
                }));
    });

    // Run the test.
    Executor->Execute();
}

} // namespace VoiceChat

} // namespace Redpoint::EOS::Tests
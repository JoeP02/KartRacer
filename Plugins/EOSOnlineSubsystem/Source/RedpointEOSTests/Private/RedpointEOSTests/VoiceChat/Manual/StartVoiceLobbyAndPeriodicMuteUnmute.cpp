// Copyright June Rhodes 2024. All Rights Reserved.

#include "CoreMinimal.h"
#include "Features/IModularFeatures.h"
#include "RedpointEOSInterfaces/Private/Interfaces/OnlineLobbyInterface.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/DelayChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/LambdaChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/PeriodicLambdaChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/RegisterEventChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/SetInstanceCountChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/UnregisterEventChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/WaitForEventChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTaskExecutor.h"
#include "RedpointEOSTests/VoiceChat/VoiceChatUserHolder.h"
#include "TestHelpers.h"
#include "VoiceChat.h"

namespace Redpoint::EOS::Tests
{

namespace VoiceChat
{

namespace Manual
{

IMPLEMENT_ASYNC_AUTOMATION_TEST(
    FOnlineSubsystemEOS_VoiceChat_Manual_StartVoiceLobbyAndPeriodicMuteUnmute,
    "OnlineSubsystemEOS.VoiceChat.Manual.StartVoiceLobbyAndPeriodicMuteUnmute",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter |
        EAutomationTestFlags::RequiresUser);

void FOnlineSubsystemEOS_VoiceChat_Manual_StartVoiceLobbyAndPeriodicMuteUnmute::RunAsyncTest(
    const std::function<void()> &OnDone)
{
    using namespace Redpoint::EOS::Tests::TestUtilities;
    using namespace Redpoint::EOS::Tests::TestUtilities::ChainedTask;

    typedef TDelegate<void(
        TSharedRef<const FUniqueNetId> UserId,
        TSharedRef<const FOnlineLobbyId> LobbyId,
        TSharedRef<const FUniqueNetId> MemberId)>
        FOnMemberConnectRefDelegate;

    TSharedRef<FChainedTaskExecutor> Executor = MakeShareable(new FChainedTaskExecutor(this, OnDone));

    // Create some shared pointers to hold state.
    auto VoiceChatUser0 = MakeShared<FVoiceChatUserHolder>();
    auto VoiceChatUser1 = MakeShared<FVoiceChatUserHolder>();
    auto CreatedLobbyId = MakeShared<TSharedPtr<const FOnlineLobbyId>>();

    // We want one instance.
    Executor->Then<FSetInstanceCountChainedTask>(2);

    // Login in the user 0 to the voice chat system.
    Executor->Then<FLambdaChainedTask>(
        [VoiceChatUser0](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            IVoiceChat *VoiceChat = IVoiceChat::Get();
            *VoiceChatUser0 = VoiceChat->CreateUser();

            FPlatformUserId PlatformUserId =
                Context->Instance(0).GetIdentityInterface()->GetPlatformUserIdFromUniqueNetId(Context->User(0));

            (*VoiceChatUser0)
                ->Login(
                    PlatformUserId,
                    Context->Instance(0).GetIdentityInterface()->GetUniquePlayerId(0)->ToString(),
                    TEXT(""),
                    FOnVoiceChatLoginCompleteDelegate::CreateLambda(
                        [Context, OnDone](const FString &PlayerName, const FVoiceChatResult &Result) {
                            Context->Assert().TestTrue(
                                TEXT("Expected voice chat to login user 0 successfully."),
                                Result.IsSuccess());
                            OnDone.ExecuteIfBound(Result.IsSuccess());
                        }));
        });

    // Login in the user 1 to the voice chat system.
    Executor->Then<FLambdaChainedTask>(
        [VoiceChatUser1](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            IVoiceChat *VoiceChat = IVoiceChat::Get();
            *VoiceChatUser1 = VoiceChat->CreateUser();

            FPlatformUserId PlatformUserId =
                Context->Instance(1).GetIdentityInterface()->GetPlatformUserIdFromUniqueNetId(Context->User(1));

            (*VoiceChatUser1)
                ->Login(
                    PlatformUserId,
                    Context->Instance(1).GetIdentityInterface()->GetUniquePlayerId(0)->ToString(),
                    TEXT(""),
                    FOnVoiceChatLoginCompleteDelegate::CreateLambda(
                        [Context, OnDone](const FString &PlayerName, const FVoiceChatResult &Result) {
                            Context->Assert().TestTrue(
                                TEXT("Expected voice chat to login user 1 successfully."),
                                Result.IsSuccess());
                            OnDone.ExecuteIfBound(Result.IsSuccess());
                        }));
        });

    // Set up the voice devices and volumes for user 0.
    Executor->Then<FLambdaChainedTask>(
        [VoiceChatUser0](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            auto OutputInfos = (*VoiceChatUser0)->GetAvailableOutputDeviceInfos();
            auto InputInfos = (*VoiceChatUser0)->GetAvailableInputDeviceInfos();

            // Make sure we actually have a virtual cable driver before we go any further.
            FVoiceChatDeviceInfo *VbCable = OutputInfos.FindByPredicate([](const FVoiceChatDeviceInfo &Info) {
                return Info.DisplayName.Contains("VB-Audio Virtual Cable");
            });
            if (!Context->Assert().TestNotNull(TEXT("Must have the VB-Audio Virtual Cable driver installed!"), VbCable))
            {
                OnDone.ExecuteIfBound(false);
                return;
            }

            FVoiceChatDeviceInfo *Output0 = OutputInfos.FindByPredicate([](const FVoiceChatDeviceInfo &Info) {
                return Info.DisplayName.Contains("VB-Audio Virtual Cable");
            });
            FVoiceChatDeviceInfo *Input0 = InputInfos.FindByPredicate([](const FVoiceChatDeviceInfo &Info) {
                return !Info.DisplayName.Contains("VB-Audio Virtual Cable");
            });

            UE_LOG(LogRedpointEOSTests, Display, TEXT("User 0 is using output device '%s'"), *Output0->DisplayName);
            UE_LOG(LogRedpointEOSTests, Display, TEXT("User 0 is using input device '%s'"), *Input0->DisplayName);

            (*VoiceChatUser0)->SetSetting("EnableAutoGainControl", "false");
            (*VoiceChatUser0)->SetOutputDeviceId(Output0->Id);
            (*VoiceChatUser0)->SetInputDeviceId(Input0->Id);
            (*VoiceChatUser0)->SetAudioInputVolume(100.0);
            (*VoiceChatUser0)->SetAudioOutputVolume(100.0);
            OnDone.ExecuteIfBound(true);
        });

    // Set up the voice devices and volumes for user 1.
    Executor->Then<FLambdaChainedTask>(
        [VoiceChatUser1](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            auto OutputInfos = (*VoiceChatUser1)->GetAvailableOutputDeviceInfos();
            auto InputInfos = (*VoiceChatUser1)->GetAvailableInputDeviceInfos();

            FVoiceChatDeviceInfo *Output1 = OutputInfos.FindByPredicate([](const FVoiceChatDeviceInfo &Info) {
                return !Info.DisplayName.Contains("VB-Audio Virtual Cable");
            });
            FVoiceChatDeviceInfo *Input1 = InputInfos.FindByPredicate([](const FVoiceChatDeviceInfo &Info) {
                return Info.DisplayName.Contains("VB-Audio Virtual Cable");
            });

            UE_LOG(LogRedpointEOSTests, Display, TEXT("User 1 is using output device '%s'"), *Output1->DisplayName);
            UE_LOG(LogRedpointEOSTests, Display, TEXT("User 1 is using input device '%s'"), *Input1->DisplayName);

            (*VoiceChatUser1)->SetSetting("EnableAutoGainControl", "false");
            (*VoiceChatUser1)->SetOutputDeviceId(Output1->Id);
            (*VoiceChatUser1)->SetInputDeviceId(Input1->Id);
            (*VoiceChatUser1)->SetAudioInputVolume(100.0);
            (*VoiceChatUser1)->SetAudioOutputVolume(100.0);
            OnDone.ExecuteIfBound(true);
        });

    // Register the event for when a second user joins the voice lobby created by user 0.
    Executor->Then<FRegisterEventChainedTask<FOnMemberConnectRefDelegate>>(
        "LobbyMemberConnected",
        [](const FChainedTaskContextRef &Context, const FOnMemberConnectRefDelegate &OnEventRaised) {
            return Online::GetLobbyInterface(&Context->Instance(0))
                ->AddOnMemberConnectDelegate_Handle(
                    FOnMemberConnectDelegate::CreateLambda([OnEventRaised](
                                                               const FUniqueNetId &UserId,
                                                               const FOnlineLobbyId &LobbyId,
                                                               const FUniqueNetId &MemberId) {
                        OnEventRaised.ExecuteIfBound(
                            ((const FUniqueNetIdEOS &)UserId).AsShared(),
                            LobbyId.AsShared(),
                            ((const FUniqueNetIdEOS &)MemberId).AsShared());
                    }));
        },
        [](const FChainedTaskContextRef &Context, FDelegateHandle Handle) {
            return Online::GetLobbyInterface(&Context->Instance(0))->ClearOnMemberConnectDelegate_Handle(Handle);
        });

    // Create a voice chat enabled lobby from user 0.
    Executor->Then<FLambdaChainedTask>([CreatedLobbyId](
                                           const FChainedTaskContextRef &Context,
                                           const FLambdaChainedTask::FOnComplete &OnDone) {
        auto Txn = Online::GetLobbyInterface(&Context->Instance(0))->MakeCreateLobbyTransaction(Context->User(0));
        Txn->Capacity = 2;
        Txn->Public = true;
        Txn->Locked = false;
        Txn->SetMetadata.Add(TEXT("RedpointEOS_VoiceChatTest"), true);
        Txn->SetMetadata.Add(TEXT("EOSVoiceChat_Enabled"), true);

        UE_LOG(LogRedpointEOSTests, Display, TEXT("Creating voice enabled lobby from user 0."));

        Online::GetLobbyInterface(&Context->Instance(0))
            ->CreateLobby(
                Context->User(0),
                *Txn,
                FOnLobbyCreateOrConnectComplete::CreateLambda([Context, OnDone, CreatedLobbyId](
                                                                  const FOnlineError &Error,
                                                                  const FUniqueNetId &UserId,
                                                                  const TSharedPtr<class FOnlineLobby> &Lobby) {
                    *CreatedLobbyId = Lobby->Id;
                    Context->Assert().TestTrue(TEXT("Expected lobby to be created successfully."), Error.bSucceeded);
                    if (Error.bSucceeded)
                    {
                        UE_LOG(LogRedpointEOSTests, Display, TEXT("Created voice enabled lobby from user 0."));
                    }
                    OnDone.ExecuteIfBound(Error.bSucceeded);
                }));
    });

    // Join the voice chat enabled lobby from user 1.
    Executor->Then<FLambdaChainedTask>(
        [CreatedLobbyId](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            UE_LOG(LogRedpointEOSTests, Display, TEXT("Connecting to voice enabled lobby from user 1."));
            Online::GetLobbyInterface(&Context->Instance(1))
                ->ConnectLobby(
                    Context->User(1),
                    *(*CreatedLobbyId),
                    FOnLobbyCreateOrConnectComplete::CreateLambda([Context, OnDone](
                                                                      const FOnlineError &Error,
                                                                      const FUniqueNetId &UserId,
                                                                      const TSharedPtr<class FOnlineLobby> &Lobby) {
                        Context->Assert().TestTrue(TEXT("Expected lobby to be joined successfully."), Error.bSucceeded);
                        if (Error.bSucceeded)
                        {
                            UE_LOG(LogRedpointEOSTests, Display, TEXT("Connected to voice enabled lobby from user 1."));
                        }
                        OnDone.ExecuteIfBound(Error.bSucceeded);
                    }));
        });

    // Wait for user 0 to see user 1 joining the lobby.
    Executor->Then<FWaitForEventChainedTask<FOnMemberConnectRefDelegate>>(
        "LobbyMemberConnected",
        10.0f,
        [](const FChainedTaskContextRef &Context,
           const TSharedRef<const FUniqueNetId> &UserId,
           const TSharedRef<const FOnlineLobbyId> &LobbyId,
           const TSharedRef<const FUniqueNetId> &MemberId) {
            return *UserId == Context->User(0) && *MemberId == Context->User(1);
        });

    // Unregister the lobby member connected event.
    Executor->Then<FUnregisterEventChainedTask>("LobbyMemberConnected");

    // Log that the voice chat lobby is now set up correctly.
    Executor->Then<FLambdaChainedTask>(
        [VoiceChatUser0](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            UE_LOG(LogRedpointEOSTests, Display, TEXT("Voice chat enabled lobby is now set up with two users."));
            OnDone.ExecuteIfBound(true);
        });

    // Wait 15 seconds so the developer can confirm that audio is working normally.
    Executor->Then<FDelayChainedTask>(15.0f);
    Executor->Then<FLambdaChainedTask>(
        [VoiceChatUser0](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            UE_LOG(LogRedpointEOSTests, Display, TEXT("Starting mute cycling for the next 30 seconds..."));
            OnDone.ExecuteIfBound(true);
        });

    // Switch mute on and off for the next 30 seconds.
    Executor->Then<FPeriodicLambdaChainedTask>(
        1.0f,
        30,
        [VoiceChatUser0](
            const FChainedTaskContextRef &Context,
            int Iteration,
            const FLambdaChainedTask::FOnComplete &OnDone) {
            (*VoiceChatUser0)->SetAudioInputVolume(((Iteration % 2) == 0) ? 0.0 : 100.0);
            OnDone.ExecuteIfBound(true);
        });

    // Ensure we're unmuted (though we should be).
    Executor->Then<FLambdaChainedTask>(
        [VoiceChatUser0](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            (*VoiceChatUser0)->SetAudioInputVolume(100.0);
            OnDone.ExecuteIfBound(true);
        });

    // Wait 60 seconds for the developer to confirm manually that the bug is reproduced.
    Executor->Then<FLambdaChainedTask>(
        [VoiceChatUser0](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            UE_LOG(
                LogRedpointEOSTests,
                Display,
                TEXT("Stopping mute cycling and letting test run for another 60 seconds..."));
            OnDone.ExecuteIfBound(true);
        });
    Executor->Then<FDelayChainedTask>(60.0f);

    // This ensures that the voice chat users don't get destroyed until the end of the test.
    Executor->Then<FLambdaChainedTask>(
        [VoiceChatUser0,
         VoiceChatUser1](const FChainedTaskContextRef &Context, const FLambdaChainedTask::FOnComplete &OnDone) {
            UE_LOG(LogRedpointEOSTests, Display, TEXT("Voice chat test is now complete."));
            OnDone.ExecuteIfBound(true);
        });

    // Run the test.
    Executor->Execute();
}

} // namespace Manual

} // namespace VoiceChat

} // namespace Redpoint::EOS::Tests
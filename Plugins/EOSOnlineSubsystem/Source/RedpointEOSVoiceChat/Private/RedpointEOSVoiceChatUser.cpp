// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSVoiceChatUser.h"

#include "OnlineSubsystemRedpointEOS/Shared/EOSPlatformUserIdManager.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineSubsystemRedpointEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"
#include "RedpointEOSVoiceChatModule.h"

#define check_loggedin(FuncName, ReturnValue)                                                                          \
    if (!this->Internal_IsLoggedIn())                                                                                  \
    {                                                                                                                  \
        UE_LOG(                                                                                                        \
            LogRedpointEOSVoiceChat,                                                                                           \
            Warning,                                                                                                   \
            TEXT("IVoiceChatUser::%s operation called, but the ::Login function was not called first. This operation " \
                 "will "                                                                                               \
                 "be ignored."),                                                                                       \
            FuncName);                                                                                                 \
        return ReturnValue;                                                                                            \
    }

bool FRedpointEOSVoiceChatUser::Internal_IsLoggedIn() const
{
    return this->VoiceManager.IsValid() && this->LocalUser.IsValid() && this->LoggedInPlayerId.IsValid();
}

FRedpointEOSVoiceChatUser::~FRedpointEOSVoiceChatUser()
{
    // Deregister our event handlers from the LocalUser.
    this->Logout(FOnVoiceChatLogoutCompleteDelegate());
}

void FRedpointEOSVoiceChatUser::SetSetting(const FString &Name, const FString &Value)
{
    check_loggedin(TEXT("SetSetting"), );
    this->LocalUser.Pin()->SetSetting(Name, Value);
}

FString FRedpointEOSVoiceChatUser::GetSetting(const FString &Name)
{
    check_loggedin(TEXT("GetSetting"), TEXT(""));
    return this->LocalUser.Pin()->GetSetting(Name);
}

void FRedpointEOSVoiceChatUser::SetAudioInputVolume(float Volume)
{
    check_loggedin(TEXT("SetAudioInputVolume"), );
    this->LocalUser.Pin()->SetAudioInputVolume(Volume);
}

void FRedpointEOSVoiceChatUser::SetAudioOutputVolume(float Volume)
{
    check_loggedin(TEXT("SetAudioOutputVolume"), );
    this->LocalUser.Pin()->SetAudioOutputVolume(Volume);
}

float FRedpointEOSVoiceChatUser::GetAudioInputVolume() const
{
    check_loggedin(TEXT("GetAudioInputVolume"), 0.0f);
    return this->LocalUser.Pin()->GetAudioInputVolume();
}

float FRedpointEOSVoiceChatUser::GetAudioOutputVolume() const
{
    check_loggedin(TEXT("GetAudioOutputVolume"), 0.0f);
    return this->LocalUser.Pin()->GetAudioOutputVolume();
}

void FRedpointEOSVoiceChatUser::SetAudioInputDeviceMuted(bool bIsMuted)
{
    check_loggedin(TEXT("SetAudioInputDeviceMuted"), );
    this->LocalUser.Pin()->SetAudioInputDeviceMuted(bIsMuted);
}

void FRedpointEOSVoiceChatUser::SetAudioOutputDeviceMuted(bool bIsMuted)
{
    check_loggedin(TEXT("SetAudioOutputDeviceMuted"), );
    this->LocalUser.Pin()->SetAudioOutputDeviceMuted(bIsMuted);
}

bool FRedpointEOSVoiceChatUser::GetAudioInputDeviceMuted() const
{
    check_loggedin(TEXT("GetAudioInputDeviceMuted"), true);
    return this->LocalUser.Pin()->GetAudioInputDeviceMuted();
}

bool FRedpointEOSVoiceChatUser::GetAudioOutputDeviceMuted() const
{
    check_loggedin(TEXT("GetAudioOutputDeviceMuted"), true);
    return this->LocalUser.Pin()->GetAudioOutputDeviceMuted();
}

TArray<FVoiceChatDeviceInfo> FRedpointEOSVoiceChatUser::GetAvailableInputDeviceInfos() const
{
    check_loggedin(TEXT("GetAvailableInputDeviceInfos"), TArray<FVoiceChatDeviceInfo>());

    TArray<FVoiceChatDeviceInfo> Results;
    for (const auto &Entry : this->LocalUser.Pin()->GetAvailableInputDeviceInfos())
    {
        Results.Add(FVoiceChatDeviceInfo{Entry.DisplayName, Entry.Id});
    }
    return Results;
}

TArray<FVoiceChatDeviceInfo> FRedpointEOSVoiceChatUser::GetAvailableOutputDeviceInfos() const
{
    check_loggedin(TEXT("GetAvailableOutputDeviceInfos"), TArray<FVoiceChatDeviceInfo>());

    TArray<FVoiceChatDeviceInfo> Results;
    for (const auto &Entry : this->LocalUser.Pin()->GetAvailableOutputDeviceInfos())
    {
        Results.Add(FVoiceChatDeviceInfo{Entry.DisplayName, Entry.Id});
    }
    return Results;
}

void FRedpointEOSVoiceChatUser::SetInputDeviceId(const FString &InputDeviceId)
{
    check_loggedin(TEXT("SetInputDeviceId"), );
    this->LocalUser.Pin()->SetInputDeviceId(InputDeviceId);
}

void FRedpointEOSVoiceChatUser::SetOutputDeviceId(const FString &OutputDeviceId)
{
    check_loggedin(TEXT("SetOutputDeviceId"), );
    this->LocalUser.Pin()->SetOutputDeviceId(OutputDeviceId);
}

FVoiceChatDeviceInfo FRedpointEOSVoiceChatUser::GetInputDeviceInfo() const
{
    check_loggedin(TEXT("GetInputDeviceInfo"), FVoiceChatDeviceInfo());
    auto Value = this->LocalUser.Pin()->GetInputDeviceInfo();
    return FVoiceChatDeviceInfo{Value.DisplayName, Value.Id};
}

FVoiceChatDeviceInfo FRedpointEOSVoiceChatUser::GetOutputDeviceInfo() const
{
    check_loggedin(TEXT("GetOutputDeviceInfo"), FVoiceChatDeviceInfo());
    auto Value = this->LocalUser.Pin()->GetOutputDeviceInfo();
    return FVoiceChatDeviceInfo{Value.DisplayName, Value.Id};
}

FVoiceChatDeviceInfo FRedpointEOSVoiceChatUser::GetDefaultInputDeviceInfo() const
{
    check_loggedin(TEXT("GetDefaultInputDeviceInfo"), FVoiceChatDeviceInfo());
    auto Value = this->LocalUser.Pin()->GetDefaultInputDeviceInfo();
    return FVoiceChatDeviceInfo{Value.DisplayName, Value.Id};
}

FVoiceChatDeviceInfo FRedpointEOSVoiceChatUser::GetDefaultOutputDeviceInfo() const
{
    check_loggedin(TEXT("GetDefaultOutputDeviceInfo"), FVoiceChatDeviceInfo());
    auto Value = this->LocalUser.Pin()->GetDefaultOutputDeviceInfo();
    return FVoiceChatDeviceInfo{Value.DisplayName, Value.Id};
}

void FRedpointEOSVoiceChatUser::Login(
    FPlatformUserId PlatformId,
    const FString &PlayerName,
    const FString &Credentials,
    const FOnVoiceChatLoginCompleteDelegate &Delegate)
{
    auto PlayerInfo = FEOSPlatformUserIdManager::FindByPlatformId(PlatformId);
    if (!PlayerInfo.IsSet())
    {
        Delegate.ExecuteIfBound(
            PlayerName,
            FVoiceChatResult(
                EVoiceChatResult::CredentialsInvalid,
                TEXT("PlatformIdInvalid"),
                TEXT("Platform ID provided to IVoiceChatUser::Login doesn't match any user signed into any local "
                     "subsystem.")));
        return;
    }

    if (PlayerName != PlayerInfo.GetValue().Value->ToString())
    {
        Delegate.ExecuteIfBound(
            PlayerName,
            FVoiceChatResult(
                EVoiceChatResult::CredentialsInvalid,
                TEXT("PlayerNameInvalid"),
                TEXT("Player name provided to IVoiceChatUser::Login must match the unique net ID of the local user. "
                     "All player name parameters in the voice chat system are unique net IDs converted to strings.")));
        return;
    }

    auto OSS = PlayerInfo.GetValue().Key;
    this->VoiceManager = OSS->GetVoiceManager();
    this->LocalUser = OSS->GetVoiceManager()->GetLocalUser(*PlayerInfo.GetValue().Value);

	// @note: Perform asynchronous operations to initialise the RTC cache inside
	// the EOS SDK. If we don't do this before returning from Login, and then we try
	// to use EOS SDK APIs in a synchronous manner, we'll get frame hitches.
	this->LocalUser.Pin()->PostLoginInit(FEOSVoiceManagerLocalUserPostLoginComplete::CreateLambda(
        [WeakThis = GetWeakThis(this), Delegate, PlayerInfo, PlayerName]() {
            if (auto This = PinWeakThis(WeakThis))
            {
                This->LoggedInPlayerId = PlayerInfo.GetValue().Value;
                checkf(This->Internal_IsLoggedIn(), TEXT("Must be logged in after successfully obtaining local user!"));

                This->OnVoiceChatAvailableAudioDevicesChangedDelegateHandle =
                    This->LocalUser.Pin()->OnVoiceChatAvailableAudioDevicesChanged().AddLambda(
                        [WeakThis = GetWeakThis(This)]() {
                            if (auto This = PinWeakThis(WeakThis))
                            {
                                This->OnVoiceChatAvailableAudioDevicesChanged().Broadcast();
                            }
                        });
                This->OnVoiceChatChannelJoinedDelegateHandle =
                    This->LocalUser.Pin()->OnVoiceChatChannelJoined().AddLambda(
                        [WeakThis = GetWeakThis(This)](const FString &ChannelName) {
                            if (auto This = PinWeakThis(WeakThis))
                            {
                                This->OnVoiceChatChannelJoined().Broadcast(ChannelName);
                            }
                        });
                This->OnVoiceChatChannelExitedDelegateHandle =
                    This->LocalUser.Pin()->OnVoiceChatChannelExited().AddLambda(
                        [WeakThis = GetWeakThis(This)](const FString &ChannelName, const FVoiceChatResult &Reason) {
                            if (auto This = PinWeakThis(WeakThis))
                            {
                                This->OnVoiceChatChannelExited().Broadcast(ChannelName, Reason);
                            }
                        });
                This->OnVoiceChatCallStatsUpdatedDelegateHandle =
                    This->LocalUser.Pin()->OnVoiceChatCallStatsUpdated().AddLambda(
                        [WeakThis = GetWeakThis(This)](const FVoiceChatCallStats &CallStats) {
                            if (auto This = PinWeakThis(WeakThis))
                            {
                                This->OnVoiceChatCallStatsUpdated().Broadcast(CallStats);
                            }
                        });
                This->OnVoiceChatPlayerAddedDelegateHandle = This->LocalUser.Pin()->OnVoiceChatPlayerAdded().AddLambda(
                    [WeakThis = GetWeakThis(This)](const FString &ChannelName, const FString &PlayerName) {
                        if (auto This = PinWeakThis(WeakThis))
                        {
                            This->OnVoiceChatPlayerAdded().Broadcast(ChannelName, PlayerName);
                        }
                    });
                This->OnVoiceChatPlayerRemovedDelegateHandle =
                    This->LocalUser.Pin()->OnVoiceChatPlayerRemoved().AddLambda(
                        [WeakThis = GetWeakThis(This)](const FString &ChannelName, const FString &PlayerName) {
                            if (auto This = PinWeakThis(WeakThis))
                            {
                                This->OnVoiceChatPlayerRemoved().Broadcast(ChannelName, PlayerName);
                            }
                        });
                This->OnVoiceChatPlayerTalkingUpdatedDelegateHandle =
                    This->LocalUser.Pin()->OnVoiceChatPlayerTalkingUpdated().AddLambda(
                        [WeakThis = GetWeakThis(This)](const FString &ChannelName, const FString &PlayerName, bool bIsTalking) {
                            if (auto This = PinWeakThis(WeakThis))
                            {
                                This->OnVoiceChatPlayerTalkingUpdated().Broadcast(ChannelName, PlayerName, bIsTalking);
                            }
                        });
                This->OnVoiceChatPlayerMuteUpdatedDelegateHandle =
                    This->LocalUser.Pin()->OnVoiceChatPlayerMuteUpdated().AddLambda(
                        [WeakThis =
                             GetWeakThis(This)](const FString &ChannelName, const FString &PlayerName, bool bIsMuted) {
                            if (auto This = PinWeakThis(WeakThis))
                            {
                                This->OnVoiceChatPlayerMuteUpdated().Broadcast(ChannelName, PlayerName, bIsMuted);
                            }
                        });
                This->OnVoiceChatPlayerVolumeUpdatedDelegateHandle =
                    This->LocalUser.Pin()->OnVoiceChatPlayerVolumeUpdated().AddLambda(
                        [WeakThis =
                             GetWeakThis(This)](const FString &ChannelName, const FString &PlayerName, float Volume) {
                            if (auto This = PinWeakThis(WeakThis))
                            {
                                This->OnVoiceChatPlayerVolumeUpdated().Broadcast(ChannelName, PlayerName, Volume);
                            }
                        });

                Delegate.ExecuteIfBound(PlayerName, FVoiceChatResult(EVoiceChatResult::Success));
            }
        }));
}

void FRedpointEOSVoiceChatUser::Logout(const FOnVoiceChatLogoutCompleteDelegate &Delegate)
{
    if (!this->LoggedInPlayerId.IsValid())
    {
        return;
    }

    if (this->LocalUser.IsValid())
    {
        this->LocalUser.Pin()->OnVoiceChatAvailableAudioDevicesChanged().Remove(
            this->OnVoiceChatAvailableAudioDevicesChangedDelegateHandle);
        this->LocalUser.Pin()->OnVoiceChatChannelJoined().Remove(this->OnVoiceChatChannelJoinedDelegateHandle);
        this->LocalUser.Pin()->OnVoiceChatChannelExited().Remove(this->OnVoiceChatChannelExitedDelegateHandle);
        this->LocalUser.Pin()->OnVoiceChatCallStatsUpdated().Remove(this->OnVoiceChatCallStatsUpdatedDelegateHandle);
        this->LocalUser.Pin()->OnVoiceChatPlayerAdded().Remove(this->OnVoiceChatPlayerAddedDelegateHandle);
        this->LocalUser.Pin()->OnVoiceChatPlayerRemoved().Remove(this->OnVoiceChatPlayerRemovedDelegateHandle);
        this->LocalUser.Pin()->OnVoiceChatPlayerTalkingUpdated().Remove(
            this->OnVoiceChatPlayerTalkingUpdatedDelegateHandle);
        this->LocalUser.Pin()->OnVoiceChatPlayerMuteUpdated().Remove(this->OnVoiceChatPlayerMuteUpdatedDelegateHandle);
        this->LocalUser.Pin()->OnVoiceChatPlayerVolumeUpdated().Remove(
            this->OnVoiceChatPlayerVolumeUpdatedDelegateHandle);
    }

    auto PlayerName = this->LoggedInPlayerId->ToString();
    this->LoggedInPlayerId.Reset();
    this->VoiceManager.Reset();
    this->LocalUser.Reset();
    Delegate.ExecuteIfBound(PlayerName, FVoiceChatResult(EVoiceChatResult::Success));
}

bool FRedpointEOSVoiceChatUser::IsLoggingIn() const
{
    // Login and Logout are not asynchronous, so this is never the case.
    return false;
}

bool FRedpointEOSVoiceChatUser::IsLoggedIn() const
{
    return this->Internal_IsLoggedIn();
}

FString FRedpointEOSVoiceChatUser::GetLoggedInPlayerName() const
{
    check_loggedin(TEXT("GetLoggedInPlayerName"), TEXT(""));
    return this->LoggedInPlayerId->ToString();
}

void FRedpointEOSVoiceChatUser::BlockPlayers(const TArray<FString> &PlayerNames)
{
    check_loggedin(TEXT("BlockPlayers"), );
    this->LocalUser.Pin()->BlockPlayers(PlayerNames);
}

void FRedpointEOSVoiceChatUser::UnblockPlayers(const TArray<FString> &PlayerNames)
{
    check_loggedin(TEXT("UnblockPlayers"), );
    this->LocalUser.Pin()->UnblockPlayers(PlayerNames);
}

void FRedpointEOSVoiceChatUser::JoinChannel(
    const FString &ChannelName,
    const FString &ChannelCredentials,
    EVoiceChatChannelType ChannelType,
    const FOnVoiceChatChannelJoinCompleteDelegate &Delegate,
    TOptional<FVoiceChatChannel3dProperties> Channel3dProperties)
{
    check_loggedin(TEXT("JoinChannel"), );
    this->LocalUser.Pin()->JoinChannel(ChannelName, ChannelCredentials, ChannelType, Delegate, Channel3dProperties);
}

void FRedpointEOSVoiceChatUser::LeaveChannel(
    const FString &ChannelName,
    const FOnVoiceChatChannelLeaveCompleteDelegate &Delegate)
{
    check_loggedin(TEXT("LeaveChannel"), );
    this->LocalUser.Pin()->LeaveChannel(ChannelName, Delegate);
}

void FRedpointEOSVoiceChatUser::Set3DPosition(
    const FString &ChannelName,
    const FVector &SpeakerPosition,
    const FVector &ListenerPosition,
    const FVector &ListenerForwardDirection,
    const FVector &ListenerUpDirection)
{
    check_loggedin(TEXT("Set3DPosition"), );
    this->LocalUser.Pin()
        ->Set3DPosition(ChannelName, SpeakerPosition, ListenerPosition, ListenerForwardDirection, ListenerUpDirection);
}

TArray<FString> FRedpointEOSVoiceChatUser::GetChannels() const
{
    check_loggedin(TEXT("GetChannels"), TArray<FString>());
    return this->LocalUser.Pin()->GetChannels();
}

TArray<FString> FRedpointEOSVoiceChatUser::GetPlayersInChannel(const FString &ChannelName) const
{
    check_loggedin(TEXT("GetPlayersInChannel"), TArray<FString>());
    return this->LocalUser.Pin()->GetPlayersInChannel(ChannelName);
}

EVoiceChatChannelType FRedpointEOSVoiceChatUser::GetChannelType(const FString &ChannelName) const
{
    check_loggedin(TEXT("GetChannelType"), EVoiceChatChannelType::NonPositional);
    return this->LocalUser.Pin()->GetChannelType(ChannelName);
}

bool FRedpointEOSVoiceChatUser::IsPlayerTalking(const FString &PlayerName) const
{
    check_loggedin(TEXT("IsPlayerTalking"), false);
    return this->LocalUser.Pin()->IsPlayerTalking(PlayerName);
}

void FRedpointEOSVoiceChatUser::SetPlayerMuted(const FString &PlayerName, bool bMuted)
{
    check_loggedin(TEXT("SetPlayerMuted"), );
    this->LocalUser.Pin()->SetPlayerMuted(PlayerName, bMuted);
}

bool FRedpointEOSVoiceChatUser::IsPlayerMuted(const FString &PlayerName) const
{
    check_loggedin(TEXT("IsPlayerMuted"), false);
    return this->LocalUser.Pin()->IsPlayerMuted(PlayerName);
}

#if defined(UE_5_0_OR_LATER)

void FRedpointEOSVoiceChatUser::SetChannelPlayerMuted(
    const FString &ChannelName,
    const FString &PlayerName,
    bool bAudioMuted)
{
    check_loggedin(TEXT("SetChannelPlayerMuted"), );
    // TODO: Support per-channel mute.
    this->SetPlayerMuted(PlayerName, bAudioMuted);
}

bool FRedpointEOSVoiceChatUser::IsChannelPlayerMuted(const FString &ChannelName, const FString &PlayerName) const
{
    check_loggedin(TEXT("IsChannelPlayerMuted"), false);
    // TODO: Support per-channel mute.
    return this->IsPlayerMuted(PlayerName);
}

#endif // #if defined(UE_5_0_OR_LATER)

void FRedpointEOSVoiceChatUser::SetPlayerVolume(const FString &PlayerName, float Volume)
{
    check_loggedin(TEXT("SetPlayerVolume"), );
    this->LocalUser.Pin()->SetPlayerVolume(PlayerName, Volume);
}

float FRedpointEOSVoiceChatUser::GetPlayerVolume(const FString &PlayerName) const
{
    check_loggedin(TEXT("GetPlayerVolume"), false);
    return this->LocalUser.Pin()->GetPlayerVolume(PlayerName);
}

void FRedpointEOSVoiceChatUser::TransmitToAllChannels()
{
    check_loggedin(TEXT("TransmitToAllChannels"), );
    this->LocalUser.Pin()->TransmitToAllChannels();
}

void FRedpointEOSVoiceChatUser::TransmitToNoChannels()
{
    check_loggedin(TEXT("TransmitToNoChannels"), );
    this->LocalUser.Pin()->TransmitToNoChannels();
}

#if defined(UE_5_3_OR_LATER)
void FRedpointEOSVoiceChatUser::TransmitToSpecificChannels(const TSet<FString> &ChannelNames)
{
    check_loggedin(TEXT("TransmitToSpecificChannels"), );
    this->LocalUser.Pin()->TransmitToSpecificChannels(ChannelNames);
}
#else
void FRedpointEOSVoiceChatUser::TransmitToSpecificChannel(const FString &ChannelName)
{
    check_loggedin(TEXT("TransmitToSpecificChannel"), );
    this->LocalUser.Pin()->TransmitToSpecificChannel(ChannelName);
}
#endif

EVoiceChatTransmitMode FRedpointEOSVoiceChatUser::GetTransmitMode() const
{
    check_loggedin(TEXT("GetTransmitMode"), EVoiceChatTransmitMode::None);
    return this->LocalUser.Pin()->GetTransmitMode();
}

#if defined(UE_5_3_OR_LATER)
TSet<FString> FRedpointEOSVoiceChatUser::GetTransmitChannels() const
{
    check_loggedin(TEXT("GetTransmitChannels"), TSet<FString>());
    return this->LocalUser.Pin()->GetTransmitChannels();
}
#else
FString FRedpointEOSVoiceChatUser::GetTransmitChannel() const
{
    check_loggedin(TEXT("GetTransmitChannel"), TEXT(""));
    return this->LocalUser.Pin()->GetTransmitChannel();
}
#endif

FDelegateHandle FRedpointEOSVoiceChatUser::StartRecording(
    const FOnVoiceChatRecordSamplesAvailableDelegate::FDelegate &Delegate)
{
    UE_LOG(LogRedpointEOSVoiceChat, Error, TEXT("IVoiceChatUser::StartRecording is not yet supported."));
    return FDelegateHandle();
}

void FRedpointEOSVoiceChatUser::StopRecording(FDelegateHandle Handle)
{
    UE_LOG(LogRedpointEOSVoiceChat, Error, TEXT("IVoiceChatUser::StopRecording is not yet supported."));
}

FString FRedpointEOSVoiceChatUser::InsecureGetLoginToken(const FString &PlayerName)
{
    UE_LOG(LogRedpointEOSVoiceChat, Error, TEXT("IVoiceChatUser::InsecureGetLoginToken is not supported."));
    return TEXT("");
}

FString FRedpointEOSVoiceChatUser::InsecureGetJoinToken(
    const FString &ChannelName,
    EVoiceChatChannelType ChannelType,
    TOptional<FVoiceChatChannel3dProperties> Channel3dProperties)
{
    UE_LOG(LogRedpointEOSVoiceChat, Error, TEXT("IVoiceChatUser::InsecureGetJoinToken is not supported."));
    return TEXT("");
}

FOnVoiceChatAvailableAudioDevicesChangedDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatAvailableAudioDevicesChanged()
{
    return this->OnVoiceChatAvailableAudioDevicesChangedDelegate;
}

FOnVoiceChatLoggedInDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatLoggedIn()
{
    return this->OnVoiceChatLoggedInDelegate;
}

FOnVoiceChatLoggedOutDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatLoggedOut()
{
    return this->OnVoiceChatLoggedOutDelegate;
}

FOnVoiceChatChannelJoinedDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatChannelJoined()
{
    return this->OnVoiceChatChannelJoinedDelegate;
}

FOnVoiceChatChannelExitedDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatChannelExited()
{
    return this->OnVoiceChatChannelExitedDelegate;
}

FOnVoiceChatCallStatsUpdatedDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatCallStatsUpdated()
{
    return this->OnVoiceChatCallStatsUpdatedDelegate;
}

FOnVoiceChatPlayerAddedDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatPlayerAdded()
{
    return this->OnVoiceChatPlayerAddedDelegate;
}

FOnVoiceChatPlayerRemovedDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatPlayerRemoved()
{
    return this->OnVoiceChatPlayerRemovedDelegate;
}

FOnVoiceChatPlayerTalkingUpdatedDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatPlayerTalkingUpdated()
{
    return this->OnVoiceChatPlayerTalkingUpdatedDelegate;
}

FOnVoiceChatPlayerMuteUpdatedDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatPlayerMuteUpdated()
{
    return this->OnVoiceChatPlayerMuteUpdatedDelegate;
}

FOnVoiceChatPlayerVolumeUpdatedDelegate &FRedpointEOSVoiceChatUser::OnVoiceChatPlayerVolumeUpdated()
{
    return this->OnVoiceChatPlayerVolumeUpdatedDelegate;
}

FDelegateHandle FRedpointEOSVoiceChatUser::RegisterOnVoiceChatAfterCaptureAudioReadDelegate(
    const FOnVoiceChatAfterCaptureAudioReadDelegate::FDelegate &Delegate)
{
    return this->OnVoiceChatAfterCaptureAudioReadDelegate.Add(Delegate);
}

void FRedpointEOSVoiceChatUser::UnregisterOnVoiceChatAfterCaptureAudioReadDelegate(FDelegateHandle Handle)
{
    this->OnVoiceChatAfterCaptureAudioReadDelegate.Remove(Handle);
}

FDelegateHandle FRedpointEOSVoiceChatUser::RegisterOnVoiceChatBeforeCaptureAudioSentDelegate(
    const FOnVoiceChatBeforeCaptureAudioSentDelegate::FDelegate &Delegate)
{
    return this->OnVoiceChatBeforeCaptureAudioSentDelegate.Add(Delegate);
}

void FRedpointEOSVoiceChatUser::UnregisterOnVoiceChatBeforeCaptureAudioSentDelegate(FDelegateHandle Handle)
{
    this->OnVoiceChatBeforeCaptureAudioSentDelegate.Remove(Handle);
}

FDelegateHandle FRedpointEOSVoiceChatUser::RegisterOnVoiceChatBeforeRecvAudioRenderedDelegate(
    const FOnVoiceChatBeforeRecvAudioRenderedDelegate::FDelegate &Delegate)
{
    return this->OnVoiceChatBeforeRecvAudioRenderedDelegate.Add(Delegate);
}

void FRedpointEOSVoiceChatUser::UnregisterOnVoiceChatBeforeRecvAudioRenderedDelegate(FDelegateHandle Handle)
{
    this->OnVoiceChatBeforeRecvAudioRenderedDelegate.Remove(Handle);
}
// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Shared/VoiceChat/VoiceManagerLocalUser.h"

#include "OnlineSubsystemRedpointEOS/Private/VoiceChat/Tasks/SetAudioInputSettingsVoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Private/VoiceChat/Tasks/SetAudioInputVolumeVoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Private/VoiceChat/Tasks/SetAudioOutputSettingsVoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Private/VoiceChat/Tasks/SetAudioOutputVolumeVoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Private/VoiceChat/Tasks/UpdateSendingVoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Private/VoiceChat/Tasks/VoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Public/EOSError.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSErrorConv.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/MultiOperation.h"
#include "OnlineSubsystemRedpointEOS/Shared/VoiceChat/VoiceManager.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"
#include "RedpointEOSConfig/Config.h"

#if EOS_HAS_AUTHENTICATION

FEOSVoiceManagerLocalUser::FEOSVoiceManagerLocalUserJoinedChannel::FEOSVoiceManagerLocalUserJoinedChannel(
    const TSharedRef<FEOSVoiceManagerLocalUser> &InOwner,
    EOS_HRTC InRTC,
    EOS_HRTCAudio InRTCAudio,
    const FString &InRoomName,
    EVoiceChatChannelType InChannelType)
    : Owner(InOwner)
    , EOSRTC(InRTC)
    , EOSRTCAudio(InRTCAudio)
    , RoomName(InRoomName)
    , RoomNameStr(nullptr)
    , ChannelType(InChannelType)
    , Participants()
    , OnDisconnected()
    , OnParticipantStatusChanged()
    , OnParticipantUpdated()
    , OnAudioInputState()
    , OnAudioOutputState()
{
    verify(EOSString_AnsiUnlimited::AllocateToCharBuffer(InRoomName, this->RoomNameStr) == EOS_EResult::EOS_Success);
}

void FEOSVoiceManagerLocalUser::FEOSVoiceManagerLocalUserJoinedChannel::RegisterEvents()
{
    EOS_RTC_AddNotifyDisconnectedOptions DisconnectOpts = {};
    DisconnectOpts.ApiVersion = EOS_RTC_ADDNOTIFYDISCONNECTED_API_LATEST;
    DisconnectOpts.LocalUserId = this->Owner->LocalUserId->GetProductUserId();
    DisconnectOpts.RoomName = this->RoomNameStr;
    this->OnDisconnected =
        EOSRegisterEvent<EOS_HRTC, EOS_RTC_AddNotifyDisconnectedOptions, EOS_RTC_DisconnectedCallbackInfo>(
            this->EOSRTC,
            &DisconnectOpts,
            EOS_RTC_AddNotifyDisconnected,
            EOS_RTC_RemoveNotifyDisconnected,
            [WeakThis = GetWeakThis(this)](const EOS_RTC_DisconnectedCallbackInfo *Data) {
                if (auto This = PinWeakThis(WeakThis))
                {
                    if (Data->ResultCode == EOS_EResult::EOS_Success)
                    {
                        // Room left because of a call to LeaveRoom or because an RTC-enabled lobby was left.
                        This->Owner->OnVoiceChatChannelExited().Broadcast(
                            This->RoomName,
                            FVoiceChatResult(EVoiceChatResult::Success));
                        This->Owner->JoinedChannels.Remove(This->RoomName);
                    }
                    else if (Data->ResultCode == EOS_EResult::EOS_NoConnection)
                    // NOLINTNEXTLINE(bugprone-branch-clone)
                    {
                        // Temporary interruption.
                        // @todo: Will EOS automatically reconnect here?
                    }
                    else if (Data->ResultCode == EOS_EResult::EOS_RTC_UserKicked)
                    {
                        // User was kicked from the RTC lobby.
                        This->Owner->OnVoiceChatChannelExited().Broadcast(
                            This->RoomName,
                            FVoiceChatResult(
                                EVoiceChatResult::NotPermitted,
                                TEXT("KickedByServer"),
                                TEXT("You were kicked from voice chat by the server.")));
                        This->Owner->JoinedChannels.Remove(This->RoomName);
                    }
                    else if (Data->ResultCode == EOS_EResult::EOS_ServiceFailure)
                    {
                        // Temporary interruption.
                        // @todo: Will EOS automatically reconnect here?
                    }
                    else
                    {
                        // Unknown.
                        // @todo: Are we actually disconnected from the room here?
                    }
                }
            });

    EOS_RTC_AddNotifyParticipantStatusChangedOptions StatusOpts = {};
    StatusOpts.ApiVersion = EOS_RTC_ADDNOTIFYPARTICIPANTSTATUSCHANGED_API_LATEST;
    StatusOpts.LocalUserId = this->Owner->LocalUserId->GetProductUserId();
    StatusOpts.RoomName = this->RoomNameStr;
    this->OnParticipantStatusChanged = EOSRegisterEvent<
        EOS_HRTC,
        EOS_RTC_AddNotifyParticipantStatusChangedOptions,
        EOS_RTC_ParticipantStatusChangedCallbackInfo>(
        this->EOSRTC,
        &StatusOpts,
        EOS_RTC_AddNotifyParticipantStatusChanged,
        EOS_RTC_RemoveNotifyParticipantStatusChanged,
        [WeakThis = GetWeakThis(this)](const EOS_RTC_ParticipantStatusChangedCallbackInfo *Data) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (Data->ParticipantStatus == EOS_ERTCParticipantStatus::EOS_RTCPS_Joined)
                {
                    TSharedRef<const FUniqueNetIdEOS> RemoteUserId = MakeShared<FUniqueNetIdEOS>(Data->ParticipantId);
                    // @todo: Grab metadata and find some way of surfacing it...
                    This->Participants.Add(
                        *RemoteUserId,
                        MakeShared<FEOSVoiceManagerLocalUserRemoteUser>(RemoteUserId));
                    This->Owner->OnVoiceChatPlayerAdded().Broadcast(This->RoomName, RemoteUserId->ToString());
                }
                else if (Data->ParticipantStatus == EOS_ERTCParticipantStatus::EOS_RTCPS_Left)
                {
                    TSharedRef<const FUniqueNetIdEOS> RemoteUserId = MakeShared<FUniqueNetIdEOS>(Data->ParticipantId);
                    This->Participants.Remove(*RemoteUserId);
                    This->Owner->OnVoiceChatPlayerRemoved().Broadcast(This->RoomName, RemoteUserId->ToString());
                }
            }
        });

    EOS_RTCAudio_AddNotifyParticipantUpdatedOptions UpdatedOpts = {};
    UpdatedOpts.ApiVersion = EOS_RTCAUDIO_ADDNOTIFYPARTICIPANTUPDATED_API_LATEST;
    UpdatedOpts.LocalUserId = this->Owner->LocalUserId->GetProductUserId();
    UpdatedOpts.RoomName = this->RoomNameStr;
    this->OnParticipantUpdated = EOSRegisterEvent<
        EOS_HRTCAudio,
        EOS_RTCAudio_AddNotifyParticipantUpdatedOptions,
        EOS_RTCAudio_ParticipantUpdatedCallbackInfo>(
        this->EOSRTCAudio,
        &UpdatedOpts,
        EOS_RTCAudio_AddNotifyParticipantUpdated,
        EOS_RTCAudio_RemoveNotifyParticipantUpdated,
        [WeakThis = GetWeakThis(this)](const EOS_RTCAudio_ParticipantUpdatedCallbackInfo *Data) {
            if (auto This = PinWeakThis(WeakThis))
            {
                TSharedRef<const FUniqueNetIdEOS> RemoteUserId = MakeShared<FUniqueNetIdEOS>(Data->ParticipantId);
                if (This->Participants.Contains(*RemoteUserId))
                {
                    auto &RemoteUser = This->Participants[*RemoteUserId];
                    bool bSpeaking = Data->bSpeaking == EOS_TRUE;
                    if (RemoteUser->bIsTalking != bSpeaking)
                    {
                        RemoteUser->bIsTalking = bSpeaking;
                        This->Owner->OnVoiceChatPlayerTalkingUpdated().Broadcast(
                            This->RoomName,
                            RemoteUserId->ToString(),
                            RemoteUser->bIsTalking);
                    }
                    if (Redpoint::EOS::Config::ApiVersionIsAtLeast(
                            *This->Owner->VoiceManager->Config,
                            EEOSApiVersion::v2023_10_27))
                    {
                        // As of 2023-10-27, we no longer sync bIsMuted based on the remote mute status.
                    }
                    else
                    {
                        bool bIsMuted = Data->AudioStatus != EOS_ERTCAudioStatus::EOS_RTCAS_Enabled;
                        if (RemoteUser->bIsMuted != bIsMuted)
                        {
                            FString AudioStatusString = TEXT("Unknown");
                            switch (Data->AudioStatus)
                            {
                            case EOS_ERTCAudioStatus::EOS_RTCAS_Enabled:
                                AudioStatusString = TEXT("Enabled");
                                break;
                            case EOS_ERTCAudioStatus::EOS_RTCAS_Disabled:
                                AudioStatusString = TEXT("Disabled");
                                break;
                            case EOS_ERTCAudioStatus::EOS_RTCAS_AdminDisabled:
                                AudioStatusString = TEXT("AdminDisabled");
                                break;
                            case EOS_ERTCAudioStatus::EOS_RTCAS_NotListeningDisabled:
                                AudioStatusString = TEXT("NotListeningDisabled");
                                break;
                            case EOS_ERTCAudioStatus::EOS_RTCAS_Unsupported:
                                AudioStatusString = TEXT("Unsupported");
                                break;
                            }
                            UE_LOG(
                                LogRedpointEOS,
                                Verbose,
                                TEXT("Voice chat participant status updated. Channel: '%s', Player: '%s', Audio "
                                     "Status: '%s'"),
                                *This->RoomName,
                                *RemoteUserId->ToString(),
                                *AudioStatusString);

                            RemoteUser->bIsMuted = bIsMuted;
                            This->Owner->OnVoiceChatPlayerMuteUpdated().Broadcast(
                                This->RoomName,
                                RemoteUserId->ToString(),
                                bIsMuted);
                        }
                    }
                }
            }
        });

    EOS_RTCAudio_AddNotifyAudioInputStateOptions InputStateOpts = {};
    InputStateOpts.ApiVersion = EOS_RTCAUDIO_ADDNOTIFYAUDIOINPUTSTATE_API_LATEST;
    InputStateOpts.LocalUserId = this->Owner->LocalUserId->GetProductUserId();
    InputStateOpts.RoomName = this->RoomNameStr;
    this->OnAudioInputState = EOSRegisterEvent<
        EOS_HRTCAudio,
        EOS_RTCAudio_AddNotifyAudioInputStateOptions,
        EOS_RTCAudio_AudioInputStateCallbackInfo>(
        this->EOSRTCAudio,
        &InputStateOpts,
        EOS_RTCAudio_AddNotifyAudioInputState,
        EOS_RTCAudio_RemoveNotifyAudioInputState,
        [WeakThis = GetWeakThis(this)](const EOS_RTCAudio_AudioInputStateCallbackInfo *Data) {
            if (auto This = PinWeakThis(WeakThis))
            {
            }
        });

    EOS_RTCAudio_AddNotifyAudioOutputStateOptions OutputStateOpts = {};
    OutputStateOpts.ApiVersion = EOS_RTCAUDIO_ADDNOTIFYAUDIOOUTPUTSTATE_API_LATEST;
    OutputStateOpts.LocalUserId = this->Owner->LocalUserId->GetProductUserId();
    OutputStateOpts.RoomName = this->RoomNameStr;
    this->OnAudioOutputState = EOSRegisterEvent<
        EOS_HRTCAudio,
        EOS_RTCAudio_AddNotifyAudioOutputStateOptions,
        EOS_RTCAudio_AudioOutputStateCallbackInfo>(
        this->EOSRTCAudio,
        &OutputStateOpts,
        EOS_RTCAudio_AddNotifyAudioOutputState,
        EOS_RTCAudio_RemoveNotifyAudioOutputState,
        [WeakThis = GetWeakThis(this)](const EOS_RTCAudio_AudioOutputStateCallbackInfo *Data) {
            if (auto This = PinWeakThis(WeakThis))
            {
            }
        });
}

TSharedRef<FEOSVoiceManagerLocalUser::FEOSVoiceManagerLocalUserJoinedChannel> FEOSVoiceManagerLocalUser::
    FEOSVoiceManagerLocalUserJoinedChannel::NewDedicated(
        const TSharedRef<FEOSVoiceManagerLocalUser> &InOwner,
        EOS_HRTC InRTC,
        EOS_HRTCAudio InRTCAudio,
        const FString &InRoomName,
        EVoiceChatChannelType InChannelType)
{
    TSharedRef<FEOSVoiceManagerLocalUserJoinedChannel> Channel = MakeShareable(
        new FEOSVoiceManagerLocalUserJoinedChannel(InOwner, InRTC, InRTCAudio, InRoomName, InChannelType));
    Channel->RegisterEvents();
    return Channel;
}

TSharedRef<FEOSVoiceManagerLocalUser::FEOSVoiceManagerLocalUserJoinedChannel> FEOSVoiceManagerLocalUser::
    FEOSVoiceManagerLocalUserJoinedChannel::NewLobby(
        const TSharedRef<FEOSVoiceManagerLocalUser> &InOwner,
        EOS_HRTC InRTC,
        EOS_HRTCAudio InRTCAudio,
        const FString &InRoomName,
        const TSharedRef<const FOnlinePartyIdEOS> &InLobbyId,
        EVoiceChatChannelType InChannelType)
{
    TSharedRef<FEOSVoiceManagerLocalUserJoinedChannel> Channel = MakeShareable(
        new FEOSVoiceManagerLocalUserJoinedChannel(InOwner, InRTC, InRTCAudio, InRoomName, InChannelType));
    Channel->LobbyId = InLobbyId;
    Channel->RegisterEvents();
    return Channel;
}

FEOSVoiceManagerLocalUser::FEOSVoiceManagerLocalUserJoinedChannel::~FEOSVoiceManagerLocalUserJoinedChannel()
{
    EOSString_AnsiUnlimited::FreeFromCharBuffer(this->RoomNameStr);
}

bool FEOSVoiceManagerLocalUser::GetDefaultedSetting(const FString &InSettingName, bool InDefault)
{
    if (this->Settings.Contains(InSettingName))
    {
        return this->Settings[InSettingName] == "true";
    }
    else
    {
        return InDefault;
    }
}

void FEOSVoiceManagerLocalUser::PerformSynchronisationToEOS()
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSVoiceChatUserSyncPerformSynchronisation);

    UE_LOG(LogRedpointEOSVoiceChat, Verbose, TEXT("Synchronising voice chat state with EOS..."));

    checkf(
        !this->bIsSynchronising,
        TEXT("PerformSynchronisationToEOS called while bIsSynchronising is true; this is a bug!"));

    this->bIsSynchronising = true;
    auto SyncMode = this->PendingSynchronisations;
    this->PendingSynchronisations = EEOSVoiceManagerLocalUserSyncMode::None;

    TArray<TSharedRef<FVoiceTask>> VoiceTasksToRun;

    if ((SyncMode & EEOSVoiceManagerLocalUserSyncMode::InputSettings) != 0)
    {
        FSetAudioInputSettingsVoiceTaskData Data;
        Data.EOSRTC = this->EOSRTC;
        Data.EOSRTCAudio = this->EOSRTCAudio;
        Data.LocalUserId = this->LocalUserId->GetProductUserId();
        Data.bHasSetCurrentInputDevice = this->bHasSetCurrentInputDevice;
        Data.CurrentInputDeviceId = this->CurrentInputDevice.Id;
        Data.DefaultInputDeviceId = this->GetDefaultInputDeviceInfo().Id;
        Data.bUserInputMuted = this->bInputMuted || this->InputVolume == 0.0f;
        Data.UserInputVolume = this->InputVolume;
        Data.bEnableEchoCancellation = this->GetDefaultedSetting("EnableEchoCancellation", true);
        Data.bEnableNoiseSuppression = this->GetDefaultedSetting("EnableNoiseSuppression", true);
        Data.bEnableAutoGainControl = this->GetDefaultedSetting("EnableAutoGainControl", true);
        Data.bEnableDtx = this->GetDefaultedSetting("EnableDtx", true);
        Data.bEnablePlatformAEC = this->GetDefaultedSetting(
            // Use the legacy option first if the developer is providing it.
            "PlatformAECEnabled",
            this->GetDefaultedSetting(
                // Otherwise use the new option.
                "EnablePlatformAEC",
                // This default is effectively ignored because the constructor
                // sets the setting to whatever GetEnableVoiceChatPlatformAECByDefault
                // has in the config (from Project Settings).
                true));

        VoiceTasksToRun.Add(MakeShared<FSetAudioInputSettingsVoiceTask>(Data));
    }

#if EOS_VERSION_AT_LEAST(1, 16, 0)
    if ((SyncMode & EEOSVoiceManagerLocalUserSyncMode::TransmitMode) != 0 ||
        (SyncMode & EEOSVoiceManagerLocalUserSyncMode::InputSettings) != 0 ||
        (SyncMode & EEOSVoiceManagerLocalUserSyncMode::JoinedRoom) != 0)
    {
        FSetAudioInputVolumeVoiceTaskData Data;
        Data.EOSRTC = this->EOSRTC;
        Data.EOSRTCAudio = this->EOSRTCAudio;
        Data.LocalUserId = this->LocalUserId->GetProductUserId();
		for (const auto& JoinedChannel : this->JoinedChannels)
		{
            Data.RoomNamesWithTransmitStatus.Add(FSetAudioInputVolumeVoiceTaskData::FRoomNameWithTransmitStatus{
                JoinedChannel.Key,
                this->bTransmitToAllChannels || this->TransmitChannelNames.Contains(JoinedChannel.Key)});
		}
        Data.bUserInputMuted = this->bInputMuted || this->InputVolume == 0.0f;
        Data.UserInputVolume = this->InputVolume;
        VoiceTasksToRun.Add(MakeShared<FSetAudioInputVolumeVoiceTask>(Data));
    }
#endif

    if ((SyncMode & EEOSVoiceManagerLocalUserSyncMode::OutputSettings) != 0)
    {
        FSetAudioOutputSettingsVoiceTaskData Data;
        Data.EOSRTCAudio = this->EOSRTCAudio;
        Data.LocalUserId = this->LocalUserId->GetProductUserId();
        Data.bHasSetCurrentOutputDevice = this->bHasSetCurrentOutputDevice;
        Data.CurrentOutputDeviceId = this->CurrentOutputDevice.Id;
        Data.DefaultOutputDeviceId = this->GetDefaultOutputDeviceInfo().Id;
        Data.bUserOutputMuted = this->bOutputMuted || this->OutputVolume == 0.0f;
        Data.UserOutputVolume = this->OutputVolume;

        VoiceTasksToRun.Add(MakeShared<FSetAudioOutputSettingsVoiceTask>(Data));
    }

#if EOS_VERSION_AT_LEAST(1, 16, 0)
    if ((SyncMode & EEOSVoiceManagerLocalUserSyncMode::OutputSettings) != 0 ||
        (SyncMode & EEOSVoiceManagerLocalUserSyncMode::JoinedRoom) != 0)
    {
        FSetAudioOutputVolumeVoiceTaskData Data;
        Data.EOSRTC = this->EOSRTC;
        Data.EOSRTCAudio = this->EOSRTCAudio;
        Data.LocalUserId = this->LocalUserId->GetProductUserId();
        this->JoinedChannels.GetKeys(Data.RoomNames);
        Data.bUserOutputMuted = this->bOutputMuted || this->OutputVolume == 0.0f;
        Data.UserOutputVolume = this->OutputVolume;

        VoiceTasksToRun.Add(MakeShared<FSetAudioOutputVolumeVoiceTask>(Data));
    }
#endif

#if !EOS_VERSION_AT_LEAST(1, 16, 0)
    if ((SyncMode & EEOSVoiceManagerLocalUserSyncMode::TransmitMode) != 0 ||
        (SyncMode & EEOSVoiceManagerLocalUserSyncMode::InputSettings) != 0 ||
        (SyncMode & EEOSVoiceManagerLocalUserSyncMode::JoinedRoom) != 0)
    {
        FUpdateSendingVoiceTaskData Data;
        Data.EOSRTCAudio = this->EOSRTCAudio;
        Data.LocalUserId = this->LocalUserId->GetProductUserId();
        Data.bUserInputMuted = this->bInputMuted || this->InputVolume == 0.0f;
        for (const auto &JoinedChannel : this->JoinedChannels)
        {
            Data.RoomNamesWithTransmitStatus.Add(FUpdateSendingVoiceTaskData::FRoomNameWithTransmitStatus{
                JoinedChannel.Key,
                this->bTransmitToAllChannels || this->TransmitChannelNames.Contains(JoinedChannel.Key)});
        }
        VoiceTasksToRun.Add(MakeShared<FUpdateSendingVoiceTask>(Data));
    }
#endif

    // If there's nothing computed to run, immediately finish.
    if (VoiceTasksToRun.Num() == 0)
    {
        UE_LOG(
            LogRedpointEOSVoiceChat,
            Warning,
            TEXT("Finished synchronising voice chat state with EOS with nothing to action."));

        this->bIsSynchronising = false;

        // Kick off another sync operation if we need to.
        if (this->PendingSynchronisations != EEOSVoiceManagerLocalUserSyncMode::None)
        {
            this->PerformSynchronisationToEOS();
        }

        return;
    }

    FMultiOperation<TSharedRef<FVoiceTask>, bool>::Run(
        VoiceTasksToRun,
        [WeakThis = GetWeakThis(this)](
            const TSharedRef<FVoiceTask> &InVoiceTask,
            const std::function<void(bool OutValue)> &OnDone) -> bool {
            if (auto This = PinWeakThis(WeakThis))
            {
                UE_LOG(
                    LogRedpointEOSVoiceChat,
                    Verbose,
                    TEXT("Synchronising voice chat with task: %s"),
                    *InVoiceTask->GetLogName());
                InVoiceTask->Run(FVoiceTaskComplete::CreateLambda([OnDone]() {
                    OnDone(true);
                }));
                return true;
            }
            return false;
        },
        [WeakThis = GetWeakThis(this)](const TArray<bool> &OutResults) {
            if (auto This = PinWeakThis(WeakThis))
            {
                UE_LOG(LogRedpointEOSVoiceChat, Verbose, TEXT("Finished synchronising voice chat state with EOS."));

                This->bIsSynchronising = false;

                // Kick off another sync operation if we need to.
                if (This->PendingSynchronisations != EEOSVoiceManagerLocalUserSyncMode::None)
                {
                    This->PerformSynchronisationToEOS();
                }
            }
        });
}

void FEOSVoiceManagerLocalUser::SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode SyncMode)
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSVoiceChatUserSyncScheduleSynchronisation);

    if (this->bIsSynchronising)
    {
        // Schedule another synchronisation after this one.
        this->PendingSynchronisations = (EEOSVoiceManagerLocalUserSyncMode)(this->PendingSynchronisations | SyncMode);
    }
    else if (this->bHasSynchronisedThisFrame)
    {
        // We've already synchronised in this frame. To prevent redundant no-op calls into the
        // EOS SDK if the game code is calling the voice chat API frequently, we only synchronise
        // at most once per frame, and then set a flag that we need to synchronise next frame instead.
        this->PendingSynchronisations = (EEOSVoiceManagerLocalUserSyncMode)(this->PendingSynchronisations | SyncMode);
        this->bSynchroniseOnNextFrame = true;
    }
    else
    {
        this->PendingSynchronisations = SyncMode;
        this->bHasSynchronisedThisFrame = true;
        this->PerformSynchronisationToEOS();
    }
}

void FEOSVoiceManagerLocalUser::RegisterLobbyChannel(
    const TSharedRef<const FOnlinePartyIdEOS> &InLobbyId,
    const FString &ChannelName,
    EVoiceChatChannelType ChannelType)
{
    if (!this->JoinedChannels.Contains(ChannelName))
    {
        this->JoinedChannels.Add(
            ChannelName,
            FEOSVoiceManagerLocalUserJoinedChannel::NewLobby(
                this->AsShared(),
                this->EOSRTC,
                this->EOSRTCAudio,
                ChannelName,
                InLobbyId,
                ChannelType));
    }
    else
    {
        UE_LOG(
            LogRedpointEOS,
            Warning,
            TEXT("%s"),
            *OnlineRedpointEOS::Errors::DuplicateNotAllowed(
                 ANSI_TO_TCHAR(__FUNCTION__),
                 TEXT("The user was already in this chat channel by the time RegisterLobbyChannel "
                      "was called. The voice chat system state may be inconsistent."))
                 .ToLogString());
    }
    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::TransmitModeAndJoinedRoom);
    this->OnVoiceChatChannelJoined().Broadcast(ChannelName);
}

void FEOSVoiceManagerLocalUser::UnregisterLobbyChannel(const TSharedRef<const FOnlinePartyIdEOS> &InLobbyId)
{
    FString ChannelName;
    for (const auto &KV : this->JoinedChannels)
    {
        if (KV.Value->LobbyId.IsValid() && *KV.Value->LobbyId == *InLobbyId)
        {
            ChannelName = KV.Value->RoomName;
            break;
        }
    }
    if (ChannelName.IsEmpty())
    {
        return;
    }

    if (this->JoinedChannels.Contains(ChannelName))
    {
        this->JoinedChannels.Remove(ChannelName);
        this->OnVoiceChatChannelExited().Broadcast(ChannelName, FVoiceChatResult(EVoiceChatResult::Success));
    }
}

FEOSVoiceManagerLocalUser::FEOSVoiceManagerLocalUser(
    EOS_HPlatform InPlatform,
    TSharedRef<FEOSVoiceManager> InVoiceManager,
    TSharedRef<const FUniqueNetIdEOS> InLocalUserId)
    : EOSRTC(EOS_Platform_GetRTCInterface(InPlatform))
    , EOSRTCAudio(EOS_RTC_GetAudioInterface(EOSRTC))
    , VoiceManager(MoveTemp(InVoiceManager))
    , LocalUserId(MoveTemp(InLocalUserId))
    , Settings()
    , bHasSetCurrentInputDevice(false)
    , CurrentInputDevice()
    , bHasSetCurrentOutputDevice(false)
    , CurrentOutputDevice()
    , OnDevicesChangedHandle()
    , bTransmitToAllChannels(true)
    , TransmitChannelNames()
    , InputVolume(100.0f)
    , OutputVolume(100.0f)
    , bInputMuted(false)
    , bOutputMuted(false)
    , bHasSynchronisedThisFrame(false)
    , bSynchroniseOnNextFrame(false)
    , bIsSynchronising(false)
    , PendingSynchronisations(EEOSVoiceManagerLocalUserSyncMode::None)
{
    this->Settings.Add("EnableEchoCancellation", "true");
    this->Settings.Add("EnableNoiseSuppression", "true");
    this->Settings.Add("EnableAutoGainControl", "true");
    this->Settings.Add("EnableDtx", "true");
    this->Settings.Add(
        "EnablePlatformAEC",
        this->VoiceManager->Config->GetEnableVoiceChatPlatformAECByDefault() ? "true" : "false");
}

FEOSVoiceManagerLocalUser::~FEOSVoiceManagerLocalUser()
{
    if (this->OnDevicesChangedHandle.IsValid())
    {
        this->VoiceManager->DeviceList->OnDevicesChanged().Remove(this->OnDevicesChangedHandle);
    }
}

void FEOSVoiceManagerLocalUser::RegisterEvents()
{
    this->OnDevicesChangedHandle = this->VoiceManager->DeviceList->OnDevicesChanged().Add(
        FOnVoiceChatAvailableAudioDevicesChangedDelegate::FDelegate::CreateLambda([WeakThis = GetWeakThis(this)]() {
            if (auto This = PinWeakThis(WeakThis))
            {
                This->OnVoiceChatAvailableAudioDevicesChanged().Broadcast();
            }
        }));
}

void FEOSVoiceManagerLocalUser::PostLoginInit(const FEOSVoiceManagerLocalUserPostLoginComplete &OnPostLoginComplete)
{
    this->VoiceManager->DeviceList->WaitForInitialDevices(
        FEOSVoiceManagerDeviceListWaitForInitialDevices::CreateLambda([OnPostLoginComplete]() {
            OnPostLoginComplete.ExecuteIfBound();
        }));
}

void FEOSVoiceManagerLocalUser::SetSetting(const FString &Name, const FString &Value)
{
    this->Settings.Add(Name, Value);
    if (Name == "EnableEchoCancellation" || Name == "EnableNoiseSuppression" || Name == "EnableAutoGainControl" ||
        Name == "EnableDtx" || Name == "EnablePlatformAEC" || Name == "PlatformAECEnabled")
    {
        this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::InputSettings);
    }
}

FString FEOSVoiceManagerLocalUser::GetSetting(const FString &Name)
{
    // Serve lobby IDs as "__EOS_LobbyId:<channel name>" and "__EOS_PartyId:<channel name>"
    if (Name.StartsWith("__EOS_LobbyId:") || Name.StartsWith("__EOS_PartyId:"))
    {
        TArray<FString> Components;
        Name.ParseIntoArray(Components, TEXT(":"), true);
        if (Components.Num() >= 2)
        {
            for (const auto &KV : this->JoinedChannels)
            {
                if (KV.Key == Components[1])
                {
                    if (KV.Value->LobbyId.IsValid())
                    {
                        return KV.Value->LobbyId->ToString();
                    }
                    return TEXT("");
                }
            }
        }
    }

    if (this->Settings.Contains(Name))
    {
        return this->Settings[Name];
    }
    return TEXT("");
}

void FEOSVoiceManagerLocalUser::SetAudioInputVolume(float Volume)
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSVoiceChatApiSetAudioInputVolume);

    float OldVolume = this->InputVolume;
    this->InputVolume = Volume;
    if (this->InputVolume < 0.0f)
    {
        this->InputVolume = 0.0f;
    }
    if (this->InputVolume > 200.0f)
    {
        this->InputVolume = 200.0f;
    }

    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::InputSettings);
}

void FEOSVoiceManagerLocalUser::SetAudioOutputVolume(float Volume)
{
    float OldVolume = this->OutputVolume;
    this->OutputVolume = Volume;
    if (this->OutputVolume < 0.0f)
    {
        this->OutputVolume = 0.0f;
    }
    if (this->OutputVolume > 200.0f)
    {
        this->OutputVolume = 200.0f;
    }

    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::OutputSettings);
}

float FEOSVoiceManagerLocalUser::GetAudioInputVolume() const
{
    return this->InputVolume;
}

float FEOSVoiceManagerLocalUser::GetAudioOutputVolume() const
{
    return this->OutputVolume;
}

void FEOSVoiceManagerLocalUser::SetAudioInputDeviceMuted(bool bIsMuted)
{
    bool bOldMuted = this->bInputMuted;
    this->bInputMuted = bIsMuted;

    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::InputSettings);
}

void FEOSVoiceManagerLocalUser::SetAudioOutputDeviceMuted(bool bIsMuted)
{
    bool bOldMuted = this->bOutputMuted;
    this->bOutputMuted = bIsMuted;

    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::OutputSettings);
}

bool FEOSVoiceManagerLocalUser::GetAudioInputDeviceMuted() const
{
    return this->bInputMuted;
}

bool FEOSVoiceManagerLocalUser::GetAudioOutputDeviceMuted() const
{
    return this->bOutputMuted;
}

TArray<FEOSVoiceManagerDevice> FEOSVoiceManagerLocalUser::GetAvailableInputDeviceInfos() const
{
    return this->VoiceManager->DeviceList->GetInputDevices();
}

TArray<FEOSVoiceManagerDevice> FEOSVoiceManagerLocalUser::GetAvailableOutputDeviceInfos() const
{
    return this->VoiceManager->DeviceList->GetOutputDevices();
}

void FEOSVoiceManagerLocalUser::SetInputDeviceId(const FString &InputDeviceId)
{
    bool bFoundTargetInputDevice = false;
    FEOSVoiceManagerDevice TargetInputDeviceId;
    TArray<FEOSVoiceManagerDevice> Results = this->GetAvailableInputDeviceInfos();
    for (const auto &Result : Results)
    {
        if (Result.Id == InputDeviceId)
        {
            TargetInputDeviceId = Result;
            bFoundTargetInputDevice = true;
            break;
        }
    }
    if (!bFoundTargetInputDevice)
    {
        UE_LOG(LogRedpointEOS, Error, TEXT("Failed to set audio input options. No such audio input device."));
        return;
    }

    FEOSVoiceManagerDevice OldDevice = this->CurrentInputDevice;
    bool bOldHasSet = this->bHasSetCurrentInputDevice;
    this->CurrentInputDevice = TargetInputDeviceId;
    this->bHasSetCurrentInputDevice = true;

    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::InputSettings);
}

void FEOSVoiceManagerLocalUser::SetOutputDeviceId(const FString &OutputDeviceId)
{
    bool bFoundTargetOutputDevice = false;
    FEOSVoiceManagerDevice TargetOutputDeviceId;
    TArray<FEOSVoiceManagerDevice> Results = this->GetAvailableOutputDeviceInfos();
    for (const auto &Result : Results)
    {
        if (Result.Id == OutputDeviceId)
        {
            TargetOutputDeviceId = Result;
            bFoundTargetOutputDevice = true;
            break;
        }
    }
    if (!bFoundTargetOutputDevice)
    {
        UE_LOG(LogRedpointEOS, Error, TEXT("Failed to set audio output options. No such audio output device."));
        return;
    }

    FEOSVoiceManagerDevice OldDevice = this->CurrentOutputDevice;
    bool bOldHasSet = this->bHasSetCurrentOutputDevice;
    this->CurrentOutputDevice = TargetOutputDeviceId;
    this->bHasSetCurrentOutputDevice = true;

    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::OutputSettings);
}

FEOSVoiceManagerDevice FEOSVoiceManagerLocalUser::GetInputDeviceInfo() const
{
    if (this->bHasSetCurrentInputDevice)
    {
        return this->CurrentInputDevice;
    }
    return this->GetDefaultInputDeviceInfo();
}

FEOSVoiceManagerDevice FEOSVoiceManagerLocalUser::GetOutputDeviceInfo() const
{
    if (this->bHasSetCurrentOutputDevice)
    {
        return this->CurrentOutputDevice;
    }
    return this->GetDefaultOutputDeviceInfo();
}

FEOSVoiceManagerDevice FEOSVoiceManagerLocalUser::GetDefaultInputDeviceInfo() const
{
    TArray<FEOSVoiceManagerDevice> Results = this->GetAvailableInputDeviceInfos();
    for (const auto &Result : Results)
    {
        if (Result.bIsDefaultDevice)
        {
            return Result;
        }
    }
    return FEOSVoiceManagerDevice();
}

FEOSVoiceManagerDevice FEOSVoiceManagerLocalUser::GetDefaultOutputDeviceInfo() const
{
    TArray<FEOSVoiceManagerDevice> Results = this->GetAvailableOutputDeviceInfos();
    for (const auto &Result : Results)
    {
        if (Result.bIsDefaultDevice)
        {
            return Result;
        }
    }
    return FEOSVoiceManagerDevice();
}

void FEOSVoiceManagerLocalUser::SetPlayersBlockState(const TArray<FString> &PlayerNames, bool bBlocked)
{
    for (const auto &PlayerName : PlayerNames)
    {
        TSharedPtr<const FUniqueNetIdEOS> ParticipantId = FUniqueNetIdEOS::ParseFromString(PlayerName);
        if (ParticipantId.IsValid())
        {
            for (const auto &Channel : this->JoinedChannels)
            {
                if (Channel.Value->Participants.Contains(*ParticipantId))
                {
                    EOS_RTC_BlockParticipantOptions Opts = {};
                    Opts.ApiVersion = EOS_RTC_BLOCKPARTICIPANT_API_LATEST;
                    Opts.bBlocked = bBlocked;
                    Opts.LocalUserId = this->LocalUserId->GetProductUserId();
                    Opts.ParticipantId = ParticipantId->GetProductUserId();
                    EOSString_AnsiUnlimited::AllocateToCharBuffer(Channel.Value->RoomName, Opts.RoomName);

                    EOSRunOperation<EOS_HRTC, EOS_RTC_BlockParticipantOptions, EOS_RTC_BlockParticipantCallbackInfo>(
                        this->EOSRTC,
                        &Opts,
                        &EOS_RTC_BlockParticipant,
                        [ParticipantId, bBlocked, RoomName = Channel.Value->RoomName, RoomNameBuffer = Opts.RoomName](
                            const EOS_RTC_BlockParticipantCallbackInfo *Data) {
                            EOSString_AnsiUnlimited::FreeFromCharBufferConst(RoomNameBuffer);
                            if (Data->ResultCode != EOS_EResult::EOS_Success)
                            {
                                UE_LOG(
                                    LogRedpointEOS,
                                    Warning,
                                    TEXT("EOS_RTC_BlockParticipant operation (%s) for remote user '%s' in room '%s' "
                                         "failed with result code %s"),
                                    bBlocked ? TEXT("blocking") : TEXT("unblocking"),
                                    *ParticipantId->ToString(),
                                    *RoomName,
                                    ANSI_TO_TCHAR(EOS_EResult_ToString(Data->ResultCode)));
                            }
                        });
                }
            }
        }
    }
}

void FEOSVoiceManagerLocalUser::BlockPlayers(const TArray<FString> &PlayerNames)
{
    this->SetPlayersBlockState(PlayerNames, true);
}

void FEOSVoiceManagerLocalUser::UnblockPlayers(const TArray<FString> &PlayerNames)
{
    this->SetPlayersBlockState(PlayerNames, false);
}

void FEOSVoiceManagerLocalUser::JoinChannel(
    const FString &ChannelName,
    const FString &ChannelCredentials,
    EVoiceChatChannelType ChannelType,
    const FOnVoiceChatChannelJoinCompleteDelegate &Delegate,
    const TOptional<FVoiceChatChannel3dProperties> &Channel3dProperties)
{
    if (ChannelType == EVoiceChatChannelType::Positional)
    {
        Delegate.ExecuteIfBound(
            ChannelName,
            FVoiceChatResult(
                EVoiceChatResult::InvalidArgument,
                TEXT("PositionalChannelsNotSupported"),
                TEXT("EOS does not support positional voice chat channels yet.")));
        return;
    }

    if (this->JoinedChannels.Contains(ChannelName))
    {
        Delegate.ExecuteIfBound(
            ChannelName,
            FVoiceChatResult(
                EVoiceChatResult::InvalidArgument,
                TEXT("AlreadyJoined"),
                TEXT("This user is already connected to that voice chat channel.")));
        return;
    }

    FString ClientBaseUrl, ParticipantToken;
    ChannelCredentials
        .Split(TEXT("?token="), &ClientBaseUrl, &ParticipantToken, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

    EOS_RTC_JoinRoomOptions Opts = {};
    Opts.ApiVersion = EOS_RTC_JOINROOM_API_LATEST;
    Opts.LocalUserId = this->LocalUserId->GetProductUserId();
    verify(EOSString_AnsiUnlimited::AllocateToCharBuffer(ChannelName, Opts.RoomName) == EOS_EResult::EOS_Success);
    verify(
        EOSString_AnsiUnlimited::AllocateToCharBuffer(ClientBaseUrl, Opts.ClientBaseUrl) == EOS_EResult::EOS_Success);
    verify(
        EOSString_AnsiUnlimited::AllocateToCharBuffer(ParticipantToken, Opts.ParticipantToken) ==
        EOS_EResult::EOS_Success);
    Opts.ParticipantId = nullptr;
    Opts.Flags = ChannelType == EVoiceChatChannelType::Echo ? EOS_RTC_JOINROOMFLAGS_ENABLE_ECHO : 0x0;
    Opts.bManualAudioInputEnabled = false;
    Opts.bManualAudioOutputEnabled = false;

    EOSRunOperation<EOS_HRTC, EOS_RTC_JoinRoomOptions, EOS_RTC_JoinRoomCallbackInfo>(
        this->EOSRTC,
        &Opts,
        &EOS_RTC_JoinRoom,
        [WeakThis = GetWeakThis(this), Opts, Delegate, ChannelName, ChannelType](
            const EOS_RTC_JoinRoomCallbackInfo *Data) {
            EOSString_AnsiUnlimited::FreeFromCharBufferConst(Opts.RoomName);
            EOSString_AnsiUnlimited::FreeFromCharBufferConst(Opts.ClientBaseUrl);
            EOSString_AnsiUnlimited::FreeFromCharBufferConst(Opts.ParticipantToken);

            if (auto This = PinWeakThis(WeakThis))
            {
                if (Data->ResultCode == EOS_EResult::EOS_Success)
                {
                    if (!This->JoinedChannels.Contains(ChannelName))
                    {
                        This->JoinedChannels.Add(
                            ChannelName,
                            FEOSVoiceManagerLocalUserJoinedChannel::NewDedicated(
                                This.ToSharedRef(),
                                This->EOSRTC,
                                This->EOSRTCAudio,
                                ChannelName,
                                ChannelType));
                    }
                    else
                    {
                        UE_LOG(
                            LogRedpointEOS,
                            Warning,
                            TEXT("%s"),
                            *OnlineRedpointEOS::Errors::DuplicateNotAllowed(
                                 ANSI_TO_TCHAR(__FUNCTION__),
                                 TEXT("The user was already in this chat channel by the time EOS_RTC_JoinRoom "
                                      "completed successfully. The voice chat system state may be inconsistent."))
                                 .ToLogString());
                    }
                    This->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::TransmitModeAndJoinedRoom);
                    This->OnVoiceChatChannelJoined().Broadcast(ChannelName);
                    Delegate.ExecuteIfBound(ChannelName, FVoiceChatResult(EVoiceChatResult::Success));
                }
                else
                {
                    UE_LOG(
                        LogRedpointEOS,
                        Error,
                        TEXT("Failed to join RTC channel: %s"),
                        ANSI_TO_TCHAR(EOS_EResult_ToString(Data->ResultCode)));
                    if (Data->ResultCode == EOS_EResult::EOS_NoConnection)
                    {
                        Delegate.ExecuteIfBound(ChannelName, FVoiceChatResult(EVoiceChatResult::ConnectionFailure));
                    }
                    else if (Data->ResultCode == EOS_EResult::EOS_InvalidAuth)
                    {
                        Delegate.ExecuteIfBound(ChannelName, FVoiceChatResult(EVoiceChatResult::CredentialsInvalid));
                    }
                    else if (Data->ResultCode == EOS_EResult::EOS_RTC_TooManyParticipants)
                    {
                        Delegate.ExecuteIfBound(ChannelName, FVoiceChatResult(EVoiceChatResult::NotPermitted));
                    }
                    else if (Data->ResultCode == EOS_EResult::EOS_AccessDenied)
                    {
                        Delegate.ExecuteIfBound(ChannelName, FVoiceChatResult(EVoiceChatResult::InvalidArgument));
                    }
                    else
                    {
                        Delegate.ExecuteIfBound(ChannelName, FVoiceChatResult(EVoiceChatResult::ImplementationError));
                    }
                }
            }
        });
}

void FEOSVoiceManagerLocalUser::LeaveChannel(
    const FString &ChannelName,
    const FOnVoiceChatChannelLeaveCompleteDelegate &Delegate)
{
    EOS_RTC_LeaveRoomOptions Opts = {};
    Opts.ApiVersion = EOS_RTC_LEAVEROOM_API_LATEST;
    Opts.LocalUserId = this->LocalUserId->GetProductUserId();
    verify(EOSString_AnsiUnlimited::AllocateToCharBuffer(ChannelName, Opts.RoomName) == EOS_EResult::EOS_Success);

    EOSRunOperation<EOS_HRTC, EOS_RTC_LeaveRoomOptions, EOS_RTC_LeaveRoomCallbackInfo>(
        this->EOSRTC,
        &Opts,
        &EOS_RTC_LeaveRoom,
        [WeakThis = GetWeakThis(this), Opts, Delegate, ChannelName](const EOS_RTC_LeaveRoomCallbackInfo *Data) {
            EOSString_AnsiUnlimited::FreeFromCharBufferConst(Opts.RoomName);

            if (auto This = PinWeakThis(WeakThis))
            {
                if (Data->ResultCode == EOS_EResult::EOS_Success)
                {
                    if (This->JoinedChannels.Contains(ChannelName))
                    {
                        This->JoinedChannels.Remove(ChannelName);
                        This->OnVoiceChatChannelExited().Broadcast(
                            ChannelName,
                            FVoiceChatResult(EVoiceChatResult::Success));
                    }
                    Delegate.ExecuteIfBound(ChannelName, FVoiceChatResult(EVoiceChatResult::Success));
                }
                else
                {
                    UE_LOG(
                        LogRedpointEOS,
                        Error,
                        TEXT("Failed to leave RTC channel: %s"),
                        ANSI_TO_TCHAR(EOS_EResult_ToString(Data->ResultCode)));
                    if (Data->ResultCode == EOS_EResult::EOS_AccessDenied)
                    {
                        Delegate.ExecuteIfBound(ChannelName, FVoiceChatResult(EVoiceChatResult::InvalidArgument));
                    }
                    else
                    {
                        Delegate.ExecuteIfBound(ChannelName, FVoiceChatResult(EVoiceChatResult::ImplementationError));
                    }
                }
            }
        });
}

void FEOSVoiceManagerLocalUser::Set3DPosition(
    const FString &ChannelName,
    const FVector &SpeakerPosition,
    const FVector &ListenerPosition,
    const FVector &ListenerForwardDirection,
    const FVector &ListenerUpDirection)
{
    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("EOS does not support calling Set3DPosition, because positional voice channels are not supported yet."));
}

TArray<FString> FEOSVoiceManagerLocalUser::GetChannels()
{
    TArray<FString> Keys;
    this->JoinedChannels.GenerateKeyArray(Keys);
    return Keys;
}

const TArray<FString> FEOSVoiceManagerLocalUser::GetPlayersInChannel(const FString &ChannelName) const
{
    TArray<FString> PlayerIds;
    if (this->JoinedChannels.Contains(ChannelName))
    {
        for (const auto &RemoteUser : this->JoinedChannels[ChannelName]->Participants)
        {
            PlayerIds.Add(RemoteUser.Key->ToString());
        }
    }
    return PlayerIds;
}

EVoiceChatChannelType FEOSVoiceManagerLocalUser::GetChannelType(const FString &ChannelName) const
{
    if (this->JoinedChannels.Contains(ChannelName))
    {
        return this->JoinedChannels[ChannelName]->ChannelType;
    }

    return EVoiceChatChannelType::NonPositional;
}

bool FEOSVoiceManagerLocalUser::IsPlayerTalking(const FString &PlayerName) const
{
    if (PlayerName == this->LocalUserId->ToString())
    {
        // If the local user is muted, they are never talking.
        if (this->bInputMuted || this->InputVolume == 0.0f)
        {
            return false;
        }
    }

    TSharedPtr<const FUniqueNetIdEOS> ParticipantId = FUniqueNetIdEOS::ParseFromString(PlayerName);
    if (ParticipantId.IsValid())
    {
        for (const auto &Channel : this->JoinedChannels)
        {
            if (Channel.Value->Participants.Contains(*ParticipantId))
            {
                if (Channel.Value->Participants[*ParticipantId]->bIsTalking)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void FEOSVoiceManagerLocalUser::SetPlayerMuted(const FString &PlayerName, bool bMuted)
{
    TSharedPtr<const FUniqueNetIdEOS> ParticipantId = FUniqueNetIdEOS::ParseFromString(PlayerName);
    if (ParticipantId.IsValid())
    {
        if (*ParticipantId == *this->LocalUserId)
        {
            // We're trying to mute ourselves, not a remote player.
            this->SetAudioInputDeviceMuted(bMuted);
            return;
        }

        for (const auto &Channel : this->JoinedChannels)
        {
            if (Channel.Value->Participants.Contains(*ParticipantId))
            {
                EOS_RTCAudio_UpdateReceivingOptions Opts = {};
                Opts.ApiVersion = EOS_RTCAUDIO_UPDATERECEIVING_API_LATEST;
                Opts.LocalUserId = this->LocalUserId->GetProductUserId();
                Opts.ParticipantId = ParticipantId->GetProductUserId();
                Opts.RoomName = Channel.Value->RoomNameStr;
                Opts.bAudioEnabled = bMuted ? EOS_FALSE : EOS_TRUE;

                EOSRunOperation<
                    EOS_HRTCAudio,
                    EOS_RTCAudio_UpdateReceivingOptions,
                    EOS_RTCAudio_UpdateReceivingCallbackInfo>(
                    this->EOSRTCAudio,
                    &Opts,
                    &EOS_RTCAudio_UpdateReceiving,
                    [WeakThis = GetWeakThis(this),
                     bMuted,
                     ParticipantId,
                     RoomName = Channel.Key,
                     RoomInfo = Channel.Value](const EOS_RTCAudio_UpdateReceivingCallbackInfo *Data) {
                        if (auto This = PinWeakThis(WeakThis))
                        {
                            if (Data->ResultCode != EOS_EResult::EOS_Success)
                            {
                                UE_LOG(
                                    LogRedpointEOS,
                                    Warning,
                                    TEXT(
                                        "EOS_RTCAudio_UpdateReceiving operation (%s) for remote user '%s' in room '%s' "
                                        "failed with result code %s"),
                                    bMuted ? TEXT("muting") : TEXT("unmuting"),
                                    *ParticipantId->ToString(),
                                    *RoomName,
                                    ANSI_TO_TCHAR(EOS_EResult_ToString(Data->ResultCode)));
                            }
                            else
                            {
                                // Update the bIsMuted flag.
                                if (RoomInfo->Participants.Contains(*ParticipantId))
                                {
                                    RoomInfo->Participants[*ParticipantId]->bIsMuted = bMuted;
                                    This->OnVoiceChatPlayerMuteUpdated().Broadcast(
                                        RoomName,
                                        ParticipantId->ToString(),
                                        bMuted);
                                }
                            }
                        }
                    });
            }
        }
    }
}

bool FEOSVoiceManagerLocalUser::IsPlayerMuted(const FString &PlayerName) const
{
    TSharedPtr<const FUniqueNetIdEOS> ParticipantId = FUniqueNetIdEOS::ParseFromString(PlayerName);
    if (ParticipantId.IsValid())
    {
        if (*ParticipantId == *this->LocalUserId)
        {
            // We're trying to check if we're muted ourselves, not a remote player.
            return this->GetAudioInputDeviceMuted();
        }

        for (const auto &Channel : this->JoinedChannels)
        {
            if (Channel.Value->Participants.Contains(*ParticipantId))
            {
                if (Channel.Value->Participants[*ParticipantId]->bIsMuted)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void FEOSVoiceManagerLocalUser::SetPlayerVolume(const FString &PlayerName, float Volume)
{
    if (Volume == 0.0f)
    {
        this->SetPlayerMuted(PlayerName, true);
    }
    else
    {
        this->SetPlayerMuted(PlayerName, false);
    }
}

float FEOSVoiceManagerLocalUser::GetPlayerVolume(const FString &PlayerName) const
{
    return this->IsPlayerMuted(PlayerName) ? 0.0f : 100.0f;
}

void FEOSVoiceManagerLocalUser::TransmitToAllChannels()
{
    this->bTransmitToAllChannels = true;
    this->TransmitChannelNames.Empty();
    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::TransmitMode);
}

void FEOSVoiceManagerLocalUser::TransmitToNoChannels()
{
    this->bTransmitToAllChannels = false;
    this->TransmitChannelNames.Empty();
    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::TransmitMode);
}

#if defined(UE_5_3_OR_LATER)
void FEOSVoiceManagerLocalUser::TransmitToSpecificChannels(const TSet<FString> &ChannelNames)
{
    this->bTransmitToAllChannels = false;
    this->TransmitChannelNames = ChannelNames;
    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::TransmitMode);
}
#else
void FEOSVoiceManagerLocalUser::TransmitToSpecificChannel(const FString &ChannelName)
{
    this->bTransmitToAllChannels = false;
    this->TransmitChannelNames.Add(ChannelName);
    this->SynchroniseToEOS(EEOSVoiceManagerLocalUserSyncMode::TransmitMode);
}
#endif

EVoiceChatTransmitMode FEOSVoiceManagerLocalUser::GetTransmitMode() const
{
    if (this->bTransmitToAllChannels)
    {
        return EVoiceChatTransmitMode::All;
    }
    else if (this->TransmitChannelNames.Num() == 0)
    {
        return EVoiceChatTransmitMode::None;
    }
    else
    {
#if defined(UE_5_3_OR_LATER)
        return EVoiceChatTransmitMode::SpecificChannels;
#else
        return EVoiceChatTransmitMode::Channel;
#endif
    }
}

#if defined(UE_5_3_OR_LATER)
TSet<FString> FEOSVoiceManagerLocalUser::GetTransmitChannels() const
{
    return this->TransmitChannelNames;
}
#else
FString FEOSVoiceManagerLocalUser::GetTransmitChannel() const
{
    if (this->bTransmitToAllChannels)
    {
        return TEXT("");
    }

    return FString::Join(this->TransmitChannelNames, TEXT(","));
}
#endif

FOnVoiceChatAvailableAudioDevicesChangedDelegate &FEOSVoiceManagerLocalUser::OnVoiceChatAvailableAudioDevicesChanged()
{
    return this->OnVoiceChatAvailableAudioDevicesChangedDelegate;
}

FOnVoiceChatChannelJoinedDelegate &FEOSVoiceManagerLocalUser::OnVoiceChatChannelJoined()
{
    return this->OnVoiceChatChannelJoinedDelegate;
}

FOnVoiceChatChannelExitedDelegate &FEOSVoiceManagerLocalUser::OnVoiceChatChannelExited()
{
    return this->OnVoiceChatChannelExitedDelegate;
}

FOnVoiceChatCallStatsUpdatedDelegate &FEOSVoiceManagerLocalUser::OnVoiceChatCallStatsUpdated()
{
    return this->OnVoiceChatCallStatsUpdatedDelegate;
}

FOnVoiceChatPlayerAddedDelegate &FEOSVoiceManagerLocalUser::OnVoiceChatPlayerAdded()
{
    return this->OnVoiceChatPlayerAddedDelegate;
}

FOnVoiceChatPlayerRemovedDelegate &FEOSVoiceManagerLocalUser::OnVoiceChatPlayerRemoved()
{
    return this->OnVoiceChatPlayerRemovedDelegate;
}

FOnVoiceChatPlayerTalkingUpdatedDelegate &FEOSVoiceManagerLocalUser::OnVoiceChatPlayerTalkingUpdated()
{
    return this->OnVoiceChatPlayerTalkingUpdatedDelegate;
}

FOnVoiceChatPlayerMuteUpdatedDelegate &FEOSVoiceManagerLocalUser::OnVoiceChatPlayerMuteUpdated()
{
    return this->OnVoiceChatPlayerMuteUpdatedDelegate;
}

FOnVoiceChatPlayerVolumeUpdatedDelegate &FEOSVoiceManagerLocalUser::OnVoiceChatPlayerVolumeUpdated()
{
    return this->OnVoiceChatPlayerVolumeUpdatedDelegate;
}

#endif // #if EOS_HAS_AUTHENTICATION
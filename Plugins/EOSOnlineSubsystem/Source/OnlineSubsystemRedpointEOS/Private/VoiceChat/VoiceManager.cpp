// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Shared/VoiceChat/VoiceManager.h"

#include "OnlineSubsystemRedpointEOS/Shared/EOSErrorConv.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlinePartyIdEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

#if EOS_HAS_AUTHENTICATION

void FEOSVoiceManager::Internal_UserJoinedLobby(
    const TSharedRef<const FUniqueNetIdEOS> &UserId,
    const TSharedRef<const FOnlinePartyIdEOS> &LobbyId,
    EOS_HLobby EOSLobby)
{
    // Get the RTC room name for this lobby.
    EOS_Lobby_GetRTCRoomNameOptions GetRTCRoomNameOpts = {};
    GetRTCRoomNameOpts.ApiVersion = EOS_LOBBY_GETRTCROOMNAME_API_LATEST;
    GetRTCRoomNameOpts.LocalUserId = UserId->GetProductUserId();
    GetRTCRoomNameOpts.LobbyId = LobbyId->GetLobbyId();
    FString RoomName;
    EOS_EResult GetRoomNameResult =
        EOSString_AnsiUnlimited::FromDynamicLengthApiCall<EOS_HLobby, EOS_Lobby_GetRTCRoomNameOptions>(
            EOSLobby,
            &GetRTCRoomNameOpts,
            EOS_Lobby_GetRTCRoomName,
            RoomName);
    if (GetRoomNameResult != EOS_EResult::EOS_Success)
    {
        if (GetRoomNameResult == EOS_EResult::EOS_Disabled)
        {
            // This is expected if the lobby does not have RTC enabled.
        }
        else
        {
            UE_LOG(
                LogRedpointEOSVoiceChat,
                Error,
                TEXT("%s"),
                *ConvertError(
                     TEXT("EOS_Lobby_GetRTCRoomName"),
                     TEXT("Unable to retrieve room name for RTC-enabled lobby"),
                     GetRoomNameResult)
                     .ToLogString());
        }
        return;
    }

    // Check if echo is enabled.
    bool IsEchoEnabled = false;
    for (int i = QueuedEchoEnabledLobbies.Num() - 1; i >= 0; i--)
    {
        const auto &Entry = QueuedEchoEnabledLobbies[i];
        if (*Entry.Key == *UserId && *Entry.Value == *LobbyId)
        {
            IsEchoEnabled = true;
            QueuedEchoEnabledLobbies.RemoveAt(i);
            break;
        }
    }

    // Register the lobby channel with RTC.
    this->GetLocalUser(*UserId)->RegisterLobbyChannel(
        LobbyId,
        RoomName,
        IsEchoEnabled ? EVoiceChatChannelType::Echo : EVoiceChatChannelType::NonPositional);
}

void FEOSVoiceManager::Internal_UserLeftLobby(
    const TSharedRef<const FUniqueNetIdEOS> &UserId,
    const TSharedRef<const FOnlinePartyIdEOS> &LobbyId,
    EOS_HLobby EOSLobby)
{
    this->GetLocalUser(*UserId)->UnregisterLobbyChannel(LobbyId);
}

void FEOSVoiceManager::Handle_LobbyMemberStatusReceived(const EOS_Lobby_LobbyMemberStatusReceivedCallbackInfo *Data)
{
    auto UserId = MakeShared<FUniqueNetIdEOS>(Data->TargetUserId);
    auto LobbyId = MakeShared<FOnlinePartyIdEOS>(Data->LobbyId);

    auto EOSLobby = EOS_Platform_GetLobbyInterface(this->EOSPlatform);

    // We're only interested in when local users join or leave lobbies.
    if (this->Identity->GetLoginStatus(*UserId) != ELoginStatus::LoggedIn)
    {
        return;
    }

    // Figure out what to do based on the status change.
    switch (Data->CurrentStatus)
    {
    case EOS_ELobbyMemberStatus::EOS_LMS_JOINED:
        // This fires when *other* users join the lobby, which we don't need to track.
    case EOS_ELobbyMemberStatus::EOS_LMS_LEFT:
        // This fires when *other* users leave the lobby, which we don't need to track.
    case EOS_ELobbyMemberStatus::EOS_LMS_PROMOTED:
        // Irrelevant for voice chat.
        break;
    case EOS_ELobbyMemberStatus::EOS_LMS_DISCONNECTED:
        // This can fire when *we* leave the lobby, so we need to handle this.
        UE_LOG(
            LogRedpointEOSVoiceChat,
            Verbose,
            TEXT("lobby %s, user %s: LobbyMemberStatusReceived with EOS_LMS_DISCONNECTED."),
            *LobbyId->ToString(),
            *UserId->ToString());
        this->Internal_UserLeftLobby(UserId, LobbyId, EOSLobby);
        break;
    case EOS_ELobbyMemberStatus::EOS_LMS_KICKED:
        // This can fire when *we* are kicked from the lobby, so we need to handle this.
        UE_LOG(
            LogRedpointEOSVoiceChat,
            Verbose,
            TEXT("lobby %s, user %s: LobbyMemberStatusReceived with EOS_LMS_KICKED."),
            *LobbyId->ToString(),
            *UserId->ToString());
        this->Internal_UserLeftLobby(UserId, LobbyId, EOSLobby);
        break;
    case EOS_ELobbyMemberStatus::EOS_LMS_CLOSED:
        // This can fire when *we* are removed from the lobby, because the lobby was deleted, so we need to handle this.
        UE_LOG(
            LogRedpointEOSVoiceChat,
            Verbose,
            TEXT("lobby %s, user %s: LobbyMemberStatusReceived with EOS_LMS_CLOSED."),
            *LobbyId->ToString(),
            *UserId->ToString());
        this->Internal_UserLeftLobby(UserId, LobbyId, EOSLobby);
        break;
    }
}

FEOSVoiceManager::FEOSVoiceManager(
    EOS_HPlatform InPlatform,
    TSharedRef<Redpoint::EOS::Config::IConfig> InConfig,
    TSharedRef<IOnlineIdentity, ESPMode::ThreadSafe> InIdentity)
    : EOSPlatform(InPlatform)
    , Config(MoveTemp(InConfig))
    , Identity(MoveTemp(InIdentity))
    , LocalUsers()
    , QueuedEchoEnabledLobbies()
    , DeviceList(MakeShared<FEOSVoiceManagerDeviceList>(InPlatform))
{
}

void FEOSVoiceManager::MarkPartyOrLobbyAsEchoEnabled(
    const TSharedRef<const FUniqueNetIdEOS> &InUserId,
    const TSharedRef<const FOnlinePartyId> &InPartyOrLobbyId)
{
    // Check to see if the lobby is already known to this user.
    auto User = this->GetLocalUser(*InUserId);
    if (!User.IsValid())
    {
        // Queue it for later.
        this->QueuedEchoEnabledLobbies.Add(
            TPair<TSharedRef<const FUniqueNetIdEOS>, TSharedRef<const FOnlinePartyId>>(InUserId, InPartyOrLobbyId));
        return;
    }
    for (const auto &Channel : User->JoinedChannels)
    {
        if (Channel.Value->LobbyId.IsValid() && *Channel.Value->LobbyId == *InPartyOrLobbyId)
        {
            // Found the existing channel, just change it's mode.
            Channel.Value->ChannelType = EVoiceChatChannelType::Echo;
            return;
        }
    }

    // Queue it for later.
    this->QueuedEchoEnabledLobbies.Add(
        TPair<TSharedRef<const FUniqueNetIdEOS>, TSharedRef<const FOnlinePartyId>>(InUserId, InPartyOrLobbyId));
    return;
}

void FEOSVoiceManager::RegisterEvents()
{
    EOS_Lobby_AddNotifyLobbyMemberStatusReceivedOptions OptsLobbyMemberStatus = {};
    OptsLobbyMemberStatus.ApiVersion = EOS_LOBBY_ADDNOTIFYLOBBYMEMBERSTATUSRECEIVED_API_LATEST;

    this->Unregister_LobbyMemberStatusReceived = EOSRegisterEvent<
        EOS_HLobby,
        EOS_Lobby_AddNotifyLobbyMemberStatusReceivedOptions,
        EOS_Lobby_LobbyMemberStatusReceivedCallbackInfo>(
        EOS_Platform_GetLobbyInterface(this->EOSPlatform),
        &OptsLobbyMemberStatus,
        EOS_Lobby_AddNotifyLobbyMemberStatusReceived,
        EOS_Lobby_RemoveNotifyLobbyMemberStatusReceived,
        [WeakThis = GetWeakThis(this)](const EOS_Lobby_LobbyMemberStatusReceivedCallbackInfo *Data) {
            if (auto This = StaticCastSharedPtr<FEOSVoiceManager>(PinWeakThis(WeakThis)))
            {
                This->Handle_LobbyMemberStatusReceived(Data);
            }
        });
}

void FEOSVoiceManager::ScheduleUserSynchronisationIfNeeded()
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSVoiceChatSyncPerformDeferredSynchronisation);

	for (const auto& LocalUser : this->LocalUsers)
	{
		if (LocalUser.Value->bSynchroniseOnNextFrame)
		{
            LocalUser.Value->bHasSynchronisedThisFrame = false;
            LocalUser.Value->bSynchroniseOnNextFrame = false;
            LocalUser.Value->PerformSynchronisationToEOS();
		}
	}
}

void FEOSVoiceManager::UserManuallyJoinedLobby(const FUniqueNetIdEOS &UserId, const FOnlinePartyIdEOS &LobbyId)
{
    UE_LOG(
        LogRedpointEOSVoiceChat,
        Verbose,
        TEXT("lobby %s, user %s: UserManuallyJoinedLobby"),
        *LobbyId.ToString(),
        *UserId.ToString());

    this->Internal_UserJoinedLobby(
        StaticCastSharedRef<const FUniqueNetIdEOS>(UserId.AsShared()),
        StaticCastSharedRef<const FOnlinePartyIdEOS>(LobbyId.AsShared()),
        EOS_Platform_GetLobbyInterface(this->EOSPlatform));
}

void FEOSVoiceManager::UserManuallyLeftLobby(const FUniqueNetIdEOS &UserId, const FOnlinePartyIdEOS &LobbyId)
{
    UE_LOG(
        LogRedpointEOSVoiceChat,
        Verbose,
        TEXT("lobby %s, user %s: UserManuallyLeftLobby"),
        *LobbyId.ToString(),
        *UserId.ToString());

    this->Internal_UserLeftLobby(
        StaticCastSharedRef<const FUniqueNetIdEOS>(UserId.AsShared()),
        StaticCastSharedRef<const FOnlinePartyIdEOS>(LobbyId.AsShared()),
        EOS_Platform_GetLobbyInterface(this->EOSPlatform));
}

void FEOSVoiceManager::AddLocalUser(const FUniqueNetIdEOS &UserId)
{
    this->LocalUsers.Add(
        UserId,
        MakeShared<FEOSVoiceManagerLocalUser>(
            this->EOSPlatform,
            this->AsShared(),
            StaticCastSharedRef<const FUniqueNetIdEOS>(UserId.AsShared())));
}

void FEOSVoiceManager::RemoveLocalUser(const FUniqueNetIdEOS &UserId)
{
    if (this->LocalUsers.Contains(UserId))
    {
        // Channels have references to their owning users, so we have to clear out the joined channels so the users
        // don't stay alive due to circular references.
        this->LocalUsers[UserId]->JoinedChannels.Empty();
    }
    this->LocalUsers.Remove(UserId);
}

void FEOSVoiceManager::RemoveAllLocalUsers()
{
    for (const auto &KV : this->LocalUsers)
    {
        // Channels have references to their owning users, so we have to clear out the joined channels so the users
        // don't stay alive due to circular references.
        KV.Value->JoinedChannels.Empty();
    }
    this->LocalUsers.Empty();
}

TSharedPtr<FEOSVoiceManagerLocalUser> FEOSVoiceManager::GetLocalUser(const FUniqueNetIdEOS &UserId)
{
    if (this->LocalUsers.Contains(UserId))
    {
        return this->LocalUsers[UserId];
    }
    return nullptr;
}

#endif // #if EOS_HAS_AUTHENTICATION
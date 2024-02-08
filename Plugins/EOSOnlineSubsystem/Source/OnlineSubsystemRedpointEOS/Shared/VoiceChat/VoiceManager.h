// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

#include "RedpointEOSConfig/Config.h"
#include "OnlineSubsystemRedpointEOS/Shared/UniqueNetIdEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/VoiceChat/VoiceManagerLocalUser.h"
#include "OnlineSubsystemRedpointEOS/Shared/VoiceChat/VoiceManagerDeviceList.h"

#if EOS_HAS_AUTHENTICATION

class ONLINESUBSYSTEMREDPOINTEOS_API FEOSVoiceManager : public TSharedFromThis<FEOSVoiceManager>
{
    friend class FEOSVoiceManagerLocalUser;

private:
    EOS_HPlatform EOSPlatform;
    TSharedRef<Redpoint::EOS::Config::IConfig> Config;
    TSharedRef<IOnlineIdentity, ESPMode::ThreadSafe> Identity;
    TUserIdMap<TSharedPtr<FEOSVoiceManagerLocalUser>> LocalUsers;
    TArray<TPair<TSharedRef<const FUniqueNetIdEOS>, TSharedRef<const FOnlinePartyId>>> QueuedEchoEnabledLobbies;
    TSharedRef<FEOSVoiceManagerDeviceList> DeviceList;

    TSharedPtr<EOSEventHandle<EOS_Lobby_LobbyMemberStatusReceivedCallbackInfo>> Unregister_LobbyMemberStatusReceived;

    void Internal_UserJoinedLobby(
        const TSharedRef<const FUniqueNetIdEOS> &UserId,
        const TSharedRef<const FOnlinePartyIdEOS> &LobbyId,
        EOS_HLobby EOSLobby);
    void Internal_UserLeftLobby(
        const TSharedRef<const FUniqueNetIdEOS> &UserId,
        const TSharedRef<const FOnlinePartyIdEOS> &LobbyId,
        EOS_HLobby EOSLobby);

    void Handle_LobbyMemberStatusReceived(const EOS_Lobby_LobbyMemberStatusReceivedCallbackInfo *Data);

public:
    FEOSVoiceManager(
        EOS_HPlatform InPlatform,
        TSharedRef<Redpoint::EOS::Config::IConfig> InConfig,
        TSharedRef<IOnlineIdentity, ESPMode::ThreadSafe> InIdentity);
    UE_NONCOPYABLE(FEOSVoiceManager);
    virtual ~FEOSVoiceManager(){};
    void RegisterEvents();

	void ScheduleUserSynchronisationIfNeeded();

    void MarkPartyOrLobbyAsEchoEnabled(
        const TSharedRef<const FUniqueNetIdEOS> &InUserId,
        const TSharedRef<const FOnlinePartyId> &InPartyOrLobbyId);

    void UserManuallyJoinedLobby(const FUniqueNetIdEOS &UserId, const FOnlinePartyIdEOS &LobbyId);
    void UserManuallyLeftLobby(const FUniqueNetIdEOS &UserId, const FOnlinePartyIdEOS &LobbyId);

    void AddLocalUser(const FUniqueNetIdEOS &UserId);
    void RemoveLocalUser(const FUniqueNetIdEOS &UserId);
    void RemoveAllLocalUsers();
    TSharedPtr<FEOSVoiceManagerLocalUser> GetLocalUser(const FUniqueNetIdEOS &UserId);
};

#endif // #if EOS_HAS_AUTHENTICATION
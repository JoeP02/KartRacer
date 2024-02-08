// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EOSCommon.h"
#include "EOSDefines.h"
#include "IPAddress.h"
#include "OnlineSubsystemRedpointEOS/Shared/AntiCheat/AntiCheat.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineSubsystemImplBase.h"
#include "OnlineSubsystemRedpointEOSModule.h"
#include "RedpointEOSAPI/Platform.h"
#include "RedpointEOSConfig/Config.h"
#include "RedpointEOSCore/RuntimePlatform.h"
#include "RedpointEOSCore/Module.h"
#include "RedpointEOSCore/Utils/RegulatedTicker.h"

EOS_ENABLE_STRICT_WARNINGS

class ONLINESUBSYSTEMREDPOINTEOS_API FOnlineSubsystemEOS
    : public FOnlineSubsystemImplBase,
      public TSharedFromThis<FOnlineSubsystemEOS, ESPMode::ThreadSafe>
{
    friend class FOnlineSubsystemRedpointEASFactory;
    friend class FSocketSubsystemEOS;
    friend class UEOSNetDriver;
    friend class FCleanShutdown;
    friend class FOnlineSubsystemEOS_Networking_P2PPacketOrderingSDK_Manager;
    friend class FOnlineSubsystemEOS_Networking_P2PPacketOrderingSocket_Manager;
    friend class FOnlineSubsystemEOS_Networking_P2PPacketOrderingRPC_Manager;
    friend class FOnlineSubsystemEOS_MessagingHubTest;
    friend class FGameplayDebuggerCategory_P2PConnections;
    friend class FOnlineIdentityInterfaceEOS;

private:
    Redpoint::EOS::API::FPlatformOptionalRefCountedHandle PlatformHandle;
    FOnlineSubsystemRedpointEOSModule *Module;
    TSharedPtr<Redpoint::EOS::Config::IConfig> Config;
    FDelegateHandle TickerHandle;
    TSharedPtr<class FEOSUserFactory, ESPMode::ThreadSafe> UserFactory;
    TSharedPtr<IAntiCheat> AntiCheat;
#if EOS_HAS_AUTHENTICATION
    TSharedPtr<class FEOSVoiceManager> VoiceManager;
    TSharedPtr<class FOnlineVoiceInterfaceEOS, ESPMode::ThreadSafe> VoiceImpl;
#endif // #if EOS_HAS_AUTHENTICATION
    TSharedPtr<class FOnlineVoiceAdminInterfaceEOS, ESPMode::ThreadSafe> VoiceAdminImpl;
#if EOS_HAS_ORCHESTRATORS
    TSharedPtr<class IServerOrchestrator> ServerOrchestrator;
#endif // #if EOS_HAS_ORCHESTRATORS
#if EOS_HAS_AUTHENTICATION
    TSharedPtr<class FOnlineSubsystemRedpointEAS, ESPMode::ThreadSafe> SubsystemEAS;
    TSharedPtr<class FOnlineLobbyInterfaceEOS, ESPMode::ThreadSafe> LobbyImpl;
    TSharedPtr<class FOnlineFriendsInterfaceSynthetic, ESPMode::ThreadSafe> FriendsImpl;
    TSharedPtr<class FOnlinePresenceInterfaceSynthetic, ESPMode::ThreadSafe> PresenceImpl;
    TSharedPtr<class FOnlinePartySystemEOS, ESPMode::ThreadSafe> PartyImpl;
    TSharedPtr<class FOnlineUserCloudInterfaceEOS, ESPMode::ThreadSafe> UserCloudImpl;
    TSharedPtr<class FSyntheticPartySessionManager> SyntheticPartySessionManager;
    TSharedPtr<class FOnlineAvatarInterfaceSynthetic, ESPMode::ThreadSafe> AvatarImpl;
    TSharedPtr<class FOnlineExternalUIInterfaceEOS, ESPMode::ThreadSafe> ExternalUIImpl;
#endif // #if EOS_HAS_AUTHENTICATION
    TSharedPtr<class FOnlineSessionInterfaceEOS, ESPMode::ThreadSafe> SessionImpl;
    TSharedPtr<class FOnlineIdentityInterfaceEOS, ESPMode::ThreadSafe> IdentityImpl;
    TSharedPtr<class FOnlineUserInterfaceEOS, ESPMode::ThreadSafe> UserImpl;
    TSharedPtr<class FOnlineTitleFileInterfaceEOS, ESPMode::ThreadSafe> TitleFileImpl;
    TSharedPtr<class FOnlineAchievementsInterfaceEOS, ESPMode::ThreadSafe> AchievementsImpl;
    TSharedPtr<class FOnlineStatsInterfaceEOS, ESPMode::ThreadSafe> StatsImpl;
    TSharedPtr<class FOnlineLeaderboardsInterfaceEOS, ESPMode::ThreadSafe> LeaderboardsImpl;
    TSharedPtr<class FOnlineEntitlementsInterfaceSynthetic, ESPMode::ThreadSafe> EntitlementsImpl;
    TSharedPtr<class FOnlineStoreInterfaceV2Synthetic, ESPMode::ThreadSafe> StoreV2Impl;
    TSharedPtr<class FOnlinePurchaseInterfaceSynthetic, ESPMode::ThreadSafe> PurchaseImpl;
    FDelegateHandle OnPreExitHandle;
    TSharedPtr<class ISocketSubsystemEOS> SocketSubsystem;
    TSharedPtr<class IMessagingHub> MessagingHub;
    bool bConfigCanBeSwitched;
    bool bDidEarlyDestroyForEditor;

    void RegisterListeningAddress(
        EOS_ProductUserId InProductUserId,
        TSharedRef<const FInternetAddr> InInternetAddr,
        TArray<TSharedPtr<FInternetAddr>> InDeveloperInternetAddrs);
    void DeregisterListeningAddress(EOS_ProductUserId InProductUserId, TSharedRef<const FInternetAddr> InInternetAddr);

    bool RegulatedTick(float DeltaTime);

public:
    UE_NONCOPYABLE(FOnlineSubsystemEOS);
    FOnlineSubsystemEOS() = delete;
    FOnlineSubsystemEOS(
        FName InInstanceName,
        FOnlineSubsystemRedpointEOSModule *InModule,
        const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig);
    ~FOnlineSubsystemEOS();

    const Redpoint::EOS::Config::IConfig &GetConfig() const
    {
        return *this->Config;
    }
    const Redpoint::EOS::Core::IRuntimePlatform &GetRuntimePlatform() const
    {
        return *Redpoint::EOS::Core::FModule::GetModuleChecked().GetRuntimePlatform();
    }

    FORCEINLINE bool IsPlatformInstanceValid() const
    {
        return this->PlatformHandle.IsValid();
    }

    virtual EOS_HPlatform GetPlatformInstance() const;

    virtual bool IsEnabled() const override;
    virtual bool Tick(float DeltaTime);
    virtual bool Exec(UWorld *InWorld, const TCHAR *Cmd, FOutputDevice &Ar) override;

    virtual IOnlineSessionPtr GetSessionInterface() const override;
    virtual IOnlineFriendsPtr GetFriendsInterface() const override;
    virtual IOnlineIdentityPtr GetIdentityInterface() const override;
    virtual IOnlinePresencePtr GetPresenceInterface() const override;
    virtual IOnlinePartyPtr GetPartyInterface() const override;
    virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;
    virtual IOnlineTournamentPtr GetTournamentInterface() const override;
    virtual IOnlineUserPtr GetUserInterface() const override;
    virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;
    virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;
    virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;
    virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;
    virtual IOnlineStatsPtr GetStatsInterface() const override;
    virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;
    virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;
    virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;
    virtual IOnlinePurchasePtr GetPurchaseInterface() const override;
    virtual TSharedPtr<class FEOSVoiceManager> GetVoiceManager() const;
    virtual IOnlineVoicePtr GetVoiceInterface() const override;

    // Our custom interfaces. Note that even those these APIs return a UObject*, we return
    // non-UObjects that are TSharedFromThis.
    virtual class UObject *GetNamedInterface(FName InterfaceName) override;

    virtual bool Init() override;
    virtual bool Shutdown() override;
    void RealShutdown();

    virtual FString GetAppId() const override;

    virtual FText GetOnlineServiceName(void) const override;

    bool IsTrueDedicatedServer() const;
};

EOS_DISABLE_STRICT_WARNINGS
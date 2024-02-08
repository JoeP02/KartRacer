// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Shared/OnlineSubsystemRedpointEOS.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Misc/CoreDelegates.h"
#include "Misc/MessageDialog.h"
#include "Misc/Parse.h"
#include "OnlineSubsystemRedpointEOS/Private/NetworkingStack/Full/SocketSubsystemEOSFull.h"
#include "OnlineSubsystemRedpointEOS/Private/NetworkingStack/ISocketSubsystemEOS.h"
#include "OnlineSubsystemRedpointEOS/Private/OnlineAvatarInterfaceSynthetic.h"
#include "OnlineSubsystemRedpointEOS/Private/OnlineLobbyInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Private/OnlineVoiceAdminInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Private/Orchestrator/AgonesServerOrchestrator.h"
#include "OnlineSubsystemRedpointEOS/Shared/AntiCheat/EOSDedicatedServerAntiCheat.h"
#include "OnlineSubsystemRedpointEOS/Shared/AntiCheat/EOSGameAntiCheat.h"
#include "OnlineSubsystemRedpointEOS/Shared/AntiCheat/EditorAntiCheat.h"
#include "OnlineSubsystemRedpointEOS/Shared/AntiCheat/NullAntiCheat.h"
#include "OnlineSubsystemRedpointEOS/Shared/Authentication/CrossPlatform/CrossPlatformAccountId.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineIdentityInterfaceEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineSubsystemRedpointEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/MessagingHub/CloudMessagingHub.h"
#include "OnlineSubsystemRedpointEOS/Shared/MessagingHub/IMessagingHub.h"
#include "OnlineSubsystemRedpointEOS/Shared/MessagingHub/P2PMessagingHub.h"
#include "OnlineSubsystemRedpointEOS/Shared/MultiOperation.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineAchievementsInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineEntitlementsInterfaceSynthetic.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineExternalUIInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineFriendsInterfaceSynthetic.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineIdentityInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineLeaderboardsInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlinePartyInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlinePresenceInterfaceSynthetic.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlinePurchaseInterfaceSynthetic.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineSessionInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineStatsInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineStoreInterfaceV2Synthetic.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineTitleFileInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineUserCloudInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineUserEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineUserInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineVoiceInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/SyntheticPartySessionManager.h"
#include "OnlineSubsystemRedpointEOS/Shared/VoiceChat/VoiceManager.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"
#include "RedpointEOSConfig/Config.h"
#include "RedpointEOSCore/InstancePool.h"
#include "RedpointEOSCore/RuntimePlatform.h"
#if EOS_HAS_AUTHENTICATION
#include "OnlineSubsystemRedpointEOS/Shared/Authentication/CrossPlatform/EpicGames/TryDeveloperAuthenticationEASCredentialsNode.h"
#endif // #if EOS_HAS_AUTHENTICATION

EOS_ENABLE_STRICT_WARNINGS

#define LOCTEXT_NAMESPACE "FOnlineSubsystemRedpointEOSModule"

FOnlineSubsystemEOS::FOnlineSubsystemEOS(
    FName InInstanceName,
    FOnlineSubsystemRedpointEOSModule *InModule,
    const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig)
    : FOnlineSubsystemImplBase(REDPOINT_EOS_SUBSYSTEM, InInstanceName)
    , PlatformHandle()
    , Module(InModule)
    , Config(InConfig)
    , TickerHandle()
    , UserFactory(nullptr)
    , AntiCheat(nullptr)
#if EOS_HAS_AUTHENTICATION
    , VoiceManager(nullptr)
    , VoiceImpl(nullptr)
#endif // #if EOS_HAS_AUTHENTICATION
    , VoiceAdminImpl(nullptr)
#if EOS_HAS_ORCHESTRATORS
    , ServerOrchestrator(nullptr)
#endif // #if EOS_HAS_ORCHESTRATORS
#if EOS_HAS_AUTHENTICATION
    , SubsystemEAS(nullptr)
    , LobbyImpl(nullptr)
    , FriendsImpl(nullptr)
    , PresenceImpl(nullptr)
    , PartyImpl(nullptr)
    , UserCloudImpl(nullptr)
    , SyntheticPartySessionManager(nullptr)
    , AvatarImpl(nullptr)
#endif // #if EOS_HAS_AUTHENTICATION
    , SessionImpl(nullptr)
    , IdentityImpl(nullptr)
    , UserImpl(nullptr)
    , TitleFileImpl(nullptr)
    , AchievementsImpl(nullptr)
    , StatsImpl(nullptr)
    , LeaderboardsImpl(nullptr)
    , EntitlementsImpl(nullptr)
    , StoreV2Impl(nullptr)
    , PurchaseImpl(nullptr)
    , OnPreExitHandle()
    , SocketSubsystem(nullptr)
    , bConfigCanBeSwitched(true)
    , bDidEarlyDestroyForEditor(false)
{
    Module->SubsystemInstances.Add(this->InstanceName, this);
}

FOnlineSubsystemEOS::~FOnlineSubsystemEOS()
{
    if (!this->bDidEarlyDestroyForEditor)
    {
        Module->SubsystemInstances.Remove(this->InstanceName);
    }
}

bool FOnlineSubsystemEOS::IsEnabled() const
{
    return true;
}

EOS_HPlatform FOnlineSubsystemEOS::GetPlatformInstance() const
{
    return this->PlatformHandle->Instance()->Handle();
}

void FOnlineSubsystemEOS::RegisterListeningAddress(
    EOS_ProductUserId InProductUserId,
    TSharedRef<const FInternetAddr> InInternetAddr,
    TArray<TSharedPtr<FInternetAddr>> InDeveloperInternetAddrs)
{
    check(this->SessionImpl.IsValid());

    StaticCastSharedPtr<FOnlineSessionInterfaceEOS>(this->SessionImpl)
        ->RegisterListeningAddress(InProductUserId, MoveTemp(InInternetAddr), MoveTemp(InDeveloperInternetAddrs));
}

void FOnlineSubsystemEOS::DeregisterListeningAddress(
    EOS_ProductUserId InProductUserId,
    TSharedRef<const FInternetAddr> InInternetAddr)
{
    check(this->SessionImpl.IsValid());

    StaticCastSharedPtr<FOnlineSessionInterfaceEOS>(this->SessionImpl)
        ->DeregisterListeningAddress(InProductUserId, MoveTemp(InInternetAddr));
}

IOnlineSessionPtr FOnlineSubsystemEOS::GetSessionInterface() const
{
    return this->SessionImpl;
}

IOnlineFriendsPtr FOnlineSubsystemEOS::GetFriendsInterface() const
{
#if EOS_HAS_AUTHENTICATION
    return this->FriendsImpl;
#else
    return nullptr;
#endif // #if EOS_HAS_AUTHENTICATION
}

IOnlineIdentityPtr FOnlineSubsystemEOS::GetIdentityInterface() const
{
    return this->IdentityImpl;
}

IOnlinePresencePtr FOnlineSubsystemEOS::GetPresenceInterface() const
{
#if EOS_HAS_AUTHENTICATION
    return this->PresenceImpl;
#else
    return nullptr;
#endif // #if EOS_HAS_AUTHENTICATION
}

IOnlinePartyPtr FOnlineSubsystemEOS::GetPartyInterface() const
{
#if EOS_HAS_AUTHENTICATION
    return this->PartyImpl;
#else
    return nullptr;
#endif // #if EOS_HAS_AUTHENTICATION
}

IOnlineUserPtr FOnlineSubsystemEOS::GetUserInterface() const
{
    return this->UserImpl;
}

IOnlineUserCloudPtr FOnlineSubsystemEOS::GetUserCloudInterface() const
{
#if EOS_HAS_AUTHENTICATION
    return this->UserCloudImpl;
#else
    return nullptr;
#endif // #if EOS_HAS_AUTHENTICATION
}

IOnlineTitleFilePtr FOnlineSubsystemEOS::GetTitleFileInterface() const
{
    return this->TitleFileImpl;
}

IOnlineLeaderboardsPtr FOnlineSubsystemEOS::GetLeaderboardsInterface() const
{
    return this->LeaderboardsImpl;
}

IOnlineEntitlementsPtr FOnlineSubsystemEOS::GetEntitlementsInterface() const
{
    return this->EntitlementsImpl;
}

IOnlineStoreV2Ptr FOnlineSubsystemEOS::GetStoreV2Interface() const
{
    return this->StoreV2Impl;
}

IOnlinePurchasePtr FOnlineSubsystemEOS::GetPurchaseInterface() const
{
    return this->PurchaseImpl;
}

IOnlineAchievementsPtr FOnlineSubsystemEOS::GetAchievementsInterface() const
{
    return this->AchievementsImpl;
}

IOnlineStatsPtr FOnlineSubsystemEOS::GetStatsInterface() const
{
    return this->StatsImpl;
}

IOnlineExternalUIPtr FOnlineSubsystemEOS::GetExternalUIInterface() const
{
#if EOS_HAS_AUTHENTICATION
    return this->ExternalUIImpl;
#else
    return nullptr;
#endif // #if EOS_HAS_AUTHENTICATION
}

TSharedPtr<FEOSVoiceManager> FOnlineSubsystemEOS::GetVoiceManager() const
{
#if EOS_HAS_AUTHENTICATION
    return this->VoiceManager;
#else
    return nullptr;
#endif // #if EOS_HAS_AUTHENTICATION
}

IOnlineVoicePtr FOnlineSubsystemEOS::GetVoiceInterface() const
{
#if EOS_HAS_AUTHENTICATION
    return this->VoiceImpl;
#else
    return nullptr;
#endif // #if EOS_HAS_AUTHENTICATION
}

class UObject *FOnlineSubsystemEOS::GetNamedInterface(FName InterfaceName)
{
#if EOS_HAS_AUTHENTICATION
    if (InterfaceName.IsEqual(ONLINE_LOBBY_INTERFACE_NAME))
    {
        return (class UObject *)(void *)&this->LobbyImpl;
    }
    if (InterfaceName.IsEqual(ONLINE_AVATAR_INTERFACE_NAME))
    {
        return (class UObject *)(void *)&this->AvatarImpl;
    }
#endif // #if EOS_HAS_AUTHENTICATION
    if (InterfaceName.IsEqual(ONLINE_VOICE_ADMIN_INTERFACE_NAME))
    {
        return (class UObject *)(void *)&this->VoiceAdminImpl;
    }

    return FOnlineSubsystemImpl::GetNamedInterface(InterfaceName);
}

IOnlineTurnBasedPtr FOnlineSubsystemEOS::GetTurnBasedInterface() const
{
    return nullptr;
}

IOnlineTournamentPtr FOnlineSubsystemEOS::GetTournamentInterface() const
{
    return nullptr;
}

bool FOnlineSubsystemEOS::Init()
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSOnlineSubsystemInit);

    bool bIsDedicatedServer = this->IsTrueDedicatedServer();
    auto RuntimePlatform = Redpoint::EOS::Core::FModule::GetModuleChecked().GetRuntimePlatform();

    this->PlatformHandle = this->Config.IsValid()
                               ? Redpoint::EOS::Core::IInstancePool::Pool().CreateWithConfig(
                                     this->InstanceName,
                                     this->Config.ToSharedRef())
                               : Redpoint::EOS::Core::IInstancePool::Pool().Create(this->InstanceName);
    if (this->PlatformHandle->Instance()->IsShutdown())
    {
        UE_LOG(LogRedpointEOS, Error, TEXT("Unable to initialize EOS platform."));
        if (FParse::Param(FCommandLine::Get(), TEXT("requireeos")))
        {
            checkf(
                !this->PlatformHandle->Instance()->IsShutdown(),
                TEXT("Unable to initialize EOS platform and you have -REQUIREEOS on the command line."));
        }
        return false;
    }

#if !WITH_EDITOR
    if (this->Config->GetRequireEpicGamesLauncher())
    {
        EOS_EResult RestartResult = EOS_Platform_CheckForLauncherAndRestart(this->PlatformHandle->Instance()->Handle());
        if (RestartResult == EOS_EResult::EOS_Success)
        {
            UE_LOG(
                LogRedpointEOS,
                Warning,
                TEXT("Game is restarting because it was not launched through the Epic Games Launcher."));
            FGenericPlatformMisc::RequestExit(false);
            return false;
        }
        else if (RestartResult == EOS_EResult::EOS_NoChange)
        {
            UE_LOG(LogRedpointEOS, Verbose, TEXT("Game was already launched through the Epic Games Launcher."));
        }
        else if (RestartResult == EOS_EResult::EOS_UnexpectedError)
        {
            UE_LOG(
                LogRedpointEOS,
                Warning,
                TEXT("Game is exiting because EOS_Platform_CheckForLauncherAndRestart failed to return an expected "
                     "result."));
            FMessageDialog::Open(
                EAppMsgType::Ok,
                LOCTEXT(
                    "OnlineSubsystemEOS_EGSRestartFailed",
                    "Unable to detect if the game was launched through the Epic Games Launcher. Please reinstall the "
                    "application."));
            FGenericPlatformMisc::RequestExit(false);
            return false;
        }
    }
#endif

    // Initialize the interfaces.
    if (this->Config->GetEnableAntiCheat())
    {
#if WITH_EDITOR
        // We're running in the editor, so we use an implementation that emulates Anti-Cheat calls.
        this->AntiCheat = MakeShared<FEditorAntiCheat>();
#else
#if WITH_SERVER_CODE
        if (bIsDedicatedServer)
        {
            // This is a dedicated server and uses a different set of EAC APIs from clients.
            this->AntiCheat = MakeShared<FEOSDedicatedServerAntiCheat>(this->PlatformHandle->Instance()->Handle());
        }
        else
#endif // #if WITH_SERVER_CODE
        {
            // This is a client either protected by EAC, or a client that should have a trusted
            // client private key for authenticating against peers.
            this->AntiCheat = MakeShared<FEOSGameAntiCheat>(
                this->PlatformHandle->Instance()->Handle(),
                !this->Config->GetTrustedClientPrivateKey().IsEmpty());
        }
#endif // #if WITH_EDITOR
    }
    else
    {
        // This game doesn't have Anti-Cheat enabled, so there won't be any instances of the game
        // that require EAC functionality.
        this->AntiCheat = MakeShared<FNullAntiCheat>();
    }
    if (!this->AntiCheat->Init())
    {
        UE_LOG(LogRedpointEOS, Error, TEXT("Anti-Cheat failed to initialize!"));
        FPlatformMisc::RequestExit(true);
        return false;
    }

    this->UserFactory = MakeShared<FEOSUserFactory, ESPMode::ThreadSafe>(
        this->GetInstanceName(),
        this->PlatformHandle->Instance()->Handle(),
        RuntimePlatform);

#if EOS_HAS_AUTHENTICATION
    if (!bIsDedicatedServer)
    {
        this->SubsystemEAS =
            MakeShared<FOnlineSubsystemRedpointEAS, ESPMode::ThreadSafe>(this->InstanceName, this->AsShared());
        verifyf(this->SubsystemEAS->Init(), TEXT("EAS Subsystem did not Init successfully! This should not happen."));
    }
#endif

    TSharedPtr<FOnlineIdentityInterfaceEAS, ESPMode::ThreadSafe> IdentityEAS = nullptr;
#if EOS_HAS_AUTHENTICATION
    if (!bIsDedicatedServer)
    {
        IdentityEAS = StaticCastSharedPtr<FOnlineIdentityInterfaceEAS>(this->SubsystemEAS->GetIdentityInterface());
    }
#endif
    auto IdentityEOS = MakeShared<FOnlineIdentityInterfaceEOS, ESPMode::ThreadSafe>(
        this->AsShared(),
        this->PlatformHandle->Instance()->Handle(),
        this->GetInstanceName().ToString(),
        bIsDedicatedServer,
        IdentityEAS,
        RuntimePlatform,
        this->Config.ToSharedRef(),
        this->UserFactory.ToSharedRef(),
        this->AsShared());
    IdentityEOS->RegisterEvents();
    this->IdentityImpl = IdentityEOS;

    this->UserImpl = MakeShared<FOnlineUserInterfaceEOS, ESPMode::ThreadSafe>(
        this->PlatformHandle->Instance()->Handle(),
#if EOS_HAS_AUTHENTICATION
        bIsDedicatedServer ? nullptr : this->SubsystemEAS,
#else
        nullptr,
#endif
        IdentityEOS,
        this->UserFactory.ToSharedRef());

#if EOS_HAS_AUTHENTICATION
    this->VoiceManager = MakeShared<FEOSVoiceManager>(
        this->PlatformHandle->Instance()->Handle(),
        this->Config.ToSharedRef(),
        this->IdentityImpl.ToSharedRef());
    this->IdentityImpl->VoiceManager = this->VoiceManager;
    this->VoiceManager->RegisterEvents();
#endif
    EOS_HRTCAdmin EOSRTCAdmin = EOS_Platform_GetRTCAdminInterface(this->PlatformHandle->Instance()->Handle());
    if (EOSRTCAdmin != nullptr)
    {
        this->VoiceAdminImpl = MakeShared<FOnlineVoiceAdminInterfaceEOS, ESPMode::ThreadSafe>(EOSRTCAdmin);
    }
#if EOS_HAS_AUTHENTICATION
    this->VoiceImpl = MakeShared<FOnlineVoiceInterfaceEOS, ESPMode::ThreadSafe>(
        this->VoiceManager.ToSharedRef(),
        this->IdentityImpl.ToSharedRef());
#endif

    this->SocketSubsystem = MakeShared<FSocketSubsystemEOSFull>(
        this->AsShared(),
        this->PlatformHandle->Instance()->Handle(),
        this->Config.ToSharedRef());

    // @todo: Handle errors more gracefully.
    FString SocketSubsystemError;
    this->SocketSubsystem->Init(SocketSubsystemError);

    if (this->Config->GetCloudMessagingHubUrl().IsEmpty())
    {
        auto P2PMessagingHub =
            MakeShared<FP2PMessagingHub>(this->IdentityImpl.ToSharedRef(), this->SocketSubsystem.ToSharedRef());
        P2PMessagingHub->RegisterEvents();
        this->MessagingHub = P2PMessagingHub;
    }
    else
    {
        auto CloudMessagingHub =
            MakeShared<FCloudMessagingHub>(this->PlatformHandle->Instance(), this->Config.ToSharedRef());
        this->MessagingHub = CloudMessagingHub;
    }
    this->IdentityImpl->AttachMessagingHub(this->MessagingHub.ToSharedRef());

#if EOS_HAS_ORCHESTRATORS
    if (bIsDedicatedServer)
    {
        FString IgnoreOverridePort = FPlatformMisc::GetEnvironmentVariable(TEXT("EOS_IGNORE_ORCHESTRATOR"));
        if (IgnoreOverridePort != TEXT("true"))
        {
            TSharedPtr<FAgonesServerOrchestrator> AgonesOrchestrator = MakeShared<FAgonesServerOrchestrator>();
            if (AgonesOrchestrator->IsEnabled())
            {
                this->ServerOrchestrator = AgonesOrchestrator;
                this->ServerOrchestrator->Init();
            }
        }
    }
#endif // #if EOS_HAS_ORCHESTRATORS

#if EOS_HAS_AUTHENTICATION
    TSharedPtr<FOnlinePartySystemEOS, ESPMode::ThreadSafe> EOSPartyImpl;
    if (!bIsDedicatedServer)
    {
        this->UserCloudImpl =
            MakeShared<FOnlineUserCloudInterfaceEOS, ESPMode::ThreadSafe>(this->PlatformHandle->Instance()->Handle());

        this->FriendsImpl = MakeShared<FOnlineFriendsInterfaceSynthetic, ESPMode::ThreadSafe>(
            this->GetInstanceName(),
            this->PlatformHandle->Instance()->Handle(),
            this->IdentityImpl.ToSharedRef(),
            this->UserCloudImpl.ToSharedRef(),
            this->MessagingHub.ToSharedRef(),
            this->SubsystemEAS,
            RuntimePlatform,
            this->Config.ToSharedRef(),
            this->UserFactory.ToSharedRef());
        this->FriendsImpl->RegisterEvents();

        this->AvatarImpl = MakeShared<FOnlineAvatarInterfaceSynthetic, ESPMode::ThreadSafe>(
            this->GetInstanceName(),
            this->Config.ToSharedRef(),
            this->IdentityImpl,
            this->FriendsImpl,
            this->UserImpl);

        this->PresenceImpl = MakeShared<FOnlinePresenceInterfaceSynthetic, ESPMode::ThreadSafe>(
            this->GetInstanceName(),
            this->IdentityImpl.ToSharedRef(),
            this->FriendsImpl.ToSharedRef(),
            this->SubsystemEAS,
            this->Config.ToSharedRef());
        this->PresenceImpl->RegisterEvents();

        EOSPartyImpl = MakeShared<FOnlinePartySystemEOS, ESPMode::ThreadSafe>(
            this->PlatformHandle->Instance()->Handle(),
            this->Config.ToSharedRef(),
            this->IdentityImpl.ToSharedRef(),
            this->FriendsImpl.ToSharedRef(),
            this->UserFactory.ToSharedRef(),
            this->VoiceManager.ToSharedRef());
        EOSPartyImpl->RegisterEvents();
        this->PartyImpl = EOSPartyImpl;

        this->LobbyImpl = MakeShared<FOnlineLobbyInterfaceEOS, ESPMode::ThreadSafe>(
            this->PlatformHandle->Instance()->Handle(),
            this->AsShared(),
            this->VoiceManager.ToSharedRef());
        this->LobbyImpl->RegisterEvents();
    }
#endif // #if EOS_HAS_AUTHENTICATION

    auto EOSSessionImpl = MakeShared<FOnlineSessionInterfaceEOS, ESPMode::ThreadSafe>(
        this->PlatformHandle->Instance()->Handle(),
        IdentityEOS,
#if EOS_HAS_AUTHENTICATION
        bIsDedicatedServer ? nullptr : FriendsImpl,
#else
        nullptr,
#endif
#if EOS_HAS_ORCHESTRATORS
        this->ServerOrchestrator,
#endif // #if EOS_HAS_ORCHESTRATORS
        this->Config.ToSharedRef());
    EOSSessionImpl->RegisterEvents();
    this->SessionImpl = EOSSessionImpl;
    this->TitleFileImpl = MakeShared<FOnlineTitleFileInterfaceEOS, ESPMode::ThreadSafe>(
        this->PlatformHandle->Instance()->Handle(),
        IdentityEOS);
    this->StatsImpl = MakeShared<FOnlineStatsInterfaceEOS, ESPMode::ThreadSafe>(
        this->PlatformHandle->Instance()->Handle(),
        this->Config.ToSharedRef(),
        this->GetInstanceName());
    auto EOSAchievementsImpl = MakeShared<FOnlineAchievementsInterfaceEOS, ESPMode::ThreadSafe>(
        this->PlatformHandle->Instance()->Handle(),
        this->StatsImpl,
        this->Config.ToSharedRef());
    EOSAchievementsImpl->RegisterEvents();
    this->AchievementsImpl = EOSAchievementsImpl;
    this->LeaderboardsImpl = MakeShared<FOnlineLeaderboardsInterfaceEOS, ESPMode::ThreadSafe>(
        this->PlatformHandle->Instance()->Handle(),
        this->StatsImpl,
        this->IdentityImpl
#if EOS_HAS_AUTHENTICATION
        ,
        bIsDedicatedServer ? nullptr : this->FriendsImpl
#endif // #if EOS_HAS_AUTHENTICATION
    );
    this->EntitlementsImpl =
        MakeShared<FOnlineEntitlementsInterfaceSynthetic, ESPMode::ThreadSafe>(this->IdentityImpl.ToSharedRef());
    this->StoreV2Impl =
        MakeShared<FOnlineStoreInterfaceV2Synthetic, ESPMode::ThreadSafe>(this->IdentityImpl.ToSharedRef());
    this->PurchaseImpl =
        MakeShared<FOnlinePurchaseInterfaceSynthetic, ESPMode::ThreadSafe>(this->IdentityImpl.ToSharedRef());
    this->PurchaseImpl->RegisterEvents();

#if EOS_HAS_AUTHENTICATION
    if (!bIsDedicatedServer)
    {
        this->SyntheticPartySessionManager = MakeShared<FSyntheticPartySessionManager>(
            this->GetInstanceName(),
            EOSPartyImpl,
            EOSSessionImpl,
            this->IdentityImpl,
            RuntimePlatform,
            this->Config.ToSharedRef());
        this->SyntheticPartySessionManager->RegisterEvents();
        EOSSessionImpl->SetSyntheticPartySessionManager(this->SyntheticPartySessionManager);
        EOSPartyImpl->SetSyntheticPartySessionManager(this->SyntheticPartySessionManager);

        this->ExternalUIImpl = MakeShared<FOnlineExternalUIInterfaceEOS, ESPMode::ThreadSafe>(
            this->PlatformHandle->Instance()->Handle(),
            this->IdentityImpl.ToSharedRef(),
            this->SessionImpl.ToSharedRef(),
            this->SyntheticPartySessionManager);
        this->ExternalUIImpl->RegisterEvents();
    }
#endif // #if EOS_HAS_AUTHENTICATION

    // If we are a dedicated server, call AutoLogin on the identity interface so that we have a valid
    // user ID in LocalUserNum 0 for all dedicated server operations.
    if (bIsDedicatedServer)
    {
        UE_LOG(
            LogRedpointEOS,
            Verbose,
            TEXT("Automatically calling AutoLogin for LocalUserNum 0 because the game is running as a dedicated "
                 "server"));
        this->IdentityImpl->AutoLogin(0);
    }

    // We want to shutdown ahead of other subsystems, because we will have hooks and events registered
    // to them. If those events are still registered when other subsystems try to shutdown, we'll get
    // check() fails because the shared pointers will still have references.
    this->OnPreExitHandle = FCoreDelegates::OnPreExit.AddLambda([WeakThis = GetWeakThis(this)]() {
        if (auto This = PinWeakThis(WeakThis))
        {
            This->Shutdown();
        }
    });

#if WITH_EDITOR && defined(UE_4_27_OR_LATER)
    // We need to listen for FWorldDelegates::OnStartGameInstance. When initializing a play-in-editor window,
    // the UpdateUniqueNetIdForPlayerController logic from post-login runs before the UWorld* or ULocalPlayer*
    // is created, so we can't set the unique net ID that way. However, Unreal doesn't assign the unique net ID
    // it got from logging in to the new ULocalPlayer*, so it'll be stuck with an invalid net ID.
    //
    // We listen to FWorldDelegates::OnStartGameInstance so we can fix up any ULocalPlayer* instances to have
    // the unique net ID that was signed in from "login before PIE".
    FWorldDelegates::OnStartGameInstance.AddLambda([WeakThis = GetWeakThis(this)](UGameInstance *NewGameInstance) {
        if (auto This = PinWeakThis(WeakThis))
        {
            TSoftObjectPtr<UWorld> OurWorld = FWorldResolution::GetWorld(This->GetInstanceName(), true);
            checkf(
                IsValid(NewGameInstance->GetWorld()),
                TEXT("World must be valid for new game instance in OnStartGameInstance handler."));
            if (!OurWorld.IsValid() || OurWorld.Get() != NewGameInstance->GetWorld())
            {
                return;
            }

            for (ULocalPlayer *Player : NewGameInstance->GetLocalPlayers())
            {
                if (This->IdentityImpl->GetLoginStatus(Player->GetControllerId()) == ELoginStatus::LoggedIn)
                {
                    auto ThisUniqueId = This->IdentityImpl->GetUniquePlayerId(Player->GetControllerId());
#if defined(UE_5_0_OR_LATER)
                    Player->SetCachedUniqueNetId(FUniqueNetIdRepl(ThisUniqueId));
#else
                    Player->SetCachedUniqueNetId(ThisUniqueId);
#endif // #if defined(UE_5_0_OR_LATER)
                    UE_LOG(
                        LogRedpointEOS,
                        Verbose,
                        TEXT("Updated unique net ID of ULocalPlayer for local player num %d (via "
                             "OnStartGameInstance): %s"),
                        Player->GetControllerId(),
                        *Player->GetCachedUniqueNetId()->ToString());
                }
            }
        }
    });
#endif

    this->TickerHandle = Redpoint::EOS::Core::Utils::FRegulatedTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateThreadSafeSP(this, &FOnlineSubsystemEOS::RegulatedTick));

    return true;
}

bool FOnlineSubsystemEOS::Tick(float DeltaTime)
{
    // We don't need an unregulated tick.
    return false;
}

bool FOnlineSubsystemEOS::RegulatedTick(float DeltaTime)
{
    EOS_TRACE_COUNTER_SET(CTR_EOSNetP2PReceivedLoopIters, 0);
    EOS_TRACE_COUNTER_SET(CTR_EOSNetP2PReceivedPackets, 0);
    EOS_TRACE_COUNTER_SET(CTR_EOSNetP2PReceivedBytes, 0);
    EOS_TRACE_COUNTER_SET(CTR_EOSNetP2PSentPackets, 0);
    EOS_TRACE_COUNTER_SET(CTR_EOSNetP2PSentBytes, 0);

    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSOnlineSubsystemTick);

    if (this->PlatformHandle.IsValid())
    {
#if EOS_HAS_AUTHENTICATION
        if (this->VoiceManager.IsValid())
        {
            this->VoiceManager->ScheduleUserSynchronisationIfNeeded();
        }
#endif
    }

#if EOS_HAS_AUTHENTICATION
    if (this->PartyImpl.IsValid())
    {
        // Used for event deduplication.
        StaticCastSharedPtr<FOnlinePartySystemEOS>(this->PartyImpl)->Tick();
    }
#endif // #if EOS_HAS_AUTHENTICATION

    return FOnlineSubsystemImpl::Tick(DeltaTime);
}

bool FOnlineSubsystemEOS::Exec(UWorld *InWorld, const TCHAR *Cmd, FOutputDevice &Ar)
{
    bool bWasHandled = false;

    if (FParse::Command(&Cmd, TEXT("IDENTITY")))
    {
        bWasHandled = this->IdentityImpl->Exec(InWorld, Cmd, Ar);
    }

    if (FParse::Command(&Cmd, TEXT("ANTICHEAT")))
    {
        bWasHandled = this->AntiCheat->Exec(InWorld, Cmd, Ar);
    }

    if (!bWasHandled)
    {
        bWasHandled = FOnlineSubsystemImpl::Exec(InWorld, Cmd, Ar);
    }

    return bWasHandled;
}

template <typename T, ESPMode Mode> void DestructInterface(TSharedPtr<T, Mode> &Ref, const TCHAR *Name)
{
    if (Ref.IsValid())
    {
        ensureMsgf(
            Ref.IsUnique(),
            TEXT(
                "Interface is not unique during shutdown of EOS Online Subsystem: %s. "
                "This indicates you have a TSharedPtr<> or IOnline... in your code that is holding a reference open to "
                "the interface longer than the lifetime of the online subsystem. You should use TWeakPtr<> "
                "to hold references to interfaces in class fields to prevent lifetime issues"),
            Name);
        Ref = nullptr;
    }
}

class FCleanShutdown
{
private:
    TSharedPtr<FOnlineSubsystemEOS, ESPMode::ThreadSafe> EOS;
    TSharedPtr<FOnlineSessionInterfaceEOS, ESPMode::ThreadSafe> SessionImpl;

public:
    FCleanShutdown(
        TSharedPtr<FOnlineSubsystemEOS, ESPMode::ThreadSafe> InEOS,
        TSharedPtr<FOnlineSessionInterfaceEOS, ESPMode::ThreadSafe> InSession)
        : EOS(MoveTemp(InEOS))
        , SessionImpl(MoveTemp(InSession)){};

    void Shutdown();
};

void FCleanShutdown::Shutdown()
{
#if EOS_HAS_AUTHENTICATION
    FTryDeveloperAuthenticationEASCredentialsNode::ForceLCTDeveloperInProgressMutexReset();
#endif // #if EOS_HAS_AUTHENTICATION

    // Set up a ticker so we can continue ticking (since the engine will no longer call the EOS's subsystems Tick
    // event).
    FTSTicker::FDelegateHandle TickerHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([EOS = this->EOS](float DeltaSeconds) {
            EOS->Tick(DeltaSeconds);
            return true;
        }),
        0.0f);

    TArray<FName> SessionNames;
    for (const auto &Session : this->SessionImpl->Sessions)
    {
        SessionNames.Add(Session.SessionName);
    }
    this->SessionImpl.Reset();

    FMultiOperation<FName, bool>::Run(
        SessionNames,
        [this](const FName &SessionName, const std::function<void(bool)> &OnDone) {
            UE_LOG(
                LogRedpointEOS,
                Verbose,
                TEXT(
                    "Automatically destroying up session %s for you, since you're running in the editor. Sessions will "
                    "not be automatically destroyed if you're running in standalone."),
                *SessionName.ToString());
            auto SessionNameAnsi = EOSString_SessionModification_SessionName::ToAnsiString(SessionName.ToString());
            EOS_Sessions_DestroySessionOptions Opts = {};
            Opts.ApiVersion = EOS_SESSIONS_ENDSESSION_API_LATEST;
            Opts.SessionName = SessionNameAnsi.Ptr.Get();
            EOSRunOperation<EOS_HSessions, EOS_Sessions_DestroySessionOptions, EOS_Sessions_DestroySessionCallbackInfo>(
                this->EOS->PlatformHandle->Instance()->Get<EOS_HSessions>(),
                &Opts,
                EOS_Sessions_DestroySession,
                [SessionName, OnDone](const EOS_Sessions_DestroySessionCallbackInfo *Info) {
                    if (Info->ResultCode == EOS_EResult::EOS_Success)
                    {
                        UE_LOG(
                            LogRedpointEOS,
                            Verbose,
                            TEXT("Session %s was automatically destroyed successfully."),
                            *SessionName.ToString());
                    }
                    else
                    {
                        UE_LOG(
                            LogRedpointEOS,
                            Error,
                            TEXT("Session %s could not be automatically destroyed. It may continue to exist on the "
                                 "EOS backend for a few minutes."),
                            *SessionName.ToString());
                    }
                    OnDone(true);
                });
            return true;
        },
        [this, TickerHandle](const TArray<bool> &Results) {
            // Do the real shutdown. We have to be super careful with pointers here for uniqueness checks!
            FTSTicker::GetCoreTicker().AddTicker(
                FTickerDelegate::CreateLambda([this, TickerHandle](float DeltaSeconds) {
                    FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
                    FName ShutdownName =
                        FName(FString::Printf(TEXT("%s_ShuttingDown"), *this->EOS->InstanceName.ToString()));
                    this->EOS->RealShutdown();
                    this->EOS->Module->SubsystemInstances.Remove(ShutdownName);
                    this->EOS.Reset();
                    delete this;
                    return false;
                }),
                0.0f);
        });
}

bool FOnlineSubsystemEOS::Shutdown()
{
#if WITH_EDITOR
    // bIsPerformingFullShutdown is true in *most* cases when the editor is exiting (from pressing X in the top-right
    // corner of the window). It's not perfect, but should eliminate some cases of delayed cleanup running on shutdown.
    bool bIsPerformingFullShutdown = IsEngineExitRequested();
    // WITH_EDITOR is true if you're playing "Standalone Game" from the editor, but bIsEditor will be false. We don't
    // want to do delayed cleanup for standalone games since the process will exit soon after calling ::Shutdown().
    bool bIsEditor = GIsEditor;
    if (this->PlatformHandle.IsValid() && this->SessionImpl.IsValid() && bIsEditor && !bIsPerformingFullShutdown)
    {
        // When we're running in the editor, try to destroy all sessions that we're a part of before we do the real
        // shutdown logic.
        FName ShutdownName = FName(FString::Printf(TEXT("%s_ShuttingDown"), *this->InstanceName.ToString()));
        if (Module->SubsystemInstances.Contains(ShutdownName) ||
            !Module->SubsystemInstances.Contains(this->InstanceName))
        {
            return true;
        }
        Module->SubsystemInstances.Add(ShutdownName, this);
        Module->SubsystemInstances.Remove(this->InstanceName);
        this->bDidEarlyDestroyForEditor = true;
        auto Impl = new FCleanShutdown(this->AsShared(), this->SessionImpl);
        Impl->Shutdown();
        return true;
    }
    else
    {
        // EOS didn't initialize the editor, so we don't need to clean up sessions.
        this->RealShutdown();
        return true;
    }
#else
    this->RealShutdown();
    return true;
#endif
}

void FOnlineSubsystemEOS::RealShutdown()
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSOnlineSubsystemShutdown);

    FCoreDelegates::OnPreExit.Remove(this->OnPreExitHandle);

    if (this->AntiCheat.IsValid())
    {
        this->AntiCheat->Shutdown();
    }
    if (this->IdentityImpl.IsValid())
    {
        this->IdentityImpl->DetachMessagingHub();
    }
    DestructInterface(this->AntiCheat, TEXT("AntiCheat"));
#if EOS_HAS_AUTHENTICATION
    DestructInterface(this->ExternalUIImpl, TEXT("IOnlineExternalUI"));
    DestructInterface(this->SyntheticPartySessionManager, TEXT("SyntheticPartySessionManager"));
#endif // #if EOS_HAS_AUTHENTICATION
    DestructInterface(this->PurchaseImpl, TEXT("IOnlinePurchase"));
    DestructInterface(this->StoreV2Impl, TEXT("IOnlineStoreV2"));
    DestructInterface(this->EntitlementsImpl, TEXT("IOnlineEntitlements"));
    DestructInterface(this->LeaderboardsImpl, TEXT("IOnlineLeaderboards"));
    DestructInterface(this->AchievementsImpl, TEXT("IOnlineAchievements"));
    DestructInterface(this->StatsImpl, TEXT("IOnlineStats"));
    DestructInterface(this->TitleFileImpl, TEXT("IOnlineTitleFile"));
    DestructInterface(this->SessionImpl, TEXT("IOnlineSession"));
#if EOS_HAS_AUTHENTICATION
    DestructInterface(this->PartyImpl, TEXT("IOnlinePartySystem"));
    DestructInterface(this->LobbyImpl, TEXT("IOnlineLobby"));
    DestructInterface(this->PresenceImpl, TEXT("IOnlinePresence"));
    DestructInterface(this->AvatarImpl, TEXT("IOnlineAvatar"));
    DestructInterface(this->FriendsImpl, TEXT("IOnlineFriends"));
    DestructInterface(this->UserCloudImpl, TEXT("IOnlineUserCloud"));
#endif // #if EOS_HAS_AUTHENTICATION
#if EOS_HAS_ORCHESTRATORS
    DestructInterface(this->ServerOrchestrator, TEXT("ServerOrchestrator"));
#endif // #if EOS_HAS_ORCHESTRATORS
    DestructInterface(this->MessagingHub, TEXT("MessagingHub"));
    if (this->SocketSubsystem.IsValid())
    {
        this->SocketSubsystem->Shutdown();
    }
    DestructInterface(this->SocketSubsystem, TEXT("SocketSubsystem"));
#if EOS_HAS_AUTHENTICATION
    DestructInterface(this->VoiceImpl, TEXT("IOnlineVoice"));
#endif // #if EOS_HAS_AUTHENTICATION
    DestructInterface(this->VoiceAdminImpl, TEXT("IOnlineVoiceAdmin"));
#if EOS_HAS_AUTHENTICATION
    if (this->IdentityImpl.IsValid())
    {
        this->IdentityImpl->VoiceManager.Reset();
    }
    if (this->VoiceManager.IsValid())
    {
        this->VoiceManager->RemoveAllLocalUsers();
    }
    DestructInterface(this->VoiceManager, TEXT("(internal) VoiceManager"));
#endif // #if EOS_HAS_AUTHENTICATION
    DestructInterface(this->UserImpl, TEXT("IOnlineUser"));
    DestructInterface(this->IdentityImpl, TEXT("IOnlineIdentity"));
#if EOS_HAS_AUTHENTICATION
    if (this->SubsystemEAS.IsValid())
    {
        verifyf(this->SubsystemEAS->Shutdown(), TEXT("EAS Subsystem did not shutdown successfully!"));
    }
    DestructInterface(this->SubsystemEAS, TEXT("(internal) SubsystemEAS"));
#endif // #if EOS_HAS_AUTHENTICATION
    DestructInterface(this->UserFactory, TEXT("(internal) UserFactory"));

    // Shutdown the platform.
    if (this->PlatformHandle.IsValid())
    {
        EOS_HPlatform OldHandleForLog = this->PlatformHandle->Instance()->Handle();
        this->PlatformHandle.Reset();

        UE_LOG(LogRedpointEOS, Verbose, TEXT("EOS platform %p has been released."), OldHandleForLog);
    }

    Redpoint::EOS::Core::Utils::FRegulatedTicker::GetCoreTicker().RemoveTicker(this->TickerHandle);
}

FString FOnlineSubsystemEOS::GetAppId() const
{
    return this->Config->GetClientId();
}

FText FOnlineSubsystemEOS::GetOnlineServiceName(void) const
{
    return NSLOCTEXT("EOS", "EOSPlatformName", "Epic Online Services");
}

bool FOnlineSubsystemEOS::IsTrueDedicatedServer() const
{
    // Neither IsServer nor IsDedicated work correctly in play-in-editor. Both listen servers
    // and dedicated servers return true from IsServer, but *neither* return true from IsDedicated
    // (in fact it looks like IsDedicated just doesn't do the right thing at all for single process).
    //
    // So instead implement our own version here which does the detection correctly.

#if WITH_EDITOR
    // Running multiple worlds in the editor; we need to see if this world is specifically a dedicated server.
    FName WorldContextHandle =
        (this->InstanceName != NAME_None && this->InstanceName != DefaultInstanceName) ? this->InstanceName : NAME_None;
    if (WorldContextHandle.IsNone())
    {
        // The default OSS instance is equal to IsRunningDedicatedServer(), in case the editor
        // is being run with -server for multi-process.
        return IsRunningDedicatedServer();
    }
    if (GEngine == nullptr)
    {
        UE_LOG(
            LogRedpointEOS,
            Error,
            TEXT("GEngine is not available, but EOS requires it in order to detect if it is running as a dedicated "
                 "server inside the editor! Please report this error in the EOS Online Subsystem Discord!"));
        return false;
    }
    FWorldContext *WorldContext = GEngine->GetWorldContextFromHandle(WorldContextHandle);
    if (WorldContext == nullptr)
    {
        // World context is invalid. This will occur during unit tests.
        return false;
    }
    return WorldContext->RunAsDedicated;
#else
    // Just use IsRunningDedicatedServer, since our process is either a server or it's not.
    return IsRunningDedicatedServer();
#endif
}

#undef LOCTEXT_NAMESPACE

EOS_DISABLE_STRICT_WARNINGS
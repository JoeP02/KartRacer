// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Public/OnlineSubsystemRedpointEOSModule.h"

#include "Containers/Ticker.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Misc/CommandLine.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/CoreDelegates.h"
#include "OnlineSubsystemRedpointEOS/Private/NullOSS/OnlineSubsystemRedpointNull.h"
#include "OnlineSubsystemRedpointEOS/Shared/Authentication/AuthenticationGraphRegistry.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineSubsystemRedpointEASFactory.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineSubsystemRedpointEOS.h"
#include "OnlineSubsystemUtils.h"
#include "RedpointEOSConfig/Config.h"
#include "RedpointEOSConfig/DependentModuleLoader.h"
#include "RedpointEOSConfig/EngineConfigHelpers.h"
#include "RedpointEOSConfig/IniConfig.h"
#include "RedpointEOSCore/Module.h"
#include "RedpointEOSCore/RuntimePlatform.h"
#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebugger.h"
#include "GameplayDebugger/GameplayDebuggerCategory_P2PConnections.h"
#endif // WITH_GAMEPLAY_DEBUGGER

#if PLATFORM_WINDOWS

#include "Windows/AllowWindowsPlatformTypes.h"

#include <libloaderapi.h>

#include "Windows/HideWindowsPlatformTypes.h"

#endif

EOS_ENABLE_STRICT_WARNINGS

#define LOCTEXT_NAMESPACE "FOnlineSubsystemRedpointEOSModule"

#if !defined(EOS_SDK_VERSION)
#define EOS_SDK_VERSION "NotSet"
#endif

#if WITH_EDITOR
static std::function<void(const FString &, const FString &)> *RedpointEOSEditorCustomSignalHandler = nullptr;
#endif



FOnlineSubsystemRedpointEOSModule::FOnlineSubsystemRedpointEOSModule()
    : IsRegisteredAsSubsystem(false)
    , bIsOperatingInNullMode(false)
    , SubsystemInstances()
    , EOSConfigInstance(nullptr)
    , EASSubsystemFactory(MakeShared<FOnlineSubsystemRedpointEASFactory>(this))
{
}

#if WITH_EDITOR
void FOnlineSubsystemRedpointEOSModule::SetCustomSignalHandler(
    std::function<void(const FString &, const FString &)> EditorHandler)
{
    RedpointEOSEditorCustomSignalHandler =
        new std::function<void(const FString &, const FString &)>(std::move(EditorHandler));
}

void FOnlineSubsystemRedpointEOSModule::SendCustomSignal(const FString &Context, const FString &SignalId)
{
    if (RedpointEOSEditorCustomSignalHandler != nullptr)
    {
        (*RedpointEOSEditorCustomSignalHandler)(Context, SignalId);
    }
}
#endif

#if !UE_BUILD_SHIPPING
FString FOnlineSubsystemRedpointEOSModule::GetPathToEASAutomatedTestingCredentials()
{
    return Redpoint::EOS::Core::FModule::GetModuleChecked()
        .GetRuntimePlatform()
        ->GetPathToEASAutomatedTestingCredentials();
}
#endif

bool FOnlineSubsystemRedpointEOSModule::IsFreeEdition()
{
#if defined(EOS_IS_FREE_EDITION)
    return true;
#else
    return false;
#endif
}

bool FOnlineSubsystemRedpointEOSModule::HasInstance(FName InstanceName)
{
    return this->SubsystemInstances.Contains(InstanceName);
}

void FOnlineSubsystemRedpointEOSModule::StartupModule()
{
    if (IsRunningCommandlet() && !FParse::Param(FCommandLine::Get(), TEXT("alloweosincommandlet")))
    {
        // Prevent EOS from loading during cook.
        this->bIsOperatingInNullMode = true;
    }

#if defined(EOS_IS_FREE_EDITION)
    UE_LOG(
        LogRedpointEOS,
        Warning,
        TEXT("This application is using the Free Edition of the EOS Online Subsystem plugin. The developer of this "
             "application must not be earning more than $30,000 USD in a calendar year. See "
             "https://redpoint.games/eos-online-subsystem-free-eula/ for the EOS Online Subsystem Free Edition license "
             "agreement. If you have inquiries about this notice, you can email sales@redpoint.games."));
#endif

    FModuleManager &ModuleManager = FModuleManager::Get();
    if (ModuleManager.GetModule("OnlineSubsystemEOS") != nullptr || ModuleManager.GetModule("EOSShared") != nullptr)
    {
        UE_LOG(
            LogRedpointEOS,
            Error,
            TEXT("The Epic \"Online Subsystem EOS\" or \"EOS Shared\" plugin is enabled in this project. These "
                 "plugins conflict with the Redpoint EOS plugin, and they must be disabled from the Plugins window "
                 "(with the editor restarted afterwards) before the Redpoint EOS plugin will work."));
        return;
    }

#if defined(UE_5_0_OR_LATER)
    // Add the DefaultOnlineSubsystemRedpointEOS.ini file in the project's Config directory to the static
    // INI hierarchy of OnlineSubsystemRedpointEOS.ini at the correct location in the hierarchy.
    {
        FString Filename;
        FConfigCacheIni::LoadGlobalIniFile(Filename, TEXT("OnlineSubsystemRedpointEOS"));
        if (!Filename.IsEmpty())
        {
            FConfigFile *File = Redpoint::EOS::Config::FEngineConfigHelpers::FindByName(Filename);
            if (File != nullptr)
            {
                File->AddDynamicLayerToHierarchy(
                    FConfigCacheIni::NormalizeConfigIniPath(FPaths::SourceConfigDir()) /
                    "DefaultOnlineSubsystemRedpointEOS.ini");
            }
            else
            {
                UE_LOG(
                    LogRedpointEOS,
                    Warning,
                    TEXT("Unable to apply project-specific overrides to OnlineSubsystemRedpointEOS.ini; custom net "
                         "driver settings will not be loaded."));
            }
        }
        else
        {
            UE_LOG(
                LogRedpointEOS,
                Warning,
                TEXT("Unable to determine config path for OnlineSubsystemRedpointEOS.ini; custom net "
                     "driver settings will not be loaded."));
        }
    }
#endif

    check(!this->EOSConfigInstance.IsValid());
    this->EOSConfigInstance = MakeShared<Redpoint::EOS::Config::FIniConfig>();

    if (this->bIsOperatingInNullMode)
    {
        UE_LOG(
            LogRedpointEOS,
            Verbose,
            TEXT("EOS module is operating in NULL mode, since this is a commandlet. Most functionality will be unavailable."));

        // Register the subsystem (this will generate null instances).

        auto OSS = ModuleManager.GetModule("OnlineSubsystem");
        if (OSS != nullptr)
        {
            ((FOnlineSubsystemModule *)OSS)->RegisterPlatformService(REDPOINT_EOS_SUBSYSTEM, this);
            this->IsRegisteredAsSubsystem = true;
        }
    }
    else
    {
        Redpoint::EOS::Config::FDependentModuleLoader::LoadConfigDependentModules(*this->EOSConfigInstance.Get());
        Redpoint::EOS::Config::FDependentModuleLoader::LoadPlatformDependentModules();

#if EOS_HAS_AUTHENTICATION
        // Register all the built-in authentication graphs. If you want to register your own authentication graphs, you
        // can do so inside your game's StartupModule.
        FAuthenticationGraphRegistry::RegisterDefaults();
#endif // #if EOS_HAS_AUTHENTICATION

        // Register the subsystem.
        auto OSS = ModuleManager.GetModule("OnlineSubsystem");
        if (OSS != nullptr)
        {
            ((FOnlineSubsystemModule *)OSS)->RegisterPlatformService(REDPOINT_EOS_SUBSYSTEM, this);
#if EOS_HAS_AUTHENTICATION
            ((FOnlineSubsystemModule *)OSS)
                ->RegisterPlatformService(REDPOINT_EAS_SUBSYSTEM, &this->EASSubsystemFactory.Get());
#endif
            this->IsRegisteredAsSubsystem = true;
        }

        UE_LOG(LogRedpointEOS, Verbose, TEXT("EOS module has finished starting up."));

#if WITH_GAMEPLAY_DEBUGGER
        FCoreDelegates::OnPostEngineInit.AddLambda([]() {
            IGameplayDebugger &GameplayDebuggerModule = IGameplayDebugger::Get();
            GameplayDebuggerModule.RegisterCategory(
                "P2PConnections",
                IGameplayDebugger::FOnGetCategory::CreateStatic(
                    &FGameplayDebuggerCategory_P2PConnections::MakeInstance),
                EGameplayDebuggerCategoryState::EnabledInGame,
                5);
            GameplayDebuggerModule.NotifyCategoriesChanged();
        });
#endif

#if WITH_EDITOR
        FWorldDelegates::OnPostWorldInitialization.AddLambda([](UWorld *World, const UWorld::InitializationValues IVS) {
            if (FParse::Param(FCommandLine::Get(), TEXT("eosauthorizer")))
            {
                UE_LOG(
                    LogRedpointEOS,
                    Verbose,
                    TEXT("Starting automatic editor-based authorization due to -eosauthorizer flag."));
                IOnlineSubsystem *OSS = Online::GetSubsystem(World, REDPOINT_EOS_SUBSYSTEM);
                if (OSS != nullptr)
                {
                    IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
                    Identity->AddOnLoginCompleteDelegate_Handle(
                        0,
                        FOnLoginCompleteDelegate::CreateLambda([](int32 LocalUserNum,
                                                                  bool bWasSuccessful,
                                                                  const FUniqueNetId &UserId,
                                                                  const FString &Error) {
                            if (!Error.IsEmpty() && !bWasSuccessful)
                            {
                                UE_LOG(LogRedpointEOS, Error, TEXT("The error from authentication was: %s"), *Error);
                            }

                            // Delaying this by one frame prevents a crash if the AutoLogin fails immediately (e.g. if
                            // the Free Edition user hasn't set a license key).
                            FTSTicker::GetCoreTicker().AddTicker(
                                FTickerDelegate::CreateLambda([](float DeltaSeconds) {
                                    FGenericPlatformMisc::RequestExit(false);
                                    return false;
                                }),
                                0.0f);
                        }));
                    Identity->AutoLogin(0);
                }
            }
        });
#endif
    }
}

IOnlineSubsystemPtr FOnlineSubsystemRedpointEOSModule::CreateSubsystem(FName InstanceName)
{
#if WITH_EDITOR
    if (GIsAutomationTesting)
    {
        // Automation testing, but not through a unit test. This scenario is hit when testing the networking with
        // play-in-editor.
        if (this->AutomationTestingConfigOverride.IsValid())
        {
            return this->CreateSubsystem(InstanceName, this->AutomationTestingConfigOverride.ToSharedRef());
        }
    }
#endif

    return this->CreateSubsystem(InstanceName, this->EOSConfigInstance.ToSharedRef());
}

IOnlineSubsystemPtr FOnlineSubsystemRedpointEOSModule::CreateSubsystem(
    FName InstanceName,
    const TSharedRef<Redpoint::EOS::Config::IConfig> &ConfigOverride)
{
    if (this->bIsOperatingInNullMode)
    {
        return MakeShared<FOnlineSubsystemRedpointNull, ESPMode::ThreadSafe>(InstanceName);
    }
    else
    {
        check(!SubsystemInstances.Contains(InstanceName));

        auto Inst = MakeShared<FOnlineSubsystemEOS, ESPMode::ThreadSafe>(InstanceName, this, ConfigOverride);
        if (Inst->IsEnabled())
        {
            if (!Inst->Init())
            {
                UE_LOG(LogRedpointEOS, Warning, TEXT("Unable to init EOS online subsystem."));
                Inst->Shutdown();
                return nullptr;
            }
        }
        else
        {
            UE_LOG(LogRedpointEOS, Warning, TEXT("EOS online subsystem is not enabled."));
            Inst->Shutdown();
            return nullptr;
        }

        return Inst;
    }
}

void FOnlineSubsystemRedpointEOSModule::ShutdownModule()
{
    UE_LOG(LogRedpointEOS, Verbose, TEXT("EOS module shutting down."));

    TArray<class FOnlineSubsystemEOS *> Arr;
    for (auto Subsystem : this->SubsystemInstances)
    {
        Arr.Add(Subsystem.Value);
    }
    for (auto Subsystem : Arr)
    {
        bool bStillHasSubsystem = false;
        for (auto S : this->SubsystemInstances)
        {
            if (S.Value == Subsystem)
            {
                bStillHasSubsystem = true;
            }
        }
        if (bStillHasSubsystem)
        {
            Subsystem->Shutdown();
        }
    }
    int NonShuttingDownInstances = 0;
    for (auto Subsystem : this->SubsystemInstances)
    {
        if (!Subsystem.Key.ToString().EndsWith(TEXT("_ShuttingDown")))
        {
            NonShuttingDownInstances++;
        }
    }
    ensureMsgf(
        NonShuttingDownInstances == 0,
        TEXT("Online subsystems did not cleanly shutdown on module shutdown. Ensure you are not holding references "
             "to online subsystem objects longer than the lifetime of the online subsystem."));

    if (this->IsRegisteredAsSubsystem)
    {
        FModuleManager &ModuleManager = FModuleManager::Get();
        auto OSS = ModuleManager.GetModule("OnlineSubsystem");
        if (OSS != nullptr)
        {
            ((FOnlineSubsystemModule *)OSS)->UnregisterPlatformService(REDPOINT_EAS_SUBSYSTEM);
            ((FOnlineSubsystemModule *)OSS)->UnregisterPlatformService(REDPOINT_EOS_SUBSYSTEM);
            this->IsRegisteredAsSubsystem = false;
        }
    }

    UE_LOG(LogRedpointEOS, Verbose, TEXT("EOS module shutdown complete."));

    this->EOSConfigInstance.Reset();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FOnlineSubsystemRedpointEOSModule, OnlineSubsystemRedpointEOS)

EOS_DISABLE_STRICT_WARNINGS
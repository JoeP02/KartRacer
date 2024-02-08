// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "OnlineSubsystem.h"
#include <functional>
#include "RedpointEOSConfig/Config.h"

#define ONLINESUBSYSTEMREDPOINTEOS_PACKAGE_PATH TEXT("/Script/OnlineSubsystemRedpointEOS")

EOS_ENABLE_STRICT_WARNINGS

class ONLINESUBSYSTEMREDPOINTEOS_API FOnlineSubsystemRedpointEOSModule : public IModuleInterface, public IOnlineFactory
{
    friend class FOnlineSubsystemEOS;
    friend class FOnlineSubsystemRedpointEASFactory;
    friend class FCleanShutdown;
    friend class FEOSLifecycleManager;

private:
    bool IsRegisteredAsSubsystem;
    bool bIsOperatingInNullMode;
    TMap<FName, class FOnlineSubsystemEOS *> SubsystemInstances;
    TSharedPtr<Redpoint::EOS::Config::IConfig> EOSConfigInstance;
    TSharedRef<class FOnlineSubsystemRedpointEASFactory> EASSubsystemFactory;

public:
#if WITH_EDITOR
    TSharedPtr<Redpoint::EOS::Config::IConfig> AutomationTestingConfigOverride;
    void SetCustomSignalHandler(std::function<void(const FString &, const FString &)> EditorHandler);
    void SendCustomSignal(const FString &Context, const FString &SignalId);
#endif

    FOnlineSubsystemRedpointEOSModule();
    UE_NONCOPYABLE(FOnlineSubsystemRedpointEOSModule);

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    bool IsOperatingInNullMode() const
    {
        return this->bIsOperatingInNullMode;
    }

    virtual bool SupportsDynamicReloading() override
    {
        return false;
    }

    virtual bool SupportsAutomaticShutdown() override
    {
        return false;
    }

#if !UE_BUILD_SHIPPING
    virtual FString GetPathToEASAutomatedTestingCredentials();
#endif

    bool IsFreeEdition();
    bool HasInstance(FName InstanceName);

    virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName) override;
    IOnlineSubsystemPtr CreateSubsystem(FName InstanceName, const TSharedRef<Redpoint::EOS::Config::IConfig> &ConfigOverride);
};

EOS_DISABLE_STRICT_WARNINGS
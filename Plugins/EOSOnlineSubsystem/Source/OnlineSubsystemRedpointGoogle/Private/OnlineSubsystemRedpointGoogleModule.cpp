// Copyright June Rhodes 2024. All Rights Reserved.

#include "CoreMinimal.h"
#include "LogRedpointGoogle.h"
#include "Modules/ModuleManager.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemRedpointGoogle.h"
#include "Engine/Engine.h"

class FOnlineSubsystemRedpointGoogleModule : public IModuleInterface, public IOnlineFactory
{
private:
    bool IsRegisteredAsSubsystem;

public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName) override;
};

void FOnlineSubsystemRedpointGoogleModule::StartupModule()
{
    if (IsRunningCommandlet())
    {
        return;
    }

    // Check if this was packaged for Oculus. If it was, we don't load any Google subsystem stuff.
    TArray<FString> OculusPlatforms;
    GConfig->GetArray(
        TEXT("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings"),
        TEXT("PackageForOculusMobile"),
        OculusPlatforms,
        GEngineIni);
    if (OculusPlatforms.Num() > 0)
    {
        UE_LOG(
            LogRedpointGoogle,
            Verbose,
            TEXT("Redpoint Google module is being skipped because this game has been packaged for Oculus."));
        return;
    }

    FModuleManager &ModuleManager = FModuleManager::Get();
    auto OSS = ModuleManager.GetModule("OnlineSubsystem");
    if (OSS != nullptr)
    {
        ((FOnlineSubsystemModule *)OSS)->RegisterPlatformService(REDPOINT_GOOGLE_SUBSYSTEM, this);
        this->IsRegisteredAsSubsystem = true;
    }

    UE_LOG(LogRedpointGoogle, Verbose, TEXT("Redpoint Google module has finished starting up."));
}

void FOnlineSubsystemRedpointGoogleModule::ShutdownModule()
{
    if (this->IsRegisteredAsSubsystem)
    {
        FModuleManager &ModuleManager = FModuleManager::Get();
        auto OSS = ModuleManager.GetModule("OnlineSubsystem");
        if (OSS != nullptr)
        {
            ((FOnlineSubsystemModule *)OSS)->UnregisterPlatformService(REDPOINT_GOOGLE_SUBSYSTEM);
            this->IsRegisteredAsSubsystem = false;
        }

        UE_LOG(LogRedpointGoogle, Verbose, TEXT("Redpoint Google module shutdown complete."));
    }
}

IOnlineSubsystemPtr FOnlineSubsystemRedpointGoogleModule::CreateSubsystem(FName InstanceName)
{
#if EOS_GOOGLE_ENABLED
    auto Inst = MakeShared<FOnlineSubsystemRedpointGoogle, ESPMode::ThreadSafe>(InstanceName);
    if (Inst->IsEnabled())
    {
        if (!Inst->Init())
        {
            UE_LOG(LogRedpointGoogle, Warning, TEXT("Unable to init Google online subsystem."));
            Inst->Shutdown();
            return nullptr;
        }
    }
    else
    {
        UE_LOG(LogRedpointGoogle, Warning, TEXT("Google online subsystem is not enabled."));
        Inst->Shutdown();
        return nullptr;
    }

    return Inst;
#else
    // Not compiled with Google support.
    return nullptr;
#endif
}

IMPLEMENT_MODULE(FOnlineSubsystemRedpointGoogleModule, OnlineSubsystemRedpointGoogle)
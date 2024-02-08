// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSCore/InstanceFactory.h"

#include "Engine/Engine.h"
#include "Misc/CommandLine.h"
#include "RedpointEOSAPI/Platform/Create.h"
#include "RedpointEOSConfig/DependentModuleLoader.h"
#include "RedpointEOSCore/Logging.h"
#include "RedpointEOSCore/Module.h"
#include "RedpointEOSCore/RuntimePlatform.h"
#include "RedpointEOSCore/LifecycleManager.h"

namespace Redpoint::EOS::Core
{

bool FInstanceFactory::IsTrueDedicated(const FName &InInstanceName)
{
    // Neither IsServer nor IsDedicated work correctly in play-in-editor. Both listen servers
    // and dedicated servers return true from IsServer, but *neither* return true from IsDedicated
    // (in fact it looks like IsDedicated just doesn't do the right thing at all for single process).
    //
    // So instead implement our own version here which does the detection correctly.

#if WITH_EDITOR
    // Running multiple worlds in the editor; we need to see if this world is specifically a dedicated server.
    FName WorldContextHandle =
        (InInstanceName != NAME_None && InInstanceName != TEXT("DefaultInstance")) ? InInstanceName : NAME_None;
    if (WorldContextHandle.IsNone())
    {
        // The default OSS instance is equal to IsRunningDedicatedServer(), in case the editor
        // is being run with -server for multi-process.
        return IsRunningDedicatedServer();
    }
    if (GEngine == nullptr)
    {
        UE_LOG(
            LogRedpointEOSCore,
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

API::FPlatformHandle FInstanceFactory::Create(const FName &InInstanceName, const TSharedRef<Config::IConfig> &InConfig)
{
    using namespace Redpoint::EOS::API::Platform;

    // Load modules that are we are dependent on for delegated subsystems.
    Config::FDependentModuleLoader::LoadConfigDependentModules(*InConfig);
    Config::FDependentModuleLoader::LoadPlatformDependentModules();

    // Get the runtime platform.
    auto RuntimePlatform = FModule::GetModuleChecked().GetRuntimePlatform();

    // Figure out the options for creating the platform.
    bool bIsServer = FInstanceFactory::IsTrueDedicated(InInstanceName);
    uint64_t Flags = 0;
#if !REDPOINT_EOS_IS_DEDICATED_SERVER
    if (!InConfig->GetCrossPlatformAccountProvider().IsEqual("EpicGames"))
    {
        // Only enable if we can ever authenticate with Epic Games, otherwise it'll never appear anyway.
        Flags = EOS_PF_DISABLE_OVERLAY;
    }
#if WITH_EDITOR
    else if (!FString(FCommandLine::Get()).ToUpper().Contains(TEXT("-GAME")))
    {
        // Disable the overlay in editor builds, if we're not running as a standalone process.
        Flags = EOS_PF_LOADING_IN_EDITOR;
    }
#endif // #if WITH_EDITOR
#endif // #if REDPOINT_EOS_IS_DEDICATED_SERVER
    FCreate::Options Options = {
        bIsServer,
        InConfig->GetEncryptionKey(),
        RuntimePlatform->GetCacheDirectory(),
        TEXT(""),
        TEXT(""),
        Flags,
        InConfig->GetProductId(),
        InConfig->GetSandboxId(),
        InConfig->GetDeploymentId(),
        bIsServer ? InConfig->GetDedicatedServerClientId() : InConfig->GetClientId(),
        bIsServer ? InConfig->GetDedicatedServerClientSecret() : InConfig->GetClientSecret(),
        RuntimePlatform->GetRTCOptions(),
    };
    UE_LOG(
        LogRedpointEOSCore,
        Verbose,
        TEXT("Creating EOS SDK platform instance: InstanceName=%s, bIsServer=%s"),
        *InInstanceName.ToString(),
        bIsServer ? TEXT("true") : TEXT("false"));

    // Create the platform.
    EOS_HPlatform RawPlatformHandle = FCreate::Execute(Options);
    if (RawPlatformHandle == nullptr)
    {
        UE_LOG(LogRedpointEOSCore, Error, TEXT("Unable to initialize EOS platform."));
        if (FParse::Param(FCommandLine::Get(), TEXT("requireeos")))
        {
            checkf(
                RawPlatformHandle != nullptr,
                TEXT("Unable to initialize EOS platform and you have -REQUIREEOS on the command line."));
        }
        return API::FPlatformInstance::CreateDeadWithNoInstance();
    }
    UE_LOG(LogRedpointEOSCore, Verbose, TEXT("EOS platform %p has been created."), RawPlatformHandle);
    auto PlatformHandle = MakeShared<Redpoint::EOS::API::FPlatformInstance>(RawPlatformHandle);

#if REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT
    // Set the initial application and network status from the runtime platform.
    RuntimePlatform->SetLifecycleForNewPlatformInstance(PlatformHandle);
#endif

    return PlatformHandle;
}

} // namespace Redpoint::EOS::Core
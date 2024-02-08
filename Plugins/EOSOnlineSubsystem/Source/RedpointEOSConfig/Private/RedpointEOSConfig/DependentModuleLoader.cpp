// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSConfig/DependentModuleLoader.h"

#include "RedpointEOSConfig/Logging.h"

namespace Redpoint::EOS::Config
{

void FDependentModuleLoader::LoadConfigDependentModules(IConfig &InConfig)
{
    FModuleManager &ModuleManager = FModuleManager::Get();

    // Load modules that are needed by delegated subsystems.
    TArray<FString> SubsystemList;
    InConfig.GetDelegatedSubsystemsString().ParseIntoArray(SubsystemList, TEXT(","), true);
    for (const auto &SubsystemName : SubsystemList)
    {
        FString ModuleName = FString::Printf(TEXT("OnlineSubsystem%s"), *SubsystemName);
        auto Module = ModuleManager.LoadModule(FName(*ModuleName));
        if (Module == nullptr)
        {
            UE_LOG(
                LogRedpointEOSConfig,
                Warning,
                TEXT("Unable to load module for delegated subsystem: %s"),
                *ModuleName);
        }
    }
}

void FDependentModuleLoader::LoadPlatformDependentModules()
{
    FModuleManager &ModuleManager = FModuleManager::Get();

    // Try to load the platform extension module for the current platform.
    {
#if (PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX || PLATFORM_IOS || PLATFORM_TVOS || PLATFORM_ANDROID) &&       \
    !PLATFORM_IS_EXTENSION
        ModuleManager.LoadModule(FName("RedpointEOSPlatformDefault"));
#else
        auto PlatformName = FName(PREPROCESSOR_TO_STRING(PREPROCESSOR_JOIN(RedpointEOSPlatform, PLATFORM_HEADER_NAME)));
        verifyf(
            ModuleManager.LoadModule(PlatformName) != nullptr,
            TEXT("If this load operation fails, then we could not load the native platform extension. For non-public "
                 "platforms, you must have a native platform extension so that the plugin can load EOS."));
#endif
    }
}

}
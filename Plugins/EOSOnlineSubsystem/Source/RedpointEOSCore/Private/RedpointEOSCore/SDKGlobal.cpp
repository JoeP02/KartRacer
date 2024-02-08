// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSCore/SDKGlobal.h"

#include "RedpointEOSCore/Logging.h"
#include "RedpointEOSCore/SDKLogging.h"
#include "RedpointEOSCore/SDKAllocator.h"
#include "RedpointEOSCore/Module.h"
#include "RedpointEOSCore/RuntimePlatform.h"
#include "RedpointEOSConfig/DependentModuleLoader.h"
#include "RedpointEOSAPI/Error.h"
#include "Containers/StringConv.h"

namespace Redpoint::EOS::Core
{

bool FSDKGlobal::bInitialized = false;
bool FSDKGlobal::bShutdown = false;

static FCriticalSection GRedpointEOSCoreSDKInitializationLock;
bool FSDKGlobal::Initialize(Redpoint::EOS::Config::IConfig &InConfig)
{
	// Perform optimistic initialization checks.
	if (FSDKGlobal::bInitialized)
	{
        return true;
	}
	if (FSDKGlobal::bShutdown)
	{
        UE_LOG(
            LogRedpointEOSCore,
            Warning,
            TEXT("FSDKGlobal::Initialize called but the EOS SDK has already been permanently shutdown."));
        return false;
	}

	// Ensure only one thread initializes the SDK at a time.
	FScopeLock Lock(&GRedpointEOSCoreSDKInitializationLock);

	// If we initialized or shutdown after obtaining the lock, return appropriately.
    if (FSDKGlobal::bInitialized)
    {
        return true;
    }
    if (FSDKGlobal::bShutdown)
    {
        UE_LOG(
            LogRedpointEOSCore,
            Warning,
            TEXT("FSDKGlobal::Initialize called but the EOS SDK has already been permanently shutdown."));
        return false;
    }

	// Load platform-specific and configuration-specific modules.
    Redpoint::EOS::Config::FDependentModuleLoader::LoadConfigDependentModules(InConfig);
	Redpoint::EOS::Config::FDependentModuleLoader::LoadPlatformDependentModules();

	// Attempt to acquire a valid runtime platform.
    TSharedRef<IRuntimePlatform> RuntimePlatform = FModule::GetModuleChecked().GetRuntimePlatform();
    if (!RuntimePlatform->IsValid())
    {
        UE_LOG(
            LogRedpointEOSCore,
            Error,
            TEXT("FSDKGlobal::Initialize could not load the runtime platform. This is usually because the runtime "
                 "dependencies of the EOS SDK could not be found."));
        return false;
    }

	// Log the EOS SDK version.
    UE_LOG(LogRedpointEOSCore, Verbose, TEXT("Loaded EOS SDK version: %s"), ANSI_TO_TCHAR(EOS_GetVersion()));
    UE_LOG(LogRedpointEOSCore, Verbose, TEXT("EOS SDK is being initialized..."));

	// Check that the product name and version are valid, or use default values.
    FString ProductNameStr = InConfig.GetProductName();
    FString ProductVersionStr = InConfig.GetProductVersion();
	if (ProductNameStr.IsEmpty())
	{
        ProductNameStr = TEXT("Product Name Not Set");
	}
	if (ProductVersionStr.IsEmpty())
	{
        ProductVersionStr = TEXT("0.0.0");
	}

	// Convert the product name and version to values to pass to EOS_Initialize.
	// @note: These must be ANSI characters, not UTF-8, or the SDK will not initialize.
    auto ProductNamePtr = StringCast<ANSICHAR>(*ProductNameStr);
    auto ProductVersionPtr = StringCast<ANSICHAR>(*ProductVersionStr);

	// Configure the options for the SDK and initialize it.
    EOS_InitializeOptions InitializeOpts = {};
    InitializeOpts.ApiVersion = EOS_INITIALIZE_API_LATEST;
    InitializeOpts.AllocateMemoryFunction = &FSDKAllocator::Allocate;
    InitializeOpts.ReallocateMemoryFunction = &FSDKAllocator::Reallocate;
    InitializeOpts.ReleaseMemoryFunction = &FSDKAllocator::Release;
    InitializeOpts.ProductName = ProductNamePtr.Get();
    InitializeOpts.ProductVersion = ProductVersionPtr.Get();
    InitializeOpts.Reserved = nullptr;
    InitializeOpts.SystemInitializeOptions = RuntimePlatform->GetSystemInitializeOptions();
    EOS_EResult InitializeResult = EOS_Initialize(&InitializeOpts);
	if (InitializeResult != EOS_EResult::EOS_Success)
    {
        UE_LOG(
            LogRedpointEOSCore,
            Error,
            TEXT("%s"),
            *Redpoint::EOS::API::ConvertError(
                 TEXT("FSDKGlobal::Initialize"),
                 TEXT("Unable to initialize EOS SDK."),
                 InitializeResult)
                 .ToLogString());
        return false;
	}

	// The EOS SDK is now initialized, even if we fail to set up logging.
    FSDKGlobal::bInitialized = true;

	// Set the log callback handler.
    EOS_EResult LogResult = EOS_Logging_SetCallback(&FSDKLogging::Log);
	if (LogResult != EOS_EResult::EOS_Success)
    {
        UE_LOG(
            LogRedpointEOSCore,
            Warning,
            TEXT("%s"),
            *Redpoint::EOS::API::ConvertError(
                 TEXT("FSDKGlobal::Initialize"),
                 TEXT("Unable to set the logging callback for the SDK. Expect log messages to be missing."),
                 LogResult)
                 .ToLogString());
		// @note: This is not a fatal error because the EOS SDK still got initialized.
	}

	// Enable all logging categories.
    EOS_EResult LogLevelResult =
        EOS_Logging_SetLogLevel(EOS_ELogCategory::EOS_LC_ALL_CATEGORIES, EOS_ELogLevel::EOS_LOG_Verbose);
    if (LogLevelResult != EOS_EResult::EOS_Success)
    {
        UE_LOG(
            LogRedpointEOSCore,
            Warning,
            TEXT("%s"),
            *Redpoint::EOS::API::ConvertError(
                 TEXT("FSDKGlobal::Initialize"),
                 TEXT("Unable to set the log level for the SDK. Expect log messages to be missing."),
                 LogLevelResult)
                 .ToLogString());
        // @note: This is not a fatal error because the EOS SDK still got initialized.
    }

    UE_LOG(LogRedpointEOSCore, Verbose, TEXT("EOS SDK was initialized successfully."));

	return true;
}

void FSDKGlobal::Shutdown()
{
    // Perform optimistic shutdown checks. We don't check bInitialized here in case
	// another thread has the scope lock and is currently initializing.
    if (FSDKGlobal::bShutdown)
    {
        return;
    }

    // Ensure only one thread shuts down the SDK at a time.
    FScopeLock Lock(&GRedpointEOSCoreSDKInitializationLock);

    // If we're not initialized, then we're already shutdown. Also check to see if
	// another thread shutdown the SDK at the same time.
    if (!FSDKGlobal::bInitialized)
    {
        FSDKGlobal::bShutdown = true;
        return;
    }
    if (FSDKGlobal::bShutdown)
    {
        return;
    }

	// Shutdown the EOS SDK.
    UE_LOG(LogRedpointEOSCore, Verbose, TEXT("EOS SDK is being shutdown..."));
    EOS_Shutdown();
    UE_LOG(LogRedpointEOSCore, Verbose, TEXT("EOS SDK has been shutdown."));
    FSDKGlobal::bShutdown = true;
}

}
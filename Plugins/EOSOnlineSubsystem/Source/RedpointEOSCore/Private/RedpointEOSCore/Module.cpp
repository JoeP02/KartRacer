// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSCore/Module.h"

#include "RedpointEOSConfig/DependentModuleLoader.h"
#include "RedpointEOSCore/InstancePool.h"
#include "RedpointEOSCore/InstancePoolImpl.h"
#include "RedpointEOSCore/RuntimePlatform.h"
#include "RedpointEOSCore/SDKGlobal.h"
#include "RedpointEOSCore/SDKLogging.h"

namespace Redpoint::EOS::Core
{

void FModule::ShutdownModule()
{
    if (this->RuntimePlatform.IsValid())
    {
        // @note: Forcibly shuts down all handles and marks
        // them as destroyed so further API calls in Redpoint::EOS::API
        // will fail with an error code instead of trying to call
        // unloaded methods.
        ((FInstancePoolImpl &)IInstancePool::Pool()).ShutdownAll();

        this->RuntimePlatform->Unload();
        this->RuntimePlatform.Reset();
    }

#if WITH_EDITOR
    FSDKLogging::EditorLogHandler.Unbind();
#endif

    FSDKGlobal::Shutdown();
}

TSharedRef<class IRuntimePlatform> FModule::GetRuntimePlatform() const
{
    if (!this->RuntimePlatform.IsValid())
    {
        // Try to get RuntimePlatform populated by
        // using FDependentModuleLoader.
        Config::FDependentModuleLoader::LoadPlatformDependentModules();

        // If RuntimePlatform is still not populated, this
        // is a hard error - we won't be able to dereference
        // RuntimePlatform to get any platform.
        checkf(
            this->RuntimePlatform.IsValid(),
            TEXT("Expected SetRuntimePlatform to be called before GetRuntimePlatform!"));
    }

    return this->RuntimePlatform.ToSharedRef();
}

void FModule::SetRuntimePlatform(const TSharedRef<class IRuntimePlatform> &InRuntimePlatform)
{
    checkf(
        !this->RuntimePlatform.IsValid(),
        TEXT("Expected the runtime platform not to be set when SetRuntimePlatform called!"));
    this->RuntimePlatform = InRuntimePlatform;

    this->RuntimePlatform->Load();
}

#if WITH_EDITOR
void FModule::SetLogHandler(const FOnLogForwardedForEditor &InEditorLogForwardingHandler)
{
    FSDKLogging::EditorLogHandler = InEditorLogForwardingHandler;
}
#endif

} // namespace Redpoint::EOS::Core

IMPLEMENT_MODULE(Redpoint::EOS::Core::FModule, RedpointEOSCore);
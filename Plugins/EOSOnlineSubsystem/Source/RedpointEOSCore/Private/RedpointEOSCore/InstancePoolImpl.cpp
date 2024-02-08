// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSCore/InstancePoolImpl.h"

#include "Engine/Engine.h"
#include "RedpointEOSAPI/Platform/Tick.h"
#include "RedpointEOSConfig/IniConfig.h"
#include "RedpointEOSCore/InstanceFactory.h"
#include "RedpointEOSCore/Logging.h"
#include "RedpointEOSCore/Module.h"
#include "RedpointEOSCore/SDKGlobal.h"
#include "RedpointEOSCore/Utils/RegulatedTicker.h"

namespace Redpoint::EOS::Core
{

FInstancePoolImpl::FInstancePoolImpl()
    : TickerHandle(Utils::FRegulatedTicker::GetCoreTicker().AddTicker(
          FTickerDelegate::CreateRaw(this, &FInstancePoolImpl::Tick)))
    , Instances()
    , bIsInShutdown(false)
#if REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT
    , RuntimePlatform()
    , bShouldPollForApplicationStatus(false)
    , bShouldPollForNetworkStatus(false)
#endif
{
}

FInstancePoolImpl::~FInstancePoolImpl()
{
    this->ShutdownAll();
    Utils::FRegulatedTicker::GetCoreTicker().RemoveTicker(this->TickerHandle);
    this->TickerHandle.Reset();
}

void FInstancePoolImpl::ShutdownAll()
{
    this->bIsInShutdown = true;
    for (const auto &KV : this->Instances)
    {
        auto Ptr = KV.Value.Pin();
        if (Ptr.IsValid())
        {
            if (!Ptr->Instance()->IsShutdown())
            {
                Ptr->Instance()->ForceShutdown();
            }
        }
    }
    this->Instances.Empty();
}

bool FInstancePoolImpl::Tick(float DeltaSeconds) const
{
    using namespace Redpoint::EOS::API::Platform;

    for (const auto &KV : this->Instances)
    {
        auto Ptr = KV.Value.Pin();
        if (Ptr.IsValid())
        {
            if (!Ptr->Instance()->IsShutdown())
            {
                FTick::Execute(Ptr->Instance());
            }
        }
    }

#if REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT
    {
        EOS_EApplicationStatus NewApplicationStatus = EOS_EApplicationStatus::EOS_AS_Foreground;
        EOS_ENetworkStatus NewNetworkStatus = EOS_ENetworkStatus::EOS_NS_Online;
        bool bShouldSetNewApplicationStatus = false;
        bool bShouldSetNewNetworkStatus = false;

        if (this->bShouldPollForApplicationStatus && this->bShouldPollForNetworkStatus)
        {
            bShouldSetNewApplicationStatus =
                this->RuntimePlatform->PollLifecycleApplicationStatus(NewApplicationStatus);
            bShouldSetNewNetworkStatus = this->RuntimePlatform->PollLifecycleNetworkStatus(NewNetworkStatus);
        }
        else if (this->bShouldPollForApplicationStatus)
        {
            bShouldSetNewApplicationStatus =
                this->RuntimePlatform->PollLifecycleApplicationStatus(NewApplicationStatus);
        }
        else if (this->bShouldPollForNetworkStatus)
        {
            bShouldSetNewNetworkStatus = this->RuntimePlatform->PollLifecycleNetworkStatus(NewNetworkStatus);
        }

        if (bShouldSetNewApplicationStatus || bShouldSetNewNetworkStatus)
        {
            for (const auto &KV : this->Instances)
            {
                auto Ptr = KV.Value.Pin();
                if (Ptr.IsValid())
                {
                    if (!Ptr->Instance()->IsShutdown())
                    {
                        EOS_HPlatform Platform = Ptr->Instance()->Handle();
                        if (bShouldSetNewApplicationStatus)
                        {
                            EOS_EApplicationStatus OldApplicationStatus = EOS_Platform_GetApplicationStatus(Platform);
                            if (OldApplicationStatus != NewApplicationStatus)
                            {
                                UE_LOG(
                                    LogRedpointEOSCore,
                                    Verbose,
                                    TEXT("FInstancePoolImpl::Tick: Platform instance %p application status moving "
                                         "from [%d] to [%d]"),
                                    Platform,
                                    OldApplicationStatus,
                                    NewApplicationStatus);
                                EOS_Platform_SetApplicationStatus(Platform, NewApplicationStatus);
                            }
                        }
                        if (bShouldSetNewNetworkStatus)
                        {
                            if (EOS_Platform_GetNetworkStatus(Platform) != NewNetworkStatus)
                            {
                                EOS_Platform_SetNetworkStatus(Platform, NewNetworkStatus);
                            }
                        }
                    }
                }
            }
        }
    }
#endif

    return true;
}

API::FPlatformRefCountedHandle FInstancePoolImpl::Create(FName InstanceName)
{
    return this->CreateWithConfig(InstanceName, MakeShared<Config::FIniConfig>());
}

API::FPlatformRefCountedHandle FInstancePoolImpl::CreateWithConfig(
    FName InstanceName,
    TSharedRef<Config::IConfig> Config)
{
    if (this->bIsInShutdown)
    {
        UE_LOG(LogRedpointEOSCore, Warning, TEXT("Ignoring request to create platform instance during shutdown."));
        return API::MakeRefCountedPlatformHandle(API::FPlatformInstance::CreateDeadWithNoInstance());
    }

    if (!FSDKGlobal::Initialize(*Config))
    {
        // The EOS SDK could not be initialized globally, return a dead instance.
        return API::MakeRefCountedPlatformHandle(API::FPlatformInstance::CreateDeadWithNoInstance());
    }

#if EOS_VERSION_AT_LEAST(1, 15, 0)
    // Initialise the lifecycle manager logic if needed.
    if (!this->RuntimePlatform.IsValid())
    {
        this->RuntimePlatform = FModule::GetModuleChecked().GetRuntimePlatform();
        this->RuntimePlatform->RegisterLifecycleHandlers(this->AsShared());
        this->bShouldPollForApplicationStatus = this->RuntimePlatform->ShouldPollLifecycleApplicationStatus();
        this->bShouldPollForNetworkStatus = this->RuntimePlatform->ShouldPollLifecycleNetworkStatus();
    }
#endif

    auto ExistingEntry = this->Instances.Find(InstanceName);
    if (ExistingEntry != nullptr)
    {
        auto Ptr = ExistingEntry->Pin();
        if (Ptr.IsValid())
        {
            return Ptr.ToSharedRef();
        }
    }

    API::FPlatformHandle Instance = FInstanceFactory::Create(InstanceName, Config);
    API::FPlatformRefCountedHandle RefHandle = API::MakeRefCountedPlatformHandle(Instance);
    this->Instances.Emplace(InstanceName, RefHandle);
    return RefHandle;
}

#if REDPOINT_EOS_HAS_LIFECYCLE_MANAGEMENT

void FInstancePoolImpl::UpdateApplicationStatus(const EOS_EApplicationStatus &InNewStatus)
{
    for (const auto &KV : this->Instances)
    {
        auto Ptr = KV.Value.Pin();
        if (Ptr.IsValid())
        {
            if (!Ptr->Instance()->IsShutdown())
            {
                EOS_HPlatform Platform = Ptr->Instance()->Handle();
                EOS_EApplicationStatus OldApplicationStatus = EOS_Platform_GetApplicationStatus(Platform);
                UE_LOG(
                    LogRedpointEOSCore,
                    Verbose,
                    TEXT("FInstancePoolImpl::UpdateApplicationStatus: Platform instance %p application status moving "
                         "from "
                         "[%d] to [%d]"),
                    Platform,
                    OldApplicationStatus,
                    InNewStatus);
                EOS_Platform_SetApplicationStatus(Platform, InNewStatus);
            }
        }
    }
}

void FInstancePoolImpl::UpdateNetworkStatus(const EOS_ENetworkStatus &InNewStatus)
{
    for (const auto &KV : this->Instances)
    {
        auto Ptr = KV.Value.Pin();
        if (Ptr.IsValid())
        {
            if (!Ptr->Instance()->IsShutdown())
            {
                EOS_Platform_SetNetworkStatus(Ptr->Instance()->Handle(), InNewStatus);
            }
        }
    }
}

#endif

} // namespace Redpoint::EOS::Core
// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX

#include "RedpointEOSCore/RuntimePlatform.h"
#if PLATFORM_WINDOWS
#include "Windows/eos_Windows.h"
#endif

class FEOSRuntimePlatformDesktopBase : public Redpoint::EOS::Core::IRuntimePlatform
{
private:
    void *DynamicLibraryHandle;
    TArray<TSharedPtr<Redpoint::EOS::Core::IRuntimePlatformIntegration>> Integrations;
    EOS_Platform_RTCOptions RTCOptions;
#if PLATFORM_WINDOWS
    EOS_Windows_RTCOptions WindowsRTCOptions;
    const char *XAudio29DllPathAllocated;
#endif

protected:
    FEOSRuntimePlatformDesktopBase() = default;

public:
    virtual ~FEOSRuntimePlatformDesktopBase() = default;

    virtual void Load() override;
    virtual void Unload() override;
    virtual bool IsValid() override;
    virtual void *GetSystemInitializeOptions() override;
    virtual EOS_Platform_RTCOptions *GetRTCOptions() override;
    virtual FString GetCacheDirectory() override;
    virtual void ClearStoredEASRefreshToken(int32 LocalUserNum) override{};
#if !UE_BUILD_SHIPPING
    virtual FString GetPathToEASAutomatedTestingCredentials() override;
#endif
    virtual const TArray<TSharedPtr<Redpoint::EOS::Core::IRuntimePlatformIntegration>> &GetIntegrations()
        const override;
    virtual bool UseCrossPlatformFriendStorage() const override;
};

#endif
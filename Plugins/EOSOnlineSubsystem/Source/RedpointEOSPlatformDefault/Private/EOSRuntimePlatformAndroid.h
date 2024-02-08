// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_ANDROID

#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSCore/RuntimePlatform.h"

#include "Android/eos_android.h"

class FEOSRuntimePlatformAndroid : public Redpoint::EOS::Core::IRuntimePlatform
{
private:
    TSharedPtr<EOS_Android_InitializeOptions> Opts = {};
    TArray<TSharedPtr<Redpoint::EOS::Core::IRuntimePlatformIntegration>> Integrations;
    EOS_Platform_RTCOptions RTCOptions;

public:
    virtual ~FEOSRuntimePlatformAndroid(){};

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

    static const char *InternalPath;
    static const char *ExternalPath;
};

#endif
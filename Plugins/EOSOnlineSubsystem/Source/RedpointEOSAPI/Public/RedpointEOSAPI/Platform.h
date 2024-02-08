// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSAPI/SDK.h"

namespace Redpoint::EOS::API
{

#define REDPOINT_EOSSDK_PLATFORM_GET(Name)                                                                             \
    template <> EOS_H##Name Get<EOS_H##Name>()                                                                         \
    {                                                                                                                  \
        if (this->bIsShutdown || this->Instance == nullptr)                                                            \
        {                                                                                                              \
            return nullptr;                                                                                            \
        }                                                                                                              \
        return EOS_Platform_Get##Name##Interface(this->Instance);                                                      \
    }

/**
 * A safe class that wraps EOS_HPlatform and allows the APIs in the Redpoint::EOS::API namespace to only attempt
 * invocations if the platform instance is still valid.
 */
class REDPOINTEOSAPI_API FPlatformInstance
{
private:
    bool bIsShutdown;
    EOS_HPlatform Instance;

    FPlatformInstance();

public:
    FPlatformInstance(EOS_HPlatform InInstance);
    UE_NONCOPYABLE(FPlatformInstance);
    virtual ~FPlatformInstance();

    static TSharedRef<FPlatformInstance> CreateDeadWithNoInstance();

    void ForceShutdown();
    bool IsShutdown() const;

    EOS_HPlatform Handle() const
    {
        return this->Instance;
    }

    template <typename TInterface> TInterface Get();
    REDPOINT_EOSSDK_PLATFORM_GET(Metrics);
    REDPOINT_EOSSDK_PLATFORM_GET(Auth);
    REDPOINT_EOSSDK_PLATFORM_GET(Connect);
    REDPOINT_EOSSDK_PLATFORM_GET(Ecom);
    REDPOINT_EOSSDK_PLATFORM_GET(UI);
    REDPOINT_EOSSDK_PLATFORM_GET(Friends);
    REDPOINT_EOSSDK_PLATFORM_GET(Presence);
    REDPOINT_EOSSDK_PLATFORM_GET(Sessions);
    REDPOINT_EOSSDK_PLATFORM_GET(Lobby);
    REDPOINT_EOSSDK_PLATFORM_GET(UserInfo);
    REDPOINT_EOSSDK_PLATFORM_GET(P2P);
    REDPOINT_EOSSDK_PLATFORM_GET(RTC);
    REDPOINT_EOSSDK_PLATFORM_GET(RTCAdmin);
    REDPOINT_EOSSDK_PLATFORM_GET(PlayerDataStorage);
    REDPOINT_EOSSDK_PLATFORM_GET(TitleStorage);
    REDPOINT_EOSSDK_PLATFORM_GET(Achievements);
    REDPOINT_EOSSDK_PLATFORM_GET(Stats);
    REDPOINT_EOSSDK_PLATFORM_GET(Leaderboards);
    REDPOINT_EOSSDK_PLATFORM_GET(Mods);
    REDPOINT_EOSSDK_PLATFORM_GET(AntiCheatClient);
    REDPOINT_EOSSDK_PLATFORM_GET(AntiCheatServer);
    REDPOINT_EOSSDK_PLATFORM_GET(ProgressionSnapshot);
    REDPOINT_EOSSDK_PLATFORM_GET(Reports);
    REDPOINT_EOSSDK_PLATFORM_GET(Sanctions);
    REDPOINT_EOSSDK_PLATFORM_GET(KWS);
    REDPOINT_EOSSDK_PLATFORM_GET(CustomInvites);
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    REDPOINT_EOSSDK_PLATFORM_GET(IntegratedPlatform);
#endif
    template <> EOS_HRTCAudio Get<EOS_HRTCAudio>()
    {
        if (this->bIsShutdown || this->Instance == nullptr)
        {
            return nullptr;
        }
        EOS_HRTC RTC = EOS_Platform_GetRTCInterface(this->Instance);
        if (RTC == nullptr)
        {
            return nullptr;
        }
        return EOS_RTC_GetAudioInterface(RTC);
    }
};

#undef REDPOINT_EOSSDK_PLATFORM_GET

typedef TSharedRef<FPlatformInstance> FPlatformHandle;

namespace Private
{
class REDPOINTEOSAPI_API FPlatformRefCountedHandleInternal
{
private:
    FPlatformHandle _Instance;

public:
    FPlatformRefCountedHandleInternal(const FPlatformHandle &InInstance);
    UE_NONCOPYABLE(FPlatformRefCountedHandleInternal);
    ~FPlatformRefCountedHandleInternal();

    const FPlatformHandle &Instance() const;
};
} // namespace Private

typedef TSharedRef<Private::FPlatformRefCountedHandleInternal> FPlatformRefCountedHandle;
typedef TSharedPtr<Private::FPlatformRefCountedHandleInternal> FPlatformOptionalRefCountedHandle;
typedef TWeakPtr<Private::FPlatformRefCountedHandleInternal> FPlatformWeakRefCountedHandle;

REDPOINTEOSAPI_API FPlatformRefCountedHandle MakeRefCountedPlatformHandle(const FPlatformHandle &Handle);

} // namespace Redpoint::EOS::API
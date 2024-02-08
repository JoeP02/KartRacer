// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "./Tasks/OnlineAsyncTaskSteamDelegates.h"
#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "RedpointEOSInterfaces/Private/Interfaces/OnlineAvatarInterface.h"

#if EOS_STEAM_ENABLED

class FOnlineAvatarInterfaceRedpointSteam
    : public IOnlineAvatar,
      public TSharedFromThis<FOnlineAvatarInterfaceRedpointSteam, ESPMode::ThreadSafe>
{
private:
    void OnProcessAvatarUrlRequestComplete(
        FHttpRequestPtr Request,
        FHttpResponsePtr Response,
        bool bConnectedSuccessfully,
        FString DefaultAvatarUrl,
        FOnGetAvatarUrlComplete OnComplete);

    void OnUserInformationFetched(
        const FOnlineError &,
        uint64 SteamID,
        TSoftObjectPtr<UTexture> DefaultTexture,
        FOnGetAvatarComplete OnComplete);

    void OnSteamAvatarDataFetched(
        const FOnlineError &,
        uint32 Width,
        uint32 Height,
        uint8 *RGBABuffer,
        size_t RGBABufferSize,
        uint64 SteamID,
        TSoftObjectPtr<UTexture> DefaultTexture,
        FOnGetAvatarComplete OnComplete);

public:
    FOnlineAvatarInterfaceRedpointSteam(){};
    virtual ~FOnlineAvatarInterfaceRedpointSteam(){};
    UE_NONCOPYABLE(FOnlineAvatarInterfaceRedpointSteam);

    bool GetAvatar(
        const FUniqueNetId &LocalUserId,
        const FUniqueNetId &TargetUserId,
        TSoftObjectPtr<UTexture> DefaultTexture,
        FOnGetAvatarComplete OnComplete) override;

    bool GetAvatarUrl(
        const FUniqueNetId &LocalUserId,
        const FUniqueNetId &TargetUserId,
        FString DefaultAvatarUrl,
        FOnGetAvatarUrlComplete OnComplete) override;
};

#endif
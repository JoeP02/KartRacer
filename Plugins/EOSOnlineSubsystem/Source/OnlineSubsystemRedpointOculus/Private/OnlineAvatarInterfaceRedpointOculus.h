// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_OCULUS_ENABLED

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "RedpointEOSInterfaces/Private/Interfaces/OnlineAvatarInterface.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class FOnlineAvatarInterfaceRedpointOculus
    : public IOnlineAvatar,
      public TSharedFromThis<FOnlineAvatarInterfaceRedpointOculus, ESPMode::ThreadSafe>
{
private:
    void OnDownloadAvatarComplete(
        FHttpRequestPtr Request,
        FHttpResponsePtr Response,
        bool bConnectedSuccessfully,
        TSoftObjectPtr<UTexture> DefaultTexture,
        FOnGetAvatarComplete OnComplete);

public:
    FOnlineAvatarInterfaceRedpointOculus(){};
    virtual ~FOnlineAvatarInterfaceRedpointOculus(){};
    UE_NONCOPYABLE(FOnlineAvatarInterfaceRedpointOculus);

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

PRAGMA_ENABLE_DEPRECATION_WARNINGS

#endif
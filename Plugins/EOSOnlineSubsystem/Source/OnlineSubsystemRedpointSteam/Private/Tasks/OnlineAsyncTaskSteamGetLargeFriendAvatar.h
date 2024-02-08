// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "./OnlineAsyncTaskSteamDelegates.h"
#include "OnlineAsyncTaskManager.h"

#if EOS_STEAM_ENABLED

THIRD_PARTY_INCLUDES_START
#include "steam/steam_api.h"
THIRD_PARTY_INCLUDES_END

EOS_ENABLE_STRICT_WARNINGS

class FOnlineAsyncTaskSteamGetLargeFriendAvatar : public FOnlineAsyncTaskBasic<class FOnlineSubsystemSteam>
{
private:
    bool bInit;
    uint64 SteamID;
    FSteamAvatarDataFetched Delegate;
    FString FailureContext;

public:
    FOnlineAsyncTaskSteamGetLargeFriendAvatar(uint64 InSteamID, FSteamAvatarDataFetched InDelegate)
        : bInit(false)
        , SteamID(InSteamID)
        , Delegate(MoveTemp(InDelegate))
    {
    }

    virtual ~FOnlineAsyncTaskSteamGetLargeFriendAvatar()
    {
    }

    virtual FString ToString() const override
    {
        return TEXT("FOnlineAsyncTaskSteamGetLargeFriendAvatar");
    }

    virtual void Tick() override;
    virtual void Finalize() override;
};

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_STEAM_ENABLED
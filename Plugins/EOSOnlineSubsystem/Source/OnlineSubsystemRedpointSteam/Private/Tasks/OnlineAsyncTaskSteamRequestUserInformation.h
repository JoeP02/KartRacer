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

class FOnlineAsyncTaskSteamRequestUserInformationCallbackHandler
{
private:
    class FOnlineAsyncTaskSteamRequestUserInformation *Owner;
    uint64 SteamID;
    STEAM_CALLBACK(
        FOnlineAsyncTaskSteamRequestUserInformationCallbackHandler,
        OnPersonaStateChange,
        PersonaStateChange_t);

public:
    FOnlineAsyncTaskSteamRequestUserInformationCallbackHandler(
        class FOnlineAsyncTaskSteamRequestUserInformation *InOwner,
        uint64 InSteamID)
        : Owner(InOwner)
        , SteamID(InSteamID){};
};

class FOnlineAsyncTaskSteamRequestUserInformation : public FOnlineAsyncTaskBasic<class FOnlineSubsystemSteam>
{
    friend class FOnlineAsyncTaskSteamRequestUserInformationCallbackHandler;

private:
    bool bInit;
    uint64 SteamID;
    FSteamUserInformationFetched Delegate;
    FString FailureContext;
    TSharedPtr<FOnlineAsyncTaskSteamRequestUserInformationCallbackHandler, ESPMode::ThreadSafe> CallbackHandler;
    void NotifyComplete();

public:
    FOnlineAsyncTaskSteamRequestUserInformation(uint64 InSteamID, FSteamUserInformationFetched InDelegate)
        : bInit(false)
        , SteamID(InSteamID)
        , Delegate(MoveTemp(InDelegate))
        , CallbackHandler(
              MakeShareable(new FOnlineAsyncTaskSteamRequestUserInformationCallbackHandler(this, InSteamID)))
    {
    }

    virtual ~FOnlineAsyncTaskSteamRequestUserInformation()
    {
    }

    virtual FString ToString() const override
    {
        return TEXT("FOnlineAsyncTaskSteamRequestUserInformation");
    }

    virtual void Tick() override;
    virtual void Finalize() override;
};

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_STEAM_ENABLED
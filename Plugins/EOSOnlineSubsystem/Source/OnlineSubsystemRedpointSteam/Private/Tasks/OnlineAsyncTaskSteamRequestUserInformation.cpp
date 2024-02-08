// Copyright June Rhodes 2024. All Rights Reserved.

#include "./OnlineAsyncTaskSteamRequestUserInformation.h"

#include "../LogRedpointSteam.h"
#include "../OnlineSubsystemRedpointSteam.h"
#include "../SteamConstants.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemRedpointEOS/Public/EOSError.h"

#if EOS_STEAM_ENABLED

EOS_ENABLE_STRICT_WARNINGS

void FOnlineAsyncTaskSteamRequestUserInformationCallbackHandler::OnPersonaStateChange(PersonaStateChange_t *InEv)
{
    if (InEv && InEv->m_ulSteamID == this->SteamID)
    {
        this->Owner->NotifyComplete();
    }
}

void FOnlineAsyncTaskSteamRequestUserInformation::NotifyComplete()
{
    this->bIsComplete = true;
    this->bWasSuccessful = true;
}

void FOnlineAsyncTaskSteamRequestUserInformation::Tick()
{
    if (!this->bInit)
    {
        if (!SteamFriends()->RequestUserInformation(this->SteamID, false))
        {
            this->bIsComplete = true;
            this->bWasSuccessful = true;
            return;
        }

        this->bInit = true;
    }

    // Otherwise wait for our FOnlineAsyncTaskSteamRequestUserInformationCallbackHandler
    // to send us a notification that the work has finished.
}

void FOnlineAsyncTaskSteamRequestUserInformation::Finalize()
{
    checkf(this->bWasSuccessful, TEXT("FOnlineAsyncTaskSteamRequestUserInformation has no failure path."));

    this->Delegate.ExecuteIfBound(OnlineRedpointEOS::Errors::Success());
}

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_STEAM_ENABLED
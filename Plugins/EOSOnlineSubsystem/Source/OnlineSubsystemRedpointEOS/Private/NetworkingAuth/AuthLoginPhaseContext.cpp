// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Private/NetworkingAuth/AuthLoginPhaseContext.h"

#include "OnlineSubsystemRedpointEOS/Private/EOSControlChannel.h"

FString FAuthLoginPhaseContext::GetIdentifier() const
{
    return *this->GetUserId()->ToString();
}

FString FAuthLoginPhaseContext::GetPhaseGroup() const
{
    return TEXT("login");
}

void FAuthLoginPhaseContext::MarkAsRegisteredForAntiCheat()
{
    UEOSControlChannel *ControlChannelTemp;
    if (GetControlChannel(ControlChannelTemp))
    {
        ControlChannelTemp->bRegisteredForAntiCheat.Add(*this->GetUserId(), true);
    }
}

void FAuthLoginPhaseContext::SetVerificationStatus(EUserVerificationStatus InStatus)
{
    UEOSControlChannel *ControlChannelTemp;
    if (GetControlChannel(ControlChannelTemp))
    {
        ControlChannelTemp->VerificationDatabase.Add(*this->GetUserId(), InStatus);
    }
}

bool FAuthLoginPhaseContext::GetVerificationStatus(EUserVerificationStatus &OutStatus) const
{
    UEOSControlChannel *ControlChannelTemp;
    if (GetControlChannel(ControlChannelTemp))
    {
        if (!ControlChannelTemp->VerificationDatabase.Contains(*this->GetUserId()))
        {
            OutStatus = EUserVerificationStatus::NotStarted;
            return true;
        }

        OutStatus = ControlChannelTemp->VerificationDatabase[*this->GetUserId()];
        return true;
    }
    return false;
}
// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Private/NetworkingAuth/AuthVerificationPhaseContext.h"

#include "OnlineSubsystemRedpointEOS/Private/EOSControlChannel.h"

FString FAuthVerificationPhaseContext::GetIdentifier() const
{
    return *this->GetUserId()->ToString();
}

FString FAuthVerificationPhaseContext::GetPhaseGroup() const
{
    return TEXT("verification");
}

void FAuthVerificationPhaseContext::SetVerificationStatus(EUserVerificationStatus InStatus)
{
    UEOSControlChannel *ControlChannelTemp;
    if (this->GetControlChannel(ControlChannelTemp))
    {
        ControlChannelTemp->VerificationDatabase.Add(*this->GetUserId(), InStatus);
    }
}

bool FAuthVerificationPhaseContext::GetVerificationStatus(EUserVerificationStatus &OutStatus) const
{
    UEOSControlChannel *ControlChannelTemp;
    if (this->GetControlChannel(ControlChannelTemp))
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

bool FAuthVerificationPhaseContext::IsConnectionAsTrustedOnClient(bool &OutIsTrusted) const
{
    UEOSControlChannel *ControlChannelTemp;
    if (this->GetControlChannel(ControlChannelTemp))
    {
        OutIsTrusted = ControlChannelTemp->bClientTrustsServer;
        return true;
    }
    return false;
}
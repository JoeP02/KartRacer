// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Private/NetworkingAuth/AuthConnectionPhaseContext.h"

#include "OnlineSubsystemRedpointEOS/Private/EOSControlChannel.h"

FString FAuthConnectionPhaseContext::GetIdentifier() const
{
    UNetConnection *NetConnection;
    if (this->GetConnection(NetConnection))
    {
        return NetConnection->LowLevelGetRemoteAddress();
    }
    return TEXT("(connection closed)");
}

FString FAuthConnectionPhaseContext::GetPhaseGroup() const
{
    return TEXT("connection");
}

void FAuthConnectionPhaseContext::MarkConnectionAsTrustedOnClient()
{
    UEOSControlChannel *ControlChannelTemp;
    if (GetControlChannel(ControlChannelTemp))
    {
        ControlChannelTemp->bClientTrustsServer = true;
    }
}
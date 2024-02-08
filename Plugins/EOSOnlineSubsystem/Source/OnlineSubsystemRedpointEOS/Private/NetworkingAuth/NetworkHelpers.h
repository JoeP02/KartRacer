// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/NetConnection.h"
#include "RedpointEOSConfig/Config.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSNetDriver.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineSubsystemRedpointEOS.h"

class FNetworkHelpers
{
public:
    static FOnlineSubsystemEOS *GetOSS(UNetConnection *Connection);
    static const Redpoint::EOS::Config::IConfig *GetConfig(UNetConnection *Connection);
    static EEOSNetDriverRole GetRole(UNetConnection *Connection);
    static void GetAntiCheat(
        UNetConnection *Connection,
        TSharedPtr<IAntiCheat> &OutAntiCheat,
        TSharedPtr<FAntiCheatSession> &OutAntiCheatSession,
        bool &OutIsBeacon);
    static ISocketSubsystem *GetSocketSubsystem(UNetConnection *Connection);
};
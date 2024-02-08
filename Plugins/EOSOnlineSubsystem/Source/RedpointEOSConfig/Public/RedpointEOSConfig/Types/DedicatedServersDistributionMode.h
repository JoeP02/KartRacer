// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "DedicatedServersDistributionMode.generated.h"

UENUM()
enum class EDedicatedServersDistributionMode : uint8
{
    /**
     * In developers only mode, dedicated servers can have the client ID and secret embedded in their packaged binaries.
     * You must ensure that the binaries are never distributed to end users, otherwise they will be able to run trusted
     * dedicated servers and impersonate other users on their behalf.
     */
    DevelopersOnly UMETA(DisplayName = "Dedicated server binaries are only ever distributed and run by developers"),

    /**
     * If dedicated servers are being run by both developers and players, the dedicated server secrets will be stored in
     * Build/NoRedist/DedicatedServerEngine.ini. You must then provide the values in this file at runtime when running
     * the dedicated servers on your own infrastructure. Dedicated servers run by players will be considered untrusted,
     * and will not perform user verification checks.
     */
    DevelopersAndPlayers UMETA(DisplayName = "Both developers and players will run dedicated servers"),

    /**
     * If dedicated servers are only being run by players, this turns off all the trusted dedicated server code paths.
     */
    PlayersOnly UMETA(DisplayName = "Dedicated server binaries will be distributed to players and only run by players"),
};
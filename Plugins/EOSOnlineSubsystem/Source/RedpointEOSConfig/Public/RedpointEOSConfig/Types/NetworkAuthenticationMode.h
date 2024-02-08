// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "NetworkAuthenticationMode.generated.h"

UENUM()
enum class ENetworkAuthenticationMode : uint8
{
    /**
     * The networking authentication mode is selected based on your API version. Currently always ID Token.
     */
    Default UMETA(DisplayName = "Default"),

    /**
     * Turns on trusted dedicated servers if relevant for the type of distribution and sanction checks. Users are
     * verified:
     * - With ID tokens when connecting to trusted dedicated servers. While you can't access Player Data Storage, it
     *   works for any kind of user, regardless of how they authenticated.
     * - Comparison of P2P sending address when connecting to listen servers over EOS P2P. Does not support split-screen
     *   connections to listen servers, as there is no way to verify the additional users on the inbound connection.
     * - Authentication is skipped when connecting to an untrusted dedicated server (typically when the distribution
     *   mode is not set to "developer only").
     * - Authentication is skipped when connecting to a listen server over IP.
     * - Connections are rejected in all other cases.
     */
    IDToken UMETA(DisplayName = "ID Token"),

    /**
     * User Credentials was removed on 2022-11-30 due to known bugs in its implementation. It only ever existed as a
     * migration path for legacy games that relied on the old network authentication logic (for example, to write to
     * Player Data Storage from game servers). All games should use ID Token moving forwards.
     */
    // UserCredentials UMETA(DisplayName = "User Credentials (Legacy)"),

    /**
     * Network authentication is turned off. No validation of connecting players is done; anyone can connect to any
     * server. You can not use Anti-Cheat in this mode.
     */
    Off UMETA(DisplayName = "Off"),
};
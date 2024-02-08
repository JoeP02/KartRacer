// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "PresenceAdvertisementType.generated.h"

/**
 * In EOS, you can only have one object advertised with presence; this can either be a party or a session, but not both.
 * This configuration option determines what gets advertised in the presence system.
 */
UENUM()
enum class EPresenceAdvertisementType : uint8
{
    /**
     * Neither parties nor sessions will be advertised with presence.
     */
    None,

    /**
     * Parties will be the type of joinable object advertised with presence. This
     * is the default for backwards compatibility.
     */
    Party,

    /**
     * Sessions will be the type of joinable object advertised with presence.
     */
    Session,
};
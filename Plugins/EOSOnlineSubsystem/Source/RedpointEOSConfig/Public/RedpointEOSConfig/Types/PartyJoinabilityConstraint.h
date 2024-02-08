// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "PartyJoinabilityConstraint.generated.h"

UENUM()
enum class EPartyJoinabilityConstraint : uint8
{
    /**
     * When a player accepts an invite from the native platform and the player is already in a party, the player will
     * join the new party in addition to the existing party they are in.  IOnlinePartySystem::GetJoinedParties will
     * return multiple parties.
     */
    AllowPlayersInMultipleParties UMETA(DisplayName = "Allow players to join multiple parties at the same time"),

    /**
     * When a player accepts an invite from the native platform and the player is already in a party, the accepted
     * invite is ignored and the IOnlinePartySystem::OnPartyInviteResponseReceived event is fired to indicate an invite
     * was ignored.
     */
    IgnoreInvitesIfAlreadyInParty UMETA(DisplayName = "Ignore accepted invites if player is already in a party")
};
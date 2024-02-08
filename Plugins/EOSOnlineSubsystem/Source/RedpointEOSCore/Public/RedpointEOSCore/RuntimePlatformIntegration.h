// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSCore/Types/ExternalAccountIdInfo.h"
#include "UObject/SoftObjectPtr.h"

class FOnlineSessionSettings;
class UWorld;
class FUniqueNetId;

namespace Redpoint::EOS::Core
{

class REDPOINTEOSCORE_API IRuntimePlatformIntegration
{
public:
    /**
     * Attempts to convert the provided external user information into an online subsystem user ID. The GetType()
     * function of the user ID should map to a loaded online subsystem, so that the caller can use the user ID with that
     * online subsystem's APIs.
     */
    virtual TSharedPtr<const FUniqueNetId> GetUserId(
        TSoftObjectPtr<UWorld> InWorld,
        EOS_Connect_ExternalAccountInfo *InExternalInfo) = 0;

    /**
     * Returns if the specified user ID can be converted into an FExternalAccountIdInfo for the friends system to look
     * up the EOS account by external info.
     */
    virtual bool CanProvideExternalAccountId(const FUniqueNetId &InUserId) = 0;

    /**
     * Returns the external account information for the given user ID.
     */
    virtual FExternalAccountIdInfo GetExternalAccountId(const FUniqueNetId &InUserId) = 0;

    /**
     * Called when the list name is being passed into a wrapped subsystem inside OnlineFriendsInterfaceSynthetic,
     * offering the integration the chance to update the list name (in case the platform restricts valid values).
     */
    virtual void MutateFriendsListNameIfRequired(FName InSubsystemName, FString &InOutListName) const;

    /**
     * Called immediately after the session name is generated for a synthetic party, offering the integration a chance
     * to force a particular session name on the local subsystem (in case the platform requires specific values).
     */
    virtual void MutateSyntheticPartySessionNameIfRequired(
        FName InSubsystemName,
        const FString &EOSPartyId,
        FString &InOutSessionName) const;

    /**
     * Called immediately after the session settings are generated for a synthetic party, but before the session is
     * created, offering the integration a chance to add additional settings to the synthetic session (in case the
     * platform requires specific values).
     */
    virtual void MutateSyntheticPartySessionSettingsIfRequired(
        FName InSubsystemName,
        const FString &EOSPartyId,
        FOnlineSessionSettings &InOutSessionSettings) const;

    /**
     * Called immediately after the session name is generated for a synthetic session, offering the integration a chance
     * to force a particular session name on the local subsystem (in case the platform requires specific values).
     */
    virtual void MutateSyntheticSessionSessionNameIfRequired(
        FName InSubsystemName,
        const FString &EOSSessionId,
        FString &InOutSessionName) const;

    /**
     * Called immediately after the session settings are generated for a synthetic session, but before the session is
     * created, offering the integration a chance to add additional settings to the synthetic session (in case the
     * platform requires specific values).
     */
    virtual void MutateSyntheticSessionSessionSettingsIfRequired(
        FName InSubsystemName,
        const FString &EOSSessionId,
        FOnlineSessionSettings &InOutSessionSettings) const;

    /**
     * Called when the synthetic friends subsystem sees an OnFriendsChange event while a ReadFriends operation is
     * in progress, to determine whether the event should be ignored.
     *
     * Some subsystems incorrectly raise the OnFriendsChange event from ReadFriendsList; semantically OnFriendsChange
     * is supposed to indicate that there are new friends to read, not that the ReadFriendsList operation is complete
     * (that is what the FOnReadFriendsListComplete delegate callback is for).
     *
     * This callback allows an integration to indicate that to say that the OnFriendsChange event should be ignored,
     * and that it does not mean that the ReadFriendsList operation is going out-of-date before it completes.
     */
    virtual void ShouldIgnoreOnFriendsChangeEventDuringReadFriendsOperation(
        FName InSubsystemName,
        bool &InOutShouldIgnore) const;
};

} // namespace Redpoint::EOS::Core
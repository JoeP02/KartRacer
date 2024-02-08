// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSCore/RuntimePlatformIntegration.h"

namespace Redpoint::EOS::Core
{

void IRuntimePlatformIntegration::MutateFriendsListNameIfRequired(FName InSubsystemName, FString &InOutListName) const
{
}

void IRuntimePlatformIntegration::MutateSyntheticPartySessionNameIfRequired(
    FName InSubsystemName,
    const FString &EOSPartyId,
    FString &InOutSessionName) const
{
}

void IRuntimePlatformIntegration::MutateSyntheticPartySessionSettingsIfRequired(
    FName InSubsystemName,
    const FString &EOSPartyId,
    FOnlineSessionSettings &InOutSessionSettings) const
{
}

void IRuntimePlatformIntegration::MutateSyntheticSessionSessionNameIfRequired(
    FName InSubsystemName,
    const FString &EOSSessionId,
    FString &InOutSessionName) const
{
}

void IRuntimePlatformIntegration::MutateSyntheticSessionSessionSettingsIfRequired(
    FName InSubsystemName,
    const FString &EOSSessionId,
    FOnlineSessionSettings &InOutSessionSettings) const
{
}

void IRuntimePlatformIntegration::ShouldIgnoreOnFriendsChangeEventDuringReadFriendsOperation(
    FName InSubsystemName,
    bool &InOutShouldIgnore) const
{
}

} // namespace Redpoint::EOS::Core
// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineAchievementsSubsystem.h"
#include "OnlineAvatarSubsystem.h"
#include "OnlineChatSubsystem.h"
#include "OnlineEntitlementsSubsystem.h"
#include "OnlineEventsSubsystem.h"
#include "OnlineExternalUISubsystem.h"
#include "OnlineFriendsSubsystem.h"
#include "OnlineGameActivitySubsystem.h"
#include "OnlineGameItemStatsSubsystem.h"
#include "OnlineGroupsSubsystem.h"
#include "OnlineIdentitySubsystem.h"
#include "OnlineLeaderboardsSubsystem.h"
#include "OnlineLobbySubsystem.h"
#include "OnlineMessageSubsystem.h"
#include "OnlineMessageSanitizerSubsystem.h"
#include "OnlinePartySubsystem.h"
#include "OnlinePresenceSubsystem.h"
#include "OnlinePurchaseSubsystem.h"
#include "OnlineSessionSubsystem.h"
#include "OnlineSharedCloudSubsystem.h"
#include "OnlineSharingSubsystem.h"
#include "OnlineStatsSubsystem.h"
#include "OnlineStoreV2Subsystem.h"
#include "OnlineTimeSubsystem.h"
#include "OnlineTitleFileSubsystem.h"
#include "OnlineTournamentSubsystem.h"
#include "OnlineTurnBasedSubsystem.h"
#include "OnlineUserSubsystem.h"
#include "OnlineUserCloudSubsystem.h"
#include "OnlineVoiceSubsystem.h"
#include "OnlineVoiceAdminSubsystem.h"
#include "OnlineVoiceChatSubsystem.h"
#include "VoiceChatUser.h"

#include "OnlineSubsystemBP.generated.h"

UCLASS(BlueprintType)
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

private:
    UPROPERTY()
    TMap<FString, UGameInstanceSubsystem*> SubsystemCache;

public:
    /** 
     * Gets the Achievements interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineAchievementsSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineAchievementsSubsystem* GetNamedAchievementsSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Avatar interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineAvatarSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineAvatarSubsystem* GetNamedAvatarSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Chat interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineChatSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineChatSubsystem* GetNamedChatSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Entitlements interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineEntitlementsSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineEntitlementsSubsystem* GetNamedEntitlementsSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Events interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineEventsSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineEventsSubsystem* GetNamedEventsSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the ExternalUI interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineExternalUISubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineExternalUISubsystem* GetNamedExternalUISubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Friends interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineFriendsSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineFriendsSubsystem* GetNamedFriendsSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the GameActivity interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineGameActivitySubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineGameActivitySubsystem* GetNamedGameActivitySubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the GameItemStats interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineGameItemStatsSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineGameItemStatsSubsystem* GetNamedGameItemStatsSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Groups interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineGroupsSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineGroupsSubsystem* GetNamedGroupsSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Identity interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineIdentitySubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineIdentitySubsystem* GetNamedIdentitySubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Leaderboards interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineLeaderboardsSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineLeaderboardsSubsystem* GetNamedLeaderboardsSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Lobby interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineLobbySubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineLobbySubsystem* GetNamedLobbySubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Message interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineMessageSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineMessageSubsystem* GetNamedMessageSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the MessageSanitizer interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineMessageSanitizerSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineMessageSanitizerSubsystem* GetNamedMessageSanitizerSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Party interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlinePartySubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlinePartySubsystem* GetNamedPartySubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Presence interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlinePresenceSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlinePresenceSubsystem* GetNamedPresenceSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Purchase interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlinePurchaseSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlinePurchaseSubsystem* GetNamedPurchaseSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Session interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineSessionSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineSessionSubsystem* GetNamedSessionSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the SharedCloud interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineSharedCloudSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineSharedCloudSubsystem* GetNamedSharedCloudSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Sharing interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineSharingSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineSharingSubsystem* GetNamedSharingSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Stats interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineStatsSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineStatsSubsystem* GetNamedStatsSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the StoreV2 interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineStoreV2Subsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineStoreV2Subsystem* GetNamedStoreV2Subsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Time interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineTimeSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineTimeSubsystem* GetNamedTimeSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the TitleFile interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineTitleFileSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineTitleFileSubsystem* GetNamedTitleFileSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Tournament interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineTournamentSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineTournamentSubsystem* GetNamedTournamentSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the TurnBased interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineTurnBasedSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineTurnBasedSubsystem* GetNamedTurnBasedSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the User interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineUserSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineUserSubsystem* GetNamedUserSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the UserCloud interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineUserCloudSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineUserCloudSubsystem* GetNamedUserCloudSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the Voice interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineVoiceSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineVoiceSubsystem* GetNamedVoiceSubsystem(FName SubsystemName = FName(TEXT("Default")));

    /** 
     * Gets the VoiceAdmin interface for the subsystem with the given name.
     * 
     * This can be used to access functionality on specific platforms (like Steam), even when you're not using that platform's online subsystem as the default. 
     * 
     * If you pass NAME_Default, this is the same as using the main "UOnlineVoiceAdminSubsystem" class from blueprints.
     * 
     * If you pass "Native" as the name, this returns the subsystem for the native OSS implementation on the current platform, as specified by NativePlatformService= in your Engine.ini file.
     * 
     * This function always returns a valid object, but its IsSubsystemAvailable() blueprint node will return false if the targeted subsystem name is not currently available or does not implement the requested interface. Therefore you should always check the result of IsSubsystemAvailable() before calling blueprints nodes off the returned subsystem at runtime.
     * */
    UFUNCTION(BlueprintPure, Category = "Online")
    UOnlineVoiceAdminSubsystem* GetNamedVoiceAdminSubsystem(FName SubsystemName = FName(TEXT("Default")));



};
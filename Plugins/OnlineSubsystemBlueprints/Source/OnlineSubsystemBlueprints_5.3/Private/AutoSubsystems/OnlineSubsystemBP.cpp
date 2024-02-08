// Copyright June Rhodes 2023. All Rights Reserved.

#include "OnlineSubsystemBP.h"
#include "OnlineSubsystemBlueprintsModule.h"

UOnlineAchievementsSubsystem* UOnlineSubsystem::GetNamedAchievementsSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedAchievementsSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineAchievementsSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Achievements|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineAchievementsSubsystem* ExistingInstance = Cast<UOnlineAchievementsSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineAchievementsSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineAchievementsSubsystem* NewInstance = NewObject<UOnlineAchievementsSubsystem>(GetGameInstance());
    UOnlineAchievementsSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineAvatarSubsystem* UOnlineSubsystem::GetNamedAvatarSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedAvatarSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineAvatarSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Avatar|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineAvatarSubsystem* ExistingInstance = Cast<UOnlineAvatarSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineAvatarSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineAvatarSubsystem* NewInstance = NewObject<UOnlineAvatarSubsystem>(GetGameInstance());
    UOnlineAvatarSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineChatSubsystem* UOnlineSubsystem::GetNamedChatSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedChatSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineChatSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Chat|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineChatSubsystem* ExistingInstance = Cast<UOnlineChatSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineChatSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineChatSubsystem* NewInstance = NewObject<UOnlineChatSubsystem>(GetGameInstance());
    UOnlineChatSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineEntitlementsSubsystem* UOnlineSubsystem::GetNamedEntitlementsSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedEntitlementsSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineEntitlementsSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Entitlements|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineEntitlementsSubsystem* ExistingInstance = Cast<UOnlineEntitlementsSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineEntitlementsSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineEntitlementsSubsystem* NewInstance = NewObject<UOnlineEntitlementsSubsystem>(GetGameInstance());
    UOnlineEntitlementsSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineEventsSubsystem* UOnlineSubsystem::GetNamedEventsSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedEventsSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineEventsSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Events|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineEventsSubsystem* ExistingInstance = Cast<UOnlineEventsSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineEventsSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineEventsSubsystem* NewInstance = NewObject<UOnlineEventsSubsystem>(GetGameInstance());
    UOnlineEventsSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineExternalUISubsystem* UOnlineSubsystem::GetNamedExternalUISubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedExternalUISubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineExternalUISubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("ExternalUI|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineExternalUISubsystem* ExistingInstance = Cast<UOnlineExternalUISubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineExternalUISubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineExternalUISubsystem* NewInstance = NewObject<UOnlineExternalUISubsystem>(GetGameInstance());
    UOnlineExternalUISubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineFriendsSubsystem* UOnlineSubsystem::GetNamedFriendsSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedFriendsSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineFriendsSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Friends|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineFriendsSubsystem* ExistingInstance = Cast<UOnlineFriendsSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineFriendsSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineFriendsSubsystem* NewInstance = NewObject<UOnlineFriendsSubsystem>(GetGameInstance());
    UOnlineFriendsSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineGameActivitySubsystem* UOnlineSubsystem::GetNamedGameActivitySubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedGameActivitySubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineGameActivitySubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("GameActivity|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineGameActivitySubsystem* ExistingInstance = Cast<UOnlineGameActivitySubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineGameActivitySubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineGameActivitySubsystem* NewInstance = NewObject<UOnlineGameActivitySubsystem>(GetGameInstance());
    UOnlineGameActivitySubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineGameItemStatsSubsystem* UOnlineSubsystem::GetNamedGameItemStatsSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedGameItemStatsSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineGameItemStatsSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("GameItemStats|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineGameItemStatsSubsystem* ExistingInstance = Cast<UOnlineGameItemStatsSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineGameItemStatsSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineGameItemStatsSubsystem* NewInstance = NewObject<UOnlineGameItemStatsSubsystem>(GetGameInstance());
    UOnlineGameItemStatsSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineGroupsSubsystem* UOnlineSubsystem::GetNamedGroupsSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedGroupsSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineGroupsSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Groups|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineGroupsSubsystem* ExistingInstance = Cast<UOnlineGroupsSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineGroupsSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineGroupsSubsystem* NewInstance = NewObject<UOnlineGroupsSubsystem>(GetGameInstance());
    UOnlineGroupsSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineIdentitySubsystem* UOnlineSubsystem::GetNamedIdentitySubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedIdentitySubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineIdentitySubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Identity|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineIdentitySubsystem* ExistingInstance = Cast<UOnlineIdentitySubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineIdentitySubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineIdentitySubsystem* NewInstance = NewObject<UOnlineIdentitySubsystem>(GetGameInstance());
    UOnlineIdentitySubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineLeaderboardsSubsystem* UOnlineSubsystem::GetNamedLeaderboardsSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedLeaderboardsSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineLeaderboardsSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Leaderboards|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineLeaderboardsSubsystem* ExistingInstance = Cast<UOnlineLeaderboardsSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineLeaderboardsSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineLeaderboardsSubsystem* NewInstance = NewObject<UOnlineLeaderboardsSubsystem>(GetGameInstance());
    UOnlineLeaderboardsSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineLobbySubsystem* UOnlineSubsystem::GetNamedLobbySubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedLobbySubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineLobbySubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Lobby|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineLobbySubsystem* ExistingInstance = Cast<UOnlineLobbySubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineLobbySubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineLobbySubsystem* NewInstance = NewObject<UOnlineLobbySubsystem>(GetGameInstance());
    UOnlineLobbySubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineMessageSubsystem* UOnlineSubsystem::GetNamedMessageSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedMessageSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineMessageSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Message|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineMessageSubsystem* ExistingInstance = Cast<UOnlineMessageSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineMessageSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineMessageSubsystem* NewInstance = NewObject<UOnlineMessageSubsystem>(GetGameInstance());
    UOnlineMessageSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineMessageSanitizerSubsystem* UOnlineSubsystem::GetNamedMessageSanitizerSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedMessageSanitizerSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineMessageSanitizerSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("MessageSanitizer|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineMessageSanitizerSubsystem* ExistingInstance = Cast<UOnlineMessageSanitizerSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineMessageSanitizerSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineMessageSanitizerSubsystem* NewInstance = NewObject<UOnlineMessageSanitizerSubsystem>(GetGameInstance());
    UOnlineMessageSanitizerSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlinePartySubsystem* UOnlineSubsystem::GetNamedPartySubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedPartySubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlinePartySubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Party|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlinePartySubsystem* ExistingInstance = Cast<UOnlinePartySubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlinePartySubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlinePartySubsystem* NewInstance = NewObject<UOnlinePartySubsystem>(GetGameInstance());
    UOnlinePartySubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlinePresenceSubsystem* UOnlineSubsystem::GetNamedPresenceSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedPresenceSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlinePresenceSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Presence|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlinePresenceSubsystem* ExistingInstance = Cast<UOnlinePresenceSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlinePresenceSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlinePresenceSubsystem* NewInstance = NewObject<UOnlinePresenceSubsystem>(GetGameInstance());
    UOnlinePresenceSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlinePurchaseSubsystem* UOnlineSubsystem::GetNamedPurchaseSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedPurchaseSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlinePurchaseSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Purchase|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlinePurchaseSubsystem* ExistingInstance = Cast<UOnlinePurchaseSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlinePurchaseSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlinePurchaseSubsystem* NewInstance = NewObject<UOnlinePurchaseSubsystem>(GetGameInstance());
    UOnlinePurchaseSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineSessionSubsystem* UOnlineSubsystem::GetNamedSessionSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedSessionSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineSessionSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Session|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineSessionSubsystem* ExistingInstance = Cast<UOnlineSessionSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineSessionSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineSessionSubsystem* NewInstance = NewObject<UOnlineSessionSubsystem>(GetGameInstance());
    UOnlineSessionSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineSharedCloudSubsystem* UOnlineSubsystem::GetNamedSharedCloudSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedSharedCloudSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineSharedCloudSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("SharedCloud|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineSharedCloudSubsystem* ExistingInstance = Cast<UOnlineSharedCloudSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineSharedCloudSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineSharedCloudSubsystem* NewInstance = NewObject<UOnlineSharedCloudSubsystem>(GetGameInstance());
    UOnlineSharedCloudSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineSharingSubsystem* UOnlineSubsystem::GetNamedSharingSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedSharingSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineSharingSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Sharing|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineSharingSubsystem* ExistingInstance = Cast<UOnlineSharingSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineSharingSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineSharingSubsystem* NewInstance = NewObject<UOnlineSharingSubsystem>(GetGameInstance());
    UOnlineSharingSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineStatsSubsystem* UOnlineSubsystem::GetNamedStatsSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedStatsSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineStatsSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Stats|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineStatsSubsystem* ExistingInstance = Cast<UOnlineStatsSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineStatsSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineStatsSubsystem* NewInstance = NewObject<UOnlineStatsSubsystem>(GetGameInstance());
    UOnlineStatsSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineStoreV2Subsystem* UOnlineSubsystem::GetNamedStoreV2Subsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedStoreV2Subsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineStoreV2Subsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("StoreV2|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineStoreV2Subsystem* ExistingInstance = Cast<UOnlineStoreV2Subsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineStoreV2Subsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineStoreV2Subsystem* NewInstance = NewObject<UOnlineStoreV2Subsystem>(GetGameInstance());
    UOnlineStoreV2Subsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineTimeSubsystem* UOnlineSubsystem::GetNamedTimeSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedTimeSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineTimeSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Time|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineTimeSubsystem* ExistingInstance = Cast<UOnlineTimeSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineTimeSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineTimeSubsystem* NewInstance = NewObject<UOnlineTimeSubsystem>(GetGameInstance());
    UOnlineTimeSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineTitleFileSubsystem* UOnlineSubsystem::GetNamedTitleFileSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedTitleFileSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineTitleFileSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("TitleFile|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineTitleFileSubsystem* ExistingInstance = Cast<UOnlineTitleFileSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineTitleFileSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineTitleFileSubsystem* NewInstance = NewObject<UOnlineTitleFileSubsystem>(GetGameInstance());
    UOnlineTitleFileSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineTournamentSubsystem* UOnlineSubsystem::GetNamedTournamentSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedTournamentSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineTournamentSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Tournament|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineTournamentSubsystem* ExistingInstance = Cast<UOnlineTournamentSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineTournamentSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineTournamentSubsystem* NewInstance = NewObject<UOnlineTournamentSubsystem>(GetGameInstance());
    UOnlineTournamentSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineTurnBasedSubsystem* UOnlineSubsystem::GetNamedTurnBasedSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedTurnBasedSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineTurnBasedSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("TurnBased|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineTurnBasedSubsystem* ExistingInstance = Cast<UOnlineTurnBasedSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineTurnBasedSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineTurnBasedSubsystem* NewInstance = NewObject<UOnlineTurnBasedSubsystem>(GetGameInstance());
    UOnlineTurnBasedSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineUserSubsystem* UOnlineSubsystem::GetNamedUserSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedUserSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineUserSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("User|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineUserSubsystem* ExistingInstance = Cast<UOnlineUserSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineUserSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineUserSubsystem* NewInstance = NewObject<UOnlineUserSubsystem>(GetGameInstance());
    UOnlineUserSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineUserCloudSubsystem* UOnlineSubsystem::GetNamedUserCloudSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedUserCloudSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineUserCloudSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("UserCloud|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineUserCloudSubsystem* ExistingInstance = Cast<UOnlineUserCloudSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineUserCloudSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineUserCloudSubsystem* NewInstance = NewObject<UOnlineUserCloudSubsystem>(GetGameInstance());
    UOnlineUserCloudSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineVoiceSubsystem* UOnlineSubsystem::GetNamedVoiceSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedVoiceSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineVoiceSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("Voice|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineVoiceSubsystem* ExistingInstance = Cast<UOnlineVoiceSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineVoiceSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineVoiceSubsystem* NewInstance = NewObject<UOnlineVoiceSubsystem>(GetGameInstance());
    UOnlineVoiceSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}

UOnlineVoiceAdminSubsystem* UOnlineSubsystem::GetNamedVoiceAdminSubsystem(FName SubsystemName)
{
    if (SubsystemName.IsEqual(NAME_None))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("'None' passed to GetNamedVoiceAdminSubsystem. This is an invalid call and no subsystem will be returned. You must pass 'Default', 'Native' or the name of a subsystem."));
        return nullptr;
    }

    if (SubsystemName.IsEqual(NAME_Default))
    {
        return UGameInstance::GetSubsystem<UOnlineVoiceAdminSubsystem>(GetGameInstance());
    }

    FString Key = FString::Printf(TEXT("VoiceAdmin|%s"), *SubsystemName.ToString());
    if (this->SubsystemCache.Contains(Key))
    {
        UOnlineVoiceAdminSubsystem* ExistingInstance = Cast<UOnlineVoiceAdminSubsystem>(this->SubsystemCache[Key]);
        if (!IsValid(ExistingInstance))
        {
            this->SubsystemCache.Remove(Key);
        }
        else
        {
            return ExistingInstance;
        }
    }

    UOnlineVoiceAdminSubsystem::OSSNameToAssignDuringConstruction = SubsystemName;
    UOnlineVoiceAdminSubsystem* NewInstance = NewObject<UOnlineVoiceAdminSubsystem>(GetGameInstance());
    UOnlineVoiceAdminSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;
    this->SubsystemCache.Add(Key, NewInstance);
    return NewInstance;
}
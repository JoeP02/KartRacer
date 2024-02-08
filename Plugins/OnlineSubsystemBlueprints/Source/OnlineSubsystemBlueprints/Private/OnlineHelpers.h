// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "AutoSubsystems/OnlinePartySubsystem.h"
#include "AutoSubsystems/OnlineSessionSubsystem.h"
#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/OSBFileTypes.h"
#include "Types/OSBPartyTypes.h"

#include "OnlineHelpers.generated.h"

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineHelpers : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Convert the unique net ID to it's string representation */
    UFUNCTION(
        BlueprintPure,
        Category = "Online",
        Meta =
            (DisplayName = "ToString (FUniqueNetIdRepl)",
             CompactNodeTitle = "->",
             Keywords = "FUniqueNetIdRepl netid cast convert to string",
             BlueprintAutocast,
             IgnoreTypePromotion))
    static FString Conv_FUniqueNetIdReplToString(FUniqueNetIdRepl InNetId);

    /** Return the name of the current subsystem (e.g. Steam) */
    UFUNCTION(
        BlueprintPure,
        Category = "Online",
        Meta =
            (DisplayName = "Get Current Subsystem Name",
             Keywords = "subsystem name",
             WorldContext = "WorldContextObject",
             BlueprintAutocast,
             IgnoreTypePromotion))
    static FName GetCurrentSubsystemName(const UObject *WorldContextObject);

    /** Return the subsystem name of the unique net ID */
    UFUNCTION(
        BlueprintPure,
        Category = "Online",
        Meta =
            (DisplayName = "Get User Id Subsystem Name",
             Keywords = "FUniqueNetIdRepl netid subsystem type name",
             BlueprintAutocast,
             IgnoreTypePromotion))
    static FName FUniqueNetIdGetType(FUniqueNetIdRepl InNetId);

    /** Return true if the unique net ID is valid */
    UFUNCTION(
        BlueprintPure,
        Category = "Online",
        Meta =
            (DisplayName = "Is Valid (FUniqueNetIdRepl)",
             Keywords = "FUniqueNetIdRepl netid subsystem is valid",
             BlueprintAutocast,
             IgnoreTypePromotion))
    static bool FUniqueNetIdIsValid(FUniqueNetIdRepl InNetId);

    /** Returns true if the unique net IDs are equal (A == B) */
    UFUNCTION(
        BlueprintPure,
        meta =
            (DisplayName = "Equal Unique Net Id", CompactNodeTitle = "==", Keywords = "== equal", IgnoreTypePromotion),
        Category = "Online")
    static bool EqualEqual_FUniqueNetIdReplFUniqueNetIdRepl(const FUniqueNetIdRepl &InA, const FUniqueNetIdRepl &InB);

    /** Returns true if the party IDs are equal (A == B) */
    UFUNCTION(
        BlueprintPure,
        meta = (DisplayName = "Equal Party Id", CompactNodeTitle = "==", Keywords = "== equal", IgnoreTypePromotion),
        Category = "Online")
    static bool EqualEqual_PartyIdPartyId(UPartyId *A, UPartyId *B);

    /** Returns true if the party ID is valid */
    UFUNCTION(
        BlueprintPure,
        meta =
            (DisplayName = "Party Id Is Valid?",
             CompactNodeTitle = "Valid?",
             Keywords = "is valid",
             IgnoreTypePromotion),
        Category = "Online")
    static bool IsValid_PartyId(UPartyId *A);

    /** Returns true if the lobby IDs are equal (A == B) */
    UFUNCTION(
        BlueprintPure,
        meta = (DisplayName = "Equal Lobby Id", CompactNodeTitle = "==", Keywords = "== equal", IgnoreTypePromotion),
        Category = "Online")
    static bool EqualEqual_LobbyIdLobbyId(ULobbyId *A, ULobbyId *B);

    /** Returns true if the lobby ID is valid */
    UFUNCTION(
        BlueprintPure,
        meta =
            (DisplayName = "Lobby Id Is Valid?",
             CompactNodeTitle = "Valid?",
             Keywords = "is valid",
             IgnoreTypePromotion),
        Category = "Online")
    static bool IsValid_LobbyId(ULobbyId *A);

    /** Returns the primary party type */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Primary Party Type", IgnoreTypePromotion), Category = "Online")
    static int64 GetPrimaryPartyType()
    {
        return (int64)IOnlinePartySystem::GetPrimaryPartyTypeId().GetValue();
    }

    /** Gets the connection string for a session by name */
    UFUNCTION(
        BlueprintPure,
        meta = (DisplayName = "Get Resolved Connect String (from Session Name)", IgnoreTypePromotion),
        Category = "Online|Sessions")
    static void GetResolvedConnectStringByName(
        class UOnlineSessionSubsystem *Subsystem,
        FName SessionName,
        FName PortType,
        bool &bWasSuccessful,
        FString &OutConnectInfo);

    /** Gets the connection string for a search result */
    UFUNCTION(
        BlueprintPure,
        meta = (DisplayName = "Get Resolved Connect String (from Search Result)", IgnoreTypePromotion),
        Category = "Online|Sessions")
    static void GetResolvedConnectStringBySearchResult(
        class UOnlineSessionSubsystem *Subsystem,
        FOnlineSessionSearchResultBP SearchResult,
        FName PortType,
        bool &bWasSuccessful,
        FString &OutConnectInfo);

    /** Gets the unique net ID for the player controller */
    UFUNCTION(
        BlueprintPure,
        meta = (DisplayName = "Get Controller Unique Net Id", IgnoreTypePromotion),
        Category = "Online")
    static FUniqueNetIdRepl GetControllerUniqueNetId(APlayerController *PlayerController);

    /** Gets the unique net ID for the player state */
    UFUNCTION(
        BlueprintPure,
        meta = (DisplayName = "Get Player State Unique Net Id", IgnoreTypePromotion),
        Category = "Online")
    static FUniqueNetIdRepl GetPlayerStateUniqueNetId(APlayerState *PlayerState);

    /**
     * Create a mutable party data based on read-only party data. You must use this if you want to modify the party data
     * you got from GetPartyData so that you can pass it to UpdatePartyData.
     */
    UFUNCTION(
        BlueprintCallable,
        meta = (DisplayName = "Create Modifiable Party Data", Keywords = "modify party data set", IgnoreTypePromotion),
        Category = "Online")
    static UMutablePartyData *CreateMutablePartyData(UReadablePartyData *ReadOnlyPartyData);

    /**
     * Create file data from a string; that is, the string will be the entire contents of the file.
     */
    UFUNCTION(
        BlueprintCallable,
        meta =
            (DisplayName = "Create File Data from String",
             Keywords = "file data filedata create user title cloud string",
             IgnoreTypePromotion),
        Category = "Online|Files")
    static UFileData *CreateFileDataFromString(const FString &String);

    /**
     * Read file data as a string, and return the string value.
     */
    UFUNCTION(
        BlueprintCallable,
        meta =
            (DisplayName = "Read File Data as String",
             Keywords = "file data filedata read user title cloud string",
             IgnoreTypePromotion),
        Category = "Online|Files")
    static FString ReadFileDataAsString(UFileData *FileData);

    /**
     * Create file data from a save game.
     */
    UFUNCTION(
        BlueprintCallable,
        meta =
            (DisplayName = "Create File Data from Save Game",
             Keywords = "file data filedata create user title cloud save game",
             IgnoreTypePromotion),
        Category = "Online|Files")
    static UFileData *CreateFileDataFromSaveGame(USaveGame *SaveGame);

    /**
     * Read file data as a string, and return the string value.
     */
    UFUNCTION(
        BlueprintCallable,
        meta =
            (DisplayName = "Read File Data as Save Game",
             Keywords = "file data filedata read user title cloud save game",
             IgnoreTypePromotion),
        Category = "Online|Files")
    static USaveGame *ReadFileDataAsSaveGame(UFileData *FileData);

    /**
     * Convert a lobby ID into a joinable party info.
     */
    UFUNCTION(
        BlueprintCallable,
        meta =
            (DisplayName = "Convert Lobby Id to Party Join Info",
             Keywords = "convert lobby id party join info",
             BlueprintAutocast,
             IgnoreTypePromotion),
        Category = "Online")
    static UOnlinePartyJoinInfo *Conv_ULobbyIdToUOnlinePartyJoinInfo(
        FUniqueNetIdRepl InLocalUserId,
        UOnlinePartySubsystem *InPartySubsystem,
        ULobbyId *InLobbyId);
};

TSharedPtr<class IMessageSanitizer, ESPMode::ThreadSafe> GetMessageSanitizerSafe(IOnlineSubsystem *OSS);
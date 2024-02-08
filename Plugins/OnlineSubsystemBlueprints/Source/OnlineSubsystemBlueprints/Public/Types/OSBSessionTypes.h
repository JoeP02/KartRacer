// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBSessionTypes.generated.h"

UENUM(BlueprintType, Meta = (ScriptName = "EOnJoinSessionCompleteResult"))
enum class EOnJoinSessionCompleteResult_ : uint8
{
    /** The join worked as expected */
    Success,
    /** There are no open slots to join */
    SessionIsFull,
    /** The session couldn't be found on the service */
    SessionDoesNotExist,
    /** There was an error getting the session server's address */
    CouldNotRetrieveAddress,
    /** The user attempting to join is already a member of the session */
    AlreadyInSession,
    /** An error not covered above occurred */
    UnknownError
};

UENUM(BlueprintType, Meta = (ScriptName = "ESessionFailure"))
enum class ESessionFailure_ : uint8
{
    /** General loss of connection */
    ServiceConnectionLost
};

UENUM(BlueprintType, Meta = (ScriptName = "EOnlineSessionState"))
enum class EOnlineSessionState_ : uint8
{
    /** An online session has not been created yet */
    NoSession,
    /** An online session is in the process of being created */
    Creating,
    /** Session has been created but the session hasn't started (pre match lobby) */
    Pending,
    /** Session has been asked to start (may take time due to communication with backend) */
    Starting,
    /** The current session has started. Sessions with join in progress disabled are no longer joinable */
    InProgress,
    /** The session is still valid, but the session is no longer being played (post match lobby) */
    Ending,
    /** The session is closed and any stats committed */
    Ended,
    /** The session is being destroyed */
    Destroying
};

UENUM(BlueprintType, Meta = (ScriptName = "EOnSessionParticipantLeftReason"))
enum class EOnSessionParticipantLeftReason_ : uint8
{
    /** The participant left the session of their own accord */
    Left,
    /** The participant got disconnected from a session that is still active */
    Disconnected,
    /** The participant was forcefully removed from the session */
    Kicked,
    /** The session ended and the participant got removed from it */
    Closed
};

UCLASS(BlueprintType, Transient, Meta = (DontUseGenericSpawnObject, IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineSessionInfo : public UObject
{
    GENERATED_BODY()

private:
    TSharedPtr<class FOnlineSessionInfo> SessionInfo;

public:
    static UOnlineSessionInfo *FromNative(TSharedPtr<class FOnlineSessionInfo> InSessionInfo);
    TSharedPtr<class FOnlineSessionInfo> ToNative() const
    {
        return this->SessionInfo;
    }
    bool IsValid() const
    {
        return this->SessionInfo.IsValid();
    }
};

UENUM(BlueprintType, Meta = (ScriptName = "EOnlineDataAdvertisementType"))
enum class EOnlineDataAdvertisementType_ : uint8
{
    /** Don't advertise via the online service or QoS data */
    DontAdvertise,
    /** Advertise via the server ping data only */
    ViaPingOnly,
    /** Advertise via the online service only */
    ViaOnlineService,
    /** Advertise via the online service and via the ping data */
    ViaOnlineServiceAndPing
};

UENUM(BlueprintType, Meta = (ScriptName = "EOnlineKeyValuePairDataType"))
enum class EOnlineKeyValuePairDataType_ : uint8
{
    /** Means the data in the OnlineData value fields should be ignored */
    Empty,
    /** 32 bit integer */
    Int32,
    /** 32 bit unsigned integer */
    UInt32_NotSupported,
    /** 64 bit integer */
    Int64,
    /** 64 bit unsigned integer */
    UInt64_NotSupported,
    /** Double (8 byte) */
    Double_NotSupported,
    /** Unicode string */
    String,
    /** Float (4 byte) */
    Float,
    /** Binary data */
    Blob_NotSupported,
    /** bool data (1 byte) */
    Bool,
    /** Serialized json text */
    Json_NotSupported
};

USTRUCT(BlueprintType) struct ONLINESUBSYSTEMBLUEPRINTS_API FVariantDataBP
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    EOnlineKeyValuePairDataType_ Type = EOnlineKeyValuePairDataType_::Empty;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool AsBool = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 AsInt = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    float AsFloat = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int64 AsInt64 = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString AsString;

    static FVariantDataBP FromNative(const FVariantData &InObj);
    FVariantData ToNative() const;
};

USTRUCT(BlueprintType) struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineSessionSettingBP
{
    GENERATED_BODY()

public:
    FOnlineSessionSettingBP() = default;

    /** Settings value */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FVariantDataBP Data;

    /** How is this session setting advertised with the backend or searches */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    EOnlineDataAdvertisementType_ AdvertisementType = EOnlineDataAdvertisementType_::DontAdvertise;

    /** Optional ID used in some platforms as the index instead of the session name */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 ID = 0;

    static FOnlineSessionSettingBP FromNative(const FOnlineSessionSetting &InObj);
    FOnlineSessionSetting ToNative();
};

USTRUCT(BlueprintType) struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineSessionMemberSettingsBP
{
    GENERATED_BODY()

public:
    /** The user these settings are for */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FUniqueNetIdRepl MemberUserId;

    /** The user's custom session settings */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    TMap<FName, FOnlineSessionSettingBP> MemberSettings;
};

USTRUCT(BlueprintType) struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineSessionSettingsBP
{
    GENERATED_BODY()

private:
    FOnlineSessionSettings RefTemp;

public:
    /** The number of publicly available connections advertised */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 NumPublicConnections = 0;

    /** The number of connections that are private (invite/password) only */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 NumPrivateConnections = 0;

    /** Whether this match is publicly advertised on the online service */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bShouldAdvertise = false;

    /** Whether joining in progress is allowed or not */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bAllowJoinInProgress = false;

    /** This game will be lan only and not be visible to external players */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bIsLANMatch = false;

    /** Whether the server is dedicated or player hosted */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bIsDedicated = false;

    /** Whether the match should gather stats or not */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bUsesStats = false;

    /** Whether the match allows invitations for this session or not */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bAllowInvites = false;

    /** Whether to display user presence information or not */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bUsesPresence = false;

    /** Whether joining via player presence is allowed or not */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bAllowJoinViaPresence = false;

    /** Whether joining via player presence is allowed for friends only or not */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bAllowJoinViaPresenceFriendsOnly = false;

    /** Whether the server employs anti-cheat (punkbuster, vac, etc) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bAntiCheatProtected = false;

    /** Whether to prefer lobbies APIs if the platform supports them */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bUseLobbiesIfAvailable = false;

    /** Whether to create (and auto join) a voice chat room for the lobby, if the platform supports it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool bUseLobbiesVoiceChatIfAvailable = false;

    /** Used to keep different builds from seeing each other during searches */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 BuildUniqueId = 0;

    /** Array of custom session settings */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    TMap<FName, FOnlineSessionSettingBP> Settings;

    /** Map of session settings per user */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    TArray<FOnlineSessionMemberSettingsBP> MemberSettings;

    static FOnlineSessionSettingsBP FromNative(const FOnlineSessionSettings &InObj);
    FOnlineSessionSettings ToNative();
    FOnlineSessionSettings &ToNativeRef();
};

/**
 * A wrapping class around the optional FOnlineSessionSettingsBP value that is returned from
 * some functions. Call GetValue() to get the actual data.
 */
UCLASS(BlueprintType, Transient, Meta = (DontUseGenericSpawnObject, IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineSessionSettings : public UObject
{
    GENERATED_BODY()

private:
    FOnlineSessionSettingsBP Value;

public:
    static UOnlineSessionSettings *FromNative(class FOnlineSessionSettings *InSession);

    UFUNCTION(BlueprintPure, Category = "Online")
    FOnlineSessionSettingsBP GetValue()
    {
        return this->Value;
    }
};

USTRUCT(BlueprintType) struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineSessionBP
{
    GENERATED_BODY()

public:
    /** Owner of the session */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FUniqueNetIdRepl OwningUserId;

    /** Owner name of the session */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString OwningUserName;

    /** The settings associated with this session */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FOnlineSessionSettingsBP SessionSettings;

    /** The platform specific session information */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    UOnlineSessionInfo *SessionInfo = nullptr;

    /** The number of private connections that are available (read only) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online")
    int32 NumOpenPrivateConnections = 0;

    /** The number of publicly available connections that are available (read only) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online")
    int32 NumOpenPublicConnections = 0;

    /** The session ID as a string (read only) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online")
    FString SessionId;

    static FOnlineSessionBP FromNative(const FOnlineSession &InObj);
    FOnlineSession ToNative();
};

USTRUCT(BlueprintType) struct ONLINESUBSYSTEMBLUEPRINTS_API FNamedOnlineSessionBP : public FOnlineSessionBP
{
    GENERATED_BODY()

public:
    /** The name of the session */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online")
    FName SessionName;

    /** Whether or not the local player is hosting this session */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online")
    bool bHosting = false;

    /** NetId of the local player that created this named session.  Could be the host, or a player joining a session. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online")
    FUniqueNetIdRepl LocalOwnerId;

    /** List of players registered in the session */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online")
    TArray<FUniqueNetIdRepl> RegisteredPlayers;

    /** State of the session */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online")
    EOnlineSessionState_ SessionState = EOnlineSessionState_::NoSession;

    static FNamedOnlineSessionBP FromNative(const FNamedOnlineSession &InObj);
};

/**
 * A wrapping class around the optional FNamedOnlineSessionBP value that is returned from
 * some functions. Call GetValue() to get the actual data.
 */
UCLASS(BlueprintType, Transient, Meta = (DontUseGenericSpawnObject, IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API UNamedOnlineSession : public UObject
{
    GENERATED_BODY()

private:
    FNamedOnlineSessionBP Value;

public:
    static UNamedOnlineSession *FromNative(class FNamedOnlineSession *InSession);

    UFUNCTION(BlueprintPure, Category = "Online")
    FNamedOnlineSessionBP GetValue()
    {
        return this->Value;
    }
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineSessionSearchResultBP
{
    GENERATED_BODY()

public:
    /** All advertised session information */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FOnlineSessionBP Session;

    /** Ping to the search result, MAX_QUERY_PING is unreachable */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int PingInMs = 0;

    static FOnlineSessionSearchResultBP FromNative(const FOnlineSessionSearchResult &InObj);
    FOnlineSessionSearchResult ToNative();
};

UENUM(BlueprintType, Meta = (ScriptName = "EOnlineAsyncTaskState"))
enum class EOnlineAsyncTaskState_ : uint8
{
    /** The task has not been started */
    NotStarted,
    /** The task is currently being processed */
    InProgress,
    /** The task has completed successfully */
    Done,
    /** The task failed to complete */
    Failed
};

UENUM(BlueprintType, Meta = (ScriptName = "EOnlineComparisonOp"))
enum class EOnlineComparisonOp_ : uint8
{
    Equals,
    NotEquals,
    GreaterThan,
    GreaterThanEquals,
    LessThan,
    LessThanEquals,
    Near,
    In,
    NotIn
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FSessionSearchParamBP
{
    GENERATED_BODY()

public:
    /* The value of the search parameter. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FVariantDataBP Data;

    /* The comparison operator. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    EOnlineComparisonOp_ Op = EOnlineComparisonOp_::Equals;

    /* The ID of the parameter - only used by some subsystems. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 ID = 0;
};

UCLASS(BlueprintType, Meta = (IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineSessionSearch : public UObject
{
    GENERATED_BODY()

private:
    TSharedPtr<class FOnlineSessionSearch> Search;
    TSharedPtr<TSharedRef<class FOnlineSessionSearch>> SearchTemp;
    void SyncPropertiesFromNative();
    void SyncPropertiesToNative();

public:
    virtual void PostInitProperties() override;

    UFUNCTION(BlueprintCallable, Category = "Online")
    TArray<FOnlineSessionSearchResultBP> GetSearchResults() const;

    UFUNCTION(BlueprintPure, Category = "Online")
    EOnlineAsyncTaskState_ GetSearchState() const;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Online")
    int32 MaxSearchResults;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Online")
    bool bIsLanQuery;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Online")
    int32 PingBucketSize;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Online")
    int32 PlatformHash;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Online")
    float TimeoutInSeconds;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Online")
    TMap<FName, FSessionSearchParamBP> SearchParams;

    TSharedRef<class FOnlineSessionSearch> ToNative();
    TSharedRef<class FOnlineSessionSearch> &ToNativeRef();
    bool IsValid() const;
};
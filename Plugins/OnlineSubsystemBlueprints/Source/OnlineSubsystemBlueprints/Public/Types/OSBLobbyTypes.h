// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Interfaces/OnlinePartyInterface.h"
#include "OSBSessionTypes.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBLobbyTypes.generated.h"

// These are defined in Interfaces/OnlineLobbyInterface.h, which is not
// a public header in this module. You should clone your own copy from
// https://src.redpoint.games/redpointgames/online-interfaces
// and place them in your game module if you want to use these types.
class FOnlineLobby;
class FOnlineLobbyTransaction;
class FOnlineLobbyMemberTransaction;
class FOnlineLobbySearchQueryFilter;
class FOnlineLobbySearchQuery;

UCLASS(BlueprintType, Transient, Meta = (DontUseGenericSpawnObject, IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API ULobbyId : public UObject
{
    GENERATED_BODY()

private:
    TSharedPtr<const FOnlinePartyId> LobbyId;

public:
    static ULobbyId *FromNative(const FOnlinePartyId &InObj);
    static ULobbyId *FromNative(const TSharedPtr<const FOnlinePartyId> &InObj);
    const FOnlinePartyId &ToNative() const;
    bool IsValid() const;

    UFUNCTION(BlueprintPure, Category = "Online")
    FString ToDebugString();
};

UCLASS(BlueprintType, Transient, Meta = (DontUseGenericSpawnObject, IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API ULobby : public UObject
{
    GENERATED_BODY()

private:
    TSharedPtr<FOnlineLobby> Lobby;

public:
    UFUNCTION(BlueprintPure, Category = "Online")
    ULobbyId *GetId();

    UFUNCTION(BlueprintPure, Category = "Online")
    FUniqueNetIdRepl GetOwnerId();

    static ULobby *FromNative(TSharedPtr<FOnlineLobby> InObj);
    TSharedPtr<FOnlineLobby> ToNative() const;
    bool IsValid() const;
};

UCLASS(BlueprintType, Transient, Meta = (DontUseGenericSpawnObject, IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineLobbyTransaction : public UObject
{
    GENERATED_BODY()

private:
    TSharedPtr<FOnlineLobbyTransaction> Txn;

public:
    UFUNCTION(BlueprintCallable, Category = "Online")
    void SetMetadata(const FString &Key, const FVariantDataBP &Value);

    UFUNCTION(BlueprintCallable, Category = "Online")
    void SetMetadataByMap(const TMap<FString, FVariantDataBP> &Metadata);

    UFUNCTION(BlueprintCallable, Category = "Online")
    void DeleteMetadata(const FString &Key);

    UFUNCTION(BlueprintCallable, Category = "Online")
    void DeleteMetadataByArray(const TArray<FString> &MetadataKeys);

    UFUNCTION(BlueprintCallable, Category = "Online")
    void SetLocked(bool Locked);

    UFUNCTION(BlueprintCallable, Category = "Online")
    void SetCapacity(int64 Capacity);

    UFUNCTION(BlueprintCallable, Category = "Online")
    void SetPublic(bool Public);

    static UOnlineLobbyTransaction *FromNative(TSharedPtr<FOnlineLobbyTransaction> InObj);
    TSharedPtr<FOnlineLobbyTransaction> ToNative() const;
    bool IsValid() const;
};

UCLASS(BlueprintType, Transient, Meta = (DontUseGenericSpawnObject, IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineLobbyMemberTransaction : public UObject
{
    GENERATED_BODY()

private:
    TSharedPtr<FOnlineLobbyMemberTransaction> Txn;

public:
    UFUNCTION(BlueprintCallable, Category = "Online")
    void SetMetadata(const FString &Key, const FVariantDataBP &Value);

    UFUNCTION(BlueprintCallable, Category = "Online")
    void SetMetadataByMap(const TMap<FString, FVariantDataBP> &Metadata);

    UFUNCTION(BlueprintCallable, Category = "Online")
    void DeleteMetadata(const FString &Key);

    UFUNCTION(BlueprintCallable, Category = "Online")
    void DeleteMetadataByArray(const TArray<FString> &MetadataKeys);

    static UOnlineLobbyMemberTransaction *FromNative(TSharedPtr<FOnlineLobbyMemberTransaction> InObj);
    TSharedPtr<FOnlineLobbyMemberTransaction> ToNative() const;
    bool IsValid() const;
};

UENUM(BlueprintType, Meta = (ScriptName = "EOnlineLobbySearchQueryFilterComparator"))
enum class EOnlineLobbySearchQueryFilterComparator_ : uint8
{
    Equal = 0,
    NotEqual,
    LessThan,
    LessThanOrEqual,
    GreaterThan,
    GreaterThanOrEqual,
};

USTRUCT(BlueprintType) struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineLobbySearchQueryFilterBP
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FVariantDataBP Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    EOnlineLobbySearchQueryFilterComparator_ Comparison = EOnlineLobbySearchQueryFilterComparator_::Equal;

    static FOnlineLobbySearchQueryFilterBP FromNative(const FOnlineLobbySearchQueryFilter &InObj);
    FOnlineLobbySearchQueryFilter ToNative() const;
};

USTRUCT(BlueprintType) struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineLobbySearchQueryBP
{
    GENERATED_BODY()

public:
    /** The search filters. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    TArray<FOnlineLobbySearchQueryFilterBP> Filters;

    /** The number of results to return, if HasLimit is true. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int64 Limit = 0;

    /** If false, an unlimited number of results will be returned. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool HasLimit = false;

    static FOnlineLobbySearchQueryBP FromNative(const FOnlineLobbySearchQuery &InObj);
    FOnlineLobbySearchQuery ToNative() const;
};
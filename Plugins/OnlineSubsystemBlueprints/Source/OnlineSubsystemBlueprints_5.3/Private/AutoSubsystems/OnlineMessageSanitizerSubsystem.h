// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Engine/GameInstance.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Types/OSBOnlineUserRef.h"
#include "Types/OSBFriendTypes.h"
#include "Types/OSBOnlineAccountCredential.h"
#include "Types/OSBOnlineErrorInfo.h"
#include "Types/OSBOnlineRecentPlayerRef.h"
#include "Types/OSBOnlineLoginStatus.h"
#include "Types/OSBBlockedQueryResultInfo.h"
#include "Types/OSBOnlineUserPrivilege.h"
#include "Types/OSBMessageTypes.h"
#include "Types/OSBChatTypes.h"
#include "Types/OSBExternalUITypes.h"
#include "Types/OSBFileTypes.h"
#include "Types/OSBPartyTypes.h"
#include "Types/OSBLobbyTypes.h"
#include "Types/OSBSessionTypes.h"
#include "Types/OSBLeaderboardTypes.h"
#include "Types/OSBStatsTypes.h"
#include "Types/OSBStoreV2Types.h"
#include "Types/OSBPurchaseTypes.h"
#include "Types/OSBEntitlementTypes.h"
#include "Types/OSBAchievementTypes.h"
#include "Types/OSBVoiceChatTypes.h"
#include "Types/OSBGameActivityTypes.h"
#include "Helpers/ArrayConversion.h"
#include "Helpers/UniqueNetIdConversion.h"
#include "Interfaces/IMessageSanitizerInterface.h"
#include "OnlineHelpers.h"

#include "OnlineMessageSanitizerSubsystem.generated.h"

UCLASS(BlueprintType)
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineMessageSanitizerSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    friend class UOnlineHelpers;

private:
    struct FWorldContext* WorldContext;
    TWeakPtr<class IMessageSanitizer, ESPMode::ThreadSafe> HandleWk;
    TSharedPtr<class IMessageSanitizer, ESPMode::ThreadSafe> GetHandle();
    bool IsHandleValid(const TSharedPtr<class IMessageSanitizer, ESPMode::ThreadSafe>& InHandle);

public:
    // When async functions use global events as callbacks (such as in identity and session),
    // we need to prevent multiple requests running at the same time where those results would
    // have the same identifying data in the callback (because then we don't know which result
    // belongs to which request). For these types of async functions, they use this set to make
    // sure that only one unique request runs at a time.
    TSet<FString> __InFlightRequests;

    static FName OSSNameToAssignDuringConstruction;
    FName OSSName = NAME_Default;
    UOnlineMessageSanitizerSubsystem();
    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "Online|MessageSanitizer")
    bool IsSubsystemAvailable();

    friend class UOnlineMessageSanitizerSubsystemSanitizeDisplayName;

    friend class UOnlineMessageSanitizerSubsystemSanitizeDisplayNames;

    friend class UOnlineMessageSanitizerSubsystemQueryBlockedUser;

    UFUNCTION(BlueprintCallable, Category = "Online|MessageSanitizer")
    void ResetBlockedUserCache();
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineMessageSanitizerSubsystemSanitizeDisplayNameCallbackPin, bool, bSuccess, FString, SanitizedMessage);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineMessageSanitizerSubsystemSanitizeDisplayName : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineMessageSanitizerSubsystemSanitizeDisplayNameCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineMessageSanitizerSubsystemSanitizeDisplayNameCallbackPin OnMessageProcessed;

    UFUNCTION(BlueprintCallable, Category = "Online|MessageSanitizer", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineMessageSanitizerSubsystemSanitizeDisplayName* SanitizeDisplayName(
        UOnlineMessageSanitizerSubsystem* Subsystem
        ,FString DisplayName
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineMessageSanitizerSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnMessageProcessed(bool bSuccess, const FString& SanitizedMessage);

    UPROPERTY()
    FString __Store__DisplayName;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnlineMessageSanitizerSubsystemSanitizeDisplayNamesCallbackPin, bool, bSuccess, const TArray<FString>&, SanitizedMessages);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineMessageSanitizerSubsystemSanitizeDisplayNames : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineMessageSanitizerSubsystemSanitizeDisplayNamesCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineMessageSanitizerSubsystemSanitizeDisplayNamesCallbackPin OnMessageArrayProcessed;

    UFUNCTION(BlueprintCallable, Category = "Online|MessageSanitizer", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineMessageSanitizerSubsystemSanitizeDisplayNames* SanitizeDisplayNames(
        UOnlineMessageSanitizerSubsystem* Subsystem
        ,TArray<FString> DisplayNames
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineMessageSanitizerSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnMessageArrayProcessed(bool bSuccess, const TArray<FString>& SanitizedMessages);

    UPROPERTY()
    TArray<FString> __Store__DisplayNames;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineMessageSanitizerSubsystemQueryBlockedUserCallbackPin, FBlockedQueryResultInfo, QueryResult);

UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineMessageSanitizerSubsystemQueryBlockedUser : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnlineMessageSanitizerSubsystemQueryBlockedUserCallbackPin OnCallFailed;
    UPROPERTY(BlueprintAssignable)
    FOnlineMessageSanitizerSubsystemQueryBlockedUserCallbackPin OnQueryUserBlockedResponse;

    UFUNCTION(BlueprintCallable, Category = "Online|MessageSanitizer", meta = (BlueprintInternalUseOnly = "true"))
    static UOnlineMessageSanitizerSubsystemQueryBlockedUser* QueryBlockedUser(
        UOnlineMessageSanitizerSubsystem* Subsystem
        ,int32 LocalUserNum, FString FromUserId, FString FromPlatform
    );

    virtual void Activate() override;

private:
    UPROPERTY()
    UOnlineMessageSanitizerSubsystem* __Store__Subsystem;
    UPROPERTY()
    FString __Store__CallUniquenessId;
    void HandleCallback_OnQueryUserBlockedResponse(const FBlockedQueryResult& QueryResult);

    UPROPERTY()
    int32 __Store__LocalUserNum;

UPROPERTY()
    FString __Store__FromUserId;

UPROPERTY()
    FString __Store__FromPlatform;
};
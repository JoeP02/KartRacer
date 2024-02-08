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
#include "Interfaces/OnlineChatInterface.h"

#include "OnlineChatSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FChat_ChatRoomCreated_BP, FUniqueNetIdRepl, Param1, FString, Param2, bool, Param3, FString, Param4);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FChat_ChatRoomConfigured_BP, FUniqueNetIdRepl, Param1, FString, Param2, bool, Param3, FString, Param4);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FChat_ChatRoomJoinPublic_BP, FUniqueNetIdRepl, Param1, FString, Param2, bool, Param3, FString, Param4);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FChat_ChatRoomJoinPrivate_BP, FUniqueNetIdRepl, Param1, FString, Param2, bool, Param3, FString, Param4);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FChat_ChatRoomExit_BP, FUniqueNetIdRepl, Param1, FString, Param2, bool, Param3, FString, Param4);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FChat_ChatRoomMemberJoin_BP, FUniqueNetIdRepl, Param1, FString, Param2, FUniqueNetIdRepl, Param3);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FChat_ChatRoomMemberExit_BP, FUniqueNetIdRepl, Param1, FString, Param2, FUniqueNetIdRepl, Param3);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FChat_ChatRoomMemberUpdate_BP, FUniqueNetIdRepl, Param1, FString, Param2, FUniqueNetIdRepl, Param3);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FChat_ChatRoomMessageReceived_BP, FUniqueNetIdRepl, Param1, FString, Param2, FChatMessageBP, Param3);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChat_ChatPrivateMessageReceived_BP, FUniqueNetIdRepl, Param1, FChatMessageBP, Param2);

UCLASS(BlueprintType)
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineChatSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    friend class UOnlineHelpers;

private:
    struct FWorldContext* WorldContext;
    TWeakPtr<class IOnlineChat, ESPMode::ThreadSafe> HandleWk;
    TSharedPtr<class IOnlineChat, ESPMode::ThreadSafe> GetHandle();
    bool IsHandleValid(const TSharedPtr<class IOnlineChat, ESPMode::ThreadSafe>& InHandle);
    FDelegateHandle DelegateHandle_OnChatRoomCreated;
    FDelegateHandle DelegateHandle_OnChatRoomConfigured;
    FDelegateHandle DelegateHandle_OnChatRoomJoinPublic;
    FDelegateHandle DelegateHandle_OnChatRoomJoinPrivate;
    FDelegateHandle DelegateHandle_OnChatRoomExit;
    FDelegateHandle DelegateHandle_OnChatRoomMemberJoin;
    FDelegateHandle DelegateHandle_OnChatRoomMemberExit;
    FDelegateHandle DelegateHandle_OnChatRoomMemberUpdate;
    FDelegateHandle DelegateHandle_OnChatRoomMessageReceived;
    FDelegateHandle DelegateHandle_OnChatPrivateMessageReceived;

public:
    // When async functions use global events as callbacks (such as in identity and session),
    // we need to prevent multiple requests running at the same time where those results would
    // have the same identifying data in the callback (because then we don't know which result
    // belongs to which request). For these types of async functions, they use this set to make
    // sure that only one unique request runs at a time.
    TSet<FString> __InFlightRequests;

    static FName OSSNameToAssignDuringConstruction;
    FName OSSName = NAME_Default;
    UOnlineChatSubsystem();
    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "Online|Chat")
    bool IsSubsystemAvailable();

    UPROPERTY(BlueprintAssignable, Category = "Online|Chat")
    FChat_ChatRoomCreated_BP OnChatRoomCreated;

    UPROPERTY(BlueprintAssignable, Category = "Online|Chat")
    FChat_ChatRoomConfigured_BP OnChatRoomConfigured;

    UPROPERTY(BlueprintAssignable, Category = "Online|Chat")
    FChat_ChatRoomJoinPublic_BP OnChatRoomJoinPublic;

    UPROPERTY(BlueprintAssignable, Category = "Online|Chat")
    FChat_ChatRoomJoinPrivate_BP OnChatRoomJoinPrivate;

    UPROPERTY(BlueprintAssignable, Category = "Online|Chat")
    FChat_ChatRoomExit_BP OnChatRoomExit;

    UPROPERTY(BlueprintAssignable, Category = "Online|Chat")
    FChat_ChatRoomMemberJoin_BP OnChatRoomMemberJoin;

    UPROPERTY(BlueprintAssignable, Category = "Online|Chat")
    FChat_ChatRoomMemberExit_BP OnChatRoomMemberExit;

    UPROPERTY(BlueprintAssignable, Category = "Online|Chat")
    FChat_ChatRoomMemberUpdate_BP OnChatRoomMemberUpdate;

    UPROPERTY(BlueprintAssignable, Category = "Online|Chat")
    FChat_ChatRoomMessageReceived_BP OnChatRoomMessageReceived;

    UPROPERTY(BlueprintAssignable, Category = "Online|Chat")
    FChat_ChatPrivateMessageReceived_BP OnChatPrivateMessageReceived;

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    bool CreateRoom(FUniqueNetIdRepl UserId, FString RoomId, FString Nickname, FChatRoomConfigBP ChatRoomConfig);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    bool ConfigureRoom(FUniqueNetIdRepl UserId, FString RoomId, FChatRoomConfigBP ChatRoomConfig);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    bool JoinPublicRoom(FUniqueNetIdRepl UserId, FString RoomId, FString Nickname, FChatRoomConfigBP ChatRoomConfig);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    bool JoinPrivateRoom(FUniqueNetIdRepl UserId, FString RoomId, FString Nickname, FChatRoomConfigBP ChatRoomConfig);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    bool ExitRoom(FUniqueNetIdRepl UserId, FString RoomId);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    bool SendRoomChat(FUniqueNetIdRepl UserId, FString RoomId, FString MsgBody);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    bool SendPrivateChat(FUniqueNetIdRepl UserId, FUniqueNetIdRepl RecipientId, FString MsgBody);

    UFUNCTION(BlueprintPure, Category = "Online|Chat")
    bool IsChatAllowed(FUniqueNetIdRepl UserId, FUniqueNetIdRepl RecipientId);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    void GetJoinedRooms(FUniqueNetIdRepl UserId, TArray<FString>& OutRooms);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    FChatRoomInfoBP GetRoomInfo(FUniqueNetIdRepl UserId, FString RoomId);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    bool GetMembers(FUniqueNetIdRepl UserId, FString RoomId, TArray<FChatRoomMemberBP>& OutMembers);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    FChatRoomMemberBP GetMember(FUniqueNetIdRepl UserId, FString RoomId, FUniqueNetIdRepl MemberId);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    bool GetLastMessages(FUniqueNetIdRepl UserId, FString RoomId, int32 NumMessages, TArray<FChatMessageBP>& OutMessages);

    // @generator-incompatible
    // bool IsMessageFromLocalUser(const FUniqueNetId& UserId, const FChatMessage& Message, const bool bIncludeExternalInstances);

    UFUNCTION(BlueprintCallable, Category = "Online|Chat")
    void DumpChatState();
};
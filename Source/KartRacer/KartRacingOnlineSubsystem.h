// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "KartRacingOnlineSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnKartLoginCompleted, int32, LocalUserNum, bool, bWasSuccessful, const FString&, Error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKartStartCreateSession);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKartCreateSessionComplete, FName, SessionName, bool, bWasSuccessful);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKartStartFindSession);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKartFindSessionsComplete, bool, bWasSuccessful, int, NumberOfSessions);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKartJoinSessionComplete, FName, SessionName);

UCLASS()
class KARTRACER_API UKartRacingOnlineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable) void PortalLogin();
	UFUNCTION(BlueprintCallable) void PersistantLogin();
	UFUNCTION(BlueprintCallable) void Logout();
	UFUNCTION(BlueprintCallable, BlueprintPure) FString GetPlayerUsername();

	UFUNCTION(BlueprintCallable) void CreateOnlineSession(int MaxNumOfPlayers, bool bLAN);

	UFUNCTION(BlueprintCallable) void FindOnlineSession();

	UFUNCTION(BlueprintCallable) void LeaveSession();
	
	void JoinSession(FOnlineSessionSearchResult& SessionToJoin);

	UPROPERTY(BlueprintAssignable, Category="Kart Online System Delegates") FOnKartLoginCompleted OnKartLoginCompleted;
	UPROPERTY(BlueprintAssignable, Category="Kart Online System Delegates") FOnKartStartCreateSession OnKartStartCreateSession;
	UPROPERTY(BlueprintAssignable, Category="Kart Online System Delegates") FOnKartCreateSessionComplete OnKartCreateSessionComplete;
	UPROPERTY(BlueprintAssignable, Category="Kart Online System Delegates") FOnKartStartFindSession OnKartStartFindSession;
	UPROPERTY(BlueprintAssignable, Category="Kart Online System Delegates") FOnKartFindSessionsComplete OnKartFindSessionsComplete;
	UPROPERTY(BlueprintAssignable, Category="Kart Online System Delegates") FOnKartJoinSessionComplete OnKartJoinSessionComplete;

	TSharedPtr<FOnlineSessionSearch> SearchSettings;

protected:

private:
	IOnlineSubsystem* OnlineSubsystem;
	IOnlineIdentityPtr Identity;
	IOnlineSessionPtr SessionsPtr;

	void OnPortalLoginCompletes(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	void OnPersistantLoginCompletes(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	void OnLogoutCompletes(int32 LocalUserNum, bool bWasSuccessful);
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnLeaveSessionComplete(FName SessionName, bool bWasSuccessful);
	
};

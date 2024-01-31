// Fill out your copyright notice in the Description page of Project Settings.


#include "KartRacingOnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

#include "Kismet/KismetSystemLibrary.h"

const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName");

void UKartRacingOnlineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UWorld* World = GetWorld();
	if (World)
	{
		OnlineSubsystem = Online::GetSubsystem(World);
		Identity = OnlineSubsystem->GetIdentityInterface();
		SessionsPtr = OnlineSubsystem->GetSessionInterface();
	}
}

void UKartRacingOnlineSubsystem::Login()
{
	Identity->OnLoginCompleteDelegates->AddUObject(this, &UKartRacingOnlineSubsystem::OnLoginCompletes);
	
	FOnlineAccountCredentials AccountCredentials;
	AccountCredentials.Type = "AccountPortal";
	AccountCredentials.Id = " ";
	AccountCredentials.Token = " ";
	
	Identity->Login(0, AccountCredentials);
}

FString UKartRacingOnlineSubsystem::GetPlayerUsername()
{
	return Identity->GetPlayerNickname(0);
}

void UKartRacingOnlineSubsystem::CreateOnlineSession()
{
	OnKartStartCreateSession.Broadcast();
	
	FOnlineSessionSettings SessionSettings;
	SessionSettings.NumPublicConnections = 12;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bAllowJoinViaPresence = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bAllowInvites = true;
	SessionSettings.Set(SERVER_NAME_SETTINGS_KEY, GetPlayerUsername(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	SessionSettings.Set(SEARCH_KEYWORDS, FString("KrazyKartsLobby"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	SessionsPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UKartRacingOnlineSubsystem::OnCreateSessionComplete);
	
	SessionsPtr->CreateSession(0, FName(*GetPlayerUsername()), SessionSettings);
}

void UKartRacingOnlineSubsystem::OnLoginCompletes(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
                                                  const FString& Error)
{
	if (bWasSuccessful)
	{
		FString Username = Identity->GetPlayerNickname(UserId);
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, "Logged In: " + Username);
	}

	OnKartLoginCompleted.Broadcast(LocalUserNum, bWasSuccessful, Error);
	
	Identity->ClearOnLoginCompleteDelegates(LocalUserNum, this);
}

void UKartRacingOnlineSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, "Created Session: " + SessionName.ToString());
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "KartRacingOnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "GenericPlatform/GenericPlatformDriver.h"

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

void UKartRacingOnlineSubsystem::PortalLogin()
{
	Identity->OnLoginCompleteDelegates->AddUObject(this, &UKartRacingOnlineSubsystem::OnPortalLoginCompletes);
	
	FOnlineAccountCredentials AccountCredentials;
	AccountCredentials.Type = "AccountPortal";
	AccountCredentials.Id = " ";
	AccountCredentials.Token = " ";
	
	Identity->Login(0, AccountCredentials);
}

void UKartRacingOnlineSubsystem::PersistantLogin()
{
	Identity->OnLoginCompleteDelegates->AddUObject(this, &UKartRacingOnlineSubsystem::OnPersistantLoginCompletes);
	
	FOnlineAccountCredentials AccountCredentials;
	AccountCredentials.Type = "persistentauth";
	AccountCredentials.Id = " ";
	AccountCredentials.Token = " ";
	
	Identity->Login(0, AccountCredentials);
}

void UKartRacingOnlineSubsystem::Logout()
{
	Identity->OnLogoutCompleteDelegates->AddUObject(this, &UKartRacingOnlineSubsystem::OnLogoutCompletes);
	Identity->Logout(0);
}

FString UKartRacingOnlineSubsystem::GetPlayerUsername()
{
	return Identity->GetPlayerNickname(0);
}

void UKartRacingOnlineSubsystem::CreateOnlineSession(int MaxNumOfPlayers, bool bLAN)
{
	OnKartStartCreateSession.Broadcast();
	
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = bLAN;
	SessionSettings.NumPublicConnections = MaxNumOfPlayers;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bAllowJoinViaPresence = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bAllowInvites = true;
	//SessionSettings.Set(SERVER_NAME_SETTINGS_KEY, NAME_GameSession, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	SessionSettings.Set(SEARCH_KEYWORDS, FString("KrazyKartsLobby"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	//SessionSettings.Settings.Add(SEARCH_KEYWORDS, FString("KrazyKartsLobby"));

	SessionsPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UKartRacingOnlineSubsystem::OnCreateSessionComplete);
	
	SessionsPtr->CreateSession(0, FName(*GetPlayerUsername()), SessionSettings);
}

void UKartRacingOnlineSubsystem::FindOnlineSession()
{
	OnKartStartFindSession.Broadcast();

	SessionsPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UKartRacingOnlineSubsystem::OnFindSessionsComplete);

	SearchSettings = MakeShareable(new FOnlineSessionSearch());
	if (SearchSettings)
	{
		SearchSettings->MaxSearchResults = 100;
		SearchSettings->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, FString("KrazyKartsLobby"), EOnlineComparisonOp::Equals);
		SearchSettings->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);

		SessionsPtr->FindSessions(0, SearchSettings.ToSharedRef());
	}
}

void UKartRacingOnlineSubsystem::LeaveSession()
{
	SessionsPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UKartRacingOnlineSubsystem::OnLeaveSessionComplete);
	SessionsPtr->DestroySession(NAME_GameSession);
}

void UKartRacingOnlineSubsystem::JoinSession(FOnlineSessionSearchResult& SessionToJoin)
{
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Cyan, TEXT("Join Session Called"));

	SessionsPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UKartRacingOnlineSubsystem::OnJoinSessionComplete);
	
	SessionsPtr->JoinSession(0, NAME_GameSession, SessionToJoin);
}

void UKartRacingOnlineSubsystem::OnPortalLoginCompletes(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
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

void UKartRacingOnlineSubsystem::OnPersistantLoginCompletes(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
												  const FString& Error)
{
	if (!bWasSuccessful)
	{
		PortalLogin();
	}
	else
	{
		OnKartLoginCompleted.Broadcast(LocalUserNum, bWasSuccessful, Error);
	
		Identity->ClearOnLoginCompleteDelegates(LocalUserNum, this);
	}
}

void UKartRacingOnlineSubsystem::OnLogoutCompletes(int32 LocalUserNum, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		GetWorld()->GetFirstPlayerController()->ClientTravel("/Game/Maps/GameInit", TRAVEL_Absolute);
	}
}


void UKartRacingOnlineSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, "Created Session: " + SessionName.ToString());
	}

	OnKartCreateSessionComplete.Broadcast(SessionName, bWasSuccessful);

	SessionsPtr->ClearOnCreateSessionCompleteDelegates(this);
}

void UKartRacingOnlineSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, "Found Sessions");
	}

	OnKartFindSessionsComplete.Broadcast(bWasSuccessful);

	SessionsPtr->ClearOnFindSessionsCompleteDelegates(this);
}

void UKartRacingOnlineSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	FString Address;
	if(!SessionsPtr->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could Not Get Connect String"));
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UKartRacingOnlineSubsystem::OnLeaveSessionComplete(FName SessionName, bool bWasSuccessful)
{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Cyan, "Left Session");
	
		GetWorld()->GetFirstPlayerController()->ClientTravel("/Game/Maps/MainMenu", TRAVEL_Absolute);
}

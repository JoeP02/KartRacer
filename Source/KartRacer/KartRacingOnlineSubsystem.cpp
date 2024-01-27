// Fill out your copyright notice in the Description page of Project Settings.


#include "KartRacingOnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

#include "Kismet/KismetSystemLibrary.h"

void UKartRacingOnlineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UWorld* World = GetWorld();
	if (World)
	{
		OnlineSubsystem = Online::GetSubsystem(World);
		Identity = OnlineSubsystem->GetIdentityInterface();
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

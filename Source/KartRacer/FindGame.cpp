// Fill out your copyright notice in the Description page of Project Settings.


#include "FindGame.h"

#include "KartRacingOnlineSubsystem.h"

void UFindGame::RefreshServerList()
{
	UGameInstance* GameInstance = GetGameInstance();
	UKartRacingOnlineSubsystem* KartRacingOnlineSubsystem = GameInstance->GetSubsystem<UKartRacingOnlineSubsystem>();

	for (FOnlineSessionSearchResult SearchResult : KartRacingOnlineSubsystem->SearchSettings->SearchResults)
	{
		
	}
}

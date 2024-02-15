// Fill out your copyright notice in the Description page of Project Settings.


#include "FindGame.h"

#include "FindGame_Item.h"
#include "KartRacingOnlineSubsystem.h"

UFindGame::UFindGame(const FObjectInitializer& Object):Super(Object)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/Widgets/MainMenu/WBP_FindGame_Item"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;

	ServerRowClass = ServerRowBPClass.Class;
}

void UFindGame::RefreshServerList()
{
	UGameInstance* GameInstance = GetGameInstance();
	UKartRacingOnlineSubsystem* KartRacingOnlineSubsystem = GameInstance->GetSubsystem<UKartRacingOnlineSubsystem>();

	for (FOnlineSessionSearchResult SearchResult : KartRacingOnlineSubsystem->SearchSettings->SearchResults)
	{
		UFindGame_Item* SessionItem = CreateWidget<UFindGame_Item>(this, ServerRowClass);
		SessionItem->SessionData = SearchResult;

		SessionScrollBox->AddChild(SessionItem);
	}
}



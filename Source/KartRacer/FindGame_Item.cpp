// Fill out your copyright notice in the Description page of Project Settings.


#include "FindGame_Item.h"

#include "KartRacingOnlineSubsystem.h"

void UFindGame_Item::JoinServer()
{
	UGameInstance* GameInstance = GetGameInstance();
	UKartRacingOnlineSubsystem* KartRacingOnlineSubsystem = GameInstance->GetSubsystem<UKartRacingOnlineSubsystem>();

	KartRacingOnlineSubsystem->JoinSession(SessionData);
}

void UFindGame_Item::NativeConstruct()
{
	Super::NativeConstruct();

	SessionNameText->SetText(FText::FromString(SessionData.Session.OwningUserName));
	PlayerCountText->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), 12 - SessionData.Session.NumOpenPublicConnections, 12)));
	PingText->SetText(FText::FromString(FString::Printf(TEXT("%dms"), SessionData.PingInMs)));
}

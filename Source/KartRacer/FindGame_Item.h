// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "OnlineSessionSettings.h"
#include "FindGame_Item.generated.h"

/**
 * 
 */
UCLASS()
class KARTRACER_API UFindGame_Item : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget)) UTextBlock* SessionNameText;
	UPROPERTY(meta=(BindWidget)) UTextBlock* PlayerCountText;
	UPROPERTY(meta=(BindWidget)) UTextBlock* PingText;

	FOnlineSessionSearchResult SessionData;

	UFUNCTION(BlueprintCallable) void JoinServer();

	virtual void NativeConstruct() override;
	
};

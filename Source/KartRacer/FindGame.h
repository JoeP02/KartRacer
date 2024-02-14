// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "FindGame.generated.h"

/**
 * 
 */
UCLASS()
class KARTRACER_API UFindGame : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget)) UScrollBox* SessionScrollBox;

	UFUNCTION() void RefreshServerList();
};

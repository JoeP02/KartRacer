// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSubsystem.h"
#include "KartRacingOnlineSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnKartLoginCompleted, int32, LocalUserNum, bool, bWasSuccessful, const FString&, Error);

UCLASS()
class KARTRACER_API UKartRacingOnlineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable) void Login();
	UFUNCTION(BlueprintCallable, BlueprintPure) FString GetPlayerUsername();

	UPROPERTY(BlueprintAssignable, Category="Kart Online System Delegates") FOnKartLoginCompleted OnKartLoginCompleted;

protected:

private:
	IOnlineSubsystem* OnlineSubsystem;
	IOnlineIdentityPtr Identity;

	void OnLoginCompletes(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
};

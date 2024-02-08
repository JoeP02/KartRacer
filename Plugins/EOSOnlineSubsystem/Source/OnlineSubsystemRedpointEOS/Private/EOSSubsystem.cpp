// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Public/EOSSubsystem.h"

#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "Engine/GameInstance.h"

UEOSSubsystem *UEOSSubsystem::GetSubsystem(UWorld *InWorld)
{
    if (IsValid(InWorld))
    {
        UGameInstance *GameInstance = InWorld->GetGameInstance();
        if (IsValid(GameInstance))
        {
            UEOSSubsystem *GlobalSubsystem = GameInstance->GetSubsystem<UEOSSubsystem>();
            if (IsValid(GlobalSubsystem))
            {
                return GlobalSubsystem;
            }
            else
            {
                UE_LOG(
                    LogRedpointEOS,
                    Warning,
                    TEXT("UEOSSubsystem::GetSubsystem: Game instance does not have UEOSSubsystem."));
                return nullptr;
            }
        }
        else
        {
            UE_LOG(LogRedpointEOS, Warning, TEXT("UEOSSubsystem::GetSubsystem: Game instance is not valid."));
            return nullptr;
        }
    }
    else
    {
        UE_LOG(LogRedpointEOS, Warning, TEXT("UEOSSubsystem::GetSubsystem: Current world is not valid."));
        return nullptr;
    }
}
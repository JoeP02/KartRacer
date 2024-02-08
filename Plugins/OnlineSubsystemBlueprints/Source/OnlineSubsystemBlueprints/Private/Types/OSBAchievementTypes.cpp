// Copyright June Rhodes 2023. All Rights Reserved.

#include "Types/OSBAchievementTypes.h"

FOnlineAchievementBP FOnlineAchievementBP::FromNative(FOnlineAchievement Achievement)
{
    FOnlineAchievementBP Result;
    Result.Id = Achievement.Id;
    Result.Progress = Achievement.Progress;
    return Result;
}

FOnlineAchievementDescBP FOnlineAchievementDescBP::FromNative(FOnlineAchievementDesc AchievementDescription)
{
    FOnlineAchievementDescBP Result;
    Result.Title = AchievementDescription.Title;
    Result.LockedDesc = AchievementDescription.LockedDesc;
    Result.UnlockedDesc = AchievementDescription.UnlockedDesc;
    Result.bIsHidden = AchievementDescription.bIsHidden;
    Result.UnlockTime = AchievementDescription.UnlockTime;
    return Result;
}

void UOnlineAchievementsWrite::SetAchievementProgress(FName AchievementId, float AchievementProgress)
{
    this->AchievementsWrite->SetFloatStat(AchievementId, AchievementProgress);
}

FOnlineAchievementsWriteRef &UOnlineAchievementsWrite::GetAchievementsWrite()
{
    return this->AchievementsWrite;
}
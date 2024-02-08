// Copyright June Rhodes 2024. All Rights Reserved.

#include "HAL/MemoryMisc.h"
#include "Misc/AutomationTest.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineAchievementsInterfaceEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineSubsystemRedpointEOS.h"
#include "RedpointEOSTestsModule.h"
#include "TestHelpers.h"
#include "Tests/AutomationCommon.h"

IMPLEMENT_ASYNC_AUTOMATION_TEST(
    FOnlineSubsystemEOS_OnlineAchievementsInterface_CanUnlockAchievements,
    "OnlineSubsystemEOS.OnlineAchievementsInterface.CanUnlockAchievements",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

void FOnlineSubsystemEOS_OnlineAchievementsInterface_CanUnlockAchievements::RunAsyncTest(
    const std::function<void()> &OnDone)
{
    CreateSingleSubsystemForTest_CreateOnDemand(
        this,
        OnDone,
        [this](
            const IOnlineSubsystemPtr &Subsystem,
            const TSharedPtr<const FUniqueNetIdEOS> &UserId,
            const FOnDone &OnDone) {
            if (!(Subsystem.IsValid() && UserId.IsValid()))
            {
                this->AddError(FString::Printf(TEXT("Unable to init subsystem / authenticate")));
                OnDone();
                return;
            }

            auto Achievements = Subsystem->GetAchievementsInterface();
            TestTrue("Online subsystem provides IOnlineAchievements interface", Achievements.IsValid());

            if (!Achievements.IsValid())
            {
                OnDone();
                return;
            }

            auto AchievementsWrite = MakeShared<FOnlineAchievementsWrite, ESPMode::ThreadSafe>();
            AchievementsWrite->Properties.Add(TEXT("TestAchievement"), 1.0f);

            Achievements->WriteAchievements(
                *UserId,
                AchievementsWrite,
                FOnAchievementsWrittenDelegate::CreateLambda(
                    // NOLINTNEXTLINE(unreal-unsafe-storage-of-oss-pointer)
                    [this, OnDone](const FUniqueNetId &UserId, const bool bWasSuccessful) {
                        TestTrue("WriteAchievements was successful", bWasSuccessful);
                        OnDone();
                    }));
        });
}
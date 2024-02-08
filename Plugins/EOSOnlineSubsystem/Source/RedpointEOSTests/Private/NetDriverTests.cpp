// Copyright June Rhodes 2024. All Rights Reserved.

#include "HAL/MemoryMisc.h"
#include "Misc/AutomationTest.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSNetDriver.h"
#include "TestHelpers.h"
#include "Tests/AutomationCommon.h"
#include "UObject/Class.h"

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(
    FOnlineSubsystemEOS_NetDriver_CanLoadCustomConfig,
    FHotReloadableAutomationTestBase,
    "OnlineSubsystemEOS.NetDriver.CanLoadCustomConfig",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

bool FOnlineSubsystemEOS_NetDriver_CanLoadCustomConfig::RunTest(const FString &Parameters)
{
    // Only run this test on CI/CD, where we know we've set up the project correctly.
    bool ShouldTestConfig = !FPlatformMisc::GetEnvironmentVariable(TEXT("CI_JOB_JWT_V1")).IsEmpty();
    if (ShouldTestConfig)
    {
        UEOSNetDriver *CDO = UEOSNetDriver::StaticClass()->GetDefaultObject<UEOSNetDriver>();
        if (this->TestEqual("Net driver has overridden MaxNetTickRate", CDO->MaxNetTickRate, 240))
        {
            this->AddInfo(
                TEXT("Net driver successfully had settings overridden by DefaultOnlineSubsystemRedpointEOS.ini"));
        }
        else
        {
            this->AddWarning(
                TEXT("Net driver DID NOT have settings overridden by DefaultOnlineSubsystemRedpointEOS.ini"));
        }
    }
    else
    {
        this->AddWarning(TEXT("Net driver test IS NOT RUNNING because this test is not running on CI/CD"));
    }
    return true;
}
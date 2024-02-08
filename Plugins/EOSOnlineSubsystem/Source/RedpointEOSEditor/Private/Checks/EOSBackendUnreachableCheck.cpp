// Copyright June Rhodes 2024. All Rights Reserved.

#include "EOSBackendUnreachableCheck.h"

const TArray<FEOSCheckEntry> FEOSBackendUnreachableCheck::ProcessLogMessage(
    EOS_ELogLevel InLogLevel,
    const FString &Category,
    const FString &Message) const
{
    if (Message.Contains("Lockout of") || Message.Contains("api.epicgames.dev"))
    {
        return TArray<FEOSCheckEntry>{FEOSCheckEntry(
            "FEOSBackendUnreachableCheck::LockoutDetected",
            "The EOS SDK is unable to reach the EOS backend. Either the EOS backend is down, you're having Internet connectivity issues, or you're being throttled by the EOS backend for making too many requests. Expect SDK calls to be slow or to fail completely. If you continue to this problem, please open a ticket on the EOS Help Portal.",
            TArray<FEOSCheckAction>{
                FEOSCheckAction("FEOSBackendUnreachableCheck::LockoutDetected", "Open EOS Help Portal")})};
    }
    return IEOSCheck::EmptyEntries;
}

void FEOSBackendUnreachableCheck::HandleAction(const FString &CheckId, const FString &ActionId) const
{
    if (CheckId == "FEOSBackendUnreachableCheck::Misconfigured")
    {
        if (ActionId == "FEOSBackendUnreachableCheck::LockoutDetected")
        {
            FPlatformProcess::LaunchURL(
                TEXT("https://eoshelp.epicgames.com/"),
                nullptr,
                nullptr);
        }
    }
}
// Copyright June Rhodes 2024. All Rights Reserved.

#include "./AntiCheatIntegrityPhase.h"

#include "OnlineSubsystemRedpointEOS/Private/EOSControlChannel.h"

void FAntiCheatIntegrityPhase::RegisterRoutes(UEOSControlChannel *ControlChannel)
{
}

void FAntiCheatIntegrityPhase::Start(const TSharedRef<FAuthLoginPhaseContext> &Context)
{
    UNetConnection *Connection;
    if (!Context->GetConnection(Connection))
    {
        Context->Finish(EAuthPhaseFailureCode::All_ConnectionHasGoneAway);
        return;
    }

    EUserVerificationStatus VerificationStatus = EUserVerificationStatus::NotStarted;
    if (Context->GetVerificationStatus(VerificationStatus) && VerificationStatus == EUserVerificationStatus::Verified)
    {
        // This client is a trusted client that is bypassing Anti-Cheat integrity. Skip
        // waiting for verification.
        Context->Finish(EAuthPhaseFailureCode::Success);
        return;
    }

    checkf(
        Connection->PlayerId.IsValid(),
        TEXT("Connection player ID must have been set by verification phase before Anti-Cheat phases can begin."));

    // NOTE: If this is a reconnection by the same player, where we skipped the registration
    // in AntiCheatProofPhase because of their existing registration, then we won't receive
    // the event and we need to proceed immediately.

    if (bIsVerified)
    {
        Context->Finish(EAuthPhaseFailureCode::Success);
    }
    else
    {
        bIsStarted = true;
    }
}

void FAntiCheatIntegrityPhase::OnAntiCheatPlayerAuthStatusChanged(
    const TSharedRef<FAuthLoginPhaseContext> &Context,
    EOS_EAntiCheatCommonClientAuthStatus NewAuthStatus)
{
    FString StatusStr = TEXT("Unknown");
    if (NewAuthStatus == EOS_EAntiCheatCommonClientAuthStatus::EOS_ACCCAS_Invalid)
    {
        StatusStr = TEXT("Invalid");
    }
    else if (NewAuthStatus == EOS_EAntiCheatCommonClientAuthStatus::EOS_ACCCAS_LocalAuthComplete)
    {
        StatusStr = TEXT("LocalAuthComplete");
    }
    else if (NewAuthStatus == EOS_EAntiCheatCommonClientAuthStatus::EOS_ACCCAS_RemoteAuthComplete)
    {
        StatusStr = TEXT("RemoteAuthComplete");
    }

    UE_LOG(
        LogRedpointEOSNetworkAuth,
        Verbose,
        TEXT("Server authentication: %s: Anti-Cheat verification status is now '%s'."),
        *Context->GetUserId()->ToString(),
        *StatusStr);

    if (NewAuthStatus == EOS_EAntiCheatCommonClientAuthStatus::EOS_ACCCAS_RemoteAuthComplete)
    {
        if (bIsStarted)
        {
            Context->Finish(EAuthPhaseFailureCode::Success);
        }
        else
        {
            bIsVerified = true;
        }
    }
}

void FAntiCheatIntegrityPhase::OnAntiCheatPlayerActionRequired(
    const TSharedRef<FAuthLoginPhaseContext> &Context,
    EOS_EAntiCheatCommonClientAction ClientAction,
    EOS_EAntiCheatCommonClientActionReason ActionReasonCode,
    const FString &ActionReasonDetailsString)
{
    FString DetailsString = FString::Printf(
        TEXT("Disconnected from server due to Anti-Cheat error. Reason: '%s'. Details: '%s'."),
        *EOS_EAntiCheatCommonClientActionReason_ToString(ActionReasonCode),
        *ActionReasonDetailsString);
    Context->Finish(EAuthPhaseFailureCode::Phase_AntiCheatIntegrity_KickedDueToEACFailure);
}
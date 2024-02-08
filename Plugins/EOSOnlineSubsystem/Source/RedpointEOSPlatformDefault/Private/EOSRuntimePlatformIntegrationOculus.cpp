// Copyright June Rhodes 2024. All Rights Reserved.

#include "EOSRuntimePlatformIntegrationOculus.h"

#if EOS_OCULUS_ENABLED

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemUtils.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

TSharedPtr<const class FUniqueNetId> FEOSRuntimePlatformIntegrationOculus::GetUserId(
    TSoftObjectPtr<class UWorld> InWorld,
    EOS_Connect_ExternalAccountInfo *InExternalInfo)
{
    if (!InWorld.IsValid() || InExternalInfo == nullptr)
    {
        return nullptr;
    }

    if (InExternalInfo->AccountIdType != EOS_EExternalAccountType::EOS_EAT_OCULUS)
    {
        return nullptr;
    }

    IOnlineSubsystem *OSS = Online::GetSubsystem(InWorld.Get(), OCULUS_SUBSYSTEM);
    if (OSS != nullptr)
    {
        IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
        if (Identity.IsValid())
        {
            FString OculusId = EOSString_Connect_ExternalAccountId::FromAnsiString(InExternalInfo->AccountId);
            return Identity->CreateUniquePlayerId(OculusId);
        }
    }

    return nullptr;
}

bool FEOSRuntimePlatformIntegrationOculus::CanProvideExternalAccountId(const FUniqueNetId &InUserId)
{
    return InUserId.GetType().IsEqual(OCULUS_SUBSYSTEM);
}

Redpoint::EOS::Core::FExternalAccountIdInfo FEOSRuntimePlatformIntegrationOculus::GetExternalAccountId(
    const FUniqueNetId &InUserId)
{
    if (!InUserId.GetType().IsEqual(OCULUS_SUBSYSTEM))
    {
        return Redpoint::EOS::Core::FExternalAccountIdInfo();
    }

    Redpoint::EOS::Core::FExternalAccountIdInfo Info;
    Info.AccountIdType = EOS_EExternalAccountType::EOS_EAT_OCULUS;
    Info.AccountId = InUserId.ToString();
    return Info;
}

void FEOSRuntimePlatformIntegrationOculus::MutateFriendsListNameIfRequired(
    FName InSubsystemName,
    FString &InOutListName) const
{
    if (InSubsystemName.IsEqual(OCULUS_SUBSYSTEM))
    {
        InOutListName = TEXT("default");
    }
}

PRAGMA_ENABLE_DEPRECATION_WARNINGS

#endif
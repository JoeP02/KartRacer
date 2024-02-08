// Copyright June Rhodes 2024. All Rights Reserved.

#include "EOSRuntimePlatformIntegrationItchIo.h"

#if EOS_ITCH_IO_ENABLED

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointItchIo/Public/OnlineSubsystemRedpointItchIoConstants.h"
#include "OnlineSubsystemUtils.h"

TSharedPtr<const class FUniqueNetId> FEOSRuntimePlatformIntegrationItchIo::GetUserId(
    TSoftObjectPtr<class UWorld> InWorld,
    EOS_Connect_ExternalAccountInfo *InExternalInfo)
{
    if (!InWorld.IsValid() || InExternalInfo == nullptr)
    {
        return nullptr;
    }

    if (InExternalInfo->AccountIdType != EOS_EExternalAccountType::EOS_EAT_ITCHIO)
    {
        return nullptr;
    }

    IOnlineSubsystem *OSS = Online::GetSubsystem(InWorld.Get(), REDPOINT_ITCH_IO_SUBSYSTEM);
    if (OSS != nullptr)
    {
        IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
        if (Identity.IsValid())
        {
            FString ItchId = EOSString_Connect_ExternalAccountId::FromAnsiString(InExternalInfo->AccountId);
            return Identity->CreateUniquePlayerId(ItchId);
        }
    }

    return nullptr;
}

bool FEOSRuntimePlatformIntegrationItchIo::CanProvideExternalAccountId(const FUniqueNetId &InUserId)
{
    return InUserId.GetType().IsEqual(REDPOINT_ITCH_IO_SUBSYSTEM);
}

Redpoint::EOS::Core::FExternalAccountIdInfo FEOSRuntimePlatformIntegrationItchIo::GetExternalAccountId(
    const FUniqueNetId &InUserId)
{
    if (!InUserId.GetType().IsEqual(REDPOINT_ITCH_IO_SUBSYSTEM))
    {
        return Redpoint::EOS::Core::FExternalAccountIdInfo();
    }

    Redpoint::EOS::Core::FExternalAccountIdInfo Info;
    Info.AccountIdType = EOS_EExternalAccountType::EOS_EAT_ITCHIO;
    Info.AccountId = InUserId.ToString();
    return Info;
}

#endif
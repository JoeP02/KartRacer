// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "HAL/IConsoleManager.h"
#include "Misc/DateTime.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"

#if !(defined(UE_BUILD_SHIPPING) && UE_BUILD_SHIPPING)
extern TAutoConsoleVariable<bool> CVarEOSEnablePacketTiming;
#endif

struct FEOSPacketTiming
{
    FEOSPacketTiming(
        const EOS_ProductUserId &InSourceUserId,
        const EOS_ProductUserId &InDestinationUserId,
        const EOS_P2P_SocketId &InSymmetricSocketId,
        uint8_t InSymmetricChannel,
        int64 SentTicks,
        const FDateTime &ReceivedAt,
        int32 InSize)
        : bHasTimingData(true)
        , SourceUserId()
        , DestinationUserId()
        , SymmetricSocketId(EOSString_P2P_SocketName::FromAnsiString(InSymmetricSocketId.SocketName))
        , SymmetricChannel(InSymmetricChannel)
        , Sent(FDateTime(SentTicks))
        , ReceivedIntoQueue(ReceivedAt)
        , PulledFromQueue(FDateTime::MinValue())
        , Size(InSize)
    {
        EOSString_ProductUserId::ToString(InSourceUserId, this->SourceUserId);
        EOSString_ProductUserId::ToString(InDestinationUserId, this->DestinationUserId);
    };
    UE_NONCOPYABLE(FEOSPacketTiming);
    ~FEOSPacketTiming() = default;

    bool bHasTimingData;

    FString SourceUserId;

    FString DestinationUserId;

    FString SymmetricSocketId;

    uint8 SymmetricChannel;

    FDateTime Sent;

    FDateTime ReceivedIntoQueue;

    FDateTime PulledFromQueue;

    int32 Size;
};

void RecordPacketTiming(const TSharedPtr<FEOSPacketTiming> &InPacketTiming);
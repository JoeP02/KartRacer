// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "./VoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

#if EOS_HAS_AUTHENTICATION && !EOS_VERSION_AT_LEAST(1, 16, 0)

class FUpdateSendingVoiceTaskData
{
public:
    struct FRoomNameWithTransmitStatus
    {
        FString RoomName;
        bool bIsTransmitting;
    };
    EOS_HRTCAudio EOSRTCAudio;
    EOS_ProductUserId LocalUserId;
    bool bUserInputMuted;
    TArray<FRoomNameWithTransmitStatus> RoomNamesWithTransmitStatus;
};

class FUpdateSendingVoiceTask : public FVoiceTask
{
private:
    FUpdateSendingVoiceTaskData Data;

public:
    FUpdateSendingVoiceTask(FUpdateSendingVoiceTaskData InData)
        : Data(MoveTemp(InData)){};
    UE_NONCOPYABLE(FUpdateSendingVoiceTask);
    virtual ~FUpdateSendingVoiceTask() = default;

    virtual FString GetLogName() override
    {
        return TEXT("FUpdateSendingVoiceTask");
    };

    virtual void Run(FVoiceTaskComplete OnComplete) override;
};

#endif // #if EOS_HAS_AUTHENTICATION && !EOS_VERSION_AT_LEAST(1, 16, 0)
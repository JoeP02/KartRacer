// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "./VoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

#if EOS_HAS_AUTHENTICATION && EOS_VERSION_AT_LEAST(1, 16, 0)

class FSetAudioOutputVolumeVoiceTaskData
{
public:
    EOS_HRTC EOSRTC;
    EOS_HRTCAudio EOSRTCAudio;
    EOS_ProductUserId LocalUserId;
    TArray<FString> RoomNames;
    bool bUserOutputMuted;
    float UserOutputVolume;
};

class FSetAudioOutputVolumeVoiceTask : public FVoiceTask
{
private:
    FSetAudioOutputVolumeVoiceTaskData Data;

public:
    FSetAudioOutputVolumeVoiceTask(FSetAudioOutputVolumeVoiceTaskData InData)
        : Data(MoveTemp(InData)){};
    UE_NONCOPYABLE(FSetAudioOutputVolumeVoiceTask);
    virtual ~FSetAudioOutputVolumeVoiceTask() = default;

    virtual FString GetLogName() override
    {
        return TEXT("FSetAudioOutputVolumeVoiceTask");
    };

    virtual void Run(FVoiceTaskComplete OnComplete) override;
};

#endif // #if EOS_HAS_AUTHENTICATION && EOS_VERSION_AT_LEAST(1, 16, 0)
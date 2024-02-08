// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "./VoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

#if EOS_HAS_AUTHENTICATION

class FSetAudioOutputSettingsVoiceTaskData
{
public:
    EOS_HRTCAudio EOSRTCAudio;
    EOS_ProductUserId LocalUserId;
    bool bHasSetCurrentOutputDevice;
    FString CurrentOutputDeviceId;
    FString DefaultOutputDeviceId;
    bool bUserOutputMuted;
    float UserOutputVolume;
};

class FSetAudioOutputSettingsVoiceTask : public FVoiceTask
{
private:
    FSetAudioOutputSettingsVoiceTaskData Data;

public:
    FSetAudioOutputSettingsVoiceTask(FSetAudioOutputSettingsVoiceTaskData InData)
        : Data(MoveTemp(InData)){};
    UE_NONCOPYABLE(FSetAudioOutputSettingsVoiceTask);
    virtual ~FSetAudioOutputSettingsVoiceTask() = default;

    virtual FString GetLogName() override
    {
        return TEXT("FSetAudioOutputSettingsVoiceTask");
    };

    virtual void Run(FVoiceTaskComplete OnComplete) override;
};

#endif // #if EOS_HAS_AUTHENTICATION
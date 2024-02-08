// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "./VoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

#if EOS_HAS_AUTHENTICATION

class FSetAudioInputSettingsVoiceTaskData
{
public:
    EOS_HRTC EOSRTC;
    EOS_HRTCAudio EOSRTCAudio;
    EOS_ProductUserId LocalUserId;
    bool bHasSetCurrentInputDevice;
    FString CurrentInputDeviceId;
    FString DefaultInputDeviceId;
    bool bUserInputMuted;
    float UserInputVolume;

    bool bEnableEchoCancellation;
    bool bEnableNoiseSuppression;
    bool bEnableAutoGainControl;
    bool bEnableDtx;
    bool bEnablePlatformAEC;
};

class FSetAudioInputSettingsVoiceTask : public FVoiceTask
{
private:
    FSetAudioInputSettingsVoiceTaskData Data;

public:
    FSetAudioInputSettingsVoiceTask(FSetAudioInputSettingsVoiceTaskData InData)
        : Data(MoveTemp(InData)){};
    UE_NONCOPYABLE(FSetAudioInputSettingsVoiceTask);
    virtual ~FSetAudioInputSettingsVoiceTask() = default;

    virtual FString GetLogName() override
    {
        return TEXT("FSetAudioInputSettingsVoiceTask");
    };

    virtual void Run(FVoiceTaskComplete OnComplete) override;
};

#endif // #if EOS_HAS_AUTHENTICATION
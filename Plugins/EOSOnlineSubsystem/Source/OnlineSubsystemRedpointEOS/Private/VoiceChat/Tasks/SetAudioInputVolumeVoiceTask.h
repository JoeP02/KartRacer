// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "./VoiceTask.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

#if EOS_HAS_AUTHENTICATION && EOS_VERSION_AT_LEAST(1, 16, 0)

class FSetAudioInputVolumeVoiceTaskData
{
public:
    struct FRoomNameWithTransmitStatus
    {
		FString RoomName;
        bool bIsTransmitting;
	};
    EOS_HRTC EOSRTC;
    EOS_HRTCAudio EOSRTCAudio;
    EOS_ProductUserId LocalUserId;
    TArray<FRoomNameWithTransmitStatus> RoomNamesWithTransmitStatus;
    bool bUserInputMuted;
    float UserInputVolume;
};

class FSetAudioInputVolumeVoiceTask : public FVoiceTask
{
private:
    FSetAudioInputVolumeVoiceTaskData Data;

public:
    FSetAudioInputVolumeVoiceTask(FSetAudioInputVolumeVoiceTaskData InData)
        : Data(MoveTemp(InData)){};
    UE_NONCOPYABLE(FSetAudioInputVolumeVoiceTask);
    virtual ~FSetAudioInputVolumeVoiceTask() = default;

    virtual FString GetLogName() override
    {
        return TEXT("FSetAudioInputVolumeVoiceTask");
    };

    virtual void Run(FVoiceTaskComplete OnComplete) override;
};

#endif // #if EOS_HAS_AUTHENTICATION && EOS_VERSION_AT_LEAST(1, 16, 0)
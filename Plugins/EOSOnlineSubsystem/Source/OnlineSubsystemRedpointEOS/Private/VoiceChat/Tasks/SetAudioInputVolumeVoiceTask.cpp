// Copyright June Rhodes 2024. All Rights Reserved.

#include "./SetAudioInputVolumeVoiceTask.h"

#include "OnlineSubsystemRedpointEOS/Shared/MultiOperation.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/RTCAudio/UpdateSendingVolume.h"

#if EOS_HAS_AUTHENTICATION && EOS_VERSION_AT_LEAST(1, 16, 0)

REDPOINT_EOS_DECLARE_CYCLE_STAT_INLINE_WITH_CALLBACK(
    VoiceChat,
    TEXT("Tasks/SetAudioInputVolume"),
    Tasks_SetAudioInputVolume);

void FSetAudioInputVolumeVoiceTask::Run(FVoiceTaskComplete OnComplete)
{
    using namespace Redpoint::EOS::API::RTCAudio;

    REDPOINT_EOS_SCOPE_CYCLE_COUNTER(VoiceChat, Tasks_SetAudioInputVolume);

    FMultiOperation<FSetAudioInputVolumeVoiceTaskData::FRoomNameWithTransmitStatus, bool>::Run(
        this->Data.RoomNamesWithTransmitStatus,
        [Data = this->Data](
            const FSetAudioInputVolumeVoiceTaskData::FRoomNameWithTransmitStatus &RoomNameWithTransmitStatus,
            auto OnDone) {
            FUpdateSendingVolume::Execute(
                Data.EOSRTCAudio,
                FUpdateSendingVolume::Options{
                    Data.LocalUserId,
                    RoomNameWithTransmitStatus.RoomName,
                    RoomNameWithTransmitStatus.bIsTransmitting
                        ? (Data.bUserInputMuted ? 0.0f : (Data.UserInputVolume / 2.0f))
                        : 0.0f},
                FUpdateSendingVolume::CompletionDelegate::CreateLambda(
                    [OnDone, RoomName = RoomNameWithTransmitStatus.RoomName](
                        const FUpdateSendingVolume::Result &SetInputVolumeResult) {
                        REDPOINT_EOS_LOG_RESULT_IF_UNSUCCESSFUL(
                            LogRedpointEOSVoiceChat,
                            Warning,
                            SetInputVolumeResult.ResultCode,
                            *FString::Printf(TEXT("Unable to set sending volume on room '%s'."), *RoomName));
                        OnDone(SetInputVolumeResult.ResultCode == EOS_EResult::EOS_Success);
                    }));
            return true;
        },
        [OnComplete](const TArray<bool> &Results) {
            OnComplete.ExecuteIfBound();
        });
}

#endif // #if EOS_HAS_AUTHENTICATION && EOS_VERSION_AT_LEAST(1, 16, 0)
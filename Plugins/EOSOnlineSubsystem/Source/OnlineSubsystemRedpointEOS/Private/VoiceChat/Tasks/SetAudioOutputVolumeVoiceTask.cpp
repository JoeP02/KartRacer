// Copyright June Rhodes 2024. All Rights Reserved.

#include "./SetAudioOutputVolumeVoiceTask.h"

#include "OnlineSubsystemRedpointEOS/Shared/EOSErrorConv.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/MultiOperation.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/RTCAudio/UpdateReceivingVolume.h"

#if EOS_HAS_AUTHENTICATION && EOS_VERSION_AT_LEAST(1, 16, 0)

REDPOINT_EOS_DECLARE_CYCLE_STAT_INLINE_WITH_CALLBACK(
    VoiceChat,
    TEXT("Tasks/SetAudioOutputVolume"),
    Tasks_SetAudioOutputVolume);

void FSetAudioOutputVolumeVoiceTask::Run(FVoiceTaskComplete OnComplete)
{
    using namespace Redpoint::EOS::API::RTCAudio;

    REDPOINT_EOS_SCOPE_CYCLE_COUNTER(VoiceChat, Tasks_SetAudioOutputVolume);

    FMultiOperation<FString, bool>::Run(
        this->Data.RoomNames,
        [Data = this->Data](const FString &RoomName, auto OnDone) {
            FUpdateReceivingVolume::Execute(
                Data.EOSRTCAudio,
                FUpdateReceivingVolume::Options{
                    Data.LocalUserId,
                    RoomName,
                    Data.bUserOutputMuted ? 0.0f : (Data.UserOutputVolume / 2.0f)},
                FUpdateReceivingVolume::CompletionDelegate::CreateLambda(
                    [OnDone, RoomName](const FUpdateReceivingVolume::Result &SetOutputVolumeResult) {
                        REDPOINT_EOS_LOG_RESULT_IF_UNSUCCESSFUL(
                            LogRedpointEOSVoiceChat,
                            Warning,
                            SetOutputVolumeResult.ResultCode,
                            *FString::Printf(TEXT("Unable to set receiving volume on room '%s'."), *RoomName));
                        OnDone(SetOutputVolumeResult.ResultCode == EOS_EResult::EOS_Success);
                    }));
            return true;
        },
        [OnComplete](const TArray<bool> &Results) {
            OnComplete.ExecuteIfBound();
        });
}

#endif // #if EOS_HAS_AUTHENTICATION && EOS_VERSION_AT_LEAST(1, 16, 0)
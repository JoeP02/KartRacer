// Copyright June Rhodes 2024. All Rights Reserved.

#include "./UpdateSendingVoiceTask.h"

#include "OnlineSubsystemRedpointEOS/Shared/MultiOperation.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/RTCAudio/UpdateSending.h"

#if EOS_HAS_AUTHENTICATION && !EOS_VERSION_AT_LEAST(1, 16, 0)

REDPOINT_EOS_DECLARE_CYCLE_STAT_INLINE_WITH_CALLBACK(VoiceChat, TEXT("Tasks/UpdateSending"), Tasks_UpdateSending);

void FUpdateSendingVoiceTask::Run(FVoiceTaskComplete OnComplete)
{
    using namespace Redpoint::EOS::API::RTCAudio;

    REDPOINT_EOS_SCOPE_CYCLE_COUNTER(VoiceChat, Tasks_UpdateSending);

    FMultiOperation<FUpdateSendingVoiceTaskData::FRoomNameWithTransmitStatus, bool>::Run(
        this->Data.RoomNamesWithTransmitStatus,
        [Data = this->Data](
            FUpdateSendingVoiceTaskData::FRoomNameWithTransmitStatus RoomNameWithTransmitStatus,
            auto OnDone) {
            FUpdateSending::Execute(
                Data.EOSRTCAudio,
                FUpdateSending::Options{
                    Data.LocalUserId,
                    RoomNameWithTransmitStatus.RoomName,
                    (RoomNameWithTransmitStatus.bIsTransmitting && !Data.bUserInputMuted)
                        ? EOS_ERTCAudioStatus::EOS_RTCAS_Enabled
                        : EOS_ERTCAudioStatus::EOS_RTCAS_Disabled},
                FUpdateSending::CompletionDelegate::CreateLambda(
                    [OnDone, RoomName = RoomNameWithTransmitStatus.RoomName](
                        const FUpdateSending::Result &UpdateSendingResult) {
                        REDPOINT_EOS_LOG_RESULT_IF_UNSUCCESSFUL(
                            LogRedpointEOSVoiceChat,
                            Warning,
                            UpdateSendingResult.ResultCode,
                            *FString::Printf(TEXT("Unable to update sending audio status on room '%s'."), *RoomName));
                        OnDone(UpdateSendingResult.ResultCode == EOS_EResult::EOS_Success);
                    }));
            return true;
        },
        [OnComplete](TArray<bool> Results) {
            OnComplete.ExecuteIfBound();
        });
}

#endif // #if EOS_HAS_AUTHENTICATION && !EOS_VERSION_AT_LEAST(1, 16, 0)
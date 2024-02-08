// Copyright June Rhodes 2024. All Rights Reserved.

#include "./SetAudioOutputSettingsVoiceTask.h"

#include "OnlineSubsystemRedpointEOS/Shared/EOSErrorConv.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/RTC/SetSetting.h"
#include "RedpointEOSAPI/RTCAudio/SetOutputDeviceSettings.h"

#if EOS_HAS_AUTHENTICATION

REDPOINT_EOS_DECLARE_CYCLE_STAT_INLINE_WITH_CALLBACK(
    VoiceChat,
    TEXT("Tasks/SetAudioOutputSettings"),
    Tasks_SetAudioOutputSettings);

void FSetAudioOutputSettingsVoiceTask::Run(FVoiceTaskComplete OnComplete)
{
    using namespace Redpoint::EOS::API::RTC;
    using namespace Redpoint::EOS::API::RTCAudio;

    REDPOINT_EOS_SCOPE_CYCLE_COUNTER(VoiceChat, Tasks_SetAudioOutputSettings);

    FString DeviceId;
    if (this->Data.bHasSetCurrentOutputDevice)
    {
        DeviceId = this->Data.CurrentOutputDeviceId;
    }
    else
    {
        DeviceId = this->Data.DefaultOutputDeviceId;
    }

    // Now we set the output settings.
    FSetOutputDeviceSettings::Execute(
        this->Data.EOSRTCAudio,
        FSetOutputDeviceSettings::Options{
            this->Data.LocalUserId,
            DeviceId,
            this->Data.bUserOutputMuted ? 0.0f : (this->Data.UserOutputVolume / 2)},
        FSetOutputDeviceSettings::CompletionDelegate::CreateLambda(
            [OnComplete](const FSetOutputDeviceSettings::Result &SetOutputDeviceResult) {
                REDPOINT_EOS_SCOPE_CYCLE_COUNTER(VoiceChat, Tasks_SetAudioOutputSettings_Callback);
                REDPOINT_EOS_LOG_RESULT_IF_UNSUCCESSFUL(
                    LogRedpointEOSVoiceChat,
                    Warning,
                    SetOutputDeviceResult.ResultCode,
                    TEXT("Failed to set audio output options."));
                OnComplete.ExecuteIfBound();
            }));
}

#endif // #if EOS_HAS_AUTHENTICATION
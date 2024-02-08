// Copyright June Rhodes 2024. All Rights Reserved.

#include "./SetAudioInputSettingsVoiceTask.h"

#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSErrorConv.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/RTC/SetSetting.h"
#include "RedpointEOSAPI/RTCAudio/SetInputDeviceSettings.h"

#if EOS_HAS_AUTHENTICATION

REDPOINT_EOS_DECLARE_CYCLE_STAT_INLINE_WITH_CALLBACK(
    VoiceChat,
    TEXT("Tasks/SetAudioInputSettings"),
    Tasks_SetAudioInputSettings);

void FSetAudioInputSettingsVoiceTask::Run(FVoiceTaskComplete OnComplete)
{
    using namespace Redpoint::EOS::API::RTC;
    using namespace Redpoint::EOS::API::RTCAudio;

    REDPOINT_EOS_SCOPE_CYCLE_COUNTER(VoiceChat, Tasks_SetAudioInputSettings);

    FString DeviceId;
    if (this->Data.bHasSetCurrentInputDevice)
    {
        DeviceId = this->Data.CurrentInputDeviceId;
    }
    else
    {
        DeviceId = this->Data.DefaultInputDeviceId;
    }

    // First we set all of the settings, since if any of these
    // are enabled, we can only set Volume to 100.0f.
    {
        EOS_EResult SetResult = FSetSetting::Execute(
            this->Data.EOSRTC,
            FSetSetting::Options{"DisableEchoCancelation", !this->Data.bEnableEchoCancellation ? "True" : "False"});
        REDPOINT_EOS_LOG_RESULT_IF_UNSUCCESSFUL(
            LogRedpointEOSVoiceChat,
            Warning,
            SetResult,
            TEXT("Unable to set echo cancellation on EOS RTC. Further calls may fail."));
    }
    {
        EOS_EResult SetResult = FSetSetting::Execute(
            this->Data.EOSRTC,
            FSetSetting::Options{"DisableNoiseSupression", !this->Data.bEnableNoiseSuppression ? "True" : "False"});
        REDPOINT_EOS_LOG_RESULT_IF_UNSUCCESSFUL(
            LogRedpointEOSVoiceChat,
            Warning,
            SetResult,
            TEXT("Unable to set noise suppression on EOS RTC. Further calls may fail."));
    }
    {
        EOS_EResult SetResult = FSetSetting::Execute(
            this->Data.EOSRTC,
            FSetSetting::Options{"DisableAutoGainControl", !this->Data.bEnableAutoGainControl ? "True" : "False"});
        REDPOINT_EOS_LOG_RESULT_IF_UNSUCCESSFUL(
            LogRedpointEOSVoiceChat,
            Warning,
            SetResult,
            TEXT("Unable to set auto gain control on EOS RTC. Further calls may fail."));
    }
    {
        EOS_EResult SetResult = FSetSetting::Execute(
            this->Data.EOSRTC,
            FSetSetting::Options{"DisableDtx", !this->Data.bEnableDtx ? "True" : "False"});
        REDPOINT_EOS_LOG_RESULT_IF_UNSUCCESSFUL(
            LogRedpointEOSVoiceChat,
            Warning,
            SetResult,
            TEXT("Unable to set DTX on EOS RTC. Further calls may fail."));
    }

    float IntendedVolume = 50.0f;
    if (!this->Data.bEnableAutoGainControl)
    {
        // InputVolume divided by two, since EOS RTC uses a range of 0.0 - 100.0f to represent silence - 2x gain.
        IntendedVolume = this->Data.bUserInputMuted ? 0.0f : (this->Data.UserInputVolume / 2.0f);
    }

    // Now we set the input settings.
    FSetInputDeviceSettings::Execute(
        this->Data.EOSRTCAudio,
        FSetInputDeviceSettings::Options{
            this->Data.LocalUserId,
            DeviceId,
            this->Data.bEnablePlatformAEC,
            IntendedVolume},
        FSetInputDeviceSettings::CompletionDelegate::CreateLambda(
            [OnComplete](const FSetInputDeviceSettings::Result &SetInputDeviceResult) {
                REDPOINT_EOS_SCOPE_CYCLE_COUNTER(VoiceChat, Tasks_SetAudioInputSettings_Callback);
                REDPOINT_EOS_LOG_RESULT_IF_UNSUCCESSFUL(
                    LogRedpointEOSVoiceChat,
                    Warning,
                    SetInputDeviceResult.ResultCode,
                    TEXT("Failed to set audio input options."));
                OnComplete.ExecuteIfBound();
            }));
}

#endif // #if EOS_HAS_AUTHENTICATION
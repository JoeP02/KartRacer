// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Shared/VoiceChat/VoiceManagerDeviceList.h"

#if EOS_HAS_AUTHENTICATION

#include "OnlineSubsystemRedpointEOS/Shared/EOSErrorConv.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/RTCAudio/QueryInputDevicesInformation.h"
#include "RedpointEOSAPI/RTCAudio/QueryOutputDevicesInformation.h"

#if !EOS_VERSION_AT_LEAST(1, 16, 0)
static bool bVoiceManagerDeviceListShownSyncWarning = false;
#endif

void FEOSVoiceManagerDeviceList::SynchroniseDeviceListFromEOS(
    const FEOSVoiceManagerDeviceListSynchronisationComplete &OnSynchronisationComplete)
{
    using namespace Redpoint::EOS::API::RTCAudio;

#if !EOS_VERSION_AT_LEAST(1, 16, 0)
    if (!bVoiceManagerDeviceListShownSyncWarning)
    {
        UE_LOG(
            LogRedpointEOSVoiceChat,
            Warning,
            TEXT("This version of the EOS SDK does not have the necessary APIs to asynchronously initialise the RTC "
                 "cache, which means you'll potentially get frame hitches or stalls when you use voice chat related "
                 "APIs for the first time. Please upgrade to EOS SDK 1.16.0 or later."));
        bVoiceManagerDeviceListShownSyncWarning = true;
    }
#endif

    // Query input devices.
    FQueryInputDevicesInformation::Execute(
        this->EOSRTCAudio,
        FQueryInputDevicesInformation::Options{},
        FQueryInputDevicesInformation::CompletionDelegate::CreateLambda(
            [WeakThis = GetWeakThis(this), OnSynchronisationComplete](
                EOS_EResult InputResultCode,
                const TArray<FDeviceInformation> &InputRawDevices) {
                if (auto This = PinWeakThis(WeakThis))
                {
                    if (InputResultCode != EOS_EResult::EOS_Success)
                    {
                        REDPOINT_EOS_LOG_RESULT(
                            LogRedpointEOSVoiceChat,
                            Error,
                            InputResultCode,
                            TEXT("Failed to query input devices."));
                        OnSynchronisationComplete.ExecuteIfBound(false, false);
                        return;
                    }

                    // Copy and set new input devices array.
                    TArray<FEOSVoiceManagerDevice> NewInputDevices;
                    for (const auto &InputDevice : InputRawDevices)
                    {
                        FEOSVoiceManagerDevice NewDevice;
                        NewDevice.Id = InputDevice.Id;
                        NewDevice.DisplayName = InputDevice.DisplayName;
                        NewDevice.bIsDefaultDevice = InputDevice.bIsDefaultDevice;
                        NewInputDevices.Add(NewDevice);
                    }
                    This->InputDevices = NewInputDevices;

                    // Query output devices.
                    FQueryOutputDevicesInformation::Execute(
                        This->EOSRTCAudio,
                        FQueryOutputDevicesInformation::Options{},
                        FQueryOutputDevicesInformation::CompletionDelegate::CreateLambda(
                            [WeakThis = GetWeakThis(This), OnSynchronisationComplete](
                                EOS_EResult OutputResultCode,
                                const TArray<FDeviceInformation> &OutputRawDevices) {
                                if (auto This = PinWeakThis(WeakThis))
                                {
                                    if (OutputResultCode != EOS_EResult::EOS_Success)
                                    {
                                        REDPOINT_EOS_LOG_RESULT(
                                            LogRedpointEOSVoiceChat,
                                            Error,
                                            OutputResultCode,
                                            TEXT("Failed to query output devices."));

                                        This->bHasSyncedAtLeastOnce = true;
                                        OnSynchronisationComplete.ExecuteIfBound(false, true);
                                        return;
                                    }

                                    // Copy and set new output devices array.
                                    TArray<FEOSVoiceManagerDevice> NewOutputDevices;
                                    for (const auto &OutputDevice : OutputRawDevices)
                                    {
                                        FEOSVoiceManagerDevice NewDevice;
                                        NewDevice.Id = OutputDevice.Id;
                                        NewDevice.DisplayName = OutputDevice.DisplayName;
                                        NewDevice.bIsDefaultDevice = OutputDevice.bIsDefaultDevice;
                                        NewOutputDevices.Add(NewDevice);
                                    }
                                    This->OutputDevices = NewOutputDevices;

                                    // Notify that input and output devices have changed.
                                    This->bHasSyncedAtLeastOnce = true;
                                    OnSynchronisationComplete.ExecuteIfBound(true, true);
                                }
                            }));
                }
            }));
}

FEOSVoiceManagerDeviceList::FEOSVoiceManagerDeviceList(EOS_HPlatform InPlatform)
    : EOSRTCAudio(EOS_RTC_GetAudioInterface(EOS_Platform_GetRTCInterface(InPlatform)))
    , Unregister_AudioDevicesChanged()
    , InputDevices()
    , OutputDevices()
    , bHasSyncedAtLeastOnce(false)
    , OnAudioDevicesChanged()
{
}

void FEOSVoiceManagerDeviceList::RegisterEvents()
{
    EOS_RTCAudio_AddNotifyAudioDevicesChangedOptions Opts = {};
    Opts.ApiVersion = EOS_RTCAUDIO_ADDNOTIFYAUDIODEVICESCHANGED_API_LATEST;

    this->Unregister_AudioDevicesChanged = EOSRegisterEvent<
        EOS_HRTCAudio,
        EOS_RTCAudio_AddNotifyAudioDevicesChangedOptions,
        EOS_RTCAudio_AudioDevicesChangedCallbackInfo>(
        this->EOSRTCAudio,
        &Opts,
        &EOS_RTCAudio_AddNotifyAudioDevicesChanged,
        &EOS_RTCAudio_RemoveNotifyAudioDevicesChanged,
        [WeakThis = GetWeakThis(this)](const EOS_RTCAudio_AudioDevicesChangedCallbackInfo *Data) {
            if (auto This = PinWeakThis(WeakThis))
            {
                This->SynchroniseDeviceListFromEOS(FEOSVoiceManagerDeviceListSynchronisationComplete::CreateLambda(
                    [WeakThis = GetWeakThis(This)](bool bWasSuccessful, bool bWasDeviceListUpdated) {
                        if (auto This = PinWeakThis(WeakThis))
                        {
                            if (bWasDeviceListUpdated)
                            {
                                This->OnAudioDevicesChanged.Broadcast();
                            }
                        }
                    }));
            }
        });
}

void FEOSVoiceManagerDeviceList::WaitForInitialDevices(
    const FEOSVoiceManagerDeviceListWaitForInitialDevices &OnInitialDevicesReceived)
{
    if (this->bHasSyncedAtLeastOnce)
    {
        // We've already synchronised the device list previously.
        OnInitialDevicesReceived.ExecuteIfBound();
    }
    else
    {
        // Perform an initial synchronisation.
        this->SynchroniseDeviceListFromEOS(FEOSVoiceManagerDeviceListSynchronisationComplete::CreateLambda(
            [OnInitialDevicesReceived](bool bWasSuccessful, bool bWasDeviceListUpdated) {
                OnInitialDevicesReceived.ExecuteIfBound();
            }));
    }
}

const TArray<FEOSVoiceManagerDevice> &FEOSVoiceManagerDeviceList::GetInputDevices() const
{
    return this->InputDevices;
}

const TArray<FEOSVoiceManagerDevice> &FEOSVoiceManagerDeviceList::GetOutputDevices() const
{
    return this->OutputDevices;
}

FOnVoiceChatAvailableAudioDevicesChangedDelegate &FEOSVoiceManagerDeviceList::OnDevicesChanged()
{
    return this->OnAudioDevicesChanged;
}

#endif // #if EOS_HAS_AUTHENTICATION
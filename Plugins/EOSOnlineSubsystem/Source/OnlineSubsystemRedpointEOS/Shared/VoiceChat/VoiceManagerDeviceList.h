// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#if EOS_HAS_AUTHENTICATION

#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "VoiceChat.h"

typedef TDelegate<void()> FEOSVoiceManagerDeviceListWaitForInitialDevices;
typedef TDelegate<void(bool bWasSuccessful, bool bWasDeviceListUpdated)>
    FEOSVoiceManagerDeviceListSynchronisationComplete;

class ONLINESUBSYSTEMREDPOINTEOS_API FEOSVoiceManagerDevice : public FVoiceChatDeviceInfo
{
public:
    bool bIsDefaultDevice;

    FEOSVoiceManagerDevice()
        : FVoiceChatDeviceInfo()
        , bIsDefaultDevice(false)
    {
        this->Id = FString();
        this->DisplayName = FString();
    }

    FEOSVoiceManagerDevice(const FString &InId, const FString &InDisplayName, bool bInIsDefaultDevice)
        : FVoiceChatDeviceInfo()
        , bIsDefaultDevice(bInIsDefaultDevice)
    {
        this->Id = InId;
        this->DisplayName = InDisplayName;
    }
};

class ONLINESUBSYSTEMREDPOINTEOS_API FEOSVoiceManagerDeviceList : public TSharedFromThis<FEOSVoiceManagerDeviceList>
{
private:
    EOS_HRTCAudio EOSRTCAudio;
    TSharedPtr<EOSEventHandle<EOS_RTCAudio_AudioDevicesChangedCallbackInfo>> Unregister_AudioDevicesChanged;
    TArray<FEOSVoiceManagerDevice> InputDevices;
    TArray<FEOSVoiceManagerDevice> OutputDevices;
    bool bHasSyncedAtLeastOnce;
    FOnVoiceChatAvailableAudioDevicesChangedDelegate OnAudioDevicesChanged;

    /** Queries devices in the EOS SDK asynchronously to update InputDevices and OutputDevices. */
    void SynchroniseDeviceListFromEOS(
        const FEOSVoiceManagerDeviceListSynchronisationComplete &OnSynchronisationComplete);

public:
    FEOSVoiceManagerDeviceList(EOS_HPlatform InPlatform);
    UE_NONCOPYABLE(FEOSVoiceManagerDeviceList);
    virtual ~FEOSVoiceManagerDeviceList(){};

    void RegisterEvents();

    /** Returns asynchronously when the initial audio devices have been received. */
    void WaitForInitialDevices(const FEOSVoiceManagerDeviceListWaitForInitialDevices &OnInitialDevicesReceived);

    /** Retrieves the current input devices. If initial audio devices haven't been received yet, this returns an empty
     * array. */
    const TArray<FEOSVoiceManagerDevice> &GetInputDevices() const;

    /** Retrieves the current output devices. If initial audio devices haven't been received yet, this returns an empty
     * array. */
    const TArray<FEOSVoiceManagerDevice> &GetOutputDevices() const;

    /** Invoked when the available audio devices change. */
    FOnVoiceChatAvailableAudioDevicesChangedDelegate &OnDevicesChanged();
};

#endif // #if EOS_HAS_AUTHENTICATION
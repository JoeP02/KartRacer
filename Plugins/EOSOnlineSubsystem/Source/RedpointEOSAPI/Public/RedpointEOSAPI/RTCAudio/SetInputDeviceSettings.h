// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSAPI/Templates.h"

namespace Redpoint::EOS::API::RTCAudio
{

class REDPOINTEOSAPI_API FSetInputDeviceSettings
{
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    REDPOINT_EOSSDK_API_CALL_ASYNC_BEGIN(
        RTCAudio,
        SetInputDeviceSettings,
        EOS_RTCAUDIO_SETINPUTDEVICESETTINGS_API_LATEST)
#else
    REDPOINT_EOSSDK_API_CALL_SYNC_AS_ASYNC_BEGIN(
        RTCAudio,
        SetAudioInputSettings,
        EOS_RTCAUDIO_SETAUDIOINPUTSETTINGS_API_LATEST)
#endif

    class Options
    {
    public:
        const ParamHelpers::TRequired<EOS_ProductUserId> LocalUserId;
        const ParamHelpers::TRequired<FString> DeviceId;
        const ParamHelpers::TRequired<bool> bEnablePlatformAEC;
        const ParamHelpers::TRequired<float> DeviceVolume;
    };

    class Result
    {
    public:
        EOS_EResult ResultCode;
    };

#if EOS_VERSION_AT_LEAST(1, 16, 0)
    REDPOINT_EOSSDK_API_CALL_ASYNC_END()
#else
    REDPOINT_EOSSDK_API_CALL_SYNC_AS_ASYNC_END()
#endif
};

} // namespace Redpoint::EOS::API::RTCAudio
// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "RedpointEOSAPI/RTCAudio/DeviceInformation.h"
#include "RedpointEOSAPI/Templates.h"

namespace Redpoint::EOS::API::RTCAudio
{

class REDPOINTEOSAPI_API FQueryInputDevicesInformation
{
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    REDPOINT_EOSSDK_API_CALL_ASYNC_LIST_BEGIN(
        RTCAudio,
        QueryInputDevicesInformation,
        EOS_RTCAUDIO_QUERYINPUTDEVICESINFORMATION_API_LATEST,
        GetInputDevicesCount,
        EOS_RTCAUDIO_GETINPUTDEVICESCOUNT_API_LATEST,
        CopyInputDeviceInformationByIndex,
        EOS_RTCAUDIO_COPYINPUTDEVICEINFORMATIONBYINDEX_API_LATEST,
        InputDeviceInformation)
#else
    REDPOINT_EOSSDK_API_CALL_SYNC_LIST_AS_ASYNC_LIST_BEGIN(
        RTCAudio,
        GetAudioInputDevicesCount,
        EOS_RTCAUDIO_GETAUDIOINPUTDEVICESCOUNT_API_LATEST,
        GetAudioInputDeviceByIndex,
        EOS_RTCAUDIO_GETAUDIOINPUTDEVICEBYINDEX_API_LATEST)
#endif

    class Options
    {
    };

    typedef FDeviceInformation ResultEntry;

#if EOS_VERSION_AT_LEAST(1, 16, 0)
    REDPOINT_EOSSDK_API_CALL_ASYNC_LIST_END()
#else
    REDPOINT_EOSSDK_API_CALL_SYNC_LIST_AS_ASYNC_LIST_END()
#endif
};

} // namespace Redpoint::EOS::API::RTCAudio
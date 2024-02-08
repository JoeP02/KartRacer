// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "RedpointEOSAPI/Templates.h"
#include "RedpointEOSAPI/RTCAudio/DeviceInformation.h"

namespace Redpoint::EOS::API::RTCAudio
{

class REDPOINTEOSAPI_API FQueryOutputDevicesInformation
{
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    REDPOINT_EOSSDK_API_CALL_ASYNC_LIST_BEGIN(
        RTCAudio,
        QueryOutputDevicesInformation,
        EOS_RTCAUDIO_QUERYOUTPUTDEVICESINFORMATION_API_LATEST,
        GetOutputDevicesCount,
        EOS_RTCAUDIO_GETOUTPUTDEVICESCOUNT_API_LATEST,
        CopyOutputDeviceInformationByIndex,
        EOS_RTCAUDIO_COPYOUTPUTDEVICEINFORMATIONBYINDEX_API_LATEST,
        OutputDeviceInformation)
#else
    REDPOINT_EOSSDK_API_CALL_SYNC_LIST_AS_ASYNC_LIST_BEGIN(
        RTCAudio,
        GetAudioOutputDevicesCount,
        EOS_RTCAUDIO_GETAUDIOOUTPUTDEVICESCOUNT_API_LATEST,
        GetAudioOutputDeviceByIndex,
        EOS_RTCAUDIO_GETAUDIOOUTPUTDEVICEBYINDEX_API_LATEST)
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
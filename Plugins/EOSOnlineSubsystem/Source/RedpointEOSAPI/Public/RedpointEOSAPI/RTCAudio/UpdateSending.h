// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "RedpointEOSAPI/Templates.h"

namespace Redpoint::EOS::API::RTCAudio
{

class REDPOINTEOSAPI_API FUpdateSending
{
    REDPOINT_EOSSDK_API_CALL_ASYNC_BEGIN(RTCAudio, UpdateSending, EOS_RTCAUDIO_UPDATESENDING_API_LATEST)

    class Options
    {
    public:
        const ParamHelpers::TRequired<EOS_ProductUserId> LocalUserId;
        const ParamHelpers::TRequired<FString> RoomName;
        const ParamHelpers::TRequired<EOS_ERTCAudioStatus> AudioStatus;
    };

    class Result
    {
    public:
        EOS_EResult ResultCode;
        EOS_ProductUserId LocalUserId;
        EOS_ERTCAudioStatus AudioStatus;
    };

    REDPOINT_EOSSDK_API_CALL_ASYNC_END()
};

} // namespace Redpoint::EOS::API::RTCAudio
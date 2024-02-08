// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "RedpointEOSAPI/Templates.h"

namespace Redpoint::EOS::API::Connect
{

class REDPOINTEOSAPI_API FLogin
{
    REDPOINT_EOSSDK_API_CALL_ASYNC_BEGIN(Connect, Login, EOS_CONNECT_LOGIN_API_LATEST)

    class Options
    {
    public:
        const ParamHelpers::TRequired<FString> Id;
        const ParamHelpers::TRequired<FString> Token;
        const ParamHelpers::TRequired<FString> LocalDisplayName;
        const ParamHelpers::TRequired<EOS_EExternalCredentialType> Type;
    };

    class Result
    {
    public:
        EOS_EResult ResultCode;
        EOS_Connect_LoginCallbackInfo Result;
    };

    REDPOINT_EOSSDK_API_CALL_ASYNC_END()
};

} // namespace Redpoint::EOS::API::Connect
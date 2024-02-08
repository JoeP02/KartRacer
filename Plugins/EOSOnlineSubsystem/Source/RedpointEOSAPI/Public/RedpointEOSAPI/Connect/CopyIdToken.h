// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "RedpointEOSAPI/Templates.h"

namespace Redpoint::EOS::API::Connect
{

class REDPOINTEOSAPI_API FCopyIdToken
{
    REDPOINT_EOSSDK_API_CALL_SYNC_COPY_BEGIN(Connect, CopyIdToken, EOS_CONNECT_COPYIDTOKEN_API_LATEST, IdToken)

    class Options
    {
    public:
        const ParamHelpers::TRequired<EOS_ProductUserId> LocalUserId;
    };

    class Result
    {
    public:
        FString JsonWebToken;
    };

    REDPOINT_EOSSDK_API_CALL_SYNC_COPY_END()
};

} // namespace Redpoint::EOS::API::Connect
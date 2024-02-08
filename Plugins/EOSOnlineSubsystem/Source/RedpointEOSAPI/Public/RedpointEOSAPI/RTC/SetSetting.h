// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "RedpointEOSAPI/Templates.h"

namespace Redpoint::EOS::API::RTC
{

class REDPOINTEOSAPI_API FSetSetting
{
    REDPOINT_EOSSDK_API_CALL_SYNC_BEGIN(RTC, SetSetting, EOS_RTC_SETSETTING_API_LATEST)

    class Options
    {
    public:
        const ParamHelpers::TRequired<FString> SettingName;
        const ParamHelpers::TRequired<FString> SettingValue;
    };

    REDPOINT_EOSSDK_API_CALL_SYNC_END()
};

} // namespace Redpoint::EOS::API::RTC
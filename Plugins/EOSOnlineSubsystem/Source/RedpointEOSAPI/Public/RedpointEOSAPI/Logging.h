// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSAPI/Error.h"

DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSAPI, Verbose, All);

#define REDPOINT_EOS_LOG_RESULT(LogCategory, LogLevel, ResultCode, LogContext)                                         \
    UE_LOG(                                                                                                            \
        LogCategory,                                                                                                   \
        LogLevel,                                                                                                      \
        TEXT("%s"),                                                                                                    \
        *Redpoint::EOS::API::ConvertError(ANSI_TO_TCHAR(__FUNCTION__), LogContext, ResultCode).ToLogString());
#define REDPOINT_EOS_LOG_RESULT_IF_UNSUCCESSFUL(LogCategory, LogLevel, ResultCode, LogContext)                         \
    if (ResultCode != EOS_EResult::EOS_Success)                                                                        \
    {                                                                                                                  \
        REDPOINT_EOS_LOG_RESULT(LogCategory, LogLevel, ResultCode, LogContext);                                        \
    }
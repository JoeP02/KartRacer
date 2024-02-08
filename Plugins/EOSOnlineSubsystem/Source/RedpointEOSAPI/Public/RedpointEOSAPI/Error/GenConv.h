// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "RedpointEOSAPI/Error/Decl.h"
#include "RedpointEOSAPI/SDK.h"

namespace Redpoint::EOS::API
{

REDPOINTEOSAPI_API const FError &ConvertError(EOS_EResult Result);
REDPOINTEOSAPI_API const FError ConvertError(const TCHAR *InCall, const FString &InContextMsg, EOS_EResult Result);
REDPOINTEOSAPI_API const FError ConvertError(const TCHAR *InCall, const TCHAR *InContextMsg, EOS_EResult Result);

}
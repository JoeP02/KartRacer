// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "Containers/UnrealString.h"
#include "CoreMinimal.h"
#include "RedpointEOSAPI/Templates/ParamHelpers.h"
#include "RedpointEOSAPI/SDK.h"

namespace Redpoint::EOS::API
{

struct REDPOINTEOSAPI_API FError
{
public:
    /** If true, the operation was successful. */
    const ParamHelpers::TRequired<bool> bWasSuccessful;

	/** The namespace for the error. This will always be "errors.com.redpoint.eos". */
    const ParamHelpers::TRequired<FString> ErrorNamespace;

	/** The string-based error code, such as "errors.com.redpoint.eos.unexpected_error". */
    const ParamHelpers::TRequired<FString> ErrorCode;

	/** The description of the error, as per the EOS SDK header files. */
    const ParamHelpers::TRequired<FText> ErrorMessage;

	/** The original EOS_EResult error code for logical comparison. */
    const ParamHelpers::TRequired<EOS_EResult> ResultCode;

	/** The name of the function or original call this error occurred in. */
    const ParamHelpers::TRequired<FString> OriginalCall;

	/** The context in which the error occurred. */
    const ParamHelpers::TRequired<FString> Context;

	/** Converts the error to a format suitable for logging. */
    FString ToLogString() const;
};

} // namespace Redpoint::EOS::API
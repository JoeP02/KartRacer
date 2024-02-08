// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/Error/Gen.h"

#include "RedpointEOSAPI/Error/Decl.h"

#define ONLINE_ERROR_NAMESPACE "errors.com.redpoint.eos"

const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Success()
{
    static Redpoint::EOS::API::FError Err = {
        true,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.success"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Success", "Successful result"),
        EOS_EResult::EOS_Success,
        TEXT(""),
        TEXT("")
    };
    return Err;
}

const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Success(const TCHAR *InCall, const FString &InContextMsg)
{
    return Redpoint::EOS::API::FError{
        true,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.success"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Success", "Successful result"),
        EOS_EResult::EOS_Success,
        InCall,
        InContextMsg
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::UnexpectedError()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.unexpected_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UnexpectedError", "An unexpected error that we cannot identify has occurred."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_UnexpectedError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::UnexpectedError(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.unexpected_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UnexpectedError", "An unexpected error that we cannot identify has occurred."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_UnexpectedError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::UnexpectedError(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.unexpected_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UnexpectedError", "An unexpected error that we cannot identify has occurred."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_UnexpectedError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::NoConnection()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.no_connection"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NoConnection", "Failed due to no connection"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NoConnection,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NoConnection(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.no_connection"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NoConnection", "Failed due to no connection"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NoConnection,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NoConnection(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.no_connection"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NoConnection", "Failed due to no connection"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NoConnection,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::InvalidParameters()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_parameters"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidParameters", "Invalid parameters specified for request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidParameters,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidParameters(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_parameters"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidParameters", "Invalid parameters specified for request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidParameters,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidParameters(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_parameters"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidParameters", "Invalid parameters specified for request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidParameters,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::InvalidRequest()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_request"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidRequest", "Invalid request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidRequest,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidRequest(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_request"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidRequest", "Invalid request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidRequest,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidRequest(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_request"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidRequest", "Invalid request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidRequest,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::UnrecognizedResponse()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.unrecognized_response"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UnrecognizedResponse", "Failed due to unable to parse or recognize a backend response"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_UnrecognizedResponse,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::UnrecognizedResponse(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.unrecognized_response"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UnrecognizedResponse", "Failed due to unable to parse or recognize a backend response"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_UnrecognizedResponse,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::UnrecognizedResponse(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.unrecognized_response"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UnrecognizedResponse", "Failed due to unable to parse or recognize a backend response"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_UnrecognizedResponse,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::IncompatibleVersion()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.incompatible_version"),
        NSLOCTEXT("RedpointEOSAPI", "Error_IncompatibleVersion", "Incompatible client for backend version"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_IncompatibleVersion,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::IncompatibleVersion(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.incompatible_version"),
        NSLOCTEXT("RedpointEOSAPI", "Error_IncompatibleVersion", "Incompatible client for backend version"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_IncompatibleVersion,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::IncompatibleVersion(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.incompatible_version"),
        NSLOCTEXT("RedpointEOSAPI", "Error_IncompatibleVersion", "Incompatible client for backend version"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_IncompatibleVersion,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::NotConfigured()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.not_configured"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NotConfigured", "Not configured correctly for use"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NotConfigured,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NotConfigured(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.not_configured"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NotConfigured", "Not configured correctly for use"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NotConfigured,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NotConfigured(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.not_configured"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NotConfigured", "Not configured correctly for use"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NotConfigured,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AlreadyConfigured()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.already_configured"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AlreadyConfigured", "Already configured for use."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AlreadyConfigured,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AlreadyConfigured(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.already_configured"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AlreadyConfigured", "Already configured for use."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AlreadyConfigured,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AlreadyConfigured(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.already_configured"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AlreadyConfigured", "Already configured for use."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AlreadyConfigured,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::NotImplemented()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.not_implemented"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NotImplemented", "Feature not available on this implementation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NotImplemented,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NotImplemented(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.not_implemented"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NotImplemented", "Feature not available on this implementation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NotImplemented,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NotImplemented(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.not_implemented"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NotImplemented", "Feature not available on this implementation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NotImplemented,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Canceled()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.canceled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Canceled", "Operation was canceled (likely by user)"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Canceled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Canceled(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.canceled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Canceled", "Operation was canceled (likely by user)"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Canceled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Canceled(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.canceled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Canceled", "Operation was canceled (likely by user)"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Canceled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::NotFound()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NotFound", "The requested information was not found"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NotFound(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NotFound", "The requested information was not found"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NotFound(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NotFound", "The requested information was not found"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Permission_RequiredPatchAvailable()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_required_patch_available"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_RequiredPatchAvailable", "Patch required before the user can use the privilege"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_RequiredPatchAvailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_RequiredPatchAvailable(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_required_patch_available"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_RequiredPatchAvailable", "Patch required before the user can use the privilege"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_RequiredPatchAvailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_RequiredPatchAvailable(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_required_patch_available"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_RequiredPatchAvailable", "Patch required before the user can use the privilege"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_RequiredPatchAvailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Permission_RequiredSystemUpdate()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_required_system_update"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_RequiredSystemUpdate", "System update required before the user can use the privilege"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_RequiredSystemUpdate,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_RequiredSystemUpdate(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_required_system_update"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_RequiredSystemUpdate", "System update required before the user can use the privilege"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_RequiredSystemUpdate,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_RequiredSystemUpdate(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_required_system_update"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_RequiredSystemUpdate", "System update required before the user can use the privilege"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_RequiredSystemUpdate,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Permission_AgeRestrictionFailure()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_age_restriction_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_AgeRestrictionFailure", "Parental control failure usually"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_AgeRestrictionFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_AgeRestrictionFailure(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_age_restriction_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_AgeRestrictionFailure", "Parental control failure usually"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_AgeRestrictionFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_AgeRestrictionFailure(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_age_restriction_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_AgeRestrictionFailure", "Parental control failure usually"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_AgeRestrictionFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Permission_AccountTypeFailure()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_account_type_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_AccountTypeFailure", "Premium Account Subscription required but not available"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_AccountTypeFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_AccountTypeFailure(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_account_type_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_AccountTypeFailure", "Premium Account Subscription required but not available"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_AccountTypeFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_AccountTypeFailure(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_account_type_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_AccountTypeFailure", "Premium Account Subscription required but not available"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_AccountTypeFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Permission_ChatRestriction()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_chat_restriction"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_ChatRestriction", "User restricted from chat"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_ChatRestriction,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_ChatRestriction(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_chat_restriction"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_ChatRestriction", "User restricted from chat"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_ChatRestriction,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_ChatRestriction(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_chat_restriction"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_ChatRestriction", "User restricted from chat"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_ChatRestriction,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Permission_UGCRestriction()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_ugc_restriction"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_UGCRestriction", "User restricted from User Generated Content"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_UGCRestriction,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_UGCRestriction(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_ugc_restriction"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_UGCRestriction", "User restricted from User Generated Content"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_UGCRestriction,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_UGCRestriction(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_ugc_restriction"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_UGCRestriction", "User restricted from User Generated Content"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_UGCRestriction,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Permission_OnlinePlayRestricted()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_online_play_restricted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_OnlinePlayRestricted", "Online play is restricted"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_OnlinePlayRestricted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_OnlinePlayRestricted(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_online_play_restricted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_OnlinePlayRestricted", "Online play is restricted"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_OnlinePlayRestricted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Permission_OnlinePlayRestricted(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.permission_online_play_restricted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Permission_OnlinePlayRestricted", "Online play is restricted"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Permission_OnlinePlayRestricted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::OperationWillRetry()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.operation_will_retry"),
        NSLOCTEXT("RedpointEOSAPI", "Error_OperationWillRetry", "An error occurred during an asynchronous operation, and it will be retried. Callbacks receiving this result will be called again in the future."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_OperationWillRetry,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::OperationWillRetry(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.operation_will_retry"),
        NSLOCTEXT("RedpointEOSAPI", "Error_OperationWillRetry", "An error occurred during an asynchronous operation, and it will be retried. Callbacks receiving this result will be called again in the future."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_OperationWillRetry,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::OperationWillRetry(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.operation_will_retry"),
        NSLOCTEXT("RedpointEOSAPI", "Error_OperationWillRetry", "An error occurred during an asynchronous operation, and it will be retried. Callbacks receiving this result will be called again in the future."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_OperationWillRetry,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::DesktopCrossplay_ApplicationNotBootstrapped()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_application_not_bootstrapped"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ApplicationNotBootstrapped", "The application was not launched through the Bootstrapper. Desktop crossplay functionality is unavailable."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ApplicationNotBootstrapped,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::DesktopCrossplay_ApplicationNotBootstrapped(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_application_not_bootstrapped"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ApplicationNotBootstrapped", "The application was not launched through the Bootstrapper. Desktop crossplay functionality is unavailable."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ApplicationNotBootstrapped,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::DesktopCrossplay_ApplicationNotBootstrapped(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_application_not_bootstrapped"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ApplicationNotBootstrapped", "The application was not launched through the Bootstrapper. Desktop crossplay functionality is unavailable."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ApplicationNotBootstrapped,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotInstalled()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_service_not_installed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ServiceNotInstalled", "The redistributable service is not installed."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ServiceNotInstalled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotInstalled(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_service_not_installed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ServiceNotInstalled", "The redistributable service is not installed."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ServiceNotInstalled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotInstalled(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_service_not_installed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ServiceNotInstalled", "The redistributable service is not installed."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ServiceNotInstalled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceStartFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_service_start_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ServiceStartFailed", "The desktop crossplay service failed to start."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ServiceStartFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceStartFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_service_start_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ServiceStartFailed", "The desktop crossplay service failed to start."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ServiceStartFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceStartFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_service_start_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ServiceStartFailed", "The desktop crossplay service failed to start."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ServiceStartFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotRunning()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_service_not_running"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ServiceNotRunning", "The desktop crossplay service is no longer running for an unknown reason."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ServiceNotRunning,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotRunning(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_service_not_running"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ServiceNotRunning", "The desktop crossplay service is no longer running for an unknown reason."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ServiceNotRunning,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotRunning(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.desktop_crossplay_service_not_running"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DesktopCrossplay_ServiceNotRunning", "The desktop crossplay service is no longer running for an unknown reason."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DesktopCrossplay_ServiceNotRunning,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::InvalidCredentials()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_credentials"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidCredentials", "Failed login due to invalid credentials"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidCredentials,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidCredentials(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_credentials"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidCredentials", "Failed login due to invalid credentials"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidCredentials,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidCredentials(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_credentials"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidCredentials", "Failed login due to invalid credentials"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidCredentials,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::NoChange()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.no_change"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NoChange", "The request had no effect"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NoChange,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NoChange(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.no_change"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NoChange", "The request had no effect"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NoChange,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NoChange(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.no_change"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NoChange", "The request had no effect"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NoChange,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::CustomInvites_InviteFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.custom_invites_invite_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_CustomInvites_InviteFailed", "When sending the custom invite failed."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_CustomInvites_InviteFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::CustomInvites_InviteFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.custom_invites_invite_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_CustomInvites_InviteFailed", "When sending the custom invite failed."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_CustomInvites_InviteFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::CustomInvites_InviteFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.custom_invites_invite_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_CustomInvites_InviteFailed", "When sending the custom invite failed."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_CustomInvites_InviteFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::VersionMismatch()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.version_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_VersionMismatch", "The request attempted to use multiple or inconsistent API versions"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_VersionMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::VersionMismatch(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.version_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_VersionMismatch", "The request attempted to use multiple or inconsistent API versions"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_VersionMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::VersionMismatch(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.version_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_VersionMismatch", "The request attempted to use multiple or inconsistent API versions"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_VersionMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::LimitExceeded()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.limit_exceeded"),
        NSLOCTEXT("RedpointEOSAPI", "Error_LimitExceeded", "A maximum limit was exceeded on the client, different from EOS_TooManyRequests"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_LimitExceeded,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::LimitExceeded(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.limit_exceeded"),
        NSLOCTEXT("RedpointEOSAPI", "Error_LimitExceeded", "A maximum limit was exceeded on the client, different from EOS_TooManyRequests"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_LimitExceeded,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::LimitExceeded(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.limit_exceeded"),
        NSLOCTEXT("RedpointEOSAPI", "Error_LimitExceeded", "A maximum limit was exceeded on the client, different from EOS_TooManyRequests"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_LimitExceeded,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::UserInfo_BestDisplayNameIndeterminate()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.user_info_best_display_name_indeterminate"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UserInfo_BestDisplayNameIndeterminate", "The best display name could not be safely determined."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_UserInfo_BestDisplayNameIndeterminate,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::UserInfo_BestDisplayNameIndeterminate(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.user_info_best_display_name_indeterminate"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UserInfo_BestDisplayNameIndeterminate", "The best display name could not be safely determined."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_UserInfo_BestDisplayNameIndeterminate,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::UserInfo_BestDisplayNameIndeterminate(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.user_info_best_display_name_indeterminate"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UserInfo_BestDisplayNameIndeterminate", "The best display name could not be safely determined."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_UserInfo_BestDisplayNameIndeterminate,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Disabled()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.disabled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Disabled", "Feature or client ID performing the operation has been disabled."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Disabled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Disabled(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.disabled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Disabled", "Feature or client ID performing the operation has been disabled."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Disabled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Disabled(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.disabled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Disabled", "Feature or client ID performing the operation has been disabled."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Disabled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::DuplicateNotAllowed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.duplicate_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DuplicateNotAllowed", "Duplicate entry not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DuplicateNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::DuplicateNotAllowed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.duplicate_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DuplicateNotAllowed", "Duplicate entry not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DuplicateNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::DuplicateNotAllowed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.duplicate_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_DuplicateNotAllowed", "Duplicate entry not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_DuplicateNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::InvalidSandboxId()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_sandbox_id"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidSandboxId", "Sandbox ID is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidSandboxId,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidSandboxId(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_sandbox_id"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidSandboxId", "Sandbox ID is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidSandboxId,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidSandboxId(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_sandbox_id"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidSandboxId", "Sandbox ID is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidSandboxId,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::TimedOut()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.timed_out"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TimedOut", "Request timed out"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TimedOut,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TimedOut(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.timed_out"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TimedOut", "Request timed out"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TimedOut,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TimedOut(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.timed_out"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TimedOut", "Request timed out"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TimedOut,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PartialResult()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.partial_result"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PartialResult", "A query returned some but not all of the requested results."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PartialResult,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PartialResult(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.partial_result"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PartialResult", "A query returned some but not all of the requested results."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PartialResult,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PartialResult(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.partial_result"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PartialResult", "A query returned some but not all of the requested results."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PartialResult,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Missing_Role()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.missing_role"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Missing_Role", "Client is missing the whitelisted role"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Missing_Role,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Missing_Role(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.missing_role"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Missing_Role", "Client is missing the whitelisted role"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Missing_Role,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Missing_Role(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.missing_role"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Missing_Role", "Client is missing the whitelisted role"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Missing_Role,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::InvalidUser()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_user"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidUser", "Failed due to invalid or missing user"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidUser,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidUser(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_user"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidUser", "Failed due to invalid or missing user"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidUser,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidUser(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_user"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidUser", "Failed due to invalid or missing user"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidUser,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Missing_Feature()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.missing_feature"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Missing_Feature", "Client is missing the whitelisted feature"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Missing_Feature,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Missing_Feature(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.missing_feature"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Missing_Feature", "Client is missing the whitelisted feature"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Missing_Feature,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Missing_Feature(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.missing_feature"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Missing_Feature", "Client is missing the whitelisted feature"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Missing_Feature,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Invalid_Sandbox()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_sandbox"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_Sandbox", "The sandbox given to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_Sandbox,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Invalid_Sandbox(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_sandbox"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_Sandbox", "The sandbox given to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_Sandbox,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Invalid_Sandbox(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_sandbox"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_Sandbox", "The sandbox given to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_Sandbox,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Invalid_Deployment()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_deployment"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_Deployment", "The deployment given to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_Deployment,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Invalid_Deployment(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_deployment"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_Deployment", "The deployment given to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_Deployment,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Invalid_Deployment(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_deployment"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_Deployment", "The deployment given to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_Deployment,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Invalid_Product()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_product"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_Product", "The product ID specified to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_Product,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Invalid_Product(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_product"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_Product", "The product ID specified to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_Product,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Invalid_Product(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_product"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_Product", "The product ID specified to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_Product,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Invalid_ProductUserID()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_product_user_id"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_ProductUserID", "The product user ID specified to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_ProductUserID,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Invalid_ProductUserID(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_product_user_id"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_ProductUserID", "The product user ID specified to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_ProductUserID,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Invalid_ProductUserID(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_product_user_id"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Invalid_ProductUserID", "The product user ID specified to the backend is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Invalid_ProductUserID,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::ServiceFailure()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.service_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_ServiceFailure", "There was a failure with the backend service"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_ServiceFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::ServiceFailure(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.service_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_ServiceFailure", "There was a failure with the backend service"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_ServiceFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::ServiceFailure(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.service_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_ServiceFailure", "There was a failure with the backend service"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_ServiceFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::CacheDirectoryMissing()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.cache_directory_missing"),
        NSLOCTEXT("RedpointEOSAPI", "Error_CacheDirectoryMissing", "Cache directory is not set in platform options."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_CacheDirectoryMissing,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::CacheDirectoryMissing(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.cache_directory_missing"),
        NSLOCTEXT("RedpointEOSAPI", "Error_CacheDirectoryMissing", "Cache directory is not set in platform options."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_CacheDirectoryMissing,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::CacheDirectoryMissing(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.cache_directory_missing"),
        NSLOCTEXT("RedpointEOSAPI", "Error_CacheDirectoryMissing", "Cache directory is not set in platform options."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_CacheDirectoryMissing,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::CacheDirectoryInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.cache_directory_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_CacheDirectoryInvalid", "Cache directory is not accessible."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_CacheDirectoryInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::CacheDirectoryInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.cache_directory_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_CacheDirectoryInvalid", "Cache directory is not accessible."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_CacheDirectoryInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::CacheDirectoryInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.cache_directory_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_CacheDirectoryInvalid", "Cache directory is not accessible."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_CacheDirectoryInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::InvalidState()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_state"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidState", "The request failed because resource was in an invalid state"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidState,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidState(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_state"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidState", "The request failed because resource was in an invalid state"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidState,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidState(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_state"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidState", "The request failed because resource was in an invalid state"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidState,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::RequestInProgress()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.request_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RequestInProgress", "Request is in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RequestInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RequestInProgress(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.request_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RequestInProgress", "Request is in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RequestInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RequestInProgress(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.request_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RequestInProgress", "Request is in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RequestInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::InvalidAuth()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_auth"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidAuth", "Failed due to invalid or missing authentication token for user (e.g. not logged in)"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidAuth,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidAuth(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_auth"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidAuth", "Failed due to invalid or missing authentication token for user (e.g. not logged in)"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidAuth,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::InvalidAuth(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.invalid_auth"),
        NSLOCTEXT("RedpointEOSAPI", "Error_InvalidAuth", "Failed due to invalid or missing authentication token for user (e.g. not logged in)"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_InvalidAuth,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::ApplicationSuspended()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.application_suspended"),
        NSLOCTEXT("RedpointEOSAPI", "Error_ApplicationSuspended", "Application is suspended"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_ApplicationSuspended,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::ApplicationSuspended(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.application_suspended"),
        NSLOCTEXT("RedpointEOSAPI", "Error_ApplicationSuspended", "Application is suspended"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_ApplicationSuspended,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::ApplicationSuspended(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.application_suspended"),
        NSLOCTEXT("RedpointEOSAPI", "Error_ApplicationSuspended", "Application is suspended"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_ApplicationSuspended,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::NetworkDisconnected()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.network_disconnected"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NetworkDisconnected", "Network is disconnected"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NetworkDisconnected,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NetworkDisconnected(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.network_disconnected"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NetworkDisconnected", "Network is disconnected"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NetworkDisconnected,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::NetworkDisconnected(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.network_disconnected"),
        NSLOCTEXT("RedpointEOSAPI", "Error_NetworkDisconnected", "Network is disconnected"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_NetworkDisconnected,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AccessDenied()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.access_denied"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AccessDenied", "Failed due to invalid access"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AccessDenied,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AccessDenied(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.access_denied"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AccessDenied", "Failed due to invalid access"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AccessDenied,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AccessDenied(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.access_denied"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AccessDenied", "Failed due to invalid access"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AccessDenied,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::MissingPermissions()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.missing_permissions"),
        NSLOCTEXT("RedpointEOSAPI", "Error_MissingPermissions", "If the client does not possess the permission required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_MissingPermissions,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::MissingPermissions(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.missing_permissions"),
        NSLOCTEXT("RedpointEOSAPI", "Error_MissingPermissions", "If the client does not possess the permission required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_MissingPermissions,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::MissingPermissions(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.missing_permissions"),
        NSLOCTEXT("RedpointEOSAPI", "Error_MissingPermissions", "If the client does not possess the permission required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_MissingPermissions,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Token_Not_Account()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.token_not_account"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Token_Not_Account", "If the token provided does not represent an account"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Token_Not_Account,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Token_Not_Account(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.token_not_account"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Token_Not_Account", "If the token provided does not represent an account"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Token_Not_Account,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Token_Not_Account(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.token_not_account"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Token_Not_Account", "If the token provided does not represent an account"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Token_Not_Account,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::TooManyRequests()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.too_many_requests"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TooManyRequests", "Throttled due to too many requests"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TooManyRequests,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TooManyRequests(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.too_many_requests"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TooManyRequests", "Throttled due to too many requests"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TooManyRequests,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TooManyRequests(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.too_many_requests"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TooManyRequests", "Throttled due to too many requests"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TooManyRequests,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AlreadyPending()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.already_pending"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AlreadyPending", "Async request was already pending"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AlreadyPending,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AlreadyPending(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.already_pending"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AlreadyPending", "Async request was already pending"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AlreadyPending,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AlreadyPending(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.already_pending"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AlreadyPending", "Async request was already pending"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AlreadyPending,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::AccountLocked()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_locked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountLocked", "Account locked due to login failures"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountLocked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AccountLocked(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_locked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountLocked", "Account locked due to login failures"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountLocked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AccountLocked(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_locked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountLocked", "Account locked due to login failures"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountLocked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::AccountLockedForUpdate()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_locked_for_update"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountLockedForUpdate", "Account locked by update operation."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountLockedForUpdate,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AccountLockedForUpdate(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_locked_for_update"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountLockedForUpdate", "Account locked by update operation."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountLockedForUpdate,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AccountLockedForUpdate(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_locked_for_update"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountLockedForUpdate", "Account locked by update operation."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountLockedForUpdate,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::InvalidRefreshToken()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.invalid_refresh_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_InvalidRefreshToken", "Refresh token used was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_InvalidRefreshToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::InvalidRefreshToken(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.invalid_refresh_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_InvalidRefreshToken", "Refresh token used was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_InvalidRefreshToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::InvalidRefreshToken(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.invalid_refresh_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_InvalidRefreshToken", "Refresh token used was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_InvalidRefreshToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::InvalidToken()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.invalid_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_InvalidToken", "Invalid access token, typically when switching between backend environments"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_InvalidToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::InvalidToken(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.invalid_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_InvalidToken", "Invalid access token, typically when switching between backend environments"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_InvalidToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::InvalidToken(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.invalid_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_InvalidToken", "Invalid access token, typically when switching between backend environments"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_InvalidToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::AuthenticationFailure()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.authentication_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AuthenticationFailure", "Invalid bearer token"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AuthenticationFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AuthenticationFailure(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.authentication_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AuthenticationFailure", "Invalid bearer token"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AuthenticationFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AuthenticationFailure(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.authentication_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AuthenticationFailure", "Invalid bearer token"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AuthenticationFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::InvalidPlatformToken()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.invalid_platform_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_InvalidPlatformToken", "Invalid platform token"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_InvalidPlatformToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::InvalidPlatformToken(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.invalid_platform_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_InvalidPlatformToken", "Invalid platform token"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_InvalidPlatformToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::InvalidPlatformToken(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.invalid_platform_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_InvalidPlatformToken", "Invalid platform token"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_InvalidPlatformToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::WrongAccount()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.wrong_account"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_WrongAccount", "Auth parameters are not associated with this account"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_WrongAccount,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::WrongAccount(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.wrong_account"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_WrongAccount", "Auth parameters are not associated with this account"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_WrongAccount,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::WrongAccount(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.wrong_account"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_WrongAccount", "Auth parameters are not associated with this account"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_WrongAccount,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::WrongClient()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.wrong_client"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_WrongClient", "Auth parameters are not associated with this client"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_WrongClient,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::WrongClient(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.wrong_client"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_WrongClient", "Auth parameters are not associated with this client"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_WrongClient,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::WrongClient(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.wrong_client"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_WrongClient", "Auth parameters are not associated with this client"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_WrongClient,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::FullAccountRequired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.full_account_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_FullAccountRequired", "Full account is required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_FullAccountRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::FullAccountRequired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.full_account_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_FullAccountRequired", "Full account is required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_FullAccountRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::FullAccountRequired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.full_account_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_FullAccountRequired", "Full account is required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_FullAccountRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::HeadlessAccountRequired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.headless_account_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_HeadlessAccountRequired", "Headless account is required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_HeadlessAccountRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::HeadlessAccountRequired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.headless_account_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_HeadlessAccountRequired", "Headless account is required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_HeadlessAccountRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::HeadlessAccountRequired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.headless_account_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_HeadlessAccountRequired", "Headless account is required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_HeadlessAccountRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::PasswordResetRequired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.password_reset_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PasswordResetRequired", "Password reset is required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PasswordResetRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::PasswordResetRequired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.password_reset_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PasswordResetRequired", "Password reset is required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PasswordResetRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::PasswordResetRequired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.password_reset_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PasswordResetRequired", "Password reset is required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PasswordResetRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::PasswordCannotBeReused()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.password_cannot_be_reused"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PasswordCannotBeReused", "Password was previously used and cannot be reused"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PasswordCannotBeReused,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::PasswordCannotBeReused(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.password_cannot_be_reused"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PasswordCannotBeReused", "Password was previously used and cannot be reused"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PasswordCannotBeReused,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::PasswordCannotBeReused(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.password_cannot_be_reused"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PasswordCannotBeReused", "Password was previously used and cannot be reused"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PasswordCannotBeReused,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::Expired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_Expired", "Authorization code/exchange code has expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_Expired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::Expired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_Expired", "Authorization code/exchange code has expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_Expired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::Expired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_Expired", "Authorization code/exchange code has expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_Expired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ScopeConsentRequired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.scope_consent_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ScopeConsentRequired", "Consent has not been given by the user"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ScopeConsentRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ScopeConsentRequired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.scope_consent_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ScopeConsentRequired", "Consent has not been given by the user"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ScopeConsentRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ScopeConsentRequired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.scope_consent_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ScopeConsentRequired", "Consent has not been given by the user"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ScopeConsentRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ApplicationNotFound()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.application_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ApplicationNotFound", "The application has no profile on the backend"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ApplicationNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ApplicationNotFound(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.application_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ApplicationNotFound", "The application has no profile on the backend"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ApplicationNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ApplicationNotFound(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.application_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ApplicationNotFound", "The application has no profile on the backend"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ApplicationNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ScopeNotFound()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.scope_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ScopeNotFound", "The requested consent wasn't found on the backend"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ScopeNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ScopeNotFound(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.scope_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ScopeNotFound", "The requested consent wasn't found on the backend"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ScopeNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ScopeNotFound(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.scope_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ScopeNotFound", "The requested consent wasn't found on the backend"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ScopeNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::AccountFeatureRestricted()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_feature_restricted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountFeatureRestricted", "This account has been denied access to login"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountFeatureRestricted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AccountFeatureRestricted(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_feature_restricted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountFeatureRestricted", "This account has been denied access to login"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountFeatureRestricted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AccountFeatureRestricted(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_feature_restricted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountFeatureRestricted", "This account has been denied access to login"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountFeatureRestricted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::AccountPortalLoadError()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_portal_load_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountPortalLoadError", "The overlay failed to load the Account Portal. This can range from general overlay failure, to overlay failed to connect to the web server, to overlay failed to render the web page."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountPortalLoadError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AccountPortalLoadError(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_portal_load_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountPortalLoadError", "The overlay failed to load the Account Portal. This can range from general overlay failure, to overlay failed to connect to the web server, to overlay failed to render the web page."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountPortalLoadError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AccountPortalLoadError(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_portal_load_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountPortalLoadError", "The overlay failed to load the Account Portal. This can range from general overlay failure, to overlay failed to connect to the web server, to overlay failed to render the web page."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountPortalLoadError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::CorrectiveActionRequired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.corrective_action_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_CorrectiveActionRequired", "An attempted login has failed due to the user needing to take corrective action on their account."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_CorrectiveActionRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::CorrectiveActionRequired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.corrective_action_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_CorrectiveActionRequired", "An attempted login has failed due to the user needing to take corrective action on their account."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_CorrectiveActionRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::CorrectiveActionRequired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.corrective_action_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_CorrectiveActionRequired", "An attempted login has failed due to the user needing to take corrective action on their account."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_CorrectiveActionRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::PinGrantCode()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.pin_grant_code"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PinGrantCode", "Pin grant code initiated"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PinGrantCode,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::PinGrantCode(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.pin_grant_code"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PinGrantCode", "Pin grant code initiated"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PinGrantCode,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::PinGrantCode(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.pin_grant_code"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PinGrantCode", "Pin grant code initiated"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PinGrantCode,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::PinGrantExpired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.pin_grant_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PinGrantExpired", "Pin grant code attempt expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PinGrantExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::PinGrantExpired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.pin_grant_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PinGrantExpired", "Pin grant code attempt expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PinGrantExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::PinGrantExpired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.pin_grant_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PinGrantExpired", "Pin grant code attempt expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PinGrantExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::PinGrantPending()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.pin_grant_pending"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PinGrantPending", "Pin grant code attempt pending"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PinGrantPending,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::PinGrantPending(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.pin_grant_pending"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PinGrantPending", "Pin grant code attempt pending"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PinGrantPending,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::PinGrantPending(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.pin_grant_pending"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_PinGrantPending", "Pin grant code attempt pending"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_PinGrantPending,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ExternalAuthNotLinked()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_not_linked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthNotLinked", "External auth source did not yield an account"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthNotLinked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthNotLinked(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_not_linked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthNotLinked", "External auth source did not yield an account"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthNotLinked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthNotLinked(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_not_linked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthNotLinked", "External auth source did not yield an account"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthNotLinked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ExternalAuthRevoked()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_revoked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthRevoked", "External auth access revoked"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthRevoked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthRevoked(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_revoked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthRevoked", "External auth access revoked"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthRevoked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthRevoked(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_revoked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthRevoked", "External auth access revoked"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthRevoked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ExternalAuthInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthInvalid", "External auth token cannot be interpreted"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthInvalid", "External auth token cannot be interpreted"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthInvalid", "External auth token cannot be interpreted"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ExternalAuthRestricted()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_restricted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthRestricted", "External auth cannot be linked to his account due to restrictions"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthRestricted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthRestricted(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_restricted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthRestricted", "External auth cannot be linked to his account due to restrictions"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthRestricted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthRestricted(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_restricted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthRestricted", "External auth cannot be linked to his account due to restrictions"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthRestricted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ExternalAuthCannotLogin()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_cannot_login"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthCannotLogin", "External auth cannot be used for login"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthCannotLogin,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthCannotLogin(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_cannot_login"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthCannotLogin", "External auth cannot be used for login"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthCannotLogin,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthCannotLogin(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_cannot_login"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthCannotLogin", "External auth cannot be used for login"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthCannotLogin,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ExternalAuthExpired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthExpired", "External auth is expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthExpired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthExpired", "External auth is expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthExpired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthExpired", "External auth is expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ExternalAuthIsLastLoginType()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_is_last_login_type"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthIsLastLoginType", "External auth cannot be removed since it's the last possible way to login"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthIsLastLoginType,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthIsLastLoginType(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_is_last_login_type"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthIsLastLoginType", "External auth cannot be removed since it's the last possible way to login"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthIsLastLoginType,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExternalAuthIsLastLoginType(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.external_auth_is_last_login_type"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExternalAuthIsLastLoginType", "External auth cannot be removed since it's the last possible way to login"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExternalAuthIsLastLoginType,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ExchangeCodeNotFound()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.exchange_code_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExchangeCodeNotFound", "Exchange code not found"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExchangeCodeNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExchangeCodeNotFound(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.exchange_code_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExchangeCodeNotFound", "Exchange code not found"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExchangeCodeNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ExchangeCodeNotFound(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.exchange_code_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ExchangeCodeNotFound", "Exchange code not found"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ExchangeCodeNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::OriginatingExchangeCodeSessionExpired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.originating_exchange_code_session_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_OriginatingExchangeCodeSessionExpired", "Originating exchange code session has expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_OriginatingExchangeCodeSessionExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::OriginatingExchangeCodeSessionExpired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.originating_exchange_code_session_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_OriginatingExchangeCodeSessionExpired", "Originating exchange code session has expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_OriginatingExchangeCodeSessionExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::OriginatingExchangeCodeSessionExpired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.originating_exchange_code_session_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_OriginatingExchangeCodeSessionExpired", "Originating exchange code session has expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_OriginatingExchangeCodeSessionExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::AccountNotActive()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_not_active"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountNotActive", "The account has been disabled and cannot be used for authentication"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountNotActive,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AccountNotActive(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_not_active"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountNotActive", "The account has been disabled and cannot be used for authentication"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountNotActive,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::AccountNotActive(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.account_not_active"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_AccountNotActive", "The account has been disabled and cannot be used for authentication"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_AccountNotActive,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::MFARequired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.mfa_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_MFARequired", "MFA challenge required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_MFARequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::MFARequired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.mfa_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_MFARequired", "MFA challenge required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_MFARequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::MFARequired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.mfa_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_MFARequired", "MFA challenge required"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_MFARequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::ParentalControls()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.parental_controls"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ParentalControls", "Parental locks are in place"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ParentalControls,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ParentalControls(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.parental_controls"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ParentalControls", "Parental locks are in place"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ParentalControls,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::ParentalControls(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.parental_controls"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_ParentalControls", "Parental locks are in place"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_ParentalControls,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::NoRealId()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.no_real_id"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_NoRealId", "Korea real ID association required but missing"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_NoRealId,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::NoRealId(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.no_real_id"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_NoRealId", "Korea real ID association required but missing"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_NoRealId,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::NoRealId(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.no_real_id"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_NoRealId", "Korea real ID association required but missing"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Auth_NoRealId,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Auth::UserInterfaceRequired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.user_interface_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_UserInterfaceRequired", "Silent login failed when EOS_LF_NO_USER_INTERFACE was specified, and user interaction is needed before the user can be logged in."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_Auth_UserInterfaceRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::UserInterfaceRequired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.user_interface_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_UserInterfaceRequired", "Silent login failed when EOS_LF_NO_USER_INTERFACE was specified, and user interaction is needed before the user can be logged in."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_Auth_UserInterfaceRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Auth::UserInterfaceRequired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.auth.user_interface_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Auth_UserInterfaceRequired", "Silent login failed when EOS_LF_NO_USER_INTERFACE was specified, and user interaction is needed before the user can be logged in."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_Auth_UserInterfaceRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Friends::InviteAwaitingAcceptance()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.invite_awaiting_acceptance"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_InviteAwaitingAcceptance", "An outgoing friend invitation is awaiting acceptance; sending another invite to the same user is erroneous"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_InviteAwaitingAcceptance,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::InviteAwaitingAcceptance(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.invite_awaiting_acceptance"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_InviteAwaitingAcceptance", "An outgoing friend invitation is awaiting acceptance; sending another invite to the same user is erroneous"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_InviteAwaitingAcceptance,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::InviteAwaitingAcceptance(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.invite_awaiting_acceptance"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_InviteAwaitingAcceptance", "An outgoing friend invitation is awaiting acceptance; sending another invite to the same user is erroneous"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_InviteAwaitingAcceptance,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Friends::NoInvitation()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.no_invitation"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_NoInvitation", "There is no friend invitation to accept/reject"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_NoInvitation,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::NoInvitation(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.no_invitation"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_NoInvitation", "There is no friend invitation to accept/reject"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_NoInvitation,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::NoInvitation(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.no_invitation"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_NoInvitation", "There is no friend invitation to accept/reject"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_NoInvitation,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Friends::AlreadyFriends()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.already_friends"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_AlreadyFriends", "Users are already friends, so sending another invite is erroneous"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_AlreadyFriends,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::AlreadyFriends(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.already_friends"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_AlreadyFriends", "Users are already friends, so sending another invite is erroneous"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_AlreadyFriends,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::AlreadyFriends(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.already_friends"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_AlreadyFriends", "Users are already friends, so sending another invite is erroneous"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_AlreadyFriends,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Friends::NotFriends()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.not_friends"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_NotFriends", "Users are not friends, so deleting the friend is erroneous"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_NotFriends,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::NotFriends(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.not_friends"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_NotFriends", "Users are not friends, so deleting the friend is erroneous"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_NotFriends,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::NotFriends(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.not_friends"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_NotFriends", "Users are not friends, so deleting the friend is erroneous"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_NotFriends,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Friends::TargetUserTooManyInvites()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.target_user_too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_TargetUserTooManyInvites", "Remote user has too many invites to receive new invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_TargetUserTooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::TargetUserTooManyInvites(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.target_user_too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_TargetUserTooManyInvites", "Remote user has too many invites to receive new invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_TargetUserTooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::TargetUserTooManyInvites(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.target_user_too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_TargetUserTooManyInvites", "Remote user has too many invites to receive new invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_TargetUserTooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Friends::LocalUserTooManyInvites()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.local_user_too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_LocalUserTooManyInvites", "Local user has too many invites to send new invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_LocalUserTooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::LocalUserTooManyInvites(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.local_user_too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_LocalUserTooManyInvites", "Local user has too many invites to send new invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_LocalUserTooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::LocalUserTooManyInvites(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.local_user_too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_LocalUserTooManyInvites", "Local user has too many invites to send new invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_LocalUserTooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Friends::TargetUserFriendLimitExceeded()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.target_user_friend_limit_exceeded"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_TargetUserFriendLimitExceeded", "Remote user has too many friends to make a new friendship"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_TargetUserFriendLimitExceeded,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::TargetUserFriendLimitExceeded(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.target_user_friend_limit_exceeded"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_TargetUserFriendLimitExceeded", "Remote user has too many friends to make a new friendship"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_TargetUserFriendLimitExceeded,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::TargetUserFriendLimitExceeded(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.target_user_friend_limit_exceeded"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_TargetUserFriendLimitExceeded", "Remote user has too many friends to make a new friendship"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_TargetUserFriendLimitExceeded,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Friends::LocalUserFriendLimitExceeded()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.local_user_friend_limit_exceeded"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_LocalUserFriendLimitExceeded", "Local user has too many friends to make a new friendship"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_LocalUserFriendLimitExceeded,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::LocalUserFriendLimitExceeded(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.local_user_friend_limit_exceeded"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_LocalUserFriendLimitExceeded", "Local user has too many friends to make a new friendship"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_LocalUserFriendLimitExceeded,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Friends::LocalUserFriendLimitExceeded(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.friends.local_user_friend_limit_exceeded"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Friends_LocalUserFriendLimitExceeded", "Local user has too many friends to make a new friendship"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Friends_LocalUserFriendLimitExceeded,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Presence::DataInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataInvalid", "Request data was null or invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataInvalid", "Request data was null or invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataInvalid", "Request data was null or invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Presence::DataLengthInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataLengthInvalid", "Request contained too many or too few unique data items, or the request would overflow the maximum amount of data allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataLengthInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataLengthInvalid", "Request contained too many or too few unique data items, or the request would overflow the maximum amount of data allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataLengthInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataLengthInvalid", "Request contained too many or too few unique data items, or the request would overflow the maximum amount of data allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Presence::DataKeyInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_key_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataKeyInvalid", "Request contained data with an invalid key"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataKeyInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataKeyInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_key_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataKeyInvalid", "Request contained data with an invalid key"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataKeyInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataKeyInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_key_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataKeyInvalid", "Request contained data with an invalid key"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataKeyInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Presence::DataKeyLengthInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_key_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataKeyLengthInvalid", "Request contained data with a key too long or too short"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataKeyLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataKeyLengthInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_key_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataKeyLengthInvalid", "Request contained data with a key too long or too short"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataKeyLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataKeyLengthInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_key_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataKeyLengthInvalid", "Request contained data with a key too long or too short"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataKeyLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Presence::DataValueInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_value_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataValueInvalid", "Request contained data with an invalid value"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataValueInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataValueInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_value_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataValueInvalid", "Request contained data with an invalid value"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataValueInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataValueInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_value_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataValueInvalid", "Request contained data with an invalid value"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataValueInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Presence::DataValueLengthInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_value_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataValueLengthInvalid", "Request contained data with a value too long"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataValueLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataValueLengthInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_value_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataValueLengthInvalid", "Request contained data with a value too long"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataValueLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::DataValueLengthInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.data_value_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_DataValueLengthInvalid", "Request contained data with a value too long"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_DataValueLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Presence::RichTextInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.rich_text_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_RichTextInvalid", "Request contained an invalid rich text string"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_RichTextInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::RichTextInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.rich_text_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_RichTextInvalid", "Request contained an invalid rich text string"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_RichTextInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::RichTextInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.rich_text_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_RichTextInvalid", "Request contained an invalid rich text string"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_RichTextInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Presence::RichTextLengthInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.rich_text_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_RichTextLengthInvalid", "Request contained a rich text string that was too long"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_RichTextLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::RichTextLengthInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.rich_text_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_RichTextLengthInvalid", "Request contained a rich text string that was too long"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_RichTextLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::RichTextLengthInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.rich_text_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_RichTextLengthInvalid", "Request contained a rich text string that was too long"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_RichTextLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Presence::StatusInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.status_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_StatusInvalid", "Request contained an invalid status state"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_StatusInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::StatusInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.status_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_StatusInvalid", "Request contained an invalid status state"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_StatusInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Presence::StatusInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.presence.status_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Presence_StatusInvalid", "Request contained an invalid status state"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Presence_StatusInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Ecom::EntitlementStale()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.entitlement_stale"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_EntitlementStale", "The entitlement retrieved is stale, requery for updated information"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_EntitlementStale,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::EntitlementStale(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.entitlement_stale"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_EntitlementStale", "The entitlement retrieved is stale, requery for updated information"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_EntitlementStale,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::EntitlementStale(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.entitlement_stale"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_EntitlementStale", "The entitlement retrieved is stale, requery for updated information"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_EntitlementStale,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Ecom::CatalogOfferStale()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.catalog_offer_stale"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CatalogOfferStale", "The offer retrieved is stale, requery for updated information"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CatalogOfferStale,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::CatalogOfferStale(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.catalog_offer_stale"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CatalogOfferStale", "The offer retrieved is stale, requery for updated information"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CatalogOfferStale,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::CatalogOfferStale(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.catalog_offer_stale"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CatalogOfferStale", "The offer retrieved is stale, requery for updated information"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CatalogOfferStale,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Ecom::CatalogItemStale()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.catalog_item_stale"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CatalogItemStale", "The item or associated structure retrieved is stale, requery for updated information"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CatalogItemStale,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::CatalogItemStale(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.catalog_item_stale"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CatalogItemStale", "The item or associated structure retrieved is stale, requery for updated information"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CatalogItemStale,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::CatalogItemStale(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.catalog_item_stale"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CatalogItemStale", "The item or associated structure retrieved is stale, requery for updated information"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CatalogItemStale,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Ecom::CatalogOfferPriceInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.catalog_offer_price_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CatalogOfferPriceInvalid", "The one or more offers has an invalid price. This may be caused by the price setup."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CatalogOfferPriceInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::CatalogOfferPriceInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.catalog_offer_price_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CatalogOfferPriceInvalid", "The one or more offers has an invalid price. This may be caused by the price setup."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CatalogOfferPriceInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::CatalogOfferPriceInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.catalog_offer_price_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CatalogOfferPriceInvalid", "The one or more offers has an invalid price. This may be caused by the price setup."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CatalogOfferPriceInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Ecom::CheckoutLoadError()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.checkout_load_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CheckoutLoadError", "The checkout page failed to load"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CheckoutLoadError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::CheckoutLoadError(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.checkout_load_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CheckoutLoadError", "The checkout page failed to load"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CheckoutLoadError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::CheckoutLoadError(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.checkout_load_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_CheckoutLoadError", "The checkout page failed to load"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Ecom_CheckoutLoadError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Ecom::PurchaseProcessing()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.purchase_processing"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_PurchaseProcessing", "The player closed the purchase flow overlay after clicking the purchase button. The purchase may still go through, and the game needs to query unredeemed entitlements for a short time."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_Ecom_PurchaseProcessing,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::PurchaseProcessing(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.purchase_processing"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_PurchaseProcessing", "The player closed the purchase flow overlay after clicking the purchase button. The purchase may still go through, and the game needs to query unredeemed entitlements for a short time."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_Ecom_PurchaseProcessing,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Ecom::PurchaseProcessing(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ecom.purchase_processing"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Ecom_PurchaseProcessing", "The player closed the purchase flow overlay after clicking the purchase button. The purchase may still go through, and the game needs to query unredeemed entitlements for a short time."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_Ecom_PurchaseProcessing,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::SessionInProgress()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.session_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SessionInProgress", "Session is already in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SessionInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::SessionInProgress(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.session_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SessionInProgress", "Session is already in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SessionInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::SessionInProgress(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.session_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SessionInProgress", "Session is already in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SessionInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::TooManyPlayers()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.too_many_players"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_TooManyPlayers", "Too many players to register with this session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_TooManyPlayers,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::TooManyPlayers(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.too_many_players"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_TooManyPlayers", "Too many players to register with this session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_TooManyPlayers,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::TooManyPlayers(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.too_many_players"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_TooManyPlayers", "Too many players to register with this session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_TooManyPlayers,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::NoPermission()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.no_permission"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_NoPermission", "Client has no permissions to access this session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_NoPermission,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::NoPermission(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.no_permission"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_NoPermission", "Client has no permissions to access this session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_NoPermission,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::NoPermission(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.no_permission"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_NoPermission", "Client has no permissions to access this session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_NoPermission,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::SessionAlreadyExists()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.session_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SessionAlreadyExists", "Session already exists in the system"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SessionAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::SessionAlreadyExists(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.session_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SessionAlreadyExists", "Session already exists in the system"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SessionAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::SessionAlreadyExists(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.session_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SessionAlreadyExists", "Session already exists in the system"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SessionAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::InvalidLock()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invalid_lock"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InvalidLock", "Session lock required for operation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InvalidLock,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::InvalidLock(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invalid_lock"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InvalidLock", "Session lock required for operation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InvalidLock,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::InvalidLock(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invalid_lock"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InvalidLock", "Session lock required for operation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InvalidLock,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::InvalidSession()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invalid_session"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InvalidSession", "Invalid session reference"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InvalidSession,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::InvalidSession(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invalid_session"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InvalidSession", "Invalid session reference"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InvalidSession,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::InvalidSession(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invalid_session"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InvalidSession", "Invalid session reference"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InvalidSession,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::SandboxNotAllowed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.sandbox_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SandboxNotAllowed", "Sandbox ID associated with auth didn't match"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SandboxNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::SandboxNotAllowed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.sandbox_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SandboxNotAllowed", "Sandbox ID associated with auth didn't match"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SandboxNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::SandboxNotAllowed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.sandbox_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SandboxNotAllowed", "Sandbox ID associated with auth didn't match"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SandboxNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::InviteFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invite_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InviteFailed", "Invite failed to send"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InviteFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::InviteFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invite_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InviteFailed", "Invite failed to send"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InviteFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::InviteFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invite_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InviteFailed", "Invite failed to send"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InviteFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::InviteNotFound()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invite_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InviteNotFound", "Invite was not found with the service"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InviteNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::InviteNotFound(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invite_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InviteNotFound", "Invite was not found with the service"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InviteNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::InviteNotFound(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.invite_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_InviteNotFound", "Invite was not found with the service"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_InviteNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::UpsertNotAllowed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.upsert_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_UpsertNotAllowed", "This client may not modify the session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_UpsertNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::UpsertNotAllowed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.upsert_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_UpsertNotAllowed", "This client may not modify the session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_UpsertNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::UpsertNotAllowed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.upsert_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_UpsertNotAllowed", "This client may not modify the session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_UpsertNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::AggregationFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.aggregation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_AggregationFailed", "Backend nodes unavailable to process request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_AggregationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::AggregationFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.aggregation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_AggregationFailed", "Backend nodes unavailable to process request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_AggregationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::AggregationFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.aggregation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_AggregationFailed", "Backend nodes unavailable to process request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_AggregationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::HostAtCapacity()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.host_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_HostAtCapacity", "Individual backend node is as capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_HostAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::HostAtCapacity(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.host_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_HostAtCapacity", "Individual backend node is as capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_HostAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::HostAtCapacity(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.host_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_HostAtCapacity", "Individual backend node is as capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_HostAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::SandboxAtCapacity()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.sandbox_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SandboxAtCapacity", "Sandbox on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SandboxAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::SandboxAtCapacity(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.sandbox_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SandboxAtCapacity", "Sandbox on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SandboxAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::SandboxAtCapacity(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.sandbox_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SandboxAtCapacity", "Sandbox on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SandboxAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::SessionNotAnonymous()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.session_not_anonymous"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SessionNotAnonymous", "An anonymous operation was attempted on a non anonymous session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SessionNotAnonymous,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::SessionNotAnonymous(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.session_not_anonymous"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SessionNotAnonymous", "An anonymous operation was attempted on a non anonymous session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SessionNotAnonymous,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::SessionNotAnonymous(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.session_not_anonymous"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_SessionNotAnonymous", "An anonymous operation was attempted on a non anonymous session"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_SessionNotAnonymous,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::OutOfSync()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.out_of_sync"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_OutOfSync", "Session is currently out of sync with the backend, data is saved locally but needs to sync with backend"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_OutOfSync,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::OutOfSync(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.out_of_sync"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_OutOfSync", "Session is currently out of sync with the backend, data is saved locally but needs to sync with backend"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_OutOfSync,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::OutOfSync(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.out_of_sync"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_OutOfSync", "Session is currently out of sync with the backend, data is saved locally but needs to sync with backend"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_OutOfSync,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::TooManyInvites()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_TooManyInvites", "User has received too many invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_TooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::TooManyInvites(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_TooManyInvites", "User has received too many invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_TooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::TooManyInvites(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_TooManyInvites", "User has received too many invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_TooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::PresenceSessionExists()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.presence_session_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_PresenceSessionExists", "Presence session already exists for the client"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_PresenceSessionExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::PresenceSessionExists(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.presence_session_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_PresenceSessionExists", "Presence session already exists for the client"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_PresenceSessionExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::PresenceSessionExists(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.presence_session_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_PresenceSessionExists", "Presence session already exists for the client"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_PresenceSessionExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::DeploymentAtCapacity()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.deployment_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_DeploymentAtCapacity", "Deployment on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_DeploymentAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::DeploymentAtCapacity(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.deployment_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_DeploymentAtCapacity", "Deployment on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_DeploymentAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::DeploymentAtCapacity(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.deployment_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_DeploymentAtCapacity", "Deployment on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_DeploymentAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::NotAllowed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_NotAllowed", "Session operation not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_NotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::NotAllowed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_NotAllowed", "Session operation not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_NotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::NotAllowed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_NotAllowed", "Session operation not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_NotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Sessions::PlayerSanctioned()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.player_sanctioned"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_PlayerSanctioned", "Session operation not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_PlayerSanctioned,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::PlayerSanctioned(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.player_sanctioned"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_PlayerSanctioned", "Session operation not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_PlayerSanctioned,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Sessions::PlayerSanctioned(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.sessions.player_sanctioned"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Sessions_PlayerSanctioned", "Session operation not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Sessions_PlayerSanctioned,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.filename_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FilenameInvalid", "Request filename was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FilenameInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.filename_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FilenameInvalid", "Request filename was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FilenameInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.filename_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FilenameInvalid", "Request filename was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FilenameInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameLengthInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.filename_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FilenameLengthInvalid", "Request filename was too long"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FilenameLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameLengthInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.filename_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FilenameLengthInvalid", "Request filename was too long"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FilenameLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameLengthInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.filename_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FilenameLengthInvalid", "Request filename was too long"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FilenameLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalidChars()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.filename_invalid_chars"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FilenameInvalidChars", "Request filename contained invalid characters"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FilenameInvalidChars,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalidChars(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.filename_invalid_chars"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FilenameInvalidChars", "Request filename contained invalid characters"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FilenameInvalidChars,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalidChars(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.filename_invalid_chars"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FilenameInvalidChars", "Request filename contained invalid characters"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FilenameInvalidChars,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeTooLarge()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_size_too_large"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileSizeTooLarge", "Request operation would grow file too large"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileSizeTooLarge,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeTooLarge(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_size_too_large"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileSizeTooLarge", "Request operation would grow file too large"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileSizeTooLarge,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeTooLarge(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_size_too_large"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileSizeTooLarge", "Request operation would grow file too large"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileSizeTooLarge,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_size_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileSizeInvalid", "Request file length is not valid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileSizeInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_size_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileSizeInvalid", "Request file length is not valid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileSizeInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_size_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileSizeInvalid", "Request file length is not valid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileSizeInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::FileHandleInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_handle_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileHandleInvalid", "Request file handle is not valid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileHandleInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FileHandleInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_handle_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileHandleInvalid", "Request file handle is not valid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileHandleInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FileHandleInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_handle_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileHandleInvalid", "Request file handle is not valid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileHandleInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::DataInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.data_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_DataInvalid", "Request data is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_DataInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::DataInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.data_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_DataInvalid", "Request data is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_DataInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::DataInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.data_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_DataInvalid", "Request data is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_DataInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::DataLengthInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.data_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_DataLengthInvalid", "Request data length was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_DataLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::DataLengthInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.data_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_DataLengthInvalid", "Request data length was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_DataLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::DataLengthInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.data_length_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_DataLengthInvalid", "Request data length was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_DataLengthInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::StartIndexInvalid()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.start_index_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_StartIndexInvalid", "Request start index was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_StartIndexInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::StartIndexInvalid(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.start_index_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_StartIndexInvalid", "Request start index was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_StartIndexInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::StartIndexInvalid(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.start_index_invalid"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_StartIndexInvalid", "Request start index was invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_StartIndexInvalid,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::RequestInProgress()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.request_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_RequestInProgress", "Request is in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_RequestInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::RequestInProgress(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.request_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_RequestInProgress", "Request is in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_RequestInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::RequestInProgress(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.request_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_RequestInProgress", "Request is in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_RequestInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::UserThrottled()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.user_throttled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_UserThrottled", "User is marked as throttled which means he can't perform some operations because limits are exceeded."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_UserThrottled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::UserThrottled(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.user_throttled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_UserThrottled", "User is marked as throttled which means he can't perform some operations because limits are exceeded."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_UserThrottled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::UserThrottled(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.user_throttled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_UserThrottled", "User is marked as throttled which means he can't perform some operations because limits are exceeded."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_UserThrottled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::EncryptionKeyNotSet()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.encryption_key_not_set"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_EncryptionKeyNotSet", "Encryption key is not set during SDK init."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_EncryptionKeyNotSet,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::EncryptionKeyNotSet(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.encryption_key_not_set"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_EncryptionKeyNotSet", "Encryption key is not set during SDK init."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_EncryptionKeyNotSet,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::EncryptionKeyNotSet(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.encryption_key_not_set"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_EncryptionKeyNotSet", "Encryption key is not set during SDK init."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_EncryptionKeyNotSet,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::UserErrorFromDataCallback()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.user_error_from_data_callback"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_UserErrorFromDataCallback", "User data callback returned error (EOS_PlayerDataStorage_EWriteResult::EOS_WR_FailRequest or EOS_PlayerDataStorage_EReadResult::EOS_RR_FailRequest)"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_UserErrorFromDataCallback,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::UserErrorFromDataCallback(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.user_error_from_data_callback"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_UserErrorFromDataCallback", "User data callback returned error (EOS_PlayerDataStorage_EWriteResult::EOS_WR_FailRequest or EOS_PlayerDataStorage_EReadResult::EOS_RR_FailRequest)"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_UserErrorFromDataCallback,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::UserErrorFromDataCallback(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.user_error_from_data_callback"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_UserErrorFromDataCallback", "User data callback returned error (EOS_PlayerDataStorage_EWriteResult::EOS_WR_FailRequest or EOS_PlayerDataStorage_EReadResult::EOS_RR_FailRequest)"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_UserErrorFromDataCallback,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::FileHeaderHasNewerVersion()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_header_has_newer_version"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileHeaderHasNewerVersion", "User is trying to read file that has header from newer version of SDK. Game/SDK needs to be updated."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileHeaderHasNewerVersion,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FileHeaderHasNewerVersion(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_header_has_newer_version"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileHeaderHasNewerVersion", "User is trying to read file that has header from newer version of SDK. Game/SDK needs to be updated."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileHeaderHasNewerVersion,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FileHeaderHasNewerVersion(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_header_has_newer_version"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileHeaderHasNewerVersion", "User is trying to read file that has header from newer version of SDK. Game/SDK needs to be updated."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileHeaderHasNewerVersion,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::PlayerDataStorage::FileCorrupted()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_corrupted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileCorrupted", "The file is corrupted. In some cases retry can fix the issue."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileCorrupted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FileCorrupted(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_corrupted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileCorrupted", "The file is corrupted. In some cases retry can fix the issue."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileCorrupted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::PlayerDataStorage::FileCorrupted(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.playerdatastorage.file_corrupted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_PlayerDataStorage_FileCorrupted", "The file is corrupted. In some cases retry can fix the issue."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_PlayerDataStorage_FileCorrupted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Connect::ExternalTokenValidationFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.external_token_validation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_ExternalTokenValidationFailed", "EOS Auth service deemed the external token invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_ExternalTokenValidationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::ExternalTokenValidationFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.external_token_validation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_ExternalTokenValidationFailed", "EOS Auth service deemed the external token invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_ExternalTokenValidationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::ExternalTokenValidationFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.external_token_validation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_ExternalTokenValidationFailed", "EOS Auth service deemed the external token invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_ExternalTokenValidationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Connect::UserAlreadyExists()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.user_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_UserAlreadyExists", "EOS Auth user already exists"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_UserAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::UserAlreadyExists(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.user_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_UserAlreadyExists", "EOS Auth user already exists"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_UserAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::UserAlreadyExists(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.user_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_UserAlreadyExists", "EOS Auth user already exists"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_UserAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Connect::AuthExpired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.auth_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_AuthExpired", "EOS Auth expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_AuthExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::AuthExpired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.auth_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_AuthExpired", "EOS Auth expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_AuthExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::AuthExpired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.auth_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_AuthExpired", "EOS Auth expired"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_AuthExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Connect::InvalidToken()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.invalid_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_InvalidToken", "EOS Auth invalid token"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_InvalidToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::InvalidToken(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.invalid_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_InvalidToken", "EOS Auth invalid token"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_InvalidToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::InvalidToken(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.invalid_token"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_InvalidToken", "EOS Auth invalid token"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_InvalidToken,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Connect::UnsupportedTokenType()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.unsupported_token_type"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_UnsupportedTokenType", "EOS Auth doesn't support this token type"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_UnsupportedTokenType,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::UnsupportedTokenType(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.unsupported_token_type"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_UnsupportedTokenType", "EOS Auth doesn't support this token type"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_UnsupportedTokenType,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::UnsupportedTokenType(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.unsupported_token_type"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_UnsupportedTokenType", "EOS Auth doesn't support this token type"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_UnsupportedTokenType,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Connect::LinkAccountFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.link_account_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_LinkAccountFailed", "EOS Auth Account link failure"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_LinkAccountFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::LinkAccountFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.link_account_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_LinkAccountFailed", "EOS Auth Account link failure"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_LinkAccountFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::LinkAccountFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.link_account_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_LinkAccountFailed", "EOS Auth Account link failure"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_LinkAccountFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Connect::ExternalServiceUnavailable()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.external_service_unavailable"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_ExternalServiceUnavailable", "EOS Auth External service for validation was unavailable"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_ExternalServiceUnavailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::ExternalServiceUnavailable(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.external_service_unavailable"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_ExternalServiceUnavailable", "EOS Auth External service for validation was unavailable"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_ExternalServiceUnavailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::ExternalServiceUnavailable(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.external_service_unavailable"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_ExternalServiceUnavailable", "EOS Auth External service for validation was unavailable"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_ExternalServiceUnavailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Connect::ExternalServiceConfigurationFailure()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.external_service_configuration_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_ExternalServiceConfigurationFailure", "EOS Auth External Service configuration failure with Dev Portal"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_ExternalServiceConfigurationFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::ExternalServiceConfigurationFailure(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.external_service_configuration_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_ExternalServiceConfigurationFailure", "EOS Auth External Service configuration failure with Dev Portal"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_ExternalServiceConfigurationFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Connect::ExternalServiceConfigurationFailure(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.connect.external_service_configuration_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Connect_ExternalServiceConfigurationFailure", "EOS Auth External Service configuration failure with Dev Portal"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Connect_ExternalServiceConfigurationFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::UI::SocialOverlayLoadError()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ui.social_overlay_load_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UI_SocialOverlayLoadError", "The social overlay page failed to load"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_UI_SocialOverlayLoadError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::UI::SocialOverlayLoadError(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ui.social_overlay_load_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UI_SocialOverlayLoadError", "The social overlay page failed to load"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_UI_SocialOverlayLoadError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::UI::SocialOverlayLoadError(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.ui.social_overlay_load_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_UI_SocialOverlayLoadError", "The social overlay page failed to load"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_UI_SocialOverlayLoadError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::NotOwner()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.not_owner"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_NotOwner", "Client has no permissions to modify this lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_NotOwner,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::NotOwner(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.not_owner"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_NotOwner", "Client has no permissions to modify this lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_NotOwner,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::NotOwner(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.not_owner"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_NotOwner", "Client has no permissions to modify this lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_NotOwner,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::InvalidLock()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invalid_lock"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InvalidLock", "Lobby lock required for operation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InvalidLock,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::InvalidLock(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invalid_lock"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InvalidLock", "Lobby lock required for operation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InvalidLock,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::InvalidLock(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invalid_lock"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InvalidLock", "Lobby lock required for operation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InvalidLock,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::LobbyAlreadyExists()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.lobby_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_LobbyAlreadyExists", "Lobby already exists in the system"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_LobbyAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::LobbyAlreadyExists(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.lobby_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_LobbyAlreadyExists", "Lobby already exists in the system"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_LobbyAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::LobbyAlreadyExists(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.lobby_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_LobbyAlreadyExists", "Lobby already exists in the system"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_LobbyAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::SessionInProgress()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.session_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_SessionInProgress", "Lobby is already in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_SessionInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::SessionInProgress(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.session_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_SessionInProgress", "Lobby is already in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_SessionInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::SessionInProgress(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.session_in_progress"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_SessionInProgress", "Lobby is already in progress"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_SessionInProgress,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::TooManyPlayers()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.too_many_players"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_TooManyPlayers", "Too many players to register with this lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_TooManyPlayers,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::TooManyPlayers(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.too_many_players"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_TooManyPlayers", "Too many players to register with this lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_TooManyPlayers,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::TooManyPlayers(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.too_many_players"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_TooManyPlayers", "Too many players to register with this lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_TooManyPlayers,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::NoPermission()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.no_permission"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_NoPermission", "Client has no permissions to access this lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_NoPermission,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::NoPermission(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.no_permission"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_NoPermission", "Client has no permissions to access this lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_NoPermission,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::NoPermission(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.no_permission"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_NoPermission", "Client has no permissions to access this lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_NoPermission,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::InvalidSession()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invalid_session"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InvalidSession", "Invalid lobby session reference"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InvalidSession,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::InvalidSession(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invalid_session"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InvalidSession", "Invalid lobby session reference"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InvalidSession,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::InvalidSession(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invalid_session"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InvalidSession", "Invalid lobby session reference"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InvalidSession,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::SandboxNotAllowed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.sandbox_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_SandboxNotAllowed", "Sandbox ID associated with auth didn't match"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_SandboxNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::SandboxNotAllowed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.sandbox_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_SandboxNotAllowed", "Sandbox ID associated with auth didn't match"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_SandboxNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::SandboxNotAllowed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.sandbox_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_SandboxNotAllowed", "Sandbox ID associated with auth didn't match"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_SandboxNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::InviteFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invite_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InviteFailed", "Invite failed to send"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InviteFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::InviteFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invite_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InviteFailed", "Invite failed to send"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InviteFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::InviteFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invite_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InviteFailed", "Invite failed to send"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InviteFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::InviteNotFound()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invite_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InviteNotFound", "Invite was not found with the service"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InviteNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::InviteNotFound(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invite_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InviteNotFound", "Invite was not found with the service"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InviteNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::InviteNotFound(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.invite_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_InviteNotFound", "Invite was not found with the service"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_InviteNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::UpsertNotAllowed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.upsert_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_UpsertNotAllowed", "This client may not modify the lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_UpsertNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::UpsertNotAllowed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.upsert_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_UpsertNotAllowed", "This client may not modify the lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_UpsertNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::UpsertNotAllowed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.upsert_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_UpsertNotAllowed", "This client may not modify the lobby"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_UpsertNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::AggregationFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.aggregation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_AggregationFailed", "Backend nodes unavailable to process request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_AggregationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::AggregationFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.aggregation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_AggregationFailed", "Backend nodes unavailable to process request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_AggregationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::AggregationFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.aggregation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_AggregationFailed", "Backend nodes unavailable to process request"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_AggregationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::HostAtCapacity()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.host_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_HostAtCapacity", "Individual backend node is as capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_HostAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::HostAtCapacity(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.host_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_HostAtCapacity", "Individual backend node is as capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_HostAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::HostAtCapacity(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.host_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_HostAtCapacity", "Individual backend node is as capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_HostAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::SandboxAtCapacity()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.sandbox_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_SandboxAtCapacity", "Sandbox on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_SandboxAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::SandboxAtCapacity(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.sandbox_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_SandboxAtCapacity", "Sandbox on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_SandboxAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::SandboxAtCapacity(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.sandbox_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_SandboxAtCapacity", "Sandbox on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_SandboxAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::TooManyInvites()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_TooManyInvites", "User has received too many invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_TooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::TooManyInvites(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_TooManyInvites", "User has received too many invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_TooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::TooManyInvites(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.too_many_invites"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_TooManyInvites", "User has received too many invites"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_TooManyInvites,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::DeploymentAtCapacity()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.deployment_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_DeploymentAtCapacity", "Deployment on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_DeploymentAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::DeploymentAtCapacity(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.deployment_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_DeploymentAtCapacity", "Deployment on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_DeploymentAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::DeploymentAtCapacity(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.deployment_at_capacity"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_DeploymentAtCapacity", "Deployment on node is at capacity"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_DeploymentAtCapacity,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::NotAllowed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_NotAllowed", "Lobby operation not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_NotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::NotAllowed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_NotAllowed", "Lobby operation not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_NotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::NotAllowed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_NotAllowed", "Lobby operation not allowed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_NotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::MemberUpdateOnly()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.member_update_only"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_MemberUpdateOnly", "While restoring a lost connection lobby ownership changed and only local member data was updated"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_MemberUpdateOnly,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::MemberUpdateOnly(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.member_update_only"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_MemberUpdateOnly", "While restoring a lost connection lobby ownership changed and only local member data was updated"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_MemberUpdateOnly,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::MemberUpdateOnly(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.member_update_only"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_MemberUpdateOnly", "While restoring a lost connection lobby ownership changed and only local member data was updated"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_MemberUpdateOnly,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::PresenceLobbyExists()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.presence_lobby_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_PresenceLobbyExists", "Presence lobby already exists for the client"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_PresenceLobbyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::PresenceLobbyExists(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.presence_lobby_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_PresenceLobbyExists", "Presence lobby already exists for the client"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_PresenceLobbyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::PresenceLobbyExists(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.presence_lobby_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_PresenceLobbyExists", "Presence lobby already exists for the client"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_PresenceLobbyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::VoiceNotEnabled()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.voice_not_enabled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_VoiceNotEnabled", "Operation requires lobby with voice enabled"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_VoiceNotEnabled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::VoiceNotEnabled(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.voice_not_enabled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_VoiceNotEnabled", "Operation requires lobby with voice enabled"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_VoiceNotEnabled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::VoiceNotEnabled(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.voice_not_enabled"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_VoiceNotEnabled", "Operation requires lobby with voice enabled"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Lobby_VoiceNotEnabled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Lobby::PlatformNotAllowed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.platform_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_PlatformNotAllowed", "The client platform does not match the allowed platform list for the lobby."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_Lobby_PlatformNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::PlatformNotAllowed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.platform_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_PlatformNotAllowed", "The client platform does not match the allowed platform list for the lobby."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_Lobby_PlatformNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Lobby::PlatformNotAllowed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.lobby.platform_not_allowed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Lobby_PlatformNotAllowed", "The client platform does not match the allowed platform list for the lobby."),
#if EOS_VERSION_AT_LEAST(1, 16, 0)
        EOS_EResult::EOS_Lobby_PlatformNotAllowed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::TitleStorage::UserErrorFromDataCallback()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.user_error_from_data_callback"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_UserErrorFromDataCallback", "User callback that receives data from storage returned error."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_UserErrorFromDataCallback,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TitleStorage::UserErrorFromDataCallback(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.user_error_from_data_callback"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_UserErrorFromDataCallback", "User callback that receives data from storage returned error."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_UserErrorFromDataCallback,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TitleStorage::UserErrorFromDataCallback(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.user_error_from_data_callback"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_UserErrorFromDataCallback", "User callback that receives data from storage returned error."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_UserErrorFromDataCallback,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::TitleStorage::EncryptionKeyNotSet()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.encryption_key_not_set"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_EncryptionKeyNotSet", "User forgot to set Encryption key during platform init. Title Storage can't work without it."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_EncryptionKeyNotSet,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TitleStorage::EncryptionKeyNotSet(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.encryption_key_not_set"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_EncryptionKeyNotSet", "User forgot to set Encryption key during platform init. Title Storage can't work without it."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_EncryptionKeyNotSet,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TitleStorage::EncryptionKeyNotSet(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.encryption_key_not_set"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_EncryptionKeyNotSet", "User forgot to set Encryption key during platform init. Title Storage can't work without it."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_EncryptionKeyNotSet,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::TitleStorage::FileCorrupted()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.file_corrupted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_FileCorrupted", "Downloaded file is corrupted."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_FileCorrupted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TitleStorage::FileCorrupted(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.file_corrupted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_FileCorrupted", "Downloaded file is corrupted."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_FileCorrupted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TitleStorage::FileCorrupted(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.file_corrupted"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_FileCorrupted", "Downloaded file is corrupted."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_FileCorrupted,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::TitleStorage::FileHeaderHasNewerVersion()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.file_header_has_newer_version"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_FileHeaderHasNewerVersion", "Downloaded file's format is newer than client SDK version."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_FileHeaderHasNewerVersion,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TitleStorage::FileHeaderHasNewerVersion(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.file_header_has_newer_version"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_FileHeaderHasNewerVersion", "Downloaded file's format is newer than client SDK version."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_FileHeaderHasNewerVersion,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::TitleStorage::FileHeaderHasNewerVersion(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.titlestorage.file_header_has_newer_version"),
        NSLOCTEXT("RedpointEOSAPI", "Error_TitleStorage_FileHeaderHasNewerVersion", "Downloaded file's format is newer than client SDK version."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_TitleStorage_FileHeaderHasNewerVersion,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::ModSdkProcessIsAlreadyRunning()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_sdk_process_is_already_running"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModSdkProcessIsAlreadyRunning", "ModSdk process is already running. This error comes from the EOSSDK."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModSdkProcessIsAlreadyRunning,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::ModSdkProcessIsAlreadyRunning(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_sdk_process_is_already_running"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModSdkProcessIsAlreadyRunning", "ModSdk process is already running. This error comes from the EOSSDK."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModSdkProcessIsAlreadyRunning,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::ModSdkProcessIsAlreadyRunning(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_sdk_process_is_already_running"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModSdkProcessIsAlreadyRunning", "ModSdk process is already running. This error comes from the EOSSDK."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModSdkProcessIsAlreadyRunning,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::ModSdkCommandIsEmpty()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_sdk_command_is_empty"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModSdkCommandIsEmpty", "ModSdk command is empty. Either the ModSdk configuration file is missing or the manifest location is empty."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModSdkCommandIsEmpty,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::ModSdkCommandIsEmpty(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_sdk_command_is_empty"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModSdkCommandIsEmpty", "ModSdk command is empty. Either the ModSdk configuration file is missing or the manifest location is empty."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModSdkCommandIsEmpty,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::ModSdkCommandIsEmpty(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_sdk_command_is_empty"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModSdkCommandIsEmpty", "ModSdk command is empty. Either the ModSdk configuration file is missing or the manifest location is empty."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModSdkCommandIsEmpty,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::ModSdkProcessCreationFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_sdk_process_creation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModSdkProcessCreationFailed", "Creation of the ModSdk process failed. This error comes from the SDK."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModSdkProcessCreationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::ModSdkProcessCreationFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_sdk_process_creation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModSdkProcessCreationFailed", "Creation of the ModSdk process failed. This error comes from the SDK."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModSdkProcessCreationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::ModSdkProcessCreationFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_sdk_process_creation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModSdkProcessCreationFailed", "Creation of the ModSdk process failed. This error comes from the SDK."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModSdkProcessCreationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::CriticalError()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.critical_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_CriticalError", "A critical error occurred in the external ModSdk process that we were unable to resolve."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_CriticalError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::CriticalError(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.critical_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_CriticalError", "A critical error occurred in the external ModSdk process that we were unable to resolve."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_CriticalError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::CriticalError(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.critical_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_CriticalError", "A critical error occurred in the external ModSdk process that we were unable to resolve."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_CriticalError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::ToolInternalError()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.tool_internal_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ToolInternalError", "A internal error occurred in the external ModSdk process that we were unable to resolve."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ToolInternalError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::ToolInternalError(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.tool_internal_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ToolInternalError", "A internal error occurred in the external ModSdk process that we were unable to resolve."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ToolInternalError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::ToolInternalError(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.tool_internal_error"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ToolInternalError", "A internal error occurred in the external ModSdk process that we were unable to resolve."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ToolInternalError,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::IPCFailure()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.ipc_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_IPCFailure", "A IPC failure occurred in the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_IPCFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::IPCFailure(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.ipc_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_IPCFailure", "A IPC failure occurred in the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_IPCFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::IPCFailure(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.ipc_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_IPCFailure", "A IPC failure occurred in the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_IPCFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::InvalidIPCResponse()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.invalid_ipc_response"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_InvalidIPCResponse", "A invalid IPC response received in the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_InvalidIPCResponse,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::InvalidIPCResponse(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.invalid_ipc_response"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_InvalidIPCResponse", "A invalid IPC response received in the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_InvalidIPCResponse,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::InvalidIPCResponse(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.invalid_ipc_response"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_InvalidIPCResponse", "A invalid IPC response received in the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_InvalidIPCResponse,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::URILaunchFailure()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.uri_launch_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_URILaunchFailure", "A URI Launch failure occurred in the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_URILaunchFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::URILaunchFailure(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.uri_launch_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_URILaunchFailure", "A URI Launch failure occurred in the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_URILaunchFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::URILaunchFailure(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.uri_launch_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_URILaunchFailure", "A URI Launch failure occurred in the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_URILaunchFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::ModIsNotInstalled()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_is_not_installed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModIsNotInstalled", "Attempting to perform an action with a mod that is not installed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModIsNotInstalled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::ModIsNotInstalled(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_is_not_installed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModIsNotInstalled", "Attempting to perform an action with a mod that is not installed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModIsNotInstalled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::ModIsNotInstalled(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.mod_is_not_installed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_ModIsNotInstalled", "Attempting to perform an action with a mod that is not installed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_ModIsNotInstalled,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::UserDoesNotOwnTheGame()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.user_does_not_own_the_game"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_UserDoesNotOwnTheGame", "Attempting to perform an action on a game that the user doesn't own. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_UserDoesNotOwnTheGame,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::UserDoesNotOwnTheGame(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.user_does_not_own_the_game"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_UserDoesNotOwnTheGame", "Attempting to perform an action on a game that the user doesn't own. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_UserDoesNotOwnTheGame,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::UserDoesNotOwnTheGame(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.user_does_not_own_the_game"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_UserDoesNotOwnTheGame", "Attempting to perform an action on a game that the user doesn't own. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_UserDoesNotOwnTheGame,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::OfferRequestByIdInvalidResult()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.offer_request_by_id_invalid_result"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_OfferRequestByIdInvalidResult", "Invalid result of the request to get the offer for the mod. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_OfferRequestByIdInvalidResult,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::OfferRequestByIdInvalidResult(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.offer_request_by_id_invalid_result"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_OfferRequestByIdInvalidResult", "Invalid result of the request to get the offer for the mod. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_OfferRequestByIdInvalidResult,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::OfferRequestByIdInvalidResult(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.offer_request_by_id_invalid_result"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_OfferRequestByIdInvalidResult", "Invalid result of the request to get the offer for the mod. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_OfferRequestByIdInvalidResult,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::CouldNotFindOffer()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.could_not_find_offer"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_CouldNotFindOffer", "Could not find the offer for the mod. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_CouldNotFindOffer,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::CouldNotFindOffer(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.could_not_find_offer"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_CouldNotFindOffer", "Could not find the offer for the mod. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_CouldNotFindOffer,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::CouldNotFindOffer(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.could_not_find_offer"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_CouldNotFindOffer", "Could not find the offer for the mod. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_CouldNotFindOffer,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::OfferRequestByIdFailure()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.offer_request_by_id_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_OfferRequestByIdFailure", "Request to get the offer for the mod failed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_OfferRequestByIdFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::OfferRequestByIdFailure(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.offer_request_by_id_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_OfferRequestByIdFailure", "Request to get the offer for the mod failed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_OfferRequestByIdFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::OfferRequestByIdFailure(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.offer_request_by_id_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_OfferRequestByIdFailure", "Request to get the offer for the mod failed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_OfferRequestByIdFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::PurchaseFailure()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.purchase_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_PurchaseFailure", "Request to purchase the mod failed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_PurchaseFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::PurchaseFailure(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.purchase_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_PurchaseFailure", "Request to purchase the mod failed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_PurchaseFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::PurchaseFailure(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.purchase_failure"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_PurchaseFailure", "Request to purchase the mod failed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_PurchaseFailure,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::InvalidGameInstallInfo()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.invalid_game_install_info"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_InvalidGameInstallInfo", "Attempting to perform an action on a game that is not installed or is partially installed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_InvalidGameInstallInfo,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::InvalidGameInstallInfo(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.invalid_game_install_info"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_InvalidGameInstallInfo", "Attempting to perform an action on a game that is not installed or is partially installed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_InvalidGameInstallInfo,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::InvalidGameInstallInfo(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.invalid_game_install_info"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_InvalidGameInstallInfo", "Attempting to perform an action on a game that is not installed or is partially installed. This error comes from the external ModSdk process."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_InvalidGameInstallInfo,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::CannotGetManifestLocation()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.cannot_get_manifest_location"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_CannotGetManifestLocation", "Failed to get manifest location. Either the ModSdk configuration file is missing or the manifest location is empty"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_CannotGetManifestLocation,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::CannotGetManifestLocation(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.cannot_get_manifest_location"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_CannotGetManifestLocation", "Failed to get manifest location. Either the ModSdk configuration file is missing or the manifest location is empty"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_CannotGetManifestLocation,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::CannotGetManifestLocation(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.cannot_get_manifest_location"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_CannotGetManifestLocation", "Failed to get manifest location. Either the ModSdk configuration file is missing or the manifest location is empty"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_CannotGetManifestLocation,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Mods::UnsupportedOS()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.unsupported_os"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_UnsupportedOS", "Attempting to perform an action with a mod that does not support the current operating system."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_UnsupportedOS,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::UnsupportedOS(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.unsupported_os"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_UnsupportedOS", "Attempting to perform an action with a mod that does not support the current operating system."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_UnsupportedOS,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Mods::UnsupportedOS(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.mods.unsupported_os"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Mods_UnsupportedOS", "Attempting to perform an action with a mod that does not support the current operating system."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Mods_UnsupportedOS,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::ClientProtectionNotAvailable()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_protection_not_available"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientProtectionNotAvailable", "The anti-cheat client protection is not available. Check that the game was started using the anti-cheat bootstrapper."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientProtectionNotAvailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ClientProtectionNotAvailable(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_protection_not_available"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientProtectionNotAvailable", "The anti-cheat client protection is not available. Check that the game was started using the anti-cheat bootstrapper."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientProtectionNotAvailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ClientProtectionNotAvailable(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_protection_not_available"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientProtectionNotAvailable", "The anti-cheat client protection is not available. Check that the game was started using the anti-cheat bootstrapper."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientProtectionNotAvailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::InvalidMode()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.invalid_mode"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_InvalidMode", "The current anti-cheat mode is incorrect for using this API"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_InvalidMode,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::InvalidMode(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.invalid_mode"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_InvalidMode", "The current anti-cheat mode is incorrect for using this API"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_InvalidMode,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::InvalidMode(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.invalid_mode"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_InvalidMode", "The current anti-cheat mode is incorrect for using this API"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_InvalidMode,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::ClientProductIdMismatch()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_product_id_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientProductIdMismatch", "The ProductId provided to the anti-cheat client helper executable does not match what was used to initialize the EOS SDK"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientProductIdMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ClientProductIdMismatch(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_product_id_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientProductIdMismatch", "The ProductId provided to the anti-cheat client helper executable does not match what was used to initialize the EOS SDK"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientProductIdMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ClientProductIdMismatch(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_product_id_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientProductIdMismatch", "The ProductId provided to the anti-cheat client helper executable does not match what was used to initialize the EOS SDK"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientProductIdMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::ClientSandboxIdMismatch()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_sandbox_id_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientSandboxIdMismatch", "The SandboxId provided to the anti-cheat client helper executable does not match what was used to initialize the EOS SDK"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientSandboxIdMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ClientSandboxIdMismatch(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_sandbox_id_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientSandboxIdMismatch", "The SandboxId provided to the anti-cheat client helper executable does not match what was used to initialize the EOS SDK"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientSandboxIdMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ClientSandboxIdMismatch(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_sandbox_id_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientSandboxIdMismatch", "The SandboxId provided to the anti-cheat client helper executable does not match what was used to initialize the EOS SDK"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientSandboxIdMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageSessionKeyRequired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.protect_message_session_key_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ProtectMessageSessionKeyRequired", "(ProtectMessage/UnprotectMessage) No session key is available, but it is required to complete this operation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ProtectMessageSessionKeyRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageSessionKeyRequired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.protect_message_session_key_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ProtectMessageSessionKeyRequired", "(ProtectMessage/UnprotectMessage) No session key is available, but it is required to complete this operation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ProtectMessageSessionKeyRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageSessionKeyRequired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.protect_message_session_key_required"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ProtectMessageSessionKeyRequired", "(ProtectMessage/UnprotectMessage) No session key is available, but it is required to complete this operation"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ProtectMessageSessionKeyRequired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageValidationFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.protect_message_validation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ProtectMessageValidationFailed", "(ProtectMessage/UnprotectMessage) Message integrity is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ProtectMessageValidationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageValidationFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.protect_message_validation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ProtectMessageValidationFailed", "(ProtectMessage/UnprotectMessage) Message integrity is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ProtectMessageValidationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageValidationFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.protect_message_validation_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ProtectMessageValidationFailed", "(ProtectMessage/UnprotectMessage) Message integrity is invalid"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ProtectMessageValidationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageInitializationFailed()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.protect_message_initialization_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ProtectMessageInitializationFailed", "(ProtectMessage/UnprotectMessage) Initialization failed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ProtectMessageInitializationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageInitializationFailed(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.protect_message_initialization_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ProtectMessageInitializationFailed", "(ProtectMessage/UnprotectMessage) Initialization failed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ProtectMessageInitializationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageInitializationFailed(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.protect_message_initialization_failed"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ProtectMessageInitializationFailed", "(ProtectMessage/UnprotectMessage) Initialization failed"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ProtectMessageInitializationFailed,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::PeerAlreadyRegistered()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.peer_already_registered"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_PeerAlreadyRegistered", "(RegisterPeer) Peer is already registered"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_PeerAlreadyRegistered,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::PeerAlreadyRegistered(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.peer_already_registered"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_PeerAlreadyRegistered", "(RegisterPeer) Peer is already registered"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_PeerAlreadyRegistered,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::PeerAlreadyRegistered(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.peer_already_registered"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_PeerAlreadyRegistered", "(RegisterPeer) Peer is already registered"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_PeerAlreadyRegistered,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::PeerNotFound()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.peer_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_PeerNotFound", "(UnregisterPeer) Peer does not exist"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_PeerNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::PeerNotFound(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.peer_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_PeerNotFound", "(UnregisterPeer) Peer does not exist"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_PeerNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::PeerNotFound(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.peer_not_found"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_PeerNotFound", "(UnregisterPeer) Peer does not exist"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_PeerNotFound,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::PeerNotProtected()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.peer_not_protected"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_PeerNotProtected", "(ReceiveMessageFromPeer) Invalid call: Peer is not protected"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_PeerNotProtected,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::PeerNotProtected(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.peer_not_protected"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_PeerNotProtected", "(ReceiveMessageFromPeer) Invalid call: Peer is not protected"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_PeerNotProtected,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::PeerNotProtected(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.peer_not_protected"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_PeerNotProtected", "(ReceiveMessageFromPeer) Invalid call: Peer is not protected"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_PeerNotProtected,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::ClientDeploymentIdMismatch()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_deployment_id_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientDeploymentIdMismatch", "The DeploymentId provided to the anti-cheat client helper executable does not match what was used to initialize the EOS SDK"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientDeploymentIdMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ClientDeploymentIdMismatch(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_deployment_id_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientDeploymentIdMismatch", "The DeploymentId provided to the anti-cheat client helper executable does not match what was used to initialize the EOS SDK"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientDeploymentIdMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::ClientDeploymentIdMismatch(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.client_deployment_id_mismatch"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_ClientDeploymentIdMismatch", "The DeploymentId provided to the anti-cheat client helper executable does not match what was used to initialize the EOS SDK"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_ClientDeploymentIdMismatch,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::AntiCheat::DeviceIdAuthIsNotSupported()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.device_id_auth_is_not_supported"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_DeviceIdAuthIsNotSupported", "EOS Connect DeviceID auth method is not supported for anti-cheat"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_DeviceIdAuthIsNotSupported,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::DeviceIdAuthIsNotSupported(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.device_id_auth_is_not_supported"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_DeviceIdAuthIsNotSupported", "EOS Connect DeviceID auth method is not supported for anti-cheat"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_DeviceIdAuthIsNotSupported,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::AntiCheat::DeviceIdAuthIsNotSupported(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.anticheat.device_id_auth_is_not_supported"),
        NSLOCTEXT("RedpointEOSAPI", "Error_AntiCheat_DeviceIdAuthIsNotSupported", "EOS Connect DeviceID auth method is not supported for anti-cheat"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_AntiCheat_DeviceIdAuthIsNotSupported,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::RTC::TooManyParticipants()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.too_many_participants"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_TooManyParticipants", "EOS RTC room cannot accept more participants"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_TooManyParticipants,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::TooManyParticipants(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.too_many_participants"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_TooManyParticipants", "EOS RTC room cannot accept more participants"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_TooManyParticipants,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::TooManyParticipants(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.too_many_participants"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_TooManyParticipants", "EOS RTC room cannot accept more participants"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_TooManyParticipants,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::RTC::RoomAlreadyExists()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.room_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_RoomAlreadyExists", "EOS RTC room already exists"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_RoomAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::RoomAlreadyExists(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.room_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_RoomAlreadyExists", "EOS RTC room already exists"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_RoomAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::RoomAlreadyExists(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.room_already_exists"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_RoomAlreadyExists", "EOS RTC room already exists"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_RoomAlreadyExists,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::RTC::UserKicked()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.user_kicked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_UserKicked", "The user kicked out from the room"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_UserKicked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::UserKicked(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.user_kicked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_UserKicked", "The user kicked out from the room"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_UserKicked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::UserKicked(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.user_kicked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_UserKicked", "The user kicked out from the room"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_UserKicked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::RTC::UserBanned()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.user_banned"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_UserBanned", "The user is banned"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_UserBanned,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::UserBanned(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.user_banned"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_UserBanned", "The user is banned"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_UserBanned,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::UserBanned(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.user_banned"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_UserBanned", "The user is banned"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_UserBanned,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::RTC::RoomWasLeft()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.room_was_left"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_RoomWasLeft", "EOS RTC room was left successfully"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_RoomWasLeft,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::RoomWasLeft(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.room_was_left"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_RoomWasLeft", "EOS RTC room was left successfully"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_RoomWasLeft,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::RoomWasLeft(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.room_was_left"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_RoomWasLeft", "EOS RTC room was left successfully"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_RoomWasLeft,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::RTC::ReconnectionTimegateExpired()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.reconnection_timegate_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_ReconnectionTimegateExpired", "Connection dropped due to long timeout"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_ReconnectionTimegateExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::ReconnectionTimegateExpired(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.reconnection_timegate_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_ReconnectionTimegateExpired", "Connection dropped due to long timeout"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_ReconnectionTimegateExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::ReconnectionTimegateExpired(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.reconnection_timegate_expired"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_ReconnectionTimegateExpired", "Connection dropped due to long timeout"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_ReconnectionTimegateExpired,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::RTC::ShutdownInvoked()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.shutdown_invoked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_ShutdownInvoked", "EOS RTC room was left due to platform release"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_ShutdownInvoked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::ShutdownInvoked(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.shutdown_invoked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_ShutdownInvoked", "EOS RTC room was left due to platform release"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_ShutdownInvoked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::ShutdownInvoked(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.shutdown_invoked"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_ShutdownInvoked", "EOS RTC room was left due to platform release"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_ShutdownInvoked,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::RTC::UserIsInBlocklist()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.user_is_in_blocklist"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_UserIsInBlocklist", "EOS RTC operation failed because the user is in the local user's block list"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_UserIsInBlocklist,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::UserIsInBlocklist(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.user_is_in_blocklist"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_UserIsInBlocklist", "EOS RTC operation failed because the user is in the local user's block list"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_UserIsInBlocklist,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::RTC::UserIsInBlocklist(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.rtc.user_is_in_blocklist"),
        NSLOCTEXT("RedpointEOSAPI", "Error_RTC_UserIsInBlocklist", "EOS RTC operation failed because the user is in the local user's block list"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_RTC_UserIsInBlocklist,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::ProgressionSnapshot::SnapshotIdUnavailable()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.progressionsnapshot.snapshot_id_unavailable"),
        NSLOCTEXT("RedpointEOSAPI", "Error_ProgressionSnapshot_SnapshotIdUnavailable", "The number of available Snapshot IDs have all been exhausted."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_ProgressionSnapshot_SnapshotIdUnavailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::ProgressionSnapshot::SnapshotIdUnavailable(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.progressionsnapshot.snapshot_id_unavailable"),
        NSLOCTEXT("RedpointEOSAPI", "Error_ProgressionSnapshot_SnapshotIdUnavailable", "The number of available Snapshot IDs have all been exhausted."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_ProgressionSnapshot_SnapshotIdUnavailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::ProgressionSnapshot::SnapshotIdUnavailable(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.progressionsnapshot.snapshot_id_unavailable"),
        NSLOCTEXT("RedpointEOSAPI", "Error_ProgressionSnapshot_SnapshotIdUnavailable", "The number of available Snapshot IDs have all been exhausted."),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_ProgressionSnapshot_SnapshotIdUnavailable,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::KWS::ParentEmailMissing()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.kws.parent_email_missing"),
        NSLOCTEXT("RedpointEOSAPI", "Error_KWS_ParentEmailMissing", "The KWS user does not have a parental email associated with the account.  The parent account was unlinked or deleted"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_KWS_ParentEmailMissing,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::KWS::ParentEmailMissing(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.kws.parent_email_missing"),
        NSLOCTEXT("RedpointEOSAPI", "Error_KWS_ParentEmailMissing", "The KWS user does not have a parental email associated with the account.  The parent account was unlinked or deleted"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_KWS_ParentEmailMissing,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::KWS::ParentEmailMissing(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.kws.parent_email_missing"),
        NSLOCTEXT("RedpointEOSAPI", "Error_KWS_ParentEmailMissing", "The KWS user does not have a parental email associated with the account.  The parent account was unlinked or deleted"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_KWS_ParentEmailMissing,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::KWS::UserGraduated()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.kws.user_graduated"),
        NSLOCTEXT("RedpointEOSAPI", "Error_KWS_UserGraduated", "The KWS user is no longer a minor and trying to update the parent email"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_KWS_UserGraduated,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::KWS::UserGraduated(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.kws.user_graduated"),
        NSLOCTEXT("RedpointEOSAPI", "Error_KWS_UserGraduated", "The KWS user is no longer a minor and trying to update the parent email"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_KWS_UserGraduated,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::KWS::UserGraduated(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.kws.user_graduated"),
        NSLOCTEXT("RedpointEOSAPI", "Error_KWS_UserGraduated", "The KWS user is no longer a minor and trying to update the parent email"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_KWS_UserGraduated,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError& Redpoint::EOS::API::Errors::Android::JavaVMNotStored()
{
    static Redpoint::EOS::API::FError Err = {
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.android.java_vm_not_stored"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Android_JavaVMNotStored", "EOS Android VM not stored"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Android_JavaVMNotStored,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        TEXT(""),
        TEXT(""),
    };
    return Err;
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Android::JavaVMNotStored(const TCHAR* InCall, const FString& InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.android.java_vm_not_stored"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Android_JavaVMNotStored", "EOS Android VM not stored"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Android_JavaVMNotStored,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}
const Redpoint::EOS::API::FError Redpoint::EOS::API::Errors::Android::JavaVMNotStored(const TCHAR* InCall, const TCHAR* InContextMsg)
{
    return Redpoint::EOS::API::FError{
        false,
        TEXT(ONLINE_ERROR_NAMESPACE),
        TEXT("errors.com.redpoint.eos.android.java_vm_not_stored"),
        NSLOCTEXT("RedpointEOSAPI", "Error_Android_JavaVMNotStored", "EOS Android VM not stored"),
#if EOS_VERSION_AT_LEAST(1, 15, 4)
        EOS_EResult::EOS_Android_JavaVMNotStored,
#else
        EOS_EResult::EOS_UnexpectedError,
#endif
        InCall,
        InContextMsg,
    };
}

#undef ONLINE_ERROR_NAMESPACE
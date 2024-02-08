// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Shared/Authentication/AuthenticationHelpers.h"

#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

#include "RedpointEOSAPI/Connect/Login.h"
#include "RedpointEOSConfig/Config.h"

EOS_ENABLE_STRICT_WARNINGS

EOS_EExternalCredentialType StrToExternalCredentialType(const FString &InStr)
{
    if (InStr.ToUpper() == TEXT("EPIC"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_EPIC;
    }
    else if (InStr.ToUpper() == TEXT("PSN_ID_TOKEN"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_PSN_ID_TOKEN;
    }
    else if (InStr.ToUpper() == TEXT("XBL_XSTS_TOKEN"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_XBL_XSTS_TOKEN;
    }
    else if (InStr.ToUpper() == TEXT("DISCORD_ACCESS_TOKEN"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_DISCORD_ACCESS_TOKEN;
    }
    else if (InStr.ToUpper() == TEXT("GOG_SESSION_TICKET"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_GOG_SESSION_TICKET;
    }
    else if (InStr.ToUpper() == TEXT("NINTENDO_ID_TOKEN"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_NINTENDO_ID_TOKEN;
    }
    else if (InStr.ToUpper() == TEXT("NINTENDO_NSA_ID_TOKEN"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_NINTENDO_NSA_ID_TOKEN;
    }
    else if (InStr.ToUpper() == TEXT("UPLAY_ACCESS_TOKEN"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_UPLAY_ACCESS_TOKEN;
    }
    else if (InStr.ToUpper() == TEXT("OPENID_ACCESS_TOKEN"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_OPENID_ACCESS_TOKEN;
    }
    else if (InStr.ToUpper() == TEXT("DEVICEID_ACCESS_TOKEN"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_DEVICEID_ACCESS_TOKEN;
    }
    else if (InStr.ToUpper() == TEXT("APPLE_ID_TOKEN"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_APPLE_ID_TOKEN;
    }
    else if (InStr.ToUpper() == TEXT("GOOGLE_ID_TOKEN"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_GOOGLE_ID_TOKEN;
    }
    else if (InStr.ToUpper() == TEXT("OCULUS_USERID_NONCE"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_OCULUS_USERID_NONCE;
    }
    else if (InStr.ToUpper() == TEXT("ITCHIO_JWT"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_ITCHIO_JWT;
    }
    else if (InStr.ToUpper() == TEXT("ITCHIO_KEY"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_ITCHIO_KEY;
    }
    else if (InStr.ToUpper() == TEXT("STEAM_SESSION_TICKET"))
    {
        return EOS_EExternalCredentialType::EOS_ECT_STEAM_SESSION_TICKET;
    }
    else if (InStr.ToUpper() == TEXT("STEAM_APP_TICKET"))
    {
        checkf(false, TEXT("STEAM_APP_TICKET is no longer supported by the EOS SDK."));
        return EOS_EExternalCredentialType::EOS_ECT_STEAM_APP_TICKET;
    }

    checkf(false, TEXT("Expected known credential type for StrToExternalCredentialType"));
    return EOS_EExternalCredentialType::EOS_ECT_EPIC;
}

EOS_DISABLE_STRICT_WARNINGS

#if EOS_HAS_AUTHENTICATION

#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"

#ifdef PLATFORM_IOS
#if defined(EOS_IOS_REQUIRES_PRESENTATIONCONTEXT) && EOS_IOS_REQUIRES_PRESENTATIONCONTEXT
#include "IOS/IOSAppDelegate.h"
#import <AuthenticationServices/AuthenticationServices.h>
#endif
#endif

EOS_ENABLE_STRICT_WARNINGS

#ifdef PLATFORM_IOS
#if defined(EOS_IOS_REQUIRES_PRESENTATIONCONTEXT) && EOS_IOS_REQUIRES_PRESENTATIONCONTEXT

@interface PresentationContext : NSObject <ASWebAuthenticationPresentationContextProviding>
{
}
@end

@implementation PresentationContext

- (ASPresentationAnchor)presentationAnchorForWebAuthenticationSession:(ASWebAuthenticationSession *)session
{
    if ([IOSAppDelegate GetDelegate].Window == nullptr)
    {
        NSLog(@"authorizationController: presentationAnchorForAuthorizationController: error window is NULL");
    }
    return [IOSAppDelegate GetDelegate].Window;
}

@end

static PresentationContext *PresentationContextProvider = nullptr;

#endif
#endif

FString ExternalCredentialTypeToStr(EOS_EExternalCredentialType InType)
{
    if (InType == EOS_EExternalCredentialType::EOS_ECT_EPIC)
    {
        return TEXT("EPIC");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_PSN_ID_TOKEN)
    {
        return TEXT("PSN_ID_TOKEN");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_XBL_XSTS_TOKEN)
    {
        return TEXT("XBL_XSTS_TOKEN");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_DISCORD_ACCESS_TOKEN)
    {
        return TEXT("DISCORD_ACCESS_TOKEN");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_GOG_SESSION_TICKET)
    {
        return TEXT("GOG_SESSION_TICKET");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_NINTENDO_ID_TOKEN)
    {
        return TEXT("NINTENDO_ID_TOKEN");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_NINTENDO_NSA_ID_TOKEN)
    {
        return TEXT("NINTENDO_NSA_ID_TOKEN");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_UPLAY_ACCESS_TOKEN)
    {
        return TEXT("UPLAY_ACCESS_TOKEN");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_OPENID_ACCESS_TOKEN)
    {
        return TEXT("OPENID_ACCESS_TOKEN");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_DEVICEID_ACCESS_TOKEN)
    {
        return TEXT("DEVICEID_ACCESS_TOKEN");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_APPLE_ID_TOKEN)
    {
        return TEXT("APPLE_ID_TOKEN");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_GOOGLE_ID_TOKEN)
    {
        return TEXT("GOOGLE_ID_TOKEN");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_OCULUS_USERID_NONCE)
    {
        return TEXT("OCULUS_USERID_NONCE");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_ITCHIO_JWT)
    {
        return TEXT("ITCHIO_JWT");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_ITCHIO_KEY)
    {
        return TEXT("ITCHIO_KEY");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_STEAM_SESSION_TICKET)
    {
        return TEXT("STEAM_SESSION_TICKET");
    }
    else if (InType == EOS_EExternalCredentialType::EOS_ECT_STEAM_APP_TICKET)
    {
        checkf(false, TEXT("STEAM_APP_TICKET is no longer supported by the EOS SDK."));
        return TEXT("STEAM_APP_TICKET");
    }

    checkf(false, TEXT("Expected known credential type for ExternalCredentialTypeToStr"));
    return TEXT("");
}

void FEASAuthentication::DoRequest(
    EOS_HAuth EOSAuth,
    const FString &Id,
    const FString &Token,
    EOS_ELoginCredentialType Type,
    const Redpoint::EOS::Config::IConfig &InConfig,
    const FEASAuth_DoRequestComplete &OnComplete)
{
    auto TokenData = StringCast<ANSICHAR>(*Token);
    auto IdData = EOSString_Connect_UserLoginInfo_DisplayName::ToUtf8String(Id);

    EOS_Auth_Credentials Creds = {};
    Creds.ApiVersion = EOS_AUTH_CREDENTIALS_API_LATEST;
    Creds.Id = ((Id == TEXT("")) ? nullptr : IdData.GetAsChar());
    Creds.Token = ((Token == TEXT("")) ? nullptr : TokenData.Get());
    Creds.Type = Type;
#if PLATFORM_IOS
    EOS_IOS_Auth_CredentialsOptions IOSOpts = {};
    IOSOpts.ApiVersion = EOS_IOS_AUTH_CREDENTIALSOPTIONS_API_LATEST;
#if defined(EOS_IOS_REQUIRES_PRESENTATIONCONTEXT) && EOS_IOS_REQUIRES_PRESENTATIONCONTEXT
    if (@available(iOS 13.0, *))
    {
        if (PresentationContextProvider != nil)
        {
            [PresentationContextProvider release];
            PresentationContextProvider = nil;
        }
        PresentationContextProvider = [PresentationContext new];
        IOSOpts.PresentationContextProviding = (void *)CFBridgingRetain(PresentationContextProvider);
    }
    else
    {
        IOSOpts.PresentationContextProviding = nullptr;
    }
#else
    IOSOpts.PresentationContextProviding = nullptr;
#endif
    Creds.SystemAuthCredentialsOptions = &IOSOpts;
#endif

    EOS_Auth_LoginOptions Opts = {};
    Opts.ApiVersion = EOS_AUTH_LOGIN_API_LATEST;
    Opts.Credentials = &Creds;
    Opts.ScopeFlags = EOS_EAuthScopeFlags::EOS_AS_NoFlags;
    for (const auto &Flag : InConfig.GetEpicGamesScopes())
    {
        Opts.ScopeFlags |= Flag;
    }
    if (Opts.ScopeFlags != InConfig.GetSupportedEpicGamesScopes())
    {
        UE_LOG(
            LogRedpointEOS,
            Warning,
            TEXT("Non-standard Epic Games scopes set in configuration; there is NO SUPPORT for using a non-standard "
                 "set of scopes!"));
    }

    UE_LOG(LogRedpointEOS, Verbose, TEXT("EOSAuth_DoRequest: Request started"));

    EOSRunOperationKeepAlive<EOS_HAuth, EOS_Auth_LoginOptions, EOS_Auth_LoginCallbackInfo>(
        EOSAuth,
        &Opts,
        &EOS_Auth_Login,
        [OnComplete](const EOS_Auth_LoginCallbackInfo *Data, bool &KeepAlive) {
            UE_LOG(
                LogRedpointEOS,
                Verbose,
                TEXT("EOSAuth_DoRequest: Request finished (result code %s)"),
                ANSI_TO_TCHAR(EOS_EResult_ToString(Data->ResultCode)));

            if (Data->ResultCode == EOS_EResult::EOS_Auth_PinGrantCode && Data->PinGrantInfo != nullptr)
            {
                // The SDK will run the callback again later, so keep the callback allocated.
                KeepAlive = true;
            }

            OnComplete.ExecuteIfBound(Data);
        });
}

void FEASAuthentication::DoRequestLink(
    EOS_HAuth EOSAuth,
    EOS_ContinuanceToken ContinuanceToken,
    EOS_ELinkAccountFlags LinkAccountFlags,
    EOS_EpicAccountId LocalUserId,
    const FEASAuth_DoRequestLinkComplete &OnComplete)
{
    EOS_Auth_LinkAccountOptions Opts = {};
    Opts.ApiVersion = EOS_AUTH_LINKACCOUNT_API_LATEST;
    Opts.ContinuanceToken = ContinuanceToken;
    Opts.LinkAccountFlags = LinkAccountFlags;
    Opts.LocalUserId = LocalUserId;

    UE_LOG(LogRedpointEOS, Verbose, TEXT("EOSAuth_DoRequestLink: Request started"));

    EOSRunOperationKeepAlive<EOS_HAuth, EOS_Auth_LinkAccountOptions, EOS_Auth_LinkAccountCallbackInfo>(
        EOSAuth,
        &Opts,
        &EOS_Auth_LinkAccount,
        [OnComplete](const EOS_Auth_LinkAccountCallbackInfo *Data, bool &KeepAlive) {
            UE_LOG(
                LogRedpointEOS,
                Verbose,
                TEXT("EOSAuth_DoRequestLink: Request finished (result code %s)"),
                ANSI_TO_TCHAR(EOS_EResult_ToString(Data->ResultCode)));

            if (Data->ResultCode == EOS_EResult::EOS_Auth_PinGrantCode && Data->PinGrantInfo != nullptr)
            {
                // The SDK will run the callback again later, so keep the callback allocated.
                KeepAlive = true;
            }

            OnComplete.ExecuteIfBound(Data);
        });
}

void FEASAuthentication::DoRequestExternal(
    EOS_HAuth EOSAuth,
    const FString &Id,
    const FString &Token,
    EOS_EExternalCredentialType ExternalType,
    bool bPermitInteractive,
    const Redpoint::EOS::Config::IConfig &InConfig,
    const FEASAuth_DoRequestComplete &OnComplete)
{
    auto TokenData = StringCast<ANSICHAR>(*Token);
    auto IdData = EOSString_Connect_UserLoginInfo_DisplayName::ToUtf8String(Id);

    EOS_Auth_Credentials Creds = {};
    Creds.ApiVersion = EOS_AUTH_CREDENTIALS_API_LATEST;
    Creds.Id = ((Id == TEXT("")) ? nullptr : IdData.GetAsChar());
    Creds.Token = ((Token == TEXT("")) ? nullptr : TokenData.Get());
    Creds.Type = EOS_ELoginCredentialType::EOS_LCT_ExternalAuth;
    Creds.ExternalType = ExternalType;
#if PLATFORM_IOS
    EOS_IOS_Auth_CredentialsOptions IOSOpts = {};
    IOSOpts.ApiVersion = EOS_IOS_AUTH_CREDENTIALSOPTIONS_API_LATEST;
#if defined(EOS_IOS_REQUIRES_PRESENTATIONCONTEXT) && EOS_IOS_REQUIRES_PRESENTATIONCONTEXT
    if (@available(iOS 13.0, *))
    {
        if (PresentationContextProvider != nil)
        {
            [PresentationContextProvider release];
            PresentationContextProvider = nil;
        }
        PresentationContextProvider = [PresentationContext new];
        IOSOpts.PresentationContextProviding = (void *)CFBridgingRetain(PresentationContextProvider);
    }
    else
    {
        IOSOpts.PresentationContextProviding = nullptr;
    }
#else
    IOSOpts.PresentationContextProviding = nullptr;
#endif
    Creds.SystemAuthCredentialsOptions = &IOSOpts;
#endif

    EOS_Auth_LoginOptions Opts = {};
    Opts.ApiVersion = EOS_AUTH_LOGIN_API_LATEST;
    Opts.Credentials = &Creds;
    Opts.ScopeFlags = EOS_EAuthScopeFlags::EOS_AS_NoFlags;
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    Opts.LoginFlags = 0;
    if (!bPermitInteractive)
    {
        Opts.LoginFlags |= EOS_LF_NO_USER_INTERFACE;
    }
#endif
    for (const auto &Flag : InConfig.GetEpicGamesScopes())
    {
        Opts.ScopeFlags |= Flag;
    }
    if (Opts.ScopeFlags != InConfig.GetSupportedEpicGamesScopes())
    {
        UE_LOG(
            LogRedpointEOS,
            Warning,
            TEXT("Non-standard Epic Games scopes set in configuration; there is NO SUPPORT for using a non-standard "
                 "set of scopes!"));
    }

    UE_LOG(LogRedpointEOS, Verbose, TEXT("EOSAuth_DoRequestExternal: Request started"));

    EOSRunOperation<EOS_HAuth, EOS_Auth_LoginOptions, EOS_Auth_LoginCallbackInfo>(
        EOSAuth,
        &Opts,
        &EOS_Auth_Login,
        [OnComplete](const EOS_Auth_LoginCallbackInfo *Data) {
            UE_LOG(
                LogRedpointEOS,
                Verbose,
                TEXT("EOSAuth_DoRequestExternal: Request finished (result code %s)"),
                ANSI_TO_TCHAR(EOS_EResult_ToString(Data->ResultCode)));

            OnComplete.ExecuteIfBound(Data);
        });
}

void FEOSAuthentication::DoRequest(
    EOS_HConnect EOSConnect,
    const FString &Id,
    const FString &Token,
    const FString &LocalDisplayName,
    EOS_EExternalCredentialType Type,
    const FEOSAuth_DoRequestComplete &OnComplete)
{
    using namespace Redpoint::EOS::API::Connect;

    FLogin::Options Opts = {
        Id,
        Token,
        LocalDisplayName,
        Type,
    };

    UE_LOG(LogRedpointEOS, Verbose, TEXT("EOSConnect_DoRequest: Request started"));
    FLogin::Execute(
        EOSConnect,
        Opts,
        FLogin::CompletionDelegate::CreateLambda([OnComplete](const FLogin::Result &Result) {
            UE_LOG(
                LogRedpointEOS,
                Verbose,
                TEXT("EOSConnect_DoRequest: Request finished (result code %s)"),
                ANSI_TO_TCHAR(EOS_EResult_ToString(Result.ResultCode)));
            OnComplete.ExecuteIfBound(&Result.Result);
        }));
}

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
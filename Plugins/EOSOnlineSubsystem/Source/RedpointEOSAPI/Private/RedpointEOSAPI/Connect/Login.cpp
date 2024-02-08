// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/Connect/Login.h"

namespace Redpoint::EOS::API::Connect
{

REDPOINT_EOSSDK_API_CALL_ASYNC_IMPL(Login);

void FLogin::MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator)
{
    auto &Creds = Allocator.Allocate<EOS_Connect_Credentials>();
    Creds.ApiVersion = EOS_CONNECT_CREDENTIALS_API_LATEST;
    Creds.Token = Allocator.AsAnsi(Options.Token);
    Creds.Type = *Options.Type;

	auto &LoginInfo = Allocator.Allocate<EOS_Connect_UserLoginInfo>();
    LoginInfo.ApiVersion = EOS_CONNECT_USERLOGININFO_API_LATEST;
    LoginInfo.DisplayName = (*Options.LocalDisplayName).IsEmpty() ? Allocator.AsUtf8(Options.Id)
                                                                  : Allocator.AsUtf8(Options.LocalDisplayName);

	NativeOptions.Credentials = &Creds;
    if (Creds.Type == EOS_EExternalCredentialType::EOS_ECT_NINTENDO_ID_TOKEN ||
        Creds.Type == EOS_EExternalCredentialType::EOS_ECT_NINTENDO_NSA_ID_TOKEN ||
        Creds.Type == EOS_EExternalCredentialType::EOS_ECT_APPLE_ID_TOKEN ||
        Creds.Type == EOS_EExternalCredentialType::EOS_ECT_OCULUS_USERID_NONCE ||
        Creds.Type == EOS_EExternalCredentialType::EOS_ECT_GOOGLE_ID_TOKEN ||
        Creds.Type == EOS_EExternalCredentialType::EOS_ECT_DEVICEID_ACCESS_TOKEN)
    {
        NativeOptions.UserLoginInfo = &LoginInfo;
    }
    else
    {
        NativeOptions.UserLoginInfo = nullptr;
    }
}

void FLogin::MapResult(Result &Result, const NativeResult &NativeResult, NativeConverter& Converter)
{
    Result.ResultCode = NativeResult.ResultCode;
	// @note: Our downstream code requires the raw EOS result data.
    Result.Result = NativeResult;
}

} // namespace Redpoint::EOS::API::Connect
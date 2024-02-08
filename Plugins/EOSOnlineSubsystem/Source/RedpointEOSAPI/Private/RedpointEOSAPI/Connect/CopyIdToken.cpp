// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/Connect/CopyIdToken.h"

namespace Redpoint::EOS::API::Connect
{

REDPOINT_EOSSDK_API_CALL_SYNC_COPY_IMPL(CopyIdToken);

void FCopyIdToken::MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator)
{
    NativeOptions.LocalUserId = *Options.LocalUserId;
}

void FCopyIdToken::MapResult(Result &Result, const NativeResult &NativeResult, NativeConverter &Converter)
{
    Result.JsonWebToken = Converter.FromUtf8(NativeResult.JsonWebToken);
}

} // namespace Redpoint::EOS::API::Connect
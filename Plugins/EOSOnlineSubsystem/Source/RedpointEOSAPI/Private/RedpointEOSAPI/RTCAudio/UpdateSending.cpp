// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/RTCAudio/UpdateSending.h"

namespace Redpoint::EOS::API::RTCAudio
{

REDPOINT_EOSSDK_API_CALL_ASYNC_IMPL(UpdateSending);

void FUpdateSending::MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator)
{
    NativeOptions.LocalUserId = *Options.LocalUserId;
    NativeOptions.RoomName = Allocator.AsAnsi(Options.RoomName);
    NativeOptions.AudioStatus = *Options.AudioStatus;
}

void FUpdateSending::MapResult(Result &Result, const NativeResult &NativeResult, NativeConverter &Converter)
{
    Result.LocalUserId = NativeResult.LocalUserId;
    Result.ResultCode = NativeResult.ResultCode;
    Result.AudioStatus = NativeResult.AudioStatus;
}

} // namespace Redpoint::EOS::API::RTCAudio
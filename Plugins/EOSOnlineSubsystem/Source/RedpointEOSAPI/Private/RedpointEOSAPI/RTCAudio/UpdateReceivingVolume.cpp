// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/RTCAudio/UpdateReceivingVolume.h"

namespace Redpoint::EOS::API::RTCAudio
{

REDPOINT_EOSSDK_API_CALL_ASYNC_IMPL(UpdateReceivingVolume);

void FUpdateReceivingVolume::MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator)
{
    NativeOptions.LocalUserId = *Options.LocalUserId;
    NativeOptions.RoomName = Allocator.AsAnsi(Options.RoomName);
    NativeOptions.Volume = *Options.Volume;
}

void FUpdateReceivingVolume::MapResult(Result &Result, const NativeResult &NativeResult, NativeConverter &Converter)
{
    Result.LocalUserId = NativeResult.LocalUserId;
    Result.ResultCode = NativeResult.ResultCode;
    Result.Volume = NativeResult.Volume;
}

} // namespace Redpoint::EOS::API::RTCAudio
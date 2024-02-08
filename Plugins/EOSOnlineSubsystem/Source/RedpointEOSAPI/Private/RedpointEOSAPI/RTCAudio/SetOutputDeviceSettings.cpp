// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/RTCAudio/SetOutputDeviceSettings.h"

namespace Redpoint::EOS::API::RTCAudio {

#if EOS_VERSION_AT_LEAST(1, 16, 0)
REDPOINT_EOSSDK_API_CALL_ASYNC_IMPL(SetOutputDeviceSettings);
#else
REDPOINT_EOSSDK_API_CALL_SYNC_AS_ASYNC_IMPL(SetOutputDeviceSettings);
#endif

void FSetOutputDeviceSettings::MapOptions(
	NativeOptions& NativeOptions,
	const Options& Options,
	NativeAllocator& Allocator)
{
    NativeOptions.LocalUserId = *Options.LocalUserId;
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    NativeOptions.RealDeviceId = Allocator.AsAnsi(Options.DeviceId);
#else
    NativeOptions.DeviceId = Allocator.AsAnsi(Options.DeviceId);
    NativeOptions.Volume = *Options.DeviceVolume;
#endif
}

void FSetOutputDeviceSettings::MapResult(Result &Result, const NativeResult &NativeResult, NativeConverter &Converter)
{
    Result.ResultCode = NativeResult.ResultCode;
}

}
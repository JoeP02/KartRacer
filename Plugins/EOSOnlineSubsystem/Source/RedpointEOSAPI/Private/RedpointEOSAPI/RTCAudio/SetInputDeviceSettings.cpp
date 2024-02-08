// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/RTCAudio/SetInputDeviceSettings.h"

namespace Redpoint::EOS::API::RTCAudio {

#if EOS_VERSION_AT_LEAST(1, 16, 0)
REDPOINT_EOSSDK_API_CALL_ASYNC_IMPL(SetInputDeviceSettings);
#else
REDPOINT_EOSSDK_API_CALL_SYNC_AS_ASYNC_IMPL(SetInputDeviceSettings);
#endif

void FSetInputDeviceSettings::MapOptions(
	NativeOptions& NativeOptions,
	const Options& Options,
	NativeAllocator& Allocator)
{
    NativeOptions.LocalUserId = *Options.LocalUserId;
    NativeOptions.bPlatformAEC = *Options.bEnablePlatformAEC ? EOS_TRUE : EOS_FALSE;
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    NativeOptions.RealDeviceId = Allocator.AsAnsi(Options.DeviceId);
#else
    NativeOptions.DeviceId = Allocator.AsAnsi(Options.DeviceId);
    NativeOptions.Volume = *Options.DeviceVolume;
#endif
}

void FSetInputDeviceSettings::MapResult(Result &Result, const NativeResult &NativeResult, NativeConverter &Converter)
{
    Result.ResultCode = NativeResult.ResultCode;
}

}
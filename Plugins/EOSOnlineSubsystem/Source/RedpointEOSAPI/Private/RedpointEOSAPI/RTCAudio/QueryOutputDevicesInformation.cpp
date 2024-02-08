// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/RTCAudio/QueryOutputDevicesInformation.h"

namespace Redpoint::EOS::API::RTCAudio
{

#if EOS_VERSION_AT_LEAST(1, 16, 0)
REDPOINT_EOSSDK_API_CALL_ASYNC_LIST_IMPL(QueryOutputDevicesInformation);
#else
REDPOINT_EOSSDK_API_CALL_SYNC_LIST_AS_ASYNC_LIST_IMPL(QueryOutputDevicesInformation);
#endif

#if EOS_VERSION_AT_LEAST(1, 16, 0)
void FQueryOutputDevicesInformation::MapQueryOptions(
    NativeQueryOptions &NativeOptions,
    const Options &Options,
    NativeAllocator &Allocator)
{
}
#endif

void FQueryOutputDevicesInformation::MapCountOptions(
    NativeCountOptions &NativeOptions,
    const Options &Options,
    NativeAllocator &Allocator)
{
}

void FQueryOutputDevicesInformation::MapCopyByIndexOptions(
    NativeCopyByIndexOptions &NativeOptions,
    const Options &Options,
	uint32_t Index,
    NativeAllocator &Allocator)
{
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    NativeOptions.DeviceIndex = Index;
#else
    NativeOptions.DeviceInfoIndex = Index;
#endif
}

void FQueryOutputDevicesInformation::MapCopyByIndexResult(
    ResultEntry &Result,
    const NativeCopyByIndexResult &NativeResult,
	NativeConverter& Converter)
{
    Result.Id = Converter.FromAnsi(NativeResult.DeviceId);
    Result.DisplayName = Converter.FromUtf8(NativeResult.DeviceName);
    Result.bIsDefaultDevice = NativeResult.bDefaultDevice == EOS_TRUE;
    Result.bIsInputDevice = false;
}

} // namespace Redpoint::EOS::API::RTCAudio
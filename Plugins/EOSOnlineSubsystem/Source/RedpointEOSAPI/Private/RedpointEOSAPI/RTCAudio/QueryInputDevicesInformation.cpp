// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/RTCAudio/QueryInputDevicesInformation.h"

namespace Redpoint::EOS::API::RTCAudio
{

#if EOS_VERSION_AT_LEAST(1, 16, 0)
REDPOINT_EOSSDK_API_CALL_ASYNC_LIST_IMPL(QueryInputDevicesInformation);
#else
REDPOINT_EOSSDK_API_CALL_SYNC_LIST_AS_ASYNC_LIST_IMPL(QueryInputDevicesInformation);
#endif

#if EOS_VERSION_AT_LEAST(1, 16, 0)
void FQueryInputDevicesInformation::MapQueryOptions(
    NativeQueryOptions &NativeOptions,
    const Options &Options,
    NativeAllocator &Allocator)
{
}
#endif

void FQueryInputDevicesInformation::MapCountOptions(
    NativeCountOptions &NativeOptions,
    const Options &Options,
    NativeAllocator &Allocator)
{
}

void FQueryInputDevicesInformation::MapCopyByIndexOptions(
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

void FQueryInputDevicesInformation::MapCopyByIndexResult(
    ResultEntry &Result,
    const NativeCopyByIndexResult &NativeResult,
    NativeConverter &Converter)
{
    Result.Id = Converter.FromAnsi(NativeResult.DeviceId);
    Result.DisplayName = Converter.FromUtf8(NativeResult.DeviceName);
    Result.bIsDefaultDevice = NativeResult.bDefaultDevice == EOS_TRUE;
    Result.bIsInputDevice = true;
}

} // namespace Redpoint::EOS::API::RTCAudio
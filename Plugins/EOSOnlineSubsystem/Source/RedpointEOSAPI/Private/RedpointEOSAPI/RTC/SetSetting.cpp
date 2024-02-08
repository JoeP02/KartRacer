// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/RTC/SetSetting.h"

namespace Redpoint::EOS::API::RTC {

REDPOINT_EOSSDK_API_CALL_SYNC_IMPL(SetSetting);

void FSetSetting::MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator)
{
    NativeOptions.SettingName = Allocator.AsAnsi(Options.SettingName);
    NativeOptions.SettingValue = Allocator.AsAnsi(Options.SettingValue);
}

}
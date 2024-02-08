// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Stats/Stats.h"

#include "RedpointEOSAPI/Error.h"
#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSAPI/Templates/ApiCallName.h"
#include "RedpointEOSAPI/Templates/Cdecl.h"

namespace Redpoint::EOS::API
{

namespace Private
{

template <typename S> struct TNativeCallSyncInfo;
template <typename Handle, typename Options, typename Result>
struct TNativeCallSyncInfo<Result(Handle, const Options *)>
{
    using HandleType = Handle;
    using OptionsType = Options;
    using ResultType = Result;
};

#define REDPOINT_EOSSDK_API_CALL_SYNC_BEGIN(CallNamespace, CallName, CallVersion)                                      \
private:                                                                                                               \
    typedef EOS_H##CallNamespace NativeHandle;                                                                         \
    typedef Redpoint::EOS::API::Private::TNativeCallSyncInfo<decltype(EOS_##CallNamespace##_##CallName)>::OptionsType  \
        NativeOptions;                                                                                                 \
    typedef Redpoint::EOS::API::Private::FApiCallNativeAllocator NativeAllocator;                                      \
    static FORCEINLINE int NativeOptionsVersion()                                                                      \
    {                                                                                                                  \
        return CallVersion;                                                                                            \
    }                                                                                                                  \
    static FORCEINLINE EOS_EResult NativeFunction(NativeHandle Handle, const NativeOptions *Options)                   \
    {                                                                                                                  \
        return EOS_##CallNamespace##_##CallName(Handle, Options);                                                      \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *StatCallName()                                                                     \
    {                                                                                                                  \
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(CallNamespace)) TEXT("_")                      \
            TEXT(PREPROCESSOR_TO_STRING(CallName));                                                                    \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *LogCallName()                                                                      \
    {                                                                                                                  \
        return TEXT(PREPROCESSOR_TO_STRING(EOS_##CallNamespace##_##CallName));                                         \
    }                                                                                                                  \
                                                                                                                       \
public:
#define REDPOINT_EOSSDK_API_CALL_SYNC_END()                                                                            \
public:                                                                                                                \
    static EOS_EResult Execute(const FPlatformHandle &InHandle, const Options &InOptions);                             \
    static EOS_EResult Execute(NativeHandle InHandle, const Options &InOptions);                                       \
                                                                                                                       \
private:                                                                                                               \
    static void MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator);
#define REDPOINT_EOSSDK_API_CALL_SYNC_IMPL(CallName)                                                                   \
    EOS_EResult F##CallName::Execute(const FPlatformHandle &InHandle, const Options &InOptions)                        \
    {                                                                                                                  \
        return Execute(InHandle->Get<NativeHandle>(), InOptions);                                                      \
    }                                                                                                                  \
    EOS_EResult F##CallName::Execute(NativeHandle InHandle, const Options &InOptions)                                  \
    {                                                                                                                  \
        DECLARE_CYCLE_STAT(StatCallName(), STAT_Call, STATGROUP_RedpointEOS);                                          \
        SCOPE_CYCLE_COUNTER(STAT_Call);                                                                                \
                                                                                                                       \
        UE_LOG(LogRedpointEOSAPI, VeryVerbose, TEXT("[starting] %s"), LogCallName());                                  \
                                                                                                                       \
        if (InHandle == nullptr)                                                                                       \
        {                                                                                                              \
            UE_LOG(                                                                                                    \
                LogRedpointEOSAPI,                                                                                     \
                VeryVerbose,                                                                                           \
                TEXT("[complete] %s"),                                                                                 \
                *ConvertError(                                                                                         \
                     LogCallName(),                                                                                    \
                     TEXT("The platform instance has been shutdown, so SDK calls can not be made."),                   \
                     EOS_EResult::EOS_NoConnection)                                                                    \
                     .ToLogString());                                                                                  \
                                                                                                                       \
            return EOS_EResult::EOS_NoConnection;                                                                      \
        }                                                                                                              \
                                                                                                                       \
        TSharedRef<NativeAllocator> Allocator = MakeShared<NativeAllocator>();                                         \
                                                                                                                       \
        NativeOptions _NativeOptions = {};                                                                             \
        _NativeOptions.ApiVersion = NativeOptionsVersion();                                                            \
        MapOptions(_NativeOptions, InOptions, *Allocator);                                                             \
                                                                                                                       \
        EOS_EResult ResultCode = NativeFunction(InHandle, &_NativeOptions);                                            \
        UE_LOG(                                                                                                        \
            LogRedpointEOSAPI,                                                                                         \
            VeryVerbose,                                                                                               \
            TEXT("[complete] %s"),                                                                                     \
            *ConvertError(LogCallName(), TEXT("Sync call completed."), ResultCode).ToLogString());                     \
        return ResultCode;                                                                                             \
    }

} // namespace Private

} // namespace Redpoint::EOS::API
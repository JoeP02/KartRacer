// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Stats/Stats.h"

#include "RedpointEOSAPI/Error.h"
#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSAPI/Templates/ApiCallName.h"
#include "RedpointEOSAPI/Templates/AsyncList.h"
#include "RedpointEOSAPI/Templates/Cdecl.h"

namespace Redpoint::EOS::API
{

namespace Private
{

#define REDPOINT_EOSSDK_API_CALL_SYNC_COPY_BEGIN(CallNamespace, CallName, CallVersion, ResultEntryName)                \
private:                                                                                                               \
    typedef EOS_H##CallNamespace NativeHandle;                                                                         \
    typedef Redpoint::EOS::API::Private::TNativeCallAsyncListCopyByIndexInfo<                                          \
        decltype(EOS_##CallNamespace##_##CallName)>::CopyOptionsType NativeOptions;                                    \
    typedef Redpoint::EOS::API::Private::TNativeCallAsyncListCopyByIndexInfo<                                          \
        decltype(EOS_##CallNamespace##_##CallName)>::ResultEntryType NativeResult;                                     \
    typedef Redpoint::EOS::API::Private::FApiCallNativeAllocator NativeAllocator;                                      \
    typedef Redpoint::EOS::API::Private::FApiCallNativeConverter NativeConverter;                                      \
    static FORCEINLINE int NativeOptionsVersion()                                                                      \
    {                                                                                                                  \
        return CallVersion;                                                                                            \
    }                                                                                                                  \
    static FORCEINLINE EOS_EResult                                                                                     \
    NativeFunction(NativeHandle Handle, const NativeOptions *Options, NativeResult **Result)                           \
    {                                                                                                                  \
        return EOS_##CallNamespace##_##CallName(Handle, Options, Result);                                              \
    }                                                                                                                  \
    static FORCEINLINE void NativeReleaseFunction(NativeResult *Result)                                                \
    {                                                                                                                  \
        EOS_##CallNamespace##_##ResultEntryName##_Release(Result);                                                     \
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
#define REDPOINT_EOSSDK_API_CALL_SYNC_COPY_END()                                                                       \
public:                                                                                                                \
    static void Execute(                                                                                               \
        const FPlatformHandle &InHandle,                                                                               \
        const Options &InOptions,                                                                                      \
        EOS_EResult &OutResultCode,                                                                                    \
        Result &OutResult);                                                                                            \
    static void Execute(                                                                                               \
        NativeHandle InHandle,                                                                                         \
        const Options &InOptions,                                                                                      \
        EOS_EResult &OutResultCode,                                                                                    \
        Result &OutResult);                                                                                            \
                                                                                                                       \
private:                                                                                                               \
    static void MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator);          \
    static void MapResult(Result &Result, const NativeResult &NativeResult, NativeConverter &Converter);
#define REDPOINT_EOSSDK_API_CALL_SYNC_COPY_IMPL(CallName)                                                              \
    void F##CallName::Execute(                                                                                         \
        const FPlatformHandle &InHandle,                                                                               \
        const Options &InOptions,                                                                                      \
        EOS_EResult &OutResultCode,                                                                                    \
        Result &OutResult)                                                                                             \
    {                                                                                                                  \
        Execute(InHandle->Get<NativeHandle>(), InOptions, OutResultCode, OutResult);                                   \
    }                                                                                                                  \
    void F##CallName::Execute(                                                                                         \
        NativeHandle InHandle,                                                                                         \
        const Options &InOptions,                                                                                      \
        EOS_EResult &OutResultCode,                                                                                    \
        Result &OutResult)                                                                                             \
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
            OutResultCode = EOS_EResult::EOS_NoConnection;                                                             \
            OutResult = {};                                                                                            \
            return;                                                                                                    \
        }                                                                                                              \
                                                                                                                       \
        TSharedRef<NativeAllocator> Allocator = MakeShared<NativeAllocator>();                                         \
        TSharedRef<NativeConverter> Converter = MakeShared<NativeConverter>();                                         \
                                                                                                                       \
        NativeOptions _NativeOptions = {};                                                                             \
        _NativeOptions.ApiVersion = NativeOptionsVersion();                                                            \
        MapOptions(_NativeOptions, InOptions, *Allocator);                                                             \
                                                                                                                       \
        NativeResult *_NativeResult = nullptr;                                                                         \
        OutResultCode = NativeFunction(InHandle, &_NativeOptions, &_NativeResult);                                     \
        if (_NativeResult != nullptr)                                                                                  \
        {                                                                                                              \
            MapResult(OutResult, *_NativeResult, *Converter);                                                          \
        }                                                                                                              \
        UE_LOG(                                                                                                        \
            LogRedpointEOSAPI,                                                                                         \
            VeryVerbose,                                                                                               \
            TEXT("[complete] %s"),                                                                                     \
            *ConvertError(LogCallName(), TEXT("Sync copy call completed."), OutResultCode).ToLogString());             \
        return;                                                                                                        \
    }

} // namespace Private

} // namespace Redpoint::EOS::API
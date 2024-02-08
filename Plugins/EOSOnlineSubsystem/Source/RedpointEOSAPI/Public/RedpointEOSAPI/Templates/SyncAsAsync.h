// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Stats/Stats.h"

#include "RedpointEOSAPI/Error.h"
#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSAPI/Templates/ApiCallName.h"
#include "RedpointEOSAPI/Templates/Cdecl.h"
#include "RedpointEOSAPI/Templates/Sync.h"

namespace Redpoint::EOS::API
{

namespace Private
{

#define REDPOINT_EOSSDK_API_CALL_SYNC_AS_ASYNC_BEGIN(CallNamespace, CallName, CallVersion)                             \
    typedef EOS_H##CallNamespace NativeHandle;                                                                         \
    typedef Redpoint::EOS::API::Private::TNativeCallSyncInfo<decltype(EOS_##CallNamespace##_##CallName)>::OptionsType  \
        NativeOptions;                                                                                                 \
    struct NativeResult                                                                                                \
    {                                                                                                                  \
    public:                                                                                                            \
        /** Synthetic result code from synchronous API call. */                                                        \
        EOS_EResult ResultCode;                                                                                        \
    };                                                                                                                 \
    typedef Redpoint::EOS::API::Private::FApiCallNativeAllocator NativeAllocator;                                      \
    typedef Redpoint::EOS::API::Private::FApiCallNativeConverter NativeConverter;                                      \
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
#define REDPOINT_EOSSDK_API_CALL_SYNC_AS_ASYNC_END()                                                                   \
    typedef TDelegate<void(const Result &InResult)> CompletionDelegate;                                                \
                                                                                                                       \
private:                                                                                                               \
public:                                                                                                                \
    static void Execute(                                                                                               \
        const FPlatformHandle &InHandle,                                                                               \
        const Options &InOptions,                                                                                      \
        const CompletionDelegate &InCompletionDelegate);                                                               \
    static void Execute(                                                                                               \
        NativeHandle InHandle,                                                                                         \
        const Options &InOptions,                                                                                      \
        const CompletionDelegate &InCompletionDelegate);                                                               \
                                                                                                                       \
private:                                                                                                               \
    static void MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator);          \
    static void MapResult(Result &Result, const NativeResult &NativeResult, NativeConverter &Converter);
#define REDPOINT_EOSSDK_API_CALL_SYNC_AS_ASYNC_IMPL(CallName)                                                          \
    void F##CallName::Execute(                                                                                         \
        const FPlatformHandle &InHandle,                                                                               \
        const Options &InOptions,                                                                                      \
        const CompletionDelegate &InCompletionDelegate)                                                                \
    {                                                                                                                  \
        return Execute(InHandle->Get<NativeHandle>(), InOptions, InCompletionDelegate);                                \
    }                                                                                                                  \
    void F##CallName::Execute(                                                                                         \
        NativeHandle InHandle,                                                                                         \
        const Options &InOptions,                                                                                      \
        const CompletionDelegate &InCompletionDelegate)                                                                \
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
            NativeResult _DeadNativeResult;                                                                            \
            Result _DeadResult;                                                                                        \
            _DeadNativeResult.ResultCode = EOS_EResult::EOS_NoConnection;                                              \
            MapResult(_DeadResult, _DeadNativeResult, *MakeShared<NativeConverter>());                                 \
            InCompletionDelegate.ExecuteIfBound(_DeadResult);                                                          \
            return;                                                                                                    \
        }                                                                                                              \
                                                                                                                       \
        TSharedRef<NativeAllocator> Allocator = MakeShared<NativeAllocator>();                                         \
                                                                                                                       \
        NativeOptions _NativeOptions = {};                                                                             \
        _NativeOptions.ApiVersion = NativeOptionsVersion();                                                            \
        MapOptions(_NativeOptions, InOptions, *Allocator);                                                             \
                                                                                                                       \
        NativeResult _NativeResult;                                                                                    \
        _NativeResult.ResultCode = NativeFunction(InHandle, &_NativeOptions);                                          \
                                                                                                                       \
        UE_LOG(                                                                                                        \
            LogRedpointEOSAPI,                                                                                         \
            VeryVerbose,                                                                                               \
            TEXT("[complete] %s"),                                                                                     \
            *ConvertError(LogCallName(), TEXT("SyncAsAsync call completed."), _NativeResult.ResultCode)                \
                 .ToLogString());                                                                                      \
                                                                                                                       \
        Result _Result;                                                                                                \
        MapResult(_Result, _NativeResult, *MakeShared<NativeConverter>());                                             \
        InCompletionDelegate.ExecuteIfBound(_Result);                                                                  \
    }

} // namespace Private

} // namespace Redpoint::EOS::API
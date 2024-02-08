// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Stats/Stats.h"

#include "RedpointEOSAPI/Error.h"
#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSAPI/Templates/Allocator.h"
#include "RedpointEOSAPI/Templates/ApiCallName.h"
#include "RedpointEOSAPI/Templates/Async.h"
#include "RedpointEOSAPI/Templates/Cdecl.h"

namespace Redpoint::EOS::API
{

namespace Private
{

template <typename S> struct TNativeCallAsyncListCountInfo;
template <typename Handle, typename CountOptions>
struct TNativeCallAsyncListCountInfo<uint32_t(Handle, const CountOptions *)>
{
    using CountOptionsType = CountOptions;
};

template <typename S> struct TNativeCallAsyncListCopyByIndexInfo;
template <typename Handle, typename CopyOptions, typename ResultEntry>
struct TNativeCallAsyncListCopyByIndexInfo<EOS_EResult(Handle, const CopyOptions *, ResultEntry **)>
{
    using CopyOptionsType = CopyOptions;
    using ResultEntryType = ResultEntry;
};

#define REDPOINT_EOSSDK_API_CALL_ASYNC_LIST_BEGIN(                                                                     \
    CallNamespace,                                                                                                     \
    QueryCallName,                                                                                                     \
    QueryCallVersion,                                                                                                  \
    CountCallName,                                                                                                     \
    CountCallVersion,                                                                                                  \
    CopyByIndexCallName,                                                                                               \
    CopyByIndexCallVersion,                                                                                            \
    ResultEntryName)                                                                                                   \
private:                                                                                                               \
    typedef EOS_H##CallNamespace NativeHandle;                                                                         \
    typedef Redpoint::EOS::API::Private::TNativeCallAsyncInfo<                                                         \
        decltype(EOS_##CallNamespace##_##QueryCallName)>::OptionsType NativeQueryOptions;                              \
    typedef Redpoint::EOS::API::Private::TNativeCallAsyncInfo<                                                         \
        decltype(EOS_##CallNamespace##_##QueryCallName)>::ResultType NativeQueryResult;                                \
    typedef Redpoint::EOS::API::Private::TNativeCallAsyncListCountInfo<                                                \
        decltype(EOS_##CallNamespace##_##CountCallName)>::CountOptionsType NativeCountOptions;                         \
    typedef Redpoint::EOS::API::Private::TNativeCallAsyncListCopyByIndexInfo<                                          \
        decltype(EOS_##CallNamespace##_##CopyByIndexCallName)>::CopyOptionsType NativeCopyByIndexOptions;              \
    typedef Redpoint::EOS::API::Private::TNativeCallAsyncListCopyByIndexInfo<                                          \
        decltype(EOS_##CallNamespace##_##CopyByIndexCallName)>::ResultEntryType NativeCopyByIndexResult;               \
    typedef Redpoint::EOS::API::Private::FApiCallNativeAllocator NativeAllocator;                                      \
    typedef Redpoint::EOS::API::Private::FApiCallNativeConverter NativeConverter;                                      \
    static FORCEINLINE int NativeQueryOptionsVersion()                                                                 \
    {                                                                                                                  \
        return QueryCallVersion;                                                                                       \
    }                                                                                                                  \
    static FORCEINLINE int NativeCountOptionsVersion()                                                                 \
    {                                                                                                                  \
        return CountCallVersion;                                                                                       \
    }                                                                                                                  \
    static FORCEINLINE int NativeCopyByIndexOptionsVersion()                                                           \
    {                                                                                                                  \
        return CopyByIndexCallVersion;                                                                                 \
    }                                                                                                                  \
    static FORCEINLINE void NativeQueryFunction(                                                                       \
        NativeHandle Handle,                                                                                           \
        const NativeQueryOptions *Options,                                                                             \
        void *ClientData,                                                                                              \
        void(__REDPOINT_EOSSDK_CDECL_ATTR * Callback)(const NativeQueryResult *Data))                                  \
    {                                                                                                                  \
        EOS_##CallNamespace##_##QueryCallName(Handle, Options, ClientData, Callback);                                  \
    }                                                                                                                  \
    static FORCEINLINE uint32_t NativeCountFunction(NativeHandle Handle, const NativeCountOptions *Options)            \
    {                                                                                                                  \
        return EOS_##CallNamespace##_##CountCallName(Handle, Options);                                                 \
    }                                                                                                                  \
    static FORCEINLINE EOS_EResult NativeCopyByIndexFunction(                                                          \
        NativeHandle Handle,                                                                                           \
        const NativeCopyByIndexOptions *Options,                                                                       \
        NativeCopyByIndexResult **Result)                                                                              \
    {                                                                                                                  \
        return EOS_##CallNamespace##_##CopyByIndexCallName(Handle, Options, Result);                                   \
    }                                                                                                                  \
    static FORCEINLINE void NativeReleaseFunction(NativeCopyByIndexResult *Result)                                     \
    {                                                                                                                  \
        EOS_##CallNamespace##_##ResultEntryName##_Release(Result);                                                     \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *StatCallName()                                                                     \
    {                                                                                                                  \
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(CallNamespace)) TEXT("_")                      \
            TEXT(PREPROCESSOR_TO_STRING(QueryCallName));                                                               \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *StatCallCompletionName()                                                           \
    {                                                                                                                  \
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(CallNamespace)) TEXT("_")                      \
            TEXT(PREPROCESSOR_TO_STRING(QueryCallName)) TEXT("/Callback");                                             \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *StatCallCountName()                                                                \
    {                                                                                                                  \
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(CallNamespace)) TEXT("_")                      \
            TEXT(PREPROCESSOR_TO_STRING(QueryCallName)) TEXT("/Count");                                                \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *StatCallCopyByIndexName()                                                          \
    {                                                                                                                  \
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(CallNamespace)) TEXT("_")                      \
            TEXT(PREPROCESSOR_TO_STRING(QueryCallName)) TEXT("/CopyByIndex");                                          \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *LogCallQueryName()                                                                 \
    {                                                                                                                  \
        return TEXT(PREPROCESSOR_TO_STRING(EOS_##CallNamespace##_##QueryCallName));                                    \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *LogCallCountName()                                                                 \
    {                                                                                                                  \
        return TEXT(PREPROCESSOR_TO_STRING(EOS_##CallNamespace##_##CountCallName));                                    \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *LogCallCopyByIndexName()                                                           \
    {                                                                                                                  \
        return TEXT(PREPROCESSOR_TO_STRING(EOS_##CallNamespace##_##CopyByIndexCallName));                              \
    }                                                                                                                  \
                                                                                                                       \
public:
#define REDPOINT_EOSSDK_API_CALL_ASYNC_LIST_END()                                                                      \
    typedef TDelegate<void(EOS_EResult ResultCode, const TArray<ResultEntry> &ResultEntries)> CompletionDelegate;      \
                                                                                                                       \
private:                                                                                                               \
    class FHeapState                                                                                                   \
    {                                                                                                                  \
    public:                                                                                                            \
        NativeHandle _NativeHandle;                                                                                    \
        NativeQueryOptions _NativeQueryOptions;                                                                        \
        Options _Options;                                                                                              \
        CompletionDelegate _CompletionDelegate;                                                                        \
        TSharedPtr<NativeAllocator> _Allocator;                                                                        \
    };                                                                                                                 \
                                                                                                                       \
    static void __REDPOINT_EOSSDK_CDECL_ATTR HandleNativeQueryCallback(const NativeQueryResult *QueryData);            \
                                                                                                                       \
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
    static void MapQueryOptions(                                                                                       \
        NativeQueryOptions &NativeOptions,                                                                             \
        const Options &Options,                                                                                        \
        NativeAllocator &Allocator);                                                                                   \
    static void MapCountOptions(                                                                                       \
        NativeCountOptions &NativeOptions,                                                                             \
        const Options &Options,                                                                                        \
        NativeAllocator &Allocator);                                                                                   \
    static void MapCopyByIndexOptions(                                                                                 \
        NativeCopyByIndexOptions &NativeOptions,                                                                       \
        const Options &Options,                                                                                        \
        uint32_t Index,                                                                                                \
        NativeAllocator &Allocator);                                                                                   \
    static void MapCopyByIndexResult(                                                                                  \
        ResultEntry &Result,                                                                                           \
        const NativeCopyByIndexResult &NativeResult,                                                                   \
        NativeConverter &Converter);
#define REDPOINT_EOSSDK_API_CALL_ASYNC_LIST_IMPL(CallName)                                                             \
    void __REDPOINT_EOSSDK_CDECL_ATTR F##CallName::HandleNativeQueryCallback(const NativeQueryResult *QueryData)       \
    {                                                                                                                  \
        DECLARE_CYCLE_STAT(StatCallCompletionName(), STAT_Call_Completion, STATGROUP_RedpointEOS);                     \
        DECLARE_CYCLE_STAT(StatCallCountName(), STAT_Call_Count, STATGROUP_RedpointEOS);                               \
        DECLARE_CYCLE_STAT(StatCallCopyByIndexName(), STAT_Call_CopyByIndex, STATGROUP_RedpointEOS);                   \
        SCOPE_CYCLE_COUNTER(STAT_Call_Completion);                                                                     \
                                                                                                                       \
        if (!EOS_EResult_IsOperationComplete(QueryData->ResultCode))                                                   \
        {                                                                                                              \
            UE_LOG(LogRedpointEOSAPI, VeryVerbose, TEXT("[pending ] %s"), LogCallQueryName());                         \
            return;                                                                                                    \
        }                                                                                                              \
                                                                                                                       \
        UE_LOG(                                                                                                        \
            LogRedpointEOSAPI,                                                                                         \
            VeryVerbose,                                                                                               \
            TEXT("[queried ] %s"),                                                                                     \
            *ConvertError(LogCallQueryName(), TEXT("AsyncList call received query result."), QueryData->ResultCode)    \
                 .ToLogString());                                                                                      \
                                                                                                                       \
        FHeapState *HeapState = (FHeapState *)QueryData->ClientData;                                                   \
                                                                                                                       \
        TArray<ResultEntry> ResultEntries;                                                                             \
                                                                                                                       \
        if (QueryData->ResultCode != EOS_EResult::EOS_Success)                                                         \
        {                                                                                                              \
            HeapState->_CompletionDelegate.ExecuteIfBound(QueryData->ResultCode, ResultEntries);                       \
            return;                                                                                                    \
        }                                                                                                              \
                                                                                                                       \
        TSharedRef<NativeConverter> _Converter = MakeShared<NativeConverter>();                                        \
        uint32_t Count = 0;                                                                                            \
        {                                                                                                              \
            SCOPE_CYCLE_COUNTER(STAT_Call_Count);                                                                      \
            UE_LOG(LogRedpointEOSAPI, VeryVerbose, TEXT("[starting] %s"), LogCallCountName());                         \
            NativeCountOptions _NativeCountOptions = {};                                                               \
            _NativeCountOptions.ApiVersion = NativeCountOptionsVersion();                                              \
            MapCountOptions(_NativeCountOptions, HeapState->_Options, *HeapState->_Allocator);                         \
            Count = NativeCountFunction(HeapState->_NativeHandle, &_NativeCountOptions);                               \
            UE_LOG(                                                                                                    \
                LogRedpointEOSAPI,                                                                                     \
                VeryVerbose,                                                                                           \
                TEXT("[complete] %s"),                                                                                 \
                *ConvertError(                                                                                         \
                     LogCallCountName(),                                                                               \
                     *FString::Printf(TEXT("Count returned %d results."), Count),                                      \
                     EOS_EResult::EOS_Success)                                                                         \
                     .ToLogString());                                                                                  \
        }                                                                                                              \
                                                                                                                       \
        for (uint32_t Index = 0; Index < Count; Index++)                                                               \
        {                                                                                                              \
            SCOPE_CYCLE_COUNTER(STAT_Call_CopyByIndex);                                                                \
                                                                                                                       \
            UE_LOG(                                                                                                    \
                LogRedpointEOSAPI,                                                                                     \
                VeryVerbose,                                                                                           \
                TEXT("[starting] %s (index: %d)"),                                                                     \
                LogCallCopyByIndexName(),                                                                              \
                Index);                                                                                                \
            NativeCopyByIndexResult *_NativeResultEntry;                                                               \
            NativeCopyByIndexOptions _NativeCopyByIndexOptions = {};                                                   \
            _NativeCopyByIndexOptions.ApiVersion = NativeCopyByIndexOptionsVersion();                                  \
            MapCopyByIndexOptions(_NativeCopyByIndexOptions, HeapState->_Options, Index, *HeapState->_Allocator);      \
            EOS_EResult CopyResult =                                                                                   \
                NativeCopyByIndexFunction(HeapState->_NativeHandle, &_NativeCopyByIndexOptions, &_NativeResultEntry);  \
            if (CopyResult != EOS_EResult::EOS_Success || _NativeResultEntry == nullptr)                               \
            {                                                                                                          \
                UE_LOG(                                                                                                \
                    LogRedpointEOSAPI,                                                                                 \
                    Warning,                                                                                           \
                    TEXT("[complete] %s"),                                                                             \
                    *ConvertError(                                                                                     \
                         LogCallCopyByIndexName(),                                                                     \
                         *FString::Printf(TEXT("CopyByIndex returned error or nullptr."), Count),                      \
                         CopyResult)                                                                                   \
                         .ToLogString());                                                                              \
                continue;                                                                                              \
            }                                                                                                          \
                                                                                                                       \
            ResultEntry _ResultEntry;                                                                                  \
            MapCopyByIndexResult(_ResultEntry, *_NativeResultEntry, *_Converter);                                      \
            NativeReleaseFunction(_NativeResultEntry);                                                                 \
            ResultEntries.Add(_ResultEntry);                                                                           \
            UE_LOG(                                                                                                    \
                LogRedpointEOSAPI,                                                                                     \
                VeryVerbose,                                                                                           \
                TEXT("[complete] %s"),                                                                                 \
                *ConvertError(                                                                                         \
                     LogCallCopyByIndexName(),                                                                         \
                     *FString::Printf(TEXT("Copied result from index %d."), Index),                                    \
                     EOS_EResult::EOS_Success)                                                                         \
                     .ToLogString());                                                                                  \
        }                                                                                                              \
                                                                                                                       \
        UE_LOG(                                                                                                        \
            LogRedpointEOSAPI,                                                                                         \
            VeryVerbose,                                                                                               \
            TEXT("[complete] %s"),                                                                                     \
            *ConvertError(                                                                                             \
                 LogCallQueryName(),                                                                                   \
                 *FString::Printf(TEXT("AsyncList call completed with %d results."), ResultEntries.Num()),             \
                 QueryData->ResultCode)                                                                                \
                 .ToLogString());                                                                                      \
                                                                                                                       \
        HeapState->_CompletionDelegate.ExecuteIfBound(QueryData->ResultCode, ResultEntries);                           \
        delete HeapState;                                                                                              \
    }                                                                                                                  \
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
        UE_LOG(LogRedpointEOSAPI, VeryVerbose, TEXT("[starting] %s"), LogCallQueryName());                             \
                                                                                                                       \
        if (InHandle == nullptr)                                                                                       \
        {                                                                                                              \
            UE_LOG(                                                                                                    \
                LogRedpointEOSAPI,                                                                                     \
                VeryVerbose,                                                                                           \
                TEXT("[complete] %s"),                                                                                 \
                *ConvertError(                                                                                         \
                     LogCallQueryName(),                                                                               \
                     TEXT("The platform instance has been shutdown, so SDK calls can not be made."),                   \
                     EOS_EResult::EOS_NoConnection)                                                                    \
                     .ToLogString());                                                                                  \
            InCompletionDelegate.ExecuteIfBound(EOS_EResult::EOS_NoConnection, TArray<ResultEntry>());                 \
            return;                                                                                                    \
        }                                                                                                              \
                                                                                                                       \
        TSharedRef<NativeAllocator> Allocator = MakeShared<NativeAllocator>();                                         \
                                                                                                                       \
        NativeQueryOptions _NativeQueryOptions;                                                                        \
        _NativeQueryOptions.ApiVersion = NativeQueryOptionsVersion();                                                  \
        MapQueryOptions(_NativeQueryOptions, InOptions, *Allocator);                                                   \
                                                                                                                       \
        FHeapState *HeapState = new FHeapState();                                                                      \
        HeapState->_NativeHandle = InHandle;                                                                           \
        HeapState->_NativeQueryOptions = _NativeQueryOptions;                                                          \
        HeapState->_Options = InOptions;                                                                               \
        HeapState->_CompletionDelegate = InCompletionDelegate;                                                         \
        HeapState->_Allocator = Allocator;                                                                             \
                                                                                                                       \
        NativeQueryFunction(InHandle, &HeapState->_NativeQueryOptions, HeapState, &HandleNativeQueryCallback);         \
    }

} // namespace Private

} // namespace Redpoint::EOS::API
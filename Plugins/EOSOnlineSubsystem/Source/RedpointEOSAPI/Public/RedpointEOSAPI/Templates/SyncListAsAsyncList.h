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
#include "RedpointEOSAPI/Templates/Sync.h"

namespace Redpoint::EOS::API
{

namespace Private
{

template <typename S> struct TNativeCallSyncListGetByIndexInfo;
template <typename Handle, typename GetOptions, typename ResultEntry>
struct TNativeCallSyncListGetByIndexInfo<const ResultEntry *(Handle, const GetOptions *)>
{
    using GetOptionsType = GetOptions;
    using ResultEntryType = ResultEntry;
};

#define REDPOINT_EOSSDK_API_CALL_SYNC_LIST_AS_ASYNC_LIST_BEGIN(                                                        \
    CallNamespace,                                                                                                     \
    CountCallName,                                                                                                     \
    CountCallVersion,                                                                                                  \
    GetByIndexCallName,                                                                                                \
    GetByIndexCallVersion)                                                                                             \
private:                                                                                                               \
    typedef EOS_H##CallNamespace NativeHandle;                                                                         \
    typedef Redpoint::EOS::API::Private::TNativeCallAsyncListCountInfo<                                                \
        decltype(EOS_##CallNamespace##_##CountCallName)>::CountOptionsType NativeCountOptions;                         \
    typedef Redpoint::EOS::API::Private::TNativeCallSyncListGetByIndexInfo<                                            \
        decltype(EOS_##CallNamespace##_##GetByIndexCallName)>::GetOptionsType NativeGetByIndexOptions;                 \
    typedef Redpoint::EOS::API::Private::TNativeCallSyncListGetByIndexInfo<                                            \
        decltype(EOS_##CallNamespace##_##GetByIndexCallName)>::ResultEntryType NativeGetByIndexResult;                 \
    typedef NativeGetByIndexOptions NativeCopyByIndexOptions;                                                          \
    typedef NativeGetByIndexResult NativeCopyByIndexResult;                                                            \
    typedef Redpoint::EOS::API::Private::FApiCallNativeAllocator NativeAllocator;                                      \
    typedef Redpoint::EOS::API::Private::FApiCallNativeConverter NativeConverter;                                      \
    static FORCEINLINE int NativeCountOptionsVersion()                                                                 \
    {                                                                                                                  \
        return CountCallVersion;                                                                                       \
    }                                                                                                                  \
    static FORCEINLINE int NativeGetByIndexOptionsVersion()                                                            \
    {                                                                                                                  \
        return GetByIndexCallVersion;                                                                                  \
    }                                                                                                                  \
    static FORCEINLINE uint32_t NativeCountFunction(NativeHandle Handle, const NativeCountOptions *Options)            \
    {                                                                                                                  \
        return EOS_##CallNamespace##_##CountCallName(Handle, Options);                                                 \
    }                                                                                                                  \
    static FORCEINLINE const NativeGetByIndexResult *NativeGetByIndexFunction(                                         \
        NativeHandle Handle,                                                                                           \
        const NativeGetByIndexOptions *Options)                                                                        \
    {                                                                                                                  \
        return EOS_##CallNamespace##_##GetByIndexCallName(Handle, Options);                                            \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *StatCallCountName()                                                                \
    {                                                                                                                  \
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(CallNamespace)) TEXT("_")                      \
            TEXT(PREPROCESSOR_TO_STRING(GetByIndexCallVersion)) TEXT("/Count");                                        \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *StatCallGetByIndexName()                                                           \
    {                                                                                                                  \
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(CallNamespace)) TEXT("_")                      \
            TEXT(PREPROCESSOR_TO_STRING(GetByIndexCallVersion)) TEXT("/GetByIndex");                                   \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *LogCallCountName()                                                                 \
    {                                                                                                                  \
        return TEXT(PREPROCESSOR_TO_STRING(EOS_##CallNamespace##_##CountCallName));                                    \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *LogCallGetByIndexName()                                                            \
    {                                                                                                                  \
        return TEXT(PREPROCESSOR_TO_STRING(EOS_##CallNamespace##_##GetByIndexCallName));                               \
    }                                                                                                                  \
                                                                                                                       \
public:
#define REDPOINT_EOSSDK_API_CALL_SYNC_LIST_AS_ASYNC_LIST_END()                                                         \
    typedef TDelegate<void(EOS_EResult ResultCode, const TArray<ResultEntry> &ResultEntries)> CompletionDelegate;      \
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
#define REDPOINT_EOSSDK_API_CALL_SYNC_LIST_AS_ASYNC_LIST_IMPL(CallName)                                                \
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
        DECLARE_CYCLE_STAT(StatCallCountName(), STAT_Call_Count, STATGROUP_RedpointEOS);                               \
        DECLARE_CYCLE_STAT(StatCallGetByIndexName(), STAT_Call_GetByIndex, STATGROUP_RedpointEOS);                     \
                                                                                                                       \
        UE_LOG(LogRedpointEOSAPI, VeryVerbose, TEXT("[starting] %s"), LogCallGetByIndexName());                        \
                                                                                                                       \
        if (InHandle == nullptr)                                                                                       \
        {                                                                                                              \
            UE_LOG(                                                                                                    \
                LogRedpointEOSAPI,                                                                                     \
                VeryVerbose,                                                                                           \
                TEXT("[complete] %s"),                                                                                 \
                *ConvertError(                                                                                         \
                     LogCallGetByIndexName(),                                                                          \
                     TEXT("The platform instance has been shutdown, so SDK calls can not be made."),                   \
                     EOS_EResult::EOS_NoConnection)                                                                    \
                     .ToLogString());                                                                                  \
            InCompletionDelegate.ExecuteIfBound(EOS_EResult::EOS_NoConnection, TArray<ResultEntry>());                 \
            return;                                                                                                    \
        }                                                                                                              \
                                                                                                                       \
        TSharedRef<NativeAllocator> _Allocator = MakeShared<NativeAllocator>();                                        \
        TSharedRef<NativeConverter> _Converter = MakeShared<NativeConverter>();                                        \
                                                                                                                       \
        TArray<ResultEntry> ResultEntries;                                                                             \
                                                                                                                       \
        uint32_t Count = 0;                                                                                            \
        {                                                                                                              \
            SCOPE_CYCLE_COUNTER(STAT_Call_Count);                                                                      \
            UE_LOG(LogRedpointEOSAPI, VeryVerbose, TEXT("[starting] %s"), LogCallCountName());                         \
            NativeCountOptions _NativeCountOptions = {};                                                               \
            _NativeCountOptions.ApiVersion = NativeCountOptionsVersion();                                              \
            MapCountOptions(_NativeCountOptions, InOptions, *_Allocator);                                              \
            Count = NativeCountFunction(InHandle, &_NativeCountOptions);                                               \
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
            SCOPE_CYCLE_COUNTER(STAT_Call_GetByIndex);                                                                 \
                                                                                                                       \
            UE_LOG(LogRedpointEOSAPI, VeryVerbose, TEXT("[starting] %s (index: %d)"), LogCallGetByIndexName(), Index); \
            NativeGetByIndexOptions _NativeGetByIndexOptions = {};                                                     \
            _NativeGetByIndexOptions.ApiVersion = NativeGetByIndexOptionsVersion();                                    \
            MapCopyByIndexOptions(_NativeGetByIndexOptions, InOptions, Index, *_Allocator);                            \
            const NativeGetByIndexResult *_NativeResultEntry =                                                         \
                NativeGetByIndexFunction(InHandle, &_NativeGetByIndexOptions);                                         \
            if (_NativeResultEntry == nullptr)                                                                         \
            {                                                                                                          \
                UE_LOG(                                                                                                \
                    LogRedpointEOSAPI,                                                                                 \
                    Warning,                                                                                           \
                    TEXT("[informat] %s: Unexpected nullptr returned from GetByIndex call."),                          \
                    LogCallGetByIndexName());                                                                          \
                continue;                                                                                              \
            }                                                                                                          \
                                                                                                                       \
            ResultEntry _ResultEntry;                                                                                  \
            MapCopyByIndexResult(_ResultEntry, *_NativeResultEntry, *_Converter);                                      \
            ResultEntries.Add(_ResultEntry);                                                                           \
            UE_LOG(                                                                                                    \
                LogRedpointEOSAPI,                                                                                     \
                VeryVerbose,                                                                                           \
                TEXT("[complete] %s"),                                                                                 \
                *ConvertError(                                                                                         \
                     LogCallGetByIndexName(),                                                                          \
                     *FString::Printf(TEXT("Retrieved result from index %d."), Index),                                 \
                     EOS_EResult::EOS_Success)                                                                         \
                     .ToLogString());                                                                                  \
        }                                                                                                              \
                                                                                                                       \
        UE_LOG(                                                                                                        \
            LogRedpointEOSAPI,                                                                                         \
            VeryVerbose,                                                                                               \
            TEXT("[complete] %s"),                                                                                     \
            *ConvertError(                                                                                             \
                 LogCallGetByIndexName(),                                                                              \
                 TEXT("SyncListAsAsyncList call completed."),                                                          \
                 EOS_EResult::EOS_Success)                                                                             \
                 .ToLogString());                                                                                      \
                                                                                                                       \
        InCompletionDelegate.ExecuteIfBound(EOS_EResult::EOS_Success, ResultEntries);                                  \
    }

} // namespace Private

} // namespace Redpoint::EOS::API
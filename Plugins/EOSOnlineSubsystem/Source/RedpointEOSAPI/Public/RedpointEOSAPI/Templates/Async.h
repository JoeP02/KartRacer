// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Stats/Stats.h"

#include "RedpointEOSAPI/Error.h"
#include "RedpointEOSAPI/Logging.h"
#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSAPI/Templates/Allocator.h"
#include "RedpointEOSAPI/Templates/ApiCallName.h"
#include "RedpointEOSAPI/Templates/Cdecl.h"

namespace Redpoint::EOS::API
{

namespace Private
{

template <typename S> struct TNativeCallAsyncInfo;
template <typename Handle, typename Options, typename Result>
struct TNativeCallAsyncInfo<void(Handle, const Options *, void *, void(__REDPOINT_EOSSDK_CDECL_ATTR *)(const Result *))>
{
    using HandleType = Handle;
    using OptionsType = Options;
    using ResultType = Result;
};

#define REDPOINT_EOSSDK_API_CALL_ASYNC_BEGIN(CallNamespace, CallName, CallVersion)                                     \
private:                                                                                                               \
    typedef EOS_H##CallNamespace NativeHandle;                                                                         \
    typedef Redpoint::EOS::API::Private::TNativeCallAsyncInfo<decltype(EOS_##CallNamespace##_##CallName)>::OptionsType \
        NativeOptions;                                                                                                 \
    typedef Redpoint::EOS::API::Private::TNativeCallAsyncInfo<decltype(EOS_##CallNamespace##_##CallName)>::ResultType  \
        NativeResult;                                                                                                  \
    typedef Redpoint::EOS::API::Private::FApiCallNativeAllocator NativeAllocator;                                      \
    typedef Redpoint::EOS::API::Private::FApiCallNativeConverter NativeConverter;                                      \
    static FORCEINLINE int NativeOptionsVersion()                                                                      \
    {                                                                                                                  \
        return CallVersion;                                                                                            \
    }                                                                                                                  \
    static FORCEINLINE void NativeFunction(                                                                            \
        NativeHandle Handle,                                                                                           \
        const NativeOptions *Options,                                                                                  \
        void *ClientData,                                                                                              \
        void(__REDPOINT_EOSSDK_CDECL_ATTR * Callback)(const NativeResult *Data))                                       \
    {                                                                                                                  \
        EOS_##CallNamespace##_##CallName(Handle, Options, ClientData, Callback);                                       \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *StatCallName()                                                                     \
    {                                                                                                                  \
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(CallNamespace)) TEXT("_")                      \
            TEXT(PREPROCESSOR_TO_STRING(CallName));                                                                    \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *StatCallCompletionName()                                                           \
    {                                                                                                                  \
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(CallNamespace)) TEXT("_")                      \
            TEXT(PREPROCESSOR_TO_STRING(CallName)) TEXT("/Callback");                                                  \
    }                                                                                                                  \
    static FORCEINLINE const TCHAR *LogCallName()                                                                      \
    {                                                                                                                  \
        return TEXT(PREPROCESSOR_TO_STRING(EOS_##CallNamespace##_##CallName));                                         \
    }                                                                                                                  \
                                                                                                                       \
public:
#define REDPOINT_EOSSDK_API_CALL_ASYNC_END()                                                                           \
    typedef TDelegate<void(const Result &InResult)> CompletionDelegate;                                                \
                                                                                                                       \
private:                                                                                                               \
    class FHeapState                                                                                                   \
    {                                                                                                                  \
    public:                                                                                                            \
        NativeOptions _NativeOptions = {};                                                                             \
        CompletionDelegate _CompletionDelegate;                                                                        \
        TSharedPtr<NativeAllocator> _Allocator;                                                                        \
    };                                                                                                                 \
                                                                                                                       \
    static void __REDPOINT_EOSSDK_CDECL_ATTR HandleNativeCallback(const NativeResult *Data);                           \
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
    static void MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator);          \
    static void MapResult(Result &Result, const NativeResult &NativeResult, NativeConverter &Converter);
#define REDPOINT_EOSSDK_API_CALL_ASYNC_IMPL(CallName)                                                                  \
    void __REDPOINT_EOSSDK_CDECL_ATTR F##CallName::HandleNativeCallback(const NativeResult *Data)                      \
    {                                                                                                                  \
        DECLARE_CYCLE_STAT(StatCallCompletionName(), STAT_Call_Completion, STATGROUP_RedpointEOS);                     \
        SCOPE_CYCLE_COUNTER(STAT_Call_Completion);                                                                     \
                                                                                                                       \
        if (!EOS_EResult_IsOperationComplete(Data->ResultCode))                                                        \
        {                                                                                                              \
            UE_LOG(LogRedpointEOSAPI, VeryVerbose, TEXT("[pending ] %s"), LogCallName());                              \
            return;                                                                                                    \
        }                                                                                                              \
                                                                                                                       \
        UE_LOG(                                                                                                        \
            LogRedpointEOSAPI,                                                                                         \
            VeryVerbose,                                                                                               \
            TEXT("[complete] %s"),                                                                                     \
            *ConvertError(LogCallName(), TEXT("Async call completed."), Data->ResultCode).ToLogString());              \
                                                                                                                       \
        FHeapState *HeapState = (FHeapState *)Data->ClientData;                                                        \
        Result _Result;                                                                                                \
        MapResult(_Result, *Data, *MakeShared<NativeConverter>());                                                     \
        HeapState->_CompletionDelegate.ExecuteIfBound(_Result);                                                        \
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
            Result _DeadResult;                                                                                        \
            _DeadResult.ResultCode = EOS_EResult::EOS_NoConnection;                                                    \
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
        FHeapState *HeapState = new FHeapState();                                                                      \
        HeapState->_NativeOptions = _NativeOptions;                                                                    \
        HeapState->_CompletionDelegate = InCompletionDelegate;                                                         \
        HeapState->_Allocator = Allocator;                                                                             \
                                                                                                                       \
        NativeFunction(InHandle, &HeapState->_NativeOptions, HeapState, &HandleNativeCallback);                        \
    }

} // namespace Private

} // namespace Redpoint::EOS::API
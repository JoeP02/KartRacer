// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "RedpointEOSAPI/Templates.h"

#include "RedpointEOSAPI/SDK.h"

namespace Redpoint::EOS::API::Platform
{

class REDPOINTEOSAPI_API FCreate
{
private:
    typedef EOS_Platform_Options NativeOptions;
    typedef Redpoint::EOS::API::Private::FApiCallNativeAllocator NativeAllocator;
    typedef Redpoint::EOS::API::Private::FApiCallNativeConverter NativeConverter;
    static FORCEINLINE int NativeOptionsVersion()
    {
        return EOS_PLATFORM_OPTIONS_API_LATEST;
    }
    static FORCEINLINE const TCHAR *StatCallName()
    {
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(Platform)) TEXT("_")
            TEXT(PREPROCESSOR_TO_STRING(Create));
    }
    static FORCEINLINE const TCHAR *LogCallName()
    {
        return TEXT(PREPROCESSOR_TO_STRING(EOS_Platform_Create));
    }

public:
    class Options
    {
    public:
        const ParamHelpers::TRequired<bool> bIsServer;
        const ParamHelpers::TRequired<FString> EncryptionKey;
        const ParamHelpers::TRequired<FString> CacheDirectory;
        const ParamHelpers::TRequired<FString> OverrideCountryCode;
        const ParamHelpers::TRequired<FString> OverrideLocaleCode;
        const ParamHelpers::TRequired<uint64_t> Flags;
        const ParamHelpers::TRequired<FString> ProductId;
        const ParamHelpers::TRequired<FString> SandboxId;
        const ParamHelpers::TRequired<FString> DeploymentId;
        const ParamHelpers::TRequired<FString> ClientId;
        const ParamHelpers::TRequired<FString> ClientSecret;
        const ParamHelpers::TRequired<EOS_Platform_RTCOptions*> RTCOptions;
    };

    typedef EOS_HPlatform Result;

public:
    static Result Execute(const Options &InOptions);

private:
    static void MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator);
};

} // namespace Redpoint::EOS::API::Platform
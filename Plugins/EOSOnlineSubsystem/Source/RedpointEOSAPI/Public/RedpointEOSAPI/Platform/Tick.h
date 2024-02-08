// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "RedpointEOSAPI/Templates.h"

#include "RedpointEOSAPI/SDK.h"

namespace Redpoint::EOS::API::Platform
{

class REDPOINTEOSAPI_API FTick
{
private:
    typedef EOS_HPlatform NativeHandle;
    static FORCEINLINE void NativeFunction(NativeHandle Handle)
    {
        EOS_Platform_Tick(Handle);
    }
    static FORCEINLINE const TCHAR *StatCallName()
    {
        return TEXT("RedpointEOS/API/EOS_") TEXT(PREPROCESSOR_TO_STRING(Platform)) TEXT("_")
            TEXT(PREPROCESSOR_TO_STRING(Tick));
    }
    static FORCEINLINE const TCHAR *LogCallName()
    {
        return TEXT(PREPROCESSOR_TO_STRING(EOS_Platform_Tick));
    }

public:
    static void Execute(const FPlatformHandle &InHandle);
};

} // namespace Redpoint::EOS::API::Platform
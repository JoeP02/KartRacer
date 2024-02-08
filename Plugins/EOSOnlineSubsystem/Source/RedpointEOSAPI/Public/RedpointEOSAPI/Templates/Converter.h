// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HAL/UnrealMemory.h"
#include "Containers/UnrealString.h"

namespace Redpoint::EOS::API
{

namespace Private
{

class FApiCallNativeConverter
{
public:
    FApiCallNativeConverter() = default;
    FApiCallNativeConverter(const FApiCallNativeConverter &) = delete;
    FApiCallNativeConverter(FApiCallNativeConverter &&) = delete;
    ~FApiCallNativeConverter() = default;
    FString FromAnsi(const char* InString);
    FString FromUtf8(const char* InString);
};

} // namespace Private
} // namespace Redpoint::EOS::API
// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSAPI/SDK.h"

namespace Redpoint::EOS::Core
{

class FSDKAllocator
{
public:
    static void *Allocate(size_t SizeInBytes, size_t Alignment);
    static void *Reallocate(void *Pointer, size_t SizeInBytes, size_t Alignment);
    static void Release(void *Pointer);
};

} // namespace Redpoint::EOS::Core
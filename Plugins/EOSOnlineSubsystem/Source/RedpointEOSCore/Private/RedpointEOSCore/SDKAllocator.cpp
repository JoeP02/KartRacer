// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSCore/SDKAllocator.h"

namespace Redpoint::EOS::Core
{

void *FSDKAllocator::Allocate(size_t SizeInBytes, size_t Alignment)
{
    return FMemory::Malloc(SizeInBytes, Alignment);
}

void *FSDKAllocator::Reallocate(void *Pointer, size_t SizeInBytes, size_t Alignment)
{
    return FMemory::Realloc(Pointer, SizeInBytes, Alignment);
}

void FSDKAllocator::Release(void *Pointer)
{
    FMemory::Free(Pointer);
}

} // namespace Redpoint::EOS::Core
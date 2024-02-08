// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HAL/UnrealMemory.h"
#include "Containers/UnrealString.h"

namespace Redpoint::EOS::API
{

namespace Private
{

class FApiCallNativeAllocator
{
private:
    TArray<void *> Buffers;

public:
    enum class EAllocationFlags : uint8_t
    {
		// Default allocation behaviour.
		Default,

		// Return nullptr instead of allocating an empty string if the
		// original FString is empty.
		ReturnNullptrIfEmptyString,
	};

    FApiCallNativeAllocator() = default;
    FApiCallNativeAllocator(const FApiCallNativeAllocator &) = delete;
    FApiCallNativeAllocator(FApiCallNativeAllocator &&) = delete;
    ~FApiCallNativeAllocator();
    const char *AsAnsi(const FString &InString, EAllocationFlags InFlags = EAllocationFlags::Default);
    const char *AsUtf8(const FString &InString, EAllocationFlags InFlags = EAllocationFlags::Default);
    template <typename T> T &Allocate()
    {
        static_assert(std::is_trivially_copyable<T>::value);
        void *Buffer = FMemory::MallocZeroed(sizeof(T));
        Buffers.Add(Buffer);
        return *((T *)Buffer);
    }
};

} // namespace Private
} // namespace Redpoint::EOS::API
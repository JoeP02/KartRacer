// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/Templates/Allocator.h"

namespace Redpoint::EOS::API
{

namespace Private
{

FApiCallNativeAllocator::~FApiCallNativeAllocator()
{
    for (const auto &Buffer : Buffers)
    {
        FMemory::Free((void *)Buffer);
    }
}

const char *FApiCallNativeAllocator::AsAnsi(
    const FString &InString,
    EAllocationFlags InFlags)
{
	if (InFlags == EAllocationFlags::ReturnNullptrIfEmptyString &&
		InString.IsEmpty())
	{
		return nullptr;
	}
    auto StrBuf = StringCast<ANSICHAR>(*InString);
    char *CharPtr = (char *)FMemory::MallocZeroed(StrBuf.Length() + 1);
    FMemory::Memcpy((void *)CharPtr, (const void *)StrBuf.Get(), StrBuf.Length());
    Buffers.Add(CharPtr);
    return CharPtr;
}

const char *FApiCallNativeAllocator::AsUtf8(
    const FString &InString,
    EAllocationFlags InFlags)
{
    if (InFlags == EAllocationFlags::ReturnNullptrIfEmptyString && InString.IsEmpty())
    {
        return nullptr;
    }
    auto StrBuf = FTCHARToUTF8(*InString);
    char *CharPtr = (char *)FMemory::MallocZeroed(StrBuf.Length() + 1);
    FMemory::Memcpy((void *)CharPtr, (const void *)StrBuf.Get(), StrBuf.Length());
    Buffers.Add(CharPtr);
    return CharPtr;
}

} // namespace Private

} // namespace Redpoint::EOS::API
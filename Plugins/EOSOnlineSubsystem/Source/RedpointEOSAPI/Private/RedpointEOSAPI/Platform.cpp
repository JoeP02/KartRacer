// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/Platform.h"

namespace Redpoint::EOS::API
{

FPlatformInstance::FPlatformInstance()
    : bIsShutdown(true)
    , Instance(nullptr)
{
}

FPlatformInstance::FPlatformInstance(EOS_HPlatform InInstance)
    : bIsShutdown(false)
    , Instance(InInstance)
{
    checkf(Instance != nullptr, TEXT("EOS_HPlatform instance must not be null when instantiating PlatformInstance."));
}

FPlatformInstance::~FPlatformInstance()
{
}

FPlatformHandle FPlatformInstance::CreateDeadWithNoInstance()
{
    return MakeShareable(new FPlatformInstance());
}

void FPlatformInstance::ForceShutdown()
{
    EOS_Platform_Release(this->Instance);
    this->bIsShutdown = true;
    this->Instance = nullptr;
}

bool FPlatformInstance::IsShutdown() const
{
    return this->bIsShutdown;
}

Private::FPlatformRefCountedHandleInternal::FPlatformRefCountedHandleInternal(const FPlatformHandle &InInstance)
    : _Instance(InInstance)
{
}

Private::FPlatformRefCountedHandleInternal::~FPlatformRefCountedHandleInternal()
{
    _Instance->ForceShutdown();
}

const FPlatformHandle &Private::FPlatformRefCountedHandleInternal::Instance() const
{
    return _Instance;
}

FPlatformRefCountedHandle MakeRefCountedPlatformHandle(const FPlatformHandle &Handle)
{
    return MakeShared<Private::FPlatformRefCountedHandleInternal>(Handle);
}

} // namespace Redpoint::EOS::API
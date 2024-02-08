// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/Platform/Create.h"

namespace Redpoint::EOS::API::Platform
{

FCreate::Result FCreate::Execute(const Options &InOptions)
{
    DECLARE_CYCLE_STAT(StatCallName(), STAT_Call, STATGROUP_RedpointEOS);
    SCOPE_CYCLE_COUNTER(STAT_Call);

    UE_LOG(LogRedpointEOSAPI, VeryVerbose, TEXT("[starting] %s"), LogCallName());

    TSharedRef<NativeAllocator> Allocator = MakeShared<NativeAllocator>();

    NativeOptions _NativeOptions = {};
    _NativeOptions.ApiVersion = NativeOptionsVersion();
    MapOptions(_NativeOptions, InOptions, *Allocator);

    return EOS_Platform_Create(&_NativeOptions);
}

void FCreate::MapOptions(NativeOptions &NativeOptions, const Options &Options, NativeAllocator &Allocator)
{
    NativeOptions.bIsServer = *Options.bIsServer;
    NativeOptions.EncryptionKey = Allocator.AsUtf8(
        Options.EncryptionKey,
        Private::FApiCallNativeAllocator::EAllocationFlags::ReturnNullptrIfEmptyString);
    NativeOptions.CacheDirectory = Allocator.AsUtf8(
        Options.CacheDirectory,
        Private::FApiCallNativeAllocator::EAllocationFlags::ReturnNullptrIfEmptyString);
    NativeOptions.OverrideCountryCode = nullptr;
    NativeOptions.OverrideLocaleCode = nullptr;
    NativeOptions.Flags = *Options.Flags;
    NativeOptions.ProductId = Allocator.AsUtf8(Options.ProductId);
    NativeOptions.SandboxId = Allocator.AsUtf8(Options.SandboxId);
    NativeOptions.DeploymentId = Allocator.AsUtf8(Options.DeploymentId);
    NativeOptions.ClientCredentials.ClientId = Allocator.AsUtf8(Options.ClientId);
    NativeOptions.ClientCredentials.ClientSecret = Allocator.AsUtf8(Options.ClientSecret);
    NativeOptions.RTCOptions = *Options.RTCOptions;

}

} // namespace Redpoint::EOS::API::Connect
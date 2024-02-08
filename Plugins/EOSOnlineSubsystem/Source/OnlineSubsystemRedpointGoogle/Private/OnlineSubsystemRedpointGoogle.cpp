// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointGoogle.h"

#include "LogRedpointGoogle.h"
#include "OnlineIdentityInterfaceRedpointGoogle.h"
#include "OnlinePurchaseInterfaceRedpointGoogle.h"
#include "OnlineStoreInterfaceV2RedpointGoogle.h"

#if EOS_GOOGLE_ENABLED

FOnlineSubsystemRedpointGoogle::FOnlineSubsystemRedpointGoogle(FName InInstanceName)
    : FOnlineSubsystemImplBase(REDPOINT_GOOGLE_SUBSYSTEM, InInstanceName)
    , IdentityImpl(nullptr)
    , StoreV2Impl(nullptr)
    , PurchaseImpl(nullptr)
{
}

FOnlineSubsystemRedpointGoogle::~FOnlineSubsystemRedpointGoogle()
{
}

bool FOnlineSubsystemRedpointGoogle::IsEnabled() const
{
    return true;
}

IOnlineIdentityPtr FOnlineSubsystemRedpointGoogle::GetIdentityInterface() const
{
    return this->IdentityImpl;
}

IOnlineStoreV2Ptr FOnlineSubsystemRedpointGoogle::GetStoreV2Interface() const
{
    return this->StoreV2Impl;
}

IOnlinePurchasePtr FOnlineSubsystemRedpointGoogle::GetPurchaseInterface() const
{
    return this->PurchaseImpl;
}

bool FOnlineSubsystemRedpointGoogle::Init()
{
    this->IdentityImpl = MakeShared<FOnlineIdentityInterfaceRedpointGoogle, ESPMode::ThreadSafe>();
    this->StoreV2Impl =
        MakeShared<FOnlineStoreInterfaceV2RedpointGoogle, ESPMode::ThreadSafe>(this->IdentityImpl.ToSharedRef());
    this->PurchaseImpl =
        MakeShared<FOnlinePurchaseInterfaceRedpointGoogle, ESPMode::ThreadSafe>(this->IdentityImpl.ToSharedRef());

    return true;
}

bool FOnlineSubsystemRedpointGoogle::Tick(float DeltaTime)
{
    return FOnlineSubsystemImpl::Tick(DeltaTime);
}

template <typename T, ESPMode Mode> void DestructInterface(TSharedPtr<T, Mode> &Ref, const TCHAR *Name)
{
    if (Ref.IsValid())
    {
        ensureMsgf(
            Ref.IsUnique(),
            TEXT(
                "Interface is not unique during shutdown of Redpoint Google subsystem: %s. "
                "This indicates you have a TSharedPtr<> or IOnline... in your code that is holding a reference open to "
                "the interface longer than the lifetime of the online subsystem. You should use TWeakPtr<> "
                "to hold references to interfaces in class fields to prevent lifetime issues"),
            Name);
        Ref = nullptr;
    }
}

bool FOnlineSubsystemRedpointGoogle::Shutdown()
{
    DestructInterface(this->PurchaseImpl, TEXT("IOnlinePurchase"));
    DestructInterface(this->StoreV2Impl, TEXT("IOnlineStoreV2"));
    DestructInterface(this->IdentityImpl, TEXT("IOnlineIdentity"));

    return true;
}

FString FOnlineSubsystemRedpointGoogle::GetAppId() const
{
    return TEXT("");
}

FText FOnlineSubsystemRedpointGoogle::GetOnlineServiceName() const
{
    return FText::GetEmpty();
}

#endif
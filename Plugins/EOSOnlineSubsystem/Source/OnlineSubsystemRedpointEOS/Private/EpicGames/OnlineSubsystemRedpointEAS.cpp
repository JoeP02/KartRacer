// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_HAS_AUTHENTICATION

#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineSubsystemRedpointEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineFriendsInterfaceEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineIdentityInterfaceEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlinePresenceInterfaceEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineUserInterfaceEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineSubsystemRedpointEOS.h"

EOS_ENABLE_STRICT_WARNINGS

template <typename T, ESPMode Mode> void DestructInterface(TSharedPtr<T, Mode> &Ref, const TCHAR *Name)
{
    if (Ref.IsValid())
    {
        ensureMsgf(
            Ref.IsUnique(),
            TEXT(
                "Interface is not unique during shutdown of EAS Online Subsystem: %s. "
                "This indicates you have a TSharedPtr<> or IOnline... in your code that is holding a reference open to "
                "the interface longer than the lifetime of the online subsystem. You should use TWeakPtr<> "
                "to hold references to interfaces in class fields to prevent lifetime issues"),
            Name);
        Ref = nullptr;
    }
}

FOnlineSubsystemRedpointEAS::FOnlineSubsystemRedpointEAS(
    FName InInstanceName,
    TSharedRef<FOnlineSubsystemEOS, ESPMode::ThreadSafe> InParentEOS)
    : FOnlineSubsystemImpl(REDPOINT_EAS_SUBSYSTEM, InInstanceName)
    , ParentEOS(MoveTemp(InParentEOS))
{
}

IOnlineFriendsPtr FOnlineSubsystemRedpointEAS::GetFriendsInterface() const
{
    return this->FriendsImpl;
}

IOnlineIdentityPtr FOnlineSubsystemRedpointEAS::GetIdentityInterface() const
{
    return this->IdentityImpl;
}

IOnlinePresencePtr FOnlineSubsystemRedpointEAS::GetPresenceInterface() const
{
    return this->PresenceImpl;
}

IOnlineUserPtr FOnlineSubsystemRedpointEAS::GetUserInterface() const
{
    return this->UserImpl;
}

IOnlineEntitlementsPtr FOnlineSubsystemRedpointEAS::GetEntitlementsInterface() const
{
    return this->EntitlementsImpl;
}

IOnlineStoreV2Ptr FOnlineSubsystemRedpointEAS::GetStoreV2Interface() const
{
    return this->StoreV2Impl;
}

IOnlinePurchasePtr FOnlineSubsystemRedpointEAS::GetPurchaseInterface() const
{
    return this->PurchaseImpl;
}

bool FOnlineSubsystemRedpointEAS::Init()
{
    this->IdentityImpl = MakeShared<FOnlineIdentityInterfaceEAS, ESPMode::ThreadSafe>();

    this->UserImpl = MakeShared<FOnlineUserInterfaceEAS, ESPMode::ThreadSafe>(
        this->ParentEOS->GetPlatformInstance(),
        this->IdentityImpl.ToSharedRef());

    this->FriendsImpl = MakeShared<FOnlineFriendsInterfaceEAS, ESPMode::ThreadSafe>(
        this->ParentEOS->GetPlatformInstance(),
        this->IdentityImpl.ToSharedRef());
    this->PresenceImpl = MakeShared<FOnlinePresenceInterfaceEAS, ESPMode::ThreadSafe>(
        this->ParentEOS->GetPlatformInstance(),
        this->IdentityImpl.ToSharedRef(),
        this->FriendsImpl.ToSharedRef(),
        this->ParentEOS->GetConfig().AsShared());

    this->PresenceImpl->ConnectFriendsToPresence();

    this->FriendsImpl->RegisterEvents();
    this->PresenceImpl->RegisterEvents();

    EOS_HEcom Ecom = EOS_Platform_GetEcomInterface(this->ParentEOS->GetPlatformInstance());
    this->StoreV2Impl = MakeShared<FOnlineStoreInterfaceV2EAS, ESPMode::ThreadSafe>(Ecom);
    this->EntitlementsImpl =
        MakeShared<FOnlineEntitlementsInterfaceEAS, ESPMode::ThreadSafe>(Ecom, this->StoreV2Impl.ToSharedRef());
    this->PurchaseImpl = MakeShared<FOnlinePurchaseInterfaceEAS, ESPMode::ThreadSafe>(
        Ecom,
        this->StoreV2Impl.ToSharedRef(),
        this->EntitlementsImpl.ToSharedRef());

    return true;
}

bool FOnlineSubsystemRedpointEAS::Shutdown()
{
    if (this->PresenceImpl.IsValid())
    {
        this->PresenceImpl->DisconnectFriendsFromPresence();
    }

    DestructInterface(this->PurchaseImpl, TEXT("IOnlinePurchase"));
    DestructInterface(this->EntitlementsImpl, TEXT("IOnlineEntitlements"));
    DestructInterface(this->StoreV2Impl, TEXT("IOnlineStoreV2"));
    DestructInterface(this->PresenceImpl, TEXT("IOnlinePresence"));
    DestructInterface(this->FriendsImpl, TEXT("IOnlineFriends"));
    DestructInterface(this->UserImpl, TEXT("IOnlineUser"));
    DestructInterface(this->IdentityImpl, TEXT("IOnlineIdentity"));

    return true;
}

FString FOnlineSubsystemRedpointEAS::GetAppId() const
{
    return TEXT("");
}

FText FOnlineSubsystemRedpointEAS::GetOnlineServiceName(void) const
{
    return FText::FromString(TEXT("Epic Games"));
}

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Shared/OnlinePurchaseInterfaceSynthetic.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemRedpointEOS/Public/EOSError.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineIdentityInterfaceEOS.h"

EOS_ENABLE_STRICT_WARNINGS

struct FNativeEventBinding
{
    TWeakPtr<IOnlinePurchase, ESPMode::ThreadSafe> PurchaseWk;
    TArray<FDelegateHandle> EventHandles;
    TSharedPtr<const FUniqueNetId> OriginalUserId;
};

static TSharedPtr<IOnlineIdentity, ESPMode::ThreadSafe> GetIdentity(IOnlineSubsystem *OSS)
{
    return OSS->GetIdentityInterface();
}

static TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> GetPurchase(IOnlineSubsystem *OSS)
{
    return OSS->GetPurchaseInterface();
}

void FOnlinePurchaseInterfaceSynthetic::OnNativeUnexpectedPurchaseReceipt(
    const FUniqueNetId &UserId,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    TSharedPtr<FNativeEventBinding> NativeEventBinding)
{
    UE_LOG(LogRedpointEOS, Verbose, TEXT("Received OnUnexpectedPurchaseReceipt event from native subsystem."));

    // @todo: Passing 0 as the LocalUserNum here could be incorrect in an extreme edge case where
    // different local users have different login statuses. However, because the code later compares
    // user IDs to get the actual correct local user num, you'd have to be in a situation where you
    // have multiple local users, are relying on the unexpected purchase receipt event from a native
    // subsystem, and local user num 0 is not currently signed into EOS.

    TSharedPtr<const FUniqueNetId> _;
    TSharedPtr<IOnlineIdentity, ESPMode::ThreadSafe> Identity =
        this->IdentityEOS->GetNativeInterface<IOnlineIdentity>(0, _, GetIdentity);
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(0, _, GetPurchase);
    if (!Identity.IsValid() || !Purchase.IsValid())
    {
        UE_LOG(
            LogRedpointEOS,
            Warning,
            TEXT("The native identity or purchase interface could not be obtained. The event will not be propagated."));
        return;
    }

    int LocalUserNum = -1;
    for (int32 i = 0; i < MAX_LOCAL_PLAYERS; i++)
    {
        TSharedPtr<const FUniqueNetId> UserIdNative = Identity->GetUniquePlayerId(i);
        if (UserIdNative.IsValid())
        {
            if (*UserIdNative == UserId)
            {
                LocalUserNum = i;
                break;
            }
        }
    }
    if (LocalUserNum == -1)
    {
        UE_LOG(LogRedpointEOS, Warning, TEXT("Unable to map user ID of OnUnexpectedPurchaseReceipt event from native subsystem to a local user number. The event will not be propagated."));
        return;
    }

    TSharedPtr<const FUniqueNetId> UserIdEOS = this->IdentityEOS->GetUniquePlayerId(LocalUserNum);
    if (!UserIdEOS.IsValid())
    {
        UE_LOG(
            LogRedpointEOS,
            Warning,
            TEXT("The local user number %d does not map to a signed in EOS user for the OnUnexpectedPurchaseReceipt event. The event will not be propagated."),
            LocalUserNum);
        return;
    }

    UE_LOG(LogRedpointEOS, Verbose, TEXT("Raising OnUnexpectedPurchaseReceipt event."));
    this->TriggerOnUnexpectedPurchaseReceiptDelegates(*UserIdEOS);
}

void FOnlinePurchaseInterfaceSynthetic::OnLoginStatusChanged(
    int32 LocalUserNum,
    ELoginStatus::Type OldStatus,
    ELoginStatus::Type NewStatus,
    const FUniqueNetId &UserId)
{
    if (OldStatus == ELoginStatus::NotLoggedIn && NewStatus == ELoginStatus::LoggedIn)
    {
        TSharedPtr<const FUniqueNetId> UserIdNative;
        TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
            this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
        if (Purchase.IsValid())
        {
            if (this->NativeEventBindingsRegisteredPerUser.Contains(UserId))
            {
                FDelegateHandle Handle = Purchase->AddOnUnexpectedPurchaseReceiptDelegate_Handle(
                    FOnUnexpectedPurchaseReceiptDelegate::CreateThreadSafeSP(
                        this,
                        &FOnlinePurchaseInterfaceSynthetic::OnNativeUnexpectedPurchaseReceipt,
                        this->NativeEventBindingsRegisteredPerUser[UserId]));

                this->NativeEventBindingsRegisteredPerUser[UserId]->EventHandles.Add(Handle);
            }
            else
            {
                TSharedRef<FNativeEventBinding> Binding = MakeShared<FNativeEventBinding>();
                Binding->PurchaseWk = Purchase;
                Binding->OriginalUserId = UserId.AsShared();

                FDelegateHandle Handle = Purchase->AddOnUnexpectedPurchaseReceiptDelegate_Handle(
                    FOnUnexpectedPurchaseReceiptDelegate::CreateThreadSafeSP(
                        this,
                        &FOnlinePurchaseInterfaceSynthetic::OnNativeUnexpectedPurchaseReceipt,
                        TSharedPtr<FNativeEventBinding>(Binding)));

                Binding->EventHandles.Add(Handle);

                this->NativeEventBindingsRegisteredPerUser.Add(UserId, TSharedPtr<FNativeEventBinding>(Binding));
            }
        }
    }
    else if (OldStatus == ELoginStatus::LoggedIn && NewStatus == ELoginStatus::NotLoggedIn)
    {
        if (this->NativeEventBindingsRegisteredPerUser.Contains(UserId))
        {
            TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
                this->NativeEventBindingsRegisteredPerUser[UserId]->PurchaseWk.Pin();
            if (Purchase.IsValid())
            {
                for (const FDelegateHandle &Handle : this->NativeEventBindingsRegisteredPerUser[UserId]->EventHandles)
                {
                    FDelegateHandle HandleCopy = Handle;
                    Purchase->ClearOnUnexpectedPurchaseReceiptDelegate_Handle(HandleCopy);
                }
            }
            this->NativeEventBindingsRegisteredPerUser.Remove(UserId);
        }
    }
}

void FOnlinePurchaseInterfaceSynthetic::RegisterEvents()
{
    // Listen for when users log in and out, so that we can register our
    // event propagation for the relevant native subsystem.
    for (int32 i = 0; i < MAX_LOCAL_PLAYERS; i++)
    {
        this->IdentityEOS->AddOnLoginStatusChangedDelegate_Handle(
            i,
            FOnLoginStatusChangedDelegate::CreateThreadSafeSP(
                this,
                &FOnlinePurchaseInterfaceSynthetic::OnLoginStatusChanged));
    }
}

bool FOnlinePurchaseInterfaceSynthetic::IsAllowedToPurchase(const FUniqueNetId &UserId)
{
    TSharedPtr<const FUniqueNetId> UserIdNative;
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
    if (Purchase.IsValid())
    {
        return Purchase->IsAllowedToPurchase(*UserIdNative);
    }

    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::Missing_Feature(
             TEXT("FOnlinePurchaseInterfaceSynthetic::IsAllowedToPurchase"),
             TEXT("This platform does not support IOnlinePurchase."))
             .ToLogString());
    return false;
}

void FOnlinePurchaseInterfaceSynthetic::Checkout(
    const FUniqueNetId &UserId,
    const FPurchaseCheckoutRequest &CheckoutRequest,
    const FOnPurchaseCheckoutComplete &Delegate)
{
    TSharedPtr<const FUniqueNetId> UserIdNative;
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
    if (Purchase.IsValid())
    {
        return Purchase->Checkout(*UserIdNative, CheckoutRequest, Delegate);
    }

    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::Missing_Feature(
             TEXT("FOnlinePurchaseInterfaceSynthetic::Checkout"),
             TEXT("This platform does not support IOnlinePurchase."))
             .ToLogString());
    Delegate.ExecuteIfBound(
        OnlineRedpointEOS::Errors::Missing_Feature(
            TEXT("FOnlinePurchaseInterfaceSynthetic::Checkout"),
            TEXT("This platform does not support IOnlinePurchase.")),
        MakeShared<FPurchaseReceipt>());
}

#if defined(UE_5_1_OR_LATER)
void FOnlinePurchaseInterfaceSynthetic::Checkout(
    const FUniqueNetId &UserId,
    const FPurchaseCheckoutRequest &CheckoutRequest,
    const FOnPurchaseReceiptlessCheckoutComplete &Delegate)
{
    TSharedPtr<const FUniqueNetId> UserIdNative;
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
    if (Purchase.IsValid())
    {
        return Purchase->Checkout(*UserIdNative, CheckoutRequest, Delegate);
    }

    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::Missing_Feature(
             TEXT("FOnlinePurchaseInterfaceSynthetic::Checkout"),
             TEXT("This platform does not support IOnlinePurchase."))
             .ToLogString());
    Delegate.ExecuteIfBound(OnlineRedpointEOS::Errors::Missing_Feature(
        TEXT("FOnlinePurchaseInterfaceSynthetic::Checkout"),
        TEXT("This platform does not support IOnlinePurchase.")));
}
#endif

void FOnlinePurchaseInterfaceSynthetic::FinalizePurchase(const FUniqueNetId &UserId, const FString &ReceiptId)
{
    TSharedPtr<const FUniqueNetId> UserIdNative;
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
    if (Purchase.IsValid())
    {
        return Purchase->FinalizePurchase(*UserIdNative, ReceiptId);
    }

    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::Missing_Feature(
             TEXT("FOnlinePurchaseInterfaceSynthetic::FinalizePurchase"),
             TEXT("This platform does not support IOnlinePurchase."))
             .ToLogString());
}

void FOnlinePurchaseInterfaceSynthetic::FinalizePurchase(
    const FUniqueNetId &UserId,
    const FString &ReceiptId,
    const FString &ReceiptInfo)
{
    TSharedPtr<const FUniqueNetId> UserIdNative;
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
    if (Purchase.IsValid())
    {
        return Purchase->FinalizePurchase(*UserIdNative, ReceiptId, ReceiptInfo);
    }

    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::Missing_Feature(
             TEXT("FOnlinePurchaseInterfaceSynthetic::FinalizePurchase"),
             TEXT("This platform does not support IOnlinePurchase."))
             .ToLogString());
}

#if PLATFORM_ANDROID
void FOnlinePurchaseInterfaceSynthetic::FinalizePurchaseWithCallback(
    const FUniqueNetId &UserId,
    const FString &ReceiptId,
    const IOnlinePurchaseWithFinalizePurchaseCallback::FOnFinalizeReceiptComplete &Delegate)
{
    TSharedPtr<const FUniqueNetId> UserIdNative;
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
    if (Purchase.IsValid())
    {
        return StaticCastSharedPtr<IOnlinePurchaseWithFinalizePurchaseCallback>(Purchase)->FinalizePurchaseWithCallback(
            *UserIdNative,
            ReceiptId,
            Delegate);
    }

    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::Missing_Feature(
             TEXT("FOnlinePurchaseInterfaceSynthetic::FinalizePurchase"),
             TEXT("This platform does not support IOnlinePurchase."))
             .ToLogString());
    Delegate.ExecuteIfBound(OnlineRedpointEOS::Errors::Missing_Feature(
        TEXT("FOnlinePurchaseInterfaceSynthetic::FinalizePurchase"),
        TEXT("This platform does not support IOnlinePurchase.")));
}
#endif // #if PLATFORM_ANDROID

void FOnlinePurchaseInterfaceSynthetic::RedeemCode(
    const FUniqueNetId &UserId,
    const FRedeemCodeRequest &RedeemCodeRequest,
    const FOnPurchaseRedeemCodeComplete &Delegate)
{
    TSharedPtr<const FUniqueNetId> UserIdNative;
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
    if (Purchase.IsValid())
    {
        return Purchase->RedeemCode(*UserIdNative, RedeemCodeRequest, Delegate);
    }

    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::Missing_Feature(
             TEXT("FOnlinePurchaseInterfaceSynthetic::RedeemCode"),
             TEXT("This platform does not support IOnlinePurchase."))
             .ToLogString());
    Delegate.ExecuteIfBound(
        OnlineRedpointEOS::Errors::Missing_Feature(
            TEXT("FOnlinePurchaseInterfaceSynthetic::RedeemCode"),
            TEXT("This platform does not support IOnlinePurchase.")),
        MakeShared<FPurchaseReceipt>());
}

void FOnlinePurchaseInterfaceSynthetic::QueryReceipts(
    const FUniqueNetId &UserId,
    bool bRestoreReceipts,
    const FOnQueryReceiptsComplete &Delegate)
{
    TSharedPtr<const FUniqueNetId> UserIdNative;
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
    if (Purchase.IsValid())
    {
        return Purchase->QueryReceipts(*UserIdNative, bRestoreReceipts, Delegate);
    }

    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::Missing_Feature(
             TEXT("FOnlinePurchaseInterfaceSynthetic::QueryReceipts"),
             TEXT("This platform does not support IOnlinePurchase."))
             .ToLogString());
    Delegate.ExecuteIfBound(OnlineRedpointEOS::Errors::Missing_Feature(
        TEXT("FOnlinePurchaseInterfaceSynthetic::QueryReceipts"),
        TEXT("This platform does not support IOnlinePurchase.")));
}

void FOnlinePurchaseInterfaceSynthetic::GetReceipts(const FUniqueNetId &UserId, TArray<FPurchaseReceipt> &OutReceipts)
    const
{
    TSharedPtr<const FUniqueNetId> UserIdNative;
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
    if (Purchase.IsValid())
    {
        return Purchase->GetReceipts(*UserIdNative, OutReceipts);
    }

    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::Missing_Feature(
             TEXT("FOnlinePurchaseInterfaceSynthetic::GetReceipts"),
             TEXT("This platform does not support IOnlinePurchase."))
             .ToLogString());
    OutReceipts.Reset();
}

void FOnlinePurchaseInterfaceSynthetic::FinalizeReceiptValidationInfo(
    const FUniqueNetId &UserId,
    FString &InReceiptValidationInfo,
    const FOnFinalizeReceiptValidationInfoComplete &Delegate)
{
    TSharedPtr<const FUniqueNetId> UserIdNative;
    TSharedPtr<IOnlinePurchase, ESPMode::ThreadSafe> Purchase =
        this->IdentityEOS->GetNativeInterface<IOnlinePurchase>(UserId, UserIdNative, GetPurchase);
    if (Purchase.IsValid())
    {
        return Purchase->FinalizeReceiptValidationInfo(*UserIdNative, InReceiptValidationInfo, Delegate);
    }

    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::Missing_Feature(
             TEXT("FOnlinePurchaseInterfaceSynthetic::FinalizeReceiptValidationInfo"),
             TEXT("This platform does not support IOnlinePurchase."))
             .ToLogString());
    Delegate.ExecuteIfBound(
        OnlineRedpointEOS::Errors::Missing_Feature(
            TEXT("FOnlinePurchaseInterfaceSynthetic::FinalizeReceiptValidationInfo"),
            TEXT("This platform does not support IOnlinePurchase.")),
        InReceiptValidationInfo);
}

EOS_DISABLE_STRICT_WARNINGS
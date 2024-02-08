// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_HAS_AUTHENTICATION

#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlinePurchaseInterfaceEAS.h"

#include "OnlineSubsystemRedpointEOS/Public/EOSError.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSErrorConv.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineEntitlementsInterfaceEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/OnlineStoreInterfaceV2EAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/UniqueNetIdEAS.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

EOS_ENABLE_STRICT_WARNINGS

bool FOnlinePurchaseInterfaceEAS::IsAllowedToPurchase(const FUniqueNetId &UserId)
{
    return true;
}

void FOnlinePurchaseInterfaceEAS::Checkout(
    const FUniqueNetId &UserId,
    const FPurchaseCheckoutRequest &CheckoutRequest,
    const FOnPurchaseCheckoutComplete &Delegate)
{
    TSharedRef<const FUniqueNetIdEAS> UserIdEAS = StaticCastSharedRef<const FUniqueNetIdEAS>(UserId.AsShared());

    if (CheckoutRequest.PurchaseOffers.Num() == 0)
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidRequest(
            TEXT("FOnlinePurchaseInterfaceEAS::Checkout"),
            TEXT("You must specify at least one offer in the checkout request."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointEOS, Error, TEXT("%s"), *Error.ToLogString());
        }
        Delegate.ExecuteIfBound(Error, FPurchaseReceiptEAS::CreateReceiptForError());
        return;
    }
    if (CheckoutRequest.PurchaseOffers.Num() > EOS_ECOM_CHECKOUT_MAX_ENTRIES)
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidRequest(
            TEXT("FOnlinePurchaseInterfaceEAS::Checkout"),
            TEXT("You have specified too many offers in the checkout request."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointEOS, Error, TEXT("%s"), *Error.ToLogString());
        }
        Delegate.ExecuteIfBound(Error, FPurchaseReceiptEAS::CreateReceiptForError());
        return;
    }

    TSet<FString> OfferIdsSet;
    for (const auto &Request : CheckoutRequest.PurchaseOffers)
    {
        if (OfferIdsSet.Contains(Request.OfferId))
        {
            FOnlineError Error = OnlineRedpointEOS::Errors::InvalidRequest(
                TEXT("FOnlinePurchaseInterfaceEAS::Checkout"),
                TEXT("You can not checkout the same offer multiple times in the same request."));
            if (!GIsAutomationTesting)
            {
                UE_LOG(LogRedpointEOS, Error, TEXT("%s"), *Error.ToLogString());
            }
            Delegate.ExecuteIfBound(Error, FPurchaseReceiptEAS::CreateReceiptForError());
            return;
        }
        else if (Request.Quantity != 1)
        {
            FOnlineError Error = OnlineRedpointEOS::Errors::InvalidRequest(
                TEXT("FOnlinePurchaseInterfaceEAS::Checkout"),
                TEXT("The quantity of each offer must be set to 1 in a checkout request."));
            if (!GIsAutomationTesting)
            {
                UE_LOG(LogRedpointEOS, Error, TEXT("%s"), *Error.ToLogString());
            }
            Delegate.ExecuteIfBound(Error, FPurchaseReceiptEAS::CreateReceiptForError());
            return;
        }
        OfferIdsSet.Add(Request.OfferId);
    }
    TArray<FString> OfferIds = OfferIdsSet.Array();

    TSharedRef<FPurchaseReceiptEAS> Receipt = FPurchaseReceiptEAS::CreateReceiptForCheckout(CheckoutRequest);
    Receipt->UserId = UserIdEAS;

    this->KnownReceipts.Add(Receipt->TransactionId, Receipt);

    EOS_Ecom_CheckoutOptions Opts = {};
    Opts.ApiVersion = EOS_ECOM_CHECKOUT_API_LATEST;
    Opts.LocalUserId = UserIdEAS->GetEpicAccountId();
    Opts.EntryCount = OfferIds.Num();
    EOS_Ecom_CheckoutEntry *Entries =
        (EOS_Ecom_CheckoutEntry *)FMemory::MallocZeroed(sizeof(EOS_Ecom_CheckoutEntry) * Opts.EntryCount);
    Opts.Entries = Entries;
    for (int i = 0; i < OfferIds.Num(); i++)
    {
        Entries[i].ApiVersion = EOS_ECOM_CHECKOUTENTRY_API_LATEST;
        EOSString_Ecom_CatalogOfferId::AllocateToCharBuffer(OfferIds[i], Entries[i].OfferId);
    }
    EOSRunOperation<EOS_HEcom, EOS_Ecom_CheckoutOptions, EOS_Ecom_CheckoutCallbackInfo>(
        this->Ecom,
        &Opts,
        &EOS_Ecom_Checkout,
        [WeakThis = GetWeakThis(this), Opts, UserIdEAS, Receipt, Delegate](const EOS_Ecom_CheckoutCallbackInfo *Info) {
            for (uint32_t i = 0; i < Opts.EntryCount; i++)
            {
                EOSString_Ecom_CatalogOfferId::FreeFromCharBufferConst(Opts.Entries[i].OfferId);
            }
            FMemory::Free((void *)Opts.Entries);
            if (auto This = PinWeakThis(WeakThis))
            {
                if (Info->ResultCode == EOS_EResult::EOS_Canceled)
                {
                    FOnlineError Error = ConvertError(
                        TEXT("FOnlinePurchaseInterfaceEAS::Checkout"),
                        TEXT("The user cancelled the purchase."),
                        Info->ResultCode);
                    Receipt->AttachCancellation();
                    Delegate.ExecuteIfBound(Error, Receipt);
                    return;
                }

                if (Info->ResultCode != EOS_EResult::EOS_Success)
                {
                    FOnlineError Error = ConvertError(
                        TEXT("FOnlinePurchaseInterfaceEAS::Checkout"),
                        TEXT("Failed to perform e-commerce checkout."),
                        Info->ResultCode);
                    if (!GIsAutomationTesting)
                    {
                        UE_LOG(LogRedpointEOS, Error, TEXT("%s"), *Error.ToLogString());
                    }
                    Receipt->AttachError(Error, true);
                    Delegate.ExecuteIfBound(Error, Receipt);
                    return;
                }

                FString TransactionId = EOSString_Ecom_TransactionId::FromAnsiString(Info->TransactionId);

                EOS_Ecom_CopyTransactionByIdOptions CopyOpts = {};
                CopyOpts.ApiVersion = EOS_ECOM_COPYTRANSACTIONBYID_API_LATEST;
                CopyOpts.LocalUserId = UserIdEAS->GetEpicAccountId();
                CopyOpts.TransactionId = Info->TransactionId;
                EOS_Ecom_HTransaction Transaction = nullptr;
                EOS_EResult CopyResult = EOS_Ecom_CopyTransactionById(This->Ecom, &CopyOpts, &Transaction);
                if (CopyResult != EOS_EResult::EOS_Success)
                {
                    FOnlineError Error = ConvertError(
                        TEXT("FOnlinePurchaseInterfaceEAS::Checkout"),
                        TEXT("Failed to copy transaction data from checkout."),
                        Info->ResultCode);
                    if (!GIsAutomationTesting)
                    {
                        UE_LOG(LogRedpointEOS, Error, TEXT("%s"), *Error.ToLogString());
                    }
                    Receipt->AttachError(Error, true);
                    Delegate.ExecuteIfBound(Error, Receipt);
                    return;
                }

                This->KnownReceipts.Remove(Receipt->TransactionId);
                This->KnownReceipts.Add(TransactionId, Receipt);

                Receipt->AttachTransaction(This->Ecom, TransactionId, Transaction);

                EOS_Ecom_Transaction_Release(Transaction);

                This->Entitlements->QueryEntitlements(
                    *UserIdEAS,
                    TEXT(""),
                    FPagedQuery(),
                    FOnQueryEntitlementsComplete::FDelegate::CreateLambda([Delegate, Receipt](
                                                                              bool bWasSuccessful,
                                                                              const FUniqueNetId &UserId,
                                                                              const FString &Namespace,
                                                                              const FString &Error) {
                        if (!bWasSuccessful)
                        {
                            UE_LOG(
                                LogRedpointEOS,
                                Warning,
                                TEXT("%s"),
                                *OnlineRedpointEOS::Errors::UnexpectedError(
                                     TEXT("FOnlinePurchaseInterfaceEAS::Checkout"),
                                     FString::Printf(
                                         TEXT("Failed to refresh entitlements after successful checkout: %s"),
                                         *Error))
                                     .ToLogString());
                        }

                        Delegate.ExecuteIfBound(OnlineRedpointEOS::Errors::Success(), Receipt);
                    }));
            }
        });
}

#if defined(UE_5_1_OR_LATER)
void FOnlinePurchaseInterfaceEAS::Checkout(
    const FUniqueNetId &UserId,
    const FPurchaseCheckoutRequest &CheckoutRequest,
    const FOnPurchaseReceiptlessCheckoutComplete &Delegate)
{
    Delegate.ExecuteIfBound(OnlineRedpointEOS::Errors::NotImplemented(
        TEXT("FOnlinePurchaseInterfaceEAS::Checkout"),
        TEXT("Epic Games Store does not support receiptless checkout. Use the other "
             "FOnlinePurchaseInterfaceEAS::Checkout call that returns a receipt instead.")));
}
#endif

void FOnlinePurchaseInterfaceEAS::FinalizePurchase(const FUniqueNetId &UserId, const FString &ReceiptId)
{
    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("%s"),
        *OnlineRedpointEOS::Errors::NotImplemented(
             TEXT("FOnlinePurchaseInterfaceEAS::FinalizePurchase"),
             TEXT("Epic Games Store does not support finalising purchases."))
             .ToLogString());
}

void FOnlinePurchaseInterfaceEAS::RedeemCode(
    const FUniqueNetId &UserId,
    const FRedeemCodeRequest &RedeemCodeRequest,
    const FOnPurchaseRedeemCodeComplete &Delegate)
{
    Delegate.ExecuteIfBound(
        OnlineRedpointEOS::Errors::NotImplemented(
            TEXT("FOnlinePurchaseInterfaceEAS::RedeemCode"),
            TEXT("Epic Games Store does not support redeeming purchases via redeem codes.")),
        FPurchaseReceiptEAS::CreateReceiptForError());
}

void FOnlinePurchaseInterfaceEAS::QueryReceipts(
    const FUniqueNetId &UserId,
    bool bRestoreReceipts,
    const FOnQueryReceiptsComplete &Delegate)
{
    Delegate.ExecuteIfBound(OnlineRedpointEOS::Errors::NotImplemented(
        TEXT("FOnlinePurchaseInterfaceEAS::QueryReceipts"),
        TEXT("Epic Games Store does not support querying historical transactions (receipts). To retrieve entitlements "
             "that were previously purchased, use the entitlements interface instead.")));
}

void FOnlinePurchaseInterfaceEAS::GetReceipts(const FUniqueNetId &UserId, TArray<FPurchaseReceipt> &OutReceipts) const
{
    OutReceipts.Empty();
    for (const auto &KV : this->KnownReceipts)
    {
        if (KV.Value.IsValid() && KV.Value->UserId.IsValid() && *KV.Value->UserId == UserId)
        {
            // @note: This makes a copy of the receipt using the copy constructor.
            OutReceipts.Add(FPurchaseReceipt(*KV.Value));
        }
    }
}

void FOnlinePurchaseInterfaceEAS::FinalizeReceiptValidationInfo(
    const FUniqueNetId &UserId,
    FString &InReceiptValidationInfo,
    const FOnFinalizeReceiptValidationInfoComplete &Delegate)
{
    TSharedRef<const FUniqueNetIdEAS> UserIdEAS = StaticCastSharedRef<const FUniqueNetIdEAS>(UserId.AsShared());

    TArray<FString> EntitlementIds;
    EntitlementIds.Add(InReceiptValidationInfo);

    EOS_Ecom_RedeemEntitlementsOptions Opts = {};
    Opts.ApiVersion = EOS_ECOM_REDEEMENTITLEMENTS_API_LATEST;
    Opts.LocalUserId = UserIdEAS->GetEpicAccountId();
    EOSString_Ecom_EntitlementId::AllocateToCharList(EntitlementIds, Opts.EntitlementIdCount, Opts.EntitlementIds);
    EOSRunOperation<EOS_HEcom, EOS_Ecom_RedeemEntitlementsOptions, EOS_Ecom_RedeemEntitlementsCallbackInfo>(
        this->Ecom,
        &Opts,
        &EOS_Ecom_RedeemEntitlements,
        [WeakThis = GetWeakThis(this), Opts, InReceiptValidationInfo, UserIdEAS, Delegate](
            const EOS_Ecom_RedeemEntitlementsCallbackInfo *Info) {
            EOSString_Ecom_EntitlementId::FreeFromCharListConst(Opts.EntitlementIdCount, Opts.EntitlementIds);
            if (auto This = PinWeakThis(WeakThis))
            {
                if (Info->ResultCode != EOS_EResult::EOS_Success)
                {
                    Delegate.ExecuteIfBound(
                        ConvertError(
                            TEXT("FOnlinePurchaseInterfaceEAS::FinalizeReceiptValidationInfo"),
                            TEXT("Failed to redeem entitlements for consumption."),
                            Info->ResultCode),
                        InReceiptValidationInfo);
                    return;
                }

                This->Entitlements->QueryEntitlements(
                    *UserIdEAS,
                    TEXT(""),
                    FPagedQuery(),
                    FOnQueryEntitlementsComplete::FDelegate::CreateLambda([Delegate, InReceiptValidationInfo](
                                                                              bool bWasSuccessful,
                                                                              const FUniqueNetId &UserId,
                                                                              const FString &Namespace,
                                                                              const FString &Error) {
                        if (!bWasSuccessful)
                        {
                            Delegate.ExecuteIfBound(
                                OnlineRedpointEOS::Errors::UnexpectedError(
                                    TEXT("FOnlinePurchaseInterfaceEAS::FinalizeReceiptValidationInfo"),
                                    FString::Printf(
                                        TEXT("Failed to refresh entitlements after successful consumption: %s"),
                                        *Error)),
                                InReceiptValidationInfo);
                            return;
                        }

                        Delegate.ExecuteIfBound(OnlineRedpointEOS::Errors::Success(), InReceiptValidationInfo);
                    }));
            }
        });
}

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
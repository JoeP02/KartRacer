// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlinePurchaseInterfaceRedpointGoogle.h"

#if EOS_GOOGLE_ENABLED

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "CoreGlobals.h"
#include "Internationalization/Culture.h"
#include "Internationalization/FastDecimalFormat.h"
#include "Internationalization/Internationalization.h"
#include "LogRedpointGoogle.h"
#include "OnlineSubsystemRedpointEOS/Public/EOSError.h"
#include "OnlineSubsystemRedpointEOS/Shared/IdentifiableCallbackDispatcher.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"
#include "OnlineSubsystemRedpointGoogle.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonTypes.h"

class FCheckoutRequest
{
public:
    TArray<FUniqueOfferId> OfferIds;
    TArray<int> Quantities;
};

class FCheckoutResponse
{
public:
    FOnlineError Error;
    FString JsonData;
};

class FConsumeRequest
{
public:
    FString PurchaseToken;
};

class FConsumeResponse
{
public:
    FOnlineError Error;
};

class FQueryRequest
{
public:
};

class FQueryResponse
{
public:
    FOnlineError Error;
};

static FIdentifiableCallbackDispatcher<FCheckoutRequest, FCheckoutResponse> CheckoutDispatcher;
static FIdentifiableCallbackDispatcher<FConsumeRequest, FConsumeResponse> ConsumeDispatcher;
static FIdentifiableCallbackDispatcher<FQueryRequest, FQueryResponse> QueryDispatcher;

FOnlinePurchaseInterfaceRedpointGoogle::FOnlinePurchaseInterfaceRedpointGoogle(
    const TSharedRef<FOnlineIdentityInterfaceRedpointGoogle> &InIdentityGooglePlay)
    : IdentityGooglePlay(InIdentityGooglePlay)
{
}

FOnlinePurchaseInterfaceRedpointGoogle::~FOnlinePurchaseInterfaceRedpointGoogle()
{
}

bool FOnlinePurchaseInterfaceRedpointGoogle::IsAllowedToPurchase(const FUniqueNetId &UserId)
{
    // Unlike OnlineSubsystemGooglePlay, our Java code handles automatic reconnections
    // to the billing service, so this is always true for the local user.
    return this->IdentityGooglePlay->GetLoginStatus(UserId) == ELoginStatus::LoggedIn;
}

void FOnlinePurchaseInterfaceRedpointGoogle::Checkout(
    const FUniqueNetId &UserId,
    const FPurchaseCheckoutRequest &CheckoutRequest,
    const FOnPurchaseCheckoutComplete &Delegate)
{
    if (this->IdentityGooglePlay->GetLoginStatus(0) != ELoginStatus::LoggedIn)
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidUser(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::Checkout"),
            TEXT("The local user has not been signed into Google Play yet, so e-commerce purchases can not be "
                 "initiated."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        Delegate.ExecuteIfBound(Error, FRedpointGooglePurchaseReceipt::CreateReceiptForError());
        return;
    }

    if (UserId != *this->IdentityGooglePlay->GetUniquePlayerId(0))
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidUser(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::Checkout"),
            TEXT("The UserId parameter must the user ID of the local user to purchase items on Google Play."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        Delegate.ExecuteIfBound(Error, FRedpointGooglePurchaseReceipt::CreateReceiptForError());
        return;
    }

    if (CheckoutRequest.PurchaseOffers.Num() == 0)
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidRequest(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::Checkout"),
            TEXT("You must specify at least one item in the checkout request."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        Delegate.ExecuteIfBound(Error, FRedpointGooglePurchaseReceipt::CreateReceiptForError());
        return;
    }

    TSharedRef<FRedpointGooglePurchaseReceipt> Receipt =
        FRedpointGooglePurchaseReceipt::CreateReceiptForCheckout(CheckoutRequest);

    this->KnownReceipts.Add(Receipt->TransactionId, Receipt);

    TArray<FString> OfferIds;
    TArray<int> Quantities;
    for (const auto &Entry : CheckoutRequest.PurchaseOffers)
    {
        OfferIds.Add(Entry.OfferId);
        Quantities.Add(Entry.Quantity);
    }

    CheckoutDispatcher.Dispatch(
        FCheckoutRequest{OfferIds, Quantities},
        [WeakThis = GetWeakThis(this), Delegate, Receipt](int32 InDispatchId, const FCheckoutRequest &InRequest) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
                {
                    static jmethodID RedpointGoogleInitiatePurchaseMethod = FJavaWrapper::FindMethod(
                        Env,
                        FJavaWrapper::GameActivityClassID,
                        "Thunk_RedpointGoogle_InitiatePurchase",
                        "(ILjava/lang/String;[Ljava/lang/String;[I)I",
                        false);

                    FScopedJavaObject<jstring> jPurchaseGuid = FJavaHelper::ToJavaString(Env, Receipt->TransactionId);

                    UE_LOG(
                        LogRedpointGoogle,
                        Verbose,
                        TEXT("Starting purchase operation with GUID '%s' and dispatch ID %d"),
                        *Receipt->TransactionId,
                        InDispatchId);

                    FScopedJavaObject<jobjectArray> jOfferIds = NewScopedJavaObject(
                        Env,
                        Env->NewObjectArray(InRequest.OfferIds.Num(), Env->FindClass("java/lang/String"), NULL));
                    for (int i = 0; i < InRequest.OfferIds.Num(); i++)
                    {
                        Env->SetObjectArrayElement(
                            *jOfferIds,
                            i,
                            Env->NewStringUTF(TCHAR_TO_UTF8(*InRequest.OfferIds[i])));
                    }

                    FScopedJavaObject<jintArray> jQuantities =
                        NewScopedJavaObject(Env, Env->NewIntArray(InRequest.Quantities.Num()));
                    jint *jQuantitiesArray = (jint *)Env->GetPrimitiveArrayCritical(*jQuantities, NULL);
                    for (int i = 0; i < InRequest.Quantities.Num(); i++)
                    {
                        jQuantitiesArray[i] = InRequest.Quantities[i];
                    }
                    Env->ReleasePrimitiveArrayCritical(*jQuantities, jQuantitiesArray, 0);

                    auto ReturnVal = FJavaWrapper::CallIntMethod(
                        Env,
                        FJavaWrapper::GameActivityThis,
                        RedpointGoogleInitiatePurchaseMethod,
                        InDispatchId,
                        *jPurchaseGuid,
                        *jOfferIds,
                        *jQuantities);
                    if (Env->ExceptionCheck())
                    {
                        FOnlineError Error = OnlineRedpointEOS::Errors::UnexpectedError(
                            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::Checkout"),
                            TEXT("Failed to start InitiatePurchase call due to Java exception."));
                        if (!GIsAutomationTesting)
                        {
                            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
                        }
                        Receipt->AttachError(Error, false);
                        Delegate.ExecuteIfBound(Error, Receipt);
                        Env->ExceptionDescribe();
                        Env->ExceptionClear();
                        return false;
                    }

                    return true;
                }
            }
            return false;
        },
        [WeakThis = GetWeakThis(this), Delegate, Receipt](const FCheckoutResponse &InResponse) {
            if (auto This = PinWeakThis(WeakThis))
            {
                UE_LOG(
                    LogRedpointGoogle,
                    Verbose,
                    TEXT("Received purchase operation callback for GUID '%s'"),
                    *Receipt->TransactionId);

                if (InResponse.Error.WasSuccessful())
                {
                    Receipt->AttachPurchase(FRedpointGooglePurchase::FromRedpointJson(InResponse.JsonData));
                }
                else if (InResponse.Error.ErrorCode == TEXT("errors.com.redpoint.eos.canceled"))
                {
                    Receipt->AttachCancellation();
                }
                else
                {
                    Receipt->AttachError(InResponse.Error, true);
                }

                Delegate.ExecuteIfBound(InResponse.Error, Receipt);
            }
        });
}

#if defined(UE_5_1_OR_LATER)

void FOnlinePurchaseInterfaceRedpointGoogle::Checkout(
    const FUniqueNetId &UserId,
    const FPurchaseCheckoutRequest &CheckoutRequest,
    const FOnPurchaseReceiptlessCheckoutComplete &Delegate)
{
    FOnlineError Error = OnlineRedpointEOS::Errors::NotImplemented(
        TEXT("FOnlinePurchaseInterfaceRedpointGoogle::Checkout"),
        TEXT("FOnlinePurchaseInterfaceRedpointGoogle::Checkout (receiptless) is not currently supported."));
    if (!GIsAutomationTesting)
    {
        UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
    }
    Delegate.ExecuteIfBound(Error);
}

#endif // #if defined(UE_5_1_OR_LATER)

void FOnlinePurchaseInterfaceRedpointGoogle::FinalizePurchaseWithCallback(
    const FUniqueNetId &UserId,
    const FString &ReceiptId,
    const IOnlinePurchaseWithFinalizePurchaseCallback::FOnFinalizeReceiptComplete &Delegate)
{
    if (this->IdentityGooglePlay->GetLoginStatus(0) != ELoginStatus::LoggedIn)
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidUser(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::FinalizePurchase"),
            TEXT("The local user has not been signed into Google Play yet, so e-commerce purchases can not be "
                 "consumed."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        return;
    }

    if (UserId != *this->IdentityGooglePlay->GetUniquePlayerId(0))
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidUser(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::FinalizePurchase"),
            TEXT("The UserId parameter must the user ID of the local user to consume items on Google Play."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        return;
    }

    // We need to look up the purchase token of the receipt so that we can consume it.
    if (!this->KnownReceipts.Contains(ReceiptId))
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidUser(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::FinalizePurchase"),
            TEXT("No such receipts exists for consuming. If you need to, call QueryReceipts."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        return;
    }

    TSharedPtr<const FRedpointGooglePurchase> Purchase = this->KnownReceipts[ReceiptId]->GetPurchase();
    if (!Purchase.IsValid() || Purchase->PurchaseState != TEXT("PURCHASED"))
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidUser(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::FinalizePurchase"),
            TEXT("The specified receipt does not contain a valid purchase, so it can not be consumed."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        return;
    }

    ConsumeDispatcher.Dispatch(
        FConsumeRequest{Purchase->PurchaseToken},
        [WeakThis = GetWeakThis(this)](int32 InDispatchId, const FConsumeRequest &InRequest) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
                {
                    static jmethodID RedpointGoogleConsumePurchaseMethod = FJavaWrapper::FindMethod(
                        Env,
                        FJavaWrapper::GameActivityClassID,
                        "Thunk_RedpointGoogle_ConsumePurchase",
                        "(ILjava/lang/String;)I",
                        false);

                    FScopedJavaObject<jstring> jPurchaseToken = FJavaHelper::ToJavaString(Env, InRequest.PurchaseToken);

                    auto ReturnVal = FJavaWrapper::CallIntMethod(
                        Env,
                        FJavaWrapper::GameActivityThis,
                        RedpointGoogleConsumePurchaseMethod,
                        InDispatchId,
                        *jPurchaseToken);
                    if (Env->ExceptionCheck())
                    {
                        FOnlineError Error = OnlineRedpointEOS::Errors::UnexpectedError(
                            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::FinalizePurchase"),
                            TEXT("Failed to start ConsumePurchase call due to Java exception."));
                        if (!GIsAutomationTesting)
                        {
                            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
                        }
                        Env->ExceptionDescribe();
                        Env->ExceptionClear();
                        return false;
                    }

                    return true;
                }
            }
            return false;
        },
        [WeakThis = GetWeakThis(this), ReceiptId, Delegate](const FConsumeResponse &InResponse) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (InResponse.Error.WasSuccessful())
                {
                    // The purchase has been consumed. Remove the receipt.
                    This->KnownReceipts.Remove(ReceiptId);

                    UE_LOG(LogRedpointGoogle, Verbose, TEXT("Successfully consumed purchase on Google Play."));
                }
                else
                {
                    if (!GIsAutomationTesting)
                    {
                        UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *InResponse.Error.ToLogString());
                    }
                }

                Delegate.ExecuteIfBound(InResponse.Error);
            }
        });
}

void FOnlinePurchaseInterfaceRedpointGoogle::FinalizePurchase(const FUniqueNetId &UserId, const FString &ReceiptId)
{
    this->FinalizePurchaseWithCallback(
        UserId,
        ReceiptId,
        IOnlinePurchaseWithFinalizePurchaseCallback::FOnFinalizeReceiptComplete());
}

void FOnlinePurchaseInterfaceRedpointGoogle::FinalizePurchase(
    const FUniqueNetId &UserId,
    const FString &ReceiptId,
    const FString &ReceiptInfo)
{
    this->FinalizePurchaseWithCallback(
        UserId,
        ReceiptId,
        IOnlinePurchaseWithFinalizePurchaseCallback::FOnFinalizeReceiptComplete());
}

void FOnlinePurchaseInterfaceRedpointGoogle::RedeemCode(
    const FUniqueNetId &UserId,
    const FRedeemCodeRequest &RedeemCodeRequest,
    const FOnPurchaseRedeemCodeComplete &Delegate)
{
    FOnlineError Error = OnlineRedpointEOS::Errors::NotImplemented(
        TEXT("FOnlinePurchaseInterfaceRedpointGoogle::RedeemCode"),
        TEXT("FOnlinePurchaseInterfaceRedpointGoogle::RedeemCode is not supported."));
    if (!GIsAutomationTesting)
    {
        UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
    }
    Delegate.ExecuteIfBound(Error, FRedpointGooglePurchaseReceipt::CreateReceiptForError());
}

void FOnlinePurchaseInterfaceRedpointGoogle::QueryReceipts(
    const FUniqueNetId &UserId,
    bool bRestoreReceipts,
    const FOnQueryReceiptsComplete &Delegate)
{
    if (this->IdentityGooglePlay->GetLoginStatus(0) != ELoginStatus::LoggedIn)
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidUser(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::QueryReceipts"),
            TEXT(
                "The local user has not been signed into Google Play yet, so e-commerce receipts can not be queried."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        return;
    }

    if (UserId != *this->IdentityGooglePlay->GetUniquePlayerId(0))
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidUser(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::QueryReceipts"),
            TEXT("The UserId parameter must the user ID of the local user to query receipts on Google Play."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        return;
    }

    QueryDispatcher.Dispatch(
        FQueryRequest{},
        [WeakThis = GetWeakThis(this)](int32 InDispatchId, const FQueryRequest &InRequest) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
                {
                    static jmethodID RedpointGoogleQueryReceiptsMethod = FJavaWrapper::FindMethod(
                        Env,
                        FJavaWrapper::GameActivityClassID,
                        "Thunk_RedpointGoogle_QueryReceipts",
                        "(I)I",
                        false);

                    auto ReturnVal = FJavaWrapper::CallIntMethod(
                        Env,
                        FJavaWrapper::GameActivityThis,
                        RedpointGoogleQueryReceiptsMethod,
                        InDispatchId);
                    if (Env->ExceptionCheck())
                    {
                        FOnlineError Error = OnlineRedpointEOS::Errors::UnexpectedError(
                            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::QueryReceipts"),
                            TEXT("Failed to start QueryReceipts call due to Java exception."));
                        if (!GIsAutomationTesting)
                        {
                            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
                        }
                        Env->ExceptionDescribe();
                        Env->ExceptionClear();
                        return false;
                    }

                    return true;
                }
            }
            return false;
        },
        [WeakThis = GetWeakThis(this), Delegate](const FQueryResponse &InResponse) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (InResponse.Error.WasSuccessful())
                {
                    UE_LOG(LogRedpointGoogle, Verbose, TEXT("Successfully queried receipts on Google Play."));
                }
                else
                {
                    if (!GIsAutomationTesting)
                    {
                        UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *InResponse.Error.ToLogString());
                    }
                }

                Delegate.ExecuteIfBound(InResponse.Error);
            }
        });
}

void FOnlinePurchaseInterfaceRedpointGoogle::GetReceipts(
    const FUniqueNetId &UserId,
    TArray<FPurchaseReceipt> &OutReceipts) const
{
    if (this->IdentityGooglePlay->GetLoginStatus(0) != ELoginStatus::LoggedIn)
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidUser(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::GetReceipts"),
            TEXT("The local user has not been signed into Google Play yet, so e-commerce receipts can not be "
                 "retrieved."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        return;
    }

    if (UserId != *this->IdentityGooglePlay->GetUniquePlayerId(0))
    {
        FOnlineError Error = OnlineRedpointEOS::Errors::InvalidUser(
            TEXT("FOnlinePurchaseInterfaceRedpointGoogle::GetReceipts"),
            TEXT("The UserId parameter must the user ID of the local user to retrieve receipts on Google Play."));
        if (!GIsAutomationTesting)
        {
            UE_LOG(LogRedpointGoogle, Error, TEXT("%s"), *Error.ToLogString());
        }
        return;
    }

    OutReceipts.Empty();
    for (const auto &KV : this->KnownReceipts)
    {
        // @note: This makes a copy of the receipt using the copy constructor.
        OutReceipts.Add(*KV.Value);
    }
}

void FOnlinePurchaseInterfaceRedpointGoogle::FinalizeReceiptValidationInfo(
    const FUniqueNetId &UserId,
    FString &InReceiptValidationInfo,
    const FOnFinalizeReceiptValidationInfoComplete &Delegate)
{
    Delegate.ExecuteIfBound(OnlineRedpointEOS::Errors::Success(), InReceiptValidationInfo);
}

void FOnlinePurchaseInterfaceRedpointGoogle::OnOutOfBandPurchasesNotification(
    FString JsonData,
    bool bWasSuccessfulReceipts,
    FString ErrorMessage)
{
    TArray<TSharedRef<const FRedpointGooglePurchase>> ReceivedPurchases =
        FRedpointGooglePurchase::FromRedpointJsonList(JsonData);
    if (ReceivedPurchases.Num() == 0)
    {
        return;
    }

    for (const auto &Purchase : ReceivedPurchases)
    {
        if (this->KnownReceipts.Contains(Purchase->PurchaseGuid))
        {
            // Updating an existing receipt.
            this->KnownReceipts[Purchase->PurchaseGuid]->AttachPurchase(Purchase);
        }
        else
        {
            // Adding a new receipt.
            TSharedRef<FRedpointGooglePurchaseReceipt> Receipt =
                FRedpointGooglePurchaseReceipt::CreateReceiptForPurchase(Purchase);
            this->KnownReceipts.Add(Receipt->TransactionId, Receipt);
        }

        if (!bWasSuccessfulReceipts)
        {
            this->KnownReceipts[Purchase->PurchaseGuid]->AttachError(OnlineRedpointEOS::Errors::UnexpectedError(
                TEXT("FOnlinePurchaseInterfaceRedpointGoogle::Checkout"),
                FString::Printf(TEXT("Error during purchase on Google Play: %s"), *ErrorMessage)), true);
        }
    }

    if (this->IdentityGooglePlay->GetLoginStatus(0) == ELoginStatus::LoggedIn)
    {
        UE_LOG(LogRedpointGoogle, Verbose, TEXT("Raising OnUnexpectedPurchaseReceipt event."));
        this->TriggerOnUnexpectedPurchaseReceiptDelegates(*this->IdentityGooglePlay->GetUniquePlayerId(0));
    }
}

JNI_METHOD void Java_games_redpoint_RedpointGoogleLogin_nativeInitiatePurchaseComplete(
    JNIEnv *Env,
    jobject thiz,
    jint DispatchId,
    bool WasSuccessful,
    bool WasCancelled,
    jstring ErrorMessage,
    jstring JsonData)
{
    checkf(DispatchId != -1, TEXT("Java state was invalid for calling back into this method!"));

    if (!WasSuccessful)
    {
        if (WasCancelled)
        {
            CheckoutDispatcher.ReceiveResponse(
                DispatchId,
                FCheckoutResponse{
                    OnlineRedpointEOS::Errors::Canceled(
                        TEXT("FOnlinePurchaseInterfaceRedpointGoogle::Checkout"),
                        TEXT("The user cancelled the purchase.")),
                    TEXT("")});
        }
        else
        {
            CheckoutDispatcher.ReceiveResponse(
                DispatchId,
                FCheckoutResponse{
                    OnlineRedpointEOS::Errors::UnexpectedError(
                        TEXT("FOnlinePurchaseInterfaceRedpointGoogle::Checkout"),
                        FString::Printf(
                            TEXT("Error during purchase on Google Play: %s"),
                            *FJavaHelper::FStringFromLocalRef(Env, ErrorMessage))),
                    TEXT("")});
        }
        return;
    }

    FString JsonDataStr = FJavaHelper::FStringFromLocalRef(Env, JsonData);

    UE_LOG(
        LogRedpointGoogle,
        Verbose,
        TEXT("Received JSON purchase for e-commerce Checkout operation: %s"),
        *JsonDataStr);

    CheckoutDispatcher.ReceiveResponse(
        DispatchId,
        FCheckoutResponse{OnlineRedpointEOS::Errors::Success(), JsonDataStr});
}

JNI_METHOD void Java_games_redpoint_RedpointGoogleLogin_nativeNotifyOutOfBandPurchases(
    JNIEnv *Env,
    jobject thiz,
    jstring JsonData,
    bool WasSuccessfulReceipts,
    jstring ErrorMessage)
{
    FString JsonDataStr = FJavaHelper::FStringFromLocalRef(Env, JsonData);
    FString ErrorMessageStr = FJavaHelper::FStringFromLocalRef(Env, ErrorMessage);

    if (WasSuccessfulReceipts)
    {
        UE_LOG(
            LogRedpointGoogle,
            Verbose,
            TEXT("Received successful JSON purchases for out-of-band purchase notification: %s"),
            *JsonDataStr);
    }
    else
    {
        UE_LOG(
            LogRedpointGoogle,
            Verbose,
            TEXT("Received failed JSON purchases for out-of-band purchase notification: %s"),
            *JsonDataStr);
        UE_LOG(
            LogRedpointGoogle,
            Verbose,
            TEXT("Error message for failed out-of-band purchases was: %s"),
            *ErrorMessageStr);
    }

    FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
        FSimpleDelegateGraphTask::FDelegate::CreateLambda([JsonDataStr, WasSuccessfulReceipts, ErrorMessageStr]() {
            if (auto OSS = static_cast<FOnlineSubsystemRedpointGoogle *const>(
                    IOnlineSubsystem::Get(REDPOINT_GOOGLE_SUBSYSTEM)))
            {
                TSharedPtr<FOnlinePurchaseInterfaceRedpointGoogle, ESPMode::ThreadSafe> PurchaseImpl =
                    StaticCastSharedPtr<FOnlinePurchaseInterfaceRedpointGoogle>(OSS->GetPurchaseInterface());
                PurchaseImpl->OnOutOfBandPurchasesNotification(JsonDataStr, WasSuccessfulReceipts, ErrorMessageStr);
            }
        }),
        GET_STATID(STAT_EOSIdentifiableCallbackDispatcher),
        nullptr,
        ENamedThreads::GameThread);
}

JNI_METHOD void Java_games_redpoint_RedpointGoogleLogin_nativeConsumePurchaseComplete(
    JNIEnv *Env,
    jobject thiz,
    jint DispatchId,
    bool WasSuccessful,
    jstring ErrorMessage)
{
    checkf(DispatchId != -1, TEXT("Java state was invalid for calling back into this method!"));

    if (!WasSuccessful)
    {
        ConsumeDispatcher.ReceiveResponse(
            DispatchId,
            FConsumeResponse{OnlineRedpointEOS::Errors::UnexpectedError(
                TEXT("FOnlinePurchaseInterfaceRedpointGoogle::FinalizePurchase"),
                FString::Printf(
                    TEXT("Error during consume operation on Google Play: %s"),
                    *FJavaHelper::FStringFromLocalRef(Env, ErrorMessage)))});
        return;
    }

    ConsumeDispatcher.ReceiveResponse(DispatchId, FConsumeResponse{OnlineRedpointEOS::Errors::Success()});
}

JNI_METHOD void Java_games_redpoint_RedpointGoogleLogin_nativeQueryReceiptsComplete(
    JNIEnv *Env,
    jobject thiz,
    jint DispatchId,
    bool WasSuccessful,
    jstring ErrorMessage)
{
    checkf(DispatchId != -1, TEXT("Java state was invalid for calling back into this method!"));

    if (!WasSuccessful)
    {
        QueryDispatcher.ReceiveResponse(
            DispatchId,
            FQueryResponse{OnlineRedpointEOS::Errors::UnexpectedError(
                TEXT("FOnlinePurchaseInterfaceRedpointGoogle::QueryReceipts"),
                FString::Printf(
                    TEXT("Error during query operation on Google Play: %s"),
                    *FJavaHelper::FStringFromLocalRef(Env, ErrorMessage)))});
        return;
    }

    QueryDispatcher.ReceiveResponse(DispatchId, FQueryResponse{OnlineRedpointEOS::Errors::Success()});
}

#endif
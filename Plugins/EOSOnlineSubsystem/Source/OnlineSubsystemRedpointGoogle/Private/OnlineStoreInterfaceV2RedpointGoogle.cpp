// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineStoreInterfaceV2RedpointGoogle.h"

#if EOS_GOOGLE_ENABLED

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Internationalization/Culture.h"
#include "Internationalization/FastDecimalFormat.h"
#include "Internationalization/Internationalization.h"
#include "LogRedpointGoogle.h"
#include "OnlineSubsystemRedpointEOS/Shared/IdentifiableCallbackDispatcher.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonTypes.h"

class FQueryOfferRequest
{
public:
    TArray<FUniqueOfferId> OfferIds;
};

class FQueryOfferResponse
{
public:
    bool bWasSuccessful;
    FString ErrorMessage;
    TArray<FOnlineStoreOfferRef> Offers;
};

static FIdentifiableCallbackDispatcher<FQueryOfferRequest, FQueryOfferResponse> QueryOfferDispatcher;

FOnlineStoreInterfaceV2RedpointGoogle::FOnlineStoreInterfaceV2RedpointGoogle(
    const TSharedRef<FOnlineIdentityInterfaceRedpointGoogle> &InIdentityGooglePlay)
    : IdentityGooglePlay(InIdentityGooglePlay)
    , bQueriedOffers(false)
    , CachedOffers()
    , CachedOffersById()
{
}

FOnlineStoreInterfaceV2RedpointGoogle::~FOnlineStoreInterfaceV2RedpointGoogle()
{
}

void FOnlineStoreInterfaceV2RedpointGoogle::QueryCategories(
    const FUniqueNetId &UserId,
    const FOnQueryOnlineStoreCategoriesComplete &Delegate)
{
    UE_LOG(LogRedpointGoogle, Error, TEXT("Google Play does not support the QueryCategories call."));
    Delegate.ExecuteIfBound(false, TEXT("Google Play does not support the QueryCategories call."));
}

void FOnlineStoreInterfaceV2RedpointGoogle::GetCategories(TArray<FOnlineStoreCategory> &OutCategories) const
{
    UE_LOG(LogRedpointGoogle, Error, TEXT("Google Play does not support the GetCategories call."));
    OutCategories.Empty();
}

void FOnlineStoreInterfaceV2RedpointGoogle::QueryOffersByFilter(
    const FUniqueNetId &UserId,
    const FOnlineStoreFilter &Filter,
    const FOnQueryOnlineStoreOffersComplete &Delegate)
{
    UE_LOG(LogRedpointGoogle, Error, TEXT("Google Play does not support the QueryOffersByFilter call."));
    Delegate.ExecuteIfBound(
        false,
        TArray<FUniqueOfferId>(),
        TEXT("Google Play does not support the QueryOffersByFilter call."));
}

void FOnlineStoreInterfaceV2RedpointGoogle::QueryOffersById(
    const FUniqueNetId &UserId,
    const TArray<FUniqueOfferId> &OfferIds,
    const FOnQueryOnlineStoreOffersComplete &Delegate)
{
    if (!this->IdentityGooglePlay->GetLoginStatus(0))
    {
        UE_LOG(
            LogRedpointGoogle,
            Error,
            TEXT("The local user has not been signed into Google Play yet, so e-commerce offers can not be queried."));
        Delegate.ExecuteIfBound(
            false,
            TArray<FUniqueOfferId>(),
            TEXT("The local user has not been signed into Google Play yet, so e-commerce offers can not be queried."));
        return;
    }

    if (UserId != *this->IdentityGooglePlay->GetUniquePlayerId(0))
    {
        UE_LOG(
            LogRedpointGoogle,
            Error,
            TEXT("The UserId parameter must the user ID of the local user to query offers on Google Play."));
        Delegate.ExecuteIfBound(
            false,
            TArray<FUniqueOfferId>(),
            TEXT("The UserId parameter must the user ID of the local user to query offers on Google Play."));
        return;
    }

    QueryOfferDispatcher.Dispatch(
        FQueryOfferRequest{OfferIds},
        [WeakThis = GetWeakThis(this), Delegate](int32 InDispatchId, const FQueryOfferRequest &InRequest) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
                {
                    static jmethodID RedpointGoogleQueryOffersByIdMethod = FJavaWrapper::FindMethod(
                        Env,
                        FJavaWrapper::GameActivityClassID,
                        "Thunk_RedpointGoogle_QueryOffersById",
                        "(I[Ljava/lang/String;)I",
                        false);

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

                    auto ReturnVal = FJavaWrapper::CallIntMethod(
                        Env,
                        FJavaWrapper::GameActivityThis,
                        RedpointGoogleQueryOffersByIdMethod,
                        InDispatchId,
                        *jOfferIds);
                    if (Env->ExceptionCheck())
                    {
                        Delegate.ExecuteIfBound(
                            false,
                            TArray<FUniqueOfferId>(),
                            TEXT("Failed to start QueryOffersById call due to Java exception"));
                        Env->ExceptionDescribe();
                        Env->ExceptionClear();
                        return false;
                    }

                    return true;
                }
            }
            return false;
        },
        [WeakThis = GetWeakThis(this), Delegate](const FQueryOfferResponse &InResponse) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (InResponse.bWasSuccessful)
                {
                    This->CachedOffers = InResponse.Offers;
                    TMap<FUniqueOfferId, FOnlineStoreOfferRef> OfferMap;
                    TArray<FUniqueOfferId> OfferIds;
                    for (const auto &Offer : InResponse.Offers)
                    {
                        OfferMap.Add(Offer->OfferId, Offer);
                        OfferIds.Add(Offer->OfferId);
                    }
                    This->CachedOffersById = OfferMap;
                    This->bQueriedOffers = true;
                    Delegate.ExecuteIfBound(true, OfferIds, TEXT(""));
                }
                else
                {
                    Delegate.ExecuteIfBound(false, TArray<FUniqueOfferId>(), InResponse.ErrorMessage);
                }
            }
        });
}

void FOnlineStoreInterfaceV2RedpointGoogle::GetOffers(TArray<FOnlineStoreOfferRef> &OutOffers) const
{
    if (!this->bQueriedOffers)
    {
        UE_LOG(
            LogRedpointGoogle,
            Error,
            TEXT("GetOffers can not be called until a successful QueryOffersById call completes!"));
        return;
    }

    OutOffers = this->CachedOffers;
}

TSharedPtr<FOnlineStoreOffer> FOnlineStoreInterfaceV2RedpointGoogle::GetOffer(const FUniqueOfferId &OfferId) const
{
    if (!this->bQueriedOffers)
    {
        UE_LOG(
            LogRedpointGoogle,
            Error,
            TEXT("GetOffer can not be called until a successful QueryOffersById call completes!"));
        return nullptr;
    }

    if (CachedOffersById.Contains(OfferId))
    {
        return CachedOffersById[OfferId];
    }

    return nullptr;
}

long ConvertGooglePlayMicrosToPrice(long InMicros, FString InCurrencyCode)
{
    if (InMicros == -1)
    {
        return -1;
    }

    FInternationalization &I18N = FInternationalization::Get();
    const FCulture &Culture = *I18N.GetCurrentCulture();
    const FDecimalNumberFormattingRules &FormattingRules = Culture.GetCurrencyFormattingRules(InCurrencyCode);
    const FNumberFormattingOptions &FormattingOptions = FormattingRules.CultureDefaultFormattingOptions;
    double Val = static_cast<double>(InMicros) *
                 static_cast<double>(FMath::Pow(10.0f, FormattingOptions.MaximumFractionalDigits - 6));
    return FMath::TruncToInt(Val + 0.5);
}

JNI_METHOD void Java_games_redpoint_RedpointGoogleLogin_nativeQueryOffersByIdComplete(
    JNIEnv *Env,
    jobject thiz,
    jint DispatchId,
    bool WasSuccessful,
    jstring ErrorMessage,
    jstring JsonData)
{
    if (!WasSuccessful)
    {
        QueryOfferDispatcher.ReceiveResponse(
            DispatchId,
            FQueryOfferResponse{
                false,
                FJavaHelper::FStringFromLocalRef(Env, ErrorMessage),
                TArray<FOnlineStoreOfferRef>()});
        return;
    }

    TSharedPtr<FJsonValue> JsonValue;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FJavaHelper::FStringFromLocalRef(Env, JsonData));
    if (!FJsonSerializer::Deserialize(Reader, JsonValue))
    {
        QueryOfferDispatcher.ReceiveResponse(
            DispatchId,
            FQueryOfferResponse{
                false,
                TEXT("Unable to parse JSON from QueryOffersById"),
                TArray<FOnlineStoreOfferRef>()});
        return;
    }

    TArray<FOnlineStoreOfferRef> Results;

    for (const auto &Item : JsonValue->AsArray())
    {
        if (Item == nullptr)
        {
            continue;
        }

        TSharedPtr<FJsonObject> ItemObject = Item->AsObject();

        TSharedRef<FOnlineStoreOffer> Offer = MakeShared<FOnlineStoreOffer>();
        Offer->OfferId = ItemObject->GetStringField(TEXT("offerId"));
        Offer->Title = FText::FromString(ItemObject->GetStringField(TEXT("title")));
        Offer->Description = FText::FromString(ItemObject->GetStringField(TEXT("description")));
        Offer->LongDescription = FText::FromString(ItemObject->GetStringField(TEXT("longDescription")));
        Offer->RegularPriceText = FText::FromString(ItemObject->GetStringField(TEXT("regularPriceText")));
        Offer->RegularPrice = ConvertGooglePlayMicrosToPrice(
            FCString::Atoi64(*ItemObject->GetStringField(TEXT("regularPrice"))),
            ItemObject->GetStringField(TEXT("currencyCode")));
        Offer->PriceText = FText::FromString(ItemObject->GetStringField(TEXT("priceText")));
        Offer->NumericPrice =
            ConvertGooglePlayMicrosToPrice(FCString::Atoi64(*ItemObject->GetStringField(TEXT("price"))), ItemObject->GetStringField(TEXT("currencyCode")));
        Offer->CurrencyCode = ItemObject->GetStringField(TEXT("currencyCode"));
        if (!ItemObject->GetStringField("releaseDateUnixTimestamp").IsEmpty())
        {
            Offer->ReleaseDate = FDateTime::FromUnixTimestamp(
                FCString::Atoi64(*ItemObject->GetStringField(TEXT("releaseDateUnixTimestamp"))));
        }
        if (!ItemObject->GetStringField("expirationDateUnixTimestamp").IsEmpty())
        {
            Offer->ExpirationDate = FDateTime::FromUnixTimestamp(
                FCString::Atoi64(*ItemObject->GetStringField(TEXT("expirationDateUnixTimestamp"))));
        }
        FString OfferDiscountType = ItemObject->GetStringField(TEXT("offerDiscountType"));
        if (OfferDiscountType == TEXT("NotOnSale"))
        {
            Offer->DiscountType = EOnlineStoreOfferDiscountType::NotOnSale;
        }
        else if (OfferDiscountType == TEXT("Percentage"))
        {
            Offer->DiscountType = EOnlineStoreOfferDiscountType::Percentage;
        }
        else if (OfferDiscountType == TEXT("DiscountAmount"))
        {
            Offer->DiscountType = EOnlineStoreOfferDiscountType::DiscountAmount;
        }
        else if (OfferDiscountType == TEXT("PayAmount"))
        {
            Offer->DiscountType = EOnlineStoreOfferDiscountType::PayAmount;
        }

        Results.Add(Offer);
    }

    QueryOfferDispatcher.ReceiveResponse(DispatchId, FQueryOfferResponse{true, TEXT(""), Results});
}

#endif
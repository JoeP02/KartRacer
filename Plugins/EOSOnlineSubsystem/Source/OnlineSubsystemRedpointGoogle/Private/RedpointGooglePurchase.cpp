// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointGooglePurchase.h"

#if EOS_GOOGLE_ENABLED

FRedpointGooglePurchase::FRedpointGooglePurchase()
    : PurchaseGuid()
    , DeveloperPayload()
    , OrderId()
    , OriginalJson()
    , PackageName()
    , ProductIds()
    , PurchaseState()
    , PurchaseTime()
    , PurchaseToken()
    , Quantity()
    , Signature()
    , IsAcknowledged()
    , IsAutoRenewing()
{
}

TSharedRef<const FRedpointGooglePurchase> FRedpointGooglePurchase::FromRedpointJsonObject(
    const TSharedPtr<class FJsonObject> &ItemObject)
{
    TSharedRef<FRedpointGooglePurchase> Purchase = MakeShareable(new FRedpointGooglePurchase());
    Purchase->PurchaseGuid = ItemObject->GetStringField(TEXT("purchaseGuid"));
    Purchase->DeveloperPayload = ItemObject->GetStringField(TEXT("developerPayload"));
    Purchase->OrderId = ItemObject->GetStringField(TEXT("orderId"));
    Purchase->OriginalJson = ItemObject->GetStringField(TEXT("originalJson"));
    Purchase->PackageName = ItemObject->GetStringField(TEXT("packageName"));
    for (const auto &ProductId : ItemObject->GetArrayField(TEXT("productIds")))
    {
        Purchase->ProductIds.Add(ProductId->AsString());
    }
    Purchase->PurchaseState = ItemObject->GetStringField(TEXT("purchaseState"));
    Purchase->PurchaseTime =
        FDateTime::FromUnixTimestamp(FCString::Atoi64(*ItemObject->GetStringField(TEXT("purchaseTime"))));
    Purchase->PurchaseToken = ItemObject->GetStringField(TEXT("purchaseToken"));
    Purchase->Quantity = (int)ItemObject->GetNumberField(TEXT("quantity"));
    Purchase->Signature = ItemObject->GetStringField(TEXT("signature"));
    Purchase->IsAcknowledged = ItemObject->GetBoolField(TEXT("isAcknowledged"));
    Purchase->IsAutoRenewing = ItemObject->GetBoolField(TEXT("isAutoRenewing"));
    return ConstCastSharedRef<const FRedpointGooglePurchase>(Purchase);
}

TSharedRef<const FRedpointGooglePurchase> FRedpointGooglePurchase::FromRedpointJson(const FString &InJson)
{
    TSharedPtr<FJsonValue> JsonValue;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(InJson);
    if (!FJsonSerializer::Deserialize(Reader, JsonValue))
    {
        return MakeShareable(new FRedpointGooglePurchase());
    }

    return FRedpointGooglePurchase::FromRedpointJsonObject(JsonValue->AsObject());
}

TArray<TSharedRef<const FRedpointGooglePurchase>> FRedpointGooglePurchase::FromRedpointJsonList(
    const FString &InJsonList)
{
    TSharedPtr<FJsonValue> JsonValue;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(InJsonList);
    if (!FJsonSerializer::Deserialize(Reader, JsonValue))
    {
        return TArray<TSharedRef<const FRedpointGooglePurchase>>();
    }

    TArray<TSharedRef<const FRedpointGooglePurchase>> Results;

    for (const auto &Item : JsonValue->AsArray())
    {
        if (Item == nullptr)
        {
            continue;
        }

        Results.Add(FRedpointGooglePurchase::FromRedpointJsonObject(Item->AsObject()));
    }

    return Results;
}

TSharedRef<const FRedpointGooglePurchase> FRedpointGooglePurchase::FromJsonSerializer(
    const TSharedPtr<FJsonObject> &InJsonObject)
{
    TSharedRef<FRedpointGooglePurchase> Purchase = MakeShareable(new FRedpointGooglePurchase());
    Purchase->FromJson(InJsonObject);
    return ConstCastSharedRef<const FRedpointGooglePurchase>(Purchase);
}

FRedpointGooglePurchase::~FRedpointGooglePurchase()
{
}

#endif
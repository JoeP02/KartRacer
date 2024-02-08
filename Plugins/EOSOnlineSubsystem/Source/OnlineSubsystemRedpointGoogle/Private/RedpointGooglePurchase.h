// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#include "OnlineJsonSerializer.h"

#if EOS_GOOGLE_ENABLED

class FRedpointGooglePurchase
	: public FOnlineJsonSerializable
{
private:
    FRedpointGooglePurchase();

    static TSharedRef<const FRedpointGooglePurchase> FromRedpointJsonObject(
        const TSharedPtr<class FJsonObject> &InJson);

public:
    static TSharedRef<const FRedpointGooglePurchase> FromRedpointJson(const FString &InJson);
    static TArray<TSharedRef<const FRedpointGooglePurchase>> FromRedpointJsonList(const FString &InJsonList);

    static TSharedRef<const FRedpointGooglePurchase> FromJsonSerializer(const TSharedPtr<FJsonObject> &InJsonObject);

    UE_NONCOPYABLE(FRedpointGooglePurchase);
    virtual ~FRedpointGooglePurchase();

    FString PurchaseGuid;
    FString DeveloperPayload;
    FString OrderId;
    FString OriginalJson;
    FString PackageName;
    TArray<FString> ProductIds;
    FString PurchaseState;
    FDateTime PurchaseTime;
    FString PurchaseToken;
    int Quantity;
    FString Signature;
    bool IsAcknowledged;
    bool IsAutoRenewing;

    BEGIN_ONLINE_JSON_SERIALIZER
        ONLINE_JSON_SERIALIZE("purchaseGuid", PurchaseGuid);
        ONLINE_JSON_SERIALIZE("developerPayload", DeveloperPayload);
        ONLINE_JSON_SERIALIZE("orderId", OrderId);
        ONLINE_JSON_SERIALIZE("originalJson", OriginalJson);
        ONLINE_JSON_SERIALIZE("packageName", PackageName);
        ONLINE_JSON_SERIALIZE_ARRAY("productIds", ProductIds);
        ONLINE_JSON_SERIALIZE("purchaseState", PurchaseState);
        ONLINE_JSON_SERIALIZE("purchaseTime", PurchaseTime);
        ONLINE_JSON_SERIALIZE("purchaseToken", PurchaseToken);
        ONLINE_JSON_SERIALIZE("quantity", Quantity);
        ONLINE_JSON_SERIALIZE("signature", Signature);
        ONLINE_JSON_SERIALIZE("isAcknowledged", IsAcknowledged);
        ONLINE_JSON_SERIALIZE("isAutoRenewing", IsAutoRenewing);
    END_ONLINE_JSON_SERIALIZER
};

#endif
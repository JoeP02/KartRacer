// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Interfaces/OnlineEntitlementsInterface.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBEntitlementTypes.generated.h"

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FPurchaseOfferEntryBP
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Entitlement")
    FString OfferNamespace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Entitlement")
    FString OfferId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Entitlement")
    int32 Quantity = 0;

    static FPurchaseOfferEntryBP FromNative(const FPurchaseCheckoutRequest::FPurchaseOfferEntry &InObj);
    FPurchaseCheckoutRequest::FPurchaseOfferEntry ToNative() const;
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FPurchaseCheckoutRequestBP
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Entitlement")
    FString AccountId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Entitlement")
    TArray<FPurchaseOfferEntryBP> PurchaseOffers;

    static FPurchaseCheckoutRequestBP FromNative(const FPurchaseCheckoutRequest &InObj);
    FPurchaseCheckoutRequest ToNative() const;
};

UCLASS(BlueprintType, Transient, Meta = (DontUseGenericSpawnObject, IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineEntitlement : public UObject
{
    GENERATED_BODY()

private:
    TWeakPtr<FOnlineEntitlement> Entitlement;

public:
    UFUNCTION(BlueprintPure, Category = "Online|Entitlement")
    FString GetId();

    UFUNCTION(BlueprintPure, Category = "Online|Entitlement")
    FString GetName();

    UFUNCTION(BlueprintPure, Category = "Online|Entitlement")
    FString GetItemId();

    UFUNCTION(BlueprintPure, Category = "Online|Entitlement")
    FString GetNamespace();

    UFUNCTION(BlueprintPure, Category = "Online|Entitlement")
    bool IsConsumable();

    UFUNCTION(BlueprintPure, Category = "Online|Entitlement")
    int32 GetRemainingCount();

    UFUNCTION(BlueprintPure, Category = "Online|Entitlement")
    int32 GetConsumedCount();

    UFUNCTION(BlueprintPure, Category = "Online|Entitlement")
    FString GetStartDate();

    UFUNCTION(BlueprintPure, Category = "Online|Entitlement")
    FString GetEndDate();

    UFUNCTION(BlueprintPure, Category = "Online|Entitlement")
    FString GetStatus();

    static UOnlineEntitlement *FromNative(const TSharedPtr<FOnlineEntitlement> &InObj);
    TSharedPtr<FOnlineEntitlement> ToNative() const;
};
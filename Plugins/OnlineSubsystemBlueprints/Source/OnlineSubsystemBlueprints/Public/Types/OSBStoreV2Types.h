// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Interfaces/OnlineStoreInterfaceV2.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBStoreV2Types.generated.h"

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineStoreCategoryBP
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Store V2")
    FString Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Store V2")
    FText Description;

    // SubCategories is not supported, as blueprints do not support recursive structs (even inside arrays).

    static FOnlineStoreCategoryBP FromNative(const FOnlineStoreCategory &InObj);
    FOnlineStoreCategory ToNative() const;
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FOnlineStoreFilterBP
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Store V2")
    TArray<FString> Keywords;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Store V2")
    TArray<FOnlineStoreCategoryBP> IncludeCategories;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Store V2")
    TArray<FOnlineStoreCategoryBP> ExcludeCategories;

    static FOnlineStoreFilterBP FromNative(const FOnlineStoreFilter &InObj);
    FOnlineStoreFilter ToNative() const;
};

UCLASS(BlueprintType, Transient, Meta = (DontUseGenericSpawnObject, IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API UOnlineStoreOffer : public UObject
{
    GENERATED_BODY()

private:
    TWeakPtr<FOnlineStoreOffer> Offer;

public:
    UFUNCTION(BlueprintPure, Category = "Online")
    FString GetOfferId();

    UFUNCTION(BlueprintPure, Category = "Online")
    FText GetTitle();

    UFUNCTION(BlueprintPure, Category = "Online")
    FText GetDescription();

    UFUNCTION(BlueprintPure, Category = "Online")
    FText GetLongDescription();

    UFUNCTION(BlueprintPure, Category = "Online")
    FText GetDisplayRegularPrice();

    UFUNCTION(BlueprintPure, Category = "Online")
    FText GetDisplayPrice();

    UFUNCTION(BlueprintPure, Category = "Online")
    int64 GetRegularPrice();

    UFUNCTION(BlueprintPure, Category = "Online")
    int64 GetNumericPrice();

    UFUNCTION(BlueprintPure, Category = "Online")
    FString GetCurrencyCode();

    UFUNCTION(BlueprintPure, Category = "Online")
    FDateTime GetReleaseDate();

    UFUNCTION(BlueprintPure, Category = "Online")
    FDateTime GetExpirationDate();

    UFUNCTION(BlueprintPure, Category = "Online")
    TMap<FString, FString> GetDynamicFields();

    UFUNCTION(BlueprintPure, Category = "Online")
    bool IsPurchasable();

    static UOnlineStoreOffer *FromNative(TSharedPtr<FOnlineStoreOffer> InObj);
    TSharedPtr<FOnlineStoreOffer> ToNative() const;
};
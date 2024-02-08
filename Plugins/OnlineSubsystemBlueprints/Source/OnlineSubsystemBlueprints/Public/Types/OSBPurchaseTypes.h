// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBPurchaseTypes.generated.h"

UENUM(BlueprintType, Meta = (ScriptName = "EPurchaseTransactionState"))
enum class EPurchaseTransactionState_ : uint8
{
    /** processing has not started on the purchase */
    NotStarted,
    /** currently processing the purchase */
    Processing,
    /** purchase completed successfully */
    Purchased,
    /** purchase completed but failed */
    Failed,
    /** purchase has been deferred (neither failed nor completed) */
    Deferred,
    /** purchase canceled by user */
    Canceled,
    /** prior purchase that has been restored */
    Restored,
    /** purchase failed as not allowed */
    NotAllowed,
    /** purchase failed as invalid */
    Invalid
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FRedeemCodeRequestBP
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Purchase")
    FString Code;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Purchase")
    FString CodeUseId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Purchase")
    FString FulfillmentSource;

    static FRedeemCodeRequestBP FromNative(const FRedeemCodeRequest &InObj);
    FRedeemCodeRequest ToNative() const;
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FLineItemInfoBP
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Purchase")
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Purchase")
    FString UniqueId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Purchase")
    FString ValidationInfo;

    static FLineItemInfoBP FromNative(const FPurchaseReceipt::FLineItemInfo &InObj);
    FPurchaseReceipt::FLineItemInfo ToNative() const;
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FReceiptOfferEntryBP
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Purchase")
    FString Namespace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Purchase")
    FString OfferId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Purchase")
    int32 Quantity = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Purchase")
    TArray<FLineItemInfoBP> LineItems;

    static FReceiptOfferEntryBP FromNative(const FPurchaseReceipt::FReceiptOfferEntry &InObj);
    FPurchaseReceipt::FReceiptOfferEntry ToNative() const;
};

UCLASS(BlueprintType, Transient, Meta = (DontUseGenericSpawnObject, IsBlueprintBase = "false"))
class ONLINESUBSYSTEMBLUEPRINTS_API UPurchaseReceipt : public UObject
{
    GENERATED_BODY()

private:
    TWeakPtr<FPurchaseReceipt> Receipt;

public:
    UFUNCTION(BlueprintPure, Category = "Online")
    FString GetTransactionId();

    UFUNCTION(BlueprintPure, Category = "Online")
    EPurchaseTransactionState_ GetPurchaseTransactionState();

    UFUNCTION(BlueprintPure, Category = "Online")
    TArray<FReceiptOfferEntryBP> GetReceiptOffers();

    static UPurchaseReceipt *FromNative(const TSharedRef<FPurchaseReceipt> &InObj);
    static UPurchaseReceipt *FromNative(const FPurchaseReceipt &InObj);
    TSharedRef<FPurchaseReceipt> ToNative() const;
};
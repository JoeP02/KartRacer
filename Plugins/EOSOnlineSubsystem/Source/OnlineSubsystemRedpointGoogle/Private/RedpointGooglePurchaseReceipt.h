// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#include "RedpointGooglePurchase.h"

#if EOS_GOOGLE_ENABLED

class FRedpointGooglePurchaseReceipt : public FPurchaseReceipt
{
private:
    TSharedPtr<const FRedpointGooglePurchase> RedpointPurchase;

    FRedpointGooglePurchaseReceipt();

public:
    static TSharedRef<FRedpointGooglePurchaseReceipt> CreateReceiptForCheckout(
        const FPurchaseCheckoutRequest &InCheckoutRequest);
    static TSharedRef<FRedpointGooglePurchaseReceipt> CreateReceiptForError();
    static TSharedRef<FRedpointGooglePurchaseReceipt> CreateReceiptForPurchase(
        const TSharedRef<const FRedpointGooglePurchase> &InPurchase);
    virtual ~FRedpointGooglePurchaseReceipt();

    void AttachPurchase(const TSharedRef<const FRedpointGooglePurchase> &InPurchase);
    TSharedPtr<const FRedpointGooglePurchase> GetPurchase() const;

    void AttachCancellation();

    void AttachError(const FOnlineError &InError, bool bPurchaseWasAttempted);

    BEGIN_ONLINE_JSON_SERIALIZER
    ONLINE_JSON_SERIALIZE("transactionId", TransactionId);
    ONLINE_JSON_SERIALIZE_ARRAY_SERIALIZABLE("receiptList", ReceiptOffers, FReceiptOfferEntry);
    if (Serializer.IsLoading())
    {
        if (Serializer.GetObject()->HasField("originalPurchase"))
        {
            RedpointPurchase =
                FRedpointGooglePurchase::FromJsonSerializer(Serializer.GetObject()->GetObjectField("originalPurchase"));
        }
    }
    else if (RedpointPurchase.IsValid())
    {
        Serializer.StartObject("originalPurchase");
        ConstCastSharedPtr<FRedpointGooglePurchase>(RedpointPurchase)->Serialize(Serializer, true);
        Serializer.EndObject();
    }
    END_ONLINE_JSON_SERIALIZER
};

#endif
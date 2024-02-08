// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_HAS_AUTHENTICATION

#include "CoreMinimal.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "OnlineSubsystemRedpointEOS/Shared/EpicGames/UniqueNetIdEAS.h"

class FPurchaseReceiptEAS : public FPurchaseReceipt, public TSharedFromThis<FPurchaseReceiptEAS>
{
private:
    FPurchaseReceiptEAS();

public:
    static TSharedRef<FPurchaseReceiptEAS> CreateReceiptForCheckout(const FPurchaseCheckoutRequest &InCheckoutRequest);
    static TSharedRef<FPurchaseReceiptEAS> CreateReceiptForError();
    UE_NONCOPYABLE(FPurchaseReceiptEAS);
    virtual ~FPurchaseReceiptEAS();

    TSharedPtr<const FUniqueNetIdEAS> UserId;

    void AttachTransaction(EOS_HEcom InEcom, const FString &InTransactionId, EOS_Ecom_HTransaction InTransaction);

    void AttachCancellation();

    void AttachError(const FOnlineError &InError, bool bPurchaseWasAttempted);
};

#endif
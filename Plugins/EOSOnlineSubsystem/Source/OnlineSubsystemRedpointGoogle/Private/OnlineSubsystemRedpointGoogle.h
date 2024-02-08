// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemRedpointEOS/Shared/OnlineSubsystemImplBase.h"
#include "OnlineSubsystemRedpointGoogleConstants.h"

#if EOS_GOOGLE_ENABLED

class FOnlineSubsystemRedpointGoogle : public FOnlineSubsystemImplBase,
                                       public TSharedFromThis<FOnlineSubsystemRedpointGoogle, ESPMode::ThreadSafe>
{
private:
    TSharedPtr<class FOnlineIdentityInterfaceRedpointGoogle, ESPMode::ThreadSafe> IdentityImpl;
    TSharedPtr<class FOnlineStoreInterfaceV2RedpointGoogle, ESPMode::ThreadSafe> StoreV2Impl;
    TSharedPtr<class FOnlinePurchaseInterfaceRedpointGoogle, ESPMode::ThreadSafe> PurchaseImpl;

public:
    UE_NONCOPYABLE(FOnlineSubsystemRedpointGoogle);
    FOnlineSubsystemRedpointGoogle() = delete;
    FOnlineSubsystemRedpointGoogle(FName InInstanceName);
    ~FOnlineSubsystemRedpointGoogle();

    virtual bool IsEnabled() const override;

    virtual IOnlineIdentityPtr GetIdentityInterface() const override;
    virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override;
    virtual IOnlinePurchasePtr GetPurchaseInterface() const override;

    virtual bool Init() override;
    virtual bool Tick(float DeltaTime) override;
    virtual bool Shutdown() override;

    virtual FString GetAppId() const override;
    virtual FText GetOnlineServiceName() const override;
};

#endif
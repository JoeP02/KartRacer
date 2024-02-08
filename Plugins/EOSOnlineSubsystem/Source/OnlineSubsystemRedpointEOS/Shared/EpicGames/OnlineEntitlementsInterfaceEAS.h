// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_HAS_AUTHENTICATION

#include "CoreMinimal.h"
#include "Interfaces/OnlineEntitlementsInterface.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"
#include "OnlineSubsystemRedpointEOS/Shared/UserIdMap.h"

EOS_ENABLE_STRICT_WARNINGS

class FOnlineEntitlementsInterfaceEAS : public IOnlineEntitlements,
                                        public TSharedFromThis<FOnlineEntitlementsInterfaceEAS, ESPMode::ThreadSafe>
{
private:
    EOS_HEcom Ecom;
    TSharedRef<class FOnlineStoreInterfaceV2EAS, ESPMode::ThreadSafe> Store;
    TUserIdMap<TArray<TSharedRef<FOnlineEntitlement>>> CachedEntitlementsArray;
    TUserIdMap<TMap<FString, TSharedPtr<FOnlineEntitlement>>> CachedEntitlementsMapByItemId;
    TUserIdMap<TMap<FUniqueEntitlementId, TSharedPtr<FOnlineEntitlement>>> CachedEntitlementsMapByEntitlementId;

public:
    FOnlineEntitlementsInterfaceEAS(
        EOS_HEcom InEcom,
        const TSharedRef<class FOnlineStoreInterfaceV2EAS, ESPMode::ThreadSafe> &InStore)
        : Ecom(InEcom)
        , Store(InStore)
        , CachedEntitlementsArray()
        , CachedEntitlementsMapByItemId()
        , CachedEntitlementsMapByEntitlementId(){};
    UE_NONCOPYABLE(FOnlineEntitlementsInterfaceEAS);
    virtual ~FOnlineEntitlementsInterfaceEAS() override = default;

    virtual TSharedPtr<FOnlineEntitlement> GetEntitlement(
        const FUniqueNetId &UserId,
        const FUniqueEntitlementId &EntitlementId) override;
    virtual TSharedPtr<FOnlineEntitlement> GetItemEntitlement(const FUniqueNetId &UserId, const FString &ItemId)
        override;
    virtual void GetAllEntitlements(
        const FUniqueNetId &UserId,
        const FString &Namespace,
        TArray<TSharedRef<FOnlineEntitlement>> &OutUserEntitlements) override;
    virtual bool QueryEntitlements(const FUniqueNetId &UserId, const FString &Namespace, const FPagedQuery &Page)
        override;
    bool QueryEntitlements(
        const FUniqueNetId &UserId,
        const FString &Namespace,
        const FPagedQuery &Page,
        const FOnQueryEntitlementsComplete::FDelegate &Delegate = FOnQueryEntitlementsComplete::FDelegate());
};

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
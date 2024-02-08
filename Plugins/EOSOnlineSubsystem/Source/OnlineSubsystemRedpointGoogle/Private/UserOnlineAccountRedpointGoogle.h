// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "UniqueNetIdRedpointGoogle.h"

#if EOS_GOOGLE_ENABLED

class FUserOnlineAccountRedpointGoogle : public FUserOnlineAccount
{
private:
    TSharedRef<const FUniqueNetIdRedpointGoogle> UserId;
    FString IdToken;
    FString Email;
    FString DisplayName;

public:
    UE_NONCOPYABLE(FUserOnlineAccountRedpointGoogle);
    FUserOnlineAccountRedpointGoogle(
        TSharedRef<const FUniqueNetIdRedpointGoogle> InUserId,
        FString InIdToken,
        FString InEmail,
        FString InDisplayName)
        : UserId(MoveTemp(InUserId))
        , IdToken(MoveTemp(InIdToken))
        , Email(MoveTemp(InEmail))
        , DisplayName(MoveTemp(InDisplayName)){};
    virtual ~FUserOnlineAccountRedpointGoogle(){};

    virtual TSharedRef<const FUniqueNetId> GetUserId() const override;
    virtual FString GetRealName() const override;
    virtual FString GetDisplayName(const FString &Platform = FString()) const override;
    virtual bool GetUserAttribute(const FString &AttrName, FString &OutAttrValue) const override;
    virtual FString GetAccessToken() const override;
    virtual bool GetAuthAttribute(const FString &AttrName, FString &OutAttrValue) const override;
    virtual bool SetUserAttribute(const FString &AttrName, const FString &AttrValue) override;
};

#endif
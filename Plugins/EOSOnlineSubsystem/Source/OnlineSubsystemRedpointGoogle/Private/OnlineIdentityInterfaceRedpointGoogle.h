// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "UniqueNetIdRedpointGoogle.h"
#include "UserOnlineAccountRedpointGoogle.h"

#if EOS_GOOGLE_ENABLED

class FOnlineIdentityInterfaceRedpointGoogle
    : public IOnlineIdentity,
      public TSharedFromThis<FOnlineIdentityInterfaceRedpointGoogle, ESPMode::ThreadSafe>
{
public:
    // Need to be public for JNI callbacks.
    TSharedPtr<const FUniqueNetIdRedpointGoogle> AuthenticatedUserId;
    TSharedPtr<FUserOnlineAccountRedpointGoogle> AuthenticatedUserAccount;
    bool bLoggingIn;
    bool bLoggedIn;

    FOnlineIdentityInterfaceRedpointGoogle();
    virtual ~FOnlineIdentityInterfaceRedpointGoogle();
    UE_NONCOPYABLE(FOnlineIdentityInterfaceRedpointGoogle);

    virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials &AccountCredentials) override;
    virtual bool Logout(int32 LocalUserNum) override;
    virtual bool AutoLogin(int32 LocalUserNum) override;
    virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId &UserId) const override;
    virtual TArray<TSharedPtr<FUserOnlineAccount>> GetAllUserAccounts() const override;
    virtual TSharedPtr<const FUniqueNetId> GetUniquePlayerId(int32 LocalUserNum) const override;
    virtual TSharedPtr<const FUniqueNetId> CreateUniquePlayerId(uint8 *Bytes, int32 Size) override;
    virtual TSharedPtr<const FUniqueNetId> CreateUniquePlayerId(const FString &Str) override;
    virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;
    virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId &UserId) const override;
    virtual FString GetPlayerNickname(int32 LocalUserNum) const override;
    virtual FString GetPlayerNickname(const FUniqueNetId &UserId) const override;
    virtual FString GetAuthToken(int32 LocalUserNum) const override;
    virtual void RevokeAuthToken(const FUniqueNetId &LocalUserId, const FOnRevokeAuthTokenCompleteDelegate &Delegate)
        override;
    virtual void GetUserPrivilege(
        const FUniqueNetId &LocalUserId,
        EUserPrivileges::Type Privilege,
        const FOnGetUserPrivilegeCompleteDelegate &Delegate) override;
    virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId &UniqueNetId) const override;
    virtual FString GetAuthType() const override;
};

#endif
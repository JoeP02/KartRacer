// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_HAS_AUTHENTICATION

#include "OnlineSubsystemRedpointEOS/Shared/Authentication/AuthenticationGraph.h"

#include "OnlineSubsystemRedpointEOS/Shared/Authentication/UserInterface/EOSUserInterface_EnterDevicePinCode.h"
#include "OnlineSubsystemRedpointEOS/Shared/Authentication/UserInterface/UserInterfaceRef.h"

EOS_ENABLE_STRICT_WARNINGS

struct FEOSAuthCallbackInfo
{
private:
    const EOS_Auth_LoginCallbackInfo *const Login;
    const EOS_Auth_LinkAccountCallbackInfo *const LinkAccount;
    const bool bIsLinkAccount;

public:
    FEOSAuthCallbackInfo(const EOS_Auth_LoginCallbackInfo *InLogin)
        : Login(InLogin)
        , LinkAccount(nullptr)
        , bIsLinkAccount(false){};
    FEOSAuthCallbackInfo(const EOS_Auth_LinkAccountCallbackInfo *InLinkAccount)
        : Login(nullptr)
        , LinkAccount(InLinkAccount)
        , bIsLinkAccount(true){};
    UE_NONCOPYABLE(FEOSAuthCallbackInfo);

    const EOS_EResult &ResultCode() const
    {
        return this->bIsLinkAccount ? this->LinkAccount->ResultCode : this->Login->ResultCode;
    }

    const EOS_Auth_PinGrantInfo *const &PinGrantInfo() const
    {
        return this->bIsLinkAccount ? this->LinkAccount->PinGrantInfo : this->Login->PinGrantInfo;
    }

    const EOS_EpicAccountId &LocalUserId() const
    {
        return this->bIsLinkAccount ? this->LinkAccount->LocalUserId : this->Login->LocalUserId;
    }
};

class ONLINESUBSYSTEMREDPOINTEOS_API FPerformInteractiveEASLoginNode : public FAuthenticationGraphNode
{
private:
    bool bSkipLogoutNodeOnCleanup;

    TSharedPtr<TUserInterfaceRef<
        IEOSUserInterface_EnterDevicePinCode,
        UEOSUserInterface_EnterDevicePinCode,
        UEOSUserInterface_EnterDevicePinCode_Context>>
        Widget;

    void OnSignInCancel(TSharedRef<FAuthenticationGraphState> State, FAuthenticationGraphNodeOnDone OnDone);

    void HandleEASAuthenticationCallback(
        const FEOSAuthCallbackInfo &Data,
        const TSharedRef<FAuthenticationGraphState> &State,
        const FAuthenticationGraphNodeOnDone &OnDone);

public:
    UE_NONCOPYABLE(FPerformInteractiveEASLoginNode);
    FPerformInteractiveEASLoginNode(bool bInSkipLogoutNodeOnCleanup = false);
    virtual ~FPerformInteractiveEASLoginNode() = default;

    virtual void Execute(TSharedRef<FAuthenticationGraphState> State, FAuthenticationGraphNodeOnDone OnDone) override;

    virtual FString GetDebugName() const override
    {
        return TEXT("FPerformInteractiveEASLoginNode");
    }
};

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
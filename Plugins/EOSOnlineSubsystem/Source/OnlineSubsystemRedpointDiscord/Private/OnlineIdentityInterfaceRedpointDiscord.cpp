// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineIdentityInterfaceRedpointDiscord.h"
#include "LogRedpointDiscord.h"
#include "Misc/ConfigCacheIni.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"
#include "UniqueNetIdRedpointDiscord.h"

#if EOS_DISCORD_ENABLED

#define DISCORD_CONFIG_SECTION TEXT("OnlineSubsystemRedpointDiscord")
#define DISCORD_LOCAL_USER_NUM 0

class FUserOnlineAccountRedpointDiscord : public FUserOnlineAccount
{
private:
    TSharedRef<const FUniqueNetIdRedpointDiscord> UserId;

public:
    UE_NONCOPYABLE(FUserOnlineAccountRedpointDiscord);
    FUserOnlineAccountRedpointDiscord(TSharedRef<const FUniqueNetIdRedpointDiscord> InUserId)
        : UserId(MoveTemp(InUserId)){};
    virtual ~FUserOnlineAccountRedpointDiscord(){};

    virtual TSharedRef<const FUniqueNetId> GetUserId() const override
    {
        return this->UserId;
    }

    virtual FString GetRealName() const override
    {
        return TEXT("");
    }

    virtual FString GetDisplayName(const FString &Platform = FString()) const override
    {
        return TEXT("");
    }

    virtual bool GetUserAttribute(const FString &AttrName, FString &OutAttrValue) const override
    {
        return false;
    }

    virtual FString GetAccessToken() const override
    {
        return TEXT("");
    }

    virtual bool GetAuthAttribute(const FString &AttrName, FString &OutAttrValue) const override
    {
        return false;
    }

    virtual bool SetUserAttribute(const FString &AttrName, const FString &AttrValue) override
    {
        return false;
    }
};

FOnlineIdentityInterfaceRedpointDiscord::FOnlineIdentityInterfaceRedpointDiscord(
    TSharedRef<discord::Core> InInstance,
    TSharedRef<FOnlineExternalUIInterfaceRedpointDiscord, ESPMode::ThreadSafe> InExternalUI)
    : Instance(MoveTemp(InInstance))
    , OnCurrentUserUpdateHandle(0)
    , CurrentUser(nullptr)
    , AuthenticatedUserId(nullptr)
    , AuthenticatedUserAccount(nullptr)
    , ExternalUI(MoveTemp(InExternalUI))
{
}

FOnlineIdentityInterfaceRedpointDiscord::~FOnlineIdentityInterfaceRedpointDiscord()
{
    if (this->OnCurrentUserUpdateHandle != 0)
    {
        this->Instance->UserManager().OnCurrentUserUpdate.Disconnect(this->OnCurrentUserUpdateHandle);
    }
}

void FOnlineIdentityInterfaceRedpointDiscord::RegisterEvents()
{
    this->OnCurrentUserUpdateHandle =
        this->Instance->UserManager().OnCurrentUserUpdate.Connect([WeakThis = GetWeakThis(this)]() {
            if (auto This = PinWeakThis(WeakThis))
            {
                bool bFirstSignIn = false;
                discord::UserId ExistingUserId = 0;
                if (!This->CurrentUser.IsValid())
                {
                    This->CurrentUser = MakeShared<discord::User>();
                    bFirstSignIn = true;
                }
                else
                {
                    ExistingUserId = This->CurrentUser->GetId();
                }

                This->Instance->UserManager().GetCurrentUser(This->CurrentUser.Get());
                checkf(This->CurrentUser != nullptr, TEXT("Current user was set to nullptr by Discord!"));

                This->AuthenticatedUserId = MakeShared<FUniqueNetIdRedpointDiscord>(This->CurrentUser->GetId());
                This->AuthenticatedUserAccount =
                    MakeShared<FUserOnlineAccountRedpointDiscord>(This->AuthenticatedUserId.ToSharedRef());

                if (bFirstSignIn)
                {
                    // Upon first login, we're going from "NotLoggedIn" to "UsingLocalProfile".
                    This->TriggerOnLoginStatusChangedDelegates(
                        DISCORD_LOCAL_USER_NUM,
                        ELoginStatus::NotLoggedIn,
                        ELoginStatus::UsingLocalProfile,
                        *This->AuthenticatedUserId);
                    This->TriggerOnLoginChangedDelegates(DISCORD_LOCAL_USER_NUM);
                }
                else if (ExistingUserId != This->CurrentUser->GetId())
                {
                    // The user ID changed. I'm not even sure it's possible, but handle it just in case.
                    This->TriggerOnLoginStatusChangedDelegates(
                        DISCORD_LOCAL_USER_NUM,
                        This->ExternalUI->HasOAuth2Token() ? ELoginStatus::LoggedIn : ELoginStatus::UsingLocalProfile,
                        ELoginStatus::NotLoggedIn,
                        *MakeShared<FUniqueNetIdRedpointDiscord>(ExistingUserId));
                    This->TriggerOnLoginStatusChangedDelegates(
                        DISCORD_LOCAL_USER_NUM,
                        ELoginStatus::NotLoggedIn,
                        ELoginStatus::UsingLocalProfile,
                        *This->AuthenticatedUserId);
                    This->TriggerOnLoginChangedDelegates(DISCORD_LOCAL_USER_NUM);

                    // Tell the external UI it needs to re-authenticate; whatever OAuth token it has would
                    // have been for a different user.
                    This->ExternalUI->ResetOAuth2Token();
                }

                if (bFirstSignIn)
                {
#if !WITH_EDITOR && PLATFORM_WINDOWS
                    // Tell Discord how to launch the game in the future.
                    FString ExecutablePath = FPlatformProcess::ExecutablePath();
                    auto ExecutablePathANSI = StringCast<ANSICHAR>(*ExecutablePath);
                    This->Instance->ActivityManager().RegisterCommand(ExecutablePathANSI.Get());
                    UE_LOG(
                        LogRedpointDiscord,
                        Verbose,
                        TEXT("Told Discord that it can launch the game with this executable: %s"),
                        *ExecutablePath);
#endif

                    // Update our presence information to say that we're in game.
                    FString GameName;
                    if (!GConfig->GetString(DISCORD_CONFIG_SECTION, TEXT("ApplicationName"), GameName, GEngineIni))
                    {
                        GameName = TEXT("Game Name Not Set");
                    }
                    FTCHARToUTF8 GameNameUTF8 = FTCHARToUTF8(*GameName);
                    discord::Activity Activity = {};
                    Activity.SetType(discord::ActivityType::Playing);
                    Activity.SetName(GameNameUTF8.Get());
                    Activity.SetState("In Game");
                    Activity.SetDetails("");
                    Activity.GetParty().SetId("");
                    Activity.GetParty().GetSize().SetCurrentSize(0);
                    Activity.GetParty().GetSize().SetMaxSize(0);
                    Activity.GetSecrets().SetJoin("");
                    Activity.GetSecrets().SetMatch("");
                    Activity.GetSecrets().SetSpectate("");
                    Activity.GetAssets().SetLargeImage("");
                    Activity.GetAssets().SetLargeText("In Game");
                    Activity.GetAssets().SetSmallImage("");
                    Activity.GetAssets().SetSmallText("In Game");
                    Activity.GetTimestamps().SetStart(0);
                    Activity.GetTimestamps().SetEnd(0);
                    This->Instance->ActivityManager().UpdateActivity(Activity, [](discord::Result Result) {
                        // Nothing to do here.
                    });
                }

                // Tell the external UI that we got the user update for the first time.
                This->ExternalUI->OnCurrentUserUpdate();
            }
        });
}

bool FOnlineIdentityInterfaceRedpointDiscord::Login(
    int32 LocalUserNum,
    const FOnlineAccountCredentials &AccountCredentials)
{
    if (LocalUserNum != 0)
    {
        UE_LOG(LogRedpointDiscord, Error, TEXT("Only local player 0 can sign into Discord."));
        return false;
    }

    if (this->ExternalUI->HasOAuth2Token())
    {
        UE_LOG(LogRedpointDiscord, Error, TEXT("The user is already fully authenticated with Discord."));
        return false;
    }

    if (!this->ExternalUI->OnLoginFlowUIRequiredDelegates.IsBound())
    {
        // There are no handlers for the event, fail immediately.
        this->TriggerOnLoginCompleteDelegates(
            LocalUserNum,
            false,
            *FUniqueNetIdRedpointDiscord::EmptyId(),
            TEXT("No registered handlers for IOnlineExternalUI::OnLoginFlowUIRequired. Either connect it up to a "
                    "call to IOnlineExternalUI::ShowLoginUI, or call ShowLoginUI before calling Login."));
        return true;
    }

    TSharedPtr<bool> ShouldContinueLogin = MakeShared<bool>(true);
    this->ExternalUI->TriggerOnLoginFlowUIRequiredDelegates(
        TEXT("http://127.0.0.1"),
        FOnLoginRedirectURL::CreateLambda([](const FString & /*URL*/) -> FLoginFlowResult {
            FLoginFlowResult Result;
            Result.Token = TEXT("UNUSED");
            Result.Error = FOnlineError::Success();
            return Result;
        }),
        FOnLoginFlowComplete::CreateLambda(
            [WeakThis = GetWeakThis(this), ShouldContinueLogin, LocalUserNum, AccountCredentials](
                const FLoginFlowResult &Result) {
                if (auto This = PinWeakThis(WeakThis))
                {
                    if (!*ShouldContinueLogin)
                    {
                        // User cancelled login.
                        This->TriggerOnLoginCompleteDelegates(
                            LocalUserNum,
                            false,
                            *FUniqueNetIdRedpointDiscord::EmptyId(),
                            TEXT("User cancelled login."));
                    }
                    else if (This->ExternalUI->HasOAuth2Token())
                    {
                        // Finished full login.
                        This->TriggerOnLoginStatusChangedDelegates(
                            LocalUserNum,
                            ELoginStatus::UsingLocalProfile,
                            ELoginStatus::LoggedIn,
                            *This->AuthenticatedUserId);
                        This->TriggerOnLoginChangedDelegates(LocalUserNum);
                        This->TriggerOnLoginCompleteDelegates(LocalUserNum, true, *This->AuthenticatedUserId, TEXT(""));
                    }
                    else
                    {
                        // Login failed, because the external UI process didn't complete properly.
                        This->TriggerOnLoginCompleteDelegates(
                            LocalUserNum,
                            false,
                            *FUniqueNetIdRedpointDiscord::EmptyId(),
                            TEXT("OnLoginFlowUIRequired handler did not result in authenticated user."));
                    }
                }
            }),
        *ShouldContinueLogin.Get());
    return true;
}

bool FOnlineIdentityInterfaceRedpointDiscord::Logout(int32 LocalUserNum)
{
    if (LocalUserNum != 0)
    {
        UE_LOG(LogRedpointDiscord, Error, TEXT("Only local player 0 can be signed into Discord."));
        return false;
    }

    if (!this->ExternalUI->HasOAuth2Token() || !this->AuthenticatedUserId.IsValid())
    {
        UE_LOG(LogRedpointDiscord, Error, TEXT("The user is not fully authenticated."));
        return false;
    }

    // We remain having the local profile; we just clear the external UI state.
    this->ExternalUI->ResetOAuth2Token();

    this->TriggerOnLoginStatusChangedDelegates(
        LocalUserNum,
        ELoginStatus::LoggedIn,
        this->CurrentUser.IsValid() ? ELoginStatus::UsingLocalProfile : ELoginStatus::NotLoggedIn,
        *this->AuthenticatedUserId);
    this->TriggerOnLoginChangedDelegates(LocalUserNum);
    this->TriggerOnLogoutCompleteDelegates(LocalUserNum, true);
    return true;
}

bool FOnlineIdentityInterfaceRedpointDiscord::AutoLogin(int32 LocalUserNum)
{
    UE_LOG(
        LogRedpointDiscord,
        Error,
        TEXT("Discord does not support AutoLogin; please call IOnlineExternalUI::ShowLoginUI and then "
             "IOnlineIdentity::Login instead."));
    return false;
}

TSharedPtr<FUserOnlineAccount> FOnlineIdentityInterfaceRedpointDiscord::GetUserAccount(const FUniqueNetId &UserId) const
{
    if (!this->AuthenticatedUserId.IsValid())
    {
        return nullptr;
    }
    if (UserId == *this->AuthenticatedUserId)
    {
        return this->AuthenticatedUserAccount;
    }
    return nullptr;
}

TArray<TSharedPtr<FUserOnlineAccount>> FOnlineIdentityInterfaceRedpointDiscord::GetAllUserAccounts() const
{
    TArray<TSharedPtr<FUserOnlineAccount>> Results;
    if (this->AuthenticatedUserAccount.IsValid())
    {
        Results.Add(this->AuthenticatedUserAccount);
    }
    return Results;
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityInterfaceRedpointDiscord::GetUniquePlayerId(int32 LocalUserNum) const
{
    return this->AuthenticatedUserId;
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityInterfaceRedpointDiscord::CreateUniquePlayerId(uint8 *Bytes, int32 Size)
{
    FString Data = BytesToString(Bytes, Size);
    return this->CreateUniquePlayerId(Data);
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityInterfaceRedpointDiscord::CreateUniquePlayerId(const FString &Str)
{
    int64 UserId = FCString::Atoi64(*Str);
    if (UserId == 0)
    {
        return nullptr;
    }

    return MakeShared<FUniqueNetIdRedpointDiscord>(UserId);
}

ELoginStatus::Type FOnlineIdentityInterfaceRedpointDiscord::GetLoginStatus(int32 LocalUserNum) const
{
    if (this->AuthenticatedUserId.IsValid() && LocalUserNum == 0)
    {
        if (this->ExternalUI->HasOAuth2Token())
        {
            return ELoginStatus::LoggedIn;
        }
        else
        {
            return ELoginStatus::UsingLocalProfile;
        }
    }

    return ELoginStatus::NotLoggedIn;
}

ELoginStatus::Type FOnlineIdentityInterfaceRedpointDiscord::GetLoginStatus(const FUniqueNetId &UserId) const
{
    if (this->AuthenticatedUserId.IsValid() && UserId == *this->AuthenticatedUserId)
    {
        if (this->ExternalUI->HasOAuth2Token())
        {
            return ELoginStatus::LoggedIn;
        }
        else
        {
            return ELoginStatus::UsingLocalProfile;
        }
    }

    return ELoginStatus::NotLoggedIn;
}

FString FOnlineIdentityInterfaceRedpointDiscord::GetPlayerNickname(int32 LocalUserNum) const
{
    if (LocalUserNum == 0 && this->CurrentUser.IsValid())
    {
        return UTF8_TO_TCHAR(this->CurrentUser->GetUsername());
    }

    return TEXT("");
}

FString FOnlineIdentityInterfaceRedpointDiscord::GetPlayerNickname(const FUniqueNetId &UserId) const
{
    if (this->AuthenticatedUserId.IsValid() && UserId == *this->AuthenticatedUserId && this->CurrentUser.IsValid())
    {
        return UTF8_TO_TCHAR(this->CurrentUser->GetUsername());
    }

    return TEXT("");
}

FString FOnlineIdentityInterfaceRedpointDiscord::GetAuthToken(int32 LocalUserNum) const
{
    if (this->AuthenticatedUserId.IsValid() && LocalUserNum == 0 &&
        this->ExternalUI->HasOAuth2Token())
    {
        return this->ExternalUI->GetOAuthToken();
    }

    return TEXT("");
}

void FOnlineIdentityInterfaceRedpointDiscord::RevokeAuthToken(
    const FUniqueNetId &LocalUserId,
    const FOnRevokeAuthTokenCompleteDelegate &Delegate)
{
    Delegate.ExecuteIfBound(LocalUserId, FOnlineError(EOnlineErrorResult::NotImplemented));
}

void FOnlineIdentityInterfaceRedpointDiscord::GetUserPrivilege(
    const FUniqueNetId &LocalUserId,
    EUserPrivileges::Type Privilege,
    const FOnGetUserPrivilegeCompleteDelegate &Delegate)
{
    Delegate.ExecuteIfBound(LocalUserId, Privilege, 0);
}

FPlatformUserId FOnlineIdentityInterfaceRedpointDiscord::GetPlatformUserIdFromUniqueNetId(
    const FUniqueNetId &UniqueNetId) const
{
    return FPlatformUserId();
}

FString FOnlineIdentityInterfaceRedpointDiscord::GetAuthType() const
{
    return TEXT("");
}

#endif
// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineExternalUIInterfaceRedpointDiscord.h"
#include "LogRedpointDiscord.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"
#include "UniqueNetIdRedpointDiscord.h"

#if EOS_DISCORD_ENABLED

FOnlineExternalUIInterfaceRedpointDiscord::FOnlineExternalUIInterfaceRedpointDiscord(
    TSharedRef<discord::Core> InInstance)
    : Instance(MoveTemp(InInstance))
    , CurrentUser(nullptr)
    , OAuth2Token(nullptr)
    , PendingLoginCallbacks()
    , bAuthenticated(false)
{
}

FOnlineExternalUIInterfaceRedpointDiscord::~FOnlineExternalUIInterfaceRedpointDiscord()
{
}

void FOnlineExternalUIInterfaceRedpointDiscord::OnCurrentUserUpdate()
{
    if (!this->CurrentUser.IsValid())
    {
        this->CurrentUser = MakeShared<discord::User>();
    }

    this->Instance->UserManager().GetCurrentUser(this->CurrentUser.Get());
    checkf(this->CurrentUser != nullptr, TEXT("Current user was set to nullptr by Discord!"));

    if (this->OAuth2Token.IsValid())
    {
        this->bAuthenticated = true;

        // Fire any login callbacks that were waiting on current user information.
        TArray<FOnLoginUIClosedDelegate> LoginCallbacks = this->PendingLoginCallbacks;
        this->PendingLoginCallbacks.Empty();
        for (const auto &Callback : LoginCallbacks)
        {
            Callback.ExecuteIfBound(
                MakeShared<FUniqueNetIdRedpointDiscord>(this->CurrentUser->GetId()),
                0,
                FOnlineError::Success());
        }
    }
}

bool FOnlineExternalUIInterfaceRedpointDiscord::HasOAuth2Token() const
{
    return this->bAuthenticated && this->OAuth2Token.IsValid();
}

FString FOnlineExternalUIInterfaceRedpointDiscord::GetOAuthToken() const
{
    if (this->bAuthenticated && this->OAuth2Token.IsValid())
    {
        return ANSI_TO_TCHAR(this->OAuth2Token->GetAccessToken());
    }

    return TEXT("");
}

void FOnlineExternalUIInterfaceRedpointDiscord::ResetOAuth2Token()
{
    this->OAuth2Token.Reset();
    this->bAuthenticated = false;

    // Don't clear out CurrentUser; it is managed by OnCurrentUserUpdate.
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowLoginUI(
    const int ControllerIndex,
    bool bShowOnlineOnly,
    bool bShowSkipButton,
    const FOnLoginUIClosedDelegate &Delegate)
{
    if (ControllerIndex != 0)
    {
        UE_LOG(LogRedpointDiscord, Error, TEXT("Only local player 0 can sign into Discord."));
        return false;
    }

    this->Instance->ApplicationManager().GetOAuth2Token(
        [WeakThis = GetWeakThis(this), Delegate](discord::Result TokenResult, const discord::OAuth2Token &Token) {
            if (auto This = PinWeakThis(WeakThis))
            {
                if (TokenResult == discord::Result::Ok)
                {
                    // Store the token.
                    This->OAuth2Token = MakeShared<discord::OAuth2Token>(Token);

                    // If we already have the current user, we are done.
                    if (This->CurrentUser.IsValid())
                    {
                        This->bAuthenticated = true;
                        Delegate.ExecuteIfBound(
                            MakeShared<FUniqueNetIdRedpointDiscord>(This->CurrentUser->GetId()),
                            0,
                            FOnlineError::Success());
                    }
                    else
                    {
                        // Otherwise store our callback onto an array which OnCurrentUserUpdate will fire once the
                        // current user data is also available.
                        This->PendingLoginCallbacks.Add(Delegate);
                    }
                }
                else
                {
                    Delegate.ExecuteIfBound(nullptr, 0, FOnlineError(EOnlineErrorResult::AccessDenied));
                }
            }
        });
    return true;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowAccountCreationUI(
    const int ControllerIndex,
    const FOnAccountCreationUIClosedDelegate &Delegate)
{
    return false;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowFriendsUI(int32 LocalUserNum)
{
    return false;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowInviteUI(int32 LocalUserNum, FName SessionName)
{
    return false;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowAchievementsUI(int32 LocalUserNum)
{
    return false;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowLeaderboardUI(const FString &LeaderboardName)
{
    return false;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowWebURL(
    const FString &Url,
    const FShowWebUrlParams &ShowParams,
    const FOnShowWebUrlClosedDelegate &Delegate)
{
    return false;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::CloseWebURL()
{
    return false;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowProfileUI(
    const FUniqueNetId &Requestor,
    const FUniqueNetId &Requestee,
    const FOnProfileUIClosedDelegate &Delegate)
{
    return false;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowAccountUpgradeUI(const FUniqueNetId &UniqueId)
{
    return false;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowStoreUI(
    int32 LocalUserNum,
    const FShowStoreParams &ShowParams,
    const FOnShowStoreUIClosedDelegate &Delegate)
{
    return false;
}

bool FOnlineExternalUIInterfaceRedpointDiscord::ShowSendMessageUI(
    int32 LocalUserNum,
    const FShowSendMessageParams &ShowParams,
    const FOnShowSendMessageUIClosedDelegate &Delegate)
{
    return false;
}

#endif
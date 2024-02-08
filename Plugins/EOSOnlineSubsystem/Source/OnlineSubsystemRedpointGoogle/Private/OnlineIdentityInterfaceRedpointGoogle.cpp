// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineIdentityInterfaceRedpointGoogle.h"

#if EOS_GOOGLE_ENABLED

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Async/TaskGraphInterfaces.h"
#include "LogRedpointGoogle.h"
#include "Misc/ConfigCacheIni.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemRedpointGoogleConstants.h"
#include "OnlineSubsystemUtils.h"
#include "RedpointEOSConfig/EngineConfigHelpers.h"
#include "UniqueNetIdRedpointGoogle.h"

DECLARE_STATS_GROUP(TEXT("RedpointGoogle"), STATGROUP_RedpointGoogle, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("RedpointGoogle/Login"), STAT_RedpointGoogleLogin, STATGROUP_RedpointGoogle);

FOnlineIdentityInterfaceRedpointGoogle::FOnlineIdentityInterfaceRedpointGoogle()
    : AuthenticatedUserId(nullptr)
    , AuthenticatedUserAccount(nullptr)
    , bLoggingIn(false)
    , bLoggedIn(false)
{
}

FOnlineIdentityInterfaceRedpointGoogle::~FOnlineIdentityInterfaceRedpointGoogle()
{
}

bool FOnlineIdentityInterfaceRedpointGoogle::Login(
    int32 LocalUserNum,
    const FOnlineAccountCredentials &AccountCredentials)
{
    if (LocalUserNum != 0)
    {
        UE_LOG(
            LogRedpointGoogle,
            Error,
            TEXT("Only local user num 0 can be logged in to Google Play on Android, as Android does not support "
                 "multiple local users."));
        return false;
    }

    if (this->bLoggedIn)
    {
        UE_LOG(LogRedpointGoogle, Error, TEXT("Login can not be called, because the user is already logged in."));
        return false;
    }

    if (this->bLoggingIn)
    {
        UE_LOG(LogRedpointGoogle, Error, TEXT("Login can not be called, because the login is already in-progress."));
        return false;
    }

    this->bLoggingIn = true;

    if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID RedpointGoogleLoginMethod = FJavaWrapper::FindMethod(
            Env,
            FJavaWrapper::GameActivityClassID,
            "Thunk_RedpointGoogle_Login",
            "([Ljava/lang/String;Ljava/lang/String;)I",
            false);

        TArray<FString> ClientIds;
        FString ServerClientId;
        FConfigFile *F = Redpoint::EOS::Config::FEngineConfigHelpers::FindByName(GEngineIni);
        if (F->GetArray(TEXT("OnlineSubsystemRedpointGoogle"), TEXT("+ClientId"), ClientIds) == 0)
        {
            F->GetArray(TEXT("OnlineSubsystemRedpointGoogle"), TEXT("ClientId"), ClientIds);
        }
        GConfig->GetString(TEXT("OnlineSubsystemRedpointGoogle"), TEXT("ServerClientId"), ServerClientId, GEngineIni);

        FScopedJavaObject<jobjectArray> jClientIds =
            NewScopedJavaObject(Env, Env->NewObjectArray(ClientIds.Num(), Env->FindClass("java/lang/String"), NULL));
        FScopedJavaObject<jstring> jServerId = FJavaHelper::ToJavaString(Env, ServerClientId);
        for (int i = 0; i < ClientIds.Num(); i++)
        {
            Env->SetObjectArrayElement(*jClientIds, i, Env->NewStringUTF(TCHAR_TO_UTF8(*ClientIds[i])));
        }

        auto ReturnVal = FJavaWrapper::CallIntMethod(
            Env,
            FJavaWrapper::GameActivityThis,
            RedpointGoogleLoginMethod,
            *jClientIds,
            *jServerId);
        if (Env->ExceptionCheck())
        {
            Env->ExceptionDescribe();
            Env->ExceptionClear();
            this->bLoggingIn = false;
            return false;
        }

        return true;
    }

    return false;
}

JNI_METHOD void Java_games_redpoint_RedpointGoogleLogin_nativeLoginComplete(
    JNIEnv *Env,
    jobject thiz,
    bool WasSuccessful,
    jstring ErrorMessage,
    jstring IdToken,
    jstring UserId,
    jstring UserEmail,
    jstring UserDisplayName)
{
    FString ErrorMessageStr = FJavaHelper::FStringFromParam(Env, ErrorMessage);
    FString IdTokenStr = FJavaHelper::FStringFromParam(Env, IdToken);
    FString UserIdStr = FJavaHelper::FStringFromParam(Env, UserId);
    FString UserEmailStr = FJavaHelper::FStringFromParam(Env, UserEmail);
    FString UserDisplayNameStr = FJavaHelper::FStringFromParam(Env, UserDisplayName);

    UE_LOG(LogRedpointGoogle, Verbose, TEXT("Error message: %s"), *ErrorMessageStr);
    UE_LOG(LogRedpointGoogle, Verbose, TEXT("ID token: %s"), *IdTokenStr);
    UE_LOG(LogRedpointGoogle, Verbose, TEXT("User ID: %s"), *UserIdStr);
    UE_LOG(LogRedpointGoogle, Verbose, TEXT("User email: %s"), *UserEmailStr);
    UE_LOG(LogRedpointGoogle, Verbose, TEXT("User display name: %s"), *UserDisplayNameStr);

    FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
        FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
            if (IOnlineSubsystem *const OSS = IOnlineSubsystem::Get(REDPOINT_GOOGLE_SUBSYSTEM))
            {
                FOnlineIdentityInterfaceRedpointGoogle *This =
                    (FOnlineIdentityInterfaceRedpointGoogle *)OSS->GetIdentityInterface().Get();

                This->bLoggingIn = false;

                if (!WasSuccessful)
                {
                    UE_LOG(LogRedpointGoogle, Error, TEXT("Error message from Java was: %s"), *ErrorMessageStr);
                    This->TriggerOnLoginCompleteDelegates(
                        0,
                        false,
                        *FUniqueNetIdRedpointGoogle::EmptyId(),
                        FString::Printf(TEXT("Error message from Java was: %s"), *ErrorMessageStr));
                    return;
                }

                This->AuthenticatedUserId = MakeShared<FUniqueNetIdRedpointGoogle>(UserIdStr);
                This->AuthenticatedUserAccount = MakeShared<FUserOnlineAccountRedpointGoogle>(
                    This->AuthenticatedUserId.ToSharedRef(),
                    IdTokenStr,
                    UserEmailStr,
                    UserDisplayNameStr);
                This->bLoggedIn = true;
                This->TriggerOnLoginCompleteDelegates(0, true, *This->AuthenticatedUserId, TEXT(""));
                return;
            }
        }),
        GET_STATID(STAT_RedpointGoogleLogin),
        nullptr,
        ENamedThreads::GameThread);
}

bool FOnlineIdentityInterfaceRedpointGoogle::Logout(int32 LocalUserNum)
{
    if (this->bLoggingIn)
    {
        UE_LOG(LogRedpointGoogle, Error, TEXT("Logout can not be called, because login is currently in-progress."));
        return false;
    }

    this->bLoggedIn = false;
    this->AuthenticatedUserId = nullptr;
    this->AuthenticatedUserAccount = nullptr;
    this->TriggerOnLogoutCompleteDelegates(LocalUserNum, true);
    return true;
}

bool FOnlineIdentityInterfaceRedpointGoogle::AutoLogin(int32 LocalUserNum)
{
    return this->Login(LocalUserNum, FOnlineAccountCredentials());
}

TSharedPtr<FUserOnlineAccount> FOnlineIdentityInterfaceRedpointGoogle::GetUserAccount(const FUniqueNetId &UserId) const
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

TArray<TSharedPtr<FUserOnlineAccount>> FOnlineIdentityInterfaceRedpointGoogle::GetAllUserAccounts() const
{
    TArray<TSharedPtr<FUserOnlineAccount>> Results;
    if (this->AuthenticatedUserAccount.IsValid())
    {
        Results.Add(this->AuthenticatedUserAccount);
    }
    return Results;
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityInterfaceRedpointGoogle::GetUniquePlayerId(int32 LocalUserNum) const
{
    return this->AuthenticatedUserId;
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityInterfaceRedpointGoogle::CreateUniquePlayerId(uint8 *Bytes, int32 Size)
{
    FString Data = BytesToString(Bytes, Size);
    return this->CreateUniquePlayerId(Data);
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityInterfaceRedpointGoogle::CreateUniquePlayerId(const FString &Str)
{
    return MakeShared<FUniqueNetIdRedpointGoogle>(Str);
}

ELoginStatus::Type FOnlineIdentityInterfaceRedpointGoogle::GetLoginStatus(int32 LocalUserNum) const
{
    if (LocalUserNum == 0 && this->bLoggedIn)
    {
        return ELoginStatus::LoggedIn;
    }

    return ELoginStatus::NotLoggedIn;
}

ELoginStatus::Type FOnlineIdentityInterfaceRedpointGoogle::GetLoginStatus(const FUniqueNetId &UserId) const
{
    if (this->bLoggedIn && UserId == *this->AuthenticatedUserId)
    {
        return ELoginStatus::LoggedIn;
    }

    return ELoginStatus::NotLoggedIn;
}

FString FOnlineIdentityInterfaceRedpointGoogle::GetPlayerNickname(int32 LocalUserNum) const
{
    if (LocalUserNum == 0 && this->bLoggedIn)
    {
        return this->AuthenticatedUserAccount->GetDisplayName();
    }

    return TEXT("");
}

FString FOnlineIdentityInterfaceRedpointGoogle::GetPlayerNickname(const FUniqueNetId &UserId) const
{
    if (this->bLoggedIn && UserId == *this->AuthenticatedUserId)
    {
        return this->AuthenticatedUserAccount->GetDisplayName();
    }

    return TEXT("");
}

FString FOnlineIdentityInterfaceRedpointGoogle::GetAuthToken(int32 LocalUserNum) const
{
    if (LocalUserNum == 0 && this->bLoggedIn)
    {
        return this->AuthenticatedUserAccount->GetAccessToken();
    }

    return TEXT("");
}

void FOnlineIdentityInterfaceRedpointGoogle::RevokeAuthToken(
    const FUniqueNetId &LocalUserId,
    const FOnRevokeAuthTokenCompleteDelegate &Delegate)
{
    Delegate.ExecuteIfBound(LocalUserId, FOnlineError(EOnlineErrorResult::NotImplemented));
}

void FOnlineIdentityInterfaceRedpointGoogle::GetUserPrivilege(
    const FUniqueNetId &LocalUserId,
    EUserPrivileges::Type Privilege,
    const FOnGetUserPrivilegeCompleteDelegate &Delegate)
{
    Delegate.ExecuteIfBound(LocalUserId, Privilege, 0);
}

FPlatformUserId FOnlineIdentityInterfaceRedpointGoogle::GetPlatformUserIdFromUniqueNetId(
    const FUniqueNetId &UniqueNetId) const
{
    return FPlatformUserId();
}

FString FOnlineIdentityInterfaceRedpointGoogle::GetAuthType() const
{
    return TEXT("");
}

#endif
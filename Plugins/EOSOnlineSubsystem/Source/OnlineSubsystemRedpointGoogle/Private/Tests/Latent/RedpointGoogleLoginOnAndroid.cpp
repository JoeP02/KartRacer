// Copyright June Rhodes 2024. All Rights Reserved.

#if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)

#include "Tests/Latent/RedpointGoogleLoginOnAndroid.h"

void FRedpointGoogleLoginOnAndroid::OnLoginComplete(
    int32 LocalUserNum,
    bool WasSuccessful,
    const FUniqueNetId &UserId,
    const FString &Error)
{
    this->Identity->ClearOnLoginCompleteDelegate_Handle(0, this->LoginDelegateHandle);
    this->LoginDelegateHandle.Reset();

    if (!WasSuccessful)
    {
        this->TestBase->TestTrue("Login call was successful", WasSuccessful);
        this->bIsDone = true;
        return;
    }

    this->TestBase->TestTrue("Login status is LoggedIn", this->Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn);

    UE_LOG(LogRedpointGoogle, Verbose, TEXT("OnLoginComplete finished successfully."));
    this->bIsDone = true;
    return;
}

bool FRedpointGoogleLoginOnAndroid::Update()
{
    if (!this->bHasInit)
    {
        UE_LOG(LogRedpointGoogle, Verbose, TEXT("Starting login on Android latent command"));

        IOnlineSubsystem *OSS = IOnlineSubsystem::Get(this->SubsystemName);
        if (!this->TestBase->TestTrue(TEXT("OSS is not null"), OSS != nullptr))
        {
            return true;
        }
        this->Identity = OSS->GetIdentityInterface();
        if (!this->TestBase->TestTrue(TEXT("Identity is not null"), this->Identity != nullptr))
        {
            return true;
        }

        if (this->Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
        {
            // We're already logged in (presumably from a previous test).
            return true;
        }

        this->LoginDelegateHandle = this->Identity->AddOnLoginCompleteDelegate_Handle(
            0,
            FOnLoginCompleteDelegate::CreateSP(this, &FRedpointGoogleLoginOnAndroid::OnLoginComplete));
        if (!this->Identity->AutoLogin(0))
        {
            this->Identity->ClearOnLoginCompleteDelegate_Handle(0, this->LoginDelegateHandle);
            this->LoginDelegateHandle.Reset();
            this->TestBase->TestTrue(TEXT("Login call starts successfully"), false);
            return true;
        }
        this->bHasInit = true;
    }

    return this->bIsDone;
}

#endif // #if EOS_GOOGLE_ENABLED && (!defined(UE_BUILD_SHIPPING) || !UE_BUILD_SHIPPING) && defined(UE_5_0_OR_LATER)
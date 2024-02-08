// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/Error/GenConv.h"

#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSAPI/Error/Gen.h"
#include "RedpointEOSAPI/Error/Decl.h"

const Redpoint::EOS::API::FError &Redpoint::EOS::API::ConvertError(EOS_EResult Result)
{
    switch (Result)
    {
    case EOS_EResult::EOS_Success:
        return Redpoint::EOS::API::Errors::Success();
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_UnexpectedError:
        return Redpoint::EOS::API::Errors::UnexpectedError();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NoConnection:
        return Redpoint::EOS::API::Errors::NoConnection();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidParameters:
        return Redpoint::EOS::API::Errors::InvalidParameters();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidRequest:
        return Redpoint::EOS::API::Errors::InvalidRequest();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_UnrecognizedResponse:
        return Redpoint::EOS::API::Errors::UnrecognizedResponse();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_IncompatibleVersion:
        return Redpoint::EOS::API::Errors::IncompatibleVersion();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NotConfigured:
        return Redpoint::EOS::API::Errors::NotConfigured();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AlreadyConfigured:
        return Redpoint::EOS::API::Errors::AlreadyConfigured();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NotImplemented:
        return Redpoint::EOS::API::Errors::NotImplemented();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Canceled:
        return Redpoint::EOS::API::Errors::Canceled();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NotFound:
        return Redpoint::EOS::API::Errors::NotFound();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_RequiredPatchAvailable:
        return Redpoint::EOS::API::Errors::Permission_RequiredPatchAvailable();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_RequiredSystemUpdate:
        return Redpoint::EOS::API::Errors::Permission_RequiredSystemUpdate();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_AgeRestrictionFailure:
        return Redpoint::EOS::API::Errors::Permission_AgeRestrictionFailure();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_AccountTypeFailure:
        return Redpoint::EOS::API::Errors::Permission_AccountTypeFailure();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_ChatRestriction:
        return Redpoint::EOS::API::Errors::Permission_ChatRestriction();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_UGCRestriction:
        return Redpoint::EOS::API::Errors::Permission_UGCRestriction();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_OnlinePlayRestricted:
        return Redpoint::EOS::API::Errors::Permission_OnlinePlayRestricted();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_OperationWillRetry:
        return Redpoint::EOS::API::Errors::OperationWillRetry();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ApplicationNotBootstrapped:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ApplicationNotBootstrapped();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ServiceNotInstalled:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotInstalled();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ServiceStartFailed:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceStartFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ServiceNotRunning:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotRunning();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidCredentials:
        return Redpoint::EOS::API::Errors::InvalidCredentials();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NoChange:
        return Redpoint::EOS::API::Errors::NoChange();
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_CustomInvites_InviteFailed:
        return Redpoint::EOS::API::Errors::CustomInvites_InviteFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_VersionMismatch:
        return Redpoint::EOS::API::Errors::VersionMismatch();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_LimitExceeded:
        return Redpoint::EOS::API::Errors::LimitExceeded();
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_UserInfo_BestDisplayNameIndeterminate:
        return Redpoint::EOS::API::Errors::UserInfo_BestDisplayNameIndeterminate();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Disabled:
        return Redpoint::EOS::API::Errors::Disabled();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DuplicateNotAllowed:
        return Redpoint::EOS::API::Errors::DuplicateNotAllowed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidSandboxId:
        return Redpoint::EOS::API::Errors::InvalidSandboxId();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TimedOut:
        return Redpoint::EOS::API::Errors::TimedOut();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PartialResult:
        return Redpoint::EOS::API::Errors::PartialResult();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Missing_Role:
        return Redpoint::EOS::API::Errors::Missing_Role();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidUser:
        return Redpoint::EOS::API::Errors::InvalidUser();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Missing_Feature:
        return Redpoint::EOS::API::Errors::Missing_Feature();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_Sandbox:
        return Redpoint::EOS::API::Errors::Invalid_Sandbox();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_Deployment:
        return Redpoint::EOS::API::Errors::Invalid_Deployment();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_Product:
        return Redpoint::EOS::API::Errors::Invalid_Product();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_ProductUserID:
        return Redpoint::EOS::API::Errors::Invalid_ProductUserID();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_ServiceFailure:
        return Redpoint::EOS::API::Errors::ServiceFailure();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_CacheDirectoryMissing:
        return Redpoint::EOS::API::Errors::CacheDirectoryMissing();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_CacheDirectoryInvalid:
        return Redpoint::EOS::API::Errors::CacheDirectoryInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidState:
        return Redpoint::EOS::API::Errors::InvalidState();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RequestInProgress:
        return Redpoint::EOS::API::Errors::RequestInProgress();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidAuth:
        return Redpoint::EOS::API::Errors::InvalidAuth();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_ApplicationSuspended:
        return Redpoint::EOS::API::Errors::ApplicationSuspended();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NetworkDisconnected:
        return Redpoint::EOS::API::Errors::NetworkDisconnected();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AccessDenied:
        return Redpoint::EOS::API::Errors::AccessDenied();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_MissingPermissions:
        return Redpoint::EOS::API::Errors::MissingPermissions();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Token_Not_Account:
        return Redpoint::EOS::API::Errors::Token_Not_Account();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TooManyRequests:
        return Redpoint::EOS::API::Errors::TooManyRequests();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AlreadyPending:
        return Redpoint::EOS::API::Errors::AlreadyPending();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountLocked:
        return Redpoint::EOS::API::Errors::Auth::AccountLocked();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountLockedForUpdate:
        return Redpoint::EOS::API::Errors::Auth::AccountLockedForUpdate();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_InvalidRefreshToken:
        return Redpoint::EOS::API::Errors::Auth::InvalidRefreshToken();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_InvalidToken:
        return Redpoint::EOS::API::Errors::Auth::InvalidToken();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AuthenticationFailure:
        return Redpoint::EOS::API::Errors::Auth::AuthenticationFailure();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_InvalidPlatformToken:
        return Redpoint::EOS::API::Errors::Auth::InvalidPlatformToken();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_WrongAccount:
        return Redpoint::EOS::API::Errors::Auth::WrongAccount();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_WrongClient:
        return Redpoint::EOS::API::Errors::Auth::WrongClient();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_FullAccountRequired:
        return Redpoint::EOS::API::Errors::Auth::FullAccountRequired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_HeadlessAccountRequired:
        return Redpoint::EOS::API::Errors::Auth::HeadlessAccountRequired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PasswordResetRequired:
        return Redpoint::EOS::API::Errors::Auth::PasswordResetRequired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PasswordCannotBeReused:
        return Redpoint::EOS::API::Errors::Auth::PasswordCannotBeReused();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_Expired:
        return Redpoint::EOS::API::Errors::Auth::Expired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ScopeConsentRequired:
        return Redpoint::EOS::API::Errors::Auth::ScopeConsentRequired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ApplicationNotFound:
        return Redpoint::EOS::API::Errors::Auth::ApplicationNotFound();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ScopeNotFound:
        return Redpoint::EOS::API::Errors::Auth::ScopeNotFound();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountFeatureRestricted:
        return Redpoint::EOS::API::Errors::Auth::AccountFeatureRestricted();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountPortalLoadError:
        return Redpoint::EOS::API::Errors::Auth::AccountPortalLoadError();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_CorrectiveActionRequired:
        return Redpoint::EOS::API::Errors::Auth::CorrectiveActionRequired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PinGrantCode:
        return Redpoint::EOS::API::Errors::Auth::PinGrantCode();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PinGrantExpired:
        return Redpoint::EOS::API::Errors::Auth::PinGrantExpired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PinGrantPending:
        return Redpoint::EOS::API::Errors::Auth::PinGrantPending();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthNotLinked:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthNotLinked();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthRevoked:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthRevoked();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthInvalid:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthRestricted:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthRestricted();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthCannotLogin:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthCannotLogin();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthExpired:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthExpired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthIsLastLoginType:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthIsLastLoginType();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExchangeCodeNotFound:
        return Redpoint::EOS::API::Errors::Auth::ExchangeCodeNotFound();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_OriginatingExchangeCodeSessionExpired:
        return Redpoint::EOS::API::Errors::Auth::OriginatingExchangeCodeSessionExpired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountNotActive:
        return Redpoint::EOS::API::Errors::Auth::AccountNotActive();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_MFARequired:
        return Redpoint::EOS::API::Errors::Auth::MFARequired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ParentalControls:
        return Redpoint::EOS::API::Errors::Auth::ParentalControls();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_NoRealId:
        return Redpoint::EOS::API::Errors::Auth::NoRealId();
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_Auth_UserInterfaceRequired:
        return Redpoint::EOS::API::Errors::Auth::UserInterfaceRequired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_InviteAwaitingAcceptance:
        return Redpoint::EOS::API::Errors::Friends::InviteAwaitingAcceptance();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_NoInvitation:
        return Redpoint::EOS::API::Errors::Friends::NoInvitation();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_AlreadyFriends:
        return Redpoint::EOS::API::Errors::Friends::AlreadyFriends();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_NotFriends:
        return Redpoint::EOS::API::Errors::Friends::NotFriends();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_TargetUserTooManyInvites:
        return Redpoint::EOS::API::Errors::Friends::TargetUserTooManyInvites();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_LocalUserTooManyInvites:
        return Redpoint::EOS::API::Errors::Friends::LocalUserTooManyInvites();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_TargetUserFriendLimitExceeded:
        return Redpoint::EOS::API::Errors::Friends::TargetUserFriendLimitExceeded();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_LocalUserFriendLimitExceeded:
        return Redpoint::EOS::API::Errors::Friends::LocalUserFriendLimitExceeded();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataLengthInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataKeyInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataKeyInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataKeyLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataKeyLengthInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataValueInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataValueInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataValueLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataValueLengthInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_RichTextInvalid:
        return Redpoint::EOS::API::Errors::Presence::RichTextInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_RichTextLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::RichTextLengthInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_StatusInvalid:
        return Redpoint::EOS::API::Errors::Presence::StatusInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_EntitlementStale:
        return Redpoint::EOS::API::Errors::Ecom::EntitlementStale();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CatalogOfferStale:
        return Redpoint::EOS::API::Errors::Ecom::CatalogOfferStale();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CatalogItemStale:
        return Redpoint::EOS::API::Errors::Ecom::CatalogItemStale();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CatalogOfferPriceInvalid:
        return Redpoint::EOS::API::Errors::Ecom::CatalogOfferPriceInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CheckoutLoadError:
        return Redpoint::EOS::API::Errors::Ecom::CheckoutLoadError();
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_Ecom_PurchaseProcessing:
        return Redpoint::EOS::API::Errors::Ecom::PurchaseProcessing();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SessionInProgress:
        return Redpoint::EOS::API::Errors::Sessions::SessionInProgress();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_TooManyPlayers:
        return Redpoint::EOS::API::Errors::Sessions::TooManyPlayers();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_NoPermission:
        return Redpoint::EOS::API::Errors::Sessions::NoPermission();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SessionAlreadyExists:
        return Redpoint::EOS::API::Errors::Sessions::SessionAlreadyExists();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InvalidLock:
        return Redpoint::EOS::API::Errors::Sessions::InvalidLock();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InvalidSession:
        return Redpoint::EOS::API::Errors::Sessions::InvalidSession();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SandboxNotAllowed:
        return Redpoint::EOS::API::Errors::Sessions::SandboxNotAllowed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InviteFailed:
        return Redpoint::EOS::API::Errors::Sessions::InviteFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InviteNotFound:
        return Redpoint::EOS::API::Errors::Sessions::InviteNotFound();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_UpsertNotAllowed:
        return Redpoint::EOS::API::Errors::Sessions::UpsertNotAllowed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_AggregationFailed:
        return Redpoint::EOS::API::Errors::Sessions::AggregationFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_HostAtCapacity:
        return Redpoint::EOS::API::Errors::Sessions::HostAtCapacity();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SandboxAtCapacity:
        return Redpoint::EOS::API::Errors::Sessions::SandboxAtCapacity();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SessionNotAnonymous:
        return Redpoint::EOS::API::Errors::Sessions::SessionNotAnonymous();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_OutOfSync:
        return Redpoint::EOS::API::Errors::Sessions::OutOfSync();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_TooManyInvites:
        return Redpoint::EOS::API::Errors::Sessions::TooManyInvites();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_PresenceSessionExists:
        return Redpoint::EOS::API::Errors::Sessions::PresenceSessionExists();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_DeploymentAtCapacity:
        return Redpoint::EOS::API::Errors::Sessions::DeploymentAtCapacity();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_NotAllowed:
        return Redpoint::EOS::API::Errors::Sessions::NotAllowed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_PlayerSanctioned:
        return Redpoint::EOS::API::Errors::Sessions::PlayerSanctioned();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FilenameInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FilenameLengthInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameLengthInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FilenameInvalidChars:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalidChars();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileSizeTooLarge:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeTooLarge();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileSizeInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileHandleInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileHandleInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_DataInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::DataInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_DataLengthInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::DataLengthInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_StartIndexInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::StartIndexInvalid();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_RequestInProgress:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::RequestInProgress();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_UserThrottled:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::UserThrottled();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_EncryptionKeyNotSet:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::EncryptionKeyNotSet();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_UserErrorFromDataCallback:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::UserErrorFromDataCallback();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileHeaderHasNewerVersion:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileHeaderHasNewerVersion();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileCorrupted:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileCorrupted();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_ExternalTokenValidationFailed:
        return Redpoint::EOS::API::Errors::Connect::ExternalTokenValidationFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_UserAlreadyExists:
        return Redpoint::EOS::API::Errors::Connect::UserAlreadyExists();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_AuthExpired:
        return Redpoint::EOS::API::Errors::Connect::AuthExpired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_InvalidToken:
        return Redpoint::EOS::API::Errors::Connect::InvalidToken();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_UnsupportedTokenType:
        return Redpoint::EOS::API::Errors::Connect::UnsupportedTokenType();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_LinkAccountFailed:
        return Redpoint::EOS::API::Errors::Connect::LinkAccountFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_ExternalServiceUnavailable:
        return Redpoint::EOS::API::Errors::Connect::ExternalServiceUnavailable();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_ExternalServiceConfigurationFailure:
        return Redpoint::EOS::API::Errors::Connect::ExternalServiceConfigurationFailure();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_UI_SocialOverlayLoadError:
        return Redpoint::EOS::API::Errors::UI::SocialOverlayLoadError();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_NotOwner:
        return Redpoint::EOS::API::Errors::Lobby::NotOwner();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InvalidLock:
        return Redpoint::EOS::API::Errors::Lobby::InvalidLock();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_LobbyAlreadyExists:
        return Redpoint::EOS::API::Errors::Lobby::LobbyAlreadyExists();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_SessionInProgress:
        return Redpoint::EOS::API::Errors::Lobby::SessionInProgress();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_TooManyPlayers:
        return Redpoint::EOS::API::Errors::Lobby::TooManyPlayers();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_NoPermission:
        return Redpoint::EOS::API::Errors::Lobby::NoPermission();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InvalidSession:
        return Redpoint::EOS::API::Errors::Lobby::InvalidSession();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_SandboxNotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::SandboxNotAllowed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InviteFailed:
        return Redpoint::EOS::API::Errors::Lobby::InviteFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InviteNotFound:
        return Redpoint::EOS::API::Errors::Lobby::InviteNotFound();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_UpsertNotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::UpsertNotAllowed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_AggregationFailed:
        return Redpoint::EOS::API::Errors::Lobby::AggregationFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_HostAtCapacity:
        return Redpoint::EOS::API::Errors::Lobby::HostAtCapacity();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_SandboxAtCapacity:
        return Redpoint::EOS::API::Errors::Lobby::SandboxAtCapacity();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_TooManyInvites:
        return Redpoint::EOS::API::Errors::Lobby::TooManyInvites();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_DeploymentAtCapacity:
        return Redpoint::EOS::API::Errors::Lobby::DeploymentAtCapacity();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_NotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::NotAllowed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_MemberUpdateOnly:
        return Redpoint::EOS::API::Errors::Lobby::MemberUpdateOnly();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_PresenceLobbyExists:
        return Redpoint::EOS::API::Errors::Lobby::PresenceLobbyExists();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_VoiceNotEnabled:
        return Redpoint::EOS::API::Errors::Lobby::VoiceNotEnabled();
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_Lobby_PlatformNotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::PlatformNotAllowed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_UserErrorFromDataCallback:
        return Redpoint::EOS::API::Errors::TitleStorage::UserErrorFromDataCallback();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_EncryptionKeyNotSet:
        return Redpoint::EOS::API::Errors::TitleStorage::EncryptionKeyNotSet();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_FileCorrupted:
        return Redpoint::EOS::API::Errors::TitleStorage::FileCorrupted();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_FileHeaderHasNewerVersion:
        return Redpoint::EOS::API::Errors::TitleStorage::FileHeaderHasNewerVersion();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModSdkProcessIsAlreadyRunning:
        return Redpoint::EOS::API::Errors::Mods::ModSdkProcessIsAlreadyRunning();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModSdkCommandIsEmpty:
        return Redpoint::EOS::API::Errors::Mods::ModSdkCommandIsEmpty();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModSdkProcessCreationFailed:
        return Redpoint::EOS::API::Errors::Mods::ModSdkProcessCreationFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_CriticalError:
        return Redpoint::EOS::API::Errors::Mods::CriticalError();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ToolInternalError:
        return Redpoint::EOS::API::Errors::Mods::ToolInternalError();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_IPCFailure:
        return Redpoint::EOS::API::Errors::Mods::IPCFailure();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_InvalidIPCResponse:
        return Redpoint::EOS::API::Errors::Mods::InvalidIPCResponse();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_URILaunchFailure:
        return Redpoint::EOS::API::Errors::Mods::URILaunchFailure();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModIsNotInstalled:
        return Redpoint::EOS::API::Errors::Mods::ModIsNotInstalled();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_UserDoesNotOwnTheGame:
        return Redpoint::EOS::API::Errors::Mods::UserDoesNotOwnTheGame();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_OfferRequestByIdInvalidResult:
        return Redpoint::EOS::API::Errors::Mods::OfferRequestByIdInvalidResult();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_CouldNotFindOffer:
        return Redpoint::EOS::API::Errors::Mods::CouldNotFindOffer();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_OfferRequestByIdFailure:
        return Redpoint::EOS::API::Errors::Mods::OfferRequestByIdFailure();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_PurchaseFailure:
        return Redpoint::EOS::API::Errors::Mods::PurchaseFailure();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_InvalidGameInstallInfo:
        return Redpoint::EOS::API::Errors::Mods::InvalidGameInstallInfo();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_CannotGetManifestLocation:
        return Redpoint::EOS::API::Errors::Mods::CannotGetManifestLocation();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_UnsupportedOS:
        return Redpoint::EOS::API::Errors::Mods::UnsupportedOS();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientProtectionNotAvailable:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientProtectionNotAvailable();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_InvalidMode:
        return Redpoint::EOS::API::Errors::AntiCheat::InvalidMode();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientProductIdMismatch:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientProductIdMismatch();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientSandboxIdMismatch:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientSandboxIdMismatch();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ProtectMessageSessionKeyRequired:
        return Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageSessionKeyRequired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ProtectMessageValidationFailed:
        return Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageValidationFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ProtectMessageInitializationFailed:
        return Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageInitializationFailed();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_PeerAlreadyRegistered:
        return Redpoint::EOS::API::Errors::AntiCheat::PeerAlreadyRegistered();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_PeerNotFound:
        return Redpoint::EOS::API::Errors::AntiCheat::PeerNotFound();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_PeerNotProtected:
        return Redpoint::EOS::API::Errors::AntiCheat::PeerNotProtected();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientDeploymentIdMismatch:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientDeploymentIdMismatch();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_DeviceIdAuthIsNotSupported:
        return Redpoint::EOS::API::Errors::AntiCheat::DeviceIdAuthIsNotSupported();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_TooManyParticipants:
        return Redpoint::EOS::API::Errors::RTC::TooManyParticipants();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_RoomAlreadyExists:
        return Redpoint::EOS::API::Errors::RTC::RoomAlreadyExists();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_UserKicked:
        return Redpoint::EOS::API::Errors::RTC::UserKicked();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_UserBanned:
        return Redpoint::EOS::API::Errors::RTC::UserBanned();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_RoomWasLeft:
        return Redpoint::EOS::API::Errors::RTC::RoomWasLeft();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_ReconnectionTimegateExpired:
        return Redpoint::EOS::API::Errors::RTC::ReconnectionTimegateExpired();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_ShutdownInvoked:
        return Redpoint::EOS::API::Errors::RTC::ShutdownInvoked();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_UserIsInBlocklist:
        return Redpoint::EOS::API::Errors::RTC::UserIsInBlocklist();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_ProgressionSnapshot_SnapshotIdUnavailable:
        return Redpoint::EOS::API::Errors::ProgressionSnapshot::SnapshotIdUnavailable();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_KWS_ParentEmailMissing:
        return Redpoint::EOS::API::Errors::KWS::ParentEmailMissing();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_KWS_UserGraduated:
        return Redpoint::EOS::API::Errors::KWS::UserGraduated();
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Android_JavaVMNotStored:
        return Redpoint::EOS::API::Errors::Android::JavaVMNotStored();
#endif
    default:
        return Redpoint::EOS::API::Errors::UnexpectedError();
    }
}

const Redpoint::EOS::API::FError Redpoint::EOS::API::ConvertError(const TCHAR* InCall, const FString& InContextMsg, EOS_EResult Result)
{
    switch (Result)
    {
    case EOS_EResult::EOS_Success:
        return Redpoint::EOS::API::Errors::Success(InCall, InContextMsg);
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_UnexpectedError:
        return Redpoint::EOS::API::Errors::UnexpectedError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NoConnection:
        return Redpoint::EOS::API::Errors::NoConnection(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidParameters:
        return Redpoint::EOS::API::Errors::InvalidParameters(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidRequest:
        return Redpoint::EOS::API::Errors::InvalidRequest(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_UnrecognizedResponse:
        return Redpoint::EOS::API::Errors::UnrecognizedResponse(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_IncompatibleVersion:
        return Redpoint::EOS::API::Errors::IncompatibleVersion(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NotConfigured:
        return Redpoint::EOS::API::Errors::NotConfigured(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AlreadyConfigured:
        return Redpoint::EOS::API::Errors::AlreadyConfigured(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NotImplemented:
        return Redpoint::EOS::API::Errors::NotImplemented(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Canceled:
        return Redpoint::EOS::API::Errors::Canceled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NotFound:
        return Redpoint::EOS::API::Errors::NotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_RequiredPatchAvailable:
        return Redpoint::EOS::API::Errors::Permission_RequiredPatchAvailable(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_RequiredSystemUpdate:
        return Redpoint::EOS::API::Errors::Permission_RequiredSystemUpdate(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_AgeRestrictionFailure:
        return Redpoint::EOS::API::Errors::Permission_AgeRestrictionFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_AccountTypeFailure:
        return Redpoint::EOS::API::Errors::Permission_AccountTypeFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_ChatRestriction:
        return Redpoint::EOS::API::Errors::Permission_ChatRestriction(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_UGCRestriction:
        return Redpoint::EOS::API::Errors::Permission_UGCRestriction(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_OnlinePlayRestricted:
        return Redpoint::EOS::API::Errors::Permission_OnlinePlayRestricted(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_OperationWillRetry:
        return Redpoint::EOS::API::Errors::OperationWillRetry(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ApplicationNotBootstrapped:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ApplicationNotBootstrapped(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ServiceNotInstalled:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotInstalled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ServiceStartFailed:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceStartFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ServiceNotRunning:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotRunning(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidCredentials:
        return Redpoint::EOS::API::Errors::InvalidCredentials(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NoChange:
        return Redpoint::EOS::API::Errors::NoChange(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_CustomInvites_InviteFailed:
        return Redpoint::EOS::API::Errors::CustomInvites_InviteFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_VersionMismatch:
        return Redpoint::EOS::API::Errors::VersionMismatch(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_LimitExceeded:
        return Redpoint::EOS::API::Errors::LimitExceeded(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_UserInfo_BestDisplayNameIndeterminate:
        return Redpoint::EOS::API::Errors::UserInfo_BestDisplayNameIndeterminate(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Disabled:
        return Redpoint::EOS::API::Errors::Disabled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DuplicateNotAllowed:
        return Redpoint::EOS::API::Errors::DuplicateNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidSandboxId:
        return Redpoint::EOS::API::Errors::InvalidSandboxId(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TimedOut:
        return Redpoint::EOS::API::Errors::TimedOut(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PartialResult:
        return Redpoint::EOS::API::Errors::PartialResult(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Missing_Role:
        return Redpoint::EOS::API::Errors::Missing_Role(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidUser:
        return Redpoint::EOS::API::Errors::InvalidUser(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Missing_Feature:
        return Redpoint::EOS::API::Errors::Missing_Feature(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_Sandbox:
        return Redpoint::EOS::API::Errors::Invalid_Sandbox(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_Deployment:
        return Redpoint::EOS::API::Errors::Invalid_Deployment(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_Product:
        return Redpoint::EOS::API::Errors::Invalid_Product(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_ProductUserID:
        return Redpoint::EOS::API::Errors::Invalid_ProductUserID(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_ServiceFailure:
        return Redpoint::EOS::API::Errors::ServiceFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_CacheDirectoryMissing:
        return Redpoint::EOS::API::Errors::CacheDirectoryMissing(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_CacheDirectoryInvalid:
        return Redpoint::EOS::API::Errors::CacheDirectoryInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidState:
        return Redpoint::EOS::API::Errors::InvalidState(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RequestInProgress:
        return Redpoint::EOS::API::Errors::RequestInProgress(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidAuth:
        return Redpoint::EOS::API::Errors::InvalidAuth(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_ApplicationSuspended:
        return Redpoint::EOS::API::Errors::ApplicationSuspended(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NetworkDisconnected:
        return Redpoint::EOS::API::Errors::NetworkDisconnected(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AccessDenied:
        return Redpoint::EOS::API::Errors::AccessDenied(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_MissingPermissions:
        return Redpoint::EOS::API::Errors::MissingPermissions(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Token_Not_Account:
        return Redpoint::EOS::API::Errors::Token_Not_Account(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TooManyRequests:
        return Redpoint::EOS::API::Errors::TooManyRequests(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AlreadyPending:
        return Redpoint::EOS::API::Errors::AlreadyPending(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountLocked:
        return Redpoint::EOS::API::Errors::Auth::AccountLocked(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountLockedForUpdate:
        return Redpoint::EOS::API::Errors::Auth::AccountLockedForUpdate(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_InvalidRefreshToken:
        return Redpoint::EOS::API::Errors::Auth::InvalidRefreshToken(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_InvalidToken:
        return Redpoint::EOS::API::Errors::Auth::InvalidToken(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AuthenticationFailure:
        return Redpoint::EOS::API::Errors::Auth::AuthenticationFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_InvalidPlatformToken:
        return Redpoint::EOS::API::Errors::Auth::InvalidPlatformToken(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_WrongAccount:
        return Redpoint::EOS::API::Errors::Auth::WrongAccount(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_WrongClient:
        return Redpoint::EOS::API::Errors::Auth::WrongClient(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_FullAccountRequired:
        return Redpoint::EOS::API::Errors::Auth::FullAccountRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_HeadlessAccountRequired:
        return Redpoint::EOS::API::Errors::Auth::HeadlessAccountRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PasswordResetRequired:
        return Redpoint::EOS::API::Errors::Auth::PasswordResetRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PasswordCannotBeReused:
        return Redpoint::EOS::API::Errors::Auth::PasswordCannotBeReused(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_Expired:
        return Redpoint::EOS::API::Errors::Auth::Expired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ScopeConsentRequired:
        return Redpoint::EOS::API::Errors::Auth::ScopeConsentRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ApplicationNotFound:
        return Redpoint::EOS::API::Errors::Auth::ApplicationNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ScopeNotFound:
        return Redpoint::EOS::API::Errors::Auth::ScopeNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountFeatureRestricted:
        return Redpoint::EOS::API::Errors::Auth::AccountFeatureRestricted(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountPortalLoadError:
        return Redpoint::EOS::API::Errors::Auth::AccountPortalLoadError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_CorrectiveActionRequired:
        return Redpoint::EOS::API::Errors::Auth::CorrectiveActionRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PinGrantCode:
        return Redpoint::EOS::API::Errors::Auth::PinGrantCode(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PinGrantExpired:
        return Redpoint::EOS::API::Errors::Auth::PinGrantExpired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PinGrantPending:
        return Redpoint::EOS::API::Errors::Auth::PinGrantPending(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthNotLinked:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthNotLinked(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthRevoked:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthRevoked(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthInvalid:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthRestricted:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthRestricted(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthCannotLogin:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthCannotLogin(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthExpired:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthExpired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthIsLastLoginType:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthIsLastLoginType(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExchangeCodeNotFound:
        return Redpoint::EOS::API::Errors::Auth::ExchangeCodeNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_OriginatingExchangeCodeSessionExpired:
        return Redpoint::EOS::API::Errors::Auth::OriginatingExchangeCodeSessionExpired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountNotActive:
        return Redpoint::EOS::API::Errors::Auth::AccountNotActive(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_MFARequired:
        return Redpoint::EOS::API::Errors::Auth::MFARequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ParentalControls:
        return Redpoint::EOS::API::Errors::Auth::ParentalControls(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_NoRealId:
        return Redpoint::EOS::API::Errors::Auth::NoRealId(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_Auth_UserInterfaceRequired:
        return Redpoint::EOS::API::Errors::Auth::UserInterfaceRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_InviteAwaitingAcceptance:
        return Redpoint::EOS::API::Errors::Friends::InviteAwaitingAcceptance(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_NoInvitation:
        return Redpoint::EOS::API::Errors::Friends::NoInvitation(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_AlreadyFriends:
        return Redpoint::EOS::API::Errors::Friends::AlreadyFriends(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_NotFriends:
        return Redpoint::EOS::API::Errors::Friends::NotFriends(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_TargetUserTooManyInvites:
        return Redpoint::EOS::API::Errors::Friends::TargetUserTooManyInvites(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_LocalUserTooManyInvites:
        return Redpoint::EOS::API::Errors::Friends::LocalUserTooManyInvites(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_TargetUserFriendLimitExceeded:
        return Redpoint::EOS::API::Errors::Friends::TargetUserFriendLimitExceeded(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_LocalUserFriendLimitExceeded:
        return Redpoint::EOS::API::Errors::Friends::LocalUserFriendLimitExceeded(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataKeyInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataKeyInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataKeyLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataKeyLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataValueInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataValueInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataValueLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataValueLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_RichTextInvalid:
        return Redpoint::EOS::API::Errors::Presence::RichTextInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_RichTextLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::RichTextLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_StatusInvalid:
        return Redpoint::EOS::API::Errors::Presence::StatusInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_EntitlementStale:
        return Redpoint::EOS::API::Errors::Ecom::EntitlementStale(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CatalogOfferStale:
        return Redpoint::EOS::API::Errors::Ecom::CatalogOfferStale(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CatalogItemStale:
        return Redpoint::EOS::API::Errors::Ecom::CatalogItemStale(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CatalogOfferPriceInvalid:
        return Redpoint::EOS::API::Errors::Ecom::CatalogOfferPriceInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CheckoutLoadError:
        return Redpoint::EOS::API::Errors::Ecom::CheckoutLoadError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_Ecom_PurchaseProcessing:
        return Redpoint::EOS::API::Errors::Ecom::PurchaseProcessing(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SessionInProgress:
        return Redpoint::EOS::API::Errors::Sessions::SessionInProgress(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_TooManyPlayers:
        return Redpoint::EOS::API::Errors::Sessions::TooManyPlayers(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_NoPermission:
        return Redpoint::EOS::API::Errors::Sessions::NoPermission(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SessionAlreadyExists:
        return Redpoint::EOS::API::Errors::Sessions::SessionAlreadyExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InvalidLock:
        return Redpoint::EOS::API::Errors::Sessions::InvalidLock(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InvalidSession:
        return Redpoint::EOS::API::Errors::Sessions::InvalidSession(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SandboxNotAllowed:
        return Redpoint::EOS::API::Errors::Sessions::SandboxNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InviteFailed:
        return Redpoint::EOS::API::Errors::Sessions::InviteFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InviteNotFound:
        return Redpoint::EOS::API::Errors::Sessions::InviteNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_UpsertNotAllowed:
        return Redpoint::EOS::API::Errors::Sessions::UpsertNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_AggregationFailed:
        return Redpoint::EOS::API::Errors::Sessions::AggregationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_HostAtCapacity:
        return Redpoint::EOS::API::Errors::Sessions::HostAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SandboxAtCapacity:
        return Redpoint::EOS::API::Errors::Sessions::SandboxAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SessionNotAnonymous:
        return Redpoint::EOS::API::Errors::Sessions::SessionNotAnonymous(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_OutOfSync:
        return Redpoint::EOS::API::Errors::Sessions::OutOfSync(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_TooManyInvites:
        return Redpoint::EOS::API::Errors::Sessions::TooManyInvites(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_PresenceSessionExists:
        return Redpoint::EOS::API::Errors::Sessions::PresenceSessionExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_DeploymentAtCapacity:
        return Redpoint::EOS::API::Errors::Sessions::DeploymentAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_NotAllowed:
        return Redpoint::EOS::API::Errors::Sessions::NotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_PlayerSanctioned:
        return Redpoint::EOS::API::Errors::Sessions::PlayerSanctioned(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FilenameInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FilenameLengthInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FilenameInvalidChars:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalidChars(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileSizeTooLarge:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeTooLarge(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileSizeInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileHandleInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileHandleInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_DataInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::DataInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_DataLengthInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::DataLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_StartIndexInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::StartIndexInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_RequestInProgress:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::RequestInProgress(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_UserThrottled:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::UserThrottled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_EncryptionKeyNotSet:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::EncryptionKeyNotSet(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_UserErrorFromDataCallback:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::UserErrorFromDataCallback(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileHeaderHasNewerVersion:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileHeaderHasNewerVersion(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileCorrupted:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileCorrupted(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_ExternalTokenValidationFailed:
        return Redpoint::EOS::API::Errors::Connect::ExternalTokenValidationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_UserAlreadyExists:
        return Redpoint::EOS::API::Errors::Connect::UserAlreadyExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_AuthExpired:
        return Redpoint::EOS::API::Errors::Connect::AuthExpired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_InvalidToken:
        return Redpoint::EOS::API::Errors::Connect::InvalidToken(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_UnsupportedTokenType:
        return Redpoint::EOS::API::Errors::Connect::UnsupportedTokenType(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_LinkAccountFailed:
        return Redpoint::EOS::API::Errors::Connect::LinkAccountFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_ExternalServiceUnavailable:
        return Redpoint::EOS::API::Errors::Connect::ExternalServiceUnavailable(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_ExternalServiceConfigurationFailure:
        return Redpoint::EOS::API::Errors::Connect::ExternalServiceConfigurationFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_UI_SocialOverlayLoadError:
        return Redpoint::EOS::API::Errors::UI::SocialOverlayLoadError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_NotOwner:
        return Redpoint::EOS::API::Errors::Lobby::NotOwner(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InvalidLock:
        return Redpoint::EOS::API::Errors::Lobby::InvalidLock(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_LobbyAlreadyExists:
        return Redpoint::EOS::API::Errors::Lobby::LobbyAlreadyExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_SessionInProgress:
        return Redpoint::EOS::API::Errors::Lobby::SessionInProgress(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_TooManyPlayers:
        return Redpoint::EOS::API::Errors::Lobby::TooManyPlayers(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_NoPermission:
        return Redpoint::EOS::API::Errors::Lobby::NoPermission(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InvalidSession:
        return Redpoint::EOS::API::Errors::Lobby::InvalidSession(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_SandboxNotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::SandboxNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InviteFailed:
        return Redpoint::EOS::API::Errors::Lobby::InviteFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InviteNotFound:
        return Redpoint::EOS::API::Errors::Lobby::InviteNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_UpsertNotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::UpsertNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_AggregationFailed:
        return Redpoint::EOS::API::Errors::Lobby::AggregationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_HostAtCapacity:
        return Redpoint::EOS::API::Errors::Lobby::HostAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_SandboxAtCapacity:
        return Redpoint::EOS::API::Errors::Lobby::SandboxAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_TooManyInvites:
        return Redpoint::EOS::API::Errors::Lobby::TooManyInvites(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_DeploymentAtCapacity:
        return Redpoint::EOS::API::Errors::Lobby::DeploymentAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_NotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::NotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_MemberUpdateOnly:
        return Redpoint::EOS::API::Errors::Lobby::MemberUpdateOnly(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_PresenceLobbyExists:
        return Redpoint::EOS::API::Errors::Lobby::PresenceLobbyExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_VoiceNotEnabled:
        return Redpoint::EOS::API::Errors::Lobby::VoiceNotEnabled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_Lobby_PlatformNotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::PlatformNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_UserErrorFromDataCallback:
        return Redpoint::EOS::API::Errors::TitleStorage::UserErrorFromDataCallback(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_EncryptionKeyNotSet:
        return Redpoint::EOS::API::Errors::TitleStorage::EncryptionKeyNotSet(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_FileCorrupted:
        return Redpoint::EOS::API::Errors::TitleStorage::FileCorrupted(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_FileHeaderHasNewerVersion:
        return Redpoint::EOS::API::Errors::TitleStorage::FileHeaderHasNewerVersion(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModSdkProcessIsAlreadyRunning:
        return Redpoint::EOS::API::Errors::Mods::ModSdkProcessIsAlreadyRunning(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModSdkCommandIsEmpty:
        return Redpoint::EOS::API::Errors::Mods::ModSdkCommandIsEmpty(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModSdkProcessCreationFailed:
        return Redpoint::EOS::API::Errors::Mods::ModSdkProcessCreationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_CriticalError:
        return Redpoint::EOS::API::Errors::Mods::CriticalError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ToolInternalError:
        return Redpoint::EOS::API::Errors::Mods::ToolInternalError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_IPCFailure:
        return Redpoint::EOS::API::Errors::Mods::IPCFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_InvalidIPCResponse:
        return Redpoint::EOS::API::Errors::Mods::InvalidIPCResponse(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_URILaunchFailure:
        return Redpoint::EOS::API::Errors::Mods::URILaunchFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModIsNotInstalled:
        return Redpoint::EOS::API::Errors::Mods::ModIsNotInstalled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_UserDoesNotOwnTheGame:
        return Redpoint::EOS::API::Errors::Mods::UserDoesNotOwnTheGame(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_OfferRequestByIdInvalidResult:
        return Redpoint::EOS::API::Errors::Mods::OfferRequestByIdInvalidResult(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_CouldNotFindOffer:
        return Redpoint::EOS::API::Errors::Mods::CouldNotFindOffer(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_OfferRequestByIdFailure:
        return Redpoint::EOS::API::Errors::Mods::OfferRequestByIdFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_PurchaseFailure:
        return Redpoint::EOS::API::Errors::Mods::PurchaseFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_InvalidGameInstallInfo:
        return Redpoint::EOS::API::Errors::Mods::InvalidGameInstallInfo(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_CannotGetManifestLocation:
        return Redpoint::EOS::API::Errors::Mods::CannotGetManifestLocation(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_UnsupportedOS:
        return Redpoint::EOS::API::Errors::Mods::UnsupportedOS(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientProtectionNotAvailable:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientProtectionNotAvailable(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_InvalidMode:
        return Redpoint::EOS::API::Errors::AntiCheat::InvalidMode(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientProductIdMismatch:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientProductIdMismatch(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientSandboxIdMismatch:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientSandboxIdMismatch(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ProtectMessageSessionKeyRequired:
        return Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageSessionKeyRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ProtectMessageValidationFailed:
        return Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageValidationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ProtectMessageInitializationFailed:
        return Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageInitializationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_PeerAlreadyRegistered:
        return Redpoint::EOS::API::Errors::AntiCheat::PeerAlreadyRegistered(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_PeerNotFound:
        return Redpoint::EOS::API::Errors::AntiCheat::PeerNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_PeerNotProtected:
        return Redpoint::EOS::API::Errors::AntiCheat::PeerNotProtected(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientDeploymentIdMismatch:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientDeploymentIdMismatch(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_DeviceIdAuthIsNotSupported:
        return Redpoint::EOS::API::Errors::AntiCheat::DeviceIdAuthIsNotSupported(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_TooManyParticipants:
        return Redpoint::EOS::API::Errors::RTC::TooManyParticipants(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_RoomAlreadyExists:
        return Redpoint::EOS::API::Errors::RTC::RoomAlreadyExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_UserKicked:
        return Redpoint::EOS::API::Errors::RTC::UserKicked(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_UserBanned:
        return Redpoint::EOS::API::Errors::RTC::UserBanned(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_RoomWasLeft:
        return Redpoint::EOS::API::Errors::RTC::RoomWasLeft(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_ReconnectionTimegateExpired:
        return Redpoint::EOS::API::Errors::RTC::ReconnectionTimegateExpired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_ShutdownInvoked:
        return Redpoint::EOS::API::Errors::RTC::ShutdownInvoked(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_UserIsInBlocklist:
        return Redpoint::EOS::API::Errors::RTC::UserIsInBlocklist(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_ProgressionSnapshot_SnapshotIdUnavailable:
        return Redpoint::EOS::API::Errors::ProgressionSnapshot::SnapshotIdUnavailable(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_KWS_ParentEmailMissing:
        return Redpoint::EOS::API::Errors::KWS::ParentEmailMissing(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_KWS_UserGraduated:
        return Redpoint::EOS::API::Errors::KWS::UserGraduated(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Android_JavaVMNotStored:
        return Redpoint::EOS::API::Errors::Android::JavaVMNotStored(InCall, InContextMsg);
#endif

    default:
        return Redpoint::EOS::API::Errors::UnexpectedError(InCall, InContextMsg);
    }
}

const Redpoint::EOS::API::FError Redpoint::EOS::API::ConvertError(const TCHAR* InCall, const TCHAR* InContextMsg, EOS_EResult Result)
{
    switch (Result)
    {
    case EOS_EResult::EOS_Success:
        return Redpoint::EOS::API::Errors::Success(InCall, InContextMsg);
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_UnexpectedError:
        return Redpoint::EOS::API::Errors::UnexpectedError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NoConnection:
        return Redpoint::EOS::API::Errors::NoConnection(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidParameters:
        return Redpoint::EOS::API::Errors::InvalidParameters(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidRequest:
        return Redpoint::EOS::API::Errors::InvalidRequest(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_UnrecognizedResponse:
        return Redpoint::EOS::API::Errors::UnrecognizedResponse(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_IncompatibleVersion:
        return Redpoint::EOS::API::Errors::IncompatibleVersion(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NotConfigured:
        return Redpoint::EOS::API::Errors::NotConfigured(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AlreadyConfigured:
        return Redpoint::EOS::API::Errors::AlreadyConfigured(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NotImplemented:
        return Redpoint::EOS::API::Errors::NotImplemented(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Canceled:
        return Redpoint::EOS::API::Errors::Canceled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NotFound:
        return Redpoint::EOS::API::Errors::NotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_RequiredPatchAvailable:
        return Redpoint::EOS::API::Errors::Permission_RequiredPatchAvailable(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_RequiredSystemUpdate:
        return Redpoint::EOS::API::Errors::Permission_RequiredSystemUpdate(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_AgeRestrictionFailure:
        return Redpoint::EOS::API::Errors::Permission_AgeRestrictionFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_AccountTypeFailure:
        return Redpoint::EOS::API::Errors::Permission_AccountTypeFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_ChatRestriction:
        return Redpoint::EOS::API::Errors::Permission_ChatRestriction(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_UGCRestriction:
        return Redpoint::EOS::API::Errors::Permission_UGCRestriction(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Permission_OnlinePlayRestricted:
        return Redpoint::EOS::API::Errors::Permission_OnlinePlayRestricted(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_OperationWillRetry:
        return Redpoint::EOS::API::Errors::OperationWillRetry(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ApplicationNotBootstrapped:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ApplicationNotBootstrapped(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ServiceNotInstalled:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotInstalled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ServiceStartFailed:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceStartFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DesktopCrossplay_ServiceNotRunning:
        return Redpoint::EOS::API::Errors::DesktopCrossplay_ServiceNotRunning(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidCredentials:
        return Redpoint::EOS::API::Errors::InvalidCredentials(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NoChange:
        return Redpoint::EOS::API::Errors::NoChange(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_CustomInvites_InviteFailed:
        return Redpoint::EOS::API::Errors::CustomInvites_InviteFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_VersionMismatch:
        return Redpoint::EOS::API::Errors::VersionMismatch(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_LimitExceeded:
        return Redpoint::EOS::API::Errors::LimitExceeded(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_UserInfo_BestDisplayNameIndeterminate:
        return Redpoint::EOS::API::Errors::UserInfo_BestDisplayNameIndeterminate(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Disabled:
        return Redpoint::EOS::API::Errors::Disabled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_DuplicateNotAllowed:
        return Redpoint::EOS::API::Errors::DuplicateNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidSandboxId:
        return Redpoint::EOS::API::Errors::InvalidSandboxId(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TimedOut:
        return Redpoint::EOS::API::Errors::TimedOut(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PartialResult:
        return Redpoint::EOS::API::Errors::PartialResult(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Missing_Role:
        return Redpoint::EOS::API::Errors::Missing_Role(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidUser:
        return Redpoint::EOS::API::Errors::InvalidUser(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Missing_Feature:
        return Redpoint::EOS::API::Errors::Missing_Feature(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_Sandbox:
        return Redpoint::EOS::API::Errors::Invalid_Sandbox(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_Deployment:
        return Redpoint::EOS::API::Errors::Invalid_Deployment(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_Product:
        return Redpoint::EOS::API::Errors::Invalid_Product(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Invalid_ProductUserID:
        return Redpoint::EOS::API::Errors::Invalid_ProductUserID(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_ServiceFailure:
        return Redpoint::EOS::API::Errors::ServiceFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_CacheDirectoryMissing:
        return Redpoint::EOS::API::Errors::CacheDirectoryMissing(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_CacheDirectoryInvalid:
        return Redpoint::EOS::API::Errors::CacheDirectoryInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidState:
        return Redpoint::EOS::API::Errors::InvalidState(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RequestInProgress:
        return Redpoint::EOS::API::Errors::RequestInProgress(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_InvalidAuth:
        return Redpoint::EOS::API::Errors::InvalidAuth(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_ApplicationSuspended:
        return Redpoint::EOS::API::Errors::ApplicationSuspended(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_NetworkDisconnected:
        return Redpoint::EOS::API::Errors::NetworkDisconnected(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AccessDenied:
        return Redpoint::EOS::API::Errors::AccessDenied(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_MissingPermissions:
        return Redpoint::EOS::API::Errors::MissingPermissions(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Token_Not_Account:
        return Redpoint::EOS::API::Errors::Token_Not_Account(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TooManyRequests:
        return Redpoint::EOS::API::Errors::TooManyRequests(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AlreadyPending:
        return Redpoint::EOS::API::Errors::AlreadyPending(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountLocked:
        return Redpoint::EOS::API::Errors::Auth::AccountLocked(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountLockedForUpdate:
        return Redpoint::EOS::API::Errors::Auth::AccountLockedForUpdate(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_InvalidRefreshToken:
        return Redpoint::EOS::API::Errors::Auth::InvalidRefreshToken(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_InvalidToken:
        return Redpoint::EOS::API::Errors::Auth::InvalidToken(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AuthenticationFailure:
        return Redpoint::EOS::API::Errors::Auth::AuthenticationFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_InvalidPlatformToken:
        return Redpoint::EOS::API::Errors::Auth::InvalidPlatformToken(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_WrongAccount:
        return Redpoint::EOS::API::Errors::Auth::WrongAccount(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_WrongClient:
        return Redpoint::EOS::API::Errors::Auth::WrongClient(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_FullAccountRequired:
        return Redpoint::EOS::API::Errors::Auth::FullAccountRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_HeadlessAccountRequired:
        return Redpoint::EOS::API::Errors::Auth::HeadlessAccountRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PasswordResetRequired:
        return Redpoint::EOS::API::Errors::Auth::PasswordResetRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PasswordCannotBeReused:
        return Redpoint::EOS::API::Errors::Auth::PasswordCannotBeReused(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_Expired:
        return Redpoint::EOS::API::Errors::Auth::Expired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ScopeConsentRequired:
        return Redpoint::EOS::API::Errors::Auth::ScopeConsentRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ApplicationNotFound:
        return Redpoint::EOS::API::Errors::Auth::ApplicationNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ScopeNotFound:
        return Redpoint::EOS::API::Errors::Auth::ScopeNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountFeatureRestricted:
        return Redpoint::EOS::API::Errors::Auth::AccountFeatureRestricted(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountPortalLoadError:
        return Redpoint::EOS::API::Errors::Auth::AccountPortalLoadError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_CorrectiveActionRequired:
        return Redpoint::EOS::API::Errors::Auth::CorrectiveActionRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PinGrantCode:
        return Redpoint::EOS::API::Errors::Auth::PinGrantCode(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PinGrantExpired:
        return Redpoint::EOS::API::Errors::Auth::PinGrantExpired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_PinGrantPending:
        return Redpoint::EOS::API::Errors::Auth::PinGrantPending(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthNotLinked:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthNotLinked(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthRevoked:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthRevoked(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthInvalid:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthRestricted:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthRestricted(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthCannotLogin:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthCannotLogin(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthExpired:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthExpired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExternalAuthIsLastLoginType:
        return Redpoint::EOS::API::Errors::Auth::ExternalAuthIsLastLoginType(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ExchangeCodeNotFound:
        return Redpoint::EOS::API::Errors::Auth::ExchangeCodeNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_OriginatingExchangeCodeSessionExpired:
        return Redpoint::EOS::API::Errors::Auth::OriginatingExchangeCodeSessionExpired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_AccountNotActive:
        return Redpoint::EOS::API::Errors::Auth::AccountNotActive(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_MFARequired:
        return Redpoint::EOS::API::Errors::Auth::MFARequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_ParentalControls:
        return Redpoint::EOS::API::Errors::Auth::ParentalControls(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Auth_NoRealId:
        return Redpoint::EOS::API::Errors::Auth::NoRealId(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_Auth_UserInterfaceRequired:
        return Redpoint::EOS::API::Errors::Auth::UserInterfaceRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_InviteAwaitingAcceptance:
        return Redpoint::EOS::API::Errors::Friends::InviteAwaitingAcceptance(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_NoInvitation:
        return Redpoint::EOS::API::Errors::Friends::NoInvitation(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_AlreadyFriends:
        return Redpoint::EOS::API::Errors::Friends::AlreadyFriends(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_NotFriends:
        return Redpoint::EOS::API::Errors::Friends::NotFriends(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_TargetUserTooManyInvites:
        return Redpoint::EOS::API::Errors::Friends::TargetUserTooManyInvites(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_LocalUserTooManyInvites:
        return Redpoint::EOS::API::Errors::Friends::LocalUserTooManyInvites(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_TargetUserFriendLimitExceeded:
        return Redpoint::EOS::API::Errors::Friends::TargetUserFriendLimitExceeded(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Friends_LocalUserFriendLimitExceeded:
        return Redpoint::EOS::API::Errors::Friends::LocalUserFriendLimitExceeded(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataKeyInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataKeyInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataKeyLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataKeyLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataValueInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataValueInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_DataValueLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::DataValueLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_RichTextInvalid:
        return Redpoint::EOS::API::Errors::Presence::RichTextInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_RichTextLengthInvalid:
        return Redpoint::EOS::API::Errors::Presence::RichTextLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Presence_StatusInvalid:
        return Redpoint::EOS::API::Errors::Presence::StatusInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_EntitlementStale:
        return Redpoint::EOS::API::Errors::Ecom::EntitlementStale(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CatalogOfferStale:
        return Redpoint::EOS::API::Errors::Ecom::CatalogOfferStale(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CatalogItemStale:
        return Redpoint::EOS::API::Errors::Ecom::CatalogItemStale(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CatalogOfferPriceInvalid:
        return Redpoint::EOS::API::Errors::Ecom::CatalogOfferPriceInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Ecom_CheckoutLoadError:
        return Redpoint::EOS::API::Errors::Ecom::CheckoutLoadError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_Ecom_PurchaseProcessing:
        return Redpoint::EOS::API::Errors::Ecom::PurchaseProcessing(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SessionInProgress:
        return Redpoint::EOS::API::Errors::Sessions::SessionInProgress(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_TooManyPlayers:
        return Redpoint::EOS::API::Errors::Sessions::TooManyPlayers(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_NoPermission:
        return Redpoint::EOS::API::Errors::Sessions::NoPermission(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SessionAlreadyExists:
        return Redpoint::EOS::API::Errors::Sessions::SessionAlreadyExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InvalidLock:
        return Redpoint::EOS::API::Errors::Sessions::InvalidLock(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InvalidSession:
        return Redpoint::EOS::API::Errors::Sessions::InvalidSession(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SandboxNotAllowed:
        return Redpoint::EOS::API::Errors::Sessions::SandboxNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InviteFailed:
        return Redpoint::EOS::API::Errors::Sessions::InviteFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_InviteNotFound:
        return Redpoint::EOS::API::Errors::Sessions::InviteNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_UpsertNotAllowed:
        return Redpoint::EOS::API::Errors::Sessions::UpsertNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_AggregationFailed:
        return Redpoint::EOS::API::Errors::Sessions::AggregationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_HostAtCapacity:
        return Redpoint::EOS::API::Errors::Sessions::HostAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SandboxAtCapacity:
        return Redpoint::EOS::API::Errors::Sessions::SandboxAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_SessionNotAnonymous:
        return Redpoint::EOS::API::Errors::Sessions::SessionNotAnonymous(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_OutOfSync:
        return Redpoint::EOS::API::Errors::Sessions::OutOfSync(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_TooManyInvites:
        return Redpoint::EOS::API::Errors::Sessions::TooManyInvites(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_PresenceSessionExists:
        return Redpoint::EOS::API::Errors::Sessions::PresenceSessionExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_DeploymentAtCapacity:
        return Redpoint::EOS::API::Errors::Sessions::DeploymentAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_NotAllowed:
        return Redpoint::EOS::API::Errors::Sessions::NotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Sessions_PlayerSanctioned:
        return Redpoint::EOS::API::Errors::Sessions::PlayerSanctioned(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FilenameInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FilenameLengthInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FilenameInvalidChars:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FilenameInvalidChars(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileSizeTooLarge:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeTooLarge(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileSizeInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileSizeInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileHandleInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileHandleInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_DataInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::DataInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_DataLengthInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::DataLengthInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_StartIndexInvalid:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::StartIndexInvalid(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_RequestInProgress:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::RequestInProgress(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_UserThrottled:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::UserThrottled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_EncryptionKeyNotSet:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::EncryptionKeyNotSet(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_UserErrorFromDataCallback:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::UserErrorFromDataCallback(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileHeaderHasNewerVersion:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileHeaderHasNewerVersion(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_PlayerDataStorage_FileCorrupted:
        return Redpoint::EOS::API::Errors::PlayerDataStorage::FileCorrupted(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_ExternalTokenValidationFailed:
        return Redpoint::EOS::API::Errors::Connect::ExternalTokenValidationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_UserAlreadyExists:
        return Redpoint::EOS::API::Errors::Connect::UserAlreadyExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_AuthExpired:
        return Redpoint::EOS::API::Errors::Connect::AuthExpired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_InvalidToken:
        return Redpoint::EOS::API::Errors::Connect::InvalidToken(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_UnsupportedTokenType:
        return Redpoint::EOS::API::Errors::Connect::UnsupportedTokenType(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_LinkAccountFailed:
        return Redpoint::EOS::API::Errors::Connect::LinkAccountFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_ExternalServiceUnavailable:
        return Redpoint::EOS::API::Errors::Connect::ExternalServiceUnavailable(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Connect_ExternalServiceConfigurationFailure:
        return Redpoint::EOS::API::Errors::Connect::ExternalServiceConfigurationFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_UI_SocialOverlayLoadError:
        return Redpoint::EOS::API::Errors::UI::SocialOverlayLoadError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_NotOwner:
        return Redpoint::EOS::API::Errors::Lobby::NotOwner(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InvalidLock:
        return Redpoint::EOS::API::Errors::Lobby::InvalidLock(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_LobbyAlreadyExists:
        return Redpoint::EOS::API::Errors::Lobby::LobbyAlreadyExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_SessionInProgress:
        return Redpoint::EOS::API::Errors::Lobby::SessionInProgress(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_TooManyPlayers:
        return Redpoint::EOS::API::Errors::Lobby::TooManyPlayers(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_NoPermission:
        return Redpoint::EOS::API::Errors::Lobby::NoPermission(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InvalidSession:
        return Redpoint::EOS::API::Errors::Lobby::InvalidSession(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_SandboxNotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::SandboxNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InviteFailed:
        return Redpoint::EOS::API::Errors::Lobby::InviteFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_InviteNotFound:
        return Redpoint::EOS::API::Errors::Lobby::InviteNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_UpsertNotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::UpsertNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_AggregationFailed:
        return Redpoint::EOS::API::Errors::Lobby::AggregationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_HostAtCapacity:
        return Redpoint::EOS::API::Errors::Lobby::HostAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_SandboxAtCapacity:
        return Redpoint::EOS::API::Errors::Lobby::SandboxAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_TooManyInvites:
        return Redpoint::EOS::API::Errors::Lobby::TooManyInvites(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_DeploymentAtCapacity:
        return Redpoint::EOS::API::Errors::Lobby::DeploymentAtCapacity(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_NotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::NotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_MemberUpdateOnly:
        return Redpoint::EOS::API::Errors::Lobby::MemberUpdateOnly(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_PresenceLobbyExists:
        return Redpoint::EOS::API::Errors::Lobby::PresenceLobbyExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Lobby_VoiceNotEnabled:
        return Redpoint::EOS::API::Errors::Lobby::VoiceNotEnabled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    case EOS_EResult::EOS_Lobby_PlatformNotAllowed:
        return Redpoint::EOS::API::Errors::Lobby::PlatformNotAllowed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_UserErrorFromDataCallback:
        return Redpoint::EOS::API::Errors::TitleStorage::UserErrorFromDataCallback(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_EncryptionKeyNotSet:
        return Redpoint::EOS::API::Errors::TitleStorage::EncryptionKeyNotSet(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_FileCorrupted:
        return Redpoint::EOS::API::Errors::TitleStorage::FileCorrupted(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_TitleStorage_FileHeaderHasNewerVersion:
        return Redpoint::EOS::API::Errors::TitleStorage::FileHeaderHasNewerVersion(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModSdkProcessIsAlreadyRunning:
        return Redpoint::EOS::API::Errors::Mods::ModSdkProcessIsAlreadyRunning(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModSdkCommandIsEmpty:
        return Redpoint::EOS::API::Errors::Mods::ModSdkCommandIsEmpty(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModSdkProcessCreationFailed:
        return Redpoint::EOS::API::Errors::Mods::ModSdkProcessCreationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_CriticalError:
        return Redpoint::EOS::API::Errors::Mods::CriticalError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ToolInternalError:
        return Redpoint::EOS::API::Errors::Mods::ToolInternalError(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_IPCFailure:
        return Redpoint::EOS::API::Errors::Mods::IPCFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_InvalidIPCResponse:
        return Redpoint::EOS::API::Errors::Mods::InvalidIPCResponse(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_URILaunchFailure:
        return Redpoint::EOS::API::Errors::Mods::URILaunchFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_ModIsNotInstalled:
        return Redpoint::EOS::API::Errors::Mods::ModIsNotInstalled(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_UserDoesNotOwnTheGame:
        return Redpoint::EOS::API::Errors::Mods::UserDoesNotOwnTheGame(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_OfferRequestByIdInvalidResult:
        return Redpoint::EOS::API::Errors::Mods::OfferRequestByIdInvalidResult(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_CouldNotFindOffer:
        return Redpoint::EOS::API::Errors::Mods::CouldNotFindOffer(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_OfferRequestByIdFailure:
        return Redpoint::EOS::API::Errors::Mods::OfferRequestByIdFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_PurchaseFailure:
        return Redpoint::EOS::API::Errors::Mods::PurchaseFailure(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_InvalidGameInstallInfo:
        return Redpoint::EOS::API::Errors::Mods::InvalidGameInstallInfo(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_CannotGetManifestLocation:
        return Redpoint::EOS::API::Errors::Mods::CannotGetManifestLocation(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Mods_UnsupportedOS:
        return Redpoint::EOS::API::Errors::Mods::UnsupportedOS(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientProtectionNotAvailable:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientProtectionNotAvailable(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_InvalidMode:
        return Redpoint::EOS::API::Errors::AntiCheat::InvalidMode(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientProductIdMismatch:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientProductIdMismatch(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientSandboxIdMismatch:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientSandboxIdMismatch(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ProtectMessageSessionKeyRequired:
        return Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageSessionKeyRequired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ProtectMessageValidationFailed:
        return Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageValidationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ProtectMessageInitializationFailed:
        return Redpoint::EOS::API::Errors::AntiCheat::ProtectMessageInitializationFailed(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_PeerAlreadyRegistered:
        return Redpoint::EOS::API::Errors::AntiCheat::PeerAlreadyRegistered(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_PeerNotFound:
        return Redpoint::EOS::API::Errors::AntiCheat::PeerNotFound(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_PeerNotProtected:
        return Redpoint::EOS::API::Errors::AntiCheat::PeerNotProtected(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_ClientDeploymentIdMismatch:
        return Redpoint::EOS::API::Errors::AntiCheat::ClientDeploymentIdMismatch(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_AntiCheat_DeviceIdAuthIsNotSupported:
        return Redpoint::EOS::API::Errors::AntiCheat::DeviceIdAuthIsNotSupported(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_TooManyParticipants:
        return Redpoint::EOS::API::Errors::RTC::TooManyParticipants(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_RoomAlreadyExists:
        return Redpoint::EOS::API::Errors::RTC::RoomAlreadyExists(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_UserKicked:
        return Redpoint::EOS::API::Errors::RTC::UserKicked(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_UserBanned:
        return Redpoint::EOS::API::Errors::RTC::UserBanned(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_RoomWasLeft:
        return Redpoint::EOS::API::Errors::RTC::RoomWasLeft(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_ReconnectionTimegateExpired:
        return Redpoint::EOS::API::Errors::RTC::ReconnectionTimegateExpired(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_ShutdownInvoked:
        return Redpoint::EOS::API::Errors::RTC::ShutdownInvoked(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_RTC_UserIsInBlocklist:
        return Redpoint::EOS::API::Errors::RTC::UserIsInBlocklist(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_ProgressionSnapshot_SnapshotIdUnavailable:
        return Redpoint::EOS::API::Errors::ProgressionSnapshot::SnapshotIdUnavailable(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_KWS_ParentEmailMissing:
        return Redpoint::EOS::API::Errors::KWS::ParentEmailMissing(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_KWS_UserGraduated:
        return Redpoint::EOS::API::Errors::KWS::UserGraduated(InCall, InContextMsg);
#endif
#if EOS_VERSION_AT_LEAST(1, 15, 4)
    case EOS_EResult::EOS_Android_JavaVMNotStored:
        return Redpoint::EOS::API::Errors::Android::JavaVMNotStored(InCall, InContextMsg);
#endif

    default:
        return Redpoint::EOS::API::Errors::UnexpectedError(InCall, InContextMsg);
    }
}
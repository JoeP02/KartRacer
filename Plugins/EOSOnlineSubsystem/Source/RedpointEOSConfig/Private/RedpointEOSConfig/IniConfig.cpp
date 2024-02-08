// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSConfig/IniConfig.h"

#include "RedpointEOSConfig/Logging.h"
#include "RedpointEOSConfig/StatTyping.h"
#include "RedpointEOSAPI/SDK.h"
#include "Misc/ConfigCacheIni.h"

namespace Redpoint::EOS::Config
{

FString FIniConfig::GetDelegatedSubsystemsString() const
{
    return GetConfigValue(TEXT("DelegatedSubsystems"), TEXT(""));
}

FString FIniConfig::GetFreeEditionLicenseKey() const
{
    return GetConfigValue(TEXT("FreeEditionLicenseKey"), TEXT(""));
}

FString FIniConfig::GetEncryptionKey() const
{
    return GetConfigValue(
        TEXT("PlayerDataEncryptionKey"),
        TEXT("4dc4ad8a46823586f4044225d6cf1b1e7ee32b3d7dff1c63b6ad5807671c4a3f"));
}

FString FIniConfig::GetProductName() const
{
    return GetConfigValue(TEXT("ProductName"), TEXT("Product Name Not Set"));
}

FString FIniConfig::GetProductVersion() const
{
    return GetConfigValue(TEXT("ProductVersion"), TEXT("0.0.0"));
}

FString FIniConfig::GetProductId() const
{
    return GetConfigValue(TEXT("ProductId"), TEXT(""));
}

FString FIniConfig::GetSandboxId() const
{
    return GetConfigValue(TEXT("SandboxId"), TEXT(""));
}

FString FIniConfig::GetDeploymentId() const
{
    return GetConfigValue(TEXT("DeploymentId"), TEXT(""));
}

FString FIniConfig::GetClientId() const
{
    return GetConfigValue(TEXT("ClientId"), TEXT(""));
}

FString FIniConfig::GetClientSecret() const
{
    return GetConfigValue(TEXT("ClientSecret"), TEXT(""));
}

FString FIniConfig::GetDedicatedServerClientId() const
{
#if WITH_EDITOR
    FString Value = TEXT("");
    GConfig->GetString(TEXT("EpicOnlineServices"), TEXT("DedicatedServerClientId"), Value, GEditorIni);
    return Value;
#else
    return GetConfigValue(TEXT("DedicatedServerClientId"), TEXT(""));
#endif
}

FString FIniConfig::GetDedicatedServerClientSecret() const
{
#if WITH_EDITOR
    FString Value = TEXT("");
    GConfig->GetString(TEXT("EpicOnlineServices"), TEXT("DedicatedServerClientSecret"), Value, GEditorIni);
    return Value;
#else
    return GetConfigValue(TEXT("DedicatedServerClientSecret"), TEXT(""));
#endif
}

FString FIniConfig::GetDeveloperToolAddress() const
{
    return GetConfigValue(TEXT("DevAuthToolAddress"), TEXT("localhost:6300"));
}

FString FIniConfig::GetDeveloperToolDefaultCredentialName() const
{
    return GetConfigValue(TEXT("DevAuthToolDefaultCredentialName"), TEXT("Context_1"));
}

FString FIniConfig::GetWidgetClass(FString WidgetName, FString DefaultValue) const
{
    return GetConfigValue(FString::Printf(TEXT("WidgetClass_%s"), *WidgetName), DefaultValue);
}

EEOSApiVersion FIniConfig::GetApiVersion() const
{
    FString ApiVersionStr = GetConfigValue(TEXT("ApiVersion"), TEXT(""));

    if (ApiVersionStr.IsEmpty())
    {
        // Pick latest for backwards compatibility.
        return (EEOSApiVersion)0;
    }

    // It's not safe to use FindObject here, because the UObject system might not have initialized yet. Instead we used
    // the provided FOREACH_ENUM_EEOSAPIVERSION macro to enumerate through all the available options and string compare
    // them.
    static int32 LastSelectedApiVersion = -1;
#define EEOS_API_VERSION_EVALUATE(op)                                                                                  \
    {                                                                                                                  \
        FString CandidateStr = FString(TEXT(#op)).Mid(FString(TEXT("EEOSApiVersion::")).Len());                        \
        if (CandidateStr == ApiVersionStr)                                                                             \
        {                                                                                                              \
            if (LastSelectedApiVersion != (int32)(op))                                                                 \
            {                                                                                                          \
                UE_LOG(                                                                                                \
                    LogRedpointEOSConfig,                                                                           \
                    Verbose,                                                                                           \
                    TEXT("Using API version '%s' because that is what is selected in configuration."),                 \
                    *CandidateStr);                                                                                    \
                LastSelectedApiVersion = (int32)(op);                                                                  \
            }                                                                                                          \
            return op;                                                                                                 \
        }                                                                                                              \
    }
    FOREACH_ENUM_EEOSAPIVERSION(EEOS_API_VERSION_EVALUATE);

    UE_LOG(
        LogRedpointEOSConfig,
        Error,
        TEXT("The ApiVersion in your configuration '%s' is not a valid option. Defaulting to latest version."),
        *ApiVersionStr);
    return (EEOSApiVersion)0;
}

bool FIniConfig::IsAutomatedTesting() const
{
    return false;
}

FName FIniConfig::GetAuthenticationGraph() const
{
    return FName(*GetConfigValue(TEXT("AuthenticationGraph"), TEXT("Default")));
}

FName FIniConfig::GetEditorAuthenticationGraph() const
{
    return FName(*GetConfigValue(TEXT("EditorAuthenticationGraph"), TEXT("Default")));
}

FName FIniConfig::GetCrossPlatformAccountProvider() const
{
    return FName(*GetConfigValue(TEXT("CrossPlatformAccountProvider"), TEXT("None")));
}

bool FIniConfig::GetRequireCrossPlatformAccount() const
{
    return GetConfigValue(TEXT("RequireCrossPlatformAccount"), false);
}

EPresenceAdvertisementType FIniConfig::GetPresenceAdvertisementType() const
{
    auto PresenceType = GetConfigValue(TEXT("PresenceAdvertises"), TEXT("Party"));
    if (PresenceType == TEXT("Party"))
    {
        return EPresenceAdvertisementType::Party;
    }
    else if (PresenceType == TEXT("Session"))
    {
        return EPresenceAdvertisementType::Session;
    }
    else
    {
        return EPresenceAdvertisementType::None;
    }
}

bool FIniConfig::GetPersistentLoginEnabled() const
{
    return !GetConfigValue(TEXT("DisablePersistentLogin"), false);
}

bool FIniConfig::GetRequireEpicGamesLauncher() const
{
    return GetConfigValue(TEXT("RequireEpicGamesLauncher"), false);
}

FString FIniConfig::GetSimpleFirstPartyLoginUrl() const
{
    return GetConfigValue(TEXT("SimpleFirstPartyLoginUrl"), TEXT(""));
}

EPartyJoinabilityConstraint FIniConfig::GetPartyJoinabilityConstraint() const
{
    auto Constraint = GetConfigValue(TEXT("PartyJoinabilityConstraint"), TEXT(""));
    if (Constraint == TEXT("AllowPlayersInMultipleParties"))
    {
        return EPartyJoinabilityConstraint::AllowPlayersInMultipleParties;
    }
    else if (Constraint == TEXT("IgnoreInvitesIfAlreadyInParty"))
    {
        return EPartyJoinabilityConstraint::IgnoreInvitesIfAlreadyInParty;
    }

    // No option or invalid option set.
    return EPartyJoinabilityConstraint::AllowPlayersInMultipleParties;
}

bool FIniConfig::GetEnableAutomaticEncryptionOnTrustedDedicatedServers() const
{
    return GetConfigValue(TEXT("EnableAutomaticEncryptionOnTrustedDedicatedServers"), true);
}

EDedicatedServersDistributionMode FIniConfig::GetDedicatedServerDistributionMode() const
{
#if WITH_EDITOR
    FString Value = TEXT("DevelopersAndPlayers");
    GConfig->GetString(TEXT("EpicOnlineServices"), TEXT("DedicatedServerDistributionMode"), Value, GEditorIni);
    if (Value == TEXT("DevelopersOnly"))
    {
        return EDedicatedServersDistributionMode::DevelopersOnly;
    }
    else if (Value == TEXT("DevelopersAndPlayers"))
    {
        return EDedicatedServersDistributionMode::DevelopersAndPlayers;
    }
    else
    {
        return EDedicatedServersDistributionMode::PlayersOnly;
    }
#else
    checkf(
        false,
        TEXT("GetDedicatedServerDistributionMode should not be called outside editor code or a WITH_EDITOR block!"));
    return EDedicatedServersDistributionMode::PlayersOnly;
#endif
}

FString FIniConfig::GetDedicatedServerPublicKey() const
{
    return GetConfigValue(TEXT("DedicatedServerPublicKey"), TEXT(""));
}

FString FIniConfig::GetDedicatedServerPrivateKey() const
{
#if WITH_EDITOR
    FString Value = TEXT("");
    GConfig->GetString(TEXT("EpicOnlineServices"), TEXT("DedicatedServerPrivateKey"), Value, GEditorIni);
    return Value;
#else
    return GetConfigValue(TEXT("DedicatedServerPrivateKey"), TEXT(""));
#endif
}

bool FIniConfig::GetEnableAntiCheat() const
{
    switch (GetNetworkAuthenticationMode())
    {
    case ENetworkAuthenticationMode::Off:
        return false;
    case ENetworkAuthenticationMode::IDToken:
    default:
        return GetConfigValue(TEXT("EnableAntiCheat"), false);
    }
}

FString FIniConfig::GetTrustedClientPublicKey() const
{
    return GetConfigValue(TEXT("TrustedClientPublicKey"), TEXT(""));
}

FString FIniConfig::GetTrustedClientPrivateKey() const
{
    return GetConfigValue(TEXT("TrustedClientPrivateKey"), TEXT(""));
}

bool FIniConfig::GetEnableVoiceChatEchoInParties() const
{
    return GetConfigValue(TEXT("EnableVoiceChatEchoInParties"), false);
}

bool FIniConfig::GetEnableVoiceChatPlatformAECByDefault() const
{
    return GetConfigValue(TEXT("EnableVoiceChatPlatformAECByDefault"), false);
}

TArray<TTuple<FString, EStatTypingRule>> FIniConfig::GetStatTypingRules() const
{
    TArray<FString> Value;
    GConfig->GetArray(TEXT("EpicOnlineServices"), TEXT("StatTypingRules"), Value, GEngineIni);
    return ParseStatTypingRules(Value);
}

bool FIniConfig::GetAcceptStatWriteRequestsFromServers() const
{
    return GetConfigValue(TEXT("AcceptStatWriteRequestsFromServers"), false);
}

ENetworkAuthenticationMode FIniConfig::GetNetworkAuthenticationMode() const
{
    auto AuthMode = GetConfigValue(TEXT("NetworkAuthenticationMode"), TEXT("Default"));
    if (AuthMode == TEXT("IDToken") || AuthMode == TEXT("UserCredentials"))
    // NOLINTNEXTLINE(bugprone-branch-clone)
    {
        return ENetworkAuthenticationMode::IDToken;
    }
    else if (AuthMode == TEXT("Off"))
    {
        return ENetworkAuthenticationMode::Off;
    }
    else // including "Default"
    {
        // note: If we change the behaviour of Default in a future release,
        // it must be conditioned on the API version here.
        return ENetworkAuthenticationMode::IDToken;
    }
}

// Necessary for EOS_EAuthScopeFlags logic without taking
// a dependency on RedpointEOSAPI.
#define REDPOINT_EOS_CONFIG_VERSION_AT_LEAST(MAJOR, MINOR, PATCH)                                                                      \
    ((EOS_MAJOR_VERSION > (MAJOR)) || (EOS_MAJOR_VERSION == (MAJOR) && EOS_MINOR_VERSION > (MINOR)) ||                 \
     (EOS_MAJOR_VERSION == (MAJOR) && EOS_MINOR_VERSION == (MINOR) && EOS_PATCH_VERSION >= (PATCH)))

TArray<EOS_EAuthScopeFlags> FIniConfig::GetEpicGamesScopes() const
{
    TArray<FString> Scopes;
    GetConfigValue(TEXT("EpicGamesScopes"), TEXT("BasicProfile,FriendsList,Presence,Country"))
        .ParseIntoArray(Scopes, TEXT(","));
    TArray<EOS_EAuthScopeFlags> ScopeFlags;
    for (const auto &Scope : Scopes)
    {
        if (Scope == TEXT("BasicProfile"))
        {
            ScopeFlags.Add(EOS_EAuthScopeFlags::EOS_AS_BasicProfile);
        }
        else if (Scope == TEXT("FriendsList"))
        {
            ScopeFlags.Add(EOS_EAuthScopeFlags::EOS_AS_FriendsList);
        }
        else if (Scope == TEXT("Presence"))
        {
            ScopeFlags.Add(EOS_EAuthScopeFlags::EOS_AS_Presence);
        }
        else if (Scope == TEXT("FriendsManagement"))
        {
            ScopeFlags.Add(EOS_EAuthScopeFlags::EOS_AS_FriendsManagement);
        }
        else if (Scope == TEXT("Email"))
        {
            ScopeFlags.Add(EOS_EAuthScopeFlags::EOS_AS_Email);
        }
#if REDPOINT_EOS_CONFIG_VERSION_AT_LEAST(1, 15, 0)
        else if (Scope == TEXT("Country"))
        {
            ScopeFlags.Add(EOS_EAuthScopeFlags::EOS_AS_Country);
        }
#endif
    }
    if (ScopeFlags.Num() == 0)
    {
        // If no scopes set, default to supported scopes.
        ScopeFlags.Add(this->GetSupportedEpicGamesScopes());
    }
    return ScopeFlags;
}

EOS_EAuthScopeFlags FIniConfig::GetSupportedEpicGamesScopes() const
{
    // If changing this, also change GetConfigValue() above.
    return EOS_EAuthScopeFlags::EOS_AS_BasicProfile | EOS_EAuthScopeFlags::EOS_AS_FriendsList |
           EOS_EAuthScopeFlags::EOS_AS_Presence
#if REDPOINT_EOS_CONFIG_VERSION_AT_LEAST(1, 15, 0)
           | EOS_EAuthScopeFlags::EOS_AS_Country
#endif
        ;
}

#undef REDPOINT_EOS_CONFIG_VERSION_AT_LEAST

FString FIniConfig::GetCloudMessagingHubUrl() const
{
    return GetConfigValue(TEXT("CloudMessagingHubUrl"), TEXT(""));
}

FString FIniConfig::GetConfigValue(const FString &Key, const FString &DefaultValue) const
{
    return GetConfigValue(Key, *DefaultValue);
}

FString FIniConfig::GetConfigValue(const FString &Key, const TCHAR *DefaultValue) const
{
    FString Value = DefaultValue;
    GConfig->GetString(TEXT("EpicOnlineServices"), *Key, Value, GEngineIni);
    return Value;
}

bool FIniConfig::GetConfigValue(const FString &Key, bool DefaultValue) const
{
    bool Value = DefaultValue;
    GConfig->GetBool(TEXT("EpicOnlineServices"), *Key, Value, GEngineIni);
    return Value;
}

} // namespace Redpoint::EOS::Config
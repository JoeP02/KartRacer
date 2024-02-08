// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "RedpointEOSConfig/Config.h"

namespace Redpoint::EOS::Config
{

class REDPOINTEOSCONFIG_API FIniConfig : public IConfig
{
public:
    FIniConfig() = default;
    UE_NONCOPYABLE(FIniConfig);
    virtual ~FIniConfig() = default;

public:
    virtual FString GetDelegatedSubsystemsString() const override;
    virtual FString GetFreeEditionLicenseKey() const override;
    virtual FString GetEncryptionKey() const override;
    virtual FString GetProductName() const override;
    virtual FString GetProductVersion() const override;
    virtual FString GetProductId() const override;
    virtual FString GetSandboxId() const override;
    virtual FString GetDeploymentId() const override;
    virtual FString GetClientId() const override;
    virtual FString GetClientSecret() const override;
    virtual FString GetDedicatedServerClientId() const override;
    virtual FString GetDedicatedServerClientSecret() const override;
    virtual FString GetDeveloperToolAddress() const override;
    virtual FString GetDeveloperToolDefaultCredentialName() const override;
    virtual FString GetWidgetClass(FString WidgetName, FString DefaultValue) const override;
    virtual EEOSApiVersion GetApiVersion() const override;
    virtual FName GetAuthenticationGraph() const override;
    virtual FName GetEditorAuthenticationGraph() const override;
    virtual FName GetCrossPlatformAccountProvider() const override;
    virtual bool GetRequireCrossPlatformAccount() const override;
    virtual EPresenceAdvertisementType GetPresenceAdvertisementType() const override;
    virtual bool GetPersistentLoginEnabled() const override;
    virtual bool IsAutomatedTesting() const override;
    virtual bool GetRequireEpicGamesLauncher() const override;
    virtual FString GetSimpleFirstPartyLoginUrl() const override;
    virtual EPartyJoinabilityConstraint GetPartyJoinabilityConstraint() const override;
    virtual bool GetEnableAutomaticEncryptionOnTrustedDedicatedServers() const override;
    virtual EDedicatedServersDistributionMode GetDedicatedServerDistributionMode() const override;
    virtual FString GetDedicatedServerPublicKey() const override;
    virtual FString GetDedicatedServerPrivateKey() const override;
    virtual bool GetEnableAntiCheat() const override;
    virtual FString GetTrustedClientPublicKey() const override;
    virtual FString GetTrustedClientPrivateKey() const override;
    virtual bool GetEnableVoiceChatEchoInParties() const override;
    virtual bool GetEnableVoiceChatPlatformAECByDefault() const override;
    virtual TArray<TTuple<FString, EStatTypingRule>> GetStatTypingRules() const override;
    virtual bool GetAcceptStatWriteRequestsFromServers() const override;
    virtual ENetworkAuthenticationMode GetNetworkAuthenticationMode() const override;
    virtual TArray<EOS_EAuthScopeFlags> GetEpicGamesScopes() const override;
    virtual EOS_EAuthScopeFlags GetSupportedEpicGamesScopes() const override;
    virtual FString GetCloudMessagingHubUrl() const override;

private:
    FString GetConfigValue(const FString &Key, const FString &DefaultValue) const;
    FString GetConfigValue(const FString &Key, const TCHAR *DefaultValue) const;
    bool GetConfigValue(const FString &Key, bool DefaultValue) const;
};

} // namespace Redpoint::EOS::Config
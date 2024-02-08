// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSConfig/Types/DedicatedServersDistributionMode.h"
#include "RedpointEOSConfig/Types/EOSApiVersion.h"
#include "RedpointEOSConfig/Types/NetworkAuthenticationMode.h"
#include "RedpointEOSConfig/Types/PartyJoinabilityConstraint.h"
#include "RedpointEOSConfig/Types/PresenceAdvertisementType.h"
#include "RedpointEOSConfig/Types/StatTypingRule.h"

namespace Redpoint::EOS::Config
{

bool REDPOINTEOSCONFIG_API ApiVersionIsAtLeast(EEOSApiVersion InConfigVersion, EEOSApiVersion InTargetVersion);
bool REDPOINTEOSCONFIG_API ApiVersionIsAtLeast(const class IConfig &InConfig, EEOSApiVersion InTargetVersion);

class REDPOINTEOSCONFIG_API IConfig : public TSharedFromThis<IConfig>
{
public:
    IConfig() = default;
    virtual ~IConfig() = default;
    UE_NONCOPYABLE(IConfig);

public:
    virtual FString GetDelegatedSubsystemsString() const = 0;
    virtual FString GetFreeEditionLicenseKey() const = 0;
    virtual FString GetEncryptionKey() const = 0;
    virtual FString GetProductName() const = 0;
    virtual FString GetProductVersion() const = 0;
    virtual FString GetProductId() const = 0;
    virtual FString GetSandboxId() const = 0;
    virtual FString GetDeploymentId() const = 0;
    virtual FString GetClientId() const = 0;
    virtual FString GetClientSecret() const = 0;
    virtual FString GetDedicatedServerClientId() const = 0;
    virtual FString GetDedicatedServerClientSecret() const = 0;
    virtual FString GetDeveloperToolAddress() const = 0;
    virtual FString GetDeveloperToolDefaultCredentialName() const = 0;
    virtual FString GetWidgetClass(FString WidgetName, FString DefaultValue) const = 0;
    virtual EEOSApiVersion GetApiVersion() const = 0;
    virtual FName GetAuthenticationGraph() const = 0;
    virtual FName GetEditorAuthenticationGraph() const = 0;
    virtual FName GetCrossPlatformAccountProvider() const = 0;
    virtual bool GetRequireCrossPlatformAccount() const = 0;
    virtual EPresenceAdvertisementType GetPresenceAdvertisementType() const = 0;
    virtual bool GetPersistentLoginEnabled() const = 0;
    virtual bool IsAutomatedTesting() const = 0;
    virtual bool GetRequireEpicGamesLauncher() const = 0;
    virtual FString GetSimpleFirstPartyLoginUrl() const = 0;
    virtual EPartyJoinabilityConstraint GetPartyJoinabilityConstraint() const = 0;
    virtual bool GetEnableAutomaticEncryptionOnTrustedDedicatedServers() const = 0;
    virtual EDedicatedServersDistributionMode GetDedicatedServerDistributionMode() const = 0;
    virtual FString GetDedicatedServerPublicKey() const = 0;
    virtual FString GetDedicatedServerPrivateKey() const = 0;
    virtual bool GetEnableAntiCheat() const = 0;
    virtual FString GetTrustedClientPublicKey() const = 0;
    virtual FString GetTrustedClientPrivateKey() const = 0;
    virtual bool GetEnableVoiceChatEchoInParties() const = 0;
    virtual bool GetEnableVoiceChatPlatformAECByDefault() const = 0;
    virtual TArray<TTuple<FString, EStatTypingRule>> GetStatTypingRules() const = 0;
    virtual bool GetAcceptStatWriteRequestsFromServers() const = 0;
    virtual ENetworkAuthenticationMode GetNetworkAuthenticationMode() const = 0;
    virtual TArray<EOS_EAuthScopeFlags> GetEpicGamesScopes() const = 0;
    virtual EOS_EAuthScopeFlags GetSupportedEpicGamesScopes() const = 0;
    virtual FString GetCloudMessagingHubUrl() const = 0;

    bool HasSynthetics() const;
};

} // namespace Redpoint::EOS::Config
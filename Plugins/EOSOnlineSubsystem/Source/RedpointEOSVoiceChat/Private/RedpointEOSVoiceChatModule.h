// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "Modules/ModuleManager.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

class FRedpointEOSVoiceChatModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TUniquePtr<class FRedpointEOSVoiceChat> VoiceChat;
};
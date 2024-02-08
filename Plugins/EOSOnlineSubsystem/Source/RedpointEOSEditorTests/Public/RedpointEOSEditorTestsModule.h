// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSEditorTestsModule, All, All);

class FRedpointEOSEditorTestsModule : public FDefaultModuleImpl
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
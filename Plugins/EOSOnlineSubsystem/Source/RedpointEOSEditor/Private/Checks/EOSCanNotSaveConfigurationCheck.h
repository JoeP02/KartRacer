// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "IEOSCheck.h"

class FEOSCanNotSaveConfigurationCheck : public IEOSCheck
{
public:
    FEOSCanNotSaveConfigurationCheck() = default;
    UE_NONCOPYABLE(FEOSCanNotSaveConfigurationCheck);
    virtual ~FEOSCanNotSaveConfigurationCheck(){};

    virtual const TArray<FEOSCheckEntry> ProcessCustomSignal(const FString &Context, const FString &SignalId)
        const override;

    virtual void HandleAction(const FString &CheckId, const FString &ActionId) const override;
};
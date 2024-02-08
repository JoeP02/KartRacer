// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "IEOSCheck.h"

class FEOSBackendUnreachableCheck : public IEOSCheck
{
public:
    FEOSBackendUnreachableCheck() = default;
    UE_NONCOPYABLE(FEOSBackendUnreachableCheck);
    virtual ~FEOSBackendUnreachableCheck(){};

    virtual const TArray<FEOSCheckEntry> ProcessLogMessage(
        EOS_ELogLevel InLogLevel,
        const FString &Category,
        const FString &Message) const override;

    virtual void HandleAction(const FString &CheckId, const FString &ActionId) const override;
};
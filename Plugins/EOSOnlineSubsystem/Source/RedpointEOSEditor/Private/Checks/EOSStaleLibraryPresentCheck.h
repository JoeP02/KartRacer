// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "IEOSCheck.h"

class FEOSStaleLibraryPresentCheck : public IEOSCheck
{
public:
    FEOSStaleLibraryPresentCheck() = default;
    UE_NONCOPYABLE(FEOSStaleLibraryPresentCheck);
    virtual ~FEOSStaleLibraryPresentCheck(){};

    virtual const TArray<FEOSCheckEntry> ProcessLogMessage(
        EOS_ELogLevel InLogLevel,
        const FString &Category,
        const FString &Message) const override;

    virtual void HandleAction(const FString &CheckId, const FString &ActionId) const override;
};
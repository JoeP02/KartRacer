// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemRedpointEOS/Private/NetworkingAuth/AuthVerificationPhase.h"
#include "OnlineSubsystemRedpointEOS/Private/NetworkingAuth/AuthVerificationPhaseContext.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

#define AUTH_PHASE_SANCTION_CHECK FName(TEXT("SanctionCheck"))

class FSanctionCheckPhase : public IAuthVerificationPhase, public TSharedFromThis<FSanctionCheckPhase>
{
public:
    FSanctionCheckPhase(){};
    UE_NONCOPYABLE(FSanctionCheckPhase);
    virtual ~FSanctionCheckPhase(){};

    virtual FName GetName() const override
    {
        return AUTH_PHASE_SANCTION_CHECK;
    }

    static void RegisterRoutes(class UEOSControlChannel *ControlChannel);
    virtual void Start(const TSharedRef<FAuthVerificationPhaseContext> &Context) override;
};
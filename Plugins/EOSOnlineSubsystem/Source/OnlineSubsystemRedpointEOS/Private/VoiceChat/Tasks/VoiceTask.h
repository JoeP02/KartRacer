// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"

#if EOS_HAS_AUTHENTICATION

DECLARE_DELEGATE(FVoiceTaskComplete);

class FVoiceTask
{
public:
    virtual FString GetLogName() = 0;
    virtual void Run(FVoiceTaskComplete OnComplete) = 0;
};

#endif // #if EOS_HAS_AUTHENTICATION
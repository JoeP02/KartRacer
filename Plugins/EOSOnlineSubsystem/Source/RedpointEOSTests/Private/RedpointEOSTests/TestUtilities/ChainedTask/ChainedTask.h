// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedpointEOSTests/TestUtilities/ChainedTaskContext.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

namespace ChainedTask
{

class FChainedTask
{
public:
    FChainedTask() = default;
    UE_NONCOPYABLE(FChainedTask);
    virtual ~FChainedTask() = default;

	typedef TDelegate<void(bool bContinueTesting)> FOnComplete;

    virtual int GetHighestInstanceIndex() const = 0;

    virtual void ExecuteAsync(const FChainedTaskContextRef &, const FOnComplete &OnDone) = 0;
};

} // namespace ChainedTask

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
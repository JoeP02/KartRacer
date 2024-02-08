// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <type_traits>
#include <functional>
#include "RedpointEOSTests/TestUtilities/ChainedTask/ChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTaskRegisteredEvent.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

class FChainedTaskExecutor : public TSharedFromThis<FChainedTaskExecutor>
{
    friend class FChainedTaskContext;

private:
    class FAsyncHotReloadableAutomationTestBase *Test;
    std::function<void()> OnDone;
    TArray<TSharedRef<ChainedTask::FChainedTask>> Steps;
    bool bExecuting;

	void OnStepComplete(
        bool bInContinueTesting,
        TSharedRef<FChainedTaskContext> InContext,
		TSharedRef<FChainedTaskExecutor> InSelf);

public:
    FChainedTaskExecutor(class FAsyncHotReloadableAutomationTestBase *InTest, std::function<void()> InOnDone);
    UE_NONCOPYABLE(FChainedTaskExecutor);
    ~FChainedTaskExecutor() = default;

	template<typename InObjectType, typename... InArgTypes> TSharedRef<FChainedTaskExecutor> Then(InArgTypes&&... Args)
	{
        static_assert(
            std::is_base_of_v<ChainedTask::FChainedTask, InObjectType>,
            "InObjectType must be an FChainedTask!");
        TSharedRef<InObjectType> Next = MakeShared<InObjectType>(Forward<InArgTypes>(Args)...);
        Steps.Add(Next);
        return this->AsShared();
	}

	void Execute();
};

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
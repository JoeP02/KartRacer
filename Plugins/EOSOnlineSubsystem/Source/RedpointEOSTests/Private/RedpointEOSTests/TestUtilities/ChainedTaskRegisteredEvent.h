// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Delegates/Delegate.h"
#include "RedpointEOSTests/TestUtilities/ChainedTask/ChainedTask.h"
#include "RedpointEOSTests/TestUtilities/ChainedTaskContext.h"

namespace Redpoint::EOS::Tests
{

namespace TestUtilities
{

class FChainedTaskRegisteredEventBase
{
public:
    typedef TDelegate<void(const FChainedTaskContextRef &, FDelegateHandle)> FOnUnregister;

protected:
    FDelegateHandle BoundHandle;
    FOnUnregister UnregisterDelegate;

public:
    void Unregister(const FChainedTaskContextRef &Context)
    {
        this->UnregisterDelegate.Execute(Context, this->BoundHandle);
    }
};

template <typename... ParamTypes> class FChainedTaskRegisteredEvent : public FChainedTaskRegisteredEventBase
{
public:
    typedef TDelegate<bool(const FChainedTaskContextRef &, ParamTypes...)> FOnFilter;

private:
    TArray<TSharedRef<TTuple<ParamTypes...>>> CachedEvents;
    TDelegate<void(ParamTypes...)> SelfDelegate;
    TDelegate<void(ParamTypes...)> DispatchWhenBound;
    FTSTicker::FDelegateHandle TimerHandle;

    void OnEventReceived(ParamTypes... Args)
    {
        if (this->DispatchWhenBound.IsBound())
        {
            this->DispatchWhenBound.Execute(Args...);
        }
        else
        {
            this->CachedEvents.Add(MakeShared<TTuple<ParamTypes...>>(Args...));
        }
    }

    bool OnEventTimedOut(
        float DeltaSeconds,
        // NOLINTNEXTLINE(performance-unnecessary-value-param)
        FChainedTaskContextRef Context,
        // NOLINTNEXTLINE(performance-unnecessary-value-param)
        FString EventName,
        float TimeoutSeconds,
        // NOLINTNEXTLINE(performance-unnecessary-value-param)
        ChainedTask::FChainedTask::FOnComplete OnDone)
    {
        FTSTicker::GetCoreTicker().RemoveTicker(this->TimerHandle);
        this->DispatchWhenBound.Unbind();
        Context->Assert().TestTrue(
            FString::Printf(TEXT("Timed out while waiting %f seconds for event '%s'"), TimeoutSeconds, *EventName),
            false);
        OnDone.Execute(false);
        return false;
    }

    void OnEventReceivedBound(
        ParamTypes... Args,
        // NOLINTNEXTLINE(performance-unnecessary-value-param)
        FChainedTaskContextRef Context,
        // NOLINTNEXTLINE(performance-unnecessary-value-param)
        FString EventName,
        FOnFilter Filter,
        // NOLINTNEXTLINE(performance-unnecessary-value-param)
        ChainedTask::FChainedTask::FOnComplete OnDone)
    {
        if (Filter.Execute(Context, Args...))
        {
            Context->Assert().AddInfo(
                FString::Printf(TEXT("Received event '%s', which matches the filter."), *EventName));
            FTSTicker::GetCoreTicker().RemoveTicker(this->TimerHandle);
            this->DispatchWhenBound.Unbind();
            OnDone.Execute(true);
        }
        else
        {
            Context->Assert().AddInfo(FString::Printf(
                TEXT("Received event '%s', which was ignored because it did not match the filter."),
                *EventName));
        }
    }

    static bool ExecuteFilter(FChainedTaskContextRef Context, FOnFilter Filter, ParamTypes... Args)
    {
        return Filter.Execute(Context, Args...);
    }

public:
    FChainedTaskRegisteredEvent(const FOnUnregister &InUnregisterDelegate)
        : CachedEvents()
        , SelfDelegate()
        , DispatchWhenBound()
        , TimerHandle()
    {
        this->SelfDelegate.BindRaw(this, &FChainedTaskRegisteredEvent::OnEventReceived);
        this->UnregisterDelegate = InUnregisterDelegate;
    }

    TDelegate<void(ParamTypes...)> &GetDelegateForRegistration()
    {
        return this->SelfDelegate;
    }

    void WaitAndProcessEvents(
        const FChainedTaskContextRef &Context,
        FString EventName,
        FOnFilter InFilter,
        float TimeoutSeconds,
        const ChainedTask::FChainedTask::FOnComplete &OnDone)
    {
        bool bDidHandle = false;
        for (const TSharedRef<TTuple<ParamTypes...>> &CachedEvent : this->CachedEvents)
        {
            if (CachedEvent->ApplyAfter(
                    &FChainedTaskRegisteredEvent::ExecuteFilter,
                    (FChainedTaskContextRef)Context,
                    (FOnFilter)InFilter))
            {
                bDidHandle = true;
                break;
            }
        }
        if (bDidHandle)
        {
            this->CachedEvents.Empty();
            OnDone.Execute(true);
            return;
        }

        this->TimerHandle = FTSTicker::GetCoreTicker().AddTicker(
            FTickerDelegate::CreateRaw(
                this,
                &FChainedTaskRegisteredEvent::OnEventTimedOut,
                Context,
                EventName,
                TimeoutSeconds,
                OnDone),
            TimeoutSeconds);

        this->DispatchWhenBound
            .BindRaw(this, &FChainedTaskRegisteredEvent::OnEventReceivedBound, Context, EventName, InFilter, OnDone);
    }
};

template <typename K> struct FChainedTaskRegisteredEventHelper
{
};

template <typename InRetValType, typename... ParamTypes>
struct FChainedTaskRegisteredEventHelper<TDelegate<InRetValType(ParamTypes...)>>
{
    typedef FChainedTaskRegisteredEvent<ParamTypes...> RegisteredEventType;
};

} // namespace TestUtilities

} // namespace Redpoint::EOS::Tests
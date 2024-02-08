// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include <functional>
#include "Async/TaskGraphInterfaces.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSStats.h"

/**
 * This should be used when callbacks where the callback lambda can not be transported
 * across the native boundary (such as Java callbacks on Android).
 *
 * It is expected that this type will be instantiated as a global variable.
 */
template <typename TRequest, typename TResponse> class FIdentifiableCallbackDispatcher
{
private:
    int32 NextDispatchId = 1000;
    TMap<int32, std::function<void(const TResponse &InResponse)>> ResponseCallbacks;

public:
    void Dispatch(
        const TRequest &InRequest,
        std::function<bool(int32 InDispatchId, const TRequest &InRequest)> InDispatch,
        std::function<void(const TResponse &InResponse)> InCompleteCallback)
    {
        int32 DispatchId = NextDispatchId++;
        ResponseCallbacks.Add(DispatchId, InCompleteCallback);
        if (!InDispatch(DispatchId, InRequest))
        {
            ResponseCallbacks.Remove(DispatchId);
        }
    }

    void ReceiveResponse(int32 InDispatchId, const TResponse &InResponse)
    {
        FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
            FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
                checkf(
                    ResponseCallbacks.Contains(InDispatchId),
                    TEXT("Expected dispatch callback to exist (make sure this isn't a double call either)!"));
                ResponseCallbacks[InDispatchId](InResponse);
                ResponseCallbacks.Remove(InDispatchId);
            }),
            GET_STATID(STAT_EOSIdentifiableCallbackDispatcher),
            nullptr,
            ENamedThreads::GameThread);
    }
};
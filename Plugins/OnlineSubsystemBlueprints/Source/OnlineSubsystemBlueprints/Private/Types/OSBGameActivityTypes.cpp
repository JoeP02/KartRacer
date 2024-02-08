// Copyright June Rhodes 2023. All Rights Reserved.

#include "Types/OSBGameActivityTypes.h"

#if defined(REDPOINT_OSB_UE_4_25_OR_LATER)

#include "Interfaces/OnlineEventsInterface.h"

FOnlineActivityTasksToResetBP FOnlineActivityTasksToResetBP::FromNative(
    const TOptional<FOnlineActivityTasksToReset> &InObj)
{
    if (!InObj.IsSet())
    {
        return FOnlineActivityTasksToResetBP();
    }

    FOnlineActivityTasksToResetBP Value;
    Value.bSet = true;
    Value.InProgressTasks = InObj->InProgressTasks;
    Value.CompletedTasks = InObj->CompletedTasks;
    return Value;
}

TOptional<FOnlineActivityTasksToReset> FOnlineActivityTasksToResetBP::ToNative() const
{
    if (!this->bSet)
    {
        return TOptional<FOnlineActivityTasksToReset>();
    }

    FOnlineActivityTasksToReset Value;
    Value.InProgressTasks = this->InProgressTasks;
    Value.CompletedTasks = this->CompletedTasks;
    return Value;
}

FOnlineActivityPlayerLocationBP FOnlineActivityPlayerLocationBP::FromNative(
    const TOptional<FOnlineActivityPlayerLocation> &InObj)
{
    if (!InObj.IsSet())
    {
        return FOnlineActivityPlayerLocationBP();
    }

    FOnlineActivityPlayerLocationBP Value;
    Value.bSet = true;
    Value.ZoneId = InObj->ZoneId;
    Value.Coordinates = InObj->Coordinates;
    return Value;
}

TOptional<FOnlineActivityPlayerLocation> FOnlineActivityPlayerLocationBP::ToNative() const
{
    if (!this->bSet)
    {
        return TOptional<FOnlineActivityPlayerLocation>();
    }

    FOnlineActivityPlayerLocation Value;
    Value.ZoneId = this->ZoneId;
    Value.Coordinates = this->Coordinates;
    return Value;
}

FOptionalOnlineSessionSearchResultBP FOptionalOnlineSessionSearchResultBP::FromNative(
    const FOnlineSessionSearchResult *InObj)
{
    if (InObj == nullptr)
    {
        return FOptionalOnlineSessionSearchResultBP();
    }

    FOptionalOnlineSessionSearchResultBP Value;
    Value.bSet = true;
    Value.SearchResult = FOnlineSessionSearchResultBP::FromNative(*InObj);
    return Value;
}

FOnlineEventParms ConvertMapToEventParams(const TMap<FString, FVariantDataBP> &EventParams)
{
    FOnlineEventParms Results;
    for (const auto &KV : EventParams)
    {
        Results.Add(KV.Key, KV.Value.ToNative());
    }
    return Results;
}

TMap<FString, FVariantDataBP> ConvertEventParamsToMap(const FOnlineEventParms &EventParams)
{
    TMap<FString, FVariantDataBP> Results;
    for (const auto &KV : EventParams)
    {
        Results.Add(KV.Key, FVariantDataBP::FromNative(KV.Value));
    }
    return Results;
}

#endif
// Copyright June Rhodes 2023. All Rights Reserved.

#include "Types/OSBBlockedQueryResultInfo.h"

FBlockedQueryResultInfo FBlockedQueryResultInfo::FromNative(const FBlockedQueryResult &InObj)
{
    FBlockedQueryResultInfo Result;
    Result.Blocked = InObj.bIsBlocked;
    Result.BlockedNonFriends = InObj.bIsBlockedNonFriends;
    Result.UserId = InObj.UserId;
    return Result;
}

FBlockedQueryResult FBlockedQueryResultInfo::ToNative()
{
    FBlockedQueryResult Result;
    Result.bIsBlocked = this->Blocked;
    Result.bIsBlockedNonFriends = this->BlockedNonFriends;
    Result.UserId = this->UserId;
    return Result;
}
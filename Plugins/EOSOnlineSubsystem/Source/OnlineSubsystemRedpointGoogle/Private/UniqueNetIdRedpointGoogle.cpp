// Copyright June Rhodes 2024. All Rights Reserved.

#include "UniqueNetIdRedpointGoogle.h"

#include "OnlineSubsystemRedpointGoogleConstants.h"

#if EOS_GOOGLE_ENABLED

FUniqueNetIdRedpointGoogle::FUniqueNetIdRedpointGoogle()
    : UserId(TEXT(""))
{
}

FUniqueNetIdRedpointGoogle::FUniqueNetIdRedpointGoogle(const FString& Id)
    : UserId(Id)
{
}

FString FUniqueNetIdRedpointGoogle::GetUserId() const
{
    return this->UserId;
}

FName FUniqueNetIdRedpointGoogle::GetType() const
{
    return REDPOINT_GOOGLE_SUBSYSTEM;
}

const uint8 *FUniqueNetIdRedpointGoogle::GetBytes() const
{
    return (const uint8 *)UserId.GetCharArray().GetData();
}

int32 FUniqueNetIdRedpointGoogle::GetSize() const
{
    return UserId.GetCharArray().GetTypeSize() * UserId.GetCharArray().Num();
}

bool FUniqueNetIdRedpointGoogle::IsValid() const
{
    return !UserId.IsEmpty();
}

FString FUniqueNetIdRedpointGoogle::ToString() const
{
    return UserId;
}

FString FUniqueNetIdRedpointGoogle::ToDebugString() const
{
    return UserId;
}

const TSharedRef<const FUniqueNetId> &FUniqueNetIdRedpointGoogle::EmptyId()
{
    static const TSharedRef<const FUniqueNetId> EmptyId(MakeShared<FUniqueNetIdRedpointGoogle>());
    return EmptyId;
}

#endif
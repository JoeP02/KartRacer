// Copyright June Rhodes 2024. All Rights Reserved.

#include "UserOnlineAccountRedpointGoogle.h"

#if EOS_GOOGLE_ENABLED

TSharedRef<const FUniqueNetId> FUserOnlineAccountRedpointGoogle::GetUserId() const
{
    return this->UserId;
}

FString FUserOnlineAccountRedpointGoogle::GetRealName() const
{
    return this->DisplayName;
}

FString FUserOnlineAccountRedpointGoogle::GetDisplayName(const FString &Platform) const
{
    return this->DisplayName;
}

bool FUserOnlineAccountRedpointGoogle::GetUserAttribute(const FString &AttrName, FString &OutAttrValue) const
{
    return false;
}

FString FUserOnlineAccountRedpointGoogle::GetAccessToken() const
{
    return this->IdToken;
}

bool FUserOnlineAccountRedpointGoogle::GetAuthAttribute(const FString &AttrName, FString &OutAttrValue) const
{
    if (AttrName == TEXT("email"))
    {
        OutAttrValue = this->Email;
        return true;
    }

    return false;
}

bool FUserOnlineAccountRedpointGoogle::SetUserAttribute(const FString &AttrName, const FString &AttrValue)
{
    return false;
}

#endif
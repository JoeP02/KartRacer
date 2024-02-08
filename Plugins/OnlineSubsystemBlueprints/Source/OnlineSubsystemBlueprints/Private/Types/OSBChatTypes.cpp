// Copyright June Rhodes 2023. All Rights Reserved.

#include "Types/OSBChatTypes.h"

FChatRoomConfigBP FChatRoomConfigBP::FromNative(const FChatRoomConfig &InObj)
{
    FChatRoomConfigBP Result;
    Result.bRejoinOnDisconnect = InObj.bRejoinOnDisconnect;
    Result.bPasswordRequired = InObj.bPasswordRequired;
    Result.Password = InObj.Password;
    Result.bAnnounceMembers = InObj.bAnnounceMembers;
    return Result;
}

FChatRoomConfig FChatRoomConfigBP::ToNative() const
{
    FChatRoomConfig Config = FChatRoomConfig();
    Config.bRejoinOnDisconnect = this->bRejoinOnDisconnect;
    Config.bPasswordRequired = this->bPasswordRequired;
    Config.Password = this->Password;
    Config.bAnnounceMembers = this->bAnnounceMembers;
    return Config;
}

FChatRoomInfoBP FChatRoomInfoBP::FromNative(const FChatRoomInfo &InObj)
{
    FChatRoomInfoBP Result;
    Result.bIsValid = true;
    Result.RoomId = InObj.GetRoomId();
    Result.OwnerId = FUniqueNetIdRepl(InObj.GetOwnerId());
    Result.Subject = InObj.GetSubject();
    Result.bPrivate = InObj.IsPrivate();
    Result.bJoined = InObj.IsJoined();
    Result.RoomConfig = FChatRoomConfigBP::FromNative(InObj.GetRoomConfig());
    return Result;
}

FChatRoomInfoBP FChatRoomInfoBP::FromNative(const TSharedPtr<FChatRoomInfo> &InObj)
{
    if (InObj.IsValid())
    {
        return FromNative(*InObj);
    }
    else
    {
        FChatRoomInfoBP Result;
        Result.bIsValid = false;
        return Result;
    }
}

FChatRoomMemberBP FChatRoomMemberBP::FromNative(const FChatRoomMember &InObj)
{
    FChatRoomMemberBP Result;
    Result.UserId = FUniqueNetIdRepl(InObj.GetUserId());
    Result.Nickname = InObj.GetNickname();
    return Result;
}

FChatRoomMemberBP FChatRoomMemberBP::FromNative(const TSharedPtr<FChatRoomMember> &InObj)
{
    if (InObj.IsValid())
    {
        return FromNative(*InObj);
    }
    else
    {
        FChatRoomMemberBP Result;
        Result.bIsValid = false;
        return Result;
    }
}

FChatMessageBP FChatMessageBP::FromNative(const FChatMessage &InObj)
{
    FChatMessageBP Result;
    Result.UserId = FUniqueNetIdRepl(InObj.GetUserId());
    Result.Nickname = InObj.GetNickname();
    Result.Body = InObj.GetBody();
    Result.Timestamp = InObj.GetTimestamp();
    return Result;
}
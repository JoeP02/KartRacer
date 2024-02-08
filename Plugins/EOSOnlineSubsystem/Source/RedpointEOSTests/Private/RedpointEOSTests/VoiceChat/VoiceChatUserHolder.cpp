// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSTests/VoiceChat/VoiceChatUserHolder.h"

namespace Redpoint::EOS::Tests
{

namespace VoiceChat
{

FVoiceChatUserHolder::FVoiceChatUserHolder()
    : VoiceChatUser(nullptr)
{
}

FVoiceChatUserHolder::FVoiceChatUserHolder(IVoiceChatUser *InVoiceChatUser)
    : VoiceChatUser(InVoiceChatUser)
{
}

FVoiceChatUserHolder::~FVoiceChatUserHolder()
{
    if (VoiceChatUser != nullptr)
    {
        IVoiceChat *VoiceChat = IVoiceChat::Get();
        VoiceChat->ReleaseUser(VoiceChatUser);
    }
}

FVoiceChatUserHolder &FVoiceChatUserHolder::operator=(IVoiceChatUser *InVoiceChatUser)
{
    if (VoiceChatUser != nullptr)
    {
        IVoiceChat *VoiceChat = IVoiceChat::Get();
        VoiceChat->ReleaseUser(VoiceChatUser);
    }
    VoiceChatUser = InVoiceChatUser;
    return *this;
}

IVoiceChatUser *FVoiceChatUserHolder::operator->()
{
    return VoiceChatUser;
}

}

}
// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Features/IModularFeatures.h"
#include "VoiceChat.h"

namespace Redpoint::EOS::Tests
{

namespace VoiceChat
{

struct FVoiceChatUserHolder
{
private:
    IVoiceChatUser *VoiceChatUser;

public:
    FVoiceChatUserHolder();
    FVoiceChatUserHolder(IVoiceChatUser *InVoiceChatUser);
    UE_NONCOPYABLE(FVoiceChatUserHolder);
    ~FVoiceChatUserHolder();
    FVoiceChatUserHolder &operator=(IVoiceChatUser *InVoiceChatUser);
    IVoiceChatUser *operator->();
};

}

}
// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSVoiceChatModule.h"

#include "RedpointEOSVoiceChat.h"

void FRedpointEOSVoiceChatModule::StartupModule()
{
    this->VoiceChat = MakeUnique<FRedpointEOSVoiceChat>();

    if (this->VoiceChat.IsValid())
    {
        IModularFeatures::Get().RegisterModularFeature(TEXT("VoiceChat"), this->VoiceChat.Get());
    }
}

void FRedpointEOSVoiceChatModule::ShutdownModule()
{
    if (this->VoiceChat.IsValid())
    {
        IModularFeatures::Get().UnregisterModularFeature(TEXT("VoiceChat"), this->VoiceChat.Get());
        this->VoiceChat->LogoutAndReleaseAllUsers();
        this->VoiceChat.Reset();
    }
}

IMPLEMENT_MODULE(FRedpointEOSVoiceChatModule, RedpointEOSVoiceChat)
// Copyright June Rhodes 2024. All Rights Reserved.

#include "./OnlineAsyncTaskSteamGetLargeFriendAvatar.h"

#include "../LogRedpointSteam.h"
#include "../OnlineSubsystemRedpointSteam.h"
#include "../SteamConstants.h"
#include "../SteamInventory.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemRedpointEOS/Public/EOSError.h"
#include <limits>

#if EOS_STEAM_ENABLED

EOS_ENABLE_STRICT_WARNINGS

void FOnlineAsyncTaskSteamGetLargeFriendAvatar::Tick()
{
    if (!this->bInit)
    {
        this->bInit = true;
    }

    int Picture = SteamFriends()->GetLargeFriendAvatar(this->SteamID);
    if (Picture == -1)
    {
        // @note: AvatarImageLoaded_t does not seem reliable when we set up
        // an event listening in response to -1, so instead we just continously
        // retry calling GetLargeFriendAvatar until it returns something.
    }
    else if (Picture == 0)
    {
        // This user has no avatar set.
        UE_LOG(LogRedpointSteam, Error, TEXT("Steam ID %llu has no avatar set"), this->SteamID);
        this->bIsComplete = true;
        this->bWasSuccessful = false;
        return;
    }
    else
    {
        // The avatar is immediately ready. Set ourselves to complete
        // and let Finalize() call GetLargeFriendAvatar() again.
        UE_LOG(LogRedpointSteam, VeryVerbose, TEXT("Steam ID %llu avatar is immediately ready"), this->SteamID);
        this->bIsComplete = true;
        this->bWasSuccessful = true;
        return;
    }
}

void FOnlineAsyncTaskSteamGetLargeFriendAvatar::Finalize()
{
    if (!this->bWasSuccessful)
    {
        this->Delegate.ExecuteIfBound(
            OnlineRedpointEOS::Errors::NotFound(
                TEXT("FOnlineAsyncTaskSteamGetLargeFriendAvatar::Finalize"),
                TEXT("The specified user does not have an avatar set.")),
            0,
            0,
            nullptr,
            0);
        return;
    }

    int Picture = SteamFriends()->GetLargeFriendAvatar(SteamID);

    uint32 Width;
    uint32 Height;
    SteamUtils()->GetImageSize(Picture, &Width, &Height);

    size_t BufferSize = (size_t)Width * Height * 4;
    if (Width > 0 && Height > 0 && BufferSize < (size_t)std::numeric_limits<int>::max())
    {
        uint8 *AvatarRGBA = (uint8 *)FMemory::MallocZeroed(BufferSize);
        SteamUtils()->GetImageRGBA(Picture, AvatarRGBA, BufferSize);
        for (uint32 i = 0; i < (Width * Height * 4); i += 4)
        {
            uint8 Temp = AvatarRGBA[i + 0];
            AvatarRGBA[i + 0] = AvatarRGBA[i + 2];
            AvatarRGBA[i + 2] = Temp;
        }

        this->Delegate.ExecuteIfBound(OnlineRedpointEOS::Errors::Success(), Width, Height, AvatarRGBA, BufferSize);

        FMemory::Free(AvatarRGBA);
    }
    else
    {
        UE_LOG(
            LogRedpointSteam,
            Error,
            TEXT("%s"),
            *OnlineRedpointEOS::Errors::UnexpectedError(
                 TEXT("FOnlineAsyncTaskSteamGetLargeFriendAvatar::Finalize"),
                 TEXT("The specified avatar has an invalid size."))
                 .ToLogString());
        this->Delegate.ExecuteIfBound(
            OnlineRedpointEOS::Errors::UnexpectedError(
                TEXT("FOnlineAsyncTaskSteamGetLargeFriendAvatar::Finalize"),
                TEXT("The specified avatar has an invalid size.")),
            0,
            0,
            nullptr,
            0);
    }
}

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_STEAM_ENABLED
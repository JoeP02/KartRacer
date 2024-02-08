// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineAvatarInterfaceRedpointSteam.h"
#include "./Tasks/OnlineAsyncTaskSteamGetLargeFriendAvatar.h"
#include "./Tasks/OnlineAsyncTaskSteamRequestUserInformation.h"
#include "Containers/Ticker.h"
#include "Dom/JsonObject.h"
#include "Engine/Texture2D.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "LogRedpointSteam.h"
#include "Misc/ConfigCacheIni.h"

#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"
#include "OnlineSubsystemRedpointSteam.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "TextureResource.h"
#include <limits>

#if EOS_STEAM_ENABLED

THIRD_PARTY_INCLUDES_START
#include "steam/steam_api.h"
THIRD_PARTY_INCLUDES_END

void FOnlineAvatarInterfaceRedpointSteam::OnProcessAvatarUrlRequestComplete(
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    FHttpRequestPtr Request,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    FHttpResponsePtr Response,
    bool bConnectedSuccessfully,
    FString DefaultAvatarUrl,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    FOnGetAvatarUrlComplete OnComplete)
{
    const FString Content = Response->GetContentAsString();

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Content);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
    {
        TSharedPtr<FJsonObject> JsonResponse = JsonObject->GetObjectField("response");
        if (JsonResponse.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> JsonPlayers = JsonResponse->GetArrayField("players");
            if (JsonPlayers.Num() > 0)
            {
                TSharedPtr<FJsonObject> JsonPlayer = JsonPlayers[0]->AsObject();
                OnComplete.ExecuteIfBound(true, JsonPlayer->GetStringField("avatarfull"));
                return;
            }
        }
    }

    OnComplete.ExecuteIfBound(false, MoveTemp(DefaultAvatarUrl));
}

void FOnlineAvatarInterfaceRedpointSteam::OnUserInformationFetched(
    const FOnlineError &Error,
    uint64 SteamID,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    TSoftObjectPtr<UTexture> DefaultTexture,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    FOnGetAvatarComplete OnComplete)
{
    if (!Error.bSucceeded)
    {
        OnComplete.ExecuteIfBound(false, DefaultTexture);
        return;
    }

    // NOLINTNEXTLINE(unreal-ionlinesubsystem-get)
    IOnlineSubsystem *OSS = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
    if (OSS == nullptr)
    {
        OnComplete.ExecuteIfBound(false, DefaultTexture);
        return;
    }

    FOnlineAsyncTaskSteamGetLargeFriendAvatar *GetLargeFriendAvatarTask = new FOnlineAsyncTaskSteamGetLargeFriendAvatar(
        SteamID,
        FSteamAvatarDataFetched::CreateThreadSafeSP(
            this,
            &FOnlineAvatarInterfaceRedpointSteam::OnSteamAvatarDataFetched,
            SteamID,
            DefaultTexture,
            OnComplete));
    FOnlineSubsystemSteamProtectedAccessor::GetAsyncTaskRunner((FOnlineSubsystemSteam *)OSS)
        ->AddToInQueue(GetLargeFriendAvatarTask);
}

void FOnlineAvatarInterfaceRedpointSteam::OnSteamAvatarDataFetched(
    const FOnlineError &Error,
    uint32 Width,
    uint32 Height,
    uint8 *RGBABuffer,
    size_t RGBABufferSize,
    uint64 SteamID,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    TSoftObjectPtr<UTexture> DefaultTexture,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    FOnGetAvatarComplete OnComplete)
{
    if (!Error.bSucceeded)
    {
        OnComplete.ExecuteIfBound(false, MoveTemp(DefaultTexture));
        return;
    }

    UTexture2D *Avatar = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
#if defined(UE_5_0_OR_LATER)
    uint8 *MipData = (uint8 *)Avatar->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
#else
    uint8 *MipData = (uint8 *)Avatar->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
#endif // #if defined(UE_5_0_OR_LATER)
    FMemory::Memcpy(MipData, (void *)RGBABuffer, RGBABufferSize);
#if defined(UE_5_0_OR_LATER)
    Avatar->GetPlatformData()->Mips[0].BulkData.Unlock();
    Avatar->GetPlatformData()->SetNumSlices(1);
#else
    Avatar->PlatformData->Mips[0].BulkData.Unlock();
    Avatar->PlatformData->SetNumSlices(1);
#endif // #if defined(UE_5_0_OR_LATER)
    Avatar->NeverStream = true;
    Avatar->UpdateResource();

    OnComplete.ExecuteIfBound(true, Avatar);
}

bool FOnlineAvatarInterfaceRedpointSteam::GetAvatar(
    const FUniqueNetId &LocalUserId,
    const FUniqueNetId &TargetUserId,
    TSoftObjectPtr<UTexture> DefaultTexture,
    FOnGetAvatarComplete OnComplete)
{
    if (TargetUserId.GetType() != STEAM_SUBSYSTEM)
    {
        UE_LOG(LogRedpointSteam, Error, TEXT("GetAvatar: TargetUserId is non-Steam user."));
        OnComplete.ExecuteIfBound(false, DefaultTexture);
        return true;
    }
    if (!LocalUserId.DoesSharedInstanceExist())
    {
        UE_LOG(LogRedpointSteam, Error, TEXT("GetAvatar: LocalUserId is not a shareable FUniqueNetId."));
        OnComplete.ExecuteIfBound(false, DefaultTexture);
        return true;
    }
    if (!TargetUserId.DoesSharedInstanceExist())
    {
        UE_LOG(LogRedpointSteam, Error, TEXT("GetAvatar: TargetUserId is not a shareable FUniqueNetId."));
        OnComplete.ExecuteIfBound(false, DefaultTexture);
        return true;
    }

    // Cheat. We can't access FUniqueNetIdSteam directly, but we do know it returns
    // the CSteamID as a uint64 from GetBytes :)
    uint64 SteamID = *(uint64 *)TargetUserId.GetBytes();

    // NOLINTNEXTLINE(unreal-ionlinesubsystem-get)
    IOnlineSubsystem *OSS = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
    if (OSS == nullptr)
    {
        OnComplete.ExecuteIfBound(false, DefaultTexture);
        return true;
    }

    FOnlineAsyncTaskSteamRequestUserInformation *RequestUserInformationTask =
        new FOnlineAsyncTaskSteamRequestUserInformation(
            SteamID,
            FSteamUserInformationFetched::CreateThreadSafeSP(
                this,
                &FOnlineAvatarInterfaceRedpointSteam::OnUserInformationFetched,
                SteamID,
                DefaultTexture,
                OnComplete));
    FOnlineSubsystemSteamProtectedAccessor::GetAsyncTaskRunner((FOnlineSubsystemSteam *)OSS)
        ->AddToInQueue(RequestUserInformationTask);
    return true;
}

bool FOnlineAvatarInterfaceRedpointSteam::GetAvatarUrl(
    const FUniqueNetId &LocalUserId,
    const FUniqueNetId &TargetUserId,
    FString DefaultAvatarUrl,
    FOnGetAvatarUrlComplete OnComplete)
{
    if (TargetUserId.GetType() != STEAM_SUBSYSTEM)
    {
        UE_LOG(LogRedpointSteam, Error, TEXT("GetAvatarUrl: TargetUserId is non-Steam user."));
        OnComplete.ExecuteIfBound(false, DefaultAvatarUrl);
        return true;
    }
    if (!LocalUserId.DoesSharedInstanceExist())
    {
        UE_LOG(LogRedpointSteam, Error, TEXT("GetAvatarUrl: LocalUserId is not a shareable FUniqueNetId."));
        OnComplete.ExecuteIfBound(false, DefaultAvatarUrl);
        return true;
    }
    if (!TargetUserId.DoesSharedInstanceExist())
    {
        UE_LOG(LogRedpointSteam, Error, TEXT("GetAvatarUrl: TargetUserId is not a shareable FUniqueNetId."));
        OnComplete.ExecuteIfBound(false, DefaultAvatarUrl);
        return true;
    }

    // Cheat. We can't access FUniqueNetIdSteam directly, but we do know it returns
    // the CSteamID as a uint64 from GetBytes :)
    uint64 SteamID = *(uint64 *)TargetUserId.GetBytes();

    FOnlineSubsystemRedpointSteam *OnlineSubsystemSteam =
        // NOLINTNEXTLINE(unreal-ionlinesubsystem-get)
        static_cast<FOnlineSubsystemRedpointSteam *>(IOnlineSubsystem::Get(REDPOINT_STEAM_SUBSYSTEM));
    if (OnlineSubsystemSteam)
    {
        const FString WebApiKey = OnlineSubsystemSteam->GetWebApiKey();
        if (!WebApiKey.IsEmpty())
        {
            const FString PlayerUrl = FString::Printf(
                TEXT("https://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=%s&steamids=%llu"),
                *WebApiKey,
                SteamID);

            auto Request = FHttpModule::Get().CreateRequest();
            Request->SetVerb("GET");
            Request->SetURL(PlayerUrl);
            Request->OnProcessRequestComplete().BindThreadSafeSP(
                AsShared(),
                &FOnlineAvatarInterfaceRedpointSteam::OnProcessAvatarUrlRequestComplete,
                DefaultAvatarUrl,
                OnComplete);

            Request->ProcessRequest();
        }
        else
        {
            UE_LOG(LogRedpointSteam, Error, TEXT("GetAvatarUrl: Web API Key is empty."));
            OnComplete.ExecuteIfBound(false, DefaultAvatarUrl);
        }
    }
    else
    {
        UE_LOG(LogRedpointSteam, Error, TEXT("GetAvatarUrl: FOnlineSubsystemRedpointSteam not valid."));
        OnComplete.ExecuteIfBound(false, DefaultAvatarUrl);
    }

    return true;
}

#endif
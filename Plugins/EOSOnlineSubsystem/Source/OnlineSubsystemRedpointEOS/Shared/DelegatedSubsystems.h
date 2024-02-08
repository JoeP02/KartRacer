// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "RedpointEOSConfig/Config.h"
#include "OnlineSubsystemRedpointEOS/Shared/WorldResolution.h"
#include "OnlineSubsystemUtils.h"
#include "UObject/NameTypes.h"
#include <functional>

EOS_ENABLE_STRICT_WARNINGS

template <typename T> struct FDelegatedInterface
{
    FName SubsystemName;
    TWeakPtr<T, ESPMode::ThreadSafe> Implementation;
};

class FDelegatedSubsystems
{
public:
    class ISubsystemContext
    {
        friend class FDelegatedSubsystems;

    private:
        FName SubsystemName;
        FName WorldContextHandle;
        IOnlineSubsystem *MainInstance;
        IOnlineSubsystem *RedpointInstance;

        ISubsystemContext(const FName &InWorldContextHandle)
            : SubsystemName()
            , WorldContextHandle(InWorldContextHandle)
            , MainInstance(nullptr)
            , RedpointInstance(nullptr){};

        // Port of Online::GetSubsystem that can work without the UWorld* pointer.
        static IOnlineSubsystem *GetSubsystemByInstanceName(
            const FName &InWorldContextHandle,
            const FName &InSubsystemName = NAME_None)
        {
#if UE_EDITOR
            // at present, multiple worlds are only possible in the editor
            FName Identifier = InSubsystemName;
            if (!InWorldContextHandle.IsEqual(FName(TEXT("DefaultInstance"))) &&
                !InWorldContextHandle.IsEqual(FName(TEXT(""))))
            {
                Identifier = FName(*FString::Printf(
                    TEXT("%s:%s"),
                    !InSubsystemName.IsNone() ? *InSubsystemName.ToString() : TEXT(""),
                    *InWorldContextHandle.ToString()));
            }

            // NOLINTNEXTLINE(unreal-ionlinesubsystem-get)
            return IOnlineSubsystem::Get(Identifier);
#else
            // NOLINTNEXTLINE(unreal-ionlinesubsystem-get)
            return IOnlineSubsystem::Get(InSubsystemName);
#endif
        }

    public:
        template <typename T>
        TWeakPtr<T, ESPMode::ThreadSafe> GetDelegatedInterface(
            std::function<TSharedPtr<T, ESPMode::ThreadSafe>(class IOnlineSubsystem *InOnlineSubsystem)> Resolver)
        {
            if (this->MainInstance == nullptr)
            {
                this->MainInstance = GetSubsystemByInstanceName(this->WorldContextHandle, this->SubsystemName);
            }
            if (this->MainInstance != nullptr)
            {
                TSharedPtr<T, ESPMode::ThreadSafe> Implementation = Resolver(MainInstance);
                if (Implementation.IsValid())
                {
                    return Implementation;
                }
            }
            if (this->RedpointInstance == nullptr)
            {
                this->RedpointInstance = GetSubsystemByInstanceName(
                    this->WorldContextHandle,
                    FName(*FString::Printf(TEXT("Redpoint%s"), *this->SubsystemName.ToString())));
            }
            if (this->RedpointInstance != nullptr)
            {
                TSharedPtr<T, ESPMode::ThreadSafe> Implementation = Resolver(RedpointInstance);
                if (Implementation.IsValid())
                {
                    return Implementation;
                }
            }
            return nullptr;
        }
    };

    template <typename T>
    static TMap<FName, TSharedPtr<T>> GetDelegatedSubsystems(
        const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig,
        FName InstanceName,
        std::function<TSharedPtr<T>(ISubsystemContext &InContext)> Construct)
    {
        return GetDelegatedSubsystemsInternal(InConfig, InstanceName, Construct);
    }

    template <typename T>
    static TMap<FName, TSharedPtr<T>> GetDelegatedSubsystems(
        const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig,
        UWorld *InWorld,
        std::function<TSharedPtr<T>(ISubsystemContext &InContext)> Construct)
    {
        checkf(
            InWorld != nullptr,
            TEXT("World parameter should not be nullptr for GetDelegatedSubsystems, try using one of the other "
                 "overloads."));

        if (GEngine == nullptr)
        {
            checkf(false, TEXT("FDelegatedSubsystems::GetDelegatedSubsystems does not have an engine available."));
            return TMap<FName, TSharedPtr<T>>();
        }

        FWorldContext *WorldContext = GEngine->GetWorldContextFromWorld(InWorld);
        if (WorldContext == nullptr)
        {
            checkf(
                false,
                TEXT("FDelegatedSubsystems::GetDelegatedSubsystems does not have a world context for the provided "
                     "world."));
            return TMap<FName, TSharedPtr<T>>();
        }

        return GetDelegatedSubsystemsInternal(InConfig, *WorldContext, Construct);
    }

private:
    template <typename T>
    static TMap<FName, TSharedPtr<T>> GetDelegatedSubsystemsInternal(
        const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig,
        const FName &InWorldContextHandle,
        std::function<TSharedPtr<T>(ISubsystemContext &InContext)> Construct)
    {
        TMap<FName, TSharedPtr<T>> Results;
        TArray<FString> SubsystemList;
        InConfig->GetDelegatedSubsystemsString().ParseIntoArray(SubsystemList, TEXT(","), true);
        for (const auto &SubsystemName : SubsystemList)
        {
            ISubsystemContext Context(InWorldContextHandle);
            Context.SubsystemName = FName(*SubsystemName);

            TSharedPtr<T> Value = Construct(Context);
            if (Value.IsValid())
            {
                Results.Add(FName(*SubsystemName), Value);
            }
        }
        return Results;
    }

public:
    template <typename T>
    static TMap<FName, FDelegatedInterface<T>> GetDelegatedInterfaces(
        const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig,
        FName InstanceName,
        std::function<TSharedPtr<T, ESPMode::ThreadSafe>(class IOnlineSubsystem *InOnlineSubsystem)> Resolver)
    {
        return GetDelegatedInterfacesInternal(InConfig, InstanceName, Resolver);
    }

    template <typename T>
    static TMap<FName, FDelegatedInterface<T>> GetDelegatedInterfaces(
        const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig,
        UWorld *InWorld,
        std::function<TSharedPtr<T, ESPMode::ThreadSafe>(class IOnlineSubsystem *InOnlineSubsystem)> Resolver)
    {
        checkf(
            InWorld != nullptr,
            TEXT("World parameter should not be nullptr for GetDelegatedInterfaces, try using one of the other "
                 "overloads."));

        if (GEngine == nullptr)
        {
            checkf(false, TEXT("FDelegatedSubsystems::GetDelegatedInterfaces does not have an engine available."));
            return TMap<FName, FDelegatedInterface<T>>();
        }

        FWorldContext *WorldContext = GEngine->GetWorldContextFromWorld(InWorld);
        if (WorldContext == nullptr)
        {
            checkf(
                false,
                TEXT("FDelegatedSubsystems::GetDelegatedInterfaces does not have a world context for the provided "
                     "world."));
            return TMap<FName, FDelegatedInterface<T>>();
        }

        return GetDelegatedInterfacesInternal(InConfig, WorldContext->ContextHandle, Resolver);
    }

private:
    template <typename T>
    static TMap<FName, FDelegatedInterface<T>> GetDelegatedInterfacesInternal(
        const TSharedRef<Redpoint::EOS::Config::IConfig> &InConfig,
        const FName &InWorldContextHandle,
        std::function<TSharedPtr<T, ESPMode::ThreadSafe>(class IOnlineSubsystem *InOnlineSubsystem)> Resolver)
    {
        TMap<FName, FDelegatedInterface<T>> Results;
        TArray<FString> SubsystemList;
        InConfig->GetDelegatedSubsystemsString().ParseIntoArray(SubsystemList, TEXT(","), true);
        for (const auto &SubsystemName : SubsystemList)
        {
            // NOLINTNEXTLINE(unreal-ionlinesubsystem-get)
            IOnlineSubsystem *MainInstance =
                ISubsystemContext::GetSubsystemByInstanceName(InWorldContextHandle, FName(*SubsystemName));
            if (MainInstance != nullptr)
            {
                TSharedPtr<T, ESPMode::ThreadSafe> Implementation = Resolver(MainInstance);
                if (Implementation.IsValid())
                {
                    Results.Add(FName(*SubsystemName), {FName(*SubsystemName), Implementation});
                    continue;
                }
            }
            IOnlineSubsystem *RedpointInstance = ISubsystemContext::GetSubsystemByInstanceName(
                InWorldContextHandle,
                FName(*FString::Printf(TEXT("Redpoint%s"), *SubsystemName)));
            if (RedpointInstance != nullptr)
            {
                TSharedPtr<T, ESPMode::ThreadSafe> Implementation = Resolver(RedpointInstance);
                if (Implementation.IsValid())
                {
                    Results.Add(FName(*SubsystemName), {FName(*SubsystemName), Implementation});
                    continue;
                }
            }
        }
        return Results;
    }
};

EOS_DISABLE_STRICT_WARNINGS
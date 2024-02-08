// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

namespace Redpoint::EOS::Core
{

#if WITH_EDITOR
typedef TDelegate<void(int32_t, const FString &, const FString &)> FOnLogForwardedForEditor;
#endif

class REDPOINTEOSCORE_API FModule : public FDefaultModuleImpl
{
private:
    TSharedPtr<class IRuntimePlatform> RuntimePlatform;

public:
    FModule() = default;
    UE_NONCOPYABLE(FModule);
    ~FModule() = default;

    virtual void ShutdownModule() override;

    static FORCEINLINE FModule &GetModuleChecked()
    {
        FModuleManager &ModuleManager = FModuleManager::Get();
        return ModuleManager.LoadModuleChecked<FModule>("RedpointEOSCore");
    }

    enum class EModuleLoadBehaviour : uint8
    {
        Default,

        ShuttingDown,
    };

    static FORCEINLINE FModule *GetModule(EModuleLoadBehaviour LoadBehaviour)
    {
        if (LoadBehaviour == EModuleLoadBehaviour::Default)
        {
            return &GetModuleChecked();
        }
        else
        {
            FModuleManager &ModuleManager = FModuleManager::Get();
            return (FModule *)ModuleManager.GetModule("RedpointEOSCore");
        }
    }

    TSharedRef<class IRuntimePlatform> GetRuntimePlatform() const;
    void SetRuntimePlatform(const TSharedRef<class IRuntimePlatform> &InRuntimePlatform);

#if WITH_EDITOR
    void SetLogHandler(const FOnLogForwardedForEditor &InEditorLogForwardingHandler);
#endif
};

} // namespace Redpoint::EOS::Core
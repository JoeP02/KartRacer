// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

class FEOSLobbyDetailsHandle
{
private:
    class FEOSLobbyDetailsHandleInternal
    {
    private:
        TWeakPtr<class FOnlineSubsystemEOS, ESPMode::ThreadSafe> OwningInterface;
        EOS_HLobbyDetails Details;

    public:
        FEOSLobbyDetailsHandleInternal(
            const TWeakPtr<class FOnlineSubsystemEOS, ESPMode::ThreadSafe> &InOwningInterface,
            EOS_HLobbyDetails InDetails);
        UE_NONCOPYABLE(FEOSLobbyDetailsHandleInternal);
        ~FEOSLobbyDetailsHandleInternal();

        EOS_HLobbyDetails &GetRef() const;
    };

    TSharedPtr<FEOSLobbyDetailsHandle::FEOSLobbyDetailsHandleInternal> Ref;
    static EOS_HLobbyDetails NullDetails;

public:
    FEOSLobbyDetailsHandle();
    FEOSLobbyDetailsHandle(
        const TWeakPtr<class FOnlineSubsystemEOS, ESPMode::ThreadSafe> &InOwningInterface,
        EOS_HLobbyDetails InDetails);
    // Default copy and move constructors are fine for this class.

    template <typename T>
    T WithWrite(
        const TWeakPtr<class FOnlineSubsystemEOS, ESPMode::ThreadSafe> &InOwningInterface,
        const std::function<T(EOS_HLobbyDetails *WriteTarget)> &Cb)
    {
        EOS_HLobbyDetails WriteTarget = nullptr;
        T Result = Cb(&WriteTarget);
        // Replace the existing reference so that if the handle is currently pointing to
        // another EOS_HLobbyDetails, that EOS_HLobbyDetails will be released if necessary.
        if (WriteTarget != nullptr)
        {
            Ref = MakeShared<FEOSLobbyDetailsHandleInternal>(InOwningInterface, WriteTarget);
        }
        else
        {
            Ref = nullptr;
        }
        return Result;
    };

    EOS_HLobbyDetails &operator*() const;
};
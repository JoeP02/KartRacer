// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Private/HandleManagement/EOSLobbyDetailsHandle.h"

EOS_HLobbyDetails FEOSLobbyDetailsHandle::NullDetails = nullptr;

FEOSLobbyDetailsHandle::FEOSLobbyDetailsHandleInternal::FEOSLobbyDetailsHandleInternal(
    const TWeakPtr<class FOnlineSubsystemEOS, ESPMode::ThreadSafe> &InOwningInterface,
    EOS_HLobbyDetails InDetails)
    : OwningInterface(InOwningInterface)
    , Details(InDetails)
{
}

FEOSLobbyDetailsHandle::FEOSLobbyDetailsHandleInternal::~FEOSLobbyDetailsHandleInternal()
{
    // Prevents us from trying to release a LobbyDetails object that has already
    // been released because the underlying platform has been released.
    if (this->OwningInterface.IsValid())
    {
        EOS_LobbyDetails_Release(this->Details);
    }
}

EOS_HLobbyDetails &FEOSLobbyDetailsHandle::FEOSLobbyDetailsHandleInternal::GetRef() const
{
    checkf(this->OwningInterface.IsValid(), TEXT("Owning interface for this handle has gone away!"));
    return const_cast<FEOSLobbyDetailsHandleInternal *>(this)->Details;
}

FEOSLobbyDetailsHandle::FEOSLobbyDetailsHandle()
    : Ref(nullptr)
{
}

FEOSLobbyDetailsHandle::FEOSLobbyDetailsHandle(
    const TWeakPtr<class FOnlineSubsystemEOS, ESPMode::ThreadSafe> &InOwningInterface,
    EOS_HLobbyDetails InDetails)
    : Ref(MakeShared<FEOSLobbyDetailsHandleInternal>(InOwningInterface, InDetails))
{
}

EOS_HLobbyDetails &FEOSLobbyDetailsHandle::operator*() const
{
    if (!this->Ref.IsValid())
    {
        return NullDetails;
    }
    return this->Ref->GetRef();
}
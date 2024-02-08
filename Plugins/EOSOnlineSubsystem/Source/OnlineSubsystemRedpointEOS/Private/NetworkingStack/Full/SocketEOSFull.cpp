// Copyright June Rhodes 2024. All Rights Reserved.

#include "./SocketEOSFull.h"

#include "../EOSPacketTiming.h"
#include "./EOSSocketRole.h"
#include "./EOSSocketRoleNone.h"
#include "./SocketSubsystemEOSFull.h"
#include "HAL/IConsoleManager.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/UniqueNetIdEOS.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"

EOS_ENABLE_STRICT_WARNINGS

#if !(defined(UE_BUILD_SHIPPING) && UE_BUILD_SHIPPING)
static TAutoConsoleVariable<bool> CVarEOSOnDemandPacketDispatch(
    TEXT("t.EOSOnDemandPacketDispatch"),
    false,
    TEXT("When on, EOS calls EOS_P2P_ReceivePacket every time a socket has RecvFrom or HasPendingData called on it, "
         "instead of only receiving packets at the start of a frame."));
#endif

FSocketEOSFull::FSocketEOSFull(
    const TSharedRef<FSocketSubsystemEOSFull> &InSocketSubsystem,
    EOS_HP2P InP2P,
    FSocketEOSMemoryId InSocketMemoryId,
    const FString &InSocketDescription)
    : ISocketEOS(ESocketType::SOCKTYPE_Datagram, InSocketDescription, REDPOINT_EOS_SUBSYSTEM)
    , Role(InSocketSubsystem->RoleInstance_None)
    , RoleState(MakeShared<FEOSSocketRoleNoneState>())
    , EOSP2P(InP2P)
    , BindAddress(nullptr)
    , SocketMemoryId(InSocketMemoryId)
    , SocketSubsystem(InSocketSubsystem)
{
    check(this->EOSP2P != nullptr);

    UE_LOG(LogRedpointEOSSocketLifecycle, Verbose, TEXT("%d: Socket created as: RoleInstance_None"), this->SocketMemoryId);
}

FSocketEOSFull::~FSocketEOSFull()
{
    UE_LOG(LogRedpointEOSSocketLifecycle, Verbose, TEXT("%d: Socket destroyed."), this->SocketMemoryId);

    this->RemoveSocketKeyIfSet();
}

TSharedRef<ISocketEOS> FSocketEOSFull::AsSharedEOS()
{
    return StaticCastSharedRef<ISocketEOS>(this->AsShared());
}

void FSocketEOSFull::UpdateSocketKey(const FSocketEOSKey &InSocketKey)
{
    this->RemoveSocketKeyIfSet();

    this->SocketKey = MakeShared<FSocketEOSKey>(InSocketKey);
    this->SocketSubsystem->AssignedSockets.Add(InSocketKey, this->AsShared());

    UE_LOG(LogRedpointEOSSocket, Verbose, TEXT("%s: Added to AssignedSockets."), *InSocketKey.ToString());
}

void FSocketEOSFull::RemoveSocketKeyIfSet()
{
    if (this->SocketKey.IsValid())
    {
        this->SocketSubsystem->AssignedSockets.Remove(*this->SocketKey);
        UE_LOG(LogRedpointEOSSocket, Verbose, TEXT("%s: Removed from AssignedSockets."), *this->SocketKey->ToString());

        // Check if this was the last socket connection to a given user.
        bool bFoundOtherRequiredConnection = false;
        for (const auto &RemainingSocket : this->SocketSubsystem->AssignedSockets)
        {
            if (RemainingSocket.Key.IsIdenticalExcludingChannel(*this->SocketKey))
            {
                bFoundOtherRequiredConnection = true;
                break;
            }
        }
        if (!bFoundOtherRequiredConnection)
        {
            UE_LOG(
                LogRedpointEOSSocket,
                Verbose,
                TEXT("%s: Closing connection because the last socket to the remote endpoint has been closed."),
                *this->SocketKey->ToString());

            EOS_P2P_CloseConnectionOptions CloseOpts = {};
            CloseOpts.ApiVersion = EOS_P2P_CLOSECONNECTION_API_LATEST;
            CloseOpts.LocalUserId = this->SocketKey->GetLocalUserId();
            CloseOpts.RemoteUserId = this->SocketKey->GetRemoteUserId();
            CloseOpts.SocketId = &this->SocketKey->GetSymmetricSocketId();

            EOS_EResult CloseResult = EOS_P2P_CloseConnection(this->EOSP2P, &CloseOpts);
            if (CloseResult != EOS_EResult::EOS_Success)
            {
                UE_LOG(
                    LogRedpointEOSSocket,
                    Error,
                    TEXT("%s: Failed to close connection, got status code %s"),
                    *this->SocketKey->ToString(),
                    ANSI_TO_TCHAR(EOS_EResult_ToString(CloseResult)));
            }
        }

        this->SocketKey.Reset();
    }
}

bool FSocketEOSFull::Shutdown(ESocketShutdownMode Mode)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::Shutdown is not supported."));
    return false;
}

bool FSocketEOSFull::Close()
{
    if (!this->Role->Close(*this))
    {
        return false;
    }

    UE_LOG(
        LogRedpointEOSSocketLifecycle,
        Verbose,
        TEXT("%d: Socket unbound on close. Bind address has been reset."),
        this->SocketMemoryId);

    this->RemoveSocketKeyIfSet();

    this->BindAddress.Reset();

    // Ensure UEOSNetConnection is aware that the socket is closed and that any connections
    // still using this socket should also close.
    this->bClosed = true;

    return true;
}

bool FSocketEOSFull::Bind(const FInternetAddr &Addr)
{
    if (Addr.GetProtocolType() != REDPOINT_EOS_SUBSYSTEM)
    {
        UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::Bind called with non-P2P address."));
        return false;
    }

    if (this->BindAddress.IsValid())
    {
        UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::Bind called on already bound socket."));
        return false;
    }

    this->BindAddress = MakeShared<FInternetAddrEOSFull>();
    this->BindAddress->SetRawIp(Addr.GetRawIp());
    check(EOS_ProductUserId_IsValid(this->BindAddress->GetUserId()));

    UE_LOG(
        LogRedpointEOSSocketLifecycle,
        Verbose,
        TEXT("%d: Socket bound to: %s"),
        this->SocketMemoryId,
        *this->BindAddress->ToString(true));

    return true;
}

bool FSocketEOSFull::Connect(const FInternetAddr &Addr)
{
    return this->Role->Connect(*this, (const FInternetAddrEOSFull &)Addr);
}

bool FSocketEOSFull::Listen(int32 MaxBacklog)
{
    return this->Role->Listen(*this, MaxBacklog);
}

bool FSocketEOSFull::WaitForPendingConnection(bool &bHasPendingConnection, const FTimespan &WaitTime)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::WaitForPendingConnection not supported."));
    return false;
}

bool FSocketEOSFull::HasPendingData(uint32 &PendingDataSize)
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSSocketHasPendingData);

#if !(defined(UE_BUILD_SHIPPING) && UE_BUILD_SHIPPING)
    if (CVarEOSOnDemandPacketDispatch.GetValueOnGameThread())
    {
        this->SocketSubsystem->Tick_ReceiveP2PPackets(0.0f);
    }
#endif

    return this->Role->HasPendingData(*this, PendingDataSize);
}

FSocket *FSocketEOSFull::Accept(const FString &InSocketDescription)
{
    UE_LOG(
        LogRedpointEOS,
        Error,
        TEXT("FSocketEOSFull::Accept is not intended to be called by client code; it should only be used internally "
             "within the socket subsystem. Instead, if you want to be notified when a client connects to a listening "
             "socket, bind to the OnConnectionAccepted event on the listening socket instead."));
    return nullptr;
}

FSocket *FSocketEOSFull::Accept(FInternetAddr &InRemoteAddr, const FString &InSocketDescription)
{
    FSocketEOSFull *NewSocket = (FSocketEOSFull *)this->SocketSubsystem->CreateSocket(
        FName(TEXT("EOSSocket")),
        InSocketDescription,
        REDPOINT_EOS_SUBSYSTEM);
    check(NewSocket != nullptr);

    if (this->Role->Accept(*this, NewSocket->AsShared(), (const FInternetAddrEOSFull &)InRemoteAddr))
    {
        this->OnConnectionAccepted.ExecuteIfBound(
            this->AsShared(),
            NewSocket->AsShared(),
            MakeShared<FUniqueNetIdEOS>(this->BindAddress->GetUserId()),
            MakeShared<FUniqueNetIdEOS>(((FInternetAddrEOSFull &)InRemoteAddr).GetUserId()));
        return NewSocket;
    }

    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::Accept failed."));
    this->SocketSubsystem->DestroySocket(NewSocket);
    return nullptr;
}

bool FSocketEOSFull::SendTo(const uint8 *Data, int32 Count, int32 &BytesSent, const FInternetAddr &Destination)
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSSocketSendTo);

#if !(defined(UE_BUILD_SHIPPING) && UE_BUILD_SHIPPING)
    if (CVarEOSEnablePacketTiming.GetValueOnGameThread())
    {
        uint8 *TimedData = (uint8 *)FMemory::Malloc(Count + sizeof(int64));
        FMemory::Memcpy(TimedData + sizeof(int64), Data, Count);
        *((int64 *)TimedData) = FDateTime::UtcNow().GetTicks();
        int32 TimedBytesSent;
        bool Result = this->Role->SendTo(
            *this,
            TimedData,
            Count + sizeof(int64),
            TimedBytesSent,
            (const FInternetAddrEOSFull &)Destination);
        BytesSent = TimedBytesSent - sizeof(int64);
        FMemory::Free(TimedData);
        return Result;
    }
#endif

    return this->Role->SendTo(*this, Data, Count, BytesSent, (const FInternetAddrEOSFull &)Destination);
}

bool FSocketEOSFull::Send(const uint8 *Data, int32 Count, int32 &BytesSent)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::Send is not supported."));
    return false;
}

bool FSocketEOSFull::RecvFrom(
    uint8 *Data,
    int32 BufferSize,
    int32 &BytesRead,
    FInternetAddr &Source,
    ESocketReceiveFlags::Type Flags)
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSSocketRecvFrom);

    if (Flags != ESocketReceiveFlags::None)
    {
        UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::RecvFrom does not support calling with non-None flags."));
        return false;
    }

#if !(defined(UE_BUILD_SHIPPING) && UE_BUILD_SHIPPING)
    if (CVarEOSOnDemandPacketDispatch.GetValueOnGameThread())
    {
        this->SocketSubsystem->Tick_ReceiveP2PPackets(0.0f);
    }
#endif

    return this->Role->RecvFrom(*this, Data, BufferSize, BytesRead, (FInternetAddrEOSFull &)Source, Flags);
}

bool FSocketEOSFull::Recv(uint8 *Data, int32 BufferSize, int32 &BytesRead, ESocketReceiveFlags::Type Flags)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::Recv is not supported."));
    return false;
}

bool FSocketEOSFull::RecvMulti(FRecvMulti &MultiData, ESocketReceiveFlags::Type Flags)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::RecvMulti not supported."));
    return false;
}

bool FSocketEOSFull::Wait(ESocketWaitConditions::Type Condition, FTimespan WaitTime)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::Wait not supported."));
    return false;
}

ESocketConnectionState FSocketEOSFull::GetConnectionState()
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::GetConnectionState is not supported."));
    return ESocketConnectionState::SCS_NotConnected;
}

void FSocketEOSFull::GetAddress(FInternetAddr &OutAddr)
{
    if (this->BindAddress.IsValid())
    {
        OutAddr.SetRawIp(this->BindAddress->GetRawIp());
        return;
    }

    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::GetAddress called on non-bound socket."));
}

bool FSocketEOSFull::GetPeerAddress(FInternetAddr &OutAddr)
{
    return this->Role->GetPeerAddress(*this, (FInternetAddrEOSFull &)OutAddr);
}

bool FSocketEOSFull::SetNonBlocking(bool bIsNonBlocking)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetNonBlocking is not supported."));
    return false;
}

bool FSocketEOSFull::SetBroadcast(bool bAllowBroadcast)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetBroadcast is not supported."));
    return false;
}

bool FSocketEOSFull::SetNoDelay(bool bIsNoDelay)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetNoDelay is not supported."));
    return false;
}

bool FSocketEOSFull::JoinMulticastGroup(const FInternetAddr &GroupAddress)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::JoinMulticastGroup is not supported."));
    return false;
}

bool FSocketEOSFull::JoinMulticastGroup(const FInternetAddr &GroupAddress, const FInternetAddr &InterfaceAddress)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::JoinMulticastGroup is not supported."));
    return false;
}

bool FSocketEOSFull::LeaveMulticastGroup(const FInternetAddr &GroupAddress)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::LeaveMulticastGroup is not supported."));
    return false;
}

bool FSocketEOSFull::LeaveMulticastGroup(const FInternetAddr &GroupAddress, const FInternetAddr &InterfaceAddress)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::LeaveMulticastGroup is not supported."));
    return false;
}

bool FSocketEOSFull::SetMulticastLoopback(bool bLoopback)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetMulticastLoopback is not supported."));
    return false;
}

bool FSocketEOSFull::SetMulticastTtl(uint8 TimeToLive)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetMulticastTtl is not supported."));
    return false;
}

bool FSocketEOSFull::SetMulticastInterface(const FInternetAddr &InterfaceAddress)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetMulticastInterface is not supported."));
    return false;
}

bool FSocketEOSFull::SetReuseAddr(bool bAllowReuse)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetReuseAddr is not supported."));
    return false;
}

bool FSocketEOSFull::SetLinger(bool bShouldLinger, int32 Timeout)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetLinger is not supported."));
    return false;
}

bool FSocketEOSFull::SetRecvErr(bool bUseErrorQueue)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetRecvErr is not supported."));
    return false;
}

bool FSocketEOSFull::SetSendBufferSize(int32 Size, int32 &NewSize)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetSendBufferSize is not supported."));
    return false;
}

bool FSocketEOSFull::SetReceiveBufferSize(int32 Size, int32 &NewSize)
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::SetReceiveBufferSize is not supported."));
    return false;
}

int32 FSocketEOSFull::GetPortNo()
{
    UE_LOG(LogRedpointEOS, Error, TEXT("FSocketEOSFull::GetPortNo is not supported."));
    return 0;
}

EOS_DISABLE_STRICT_WARNINGS
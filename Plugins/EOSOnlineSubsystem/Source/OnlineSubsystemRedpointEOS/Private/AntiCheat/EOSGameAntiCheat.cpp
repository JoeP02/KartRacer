// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Shared/AntiCheat/EOSGameAntiCheat.h"

#include "OnlineSubsystemRedpointEOS/Private/AntiCheat/AntiCheatPlayerTracker.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSString.h"
#include "OnlineSubsystemRedpointEOS/Shared/WeakPtrHelpers.h"

#define FUNCTION_CONTEXT_CURRENT_SESSION_STRING                                                                        \
    (this->CurrentSession.IsValid() ? *this->CurrentSession->GetInstanceGuid().ToString() : TEXT(""))

class FIgnoredEOSGameAntiCheatSession : public FAntiCheatSession
{
public:
    FIgnoredEOSGameAntiCheatSession() = default;
    UE_NONCOPYABLE(FIgnoredEOSGameAntiCheatSession);
};

FEOSGameAntiCheatSession::FEOSGameAntiCheatSession(TSharedRef<const FUniqueNetIdEOS> InHostUserId)
    : FAntiCheatSession()
    , PlayerTracking(MakeShared<FAntiCheatPlayerTracker>())
    , bIsServer(false)
    , HostUserId(MoveTemp(InHostUserId))
    , ListenServerUserId()
    , bIsDedicatedServerSession(false)
    , StackCount(0)
    , ServerConnectionUrlOnClient(TEXT(""))
{
}

EOS_AntiCheatCommon_ClientHandle FEOSGameAntiCheatSession::AddPlayer(
    const FUniqueNetIdEOS &UserId,
    bool &bOutShouldRegister)
{
    UE_LOG(
        LogRedpointEOSAntiCheat,
        Verbose,
        TEXT("Game Anti-Cheat: %p: AddPlayer(UserId: %s)"),
        this,
        *UserId.ToString());

    return this->PlayerTracking->AddPlayer(UserId, bOutShouldRegister);
}

void FEOSGameAntiCheatSession::RemovePlayer(const FUniqueNetIdEOS &UserId)
{
    UE_LOG(
        LogRedpointEOSAntiCheat,
        Verbose,
        TEXT("Game Anti-Cheat: %p: RemovePlayer(UserId: %s)"),
        this,
        *UserId.ToString());

    this->PlayerTracking->RemovePlayer(UserId);
}

bool FEOSGameAntiCheatSession::ShouldDeregisterPlayerBeforeRemove(const FUniqueNetIdEOS &UserId) const
{
    return this->PlayerTracking->ShouldDeregisterPlayerBeforeRemove(UserId);
}

TSharedPtr<const FUniqueNetIdEOS> FEOSGameAntiCheatSession::GetPlayer(EOS_AntiCheatCommon_ClientHandle Handle)
{
    return this->PlayerTracking->GetPlayer(Handle);
}

EOS_AntiCheatCommon_ClientHandle FEOSGameAntiCheatSession::GetHandle(const FUniqueNetIdEOS &UserId)
{
    return this->PlayerTracking->GetHandle(UserId);
}

bool FEOSGameAntiCheatSession::HasPlayer(const FUniqueNetIdEOS &UserId)
{
    return this->PlayerTracking->HasPlayer(UserId);
}

void FEOSGameAntiCheat::EnsureSessionIsCurrent(FAntiCheatSession &Session, const TCHAR *FunctionName) const
{
    bool bIsCurrentSession = Session.GetInstanceGuid() == this->CurrentSession->GetInstanceGuid();
    checkf(
        bIsCurrentSession,
        TEXT("Anti-Cheat requested session %s in %s must match current session %s!"),
        *Session.GetInstanceGuid().ToString(),
        FunctionName,
        *this->CurrentSession->GetInstanceGuid().ToString());
    if (!bIsCurrentSession)
    {
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Fatal,
            TEXT("Anti-Cheat requested session %s in %s must match current session %s!"),
            *Session.GetInstanceGuid().ToString(),
            FunctionName,
            *this->CurrentSession->GetInstanceGuid().ToString());
    }
}

FEOSGameAntiCheat::FEOSGameAntiCheat(EOS_HPlatform InPlatform, bool bInHasTrustedClientPrivateKey)
    : EOSACClient(EOS_Platform_GetAntiCheatClientInterface(InPlatform))
    , bHasTrustedClientPrivateKey(bInHasTrustedClientPrivateKey)
    , CurrentSession()
    , NotifyMessageToServer()
    , NotifyMessageToPeer()
    , NotifyClientActionRequired()
    , NotifyClientAuthStatusChanged()
#if EOS_VERSION_AT_LEAST(1, 16, 0)
    , NotifyClientIntegrityViolated()
#endif
          {};

bool FEOSGameAntiCheat::Init()
{
    UE_LOG(LogRedpointEOSAntiCheat, Verbose, TEXT("Game Anti-Cheat: %p: Init"), this);

    if (this->ShouldRemoteSkipPeerRegistration())
    {
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT("Game Anti-Cheat: %p: Operating in 'skip registration' mode as this trusted client can not process "
                 "network messages."),
            this);
        return true;
    }

    EOS_AntiCheatClient_AddNotifyMessageToServerOptions MsgSrvOpts = {};
    MsgSrvOpts.ApiVersion = EOS_ANTICHEATCLIENT_ADDNOTIFYMESSAGETOSERVER_API_LATEST;
    this->NotifyMessageToServer = EOSRegisterEvent<
        EOS_HAntiCheatClient,
        EOS_AntiCheatClient_AddNotifyMessageToServerOptions,
        EOS_AntiCheatClient_OnMessageToServerCallbackInfo>(
        this->EOSACClient,
        &MsgSrvOpts,
        EOS_AntiCheatClient_AddNotifyMessageToServer,
        EOS_AntiCheatClient_RemoveNotifyMessageToServer,
        [WeakThis = GetWeakThis(this)](const EOS_AntiCheatClient_OnMessageToServerCallbackInfo *Data) {
#define FUNCTION_CONTEXT_MACRO                                                                                         \
    "Game Anti-Cheat: %p: NotifyMessageToServer(MessageData: ..., MessageDataSizeInBytes: %u)"
#define FUNCTION_CONTEXT_ARGS WeakThis.IsValid() ? WeakThis.Pin().Get() : nullptr, Data->MessageDataSizeBytes
            if (auto This = PinWeakThis(WeakThis))
            {
                if (This->CurrentSession.IsValid())
                {
                    TSharedPtr<const FUniqueNetIdEOS> HostUserId = This->CurrentSession->HostUserId;
                    if (HostUserId.IsValid())
                    {
                        This->OnSendNetworkMessage.ExecuteIfBound(
                            StaticCastSharedRef<FAntiCheatSession>(This->CurrentSession.ToSharedRef()),
                            *HostUserId,
                            *FUniqueNetIdEOS::DedicatedServerId(),
                            (const uint8 *)Data->MessageData,
                            Data->MessageDataSizeBytes);

                        if (!This->OnSendNetworkMessage.IsBound())
                        {
                            UE_LOG(
                                LogRedpointEOSAntiCheat,
                                Warning,
                                TEXT(FUNCTION_CONTEXT_MACRO
                                     ": Propagated event OnSendNetworkMessage() handler, but no handlers were "
                                     "bound."),
                                FUNCTION_CONTEXT_ARGS);
                        }
                        else
                        {
                            UE_LOG(
                                LogRedpointEOSAntiCheat,
                                VeryVerbose,
                                TEXT(FUNCTION_CONTEXT_MACRO ": Propagated event to OnSendNetworkMessage() handler."),
                                FUNCTION_CONTEXT_ARGS);
                        }
                    }
                    else
                    {
                        UE_LOG(
                            LogRedpointEOSAntiCheat,
                            Error,
                            TEXT(FUNCTION_CONTEXT_MACRO
                                 ": Ignoring call as the host ID of the current session is not valid."),
                            FUNCTION_CONTEXT_ARGS);
                    }
                }
                else
                {
                    UE_LOG(
                        LogRedpointEOSAntiCheat,
                        Error,
                        TEXT(FUNCTION_CONTEXT_MACRO ": Ignoring call as there is no current session."),
                        FUNCTION_CONTEXT_ARGS);
                }
            }
            else
            {
                UE_LOG(
                    LogRedpointEOSAntiCheat,
                    Warning,
                    TEXT(FUNCTION_CONTEXT_MACRO ": Ignoring call as the instance is no longer valid."),
                    FUNCTION_CONTEXT_ARGS);
            }

#undef FUNCTION_CONTEXT_MACRO
#undef FUNCTION_CONTEXT_ARGS
        });

    EOS_AntiCheatClient_AddNotifyMessageToPeerOptions MsgOpts = {};
    MsgOpts.ApiVersion = EOS_ANTICHEATCLIENT_ADDNOTIFYMESSAGETOPEER_API_LATEST;
    this->NotifyMessageToPeer = EOSRegisterEvent<
        EOS_HAntiCheatClient,
        EOS_AntiCheatClient_AddNotifyMessageToPeerOptions,
        EOS_AntiCheatCommon_OnMessageToClientCallbackInfo>(
        this->EOSACClient,
        &MsgOpts,
        EOS_AntiCheatClient_AddNotifyMessageToPeer,
        EOS_AntiCheatClient_RemoveNotifyMessageToPeer,
        [WeakThis = GetWeakThis(this)](const EOS_AntiCheatCommon_OnMessageToClientCallbackInfo *Data) {
#define FUNCTION_CONTEXT_MACRO                                                                                         \
    "Game Anti-Cheat: %p: NotifyMessageToPeer(ClientHandle: %d, MessageData: ..., MessageDataSizeInBytes: %u)"
#define FUNCTION_CONTEXT_ARGS                                                                                          \
    WeakThis.IsValid() ? WeakThis.Pin().Get() : nullptr, Data->ClientHandle, Data->MessageDataSizeBytes
            if (auto This = PinWeakThis(WeakThis))
            {
                if (This->CurrentSession.IsValid())
                {
                    TSharedPtr<const FUniqueNetIdEOS> HostUserId = This->CurrentSession->HostUserId;
                    TSharedPtr<const FUniqueNetIdEOS> PlayerId = This->CurrentSession->GetPlayer(Data->ClientHandle);

                    if (!HostUserId.IsValid())
                    {
                        UE_LOG(
                            LogRedpointEOSAntiCheat,
                            Error,
                            TEXT(FUNCTION_CONTEXT_MACRO
                                 ": Ignoring call as the host ID of the current session is not valid."),
                            FUNCTION_CONTEXT_ARGS);
                    }
                    else if (!PlayerId.IsValid())
                    {
                        UE_LOG(
                            LogRedpointEOSAntiCheat,
                            Error,
                            TEXT(FUNCTION_CONTEXT_MACRO ": Ignoring call as the target player ID is not valid."),
                            FUNCTION_CONTEXT_ARGS);
                    }
                    else
                    {
                        This->OnSendNetworkMessage.ExecuteIfBound(
                            StaticCastSharedRef<FAntiCheatSession>(This->CurrentSession.ToSharedRef()),
                            *HostUserId,
                            *PlayerId,
                            (const uint8 *)Data->MessageData,
                            Data->MessageDataSizeBytes);

                        if (!This->OnSendNetworkMessage.IsBound())
                        {
                            UE_LOG(
                                LogRedpointEOSAntiCheat,
                                Warning,
                                TEXT(FUNCTION_CONTEXT_MACRO
                                     ": Propagated event OnSendNetworkMessage() handler, but no handlers were "
                                     "bound."),
                                FUNCTION_CONTEXT_ARGS);
                        }
                        else
                        {
                            UE_LOG(
                                LogRedpointEOSAntiCheat,
                                VeryVerbose,
                                TEXT(FUNCTION_CONTEXT_MACRO ": Propagated event to OnSendNetworkMessage() handler."),
                                FUNCTION_CONTEXT_ARGS);
                        }
                    }
                }
                else
                {
                    UE_LOG(
                        LogRedpointEOSAntiCheat,
                        Error,
                        TEXT(FUNCTION_CONTEXT_MACRO ": Ignoring call as there is no current session."),
                        FUNCTION_CONTEXT_ARGS);
                }
            }
            else
            {
                UE_LOG(
                    LogRedpointEOSAntiCheat,
                    Warning,
                    TEXT(FUNCTION_CONTEXT_MACRO ": Ignoring call as the instance is no longer valid."),
                    FUNCTION_CONTEXT_ARGS);
            }

#undef FUNCTION_CONTEXT_MACRO
#undef FUNCTION_CONTEXT_ARGS
        });

    EOS_AntiCheatClient_AddNotifyPeerActionRequiredOptions ActOpts = {};
    ActOpts.ApiVersion = EOS_ANTICHEATCLIENT_ADDNOTIFYPEERACTIONREQUIRED_API_LATEST;
    this->NotifyClientActionRequired = EOSRegisterEvent<
        EOS_HAntiCheatClient,
        EOS_AntiCheatClient_AddNotifyPeerActionRequiredOptions,
        EOS_AntiCheatCommon_OnClientActionRequiredCallbackInfo>(
        this->EOSACClient,
        &ActOpts,
        EOS_AntiCheatClient_AddNotifyPeerActionRequired,
        EOS_AntiCheatClient_RemoveNotifyPeerActionRequired,
        [WeakThis = GetWeakThis(this)](const EOS_AntiCheatCommon_OnClientActionRequiredCallbackInfo *Data) {
#define FUNCTION_CONTEXT_MACRO                                                                                         \
    "Game Anti-Cheat: %p: NotifyPeerActionRequired(ClientHandle: %d, ClientAction: %u, ActionReasonCode: %u, "         \
    "ActionReasonDetailsString: %s)"
#define FUNCTION_CONTEXT_ARGS                                                                                          \
    WeakThis.IsValid() ? WeakThis.Pin().Get() : nullptr, Data->ClientHandle, Data->ClientAction,                       \
        Data->ActionReasonCode,                                                                                        \
        *EOSString_AntiCheat_ActionReasonDetailsString::FromUtf8String(Data->ActionReasonDetailsString)
            if (auto This = PinWeakThis(WeakThis))
            {
                if (This->CurrentSession.IsValid())
                {
                    This->OnPlayerActionRequired.Broadcast(
                        *This->CurrentSession->GetPlayer(Data->ClientHandle),
                        Data->ClientAction,
                        Data->ActionReasonCode,
                        EOSString_AntiCheat_ActionReasonDetailsString::FromUtf8String(Data->ActionReasonDetailsString));

                    if (!This->OnPlayerActionRequired.IsBound())
                    {
                        UE_LOG(
                            LogRedpointEOSAntiCheat,
                            Warning,
                            TEXT(FUNCTION_CONTEXT_MACRO
                                 ": Propagated event OnPlayerActionRequired() handler, but no handlers were "
                                 "bound."),
                            FUNCTION_CONTEXT_ARGS);
                    }
                    else
                    {
                        UE_LOG(
                            LogRedpointEOSAntiCheat,
                            Verbose,
                            TEXT(FUNCTION_CONTEXT_MACRO ": Propagated event to OnPlayerActionRequired() handler."),
                            FUNCTION_CONTEXT_ARGS);
                    }
                }
                else
                {
                    UE_LOG(
                        LogRedpointEOSAntiCheat,
                        Error,
                        TEXT(FUNCTION_CONTEXT_MACRO ": Ignoring call as there is no current session."),
                        FUNCTION_CONTEXT_ARGS);
                }
            }
            else
            {
                UE_LOG(
                    LogRedpointEOSAntiCheat,
                    Warning,
                    TEXT(FUNCTION_CONTEXT_MACRO ": Ignoring call as the instance is no longer valid."),
                    FUNCTION_CONTEXT_ARGS);
            }

#undef FUNCTION_CONTEXT_MACRO
#undef FUNCTION_CONTEXT_ARGS
        });

    EOS_AntiCheatClient_AddNotifyPeerAuthStatusChangedOptions AuthOpts = {};
    AuthOpts.ApiVersion = EOS_ANTICHEATCLIENT_ADDNOTIFYPEERAUTHSTATUSCHANGED_API_LATEST;
    this->NotifyClientAuthStatusChanged = EOSRegisterEvent<
        EOS_HAntiCheatClient,
        EOS_AntiCheatClient_AddNotifyPeerAuthStatusChangedOptions,
        EOS_AntiCheatCommon_OnClientAuthStatusChangedCallbackInfo>(
        this->EOSACClient,
        &AuthOpts,
        EOS_AntiCheatClient_AddNotifyPeerAuthStatusChanged,
        EOS_AntiCheatClient_RemoveNotifyPeerAuthStatusChanged,
        [WeakThis = GetWeakThis(this)](const EOS_AntiCheatCommon_OnClientAuthStatusChangedCallbackInfo *Data) {
#define FUNCTION_CONTEXT_MACRO                                                                                         \
    "Game Anti-Cheat: %p: NotifyPeerAuthStatusChanged(ClientHandle: %d, ClientAuthStatus: %u)"
#define FUNCTION_CONTEXT_ARGS                                                                                          \
    WeakThis.IsValid() ? WeakThis.Pin().Get() : nullptr, Data->ClientHandle, Data->ClientAuthStatus
            if (auto This = PinWeakThis(WeakThis))
            {
                if (This->CurrentSession.IsValid())
                {
                    This->OnPlayerAuthStatusChanged.Broadcast(
                        *This->CurrentSession->GetPlayer(Data->ClientHandle),
                        Data->ClientAuthStatus);

                    if (!This->OnPlayerAuthStatusChanged.IsBound())
                    {
                        UE_LOG(
                            LogRedpointEOSAntiCheat,
                            Warning,
                            TEXT(FUNCTION_CONTEXT_MACRO
                                 ": Propagated event OnPlayerAuthStatusChanged() handler, but no handlers were "
                                 "bound."),
                            FUNCTION_CONTEXT_ARGS);
                    }
                    else
                    {
                        UE_LOG(
                            LogRedpointEOSAntiCheat,
                            Verbose,
                            TEXT(FUNCTION_CONTEXT_MACRO ": Propagated event to OnPlayerAuthStatusChanged() handler."),
                            FUNCTION_CONTEXT_ARGS);
                    }
                }
                else
                {
                    UE_LOG(
                        LogRedpointEOSAntiCheat,
                        Error,
                        TEXT(FUNCTION_CONTEXT_MACRO ": Ignoring call as there is no current session."),
                        FUNCTION_CONTEXT_ARGS);
                }
            }
            else
            {
                UE_LOG(
                    LogRedpointEOSAntiCheat,
                    Warning,
                    TEXT(FUNCTION_CONTEXT_MACRO ": Ignoring call as the instance is no longer valid."),
                    FUNCTION_CONTEXT_ARGS);
            }

#undef FUNCTION_CONTEXT_MACRO
#undef FUNCTION_CONTEXT_ARGS
        });

#if EOS_VERSION_AT_LEAST(1, 16, 0)
    EOS_AntiCheatClient_AddNotifyClientIntegrityViolatedOptions IntegrityOpts = {};
    IntegrityOpts.ApiVersion = EOS_ANTICHEATCLIENT_ADDNOTIFYCLIENTINTEGRITYVIOLATED_API_LATEST;
    this->NotifyClientIntegrityViolated = EOSRegisterEvent<
        EOS_HAntiCheatClient,
        EOS_AntiCheatClient_AddNotifyClientIntegrityViolatedOptions,
        EOS_AntiCheatClient_OnClientIntegrityViolatedCallbackInfo>(
        this->EOSACClient,
        &IntegrityOpts,
        EOS_AntiCheatClient_AddNotifyClientIntegrityViolated,
        EOS_AntiCheatClient_RemoveNotifyClientIntegrityViolated,
        [WeakThis = GetWeakThis(this)](const EOS_AntiCheatClient_OnClientIntegrityViolatedCallbackInfo *Data) {
            if (auto This = PinWeakThis(WeakThis))
            {
                // There is an Anti-Cheat violation.
                // @todo: We need to propagate this to an event the developer can listen on, but there aren't any good
                // events in the standard IOnlineSubsystem API. We probably need to add a custom interface for this.
                FString ViolationTypeStr = TEXT("Unknown");
                auto ViolationType = Data->ViolationType;
                if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_Invalid)
                {
                    ViolationTypeStr = TEXT("Invalid");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_IntegrityCatalogNotFound)
                {
                    ViolationTypeStr = TEXT("IntegrityCatalogNotFound");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_IntegrityCatalogError)
                {
                    ViolationTypeStr = TEXT("IntegrityCatalogError");
                }
                else if (
                    ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_IntegrityCatalogCertificateRevoked)
                {
                    ViolationTypeStr = TEXT("IntegrityCatalogCertificateRevoked");
                }
                else if (
                    ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_IntegrityCatalogMissingMainExecutable)
                {
                    ViolationTypeStr = TEXT("IntegrityCatalogMissingMainExecutable");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_GameFileMismatch)
                {
                    ViolationTypeStr = TEXT("GameFileMismatch");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_RequiredGameFileNotFound)
                {
                    ViolationTypeStr = TEXT("RequiredGameFileNotFound");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_UnknownGameFileForbidden)
                {
                    ViolationTypeStr = TEXT("UnknownGameFileForbidden");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_SystemFileUntrusted)
                {
                    ViolationTypeStr = TEXT("SystemFileUntrusted");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_ForbiddenModuleLoaded)
                {
                    ViolationTypeStr = TEXT("ForbiddenModuleLoaded");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_CorruptedMemory)
                {
                    ViolationTypeStr = TEXT("CorruptedMemory");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_ForbiddenToolDetected)
                {
                    ViolationTypeStr = TEXT("ForbiddenToolDetected");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_InternalAntiCheatViolation)
                {
                    ViolationTypeStr = TEXT("InternalAntiCheatViolation");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_CorruptedNetworkMessageFlow)
                {
                    ViolationTypeStr = TEXT("CorruptedNetworkMessageFlow");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_VirtualMachineNotAllowed)
                {
                    ViolationTypeStr = TEXT("VirtualMachineNotAllowed");
                }
                else if (ViolationType == EOS_EAntiCheatClientViolationType::EOS_ACCVT_ForbiddenSystemConfiguration)
                {
                    ViolationTypeStr = TEXT("ForbiddenSystemConfiguration");
                }
                UE_LOG(
                    LogRedpointEOS,
                    Error,
                    TEXT(
                        "Anti-Cheat Violation: Type: '%s'. Message: '%s'. You will not be able to connect to protected "
                        "servers."),
                    *ViolationTypeStr,
                    ANSI_TO_TCHAR(Data->ViolationMessage));
            }
        });
#endif

    return true;
}

void FEOSGameAntiCheat::Shutdown()
{
    UE_LOG(LogRedpointEOSAntiCheat, Verbose, TEXT("Game Anti-Cheat: %p: Shutdown"), this);

    this->NotifyMessageToServer.Reset();
    this->NotifyMessageToPeer.Reset();
    this->NotifyClientActionRequired.Reset();
    this->NotifyClientAuthStatusChanged.Reset();
}

bool FEOSGameAntiCheat::ShouldRemoteSkipPeerRegistration() const
{
    // If EOSACClient is nullptr, then this client can't process network messages
    // from peers even when it is a trusted client.
    return this->EOSACClient == nullptr && this->bHasTrustedClientPrivateKey;
}

bool FEOSGameAntiCheat::Exec(UWorld *InWorld, const TCHAR *Cmd, FOutputDevice &Ar)
{
    return false;
}

TSharedPtr<FAntiCheatSession> FEOSGameAntiCheat::CreateSession(
    bool bIsServer,
    const FUniqueNetIdEOS &HostUserId,
    bool bIsDedicatedServerSession,
    TSharedPtr<const FUniqueNetIdEOS> ListenServerUserId,
    FString ServerConnectionUrlOnClient)
{
#define FUNCTION_CONTEXT_MACRO                                                                                         \
    "Game Anti-Cheat: %p: CreateSession(bIsServer: %s, HostUserId: %s, bIsDedicatedServerSession: %s, "                \
    "ListenServerUserId: %s, ServerConnectionUrlOnClient: %s)"
#define FUNCTION_CONTEXT_ARGS                                                                                          \
    this, bIsServer ? TEXT("true") : TEXT("false"), *HostUserId.ToString(),                                            \
        bIsDedicatedServerSession ? TEXT("true") : TEXT("false"),                                                      \
        ListenServerUserId.IsValid() ? *ListenServerUserId->ToString() : TEXT("(none)"), *ServerConnectionUrlOnClient

    if (this->ShouldRemoteSkipPeerRegistration())
    {
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO
                 ": Skipping CreateSession implementation as this is a trusted client without EOS_HAntiCheatClient."),
            FUNCTION_CONTEXT_ARGS);
        return MakeShared<FIgnoredEOSGameAntiCheatSession>();
    }

    UE_LOG(LogRedpointEOSAntiCheat, Verbose, TEXT(FUNCTION_CONTEXT_MACRO ": Called"), FUNCTION_CONTEXT_ARGS);

    checkf(
        !bIsServer || (bIsServer && !bIsDedicatedServerSession),
        TEXT("Invalid BeginSession call for Game Anti-Cheat."));

    if (this->CurrentSession.IsValid())
    {
        if (!bIsServer && this->CurrentSession->ServerConnectionUrlOnClient != ServerConnectionUrlOnClient)
        {
            UE_LOG(
                LogRedpointEOSAntiCheat,
                Verbose,
                TEXT(FUNCTION_CONTEXT_MACRO
                     ": Current session exists, but we're creating a session to a different server. The current "
                     "session URL is '%s'; the new session URL is '%s'. Destroying current session first, then "
                     "continuing as normal."),
                FUNCTION_CONTEXT_ARGS,
                *this->CurrentSession->ServerConnectionUrlOnClient,
                *ServerConnectionUrlOnClient);

            // The client is connecting to a new server. We have to immediately
            // end the current Anti-Cheat session so we can start a new one.
            this->CurrentSession->StackCount = 1;
            if (!this->DestroySession(*this->CurrentSession))
            {
                UE_LOG(
                    LogRedpointEOSAntiCheat,
                    Error,
                    TEXT(FUNCTION_CONTEXT_MACRO ": Failed to destroy current session as part of implicit cleanup."),
                    FUNCTION_CONTEXT_ARGS);
                return nullptr;
            }

            // Now we have closed the current session, we continue as normal to
            // establish the new session.
            UE_LOG(
                LogRedpointEOSAntiCheat,
                Verbose,
                TEXT(FUNCTION_CONTEXT_MACRO
                     ": Implicitly closed the current session, continuing with session creation."),
                FUNCTION_CONTEXT_ARGS);
        }
        else
        {
            UE_LOG(
                LogRedpointEOSAntiCheat,
                Verbose,
                TEXT(FUNCTION_CONTEXT_MACRO ": Current session is already valid, "
                                            "incrementing stack count to %d."),
                FUNCTION_CONTEXT_ARGS,
                this->CurrentSession->StackCount + 1);

            this->CurrentSession->StackCount++;
            return this->CurrentSession;
        }
    }

    EOS_AntiCheatClient_BeginSessionOptions ClientOpts = {};
    ClientOpts.ApiVersion = EOS_ANTICHEATCLIENT_BEGINSESSION_API_LATEST;
    ClientOpts.LocalUserId = HostUserId.GetProductUserId();
    ClientOpts.Mode = bIsDedicatedServerSession ? EOS_EAntiCheatClientMode::EOS_ACCM_ClientServer
                                                : EOS_EAntiCheatClientMode::EOS_ACCM_PeerToPeer;
    EOS_EResult ClientResult = EOS_AntiCheatClient_BeginSession(this->EOSACClient, &ClientOpts);
    if (ClientResult != EOS_EResult::EOS_Success)
    {
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Error,
            TEXT(FUNCTION_CONTEXT_MACRO ": Unable to begin game session (got result %s)."),
            FUNCTION_CONTEXT_ARGS,
            ANSI_TO_TCHAR(EOS_EResult_ToString(ClientResult)));
        return nullptr;
    }

    TSharedRef<FEOSGameAntiCheatSession> Session =
        MakeShared<FEOSGameAntiCheatSession>(StaticCastSharedRef<const FUniqueNetIdEOS>(HostUserId.AsShared()));
    Session->bIsServer = bIsServer;
    Session->bIsDedicatedServerSession = bIsDedicatedServerSession;
    Session->StackCount = 1;
    Session->ListenServerUserId.Reset();
    Session->ServerConnectionUrlOnClient = ServerConnectionUrlOnClient;
    this->CurrentSession = Session;

    UE_LOG(
        LogRedpointEOSAntiCheat,
        Verbose,
        TEXT(FUNCTION_CONTEXT_MACRO ": Started new session; current session is now %s."),
        FUNCTION_CONTEXT_ARGS,
        *this->CurrentSession->ToString());

    if (!bIsServer && !bIsDedicatedServerSession)
    {
        // We are a client connecting to a listen server. We need to register the host as a player immediately.
        checkf(
            ListenServerUserId.IsValid(),
            TEXT("Expected listen server user ID if we are a client connecting to a listen server!"));
        Session->ListenServerUserId = ListenServerUserId;
        if (!this->RegisterPlayer(
                *Session,
                *ListenServerUserId,
                EOS_EAntiCheatCommonClientType::EOS_ACCCT_ProtectedClient,
                EOS_EAntiCheatCommonClientPlatform::EOS_ACCCP_Unknown))
        {
            this->DestroySession(*Session);
            return nullptr;
        }
    }

    return Session;

#undef FUNCTION_CONTEXT_MACRO
#undef FUNCTION_CONTEXT_ARGS
}

bool FEOSGameAntiCheat::DestroySession(FAntiCheatSession &Session)
{
#define FUNCTION_CONTEXT_MACRO "Game Anti-Cheat: %p: DestroySession(CurrentSession: %s, TargetSession: %s)"
#define FUNCTION_CONTEXT_ARGS this, FUNCTION_CONTEXT_CURRENT_SESSION_STRING, *Session.ToString()

    if (this->ShouldRemoteSkipPeerRegistration())
    {
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO
                 ": Skipping DestroySession implementation as this is a trusted client without EOS_HAntiCheatClient."),
            FUNCTION_CONTEXT_ARGS);
        return true;
    }

    if (!this->CurrentSession.IsValid())
    {
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO ": There is no current session, ignoring DestroySession call."),
            FUNCTION_CONTEXT_ARGS);

        return true;
    }

    this->EnsureSessionIsCurrent(Session, ANSI_TO_TCHAR(__FUNCTION__));
    this->CurrentSession->StackCount--;

    UE_LOG(
        LogRedpointEOSAntiCheat,
        Verbose,
        TEXT(FUNCTION_CONTEXT_MACRO ": Decremented stack count of session; stack count is now at %d."),
        FUNCTION_CONTEXT_ARGS,
        this->CurrentSession->StackCount);

    if (this->CurrentSession->StackCount == 0)
    {
        if (this->CurrentSession->ListenServerUserId.IsValid())
        {
            UE_LOG(
                LogRedpointEOS,
                Verbose,
                TEXT(FUNCTION_CONTEXT_MACRO ": Unregistering listen server player %s as current session is closing."),
                FUNCTION_CONTEXT_ARGS,
                *this->CurrentSession->ListenServerUserId->ToString());

            this->UnregisterPlayer(Session, *this->CurrentSession->ListenServerUserId);
        }

        EOS_AntiCheatClient_EndSessionOptions ClientOpts = {};
        ClientOpts.ApiVersion = EOS_ANTICHEATCLIENT_ENDSESSION_API_LATEST;
        EOS_EResult ClientResult = EOS_AntiCheatClient_EndSession(this->EOSACClient, &ClientOpts);
        if (ClientResult != EOS_EResult::EOS_Success)
        {
            UE_LOG(
                LogRedpointEOS,
                Error,
                TEXT(FUNCTION_CONTEXT_MACRO ": Unable to end game server session (got result %s)."),
                FUNCTION_CONTEXT_ARGS,
                ANSI_TO_TCHAR(EOS_EResult_ToString(ClientResult)));
            return false;
        }

        this->CurrentSession.Reset();

        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO ": Successfully ended game session."),
            FUNCTION_CONTEXT_ARGS);
    }

    return true;

#undef FUNCTION_CONTEXT_MACRO
#undef FUNCTION_CONTEXT_ARGS
}

bool FEOSGameAntiCheat::RegisterPlayer(
    FAntiCheatSession &Session,
    const FUniqueNetIdEOS &UserId,
    EOS_EAntiCheatCommonClientType ClientType,
    EOS_EAntiCheatCommonClientPlatform ClientPlatform)
{
#define FUNCTION_CONTEXT_MACRO                                                                                         \
    "Game Anti-Cheat: %p: RegisterPlayer(CurrentSession: %s, TargetSession: %s, UserId: %s, ClientType: %u, "          \
    "ClientPlatform: %u)"
#define FUNCTION_CONTEXT_ARGS                                                                                          \
    this, FUNCTION_CONTEXT_CURRENT_SESSION_STRING, *Session.ToString(), *UserId.ToString(), ClientType, ClientPlatform

    if (this->ShouldRemoteSkipPeerRegistration())
    {
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO
                 ": Skipping RegisterPlayer implementation as this is a trusted client without EOS_HAntiCheatClient."),
            FUNCTION_CONTEXT_ARGS);
        this->OnPlayerAuthStatusChanged.Broadcast(
            UserId,
            EOS_EAntiCheatCommonClientAuthStatus::EOS_ACCCAS_RemoteAuthComplete);
        return true;
    }

    UE_LOG(LogRedpointEOSAntiCheat, Verbose, TEXT(FUNCTION_CONTEXT_MACRO ": Called"), FUNCTION_CONTEXT_ARGS);

    this->EnsureSessionIsCurrent(Session, ANSI_TO_TCHAR(__FUNCTION__));

    FEOSGameAntiCheatSession &GameSession = (FEOSGameAntiCheatSession &)Session;

    if (GameSession.bIsDedicatedServerSession)
    {
        // Clients connecting to dedicated servers don't register the server as a peer, and dedicated servers never use
        // this implementation.
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO
                 ": Ignoring RegisterPlayer request as we are a client connected to a dedicated server."),
            FUNCTION_CONTEXT_ARGS);
        return true;
    }

    // Otherwise, this is called on clients when they connect to the listen server (with the listen server as the
    // UserId), and on the listen server for each connecting user.

    bool bShouldRegister = false;
    EOS_AntiCheatCommon_ClientHandle ClientHandle = GameSession.AddPlayer(UserId, bShouldRegister);

    UE_LOG(
        LogRedpointEOSAntiCheat,
        Verbose,
        TEXT(FUNCTION_CONTEXT_MACRO ": Should we register the specified player? %s"),
        FUNCTION_CONTEXT_ARGS,
        bShouldRegister ? TEXT("true") : TEXT("false"));

    if (bShouldRegister)
    {
        EOS_AntiCheatClient_RegisterPeerOptions PeerOpts = {};
        PeerOpts.ApiVersion = EOS_ANTICHEATCLIENT_REGISTERPEER_API_LATEST;
        PeerOpts.PeerHandle = ClientHandle;
        PeerOpts.ClientType = ClientType;
        PeerOpts.ClientPlatform = ClientPlatform;
#if EOS_VERSION_AT_LEAST(1, 15, 0)
        PeerOpts.PeerProductUserId = UserId.GetProductUserId();
        PeerOpts.AuthenticationTimeout = 120;
#else
        EOSString_ProductUserId::AllocateToCharBuffer(UserId.GetProductUserId(), PeerOpts.AccountId);
#endif
        PeerOpts.IpAddress =
            nullptr; // We never use the IpAddress field for peers, because it will always be over EOS P2P.
        EOS_EResult PeerResult = EOS_AntiCheatClient_RegisterPeer(this->EOSACClient, &PeerOpts);
#if EOS_VERSION_AT_LEAST(1, 15, 0)
#else
        EOSString_ProductUserId::FreeFromCharBuffer(PeerOpts.AccountId);
#endif
        if (PeerResult != EOS_EResult::EOS_Success)
        {
            GameSession.RemovePlayer(UserId);
            UE_LOG(
                LogRedpointEOS,
                Error,
                TEXT(FUNCTION_CONTEXT_MACRO ": Unable to register client (got result %s)."),
                FUNCTION_CONTEXT_ARGS,
                ANSI_TO_TCHAR(EOS_EResult_ToString(PeerResult)));
            return false;
        }

        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO ": Successfully registered player with Anti-Cheat interface."),
            FUNCTION_CONTEXT_ARGS);
    }

    return true;

#undef FUNCTION_CONTEXT_MACRO
#undef FUNCTION_CONTEXT_ARGS
}

bool FEOSGameAntiCheat::UnregisterPlayer(FAntiCheatSession &Session, const FUniqueNetIdEOS &UserId)
{
#define FUNCTION_CONTEXT_MACRO                                                                                         \
    "Game Anti-Cheat: %p: UnregisterPlayer(CurrentSession: %s, TargetSession: %s, UserId: %s)"
#define FUNCTION_CONTEXT_ARGS this, FUNCTION_CONTEXT_CURRENT_SESSION_STRING, *Session.ToString(), *UserId.ToString()

    if (this->ShouldRemoteSkipPeerRegistration())
    {
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(
                FUNCTION_CONTEXT_MACRO
                ": Skipping UnregisterPlayer implementation as this is a trusted client without EOS_HAntiCheatClient."),
            FUNCTION_CONTEXT_ARGS);
        return true;
    }

    UE_LOG(LogRedpointEOSAntiCheat, Verbose, TEXT(FUNCTION_CONTEXT_MACRO ": Called"), FUNCTION_CONTEXT_ARGS);

    this->EnsureSessionIsCurrent(Session, ANSI_TO_TCHAR(__FUNCTION__));

    FEOSGameAntiCheatSession &GameSession = (FEOSGameAntiCheatSession &)Session;

    if (GameSession.bIsDedicatedServerSession)
    {
        // Clients connecting to dedicated servers don't register the server as a peer, and dedicated servers never use
        // this implementation.
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO
                 ": Ignoring UnregisterPlayer request as we are a client connected to a dedicated server."),
            FUNCTION_CONTEXT_ARGS);
        return true;
    }

    if (GameSession.ShouldDeregisterPlayerBeforeRemove(UserId))
    {
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO
                 ": Player tracking indicated we should try to deregister player with Anti-Cheat interface before "
                 "removing them from tracking."),
            FUNCTION_CONTEXT_ARGS);

        EOS_AntiCheatClient_UnregisterPeerOptions PeerOpts = {};
        PeerOpts.ApiVersion = EOS_ANTICHEATCLIENT_UNREGISTERPEER_API_LATEST;
        PeerOpts.PeerHandle = GameSession.GetHandle(UserId);
        EOS_EResult PeerResult = EOS_AntiCheatClient_UnregisterPeer(this->EOSACClient, &PeerOpts);
        if (PeerResult != EOS_EResult::EOS_Success)
        {
            UE_LOG(
                LogRedpointEOS,
                Error,
                TEXT("Anti-Cheat: Unable to unregister client (got result %s)."),
                ANSI_TO_TCHAR(EOS_EResult_ToString(PeerResult)));
            return false;
        }

        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO ": Successfully unregistered player from Anti-Cheat interface."),
            FUNCTION_CONTEXT_ARGS);
    }

    GameSession.RemovePlayer(UserId);

    UE_LOG(
        LogRedpointEOSAntiCheat,
        Verbose,
        TEXT(FUNCTION_CONTEXT_MACRO ": Removed player from player tracking."),
        FUNCTION_CONTEXT_ARGS);

    return true;

#undef FUNCTION_CONTEXT_MACRO
#undef FUNCTION_CONTEXT_ARGS
}

bool FEOSGameAntiCheat::ReceiveNetworkMessage(
    FAntiCheatSession &Session,
    const FUniqueNetIdEOS &SourceUserId,
    const FUniqueNetIdEOS &TargetUserId,
    const uint8 *Data,
    uint32_t Size)
{
#define FUNCTION_CONTEXT_MACRO                                                                                         \
    "Game Anti-Cheat: %p: ReceiveNetworkMessage(CurrentSession: %s, TargetSession: %s, SourceUserId: %s, "             \
    "TargetUserId: %s, Data: ..., Size: %u)"
#define FUNCTION_CONTEXT_ARGS                                                                                          \
    this, FUNCTION_CONTEXT_CURRENT_SESSION_STRING, *Session.ToString(), *SourceUserId.ToString(),                      \
        *TargetUserId.ToString(), Size

    if (this->ShouldRemoteSkipPeerRegistration())
    {
        UE_LOG(
            LogRedpointEOSAntiCheat,
            Verbose,
            TEXT(FUNCTION_CONTEXT_MACRO ": Skipping ReceiveNetworkMessage implementation as this is a trusted client "
                                        "without EOS_HAntiCheatClient."),
            FUNCTION_CONTEXT_ARGS);
        return true;
    }

    EOS_EResult Result;
    FString CallName = TEXT("(Unknown)");
    if (SourceUserId.IsDedicatedServer())
    {
        EOS_AntiCheatClient_ReceiveMessageFromServerOptions Opts = {};
        Opts.ApiVersion = EOS_ANTICHEATCLIENT_RECEIVEMESSAGEFROMSERVER_API_LATEST;
        Opts.Data = Data;
        Opts.DataLengthBytes = Size;
        Result = EOS_AntiCheatClient_ReceiveMessageFromServer(this->EOSACClient, &Opts);
        CallName = TEXT("EOS_AntiCheatClient_ReceiveMessageFromServer");
    }
    else if (this->CurrentSession.IsValid() && this->CurrentSession->HasPlayer(SourceUserId))
    {
        EOS_AntiCheatClient_ReceiveMessageFromPeerOptions Opts = {};
        Opts.ApiVersion = EOS_ANTICHEATCLIENT_RECEIVEMESSAGEFROMPEER_API_LATEST;
        Opts.Data = Data;
        Opts.DataLengthBytes = Size;
        Opts.PeerHandle = this->CurrentSession->GetHandle(SourceUserId);
        Result = EOS_AntiCheatClient_ReceiveMessageFromPeer(this->EOSACClient, &Opts);
        CallName = TEXT("EOS_AntiCheatClient_ReceiveMessageFromPeer");
    }
    else
    {
        Result = EOS_EResult::EOS_NotFound;
    }
    if (Result != EOS_EResult::EOS_Success)
    {
        UE_LOG(
            LogRedpointEOS,
            Error,
            TEXT(FUNCTION_CONTEXT_MACRO ": Failed to receive message from client via %s: %s"),
            FUNCTION_CONTEXT_ARGS,
            *CallName,
            ANSI_TO_TCHAR(EOS_EResult_ToString(Result)));
        return false;
    }

    UE_LOG(
        LogRedpointEOSAntiCheat,
        VeryVerbose,
        TEXT(FUNCTION_CONTEXT_MACRO ": Received network message."),
        FUNCTION_CONTEXT_ARGS);

    return true;

#undef FUNCTION_CONTEXT_MACRO
#undef FUNCTION_CONTEXT_ARGS
}

#undef FUNCTION_CONTEXT_CURRENT_SESSION_STRING
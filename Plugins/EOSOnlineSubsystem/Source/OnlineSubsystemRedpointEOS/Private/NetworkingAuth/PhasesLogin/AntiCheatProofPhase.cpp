// Copyright June Rhodes 2024. All Rights Reserved.

#include "./AntiCheatProofPhase.h"

#include "Misc/Base64.h"
#include "OnlineSubsystemRedpointEOS/Private/EOSControlChannel.h"
#include "RedpointLibHydrogen.h"

#define hydro_sign_NONCEBYTES 32

void FAntiCheatProofPhase::InitializeNonceForRequestProof()
{
    char Nonce[hydro_sign_NONCEBYTES];
    FMemory::Memzero(&Nonce, hydro_sign_NONCEBYTES);
    hydro_random_buf(&Nonce, hydro_sign_NONCEBYTES);
    checkf(this->PendingNonceCheck.IsEmpty(), TEXT("There is already an outbound proof verification in progress."));
    this->PendingNonceCheck = FBase64::Encode((uint8 *)&Nonce, hydro_sign_NONCEBYTES);
}

void FAntiCheatProofPhase::RequestProofFromPeer(
    const TSharedRef<FAuthLoginPhaseContext> &Context,
    const TSharedPtr<IAntiCheat> &AntiCheat,
    UNetConnection *Connection,
    const FUniqueNetIdRepl &UserIdRepl)
{
    // Request the trusted client proof from the peer. Certain platforms like consoles are able to run as
    // unprotected clients and still be secure, so they don't need Anti-Cheat active. To ensure that peers don't
    // pretend as if they're on console, we make peers send a cryptographic proof. Only the console builds contain the
    // private key necessary for signing the proof.
    UE_LOG(
        LogRedpointEOSNetworkAuth,
        Verbose,
        TEXT("Server authentication: %s: Requesting trusted client proof from remote peer %s..."),
        *Context->GetUserId()->ToString(),
        *UserIdRepl.ToString());
    this->InitializeNonceForRequestProof();
    uint8 ImplementationType = (uint8)AntiCheat->GetImplementationType();
    FUniqueNetIdRepl UserIdReplTemp = UserIdRepl;
    FNetControlMessage<NMT_EOS_RequestTrustedClientProof>::Send(
        Connection,
        UserIdReplTemp,
        this->PendingNonceCheck,
        ImplementationType);
}

void FAntiCheatProofPhase::DeliverProofToPeer(
    const TSharedRef<FAuthLoginPhaseContext> &Context,
    const TSharedPtr<IAntiCheat> &AntiCheat,
    const Redpoint::EOS::Config::IConfig *Config,
    UNetConnection *Connection,
    const FString &EncodedNonce,
    FOnlineSubsystemEOS *OSS,
    bool bRequestingTrustedClientProofFromListenServer)
{
    bool bCanProvideProof = false;
    FString EncodedProof = TEXT("");
    FString PlatformString = TEXT("");

    if (Config == nullptr)
    {
        UE_LOG(
            LogRedpointEOSNetworkAuth,
            Warning,
            TEXT("Can't provide client proof, as configuration is not available."));
    }
    else
    {
        FString TrustedClientPrivateKey = Config->GetTrustedClientPrivateKey();
        if (!TrustedClientPrivateKey.IsEmpty())
        {
            TArray<uint8> TrustedClientPrivateKeyBytes;
            if (FBase64::Decode(TrustedClientPrivateKey, TrustedClientPrivateKeyBytes) &&
                TrustedClientPrivateKeyBytes.Num() == hydro_sign_SECRETKEYBYTES)
            {
                TArray<uint8> DecodedNonce;
                if (FBase64::Decode(EncodedNonce, DecodedNonce) && DecodedNonce.Num() == hydro_sign_NONCEBYTES)
                {
                    uint8_t signature[hydro_sign_BYTES];
                    if (hydro_sign_create(
                            signature,
                            DecodedNonce.GetData(),
                            DecodedNonce.Num(),
                            "TRSTPROF",
                            TrustedClientPrivateKeyBytes.GetData()) == 0)
                    {
                        TArray<uint8> SignatureBytes(&signature[0], hydro_sign_BYTES);
                        EncodedProof = FBase64::Encode(SignatureBytes);
                        bCanProvideProof = true;

                        if (OSS != nullptr)
                        {
                            PlatformString = OSS->GetRuntimePlatform().GetAntiCheatPlatformName();
                        }
                        else
                        {
                            PlatformString = TEXT("Unknown");
                        }
                    }
                }
            }
        }
    }

    if (bCanProvideProof)
    {
        UE_LOG(LogRedpointEOSNetworkAuth, Verbose, TEXT("Providing trusted client proof..."));
    }
    else
    {
        UE_LOG(
            LogRedpointEOSNetworkAuth,
            Verbose,
            TEXT("Responding to trusted client proof request with no proof available..."));
    }

    if (bRequestingTrustedClientProofFromListenServer)
    {
        this->InitializeNonceForRequestProof();
    }

    FUniqueNetIdRepl UserIdRepl = StaticCastSharedRef<const FUniqueNetId>(Context->GetUserId());
    bool bSkipPeerRegistration = bCanProvideProof && AntiCheat->ShouldRemoteSkipPeerRegistration();
    FNetControlMessage<NMT_EOS_DeliverTrustedClientProof>::Send(
        Connection,
        UserIdRepl,
        bCanProvideProof,
        EncodedProof,
        PlatformString,
        bRequestingTrustedClientProofFromListenServer,
        this->PendingNonceCheck,
        bSkipPeerRegistration);
}

void FAntiCheatProofPhase::RegisterRoutes(UEOSControlChannel *ControlChannel)
{
    ControlChannel->AddRoute(
        NMT_EOS_RequestTrustedClientProof,
        FAuthPhaseRoute::CreateLambda([](UEOSControlChannel *ControlChannel, FInBunch &Bunch) {
            FUniqueNetIdRepl TargetUserId;
            FString EncodedNonce;
            uint8 AntiCheatImplementationType;
            if (FNetControlMessage<NMT_EOS_RequestTrustedClientProof>::Receive(
                    Bunch,
                    TargetUserId,
                    EncodedNonce,
                    AntiCheatImplementationType))
            {
                TSharedPtr<FAuthLoginPhaseContext> Context = ControlChannel->GetAuthLoginPhaseContext(TargetUserId);
                if (Context)
                {
                    TSharedPtr<FAntiCheatProofPhase> Phase =
                        Context->GetPhase<FAntiCheatProofPhase>(AUTH_PHASE_ANTI_CHEAT_PROOF);
                    if (Phase)
                    {
                        Phase->On_NMT_EOS_RequestTrustedClientProof(
                            Context.ToSharedRef(),
                            EncodedNonce,
                            (EAntiCheatImplementationType)AntiCheatImplementationType);
                        return true;
                    }
                }
            }
            return false;
        }));
    ControlChannel->AddRoute(
        NMT_EOS_DeliverTrustedClientProof,
        FAuthPhaseRoute::CreateLambda([](UEOSControlChannel *ControlChannel, FInBunch &Bunch) {
            FUniqueNetIdRepl TargetUserId;
            bool bCanProvideProof;
            FString EncodedProof;
            FString PlatformString;
            bool bRequestMutualProofFromListenServer;
            FString EncodedNonceForListenServer;
            bool bSkipPeerRegistration;
            if (FNetControlMessage<NMT_EOS_DeliverTrustedClientProof>::Receive(
                    Bunch,
                    TargetUserId,
                    bCanProvideProof,
                    EncodedProof,
                    PlatformString,
                    bRequestMutualProofFromListenServer,
                    EncodedNonceForListenServer,
                    bSkipPeerRegistration))
            {
                TSharedPtr<FAuthLoginPhaseContext> Context = ControlChannel->GetAuthLoginPhaseContext(TargetUserId);
                if (Context)
                {
                    TSharedPtr<FAntiCheatProofPhase> Phase =
                        Context->GetPhase<FAntiCheatProofPhase>(AUTH_PHASE_ANTI_CHEAT_PROOF);
                    if (Phase)
                    {
                        Phase->On_NMT_EOS_DeliverTrustedClientProof(
                            Context.ToSharedRef(),
                            bCanProvideProof,
                            EncodedProof,
                            PlatformString,
                            bRequestMutualProofFromListenServer,
                            EncodedNonceForListenServer,
                            bSkipPeerRegistration);
                        return true;
                    }
                }
            }
            return false;
        }));
    ControlChannel->AddRoute(
        NMT_EOS_AcceptedMutualTrustedClientProof,
        FAuthPhaseRoute::CreateLambda([](UEOSControlChannel *ControlChannel, FInBunch &Bunch) {
            FUniqueNetIdRepl TargetUserId;
            if (FNetControlMessage<NMT_EOS_AcceptedMutualTrustedClientProof>::Receive(Bunch, TargetUserId))
            {
                TSharedPtr<FAuthLoginPhaseContext> Context = ControlChannel->GetAuthLoginPhaseContext(TargetUserId);
                if (Context)
                {
                    TSharedPtr<FAntiCheatProofPhase> Phase =
                        Context->GetPhase<FAntiCheatProofPhase>(AUTH_PHASE_ANTI_CHEAT_PROOF);
                    if (Phase)
                    {
                        Phase->On_NMT_EOS_AcceptedMutualTrustedClientProof(Context.ToSharedRef());
                        return true;
                    }
                }
            }
            return false;
        }));
}

void FAntiCheatProofPhase::Start(const TSharedRef<FAuthLoginPhaseContext> &Context)
{
    UNetConnection *Connection;
    const Redpoint::EOS::Config::IConfig *Config;
    if (!Context->GetConnection(Connection) || !Context->GetConfig(Config))
    {
        Context->Finish(EAuthPhaseFailureCode::All_ConnectionHasGoneAway);
        return;
    }

    checkf(
        Connection->PlayerId.IsValid(),
        TEXT("Connection player ID must have been set by verification phase before Anti-Cheat phases can begin."));

    Context->SetVerificationStatus(EUserVerificationStatus::EstablishingAntiCheatProof);

    TSharedPtr<IAntiCheat> AntiCheat;
    TSharedPtr<FAntiCheatSession> AntiCheatSession;
    bool bIsOwnedByBeacon;
    if (!Context->GetAntiCheat(AntiCheat, AntiCheatSession, bIsOwnedByBeacon))
    {
        Context->Finish(EAuthPhaseFailureCode::All_ConnectionHasGoneAway);
        return;
    }
    if (bIsOwnedByBeacon)
    {
        // Beacons do not use Anti-Cheat, because Anti-Cheat only allows one Anti-Cheat connection
        // for the main game session.
        UE_LOG(
            LogRedpointEOSNetworkAuth,
            Verbose,
            TEXT("Server authentication: %s: Skipping Anti-Cheat connection because this is a beacon connection..."),
            *Context->GetUserId()->ToString());
        Context->Finish(EAuthPhaseFailureCode::Success);
        return;
    }
    if (!AntiCheat.IsValid() || !AntiCheatSession.IsValid())
    {
        UE_LOG(
            LogRedpointEOSNetworkAuth,
            Error,
            TEXT("Server authentication: %s: Failed to obtain Anti-Cheat interface or session."),
            *Context->GetUserId()->ToString());
        Context->Finish(EAuthPhaseFailureCode::All_CanNotAccessAntiCheat);
        return;
    }

    FUniqueNetIdRepl UserIdRepl(Context->GetUserId()->AsShared());

    // Check if we can request a proof.
    if (Config == nullptr)
    {
        UE_LOG(
            LogRedpointEOSNetworkAuth,
            Error,
            TEXT("Server authentication: %s: Failed to obtain configuration."),
            *Context->GetUserId()->ToString());
        Context->Finish(EAuthPhaseFailureCode::All_CanNotAccessConfig);
        return;
    }
    FString TrustedClientPublicKey = Config->GetTrustedClientPublicKey();
    if (TrustedClientPublicKey.IsEmpty())
    {
        // We can't request proof verification from the client, because we don't have a public key.
        this->On_NMT_EOS_DeliverTrustedClientProof(Context, false, TEXT(""), TEXT(""), false, TEXT(""), false);
        return;
    }

    // Request the trusted client proof from the peer.
    this->RequestProofFromPeer(Context, AntiCheat, Connection, UserIdRepl);
}

void FAntiCheatProofPhase::On_NMT_EOS_RequestTrustedClientProof(
    const TSharedRef<FAuthLoginPhaseContext> &Context,
    const FString &EncodedNonce,
    EAntiCheatImplementationType AntiCheatImplementationType)
{
    EEOSNetDriverRole Role;
    if (!Context->GetRole(Role))
    {
        Context->Finish(EAuthPhaseFailureCode::All_CanNotAccessConfig);
        return;
    }

    if (Role == EEOSNetDriverRole::DedicatedServer)
    {
        // Dedicated servers can't be asked to proof their Anti-Cheat status. We only allow
        // trusted client proofs in the following scenarios:
        //
        // - ListenServer: A player is hosting a listen server on their machine, and clients need to verify the listen
        //				   server is intact.
        // - ClientConnectedToDedicatedServer: A player is connecting to a dedicated server, and the server needs to
        //                                     verify the client is intact.
        // - ClientConnectedToListenServer: A player is connecting to a listen server, and the server needs to verify
        //                                  the client is intact.
        Context->Finish(EAuthPhaseFailureCode::Phase_AntiCheatProof_NotPermittedToRequestClientProof);
        return;
    }

    UNetConnection *Connection;
    const Redpoint::EOS::Config::IConfig *Config;
    FOnlineSubsystemEOS *OSS;
    if (!Context->GetConnection(Connection) || !Context->GetConfig(Config) || !Context->GetOSS(OSS))
    {
        Context->Finish(EAuthPhaseFailureCode::All_ConnectionHasGoneAway);
        return;
    }

    TSharedPtr<IAntiCheat> AntiCheat;
    TSharedPtr<FAntiCheatSession> AntiCheatSession;
    bool bIsBeacon;
    if (Context->GetAntiCheat(AntiCheat, AntiCheatSession, bIsBeacon) && AntiCheat.IsValid() &&
        AntiCheat->GetImplementationType() != AntiCheatImplementationType)
    {
        Context->Finish(EAuthPhaseFailureCode::Phase_AntiCheatProof_AntiCheatImplementationNotCompatible);
        return;
    }

    // Deliver the requested proof, if possible, to the peer. If we are a client connecting to
    // a listen server, we ask the listen server to prove their EAC status or prove that they're
    // a trusted client.
    this->DeliverProofToPeer(
        Context,
        AntiCheat,
        Config,
        Connection,
        EncodedNonce,
        OSS,
        Role == EEOSNetDriverRole::ClientConnectedToListenServer);
}

void FAntiCheatProofPhase::On_NMT_EOS_DeliverTrustedClientProof(
    const TSharedRef<FAuthLoginPhaseContext> &Context,
    bool bCanProvideProof,
    const FString &EncodedProof,
    const FString &PlatformString,
    bool bRequestMutualProofFromListenServer,
    FString EncodedNonceForListenServer,
    bool bSkipPeerRegistration)
{
    EEOSNetDriverRole Role;
    if (!Context->GetRole(Role))
    {
        Context->Finish(EAuthPhaseFailureCode::All_CanNotAccessConfig);
        return;
    }

    if (Role == EEOSNetDriverRole::ClientConnectedToDedicatedServer)
    {
        // This is unexpected; as a client we shouldn't have been able to ask
        // a dedicated server for a trusted client proof.
        Context->Finish(EAuthPhaseFailureCode::Phase_AntiCheatProof_NotPermittedToRequestClientProof);
        return;
    }

    if (Role != EEOSNetDriverRole::ListenServer && bRequestMutualProofFromListenServer)
    {
        // Clients can't anyone other than a listen server to do a mutual proof.
        Context->Finish(EAuthPhaseFailureCode::Phase_AntiCheatProof_NotPermittedToRequestClientProof);
        return;
    }

    UNetConnection *Connection;
    const Redpoint::EOS::Config::IConfig *Config;
    FOnlineSubsystemEOS *OSS;
    if (!Context->GetConnection(Connection) || !Context->GetConfig(Config) || !Context->GetOSS(OSS))
    {
        Context->Finish(EAuthPhaseFailureCode::All_ConnectionHasGoneAway);
        return;
    }

    const TSharedPtr<const FUniqueNetId> &UserId = Context->GetUserId();
    if (!UserId.IsValid())
    {
        UE_LOG(LogRedpointEOSNetworkAuth, Warning, TEXT("Ignoring NMT_EOS_DeliverTrustedClientProof, missing UserId."));
        return;
    }

    EUserVerificationStatus VerificationStatus;
    if (Role != EEOSNetDriverRole::ClientConnectedToListenServer)
    {
        if (!Context->GetVerificationStatus(VerificationStatus))
        {
            Context->Finish(EAuthPhaseFailureCode::All_ConnectionHasGoneAway);
            return;
        }
    }
    else
    {
        // When clients receive this, they assume they're establishing the Anti-Cheat proof
        // with the listen server.
        VerificationStatus = EUserVerificationStatus::EstablishingAntiCheatProof;
    }
    if (VerificationStatus != EUserVerificationStatus::EstablishingAntiCheatProof)
    {
        UE_LOG(LogRedpointEOSNetworkAuth, Warning, TEXT("Ignoring NMT_EOS_DeliverTrustedClientProof, invalid UserId."));
        return;
    }

    TSharedPtr<IAntiCheat> AntiCheat;
    TSharedPtr<FAntiCheatSession> AntiCheatSession;
    bool bIsOwnedByBeacon;
    if (!Context->GetAntiCheat(AntiCheat, AntiCheatSession, bIsOwnedByBeacon))
    {
        Context->Finish(EAuthPhaseFailureCode::All_ConnectionHasGoneAway);
        return;
    }
    checkf(!bIsOwnedByBeacon, TEXT("Did not expect beacon connection to also negotiate Anti-Cheat."));
    if (!AntiCheat.IsValid() || !AntiCheatSession.IsValid())
    {
        UE_LOG(
            LogRedpointEOSNetworkAuth,
            Error,
            TEXT("Server authentication: %s: Failed to obtain Anti-Cheat interface or session."),
            *UserId->ToString());
        Context->Finish(EAuthPhaseFailureCode::All_CanNotAccessAntiCheat);
        return;
    }

    if (Config == nullptr)
    {
        UE_LOG(
            LogRedpointEOSNetworkAuth,
            Error,
            TEXT("Server authentication: %s: Unable to get configuration when verifying client proof."),
            *UserId->ToString());
        Context->Finish(EAuthPhaseFailureCode::All_CanNotAccessConfig);
        return;
    }

    EOS_EAntiCheatCommonClientType ClientType = EOS_EAntiCheatCommonClientType::EOS_ACCCT_ProtectedClient;
    EOS_EAntiCheatCommonClientPlatform ClientPlatform = EOS_EAntiCheatCommonClientPlatform::EOS_ACCCP_Unknown;
    if (bCanProvideProof)
    {
        bool bProofValid = false;
        FString TrustedClientPublicKey = Config->GetTrustedClientPublicKey();
        if (!TrustedClientPublicKey.IsEmpty())
        {
            TArray<uint8> TrustedClientPublicKeyBytes;
            if (FBase64::Decode(TrustedClientPublicKey, TrustedClientPublicKeyBytes) &&
                TrustedClientPublicKeyBytes.Num() == hydro_sign_PUBLICKEYBYTES)
            {
                TArray<uint8> PendingNonce;
                if (!this->PendingNonceCheck.IsEmpty() && FBase64::Decode(this->PendingNonceCheck, PendingNonce) &&
                    PendingNonce.Num() == hydro_sign_NONCEBYTES)
                {
                    TArray<uint8> Signature;
                    if (FBase64::Decode(EncodedProof, Signature))
                    {
                        if (Signature.Num() == hydro_sign_BYTES)
                        {
                            if (hydro_sign_verify(
                                    Signature.GetData(),
                                    PendingNonce.GetData(),
                                    PendingNonce.Num(),
                                    "TRSTPROF",
                                    TrustedClientPublicKeyBytes.GetData()) == 0)
                            {
                                bProofValid = true;
                            }
                            else
                            {
                                UE_LOG(
                                    LogRedpointEOSNetworkAuth,
                                    Error,
                                    TEXT("Server authentication: %s: hydro_sign_verify failed to verify the provided "
                                         "signature."),
                                    *UserId->ToString());
                            }
                        }
                        else
                        {
                            UE_LOG(
                                LogRedpointEOSNetworkAuth,
                                Error,
                                TEXT("Server authentication: %s: Provided signature from client was not the correct "
                                     "length."),
                                *UserId->ToString());
                        }
                    }
                    else
                    {
                        UE_LOG(
                            LogRedpointEOSNetworkAuth,
                            Error,
                            TEXT("Server authentication: %s: Server could not decode provided signature."),
                            *UserId->ToString());
                    }
                }
                else
                {
                    UE_LOG(
                        LogRedpointEOSNetworkAuth,
                        Error,
                        TEXT("Server authentication: %s: Server does not have a pending nonce or it is the incorrect "
                             "length."),
                        *UserId->ToString());
                }
            }
            else
            {
                UE_LOG(
                    LogRedpointEOSNetworkAuth,
                    Error,
                    TEXT("Server authentication: %s: Server does not have public key for trusted clients."),
                    *UserId->ToString());
            }
        }
        if (!bProofValid)
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Error,
                TEXT("Server authentication: %s: Invalid signature for unprotected client proof."),
                *UserId->ToString());
            Context->Finish(EAuthPhaseFailureCode::Phase_AntiCheatProof_InvalidSignatureForUnprotectedClient);
            return;
        }

        ClientType = EOS_EAntiCheatCommonClientType::EOS_ACCCT_UnprotectedClient;
        if (PlatformString == TEXT("Xbox"))
        {
            ClientPlatform = EOS_EAntiCheatCommonClientPlatform::EOS_ACCCP_Xbox;
        }
        else if (PlatformString == TEXT("PlayStation"))
        {
            ClientPlatform = EOS_EAntiCheatCommonClientPlatform::EOS_ACCCP_PlayStation;
        }
        else if (PlatformString == TEXT("Nintendo"))
        {
            ClientPlatform = EOS_EAntiCheatCommonClientPlatform::EOS_ACCCP_Nintendo;
        }
        else if (PlatformString == TEXT("Windows"))
        {
            ClientPlatform = EOS_EAntiCheatCommonClientPlatform::EOS_ACCCP_Windows;
        }
        else if (PlatformString == TEXT("Mac"))
        {
            ClientPlatform = EOS_EAntiCheatCommonClientPlatform::EOS_ACCCP_Mac;
        }
        else if (PlatformString == TEXT("Linux"))
        {
            ClientPlatform = EOS_EAntiCheatCommonClientPlatform::EOS_ACCCP_Linux;
        }
        else if (PlatformString == TEXT("Android"))
        {
            ClientPlatform = EOS_EAntiCheatCommonClientPlatform::EOS_ACCCP_Android;
        }
        else if (PlatformString == TEXT("IOS"))
        {
            ClientPlatform = EOS_EAntiCheatCommonClientPlatform::EOS_ACCCP_iOS;
        }
    }

    if (ClientType == EOS_EAntiCheatCommonClientType::EOS_ACCCT_ProtectedClient)
    {
        // Only trusted clients can skip peer registration.
        bSkipPeerRegistration = false;
    }

    UE_LOG(
        LogRedpointEOSNetworkAuth,
        Verbose,
        TEXT("Server authentication: %s: Received proof data from %s (%s)."),
        *UserId->ToString(),
        Role == EEOSNetDriverRole::ClientConnectedToListenServer ? TEXT("listen server") : TEXT("client"),
        ClientType == EOS_EAntiCheatCommonClientType::EOS_ACCCT_ProtectedClient
            ? TEXT("protected")
            : (bSkipPeerRegistration ? TEXT("skipped+trusted") : TEXT("unprotected+trusted")));

    if (Role != EEOSNetDriverRole::ClientConnectedToListenServer)
    {
        if (ClientType == EOS_EAntiCheatCommonClientType::EOS_ACCCT_ProtectedClient)
        {
            Context->SetVerificationStatus(EUserVerificationStatus::WaitingForAntiCheatIntegrity);
        }
        else
        {
            Context->SetVerificationStatus(EUserVerificationStatus::Verified);
        }
    }

    if (!bSkipPeerRegistration)
    {
        if (!AntiCheat->RegisterPlayer(*AntiCheatSession, (const FUniqueNetIdEOS &)*UserId, ClientType, ClientPlatform))
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Error,
                TEXT("Server authentication: %s: Failed to register player with Anti-Cheat."),
                *UserId->ToString());
            Context->Finish(EAuthPhaseFailureCode::Phase_AntiCheatProof_AntiCheatRegistrationFailed);
            return;
        }

        Context->MarkAsRegisteredForAntiCheat();
    }
    else
    {
        UE_LOG(
            LogRedpointEOSNetworkAuth,
            Verbose,
            TEXT("Server authentication: %s: Skipping peer registration because they're a trusted client and they can "
                 "not process network messages."),
            *UserId->ToString());
    }

    if (Role != EEOSNetDriverRole::ClientConnectedToListenServer)
    {
        if (bRequestMutualProofFromListenServer)
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Verbose,
                TEXT("Server authentication: %s: Registered player with Anti-Cheat. Remote client requested mutual "
                     "trusted client proof, sending proof if we have one."),
                *UserId->ToString());

            this->bWaitingForClientToAcceptOurProof = true;
            this->DeliverProofToPeer(Context, AntiCheat, Config, Connection, EncodedNonceForListenServer, OSS, false);

            // Now we must wait for On_NMT_EOS_AcceptedMutualTrustedClientProof.
        }
        else
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Verbose,
                TEXT("Server authentication: %s: Registered player with Anti-Cheat. Now waiting for Anti-Cheat "
                     "verification status."),
                *UserId->ToString());

            Context->Finish(EAuthPhaseFailureCode::Success);
        }
    }
    else
    {
        if (ClientType == EOS_EAntiCheatCommonClientType::EOS_ACCCT_ProtectedClient)
        {
            // The listen server is a protected client. Wait until OnAntiCheatPlayerAuthStatusChanged
            // fires before we send EOS_AcceptedMutualTrustedClientProof.
        }
        else
        {
            // The listen server is an unprotected trusted client. We immediately accept their proof
            // and don't wait for EAC events.
            if (!this->bReceivedRemoteAuthForListenServerFromClient)
            {
                UE_LOG(
                    LogRedpointEOSNetworkAuth,
                    Verbose,
                    TEXT("Server authentication: %s: Notifying the listen server that we now trust them (as a trusted "
                         "client)."),
                    *Context->GetUserId()->ToString());
                this->bReceivedRemoteAuthForListenServerFromClient = true;
                FUniqueNetIdRepl TargetUserId = FUniqueNetIdRepl(*Context->GetUserId());
                FNetControlMessage<NMT_EOS_AcceptedMutualTrustedClientProof>::Send(Connection, TargetUserId);
            }
        }
    }
}

void FAntiCheatProofPhase::On_NMT_EOS_AcceptedMutualTrustedClientProof(
    const TSharedRef<FAuthLoginPhaseContext> &Context)
{
    EEOSNetDriverRole Role;
    if (!Context->GetRole(Role) || Role != EEOSNetDriverRole::ListenServer)
    {
        Context->Finish(EAuthPhaseFailureCode::All_InvalidMessageType);
        return;
    }
    if (!this->bWaitingForClientToAcceptOurProof)
    {
        Context->Finish(EAuthPhaseFailureCode::All_InvalidMessageType);
        return;
    }

    const TSharedPtr<const FUniqueNetId> &UserId = Context->GetUserId();
    UE_LOG(
        LogRedpointEOSNetworkAuth,
        Verbose,
        TEXT("Server authentication: %s: Client accepted our listen server trusted client proof. Continuing with "
             "network authentication."),
        *UserId->ToString());

    Context->Finish(EAuthPhaseFailureCode::Success);
}

void FAntiCheatProofPhase::OnAntiCheatPlayerAuthStatusChanged(
    const TSharedRef<FAuthLoginPhaseContext> &Context,
    EOS_EAntiCheatCommonClientAuthStatus NewAuthStatus)
{
    EEOSNetDriverRole Role;
    if (!Context->GetRole(Role) || Role != EEOSNetDriverRole::ClientConnectedToListenServer)
    {
        // Just silently drop events here, in case we receive them but don't care about them.
        return;
    }
    UNetConnection *Connection;
    if (!Context->GetConnection(Connection))
    {
        Context->Finish(EAuthPhaseFailureCode::All_ConnectionHasGoneAway);
        return;
    }

    FString StatusStr = TEXT("Unknown");
    if (NewAuthStatus == EOS_EAntiCheatCommonClientAuthStatus::EOS_ACCCAS_Invalid)
    {
        StatusStr = TEXT("Invalid");
    }
    else if (NewAuthStatus == EOS_EAntiCheatCommonClientAuthStatus::EOS_ACCCAS_LocalAuthComplete)
    {
        StatusStr = TEXT("LocalAuthComplete");
    }
    else if (NewAuthStatus == EOS_EAntiCheatCommonClientAuthStatus::EOS_ACCCAS_RemoteAuthComplete)
    {
        StatusStr = TEXT("RemoteAuthComplete");
    }

    UE_LOG(
        LogRedpointEOSNetworkAuth,
        Verbose,
        TEXT("Server authentication: %s: Anti-Cheat verification status of remote listen server is now '%s'."),
        *Context->GetUserId()->ToString(),
        *StatusStr);

    if (NewAuthStatus == EOS_EAntiCheatCommonClientAuthStatus::EOS_ACCCAS_RemoteAuthComplete)
    {
        if (!this->bReceivedRemoteAuthForListenServerFromClient)
        {
            UE_LOG(
                LogRedpointEOSNetworkAuth,
                Verbose,
                TEXT("Server authentication: %s: Notifying the listen server that we now trust them (as a protected "
                     "client)."),
                *Context->GetUserId()->ToString());
            this->bReceivedRemoteAuthForListenServerFromClient = true;
            FUniqueNetIdRepl TargetUserId = FUniqueNetIdRepl(*Context->GetUserId());
            FNetControlMessage<NMT_EOS_AcceptedMutualTrustedClientProof>::Send(Connection, TargetUserId);
        }
    }
}

#undef hydro_sign_NONCEBYTES
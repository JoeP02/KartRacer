// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemRedpointEOS/Shared/EOSCommon.h"

#if WITH_EDITOR
#include "Modules/ModuleManager.h"
#include "OnlineSubsystemRedpointEOS/Public/OnlineSubsystemRedpointEOSModule.h"
#endif

EOS_ENABLE_STRICT_WARNINGS

DEFINE_LOG_CATEGORY(LogRedpointEOSIdentity);
DEFINE_LOG_CATEGORY(LogRedpointEOSSocket);
DEFINE_LOG_CATEGORY(LogRedpointEOSSocketLifecycle);
DEFINE_LOG_CATEGORY(LogRedpointEOSSessionListening);
DEFINE_LOG_CATEGORY(LogRedpointEOSNetworkTrace);
DEFINE_LOG_CATEGORY(LogRedpointEOSNetworkAuth);
DEFINE_LOG_CATEGORY(LogRedpointEOSStat);
DEFINE_LOG_CATEGORY(LogRedpointEOSAntiCheat);
DEFINE_LOG_CATEGORY(LogRedpointEOSFriends);
DEFINE_LOG_CATEGORY(LogRedpointEOSFileTransfer);
DEFINE_LOG_CATEGORY(LogRedpointEOSVoiceChat);
DEFINE_LOG_CATEGORY(LogRedpointEOSCloudMessagingHub);
#if defined(EOS_IS_FREE_EDITION)
DEFINE_LOG_CATEGORY(LogRedpointEOSLicenseValidation);
#endif

DEFINE_STAT(STAT_EOSIdentifiableCallbackDispatcher);

#if defined(EOS_ENABLE_TRACE)
DEFINE_STAT(STAT_EOSOpInvoke);
DEFINE_STAT(STAT_EOSOpCallback);
DEFINE_STAT(STAT_EOSOpKeepAliveInvoke);
DEFINE_STAT(STAT_EOSOpKeepAliveCallback);
DEFINE_STAT(STAT_EOSEvRegister);
DEFINE_STAT(STAT_EOSEvCallback);
DEFINE_STAT(STAT_EOSEvDeregister);

DEFINE_STAT(STAT_EOSOnlineSubsystemInit);
DEFINE_STAT(STAT_EOSOnlineSubsystemTick);
DEFINE_STAT(STAT_EOSOnlineSubsystemShutdown);

DEFINE_STAT(STAT_EOSNetDriverTickDispatch);
DEFINE_STAT(STAT_EOSNetDriverBaseTickDispatch);
DEFINE_STAT(STAT_EOSNetDriverOnIncomingConnection);
DEFINE_STAT(STAT_EOSNetDriverOnConnectionAccepted);
DEFINE_STAT(STAT_EOSNetDriverOnConnectionClosed);
DEFINE_STAT(STAT_EOSNetDriverInitConnect);
DEFINE_STAT(STAT_EOSNetDriverInitListen);

DEFINE_STAT(STAT_EOSSocketRecvFrom);
DEFINE_STAT(STAT_EOSSocketHasPendingData);
DEFINE_STAT(STAT_EOSSocketSendTo);

DEFINE_STAT(STAT_EOSVoiceChatSyncPerformDeferredSynchronisation);
DEFINE_STAT(STAT_EOSVoiceChatUserSyncScheduleSynchronisation);
DEFINE_STAT(STAT_EOSVoiceChatUserSyncPerformSynchronisation);
DEFINE_STAT(STAT_EOSVoiceChatApiSetAudioInputVolume);

DEFINE_STAT(STAT_EOSNetP2PReceivedLoopIters);
DEFINE_STAT(STAT_EOSNetP2PReceivedPackets);
DEFINE_STAT(STAT_EOSNetP2PReceivedBytes);
DEFINE_STAT(STAT_EOSNetP2PSentPackets);
DEFINE_STAT(STAT_EOSNetP2PSentBytes);
TRACE_DECLARE_INT_COUNTER(CTR_EOSNetP2PReceivedLoopIters, TEXT("EOS/P2P/ReceivedLoopIters"));
TRACE_DECLARE_INT_COUNTER(CTR_EOSNetP2PReceivedPackets, TEXT("EOS/P2P/ReceivedPackets"));
TRACE_DECLARE_INT_COUNTER(CTR_EOSNetP2PReceivedBytes, TEXT("EOS/P2P/ReceivedBytes"));
TRACE_DECLARE_INT_COUNTER(CTR_EOSNetP2PSentPackets, TEXT("EOS/P2P/SentPackets"));
TRACE_DECLARE_INT_COUNTER(CTR_EOSNetP2PSentBytes, TEXT("EOS/P2P/SentBytes"));
#endif

void EOSSendCustomEditorSignal(const FString &Context, const FString &SignalId)
{
#if WITH_EDITOR
    FModuleManager &ModuleManager = FModuleManager::Get();
    auto RuntimeModule = (FOnlineSubsystemRedpointEOSModule *)ModuleManager.GetModule("OnlineSubsystemRedpointEOS");
    if (RuntimeModule != nullptr)
    {
        RuntimeModule->SendCustomSignal(Context, SignalId);
    }
#endif
}

EOS_DISABLE_STRICT_WARNINGS
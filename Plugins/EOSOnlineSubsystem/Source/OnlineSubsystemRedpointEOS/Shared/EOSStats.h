// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProfilingDebugging/CountersTrace.h"
#include "Stats/Stats.h"

#include "RedpointEOSAPI/Stats.h"

// @todo: The rest of this file should be moved out. We should no longer have a EOS_ENABLE_TRACE
// macro, since it's redundant as stats get compiled out in shipping anyway.

DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/IdentifiableCallbackDispatcher"),
    STAT_EOSIdentifiableCallbackDispatcher,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);

#if defined(EOS_ENABLE_TRACE)
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/RunOperation/Invoke"),
    STAT_EOSOpInvoke,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/RunOperation/Callback"),
    STAT_EOSOpCallback,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/RunOperationKeepAlive/Invoke"),
    STAT_EOSOpKeepAliveInvoke,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/RunOperationKeepAlive/Callback"),
    STAT_EOSOpKeepAliveCallback,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/RegisterEvent/Register"),
    STAT_EOSEvRegister,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/RegisterEvent/Callback"),
    STAT_EOSEvCallback,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/RegisterEvent/Deregister"),
    STAT_EOSEvDeregister,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);

DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/OnlineSubsystem/Init"),
    STAT_EOSOnlineSubsystemInit,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/OnlineSubsystem/Tick"),
    STAT_EOSOnlineSubsystemTick,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/OnlineSubsystem/Shutdown"),
    STAT_EOSOnlineSubsystemShutdown,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);

DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/NetDriver/TickDispatch"),
    STAT_EOSNetDriverTickDispatch,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/NetDriver/BaseTickDispatch"),
    STAT_EOSNetDriverBaseTickDispatch,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/NetDriver/OnIncomingConnection"),
    STAT_EOSNetDriverOnIncomingConnection,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/NetDriver/OnConnectionAccepted"),
    STAT_EOSNetDriverOnConnectionAccepted,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/NetDriver/OnConnectionClosed"),
    STAT_EOSNetDriverOnConnectionClosed,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/NetDriver/InitConnect"),
    STAT_EOSNetDriverInitConnect,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/NetDriver/InitListen"),
    STAT_EOSNetDriverInitListen,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);

DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/Socket/RecvFrom"),
    STAT_EOSSocketRecvFrom,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/Socket/HasPendingData"),
    STAT_EOSSocketHasPendingData,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/Socket/SendTo"),
    STAT_EOSSocketSendTo,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);

DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChat/Tasks/SetAudioInputSettings"),
    STAT_EOSVoiceChatTasksSetAudioInputSettings,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChat/Tasks/SetAudioOutputSettings"),
    STAT_EOSVoiceChatTasksSetAudioOutputSettings,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChat/Tasks/UpdateSending"),
    STAT_EOSVoiceChatTasksUpdateSending,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChat/Tasks/UpdateSending/Callback"),
    STAT_EOSVoiceChatTasksUpdateSendingCallback,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChat/Sync/PerformDeferredSynchronisation"),
    STAT_EOSVoiceChatSyncPerformDeferredSynchronisation,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChatUser/Sync/ScheduleSynchronisation"),
    STAT_EOSVoiceChatUserSyncScheduleSynchronisation,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChatUser/Sync/PerformSynchronisation"),
    STAT_EOSVoiceChatUserSyncPerformSynchronisation,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChatUser/Api/SetAudioInputVolume"),
    STAT_EOSVoiceChatApiSetAudioInputVolume,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChatUser/Api/GetAvailableInputDeviceInfos"),
    STAT_EOSVoiceChatApiGetAvailableInputDeviceInfos,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChatUser/Api/GetAvailableInputDeviceInfos/EOS_RTCAudio_GetAudioInputDevicesCount"),
    STAT_EOSVoiceChatApiGetAvailableInputDeviceInfos_EOS_RTCAudio_GetAudioInputDevicesCount,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChatUser/Api/GetAvailableInputDeviceInfos/EOS_RTCAudio_GetAudioInputDeviceByIndex"),
    STAT_EOSVoiceChatApiGetAvailableInputDeviceInfos_EOS_RTCAudio_GetAudioInputDeviceByIndex,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChatUser/Api/GetAvailableOutputDeviceInfos"),
    STAT_EOSVoiceChatApiGetAvailableOutputDeviceInfos,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChatUser/Api/GetAvailableOutputDeviceInfos/EOS_RTCAudio_GetAudioOutputDevicesCount"),
    STAT_EOSVoiceChatApiGetAvailableOutputDeviceInfos_EOS_RTCAudio_GetAudioOutputDevicesCount,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_CYCLE_STAT_EXTERN(
    TEXT("RedpointEOS/VoiceChatUser/Api/GetAvailableOutputDeviceInfos/EOS_RTCAudio_GetAudioOutputDeviceByIndex"),
    STAT_EOSVoiceChatApiGetAvailableOutputDeviceInfos_EOS_RTCAudio_GetAudioOutputDeviceByIndex,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);

DECLARE_DWORD_COUNTER_STAT_EXTERN(
    TEXT("RedpointEOS/P2P/ReceivedLoopIters"),
    STAT_EOSNetP2PReceivedLoopIters,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_DWORD_COUNTER_STAT_EXTERN(
    TEXT("RedpointEOS/P2P/ReceivedPackets"),
    STAT_EOSNetP2PReceivedPackets,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_DWORD_COUNTER_STAT_EXTERN(
    TEXT("RedpointEOS/P2P/ReceivedBytes"),
    STAT_EOSNetP2PReceivedBytes,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_DWORD_COUNTER_STAT_EXTERN(
    TEXT("RedpointEOS/P2P/SentPackets"),
    STAT_EOSNetP2PSentPackets,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_DWORD_COUNTER_STAT_EXTERN(
    TEXT("RedpointEOS/P2P/SentBytes"),
    STAT_EOSNetP2PSentBytes,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
DECLARE_DWORD_COUNTER_STAT_EXTERN(
    TEXT("RedpointEOS/RegulatedTicks/InvocationsLastSecond"),
    STAT_EOSRegulatedTicksInvocationsLastSecond,
    STATGROUP_RedpointEOS,
    ONLINESUBSYSTEMREDPOINTEOS_API);
TRACE_DECLARE_INT_COUNTER_EXTERN(CTR_EOSNetP2PReceivedLoopIters);
TRACE_DECLARE_INT_COUNTER_EXTERN(CTR_EOSNetP2PReceivedPackets);
TRACE_DECLARE_INT_COUNTER_EXTERN(CTR_EOSNetP2PReceivedBytes);
TRACE_DECLARE_INT_COUNTER_EXTERN(CTR_EOSNetP2PSentPackets);
TRACE_DECLARE_INT_COUNTER_EXTERN(CTR_EOSNetP2PSentBytes);

// Deprecated trace usage macros.
#define EOS_SCOPE_CYCLE_COUNTER(StatName)                                                                              \
    SCOPE_CYCLE_COUNTER(StatName)
#define EOS_TRACE_COUNTER_SET(Ctr, CtrValue)                                                                           \
    TRACE_COUNTER_SET(Ctr, CtrValue)
#define EOS_TRACE_COUNTER_INCREMENT(Ctr)                                                                               \
    TRACE_COUNTER_INCREMENT(Ctr)
#define EOS_TRACE_COUNTER_ADD(Ctr, CtrValue)                                                                           \
    TRACE_COUNTER_ADD(Ctr, CtrValue)
#define EOS_INC_DWORD_STAT(StatName)                                                                                   \
    INC_DWORD_STAT(StatName)
#define EOS_INC_DWORD_STAT_BY(StatName, StatValue)                                                                     \
    INC_DWORD_STAT_BY(StatName, StatValue)
#else
// Deprecated trace usage macros.
#define EOS_SCOPE_CYCLE_COUNTER(StatName)
#define EOS_TRACE_COUNTER_SET(Ctr, CtrValue)
#define EOS_TRACE_COUNTER_INCREMENT(Ctr)
#define EOS_TRACE_COUNTER_ADD(Ctr, CtrValue)
#define EOS_INC_DWORD_STAT(StatName)
#define EOS_INC_DWORD_STAT_BY(StatName, StatValue)
#endif
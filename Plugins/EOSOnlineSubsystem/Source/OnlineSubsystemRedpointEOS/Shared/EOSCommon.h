// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSDefines.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSStats.h"
#include <functional>
#include <limits>
#include "RedpointEOSAPI/SDK.h"
#include "RedpointEOSCore/Logging.h"

EOS_ENABLE_STRICT_WARNINGS

#if defined(EOS_SUBSYSTEM)
#undef EOS_SUBSYSTEM
#endif
#define REDPOINT_EOS_SUBSYSTEM FName(TEXT("RedpointEOS"))
#define REDPOINT_EAS_SUBSYSTEM FName(TEXT("RedpointEAS"))

// Used as the type for unique net IDs of EOS sessions (not users).
#define REDPOINT_EOS_SUBSYSTEM_SESSION FName(TEXT("RedpointEOS.Session"))

#define EOS_CHANNEL_ID_TYPE uint8
// We add one here because to get a range of numbers between e.g. 0 - 15 you would need to modulo by 16.
// We subtract one here because we use channel 255 as a control channel to reset sockets when a channel during
// re-connects (where a full disconnected through EOS_P2P_CloseConnection did not happen because other sockets kept the
// main connection alive).
#define EOS_CHANNEL_ID_MODULO (std::numeric_limits<EOS_CHANNEL_ID_TYPE>().max() + 1 - 1)
#define EOS_CHANNEL_ID_CONTROL (std::numeric_limits<EOS_CHANNEL_ID_TYPE>().max())

#ifndef EOS_P2P_SOCKET_NAME_MAX_LENGTH
#define EOS_P2P_SOCKET_NAME_MAX_LENGTH 32
#endif

#define INTERNET_ADDR_EOS_P2P_DOMAIN_SUFFIX TEXT("eosp2p")

#if PLATFORM_ANDROID
#define __CDECL_ATTR
#else
#define __CDECL_ATTR __cdecl
#endif

ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSIdentity, Verbose, Verbose);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSSocket, Warning, Verbose);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSSocketLifecycle, Warning, Verbose);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSSessionListening, Verbose, All);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSNetworkTrace, Verbose, All);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSNetworkAuth, Verbose, All);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSStat, Warning, Verbose);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSAntiCheat, Verbose, All);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSFriends, Warning, VeryVerbose);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSFileTransfer, Warning, Verbose);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSVoiceChat, Warning, Verbose);
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSCloudMessagingHub, Verbose, All);
#if defined(EOS_IS_FREE_EDITION)
ONLINESUBSYSTEMREDPOINTEOS_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSLicenseValidation, All, All);
#endif

// The _MAX_LENGTH definitions in the SDK do not include the null terminator, but both the buffer and the
// length you pass into functions such as () must include the null terminator
// in their length (it's not enough to just add one when allocating the destination array, and then pass
// EOS_EPICACCOUNTID_MAX_LENGTH into EOS_EpicAccountId_ToString; you have to add one in both places). To make
// things easier, we define a _MAX_BUFFER_LEN for all of these _MAX_LENGTH values that include the null
// terminator, and then we use these definitions instead.
#define EOS_CONNECT_EXTERNAL_ACCOUNT_ID_MAX_BUFFER_LEN (EOS_CONNECT_EXTERNAL_ACCOUNT_ID_MAX_LENGTH + 1)
#define EOS_CONNECT_USERLOGININFO_DISPLAYNAME_MAX_BUFFER_LEN (EOS_CONNECT_USERLOGININFO_DISPLAYNAME_MAX_LENGTH + 1)
#define EOS_CONNECT_CREATEDEVICEID_DEVICEMODEL_MAX_BUFFER_LEN (EOS_CONNECT_CREATEDEVICEID_DEVICEMODEL_MAX_LENGTH + 1)
#define EOS_LOBBY_INVITEID_MAX_BUFFER_LEN (EOS_LOBBY_INVITEID_MAX_LENGTH + 1)
#define EOS_PLAYERDATASTORAGE_FILENAME_MAX_BUFFER_BYTES_LEN (EOS_PLAYERDATASTORAGE_FILENAME_MAX_LENGTH_BYTES + 1)
#define EOS_PRESENCEMODIFICATION_JOININFO_MAX_BUFFER_LEN (EOS_PRESENCEMODIFICATION_JOININFO_MAX_LENGTH + 1)
#define EOS_SESSIONS_INVITEID_MAX_BUFFER_LEN (EOS_SESSIONS_INVITEID_MAX_LENGTH + 1)
#define EOS_TITLESTORAGE_FILENAME_MAX_BUFFER_BYTES_LEN (EOS_TITLESTORAGE_FILENAME_MAX_LENGTH_BYTES + 1)

/**
 * Runs an EOS SDK operation with the specified callback. This helper handles the mess of moving
 * a lambda to the heap, passing it's pointer through the ClientData and freeing the lambda after
 * the callback has run.
 */
template <typename TInter, typename TOpts, typename TResult>
void EOSRunOperation(
    TInter Inter,
    const TOpts *Opts,
    std::function<void(TInter, const TOpts *, void *, void(__CDECL_ATTR *)(const TResult *))> Op,
    std::function<void(const TResult *)> Callback)
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSOpInvoke);

    std::function<void(const TResult *)> *CallbackOnHeap =
        new std::function<void(const TResult *)>(std::move(Callback));

    Op(Inter, Opts, CallbackOnHeap, [](const TResult *Data) {
        EOS_SCOPE_CYCLE_COUNTER(STAT_EOSOpCallback);

        if (!EOS_EResult_IsOperationComplete(Data->ResultCode))
        {
            UE_LOG(
                LogRedpointEOS,
                Warning,
                TEXT("EOSRunOperation got non-complete result status of %s, deferring callback."),
                ANSI_TO_TCHAR(EOS_EResult_ToString(Data->ResultCode)));
            return;
        }

        auto CallbackOnHeap = (std::function<void(const TResult *)> *)Data->ClientData;
        (*CallbackOnHeap)(Data);
        delete CallbackOnHeap;
    });
};

/**
 * A variant of EOSRunOperation that handles operations that take non-const Options. This appears to be the case for
 * some RTC operations.
 */
template <typename TInter, typename TOpts, typename TResult>
void EOSRunOperation(
    TInter Inter,
    TOpts *Opts,
    std::function<void(TInter, TOpts *, void *, void(__CDECL_ATTR *)(const TResult *))> Op,
    std::function<void(const TResult *)> Callback)
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSOpInvoke);

    std::function<void(const TResult *)> *CallbackOnHeap =
        new std::function<void(const TResult *)>(std::move(Callback));

    Op(Inter, Opts, CallbackOnHeap, [](const TResult *Data) {
        EOS_SCOPE_CYCLE_COUNTER(STAT_EOSOpCallback);

        if (!EOS_EResult_IsOperationComplete(Data->ResultCode))
        {
            UE_LOG(
                LogRedpointEOS,
                Warning,
                TEXT("EOSRunOperation got non-complete result status of %s, deferring callback."),
                ANSI_TO_TCHAR(EOS_EResult_ToString(Data->ResultCode)));
            return;
        }

        auto CallbackOnHeap = (std::function<void(const TResult *)> *)Data->ClientData;
        (*CallbackOnHeap)(Data);
        delete CallbackOnHeap;
    });
};

/**
 * A variant of EOSRunOperation that allows you to keep the callback alive if you know
 * the SDK will call it again. Used by EOS_Auth_Login when handling device codes.
 */
template <typename TInter, typename TOpts, typename TResult>
void EOSRunOperationKeepAlive(
    TInter Inter,
    const TOpts *Opts,
    std::function<void(TInter, const TOpts *, void *, void(__CDECL_ATTR *)(const TResult *))> Op,
    std::function<void(const TResult *, bool &)> Callback)
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSOpKeepAliveInvoke);

    std::function<void(const TResult *, bool &)> *CallbackOnHeap =
        new std::function<void(const TResult *, bool &)>(std::move(Callback));

    Op(Inter, Opts, CallbackOnHeap, [](const TResult *Data) {
        EOS_SCOPE_CYCLE_COUNTER(STAT_EOSOpKeepAliveCallback);

        if (!EOS_EResult_IsOperationComplete(Data->ResultCode) &&
            Data->ResultCode != EOS_EResult::EOS_Auth_PinGrantCode)
        {
            UE_LOG(
                LogRedpointEOS,
                Warning,
                TEXT("EOSRunOperationKeepAlive got non-complete result status of %s, deferring callback."),
                ANSI_TO_TCHAR(EOS_EResult_ToString(Data->ResultCode)));
            return;
        }

        bool KeepAlive = false;
        auto CallbackOnHeap = (std::function<void(const TResult *, bool &)> *)Data->ClientData;
        (*CallbackOnHeap)(Data, KeepAlive);
        if (!KeepAlive)
        {
            delete CallbackOnHeap;
        }
    });
};

/**
 * An EOS event handle that wraps EOS_NotificationId and handles deregistering events when
 * the EOS handle is destructed (due to no more shared pointer references).
 */
template <typename TResult> class EOSEventHandle : public TSharedFromThis<EOSEventHandle<TResult>>
{
private:
    std::function<void()> DeregisterEvent;
    std::function<void(const TResult *)> Callback;
    EOS_NotificationId NotificationId;

public:
    UE_NONCOPYABLE(EOSEventHandle);
    EOSEventHandle(std::function<void(const TResult *)> InCallback)
        : DeregisterEvent([]() {
        })
        , Callback(InCallback)
        , NotificationId(EOS_INVALID_NOTIFICATIONID){};
    ~EOSEventHandle()
    {
        // Note: If you are getting a crash in this code, it's most likely because the underlying EOS_HPlatform
        // has been released (because the online subsystem has been released), even though there were still
        // events registered.
        //
        // You should ensure that any objects that are using events have a chain of shared pointers that can
        // be traced from the object that registered the event up to the online subsystem. This will ensure
        // that the object with the event registered will prevent the online subsystem from being destroyed
        // (or more accurately, the online subsystem check() will fail because there are still alive objects,
        // and then you can go and fix up the code to clean up the objects that still have events registered).

        if (this->NotificationId != EOS_INVALID_NOTIFICATIONID)
        {
            // Only call deregister event if the notification ID is valid.
            this->DeregisterEvent();
        }
        this->NotificationId = EOS_INVALID_NOTIFICATIONID;
    }
    void SetNotificationId(EOS_NotificationId InNotificationId)
    {
        check(this->NotificationId == EOS_INVALID_NOTIFICATIONID);
        this->NotificationId = InNotificationId;
    }
    void SetDeregisterEvent(const std::function<void()> &InDeregisterEvent)
    {
        this->DeregisterEvent = InDeregisterEvent;
    }
    void RunCallback(const TResult *Data)
    {
        this->Callback(Data);
    }
    bool IsValid()
    {
        return this->NotificationId != EOS_INVALID_NOTIFICATIONID;
    }
};

/**
 * Registers a new EOS event handler in the SDK, and returns the event handle. The event will be
 * automatically deregistered when there are no more references to the event handle.
 */
template <typename TInter, typename TAddOpts, typename TResult>
TSharedPtr<EOSEventHandle<TResult>> EOSRegisterEvent(
    TInter Inter,
    const TAddOpts *AddOpts,
    std::function<EOS_NotificationId(TInter Inter, const TAddOpts *Opts, void *, void(__CDECL_ATTR *)(const TResult *))>
        Register,
    std::function<void(TInter Inter, EOS_NotificationId InId)> Deregister,
    std::function<void(const TResult *)> Callback)
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSEvRegister);

    TSharedPtr<EOSEventHandle<TResult>> EventHandle = MakeShared<EOSEventHandle<TResult>>(Callback);

    auto NotificationId = Register(Inter, AddOpts, EventHandle.Get(), [](const TResult *Data) {
        EOS_SCOPE_CYCLE_COUNTER(STAT_EOSEvCallback);

        TSharedRef<EOSEventHandle<TResult>> EventHandleLoaded =
            ((EOSEventHandle<TResult> *)Data->ClientData)->AsShared();
        EventHandleLoaded->RunCallback(Data);
    });
    EventHandle->SetNotificationId(NotificationId);
    EventHandle->SetDeregisterEvent([Deregister, Inter, NotificationId]() {
        EOS_SCOPE_CYCLE_COUNTER(STAT_EOSEvDeregister);

        Deregister(Inter, NotificationId);
    });

    return EventHandle;
}

/**
 * A variant of EOSRegisterEvent that handles operations that take non-const Options. This appears to be the case for
 * some RTC operations.
 */
template <typename TInter, typename TAddOpts, typename TResult>
TSharedPtr<EOSEventHandle<TResult>> EOSRegisterEvent(
    TInter Inter,
    TAddOpts *AddOpts,
    std::function<EOS_NotificationId(TInter Inter, TAddOpts *Opts, void *, void(__CDECL_ATTR *)(const TResult *))>
        Register,
    std::function<void(TInter Inter, EOS_NotificationId InId)> Deregister,
    std::function<void(const TResult *)> Callback)
{
    EOS_SCOPE_CYCLE_COUNTER(STAT_EOSEvRegister);

    TSharedPtr<EOSEventHandle<TResult>> EventHandle = MakeShared<EOSEventHandle<TResult>>(Callback);

    auto NotificationId = Register(Inter, AddOpts, EventHandle.Get(), [](const TResult *Data) {
        EOS_SCOPE_CYCLE_COUNTER(STAT_EOSEvCallback);

        TSharedRef<EOSEventHandle<TResult>> EventHandleLoaded =
            ((EOSEventHandle<TResult> *)Data->ClientData)->AsShared();
        EventHandleLoaded->RunCallback(Data);
    });
    EventHandle->SetNotificationId(NotificationId);
    EventHandle->SetDeregisterEvent([Deregister, Inter, NotificationId]() {
        EOS_SCOPE_CYCLE_COUNTER(STAT_EOSEvDeregister);

        Deregister(Inter, NotificationId);
    });

    return EventHandle;
}

ONLINESUBSYSTEMREDPOINTEOS_API void EOSSendCustomEditorSignal(const FString &Context, const FString &SignalId);

EOS_DISABLE_STRICT_WARNINGS
// Copyright June Rhodes 2023. All Rights Reserved.

#include "AutoSubsystems/OnlineGameActivitySubsystem.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemBlueprintsModule.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"

FName UOnlineGameActivitySubsystem::OSSNameToAssignDuringConstruction = NAME_Default;

TSharedPtr<class IOnlineGameActivity, ESPMode::ThreadSafe> UOnlineGameActivitySubsystem::GetHandle()
{
    if (this->HasAnyFlags(RF_BeginDestroyed))
    {
        auto BDCheck_GameInstance = this->GetGameInstance();
        check(IsValid(BDCheck_GameInstance));
    
        auto BDCheck_World = BDCheck_GameInstance->GetWorld();
        auto BDCheck_Pinned = this->HandleWk.Pin();

        if ((BDCheck_Pinned == nullptr || !BDCheck_Pinned.IsValid()) && !IsValid(BDCheck_World))
        {
            // The world and associated online subsystem interfaces have already been cleaned up.
            // The only caller of GetHandle() in this context is event deregistration, which doesn't
            // need to be done if the online subsystem itself is already gone.
            return nullptr;
        }
    }

    auto GameInstance = this->GetGameInstance();
    check(IsValid(GameInstance));

    auto World = GameInstance->GetWorld();
    if (World == nullptr)
    {
        // The world has already been freed; this GetHandle call might be happening in a callback
        // (where it is already handled as a "CallFailed" if GetHandle returns a nullptr).
        return nullptr;
    }

    auto CurrentWorldContext = GEngine->GetWorldContextFromWorld(World);
    if (CurrentWorldContext == nullptr ||
        !CurrentWorldContext->ContextHandle.IsEqual(this->WorldContext->ContextHandle))
    {
        // There is no world context for the current world. This can happen during
        // play-in-editor shutdown when using voice.
        return nullptr;
    }

    TSharedPtr<class IOnlineGameActivity, ESPMode::ThreadSafe> Pinned = this->HandleWk.Pin();
    if (Pinned == nullptr || !Pinned.IsValid())
    {
        // Even though Online::GetSubsystem takes a UWorld* as it's argument, it only ever uses it
        // to get the world context, so that it can provide a different online subsystem per
        // play-in-editor context.
        //
        // There's one UGameInstance* per play-in-editor context, which also means game instance
        // subsystems get created per play-in-editor context. In contrast, the UWorld* gets reused
        // between contexts, which means that if we inherited from UWorldSubsystem, our lifetime
        // would span contexts and in turn make accessing the correct online subsystem instance
        // much harder.
        //
        // So we get the UWorld* of the UGameInstance*, which will be the same UWorld that's shared
        // between all other instances, but we'll have the right FWorldContext
        IOnlineSubsystem* Subsystem = nullptr;
        if (this->OSSName.IsEqual(NAME_Default))
        {
            Subsystem = Online::GetSubsystem(World);
        }
        else if (this->OSSName.IsEqual(FName(TEXT("Native"))))
        {
            Subsystem = IOnlineSubsystem::GetByPlatform();
        }
        else
        {
            Subsystem = Online::GetSubsystem(World, this->OSSName);
        }
        if (Subsystem == nullptr)
        {
            // No subsystem is available.
            return nullptr;
        }
        
        // Finish setup, store the reference to the interface.
        auto __Handle__ = Subsystem->GetGameActivityInterface();
        this->HandleWk = __Handle__;
        Pinned = __Handle__;
    }

    return Pinned;
}

bool UOnlineGameActivitySubsystem::IsHandleValid(const TSharedPtr<class IOnlineGameActivity, ESPMode::ThreadSafe>& InHandle)
{
    return InHandle.IsValid();
}

UOnlineGameActivitySubsystem::UOnlineGameActivitySubsystem()
{
    if (this->HasAnyFlags(RF_ClassDefaultObject))
    {
        return;
    }

    this->OSSName = UOnlineGameActivitySubsystem::OSSNameToAssignDuringConstruction;
    UOnlineGameActivitySubsystem::OSSNameToAssignDuringConstruction = NAME_Default;

    auto GameInstance = this->GetGameInstance();
    check(IsValid(GameInstance));

    auto World = GameInstance->GetWorld();
    check(IsValid(World));
    
    // Store the WorldContext so we can assert that it never changes later during our
    // operation (required for semantic correctness).
    this->WorldContext = GEngine->GetWorldContextFromWorld(World);
    check(WorldContext != nullptr);
    UE_LOG(LogOnlineBlueprint, Verbose, TEXT("OnlineGameActivitySubsystem subsystem initialized in context %s"), *WorldContext->ContextHandle.ToString());

    // Perform the initial cache of the online subsystem pointer. Calling GetHandle()
    // is enough to cache the weak pointer.
    this->HandleWk = nullptr;
    this->GetHandle();

    // Now, register events.
    
    TSharedPtr<class IOnlineGameActivity, ESPMode::ThreadSafe> Handle = this->GetHandle();
    if (Handle.IsValid())
    {
        for (auto i = 0; i < MAX_LOCAL_PLAYERS; i++)
        {
        }
        this->DelegateHandle_OnGameActivityActivationRequested = Handle->AddOnGameActivityActivationRequestedDelegate_Handle(
            FOnGameActivityActivationRequested::FDelegate::CreateWeakLambda(this, [this](const FUniqueNetId& LocalUserId, const FString& ActivityId, const FOnlineSessionSearchResult* SessionInfo) {
                this->OnGameActivityActivationRequested.Broadcast(ConvertDangerousUniqueNetIdToRepl(LocalUserId), ActivityId, FOptionalOnlineSessionSearchResultBP::FromNative(SessionInfo));
            })
        );
    }
}

void UOnlineGameActivitySubsystem::BeginDestroy()
{
    if (this->HasAnyFlags(RF_ClassDefaultObject))
    {
        Super::BeginDestroy();
        return;
    }

    TSharedPtr<class IOnlineGameActivity, ESPMode::ThreadSafe> Handle = this->GetHandle();
    if (Handle.IsValid())
    {
        for (auto i = 0; i < MAX_LOCAL_PLAYERS; i++)
        {
        }
        Handle->ClearOnGameActivityActivationRequestedDelegate_Handle(this->DelegateHandle_OnGameActivityActivationRequested);
        
    }

    Super::BeginDestroy();
}

bool UOnlineGameActivitySubsystem::IsSubsystemAvailable()
{
    check(!this->HasAnyFlags(RF_ClassDefaultObject));
    return this->IsHandleValid(this->GetHandle());
}

UOnlineGameActivitySubsystemStartActivity* UOnlineGameActivitySubsystemStartActivity::StartActivity(UOnlineGameActivitySubsystem* Subsystem ,FUniqueNetIdRepl LocalUserId, FString ActivityId, TMap<FString, FVariantDataBP> Parms)
{
    if (!IsValid(Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("OnlineGameActivitySubsystem is not available. It's possible the online subsystem you are using doesn't support it. Alternatively, make sure that you are not attempting to use Online Subsystem Blueprints during the Init event in a GameInstance. Add a 'Delay 0.1' node between the Init event and the rest of your logic if you need to use Online Subsystem Blueprints this early in game startup."));
        return nullptr;
    }

    check(!Subsystem->HasAnyFlags(RF_ClassDefaultObject));

    UOnlineGameActivitySubsystemStartActivity* Node = NewObject<UOnlineGameActivitySubsystemStartActivity>();
    Node->__Store__Subsystem = Subsystem;
    Node->__Store__CallUniquenessId = TEXT("");
    Node->__Store__LocalUserId = LocalUserId;
    Node->__Store__ActivityId = ActivityId;
    Node->__Store__Parms = Parms;
    return Node;
}

void UOnlineGameActivitySubsystemStartActivity::Activate()
{
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem value not valid when Activate() was called"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), FOnlineErrorInfo());
        return;
    }
    if (!(this->__Store__LocalUserId.IsValid() && this->__Store__LocalUserId.GetUniqueNetId().IsValid()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'LocalUserId' was not valid"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), FOnlineErrorInfo());
        return;
    }

    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        if (this->__Store__Subsystem->__InFlightRequests.Contains(this->__Store__CallUniquenessId))
        {
            UE_LOG(LogOnlineBlueprint, Error, TEXT("There is already a request running with ID '%s'. Wait until it is complete before starting another request with the same parameters."), *this->__Store__CallUniquenessId);
            this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), FOnlineErrorInfo());
            return;
        }

        this->__Store__Subsystem->__InFlightRequests.Add(this->__Store__CallUniquenessId);
    }

    auto __DelegateHandle_OnStartActivityComplete = FOnStartActivityComplete::CreateUObject(this, &UOnlineGameActivitySubsystemStartActivity::HandleCallback_OnStartActivityComplete);

    Handle->StartActivity(this->__Store__LocalUserId.GetUniqueNetId().ToSharedRef().Get(), this->__Store__ActivityId, ConvertMapToEventParams(this->__Store__Parms), __DelegateHandle_OnStartActivityComplete);
}

void UOnlineGameActivitySubsystemStartActivity::HandleCallback_OnStartActivityComplete(const FUniqueNetId& LocalUserId, const FString& ActivityId, const FOnlineError& Status)
{
    if (!IsValid(this->__Store__Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), FOnlineErrorInfo());
        return;
    }
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem handle was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), FOnlineErrorInfo());
        return;
    }
    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        this->__Store__Subsystem->__InFlightRequests.Remove(this->__Store__CallUniquenessId);
    }

    this->OnStartActivityComplete.Broadcast(ConvertDangerousUniqueNetIdToRepl(LocalUserId), ActivityId, FOnlineErrorInfo::FromNative(Status));
}

UOnlineGameActivitySubsystemEndActivity* UOnlineGameActivitySubsystemEndActivity::EndActivity(UOnlineGameActivitySubsystem* Subsystem ,FUniqueNetIdRepl LocalUserId, FString ActivityId, EOnlineActivityOutcome_ ActivityOutcome, TMap<FString, FVariantDataBP> Parms)
{
    if (!IsValid(Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("OnlineGameActivitySubsystem is not available. It's possible the online subsystem you are using doesn't support it. Alternatively, make sure that you are not attempting to use Online Subsystem Blueprints during the Init event in a GameInstance. Add a 'Delay 0.1' node between the Init event and the rest of your logic if you need to use Online Subsystem Blueprints this early in game startup."));
        return nullptr;
    }

    check(!Subsystem->HasAnyFlags(RF_ClassDefaultObject));

    UOnlineGameActivitySubsystemEndActivity* Node = NewObject<UOnlineGameActivitySubsystemEndActivity>();
    Node->__Store__Subsystem = Subsystem;
    Node->__Store__CallUniquenessId = TEXT("");
    Node->__Store__LocalUserId = LocalUserId;
    Node->__Store__ActivityId = ActivityId;
    Node->__Store__ActivityOutcome = ActivityOutcome;
    Node->__Store__Parms = Parms;
    return Node;
}

void UOnlineGameActivitySubsystemEndActivity::Activate()
{
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem value not valid when Activate() was called"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), EOnlineActivityOutcome_::Completed, FOnlineErrorInfo());
        return;
    }
    if (!(this->__Store__LocalUserId.IsValid() && this->__Store__LocalUserId.GetUniqueNetId().IsValid()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'LocalUserId' was not valid"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), EOnlineActivityOutcome_::Completed, FOnlineErrorInfo());
        return;
    }

    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        if (this->__Store__Subsystem->__InFlightRequests.Contains(this->__Store__CallUniquenessId))
        {
            UE_LOG(LogOnlineBlueprint, Error, TEXT("There is already a request running with ID '%s'. Wait until it is complete before starting another request with the same parameters."), *this->__Store__CallUniquenessId);
            this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), EOnlineActivityOutcome_::Completed, FOnlineErrorInfo());
            return;
        }

        this->__Store__Subsystem->__InFlightRequests.Add(this->__Store__CallUniquenessId);
    }

    auto __DelegateHandle_OnEndActivityComplete = FOnEndActivityComplete::CreateUObject(this, &UOnlineGameActivitySubsystemEndActivity::HandleCallback_OnEndActivityComplete);

    Handle->EndActivity(this->__Store__LocalUserId.GetUniqueNetId().ToSharedRef().Get(), this->__Store__ActivityId, (EOnlineActivityOutcome)(this->__Store__ActivityOutcome), ConvertMapToEventParams(this->__Store__Parms), __DelegateHandle_OnEndActivityComplete);
}

void UOnlineGameActivitySubsystemEndActivity::HandleCallback_OnEndActivityComplete(const FUniqueNetId& LocalUserId, const FString& ActivityId, const EOnlineActivityOutcome& Outcome, const FOnlineError& Status)
{
    if (!IsValid(this->__Store__Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), EOnlineActivityOutcome_::Completed, FOnlineErrorInfo());
        return;
    }
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem handle was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), EOnlineActivityOutcome_::Completed, FOnlineErrorInfo());
        return;
    }
    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        this->__Store__Subsystem->__InFlightRequests.Remove(this->__Store__CallUniquenessId);
    }

    this->OnEndActivityComplete.Broadcast(ConvertDangerousUniqueNetIdToRepl(LocalUserId), ActivityId, (EOnlineActivityOutcome_)(Outcome), FOnlineErrorInfo::FromNative(Status));
}

UOnlineGameActivitySubsystemResetAllActiveActivities* UOnlineGameActivitySubsystemResetAllActiveActivities::ResetAllActiveActivities(UOnlineGameActivitySubsystem* Subsystem ,FUniqueNetIdRepl LocalUserId)
{
    if (!IsValid(Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("OnlineGameActivitySubsystem is not available. It's possible the online subsystem you are using doesn't support it. Alternatively, make sure that you are not attempting to use Online Subsystem Blueprints during the Init event in a GameInstance. Add a 'Delay 0.1' node between the Init event and the rest of your logic if you need to use Online Subsystem Blueprints this early in game startup."));
        return nullptr;
    }

    check(!Subsystem->HasAnyFlags(RF_ClassDefaultObject));

    UOnlineGameActivitySubsystemResetAllActiveActivities* Node = NewObject<UOnlineGameActivitySubsystemResetAllActiveActivities>();
    Node->__Store__Subsystem = Subsystem;
    Node->__Store__CallUniquenessId = TEXT("");
    Node->__Store__LocalUserId = LocalUserId;
    return Node;
}

void UOnlineGameActivitySubsystemResetAllActiveActivities::Activate()
{
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem value not valid when Activate() was called"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }
    if (!(this->__Store__LocalUserId.IsValid() && this->__Store__LocalUserId.GetUniqueNetId().IsValid()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'LocalUserId' was not valid"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }

    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        if (this->__Store__Subsystem->__InFlightRequests.Contains(this->__Store__CallUniquenessId))
        {
            UE_LOG(LogOnlineBlueprint, Error, TEXT("There is already a request running with ID '%s'. Wait until it is complete before starting another request with the same parameters."), *this->__Store__CallUniquenessId);
            this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
            return;
        }

        this->__Store__Subsystem->__InFlightRequests.Add(this->__Store__CallUniquenessId);
    }

    auto __DelegateHandle_OnResetAllActiveActivitiesComplete = FOnResetAllActiveActivitiesComplete::CreateUObject(this, &UOnlineGameActivitySubsystemResetAllActiveActivities::HandleCallback_OnResetAllActiveActivitiesComplete);

    Handle->ResetAllActiveActivities(this->__Store__LocalUserId.GetUniqueNetId().ToSharedRef().Get(), __DelegateHandle_OnResetAllActiveActivitiesComplete);
}

void UOnlineGameActivitySubsystemResetAllActiveActivities::HandleCallback_OnResetAllActiveActivitiesComplete(const FUniqueNetId& LocalUserId, const FOnlineError& Status)
{
    if (!IsValid(this->__Store__Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem handle was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }
    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        this->__Store__Subsystem->__InFlightRequests.Remove(this->__Store__CallUniquenessId);
    }

    this->OnResetAllActiveActivitiesComplete.Broadcast(ConvertDangerousUniqueNetIdToRepl(LocalUserId), FOnlineErrorInfo::FromNative(Status));
}

UOnlineGameActivitySubsystemResumeActivity* UOnlineGameActivitySubsystemResumeActivity::ResumeActivity(UOnlineGameActivitySubsystem* Subsystem ,FUniqueNetIdRepl LocalUserId, FString ActivityId, FOnlineActivityTasksToResetBP TasksToReset)
{
    if (!IsValid(Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("OnlineGameActivitySubsystem is not available. It's possible the online subsystem you are using doesn't support it. Alternatively, make sure that you are not attempting to use Online Subsystem Blueprints during the Init event in a GameInstance. Add a 'Delay 0.1' node between the Init event and the rest of your logic if you need to use Online Subsystem Blueprints this early in game startup."));
        return nullptr;
    }

    check(!Subsystem->HasAnyFlags(RF_ClassDefaultObject));

    UOnlineGameActivitySubsystemResumeActivity* Node = NewObject<UOnlineGameActivitySubsystemResumeActivity>();
    Node->__Store__Subsystem = Subsystem;
    Node->__Store__CallUniquenessId = TEXT("");
    Node->__Store__LocalUserId = LocalUserId;
    Node->__Store__ActivityId = ActivityId;
    Node->__Store__TasksToReset = TasksToReset;
    return Node;
}

void UOnlineGameActivitySubsystemResumeActivity::Activate()
{
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem value not valid when Activate() was called"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), FOnlineErrorInfo());
        return;
    }
    if (!(this->__Store__LocalUserId.IsValid() && this->__Store__LocalUserId.GetUniqueNetId().IsValid()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'LocalUserId' was not valid"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), FOnlineErrorInfo());
        return;
    }

    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        if (this->__Store__Subsystem->__InFlightRequests.Contains(this->__Store__CallUniquenessId))
        {
            UE_LOG(LogOnlineBlueprint, Error, TEXT("There is already a request running with ID '%s'. Wait until it is complete before starting another request with the same parameters."), *this->__Store__CallUniquenessId);
            this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), FOnlineErrorInfo());
            return;
        }

        this->__Store__Subsystem->__InFlightRequests.Add(this->__Store__CallUniquenessId);
    }

    auto __DelegateHandle_OnResumeActivityComplete = FOnResumeActivityComplete::CreateUObject(this, &UOnlineGameActivitySubsystemResumeActivity::HandleCallback_OnResumeActivityComplete);

    Handle->ResumeActivity(this->__Store__LocalUserId.GetUniqueNetId().ToSharedRef().Get(), this->__Store__ActivityId, this->__Store__TasksToReset.ToNative(), __DelegateHandle_OnResumeActivityComplete);
}

void UOnlineGameActivitySubsystemResumeActivity::HandleCallback_OnResumeActivityComplete(const FUniqueNetId& LocalUserId, const FString& ActivityId, const FOnlineError& Status)
{
    if (!IsValid(this->__Store__Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), FOnlineErrorInfo());
        return;
    }
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem handle was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), TEXT(""), FOnlineErrorInfo());
        return;
    }
    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        this->__Store__Subsystem->__InFlightRequests.Remove(this->__Store__CallUniquenessId);
    }

    this->OnResumeActivityComplete.Broadcast(ConvertDangerousUniqueNetIdToRepl(LocalUserId), ActivityId, FOnlineErrorInfo::FromNative(Status));
}

UOnlineGameActivitySubsystemSetActivityAvailability* UOnlineGameActivitySubsystemSetActivityAvailability::SetActivityAvailability(UOnlineGameActivitySubsystem* Subsystem ,FUniqueNetIdRepl LocalUserId, FString ActivityId, bool bEnabled)
{
    if (!IsValid(Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("OnlineGameActivitySubsystem is not available. It's possible the online subsystem you are using doesn't support it. Alternatively, make sure that you are not attempting to use Online Subsystem Blueprints during the Init event in a GameInstance. Add a 'Delay 0.1' node between the Init event and the rest of your logic if you need to use Online Subsystem Blueprints this early in game startup."));
        return nullptr;
    }

    check(!Subsystem->HasAnyFlags(RF_ClassDefaultObject));

    UOnlineGameActivitySubsystemSetActivityAvailability* Node = NewObject<UOnlineGameActivitySubsystemSetActivityAvailability>();
    Node->__Store__Subsystem = Subsystem;
    Node->__Store__CallUniquenessId = TEXT("");
    Node->__Store__LocalUserId = LocalUserId;
    Node->__Store__ActivityId = ActivityId;
    Node->__Store__bEnabled = bEnabled;
    return Node;
}

void UOnlineGameActivitySubsystemSetActivityAvailability::Activate()
{
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem value not valid when Activate() was called"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }
    if (!(this->__Store__LocalUserId.IsValid() && this->__Store__LocalUserId.GetUniqueNetId().IsValid()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'LocalUserId' was not valid"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }

    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        if (this->__Store__Subsystem->__InFlightRequests.Contains(this->__Store__CallUniquenessId))
        {
            UE_LOG(LogOnlineBlueprint, Error, TEXT("There is already a request running with ID '%s'. Wait until it is complete before starting another request with the same parameters."), *this->__Store__CallUniquenessId);
            this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
            return;
        }

        this->__Store__Subsystem->__InFlightRequests.Add(this->__Store__CallUniquenessId);
    }

    auto __DelegateHandle_OnSetActivityAvailabilityComplete = FOnSetActivityAvailabilityComplete::CreateUObject(this, &UOnlineGameActivitySubsystemSetActivityAvailability::HandleCallback_OnSetActivityAvailabilityComplete);

    Handle->SetActivityAvailability(this->__Store__LocalUserId.GetUniqueNetId().ToSharedRef().Get(), this->__Store__ActivityId, this->__Store__bEnabled, __DelegateHandle_OnSetActivityAvailabilityComplete);
}

void UOnlineGameActivitySubsystemSetActivityAvailability::HandleCallback_OnSetActivityAvailabilityComplete(const FUniqueNetId& LocalUserId, const FOnlineError& Status)
{
    if (!IsValid(this->__Store__Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem handle was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }
    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        this->__Store__Subsystem->__InFlightRequests.Remove(this->__Store__CallUniquenessId);
    }

    this->OnSetActivityAvailabilityComplete.Broadcast(ConvertDangerousUniqueNetIdToRepl(LocalUserId), FOnlineErrorInfo::FromNative(Status));
}

UOnlineGameActivitySubsystemSetActivityPriority* UOnlineGameActivitySubsystemSetActivityPriority::SetActivityPriority(UOnlineGameActivitySubsystem* Subsystem ,FUniqueNetIdRepl LocalUserId, TMap<FString, int32> PrioritizedActivities)
{
    if (!IsValid(Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("OnlineGameActivitySubsystem is not available. It's possible the online subsystem you are using doesn't support it. Alternatively, make sure that you are not attempting to use Online Subsystem Blueprints during the Init event in a GameInstance. Add a 'Delay 0.1' node between the Init event and the rest of your logic if you need to use Online Subsystem Blueprints this early in game startup."));
        return nullptr;
    }

    check(!Subsystem->HasAnyFlags(RF_ClassDefaultObject));

    UOnlineGameActivitySubsystemSetActivityPriority* Node = NewObject<UOnlineGameActivitySubsystemSetActivityPriority>();
    Node->__Store__Subsystem = Subsystem;
    Node->__Store__CallUniquenessId = TEXT("");
    Node->__Store__LocalUserId = LocalUserId;
    Node->__Store__PrioritizedActivities = PrioritizedActivities;
    return Node;
}

void UOnlineGameActivitySubsystemSetActivityPriority::Activate()
{
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem value not valid when Activate() was called"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }
    if (!(this->__Store__LocalUserId.IsValid() && this->__Store__LocalUserId.GetUniqueNetId().IsValid()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'LocalUserId' was not valid"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }
    if (!(ValidateMapElements<FString, int32>(this->__Store__PrioritizedActivities, [](const FString& Val) { return true; }, [](const int32& Val) { return true; })))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'PrioritizedActivities' was not valid"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }

    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        if (this->__Store__Subsystem->__InFlightRequests.Contains(this->__Store__CallUniquenessId))
        {
            UE_LOG(LogOnlineBlueprint, Error, TEXT("There is already a request running with ID '%s'. Wait until it is complete before starting another request with the same parameters."), *this->__Store__CallUniquenessId);
            this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
            return;
        }

        this->__Store__Subsystem->__InFlightRequests.Add(this->__Store__CallUniquenessId);
    }

    auto __DelegateHandle_OnSetActivityPriorityComplete = FOnSetActivityPriorityComplete::CreateUObject(this, &UOnlineGameActivitySubsystemSetActivityPriority::HandleCallback_OnSetActivityPriorityComplete);

    Handle->SetActivityPriority(this->__Store__LocalUserId.GetUniqueNetId().ToSharedRef().Get(), ConvertMapElements<FString, FString, int32, int32>(this->__Store__PrioritizedActivities, [](const FString& Val) { return Val; }, [](const int32& Val) { return Val; }), __DelegateHandle_OnSetActivityPriorityComplete);
}

void UOnlineGameActivitySubsystemSetActivityPriority::HandleCallback_OnSetActivityPriorityComplete(const FUniqueNetId& LocalUserId, const FOnlineError& Status)
{
    if (!IsValid(this->__Store__Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem handle was not valid during callback handling"));
        this->OnCallFailed.Broadcast(FUniqueNetIdRepl(), FOnlineErrorInfo());
        return;
    }
    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        this->__Store__Subsystem->__InFlightRequests.Remove(this->__Store__CallUniquenessId);
    }

    this->OnSetActivityPriorityComplete.Broadcast(ConvertDangerousUniqueNetIdToRepl(LocalUserId), FOnlineErrorInfo::FromNative(Status));
}

void UOnlineGameActivitySubsystem::UpdatePlayerLocation(FUniqueNetIdRepl LocalUserId, FOnlineActivityPlayerLocationBP& ActivityPlayerLocation)
{
    check(!this->HasAnyFlags(RF_ClassDefaultObject));
    auto Handle = this->GetHandle();
    if (!this->IsHandleValid(Handle))
    {
        return ;
    }
    if (!(LocalUserId.IsValid() && LocalUserId.GetUniqueNetId().IsValid()))
    {
        return ;
    }

    TOptional<FOnlineActivityPlayerLocation> __StoreTemp__ActivityPlayerLocation;

    Handle->UpdatePlayerLocation(LocalUserId.GetUniqueNetId().ToSharedRef().Get(), __StoreTemp__ActivityPlayerLocation);
    ActivityPlayerLocation = FOnlineActivityPlayerLocationBP::FromNative(__StoreTemp__ActivityPlayerLocation);
}
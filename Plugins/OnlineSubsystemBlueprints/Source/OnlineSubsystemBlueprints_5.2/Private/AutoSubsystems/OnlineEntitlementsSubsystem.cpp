// Copyright June Rhodes 2023. All Rights Reserved.

#include "AutoSubsystems/OnlineEntitlementsSubsystem.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemBlueprintsModule.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"

FName UOnlineEntitlementsSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;

TSharedPtr<class IOnlineEntitlements, ESPMode::ThreadSafe> UOnlineEntitlementsSubsystem::GetHandle()
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

    TSharedPtr<class IOnlineEntitlements, ESPMode::ThreadSafe> Pinned = this->HandleWk.Pin();
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
        auto __Handle__ = Subsystem->GetEntitlementsInterface();
        this->HandleWk = __Handle__;
        Pinned = __Handle__;
    }

    return Pinned;
}

bool UOnlineEntitlementsSubsystem::IsHandleValid(const TSharedPtr<class IOnlineEntitlements, ESPMode::ThreadSafe>& InHandle)
{
    return InHandle.IsValid();
}

UOnlineEntitlementsSubsystem::UOnlineEntitlementsSubsystem()
{
    if (this->HasAnyFlags(RF_ClassDefaultObject))
    {
        return;
    }

    this->OSSName = UOnlineEntitlementsSubsystem::OSSNameToAssignDuringConstruction;
    UOnlineEntitlementsSubsystem::OSSNameToAssignDuringConstruction = NAME_Default;

    auto GameInstance = this->GetGameInstance();
    check(IsValid(GameInstance));

    auto World = GameInstance->GetWorld();
    check(IsValid(World));
    
    // Store the WorldContext so we can assert that it never changes later during our
    // operation (required for semantic correctness).
    this->WorldContext = GEngine->GetWorldContextFromWorld(World);
    check(WorldContext != nullptr);
    UE_LOG(LogOnlineBlueprint, Verbose, TEXT("OnlineEntitlementsSubsystem subsystem initialized in context %s"), *WorldContext->ContextHandle.ToString());

    // Perform the initial cache of the online subsystem pointer. Calling GetHandle()
    // is enough to cache the weak pointer.
    this->HandleWk = nullptr;
    this->GetHandle();

    // Now, register events.
    
    TSharedPtr<class IOnlineEntitlements, ESPMode::ThreadSafe> Handle = this->GetHandle();
    if (Handle.IsValid())
    {
        for (auto i = 0; i < MAX_LOCAL_PLAYERS; i++)
        {
        }
        this->DelegateHandle_OnQueryEntitlementsComplete = Handle->AddOnQueryEntitlementsCompleteDelegate_Handle(
            FOnQueryEntitlementsComplete::FDelegate::CreateWeakLambda(this, [this](bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Namespace, const FString& Error) {
                this->OnQueryEntitlementsComplete.Broadcast(bWasSuccessful, ConvertDangerousUniqueNetIdToRepl(UserId), Namespace, Error);
            })
        );
    }
}

void UOnlineEntitlementsSubsystem::BeginDestroy()
{
    if (this->HasAnyFlags(RF_ClassDefaultObject))
    {
        Super::BeginDestroy();
        return;
    }

    TSharedPtr<class IOnlineEntitlements, ESPMode::ThreadSafe> Handle = this->GetHandle();
    if (Handle.IsValid())
    {
        for (auto i = 0; i < MAX_LOCAL_PLAYERS; i++)
        {
        }
        Handle->ClearOnQueryEntitlementsCompleteDelegate_Handle(this->DelegateHandle_OnQueryEntitlementsComplete);
        
    }

    Super::BeginDestroy();
}

bool UOnlineEntitlementsSubsystem::IsSubsystemAvailable()
{
    check(!this->HasAnyFlags(RF_ClassDefaultObject));
    return this->IsHandleValid(this->GetHandle());
}

UOnlineEntitlement* UOnlineEntitlementsSubsystem::GetEntitlement(FUniqueNetIdRepl UserId, FString EntitlementId)
{
    check(!this->HasAnyFlags(RF_ClassDefaultObject));
    auto Handle = this->GetHandle();
    if (!this->IsHandleValid(Handle))
    {
        return nullptr;
    }
    if (!(UserId.IsValid() && UserId.GetUniqueNetId().IsValid()))
    {
        return nullptr;
    }


    auto __Result = UOnlineEntitlement::FromNative(Handle->GetEntitlement(UserId.GetUniqueNetId().ToSharedRef().Get(), EntitlementId));

    return __Result;
}

UOnlineEntitlement* UOnlineEntitlementsSubsystem::GetItemEntitlement(FUniqueNetIdRepl UserId, FString ItemId)
{
    check(!this->HasAnyFlags(RF_ClassDefaultObject));
    auto Handle = this->GetHandle();
    if (!this->IsHandleValid(Handle))
    {
        return nullptr;
    }
    if (!(UserId.IsValid() && UserId.GetUniqueNetId().IsValid()))
    {
        return nullptr;
    }


    auto __Result = UOnlineEntitlement::FromNative(Handle->GetItemEntitlement(UserId.GetUniqueNetId().ToSharedRef().Get(), ItemId));

    return __Result;
}

void UOnlineEntitlementsSubsystem::GetAllEntitlements(FUniqueNetIdRepl UserId, FString Namespace, TArray<UOnlineEntitlement*>& OutUserEntitlements)
{
    check(!this->HasAnyFlags(RF_ClassDefaultObject));
    auto Handle = this->GetHandle();
    if (!this->IsHandleValid(Handle))
    {
        return ;
    }
    if (!(UserId.IsValid() && UserId.GetUniqueNetId().IsValid()))
    {
        return ;
    }

    TArray<TSharedRef<FOnlineEntitlement>> __StoreTemp__OutUserEntitlements;

    Handle->GetAllEntitlements(UserId.GetUniqueNetId().ToSharedRef().Get(), Namespace, __StoreTemp__OutUserEntitlements);
    OutUserEntitlements = ConvertArrayElements<TSharedRef<FOnlineEntitlement>, UOnlineEntitlement*>(__StoreTemp__OutUserEntitlements, [](const TSharedRef<FOnlineEntitlement>& Val) { return UOnlineEntitlement::FromNative(Val); });
}

UOnlineEntitlementsSubsystemQueryEntitlements* UOnlineEntitlementsSubsystemQueryEntitlements::QueryEntitlements(UOnlineEntitlementsSubsystem* Subsystem ,FUniqueNetIdRepl UserId, FString Namespace, FPagedQueryBP Page)
{
    if (!IsValid(Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("OnlineEntitlementsSubsystem is not available. It's possible the online subsystem you are using doesn't support it. Alternatively, make sure that you are not attempting to use Online Subsystem Blueprints during the Init event in a GameInstance. Add a 'Delay 0.1' node between the Init event and the rest of your logic if you need to use Online Subsystem Blueprints this early in game startup."));
        return nullptr;
    }

    check(!Subsystem->HasAnyFlags(RF_ClassDefaultObject));

    UOnlineEntitlementsSubsystemQueryEntitlements* Node = NewObject<UOnlineEntitlementsSubsystemQueryEntitlements>();
    Node->__Store__Subsystem = Subsystem;
    Node->__Store__CallUniquenessId = TEXT("OnQueryEntitlementsComplete");
    Node->__Store__UserId = UserId;
    Node->__Store__Namespace = Namespace;
    Node->__Store__Page = Page;
    return Node;
}

void UOnlineEntitlementsSubsystemQueryEntitlements::Activate()
{
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem value not valid when Activate() was called"));
        this->OnCallFailed.Broadcast(false, FUniqueNetIdRepl(), TEXT(""), TEXT(""));
        return;
    }
    if (!(this->__Store__UserId.IsValid() && this->__Store__UserId.GetUniqueNetId().IsValid()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'UserId' was not valid"));
        this->OnCallFailed.Broadcast(false, FUniqueNetIdRepl(), TEXT(""), TEXT(""));
        return;
    }

    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        if (this->__Store__Subsystem->__InFlightRequests.Contains(this->__Store__CallUniquenessId))
        {
            UE_LOG(LogOnlineBlueprint, Error, TEXT("There is already a request running with ID '%s'. Wait until it is complete before starting another request with the same parameters."), *this->__Store__CallUniquenessId);
            this->OnCallFailed.Broadcast(false, FUniqueNetIdRepl(), TEXT(""), TEXT(""));
            return;
        }

        this->__Store__Subsystem->__InFlightRequests.Add(this->__Store__CallUniquenessId);
    }

    this->DelegateHandle_OnQueryEntitlementsComplete = Handle->AddOnQueryEntitlementsCompleteDelegate_Handle(
        FOnQueryEntitlementsCompleteDelegate::CreateUObject(this, &UOnlineEntitlementsSubsystemQueryEntitlements::HandleCallback_OnQueryEntitlementsComplete));
    
    if (!Handle->QueryEntitlements(this->__Store__UserId.GetUniqueNetId().ToSharedRef().Get(), this->__Store__Namespace, this->__Store__Page.ToNative()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Call 'QueryEntitlements' did not start successfully"));
        Handle->ClearOnQueryEntitlementsCompleteDelegate_Handle(this->DelegateHandle_OnQueryEntitlementsComplete);
        this->OnCallFailed.Broadcast(false, FUniqueNetIdRepl(), TEXT(""), TEXT(""));
        return;
    }
}

void UOnlineEntitlementsSubsystemQueryEntitlements::HandleCallback_OnQueryEntitlementsComplete(bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Namespace, const FString& Error)
{
    if (!IsValid(this->__Store__Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem was not valid during callback handling"));
        this->OnCallFailed.Broadcast(false, FUniqueNetIdRepl(), TEXT(""), TEXT(""));
        return;
    }
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem handle was not valid during callback handling"));
        this->OnCallFailed.Broadcast(false, FUniqueNetIdRepl(), TEXT(""), TEXT(""));
        return;
    }
    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        this->__Store__Subsystem->__InFlightRequests.Remove(this->__Store__CallUniquenessId);
    }
        Handle->ClearOnQueryEntitlementsCompleteDelegate_Handle(this->DelegateHandle_OnQueryEntitlementsComplete);

    this->OnQueryEntitlementsComplete.Broadcast(bWasSuccessful, ConvertDangerousUniqueNetIdToRepl(UserId), Namespace, Error);
}
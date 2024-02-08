// Copyright June Rhodes 2023. All Rights Reserved.

#include "AutoSubsystems/OnlineStoreV2Subsystem.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemBlueprintsModule.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"

FName UOnlineStoreV2Subsystem::OSSNameToAssignDuringConstruction = NAME_Default;

TSharedPtr<class IOnlineStoreV2, ESPMode::ThreadSafe> UOnlineStoreV2Subsystem::GetHandle()
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

    TSharedPtr<class IOnlineStoreV2, ESPMode::ThreadSafe> Pinned = this->HandleWk.Pin();
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
        auto __Handle__ = Subsystem->GetStoreV2Interface();
        this->HandleWk = __Handle__;
        Pinned = __Handle__;
    }

    return Pinned;
}

bool UOnlineStoreV2Subsystem::IsHandleValid(const TSharedPtr<class IOnlineStoreV2, ESPMode::ThreadSafe>& InHandle)
{
    return InHandle.IsValid();
}

UOnlineStoreV2Subsystem::UOnlineStoreV2Subsystem()
{
    if (this->HasAnyFlags(RF_ClassDefaultObject))
    {
        return;
    }

    this->OSSName = UOnlineStoreV2Subsystem::OSSNameToAssignDuringConstruction;
    UOnlineStoreV2Subsystem::OSSNameToAssignDuringConstruction = NAME_Default;

    auto GameInstance = this->GetGameInstance();
    check(IsValid(GameInstance));

    auto World = GameInstance->GetWorld();
    check(IsValid(World));
    
    // Store the WorldContext so we can assert that it never changes later during our
    // operation (required for semantic correctness).
    this->WorldContext = GEngine->GetWorldContextFromWorld(World);
    check(WorldContext != nullptr);
    UE_LOG(LogOnlineBlueprint, Verbose, TEXT("OnlineStoreV2Subsystem subsystem initialized in context %s"), *WorldContext->ContextHandle.ToString());

    // Perform the initial cache of the online subsystem pointer. Calling GetHandle()
    // is enough to cache the weak pointer.
    this->HandleWk = nullptr;
    this->GetHandle();

    // Now, register events.
    
    TSharedPtr<class IOnlineStoreV2, ESPMode::ThreadSafe> Handle = this->GetHandle();
    if (Handle.IsValid())
    {
        for (auto i = 0; i < MAX_LOCAL_PLAYERS; i++)
        {
        }
        this->DelegateHandle_OnQueryForAvailablePurchasesComplete = Handle->AddOnQueryForAvailablePurchasesCompleteDelegate_Handle(
            FOnQueryForAvailablePurchasesComplete::FDelegate::CreateWeakLambda(this, [this](bool Param1) {
                this->OnQueryForAvailablePurchasesComplete.Broadcast(Param1);
            })
        );
    }
}

void UOnlineStoreV2Subsystem::BeginDestroy()
{
    if (this->HasAnyFlags(RF_ClassDefaultObject))
    {
        Super::BeginDestroy();
        return;
    }

    TSharedPtr<class IOnlineStoreV2, ESPMode::ThreadSafe> Handle = this->GetHandle();
    if (Handle.IsValid())
    {
        for (auto i = 0; i < MAX_LOCAL_PLAYERS; i++)
        {
        }
        Handle->ClearOnQueryForAvailablePurchasesCompleteDelegate_Handle(this->DelegateHandle_OnQueryForAvailablePurchasesComplete);
        
    }

    Super::BeginDestroy();
}

bool UOnlineStoreV2Subsystem::IsSubsystemAvailable()
{
    check(!this->HasAnyFlags(RF_ClassDefaultObject));
    return this->IsHandleValid(this->GetHandle());
}

UOnlineStoreV2SubsystemQueryCategories* UOnlineStoreV2SubsystemQueryCategories::QueryCategories(UOnlineStoreV2Subsystem* Subsystem ,FUniqueNetIdRepl UserId)
{
    if (!IsValid(Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("OnlineStoreV2Subsystem is not available. It's possible the online subsystem you are using doesn't support it. Alternatively, make sure that you are not attempting to use Online Subsystem Blueprints during the Init event in a GameInstance. Add a 'Delay 0.1' node between the Init event and the rest of your logic if you need to use Online Subsystem Blueprints this early in game startup."));
        return nullptr;
    }

    check(!Subsystem->HasAnyFlags(RF_ClassDefaultObject));

    UOnlineStoreV2SubsystemQueryCategories* Node = NewObject<UOnlineStoreV2SubsystemQueryCategories>();
    Node->__Store__Subsystem = Subsystem;
    Node->__Store__CallUniquenessId = TEXT("");
    Node->__Store__UserId = UserId;
    return Node;
}

void UOnlineStoreV2SubsystemQueryCategories::Activate()
{
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem value not valid when Activate() was called"));
        this->OnCallFailed.Broadcast(false, TEXT(""));
        return;
    }
    if (!(this->__Store__UserId.IsValid() && this->__Store__UserId.GetUniqueNetId().IsValid()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'UserId' was not valid"));
        this->OnCallFailed.Broadcast(false, TEXT(""));
        return;
    }

    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        if (this->__Store__Subsystem->__InFlightRequests.Contains(this->__Store__CallUniquenessId))
        {
            UE_LOG(LogOnlineBlueprint, Error, TEXT("There is already a request running with ID '%s'. Wait until it is complete before starting another request with the same parameters."), *this->__Store__CallUniquenessId);
            this->OnCallFailed.Broadcast(false, TEXT(""));
            return;
        }

        this->__Store__Subsystem->__InFlightRequests.Add(this->__Store__CallUniquenessId);
    }

    auto __DelegateHandle_OnQueryOnlineStoreCategoriesComplete = FOnQueryOnlineStoreCategoriesComplete::CreateUObject(this, &UOnlineStoreV2SubsystemQueryCategories::HandleCallback_OnQueryOnlineStoreCategoriesComplete);

    Handle->QueryCategories(this->__Store__UserId.GetUniqueNetId().ToSharedRef().Get(), __DelegateHandle_OnQueryOnlineStoreCategoriesComplete);
}

void UOnlineStoreV2SubsystemQueryCategories::HandleCallback_OnQueryOnlineStoreCategoriesComplete(bool bWasSuccessful, const FString& Error)
{
    if (!IsValid(this->__Store__Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem was not valid during callback handling"));
        this->OnCallFailed.Broadcast(false, TEXT(""));
        return;
    }
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem handle was not valid during callback handling"));
        this->OnCallFailed.Broadcast(false, TEXT(""));
        return;
    }
    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        this->__Store__Subsystem->__InFlightRequests.Remove(this->__Store__CallUniquenessId);
    }

    this->OnQueryOnlineStoreCategoriesComplete.Broadcast(bWasSuccessful, Error);
}

void UOnlineStoreV2Subsystem::GetCategories(TArray<FOnlineStoreCategoryBP>& OutCategories)
{
    check(!this->HasAnyFlags(RF_ClassDefaultObject));
    auto Handle = this->GetHandle();
    if (!this->IsHandleValid(Handle))
    {
        return ;
    }

    TArray<FOnlineStoreCategory> __StoreTemp__OutCategories;

    Handle->GetCategories(__StoreTemp__OutCategories);
    OutCategories = ConvertArrayElements<FOnlineStoreCategory, FOnlineStoreCategoryBP>(__StoreTemp__OutCategories, [](const FOnlineStoreCategory& Val) { return FOnlineStoreCategoryBP::FromNative(Val); });
}

UOnlineStoreV2SubsystemQueryOffersByFilter* UOnlineStoreV2SubsystemQueryOffersByFilter::QueryOffersByFilter(UOnlineStoreV2Subsystem* Subsystem ,FUniqueNetIdRepl UserId, FOnlineStoreFilterBP Filter)
{
    if (!IsValid(Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("OnlineStoreV2Subsystem is not available. It's possible the online subsystem you are using doesn't support it. Alternatively, make sure that you are not attempting to use Online Subsystem Blueprints during the Init event in a GameInstance. Add a 'Delay 0.1' node between the Init event and the rest of your logic if you need to use Online Subsystem Blueprints this early in game startup."));
        return nullptr;
    }

    check(!Subsystem->HasAnyFlags(RF_ClassDefaultObject));

    UOnlineStoreV2SubsystemQueryOffersByFilter* Node = NewObject<UOnlineStoreV2SubsystemQueryOffersByFilter>();
    Node->__Store__Subsystem = Subsystem;
    Node->__Store__CallUniquenessId = TEXT("");
    Node->__Store__UserId = UserId;
    Node->__Store__Filter = Filter;
    return Node;
}

void UOnlineStoreV2SubsystemQueryOffersByFilter::Activate()
{
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem value not valid when Activate() was called"));
        this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
        return;
    }
    if (!(this->__Store__UserId.IsValid() && this->__Store__UserId.GetUniqueNetId().IsValid()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'UserId' was not valid"));
        this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
        return;
    }

    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        if (this->__Store__Subsystem->__InFlightRequests.Contains(this->__Store__CallUniquenessId))
        {
            UE_LOG(LogOnlineBlueprint, Error, TEXT("There is already a request running with ID '%s'. Wait until it is complete before starting another request with the same parameters."), *this->__Store__CallUniquenessId);
            this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
            return;
        }

        this->__Store__Subsystem->__InFlightRequests.Add(this->__Store__CallUniquenessId);
    }

    auto __DelegateHandle_OnQueryOnlineStoreOffersComplete = FOnQueryOnlineStoreOffersComplete::CreateUObject(this, &UOnlineStoreV2SubsystemQueryOffersByFilter::HandleCallback_OnQueryOnlineStoreOffersComplete);

    Handle->QueryOffersByFilter(this->__Store__UserId.GetUniqueNetId().ToSharedRef().Get(), this->__Store__Filter.ToNative(), __DelegateHandle_OnQueryOnlineStoreOffersComplete);
}

void UOnlineStoreV2SubsystemQueryOffersByFilter::HandleCallback_OnQueryOnlineStoreOffersComplete(bool bWasSuccessful, const TArray<FUniqueOfferId>& OfferIds, const FString& Error)
{
    if (!IsValid(this->__Store__Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem was not valid during callback handling"));
        this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
        return;
    }
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem handle was not valid during callback handling"));
        this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
        return;
    }
    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        this->__Store__Subsystem->__InFlightRequests.Remove(this->__Store__CallUniquenessId);
    }

    this->OnQueryOnlineStoreOffersComplete.Broadcast(bWasSuccessful, ConvertArrayElements<FUniqueOfferId, FString>(OfferIds, [](const FUniqueOfferId& Val) { return Val; }), Error);
}

UOnlineStoreV2SubsystemQueryOffersById* UOnlineStoreV2SubsystemQueryOffersById::QueryOffersById(UOnlineStoreV2Subsystem* Subsystem ,FUniqueNetIdRepl UserId, TArray<FString> OfferIds)
{
    if (!IsValid(Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("OnlineStoreV2Subsystem is not available. It's possible the online subsystem you are using doesn't support it. Alternatively, make sure that you are not attempting to use Online Subsystem Blueprints during the Init event in a GameInstance. Add a 'Delay 0.1' node between the Init event and the rest of your logic if you need to use Online Subsystem Blueprints this early in game startup."));
        return nullptr;
    }

    check(!Subsystem->HasAnyFlags(RF_ClassDefaultObject));

    UOnlineStoreV2SubsystemQueryOffersById* Node = NewObject<UOnlineStoreV2SubsystemQueryOffersById>();
    Node->__Store__Subsystem = Subsystem;
    Node->__Store__CallUniquenessId = TEXT("");
    Node->__Store__UserId = UserId;
    Node->__Store__OfferIds = OfferIds;
    return Node;
}

void UOnlineStoreV2SubsystemQueryOffersById::Activate()
{
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem value not valid when Activate() was called"));
        this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
        return;
    }
    if (!(this->__Store__UserId.IsValid() && this->__Store__UserId.GetUniqueNetId().IsValid()))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'UserId' was not valid"));
        this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
        return;
    }
    if (!(ValidateArrayElements<FString>(this->__Store__OfferIds, [](const FString& Val) { return true; })))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Parameter 'OfferIds' was not valid"));
        this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
        return;
    }

    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        if (this->__Store__Subsystem->__InFlightRequests.Contains(this->__Store__CallUniquenessId))
        {
            UE_LOG(LogOnlineBlueprint, Error, TEXT("There is already a request running with ID '%s'. Wait until it is complete before starting another request with the same parameters."), *this->__Store__CallUniquenessId);
            this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
            return;
        }

        this->__Store__Subsystem->__InFlightRequests.Add(this->__Store__CallUniquenessId);
    }

    auto __DelegateHandle_OnQueryOnlineStoreOffersComplete = FOnQueryOnlineStoreOffersComplete::CreateUObject(this, &UOnlineStoreV2SubsystemQueryOffersById::HandleCallback_OnQueryOnlineStoreOffersComplete);

    Handle->QueryOffersById(this->__Store__UserId.GetUniqueNetId().ToSharedRef().Get(), ConvertArrayElements<FString, FUniqueOfferId>(this->__Store__OfferIds, [](const FString& Val) { return Val; }), __DelegateHandle_OnQueryOnlineStoreOffersComplete);
}

void UOnlineStoreV2SubsystemQueryOffersById::HandleCallback_OnQueryOnlineStoreOffersComplete(bool bWasSuccessful, const TArray<FUniqueOfferId>& OfferIds, const FString& Error)
{
    if (!IsValid(this->__Store__Subsystem))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem was not valid during callback handling"));
        this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
        return;
    }
    auto Handle = this->__Store__Subsystem->GetHandle();
    if (!this->__Store__Subsystem->IsHandleValid(Handle))
    {
        UE_LOG(LogOnlineBlueprint, Error, TEXT("Subsystem handle was not valid during callback handling"));
        this->OnCallFailed.Broadcast(false, TArray<FString>(), TEXT(""));
        return;
    }
    if (this->__Store__CallUniquenessId != TEXT(""))
    {
        this->__Store__Subsystem->__InFlightRequests.Remove(this->__Store__CallUniquenessId);
    }

    this->OnQueryOnlineStoreOffersComplete.Broadcast(bWasSuccessful, ConvertArrayElements<FUniqueOfferId, FString>(OfferIds, [](const FUniqueOfferId& Val) { return Val; }), Error);
}

void UOnlineStoreV2Subsystem::GetOffers(TArray<UOnlineStoreOffer*>& OutOffers)
{
    check(!this->HasAnyFlags(RF_ClassDefaultObject));
    auto Handle = this->GetHandle();
    if (!this->IsHandleValid(Handle))
    {
        return ;
    }

    TArray<FOnlineStoreOfferRef> __StoreTemp__OutOffers;

    Handle->GetOffers(__StoreTemp__OutOffers);
    OutOffers = ConvertArrayElements<FOnlineStoreOfferRef, UOnlineStoreOffer*>(__StoreTemp__OutOffers, [](const FOnlineStoreOfferRef& Val) { return UOnlineStoreOffer::FromNative(Val); });
}

UOnlineStoreOffer* UOnlineStoreV2Subsystem::GetOffer(FString OfferId)
{
    check(!this->HasAnyFlags(RF_ClassDefaultObject));
    auto Handle = this->GetHandle();
    if (!this->IsHandleValid(Handle))
    {
        return nullptr;
    }


    auto __Result = UOnlineStoreOffer::FromNative(Handle->GetOffer(OfferId));

    return __Result;
}
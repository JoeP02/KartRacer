// Copyright June Rhodes 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineExternalUIInterface.h"
#include "Types/OSBMessageTypes.h"
#include "UObject/Interface.h"
#if defined(REDPOINT_OSB_UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

#include "OSBExternalUITypes.generated.h"

USTRUCT()
struct ONLINESUBSYSTEMBLUEPRINTS_API FExternalUIFlowHandlerRegistration
{
    GENERATED_BODY()

public:
    UPROPERTY()
    UObject *Interface = nullptr;
    FDelegateHandle LoginFlowUIRequired;
    FDelegateHandle CreateAccountFlowUIRequired;
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FLoginFlowResultBP
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString Token;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FText ErrorMessage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString ErrorRaw;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 NumericErrorCode = 0;

    static FLoginFlowResultBP FromNative(const FLoginFlowResult &InObj);
    FLoginFlowResult ToNative();
};

UINTERFACE(BlueprintType)
class ONLINESUBSYSTEMBLUEPRINTS_API UExternalUIFlowHandler : public UInterface
{
    GENERATED_BODY()
};

class ONLINESUBSYSTEMBLUEPRINTS_API IExternalUIFlowHandler
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, Category = "Online|External UI")
    bool OnLoginFlowUIRequired(
        const FString &RequestedURL,
        class UOnlineExternalUISubsystem *ExternalUIContext,
        int RequestID);

    UFUNCTION(BlueprintNativeEvent, Category = "Online|External UI")
    bool OnCreateAccountFlowUIRequired(
        const FString &RequestedURL,
        class UOnlineExternalUISubsystem *ExternalUIContext,
        int RequestID);
};

USTRUCT(BlueprintType) struct ONLINESUBSYSTEMBLUEPRINTS_API FShowWebUrlParameters
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool Embedded = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool ShowCloseButton = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool ShowBackground = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool HideCursor = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool ResetCookies = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 OffsetX = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 OffsetY = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 SizeX = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 SizeY = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    TArray<FString> AllowedDomains;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString CallbackPath;

    static FShowWebUrlParameters FromNative(const FShowWebUrlParams &InObj);
    FShowWebUrlParams ToNative();
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FShowStoreParameters
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString Category;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FString ProductId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    bool AddToCart = false;

    static FShowStoreParameters FromNative(const FShowStoreParams &InObj);
    FShowStoreParams ToNative();
};

USTRUCT(BlueprintType)
struct ONLINESUBSYSTEMBLUEPRINTS_API FShowSendMessageParameters
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FText DisplayTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    TMap<FString, FString> DisplayTitle_Loc;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FText DisplayMessage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FText DisplayDetails;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    TMap<FString, FString> DisplayDetails_Loc;

    // todo: DisplayThumbnail - this is meant to be image data

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    FOnlineMessagePayloadData DataPayload;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online")
    int32 MaxRecipients = 0;

    static FShowSendMessageParameters FromNative(const FShowSendMessageParams &InObj);
    FShowSendMessageParams ToNative();
};

UENUM(BlueprintType, Meta = (ScriptName = "EPlatformMessageType"))
enum class EPlatformMessageType_ : uint8
{
    EmptyStore,
    ChatRestricted,
    UGCRestricted
};
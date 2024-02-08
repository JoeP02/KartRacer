// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#if EOS_HAS_AUTHENTICATION

#include "CoreMinimal.h"

EOS_ENABLE_STRICT_WARNINGS

enum class EOnlineStoreOfferItemType : uint8
{
    Durable = 0,
    Consumable = 1,
    Other = 2,
};

EOS_DISABLE_STRICT_WARNINGS

#endif // #if EOS_HAS_AUTHENTICATION
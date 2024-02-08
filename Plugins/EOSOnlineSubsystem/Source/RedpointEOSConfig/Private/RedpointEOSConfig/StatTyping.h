// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "RedpointEOSConfig/Types/StatTypingRule.h"

namespace Redpoint::EOS::Config
{

TArray<TTuple<FString, EStatTypingRule>> ParseStatTypingRules(const TArray<FString> &Value);

}
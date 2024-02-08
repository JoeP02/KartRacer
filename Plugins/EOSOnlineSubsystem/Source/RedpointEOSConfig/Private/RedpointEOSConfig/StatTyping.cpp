// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSConfig/StatTyping.h"

namespace Redpoint::EOS::Config
{

TArray<TTuple<FString, EStatTypingRule>> ParseStatTypingRules(const TArray<FString> &Value)
{
    TArray<TTuple<FString, EStatTypingRule>> Results;
    for (const FString &V : Value)
    {
        TArray<FString> Components;
        V.ParseIntoArray(Components, TEXT(":"));
        if (Components.Num() == 2)
        {
            EStatTypingRule Rule = EStatTypingRule::Int32;
            if (Components[1] == TEXT("Int32"))
            {
                Rule = EStatTypingRule::Int32;
            }
            else if (Components[1] == TEXT("Bool"))
            {
                Rule = EStatTypingRule::Bool;
            }
            else if (Components[1] == TEXT("FloatTruncated"))
            {
                Rule = EStatTypingRule::FloatTruncated;
            }
            else if (Components[1] == TEXT("FloatEncoded"))
            {
                Rule = EStatTypingRule::FloatEncoded;
            }
            else if (Components[1] == TEXT("DoubleEncoded"))
            {
                Rule = EStatTypingRule::DoubleEncoded;
            }
            Results.Add(TTuple<FString, EStatTypingRule>(Components[0], Rule));
        }
    }
    return Results;
}

} // namespace Redpoint::EOS::Config
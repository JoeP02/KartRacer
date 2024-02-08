// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace Redpoint::EOS::API
{

namespace ParamHelpers
{

template <typename T> class TRequired
{
private:
    T Value;

public:
    [[deprecated("This parameter must be initialised to a value. Use aggregate initialization in C++20 to initialize "
                 "all of the required Params fields.")]] TRequired() = delete;
    TRequired(const T &InValue)
        : Value(InValue){};
    TRequired(const TRequired &InOther)
        : Value(InOther.Value){};
    TRequired(TRequired &&Other) = delete;
    ~TRequired(){};

    TRequired(const char *InValue)
        : Value(FString(InValue)){};
    TRequired(const TCHAR *InValue)
        : Value(FString(InValue)){};

    const T &operator*() const
    {
        return Value;
    }
    const T &operator->() const
    {
        return Value;
    }
    operator T() const
    {
        return Value;
    }
    operator const T &() const
    {
        return Value;
    }
};

} // namespace ParamHelpers

} // namespace Redpoint::EOS::API
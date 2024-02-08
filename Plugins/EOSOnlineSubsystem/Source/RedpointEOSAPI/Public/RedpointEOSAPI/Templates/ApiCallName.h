// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Platform.h"
#include <array>

namespace Redpoint::EOS::API
{

namespace Private
{

namespace ApiCallName
{

template <std::size_t N> using Type = std::array<TCHAR, N>;

template <std::size_t N> constexpr Type<N> Constant(const TCHAR (&a)[N])
{
    Type<N> res{};
    for (std::size_t i = 0; i != N - 1; ++i)
    {
        res[i] = a[i];
    }
    return res;
}

template <std::size_t... Ns> constexpr Type<(Ns + ...)> Concat(const Type<Ns> &...as)
{
    Type<(Ns + ...)> res{};
    std::size_t i = 0;
    auto l = [&](const auto &a) {
        for (auto c : a)
        {
            if (c != '\0')
            {
                res[i++] = c;
            }
        }
    };
    (l(as), ...);
    for (; i < (Ns + ...); i++)
    {
        res[i] = '\0';
    }
    return res;
}

} // namespace ApiCallName

} // namespace Private

} // namespace Redpoint::EOS::API
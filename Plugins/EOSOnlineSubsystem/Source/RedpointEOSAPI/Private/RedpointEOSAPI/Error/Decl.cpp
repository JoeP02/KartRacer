// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/Error/Decl.h"

namespace Redpoint::EOS::API
{

FString FError::ToLogString() const
{
    return FString::Printf(
        TEXT("ErrorNamespace=%s ErrorCode=%s ErrorMessage='%s' OriginalCall=%s Context='%s'"),
        *(*this->ErrorNamespace),
        *(*this->ErrorCode),
        *(*this->ErrorMessage).ToString(),
        *(*this->OriginalCall),
        *(*this->Context));
}

} // namespace Redpoint::EOS::API
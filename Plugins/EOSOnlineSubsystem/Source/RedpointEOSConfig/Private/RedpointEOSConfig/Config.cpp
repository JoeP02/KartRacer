// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSConfig/Config.h"

namespace Redpoint::EOS::Config
{

bool ApiVersionIsAtLeast(EEOSApiVersion InConfigVersion, EEOSApiVersion InTargetVersion)
{
    return InConfigVersion <= InTargetVersion;
}

bool ApiVersionIsAtLeast(const IConfig &InConfig, EEOSApiVersion InTargetVersion)
{
    return ApiVersionIsAtLeast(InConfig.GetApiVersion(), InTargetVersion);
}

bool IConfig::HasSynthetics() const
{
    return !this->GetDelegatedSubsystemsString().IsEmpty();
}

} // namespace Redpoint::EOS::Config
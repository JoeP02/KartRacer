// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace Redpoint::EOS::Core
{

DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOSCore, Verbose, All);

}

// @note: This has moved from OnlineSubsystemRedpointEOS because RedpointEOSCore
// now handles forwarding the EOS SDK logs and thus we need to use it in this module.
REDPOINTEOSCORE_API DECLARE_LOG_CATEGORY_EXTERN(LogRedpointEOS, Verbose, All);
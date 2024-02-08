// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "RedpointEOSConfig/Config.h"

namespace Redpoint::EOS::Core
{

class FSDKGlobal
{
private:
    static bool bInitialized;
    static bool bShutdown;

public:
    /**
	 * Attempts to initialize the global parts of the EOS SDK. If the EOS SDK can't be initialized, this returns false.
	 */
    static bool Initialize(Redpoint::EOS::Config::IConfig& InConfig);

	/**
	 * Shuts down the EOS SDK globally. Once this is called, the SDK can't be initialized again and no platform calls will succeed.
	 */
    static void Shutdown();
};

} // namespace Redpoint::EOS::Core
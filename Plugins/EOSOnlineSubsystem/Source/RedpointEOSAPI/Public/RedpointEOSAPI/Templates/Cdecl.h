// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_ANDROID
#define __REDPOINT_EOSSDK_CDECL_ATTR
#else
#define __REDPOINT_EOSSDK_CDECL_ATTR __cdecl
#endif
// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#if defined(UNREAL_CODE_ANALYZER)
#if UNREAL_CODE_ANALYZER
// HACK: When running under clang-tidy, these get mapped to stdcall attributes for Windows, which causes all sorts of
// weird compilation errors that aren't true when actually building under MSVC.
#define EOS_CALL
#define EOS_MEMORY_CALL
#endif
#endif

#if defined(EOS_BUILD_PLATFORM_NAME)
#include "eos_platform_prereqs.h"

#include "eos_base.h"
#endif

#include "eos_version.h"

#define EOS_VERSION_AT_LEAST(MAJOR, MINOR, PATCH)                                                                      \
    ((EOS_MAJOR_VERSION > (MAJOR)) || (EOS_MAJOR_VERSION == (MAJOR) && EOS_MINOR_VERSION > (MINOR)) ||                 \
     (EOS_MAJOR_VERSION == (MAJOR) && EOS_MINOR_VERSION == (MINOR) && EOS_PATCH_VERSION >= (PATCH)))
#define EOS_VERSION_AT_MOST(MAJOR, MINOR, PATCH)                                                                       \
    ((EOS_MAJOR_VERSION < (MAJOR)) || (EOS_MAJOR_VERSION == (MAJOR) && EOS_MINOR_VERSION < (MINOR)) ||                 \
     (EOS_MAJOR_VERSION == (MAJOR) && EOS_MINOR_VERSION == (MINOR) && EOS_PATCH_VERSION <= (PATCH)))

#include "eos_achievements.h"
#include "eos_auth.h"
#include "eos_common.h"
#include "eos_connect.h"
#include "eos_ecom.h"
#include "eos_friends.h"
#include "eos_leaderboards.h"
#include "eos_lobby.h"
#include "eos_logging.h"
#include "eos_metrics.h"
#include "eos_p2p.h"
#include "eos_playerdatastorage.h"
#include "eos_presence.h"
#include "eos_reports.h"
#include "eos_sanctions.h"
#include "eos_sdk.h"
#include "eos_sessions.h"
#include "eos_stats.h"
#include "eos_titlestorage.h"
#include "eos_ui.h"
#include "eos_userinfo.h"
#if PLATFORM_IOS
#include "eos_ios.h"
#endif
#include "eos_anticheatclient.h"
#if WITH_SERVER_CODE
#include "eos_anticheatserver.h"
#endif
#include "eos_rtc.h"
#include "eos_rtc_admin.h"
#include "eos_rtc_audio.h"

#include "RedpointEOSAPI/Templates/Cdecl.h"
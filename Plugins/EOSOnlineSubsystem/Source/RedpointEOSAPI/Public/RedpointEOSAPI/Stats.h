// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Stats/Stats.h"

// Stat group for all Redpoint EOS stats.
DECLARE_STATS_GROUP(TEXT("RedpointEOS"), STATGROUP_RedpointEOS, STATCAT_Advanced);

// Trace declaration macros.
#define REDPOINT_EOS_DECLARE_CYCLE_STAT(CounterScope, CounterName, StatIdSuffix)                                       \
    DECLARE_CYCLE_STAT_EXTERN(                                                                                         \
        TEXT("RedpointEOS/") TEXT(PREPROCESSOR_TO_STRING(CounterScope)) TEXT("/") CounterName,                         \
        STAT_RedpointEOS_##CounterScope##_##StatIdSuffix,                                                              \
        STATGROUP_RedpointEOS,                                                                                         \
        ONLINESUBSYSTEMREDPOINTEOS_API)
#define REDPOINT_EOS_DEFINE_STAT(CounterScope, StatIdSuffix)                                                           \
    DEFINE_STAT(STAT_RedpointEOS_##CounterScope##_##StatIdSuffix)
#define REDPOINT_EOS_DECLARE_CYCLE_STAT_INLINE(CounterScope, CounterName, StatIdSuffix)                                \
    REDPOINT_EOS_DECLARE_CYCLE_STAT(CounterScope, CounterName, StatIdSuffix);                                          \
    REDPOINT_EOS_DEFINE_STAT(CounterScope, StatIdSuffix)
#define REDPOINT_EOS_DECLARE_CYCLE_STAT_INLINE_WITH_CALLBACK(CounterScope, CounterName, StatIdSuffix)                  \
    REDPOINT_EOS_DECLARE_CYCLE_STAT_INLINE(CounterScope, CounterName, StatIdSuffix);                                   \
    REDPOINT_EOS_DECLARE_CYCLE_STAT_INLINE(CounterScope, CounterName TEXT("/Callback"), StatIdSuffix##_Callback)

// Trace usage macros.
#define REDPOINT_EOS_SCOPE_CYCLE_COUNTER(CounterScope, StatIdSuffix)                                                   \
    SCOPE_CYCLE_COUNTER(STAT_RedpointEOS_##CounterScope##_##StatIdSuffix)
#define REDPOINT_EOS_TRACE_COUNTER_SET(Ctr, CtrValue) TRACE_COUNTER_SET(Ctr, CtrValue)
#define REDPOINT_EOS_TRACE_COUNTER_INCREMENT(Ctr) TRACE_COUNTER_INCREMENT(Ctr)
#define REDPOINT_EOS_TRACE_COUNTER_ADD(Ctr, CtrValue) TRACE_COUNTER_ADD(Ctr, CtrValue)
#define REDPOINT_EOS_INC_DWORD_STAT(StatName) INC_DWORD_STAT(StatName)
#define REDPOINT_EOS_INC_DWORD_STAT_BY(StatName, StatValue) INC_DWORD_STAT_BY(StatName, StatValue)
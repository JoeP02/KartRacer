// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "StatTypingRule.generated.h"

UENUM()
enum class EStatTypingRule : uint8
{
    /**
     * The stat is stored as a 32-bit signed integer. This is the native stat format for EOS, and is compatible
     * with achievements and leaderboards.
     *
     * On the EOS backend, the stat can be configured as LATEST, SUM, MIN or MAX.
     */
    Int32 UMETA(DisplayName = "Int32"),

    /**
     * The boolean value is converted to a 32-bit signed integer (either a 0 or a 1). Because this value can be
     * entirely contained within a 32-bit signed integer, this stat is compatible with achievements and leaderboards.
     *
     * When configuring achievements, remember that the values for this stat can be either 0 or 1, so you'll typically
     * want to unlock the achievement on a value of 1.
     *
     * On the EOS backend, the stat can be configured as LATEST, SUM, MIN or MAX.
     */
    Bool UMETA(DisplayName = "Boolean"),

    /**
     * The floating point value is multiplied by 10,000,000, truncated and stored as an int32. This preserves
     * ordering and permits it's use in leaderboards, at the cost of range. The maximum range for a stat
     * using truncated floats is -214.7483648 to 214.7483647.
     *
     * When using this stat with achievements and leaderboards, you must remember that the values will
     * be stored with the multipler, and set achievement thresholds appropriately, and divide by 10,000,000
     * when displaying leaderboard values.
     *
     * On the EOS backend, the stat can be configured as LATEST, SUM, MIN or MAX.
     */
    FloatTruncated UMETA(DisplayName = "Float (Truncated)"),

    /**
     * The bits that make up the floating point number are treated as an int32, and this value is stored.
     * This preserves the precision of the floating point number, and allows you to store the full range of values,
     * at the cost of ordering (making it unsuitable for achievements and leaderboards). You should only read
     * these kinds of stats through QueryStats.
     *
     * On the EOS backend, the stat must be configured as LATEST.
     */
    FloatEncoded UMETA(DisplayName = "Float (Encoded)"),

    /**
     * The bits that make up the double floating point number are split into two int32 values, and these are
     * independently stored in EOS with the name <stat>_upper and <stat>_lower.
     *
     * This preserves the precision of the double floating point number, and allows you to store the full range
     * of values, but does not preserve ordering and you can't use the values in any other system (achievements
     * or leaderboards), as the value is split over two underlying stats.
     *
     * On the EOS backend, both the <stat>_upper and <stat>_lower stats must be configured as LATEST.
     */
    DoubleEncoded UMETA(DisplayName = "Double (Encoded)")
};
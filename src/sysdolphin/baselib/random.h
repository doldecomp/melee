/**
 * @file random.h
 * @brief Pseudo-Random Number Generator (PRNG)
 * @details Implements a linear congruential generator used for AI decisions, item spawns, and effects.
 */
#ifndef _random_h_
#define _random_h_

#include <Runtime/platform.h>

/**
 * @brief Generates a random 32-bit signed integer.
 * @return Random integer
 */
s32 HSD_Rand(void);
/**
 * @brief Generates a random float between 0.0 and 1.0.
 * @return Random float
 */
f32 HSD_Randf(void);
/**
 * @brief Generates a random 32-bit signed integer between 0 and max_val - 1.
 * @param max_val The upper bound (exclusive)
 * @return Random integer
 */
s32 HSD_Randi(s32 max_val);
/**
 * @brief Restores the seed pointer if it falls within the specified memory range.
 * @param low Lower bound of memory range
 * @param high Upper bound of memory range
 */
void _HSD_RandForgetMemory(void* low, void* high);
extern u32* HSD_RandSeedPtr;

/// #HSD_Randi that accepts an empty range.
static inline int randi(int max_val)
{
    if (max_val != 0) {
        return HSD_Randi(max_val);
    }
    return 0;
}

#endif

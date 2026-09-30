/**
 * @file random.c
 * @brief Pseudo-Random Number Generator (PRNG)
 * @details Implements a linear congruential generator used for AI decisions, item spawns, and effects.
 */
#include "random.h"

static u32 seed = 1;
u32* HSD_RandSeedPtr = &seed;

/**
 * @brief Generates a random 32-bit signed integer.
 */
s32 HSD_Rand(void)
{
    *HSD_RandSeedPtr = *HSD_RandSeedPtr * 214013 + 2531011;
    return *HSD_RandSeedPtr >> 0x10;
}

/**
 * @brief Generates a random float between 0.0 and 1.0.
 */
f32 HSD_Randf(void)
{
    *HSD_RandSeedPtr = *HSD_RandSeedPtr * 214013 + 2531011;
    return (f32) (*HSD_RandSeedPtr >> 0x10) / (1 << 16);
}

/**
 * @brief Generates a random 32-bit signed integer between 0 and max_val - 1.
 */
s32 HSD_Randi(s32 max_val)
{
    return max_val * HSD_Rand() / (1 << 16);
}

/**
 * @brief Restores the seed pointer if it falls within the specified memory range.
 */
void _HSD_RandForgetMemory(void* low, void* high)
{
    if (low <= (void*) HSD_RandSeedPtr && (void*) HSD_RandSeedPtr < high) {
        HSD_RandSeedPtr = &seed;
    }
}

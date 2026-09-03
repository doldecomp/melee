#include "random.h"

u32 seed = 1;
u32* seed_ptr = &seed;

s32 HSD_Rand(void)
{
    *seed_ptr = *seed_ptr * 214013 + 2531011;
    return *seed_ptr >> 0x10;
}

f32 HSD_Randf(void)
{
    *seed_ptr = *seed_ptr * 214013 + 2531011;
    return (f32) (*seed_ptr >> 0x10) / (1 << 16);
}

s32 HSD_Randi(s32 max_val)
{
    return max_val * HSD_Rand() / (1 << 16);
}

void _HSD_RandForgetMemory(void* low, void* high)
{
    if (low <= (void*) seed_ptr && (void*) seed_ptr < high) {
        seed_ptr = &seed;
    }
    return;
}

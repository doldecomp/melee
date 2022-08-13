#include <sysdolphin/baselib/random.h>

u32 seed = 1;
u32* seed_ptr = &seed;

s32 HSD_Rand(void)
{
    *seed_ptr = *seed_ptr * 214013 + 2531011;
    return *seed_ptr >> 0x10;
}

inline s32 HSD_Rand_inline(void)
{
    *seed_ptr = *seed_ptr * 214013 + 2531011;
    return *seed_ptr >> 0x10;
}

f32 HSD_Randf(void) {
    *seed_ptr = *seed_ptr * 214013 + 2531011;
    return (f32)(*seed_ptr >> 0x10) / 65536;
}

s32 HSD_Randi(s32 max_val) {
    return (max_val * HSD_Rand_inline()) / 0x10000;
}

void _HSD_RandForgetMemory(u32* low, u32* high)
{
    if (low <= seed_ptr && seed_ptr < high){
        seed_ptr = &seed;
    }
    return;
}

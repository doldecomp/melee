#ifndef _random_h_
#define _random_h_

#include <Runtime/platform.h>

s32 HSD_Rand(void);
f32 HSD_Randf(void);
s32 HSD_Randi(s32 max_val);
void _HSD_RandForgetMemory(any_t low, any_t high);

#endif

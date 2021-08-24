#ifndef _random_h_
#define _random_h_

#include "global.h"

s32 HSD_Rand(void);
f32 HSD_Randf(void);
s32 HSD_Randi(s32 max_val);
void _HSD_RandForgetMemory(u32* low, u32* high);

#endif

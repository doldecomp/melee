#ifndef _lbtime_h_
#define _lbtime_h_

#include <dolphin/os/OSTime.h>

extern s64 __div2i(s64, s64);

u32 func_8000AEC8(u32 a, u32 b);
u32 func_8000AEE4(u32 a, int b);
u32 func_8000AF24(u32 a, int b, int c);
u32 func_8000AF74(u32 a, int b);
u32 func_8000AFBC(void);
void func_8000B028(OSCalendarTime* td, unsigned int ticks);

#endif

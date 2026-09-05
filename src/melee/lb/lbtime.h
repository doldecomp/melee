#ifndef MELEE_LB_LBTIME_H
#define MELEE_LB_LBTIME_H

#include <dolphin/os.h>
#include <Runtime/platform.h>

u32 lbTime_8000AEC8(u32 a, u32 b);
u32 lbTime_8000AEE4(u32 a, int b);
u32 lbTime_8000AF24(u32 a, int b);
u32 lbTime_8000AF74(u32 a, int b);
u32 lbTime_GetTimeInSeconds(void);
void lbTime_8000B028(OSCalendarTime* td, unsigned int secs);

#endif

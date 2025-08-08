#include "lb/lbtime.h"

#define UINT_MAX 0xFFFFFFFF

u32 lbTime_8000AEC8(u32 a, u32 b)
{
    return -1 - a > b ? a + b : -1;
}

u32 lbTime_8000AEE4(u32 a, int b)
{
    if (b > 0) {
        return -1 - a > (unsigned) b ? a + b : -1;
    } else {
        return a > (unsigned) -b ? a + b : 0;
    }
}

u32 lbTime_8000AF24(u32 a, int b)
{
    int c;
    if (b > 0) {
        unsigned int ab = a & 0x0000ffff;
        c = 0x0000ffff;
        if (c - ab > (unsigned) b) {
            return a + b;
        } else {
            return c;
        }
    } else {
        c = a & 0xffff;

        if (c > -b) {
            return a + b;
        } else {
            return 0;
        }
    }
}

u32 lbTime_8000AF74(u32 a, int b)
{
    if (b > 0) {
        u32 r0 = a & 0xff;
        r0 = 0xff - r0;

        return (r0 > (unsigned) b) ? a + b : 0xff;
    } else {
        int c = a & 0xff;

        return (c > -b) ? a + b : 0;
    }
}

u32 lbTime_8000AFBC(void)
{
    u64 secs = OSTicksToSeconds(OSGetTime());
    if (secs > UINT_MAX) {
        secs = UINT_MAX;
    }
    return secs;
}

void lbTime_8000B028(OSCalendarTime* td, unsigned int secs)
{
    OSTicksToCalendarTime(OSSecondsToTicks((u64) secs), td);
}

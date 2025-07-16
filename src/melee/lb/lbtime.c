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
    u64 uVar3 = OSGetTime() / (*(u32*) 0x800000F8 / 4);
    if (uVar3 > UINT_MAX) {
        uVar3 = UINT_MAX;
    }
    return uVar3;
}

void lbTime_8000B028(OSCalendarTime* td, unsigned int ticks)
{
    OSTicksToCalendarTime(
        (u64) ticks * (long long) ((*(unsigned int*) 0x800000F8) >> 2), td);
}

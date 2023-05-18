#include <Gecko_setjmp.h>
#include <string.h>
#include <baselib/__baselib.h>
#include <baselib/hsd_3B33.h>

void hsd_803B3344(u8 byte)
{
    u8* temp_r5;

    temp_r5 = hsd_804D79A0;
    if ((u32) temp_r5 < (u32) hsd_804D79A4 + (u32) hsd_804D79A8) {
        hsd_804D79A0 = temp_r5 + 1;
        *temp_r5 = byte;
        return;
    }

    longjmp(&hsd_804D2648, true);
}

void hsd_803B3398(void* src, size_t size)
{
    void* temp_r3 = hsd_804D79A0;

    if ((u32) temp_r3 < (u32) hsd_804D79A4 + (u32) hsd_804D79A8 - size) {
        memcpy(temp_r3, src, size);
        *((u32*) &hsd_804D79A0) += size;
        return;
    }

    longjmp(&hsd_804D2648, true);
}

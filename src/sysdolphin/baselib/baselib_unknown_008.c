#include <sysdolphin/baselib/__baselib.h>
#include <dolphin/gecko.h>
#include <string.h>

void func_803B3344(u8 byte)
{
    u8 *temp_r5;

    temp_r5 = lbl_804D79A0;
    if ((u32)temp_r5 < (u32)lbl_804D79A4 + (u32)lbl_804D79A8)
    {
        lbl_804D79A0 = temp_r5 + 1;
        *temp_r5 = byte;
        return;
    }

    longjmp(&lbl_804D2648, TRUE);
}

void func_803B3398(void *src, size_t size)
{
    void *temp_r3 = lbl_804D79A0;

    if ((u32)temp_r3 < (u32)lbl_804D79A4 + (u32)lbl_804D79A8 - size)
    {
        memcpy(temp_r3, src, size);
        *((u32 *)&lbl_804D79A0) += size;
        return;
    }

    longjmp(&lbl_804D2648, TRUE);
}

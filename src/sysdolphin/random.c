#include "random.h"

extern u32* lbl_804D5F94; //seed

s32 HSD_Rand(void)
{
    *lbl_804D5F94 = *lbl_804D5F94 * 214013 + 2531011;
    return *lbl_804D5F94 >> 0x10;
}

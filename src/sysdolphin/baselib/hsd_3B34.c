#include "hsd_3B34.h"

#include "hsd_3A94.h"

/// hsd_803B5C2C
static int lbl_804D6398 = 3;

extern u8* hsd_804D79B8;
extern s32 hsd_804D79BC;
extern s32 hsd_804D79C0;
extern s32 hsd_804D79C4;
extern u8 hsd_804D79C8;

void hsd_803B5C2C(int mode)
{
    lbl_804D6398 = mode;
    if ((mode < 1) || (mode > 10)) {
        lbl_804D6398 = 3;
    }
}

int hsd_803B5C4C(int arg0)
{
    __jmp_buf* env = (__jmp_buf*) hsd_804D2E70;
    int var_r29;
    int var_r30;

    var_r30 = 0;
    var_r29 = arg0;
    do {
        if (hsd_804D79C4 == 0) {
            hsd_804D79C4 = 8;
            if (hsd_804D79B8 >= (u8*) (hsd_804D79BC + hsd_804D79C0)) {
                longjmp(env, 1);
            }
            hsd_804D79C8 = *hsd_804D79B8++;
            if (hsd_804D79C8 == 0xFF) {
                if (*hsd_804D79B8 != 0) {
                    longjmp(env, 1);
                } else {
                    if (hsd_804D79B8 >= (u8*) (hsd_804D79BC + hsd_804D79C0)) {
                        longjmp(env, 1);
                    }
                    hsd_804D79B8 += 1;
                }
            }
        }
        var_r30 *= 2;
        if (hsd_804D79C8 & (1 << (hsd_804D79C4 - 1))) {
            var_r30 |= 1;
        }
        var_r29 -= 1;
        hsd_804D79C4 -= 1;
    } while (var_r29 != 0);
    return var_r30;
}

#include <melee/if/ifstatus.h>

extern s8 lbl_804D6D60;

void func_802F665C(s8 arg0)
{
    s32 i;

    func_802F343C();
    lbl_804D6D60 = arg0;
    for (i = 0; i < 6; i++) {
        func_802F6508(i);
    }
}

#include "ftMasterHand.h"

// 80155C88 152868
void func_80155C88(HSD_GObj* gobj) {
    return;
}



// 80155C8C 15286C
void func_80155C8C(HSD_GObj* gobj) {
    return;
}



// 80155C90 152870
void func_80155C90(HSD_GObj* gobj) {
    return;
}



// 80155C94 152874
// https://decomp.me/scratch/8Kpd7
void func_80155C94(HSD_GObj* gobj) {
    Fighter* ft;

    ft = gobj->user_data;
    Fighter_ActionStateChange_800693AC(gobj, 0x149, 0, 0, 0.0f, 1.0f, 0.0f);
    ft->x221E_flag.bits.b0 = 1;
    func_8007E2F4(ft, 0x1FF);
    ft->x2220_flag.bits.b3 = 1;
    func_8006EBA4(gobj);
}


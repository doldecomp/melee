#include "ftpurin.h"


extern s32 lbl_8045A1E0[5];

void func_8013C2F8() {
    lbl_8045A1E0[0] = 0;
    lbl_8045A1E0[1] = 0;
    lbl_8045A1E0[2] = 0;
    lbl_8045A1E0[3] = 0;
    lbl_8045A1E0[4] = 0;
}

void ftPurin_OnDeath(HSD_GObj* fighterObj) {
    func_80074A4C(fighterObj, 0, 0);
}

void func_8013C340(HSD_GObj* fighterObj) {
    func_8013C494(fighterObj);
}


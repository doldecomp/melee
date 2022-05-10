#include "ftMasterHand.h"

// 80155D1C 1528FC
// https://decomp.me/scratch/YDeLe
void func_80155D1C(HSD_GObj* gobj) {
    Fighter* ft;

    ft = gobj->user_data;
    ft->x221E_flag.bits.b0 = 0;
    ft->x2C_facing_direction = -ft->x2C_facing_direction;
    func_800DC750(gobj);
}




// 80155D5C 15293C
void func_80155D5C(HSD_GObj* gobj) {
    return;
}



// 80155D60 152940
void func_80155D60(HSD_GObj* gobj) {
    return;
}



// 80155D64 152944
void func_80155D64(HSD_GObj* gobj) {
    return;
}



// 80155D68 152948
void func_80155D68(HSD_GObj* gobj) {
    return;
}



// 80155D6C 15294C
// https://decomp.me/scratch/y3wmm
void func_80155D6C(HSD_GObj* gobj, s32 arg1) {
    Fighter* ft;
    s32 unused[6];

    ft = gobj->user_data;
    ft->x2C_facing_direction = ((Fighter*)ft->x1A58_interactedFighter->user_data)->x2C_facing_direction;
    ft->x2340_stateVar1 = 0;
    Fighter_ActionStateChange_800693AC(gobj, 0x14A, 0, 0, 0.0f, 1.0f, 0.0f);
    ft->x221E_flag.bits.b0 = 0;
    ft->cb.x21B0_callback_Accessory1 = &func_800DE508;
    func_8007E2F4(ft, 0x1FFU);
    func_8006EBA4(gobj);
}




// 80155E08 1529E8
void func_80155E08(HSD_GObj* gobj) {
    return;
}



// 80155E0C 1529EC
void func_80155E0C(HSD_GObj* gobj) {
    return;
}



// 80155E10 1529F0
void func_80155E10(HSD_GObj* gobj) {
    return;
}



// 80155E14 1529F4
void func_80155E14(HSD_GObj* gobj) {
    return;
}


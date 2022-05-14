#include "ftness.h"



void lbl_80114BF4(HSD_GObj* arg0) {
    func_80088148(arg0->user_data, 0xE0U, 0x7FU, 0x40U);
};

void* func_802AD478(HSD_GObj*, void*, s32, f32);        /* extern */
extern void func_801148F8();
extern f32 lbl_804D96B8;
extern f32 lbl_804D96BC;

void func_80114C24(HSD_GObj* gobj) {
    Fighter* ft;
    void* tmp;
    int unused[2];

    ft = gobj->user_data;
    ft->x2218_flag.bits.b0 = 0;
    ft->x2200_ftcmd_var0 = 0;
    Fighter_ActionStateChange_800693AC(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    tmp = func_802AD478(gobj, &ft->xB0_pos, 0x2A, ft->x2C_facing_direction);
    ft->sa.ness.x2248 = tmp;
    if (tmp != 0) {
        ft->cb.x21E4_callback_OnDeath2 = func_801148F8;
        ft->cb.x21DC_callback_OnTakeDamage = func_801148F8;
    }
};

#include "ftclink.h"

extern void func_800EAF58(HSD_GObj*);

void func_80149354(HSD_GObj* gobj)
{
    void* temp_r3;
    Fighter* ft;
    Fighter* ft2;
    int unused[4];

    ft = ft2 = gobj->user_data;

    if (ft->x2204_ftcmd_var1 == 1 && ft->sa.clink.x2244 == 0) {
        temp_r3 = func_802C8B28(gobj, &ft->xB0_pos, func_8007500C(ft2, 0x1F),
                                ft->x2C_facing_direction);
        ft->sa.clink.x2244 = (u32) temp_r3;
        if (temp_r3 != NULL) {
            ft->cb.x21E4_callback_OnDeath2 = func_800EAF58;
            ft->cb.x21DC_callback_OnTakeDamage = func_800EAF58;
        }
    } else if (ft2->x2204_ftcmd_var1 == 2) {
        func_80149268(gobj);
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        checkFighter2244(gobj);
        func_8008A2BC(gobj);
    }
}

void func_8014943C(HSD_GObj* gobj)
{
    func_800DED30(gobj);
}

void func_8014945C(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void func_8014947C(HSD_GObj* gobj)
{
    func_80084280(gobj);
}

#include "ftcliffcommon.h"

// func_80081298

// func_80081370

void func_80081504(s32 arg0)
{
    if (func_8006F238() == 0)
    {
        func_8009A804(arg0);
    }
}

void func_80081540() {}

void func_80081544(HSD_GObj* gobj) {
    s32 dummy1[1];
    f32 sp10[2];
    s32 dummy2[1];

    Fighter* fighter = gobj->user_data;
    if (func_80054ED8(fighter->x2340_stateVar) != 0) {
        if (fighter->x2C_facingDirection > 0.0f) {
            func_80053ECC(fighter->x2340_stateVar, sp10);
        } else {
            func_80053DA4(fighter->x2340_stateVar, sp10);
        }
        fighter->xB0_pos.x = (f32) ((fighter->x68C.z * fighter->x2C_facingDirection) + sp10[0]);
        fighter->xB0_pos.y = (f32) (sp10[1] + fighter->x68C.y);
        return;
    }
    func_800CC730(gobj);
}

extern CommonAttributes* lbl_804D6554;

void func_800815E4(HSD_GObj* gobj) {
    Fighter* fighter;
    s32 unused1, unused2;
    if (func_800821DC() != 0) {
        func_80082B1C(gobj);
        return;
    }
    if (func_8009EF68(gobj) != 0) {
        fighter = gobj->user_data;
        fighter->x2064_ledgeCooldown = lbl_804D6554->x498_ledgeCooldownTime;
    }
}

void func_80081644(HSD_GObj* gobj)
{
    Fighter* fighter = gobj->user_data;
    func_800761C8();
    if ((s32) fighter->xE0_airState == 1)
    {
        func_8005811C(&fighter->x6F0_collData, fighter->x2340_stateVar);
        fighter->x890->xC_flag.b0 = 1;
    }
}

#include "ftmars.h"

// 80136258 00132E38
// https://decomp.me/scratch/6RQ5w
void ftMars_OnDeath(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, 0);
    ft->x222C = 0;
}

// 801362B0 00132E90
// ftMars_OnItemPickup
// https://decomp.me/scratch/cdTAI
void func_801362B0(HSD_GObj* gobj, s32 arg1) {
    Fighter* ft = gobj->user_data;
    s32 unused, unused2; // need to gobble some stack

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        switch (func_8026B320(ft->x1974_heldItem)) {
            case 1:
                func_80070FB4(gobj, 0, 1);
                break;
            case 2:
                func_80070FB4(gobj, 0, 0);
                break;
            case 3:
                func_80070FB4(gobj, 0, 2);
                break;
            case 4:
                func_80070FB4(gobj, 0, 3);
                break;
        }

        if (arg1 != 0) {
            func_80070C48(gobj, 1);
        }
    }
}

// 80136390 00132F70
// ftMars_OnItemInvisible
// https://decomp.me/scratch/BksNr
void func_80136390(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 0);
    }
}

// 801363D8 00132FB8
// ftMars_OnItemVisible
// https://decomp.me/scratch/9zuEy
void func_801363D8(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 0);
    }
}

// 80136420 00133000
// ftMars_OnItemRelease
// https://decomp.me/scratch/Ws8ow
void func_80136420(HSD_GObj* gobj, s32 arg1) {
    func_80070FB4(gobj, 0, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

// 80136474 00133054
// https://decomp.me/scratch/2TlGi
void func_80136474(Fighter* ft) {
    MarsAttributes* sA2 = ft->x2D8_specialAttributes2;
    MarsAttributes* ext_attr = ft->x10C_ftData->ext_attr;
    *sA2 = *ext_attr;
    ft->x2D4_specialAttributes = sA2;
}

// 801364AC 0013308C
// https://decomp.me/scratch/9UJHY
void ftMars_OnLoad(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    MarsAttributes* sA2 = ft->x2D8_specialAttributes2;
    *(MarsAttributes*)ft->x2D8_specialAttributes2 = *(MarsAttributes*)ft->x10C_ftData->ext_attr;
    ft->x2D4_specialAttributes = sA2;
}

// 801364E8 001330C8
// https://decomp.me/scratch/tfzFL
void func_801364E8(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    MarsAttributes* a = ft->x10C_ftData->ext_attr;
    MarsAttributes* b = ft->x2D4_specialAttributes;
    *b = *a;
}

// 80136520 00133100
// ftMars_OnKnockbackEnter
// https://decomp.me/scratch/rgfFA
void func_80136520(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

// 80136564 00133144
// https://decomp.me/scratch/Jqd2A
void func_80136564(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

// 801365A8 00133188
// https://decomp.me/scratch/Jqd2A
void lbl_801365A8(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    s32 result;
    if (!ft->x2219_flag.bits.b0) {
        result = func_800872A4(gobj);
        switch (result) {
            case 0x12:
                ef_Spawn(0x4F2, gobj, ft->x5E8_fighterBones->x0_joint);
                break;
            case 0x1A:
                ef_Spawn(0x511, gobj, ft->x5E8_fighterBones->x0_joint);
                break;
        }
        ft->x2219_flag.bits.b0 = 1;
    }

    ft->x21D4_callback_EnterHitlag = efLib_PauseAll;
    ft->x21D8_callback_ExitHitlag = efLib_ResumeAll;
    ft->x21BC_callback_Accessory4 = 0;
    return;
}

// 8013666C 0013324C
// https://decomp.me/scratch/Jqd2A
void lbl_8013666C(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    s32 result;
    if (!ft->x2219_flag.bits.b0) {
        result = func_800872A4(gobj);
        switch (result) {
            case 0x12:
                ef_Spawn(0x4F3, gobj, ft->x5E8_fighterBones->x0_joint);
                break;
            case 0x1A:
                ef_Spawn(0x512, gobj, ft->x5E8_fighterBones->x0_joint);
                break;
        }
        ft->x2219_flag.bits.b0 = 1;
    }

    ft->x21D4_callback_EnterHitlag = efLib_PauseAll;
    ft->x21D8_callback_ExitHitlag = efLib_ResumeAll;
    ft->x21BC_callback_Accessory4 = 0;
    return;
}

// 80136730 00133310
// https://decomp.me/scratch/Jqd2A
void lbl_80136730(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2340_stateVar1 = 0;
}

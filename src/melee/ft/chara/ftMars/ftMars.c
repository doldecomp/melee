#include <melee/ft/chara/ftMars/ftMars.h>

// 80136258 00132E38
// https://decomp.me/scratch/6RQ5w
void ftMars_OnDeath(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, 0);
    fp->sa.mars.x222C = 0;
}

// 801362B0 00132E90
// ftMars_OnItemPickup
void ftMars_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 0, 1);
}

// 80136390 00132F70
// ftMars_OnItemInvisible
// https://decomp.me/scratch/BksNr
void ftMars_OnItemInvisible(HSD_GObj* gobj) {
    Fighter_OnItemInvisible(gobj, 0);
}

// 801363D8 00132FB8
// ftMars_OnItemVisible
// https://decomp.me/scratch/9zuEy
void ftMars_OnItemVisible(HSD_GObj* gobj) {
    Fighter_OnItemVisible(gobj, 0);
}

// 80136420 00133000
// ftMars_OnItemDrop
// https://decomp.me/scratch/Ws8ow
void ftMars_OnItemDrop(HSD_GObj* gobj, BOOL bool1) {
    Fighter_OnItemDrop(gobj, bool1, 0, 1);
}

// 80136474 00133054
// https://decomp.me/scratch/2TlGi
void ftMars_OnLoadForRoy(Fighter* fp) {
    PUSH_ATTRS(fp, MarsAttributes);
}

// 801364AC 0013308C
// https://decomp.me/scratch/9UJHY
void ftMars_OnLoad(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    PUSH_ATTRS(fp, MarsAttributes);
}

// 801364E8 001330C8
// https://decomp.me/scratch/tfzFL
void ftMars_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, MarsAttributes);
}

// 80136520 00133100
// ftMars_OnKnockbackEnter
// https://decomp.me/scratch/rgfFA
void ftMars_OnKnockbackEnter(HSD_GObj* gobj) {
    Fighter_OnKnockbackEnter(gobj, 1);
}

// 80136564 00133144
// https://decomp.me/scratch/Jqd2A
void ftMars_OnKnockbackExit(HSD_GObj* gobj) {
    Fighter_OnKnockbackExit(gobj, 1);
}

// 801365A8 00133188
// https://decomp.me/scratch/Jqd2A
void lbl_801365A8(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_flag.bits.b0) {
        result = func_800872A4(gobj);
        switch (result) {
            case 0x12:
                ef_Spawn(0x4F2, gobj, fp->x5E8_fighterBones->x0_jobj);
                break;
            case 0x1A:
                ef_Spawn(0x511, gobj, fp->x5E8_fighterBones->x0_jobj);
                break;
        }
        fp->x2219_flag.bits.b0 = 1;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
    return;
}

// 8013666C 0013324C
// https://decomp.me/scratch/Jqd2A
void lbl_8013666C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 result;
    if (!fp->x2219_flag.bits.b0) {
        result = func_800872A4(gobj);
        switch (result) {
            case 0x12:
                ef_Spawn(0x4F3, gobj, fp->x5E8_fighterBones->x0_jobj);
                break;
            case 0x1A:
                ef_Spawn(0x512, gobj, fp->x5E8_fighterBones->x0_jobj);
                break;
        }
        fp->x2219_flag.bits.b0 = 1;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
    return;
}

// 80136730 00133310
// https://decomp.me/scratch/Jqd2A
void lbl_80136730(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2340_stateVar1 = 0;
}

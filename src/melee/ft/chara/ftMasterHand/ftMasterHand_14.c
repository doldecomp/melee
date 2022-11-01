#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

#include <melee/lb/lbunknown_001.h>

// 80152BC8 14F7A8
void lbl_80152BC8(HSD_GObj* gobj) {
    return;
}


// 80152BCC 14F7AC
// https://decomp.me/scratch/Lyvr5
void lbl_80152BCC(HSD_GObj* arg0) {
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    Fighter_ActionStateChange_800693AC(arg0, 0x169, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
    temp_r31->x2368 = -1;
    temp_r31->x236C = -1;
    temp_r31->x2370 = -1;
}

void ftMasterHand_80152CD8(HSD_GObj* fighter_gobj);

void ftMasterHand_80152C34(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) {
        ftMasterHand_80152CD8(fighter_gobj);
    }
}

// 80152C70 14F850
// https://decomp.me/scratch/5SqNT
void lbl_80152C70(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftbosslib_8015BD20(arg0);
    }
}



// 80152CB4 14F894
// https://decomp.me/scratch/ZDCi1
void lbl_80152CB4(HSD_GObj* arg0) {
    func_80085134(arg0);
}



// 80152CD4 14F8B4
void lbl_80152CD4(HSD_GObj *arg0) {
    return;
}

static void ftMasterHand_80152CD8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16A, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &lbl_80152E28;
    fp->x2200_ftcmd_var0 = 1;
}

void ftMasterHand_80152F80(HSD_GObj* fighter_gobj);

void ftMasterHand_80152D44(HSD_GObj* fighter_gobj)
{
    Fighter* fp;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) {
        fp = fighter_gobj->user_data;
        ftMasterHand_80152F80(fighter_gobj);
        func_802F046C(fp->x2374);
        func_802F046C(fp->x2378);
        func_802F046C(fp->x237C);
        func_802F046C(fp->x2380);
        fp->x2374 = 0;
        fp->x2378 = 0;
        fp->x237C = 0;
        fp->x2380 = 0;
    }
}

// 80152DC0 14F9A0
// https://decomp.me/scratch/X13ZG
void lbl_80152DC0(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftbosslib_8015BD20(arg0);
    }
}


// 80152E04 14F9E4
// https://decomp.me/scratch/BwM1c
void lbl_80152E04(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 80152E24 14FA04
void lbl_80152E24(HSD_GObj* gobj) {
    return;
}



// 80152E28 14FA08
// https://decomp.me/scratch/Uqf2Q
void lbl_80152E28(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 unk1;
    Vec3 sp10;
    s32 unk2;

    if (fp->x2200_ftcmd_var0 != 0) {
        func_8000B1CC(fp->x5E8_fighterBones[11].x0_jobj, 0, &sp10);
        fp->x2374 = func_802F0340(gobj, &sp10, &sp10, 0xB, 0x7D, fp->x2C_facing_direction);
        func_8000B1CC(fp->x5E8_fighterBones[16].x0_jobj, 0, &sp10);
        fp->x2378 = func_802F0340(gobj, &sp10, &sp10, 0x10, 0x7D, fp->x2C_facing_direction);
        func_8000B1CC(fp->x5E8_fighterBones[21].x0_jobj, 0, &sp10);
        fp->x237C = func_802F0340(gobj, &sp10, &sp10, 0x15, 0x7D, fp->x2C_facing_direction);
        func_8000B1CC(fp->x5E8_fighterBones[26].x0_jobj, 0, &sp10);
        fp->x2380 = func_802F0340(gobj, &sp10, &sp10, 0x1A, 0x7D, fp->x2C_facing_direction);
        fp->x2368 = func_800237A8(0x4E204, 0x7F, 0x40);
        fp->x236C = func_800237A8(0x4E205, 0x7F, 0x40);
        fp->x2370 = func_800237A8(0x4E206, 0x7F, 0x40);
        fp->x2200_ftcmd_var0 = 0;
    }
}

void ftMasterHand_80152F80(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16B, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    func_800236B8(fp->x2368);
    func_800236B8(fp->x236C);
    func_800236B8(fp->x2370);
    fp->x2368 = -1;
    fp->x236C = -1;
    fp->x2370 = -1;
}

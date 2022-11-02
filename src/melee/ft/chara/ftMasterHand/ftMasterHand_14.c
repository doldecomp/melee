#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#include <melee/lb/lbunknown_001.h>

void ftMasterHand_80152BC8(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80152BCC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x169, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    fp->x2368 = -1;
    fp->x236C = -1;
    fp->x2370 = -1;
}

static void ftMasterHand_80152CD8(HSD_GObj* fighter_gobj);

void ftMasterHand_80152C34(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80152CD8(fighter_gobj);
}

void ftMasterHand_80152C70(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80152CB4(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80152CD4(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_80152E28(HSD_GObj* fighter_gobj);

static void ftMasterHand_80152CD8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16A, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    fp->cb.x21BC_callback_Accessory4 = &ftMasterHand_80152E28;
    fp->x2200_ftcmd_var0 = 1;
}

static void ftMasterHand_80152F80(HSD_GObj* fighter_gobj);

void ftMasterHand_80152D44(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;

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

void ftMasterHand_80152DC0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80152E04(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80152E24(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_80152E28(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2200_ftcmd_var0 != 0) {
        u32 unused1;
        Vec3 vec;
        u32 unused2;

        func_8000B1CC(fp->x5E8_fighterBones[11].x0_jobj, 0, &vec);
        fp->x2374 = func_802F0340(fighter_gobj, &vec, &vec, 0xB, 0x7D, fp->x2C_facing_direction);

        func_8000B1CC(fp->x5E8_fighterBones[16].x0_jobj, 0, &vec);
        fp->x2378 = func_802F0340(fighter_gobj, &vec, &vec, 0x10, 0x7D, fp->x2C_facing_direction);

        func_8000B1CC(fp->x5E8_fighterBones[21].x0_jobj, 0, &vec);
        fp->x237C = func_802F0340(fighter_gobj, &vec, &vec, 0x15, 0x7D, fp->x2C_facing_direction);

        func_8000B1CC(fp->x5E8_fighterBones[26].x0_jobj, 0, &vec);

        fp->x2380 = func_802F0340(fighter_gobj, &vec, &vec, 0x1A, 0x7D, fp->x2C_facing_direction);
        fp->x2368 = func_800237A8(0x4E204, 0x7F, 0x40);
        fp->x236C = func_800237A8(0x4E205, 0x7F, 0x40);
        fp->x2370 = func_800237A8(0x4E206, 0x7F, 0x40);

        fp->x2200_ftcmd_var0 = 0;
    }
}

static void ftMasterHand_80152F80(HSD_GObj* fighter_gobj)
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

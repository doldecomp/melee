#include "ftMasterHand_14.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"

// 80152BC8 14F7A8
void ftMasterHand_80152BC8(HSD_GObj* gobj)
{
    return;
}

// 80152BCC 14F7AC
// https://decomp.me/scratch/Lyvr5
void ftMasterHand_80152BCC(HSD_GObj* arg0)
{
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    Fighter_ChangeMotionState(arg0, 0x169, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
    temp_r31->sv.mh.unk0.x28 = -1;
    temp_r31->sv.mh.unk0.x2C = -1;
    temp_r31->sv.mh.unk0.x30 = -1;
}

// 80152C34 14F814
// https://decomp.me/scratch/Whi0Q
void ftMasterHand_80152C34(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMasterHand_80152CD8(arg0);
    }
}

// 80152C70 14F850
// https://decomp.me/scratch/5SqNT
void ftMasterHand_80152C70(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 80152CB4 14F894
// https://decomp.me/scratch/ZDCi1
void ftMasterHand_80152CB4(HSD_GObj* arg0)
{
    ft_80085134(arg0);
}

// 80152CD4 14F8B4
void ftMasterHand_80152CD4(HSD_GObj* arg0)
{
    return;
}

// 80152CD8 14F8B8
// https://decomp.me/scratch/C5hzY
void ftMasterHand_80152CD8(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    Fighter_ChangeMotionState(arg0, 0x16A, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
    fp->cb.x21BC_callback_Accessory4 = &ftMasterHand_80152E28;
    fp->x2200_ftcmd_var0 = 1;
}

// 80152D44 14F924
// https://decomp.me/scratch/n1fhW
void ftMasterHand_80152D44(HSD_GObj* arg0)
{
    Fighter* temp_r31;

    if (!ftAnim_IsFramesRemaining(arg0)) {
        temp_r31 = arg0->user_data;
        ftMasterHand_80152F80(arg0);
        it_802F046C(temp_r31->sv.mh.unk0.x34);
        it_802F046C(temp_r31->sv.mh.unk0.x38);
        it_802F046C(temp_r31->sv.mh.unk0.x3C);
        it_802F046C(temp_r31->sv.mh.unk0.x40);
        temp_r31->sv.mh.unk0.x34 = 0;
        temp_r31->sv.mh.unk0.x38 = 0;
        temp_r31->sv.mh.unk0.x3C = 0;
        temp_r31->sv.mh.unk0.x40 = 0;
    }
}

// 80152DC0 14F9A0
// https://decomp.me/scratch/X13ZG
void ftMasterHand_80152DC0(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 80152E04 14F9E4
// https://decomp.me/scratch/BwM1c
void ftMasterHand_80152E04(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 80152E24 14FA04
void ftMasterHand_80152E24(HSD_GObj* gobj)
{
    return;
}

// 80152E28 14FA08
// https://decomp.me/scratch/Uqf2Q
void ftMasterHand_80152E28(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 sp10;

    if (fp->x2200_ftcmd_var0 != 0) {
        lb_8000B1CC(fp->x5E8_fighterBones[11].x0_jobj, 0, &sp10);
        fp->sv.mh.unk0.x34 =
            it_802F0340(gobj, &sp10, &sp10, 0xB, 0x7D, fp->facing_dir);
        lb_8000B1CC(fp->x5E8_fighterBones[16].x0_jobj, 0, &sp10);
        fp->sv.mh.unk0.x38 =
            it_802F0340(gobj, &sp10, &sp10, 0x10, 0x7D, fp->facing_dir);
        lb_8000B1CC(fp->x5E8_fighterBones[21].x0_jobj, 0, &sp10);
        fp->sv.mh.unk0.x3C =
            it_802F0340(gobj, &sp10, &sp10, 0x15, 0x7D, fp->facing_dir);
        lb_8000B1CC(fp->x5E8_fighterBones[26].x0_jobj, 0, &sp10);
        fp->sv.mh.unk0.x40 =
            it_802F0340(gobj, &sp10, &sp10, 0x1A, 0x7D, fp->facing_dir);
        fp->sv.mh.unk0.x28 = lbAudioAx_800237A8(0x4E204, 0x7F, 0x40);
        fp->sv.mh.unk0.x2C = lbAudioAx_800237A8(0x4E205, 0x7F, 0x40);
        fp->sv.mh.unk0.x30 = lbAudioAx_800237A8(0x4E206, 0x7F, 0x40);
        fp->x2200_ftcmd_var0 = 0;
    }
}

// 80152F80 14FB60
// https://decomp.me/scratch/HCvJq
void ftMasterHand_80152F80(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x16B, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    lbAudioAx_800236B8(fp->sv.mh.unk0.x28);
    lbAudioAx_800236B8(fp->sv.mh.unk0.x2C);
    lbAudioAx_800236B8(fp->sv.mh.unk0.x30);
    fp->sv.mh.unk0.x28 = -1;
    fp->sv.mh.unk0.x2C = -1;
    fp->sv.mh.unk0.x30 = -1;
}

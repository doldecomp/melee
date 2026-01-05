#include "ftCh_Init.h"

#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/chara/ftCommon/ftCo_CaptureCut.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_Thrown.h"
#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCrazyHand/forward.h"

#include "ftMasterHand/types.h"
#include "it/it_26B1.h"
#include "it/items/itmasterhandlaser.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

/* static */ void fn_8015B2C0(HSD_GObj*);
/* static */ void ftCh_GrabUnk1_8015B850(HSD_GObj*, int);
/* static */ void ftCh_Init_80158F34(HSD_GObj*);
/* static */ void ftCh_Init_801592D4(HSD_GObj*);
/* static */ void ftCh_Init_801566B4(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156688(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_801566E0(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156710(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156740(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156770(void);
/* static */ void ftCh_Init_801567A0(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_801567AC(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_801567DC(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_8015683C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_8015686C(void);
/* static */ void ftCh_Init_80156878(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156884(void);
/* static */ void ftCh_Init_80156898(void);
/* static */ void ftCh_Init_801568AC(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_80156A5C(void);
/* static */ void ftCh_Init_801568B8(void);
/* static */ void ftCh_Init_801568E8(void);
/* static */ void ftCh_Init_80156918(void);
/* static */ void ftCh_Init_80156948(void);
/* static */ void fn_8015AAC8(Fighter_GObj* gobj);
/* static */ void ftCh_TagFail_Anim(Fighter_GObj* gobj);
/* static */ void ftCh_GrabUnk1_8015B800(Fighter_GObj* gobj);
/* static */ void ftCh_GrabUnk1_8015A888(Fighter_GObj* gobj);
/* static */ void fn_8015746C(Fighter_GObj* gobj);
/* static */ void fn_8015755C(Fighter_GObj* gobj);
/* static */ void ftCh_Init_8015737C(Fighter_GObj* gobj);
/* static */ void ftCh_Init_801577F8(Fighter_GObj* gobj);
/* static */ void fn_801577B4(Fighter_GObj* gobj);
/* static */ void fn_801578E8(Fighter_GObj* gobj);
/* static */ void ftCh_Init_801579F4(Fighter_GObj* gobj);
/* static */ void fn_80159288(Fighter_GObj* gobj);
/* static */ void ftCh_Init_80159F40(Fighter_GObj* gobj);
/* static */ void ftCh_GrabUnk1_8015ABD0(Fighter_GObj* gobj);
/* static */ void ftCh_Init_80157B58(Fighter_GObj* gobj);
/* static */ void ftCh_Init_8015A184(Fighter_GObj* gobj);
/* static */ void ftCh_FingerBeamEnd_Anim(HSD_GObj* gobj);
/* static */ void ftCh_GrabUnk1_8015AC50(HSD_GObj* gobj);
/* static */ void ftCh_BackDisappear_Phys(Fighter_GObj* gobj);
/* static */ void ftCh_TagCancel_Coll(Fighter_GObj* gobj);
/* static */ void ftCh_BackPunch_Phys(Fighter_GObj* gobj);
/* static */ void ftCh_FingerGun1_Phys(Fighter_GObj* gobj);

char ftCh_Init_DatFilename[] = "PlCh.dat";
char ftCh_Init_DataName[] = "ftDataCrazyhand";
char ftCh_Init_803D4834[] = "PlChNr.dat";
char ftCh_Init_803D4840[] = "PlyCrazyhand_Share_joint";
char ftCh_Init_AnimDatFilename[] = "PlChAJ.dat";

Fighter_CostumeStrings ftCh_Init_CostumeStrings[] = {
    { ftCh_Init_803D4834, ftCh_Init_803D4840, NULL },
};

jtbl_t ftCh_Init_803D4900 = {
    ftCh_Init_801566B4, ftCh_Init_80156A5C, ftCh_Init_80156688,
    ftCh_Init_80156A5C, ftCh_Init_801566E0, ftCh_Init_80156A5C,
    ftCh_Init_80156710, ftCh_Init_80156A5C, ftCh_Init_80156740,
    ftCh_Init_80156A5C, ftCh_Init_80156A5C, ftCh_Init_80156770,
    ftCh_Init_801567A0, ftCh_Init_80156A5C, ftCh_Init_801567AC,
    ftCh_Init_80156A5C, ftCh_Init_801567DC, ftCh_Init_80156A5C,
    ftCh_Init_8015683C, ftCh_Init_80156A5C, ftCh_Init_80156A5C,
    ftCh_Init_80156A5C, ftCh_Init_80156A5C, ftCh_Init_80156A5C,
    ftCh_Init_80156A5C, ftCh_Init_8015686C, ftCh_Init_80156878,
    ftCh_Init_80156A5C, ftCh_Init_80156A5C, ftCh_Init_80156884,
    ftCh_Init_80156898, ftCh_Init_801568AC, ftCh_Init_80156A5C,
    ftCh_Init_80156A5C, ftCh_Init_801568B8, ftCh_Init_801568E8,
    ftCh_Init_80156918, ftCh_Init_80156948,
};

/* static */ void ftCh_GrabUnk1_8015B2FC(void);
/* static */ void ftCh_GrabUnk1_8015B35C(void);
/* static */ void ftCh_GrabUnk1_8015B390(void);
/* static */ void ftCh_GrabUnk1_8015B3B8(void);
/* static */ void ftCh_GrabUnk1_8015B3EC(void);
/* static */ void ftCh_GrabUnk1_8015B404(void);
/* static */ void ftCh_GrabUnk1_8015B43C(void);
/* static */ void ftCh_GrabUnk1_8015B46C(void);
/* static */ void ftCh_GrabUnk1_8015B4AC(void);
/* static */ void ftCh_GrabUnk1_8015B4BC(void);

jtbl_t ftCh_Init_803D4998 = {
    ftCh_GrabUnk1_8015B2FC, ftCh_GrabUnk1_8015B35C, ftCh_GrabUnk1_8015B390,
    ftCh_GrabUnk1_8015B3B8, ftCh_GrabUnk1_8015B3EC, ftCh_GrabUnk1_8015B404,
    ftCh_GrabUnk1_8015B43C, ftCh_GrabUnk1_8015B46C, ftCh_GrabUnk1_8015B4AC,
    ftCh_GrabUnk1_8015B4BC,
};

void ftCh_Init_OnDeath(HSD_GObj* gobj) {}

void ftCh_Init_OnLoad(HSD_GObj* gobj)
{
    ftData* ftdata;
    ftCrazyHand_DatAttrs* ftData_attr;
    void** items;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftdata = fp->ft_data;
    ftData_attr = ftdata->ext_attr;
    items = ftdata->x48_items;

    PUSH_ATTRS(fp, ftCrazyHand_DatAttrs);

    ftBossLib_8015BDB4(gobj);
    it_8026B3F8(items[0], 127);
    it_8026B3F8(items[1], 128);
    it_8026B3F8(items[2], 129);
    fp->no_normal_motion = 1;
    fp->x2229_b6 = 1;
    fp->no_kb = 1;
    fp->x222A_b0 = 1;
    fp->x222A_b1 = 1;
    fp->x2229_b3 = 1;
    fp->cur_pos.x = ftData_attr->x18;
    fp->cur_pos.y = ftData_attr->x1C;
    fp->cur_pos.z = 0.0f;
    fp->mv.ch.unk0.x28 = 0;
    fp->mv.ch.unk0.x2C = 0;
    fp->mv.ch.unk0.x30 = 0;
    fp->mv.ch.unk0.x34 = 0;
    fp->mv.ch.unk0.x38 = -1;
    fp->mv.ch.unk0.x3C = -1;
    fp->mv.ch.unk0.x40 = -1;
    fp->mv.ch.unk0.x1C = 0.0f;
    fp->mv.ch.unk0.x20 = 0;
    fp->fv.ch.x222C = ftBossLib_8015C244(gobj, &fp->cur_pos);
    fp->fv.ch.x2238 = 1.0f;
    fp->fv.ch.x224C = 0;
    fp->fv.ch.x2250 = ftMh_MS_Damage2;
    fp->fv.ch.x2254 = 0;
    fp->x1A88.level = 1;
    ftBossLib_8015BD24(fp->x1A88.level, &fp->fv.mh.x223C, fp->fv.ch.x2238,
                       ftData_attr->x0, ftData_attr->x8, ftData_attr->x4);
}

void ftCh_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCrazyHand_DatAttrs);
}

/* static */ void ftCh_Init_80156310(HSD_GObj* gobj);
void ftCh_GrabUnk1_8015B174(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    f32 zero = 0.0f;
    f32 one = 1.0f;
    ftMasterHand_SpecialAttrs* attrs = fp->ft_data->ext_attr;

    Fighter_ChangeMotionState(gobj, 0x183, 0, zero, one, zero, NULL);
    ftAnim_8006EBA4(gobj);

    fp->cur_pos.x = *(f32*) &attrs->x18;
    fp->cur_pos.y = *(f32*) &attrs->x1C;
    fp->cur_pos.z = 0.0f;
    fp->accessory4_cb = fn_8015B2C0;
    *(s32*) &fp->mv.mh.unk0.x0 = 0;
    ft_800881D8(fp, 0x4E202, 0x7F, 0x40);
    ftBossLib_8015C09C(gobj, 1.0f);
}

void ftCh_Init_80156014(HSD_GObj* gobj) {}

/// #ftCh_Init_80156018

/// #ftCh_Init_801560D8

/// #ftCh_Init_80156198

/// #ftCh_Init_80156310

/// #ftCh_Wait1_0_Anim

void ftCh_Wait1_0_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Wait1_0_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Wait1_0_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_80156AD8

/// #fn_80156F6C

void ftCh_Entry_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Entry_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Entry_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Entry_Coll(HSD_GObj* gobj) {}

void fn_80157080(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x158, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Damage_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_80157170(gobj);
    }
}

void ftCh_Damage_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Damage_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Damage_Coll(HSD_GObj* gobj) {}

/// #ftCh_Init_80157170

void ftCh_Damage2_Anim(HSD_GObj* gobj)
{
    s32 unused;
    Vec3 floor_pos;
    s32 unused2[2];
    Fighter* fp;
    ftMasterHand_SpecialAttrs* attrs;

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp = gobj->user_data;
        mpFloorGetRight(0, &floor_pos);

        if (fp->cur_pos.x > floor_pos.x) {
            ftCh_Init_8015737C(gobj);
        } else {
            f32 zero;
            f32 rate;
            fp = gobj->user_data;
            attrs = fp->ft_data->ext_attr;

            fp->mv.mh.unk0.xC.x = fp->cur_pos.x - *(f32*) &attrs->x28;
            fp->mv.mh.unk0.xC.y = *(f32*) &attrs->x24;
            zero = 0.0f;
            fp->mv.mh.unk0.xC.z = zero;
            rate = 2.0f;
            Fighter_ChangeMotionState(gobj, 0x159, 0, zero, rate, zero, NULL);
            ftAnim_8006EBA4(gobj);
            ft_PlaySFX(fp, 0x4E207, 0x7F, 0x40);
        }
    }
}
void ftCh_Damage2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Damage2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       *(float*) &da->x10);
}

void ftCh_Damage2_Coll(HSD_GObj* gobj) {}

void ftCh_Init_8015737C(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_WaitSweep, 0, 0, 1.0f, 1.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_WaitSweep_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_WaitSweep_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_WaitSweep_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WaitSweep_Coll(HSD_GObj* gobj) {}

void fn_8015746C(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_SweepLoop, 0, 0, 1.0f, 1.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_SweepLoop_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_SweepLoop_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_SweepLoop_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_SweepLoop_Coll(HSD_GObj* gobj) {}

void fn_8015755C(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_SweepWait, 0, 0, 1.0f, 1.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_SweepWait_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_8015764C(gobj);
    }
}

void ftCh_SweepWait_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_SweepWait_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_SweepWait_Coll(HSD_GObj* gobj) {}

void ftCh_Init_8015764C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x15D, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_801577B4;
}

void ftCh_Slap_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 0x15D, 0, 0.0f, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
        fp->accessory4_cb = fn_801577B4;
    }
}

void ftCh_Slap_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Slap_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    fp->self_vel.x += da->x40_pos.x;
}

void fn_801577B4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    if (fp->cur_pos.x > da->x3C) {
        fp->self_vel.x = 0.0f;
        ftCh_Init_801577F8(gobj);
    }
}

void ftCh_Init_801577F8(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Walk2, 0, 0, 1.0f, 1.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Walk2_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Walk2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Walk2_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Slap_Coll(HSD_GObj* gobj) {}

void fn_801578E8(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_WalkLoop, 0, 0, 1.0f, 1.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_WalkLoop_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
        ftCh_Init_801579F4(gobj);
        fp->mv.mh.unk0.x8 = *(s32*) &da->x64;
    }
}

void ftCh_WalkLoop_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WalkLoop_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_WalkLoop_Coll(HSD_GObj* gobj) {}

void ftCh_Init_801579F4(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_WalkWait, 0, 0, 1.0f, 1.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_WalkWait_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (--fp->mv.mh.unk0.x8 == 0) {
        ftCh_Init_80157B58(gobj);
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter_ChangeMotionState(gobj, 0x160, 0, 0.0f, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
}

void ftCh_WalkWait_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WalkWait_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015C010(gobj, da->x68);
    ftBossLib_8015C190(gobj);
}

void ftCh_WalkWait_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80157B58(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->self_vel.x = 0.0f;
    Fighter_ChangeMotionState(gobj, ftMh_MS_WalkShoot, 0, 0, 0.0f, 1.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_WalkShoot_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_WalkShoot_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WalkShoot_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_WalkShoot_Coll(HSD_GObj* gobj) {}

void fn_80157C50(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x162, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x0 = 0.0f;
}

void ftCh_Drill_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Drill_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Drill_Phys(HSD_GObj* gobj)
{
    f32 mv_val;
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attrs = fp->ft_data->ext_attr;

    ft_80085134(gobj);

    mv_val = fp->mv.mh.unk0.x0 += 1.0f;

    if (mv_val > (f32) attrs->x74 &&
        (mv_val = fp->mv.mh.unk0.x0, mv_val < (f32) * (s32*) &attrs->x78))
    {
        ftBossLib_8015C010(gobj, *(float*) &attrs->x7C);
    } else {
        fp->self_vel.x = 0.0f;
    }

    ftBossLib_8015C190(gobj);
}
void ftCh_Drill_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80157DF8(HSD_GObj* gobj)
{
    s32 unused[2];
    Fighter* fp = gobj->user_data;
    f32 zero = 0.0f;
    f32 one = 1.0f;
    ftMasterHand_SpecialAttrs* attrs = fp->ft_data->ext_attr;

    Fighter_ChangeMotionState(gobj, 0x163, 0, zero, one, zero, NULL);
    ftAnim_8006EBA4(gobj);

    fp->mv.mh.unk0.x0 =
        (f32) (*(s32*) &attrs->x58 +
               HSD_Randi(*(s32*) &attrs->x50.y - *(s32*) &attrs->x58));
    *(f32*) &fp->mv.mh.unk0.x4 = 0.0f;
}
/// #ftCh_RockCrushUp_Anim

void ftCh_RockCrushWait_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_RockCrushUp_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

/// #ftCh_RockCrushUp_Phys

void ftCh_RockCrushUp_Coll(HSD_GObj* gobj) {}

void fn_80158144(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x165, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x0 = 107.0f;
}

void ftCh_RockCrushDown_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_RockCrushDown_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_RockCrushDown_Phys(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attrs = fp->ft_data->ext_attr;
    f32 temp_f2;

    ft_80085134(gobj);

    temp_f2 = fp->mv.mh.unk0.x0 - 1.0f;
    fp->mv.mh.unk0.x0 = temp_f2;

    if (temp_f2 > (f32) * (s32*) &attrs->x40_pos.z ||
        (temp_f2 = fp->mv.mh.unk0.x0, temp_f2 < 0.0f))
    {
        fp->self_vel.x = 0.0f;
    } else {
        ftBossLib_8015C010(gobj, attrs->x40_pos.y);
    }

    ftBossLib_8015C190(gobj);
}
void ftCh_RockCrushDown_Coll(HSD_GObj* gobj) {}

void fn_801582D8(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x166, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x38 = -1;
    fp->mv.mh.unk0.x3C = -1;
    fp->mv.mh.unk0.x40 = -1;
}

void ftCh_PaperCrush_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_801583E4(gobj);
    }
}

void ftCh_PaperCrush_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_PaperCrush_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_PaperCrush_Coll(HSD_GObj* gobj) {}

/* static */ void fn_80158534(HSD_GObj* gobj);

void ftCh_Init_801583E4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x167, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_80158534;
    fp->cmd_vars[0] = 1;
}

/* static */ void ftCh_Init_8015868C(Fighter_GObj* gobj);

void ftCh_Poke1_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = gobj->user_data;
        ftCh_Init_8015868C(gobj);
        it_802F046C((Item_GObj*) fp->mv.mh.dmg0.x28);
        it_802F046C((Item_GObj*) fp->mv.mh.dmg0.x2C);
        it_802F046C((Item_GObj*) fp->mv.mh.dmg0.x30);
        it_802F046C(fp->mv.mh.dmg0.x34);
        fp->mv.mh.dmg0.x28 = 0;
        fp->mv.mh.dmg0.x2C = 0;
        fp->mv.mh.dmg0.x30 = 0;
        fp->mv.mh.dmg0.x34 = 0;
    }
}

void ftCh_Poke1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Poke1_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Poke1_Coll(HSD_GObj* gobj) {}

/// #fn_80158534

void ftCh_Init_8015868C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x168, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x38);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x3C);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x40);
    fp->mv.mh.unk0.x38 = -1;
    fp->mv.mh.unk0.x3C = -1;
    fp->mv.mh.unk0.x40 = -1;
}

void ftCh_Poke2_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Poke2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Poke2_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Poke2_Coll(HSD_GObj* gobj) {}

/* static */ void fn_801588B8(Fighter_GObj* gobj);

void fn_801587B0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x169, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[3] = 0;
    fp->accessory4_cb = fn_801588B8;
}

void ftCh_FingerBeamStart_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_FingerBeamStart_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerBeamStart_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_FingerBeamStart_Coll(HSD_GObj* gobj) {}

/// #fn_801588B8

/// #ftCh_Init_80158B3C

/* static */ void ftCh_Init_80158DFC(Fighter_GObj* gobj);

void ftCh_FingerBeamLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    s32 unused;

    fp = gobj->user_data;
    if (--fp->mv.mh.unk0.x8 == 0) {
        ftAnim_SetAnimRate(gobj, 1.0f);
        ftCh_Init_80158DFC(gobj);
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        f32 zero = 0.0f;
        f32 one = 1.0f;
        Fighter_ChangeMotionState(gobj, 0x16A, 0, zero, one, zero, NULL);
        ftAnim_8006EBA4(gobj);
    }
}
void ftCh_FingerBeamLoop_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

/// #ftCh_FingerBeamLoop_Phys

void ftCh_FingerBeamLoop_Coll(HSD_GObj* gobj) {}

/* static */ void fn_8015B548(HSD_GObj* gobj, HSD_GObj* grabbed);

void ftCh_Init_80158DFC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x16B, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2D0(fp, 0x100, fn_80159288, NULL, fn_8015B548);
    fp->mv.mh.unk0.x20 = 0;
}

void ftCh_FingerBeamEnd_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
        ftCh_GrabUnk1_8015AC50(gobj);
    }
}

void ftCh_FingerBeamEnd_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerBeamEnd_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_FingerBeamEnd_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80158F34(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x172, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.xC.x = *(float*) &da->x18;
    fp->mv.mh.unk0.xC.y = *(float*) &da->x1C;
    fp->mv.mh.unk0.xC.z = 0.0f;
}

void ftCh_BackPunch_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_BackPunch_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackPunch_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       *(float*) &da->x10);
}

void ftCh_BackPunch_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80159098(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x16C, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x24 = da->xD8;
    fp->cmd_vars[0] = 1;
    fp->self_vel.x = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.z = 0.0f;
    fp->mv.mh.unk0.xC.x = *(float*) &da->x18;
    fp->mv.mh.unk0.xC.y = *(float*) &da->x1C;
    fp->mv.mh.unk0.xC.z = 0.0f;
}

void ftCh_FingerGun1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    f32 timer = fp->mv.mh.unk0.x24 -= 1.0f;

    if (timer <= 0.0f && fp->cmd_vars[0] != 0) {
        ftCh_GrabUnk1_8015B800(fp->victim_gobj);
        fp->mv.mh.unk0.x20 = 0;
        fp->cmd_vars[0] = 0;
    }

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}
void ftCh_FingerGun1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerGun1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       *(float*) &da->x10);
}

void ftCh_FingerGun1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.mh.unk0.x18 == 0.0f) {
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
    }
}

void fn_80159288(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->self_vel.z = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
    fp->mv.mh.unk0.x20 = 1;
    fp->x221E_b6 = false;
    ftCh_GrabUnk1_8015ABD0(gobj);
}

/// #ftCh_Init_801592D4

/* static */ void ftCh_Init_801594D4(Fighter_GObj* gobj);
/* static */ void ftCh_Init_80159670(Fighter_GObj* gobj);

void ftCh_BackAirplane1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->cmd_vars[1] != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->cmd_vars[1] = 0;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp = gobj->user_data;
        if (fp->fv.ch.x2250 == 0x170) {
            ftCh_Init_801594D4(gobj);
        } else {
            ftCh_Init_80159670(gobj);
        }
    }
}

void ftCh_BackAirplane1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackAirplane1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       *(float*) &da->x10);
}

void ftCh_BackAirplane1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.mh.unk0.x18 == 0.0f) {
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
    }
}

void ftCh_Init_801594D4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x170, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->cmd_vars[0] = 0;
}

void ftCh_BackAirplane2_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    HSD_GObj* victim_gobj;
    Fighter* victim_fp;
    s32 unused[2];

    fp = gobj->user_data;

    if (fp->cmd_vars[0] != 0) {
        HSD_GObj* temp;
        fp->cmd_vars[0] = 0;
        ftCh_GrabUnk1_8015B850(fp->victim_gobj, 0x153);
        temp = fp->victim_gobj;
        if (temp != NULL) {
            victim_fp = temp->user_data;
            victim_gobj = temp;
            ftCommon_8007E2F4(fp, 0);
            ftCo_800DE2A8(gobj, victim_gobj);
            victim_fp->dmg.facing_dir_1 *= 0.6f;
            ftCo_800DE7C0(victim_gobj, 0, 0);
        }
        fp->mv.mh.unk0.x20 = 0;
    }

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}
void ftCh_BackAirplane2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackAirplane2_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_BackAirplane2_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80159670(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x171, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->cmd_vars[0] = 0;
}

void ftCh_BackAirplane3_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    HSD_GObj* victim_gobj;
    s32 unused[2];

    fp = gobj->user_data;

    if (fp->cmd_vars[0] != 0) {
        HSD_GObj* temp;
        fp->cmd_vars[0] = 0;
        ftCh_GrabUnk1_8015B850(fp->victim_gobj, 0x153);
        temp = fp->victim_gobj;
        if (temp != NULL) {
            victim_gobj = temp;
            ftCommon_8007E2F4(fp, 0);
            ftCo_800DE2A8(gobj, victim_gobj);
            ftCo_800DE7C0(victim_gobj, 0, 0);
        }
        fp->mv.mh.unk0.x20 = 0;
    }

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}
void ftCh_BackAirplane3_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackAirplane3_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_BackAirplane3_Coll(HSD_GObj* gobj) {}

void ftCh_Init_801597F0(Fighter_GObj* gobj, HSD_GObjEvent callback)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x173, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x4 = callback;
}

void ftCh_BackCrush_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.mh.unk0.x4(gobj);
    }
}

void ftCh_BackCrush_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackCrush_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_BackCrush_Coll(HSD_GObj* gobj) {}

void fn_80159908(HSD_GObj* gobj)
{
    Vec3 temp_pos;
    s32 unused;
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attrs = fp->ft_data->ext_attr;
    f32 zero = 0.0f;
    f32 half = 0.5f;

    Fighter_ChangeMotionState(gobj, 0x174, 0, zero, half, zero, NULL);
    ftAnim_8006EBA4(gobj);

    fp->mv.mh.unk0.x0 = (f32) attrs->xF0;

    ftBossLib_8015C208(gobj, &temp_pos);
    fp->cur_pos.x = temp_pos.x;
    fp->cur_pos.y = *(f32*) &attrs->xEC;

    fp->self_vel.z = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
}
void ftCh_BackDisappear_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = 0.0f;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_BackDisappear_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackDisappear_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    float new_val = fp->mv.mh.unk0.x0 - 1.0f;
    fp->mv.mh.unk0.x0 = new_val;
    if (new_val > 0.0f) {
        ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
        ftBossLib_8015BF74(gobj, da->xDC);
    } else {
        fp->self_vel.x = 0.0f;
    }
}

void ftCh_BackDisappear_Coll(HSD_GObj* gobj) {}

/// #fn_80159AA4

/// #ftCh_Wait1_1_Anim

void ftCh_Wait1_1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Wait1_1_Phys(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    f32 new_val = fp->mv.mh.unk0.x0 - 1.0f;
    fp->mv.mh.unk0.x0 = new_val;

    if (new_val > 0.0f) {
        ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
        ftBossLib_8015BF74(gobj, da->xDC);
    } else {
        fp->self_vel.x = 0.0f;
    }

    ftBossLib_8015C190(gobj);
}
void ftCh_Wait1_1_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80159F40(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Grab, 0, 0, 1.0f, 1.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Grab_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_8015A030(gobj);
    }
}

void ftCh_Grab_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Grab_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Grab_Coll(HSD_GObj* gobj) {}

void ftCh_Init_8015A030(HSD_GObj* gobj)
{
    Vec3 stack_vec;
    s32 unused;
    Fighter* fp = gobj->user_data;
    f32 zero = 0.0f;
    f32 one = 1.0f;
    ftMasterHand_SpecialAttrs* attrs = fp->ft_data->ext_attr;

    Fighter_ChangeMotionState(gobj, 0x177, 0, zero, one, zero, NULL);
    ftAnim_8006EBA4(gobj);
    ftBossLib_8015C208(gobj, &stack_vec);

    fp->cur_pos.x = stack_vec.x;
    fp->cur_pos.y = attrs->xE0;
    fp->self_vel.z = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
}
void ftCh_Cancel_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = 0.0f;
        ftCh_Init_8015A184(gobj);
    }
}

void ftCh_Cancel_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Cancel_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ftBossLib_8015BF74(gobj, da->xDC);
}

void ftCh_Cancel_Coll(HSD_GObj* gobj) {}

void ftCh_Init_8015A184(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x178, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->cur_pos.x = da->xE4;
    fp->cur_pos.y = da->xE8;
    fp->self_vel.z = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
}

void ftCh_Squeezing0_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Squeezing0_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Squeezing0_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Squeezing0_Coll(HSD_GObj* gobj) {}

void ftCh_Init_8015A2B0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x1A5C = ftBossLib_8015C3E8(0x1B);
    Fighter_ChangeMotionState(gobj, 0x179, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Squeezing1_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C2E0() != 0 || ftBossLib_8015C358() != 0 ||
        ftAnim_IsFramesRemaining(gobj) == 0)
    {
        Fighter* fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Squeezing1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Squeezing1_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Squeezing1_Coll(HSD_GObj* gobj) {}

void ftCh_Init_8015A3F4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->cmd_vars[1] = 0;
    fp->x1A5C = ftBossLib_8015C3E8(0x1B);
    Fighter_ChangeMotionState(gobj, 0x17A, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Squeeze_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    s32 unused[2];

    fp = gobj->user_data;

    if (fp->cmd_vars[1] != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->cmd_vars[1] = 0;
    }

    if (ftBossLib_8015C2E0() != 0 || ftBossLib_8015C358() != 0 ||
        ftAnim_IsFramesRemaining(gobj) == 0)
    {
        fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}
void ftCh_Squeeze_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Squeeze_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Squeeze_Coll(HSD_GObj* gobj) {}

void ftCh_Init_8015A560(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->cmd_vars[1] = 0;
    fp->x1A5C = ftBossLib_8015C3E8(0x1B);
    Fighter_ChangeMotionState(gobj, 0x17B, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Throw_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    s32 unused[2];

    fp = gobj->user_data;

    if (fp->cmd_vars[1] != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->cmd_vars[1] = 0;
    }

    if (ftBossLib_8015C2E0() != 0 || ftBossLib_8015C358() != 0 ||
        ftAnim_IsFramesRemaining(gobj) == 0)
    {
        fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}
void ftCh_Throw_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Throw_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Throw_Coll(HSD_GObj* gobj) {}

void ftCh_Slam_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C2E0() != 0 || ftBossLib_8015C358() != 0 ||
        ftAnim_IsFramesRemaining(gobj) == 0)
    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = NULL;
        ftCh_GrabUnk1_8015A888(gobj);
    }
}

void ftCh_Slam_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Slam_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Slam_Coll(HSD_GObj* gobj) {}

void ftCh_Fail_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C31C() != 0 || ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = NULL;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Fail_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Fail_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Fail_Coll(HSD_GObj* gobj) {}

void ftCh_GrabUnk1_8015A888(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_TagCrush, 0, 0, 1.0f, 1.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_TagCrush_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_TagCrush_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagCrush_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_TagCrush_Coll(HSD_GObj* gobj) {}

void ftCh_TagApplaud_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    f32 timer = fp->mv.mh.unk0.x24 -= 1.0f;

    if (timer <= 0.0f && fp->cmd_vars[0] != 0) {
        ftCh_GrabUnk1_8015B800(fp->victim_gobj);
        fp->cmd_vars[0] = 0;
    }

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}
void ftCh_TagApplaud_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagApplaud_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       *(float*) &da->x10);
}

void ftCh_TagApplaud_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.mh.unk0.x18 == 0.0f) {
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
    }
}

void fn_8015AAC8(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftMh_MS_TagRockPaper, 0,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

void ftCh_TagRockPaper_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C2E0() != 0 || ftBossLib_8015C358() != 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter_ChangeMotionState(gobj, 0x180, 0, 0.0f, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
}

void ftCh_TagRockPaper_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagRockPaper_Phys(HSD_GObj* gobj) {}

void ftCh_TagRockPaper_Coll(HSD_GObj* gobj) {}

void ftCh_GrabUnk1_8015ABD0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attrs = fp->ft_data->ext_attr;
    f32 zero = 0.0f;
    f32 one = 1.0f;

    Fighter_ChangeMotionState(gobj, 0x16D, 0, zero, one, zero, NULL);
    ftAnim_8006EBA4(gobj);

    fp->mv.mh.unk0.xC.x = attrs->xCC_pos.y;
    fp->mv.mh.unk0.xC.y = attrs->xD4;
    fp->mv.mh.unk0.xC.z = 0.0f;
}
void ftCh_GrabUnk1_8015AC50(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attrs = fp->ft_data->ext_attr;
    f32 zero = 0.0f;
    f32 one = 1.0f;

    Fighter_ChangeMotionState(gobj, 0x16E, 0, zero, one, zero, NULL);
    ftAnim_8006EBA4(gobj);

    fp->mv.mh.unk0.xC.x = *(f32*) &attrs->x18;
    fp->mv.mh.unk0.xC.y = *(f32*) &attrs->x1C;
    fp->mv.mh.unk0.xC.z = 0.0f;
}
void ftCh_FingerGun2_Anim(HSD_GObj* gobj)
{
    s32 unused[2];
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = gobj->user_data;
        if (fp->mv.mh.unk0.x20 == 1) {
            ftCh_Init_801592D4(gobj);
        } else {
            ftCh_Init_80158F34(gobj);
        }
    }
}

void ftCh_FingerGun2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerGun2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       *(float*) &da->x10);
}

void ftCh_FingerGun2_Coll(HSD_GObj* gobj) {}

/// #ftCh_GrabUnk1_8015ADD0

/// #ftCh_TagGrab_Anim

/// #ftCh_TagSqueeze_Anim

void ftCh_TagGrab_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagGrab_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    fp->self_vel.y += da->x12C_pos.y;
    fp->self_vel.z += da->x134_pos.y;
}

void ftCh_TagGrab_Coll(HSD_GObj* gobj) {}

void ftCh_TagFail_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = gobj->user_data;
        fp->fv.mh.x2258 = ftMh_MS_Wait1_0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_TagFail_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagFail_Phys(HSD_GObj* gobj) {}

void ftCh_TagFail_Coll(HSD_GObj* gobj) {}

/// #fn_8015B2C0

bool fn_8015B4EC(Vec3* out_pos)
{
    HSD_GObj* gobj = ftBossLib_8015C3E8(0x1C);
    if (gobj != NULL) {
        Fighter* fp = gobj->user_data;
        lb_8000B1CC(fp->parts[5].joint, 0, out_pos);
        return true;
    }
    return false;
}

/// #fn_8015B548

void ftCo_CaptureCrazyHand_Anim(HSD_GObj* gobj) {}

void ftCo_CaptureCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureCrazyHand_Coll(HSD_GObj* gobj) {}

/// #ftCh_GrabUnk1_8015B670

void ftCo_CaptureDamageCrazyHand_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_GrabMash(fp, p_ftCommonData->x3A8);
    if (fp->grab_timer <= ftCh_Init_804DA1D8) {
        ftCh_GrabUnk1_8015B778(gobj);
        ftCh_Init_80159098(fp->victim_gobj);
    }
}
void ftCo_CaptureDamageCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureDamageCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureDamageCrazyHand_Coll(HSD_GObj* gobj) {}

/// #ftCh_GrabUnk1_8015B778

void ftCh_GrabUnk1_8015B800(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x221E_b7 = false;
    fp->facing_dir = -fp->facing_dir;
    ftCo_CaptureCut_Enter(gobj);
}

void ftCo_CaptureWaitCrazyHand_Anim(HSD_GObj* gobj) {}

void ftCo_CaptureWaitCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureWaitCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureWaitCrazyHand_Coll(HSD_GObj* gobj) {}

void ftCh_GrabUnk1_8015B850(HSD_GObj* gobj, int unused_state)
{
    s32 unused[4];
    Fighter* fp = gobj->user_data;
    HSD_GObj* victim_gobj = fp->victim_gobj;
    Fighter* victim_fp = victim_gobj->user_data;
    s32 flag = 0;

    fp->facing_dir = victim_fp->facing_dir;
    *(s32*) &fp->mv.mh.unk0.x0 = flag;
    {
        f32 zero = 0.0f;
        f32 one = 1.0f;
        Fighter_ChangeMotionState(gobj, 0x153, 0, zero, one, zero, NULL);
    }
    fp->invisible = flag;
    fp->accessory1_cb = ftCo_800DE508;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
}
void ftCo_ThrownCrazyHand_Anim(HSD_GObj* gobj) {}

void ftCo_ThrownCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_ThrownCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_ThrownCrazyHand_Coll(HSD_GObj* gobj) {}

void ftCh_GrabUnk1_8015B8FC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 state = fp->fv.ch.x2258;

    if (state == 0x155 || state == 0x184) {
        f32 anim_frame = fp->cur_anim_frame;
        f32 one = 1.0f;
        f32 zero = 0.0f;
        Fighter_ChangeMotionState(gobj, 0x184, 0, anim_frame, one, zero, NULL);
    } else {
        f32 zero = 0.0f;
        f32 one = 1.0f;
        Fighter_ChangeMotionState(gobj, 0x184, 0, zero, one, zero, NULL);
        ftAnim_8006EBA4(gobj);
    }

    fp->fv.ch.x2258 = 0x184;
}
void ftCh_GrabUnk1_8015B998(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 state = fp->fv.ch.x2258;

    if (state == 0x156 || state == 0x185) {
        f32 anim_frame = fp->cur_anim_frame;
        f32 one = 1.0f;
        f32 zero = 0.0f;
        Fighter_ChangeMotionState(gobj, 0x185, 0, anim_frame, one, zero, NULL);
    } else {
        f32 zero = 0.0f;
        f32 one = 1.0f;
        Fighter_ChangeMotionState(gobj, 0x185, 0, zero, one, zero, NULL);
        ftAnim_8006EBA4(gobj);
    }

    fp->fv.ch.x2258 = 0x185;
}
/// #ftCh_GrabUnk1_8015BA34

void ftCh_TagCancel_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->fv.mh.x2258 = 0x184;
        Fighter_ChangeMotionState(gobj, 0x184, 0, 0.0f, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
}

void ftCh_TagCancel_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x14,
                       *(float*) &da->x10);
}

void ftCh_TagCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.mh.unk0.x18 == 0.0f) {
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
        if (fp->mv.mh.unk0.x4 != NULL) {
            fp->mv.mh.unk0.x4(gobj);
        }
    }
}

void ftCh_Init_80156198(HSD_GObj* gobj);

void ftCh_GrabUnk1_8015BC88(HSD_GObj* gobj)
{
    Vec3 pos;
    s32 unused[4];
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attrs = fp->ft_data->ext_attr;

    fp->mv.mh.unk0.x20 = 0;
    pos.x = *(f32*) &attrs->x18;
    pos.y = *(f32*) &attrs->x1C;
    pos.z = 0.0f;
    fp->fv.ch.x2258 = 0x184;

    fp = gobj->user_data;
    if (fp->fv.ch.x2258 == 0x156) {
        ftCh_GrabUnk1_8015B998(gobj);
    } else {
        ftCh_GrabUnk1_8015B8FC(gobj);
    }

    fp->mv.mh.unk0.x4 = ftCh_Init_80156198;
    fp->mv.mh.unk0.xC = pos;
}

struct {
    enum_t asids[18];
    s8 bytes[64];
} ftCh_Init_803D4878 = {
    { ftMh_MS_Entry, ftMh_MS_Damage2, ftMh_MS_SweepLoop, ftMh_MS_Slap,
      ftMh_MS_WalkLoop, ftMh_MS_Drill, ftMh_MS_RockCrushUp,
      ftMh_MS_RockCrushDown, ftMh_MS_BackDisappear, ftMh_MS_Wait1_1,
      ftMh_MS_Grab, ftMh_MS_Poke1, ftMh_MS_FingerBeamStart,
      ftMh_MS_BackAirplane2, ftMh_MS_BackAirplane3, ftMh_MS_Squeezing1,
      ftMh_MS_Squeeze, ftMh_MS_Throw },
    { 0,  1,  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
      16, 17, 0, 0, 0, 4, 4, 4, 8, 3, 11, 2,  13, 2,  15, 3,
      1,  2,  3, 4, 5, 0, 2, 3, 4, 5, 0,  1,  3,  4,  5,  0,
      1,  2,  4, 5, 0, 1, 2, 3, 5, 0, 1,  2,  3,  4,  0,  0 },
};

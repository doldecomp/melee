#include "placeholder.h"

#include <platform.h>

#include "cm/camera.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_CaptureDamageKoopa.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_Throw.h"
#include "ftCommon/ftCo_Thrown.h"
#include "ftCommon/ftCo_ThrownKoopa.h"

#include "ftKoopa/forward.h"

#include "ftKoopa/ftKp_Init.h"
#include "ftKoopa/ftKp_Unk1.h"
#include "ftKoopa/types.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

#include <baselib/forward.h>

#include <trigf.h>
#include <baselib/gobj.h>

inline void inlineA0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.kp.specials.x4) {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirSHit1,
                                  Ft_MF_SkipMatAnim, 0, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirSHit0_0, Ft_MF_None,
                                  0, 1, 0, NULL);
    }
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.specials.b_held = false;
    fp->cmd_vars[0] = 0;
}

static inline void inlineA1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirSHit0_1,
                              Ft_MF_SkipMatAnim | Ft_MF_Unk19,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftAnim_8006F0FC(gobj, 0);
    fp->mv.kp.specials.b_held = false;
    fp->cmd_vars[0] = 0;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKp_SpecialAirSHit_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    if (fp->cmd_vars[0] != 0 && fp->mv.kp.specials.x4) {
        ftColl_8007ABD0(fp->x914, da->x2C, gobj);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.kp.specials.b_held) {
            fp->mv.kp.specials.x4 = true;
            inlineA0(gobj);
            ftCo_800BCAF4(fp->victim_gobj);
        } else {
            inlineA1(gobj);
        }
    }
}

void ftKp_SpecialSWait_Anim(HSD_GObj* gobj) {}

void ftKp_SpecialAirSWait_Anim(HSD_GObj* gobj) {}

static inline void doEndFAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FORCE_PAD_STACK(4 * 2);
    if (ftCheckThrowB4(fp)) {
        fp->facing_dir = -fp->facing_dir;
        fp->mv.kp.specials.xC = true;
    }
    if (fp->cmd_vars[0] != 0) {
        HSD_GObj* victim_gobj = fp->victim_gobj;
        if (victim_gobj != NULL) {
            ftCommon_8007E2F4(fp, 0);
            ftCo_800DE2A8(gobj, victim_gobj);
            ftCo_800DE7C0(victim_gobj, 0, 0);
            fp->cmd_vars[0] = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKp_SpecialSEndF_Anim(HSD_GObj* gobj)
{
    doEndFAnim(gobj, ft_8008A2BC);
}

static inline void doEndBAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    FORCE_PAD_STACK(4 * 2);
    ftKp_SpecialS_80132E30(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKp_SpecialSEndB_Anim(HSD_GObj* gobj)
{
    doEndBAnim(gobj, ft_8008A2BC);
}

void ftKp_SpecialAirSEndF_Anim(HSD_GObj* gobj)
{
    doEndFAnim(gobj, ftCo_Fall_Enter);
}

void ftKp_SpecialAirSEndB_Anim(HSD_GObj* gobj)
{
    doEndBAnim(gobj, ftCo_Fall_Enter);
}

inline void ftKoopa_SpecialS_ChangeAction(HSD_GObj* gobj,
                                          ftKoopa_MotionState kp_msid_f,
                                          ftCommon_MotionState victim_msid_f,
                                          ftKoopa_MotionState kp_msid_b,
                                          ftCommon_MotionState victim_msid_b)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    if (fp->mv.kp.specials.facing_dir == +1) {
        Fighter_ChangeMotionState(gobj, kp_msid_f, Ft_MF_Unk19, 0, 1, 0, NULL);
        ftCo_800BCDE0(fp->victim_gobj, victim_msid_f);
    } else {
        Fighter_ChangeMotionState(gobj, kp_msid_b, Ft_MF_Unk19, 0, 1, 0, NULL);
        ftCo_800BCDE0(fp->victim_gobj, victim_msid_b);
    }
}

static s32 ftKp_SpecialS_set_dir(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    s32 facing_dir = 0;
    if (fp->input.x668 & HSD_PAD_B) {
        fp->mv.kp.specials.b_held = true;
    }
    if (fp->input.lstick1.x > -da->x30 && fp->input.lstick.x < -da->x30) {
        facing_dir = -1;
    }
    if (fp->input.lstick1.x < da->x30 && fp->input.lstick.x > da->x30) {
        facing_dir = +1;
    }
    fp->mv.kp.specials.facing_dir = fp->facing_dir * facing_dir;
    return facing_dir;
}

/// @todo Shared inline with #ftKp_SpecialAirSHit_IASA.
void ftKp_SpecialSHit_IASA(HSD_GObj* gobj)
{
    s32 facing_dir = ftKp_SpecialS_set_dir(gobj);
    PAD_STACK(16);
    if (facing_dir != 0) {
        ftKoopa_SpecialS_ChangeAction(
            gobj, ftKp_MS_SpecialSEndF, ftCo_MS_ThrownKoopaF,
            ftKp_MS_SpecialSEndB, ftCo_MS_ThrownKoopaB);
    }
}

/// @todo Shared inline with #ftKp_SpecialSHit_IASA.
void ftKp_SpecialAirSHit_IASA(HSD_GObj* gobj)
{
    s32 facing_dir = ftKp_SpecialS_set_dir(gobj);
    PAD_STACK(16);
    if (facing_dir != 0) {
        ftKoopa_SpecialS_ChangeAction(
            gobj, ftKp_MS_SpecialAirSEndF, ftCo_MS_ThrownKoopaAirF,
            ftKp_MS_SpecialAirSEndB, ftCo_MS_ThrownKoopaAirB);
    }
}

inline void ftKp_SpecialSWait_IASA_inline(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.kp.specials.x4) {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialSHit1,
                                  Ft_MF_SkipMatAnim, 0, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialSHit0_0, Ft_MF_None, 0,
                                  1, 0, NULL);
    }
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.specials.b_held = false;
    fp->cmd_vars[0] = 0;
}

void ftKp_SpecialSWait_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 facing_dir = ftKp_SpecialS_set_dir(gobj);
    PAD_STACK(16);
    if (facing_dir != 0) {
        ftKoopa_SpecialS_ChangeAction(
            gobj, ftKp_MS_SpecialSEndF, ftCo_MS_ThrownKoopaF,
            ftKp_MS_SpecialSEndB, ftCo_MS_ThrownKoopaB);
    } else {
        if (fp->mv.kp.specials.b_held) {
            fp->mv.kp.specials.x4 = true;
            ftKp_SpecialSWait_IASA_inline(gobj);
            ftCo_800BCAF4(fp->victim_gobj);
        }
    }
}

static void ftKp_SpecialAirSWait_IASA_inline_2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ca.specialhi.vel.x != 0) {
        Fighter_ChangeMotionState(gobj, 0x163, 0x80U, 0.0f, 1.0f, 0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, 0x162, 0U, 0.0f, 1.0f, 0.0f, NULL);
    }
    fp->x2222_b2 = 1;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.specials.b_held = false;
    fp->cmd_vars[0] = 0;
}

void ftKp_SpecialAirSWait_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 facing_dir = ftKp_SpecialS_set_dir(gobj);
    PAD_STACK(16);
    if (facing_dir != 0) {
        ftKoopa_SpecialS_ChangeAction(
            gobj, ftKp_MS_SpecialAirSEndF, ftCo_MS_ThrownKoopaAirF,
            ftKp_MS_SpecialAirSEndB, ftCo_MS_ThrownKoopaAirB);
    } else {
        if (fp->mv.kp.specials.b_held) {
            fp->mv.kp.specials.x4 = true;
            inlineA0(gobj);
            ftCo_800BCAF4(fp->victim_gobj);
        }
    }
}

void ftKp_SpecialSStart_Phys(Fighter_GObj* gobj)
{
    ft_800850B4(gobj);
}

void ftKp_SpecialAirSStart_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 vel_y = fp->self_vel.y;
    ft_80085134(gobj);
    fp->self_vel.y = vel_y;
    ftCommon_8007D4B8(fp);
}

void ftKp_SpecialSHit_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialAirSHit_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKp_SpecialSWait_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialAirSWait_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKp_SpecialSEndF_Phys(Fighter_GObj* gobj)
{
    ft_800850B4(gobj);
}

void ftKp_SpecialSEndB_Phys(Fighter_GObj* gobj)
{
    ft_800850B4(gobj);
}

void ftKp_SpecialAirSEndF_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKp_SpecialAirSEndB_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKp_SpecialSStart_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftKp_SpecialS_8013319C);
}

void ftKp_SpecialAirSStart_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftKp_SpecialS_8013322C);
}

void ftKp_SpecialSHit_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, ftKp_SpecialS_801332C4);
}

void ftKp_SpecialAirSHit_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftKp_SpecialS_80133324);
}

void ftKp_SpecialSWait_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, ftKp_SpecialS_80133398);
}

void ftKp_SpecialAirSWait_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftKp_SpecialS_801333F8);
}

void ftKp_SpecialSEndF_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, ftKp_SpecialS_80133484);
}

void ftKp_SpecialSEndB_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, ftKp_SpecialS_80133484);
}

void ftKp_SpecialAirSEndF_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftKp_SpecialS_801334E4);
}

void ftKp_SpecialAirSEndB_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftKp_SpecialS_8013359C);
}

static void fn_80134518(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(0x4D8, gobj, &fp->cur_pos);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

static void fn_80134590(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (!fp->x2219_b0) {
        efSync_Spawn(0x4DF, gobj, fp->parts->joint);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

static void ftKp_SpecialLw_Enter_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags_b0 = false;
    fp->x6A4_transNOffset.y = 0.0f;
    fp->x2223_b4 = true;
}

void ftKp_SpecialLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);
    fp->self_vel.x = fp->self_vel.y = 0.0f;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x169, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftKp_SpecialLw_Enter_inline(gobj);
}

void ftKp_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    fp->self_vel.x *= da->x80;
    fp->self_vel.y *= da->x84;
    Fighter_ChangeMotionState(gobj, 0x16A, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftKp_SpecialLw_Enter_inline(gobj);
}

void ftKp_SpecialLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKp_SpecialLw_80134988(gobj);
    }
}

void ftKp_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->cmd_vars[1] = 1;
    }
}

void ftKp_SpecialLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80085134(gobj);
    if (fp->self_vel.y < 0.0f) {
        fp->self_vel.y = 0.0f;
    }
}

void ftKp_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    ftCommon_8007D494(fp, da->x8C, da->x90);
    ftCommon_8007CE94(fp, da->x88);
    if ((fp->self_vel.y < da->x94) || (fp->cmd_vars[1] != 0)) {
        fp->self_vel.y = da->x94;
    }
    if (fp->cmd_vars[1] != 0) {
        fp->self_vel.x = 0.0f;
        if (!fp->x2219_b0) {
            fp->accessory4_cb = fn_80134590;
        }
    }
}

void ftKp_SpecialLw_Coll(Fighter_GObj* gobj)
{
    ftKp_SpecialAirLw_Coll(gobj);
}

void ftKp_SpecialAirLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
        if ((fp->cmd_vars[0] != 0) && fp->self_vel.y <= 0.0f) {
            ftKp_SpecialLw_80134A5C(gobj);
        } else {
            ftCommon_8007D5D4(fp);
            ftCommon_8007D5BC(fp);
        }
    } else if ((fp->cmd_vars[0] != 0) && (ftCliffCommon_80081298(gobj) != 0)) {
        ftCliffCommon_80081370(gobj);
    }
}

void ftKp_SpecialLw_80134988(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirLw, 0x0C4C5088, 30.0f,
                              1.0f, 0.0f, NULL);
}

void ftKp_SpecialLwLanding_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKp_SpecialLwLanding_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialLwLanding_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKp_SpecialLw_80134A5C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->gr_vel = 0.0f;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x16B, 0U, 0.0f, 1.0f, 0.0f, NULL);
    fp->accessory4_cb = fn_80134518;
}

Item_GObj* it_802ACBA0(Item_GObj* arg0, Vec3* arg1, f32 farg1, bool arg2,
                       s32 arg3, s32 arg4, s32 arg5, s32 arg6);

static inline int ftKp_SpecialLw_80134ACC_inline(Fighter_GObj* gobj,
                                                 enum_t* dirs)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int new_facing;
    switch (fp->mv.kp.specials.facing_dir) {
    case 1:
    case 2:
        new_facing = dirs[HSD_Randi(0x20) + 0x20];
        break;
    case 0:
    case 3:
    default:
        if (dirs[HSD_Randi(0x20)] == 0) {
            new_facing = dirs[HSD_Randi(0x20) + 0x20];
        } else {
            new_facing = dirs[HSD_Randi(0x20) + 0x40];
        }
        break;
    }
    fp->mv.kp.specials.facing_dir = new_facing;
    return new_facing;
}

void ftKp_SpecialLw_80134ACC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    Vec3 v;
    enum_t* dirs = ftKp_Init_803CF2A0;
    PAD_STACK(12);
    lb_8000B1CC(fp->parts[48].joint, NULL, &v);
    v.x += fp->x34_scale.y * (da->x24 * fp->facing_dir);
    v.y += da->x28 * fp->x34_scale.y;
    it_802ACBA0(gobj, &v, fp->facing_dir, fp->mv.kp.specials.x4,
                ftKp_SpecialLw_80134ACC_inline(gobj, dirs), fp->fv.kp.x222C,
                fp->fv.kp.x2230, 100);
    if (fp->mv.kp.specials.x14 == 0) {
        fp->mv.kp.unk1.x4 = Item_8026AE60();
        ft_80089824(gobj);
        ft_800892A0(gobj);
    }
    if ((fp->mv.kp.specials.x14 % 3) == 0) {
        f32 f = (fp->fv.kp.x2230 - da->x1C) / (da->x18 - da->x1C);
        if (f < 0.3333f) {
            if (fp->kind == FTKIND_KOOPA) {
                ft_PlaySFX(fp, 0x24A2B, 0x7F, 0x40);
            } else {
                ft_PlaySFX(fp, 0x1D4F3, 0x7F, 0x40);
            }
        } else if (f < 0.6666f) {
            if (fp->kind == FTKIND_KOOPA) {
                ft_PlaySFX(fp, 0x24A28, 0x7F, 0x40);
            } else {
                ft_PlaySFX(fp, 0x1D4F0, 0x7F, 0x40);
            }
        } else if (fp->kind == FTKIND_KOOPA) {
            ft_PlaySFX(fp, 0x24A25, 0x7F, 0x40);
        } else {
            ft_PlaySFX(fp, 0x1D4ED, 0x7F, 0x40);
        }
    }
    fp->mv.kp.specials.x14 += 1;
    fp->mv.kp.specials.x14 %= 0xC;
}

void ftKp_SpecialLw_80134D78(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    if ((fp->motion_id >= 0x15B) || (fp->motion_id < 0x155)) {
        fp->fv.kp.x222C = fp->fv.kp.x222C + da->x8;
        if (fp->fv.kp.x222C > da->x10) {
            fp->fv.kp.x222C = da->x10;
        }
        fp->fv.kp.x2230 = fp->fv.kp.x2230 + da->xC;
        if (fp->fv.kp.x2230 > da->x18) {
            fp->fv.kp.x2230 = da->x18;
        }
    }
}

s32 ftKp_SpecialLw_80134DE0(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            ftKoopaAttributes* da = fp->dat_attrs;
            return da->x10;
        }
    }
    return 1;
}

s32 ftKp_SpecialLw_80134E1C(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            ftKoopaAttributes* da = fp->dat_attrs;
            return da->x18;
        }
    }
    return 2;
}

static void ftKp_SpecialN_Enter_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.kp.specials.b_held = 0;
    fp->mv.kp.unk1.x4 = Item_8026AE60();
    fp->mv.kp.specials.facing_dir = 0;
    fp->mv.kp.specials.x10 = 1;
    fp->mv.kp.specials.x14 = 0;
    fp->mv.kp.specials.x18 = 0;
    fp->mv.kp.unk1.xC = 0;
}

void ftKp_SpecialN_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x155, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftKp_SpecialN_Enter_inline(gobj);
}

void ftKp_SpecialAirN_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x158, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftKp_SpecialN_Enter_inline(gobj);
}

void ftKp_SpecialNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialN, Ft_MF_None, 0.0f,
                                  1.0f, 0.0f, NULL);
    }
}

static void ftKp_SpecialN_Anim_inline_1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cur_anim_frame == 0.0f) {
        fp->mv.kp.specials.x10 -= 1;
        if (fp->mv.kp.specials.x10 <= 0) {
            fp->mv.kp.specials.x10 = 0;
        }
    }
}

static void ftKp_SpecialN_Anim_inline_2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    if (fp->mv.kp.specials.x18 == 0) {
        Camera_80030E44(2, &fp->cur_pos);
    }
    fp->mv.kp.specials.x18 += 1;
    fp->mv.kp.specials.x18 %= da->x20;
}

void ftKp_SpecialN_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    ftKp_SpecialN_Anim_inline_1(gobj);
    ftKp_SpecialN_Anim_inline_2(gobj);
}

void ftKp_SpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKp_SpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirN, Ft_MF_None, 0.0f,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialAirN_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    ftKp_SpecialN_Anim_inline_1(gobj);
    ftKp_SpecialN_Anim_inline_2(gobj);
}

void ftKp_SpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKp_SpecialNStart_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->mv.co.itemthrow.xC >= da->x4) {
        if (fp->input.held_inputs & HSD_PAD_B) {
            if (!fp->mv.kp.specials.b_held) {
                ftKp_SpecialLw_80134ACC(gobj);
            }
        } else if (fp->mv.kp.specials.x10 != 0) {
            if (!fp->mv.kp.specials.b_held) {
                ftKp_SpecialLw_80134ACC(gobj);
            }
        } else {
            Fighter_ChangeMotionState(gobj, 0x157, 0, 0.0f, 1.0f, 0.0f, NULL);
        }
    } else if (!fp->mv.kp.specials.b_held) {
        ftKp_SpecialLw_80134ACC(gobj);
    }
    fp->mv.co.throw.x0 += 1;
    if (fp->mv.co.throw.x0 >= 3) {
        fp->mv.co.throw.x0 = 0;
    }
    fp->fv.kp.x222C -= 1.0f;
    if (fp->fv.kp.x222C < da->x14) {
        fp->fv.kp.x222C = da->x14;
    }
    fp->fv.kp.x2230 -= 1.0f;
    if (fp->fv.kp.x2230 < da->x1C) {
        fp->fv.kp.x2230 = da->x1C;
    }
    fp->mv.co.itemthrow.xC += 1;
    if (fp->mv.co.itemthrow.xC > da->x4) {
        fp->mv.co.itemthrow.xC = da->x4;
    }
}

void ftKp_SpecialNEnd_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialAirNStart_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->mv.co.itemthrow.xC >= da->x4) {
        if (fp->input.held_inputs & HSD_PAD_B) {
            if (!fp->mv.kp.specials.b_held) {
                ftKp_SpecialLw_80134ACC(gobj);
            }
        } else if (fp->mv.kp.specials.x10 != 0) {
            if (!fp->mv.kp.specials.b_held) {
                ftKp_SpecialLw_80134ACC(gobj);
            }
        } else {
            Fighter_ChangeMotionState(gobj, 0x15a, 0, 0.0f, 1.0f, 0.0f, NULL);
        }
    } else if (!fp->mv.kp.specials.b_held) {
        ftKp_SpecialLw_80134ACC(gobj);
    }
    fp->mv.co.throw.x0 += 1;
    if (fp->mv.co.throw.x0 >= 3) {
        fp->mv.co.throw.x0 = 0;
    }
    fp->fv.kp.x222C -= 1.0f;
    if (fp->fv.kp.x222C < da->x14) {
        fp->fv.kp.x222C = da->x14;
    }
    fp->fv.kp.x2230 -= 1.0f;
    if (fp->fv.kp.x2230 < da->x1C) {
        fp->fv.kp.x2230 = da->x1C;
    }
    fp->mv.co.itemthrow.xC += 1;
    if (fp->mv.co.itemthrow.xC > da->x4) {
        fp->mv.co.itemthrow.xC = da->x4;
    }
}

void ftKp_SpecialAirNEnd_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKp_SpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKp_SpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKp_SpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKp_SpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirNStart, 0x0C4C5080,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x159, 0x0C4C5880, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x15A, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x155, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x156, 0x0C4C5880U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

void ftKp_SpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x157, 0x0C4C5080U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
    }
}

static void ftKp_SpecialN_80135780_inline(Fighter_GObj* gobj)
{
    ftParts_80074B0C(gobj, 0, 1);
    ftColl_8007B128(gobj, 0x37, Intangible);
    ftColl_8007B128(gobj, 0x30, Intangible);
    ftColl_8007B128(gobj, 0x3C, Intangible);
    ftColl_8007B128(gobj, 0x21, Intangible);
    ftColl_8007B128(gobj, 0x3D, Intangible);
    ftColl_8007B128(gobj, 0x22, Intangible);
    ftColl_8007B128(gobj, 0xF, Intangible);
    ftColl_8007B128(gobj, 6, Intangible);
    ftColl_8007B128(gobj, 0x10, Intangible);
    ftColl_8007B128(gobj, 7, Intangible);
    ftColl_8007B128(gobj, 0x13, Intangible);
    ftColl_8007B128(gobj, 0xA, Intangible);
    ftCommon_8007F5CC(gobj, 0);
}

static void ftKp_SpecialN_80135780_inline_2(Fighter_GObj* gobj)
{
    ftParts_80074B0C(gobj, 0, 0);
    ftColl_8007B0C0(gobj, HurtCapsule_Enabled);
    ftCommon_8007F5CC(gobj, 1);
}

void ftKp_SpecialN_80135780(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (fp->ground_or_air == GA_Ground) {
        if (fp->cmd_vars[2] & 1) {
            ftKp_SpecialN_80135780_inline(gobj);
            fp->x221E_b4 = false;
        } else {
            ftKp_SpecialN_80135780_inline_2(gobj);
            fp->x221E_b4 = true;
        }
    } else {
        if (fp->cmd_vars[1] & 1) {
            ftKp_SpecialN_80135780_inline(gobj);
            fp->x221E_b4 = false;
        } else {
            ftKp_SpecialN_80135780_inline_2(gobj);
            fp->x221E_b4 = true;
        }
    }
}

static inline void ftKp_SpecialHi_Enter_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKp_Init_80132B38;
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKp_Init_80132B38;
}

void ftKp_SpecialHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x167, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftKp_SpecialHi_Enter_inline(gobj);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->self_vel.y = 0.0f;
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    fp->mv.co.capturekoopa.xC = 0.0f;
    fp->mv.kp.specials.x10 = 0;
    efSync_Spawn(0x4DA, gobj, fp->parts->joint);
    fp->x2219_b0 = true;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    ftAnim_8006EBA4(gobj);
}

void ftKp_SpecialAirHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x168, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftKp_SpecialHi_Enter_inline(gobj);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftCommon_8007CC78(fp, da->x60);
    fp->self_vel.y = da->x54;
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    fp->mv.co.capturekoopa.xC = 0.0f;
    fp->mv.kp.specials.x10 = 0;
    efSync_Spawn(0x4DA, gobj, fp->parts->joint);
    fp->x2219_b0 = true;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    ftAnim_8006EBA4(gobj);
    ftKp_SpecialHi_Anim(gobj);
}

void ftKp_SpecialHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.walk.middle_anim_frame += 1.0f;
    ftKp_SpecialN_80135780(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKp_SpecialAirHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);

    fp->mv.co.walk.middle_anim_frame += 1.0f;
    ftKp_SpecialN_80135780(gobj);
    if (fp->cmd_vars[2] == 2) {
        if (fp->ground_or_air == GA_Air) {
            ftCommon_8007D60C(fp);
            efLib_DestroyAll(gobj);
            fp->x2219_b0 = false;
            fp->pre_hitlag_cb = NULL;
            fp->post_hitlag_cb = NULL;
            if (da->x7C == 0.0f) {
                ftCo_Fall_Enter(gobj);
            } else {
                ftCo_80096900(gobj, 1, 0, 1, 1.0f, da->x7C);
            }
        }
    } else if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D60C(fp);
        if (da->x7C == 0.0f) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0f, da->x7C);
        }
    }
}

void ftKp_SpecialHi_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialAirHi_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialHi_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->cmd_vars[0] == 0) {
        ftCommon_8007CADC(fp, 0.0f, da->x68, da->x60);
        ftCommon_8007CB74(gobj);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftKp_SpecialAirHi_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->cmd_vars[0] == 0) {
        ftCommon_8007D494(fp, da->x58, da->x5C);
        ftCommon_8007D344(fp, 0.0f, da->x6C, da->x64);
    } else {
        ft_80084DB0(gobj);
    }
}

static void ftKp_SpecialHi_Coll_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->cmd_vars[3] != 0) && (fp->mv.kp.specials.x10 != 0)) {
        ftParts_8007592C(fp, 0,
                         fp->facing_dir *
                             atan2f(fp->coll_data.floor.normal.x,
                                    fp->coll_data.floor.normal.y));
    } else {
        ftParts_8007592C(fp, 0, 0.0f);
    }
}

void ftKp_SpecialHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, 0x168, 0x0C4C5292, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKp_SpecialHi_Enter_inline(gobj);
        ftCommon_8007D440(fp, da->x64);
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
        fp->mv.kp.specials.x10 = 0;
    } else {
        fp->mv.kp.specials.x10 = 1;
    }
    ftKp_SpecialN_80135780(gobj);
    ftKp_SpecialHi_Coll_inline(gobj);
}

static inline void ftKp_SpecialAirHi_Coll_inline(Fighter_GObj* gobj,
                                                 Fighter* fp,
                                                 ftKoopaAttributes* da)
{
    ftCommon_8007D7FC(fp);
    da->x70 = da->x70;
    if ((da->x70 < fp->mv.co.walk.middle_anim_frame) &&
        (fp->mv.co.walk.middle_anim_frame < da->x70))
    {
        Fighter_ChangeMotionState(gobj, 0x167, 0x0C4C5292,
                                  fp->cur_anim_frame - da->x78, 1.0f, 0.0f,
                                  NULL);
        ftKp_SpecialHi_Enter_inline(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, 0x167, 0x0C4C5292, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        ftKp_SpecialHi_Enter_inline(gobj);
    }
    ftCommon_8007CC78(fp, da->x60);
}

static inline void ftKp_SpecialAirHi_Coll_inline_2(Fighter_GObj* gobj)
{
    Fighter* fp;
    ftKp_SpecialN_80135780(gobj);
    fp = GET_FIGHTER(gobj);
    if ((fp->cmd_vars[3] != 0) && (fp->mv.kp.specials.x10 != 0)) {
        ftParts_8007592C(fp, 0,
                         fp->facing_dir *
                             atan2f(fp->coll_data.floor.normal.x,
                                    fp->coll_data.floor.normal.y));
    } else {
        ftParts_8007592C(fp, 0, 0.0f);
    }
}

void ftKp_SpecialAirHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->self_vel.y >= 0.0f) {
        if (ft_80081D0C(gobj) != GA_Ground) {
            ftKp_SpecialAirHi_Coll_inline(gobj, fp, da);
            fp->pre_hitlag_cb = efLib_PauseAll;
            fp->post_hitlag_cb = efLib_ResumeAll;
            fp->mv.kp.specials.x10 = 1;
        } else {
            fp->mv.kp.specials.x10 = 0;
        }
        ftKp_SpecialAirHi_Coll_inline_2(gobj);
    } else if (ft_CheckGroundAndLedge(gobj, 0) != 0) {
        ftKp_SpecialAirHi_Coll_inline(gobj, fp, da);
        fp->mv.kp.specials.x10 = 1;
        ftKp_SpecialAirHi_Coll_inline_2(gobj);
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    } else {
        fp->mv.kp.specials.x10 = 0;
        if (ftCliffCommon_80081298(gobj) != 0) {
            ftCliffCommon_80081370(gobj);
        }
    }
}

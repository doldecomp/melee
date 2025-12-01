#include "ftPe_SpecialS.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftPeach/types.h"
#include "it/items/itpeachexplode.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 11C2F4 */ static void reset(HSD_GObj* gobj);
/* 11C430 */ static void doAirEnd0(HSD_GObj* gobj);
/* 11C7B0 */ static void enterAirStart(HSD_GObj* gobj);
/* 11C818 */ static void enterStart(HSD_GObj* gobj);
/* 11C9E0 */ static void enterAirJump(HSD_GObj* gobj);
/* 11CBBC */ static void enterAirEnd(HSD_GObj* gobj);
/* 11CC18 */ static void enterEnd(HSD_GObj* gobj);
/* 11CC74 */ static void enterEndSmash(HSD_GObj* gobj);
/* 11CD30 */ static void enterAirEndSmash(HSD_GObj* gobj);

static MotionFlags const start_mf =
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
    Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;
static MotionFlags const end_mf = Ft_MF_SkipColAnim | Ft_MF_UpdateCmd;

static void reset(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->self_vel.x = 0;
    fp->x6A4_transNOffset.x = 0;
    if (fp->x673 < da->x30) {
        fp->x2070.x2072_b4 = true;
        fp->mv.pe.specials.x0 = true;
    } else {
        fp->mv.pe.specials.x0 = false;
    }
}

static inline void enter(HSD_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->x21EC = reset;
    fp->self_vel.y = 0;
    fp->gr_vel = da->x34 * fp->facing_dir;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftPe_SpecialS_Enter(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->x21EC = reset;
    fp->self_vel.y = 0;
    fp->gr_vel = da->x34 * fp->facing_dir;
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialSStart, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

void ftPe_SpecialAirS_Enter(HSD_GObj* gobj)
{
    u8 _[16];
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    fp->x21EC = reset;
    fp->self_vel.y = da->x40;
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSStart, Ft_MF_None, 0, 1,
                              0, NULL);
    ftAnim_8006EBA4(gobj);
}

static void doAirEnd0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221C_b5) {
        Fighter* other_fp = GET_FIGHTER(fp->unk_gobj);
        if (other_fp != NULL) {
            switch (other_fp->kind) {
            case FTKIND_MARS:
            case FTKIND_EMBLEM: {
                FtMotionId msid = other_fp->motion_id;
                if (msid != 369 && msid != 371) {
                    return;
                }
                break;
            }
            case FTKIND_PEACH: {
                FtMotionId msid = other_fp->motion_id;
                if (msid != 365 && msid != 367) {
                    return;
                }
                break;
            }
            default:
                return;
            }
        }
    }
    fp->self_vel.x = 0;
    if (fp->self_vel.y >= 0) {
        fp->self_vel.y = 0;
    }
    fp->cmd_vars[2] = 1;
    enterAirEndSmash(gobj);
}

void ftPe_SpecialSStart_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftAnim_IsFramesRemaining(gobj)) {
        return;
    }
    if (fp->cmd_vars[0]) {
        enterEndSmash(gobj);
    } else {
        ftCommon_8007D5D4(fp);
        fp->cur_pos.x += -4 * fp->facing_dir * fp->x34_scale.y;
        fp->cur_pos.y += 3.5f * fp->x34_scale.y;
        enterAirJump(gobj);
    }
}

void ftPe_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->cmd_vars[0]) {
            enterAirEndSmash(gobj);
        } else {
            enterAirJump(gobj);
        }
    }
}

void ftPe_SpecialSStart_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialAirSStart_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialSStart_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    ftCommon_8007CA80(fp, da->specials_start_accel * fp->facing_dir,
                      da->specials_start_vel_x * fp->facing_dir, 0);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftPe_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPe_SpecialSStart_Coll(Fighter_GObj* gobj)
{
    CollData* coll;
    Fighter* fp = gobj->user_data;
    coll = &fp->coll_data;
    if (!ft_800827A0(gobj)) {
        enterAirStart(gobj);
    }
    {
        u32 env_flags = coll->env_flags;
        if ((env_flags & Collide_RightWallMask &&
             fp->facing_dir == (float) -1.0) ||
            (env_flags & Collide_LeftWallMask && fp->facing_dir == 1.0f))
        {
            fp->gr_vel = 0;
            fp->cmd_vars[0] = 1;
        }
    }
}

void ftPe_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if (ft_80081D0C(gobj)) {
        enterStart(gobj);
    }
    if (coll->env_flags & Collide_CeilingMask) {
        fp->self_vel.y = 0;
        fp->cmd_vars[0] = 1;
    }
    {
        u32 env_flags = coll->env_flags;
        if ((env_flags & Collide_RightWallMask &&
             fp->facing_dir == (float) -1.0) ||
            (env_flags & Collide_LeftWallMask && fp->facing_dir == +1))
        {
            fp->self_vel.x = 0;
            fp->cmd_vars[0] = 1;
        }
    }
}

static void enterAirStart(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.x = 0;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSStart, start_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}

static void enterStart(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialSStart, start_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}

void ftPe_SpecialAirSJump_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    if (GET_FIGHTER(gobj)->cmd_vars[3] != 0 || !ftAnim_IsFramesRemaining(gobj))
    {
        enterAirEndSmash(gobj);
    }
}

void ftPe_SpecialAirSJump_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialAirSJump_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[1]) {
        ftCommon_ApplyFrictionAir(fp, da->x54);
    }
    ftCommon_Fall(fp, fp->cmd_vars[1] ? da->x58_gravity : da->x50_gravity,
                  da->x5C_terminal_vel);
}

void ftPe_SpecialAirSJump_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
        enterEndSmash(gobj);
    }
    {
        u32 env_flags = coll->env_flags;
        if ((env_flags & Collide_RightWallMask &&
             fp->facing_dir == (float) -1.0) ||
            (env_flags & Collide_LeftWallMask && fp->facing_dir == +1))
        {
            fp->cmd_vars[2] = 1;
            enterAirEndSmash(gobj);
        }
    }
}

static void enterAirJump(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftPe_DatAttrs* da = fp->dat_attrs;
    u8 _[8];

    if (fp->mv.pe.specials.x0) {
        fp->self_vel.x = da->specials_smash_vel_x * fp->facing_dir;
    } else {
        fp->self_vel.x = da->specials_vel_x * fp->facing_dir;
    }
    fp->self_vel.y = da->specials_vel_y;
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSJump, Ft_MF_None, 0, 1,
                              0, NULL);
    fp = gobj->user_data;
    fp->x21F8 = ftCommon_8007F76C;
    fp->hurtbox_detect_cb = doAirEnd0;
}

void ftPe_SpecialSEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftPe_SpecialAirSEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftPe_SpecialSEnd_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialAirSEnd_IASA(HSD_GObj* gobj) {}

void ftPe_SpecialSEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPe_SpecialAirSEnd_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPe_SpecialSEnd_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        enterAirEnd(gobj);
    }
}

void ftPe_SpecialAirSEnd_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        enterEnd(gobj);
    }
}

void enterAirEnd(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSEnd_0, end_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}

void enterEnd(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialSEnd, end_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}

static void doPostEnd(HSD_GObj* gobj)
{
    u8 _[38] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[2]) {
        Vec3 vec;
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, NULL, &vec);
        vec.z = 0;
        {
            float facing_dir = fp->facing_dir;
            it_802BD158(gobj, &vec, fp->mv.pe.specials.x0, facing_dir);
            fp->self_vel.x = da->specials_end_vel_x * fp->facing_dir;
            fp->self_vel.y = da->specials_end_vel_y;
        }
    }
    fp->x21F8 = ftCommon_8007F7B4;
}

static void doPostEnd_SmallerStack(HSD_GObj* gobj)
{
    u8 _[34] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[2]) {
        Vec3 vec;
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, NULL, &vec);
        vec.z = 0;
        {
            float facing_dir = fp->facing_dir;
            it_802BD158(gobj, &vec, fp->mv.pe.specials.x0, facing_dir);
            fp->self_vel.x = da->specials_end_vel_x * fp->facing_dir;
            fp->self_vel.y = da->specials_end_vel_y;
        }
    }
    fp->x21F8 = ftCommon_8007F7B4;
}

static void enterEndSmash(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialSEnd, Ft_MF_None, 0, 1, 0,
                              NULL);
    doPostEnd(gobj);
}

void enterAirEndSmash(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;

    fp->self_vel.x /= da->x68;
    fp->self_vel.y /= da->x6C;
    if (fp->cmd_vars[2] != 0U) {
        Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSEnd_1, 0, 0.0f,
                                  1.0f, 0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirSEnd_0, 0, 0.0f,
                                  1.0f, 0.0f, NULL);
    }
    doPostEnd_SmallerStack(gobj);
}

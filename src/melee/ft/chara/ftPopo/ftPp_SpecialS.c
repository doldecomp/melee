#include <platform.h>

#include "ef/eflib.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftNana/ftNn_Init.h"

#include "ftPopo/forward.h"

#include "ftPopo/ftPp_1211.h"
#include "ftPopo/ftPp_Init.h"
#include "ftPopo/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <math.h>
#include <math_ppc.h>
#include <trigf.h>
#include <dolphin/pad.h>
#include <melee/ft/chara/ftCommon/ftCo_Fall.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftPopo/ftPp_SpecialS.h>
#include <melee/it/items/itclimbersstring.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbvector.h>

/* 121AC8 */ void ftPp_SpecialHiThrow_0_IASA(Fighter_GObj* gobj);
/* 121ACC */ void ftPp_SpecialAirHiThrow_0_IASA(Fighter_GObj* gobj);
/* 121EB0 */ void ftPp_SpecialHiStart_1_IASA(Fighter_GObj* gobj);
/* 121EB4 */ void ftPp_SpecialAirHiStart_1_IASA(Fighter_GObj* gobj);
/* 1221B0 */ void ftPp_SpecialAirHiThrow_1_IASA(Fighter_GObj* gobj);
/* 12248C */ void ftPp_SpecialHiThrow2_IASA(Fighter_GObj* gobj);
/* 122490 */ void ftPp_SpecialAirHiThrow2_IASA(Fighter_GObj* gobj);
/* 122B0C */ void ftPp_SpecialLw_IASA(Fighter_GObj* gobj);
/* 122B10 */ void ftPp_SpecialAirLw_IASA(Fighter_GObj* gobj);

/* 1218AC */ void ftPp_SpecialHi_801218AC(Fighter_GObj* gobj);
/* 1218F8 */ void ftPp_SpecialHi_801218F8(Fighter_GObj* gobj);

static void setRefGObjFlagAndClear(Fighter* fp)
{
    Fighter_GObj* gobj = fp->x1A5C;
    Fighter* ref_fp;

    if (gobj != NULL) {
        ref_fp = gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        ref_fp->x1A5C = NULL;
    }
    fp->x1A5C = NULL;
}

void ftPp_SpecialS_8011F68C(Fighter_GObj* gobj)
{
    Fighter* fp;
    u8 _[16];

    fp = gobj->user_data;
    ftPartSetRotX(fp, 0, 0);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    setRefGObjFlagAndClear(fp);
}

bool ftPp_SpecialS_8011F6FC(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp != NULL) {
            return fp->cmd_vars[1];
        }
    }

    return true;
}

void ftPp_SpecialS_8011F720(Fighter_GObj* gobj)
{
    Fighter* fp;
    HSD_JObj* temp_r30;
    HSD_JObj* var_r0;
    f32 angle;
    HSD_GObj* temp_r3_2;

    fp = GET_FIGHTER(gobj);
    if (fp->mv.pp.specials.x8 != NULL) {
        if (fp->x2219_b0 && fp->mv.pp.specials.x8 != NULL) {
            temp_r3_2 = fp->mv.pp.specials.x8->x4;
            if (temp_r3_2 != NULL) {
                var_r0 =
                    HSD_JObjGetNext(HSD_JObjGetChild(GET_JOBJ(temp_r3_2)));
                temp_r30 = temp_r3_2->hsd_obj;
                if (fp->motion_id == ftPp_MS_SpecialS1 ||
                    fp->motion_id == ftPp_MS_SpecialS2)
                {
                    HSD_JObjClearFlagsAll(var_r0, JOBJ_HIDDEN);
                } else {
                    HSD_JObjSetFlagsAll(var_r0, JOBJ_HIDDEN);
                }
                if (fp->cmd_vars[3] != 0 && fp->mv.pp.specials.xC != 0) {
                    angle = -atan2f(fp->coll_data.floor.normal.x,
                                    fp->coll_data.floor.normal.y);
                    HSD_JObjSetRotationZ(temp_r30, angle);
                } else {
                    HSD_JObjSetRotationZ(temp_r30, 0.0F);
                }
                fp->pre_hitlag_cb = efLib_PauseAll;
                fp->post_hitlag_cb = efLib_ResumeAll;
                return;
            }
        }
        fp->mv.pp.specials.x8 = 0;
        fp->x2219_b0 = false;
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
    }
}

bool ftPp_SpecialS_8011F964(Fighter_GObj* gobj)
{
    switch (GET_FIGHTER(gobj)->motion_id) {
    case ftPp_MS_SpecialS2:
    case ftPp_MS_SpecialAirS2:
        return false;
    }
    return true;
}

static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftPp_Init_8011F060;
    fp->death2_cb = ftPp_Init_8011F060;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

static inline void inlineA1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.pp.specials.x8 = 0;
    fp->x2219_b0 = true;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

static inline void inlineA2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->mv.pp.specials.x0 = 0;
    fp->mv.pp.specials.x4 = 10;
    fp->mv.pp.specials.xC = 0;
    fp->mv.pp.specials.x8 = 0;
    fp->mv.pp.specials.x10 = 0;
    fp->mv.pp.specials.x14 = da->x68;
    fp->mv.pp.specials.x18 = NULL;
    fp->mv.pp.specials.x1C = 0;
    if (ftNn_Init_80123954(Player_GetEntityAtIndex(fp->player_id, 1),
                           fp->ground_or_air) == GA_Air)
    {
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialS1, Ft_MF_None, 0, 1, 0,
                                  NULL);
        fp->x1A5C = NULL;
    } else {
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialS2, Ft_MF_None, 0, 1, 0,
                                  NULL);
        fp->x1A5C = Player_GetEntityAtIndex(fp->player_id, 1);
    }
    fp->self_vel.y = 0;
    {
        float x_vel = da->x28 * fp->facing_dir;
        fp->self_vel.x = x_vel;
        fp->gr_vel = x_vel;
    }
}

void ftPp_SpecialS_Enter(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 6);
    inlineA2(gobj);
    inlineA0(gobj);
    ftAnim_8006EBA4(gobj);
    inlineA1(gobj);
    inlineA0(gobj);
}

/// @todo Can probably share some more code with #inlineA2
static inline void inlineB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->mv.pp.specials.x0 = 0;
    fp->mv.pp.specials.x4 = 10;
    fp->mv.pp.specials.xC = 0;
    fp->mv.pp.specials.x8 = 0;
    fp->mv.pp.specials.x10 = 0;
    fp->mv.pp.specials.x14 = da->x68;
    fp->mv.pp.specials.x18 = NULL;
    fp->mv.pp.specials.x1C = 0;
    if (ftNn_Init_80123954(Player_GetEntityAtIndex(fp->player_id, 1),
                           fp->ground_or_air) == GA_Air)
    {
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirS1, 0, 0, 1, 0,
                                  NULL);
        fp->x1A5C = NULL;
        fp->self_vel.y = da->x20;
    } else {
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirS2, 0, 0, 1, 0,
                                  NULL);
        fp->x1A5C = Player_GetEntityAtIndex(fp->player_id, 1);
        fp->self_vel.y = da->x24;
    }
    fp->self_vel.x = da->x2C * fp->facing_dir;
}

void ftPp_SpecialAirS_Enter(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 6);
    inlineB0(gobj);
    inlineA0(gobj);
    ftAnim_8006EBA4(gobj);
    inlineA1(gobj);
    inlineA0(gobj);
}

static inline void resetAnim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
    fp->pre_hitlag_cb = NULL;
    fp->post_hitlag_cb = NULL;
    fp->x1A5C = NULL;
    ft_8008A2BC(gobj);
}

void ftPp_SpecialS1_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 2);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        resetAnim(gobj);
    }
}

static inline void inlineC0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    fp->x1A5C = NULL;
}

static inline void inlineC1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPartSetRotX(fp, 0, 0);
    Fighter_UnkSetFlag_8006CFBC(gobj);

    if (fp->x1A5C != NULL) {
        inlineC0(fp->x1A5C);
    }
    fp->x1A5C = NULL;
    resetAnim(gobj);
}

void ftPp_SpecialS2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* nn_gobj = Player_GetEntityAtIndex(fp->player_id, 1);
    PAD_STACK(4 * 2);
    if (!ftAnim_IsFramesRemaining(gobj) || ftNn_Init_80123B10(nn_gobj)) {
        inlineC1(gobj);
    }
}

static inline void inline0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
    fp->pre_hitlag_cb = NULL;
    fp->post_hitlag_cb = NULL;
    fp->x1A5C = NULL;
}

void ftPp_SpecialAirS1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        inline0(gobj);
        if (da->x70 == 0.0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCommon_8007D60C(fp);
            ftCo_80096900(gobj, 1, 0, 1, 1.0F, da->x70);
        }
    }
}

static inline void inline1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPartSetRotX(fp, 0, 0.0F);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    setRefGObjFlagAndClear(fp);
}

void ftPp_SpecialAirS2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    Fighter_GObj* temp_r30 = Player_GetEntityAtIndex(fp->player_id, 1);
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj) || ftNn_Init_80123B10(temp_r30)) {
        inline1(gobj);
        inline0(gobj);
        if (da->x70 == 0.0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCommon_8007D60C(fp);
            ftCo_80096900(gobj, 1, 0, 1, 1.0F, da->x70);
        }
    }
}

void ftPp_SpecialS1_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    if (ABS(fp->input.lstick.x) >= da->x40) {
        fp->mv.pp.specials.x1C = fp->input.lstick.x * da->x30;
    } else {
        fp->mv.pp.specials.x1C = 0.0F;
    }
}

void ftPp_SpecialS2_IASA(Fighter_GObj* gobj)
{
    ftPp_SpecialS1_IASA(gobj);
}

void ftPp_SpecialAirS1_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    if (ABS(fp->input.lstick.x) >= da->x40) {
        fp->mv.pp.specials.x1C = fp->input.lstick.x * da->x34;
    } else {
        fp->mv.pp.specials.x1C = 0.0F;
    }
}

void ftPp_SpecialAirS2_IASA(Fighter_GObj* gobj)
{
    ftPp_SpecialAirS1_IASA(gobj);
}

void ftPp_SpecialS1_Phys(Fighter_GObj* gobj)
{
    ftIceClimberAttributes* temp_r28;
    Fighter* temp_r27;
    Fighter* fp;
    Fighter* temp_r5;
    Fighter* temp_r5_2;
    f32 temp_f1;
    f32 target_vel;
    ftIceClimberAttributes* temp_r30;

    PAD_STACK(0x18);

    fp = GET_FIGHTER(gobj);
    temp_r30 = fp->dat_attrs;
    if (fp->cmd_vars[0] == 0 && fp->mv.pp.specials.x1C != 0.0F) {
        target_vel =
            fp->mv.pp.specials.x1C > 0.0F ? temp_r30->x38 : -temp_r30->x38;
        ftCommon_8007CA80(fp, fp->mv.pp.specials.x1C, target_vel,
                          fp->co_attrs.gr_friction);
        temp_r5 = GET_FIGHTER(gobj);
        {
            ftIceClimberAttributes* da = temp_r5->dat_attrs;
            temp_r5->xE4_ground_accel_1 +=
                da->x6C * temp_r5->coll_data.floor.normal.x;
        }
        ftCommon_ClampGrVel(fp, temp_r30->x38);
        ftCommon_ApplyGroundMovementNoSlide(gobj);
    } else {
        float friction = fp->co_attrs.gr_friction;
        ftCommon_ApplyFrictionGround(fp, friction);
        ftCommon_ClampGrVel(fp, temp_r30->x38);
        ftCommon_ApplyGroundMovementNoSlide(gobj);
    }
    fp->mv.pp.specials.x14 += 1;
    if (fp->cmd_vars[2] != 0 && (fp->input.x668 & HSD_PAD_B)) {
        fp->mv.pp.specials.x10 += 1;
    }
    if (fp->mv.pp.specials.x10 != 0 && fp->mv.pp.specials.x14 > temp_r30->x68)
    {
        temp_r27 = GET_FIGHTER(gobj);
        temp_r28 = temp_r27->dat_attrs;
        ftCommon_8007D5D4(temp_r27);
        temp_r27->x74_anim_vel.x = temp_r27->xE4_ground_accel_1;
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirS1, 0x0C4C528A,
                                  temp_r27->cur_anim_frame, 1.0F, 0.0F, NULL);
        temp_r5_2 = GET_FIGHTER(gobj);
        temp_r5_2->take_dmg_cb = ftPp_Init_8011F060;
        temp_r5_2->death2_cb = ftPp_Init_8011F060;
        temp_r5_2->pre_hitlag_cb = efLib_PauseAll;
        temp_r5_2->post_hitlag_cb = efLib_ResumeAll;
        ftCommon_ClampSelfVelX(temp_r27, temp_r28->x3C);
        fp->self_vel.y += temp_r30->x60;
        fp->mv.pp.specials.x10 = 0;
        fp->mv.pp.specials.x14 = 0;
    }
    fp->mv.pp.specials.x18 += 1;
}

void ftPp_SpecialS2_Phys(Fighter_GObj* gobj)
{
    Fighter* temp_r31;
    ftIceClimberAttributes* temp_r30;
    ftIceClimberAttributes* temp_r28;
    Fighter* temp_r27;
    Fighter* temp_r5;
    Fighter* temp_r5_2;
    f32 temp_f1;
    f32 target_vel;

    PAD_STACK(0x18);

    temp_r31 = GET_FIGHTER(gobj);
    temp_r30 = temp_r31->dat_attrs;
    if (temp_r31->cmd_vars[0] == 0 && temp_r31->mv.pp.specials.x1C != 0.0F) {
        target_vel = temp_r31->mv.pp.specials.x1C > 0.0F ? temp_r30->x38
                                                         : -temp_r30->x38;
        ftCommon_8007CA80(temp_r31, temp_r31->mv.pp.specials.x1C, target_vel,
                          temp_r31->co_attrs.gr_friction);
        temp_r5 = GET_FIGHTER(gobj);
        {
            ftIceClimberAttributes* da = temp_r5->dat_attrs;
            temp_r5->xE4_ground_accel_1 +=
                da->x6C * temp_r5->coll_data.floor.normal.x;
        }
        ftCommon_ClampGrVel(temp_r31, temp_r30->x38);
        ftCommon_ApplyGroundMovementNoSlide(gobj);
    } else {
        float friction = temp_r31->co_attrs.gr_friction;
        ftCommon_ApplyFrictionGround(temp_r31, friction);
        ftCommon_ClampGrVel(temp_r31, temp_r30->x38);
        ftCommon_ApplyGroundMovementNoSlide(gobj);
    }
    temp_r31->mv.pp.specials.x14 += 1;
    if (((u32) temp_r31->cmd_vars[2] != 0) &&
        (temp_r31->input.x668 & HSD_PAD_B))
    {
        temp_r31->mv.pp.specials.x10 += 1;
    }
    if (temp_r31->mv.pp.specials.x10 != 0 &&
        temp_r31->mv.pp.specials.x14 > temp_r30->x68)
    {
        temp_r27 = GET_FIGHTER(gobj);
        temp_r28 = temp_r27->dat_attrs;
        ftCommon_8007D5D4(temp_r27);
        temp_r27->x74_anim_vel.x = temp_r27->xE4_ground_accel_1;
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirS2, 0xC4C528A,
                                  temp_r27->cur_anim_frame, 1.0F, 0.0F, NULL);
        temp_r5_2 = GET_FIGHTER(gobj);
        temp_r5_2->take_dmg_cb = ftPp_Init_8011F060;
        temp_r5_2->death2_cb = ftPp_Init_8011F060;
        temp_r5_2->pre_hitlag_cb = efLib_PauseAll;
        temp_r5_2->post_hitlag_cb = efLib_ResumeAll;
        ftCommon_ClampSelfVelX(temp_r27, temp_r28->x3C);
        temp_r31->self_vel.y += temp_r30->x64;
        temp_r31->mv.pp.specials.x10 = 0;
        temp_r31->mv.pp.specials.x14 = 0;
    }
    temp_r31->mv.pp.specials.x18 += 1;
}

void ftPp_SpecialAirS1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(8);

    fp->mv.pp.specials.x14 += 1;
    if (fp->cmd_vars[2] != 0 && (fp->input.x668 & HSD_PAD_B)) {
        fp->mv.pp.specials.x10 += 1;
    }
    if (fp->mv.pp.specials.x10 != 0 && fp->mv.pp.specials.x14 > da->x68) {
        fp->self_vel.y += da->x60;
        fp->mv.pp.specials.x10 = 0;
        fp->mv.pp.specials.x14 = 0;
    }
    fp->mv.pp.specials.x18 += 1;
    if (fp->mv.pp.specials.x18 < da->x5C) {
        ftCommon_Fall(fp, da->x4C_gravity, da->x54_terminal_vel);
    } else {
        ftCommon_FallBasic(fp);
    }
    if (fp->cmd_vars[0] == 0 && fp->mv.pp.specials.x1C != 0.0F) {
        f32 var_f0 = fp->mv.pp.specials.x1C > 0.0F ? da->x3C : -da->x3C;
        ftCommon_8007D2E8(fp, fp->mv.pp.specials.x1C, var_f0, 0.0F);
    } else {
        ftCommon_8007CEF4(fp);
    }
}

void ftPp_SpecialAirS2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(8);

    fp->mv.pp.specials.x14 += 1;
    if (fp->cmd_vars[2] != 0 && (fp->input.x668 & HSD_PAD_B)) {
        fp->mv.pp.specials.x10 += 1;
    }
    if (fp->mv.pp.specials.x10 != 0 && fp->mv.pp.specials.x14 > da->x68) {
        fp->self_vel.y += da->x64;
        fp->mv.pp.specials.x10 = 0;
        fp->mv.pp.specials.x14 = 0;
    }
    fp->mv.pp.specials.x18 += 1;
    if (fp->mv.pp.specials.x18 < da->x5C) {
        ftCommon_Fall(fp, da->x50_gravity, da->x58_terminal_vel);
    } else {
        ftCommon_FallBasic(fp);
    }
    if (fp->cmd_vars[0] == 0 && fp->mv.pp.specials.x1C != 0.0F) {
        f32 var_f0 = fp->mv.pp.specials.x1C > 0.0F ? da->x3C : -da->x3C;
        ftCommon_8007D2E8(fp, fp->mv.pp.specials.x1C, var_f0, 0.0F);
    } else {
        ftCommon_8007CEF4(fp);
    }
}

static ftCollisionBox ftNn_Init_803CD820 = {
    12, 0, -6, 6, 6, 6,
};

static inline void inline2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[3] != 0 && fp->mv.pp.specials.xC != 0) {
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
    } else {
        ftPartSetRotX(fp, 0, 0.0F);
    }
}

static inline void inline3(Fighter_GObj* gobj, int msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* temp_r30 = fp->dat_attrs;
    ftCommon_8007D5D4(fp);
    fp->x74_anim_vel.x = fp->xE4_ground_accel_1;
    Fighter_ChangeMotionState(gobj, msid, 0xC4C528A, fp->cur_anim_frame, 1.0F,
                              0.0F, NULL);
    inlineA0(gobj);
    ftCommon_ClampSelfVelX(fp, temp_r30->x3C);
}

void ftPp_SpecialS1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    bool temp_r3 = ft_80082888(gobj, &ftNn_Init_803CD820);
    bool var_r0 = false;
    PAD_STACK(0x18);
    if (fp->gr_vel != 0.0F) {
        if (fp->gr_vel > 0.0F) {
            var_r0 = fp->coll_data.env_flags & Collide_LeftWallMask;
        } else {
            var_r0 = fp->coll_data.env_flags & Collide_RightWallMask;
        }
    }
    if (var_r0) {
        if (ABS(fp->gr_vel) < da->x48) {
            fp->gr_vel = fp->gr_vel > 0.0F ? -da->x48 : da->x48;
        } else {
            fp->gr_vel *= -da->x44;
        }
    }
    if (!temp_r3) {
        inline3(gobj, ftPp_MS_SpecialAirS1);
        fp->mv.pp.specials.xC = 0;
    } else {
        fp->mv.pp.specials.xC = 1;
    }
    inline2(gobj);
    ftPp_SpecialS_8011F720(gobj);
    inlineA0(gobj);
}

void ftPp_SpecialS2_Coll(Fighter_GObj* gobj)
{
    Fighter* temp_r28 = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = temp_r28->dat_attrs;
    bool temp_r3 = ft_80082888(gobj, &ftNn_Init_803CD820);
    bool var_r0 = false;
    PAD_STACK(0x18);
    if (temp_r28->gr_vel != 0.0F) {
        if (temp_r28->gr_vel > 0.0F) {
            var_r0 = temp_r28->coll_data.env_flags & Collide_LeftWallMask;
        } else {
            var_r0 = temp_r28->coll_data.env_flags & Collide_RightWallMask;
        }
    }
    if (var_r0) {
        if (ABS(temp_r28->gr_vel) < da->x48) {
            temp_r28->gr_vel = temp_r28->gr_vel > 0.0F ? -da->x48 : da->x48;
        } else {
            temp_r28->gr_vel *= -da->x44;
        }
    }
    if (!temp_r3) {
        inline3(gobj, ftPp_MS_SpecialAirS2);
        temp_r28->mv.pp.specials.xC = 0;
    } else {
        temp_r28->mv.pp.specials.xC = 1;
    }
    inline2(gobj);
    ftPp_SpecialS_8011F720(gobj);
    inlineA0(gobj);
}

static inline void inline4(Fighter_GObj* gobj, int msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, msid, 0xC4C528A, fp->cur_anim_frame, 1.0F,
                              0.0F, NULL);
    inlineA0(gobj);
    fp->x74_anim_vel.y = 0.0F;
    fp->self_vel.y = 0.0F;
    ftCommon_ClampGrVel(fp, da->x38);
}

void ftPp_SpecialAirS1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    bool temp_r3;
    bool var_r0;
    PAD_STACK(0x20);

    temp_r3 = ft_800824A0(gobj, &ftNn_Init_803CD820);
    if ((fp->coll_data.env_flags & Collide_CeilingMask) == 1) {
        fp->self_vel.y = 0.0F;
    }
    var_r0 = false;
    if (fp->self_vel.x != 0.0F) {
        if (fp->self_vel.x > 0.0F) {
            var_r0 = fp->coll_data.env_flags & Collide_LeftWallMask;
        } else {
            var_r0 = fp->coll_data.env_flags & Collide_RightWallMask;
        }
    }
    if (var_r0) {
        if (ABS(fp->self_vel.x) < da->x48) {
            fp->self_vel.x = fp->self_vel.x > 0.0F ? -da->x48 : da->x48;
        } else {
            fp->self_vel.x *= -da->x44;
        }
    }
    if (temp_r3) {
        inline4(gobj, ftPp_MS_SpecialS1);
        fp->mv.pp.specials.xC = 1;
    } else {
        fp->mv.pp.specials.xC = 0;
    }
    inline2(gobj);
    ftPp_SpecialS_8011F720(gobj);
    inlineA0(gobj);
}

void ftPp_SpecialAirS2_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    bool temp_r3 = ft_800824A0(gobj, &ftNn_Init_803CD820);
    bool var_r0;
    PAD_STACK(0x20);
    if ((fp->coll_data.env_flags & Collide_CeilingMask) == 1) {
        fp->self_vel.y = 0.0F;
    }
    var_r0 = false;
    if (fp->self_vel.x != 0.0F) {
        if (fp->self_vel.x > 0.0F) {
            var_r0 = fp->coll_data.env_flags & Collide_LeftWallMask;
        } else {
            var_r0 = fp->coll_data.env_flags & Collide_RightWallMask;
        }
    }
    if (var_r0) {
        if (ABS(fp->self_vel.x) < da->x48) {
            fp->self_vel.x = fp->self_vel.x > 0.0F ? -da->x48 : da->x48;
        } else {
            fp->self_vel.x *= -da->x44;
        }
    }
    if (temp_r3) {
        inline4(gobj, ftPp_MS_SpecialS2);
        fp->mv.pp.specials.xC = 1;
    } else {
        fp->mv.pp.specials.xC = 0;
    }
    inline2(gobj);
    ftPp_SpecialS_8011F720(gobj);
    inlineA0(gobj);
}

void ftPp_SpecialS_80120E68(Fighter_GObj* gobj)
{
    Fighter* temp_r31;
    HSD_GObj* temp_r3;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;
    ftIceClimberAttributes* temp_r30;
    Fighter* temp_r29;
    PAD_STACK(0x8);

    temp_r31 = GET_FIGHTER(gobj);
    temp_r30 = temp_r31->dat_attrs;
    if (Player_GetEntityAtIndex(temp_r31->player_id, 1) != NULL) {
        temp_r29 = GET_FIGHTER(gobj);
        temp_r31->self_vel.x = temp_r29->cur_pos.x - temp_r31->cur_pos.x;
        temp_r31->self_vel.y = temp_r29->cur_pos.y - temp_r31->cur_pos.y;
        temp_r31->self_vel.z = 0.0F;
        temp_r31->self_vel.x =
            -(3.0F * temp_r29->facing_dir - temp_r31->self_vel.x);
        temp_r31->self_vel.y += 5.0F;
        lbVector_Normalize(&temp_r31->self_vel);
        temp_f3 = SQ(temp_r31->cur_pos.x - temp_r29->cur_pos.x);
        temp_f1 = SQ(temp_r31->cur_pos.y - temp_r29->cur_pos.y);
        temp_f2 = sqrtf(temp_f3 + temp_f1) / temp_r30->x98;
        temp_r31->self_vel.x *= temp_r30->x94 + temp_f2;
        temp_r31->self_vel.y *= temp_r30->x94 + temp_f2;
        if (temp_r31->self_vel.x > 0.0F) {
            temp_r31->facing_dir = +1.0F;
        } else {
            temp_r31->facing_dir = -1.0F;
        }
    }
}

/// #ftPp_SpecialS_80120FE0

void ftPp_SpecialS_801210C8(Fighter_GObj* arg0)
{
    Vec3 sp10;
    Fighter* fp = GET_FIGHTER(arg0);
    float dir;
    lb_8000B1CC(fp->parts[FtPart_L4thNb].joint, NULL, &sp10);
    dir = fp->facing_dir;
    fp->fv.pp.x2238 = it_802C27D4(arg0, &sp10, fp->motion_id, dir);
    fp->x1984_heldItemSpec = fp->fv.pp.x2238;
    if (fp->fv.pp.x2238 != NULL) {
        fp->death3_cb = ftPp_Init_8011F060;
        fp->take_dmg_cb = ftPp_Init_8011F060;
    }
}

void ftPp_SpecialS_8012114C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.pp.x2238 = NULL;
    fp->death3_cb = NULL;
    fp->take_dmg_cb = NULL;
}

void ftPp_SpecialS_80121164(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.pp.x2238 != NULL) {
        it_802C2750(fp->fv.pp.x2238);
        ftPp_SpecialS_8012114C(gobj);
    }
}

void ftPp_SpecialHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;

    fp->gr_vel /= da->x84;

    ftPp_SpecialHi_801218AC(gobj);

    fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp = GET_FIGHTER(gobj);
    fp->mv.pp.unk_80123954.x0 = 1;
    fp->fv.pp.x223C = 0;
    fp->fv.pp.x2240.z = 0.0f;
    fp->fv.pp.x2240.y = 0.0f;
    fp->fv.pp.x2240.x = 0.0f;
}
/// #ftPp_SpecialAirHi_Enter

/// #ftPp_SpecialHiStart_0_Anim

/// #ftPp_SpecialAirHiStart_0_Anim

/// #ftPp_SpecialHiStart_0_IASA

/// #ftPp_SpecialAirHiStart_0_IASA

/// #ftPp_SpecialHiStart_0_Phys

/// #ftPp_SpecialAirHiStart_0_Phys

void ftPp_SpecialHiStart_0_Coll(Fighter_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftPp_SpecialHi_801217EC(gobj);
    }
}
/// #ftPp_SpecialAirHiStart_0_Coll

/// #ftPp_SpecialHi_801217EC

void ftPp_SpecialHi_8012184C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x15B, 0x0C4C508AU, fp->cur_anim_frame, 0,
                              1, NULL);
}

void ftPp_SpecialHi_801218AC(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x15B, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftPp_SpecialHi_801218F8(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x160, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

/// #ftPp_SpecialHiThrow_0_Anim

/// #ftPp_SpecialAirHiThrow_0_Anim

void ftPp_SpecialHiThrow_0_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiThrow_0_IASA(Fighter_GObj* gobj) {}

/// #ftPp_SpecialHiThrow_0_Phys

/// #ftPp_SpecialAirHiThrow_0_Phys

void ftPp_SpecialHiThrow_0_Coll(Fighter_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftPp_SpecialHi_80121CE0(gobj);
    }
}
/// #ftPp_SpecialAirHiThrow_0_Coll

/// #ftPp_SpecialHi_80121CE0

/// #ftPp_SpecialHi_80121D40

void ftPp_SpecialHi_80121DA0(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x15C, 0, 0, 1.0f, 0.0f, NULL);
}
/// #ftPp_SpecialHi_80121DD8

/// #ftPp_SpecialHiStart_1_Anim

/// #ftPp_SpecialAirHiStart_1_Anim

void ftPp_SpecialHiStart_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiStart_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialHiStart_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// #ftPp_SpecialAirHiStart_1_Phys

/// #ftPp_SpecialHiStart_1_Coll

/// #ftPp_SpecialAirHiStart_1_Coll

/// #ftPp_SpecialHi_80121FD8

/// #ftPp_SpecialHi_80122038

void ftPp_SpecialHi_80122098(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x15E, 0, fp->cur_anim_frame, 1.0f, 0.0f,
                              NULL);
}
/// #ftPp_SpecialHi_801220D4

void ftPp_SpecialHiThrow_1_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}
/// #ftPp_SpecialAirHiThrow_1_Anim

void ftPp_SpecialHiThrow_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiThrow_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialHiThrow_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// #ftPp_SpecialAirHiThrow_1_Phys

/// #ftPp_SpecialHiThrow_1_Coll

/// #ftPp_SpecialAirHiThrow_1_Coll

/// #ftPp_SpecialHi_801222E8

/// #ftPp_SpecialHi_80122348

/// #ftPp_SpecialHi_80122380

/// #ftPp_SpecialHiThrow2_Anim

/// #ftPp_SpecialAirHiThrow2_Anim

void ftPp_SpecialHiThrow2_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiThrow2_IASA(Fighter_GObj* gobj) {}

/// #ftPp_SpecialHiThrow2_Phys

/// #ftPp_SpecialAirHiThrow2_Phys

/// #ftPp_SpecialHiThrow2_Coll

/// #ftPp_SpecialAirHiThrow2_Coll

/// #ftPp_SpecialHi_801227AC

/// #ftPp_SpecialHi_8012280C

/// #ftPp_SpecialHi_80122898

/// #ftPp_SpecialLw_Enter

/// #ftPp_SpecialAirLw_Enter

/// #ftPp_SpecialLw_Anim

/// #ftPp_SpecialAirLw_Anim

void ftPp_SpecialLw_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirLw_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialLw_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPp_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/// #fn_80122B54

/// #ftPp_SpecialLw_Coll

void ftPp_SpecialAirLw_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80122B54);
}

/// #fn_80122D2C

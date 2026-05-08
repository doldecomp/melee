#include "ft/chara/ftPopo/ftPp_SpecialS.h"

#include "ef/eflib.h"
#include "ft/chara/ftCommon/ftCo_Fall.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftNana/ftNn_Init.h"
#include "ftPopo/ftPp_Init.h"
#include "pl/player.h"

#include <math.h>
#include <trigf.h>

static inline void setRefGObjFlagAndClear(Fighter* fp)
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

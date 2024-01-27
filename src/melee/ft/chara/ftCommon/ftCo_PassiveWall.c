#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"
#include <dolphin/mtx/forward.h>

#include "ftCo_PassiveWall.h"

#include "ftCo_AirCatch.h"
#include "ftCo_AttackAir.h"
#include "ftCo_DownAttack.h"
#include "ftCo_EscapeAir.h"
#include "ftCo_FallSpecial.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_SpecialAir.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0CEE.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/types.h"
#include "ftKirby/ftKb_Init.h"
#include "lb/lb_00CE.h"

#include <common_structs.h>
#include <placeholder.h>

/* literal */ extern float const ftCo_804D8C60;
/* literal */ extern float const ftCo_804D8C64;
/* literal */ extern double const ftCo_804D8C68;
/* literal */ extern float const ftCo_804D8C70;
/* literal */ extern double const ftCo_804D8C78;

#pragma force_active on

bool ftCo_800C1D38(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if ((coll->env_flags & MPCOLL_FLAGS_B11 ||
         coll->env_flags & MPCOLL_FLAGS_B05) &&
        ftCo_800986B0(gobj))
    {
        ftCommon_MotionState msid =
            ftCo_800C1E0C(fp) ? ftCo_MS_PassiveWallJump : ftCo_MS_PassiveWall;
        if (coll->env_flags & MPCOLL_FLAGS_B11) {
            ftCo_800C1E64(gobj, msid, p_ftCommonData->x760, 0, ftCo_804D8C60);
        } else {
            ftCo_800C1E64(gobj, msid, p_ftCommonData->x760, 0, ftCo_804D8C64);
        }
        return true;
    }
    return false;
}

bool ftCo_800C1E0C(Fighter* fp)
{
    if (fp->x67E < p_ftCommonData->x250 ||
        fp->input.lstick.y >= p_ftCommonData->x70_someLStickYMax)
    {
        return true;
    }
    return false;
}

void ftCo_800C1E64(ftCo_GObj* gobj, int msid, int timer, int vel_y_exponent,
                   float facing_dir)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 ef_offset;
    fp->cmd_vars[0] = true;
    {
        CollData* coll = &fp->coll_data;
        fp->facing_dir = -facing_dir;
        ftCommon_8007E2FC(gobj);
        if (fp->coll_data.env_flags & MPCOLL_FLAGS_B11) {
            ef_offset.x = coll->xA4_ecbCurrCorrect.left.x;
            ef_offset.y = coll->xA4_ecbCurrCorrect.left.y;
            ef_offset.z = ftCo_804D8C70;
        } else {
            ef_offset.x = coll->xA4_ecbCurrCorrect.right.x;
            ef_offset.y = coll->xA4_ecbCurrCorrect.right.y;
            ef_offset.z = ftCo_804D8C70;
        }
    }
    ftKb_SpecialN_800F1F1C(gobj, &ef_offset);
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, ftCo_804D8C70,
                              timer != 0 ? ftCo_804D8C70 : ftCo_804D8C64,
                              ftCo_804D8C70, NULL);
    fp->x670_timer_lstick_tilt_x = 0xFE;
    fp->x671_timer_lstick_tilt_y = 0xFE;
    fp->mv.co.passivewall.timer = timer;
    fp->mv.co.passivewall.x4 = 0;
    fp->mv.co.passivewall.x8 = false;
    fp->mv.co.passivewall.vel_y_exponent = vel_y_exponent;
    {
        Vec3 ef_pos;
        float pos_x_offset = fp->cur_pos.x + ef_offset.x;
        u8 _[4] = { 0 };
        ef_pos.x = pos_x_offset;
        ef_pos.y = fp->cur_pos.y + ef_offset.y;
        ef_pos.z = fp->cur_pos.z;
        efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 2,
                      (1 << 0) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 10),
                      NULL, &ef_pos);
        fp->cur_pos.x =
            -(fp->x68C_transNPos.z * -fp->facing_dir - pos_x_offset);
    }
    ft_80081F2C(gobj);
    ft_800881D8(fp, fp->ft_data->x4C_collisionData->x24, 0x7F, 0x40);
    ftCommon_8007EBAC(fp, 12, 0);
    if (timer == 0) {
        ft_80088148(fp, 3, 0x7F, 0x40);
    }
    ftCo_800BFFD0(fp, 120, 0);
    ftColl_8007B760(gobj, p_ftCommonData->x764);
}

static inline void inlineA0(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_PassiveWallJump, Ft_MF_None,
                              fp->cur_anim_frame, ftCo_804D8C64, ftCo_804D8C70,
                              NULL);
    fp->x671_timer_lstick_tilt_y = 0xFE;
    fp->mv.co.passivewall.timer = 0;
}

void ftCo_PassiveWall_Anim(ftCo_GObj* gobj)
{
    u8 _[16] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.passivewall.timer != 0) {
        --fp->mv.co.passivewall.timer;
        if (fp->mv.co.passivewall.timer == 0) {
            ft_80088148(fp, 8, 0x7F, 0x40);
            if (fp->mv.co.passivewall.x8) {
                inlineA0(gobj);
            } else {
                ftAnim_SetAnimRate(gobj, ftCo_804D8C64);
            }
            if (fp->motion_id == ftCo_MS_PassiveWall) {
                fp->self_vel.x =
                    fp->facing_dir * fp->co_attrs.passivewall_vel_x;
            } else {
                fp->self_vel.x = fp->facing_dir *
                                 fp->co_attrs.wall_jump_horizontal_velocity;
                fp->self_vel.y = fp->co_attrs.wall_jump_vertical_velocity;
                if (fp->x1969_walljumpUsed != 0) {
                    fp->self_vel.y *=
                        powf(p_ftCommonData->passive_wall_vel_y_base,
                             fp->mv.co.passivewall.vel_y_exponent);
                }
            }
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftCo_PassiveWall_IASA(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->mv.co.passivewall.timer) {
        RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
        RETURN_IF(ftCo_80095328(gobj, NULL));
        RETURN_IF(ftCo_800D7100(gobj));
        RETURN_IF(ftCo_800C3B10(gobj));
        RETURN_IF(ftCo_80099A58(gobj));
        RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
        RETURN_IF(ftCo_800D705C(gobj));
        RETURN_IF(ftCo_800CB870(gobj));
        RETURN_IF(fp->cmd_vars[0] == 0);
        RETURN_IF(ftCo_800CEE70(gobj));
    } else {
        RETURN_IF(!ftCo_800C1E0C(fp));
        fp->mv.co.passivewall.x8 = true;
    }
}

void ftCo_PassiveWall_Phys(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->mv.co.passivewall.timer) {
        ftCo_DatAttrs* co = &fp->co_attrs;
        ftCommon_8007D528(fp);
        if (fp->x221A_b4) {
            ftCommon_8007D4E4(fp);
        } else {
            ftCommon_8007D494(fp, co->grav, co->terminal_vel);
        }
        ftCommon_8007D140(fp, ftCo_804D8C70, ftCo_804D8C70,
                          fp->co_attrs.aerial_friction);
    }
}

void ftCo_PassiveWall_Coll(ftCo_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->mv.co.passivewall.timer) {
        ft_80083318(gobj, ftCo_80096CC8, ft_80082B1C);
    } else {
        ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
    }
}

#include "ftCo_PassiveWall.h"

#include "ftCo_AirCatch.h"
#include "ftCo_AttackAir.h"
#include "ftCo_DownAttack.h"
#include "ftCo_EscapeAir.h"
#include "ftCo_FallSpecial.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_SpecialAir.h"

#include <platform.h>

#include "ef/efasync.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ftanim.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_ItemParasolOpen.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/types.h"
#include "ftKirby/ftKb_Init.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

bool ftCo_800C1D38(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if ((coll->env_flags & Collide_RightWallHug ||
         coll->env_flags & Collide_LeftWallHug) &&
        ftCo_800986B0(gobj))
    {
        ftCommon_MotionState msid =
            ftCo_800C1E0C(fp) ? ftCo_MS_PassiveWallJump : ftCo_MS_PassiveWall;
        if (coll->env_flags & Collide_RightWallHug) {
            ftCo_800C1E64(gobj, msid, p_ftCommonData->x760, 0, -1);
        } else {
            ftCo_800C1E64(gobj, msid, p_ftCommonData->x760, 0, +1);
        }
        return true;
    }
    return false;
}

bool ftCo_800C1E0C(Fighter* fp)
{
    if (fp->x67E < p_ftCommonData->x250 ||
        fp->input.lstick.y >= p_ftCommonData->tap_jump_threshold)
    {
        return true;
    }
    return false;
}

void ftCo_800C1E64(Fighter_GObj* gobj, int msid, int timer, int vel_y_exponent,
                   float facing_dir)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 ef_offset;
    fp->cmd_vars[0] = true;
    {
        CollData* coll = &fp->coll_data;
        fp->facing_dir = -facing_dir;
        ftCommon_8007E2FC(gobj);
        if (fp->coll_data.env_flags & Collide_RightWallHug) {
            ef_offset.x = coll->ecb.left.x;
            ef_offset.y = coll->ecb.left.y;
            ef_offset.z = 0.0F;
        } else {
            ef_offset.x = coll->ecb.right.x;
            ef_offset.y = coll->ecb.right.y;
            ef_offset.z = 0.0F;
        }
    }
    ftKb_SpecialN_800F1F1C(gobj, &ef_offset);
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0.0F,
                              timer != 0 ? 0.0F : 1.0F, 0.0F, NULL);
    fp->x670_timer_lstick_tilt_x = 0xFE;
    fp->x671_timer_lstick_tilt_y = 0xFE;
    fp->mv.co.passivewall.timer = timer;
    fp->mv.co.passivewall.x4 = 0;
    fp->mv.co.passivewall.x8 = false;
    fp->mv.co.passivewall.vel_y_exponent = vel_y_exponent;
    {
        Vec3 ef_pos;
        float pos_x_offset = fp->cur_pos.x + ef_offset.x;
        PAD_STACK(4);
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
    ft_800881D8(fp, fp->ft_data->x4C_sfx->x24, 0x7F, 0x40);
    ftCommon_8007EBAC(fp, 12, 0);
    if (timer == 0) {
        ft_PlaySFX(fp, 3, 0x7F, 0x40);
    }
    ftCo_800BFFD0(fp, 120, 0);
    ftColl_8007B760(gobj, p_ftCommonData->x764);
}

static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_PassiveWallJump, Ft_MF_None,
                              fp->cur_anim_frame, 1, 0, NULL);
    fp->x671_timer_lstick_tilt_y = 0xFE;
    fp->mv.co.passivewall.timer = 0;
}

void ftCo_PassiveWall_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);
    if (fp->mv.co.passivewall.timer != 0) {
        --fp->mv.co.passivewall.timer;
        if (fp->mv.co.passivewall.timer == 0) {
            ft_PlaySFX(fp, 8, 127, 64);
            if (fp->mv.co.passivewall.x8) {
                inlineA0(gobj);
            } else {
                ftAnim_SetAnimRate(gobj, 1);
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
        ftCo_Fall_Enter(gobj);
    }
}

void ftCo_PassiveWall_IASA(Fighter_GObj* gobj)
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

void ftCo_PassiveWall_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (!fp->mv.co.passivewall.timer) {
        ftCo_DatAttrs* co = &fp->co_attrs;
        ftCommon_CheckFallFast(fp);
        if (fp->fall_fast) {
            ftCommon_FallFast(fp);
        } else {
            ftCommon_Fall(fp, co->grav, co->terminal_vel);
        }
        ftCommon_8007D140(fp, 0.0F, 0.0F, fp->co_attrs.aerial_friction);
    }
}

void ftCo_PassiveWall_Coll(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->mv.co.passivewall.timer) {
        ft_80083318(gobj, ftCo_80096CC8, ft_80082B1C);
    } else {
        ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
    }
}

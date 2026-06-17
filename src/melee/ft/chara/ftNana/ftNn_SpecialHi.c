#include "ftNn_Init.h"

#include <platform.h>

#include "ft/chara/ftCommon/ftCo_Fall.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftPopo/types.h"
#include "lb/lb_00B0.h"
#include "pl/player.h"

#include <dolphin/mtx.h>
#include <MSL/math.h>

/* 1230D0 */ static bool ftNn_Init_801230D0(Fighter_GObj* nana_gobj);
/* 123218 */ static void fn_80123218(Fighter_GObj* nana_gobj);
/* 1233F8 */ static void ftNn_Init_801233F8(Fighter_GObj* gobj);
/* 123720 */ static void ftNn_Init_80123720(Fighter_GObj* gobj);
/* 12378C */ static void ftNn_Init_8012378C(Fighter_GObj* gobj);
/* 1237F8 */ static void ftNn_Init_801237F8(Fighter_GObj* gobj);

bool ftNn_Init_801230D0(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    u8 _[12];
    Vec popo_vec;
    Vec nana_vec;
    float x;
    float y;
    float z;
    if (popo_gobj != NULL) {
        Fighter* popo_fp = GET_FIGHTER(popo_gobj);
        if (popo_fp->motion_id < 347 || popo_fp->motion_id > 352) {
            return false;
        }
        if (nana_fp->facing_dir != popo_fp->facing_dir) {
            nana_fp->facing_dir = popo_fp->facing_dir;
            ftPartSetRotY(nana_fp, 0, M_PI_2 * nana_fp->facing_dir);
        }
        lb_8000B1CC(popo_fp->parts[FtPart_R4thNb].joint, NULL, &popo_vec);
        lb_8000B1CC(nana_fp->parts[FtPart_XRotN].joint, NULL, &nana_vec);
        x = nana_fp->cur_pos.x - nana_vec.x;
        y = nana_fp->cur_pos.y - nana_vec.y;
        z = nana_fp->cur_pos.z - nana_vec.z;
        nana_fp->cur_pos.x = popo_vec.x + x;
        nana_fp->cur_pos.y = popo_vec.y + y;
        nana_fp->cur_pos.z = popo_vec.z + z;
        if (popo_fp->x2219_b5) {
            ftAnim_SetAnimRate(nana_gobj, 0.0f);
        } else {
            if (nana_fp->frame_speed_mul != popo_fp->frame_speed_mul) {
                ftAnim_SetAnimRate(nana_gobj, popo_fp->frame_speed_mul);
            }
        }
    }
    return true;
}

void fn_80123218(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    if (popo_gobj != NULL) {
        Fighter* popo_fp = GET_FIGHTER(popo_gobj);
        Vec nana_vec;
        PAD_STACK(8);
        nana_vec.x = nana_vec.y = nana_vec.z = 0;
        lb_8000B1CC(GET_FIGHTER(nana_gobj)->parts[FtPart_L4thNb].joint, NULL,
                    &nana_vec);
        popo_fp->fv.pp.x2240 = nana_vec;
    }
}

static inline void ftNn_Init_801232A4_inline(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    nana_fp->cmd_vars[0] = 0;
    nana_fp->x2222_b2 = 1;
}

void ftNn_Init_801232A4(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    ftCo_DatAttrs* attrs = getFtAttrs(nana_fp);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    if (popo_gobj != NULL) {
        Fighter* popo_fp = GET_FIGHTER(popo_gobj);
        nana_fp->facing_dir = popo_fp->facing_dir;
    }
    if (nana_fp->ground_or_air == GA_Ground) {
        ftCommon_8007D60C(nana_fp);
    } else {
        nana_fp->x1968_jumpsUsed = attrs->max_jumps;
    }
    ftNn_Init_801233F8(nana_gobj);
    ftNn_Init_801232A4_inline(nana_gobj);
}

void ftPp_SpecialHi_0_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftNn_Init_801237F8(gobj);
    }
}

void ftPp_SpecialHi_3_Anim(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_0_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_3_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftNn_Init_801230D0(gobj)) {
        fp->cur_pos.x = -((8.0f * fp->facing_dir) - fp->cur_pos.x);
        ftCo_Fall_Enter(gobj);
    }
}

void ftPp_SpecialHi_3_Phys(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_0_Coll(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_3_Coll(Fighter_GObj* gobj)
{
    return;
}

void ftNn_Init_801233F8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x169, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->accessory4_cb = fn_80123218;
}

void ftPp_SpecialHi_1_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftPp_SpecialHi_4_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* attrs = fp->dat_attrs;
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_80096900(gobj, 0, 1, 0, attrs->x130, attrs->x134);
    }
}

void ftPp_SpecialHi_1_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_4_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPp_SpecialHi_4_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* attrs = fp->dat_attrs;
    ftCo_DatAttrs* co_attrs = getFtAttrs(fp);
    ftCommon_Fall(fp, attrs->x144, attrs->x148);
    if (ABS(fp->input.lstick.x) > attrs->x138) {
        ftCommon_8007D344(fp, 0.0f, co_attrs->air_drift_stick_mul * attrs->xB0,
                          co_attrs->air_drift_max * attrs->xB4);
    } else if (fp->self_vel.y < 0.0f) {
        ftCommon_8007CEF4(fp);
    }
}

void ftPp_SpecialHi_1_Coll(Fighter_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftNn_Init_80123720(gobj);
    }
}

void ftPp_SpecialHi_4_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* attrs = fp->dat_attrs;
    CollData* cd = &fp->coll_data;
    PAD_STACK(8);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftNn_Init_8012378C(gobj);
        return;
    }
    if (cd->env_flags & Collide_LeftWallMask) {
        if (fp->self_vel.x > 0.0f) {
            fp->self_vel.x *= -1 * attrs->x14C;
            fp->facing_dir *= -1;
            ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
            return;
        }
    }
    if (cd->env_flags & Collide_RightWallMask) {
        if (fp->self_vel.x < 0.0f) {
            fp->self_vel.x *= -1 * attrs->x14C;
            fp->facing_dir *= -1;
            ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
            return;
        }
    }
    if (cd->env_flags & Collide_CeilingMask) {
        fp->self_vel.y = 0.0f;
    }
}

void ftNn_Init_80123720(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 365, 0x0C4C508A, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
    fp->accessory4_cb = fn_80123218;
}

void ftNn_Init_8012378C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 362, 0x0C4C508A, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
    fp->accessory4_cb = fn_80123218;
}

void ftNn_Init_801237F8(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    ftIceClimberAttributes* attrs = nana_fp->dat_attrs;
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    PAD_STACK(0x10);
    if (popo_gobj != NULL) {
        Fighter* popo_fp = GET_FIGHTER(popo_gobj);
        ft_800849EC(popo_fp, nana_fp);
    }
    nana_fp->self_vel.x =
        nana_fp->facing_dir * (attrs->x13C * cosf(attrs->x140));
    nana_fp->self_vel.y = attrs->x13C * sinf(attrs->x140);
    nana_fp->cur_pos.x += 4.0f * nana_fp->facing_dir * nana_fp->x34_scale.y;
    nana_fp->cur_pos.y += 7.0f * nana_fp->x34_scale.y;
    Fighter_ChangeMotionState(nana_gobj, 365, 0, 0.0f, 1.0f, 0.0f, NULL);
    nana_fp->accessory4_cb = fn_80123218;
}

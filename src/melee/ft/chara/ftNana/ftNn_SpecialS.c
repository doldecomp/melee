#include "ftNn_Init.h"

#include <platform.h>

#include "ef/eflib.h"
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
#include "ftPopo/ftPp_SpecialS.h"
#include "ftPopo/types.h"
#include "pl/player.h"

#include <dolphin/mtx.h>
#include <MSL/math.h>

/* 123B3C */ static void ftNn_Init_80123B3C(Fighter_GObj* nana_gobj);
/* 123BF0 */ static void ftNn_Init_80123BF0(Fighter_GObj* gobj);
/* 3CDD60 */ ftCollisionBox ftNn_Unk2_803CDD60 = {
    12, 0, { -6, 6 }, { 6, 6 }
};

void ftNn_Init_801238E4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPartSetRotX(fp, 0, 0.0F);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    if (fp->x1A5C != NULL) {
        Fighter* fp2 = GET_FIGHTER(fp->x1A5C);
        Fighter_UnkSetFlag_8006CFBC(fp->x1A5C);
        fp2->x1A5C = NULL;
    }
    fp->x1A5C = NULL;
}

bool ftNn_Init_80123954(Fighter_GObj* nana_gobj, GroundOrAir pp_ga)
{
    Fighter* nana_fp;
    bool ret;
    if (nana_gobj != NULL) {
        Fighter* popo_fp;
        ftIceClimberAttributes* attrs;
        nana_fp = GET_FIGHTER(nana_gobj);
        popo_fp = GET_FIGHTER(Player_GetEntityAtIndex(nana_fp->player_id, 0));
        attrs = nana_fp->dat_attrs;
        switch (nana_fp->x2070.x2071_b0_3) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            nana_fp->x1A5C = NULL;
            ret = true;
            break;
        default: {
            float dd = attrs->xD0;
            float dx = nana_fp->cur_pos.x - popo_fp->cur_pos.x;
            float dy = nana_fp->cur_pos.y - popo_fp->cur_pos.y;
            float dxsq = dx * dx;
            float dysq = dy * dy;
            if (dxsq + dysq < (s32) (popo_fp->x34_scale.y * (dd * dd))) {
                ret = false;
                if (pp_ga == GA_Air) {
                    if (pp_ga != nana_fp->ground_or_air) {
                        ftCommon_8007D5D4(nana_fp);
                    }
                    ftNn_Init_80123BF0(nana_gobj);
                } else {
                    if (pp_ga != nana_fp->ground_or_air) {
                        ft_800849EC(popo_fp, nana_fp);
                        ftCommon_8007D7FC(nana_fp);
                    }
                    ftNn_Init_80123B3C(nana_gobj);
                }
                nana_fp->mv.pp.unk_80123954.x0 = 0;
                nana_fp->cur_pos = popo_fp->cur_pos;
                nana_fp->self_vel = popo_fp->self_vel;
                nana_fp->gr_vel = popo_fp->gr_vel;
                nana_fp->facing_dir = popo_fp->facing_dir;
                ftPartSetRotY(nana_fp, 0, M_PI_2 * nana_fp->facing_dir);
                nana_fp->x1A5C =
                    Player_GetEntityAtIndex(nana_fp->player_id, 0);
            } else {
                nana_fp->x1A5C = NULL;
                ret = true;
            }
            break;
        }
        }
    } else {
        ret = true;
    }
    return ret;
}

bool ftNn_Init_80123B10(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->motion_id) {
    case 359:
    case 360:
        return false;
    default:
        return true;
    }
}

static inline void ftNn_Init_80123B3C_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftNn_Init_80122FAC;
    fp->death2_cb = ftNn_Init_80122FAC;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftNn_Init_80123B3C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(0x10);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftNn_Init_80123B3C_inline(gobj);
    Fighter_ChangeMotionState(gobj, 359, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftNn_Init_80123B3C_inline(gobj);
    ftAnim_8006EBA4(gobj);
    fp->x74_anim_vel.y = 0.0f;
    fp->self_vel.y = 0.0f;
}

void ftNn_Init_80123BF0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(0x10);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftNn_Init_80123B3C_inline(gobj);
    Fighter_ChangeMotionState(gobj, 360, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftNn_Init_80123B3C_inline(gobj);
    ftAnim_8006EBA4(gobj);
    fp->x74_anim_vel.y = 0.0f;
    fp->self_vel.y = 0.0f;
}

static inline void ftPp_SpecialS_0_Anim_inline(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    nana_fp->take_dmg_cb = NULL;
    nana_fp->death2_cb = NULL;
    nana_fp->pre_hitlag_cb = NULL;
    nana_fp->post_hitlag_cb = NULL;
    nana_fp->x1A5C = NULL;
}

void ftPp_SpecialS_0_Anim(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Fighter* popo_fp = GET_FIGHTER(popo_gobj);
    if (!ftPp_SpecialS_8011F964(popo_gobj)) {
        nana_fp->cur_anim_frame = popo_fp->cur_anim_frame;
        return;
    }
    ftNn_Init_801238E4(nana_gobj); // inlined
    ftPp_SpecialS_0_Anim_inline(nana_gobj);
    ft_8008A2BC(nana_gobj);
}

void ftPp_SpecialS_1_Anim(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    ftIceClimberAttributes* attrs = nana_fp->dat_attrs;
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Fighter* popo_fp = GET_FIGHTER(popo_gobj);
    PAD_STACK(8);
    if (!ftPp_SpecialS_8011F964(popo_gobj)) {
        nana_fp->cur_anim_frame = popo_fp->cur_anim_frame;
        return;
    }
    ftNn_Init_801238E4(nana_gobj); // inlined
    ftPp_SpecialS_0_Anim_inline(nana_gobj);
    if (0.0 == attrs->x12C) {
        ftCo_Fall_Enter(nana_gobj);
    } else {
        ftCommon_8007D60C(nana_fp);
        ftCo_80096900(nana_gobj, 1, 0, 1, 1.0f, attrs->x12C);
    }
}

void ftPp_SpecialS_0_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialS_1_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialS_0_Phys(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter* popo_fp =
        GET_FIGHTER(Player_GetEntityAtIndex(nana_fp->player_id, 0));
    PAD_STACK(8);
    nana_fp->self_vel = popo_fp->self_vel;
    nana_fp->x74_anim_vel = popo_fp->x74_anim_vel;
    nana_fp->gr_vel = popo_fp->gr_vel;
    nana_fp->xE4_ground_accel_1 = popo_fp->xE4_ground_accel_1;
    nana_fp->facing_dir = popo_fp->facing_dir;
    ftPartSetRotY(nana_fp, 0, M_PI_2 * nana_fp->facing_dir);
}

void ftPp_SpecialS_1_Phys(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter* popo_fp =
        GET_FIGHTER(Player_GetEntityAtIndex(nana_fp->player_id, 0));
    PAD_STACK(8);
    nana_fp->self_vel = popo_fp->self_vel;
    nana_fp->x74_anim_vel = popo_fp->x74_anim_vel;
    nana_fp->gr_vel = popo_fp->gr_vel;
    nana_fp->xE4_ground_accel_1 = popo_fp->xE4_ground_accel_1;
    nana_fp->facing_dir = popo_fp->facing_dir;
    ftPartSetRotY(nana_fp, 0, M_PI_2 * nana_fp->facing_dir);
}

static inline void ftPp_SpecialS_0_Coll_inline(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Fighter* popo_fp = GET_FIGHTER(popo_gobj);

    ftPartSetRotX(nana_fp, 0, ftPartGetRotX(popo_fp, 0));
}

static inline void ftPp_SpecialS_0_Coll_inline2(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    nana_fp->take_dmg_cb = ftNn_Init_80122FAC;
    nana_fp->death2_cb = ftNn_Init_80122FAC;
    nana_fp->pre_hitlag_cb = efLib_PauseAll;
    nana_fp->post_hitlag_cb = efLib_ResumeAll;
}

static inline void ftPp_SpecialS_0_Coll_inline3(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftNn_Init_80123B3C_inline(gobj);
    {
        Fighter* fp2 = fp;
        ftCommon_8007D5D4(fp2);
    }
    Fighter_ChangeMotionState(gobj, 360, 0x0C4C528A, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
    ftNn_Init_80123B3C_inline(gobj);
}

void ftPp_SpecialS_0_Coll(Fighter_GObj* nana_gobj)
{
    u8 _[16];
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Fighter* popo_fp = GET_FIGHTER(popo_gobj);
    if (!ftPp_SpecialS_8011F964(popo_gobj) &&
        !ftPp_SpecialS_8011F6FC(popo_gobj))
    {
        nana_fp->cur_pos = popo_fp->cur_pos;
        ft_800849EC(popo_fp, nana_fp);
        if (nana_fp->ground_or_air != popo_fp->ground_or_air) {
            Fighter_ChangeMotionState(nana_gobj, 360, 0x0C4C528A,
                                      nana_fp->cur_anim_frame, 1.0f, 0.0f,
                                      NULL);
        }
        nana_fp->ground_or_air = popo_fp->ground_or_air;
    } else {
        nana_fp->mv.pp.unk_80123954.x0 += 1;
        if (nana_fp->mv.pp.unk_80123954.x0 > 5) {
            nana_fp->mv.pp.unk_80123954.x0 = 5;
        }
        nana_fp->cur_pos.x =
            -((1.5f * (nana_fp->mv.pp.unk_80123954.x0 * nana_fp->facing_dir)) -
              popo_fp->cur_pos.x);
        if (!ft_80082888(nana_gobj, &ftNn_Unk2_803CDD60)) {
            ftPp_SpecialS_0_Coll_inline3(nana_gobj);
        }
    }
    ftPp_SpecialS_0_Coll_inline(nana_gobj);
    ftPp_SpecialS_0_Coll_inline2(nana_gobj);
}

static inline void ftPp_SpecialS_1_Coll_inline3(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftNn_Init_80123B3C_inline(gobj);
    {
        Fighter* fp2 = fp;
        ftCommon_8007D7FC(fp2);
    }
    fp->self_vel.y = 0.0f;
    Fighter_ChangeMotionState(gobj, 359, 0x0C4C528A, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
    ftNn_Init_80123B3C_inline(gobj);
}

void ftPp_SpecialS_1_Coll(Fighter_GObj* nana_gobj)
{
    u8 _[16];
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Fighter* popo_fp = GET_FIGHTER(popo_gobj);
    if (!ftPp_SpecialS_8011F964(popo_gobj) &&
        !ftPp_SpecialS_8011F6FC(popo_gobj))
    {
        nana_fp->cur_pos = popo_fp->cur_pos;
        ft_800849EC(popo_fp, nana_fp);
        if (nana_fp->ground_or_air != popo_fp->ground_or_air) {
            Fighter_ChangeMotionState(nana_gobj, 359, 0x0C4C528A,
                                      nana_fp->cur_anim_frame, 1.0f, 0.0f,
                                      NULL);
        }
        nana_fp->ground_or_air = popo_fp->ground_or_air;
    } else {
        nana_fp->mv.pp.unk_80123954.x0 += 1;
        if (nana_fp->mv.pp.unk_80123954.x0 > 5) {
            nana_fp->mv.pp.unk_80123954.x0 = 5;
        }
        nana_fp->cur_pos.x =
            -((1.5f * (nana_fp->mv.pp.unk_80123954.x0 * nana_fp->facing_dir)) -
              popo_fp->cur_pos.x);
        if (ft_800824A0(nana_gobj, &ftNn_Unk2_803CDD60)) {
            ftPp_SpecialS_1_Coll_inline3(nana_gobj);
        }
    }
    ftPp_SpecialS_0_Coll_inline(nana_gobj);
    ftPp_SpecialS_0_Coll_inline2(nana_gobj);
}

#include <platform.h>
#include "ft/forward.h"
#include "ftPopo/forward.h"

#include "ef/eflib.h"
#include "ft/fighter.h"
#include "ft/ft_0892.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftNana/ftNn_Init.h"
#include "ftPopo/ftPp_Init.h"
#include "ftPopo/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/pad/pad.h>
#include <melee/ft/chara/ftPopo/ftPp_SpecialS.h>

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
    ftParts_8007592C(fp, 0, 0);
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

s32 ftNn_Init_80123B10(Fighter_GObj*); /* extern */

static inline void inlineC0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    fp->x1A5C = NULL;
}

static inline void inlineC1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_8007592C(fp, 0, 0);
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

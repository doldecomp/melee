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
#include <dolphin/pad.h>
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

/// #ftPp_SpecialS_8011F720

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

/// #ftPp_SpecialAirS1_Anim

/// #ftPp_SpecialAirS2_Anim

/// #ftPp_SpecialS1_IASA

/// #ftPp_SpecialS2_IASA

/// #ftPp_SpecialAirS1_IASA

/// #ftPp_SpecialAirS2_IASA

/// #ftPp_SpecialS1_Phys

/// #ftPp_SpecialS2_Phys

/// #ftPp_SpecialAirS1_Phys

/// #ftPp_SpecialAirS2_Phys

/// #ftPp_SpecialS1_Coll

/// #ftPp_SpecialS2_Coll

/// #ftPp_SpecialAirS1_Coll

/// #ftPp_SpecialAirS2_Coll

/// #ftPp_SpecialS_80120E68

/// #ftPp_SpecialS_80120FE0

/// #ftPp_SpecialS_801210C8

void ftPp_SpecialS_8012114C(void* arg0)
{
    void* temp_r3;

    temp_r3 = M2C_FIELD(arg0, void**, 0x2C);
    M2C_FIELD(temp_r3, s32*, 0x2238) = 0;
    M2C_FIELD(temp_r3, s32*, 0x21E8) = 0;
    M2C_FIELD(temp_r3, s32*, 0x21DC) = 0;
}

/// #ftPp_SpecialS_80121164

/// #ftPp_SpecialHi_Enter

/// #ftPp_SpecialAirHi_Enter

/// #ftPp_SpecialHiStart_0_Anim

/// #ftPp_SpecialAirHiStart_0_Anim

/// #ftPp_SpecialHiStart_0_IASA

/// #ftPp_SpecialAirHiStart_0_IASA

/// #ftPp_SpecialHiStart_0_Phys

/// #ftPp_SpecialAirHiStart_0_Phys

/// #ftPp_SpecialHiStart_0_Coll

/// #ftPp_SpecialAirHiStart_0_Coll

/// #ftPp_SpecialHi_801217EC

/// #ftPp_SpecialHi_8012184C

/// #ftPp_SpecialHi_801218AC

/// #ftPp_SpecialHi_801218F8

/// #ftPp_SpecialHiThrow_0_Anim

/// #ftPp_SpecialAirHiThrow_0_Anim

void ftPp_SpecialHiThrow_0_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiThrow_0_IASA(Fighter_GObj* gobj) {}

/// #ftPp_SpecialHiThrow_0_Phys

/// #ftPp_SpecialAirHiThrow_0_Phys

/// #ftPp_SpecialHiThrow_0_Coll

/// #ftPp_SpecialAirHiThrow_0_Coll

/// #ftPp_SpecialHi_80121CE0

/// #ftPp_SpecialHi_80121D40

/// #ftPp_SpecialHi_80121DA0

/// #ftPp_SpecialHi_80121DD8

/// #ftPp_SpecialHiStart_1_Anim

/// #ftPp_SpecialAirHiStart_1_Anim

void ftPp_SpecialHiStart_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiStart_1_IASA(Fighter_GObj* gobj) {}

/// #ftPp_SpecialHiStart_1_Phys

/// #ftPp_SpecialAirHiStart_1_Phys

/// #ftPp_SpecialHiStart_1_Coll

/// #ftPp_SpecialAirHiStart_1_Coll

/// #ftPp_SpecialHi_80121FD8

/// #ftPp_SpecialHi_80122038

/// #ftPp_SpecialHi_80122098

/// #ftPp_SpecialHi_801220D4

/// #ftPp_SpecialHiThrow_1_Anim

/// #ftPp_SpecialAirHiThrow_1_Anim

void ftPp_SpecialHiThrow_1_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirHiThrow_1_IASA(Fighter_GObj* gobj) {}

/// #ftPp_SpecialHiThrow_1_Phys

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

/// #ftPp_SpecialLw_Phys

/// #ftPp_SpecialAirLw_Phys

/// #fn_80122B54

/// #ftPp_SpecialLw_Coll

/// #ftPp_SpecialAirLw_Coll

/// #fn_80122D2C

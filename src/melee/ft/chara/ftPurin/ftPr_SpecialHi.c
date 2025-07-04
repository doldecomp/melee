#include <placeholder.h>

#include "forward.h"

#include "ftPr_SpecialHi.h"

#include "ftPr_Init.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftPurin/types.h"
#include "gm/gm_1601.h"
#include "gr/grstadium.h"
#include "lb/types.h"

#include <common_structs.h>
#include <baselib/archive.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/objalloc.h>

static inline void ftPurin_SpecialHi_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->cmd_vars[0] = 0;

    fp->accessory4_cb = &ftPr_Init_8013C94C;

    if (gm_8016B1D8() && grStadium_801D4FF8(fp->player_id)) {
        fp->mv.pr.specialhi.x0 = true;
    } else {
        fp->mv.pr.specialhi.x0 = false;
    }
}

inline void ftPurin_SpecialHi_SetActionFromFacingDirection(HSD_GObj* gobj,
                                                           u32 left_id,
                                                           u32 right_id)
{
    Fighter* fighter = GET_FIGHTER(gobj);

    if (-1 == fighter->facing_dir) {
        Fighter_ChangeMotionState(gobj, left_id, 0, 0, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, right_id, 0, 0, 1, 0, NULL);
    }
}

inline void startHi(HSD_GObj* gobj, int left_id, int right_id)
{
    Fighter* fighter;

    ftPurin_SpecialHi_SetActionFromFacingDirection(gobj, left_id, right_id);

    ftAnim_8006EBA4(gobj);

    fighter = (Fighter*) HSD_GObjGetUserData(gobj);

    if (-1 == fighter->facing_dir) {
        Fighter_ChangeMotionState(gobj, left_id, 0, 0, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, right_id, 0, 0, 1, 0, NULL);
    }
}

void ftPr_SpecialHi_Enter(HSD_GObj* gobj)
{
    ftPurin_SpecialHi_SetActionFromFacingDirection(gobj, 365, 367);

    ftAnim_8006EBA4(gobj);
    ftPurin_SpecialHi_SetVars(gobj);
}

void ftPr_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    ftPurin_SpecialHi_SetActionFromFacingDirection(gobj, 366, 368);

    ftAnim_8006EBA4(gobj);
    ftPurin_SpecialHi_SetVars(gobj);
}

void ftPr_SpecialHi_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);

    if (fighter->mv.pr.specialhi.x0 != 0 && !fighter->x914[0].x43_b2 &&
        fighter->x914[0].state != HitCapsule_Disabled)
    {
        fighter->x914[0].x43_b2 = 1;
        fighter->x914[0].element = HitElement_Sleep;
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_8008A2BC(fighter_gobj);
    }
}

void ftPr_SpecialAirHi_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = fighter_gobj->user_data;
    if (fighter->mv.pr.specialhi.x0 != 0 && !fighter->x914[0].x43_b2 &&
        fighter->x914[0].state != HitCapsule_Disabled)
    {
        fighter->x914[0].x43_b2 = 1;
        fighter->x914[0].element = HitElement_Sleep;
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftCo_800CC730(fighter_gobj);
    }
}

void ftPr_SpecialHi_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirHi_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialHi_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPr_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPr_SpecialHi_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftPr_SpecialHi_8013CD34(gobj);
    }
}

void ftPr_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    if (ft_CheckGroundAndLedge(gobj, 0)) {
        ftPr_SpecialHi_8013CDD8(gobj);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

void ftPr_SpecialHi_8013CD34(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);

    if (-1 == fp->facing_dir) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirHiL, 0x0C4C508A,
                                  fp->cur_anim_frame, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirHiR, 0x0C4C508A,
                                  fp->cur_anim_frame, 1, 0, NULL);
    }

    fp->accessory4_cb = ftPr_Init_8013C94C;
}

void ftPr_SpecialHi_8013CDD8(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = fighter_gobj->user_data;
    ftCommon_8007D7FC(fighter);
    if (-1 == fighter->facing_dir) {
        Fighter_ChangeMotionState(fighter_gobj, ftPr_MS_SpecialHiL,
                                  0x0C4C508AU, fighter->cur_anim_frame, 1, 0,
                                  NULL);
    } else {
        Fighter_ChangeMotionState(fighter_gobj, ftPr_MS_SpecialHiR,
                                  0x0C4C508AU, fighter->cur_anim_frame, 1, 0,
                                  NULL);
    }
    fighter->accessory4_cb = ftPr_Init_8013C94C;
}

void ftPr_SpecialHi_8013CE7C(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);
    fighter->accessory4_cb = NULL;
}

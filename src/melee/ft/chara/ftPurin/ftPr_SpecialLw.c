#include <placeholder.h>

#include "forward.h"

#include "ftPr_SpecialLw.h"

#include "ftPr_SpecialHi.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include <common_structs.h>
#include <baselib/archive.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/objalloc.h>

void ftPr_SpecialLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    u8 _[8];

    if (-1 == fp->facing_dir) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialLwL, 0U, 0, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialLwR, 0U, 0, 1, 0, NULL);
    }
    ftAnim_8006EBA4(gobj);
    fp = gobj->user_data;
    fp->cmd_vars[0] = 0;
    fp->accessory4_cb = &ftPr_SpecialHi_8013CE7C;
}

void ftPr_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    u8 _[8];

    if (-1 == fp->facing_dir) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirLwL, 0U, 0, 1, 0,
                                  NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirLwR, 0U, 0, 1, 0,
                                  NULL);
    }
    ftAnim_8006EBA4(gobj);
    fp = gobj->user_data;
    fp->cmd_vars[0] = 0;
    fp->accessory4_cb = &ftPr_SpecialHi_8013CE7C;
}

void ftPr_SpecialLw_Anim(Fighter_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_8008A2BC(fighter_gobj);
    }
}

void ftPr_SpecialAirLw_Anim(Fighter_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftCo_Fall_Enter(fighter_gobj);
    }
}

void ftPr_SpecialLw_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirLw_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPr_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPr_SpecialLw_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftPr_SpecialLw_8013D104(gobj);
    }
}

void ftPr_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftPr_SpecialLw_8013D19C(gobj);
    }
}

void ftPr_SpecialLw_8013D104(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    if (-1 == fp->facing_dir) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirLwL, 0x0C4C508EU,
                                  fp->cur_anim_frame, 1, 0, NULL);
        return;
    }
    Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirLwR, 0x0C4C508EU,
                              fp->cur_anim_frame, 1, 0, NULL);
}

void ftPr_SpecialLw_8013D19C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    if (-1 == fp->facing_dir) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialLwL, 0x0C4C508EU,
                                  fp->cur_anim_frame, 1, 0, NULL);
        return;
    }
    Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialLwR, 0x0C4C508EU,
                              fp->cur_anim_frame, 1, 0, NULL);
}

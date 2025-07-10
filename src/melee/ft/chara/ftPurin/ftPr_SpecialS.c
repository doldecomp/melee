#include <placeholder.h>

#include "forward.h"
#include "ft/forward.h"

#include "ftPr_SpecialS.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftPurin/types.h"

#include <common_structs.h>
#include <math.h>
#include <baselib/archive.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/objalloc.h>

/// @todo Float order hack.
static float forceFloatOrder0(void)
{
    return 0;
}

/// @todo Float order hack.
static float forceFloatOrder1(void)
{
    return deg_to_rad;
}

/// @todo Float order hack.
static float forceFloatOrder2(void)
{
    return 1;
}

void ftPr_SpecialS_Enter(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);
    Fighter_ChangeMotionState(fighter_gobj, 0x16B, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(fighter_gobj);
    fighter->cmd_vars[0] = fighter->cmd_vars[1] = fighter->cmd_vars[2] =
        fighter->cmd_vars[3] = 0;
}

void ftPr_SpecialAirS_Enter(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);

    Fighter_ChangeMotionState(fighter_gobj, 0x16C, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(fighter_gobj);
    fighter->cmd_vars[0] = fighter->cmd_vars[1] = fighter->cmd_vars[2] =
        fighter->cmd_vars[3] = 0;
}

void ftPr_SpecialS_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftPr_SpecialAirS_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftPr_SpecialS_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirS_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialS_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

static inline float calcAngleRadians(HSD_GObj* gobj, float lstick_y)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;

    float left_stick_y = stickGetDir(lstick_y, 0);
    if (left_stick_y > da->xE0) {
        left_stick_y = da->xE0;
    }
    left_stick_y -= da->xDC;
    if (left_stick_y < 0) {
        left_stick_y = 0;
    }
    if (lstick_y < 0) {
        left_stick_y = -left_stick_y;
    }

    {
        float degrees = (left_stick_y * da->xE4) / (da->xE0 - da->xDC);
        return deg_to_rad * degrees;
    }
}

/// This is called once each frame during Puff's aerial side special
void ftPr_SpecialAirS_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 6);

    if (fp->cmd_vars[0]) {
        fp->cmd_vars[0] = 0;
        ++fp->fv.pr.x222C;
        {
            float angle = calcAngleRadians(gobj, fp->input.lstick.y);
            fp->self_vel.y = da->xF0 * sinf(angle);
            fp->self_vel.x = da->xF0 * (fp->facing_dir * cosf(angle));
        }
    }

    switch (fp->cmd_vars[1]) {
    case 0:
        ft_80084EEC(gobj);
        return;
    case 1:
        fp->self_vel.y = fp->self_vel.y * da->xF4;
        fp->self_vel.x = fp->self_vel.x * da->xF4;
        return;
    case 2:
        ft_80084DB0(gobj);
        return;
    }
}

void ftPr_SpecialS_Coll(Fighter_GObj* gobj)
{
    if (ft_800827A0(gobj) == GA_Ground) {
        ftPr_SpecialS_8013D590(gobj);
    }
}

void ftPr_SpecialAirS_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftPr_SpecialS_8013D5F0(gobj);
    }
}

void ftPr_SpecialS_8013D590(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirS, 0x0C4C508AU,
                              fp->cur_anim_frame, 1, 0, NULL);
}

void ftPr_SpecialS_8013D5F0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialS, 0x0C4C508AU,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftCommon_8007D468(fp);
}

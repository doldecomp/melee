#include "ftCo_DamageSong.h"
#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_Throw.h"

#include "ftCo_0C35.h"
#include "ftCo_Lift.h"

#include <placeholder.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "pl/player.h"

/* 0C3390 */ static void ftCo_800C3390(Fighter_GObj* gobj);
/* 0C3480 */ static void ftCo_800C3480(Fighter_GObj* gobj);

static float inlineA0(Fighter* fp, bool arg1)
{
    float result =
        (fp->dmg.x1830_percent * p_ftCommonData->x638) +
        ((p_ftCommonData->x628 *
          (p_ftCommonData->x62C - Player_GetHandicap(fp->player_id))) +
         p_ftCommonData->x624 +
         p_ftCommonData->x630 *
             (p_ftCommonData->x634 - ((Player_80033BB8(fp->player_id)) + 1)));
    if (arg1) {
        result *= p_ftCommonData->x644;
    }
    return result;
}

void ftCo_800C318C(Fighter_GObj* gobj, bool arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_DamageSong, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_InitGrab(fp, 0, inlineA0(fp, arg1));
}

static inline bool inlineB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->grab_timer -= p_ftCommonData->x63C;
    ftCommon_8007DC08(fp, p_ftCommonData->x640);
    if (fp->grab_timer <= 0) {
        ftCo_800C3480(gobj);
        return true;
    } else {
        return false;
    }
}

void ftCo_DamageSong_Anim(Fighter_GObj* gobj)
{
    if (!inlineB0(gobj) && !ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800C3390(gobj);
    }
}

void ftCo_DamageSong_IASA(Fighter_GObj* gobj) {}

void ftCo_DamageSong_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DamageSong_Coll(Fighter_GObj* gobj)
{
    ft_80084280(gobj);
}

void ftCo_800C3390(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftCo_MS_DamageSongWait,
                              Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim, 0, 1, 0,
                              NULL);
}

void ftCo_DamageSongWait_Anim(Fighter_GObj* gobj)
{
    inlineB0(gobj);
}

void ftCo_DamageSongWait_IASA(Fighter_GObj* gobj) {}

void ftCo_DamageSongWait_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DamageSongWait_Coll(Fighter_GObj* gobj)
{
    ft_80084280(gobj);
}

void ftCo_800C3480(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftCo_MS_DamageSongRv, Ft_MF_None, 0, 1, 0,
                              NULL);
}

void ftCo_DamageSongRv_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_DamageSongRv_IASA(Fighter_GObj* gobj) {}

void ftCo_DamageSongRv_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DamageSongRv_Coll(Fighter_GObj* gobj)
{
    ft_80084280(gobj);
}

bool ftCo_800C3538(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2222_b2) {
        return false;
    }
    switch (fp->x2070.x2071_b0_3) {
    case 9:
    case 10:
    case 11:
        return false;
    default:
        ftCo_800C3598(gobj);
        return true;
    }
}

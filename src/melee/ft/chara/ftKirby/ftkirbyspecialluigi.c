#include "ftkirby.h"

#include "baselib/forward.h"

#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_084E.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/inlines.h"

#include "ftKirby/forward.h"
#include "ftLuigi/forward.h"

#include "it/items/itluigifireball.h"
#include "lb/lb_00B0.h"

#include <stddef.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/random.h>

static void fn_800F98F4(Fighter_GObj*);

void ftKb_SpecialNLg_800F9614(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_LgSpecialN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_800F98F4;
}

void ftKb_SpecialNLg_800F9684(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_LgSpecialAirN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_800F98F4;
}

void ftKb_LgSpecialN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_LgSpecialAirN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_LgSpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftKb_LgSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Fall_IASA_Inner(gobj);
    }
}

void ftKb_LgSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LgSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_LgSpecialN_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter* fp = gobj->user_data;
        ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_LgSpecialAirN,
                                        ftLg_MF_SpecialN_Coll);
        fp->accessory4_cb = fn_800F98F4;
    }
}

void ftKb_LgSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        Fighter* fp = gobj->user_data;
        ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_LgSpecialN,
                                        ftLg_MF_SpecialN_Coll);
        fp->accessory4_cb = fn_800F98F4;
    }
}

void fn_800F98F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCheckThrowB0(fp)) {
        Vec3 pos;
        Fighter_Part bone = ftParts_GetBoneIndex(fp, FtPart_LHandN);
        lb_8000B1CC(fp->parts[bone].joint, NULL, &pos);
        it_802C01AC(gobj, &pos, It_Kind_Kirby_LuigiFire, fp->facing_dir);
        efSync_Spawn(0x4B1, gobj,
                     fp->parts[ftParts_GetBoneIndex(fp, FtPart_LHandN)].joint,
                     &fp->facing_dir);
    }
}

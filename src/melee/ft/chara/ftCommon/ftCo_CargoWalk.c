#include <platform.h>

#include "ftCo_CargoWalk.h"

#include "ftCo_09C4.h"
#include "ftCo_CargoJump.h"
#include "ftCo_CargoThrow.h"
#include "ftCo_CargoWait.h"
#include "ftCo_Shouldered.h"

#include "ft/ftwalkcommon.h"
#include "ft/types.h"
#include "ftDonkey/types.h"

#include <baselib/gobj.h>

/* 09B6C8 */ static void ftCo_8009B6C8(Fighter_GObj* gobj, float anim_start);

bool ftCo_8009B67C(Fighter_GObj* gobj)
{
    if (ftWalkCommon_800DFC70(gobj)) {
        ftCo_8009B6C8(gobj, 0);
        return true;
    }
    return false;
}

void ftCo_8009B6C8(Fighter_GObj* gobj, float anim_start)
{
    u8 _[20] = { 0 };
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* fp_x2CC = fp->x2CC;
    ftWalkCommon_800DFCA4(gobj, fp_x2CC->x4_motion_state + 1, Ft_MF_None,
                          anim_start, fp_x2CC->x8, fp_x2CC->xC, fp_x2CC->x10,
                          fp_x2CC->x14, fp_x2CC->x18, fp_x2CC->x1C, 1);
    ftCo_8009C5A4(fp->victim_gobj,
                  ftWalkCommon_GetWalkType(gobj) + ftCo_MS_ShoulderedWait);
}

void ftCo_CargoWalk_Anim(Fighter_GObj* gobj)
{
    ftWalkCommon_800DFDDC(gobj);
}

void ftCo_CargoWalk_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_8009BF3C(gobj));
    RETURN_IF(ftCo_8009BB1C(gobj));
    RETURN_IF(ftCo_8009C4F8(gobj));
    RETURN_IF(ftCo_8009B4D0(gobj));
    ftWalkCommon_800DFEC8(gobj, ftCo_8009B6C8);
}

void ftCo_CargoWalk_Phys(Fighter_GObj* gobj)
{
    ftWalkCommon_800E0060(gobj);
}

void ftCo_CargoWalk_Coll(Fighter_GObj* gobj)
{
    ftCo_CargoWait_Coll(gobj);
}

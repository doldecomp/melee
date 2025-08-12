#include <platform.h>

#include "ftCo_HammerTurn.h"

#include "ftCo_HammerJump.h"
#include "ftCo_HammerWait.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Turn.h"
#include "ftCommon/types.h"

#include <math.h>
#include <baselib/jobj.h>

/* 0C57B4 */ static void ftCo_800C57B4(Fighter_GObj* gobj);

bool ftCo_800C576C(Fighter_GObj* gobj)
{
    if (ftCo_800C97A8(gobj)) {
        ftCo_800C57B4(gobj);
        return true;
    }
    return false;
}

void ftCo_800C57B4(Fighter_GObj* gobj)
{
    /// @todo Cannot move below @c fp, which suggests an inline
    u32 flags;
    Fighter* fp = GET_FIGHTER(gobj);
    flags = ftCo_800C54C4(fp);
    ftCo_Turn_Enter(gobj, ftCo_MS_HammerTurn, flags, 0, p_ftCommonData->x6B0,
                  ftCo_800C548C(fp));
    ftCo_800C4E94(fp);
}

void ftCo_HammerTurn_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800C4F64(gobj);
    if (fp->mv.co.walk.fast_anim_frame) {
        Fighter_Part part = ftParts_GetBoneIndex(fp, FtPart_TransN);
        HSD_JObj* jobj = fp->parts[part].x4_jobj2;
        --fp->mv.co.walk.fast_anim_frame;
        if (!fp->x2222_b6) {
            float rot_y =
                M_PI *
                ((p_ftCommonData->x6B0 - fp->mv.co.walk.fast_anim_frame) /
                 p_ftCommonData->x6B0);
            ftParts_80075AF0(fp, part, rot_y);
            HSD_JObjSetRotationY(jobj, rot_y);
        }
        if (fp->mv.co.walk.fast_anim_frame <= 0) {
            fp->facing_dir = -fp->facing_dir;
            ftCo_800C4ED8(gobj);
        }
    }
}

void ftCo_HammerTurn_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_800C5A50(gobj));
}

void ftCo_HammerTurn_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_HammerTurn_Coll(Fighter_GObj* gobj)
{
    ftCo_HammerWait_Coll(gobj);
}

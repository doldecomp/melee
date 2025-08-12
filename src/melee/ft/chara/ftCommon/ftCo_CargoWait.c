#include "ftCo_CargoWait.h"

#include "ftCo_09C4.h"
#include "ftCo_CargoFall.h"
#include "ftCo_CargoJump.h"
#include "ftCo_CargoThrow.h"
#include "ftCo_CargoTurn.h"
#include "ftCo_CargoWalk.h"
#include "ftCo_Shouldered.h"

#include <platform.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ftDonkey/types.h"

bool ftCo_8009B4D0(Fighter_GObj* gobj)
{
    if (ft_8008A1FC(gobj)) {
        ftCo_8009B518(gobj);
        return true;
    }
    return false;
}

static inline void inlineA0(Fighter_GObj* gobj,
                            void (*cb)(Fighter_GObj* gobj, int))
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, fp->x2CC->x4_motion_state, Ft_MF_None, 0,
                              1, 0, NULL);
    cb(fp->victim_gobj, 266);
}

void ftCo_8009B518(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    inlineA0(gobj, ftCo_8009C5A4);
}

void ftCo_8009B56C(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    inlineA0(gobj, ftCo_8009C640);
}

void ftCo_CargoWait_Anim(Fighter_GObj* gobj) {}

void ftCo_CargoWait_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_8009BF3C(gobj));
    RETURN_IF(ftCo_8009BB1C(gobj));
    RETURN_IF(ftCo_8009C4F8(gobj));
    RETURN_IF(ftCo_8009B818(gobj));
    RETURN_IF(ftCo_8009B67C(gobj));
}

void ftCo_CargoWait_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_CargoWait_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_8009BC58);
}

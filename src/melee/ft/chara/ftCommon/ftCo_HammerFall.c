#include "ftCo_HammerFall.h"

#include "ftCo_HammerLanding.h"
#include "ftCo_HammerWait.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "it/item.h"
#include "pl/plbonuslib.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

bool ftCo_800C5CD4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCo_800C5240(gobj) && fp->input.x668 & HSD_PAD_AB) {
        ftCo_800C5D34(gobj);
        return true;
    }
    return false;
}

void ftCo_800C5D34(Fighter_GObj* gobj)
{
    /// @todo Cannot move below @c fp, which suggests an inline
    u32 flags;
    Fighter* fp = GET_FIGHTER(gobj);
    flags = ftCo_800C54C4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_HammerFall, flags,
                              ftCo_800C548C(fp), 1, 0, NULL);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
    ftCo_800C4E94(fp);
}

void ftCo_HammerFall_Anim(Fighter_GObj* gobj)
{
    ftCo_800C4F64(gobj);
}

static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    pos.x = pos.y = pos.z = 0;
    Item_8026ABD8(fp->item_gobj, &pos, 1);
    ftCo_Fall_Enter(gobj);
    ftCo_800C544C(fp);
    pl_8003FDF4(fp->player_id, fp->x221F_b4);
}

bool ftCo_800C5DDC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2338.y != 0 && fp->input.x668 & HSD_PAD_A &&
        fp->input.held_inputs & HSD_PAD_LR && fp->x683 >= p_ftCommonData->x1C)
    {
        inlineA0(gobj);
        return true;
    }
    return false;
}

void ftCo_HammerFall_IASA(Fighter_GObj* gobj)
{
    ftCo_800C5DDC(gobj);
}

void ftCo_HammerFall_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_HammerFall_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftCo_800C5F88);
}

#include "ftCh_Squeeze.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_TagCancel.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftCh_Init_8015A3F4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->x1A5C = ftBossLib_8015C3E8(FTKIND_MASTERH);
    Fighter_ChangeMotionState(gobj, 0x17A, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Squeeze_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[1] != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->cmd_vars[1] = 0;
    }

    if ((ftBossLib_8015C2E0() != 0) || (ftBossLib_8015C358() != 0) ||
        (!ftAnim_IsFramesRemaining(gobj)))
    {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Squeeze_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Squeeze_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Squeeze_Coll(HSD_GObj* gobj) {}

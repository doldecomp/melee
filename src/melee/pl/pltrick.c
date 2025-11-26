#include "pltrick.h"

#include "ft/inlines.h"
#include "pl/player.h"

#include <sysdolphin/baselib/debug.h>

int pl_80037B2C(struct plActionStats* arg0, int h_player, int idx)
{
    HSD_ASSERT(0x89, 0 <= h_player && h_player < 8);
    if (idx < 0x64) {
        return arg0->x504[idx] & (1 << (u8) h_player);
    }
}

/// #pl_80037BC0

/// #pl_80037C60

/// #pl_80037DF4

void pl_80037ECC(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    plActionStats* acp = Player_GetActionStats(ft->player_id);
    acp->attacks.x1A8++;
}

/// #fn_80037F00

/// #pl_80038144

/// #pl_800384DC

/// #pl_80038628

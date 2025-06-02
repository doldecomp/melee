#include <melee/pl/pltrick.h>

#include <sysdolphin/baselib/debug.h>


int pl_80037B2C(struct pl_80037B2C_unk* arg0, int h_player, int idx)
{
    HSD_ASSERT(0x89, 0 <= h_player && h_player < 8);
    if (idx < 0x64) {
        return arg0->x504[idx] & (1 << (u8) h_player);
    }
}

/// #pl_80037BC0

/// #pl_80037C60

/// #pl_80037DF4

/// #pl_80037ECC

/// #fn_80037F00

/// #pl_80038144

/// #pl_800384DC

/// #pl_80038628

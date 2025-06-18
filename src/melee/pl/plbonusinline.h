#ifndef MELEE_PL_PLBONUSLIB_INLINE_H
#define MELEE_PL_PLBONUSLIB_INLINE_H

#include <gm/gm_1601.h>
#include <pl/player.h>
#include <pl/types.h>

static inline void pl_80039450_inline(int slot)
{
    pl_StaleMoveTableExt_t* var_r26;
    int i;

    var_r26 = Player_GetStaleMoveTableIndexPtr2(slot);

    for (i = 0; i < 215; ++i) {
        if (gm_8016F1B8(i) == 0) {
            var_r26->x0_staleMoveTable.x904[0] = 0;
        }
        var_r26 = (pl_StaleMoveTableExt_t*) ((char*) var_r26 + 4);
    }
}

#endif

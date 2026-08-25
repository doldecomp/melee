#ifndef MELEE_FT_CHARA_FTFOX_INLINES_H
#define MELEE_FT_CHARA_FTFOX_INLINES_H

#include "ft/inlines.h"
#include "ft/types.h"

static inline void ftFox_SpecialN_CheckLoopInput(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] != 0 && (fp->input.x668 & HSD_PAD_B)) {
        fp->mv.fx.SpecialN.isBlasterLoop = true;
    }
}

#endif

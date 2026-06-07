#ifndef MELEE_FT_CHARA_FTKIRBY_INLINES_H
#define MELEE_FT_CHARA_FTKIRBY_INLINES_H

#include <placeholder.h>

#include "ft/inlines.h"
#include "ftKirby/ftKb_Init.h"

static inline void ftKb_SpecialN_set_cbs(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

#endif

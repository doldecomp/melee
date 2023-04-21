#ifndef MELEE_FT_CHARA_FTMARIO_INLINES_H
#define MELEE_FT_CHARA_FTMARIO_INLINES_H

#include "ft/types.h"
#include "ftMario/types.h"

static inline ftMario_DatAttrs* GetMarioAttr(Fighter* fp)
{
    ftMario_DatAttrs* mario_attr = fp->x2D4_specialAttributes;
    return mario_attr;
}

#endif

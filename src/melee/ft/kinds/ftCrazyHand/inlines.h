#ifndef MELEE_FT_CHARA_FTCRAZYHAND_INLINES_H
#define MELEE_FT_CHARA_FTCRAZYHAND_INLINES_H

#include <melee/ft/ft_084E.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/kinds/ftCrazyHand/types.h>
#include <melee/ft/types.h>

static inline void ftCh_UpdateBossMotion(HSD_GObj* gobj, Fighter* fp,
                                         ftCrazyHand_DatAttrs* da)
{
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.ch.unk0.xC, &fp->mv.ch.unk0.x18, da->x14,
                       da->x10);
}

#endif

#ifndef MELEE_FT_CHARA_FTMASTERHAND_INLINES_H
#define MELEE_FT_CHARA_FTMASTERHAND_INLINES_H

#include <melee/ft/ft_084E.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/kinds/ftMasterHand/types.h>
#include <melee/ft/types.h>

static inline void ftMh_UpdateBossMotion(HSD_GObj* gobj, Fighter* fp,
                                         ftMasterHand_SpecialAttrs* da)
{
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x2C,
                       da->x28);
}

#endif

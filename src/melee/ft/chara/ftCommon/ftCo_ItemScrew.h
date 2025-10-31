#ifndef MELEE_FTCO_ITEMSCREW_H
#define MELEE_FTCO_ITEMSCREW_H

#include "ft/forward.h"

/* 0D2D50 */ void ftCo_ItemScrew_Enter(Fighter_GObj*);
/* 0D2DD0 */ void ftCo_ItemScrew_Anim(Fighter_GObj* gobj);
/* 0D2E0C */ void ftCo_ItemScrew_IASA(Fighter_GObj* gobj);
/* 0D2E2C */ void ftCo_ItemScrew_Phys(Fighter_GObj* gobj);
/* 0D2E4C */ void ftCo_ItemScrew_Coll(Fighter_GObj* gobj);
/* 0D2E7C */ void ft_800D2E7C(Fighter_GObj*, Vec3*);
/* 0D2EF8 */ void ftCo_ItemScrewAir_Anim(Fighter_GObj* gobj);
/* 0D2F34 */ void ftCo_ItemScrewAir_IASA(Fighter_GObj* gobj);
/* 0D2F54 */ void ftCo_ItemScrewAir_Phys(Fighter_GObj* gobj);
/* 0D2F74 */ void ftCo_ItemScrewAir_Coll(Fighter_GObj* gobj);

#endif

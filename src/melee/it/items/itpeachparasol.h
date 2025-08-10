#ifndef GALE01_2BDA40
#define GALE01_2BDA40

#include <platform.h>

#include "it/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"
#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2BDA40 */ int it_802BDA40(Item_GObj*, int);
/* 2BDA64 */ Item_GObj* it_802BDA64(HSD_GObj* parent, Vec3* pos,
                                    Fighter_Part arg2, f32 dir);
/* 2BDB4C */ void it_802BDB4C(Item_GObj*);
/* 2BDB94 */ void it_802BDB94(Item_GObj*);
/* 2BDBF8 */ void it_802BDBF8(Item_GObj*);
/* 2BDC18 */ void it_802BDC18(Item_GObj*);
/* 2BDC38 */ bool it_802BDC38(Item_GObj*);
/* 2BDC74 */ void it_802BDC74(Item_GObj*);
/* 2BDCC0 */ bool itPeachparasol_UnkMotion2_Anim(Item_GObj*);
/* 2BDD3C */ void it_802BDD3C(Item_GObj*);
/* 2BDD40 */ void it_802BDD40(Item_GObj*, f32 arg1);
/* 2BDDB4 */ void it_802BDDB4(Item_GObj*, f32 arg1);
/* 2BDDF8 */ void it_802BDDF8(Item_GObj*, HSD_GObj*);
/* 3F74F8 */ extern ItemStateTable it_803F74F8[];

#endif

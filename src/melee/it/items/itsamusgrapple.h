#ifndef GALE01_2B7150
#define GALE01_2B7150

#include "ft/forward.h"
#include "it/forward.h"
#include <dolphin/mtx/forward.h>

#include "it/types.h"

void it_802B7150(Item_GObj*);
void it_802BA97C(Item_GObj*);
void it_802BAEA0(Item_GObj*, Item_GObj*);
/* 2BAC80 */ void it_802BAC80(Fighter_GObj* gobj);
/* 2BAC3C */ void it_802BAC3C(Fighter_GObj* gobj);
/* 2BACC4 */ void it_802BACC4(Fighter_GObj* gobj);
/* 2BAA58 */ void it_802BAA58(Item_GObj* gobj);
/* 2BAAE4 */ void it_802BAAE4(HSD_GObj*, Vec3*, float facing_dir);
/* 2B7B84 */ void it_802B7B84(Item_GObj* gobj);
/* 2B7C18 */ Item_GObj* it_802B7C18(Fighter_GObj*, Vec3*, float facing_dir);
/* 2A77DC */ void it_802A77DC(Item_GObj* gobj);

extern ItemStateTable it_803F73A8[];

#endif

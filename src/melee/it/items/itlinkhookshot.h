#ifndef GALE01_2A2418
#define GALE01_2A2418

#include "ft/forward.h"
#include "it/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "it/types.h"

void it_802A2418(Item_GObj*);
void it_802A7688(Item_GObj*);
void it_802A7D40(Item_GObj*, Item_GObj*);
/* 2A7AF0 */ void it_802A7AF0(HSD_GObj*);
/* 2A7AAC */ void it_802A7AAC(HSD_GObj*);
/* 2A7B34 */ void it_802A7B34(HSD_GObj*);
/* 2A78B8 */ void it_802A78B8(HSD_GObj*, Vec3*, float);
/* 2A2B10 */ void it_802A2B10(Item_GObj* gobj);
/* 2A2BA4 */ Item_GObj* it_802A2BA4(Fighter_GObj*, Vec3*, float, int);

extern ItemStateTable it_803F6998[];

#endif

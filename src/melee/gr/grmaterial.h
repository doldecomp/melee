#ifndef MELEE_GR_GRMATERIAL_H
#define MELEE_GR_GRMATERIAL_H

#include "gr/ground.h"

#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

void grMaterial_801C95C4(HSD_GObj*);
void grMaterial_801C9698(HSD_GObj*);
void grMaterial_801C94D8(unk_t hsd_obj);
void grMaterial_801C9604(HSD_GObj* bg, int, bool);
void grMaterial_801C8858(HSD_JObj*, u32 flags);
UNK_RET grMaterial_801C8CDC(UNK_PARAMS);
void grMaterial_801C8E08(int);
int grMaterial_801C8CFC(int, int, Ground*, HSD_JObj*, int, Event, int);

#endif

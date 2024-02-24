#ifndef GALE01_2B18B0
#define GALE01_2B18B0

#include "ft/forward.h"
#include "it/forward.h"

#include "it/items/types.h"

/* 2AFD8C */ Item_GObj* it_802AFD8C(Item_GObj*, Vec3*, u32, float);
/* 2AFEA8 */ Item_GObj* it_802AFEA8(Item_GObj* gobj, Fighter_GObj* owner_gobj,
                                    u32);
/* 2B19AC */ Item_GObj* it_802B19AC(Item_GObj*, Vec3* cur_pos, u32, u32,
                                    float facing_dir);
/* 2B1AAC */ void it_802B1AAC(Item_GObj*);
/* 2B1C40 */ void it_802B1C40(Item_GObj*, Item_GObj*);
/* 3F70A8 */ extern ItemStateTable it_803F70A8[];

#endif

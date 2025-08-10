#ifndef GALE01_2B18B0
#define GALE01_2B18B0

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2B18B0 */ UNK_RET it_802B18B0(UNK_PARAMS);
/* 2B19AC */ Item_GObj* it_802B19AC(Item_GObj*, Vec3* cur_pos, u32, u32,
                                    float facing_dir);
/* 2B1AAC */ void it_802B1AAC(Item_GObj*);
/* 2B1AD4 */ bool itSeakneedleheld_UnkMotion0_Anim(Item_GObj* gobj);
/* 2B1C34 */ void itSeakneedleheld_UnkMotion0_Phys(Item_GObj* gobj);
/* 2B1C38 */ bool itSeakneedleheld_UnkMotion0_Coll(Item_GObj* gobj);
/* 2B1C40 */ void it_802B1C40(Item_GObj*, Item_GObj*);
/* 3F70A8 */ extern ItemStateTable it_803F70A8[];

#endif

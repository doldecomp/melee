#ifndef GALE01_2F0340
#define GALE01_2F0340

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2F0340 */ Item_GObj* it_802F0340(Item_GObj* gobj, Vec3* prev_pos, Vec3* pos,
                                    Fighter_Part part, ItemKind kind,
                                    f32 facing_dir);
/* 2F044C */ void it_802F044C(Item_GObj*, Item_GObj*);
/* 2F046C */ void it_802F046C(Item_GObj*);
/* 2F0484 */ void it_802F0484(Item_GObj*);
/* 2F04F0 */ bool it_802F04F0(Item_GObj*);
/* 2F059C */ UNK_RET it_802F059C(UNK_PARAMS);
/* 2F05A0 */ bool it_802F05A0(UNK_PARAMS);
/* 2F05A8 */ void it_802F05A8(Item_GObj*);
/* 2F063C */ void it_802F063C(Item_GObj*, Item_GObj*);
/* 3F9378 */ extern ItemStateTable it_803F9378[];

#endif

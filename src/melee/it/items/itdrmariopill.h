#ifndef GALE01_2C0510
#define GALE01_2C0510

#include <platform.h>

#include "ft/forward.h"
#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2C09C4 */ Item_GObj* it_802C09C4(Fighter_GObj* owner, Vec3* pos, s32 arg2,
                                    ItemKind arg3, s32 arg4, Fighter_Part arg5,
                                    f32 facing_dir);
/* 2C11E0 */ void it_802C11E0(Item_GObj*);
/* 2C1384 */ bool it_802C1384(Item_GObj*);
/* 2C13CC */ bool it_802C13CC(Item_GObj*);
/* 2C1400 */ bool it_802C1400(Item_GObj*);
/* 2C145C */ bool it_802C145C(Item_GObj*);
/* 2C14B8 */ bool it_802C14B8(Item_GObj*);
/* 2C1514 */ bool it_802C1514(Item_GObj*);
/* 2C1570 */ void it_802C1570(Item_GObj*, Item_GObj*);
/* 3F75D0 */ extern ItemStateTable it_803F75D0[];

#endif

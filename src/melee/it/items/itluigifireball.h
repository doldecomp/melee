#ifndef GALE01_2C01AC
#define GALE01_2C01AC

#include <platform.h>

#include "it/forward.h"
#include <baselib/forward.h>

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2C01AC */ void it_802C01AC(Item_GObj* gobj, Vec3* pos, ItemKind kind,
                              float facing_dir);
/* 2C0490 */ bool it_802C0490(Item_GObj*);
/* 2C0498 */ bool it_802C0498(Item_GObj*);
/* 2C04B8 */ bool it_802C04B8(Item_GObj*);
/* 2C04C0 */ bool it_802C04C0(Item_GObj*);
/* 2C04C8 */ bool it_802C04C8(Item_GObj*);
/* 2C04D0 */ bool it_802C04D0(Item_GObj*);
/* 2C04F0 */ void it_802C04F0(Item_GObj*, HSD_GObj*);
/* 3F75C0 */ extern ItemStateTable it_803F75C0[];

#endif

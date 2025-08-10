#ifndef GALE01_2C01AC
#define GALE01_2C01AC

#include <platform.h>

#include "it/forward.h"
#include <baselib/forward.h>

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2C01AC */ void it_802C01AC(Item_GObj* gobj, Vec3* pos, ItemKind kind,
                              float facing_dir);
/* 2C0490 */ bool it_2725_Logic89_DmgDealt(Item_GObj*);
/* 2C0498 */ bool it_2725_Logic89_Reflected(Item_GObj*);
/* 2C04B8 */ bool it_2725_Logic89_Clanked(Item_GObj*);
/* 2C04C0 */ bool it_2725_Logic89_HitShield(Item_GObj*);
/* 2C04C8 */ bool it_2725_Logic89_Absorbed(Item_GObj*);
/* 2C04D0 */ bool it_2725_Logic89_ShieldBounced(Item_GObj*);
/* 2C04F0 */ void it_2725_Logic89_EvtUnk(Item_GObj*, HSD_GObj*);
/* 3F75C0 */ extern ItemStateTable it_803F75C0[];

#endif

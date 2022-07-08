#ifndef _ftpichu_h_
#define _ftpichu_h_

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

typedef struct _ftPichuAttributes {
    /* 0x00 */ u32 x0_padding[(0x14 - 0x0) / 4];
    /* 0x14 */ u32 x14;
    /* 0x14 */ u32 x18;
    /* 0x18 */ u32 x18_padding[(0xDC - 0x1C) / 4];
    /* 0xDC */ u32 xDC;
} ftPichuAttributes;

void ftPichu_OnLoad(HSD_GObj*);
void ftPichu_OnDeath(HSD_GObj*);
void ftPichu_OnItemPickup(HSD_GObj*, BOOL);
void ftPichu_OnItemInvisible(HSD_GObj*);
void ftPichu_OnItemVisible(HSD_GObj*);
void ftPichu_OnItemDrop(HSD_GObj*, BOOL);
void func_8014A1A8(HSD_GObj*);
void ftPichu_OnKnockbackEnter(HSD_GObj*);
void ftPichu_OnKnockbackExit(HSD_GObj*);

#endif

#ifndef _ftpichu_h_
#define _ftpichu_h_

#include <baselib/gobj.h>
#include <melee/ft/fighter.h>

typedef struct _ftPichuAttributes {
    /* 0x00 */ u32 x0_padding[(0x14 - 0x0) / 4];
    /* 0x14 */ u32 x14;
    /* 0x14 */ u32 x18;
    /* 0x18 */ u32 x18_padding[(0xDC - 0x1C) / 4];
    /* 0xDC */ u32 xDC;
} ftPichuAttributes;

extern ActionState as_table_pichu[];
extern char lbl_803D21E8[];
extern char lbl_803D21F4[];
extern Fighter_CostumeStrings lbl_803D23B4[];
extern char lbl_803D2328[];
extern Fighter_DemoStrings lbl_803D23A4;

void ftPichu_OnLoad(HSD_GObj*);
void ftPichu_OnDeath(HSD_GObj*);
void ftPichu_OnItemPickup(HSD_GObj*, bool);
void ftPichu_OnItemInvisible(HSD_GObj*);
void ftPichu_OnItemVisible(HSD_GObj*);
void ftPichu_OnItemDrop(HSD_GObj*, bool);
void ftPichu_LoadSpecialAttrs(HSD_GObj*);
void ftPichu_OnKnockbackEnter(HSD_GObj*);
void ftPichu_OnKnockbackExit(HSD_GObj*);

#endif

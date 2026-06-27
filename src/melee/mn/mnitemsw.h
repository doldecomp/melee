#ifndef MELEE_MN_ITEMSW_H
#define MELEE_MN_ITEMSW_H

#include <placeholder.h>

#include <baselib/gobj.h>
#include <baselib/jobj.h>

typedef struct MnItemSwData {
    /* 0x00 */ u8 menu_kind;
    /* 0x01 */ u8 cursor;
    /* 0x02 */ u8 items[0x1F];
    /* 0x21 */ u8 x21;
    /* 0x22 */ u8 pad;
    /* 0x23 */ u8 x23;
    /* 0x24 */ HSD_JObj* jobjs[9];
} MnItemSwData; // size 0x48

/* 233A98 */ s32 mnItemSw_80233A98(s32);
/* 233B68 */ void mnItemSw_80233B68(MnItemSwData*, u32);
/* 233E10 */ void fn_80233E10(HSD_GObj*);
/* 23405C */ HSD_JObj* mnItemSw_8023405C(MnItemSwData*, u8);
/* 234104 */ void mnItemSw_80234104(HSD_GObj*);
/* 23453C */ void mnItemSw_8023453C(HSD_GObj*, u8, u8);
/* 234C24 */ void fn_80234C24(HSD_GObj*);
/* 235020 */ HSD_JObj* mnItemSw_80235020(u8, MnItemSwData*);
/* 2351A0 */ HSD_GObj* mnItemSw_802351A0(s32);
/* 2358C0 */ void mnItemSw_802358C0(void);

extern HSD_GObj* mnItemSw_804D6BE8;
extern u8 mnItemSw_804D6BEC;

#endif

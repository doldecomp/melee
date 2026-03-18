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
/* 233B68 */ UNK_RET mnItemSw_80233B68(UNK_PARAMS);
/* 233E10 */ void fn_80233E10(HSD_GObj*);
/* 23405C */ HSD_JObj* mnItemSw_8023405C(MnItemSwData*, u8);
/* 234104 */ UNK_RET mnItemSw_80234104(UNK_PARAMS);
/* 23453C */ UNK_RET mnItemSw_8023453C(UNK_PARAMS);
/* 234C24 */ UNK_RET fn_80234C24(UNK_PARAMS);
/* 235020 */ UNK_RET mnItemSw_80235020(UNK_PARAMS);
/* 2351A0 */ void mnItemSw_802351A0(s32);
/* 2358C0 */ void mnItemSw_802358C0(void);

extern u8 mnItemSw_804D6BEC;

#endif

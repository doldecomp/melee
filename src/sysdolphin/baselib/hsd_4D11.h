/** @file hsd_4D11.h
 * Card work area .bss/.sbss used by the card functions in hsd_3A94.c
 * (and the JPEG decoder in hsd_3B34.c). Kept in its own TU: the card
 * functions only match when this data is referenced as extern, so it
 * cannot be defined alongside them.
 */
#ifndef SYSDOLPHIN_BASELIB_HSD_4D11_H
#define SYSDOLPHIN_BASELIB_HSD_4D11_H

#include <Runtime/platform.h>

typedef struct {
    u8 x0[0x300];
} __baselib_UnkType003;

/* 4D1138 */ extern u8 hsd_804D1138[0x10];
/* 4D1148 */ extern u32 hsd_804D1148[0x80][0x9];
/* 4D2348 */ extern __baselib_UnkType003 hsd_804D2348;

/// Command ring head (next command to run) and tail (next free slot).
/* 4D7980 */ extern volatile s32 hsd_804D7980;

/* 4D7984 */ extern volatile s32 hsd_804D7984;
/* 4D7988 */ extern int _card_result;
/* 4D798C */ extern s32 hsd_804D798C;
/* 4D7990 */ extern s32 hsd_804D7990;
/* 4D7994 */ extern s32 hsd_804D7994;

/// Ring tail saved before queueing a request; -1 when nothing to roll back.
/* 4D7998 */ extern s32 hsd_804D7998;

/* 4D799C */ extern s32 hsd_804D799C;

#endif

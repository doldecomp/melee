#ifndef _DOLPHIN_DEMO_H_
#define _DOLPHIN_DEMO_H_

#include <dolphin/pad.h>
#include <dolphin/gx.h>

struct STRUCT_MENU_ITEM {
    /* 0x00 */ char * name;
    /* 0x04 */ unsigned long flags;
    /* 0x08 */ void (* function)(struct STRUCT_MENU *, unsigned long, unsigned long *);
    /* 0x0C */ struct STRUCT_MENU * link;
};

struct STRUCT_MENU {
    /* 0x00 */ char * title;
    /* 0x04 */ struct STRUCT_DEMOWIN * handle;
    /* 0x08 */ struct STRUCT_MENU_ITEM * items;
    /* 0x0C */ long max_display_items;
    /* 0x10 */ unsigned long flags;
    /* 0x14 */ void (* cb_open)(struct STRUCT_MENU *, unsigned long);
    /* 0x18 */ void (* cb_move)(struct STRUCT_MENU *, unsigned long);
    /* 0x1C */ void (* cb_select)(struct STRUCT_MENU *, unsigned long);
    /* 0x20 */ void (* cb_cancel)(struct STRUCT_MENU *, unsigned long);
    /* 0x24 */ long num_display_items;
    /* 0x28 */ long num_items;
    /* 0x2C */ unsigned long max_str_len;
    /* 0x30 */ long curr_pos;
    /* 0x34 */ long display_pos;
};

typedef struct {
    /* 0x00 */ struct PADStatus pads[4];
    /* 0x30 */ unsigned long button[4];
    /* 0x40 */ unsigned long old_button[4];
    /* 0x50 */ unsigned long changed_button[4];
    /* 0x60 */ unsigned long repeat_button[4];
    /* 0x70 */ unsigned long repeat_ctr[4];
} DEMOWinPadInfo;

struct STRUCT_LISTBOX_ITEM {
    /* 0x00 */ char * name; // offset 0x0, size 0x4
    /* 0x04 */ unsigned long flags; // offset 0x4, size 0x4
};

struct STRUCT_LISTBOX {
    /* 0x00 */ char * title; // offset 0x0, size 0x4
    /* 0x04 */ struct STRUCT_DEMOWIN * handle; // offset 0x4, size 0x4
    /* 0x08 */ struct STRUCT_LISTBOX_ITEM * items; // offset 0x8, size 0x4
    /* 0x0C */ long max_display_items; // offset 0xC, size 0x4
    /* 0x10 */ unsigned long flags; // offset 0x10, size 0x4
    /* 0x14 */ long num_display_items; // offset 0x14, size 0x4
    /* 0x18 */ long num_items; // offset 0x18, size 0x4
    /* 0x1C */ unsigned long max_str_len; // offset 0x1C, size 0x4
    /* 0x20 */ long curr_pos; // offset 0x20, size 0x4
    /* 0x24 */ long display_pos; // offset 0x24, size 0x4
    /* 0x28 */ int cursor_state; // offset 0x28, size 0x4
};

extern unsigned long DEMOFontBitmap[768];

#include <dolphin/demo/DEMOInit.h>
#include <dolphin/demo/DEMOPad.h>
#include <dolphin/demo/DEMOPuts.h>
#include <dolphin/demo/DEMOStats.h>
#include <dolphin/demo/DEMOWin.h>

// unsorted externs
extern void DEMOPrintf(s16 x, s16 y, s16 priority, char *str, ...);

extern struct _GXRenderModeObj *DEMOGetRenderModeObj();

#endif // _DOLPHIN_DEMO_H_

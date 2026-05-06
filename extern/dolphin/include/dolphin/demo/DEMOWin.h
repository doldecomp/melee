#ifndef _DOLPHIN_DEMOWIN_H_
#define _DOLPHIN_DEMOWIN_H_

enum DEMOWinItem {
    DEMOWIN_ITEM_CAP,
    DEMOWIN_ITEM_BKGND,
    DEMOWIN_ITEM_BORDER,
    DEMOWIN_ITEM_DEFAULT
};

// flags
#define DEMOWIN_FLAGS_INIT   (1 << 0)
#define DEMOWIN_FLAGS_OPENED (1 << 1)

struct STRUCT_DEMOWIN {
    /* 0x00 */ long x1;
    /* 0x04 */ long y1;
    /* 0x08 */ long x2;
    /* 0x0C */ long y2;
    /* 0x10 */ unsigned long priority;
    /* 0x14 */ unsigned long flags;
    /* 0x18 */ unsigned short x_cal;
    /* 0x1A */ unsigned short y_cal;
    /* 0x1C */ unsigned short pixel_width;
    /* 0x1E */ unsigned short pixel_height;
    /* 0x20 */ unsigned short char_width;
    /* 0x22 */ unsigned short char_height;
    /* 0x24 */ unsigned short num_scroll_lines;
    /* 0x26 */ unsigned short total_lines;
    /* 0x28 */ unsigned short curr_output_line;
    /* 0x2A */ unsigned short curr_output_col;
    /* 0x2C */ unsigned short curr_view_line;
    /* 0x2E */ signed short cursor_line;
    /* 0x30 */ char * caption;
    /* 0x34 */ unsigned char * buffer;
    /* 0x38 */ GXColor bkgnd;
    /* 0x3C */ GXColor cap;
    /* 0x40 */ GXColor border;
    /* 0x44 */ void (* refresh)(struct STRUCT_DEMOWIN *);
    /* 0x48 */ struct STRUCT_DEMOWIN * next;
    /* 0x4C */ struct STRUCT_DEMOWIN * prev;
    /* 0x50 */ void * parent;
};

// functions
void DEMOWinInit();
struct STRUCT_DEMOWIN * DEMOWinCreateWindow(s32 x1, s32 y1, s32 x2, s32 y2, char * caption, u16 scroll, void * func);
void DEMOWinDestroyWindow(struct STRUCT_DEMOWIN * handle);
void DEMOWinOpenWindow(struct STRUCT_DEMOWIN * handle);
void DEMOWinCloseWindow(struct STRUCT_DEMOWIN * handle);
void DEMOWinSetWindowColor(struct STRUCT_DEMOWIN * handle, enum DEMOWinItem item, u8 r, u8 g, u8 b, u8 a);
void DEMOWinLogPrintf(struct STRUCT_DEMOWIN * handle, char * fmt, ...);
void DEMOWinPrintfXY(struct STRUCT_DEMOWIN * handle, u16 col, u16 row, char * fmt, ...);
void DEMOWinScrollWindow(struct STRUCT_DEMOWIN * handle, u32 dir);
void DEMOWinBringToFront(struct STRUCT_DEMOWIN * handle);
void DEMOWinSendToBack(struct STRUCT_DEMOWIN * handle);
void DEMOWinClearRow(struct STRUCT_DEMOWIN * handle, u16 row);
void DEMOWinClearWindow(struct STRUCT_DEMOWIN * handle);
void DEMOWinClearBuffer(struct STRUCT_DEMOWIN * handle);
void DEMOWinRefresh();
struct STRUCT_MENU * DEMOWinCreateMenuWindow(struct STRUCT_MENU * menu, u16 x, u16 y);
void DEMOWinDestroyMenuWindow(struct STRUCT_MENU * menu);
u32 DEMOWinMenuChild(struct STRUCT_MENU * menu, int child_flag);
void DEMOWinPadInit(DEMOWinPadInfo *p);
void DEMOWinPadRead(DEMOWinPadInfo *p);
void DEMOWinSetRepeat(unsigned long threshold, unsigned long rate);
void DEMOWinResetRepeat();
struct STRUCT_LISTBOX * DEMOWinCreateListWindow(struct STRUCT_LISTBOX * list, unsigned short x, unsigned short y);
void DEMOWinDestroyListWindow(struct STRUCT_LISTBOX * list);
void DEMOWinListSetCursor(struct STRUCT_LISTBOX * list, int x);
long DEMOWinListScrollList(struct STRUCT_LISTBOX * list, unsigned long dir);
long DEMOWinListMoveCursor(struct STRUCT_LISTBOX * list, unsigned long dir);

#endif // _DOLPHIN_DEMOWIN_H_

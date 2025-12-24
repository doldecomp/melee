#ifndef GALE01_302834
#define GALE01_302834

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"
#include "if/forward.h"

#include <dolphin/gx.h>

/* 302834 */ DevText* DevText_Create(char, int, int, int, int, char*);
/* 3029B4 */ void DevText_EraseFirstLine(DevText* text);
/* 302A3C */ void DevText_SetCursorXY(DevText* text, int x, int y);
/* 302A88 */ void DevText_SetCursorX(DevText* text, int x);
/* 302AB0 */ void DevText_HideCursor(DevText* text);
/* 302AC0 */ void DevText_80302AC0(DevText* text);
/* 302AD0 */ void DevText_ShowBackground(DevText* text);
/* 302AE0 */ void DevText_HideBackground(DevText* text);
/* 302AF0 */ void DevText_ShowText(DevText* text);
/* 302B00 */ void DevText_HideText(DevText* text);
/* 302B10 */ void DevText_SetScale(DevText* text, float x, float y);
/* 302B1C */ void DevText_SetXY(DevText* text, int x, int y);
/* 302B48 */ u8 DevText_StoreColorIndex(DevText* text, u8 index);
/* 302B64 */ GXColor DevText_SetTextColor(DevText* text, GXColor color);
/* 302B90 */ GXColor DevText_SetBGColor(DevText* text, GXColor color);
/* 302BB0 */ void DevText_Erase(DevText* text);
/* 302BE4 */ void DevText_Print(DevText* text, char* str);
/* 302D0C */ void DevText_PrintInt(DevText* text, int num);
/* 302D4C */ void DevText_Printf(DevText* text, char* format, ...);
/* 302DF0 */ struct un_80304138_objalloc_t* un_80302DF0(void);
/* 302DF8 */ void un_80302DF8(struct un_80304138_objalloc_t* arg0, void* arg1);
/* 302E00 */ int un_80302E00(struct un_80304138_objalloc_t_x8*, int);
/* 302EA4 */ int un_80302EA4(struct un_80304138_objalloc_t_x8*);
/* 302FFC */ void un_80302FFC(struct un_80304138_objalloc_t*);
/* 303444 */ bool un_80303444(struct un_80304138_objalloc_t*);
/* 303720 */ bool un_80303720(struct un_80304138_objalloc_t* arg0);
/* 3039A4 */ int un_803039A4(unsigned char);
/* 303AC4 */ void un_80303AC4(struct un_80304138_objalloc_t*);
/* 303EF4 */ void fn_80303EF4(HSD_GObj*);
/* 303FD4 */ void un_80303FD4(HSD_GObj*, struct un_80304138_objalloc_t*,
                              struct un_80304138_objalloc_t_x8*, int, int,
                              int);
/* 304138 */ UNK_RET un_80304138(UNK_PARAMS);
/* 304168 */ HSD_GObj* un_80304168(void* arg0, int arg1, int arg2, int arg3);
/* 304210 */ void un_80304210(struct un_80304138_objalloc_t* arg0, void* arg1,
                              int arg2, int arg3, int arg4);
/* 304334 */ void un_80304334(struct un_80304138_objalloc_t* arg0);
/* 304344 */ void un_80304344(struct un_80304138_objalloc_t*);
/* 304470 */ bool un_80304470(void);
/* 304510 */ bool un_80304510(void);
/* 3045A0 */ int un_803045A0(void);
/* 304690 */ int un_80304690(void);
/* 304780 */ bool un_80304780(void);
/* 304870 */ int un_80304870(void);
/* 3048C0 */ int un_803048C0(int);
/* 304924 */ bool un_80304924(int);
/* 304988 */ void un_80304988(int);
/* 3049F4 */ bool un_803049F4(int);
/* 304A58 */ void un_80304A58(int);
/* 304B0C */ bool un_80304B0C(int);
/* 304B94 */ int un_80304B94(int);
/* 304CC8 */ bool un_80304CC8(int);
/* 304D30 */ int un_80304D30(void);
/* 4A26B8 */ extern unsigned short un_804A26B8[1000];
/* 4A284C */ extern unsigned short un_804A284C[1000];

#endif

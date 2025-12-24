#ifndef _TEXTDRAW_H_
#define _TEXTDRAW_H_

#include "if/forward.h"
#include <baselib/forward.h>

/* 301E44 */ int DevText_StrLen(char* str);
/* 301E78 */ void DevText_NumToStr(int, char*);
/* 301FB4 */ HSD_GObj* DevText_GetGObj(void);
/* 301FBC */ void DevText_InitPool(void);
/* 3020FC */ void DevText_Remove(DevText** ptext);
/* 302164 */ void DevText_SetupCObj(void);
/* 3022BC */ void DevText_Draw(DevText* text);
/* 302608 */ void DevText_DrawAll(HSD_GObj* gobj, int pass);
/* 30265C */ void DevText_CreateCObj(int classifier, int p_link,
                                     int gobj_priority, int gx_link,
                                     u8 gx_priority);
/* 302708 */ HSD_GObj* DevText_Setup(int classifier, int p_link, int priority,
                                     int gx_link, int render_priority,
                                     u8 camera_priority);
/* 3027A0 */ void DevText_AddToList(DevText** list, DevText* text);
/* 302810 */ void DevText_Show(HSD_GObj* gobj, DevText* text);

#endif

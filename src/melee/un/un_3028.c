#include "un_3028.h"

#include "baselib/controller.h"
#include "baselib/debug.h"
#include "dolphin/os.h"
#include "gm/gm_unsplit.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "ty/toy.h"

#include "un/forward.h"

#include "un/types.h"
#include "un/un_2FC9.h"

#include <printf.h>
#include <stdarg.h>
#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/particle.h>
#include <baselib/sislib.h>
#include <MSL/math.h>
#include <MSL/stdio.h>
#include <MSL/string.h>

// ?
/* 4D6E18 */ extern DevText* devtext_drawlist;
/* 4D6E38 */ extern DevText* devtext_poolhead;
unsigned short un_804A26B8[1000];
unsigned short un_804A284C[1000];
short* un_804D6EB4;
struct un_80304138_objalloc_t* un_804D6E40;
struct un_80304138_objalloc_t_x8* un_804D6E48;
struct idk {
    short idk[26];
} un_803B8810;
struct idk un_803B87DC;
struct idk un_803B87A8;
unsigned char un_804D6E4C;

// .bss
/* 4A2688 */ static HSD_ObjAllocData un_804A2688;

// .sbss
/* 4D6E44 */ static struct un_80304138_objalloc_t* un_804D6E44;

GXColor white = { 0xFF, 0xFF, 0xFF, 0xFF };
GXColor red = { 0xFF, 0x80, 0x80, 0xFF };
GXColor green = { 0x80, 0xFF, 0x80, 0xFF };
GXColor blue = { 0x80, 0x80, 0xFF, 0xFF };

GXColor color_08 = { 0x40, 0x50, 0x80, 0x80 };
GXColor color_0C = { 0xE2, 0xE2, 0xE2, 0xFF };
GXColor color_10 = { 0xFF, 0x80, 0x20, 0xFF };
GXColor color_14 = { 0xA0, 0xA0, 0xFF, 0xFF };

static inline DevText* find_by_id(char id)
{
    DevText* text;
    for (text = devtext_drawlist; text != NULL; text = text->next) {
        if (text->id == id) {
            return text;
        }
    }
    return NULL;
}

DevText* DevText_Create(char id, int x, int y, int w, int h, char* buf)
{
    DevText* text;
    GXColor bg = { 0x60, 0xD0, 0xB0, 0x70 };
    PAD_STACK(0x60 - 0x48);

    if ((text = find_by_id(id))) {
        return NULL;
    }
    text = devtext_poolhead;
    if (text != NULL) {
        devtext_poolhead = text->next;
    } else {
        text = NULL;
    }
    if (text == NULL) {
        // HSD_ASSERT
        OSReport("TW : Screen alloc Fail\n");
        __assert("textlib.c", 309, "0");
    }
    if (text != NULL) {
        text->x = x;
        text->y = y;
        text->w = w;
        text->h = h;
        text->cursor_x = 0;
        text->cursor_y = 0;
        text->scale_x = 10.0;
        text->scale_y = 16.0;
        text->bg_color = bg;
        text->text_colors[0] = white;
        text->text_colors[1] = red;
        text->text_colors[2] = green;
        text->text_colors[3] = blue;
        text->id = (int) id;
        text->line_width = 10;
        text->flags = DEVTEXT_FLAG_SHOWCURSOR;
        text->unk = 0;
        text->current_color = 0;
        text->prev = NULL;
        text->next = NULL;
        text->buf = buf;
        memzero(buf, h * (w * 2));
    }
    return text;
}

void DevText_EraseFirstLine(DevText* text)
{
    char* start_of_line = text->buf;
    int line_length = text->w * 2;
    int line_number;

    for (line_number = 0; line_number < text->h - 1; line_number++) {
        memcpy(start_of_line, start_of_line + line_length, line_length);
        start_of_line += line_length;
    }
    memzero(start_of_line, line_length);
}

inline int DevText_Clamp(int val, int max)
{
    if (max <= val) {
        return max - 1;
    } else if (val < 0) {
        return 0;
    } else {
        return val;
    }
}

void DevText_SetCursorXY(DevText* text, int x, int y)
{
    text->cursor_x = DevText_Clamp(x, text->w);
    text->cursor_y = DevText_Clamp(y, text->h);
}

void DevText_SetCursorX(DevText* text, int x)
{
    text->cursor_x = DevText_Clamp(x, text->w);
}

void DevText_HideCursor(DevText* text)
{
    text->flags &= ~(1 << 4);
}

void DevText_80302AC0(DevText* text)
{
    text->flags |= (1 << 5);
}

void DevText_ShowBackground(DevText* text)
{
    text->flags &= ~(1 << 6);
}

void DevText_HideBackground(DevText* text)
{
    text->flags |= (1 << 6);
}

void DevText_ShowText(DevText* text)
{
    text->flags &= ~(1 << 7);
}

void DevText_HideText(DevText* text)
{
    text->flags |= (1 << 7);
}

void DevText_SetScale(DevText* text, f32 x, f32 y)
{
    text->scale_x = x;
    text->scale_y = y;
}

void DevText_SetXY(DevText* text, int x, int y)
{
    if (x < 8) {
        x = 8;
    }
    if (y < 8) {
        y = 8;
    }
    text->x = x;
    text->y = y;
}

u8 DevText_StoreColorIndex(DevText* text, u8 index)
{
    u8 old = text->current_color;
    text->current_color = index;
    return old;
}

GXColor DevText_SetTextColor(DevText* text, GXColor color)
{
    int index = text->current_color;
    GXColor old = text->text_colors[index];
    text->text_colors[index] = color;
    return old;
}

GXColor DevText_SetBGColor(DevText* text, GXColor color)
{
    GXColor old = text->bg_color;
    text->bg_color = color;
    return old;
}

void DevText_Erase(DevText* text)
{
    memzero(text->buf, 2 * text->w * text->h);
}

inline void DevText_AdvanceLine(DevText* text)
{
    text->cursor_x = 0;
    if (text->cursor_y < text->h - 1) {
        text->cursor_y++;
    } else {
        DevText_EraseFirstLine(text);
    }
}

void DevText_Print(DevText* text, char* str)
{
    if (str) {
        while (*str) {
            if (*str != '\n') {
                int index = (text->cursor_x + text->cursor_y * text->w) * 2;
                text->buf[index] = *str;
                text->buf[index + 1] = text->current_color << 6;
                if (text->cursor_x < text->w - 1) {
                    text->cursor_x++;
                } else if ((text->flags & DEVTEXT_FLAG_NOWRAP) == 0) {
                    DevText_AdvanceLine(text);
                }
            } else {
                DevText_AdvanceLine(text);
            }
            str++;
        }
    }
}

void DevText_PrintInt(DevText* text, int num)
{
    char str[16];
    DevText_NumToStr(num, str);
    DevText_Print(text, str);
}

void DevText_Printf(DevText* text, char* format, ...)
{
    char str[64];
    va_list args;
    va_start(args, format);
    vsnprintf(str, -1, format, args);
    va_end(args);
    DevText_Print(text, str);
}

struct un_80304138_objalloc_t* un_80302DF0(void)
{
    return un_804D6E44;
}

void un_80302DF8(struct un_80304138_objalloc_t* arg0, void* arg1)
{
    arg0->xC = arg1;
}

int un_80302E00(struct un_80304138_objalloc_t_x8* arg0, int arg1)
{
    int ret = 0;
    if (arg0->x4 != NULL) {
        un_804D6E48 = arg0;
        ret = arg0->x4(arg1);
        if (ret == 0) {
            if (un_804D6E44 && un_804D6E44->xC) {
                return un_804D6E44->xC(arg1);
            }
        }
    } else if (un_804D6E44 && un_804D6E44->xC) {
        return un_804D6E44->xC(arg1);
    }
    return ret;
}

int un_80302EA4(struct un_80304138_objalloc_t_x8* arg0)
{
    int i;
    int x = 1;
    int y = 1;
    int z = 1;
    while (arg0->x0 != 9) {
        if ((unsigned int) arg0->x0 <= 1) {
            int len = DevText_StrLen(arg0->x8) + 1;
            if (len > z) {
                z = len;
            }
        } else {
            int len = DevText_StrLen(arg0->x8) + 1;
            if (len > x) {
                x = len;
            }
        }
        if ((arg0->x0 == 3 || arg0->x0 == 8) && y < 3) {
            y = 3;
        }
        if (arg0->x0 == 4 && y < 10) {
            y = 10;
        }
        if (arg0->x0 == 5 && y < 2) {
            y = 2;
        }
        if (arg0->x0 == 6 && y < 4) {
            y = 4;
        }
        if (arg0->x0 == 7 && y < 8) {
            y = 8;
        }
        if (arg0->x0 == 2) {
            for (i = 0; i < (int) arg0->x18; i++) {
                int len = DevText_StrLen(arg0->xC[i]);
                if (len > y) {
                    y = len;
                }
            }
        }
        arg0++;
    }
    x += y;
    if (x > z) {
        return x + 1;
    } else {
        return z + 1;
    }
}

static inline GXColor adjust(GXColor c)
{
    c.r = c.r * 50 / 100;
    c.g = c.g * 50 / 100;
    c.b = c.b * 50 / 100;
    return c;
}

void un_80302FFC(struct un_80304138_objalloc_t* arg0)
{
    struct un_80304138_objalloc_t_x8* x8 = arg0->x8;
    struct un_80304138_objalloc_t_x8* thing;
    int cursor_x = 1;
    int cursor_y;
    for (thing = x8; thing->x0 != 9; thing++) {
        if (thing->x0 != 0 && thing->x0 != 1) {
            int len = DevText_StrLen(thing->x8);
            if (len + 1 > cursor_x) {
                cursor_x = len + 1;
            }
        }
    }
    if (arg0->x1 & 0x10) {
        DevText_StoreColorIndex(arg0->x4, 0);
        DevText_SetTextColor(arg0->x4, adjust(color_0C));
        DevText_StoreColorIndex(arg0->x4, 1);
        DevText_SetTextColor(arg0->x4, adjust(color_10));
        DevText_StoreColorIndex(arg0->x4, 2);
        DevText_SetTextColor(arg0->x4, adjust(color_14));
        DevText_SetBGColor(arg0->x4, adjust(color_08));
    } else {
        DevText_StoreColorIndex(arg0->x4, 0);
        DevText_SetTextColor(arg0->x4, color_0C);
        DevText_StoreColorIndex(arg0->x4, 1);
        DevText_SetTextColor(arg0->x4, color_10);
        DevText_StoreColorIndex(arg0->x4, 2);
        DevText_SetTextColor(arg0->x4, color_14);
        DevText_SetBGColor(arg0->x4, color_08);
    }
    for (cursor_y = 0; cursor_y < arg0->x4->h; cursor_y++) {
        if (arg0->x0 == 0) {
            DevText_StoreColorIndex(arg0->x4, 2);
        } else if (arg0->x0 == cursor_y) {
            DevText_StoreColorIndex(arg0->x4, 1);
        } else {
            DevText_StoreColorIndex(arg0->x4, 0);
        }
        DevText_SetCursorXY(arg0->x4, 0, cursor_y);
        DevText_Print(arg0->x4, x8->x8);
        DevText_SetCursorXY(arg0->x4, cursor_x, cursor_y);
        switch (x8->x0) {
        case 2:
            DevText_Print(arg0->x4, x8->xC[*(int*) x8->x10]);
            break;
        case 3:
            DevText_PrintInt(arg0->x4, *(int*) x8->x10);
            break;
        case 4:
            DevText_Printf(arg0->x4, "%d", *(int*) x8->x10);
            break;
        case 5:
            DevText_Printf(arg0->x4, "%02x", *(unsigned char*) x8->x10);
            break;
        case 6:
            DevText_Printf(arg0->x4, "%04x", *(unsigned short*) x8->x10);
            break;
        case 7:
            DevText_Printf(arg0->x4, "%08x", *(int*) x8->x10);
            break;
        case 8:
            DevText_Printf(arg0->x4, "%3.2f", *(float*) x8->x10);
            break;
        }
        arg0++;
    }
}

bool un_80303444(struct un_80304138_objalloc_t* arg0)
{
    bool ret = false;
    struct un_80304138_objalloc_t_x8* x8 = arg0->x8;
    switch (x8[arg0->x0].x0) {
    case 2: {
        int* q = x8[arg0->x0].x10;
        if (*q < x8[arg0->x0].x18 - 1.0f) {
            *q += 1;
            ret = true;
            arg0->x1 = arg0->x1 | 1;
            lbAudioAx_80024030(2);
        }
        break;
    }
    case 3: {
        int* q = x8[arg0->x0].x10;
        if (*q + x8[arg0->x0].x1C <= x8[arg0->x0].x18) {
            ret = true;
            *q += x8[arg0->x0].x1C;
            arg0->x1 = arg0->x1 | 1;
            lbAudioAx_80024030(2);
        }
        break;
    }
    case 5: {
        unsigned char* q = x8[arg0->x0].x10;
        int idk = x8[arg0->x0].x1C;
        if (*q + (idk & 0xFF) <= 0xFF) {
            *q += idk;
        } else {
            *q -= 0x100 - idk;
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        lbAudioAx_80024030(2);
        break;
    }
    case 6: {
        unsigned short* q = x8[arg0->x0].x10;
        int idk = x8[arg0->x0].x1C;
        if (*q + (idk & 0xFFFF) <= 0xFFFF) {
            *q += idk;
        } else {
            *q -= 0x10000 - idk;
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        lbAudioAx_80024030(2);
        break;
    }
    case 4:
    case 7: {
        int* q = x8[arg0->x0].x10;
        unsigned int idk = x8[arg0->x0].x1C;
        if (*q + (idk & 0xFFFFFFFF) <= 0xFFFFFFFF) {
            *q += idk;
        } else {
            *q -= 0x100000000 - idk;
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        lbAudioAx_80024030(2);
        break;
    }
    case 8: {
        float* q = x8[arg0->x0].x10;
        if (*q + x8[arg0->x0].x1C <= x8[arg0->x0].x18) {
            *q += x8[arg0->x0].x1C;
            ret = true;
            arg0->x1 = arg0->x1 | 1;
            lbAudioAx_80024030(2);
        }
        break;
    }
    }
    return ret;
}

bool un_80303720(struct un_80304138_objalloc_t* arg0)
{
    bool ret = false;
    struct un_80304138_objalloc_t_x8* x8 = arg0->x8;
    switch (x8[arg0->x0].x0) {
    case 2: {
        int* q = x8[arg0->x0].x10;
        if (*q > x8[arg0->x0].x14) {
            *q -= 1;
            ret = true;
            arg0->x1 = arg0->x1 | 1;
            lbAudioAx_80024030(2);
        }
        break;
    }
    case 3: {
        int* q = x8[arg0->x0].x10;
        if (*q - x8[arg0->x0].x1C >= x8[arg0->x0].x14) {
            ret = true;
            *q -= x8[arg0->x0].x1C;
            arg0->x1 = arg0->x1 | 1;
            lbAudioAx_80024030(2);
        }
        break;
    }
    case 5: {
        unsigned char* q = x8[arg0->x0].x10;
        int idk = x8[arg0->x0].x1C;
        if (*q - (idk & 0xFF) >= 0) {
            *q -= idk;
        } else {
            *q += 0x100 - idk;
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        lbAudioAx_80024030(2);
        break;
    }
    case 6: {
        unsigned short* q = x8[arg0->x0].x10;
        int idk = x8[arg0->x0].x1C;
        if (*q - (idk & 0xFFFF) >= 0) {
            *q -= idk;
        } else {
            *q += 0x10000 - idk;
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        lbAudioAx_80024030(2);
        break;
    }
    case 4:
    case 7: {
        int* q = x8[arg0->x0].x10;
        unsigned int idk = x8[arg0->x0].x1C;
        *q = *q - idk;
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        lbAudioAx_80024030(2);
        break;
    }
    case 8: {
        float* q = x8[arg0->x0].x10;
        if (*q - x8[arg0->x0].x1C >= x8[arg0->x0].x14) {
            *q -= x8[arg0->x0].x1C;
            ret = true;
            arg0->x1 = arg0->x1 | 1;
            lbAudioAx_80024030(2);
        }
        break;
    }
    }
    return ret;
}

int un_803039A4(unsigned char arg0)
{
    unsigned int ret = 0;
    int button;
    if (HSD_PadCopyStatus[0].button & HSD_PAD_R) {
        button = 1;
    } else {
        button = 8;
    }
    if (HSD_PadCopyStatus[arg0].stickX < -60 && un_804D6E4C == 0) {
        ret |= 0x40000000;
    }
    if (HSD_PadCopyStatus[arg0].stickX > 60 && un_804D6E4C == 0) {
        ret |= 0x80000000;
    }
    if (HSD_PadCopyStatus[arg0].stickY < -60 && un_804D6E4C == 0) {
        ret |= 0x20000000;
    }
    if (HSD_PadCopyStatus[arg0].stickY > 60 && un_804D6E4C == 0) {
        ret |= 0x10000000;
    }
    if (ret != 0 && un_804D6E4C == 0) {
        un_804D6E4C = button;
    }
    if (ABS((int) HSD_PadCopyStatus[arg0].stickX) <= 60 &&
        ABS((int) HSD_PadCopyStatus[arg0].stickY) <= 60)
    {
        un_804D6E4C = 0;
    }
    if (un_804D6E4C != 0) {
        un_804D6E4C -= 1;
    }
    return ret;
}

void un_80303AC4(struct un_80304138_objalloc_t* arg0)
{
    int trigger = HSD_PadCopyStatus[0].trigger;
    int stick = un_803039A4(0);
    int buttons = stick | trigger;
    if (buttons & HSD_PAD_START) {
        struct un_80304138_objalloc_t_x8* x8 = &arg0->x8[arg0->x0];
        if (x8->x4 != NULL) {
            un_804D6E48 = x8;
            if (x8->x4(6) == 0) {
                if (un_804D6E44 != NULL && un_804D6E44->xC != NULL) {
                    un_804D6E44->xC(6);
                }
            }
        } else if (un_804D6E44 != NULL && un_804D6E44->xC) {
            un_804D6E44->xC(6);
        }
    } else if (buttons & (0x10000000 | HSD_PAD_Y)) { // up
        int i;
        int w;
        for (i = arg0->x0; i >= 0; i--) {
            if (arg0->x8[i].x0 != NULL) {
                w = i;
                goto up_found;
            }
        }
        w = -1;
    up_found:
        if (w != -1) {
            arg0->x0 = w;
            arg0->x1 = arg0->x1 | 1;
            lbAudioAx_80024030(2);
        }
    } else if (buttons & (0x20000000 | HSD_PAD_X)) { // down
        int i;
        int w;
        for (i = arg0->x0; i < arg0->x4->h; i++) {
            if (arg0->x8[i].x0 != NULL) {
                w = i;
                goto down_found;
            }
        }
        w = -1;
    down_found:
        if (w != -1) {
            arg0->x0 = w;
            arg0->x1 = arg0->x1 | 1;
            lbAudioAx_80024030(2);
        }
    } else if (buttons & (0x80000000 | HSD_PAD_R)) { // right
        if (un_80303444(arg0)) {
            struct un_80304138_objalloc_t_x8* x8 = &arg0->x8[arg0->x0];
            if (x8->x4 != NULL) {
                un_804D6E48 = x8;
                if (x8->x4(3) == 0) {
                    if (un_804D6E44 != NULL && un_804D6E44->xC) {
                        un_804D6E44->xC(3);
                    }
                }
            } else if (un_804D6E44 != NULL && un_804D6E44->xC) {
                un_804D6E44->xC(3);
            }
        }
    } else if (buttons & (0x40000000 | HSD_PAD_L)) { // left
        if (un_80303720(arg0)) {
            struct un_80304138_objalloc_t_x8* x8 = &arg0->x8[arg0->x0];
            if (x8->x4 != NULL) {
                un_804D6E48 = x8;
                if (x8->x4(2) == 0) {
                    if (un_804D6E44 != NULL && un_804D6E44->xC) {
                        un_804D6E44->xC(2);
                    }
                }
            } else if (un_804D6E44 != NULL && un_804D6E44->xC) {
                un_804D6E44->xC(2);
            }
        }
    } else if (buttons & HSD_PAD_A) {
        struct un_80304138_objalloc_t_x8* x8 = &arg0->x8[arg0->x0];
        if (x8->x4 != NULL) {
            un_804D6E48 = x8;
            if (x8->x4(1) == 0) {
                if (un_804D6E44 != NULL && un_804D6E44->xC) {
                    un_804D6E44->xC(1);
                }
            }
        } else if (un_804D6E44 != NULL && un_804D6E44->xC) {
            un_804D6E44->xC(1);
        }
    } else if (buttons & HSD_PAD_B) {
        struct un_80304138_objalloc_t_x8* x8 = &arg0->x8[arg0->x0];
        if (x8->x4 != NULL) {
            un_804D6E48 = x8;
            if (x8->x4(0) == 0) {
                if (un_804D6E44 != NULL && un_804D6E44->xC) {
                    un_804D6E44->xC(0);
                }
            }
        } else if (un_804D6E44 != NULL && un_804D6E44->xC) {
            un_804D6E44->xC(0);
        }
    }
}

void fn_80303EF4(HSD_GObj* gobj)
{
    struct un_80304138_objalloc_t* q = un_804D6E40;
    while (q != NULL) {
        if (q->x1 & 0x20) {
            DevText_HideText(q->x4);
            DevText_HideBackground(q->x4);
        } else {
            DevText_ShowText(q->x4);
            DevText_ShowBackground(q->x4);
            if (q->x1 & 1) {
                DevText_Erase(q->x4);
                un_80302FFC(q);
                q->x1 = q->x1 & ~1;
            } else {
                un_80302FFC(q);
            }
            if (q->x1 & 2) {
                q->x1 = q->x1 & ~2;
            } else if ((q->x1 & 0x10) == 0) {
                un_80303AC4(q);
            }
        }
        if (q->x1 & 0x80) {
            un_80304344(q);
            q = NULL;
        } else {
            q = q->prev;
        }
    }
}

void un_80303FD4(HSD_GObj* arg0, struct un_80304138_objalloc_t* arg1,
                 struct un_80304138_objalloc_t_x8* arg2, int arg3, int arg4,
                 int arg5)
{
    int i;
    int count;
    int count2 = 0;
    int size;
    void* buf;
    struct un_80304138_objalloc_t* un;

    arg1->x8 = arg2;
    arg1->x1 = 0;
    arg1->prev = NULL;
    arg1->next = NULL;
    arg1->x10 = arg0;

    count = 0;
    while (arg1->x8[count].x0 != 9) {
        count++;
    }

    size = un_80302EA4(arg1->x8);
    un_804D6E44 = arg1;
    buf = HSD_MemAlloc(size * count * 2);
    if (buf != NULL) {
        un = un_804D6E40;
        while (un != NULL && un != arg1) {
            un = un->prev;
            count2++;
        }
        arg1->x4 = DevText_Create(count2 + 0x78, arg4, arg5, size, count, buf);
        if (arg1->x4 != NULL) {
            DevText_Show(arg0, arg1->x4);
            for (i = 0; arg1->x8[i].x0 != 0; i++) {
                if (arg1->x8[i].x0 == 9) {
                    i = 0;
                    break;
                }
            }
            arg1->x0 = i;
            arg1->xC = NULL;
            DevText_HideCursor(arg1->x4);
            DevText_SetScale(arg1->x4, 10.0f, 17.0f);
            un_804D6E48 = NULL;
            for (i = 0; arg1->x8[i].x0 != 9; i++) {
                un_80302E00(&arg1->x8[i], 4);
            }
        }
    }
}

void un_80304138(void)
{
    HSD_ObjAllocInit(&un_804A2688, sizeof(struct un_80304138_objalloc_t), 4);
}

HSD_GObj* un_80304168(void* arg0, int arg1, int arg2, int arg3)
{
    HSD_GObj* gobj = DevText_GetGObj();
    HSD_GObj* gobj2 = NULL;
    struct un_80304138_objalloc_t* userdata;
    PAD_STACK(8);
    if (gobj != NULL) {
        gobj2 = GObj_Create(gobj->classifier, gobj->p_link, gobj->p_priority);
        if (gobj2 != NULL) {
            userdata = HSD_ObjAlloc(&un_804A2688);
            un_804D6E40 = userdata;
            un_80303FD4(gobj2, userdata, arg0, arg1, arg2, arg3);
            userdata->x14 = HSD_GObjProc_8038FD54(gobj2, fn_80303EF4, 0);
        }
    }
    return gobj2;
}

void un_80304210(struct un_80304138_objalloc_t* arg0, void* arg1, int arg2,
                 int arg3, int arg4)
{
    struct un_80304138_objalloc_t* obj = HSD_ObjAlloc(&un_804A2688);
    if (obj != NULL) {
        DevText* text = arg0->x4;
        un_80303FD4(arg0->x10, obj, arg1, arg2,
                    text->x + arg3 + text->scale_x * text->w,
                    text->y + arg4 + text->scale_y * arg0->x0);
        arg0->x1 = arg0->x1 | 0x10;
        arg0->prev = obj;
        obj->next = arg0;
        obj->x1 = obj->x1 | 2;
    }
}

void un_80304334(struct un_80304138_objalloc_t* arg0)
{
    arg0->x1 |= (1 << 7);
}

void un_80304344(struct un_80304138_objalloc_t* arg0)
{
    struct un_80304138_objalloc_t* next = arg0->next;
    struct un_80304138_objalloc_t* w;
    struct un_80304138_objalloc_t_x8* r4;
    int (*q)(int);
    if (next) {
        next->x1 = next->x1 & ~0x10;
        next->prev = NULL;
    }
    while (arg0) {
        r4 = arg0->x8;
        un_804D6E44 = arg0;
        while (r4->x0 != 9) {
            r4++;
        }
        if (r4->x4) {
            un_804D6E48 = r4;
            if (r4->x4(5) == 0 && un_804D6E44 != NULL) {
                if ((q = un_804D6E44->xC)) {
                    q(5);
                }
            }
        } else if (arg0) {
            if ((q = arg0->xC)) {
                q(5);
            }
        }
        HSD_Free(arg0->x4->buf);
        DevText_Remove(&arg0->x4);
        w = arg0->prev;
        HSD_ObjFree(&un_804A2688, arg0);
        arg0 = w;
    }
    un_804D6E44 = next;
}

int un_80304470(void)
{
    int i;
    int sum = 0;
    int count;
    for (i = 0; i < 8; i++) {
        sum += un_80304B94(i);
    }
    count = 0;
    for (i = 0; i < 0x125; i++) {
        if (i != 0xE6 && i != 0xC9 && un_803048C0(i)) {
            count++;
        }
    }
    if (sum <= count) {
        return 1;
    } else {
        return 0;
    }
}

int un_80304510(void)
{
    int i;
    int sum = 0;
    int count;
    for (i = 0; i < 9; i++) {
        sum += un_80304B94(i);
    }
    count = 0;
    for (i = 0; i < 0x125; i++) {
        if (un_803048C0(i)) {
            count++;
        }
    }
    if (sum == count) {
        return 1;
    } else {
        return 0;
    }
}

bool un_803045A0(void)
{
    struct idk sp = un_803B87A8;
    unsigned int i;
    unsigned int count = 0;
    for (i = 0; i < 26; i++) {
        if (un_803048C0(sp.idk[i])) {
            count++;
        }
    }
    if (count == 26) {
        return 1;
    } else {
        return 0;
    }
}

bool un_80304690(void)
{
    struct idk sp = un_803B87DC;
    unsigned int i;
    unsigned int count = 0;
    for (i = 0; i < 26; i++) {
        if (un_803048C0(sp.idk[i])) {
            count++;
        }
    }
    if (count == 26) {
        return 1;
    } else {
        return 0;
    }
}

bool un_80304780(void)
{
    struct idk sp = un_803B8810;
    unsigned int i;
    unsigned int count = 0;
    for (i = 0; i < 26; i++) {
        if (un_803048C0(sp.idk[i])) {
            count++;
        }
    }
    if (count == 26) {
        return 1;
    } else {
        return 0;
    }
}

int un_80304870(void)
{
    if (gm_8016B498() || gm_801A4310() == 12) {
        return (short) un_804A284C[0x258 / 2];
    } else {
        return *gmMainLib_8015CC90();
    }
}

inline static unsigned short* idk(void)
{
    if (gm_8016B498() || gm_801A4310() == 12) {
        return &un_804A284C[5];
    } else {
        return gmMainLib_8015CC78();
    }
}

bool un_803048C0(int arg0)
{
    return idk()[arg0] & 0xFF;
}

bool un_80304924(int arg0)
{
    return idk()[arg0] & 0x8000;
}

void un_80304988(int arg0)
{
    unsigned short* v = idk();
    v[arg0] = v[arg0] ^ 0x8000;
}

bool un_803049F4(int arg0)
{
    return idk()[arg0] & 0x4000;
}

void un_80304A58(int arg0)
{
    unsigned short* v = idk();
    if (un_803049F4(arg0)) {
        v[arg0] = v[arg0] ^ 0x4000;
    }
}

bool un_80304B0C(int arg0)
{
    unsigned short* v;
    unsigned short s;
    if (gm_8016B498() || gm_801A4310() == 12) {
        s = un_804A284C[3] | un_804A284C[4];
        v = &s;
    } else {
        v = gmMainLib_8015CC84();
    }
    if (*v & (1 << arg0)) {
        return 1;
    } else {
        return 0;
    }
}

int un_80304B94(int option)
{
    int res;
    switch (option) {
    case 0:
        if (lbLang_IsSettingJP()) {
            res = 0x4;
        } else {
            res = 0x4;
        }
        break;
    case 1:
        if (lbLang_IsSettingJP()) {
            res = 0xA;
        } else {
            res = 0xA;
        }
        break;
    case 2:
        if (lbLang_IsSettingJP()) {
            res = 0x11;
        } else {
            res = 0x10;
        }
        break;
    case 3:
        if (lbLang_IsSettingJP()) {
            res = 0x17;
        } else {
            res = 0x17;
        }
        break;
    case 4:
        if (lbLang_IsSettingJP()) {
            res = 0xC;
        } else {
            res = 0xC;
        }
        break;
    case 5:
        if (lbLang_IsSettingJP()) {
            res = 0x48;
        } else {
            res = 0x48;
        }
        break;
    case 6:
        if (lbLang_IsSettingJP()) {
            res = 0x1B;
        } else {
            res = 0x1B;
        }
        break;
    case 7:
        if (lbLang_IsSettingJP()) {
            res = 0x7E;
        } else {
            res = 0x7E;
        }
        break;
    case 8:
        if (lbLang_IsSettingJP()) {
            res = 0x2;
        } else {
            res = 0x2;
        }
        break;
    }
    return res;
}

bool un_80304CC8(int arg0)
{
    short* v = un_804D6EB4;
    if (lbLang_IsSettingUS()) {
        for (; *v != -1; v++) {
            if (*v == arg0) {
                return 0;
            }
        }
    }
    return 1;
}

int un_80304D30(void)
{
    int i;
    int x;
    int count;
    int count2;
    int idk;
    int* qwe;
    int sp14[36 / 4];
    if (un_80304470()) {
        return 0;
    }
    memzero(sp14, 36);
    count = 0;
    for (i = 0; i < 0x125; i++) {
        if (un_80304CC8(i)) {
            if (un_803048C0(i)) {
                x = un_803060BC(i, 6);
                sp14[x]++;
                if (x != 8 && x != 1) {
                    count++;
                }
            }
        }
    }

    idk = 6;
    qwe = sp14;
    while (idk != 0) {
        if (idk <= (unsigned int) 2 || *qwe == 0 || *qwe != un_80304B94(idk)) {
            break;
        }
        for (i = 0; i < idk; i++) {
            if (1 < (unsigned int) idk && idk != 3) {
                if (!un_80304B0C(idk)) {
                    un_804A284C[0] = 2;
                    un_80305918(idk, 0, 0);
                }
            }
        }
        i = idk + 1;
        while (un_80304B94(i) == 0) {
            i++;
        }
        if (4 <= idk && idk <= 6) {
            if (!un_80304B0C(idk)) {
                un_804A284C[0] = 2;
                un_80305918(idk, 0, 0);
                break;
            }
        }
        idk--;
        qwe--;
    }

    count2 = 0;
    for (i = 0; i < 8; i++) {
        if (x != 8 && x != 1) {
            if (un_80304B0C(i)) {
                count2 += un_80304B94(i);
            }
        }
    }
    return count2 - count;
}

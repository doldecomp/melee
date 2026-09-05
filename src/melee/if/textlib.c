#include "textlib.h"

#include <Runtime/platform.h>

#include "textdraw.h"
#include "types.h"
#include <melee/lb/lb_00B0.h>

#include <printf.h> // IWYU pragma: keep
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sysdolphin/baselib/debug.h>

struct unk_series {
    s16 values[26];
};

/// ?
/* 4D6E18 */ extern DevText* devtext_drawlist;
/* 4D6E38 */ extern DevText* devtext_poolhead;
/* 4DDC88 */ extern GXColor un_804DDC88;

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
    static GXColor const cyan = { 0x60, 0xD0, 0xB0, 0x70 };
    DevText* text;
    UNUSED u32 pad;
    GXColor bg = cyan;
    PAD_STACK(0x14);

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
        HSD_ASSERTREPORT(309, 0, "TW : Screen alloc Fail\n");
    }
    if (text != NULL) {
        static GXColor const white = { 0xFF, 0xFF, 0xFF, 0xFF };
        static GXColor const red = { 0xFF, 0x80, 0x80, 0xFF };
        static GXColor const green = { 0x80, 0xFF, 0x80, 0xFF };
        static GXColor const blue = { 0x80, 0x80, 0xFF, 0xFF };
        text->x = x;
        text->y = y;
        text->w = w;
        text->h = h;
        text->cursor_x = 0;
        text->cursor_y = 0;
        text->scale_x = 10.0f;
        text->scale_y = 16.0f;
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

static inline int DevText_Clamp(int val, int max)
{
    if (max <= val) {
        return max - 1;
    } else if (val < 0) {
        return 0;
    } else {
        return val;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void DevText_SetCursorXY(DevText* text, int x, int y)
{
    if (text->w <= x) {
        x = text->w - 1;
    } else if (x < 0) {
        x = 0;
    }
    text->cursor_x = x;
    if (text->h <= y) {
        y = text->h - 1;
    } else if (y < 0) {
        y = 0;
    }
    text->cursor_y = y;
}
#ifdef MUST_MATCH
#pragma pop
#endif

void DevText_SetCursorX(DevText* text, int x)
{
    text->cursor_x = DevText_Clamp(x, text->w);
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void DevText_HideCursor(DevText* text)
{
    text->flags &= ~(1 << 4);
}
#ifdef MUST_MATCH
#pragma pop
#endif

void DevText_80302AC0(DevText* text)
{
    text->flags |= (1 << 5);
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void DevText_ShowBackground(DevText* text)
{
    text->flags &= ~(1 << 6);
}
#ifdef MUST_MATCH
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void DevText_HideBackground(DevText* text)
{
    text->flags |= (1 << 6);
}
#ifdef MUST_MATCH
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void DevText_ShowText(DevText* text)
{
    text->flags &= ~(1 << 7);
}
#ifdef MUST_MATCH
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void DevText_HideText(DevText* text)
{
    text->flags |= (1 << 7);
}
#ifdef MUST_MATCH
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void DevText_SetScale(DevText* text, f32 x, f32 y)
{
    text->scale_x = x;
    text->scale_y = y;
}
#ifdef MUST_MATCH
#pragma pop
#endif

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

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
u8 DevText_StoreColorIndex(DevText* text, u8 index)
{
    u8 old = text->current_color;
    text->current_color = index;
    return old;
}
#ifdef MUST_MATCH
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
GXColor DevText_SetTextColor(DevText* text, GXColor color)
{
    int index = text->current_color;
    GXColor old = text->text_colors[index];
    text->text_colors[index] = color;
    return old;
}
#ifdef MUST_MATCH
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
GXColor DevText_SetBGColor(DevText* text, GXColor color)
{
    GXColor old = text->bg_color;
    text->bg_color = color;
    return old;
}
#ifdef MUST_MATCH
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void DevText_Erase(DevText* text)
{
    memzero(text->buf, 2 * text->w * text->h);
}
#ifdef MUST_MATCH
#pragma pop
#endif

static inline void DevText_AdvanceLine(DevText* text)
{
    text->cursor_x = 0;
    if (text->cursor_y < text->h - 1) {
        text->cursor_y++;
    } else {
        DevText_EraseFirstLine(text);
    }
}

typedef struct DevTextGlyph {
    u8 chr;
    u8 color : 2;
    u8 unk : 6;
} DevTextGlyph;

void DevText_Print(DevText* text, char* str)
{
    char* cur;
    if (str != NULL) {
        cur = str;
        while (*cur) {
            if (*cur != '\n') {
                int index = text->cursor_x + text->cursor_y * text->w;
                ((DevTextGlyph*) text->buf)[index].chr = *cur;
                ((DevTextGlyph*) text->buf)[index].color = text->current_color;
                if (text->cursor_x < text->w - 1) {
                    text->cursor_x++;
                } else if ((text->flags & DEVTEXT_FLAG_NOWRAP) == 0) {
                    DevText_AdvanceLine(text);
                }
            } else {
                DevText_AdvanceLine(text);
            }
            cur++;
        }
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void DevText_PrintInt(DevText* text, int num)
{
    char str[16];
    DevText_NumToStr(num, str);
    DevText_Print(text, str);
}
#ifdef MUST_MATCH
#pragma pop
#endif

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

void un_80302DF8(struct un_80304138_objalloc_t* arg0, soundtest_callback arg1)
{
    arg0->xC = arg1;
}

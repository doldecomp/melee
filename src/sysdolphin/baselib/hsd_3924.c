#include "hsd_3924.h"

#include "hsd_3915.h"
#include "list.h"
#include "memory.h"

#include <placeholder.h>

#include <string.h>
#include <dolphin/gx.h>

// .sbss
/* 4D7850 */ static HSD_SList* hsd_804D7850;

void hsd_80392474(void)
{
    hsd_804D7850 = NULL;
}

struct EventPriority {
    Event event;
    int priority;
};

HSD_SList* fn_80392480(Event event, int priority)
{
    HSD_SList* prev = NULL;
    HSD_SList* cur = hsd_804D7850;

    goto loop_5;
block_1: {
    HSD_SList* ret = cur->data;
    if (event != (Event) ret->next) {
        if (((struct EventPriority*) ret)->priority <= priority) {
            prev = cur;
        }
        cur = cur->next;
    loop_5:
        if (cur != NULL) {
            goto block_1;
        }
        {
            struct EventPriority* data =
                HSD_MemAlloc(sizeof(struct EventPriority));
            data->event = event;
            data->priority = priority;
            if (prev != NULL) {
                return HSD_SListAllocAndAppend(prev, data);
            }
            ret = HSD_SListAllocAndPrepend(hsd_804D7850, data);
        }
        hsd_804D7850 = ret;
    }
    return ret;
}
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void hsd_80392528(Event event)
{
    fn_80392480(event, 0x80);
}
#ifdef MUST_MATCH
#pragma pop
#endif

typedef struct {
    s32 count;
    GXColor color;
} DispBar;

typedef struct _DispItem {
    /* 0x00 */ struct _DispItem* next;
    /* 0x04 */ s32 type;
    /* 0x08 */ union {
        char text[128];
        DispBar bars[1];
        u8 gradient[8];
    } content;
} DispItem;

typedef DispItem* (*DispCallback)(void*);

static inline s32 count_bar_units(DispItem* item)
{
    s32 total = 0;
    s32 count;

    while ((count = item->content.bars[0].count) > 0) {
        total += count;
        item = (DispItem*) ((DispBar*) item + 1);
    }
    return total;
}

static inline s32 count_text_chars(char* text)
{
    s32 count;
    s32 i;
    s32 len;

    if (text == NULL) {
        return 0;
    }
    count = 0;
    len = strlen(text);
    i = count;
    while (i < len) {
        if ((s8) text[i] != '\\') {
            count++;
        } else {
            i++;
            switch ((s8) text[i]) {
            case 'c':
            case 'C':
                i += 6;
                break;
            }
        }
        i++;
    }
    return count;
}

static const GXColor hsd_3915_default_color = { 0xFF, 0xFF, 0xFF, 0xFF };

void hsd_8039254C(void)
{
    static GXColor lbl_804D6080 = { 0x40, 0x40, 0x40 };
    f32 line;
    f32 bar_y;
    f32 bar_x;
    f32 t2;
    GXColor default_col;
    DispItem* bar_draw_ptr;
    s32 char_count;
    s32 count;
    GXColor* p_bg_col0;
    GXColor* p_bg_col1;
    GXColor* p_txt_col;
    GXColor* p_bg_col2;
    GXColor* p_bg_col3;
    GXColor* p_bar_col;
    s32 col_pos;
    s32 first;
    HSD_SList* event_node;

    PAD_STACK(4);

    col_pos = 60;
    first = 1;
    line = 1.0F;
    event_node = hsd_804D7850;
    default_col = hsd_3915_default_color;

    while (event_node != NULL) {
        DispItem* item;
        DispCallback cb;
        cb = (DispCallback) ((void**) event_node->data)[0];
        item = cb(event_node->data);

        while (item != NULL) {
            if (first) {
                GXColor bg_col0;
                p_bg_col0 = &bg_col0;
                if (lbl_804D6080.a != 0) {
                    hsd_80391A04(10.0F, 10.0F, 6);
                    bg_col0 = lbl_804D6080;
                    DrawRectangle(-10.0F, 5.0F, 620.0F, 10.0F, p_bg_col0);
                }
                first = 0;
            }
            switch (item->type) {
            case 0: {
                GXColor bg_col1;
                GXColor txt_col;
                p_bg_col1 = &bg_col1;
                p_txt_col = &txt_col;
                char_count = count_text_chars(item->content.text);
                if (col_pos + char_count > 60) {
                    line -= 1.0F;
                    col_pos = 0;
                    if (lbl_804D6080.a != 0) {
                        bg_col1 = lbl_804D6080;
                        DrawRectangle(-10.0F, (10.0F * line) - 5.0F, 620.0F,
                                      10.0F, p_bg_col1);
                    }
                }
                hsd_80391A04(10.0F, 10.0F, 6);
                txt_col = default_col;
                hsd_80391AC8(item->content.text, p_txt_col,
                             (f32) (col_pos * 10), 10.0F * line);
                col_pos += char_count + 2;
                break;
            }
            case 2: {
                GXColor bg_col2;
                p_bg_col2 = &bg_col2;
                if (col_pos != 0) {
                    line -= 0.5;
                    if (lbl_804D6080.a != 0) {
                        bg_col2 = lbl_804D6080;
                        DrawRectangle(-10.0F, (10.0F * line) - 5.0F, 620.0F,
                                      5.0F, p_bg_col2);
                    }
                }
                hsd_80391A04(10.0F, 10.0F, 24);
                t2 = (10.0F * line) + 2.0F;
                hsd_80391E18(item->content.gradient, 0.0F, t2, 600.0F, t2);
                col_pos = 60;
                break;
            }
            case 1: {
                GXColor bg_col3;
                GXColor bar_col;
                p_bar_col = &bar_col;
                p_bg_col3 = &bg_col3;
                char_count = count_bar_units(item);
                if (char_count > 0) {
                    if (col_pos != 0) {
                        line -= 0.5;
                        if (lbl_804D6080.a != 0) {
                            bg_col3 = lbl_804D6080;
                            DrawRectangle(-10.0F, (10.0F * line) - 5.0F,
                                          620.0F, 5.0F, p_bg_col3);
                        }
                    }
                    hsd_80391A04(10.0F, 10.0F, 12);
                    bar_y = (10.0F * line) + 2.0F;
                    bar_x = 0.0F;
                    bar_draw_ptr = item;
                    while ((count = bar_draw_ptr->content.bars[0].count) > 0) {
                        f32 prev_x;
                        prev_x = bar_x;
                        bar_x += (600.0F / (f32) char_count) * (f32) count;
                        bar_col = bar_draw_ptr->content.bars[0].color;
                        hsd_80391F28(
                            p_bar_col, prev_x, bar_y, bar_x, bar_y,
                            (f32) bar_draw_ptr->content.bars[0].count);
                        bar_draw_ptr =
                            (DispItem*) ((DispBar*) bar_draw_ptr + 1);
                    }
                    col_pos = 60;
                }
                break;
            }
            }
            item = item->next;
        }
        event_node = event_node->next;
    }
}

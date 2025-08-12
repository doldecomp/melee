#include "baselib/forward.h"

#include "baselib/jobj.h"
#include "baselib/wobj.h"

#include "un/forward.h"

#include "un/types.h"
#include "un/un_2FC9.h"

#include <printf.h>
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
#include <MSL/stdio.h>
#include <MSL/string.h>

// .data
/* 3FDC20 */ static HSD_WObjDesc devtext_eyepos = {
    NULL, { 0.0f, 40.241424560546875f, 300.2409973144531f }, NULL
};
/* 3FDC34 */ static HSD_WObjDesc devtext_interest = { NULL,
                                                      { 0.0f, 10.0f, 0.0f },
                                                      NULL };
/* 3FDC48 */ static HSD_CameraDescPerspective devtext_CObjDesc = {
    NULL,
    0,
    1,
    0,
    640,
    0,
    480,
    0,
    640,
    0,
    480,
    &devtext_eyepos,
    &devtext_interest,
    0,
    NULL,
    0.1f,
    32768.0f,
    30.0f,
    1.3636000156402588f,
};

// .bss
/* 4A1FD8 */ static DevText devtext_pool[32];

// .sbss
/* 4D6E18 */ static DevText* devtext_drawlist;
/* 4D6E1C */ static HSD_GObj* devtext_gobj;
/* 4D6E20 */ static HSD_CObj* devtext_cobj;
/* 4D6E24 */ static int devtext_setup_classifier;
/* 4D6E28 */ static int devtext_setup_p_link;
/* 4D6E2C */ static int devtext_setup_priority;
/* 4D6E30 */ static int devtext_setup_gx_link;
/* 4D6E34 */ static int devtext_setup_render_priority;
/* 4D6E38 */ static DevText* devtext_poolhead;

int DevText_StrLen(char* str)
{
    if (str) {
        int length = 0;
        while (*str++) {
            length++;
        }
        return length;
    }
    return 0;
}

void DevText_NumToStr(int num, char* str)
{
    int length = 0;
    int i;
    char* strEnd;

    if (num < 0) {
        *str = '-';
        num = -num;
        str++;
    }

    strEnd = str;
    do {
        *strEnd = (num % 10) + '0';
        num = num / 10;
        strEnd++;
        length++;
    } while (num != 0);
    *strEnd = '\0';
    strEnd--;
    length >>= 1;

    for (i = 0; i != length; i++) {
        char temp = *str;
        *str = *strEnd;
        *strEnd = temp;
        strEnd--;
        str++;
    }
}

HSD_GObj* DevText_GetGObj(void)
{
    return devtext_gobj;
}

void DevText_InitPool(void)
{
    DevText* text = devtext_pool;
    int i;
    devtext_pool[0].prev = NULL;
    for (i = 0; i < 31; i++) {
        devtext_pool[i + 1].prev = &devtext_pool[i];
        devtext_pool[i].next = &devtext_pool[i + 1];
    }
    devtext_pool[31].next = NULL;
    devtext_poolhead = devtext_pool;
    devtext_drawlist = NULL;
}

void DevText_Remove(DevText** ptext)
{
    DevText* text = *ptext;
    if (text->next) {
        text->next->prev = text->prev;
    }
    text = *ptext;
    if (text->prev) {
        text->prev->next = text->next;
    } else {
        if (text->next) {
            *ptext = text->next;
        } else {
            *ptext = NULL;
        }
    }
    text->next = devtext_poolhead;
    text->prev = NULL;
    devtext_poolhead = text;
}

void DevText_SetupCObj(void)
{
    if (devtext_cobj == NULL) {
        HSD_RectS16 viewport;
        Scissor scissor;
        Vec3 eyepos = { 0, 0, 1 };
        Vec3 interest = { 0, 0, 0 };
        float roll = 0;
        float near = 0;
        float far = 2;
        float top = -20;
        float bottom = 500;
        float left = -20;
        float right = 660;

        viewport.xmin = 0;
        viewport.xmax = 640;
        viewport.ymin = 0;
        viewport.ymax = 480;

        scissor.left = 0;
        scissor.right = 640;
        scissor.top = 0;
        scissor.bottom = 480;

        devtext_cobj = HSD_CObjAlloc();
        HSD_CObjSetProjectionType(devtext_cobj, 3);
        HSD_CObjSetViewport(devtext_cobj, &viewport);
        HSD_CObjSetScissor(devtext_cobj, &scissor);
        HSD_CObjSetEyePosition(devtext_cobj, &eyepos);
        HSD_CObjSetInterest(devtext_cobj, &interest);
        HSD_CObjSetRoll(devtext_cobj, roll);
        HSD_CObjSetNear(devtext_cobj, near);
        HSD_CObjSetFar(devtext_cobj, far);
        HSD_CObjSetOrtho(devtext_cobj, top, bottom, left, right);
    }
    HSD_CObjSetCurrent(devtext_cobj);
}

void DevText_Draw(DevText* text)
{
    hsd_80391A04(text->scale_x, text->scale_y, text->line_width);
    if ((text->flags & DEVTEXT_FLAG_HIDEBACKGROUND) == 0) {
        DrawRectangle(text->x - 8, text->y - 8, text->scale_x * text->w + 8,
                      text->scale_y * text->h + 8, &text->bg_color);
        DrawRectangle(text->x - 4, text->y - 4, text->scale_x * text->w + 4,
                      text->scale_y * text->h + 4, &text->bg_color);
    }
    if ((text->flags & DEVTEXT_FLAG_HIDETEXT) == 0) {
        int row = 0;
        int y = text->y;
        while (row < text->h) {
            int col = 0;
            int x = text->x;
            while (col < text->w) {
                int index = (col + text->w * row) * 2;
                int chr = text->buf[index];
                if (chr) {
                    GXColor* color =
                        &text->text_colors[text->buf[index + 1] >> 6];
                    DrawASCII(chr, x, y, color);
                }
                x += text->scale_x;
                col++;
            }
            y += text->scale_y;
            row++;
        }
    }
    if ((text->flags & DEVTEXT_FLAG_SHOWCURSOR) == 1) {
        text->unk++;
        if (text->unk < 17) {
            if (8 < text->unk) {
                GXColor color = { 0xFF, 0xFF, 0xFF, 0xC0 };
                DrawRectangle(text->x + text->scale_x * text->cursor_x,
                              text->y + text->scale_y * text->cursor_y,
                              text->scale_x, text->scale_y, &color);
            }
        } else {
            text->unk = 0;
        }
    }
}

void DevText_DrawAll(HSD_GObj* gobj, int pass)
{
    PAD_STACK(8);

    if ((unsigned int) pass == HSD_RP_BOTTOMHALF) {
        DevText* text = devtext_drawlist;
        HSD_FogSet(NULL);
        DevText_SetupCObj();
        while (text) {
            DevText_Draw(text);
            text = text->next;
        }
    }
}

void DevText_CreateCObj(int classifier, int p_link, int gobj_priority,
                        int gx_link, u8 gx_priority)
{
    HSD_GObj* gobj = GObj_Create(classifier, p_link, gobj_priority);
    if (gobj) {
        HSD_CObj* cobj = HSD_CObjLoadDesc((HSD_CObjDesc*) &devtext_CObjDesc);
        if (cobj) {
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
            GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, gx_priority);
            gobj->gxlink_prios = 1LL << gx_link;
        } else {
            HSD_GObjPLink_80390228(gobj);
        }
    }
}

HSD_GObj* DevText_Setup(int classifier, int p_link, int priority, int gx_link,
                        int render_priority, u8 camera_priority)
{
    HSD_GObj* gobj;

    devtext_setup_classifier = classifier;
    devtext_setup_p_link = p_link;
    devtext_setup_priority = priority;
    devtext_setup_gx_link = gx_link;
    devtext_setup_render_priority = render_priority;
    devtext_cobj = NULL;

    DevText_CreateCObj(classifier, p_link, priority, gx_link, camera_priority);
    DevText_InitPool();
    gobj = GObj_Create(devtext_setup_classifier, devtext_setup_p_link,
                       devtext_setup_priority);
    if (gobj) {
        GObj_SetupGXLink(gobj, DevText_DrawAll, devtext_setup_gx_link,
                         devtext_setup_render_priority);
    }
    devtext_gobj = gobj;
    return devtext_gobj;
}

void DevText_AddToList(DevText** list, DevText* text)
{
    if (*list) {
        DevText* next = *list;
        DevText* prev = NULL;

        while (next) {
            if (text->id >= next->id) {
                prev = next;
                next = next->next;
            } else {
                break;
            }
        }

        text->next = next;
        // next->prev = text;

        if (prev) {
            prev->next = text;
            text->prev = prev;
        } else {
            text->prev = NULL;
            *list = text;
        }
    } else {
        *list = text;
    }
}

void DevText_Show(HSD_GObj* gobj, DevText* text)
{
    DevText_AddToList(&devtext_drawlist, text);
}

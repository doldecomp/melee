#include "un/forward.h"

#include "un_2FC9.static.h"

#include "lb/lb_00B0.h"
#include "un/types.h"
#include "un/un_2FC9.h"

#include <stdarg.h>
#include <dolphin/mtx/types.h>
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjuserdata.h>
#include <baselib/particle.h>
#include <MSL/stdio.h>
#include <MSL/string.h>

/// #un_802FC9B4

/// #fn_802FCAA4

/// #fn_802FCAC4

/// #un_802FCBA0

/// #fn_802FCC44

/// #un_802FCF38

/// #un_802FD28C

/// #un_802FD404

/// #un_802FD428

void un_802FD450(void)
{
    un_804D6D6C = 1;
}

void un_802FD45C(void)
{
    un_804D6D6C = 0;
}

/// #un_802FD468

/// #un_802FD4C8

/// #un_802FD604

void un_802FD65C(void)
{
    un_804D6D88 = 0;
}

void un_802FD668(void)
{
    un_804D6D8C = 1;
}

void un_802FD674(void)
{
    un_804D6D8C = 0;
}

/// #fn_802FD680

/// #fn_802FD6CC

void un_802FD704(void) {}

/// #un_802FD708

/// #un_802FD8A0

/// #un_802FD8C4

/// #un_802FD8E8

void un_802FD90C(void) {}

void un_802FD910(void)
{
    un_804D6D90.x = 1;
}

void un_802FD91C(void)
{
    un_804D6D90.x = 0;
}

/// #un_802FD928

/// #un_802FD9D8

/// #fn_802FDA4C

/// #fn_802FDA78

/// #un_802FE260

/// #un_802FE390

/// #un_802FE3F8

/// #fn_802FE470

/// #un_802FE6A8

/// #un_802FE8CC

/// #un_802FE918

/// #un_802FEBE0

void un_802FED10(void) {}

/// #fn_802FED14

/// #un_802FEFAC

/// #un_802FF128

/// #un_802FF190

/// #un_802FF1B4

/// #fn_802FF218

void fn_802FF360(void) {}

/// #un_802FF364

/// #un_802FF498

/// #un_802FF4FC

/// #un_802FF570

/// #un_802FF620

/// #un_802FF6A0

/// #un_802FF710

/// #un_802FF78C

/// #un_802FF7DC

bool un_802FF884(void)
{
    return false;
}

/// #un_802FF88C

/// #un_802FF934

/// #un_802FF958

/// #un_802FF99C

/// #un_802FF9DC

/// #un_802FFB58

/// #un_802FFBAC

/// #un_802FFC30

/// #un_802FFC6C

bool fn_802FFCC8(void)
{
    return false;
}

/// #un_802FFCD0

/// #un_802FFD94

/// #fn_802FFE0C

/// #fn_802FFE6C

/// #un_802FFEA4

/// #un_802FFEE0

/// #un_802FFF2C

/// #un_803001DC

/// #un_80300218

/// #un_80300248

/// #un_80300290

/// #un_803002FC

/// #un_80300338

/// #un_80300378

/// #un_803003C4

/// #un_80300410

/// #un_80300480

/// #un_803004B4

/// #un_803004E8

/// #un_8030051C

/// #un_80300550

/// #un_80300584

/// #un_803005B8

/// #un_803005EC

/// #un_80300620

/// #un_80300654

/// #un_80300688

/// #un_803006BC

/// #un_803006F0

/// #un_80300724

/// #un_80300758

/// #un_80300790

/// #un_803007C8

/// #un_803007FC

/// #un_80300830

/// #un_80300864

/// #un_80300898

/// #un_803008CC

/// #un_80300900

/// #un_80300934

/// #un_80300968

/// #un_803009A4

/// #un_803009E0

/// #un_80300A88

/// #un_80300AB8

/// #un_80300AF4

/// #un_80300B58

/// #un_80300BBC

/// #un_80300BF8

/// #un_80300C3C

/// #un_80300C80

/// #fn_80300CC8

/// #un_80300D78

/// #fn_80300DE0

/// #un_80300E74

/// #fn_80300ED0

/// #un_80300F3C

/// #un_80300F98

/// #un_80300FEC

/// #un_80301028

/// #un_80301074

/// #un_803010C0

/// #fn_8030110C

/// #fn_803011EC

/// #un_80301280

/// #un_803012D4

/// #un_80301328

/// #un_8030136C

/// #un_803013B0

/// #un_803013EC

/// #un_80301420

/// #un_80301454

/// #un_80301490

/// #un_803014CC

/// #un_80301508

/// #un_80301544

/// #un_80301580

/// #un_803015BC

/// #un_803015F8

/// #un_80301634

/// #un_803016D8

/// #un_80301734

/// #un_8030178C

/// #un_80301800

/// #un_80301840

/// #un_803018BC

/// #un_8030191C

/// #un_80301964

/// #un_80301A64

/// #un_80301AD4

/// #un_80301B48

/// #un_80301BA8

/// #un_80301C64

/// #un_80301C80

/// #un_80301CE0

/// #un_80301D40

/// #un_80301D7C

/// #un_80301DCC

/// #un_80301E08

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

    for (i = 0; i != length / 2; i++) {
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
    devtext_drawlist = NULL;
    devtext_poolhead = devtext_pool;
}

void fn_803020F8(void) {}

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
        HSD_CObj* cobj = HSD_CObjLoadDesc(&devtext_CObjDesc);
        if (cobj) {
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B[0], cobj);
            GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, gx_priority);
            gobj->gxlink_prios = 1LL << gx_link;
        } else {
            HSD_GObjPLink_80390228(gobj);
        }
    }
}

#pragma push
#pragma dont_inline on
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
#pragma pop

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

/// #DevText_Create

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

GXColor DevText_SetTextColor(DevText* text, GXColor* color)
{
    int index = text->current_color;
    GXColor old = text->text_colors[index];
    text->text_colors[index] = *color;
    return old;
}

GXColor DevText_SetBGColor(DevText* text, GXColor* color)
{
    GXColor old = text->bg_color;
    text->bg_color = *color;
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
    vsprintf(str, format, args);
    va_end(args);
    DevText_Print(text, str);
}

UNK_T un_80302DF0(void)
{
    return un_804D6E44;
}

void un_80302DF8(un_80302DF8_t* arg0, int arg1)
{
    arg0->xC = arg1;
}

/// #un_80302E00

/// #un_80302EA4

/// #un_80302FFC

/// #un_80303444

/// #un_80303720

/// #un_803039A4

/// #un_80303AC4

/// #fn_80303EF4

/// #un_80303FD4

/// #un_80304138

/// #un_80304168

/// #un_80304210

void un_80304334(un_80304334_t* arg0)
{
    arg0->x1 |= (1 << 7);
}

/// #un_80304344

/// #un_80304470

/// #un_80304510

/// #un_803045A0

/// #un_80304690

/// #un_80304780

/// #un_80304870

/// #un_803048C0

/// #un_80304924

/// #un_80304988

/// #un_803049F4

/// #un_80304A58

/// #un_80304B0C

/// #un_80304B94

/// #un_80304CC8

/// #un_80304D30

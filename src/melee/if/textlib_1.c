#include "platform.h"
#include "textlib.h"

#include "baselib/controller.h"
#include "if/textdraw.h"
#include "if/types.h"
#include "mn/inlines.h"
#include "ty/toy.h"

#include <printf.h> // IWYU pragma: keep
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>

/* 4D6E4C */ unsigned char un_804D6E4C;
/* 4D6E48 */ struct un_80304138_objalloc_t_x8* un_804D6E48;
/* 4D6E44 */ struct un_80304138_objalloc_t* un_804D6E44;
/* 4D6E40 */ struct un_80304138_objalloc_t* un_804D6E40;
/* 4A2688 */ static HSD_ObjAllocData un_804A2688;

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
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
#ifdef MUST_MATCH
#pragma pop
#endif

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

static inline int un_80302FFC_maxlen(struct un_80304138_objalloc_t_x8* thing)
{
    int cursor_x = 1;
    for (; thing->x0 != 9; thing++) {
        if (thing->x0 != 0 && thing->x0 != 1) {
            int len = DevText_StrLen(thing->x8);
            if (len + 1 > cursor_x) {
                cursor_x = len + 1;
            }
        }
    }
    return cursor_x;
}

GXColor un_804D5A08 = { 0x40, 0x50, 0x80, 0x80 };
GXColor un_804D5A0C = { 0xE2, 0xE2, 0xE2, 0xFF };
GXColor un_804D5A10 = { 0xFF, 0x80, 0x20, 0xFF };
GXColor un_804D5A14 = { 0xA0, 0xA0, 0xFF, 0xFF };

void un_80302FFC(struct un_80304138_objalloc_t* arg0)
{
    struct un_80304138_objalloc_t_x8* x8 = arg0->x8;
    int cursor_x = un_80302FFC_maxlen(arg0->x8);
    int cursor_y;
    if (arg0->x1 & 0x10) {
        DevText_StoreColorIndex(arg0->x4, 0);
        DevText_SetTextColor(arg0->x4, adjust(un_804D5A0C));
        DevText_StoreColorIndex(arg0->x4, 1);
        DevText_SetTextColor(arg0->x4, adjust(un_804D5A10));
        DevText_StoreColorIndex(arg0->x4, 2);
        DevText_SetTextColor(arg0->x4, adjust(un_804D5A14));
        DevText_SetBGColor(arg0->x4, adjust(un_804D5A08));
    } else {
        DevText_StoreColorIndex(arg0->x4, 0);
        DevText_SetTextColor(arg0->x4, un_804D5A0C);
        DevText_StoreColorIndex(arg0->x4, 1);
        DevText_SetTextColor(arg0->x4, un_804D5A10);
        DevText_StoreColorIndex(arg0->x4, 2);
        DevText_SetTextColor(arg0->x4, un_804D5A14);
        DevText_SetBGColor(arg0->x4, un_804D5A08);
    }
    for (cursor_y = 0; cursor_y < arg0->x4->h; cursor_y++) {
        if (x8->x0 == 0) {
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
            DevText_Printf(arg0->x4, "%04x", *(u16*) x8->x10);
            break;
        case 7:
            DevText_Printf(arg0->x4, "%08x", *(int*) x8->x10);
            break;
        case 8:
            DevText_Printf(arg0->x4, "%3.2f", *(float*) x8->x10);
            break;
        }
        x8++;
    }
}

bool un_80303444(struct un_80304138_objalloc_t* arg0)
{
    bool ret = false;
    switch (arg0->x8[arg0->x0].x0) {
    case 2: {
        int* q = arg0->x8[arg0->x0].x10;
        if (*q < arg0->x8[arg0->x0].x18 - 1.0f) {
            *q += 1;
            ret = true;
            arg0->x1 = arg0->x1 | 1;
            sfxMove();
        }
        break;
    }
    case 3: {
        int* q = arg0->x8[arg0->x0].x10;
        if (*q + arg0->x8[arg0->x0].x1C <= arg0->x8[arg0->x0].x18) {
            ret = true;
            *q += arg0->x8[arg0->x0].x1C;
            arg0->x1 = arg0->x1 | 1;
            sfxMove();
        }
        break;
    }
    case 5: {
        unsigned char* q = arg0->x8[arg0->x0].x10;
        int idk = arg0->x8[arg0->x0].x1C;
        if (*q + (idk & 0xFF) <= 0xFF) {
            *q += idk;
        } else {
            *q -= 0x100 - idk;
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        sfxMove();
        break;
    }
    case 6: {
        u16* q = arg0->x8[arg0->x0].x10;
        int idk = arg0->x8[arg0->x0].x1C;
        if (*q + (idk & 0xFFFF) <= 0xFFFF) {
            *q += idk;
        } else {
            *q -= 0x10000 - idk;
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        sfxMove();
        break;
    }
    case 4:
    case 7: {
        unsigned int* q = arg0->x8[arg0->x0].x10;
        unsigned int idk = arg0->x8[arg0->x0].x1C;
        if (*q + (idk & 0xFFFFFFFF) <= 0xFFFFFFFF) {
            *q += idk;
        } else {
            *q -= (unsigned int) (0x100000000 - idk);
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        sfxMove();
        break;
    }
    case 8: {
        float* q = arg0->x8[arg0->x0].x10;
        if (*q + arg0->x8[arg0->x0].x1C <= arg0->x8[arg0->x0].x18) {
            *q += arg0->x8[arg0->x0].x1C;
            ret = true;
            arg0->x1 = arg0->x1 | 1;
            sfxMove();
        }
        break;
    }
    }
    return ret;
}

bool un_80303720(struct un_80304138_objalloc_t* arg0)
{
    bool ret = false;
    switch (arg0->x8[arg0->x0].x0) {
    case 2: {
        int* q = arg0->x8[arg0->x0].x10;
        if (*q > arg0->x8[arg0->x0].x14) {
            *q -= 1;
            ret = true;
            arg0->x1 = arg0->x1 | 1;
            sfxMove();
        }
        break;
    }
    case 3: {
        int* q = arg0->x8[arg0->x0].x10;
        if (*q - arg0->x8[arg0->x0].x1C >= arg0->x8[arg0->x0].x14) {
            ret = true;
            *q -= arg0->x8[arg0->x0].x1C;
            arg0->x1 = arg0->x1 | 1;
            sfxMove();
        }
        break;
    }
    case 5: {
        unsigned char* q = arg0->x8[arg0->x0].x10;
        int idk = arg0->x8[arg0->x0].x1C;
        if (*q - (idk & 0xFF) >= 0) {
            *q -= idk;
        } else {
            *q += 0x100 - idk;
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        sfxMove();
        break;
    }
    case 6: {
        u16* q = arg0->x8[arg0->x0].x10;
        int idk = arg0->x8[arg0->x0].x1C;
        if (*q - (idk & 0xFFFF) >= 0) {
            *q -= idk;
        } else {
            *q += 0x10000 - idk;
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        sfxMove();
        break;
    }
    case 4:
    case 7: {
        unsigned int* q = arg0->x8[arg0->x0].x10;
        unsigned int idk = arg0->x8[arg0->x0].x1C;
        if (*q - (idk & 0xFFFFFFFF) >= 0) {
            *q -= idk;
        } else {
            *q += (unsigned int) (0x100000000 - idk);
        }
        ret = true;
        arg0->x1 = arg0->x1 | 1;
        sfxMove();
        break;
    }
    case 8: {
        float* q = arg0->x8[arg0->x0].x10;
        if (*q - arg0->x8[arg0->x0].x1C >= arg0->x8[arg0->x0].x14) {
            *q -= arg0->x8[arg0->x0].x1C;
            ret = true;
            arg0->x1 = arg0->x1 | 1;
            sfxMove();
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
    PAD_STACK(8);
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
        u8 j = arg0->x0;
        int i = j;
        (void) j;
        for (i--; i >= 0; i--) {
            if (arg0->x8[i].x0 != 0) {
                (void) i;
                goto up_found;
            }
        }
        i = -1;
    up_found:
        if (i != -1) {
            arg0->x0 = i;
            arg0->x1 = arg0->x1 | 1;
            sfxMove();
        }
    } else if (buttons & (0x20000000 | HSD_PAD_X)) { // down
        u8 j = arg0->x0;
        int i = j;
        (void) j;
        for (i++; i < arg0->x4->h; i++) {
            if (arg0->x8[i].x0 != 0) {
                (void) i;
                goto down_found;
            }
        }
        i = -1;
    down_found:
        if (i != -1) {
            arg0->x0 = i;
            arg0->x1 = arg0->x1 | 1;
            sfxMove();
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

#line 828 "textlib.c"
static inline int un_80303FD4_first(struct un_80304138_objalloc_t_x8* p)
{
    int i;
    int v;
    for (i = 0; (v = p->x0) != 9; p++, i++) {
        if (v != 0) {
            return i;
        }
    }
    return 0;
}

#line 840 "textlib.c"
static inline int un_80303FD4_count(struct un_80304138_objalloc_t_x8* p)
{
    int n = 0;
    while (p->x0 != 9) {
        n++;
        p++;
    }
    return n;
}

#line 850 "textlib.c"
void un_80303FD4(HSD_GObj* arg0, struct un_80304138_objalloc_t* arg1,
                 struct un_80304138_objalloc_t_x8* arg2, int arg3, int arg4,
                 int arg5)
{
    struct un_80304138_objalloc_t_x8* p2;
    struct un_80304138_objalloc_t_x8* p;
    int i;
    int size;
    int count;
    int count2 = 0;
    int v;
    void* buf;
    struct un_80304138_objalloc_t* un;

    arg1->x8 = arg2;
    arg1->x1 = 0;
    arg1->prev = NULL;
    arg1->next = NULL;
    arg1->x10 = arg0;

    count = un_80303FD4_count(arg1->x8);
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
            arg1->x0 = un_80303FD4_first(arg1->x8);
            arg1->xC = NULL;
            DevText_HideCursor(arg1->x4);
            DevText_SetScale(arg1->x4, 10.0f, 17.0f);
            un_804D6E48 = NULL;
            p2 = arg1->x8;
            while (p2->x0 != 9) {
                un_80302E00(p2, 4);
                p2++;
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
            userdata->x14 = HSD_GObj_SetupProc(gobj2, fn_80303EF4, 0);
        }
    }
    return gobj2;
}

struct un_80304138_objalloc_t* un_80304210(struct un_80304138_objalloc_t* arg0,
                                           void* arg1, int arg2, int arg3,
                                           int arg4)
{
    struct un_80304138_objalloc_t* obj = HSD_ObjAlloc(&un_804A2688);
    if (obj != NULL) {
        DevText* text = arg0->x4;
        f32 x = text->scale_x * (f32) text->w;
        {
            s32 x_pos = (s32) ((f32) arg3 + x);
            s32 y_pos = (s32) (text->scale_y * (f32) arg0->x0 + (f32) arg4);
            un_80303FD4(arg0->x10, obj, arg1, arg2, text->x + x_pos,
                        text->y + y_pos);
        }
        arg0->x1 = arg0->x1 | 0x10;
        arg0->prev = obj;
        obj->next = arg0;
        obj->x1 = obj->x1 | 2;
    }
    return obj;
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
    soundtest_callback q;
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

bool un_80304470(void)
{
    int i;
    int sum = 0;
    int count;
    for (i = 0; i < 8; i++) {
        sum += Toy_80304B94(i);
    }
    count = 0;
    for (i = 0; i < TY_TROPHY_COUNT; i++) {
        if (i != 0xE6 && i != 0xC9 && Toy_803048C0(i)) {
            count++;
        }
    }
    if (sum <= count) {
        return 1;
    } else {
        return 0;
    }
}

bool un_80304510(void)
{
    int i;
    int sum = 0;
    int count;
    for (i = 0; i < 9; i++) {
        sum += Toy_80304B94(i);
    }
    count = 0;
    for (i = 0; i < TY_TROPHY_COUNT; i++) {
        if (Toy_803048C0(i)) {
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
    s16 sp[] = {
        0,  3,  6,  9,  12, 15, 18, 21, 24, 27, 30, 33, 36,
        39, 42, 45, 48, 51, 54, 57, 60, 63, 66, 69, 72, 75,
    };
    unsigned int i;
    unsigned int count = 0;
    for (i = 0; i < ARRAY_SIZE(sp); i++) {
        if (Toy_803048C0(sp[i])) {
            count++;
        }
    }
    if (count == ARRAY_SIZE(sp)) {
        return true;
    } else {
        return false;
    }
}

/// @todo Duplicate code of #un_803045A0 with different data
bool un_80304690(void)
{
    s16 sp[] = {
        1,  4,  7,  10, 13, 16, 19, 22, 25, 28, 31, 34, 37,
        40, 43, 46, 49, 52, 55, 58, 61, 64, 67, 70, 73, 76,
    };

    unsigned int i;
    unsigned int count = 0;
    for (i = 0; i < ARRAY_SIZE(sp); i++) {
        if (Toy_803048C0(sp[i])) {
            count++;
        }
    }
    if (count == ARRAY_SIZE(sp)) {
        return true;
    } else {
        return false;
    }
}

/// @todo Duplicate code of #un_803045A0 with different data
bool un_80304780(void)
{
    s16 sp[] = {
        2,  5,  8,  11, 14, 17, 20, 23, 26, 29, 32, 35, 38,
        41, 44, 47, 50, 53, 56, 59, 62, 65, 68, 71, 74, 77,
    };

    unsigned int i;
    unsigned int count = 0;
    for (i = 0; i < ARRAY_SIZE(sp); i++) {
        if (Toy_803048C0(sp[i])) {
            count++;
        }
    }
    if (count == ARRAY_SIZE(sp)) {
        return true;
    } else {
        return false;
    }
}

/**
 * @file lbbgflash.c
 * @brief Background flash effects for dramatic game events.
 *
 * Provides full-screen color overlay flashes triggered by various game events.
 * Called from game mode code (gmallstar.c, gmregclear.c, gm_1A7A.c, etc).
 */

#include "lbbgflash.h"

#include <placeholder.h>

#include "dolphin/gx/GXStruct.h"

#include <sysdolphin/baselib/wobj.h>

typedef struct BgFlashState {
    u8 active : 1;
    u8 mode : 7;
} BgFlashState;

typedef struct BgFlashData {
    /* 0x00 */ BgFlashState state;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ GXColor x4;
    /* 0x08 */ GXColor x8;
    /* 0x0C */ GXColor xC;
    /* 0x10 */ f32 x10[4];
    /* 0x20 */ f32 x20[4];
    /* 0x30 */ u8 x30;
    /* 0x31 */ u8 x31;
    /* 0x32 */ u8 x32;
    /* 0x33 */ u8 x33;
    /* 0x34 */ s32 x34;
    /* 0x38 */ s32 x38;
    /* 0x3C */ s32 x3C;
    /* 0x40 */ HSD_GObj* x40;
    /* 0x44 */ HSD_GObj* x44;
} BgFlashData;

BgFlashData lbl_80433658;

#include <dolphin/gx.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/hsd_3915.h>

static GXColor lbl_804D3840 = { 0, 0, 0, 255 };
static GXColor lbl_804D3844 = { 0, 0, 0, 0 };
static GXColor lbl_804D3848 = { 255, 255, 255, 255 };
static GXColor lbl_804D384C = { 0, 0, 0, 0 };

static HSD_WObjDesc lbl_803BB000 = {
    NULL,
    { 320.0f, -240.0f, 415.69220f },
};

static HSD_WObjDesc lbl_803BB014 = {
    NULL,
    { 320.0f, -240.0f, 0.0f },
};

HSD_CameraDescPerspective lbl_803BB028 = {
    NULL,
    0,
    PROJ_PERSPECTIVE,
    { 0, 640, 0, 480 },
    { 0, 640, 0, 480 },
    &lbl_803BB000,
    &lbl_803BB014,
    0.0f,
    NULL,
    0.1f,
    30000.0f,
    60.0f,
    1.3333333f,
};

void fn_8001FC08(void)
{
    // TODO: Un-unroll this somehow?
    // When I try it just stays a loop in the asm
    BgFlashData* data = &lbl_80433658;
    f32 val;
    f32 cur_val;
    f32* cur;
    u8 target;

    if (data->x20[0] > 0.0f) {
        cur_val = *(cur = &data->x10[0]);
        val = cur_val + data->x20[0];
        if (val < (f32) (target = data->x8.r)) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    } else {
        cur_val = *(cur = &data->x10[0]);
        val = cur_val + data->x20[0];
        if (val > (f32) (target = data->x8.r)) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    }

    if (data->x20[1] > 0.0f) {
        cur_val = *(cur = &data->x10[1]);
        val = cur_val + data->x20[1];
        if (val < (f32) (target = data->x8.g)) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    } else {
        cur_val = *(cur = &data->x10[1]);
        val = cur_val + data->x20[1];
        if (val > (f32) (target = data->x8.g)) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    }

    if (data->x20[2] > 0.0f) {
        cur_val = *(cur = &data->x10[2]);
        val = cur_val + data->x20[2];
        if (val < (f32) (target = data->x8.b)) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    } else {
        cur_val = *(cur = &data->x10[2]);
        val = cur_val + data->x20[2];
        if (val > (f32) (target = data->x8.b)) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    }

    if (data->x20[3] > 0.0f) {
        cur_val = *(cur = &data->x10[3]);
        val = cur_val + data->x20[3];
        if (val < (f32) (target = data->x8.a)) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    } else {
        cur_val = *(cur = &data->x10[3]);
        val = cur_val + data->x20[3];
        if (val > (f32) (target = data->x8.a)) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    }
}

/// @todo .sdata2 order hack: the signed int-to-float conversion constant,
/// with no signed conversion left in the TU to allocate it.
#ifdef MUST_MATCH
static void sdata2_order(void)
{
    (void) 4503601774854144.0;
}
#endif

void fn_8001FEC4(HSD_GObj* gobj, s32 code)
{
    BgFlashData* data = &lbl_80433658;
    s32 mode;
    s32 y;
    PAD_STACK(8);

    if (data->state.active) {
        return;
    }

    hsd_80391A04(1.0f, 1.0f, 1);
    mode = data->state.mode;

    if (mode == 5 || mode >= 5 || mode < 3) {
        u8 r;
        u8 g;
        u8 b;
        u8 a;

        a = data->xC.a;
        b = data->xC.b;
        g = data->xC.g;
        r = data->xC.r;

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2f32(0.0f, 0.0f);
        GXColor4u8(r, g, b, a);
        GXPosition2f32(640.0f, 0.0f);
        GXColor4u8(r, g, b, a);
        GXPosition2f32(640.0f, -480.0f);
        GXColor4u8(r, g, b, a);
        GXPosition2f32(0.0f, -480.0f);
        GXColor4u8(r, g, b, a);
        return;
    }

    if (data->x33 != 0) {
        if ((u32) mode == 3U) {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition2f32(0.0f, 0.0f);
            GXColor4u8(0, 0, 0, 0xFF);
            GXPosition2f32(640.0f, 0.0f);
            GXColor4u8(0, 0, 0, 0xFF);
            GXPosition2f32(640.0f, -480.0f);
            GXColor4u8(0, 0, 0, 0xFF);
            GXPosition2f32(0.0f, -480.0f);
            GXColor4u8(0, 0, 0, 0xFF);
        }
        return;
    }

    switch ((s32) data->x30) {
    case 0:
        if ((u32) mode == 3U) {
            y = 0;
            while (y <= data->x38) {
                if (y == data->x38) {
                    s32 width;
                    u8 strip_h;
                    s32 neg_y;
                    s32 neg_yh;

                    strip_h = data->x32;
                    width = data->x34;
                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    neg_y = -y;
                    neg_yh = -(y + strip_h);
                    GXPosition2f32(0.0f, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32((f32) width, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32((f32) width, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(0.0f, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                } else {
                    u8 strip_h = data->x32;
                    s32 neg_y;
                    s32 neg_yh;

                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    neg_y = -y;
                    neg_yh = -(y + strip_h);
                    GXPosition2f32(0.0f, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(640.0f, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(640.0f, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(0.0f, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                }
                y += data->x32;
            }
        } else {
            s32* pY;
            s32 y2;

            for (y2 = *(pY = &data->x38); y2 <= 0x1E0; y2 += data->x32) {
                s32 right;
                u8 strip_h;
                s32 x34;

                if (y2 == *pY) {
                    s32 neg_y;
                    s32 xr;
                    s32 neg_yh;

                    x34 = data->x34;
                    strip_h = data->x32;
                    right = 0x280;
                    right -= x34;
                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    neg_y = -y2;
                    xr = x34 + right;
                    neg_yh = -(y2 + strip_h);
                    GXPosition2f32((f32) x34, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32((f32) xr, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32((f32) xr, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32((f32) x34, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                } else {
                    s32 neg_y;
                    s32 neg_yh;

                    strip_h = data->x32;
                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    neg_y = -y2;
                    neg_yh = -(y2 + strip_h);
                    GXPosition2f32(0.0f, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(640.0f, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(640.0f, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(0.0f, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                }
                /* Keep strip_h live across both arms (required for match). */
                (void) strip_h;
            }
        }
        break;
    }
}

void fn_800204C8(void)
{
    BgFlashData* data = &lbl_80433658;
    s32 mode = data->state.mode;

    switch (mode) {
    case 0:
    case 1:
    case 2:
        fn_8001FC08();
        data->xC.r = data->x10[0];
        data->xC.g = data->x10[1];
        data->xC.b = data->x10[2];
        data->xC.a = data->x10[3];
        return;
    case 3:
    case 4:
        switch ((s32) data->x30) {
        case 0: {
            s32* pX;
            s32* pY;
            s32 i;

            pY = &data->x38;
            pX = &data->x34;

            for (i = 0; i < data->x3C; i++) {
                if (*pX < 0x280) {
                    *pX = *pX + data->x31;
                } else if (*pY < 0x1E0) {
                    *pY = *pY + data->x32;
                    *pX = 0;
                } else {
                    data->x33 = 1;
                    return;
                }
            }
            break;
        }
        }
        break;
    case 5:
    default:
        return;
    }
}

/// @brief Trigger background flash.
/// @param duration Flash duration in frames (minimum 1).
void lbBgFlash_800205F0(s32 duration)
{
    if (duration < 1) {
        duration = 1;
    }
    lbBgFlash_800206D4(&lbl_804D3848, &lbl_804D3840, duration);
    lbl_80433658.state.mode = 0;
}

/// @brief Trigger background flash.
/// @param count Flash duration in frames (minimum 1).
void lbBgFlash_8002063C(int count)
{
    if (count < 1) {
        count = 1;
    }
    lbBgFlash_800206D4(&lbl_804D3844, &lbl_804D3840, count);
    lbl_80433658.state.mode = 0;
}

void lbBgFlash_80020688(int count)
{
    if (count < 1) {
        count = 1;
    }
    lbBgFlash_800206D4(&lbl_804D384C, &lbl_804D3848, count);
    lbl_80433658.state.mode = 0;
}

void lbBgFlash_800206D4(GXColor* col1, GXColor* col2, int arg2)
{
    BgFlashData* data = &lbl_80433658;
    int count = arg2;

    if (count < 1) {
        count = 1;
    }

    data->state.active = 0;
    data->state.mode = 2;
    data->x4 = *col1;
    data->xC = data->x4;
    data->x8 = *col2;
    data->x10[0] = (f32) col1->r;
    data->x10[1] = (f32) col1->g;
    data->x10[2] = (f32) col1->b;
    data->x10[3] = (f32) col1->a;
    data->x20[0] = (f32) (col2->r - col1->r) / (f32) count;
    data->x20[1] = (f32) (col2->g - col1->g) / (f32) count;
    data->x20[2] = (f32) (col2->b - col1->b) / (f32) count;
    data->x20[3] = (f32) (col2->a - col1->a) / (f32) count;
}

void lbBgFlash_InitState(GXColor* color)
{
    lbl_80433658.state.active = 0;
    lbl_80433658.state.mode = 5;
    lbl_80433658.xC = *color;
}
void fn_800208B0(u8 arg0)
{
    BgFlashData* data = &lbl_80433658;
    lbl_80433658.state.active = 0;
    if ((data && data) && data) {
    }
    lbl_80433658.state.mode = 5;
    data->xC.b = 0;
    data->xC.g = 0;
    data->xC.r = 0;
    data->xC.a = arg0;
}
void lbBgFlash_800208EC(int arg0)
{
    BgFlashData* flash = &lbl_80433658;
    HSD_GObj** gobj1_slot;
    HSD_GObj** gobj2_slot;

    HSD_CObj* temp1;
    HSD_CObj* temp2;
    u8 temp3;

    lbl_80433658.x44 = GObj_Create(0x14, 0x16, 0);

    temp2 = (temp1 = HSD_CObjLoadDesc((HSD_CObjDesc*) &lbl_803BB028));
    temp3 = HSD_GObj_CameraKind;
    gobj1_slot = &flash->x44;
    HSD_GObjObject_80390A70(*gobj1_slot, temp3 & 0xFFFFFFFF, temp2);

    if ((gobj1_slot && gobj1_slot) && gobj1_slot) {
    }

    GObj_SetupGXLinkMax(*gobj1_slot, HSD_GObj_803910D8, (u8) (arg0 & 0xFFFFu));
    (*gobj1_slot)->gxlink_prios = 0x10000;
    flash->x40 = GObj_Create(0x15, 0x16, 2);

    gobj2_slot = &flash->x40;
    GObj_SetupGXLink(*gobj2_slot, (GObj_RenderFunc) fn_8001FEC4, 0x10,
                     (u8) arg0);
    HSD_GObj_SetupProc(*gobj2_slot, (HSD_GObjEvent) fn_800204C8, 0);

    lbl_80433658.state.active = 1;
    lbl_80433658.state.mode = 0;
}

void lbBgFlash_800209F4(void)
{
    BgFlashData* flash = &lbl_80433658;
    HSD_GObj** gobj1_slot;
    HSD_GObj** gobj2_slot;
    HSD_GObj* temp;

    PAD_STACK(0x8);

    // This is flash->x44
    lbl_80433658.x44 = GObj_Create(0x14, 0x16, 0);
    gobj1_slot = &flash->x44;
    HSD_GObjObject_80390A70(*gobj1_slot,
                            HSD_GObj_CameraKind & 0xFFFFFFFFFFFFFFFF,
                            HSD_CObjLoadDesc((HSD_CObjDesc*) &lbl_803BB028));
    GObj_SetupGXLinkMax(*gobj1_slot, HSD_GObj_803910D8, 0xa);
    (*gobj1_slot)->gxlink_prios = 0x10000;

    if ((!HSD_GObj_CameraKind) && (!HSD_GObj_CameraKind)) {
    }
    // This is flash->x40
    lbl_80433658.x40 = GObj_Create(0x15, 0x16, 2);
    gobj2_slot = &flash->x40;
    GObj_SetupGXLink(*gobj2_slot, (GObj_RenderFunc) fn_8001FEC4, 0x10, 0xa);
    temp = *gobj2_slot;
    HSD_GObj_SetupProc(temp, (HSD_GObjEvent) fn_800204C8, 0);
    lbl_80433658.state.active = 1;
    lbl_80433658.state.mode = 0;
}

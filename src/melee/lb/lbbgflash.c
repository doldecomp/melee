/**
 * @file lbbgflash.c
 * @brief Background flash effects for dramatic game events.
 *
 * Provides full-screen color overlay flashes triggered by various game events.
 * Called from game mode code (gmallstar.c, gm_17C0.c, gm_1A4C.c, etc).
 */

#include "lbbgflash.h"

#include <placeholder.h>

#include "lb/forward.h"

#include "lb/lb_00F9.h"

typedef struct BgFlashState {
    u8 active : 1;
    u8 mode : 7;
} BgFlashState;

typedef struct BgFlashData {
    BgFlashState state;
    u8 pad[3];
    int x4;
    int x8;
    int xC;
} BgFlashData;

extern BgFlashData lbl_80433658;

#include <baselib/gobj.h>
#include <baselib/objalloc.h>
#include <melee/lb/lb_00F9.h>

/* 021A10 */ static void lbBgFlash_80021A10(f32 arg8);
/* 021C18 */ static void fn_80021C18(HSD_GObj* gobj, CommandInfo* cmd,
                                     int arg2);
/// @brief Initialize background flash state.
/* 02087C */ void lbBgFlash_InitState(int* duration);

extern s32 lbl_804D3840;
extern s32 lbl_804D3844;
extern s32 lbl_804D3848;
extern s32 lbl_804D384C;

typedef struct BgFlashData2 {
    u8 state;
    u8 pad1[3];
    int x4;
    int x8;
    u8 xC;
    u8 xD;
    u8 xE;
    u8 xF;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    u8 pad2[0x10];
    u8 x30;
    u8 x31;
    u8 x32;
    u8 x33;
    s32 x34;
    s32 x38;
    s32 x3C;
} BgFlashData2;

/// #fn_8001FC08

/// #fn_8001FEC4

void fn_800204C8(void)
{
    f64 temp;
    BgFlashData2* data = (BgFlashData2*) &lbl_80433658;
    s32 mode = data->state & 0x7F;

    if (mode == 5) {
        return;
    }
    if (mode >= 5) {
        return;
    }
    if (mode >= 3) {
        goto case_3_4;
    }
    if (mode >= 0) {
        goto case_0_1_2;
    }
    return;

case_0_1_2:
    fn_8001FC08();
    data->xC = (s32) data->x10;
    data->xD = (s32) data->x14;
    data->xE = (s32) data->x18;
    data->xF = (s32) data->x1C;
    return;

case_3_4:
    if ((s32) data->x30 == 0) {
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

/// #lbBgFlash_800206D4

void lbBgFlash_InitState(int* duration)
{
    lbl_80433658.state.active = 0;
    lbl_80433658.state.mode = 5;
    lbl_80433658.xC = *duration;
}
/// #fn_800208B0

/// #lbBgFlash_800208EC

/// #lbBgFlash_800209F4

/// #fn_80020AEC

/// #lbBgFlash_80020E38

/// #fn_8002113C

/// #lbBgFlash_80021410

extern HSD_ObjAllocData lbl_804336A0;

void fn_800219E4(void* arg0)
{
    HSD_ObjFree(&lbl_804336A0, arg0);
}

f32 lbl_804D63D8;

typedef struct {
    char pad[0x2C];
    void* x2C;
} BgFlashGlobal;

extern BgFlashGlobal* lbl_804D63E0;
extern struct Fighter_804D653C_t* lbl_804D63DC;

static void lbBgFlash_80021A10(f32 arg8)
{
    lbl_804D63D8 = arg8;
}

/// #lbBgFlash_80021A18

/// #fn_80021B04

static void fn_80021C18(HSD_GObj* gobj, CommandInfo* cmd, int arg2) {}

void fn_80021C1C(void)
{
    HSD_GObj* gobj = (HSD_GObj*) lbl_804D63E0;
    u8* user_data = gobj->user_data;
    lb_80014498((ColorOverlay*) (user_data + 4));
}

void lbBgFlash_80021C48(u32 arg0, u32 arg1)
{
    struct {
        u8 unk0[4];
        ColorOverlay x4;
    }* data = lbl_804D63E0->x2C;
    lb_800144C8(&data->x4, lbl_804D63DC, arg0, arg1);
}

void fn_80021C80(HSD_GObj* gobj)
{
    struct {
        u8 unk0[4];
        ColorOverlay x4;
    }* user_data = gobj->user_data;

    while (lb_80014258(gobj, &user_data->x4, fn_80021C18)) {
        lb_80014498(&user_data->x4);
    }
}

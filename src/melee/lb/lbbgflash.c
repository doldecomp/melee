#include "lbbgflash.h"

#include <placeholder.h>

#include <baselib/gobj.h>
#include <melee/lb/lb_00F9.h>

/* 021C18 */ static void fn_80021C18(HSD_GObj* gobj, CommandInfo* cmd, int arg2);

typedef struct lbl_80433658_t {
    u8 _0 : 1;
    u8 field : 7;
    u8 bytes[0x47];
} lbl_80433658_t;

extern s32 lbl_804D3840;
extern s32 lbl_804D3844;
extern lbl_80433658_t lbl_80433658;

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
    BgFlashData2* data = (BgFlashData2*)&lbl_80433658;
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
    data->xC = (s32)data->x10;
    data->xD = (s32)data->x14;
    data->xE = (s32)data->x18;
    data->xF = (s32)data->x1C;
    return;

case_3_4:
    if ((s32)data->x30 == 0) {
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
/// #lbBgFlash_800205F0

void lbBgFlash_8002063C(int count)
{
    if (count < 1) {
        count = 1;
    }
    lbBgFlash_800206D4(&lbl_804D3844, &lbl_804D3840, count);
    lbl_80433658.field = 0;
}

/// #lbBgFlash_80020688

/// #lbBgFlash_800206D4

/// #fn_8002087C

/// #fn_800208B0

/// #lbBgFlash_800208EC

/// #lbBgFlash_800209F4

/// #fn_80020AEC

/// #lbBgFlash_80020E38

/// #fn_8002113C

/// #lbBgFlash_80021410

/// #fn_800219E4

f32 lbl_804D63D8;

void lbBgFlash_80021A10(f32 arg8)
{
    lbl_804D63D8 = arg8;
}

/// #lbBgFlash_80021A18

/// #fn_80021B04

void fn_80021C18(HSD_GObj* gobj, CommandInfo* cmd, int arg2) {}

/// #fn_80021C1C

/// #lbBgFlash_80021C48

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

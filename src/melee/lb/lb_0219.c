/**
 * @file lb_0219.c
 * @brief Data-driven animated screen flashes.
 *
 * Plays the colour animations stored in LbBf.dat over the background flash
 * overlay owned by lbbgflash.c.
 */

#include "lb_0219.h"

#include <placeholder.h>

#include "dolphin/gx/GXStruct.h"
#include "lb/lbbgflash.h"
#include "lb/types.h"

#include <baselib/gobj.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/objalloc.h>
#include <melee/lb/lbarchive.h>

HSD_ObjAllocData lbl_804336A0;

void fn_800219E4(void* arg0)
{
    HSD_ObjFree(&lbl_804336A0, arg0);
}

f32 lbl_804D63D8;

typedef struct {
    char pad[0x2C];
    void* x2C;
} BgFlashGlobal;

BgFlashGlobal* lbl_804D63E0;
struct Fighter_804D653C_t* lbl_804D63DC;

void lbBgFlash_80021A10(f32 arg8)
{
    lbl_804D63D8 = arg8;
}

void lbBgFlash_80021A18(int arg0)
{
    HSD_GObj* gobj;
    u8* user_data;

    HSD_ObjAllocInit(&lbl_804336A0, 0x84, 4);
    gobj = GObj_Create(0xE, 0xE, 0);
    if (gobj != NULL) {
        user_data = HSD_ObjAlloc(&lbl_804336A0);
        if (user_data != NULL) {
            GObj_InitUserData(gobj, 0xE, fn_800219E4, user_data);
            lbl_804D63E0 = (BgFlashGlobal*) gobj;
            lbl_804D63D8 = 1.0f;
            *user_data = (u8) arg0;
            lbArchive_LoadSymbols("LbBf.dat", &lbl_804D63DC,
                                  "lbBgFlashColAnimData", NULL);
            lbBgFlash_800208EC(6);
            fn_80021C1C();
            HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_80021B04, 1);
            return;
        }
        HSD_GObjPLink_80390228(gobj);
    }
}

typedef struct BgFlashUserData {
    u8 x0;
    u8 pad_01[3];
    ColorOverlay x4;
} BgFlashUserData;

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void fn_80021B04(HSD_GObj* gobj)
{
    BgFlashUserData* data = gobj->user_data;
    int was_active = data->x4.x7C_color_enable;
    GXColor color;
    f32 scale;

    PAD_STACK(4);

    fn_80021C80(gobj);
    if (data->x4.x7C_color_enable) {
        u8* bytes = (u8*) &color;
        scale = lbl_804D63D8;
        bytes[0] = (u8) ((f32) data->x4.x2C_hex.r * scale);
        // This is bytes[1] to bytes[3]
        ((u8*) (&color))[1] = (u8) (((f32) data->x4.x2C_hex.g) * scale);
        ((u8*) (&color))[2] = (u8) (((f32) data->x4.x2C_hex.b) * scale);
        ((u8*) (&color))[3] = (data->x4.x2C_hex.a * data->x0) / 255;
        lbBgFlash_InitState(&color);
        return;
    }
    if (was_active) {
        fn_800208B0(0);
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

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

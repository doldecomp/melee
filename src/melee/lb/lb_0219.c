/**
 * @file lb_0219.c
 * @brief Data-driven animated screen flashes.
 *
 * Plays the colour animations stored in LbBf.dat over the background flash
 * overlay owned by lbbgflash.c.
 */

#include "lb_0219.h"

#include <placeholder.h>

#include "lb_013B.h"
#include "lbarchive.h"
#include "lbbgflash.h"
#include "types.h"
#include <dolphin/gx/GXStruct.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/objalloc.h>

HSD_ObjAllocData bgflash_alloc_data;

typedef struct BgFlashUserData {
    u8 x0;
    u8 pad_01[3];
    ColorOverlay x4;
} BgFlashUserData;

HSD_GObj* flash_gobj;
struct Fighter_804D653C_t* lbl_804D63DC;
f32 flash_scale;

void lbBgFlash_Free(void* arg0)
{
    HSD_ObjFree(&bgflash_alloc_data, arg0);
}

void lbBgFlash_SetFlashScale(f32 arg8)
{
    flash_scale = arg8;
}

void lbBgFlash_Init(int arg0)
{
    HSD_GObj* gobj;
    BgFlashUserData* user_data;

    HSD_ObjAllocInit(&bgflash_alloc_data, sizeof(BgFlashUserData), 4);
    gobj = GObj_Create(0xE, 0xE, 0);
    if (gobj != NULL) {
        user_data = (BgFlashUserData*) HSD_ObjAlloc(&bgflash_alloc_data);
        if (user_data != NULL) {
            GObj_InitUserData(gobj, 0xE, lbBgFlash_Free, user_data);
            flash_gobj = gobj;
            flash_scale = 1.0f;
            user_data->x0 = (u8) arg0;
            lbArchive_LoadSymbols("LbBf.dat", &lbl_804D63DC,
                                  "lbBgFlashColAnimData", NULL);
            lbBgFlash_800208EC(6);
            fn_80021C1C();
            HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) lbBgFlash_Proc, 1);
            return;
        }
        HSD_GObjFree(gobj);
    }
}

void lbBgFlash_Proc(HSD_GObj* gobj)
{
    BgFlashUserData* data = (BgFlashUserData*) gobj->user_data;
    int was_active = data->x4.x7C_color_enable;
    GXColor color;
    f32 scale;

    PAD_STACK(4);

    fn_80021C80(gobj);
    if (data->x4.x7C_color_enable) {
        u8* bytes = (u8*) &color;
        scale = flash_scale;
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

static void fn_80021C18(HSD_GObj* gobj, CommandInfo* cmd, int arg2) {}

void fn_80021C1C(void)
{
    HSD_GObj* gobj = flash_gobj;
    BgFlashUserData* user_data = (BgFlashUserData*) gobj->user_data;
    lb_80014498(&user_data->x4);
}

void lbBgFlash_80021C48(u32 arg0, u32 arg1)
{
    BgFlashUserData* data = (BgFlashUserData*) flash_gobj->user_data;
    lb_800144C8(&data->x4, lbl_804D63DC, arg0, arg1);
}

void fn_80021C80(HSD_GObj* gobj)
{
    BgFlashUserData* user_data = (BgFlashUserData*) gobj->user_data;

    while (lb_80014258(gobj, &user_data->x4, fn_80021C18)) {
        lb_80014498(&user_data->x4);
    }
}

#include "mngallery.h"

#include <platform.h>
#include <placeholder.h>
#include <baselib/cobj.h>
#include <baselib/controller.h>
#include <baselib/displayfunc.h>
#include <baselib/gobj.h>
#include <baselib/gobjplink.h>
#include <baselib/memory.h>
#include <baselib/sobjlib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbmthp.h>
#include <melee/mn/mnmain.h>

static void* mnGallery_804D6C88;
static void* mnGallery_804D6C8C;

void mnGallery_80258940(void)
{
    mnGallery_804D6C8C = HSD_MemAlloc(0x271000);
}

void mnGallery_8025896C(HSD_GObj* gobj, s32 render_pass)
{
    struct {
        u8 pad[0x2C];
        struct {
            u8 pad2[0x14];
            u8 state;
        }* unk2C;
    }* data = mnGallery_804D6C88;
    HSD_CObj* cobj = gobj->hsd_obj;
    PAD_STACK(0x10);

    if (data->unk2C->state == 3) {
        if (HSD_CObjSetCurrent(cobj)) {
            HSD_SetEraseColor(0, 0, 0, 0xFF);
            HSD_CObjEraseScreen(cobj, 1, 0, 0);
            HSD_CObjEndCurrent();
        }
        HSD_SObjLib_803A54EC(gobj, render_pass);
    }
}

/// #mnGallery_80258A08

/// #mnGallery_80258BC4

void mnGallery_80258D50(void* arg)
{
    struct {
        u8 unk0;
        u8 unk1;
        u8 pad[6];
        HSD_GObj* gobj;
    }* data = arg;
    s32 zero;

    if (data->unk0 != 0) {
        lbMthp_8001F800();
        lbAudioAx_800236DC();
        lbAudioAx_80023F28(gmMainLib_8015ECB0());

        zero = 0;
        data->unk0 = zero;
        data->unk1 = zero;

        if (data->gobj != NULL) {
            HSD_GObjPLink_80390228(data->gobj);
            data->gobj = NULL;
        }
    }
}

void mnGallery_80258DBC(HSD_GObj* gobj, void* arg)
{
    struct {
        u8 unk0;
        u8 unk1;
        u8 pad[6];
        HSD_GObj* gobj;
        u8 pad2[0x08];
        u8 unk14;
    }* data = arg;
    u32 buttons;
    u32 skip;
    u32 pressed;
    PAD_STACK(0x10);

    skip = 0;
    buttons = HSD_PadCopyStatus[0].trigger | HSD_PadCopyStatus[1].trigger;
    buttons |= HSD_PadCopyStatus[2].trigger;
    buttons |= HSD_PadCopyStatus[3].trigger;
    lbMthp_8001F578();
    if (lbMthp_8001F604() != 0) {
        data->unk1 = data->unk1 + 1;
    }
    if (gmMainLib_8046B0F0.xC != 0 && lbMthp_8001F604() == 0) {
        skip = 1;
    }
    pressed = buttons & 0x1300;
    if (pressed != 0 || data->unk1 > 0x32 || skip != 0) {
        if (pressed != 0) {
            lbAudioAx_80024030(0);
        }
        data->unk14 = 1;
        mn_8022BD8C();
        if (data->unk0 != 0) {
            lbMthp_8001F800();
            lbAudioAx_800236DC();
            lbAudioAx_80023F28(gmMainLib_8015ECB0());
            data->unk0 = 0;
            data->unk1 = 0;
            if (data->gobj != NULL) {
                HSD_GObjPLink_80390228(data->gobj);
                data->gobj = NULL;
            }
        }
    }
}

/// #fn_80258ED0

/// #fn_802590C4

/// #mnGallery_802591BC

void mnGallery_80259604(void* arg)
{
    struct {
        /* 0x00 */ u8 unk0;
        /* 0x01 */ u8 unk1;
        /* 0x02 */ u8 unk2;
        /* 0x03 */ u8 pad3;
        /* 0x04 */ s32 unk4;
        /* 0x08 */ s32 unk8;
        /* 0x0C */ s32 unkC;
        /* 0x10 */ s32 unk10;
        /* 0x14 */ u8 unk14;
        /* 0x15 */ u8 unk15;
        /* 0x16 */ u8 pad16[2];
        /* 0x18 */ s32 unk18;
        /* 0x1C */ s32 unk1C;
        /* 0x20 */ s32 unk20;
    }* data = arg;

    data->unk0 = 0;
    data->unk1 = 0;
    data->unk2 = 0;
    data->unk4 = 0;
    data->unk8 = 0;
    data->unkC = 0;
    data->unk10 = 0;
    data->unk14 = 0;
    data->unk15 = 0;
    data->unk18 = 0;
    data->unk1C = 0;
    data->unk20 = 0;
}

/// #mnGallery_8025963C

/// #mnGallery_80259868

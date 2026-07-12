/// VS-mode camera (memory card snapshot) screen: OnEnter/OnFrame/OnLeave
/// handlers and text refresh, split from gmcamera.c.
/// Evidence for the TU boundary (config/GALE01/symbols.txt): retail
/// gmCamera_801A33BC addresses this file's data through a merged-data
/// anchor at 0x803DA758 and a .bss anchor at 0x80479C20 - MWCC 1.2.5n
/// anchors always sit at a TU's .data+0/.bss+0, while gmCamera_801A31FC in
/// gmcamera.c anchors .data at 0x803DA630 - two .data anchors cannot come
/// from one TU. The .sdata2 pool also restarts (align-8 gap at 0x804DA9D4,
/// duplicate 0.0f at 0x804DA9E0), and retail gmCamera_801A33BC /
/// gmCamera_801A3634_OnEnter call gmCamera_801A25C8 / gmCamera_801A2650
/// directly (no inlining), consistent with cross-TU calls.
#include "gmcamera.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/sislib.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A45.h"
#include "gm/types.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbsnap.h"
#include "mn/mnmain.h"

/// Text layout table for the snapshot texts: three rows of
/// { font_size_x, font_size_y, pos_x, pos_y } for the two card-slot texts
/// and the bottom text (retail 0x803DA758, this TU's .data anchor).
f32 gmCamera_VsCameraTextLayout[12] = {
    0.7f,   0.7f,   168.0f, 160.0f, 0.7f, 0.7f,
    168.0f, 192.0f, 0.7f,   0.7f,   0.0f, 256.0f,
};

/// Per-run data of the VS camera-mode screen (slot texts, bottom text,
/// scene-exit code pointer); named after its type CameraVsData and the
/// SIS data file "SIS_VsCameraData" (retail .bss object at 0x80479C20).
struct CameraVsData gmCamera_VsCameraData;

void gmCamera_801A33BC(void)
{
    HSD_Text* text;
    s32 state;
    s32 blocks;

    gmCamera_801A25C8();
    gmCamera_VsCameraData.slot_a = gmCamera_801A2334(
        0, gmCamera_VsCameraTextLayout[2], gmCamera_VsCameraTextLayout[3],
        gmCamera_VsCameraTextLayout[0], gmCamera_VsCameraTextLayout[1]);
    gmCamera_VsCameraData.slot_b = gmCamera_801A2334(
        1, gmCamera_VsCameraTextLayout[6], gmCamera_VsCameraTextLayout[7],
        gmCamera_VsCameraTextLayout[4], gmCamera_VsCameraTextLayout[5]);
    gmCamera_801A253C(&state, &blocks);
    text = HSD_SisLib_803A5ACC(3, gmCamera_801A2640(),
                               gmCamera_VsCameraTextLayout[10],
                               gmCamera_VsCameraTextLayout[11], 0.0f,
                               914.2857f, 64.0f);
    gmCamera_VsCameraData.bottom_text = text;
    text->default_alignment = 1;
    text->default_kerning = 1;
    text->default_fitting = 1;
    {
        f32 fy = gmCamera_VsCameraTextLayout[9];
        f32 fx = gmCamera_VsCameraTextLayout[8];
        text->font_size.x = fx;
        text->font_size.y = fy;
    }
    HSD_SisLib_803A6368(text, 0x15);
    switch (state) {
    case 0:
    case 1:
        gmCamera_801A2224(HSD_SisLib_803A6530(3, 0x15, 0x11), blocks);
        HSD_SisLib_803A660C(3, 0x15, 0x12);
        break;
    case 2:
        HSD_SisLib_803A6530(3, 0x15, 0x13);
        break;
    default:
        HSD_SisLib_803A6530(3, 0x15, 0x14);
    }
}

void gmCamera_801A34FC_OnFrame(void)
{
    CameraVsData* data;
    s32 i;
    u64 button;

    data = &gmCamera_VsCameraData;
    if ((lbSnap_8001D338(0) != 0) || (lbSnap_8001D338(1) != 0)) {
        for (i = 0; i < 3; i++) {
            if (data->text[i] != NULL) {
                HSD_SisLib_803A5CC4(data->text[i]);
                data->text[i] = NULL;
            }
        }
        gmCamera_801A33BC();
    } else if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        mn_8022F268();
        *gmCamera_VsCameraData.x0 = 2;
        gm_801A4B60();
    } else if (button = gm_801A36A0(4), (button & 0x1100) | (button & 0)) {
        lbAudioAx_80024030(1);
        *gmCamera_VsCameraData.x0 = 0;
        gm_801A4B60();
    } else if (button = gm_801A36A0(4), (button & 0x200) | (button & 0)) {
        lbAudioAx_80024030(0);
        *gmCamera_VsCameraData.x0 = 1;
        gm_801A4B60();
    }
}

void gmCamera_801A3634_OnEnter(UNK_T arg0)
{
    PAD_STACK(8);

    gmCamera_VsCameraData.x0 = (u32*) arg0;
    gmCamera_801A2650();
    gmCamera_VsCameraData.slot_a = NULL;
    gmCamera_VsCameraData.slot_b = NULL;
    gmCamera_VsCameraData.bottom_text = NULL;
    gmCamera_801A33BC();
}

void gmCamera_801A367C_OnLeave(UNK_T unused) {}

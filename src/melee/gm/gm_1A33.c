#include "gm_1A33.h"

#include <dolphin/pad.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/gmcamera.h>
#include <melee/gm/types.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbsnap.h>
#include <melee/mn/mnmain.h>

static f32 gmCamera_803DA758[12] = {
    0.7f,   0.7f,   168.0f, 160.0f, 0.7f, 0.7f,
    168.0f, 192.0f, 0.7f,   0.7f,   0.0f, 256.0f,
};

static struct CameraVsData gmCamera_VsCameraTextLayout;

void gmCamera_801A33BC(void)
{
    HSD_Text* text;
    s32 sp10;
    s32 spC;

    gmCamera_801A25C8();
    gmCamera_VsCameraTextLayout.slot_a =
        gmCamera_801A2334(0, gmCamera_803DA758[2], gmCamera_803DA758[3],
                          gmCamera_803DA758[0], gmCamera_803DA758[1]);
    gmCamera_VsCameraTextLayout.slot_b =
        gmCamera_801A2334(1, gmCamera_803DA758[6], gmCamera_803DA758[7],
                          gmCamera_803DA758[4], gmCamera_803DA758[5]);
    gmCamera_801A253C(&sp10, &spC);
    text = HSD_SisLib_803A5ACC(3, gmCamera_801A2640(), gmCamera_803DA758[10],
                               gmCamera_803DA758[11], 0.0f, 914.2857f, 64.0f);
    gmCamera_VsCameraTextLayout.bottom_text = text;
    text->default_alignment = 1;
    text->default_kerning = 1;
    text->default_fitting = 1;
    {
        f32 fy = gmCamera_803DA758[9];
        f32 fx = gmCamera_803DA758[8];
        text->font_size.x = fx;
        text->font_size.y = fy;
    }
    HSD_SisLib_803A6368(text, 0x15);
    switch (sp10) {
    case 0:
    case 1:
        gmCamera_801A2224(HSD_SisLib_803A6530(3, 0x15, 0x11), spC);
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

    data = &gmCamera_VsCameraTextLayout;
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
        *gmCamera_VsCameraTextLayout.x0 = 2;
        gm_801A4B60();
    } else if (button = gm_GetButtonsTriggered(PAD_ALL_CONTROLLERS),
               (button & (HSD_PAD_START | HSD_PAD_A)) | (button & 0))
    {
        lbAudioAx_80024030(1);
        *gmCamera_VsCameraTextLayout.x0 = 0;
        gm_801A4B60();
    } else if (button = gm_GetButtonsTriggered(PAD_ALL_CONTROLLERS),
               (button & PAD_BUTTON_B) | (button & 0))
    {
        lbAudioAx_80024030(0);
        *gmCamera_VsCameraTextLayout.x0 = 1;
        gm_801A4B60();
    }
}

void gmCamera_801A3634_OnEnter(UNK_T arg0)
{
    PAD_STACK(8);

    gmCamera_VsCameraTextLayout.x0 = (u32*) arg0;
    gmCamera_801A2650();
    gmCamera_VsCameraTextLayout.slot_a = NULL;
    gmCamera_VsCameraTextLayout.slot_b = NULL;
    gmCamera_VsCameraTextLayout.bottom_text = NULL;
    gmCamera_801A33BC();
}

void gmCamera_801A367C_OnLeave(UNK_T unused) {}

#include "gmcamera.h"
#include "gm/gmcamera.static.h"
#include "baselib/sislib.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A45.h"
#include "gm/types.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbsnap.h"
#include "mn/mn_2295.h"

#include <platform.h>
#include <placeholder.h>

// void* HSD_SisLib_803A5ACC(u8, int, float, float, float); /* extern */
// void HSD_SisLib_803A6368(void*, u32);                    /* extern */
// void HSD_SisLib_803A6530(u32, u32, u32);                 /* extern */
// void HSD_SisLib_803A660C(u32, u32, u32);                 /* extern */
// void HSD_SisLib_803A62A0(s32, char*, char*);
// s32 HSD_SisLib_803A611C(int, u32, u16, u8, u8, u8, u8, u32);

typedef struct _SisLibUnkStruct2 {
    /*0x00*/ u8 x0_padding[0x8 - 0x0];
    /*0x08*/ u8* x08_arr; // Unknown length as of right now
} SisLibUnkStruct2;

/// @todo #SIS
typedef struct _SisLibUnkStruct {
    /*0x00*/ u8 x0_padding[0xC - 0x0];
    /*0x0C*/ SisLibUnkStruct2* x0C_ptr;
    /*0x10*/ u8 x10_padding[0x14 - 0x10];
} SisLibUnkStruct;

/// @todo #HSD_SisLib_804D1124 is of type #SIS.
// extern SisLibUnkStruct HSD_SisLib_804D1124;

u8* gmCamera_801A2224(u8* arg0, u32 arg1)
{
    u32 masked_arg1;
    u32 cond_flag = 0;
    u8 *slus2_arr_ptr = ((SisLibUnkStruct*)HSD_SisLib_804D1124)->x0C_ptr->x08_arr;

    if (arg1 >= 0x2710U) {
        arg1 = 0x270F;
    }

    if (arg1 >= 0x3E8U) {
        masked_arg1 = (arg1 / 500) & 0x07FFFFFE;
        arg0[0] = slus2_arr_ptr[0 + masked_arg1];
        arg0[1] = slus2_arr_ptr[1 + masked_arg1];
        arg1 %= 0x3E8;
        cond_flag = 1U;
        arg0 += 2;
    }
    if ((arg1 >= 0x64U) || (cond_flag != 0)) {
        masked_arg1 = (arg1 / 50) & 0x0FFFFFFE;
        arg0[0] = slus2_arr_ptr[0 + masked_arg1];
        arg0[1] = slus2_arr_ptr[1 + masked_arg1];
        arg1 %= 0x64;
        cond_flag += 1;
        arg0 += 2;
    }
    if ((arg1 >= 0xAU) || (cond_flag != 0)) {
        masked_arg1 = (arg1 / 5) & 0x3FFFFFFE;
        arg0[0] = slus2_arr_ptr[0 + masked_arg1];
        arg0[1] = slus2_arr_ptr[1 + masked_arg1];
        arg1 %= 0xA;
        arg0 += 2;
    }
    *(arg0++) = slus2_arr_ptr[0 + arg1 * 2];
    *(arg0++) = slus2_arr_ptr[1 + arg1 * 2];
    *arg0 = 0;
    return arg0;
}

HSD_Text* gmCamera_801A2334(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4)
{
    HSD_Text* text;
    s32 temp_r4;
    s32 temp_r6;
    s32 var_r0;
    s32 var_r30;
    s32 var_r5;
    u32 temp_r0;
    u32* temp_r27;
    gmCameraUnkStruct2* temp_r5;

    text = HSD_SisLib_803A5ACC(3, (s32) gmCamera_80479BC8.gcus.x54, arg1, arg2, 0.0f, 640.0f, 32.0f);
    text->x24.x = arg3;
    text->x24.y = arg4;
    text->x49 = 1;
    if (arg0 == 0) {
        var_r30 = 6;
        HSD_SisLib_803A6530(3, 6, 8);
    } else {
        var_r30 = 7;
        HSD_SisLib_803A6530(3, 7, 9);
    }
    temp_r6 = arg0 * 0x10;
    temp_r5 = (gmCameraUnkStruct2*) ((int) &(gmCamera_80479BC8.gcus2_ptrs) +
                                     temp_r6);
    temp_r0 = temp_r5->x24;
    switch (temp_r0) {
    case 0:
        if ((s32) temp_r5->x2C == 0) {
            temp_r5->x30 = 3;
            HSD_SisLib_803A660C(3, var_r30, 0xC);
        } else {
            temp_r27 = &(temp_r5->x28);
            temp_r4 = temp_r5->x28;
            if (temp_r4 == 0) {
                temp_r5->x30 = 2;
                HSD_SisLib_803A660C(3, var_r30, 0xC);
            } else {
                if (temp_r4 >= (s32) gmCamera_80479BC8.gcus.x20) {
                    if (arg0 != 0) {
                        var_r0 = 0;
                    } else {
                        var_r0 = 1;
                    }
                } else {
                    var_r0 = 2;
                }
                temp_r5->x30 = var_r0;
                gmCamera_801A2224((u8*) *temp_r27, *temp_r27);
                if ((s32) *temp_r27 != 1) {
                    var_r5 = 0xB;
                } else {
                    var_r5 = 0xA;
                }
                HSD_SisLib_803A660C(3, var_r30, var_r5);
            }
        }
        break;
    case 15:
        temp_r5->x30 = 5;
        HSD_SisLib_803A660C(3, var_r30, 0x10);
        break;
    case 9:
        temp_r5->x30 = 4;
        HSD_SisLib_803A660C(3, var_r30, 0xD);
        break;
    case 12:
        temp_r5->x30 = 4;
        HSD_SisLib_803A660C(3, var_r30, 0xE);
        break;
    default:
        temp_r5->x30 = 4;
        HSD_SisLib_803A660C(3, var_r30, 0xF);
        break;
    }
    HSD_SisLib_803A6368(text, var_r30);
    return text;
}

/// #gmCamera_801A253C

/// #gmCamera_801A25C8

s32 gmCamera_801A2640(void)
{
    return M2C_FIELD(&gmCamera_80479BC8, s32*, 0x54);
}

#pragma dont_inline on
void gmCamera_801A2650(void)
{
    gmCamera_80479BC8.gcus.x20 = 2;
    HSD_SisLib_803A62A0(3, "SdVsCam", "SIS_VsCameraData");
    gmCamera_80479BC8.gcus.x54 = HSD_SisLib_803A611C(3, 0, 9, 13, 0, 14, 0, 11);
}
#pragma dont_inline reset

/// #gmCamera_801A26C0

/// #gmCamera_801A2798

/// #gmCamera_801A2800

/// #gmCamera_801A28AC

/// #gmCamera_801A292C

/// #gmCamera_801A2AAC

/// #gmCamera_801A2BB0

/// #gmCamera_801A2BF0

/// #gmCamera_801A2D44

/// #gmCamera_801A2FBC

/// #gmCamera_801A2FFC

/// #gmCamera_801A3048

/// #gmCamera_801A3098

/// #gmCamera_801A30E4

/// #fn_801A31D8

/// #gmCamera_801A31FC

/// #gmCamera_801A33BC

void gmCamera_801A34FC_OnFrame(void)
{
    CameraVsData* data;
    s32 i;
    u64 button;
    u64 _button;

    data = &gmCamera_80479C20;
    if ((lbSnap_8001D338(0) != 0) || (lbSnap_8001D338(1) != 0)) {
        for (i = 0; i < 3; i++) {
            if (data->text[i] != NULL) {
                HSD_SisLib_803A5CC4(data->text[i]);
                data->text[i] = NULL;
            }
        }
        gmCamera_801A33BC();
        return;
    }

    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        mn_8022F268();
        *gmCamera_80479C20.x0 = 2;
        gm_801A4B60();
        return;
    }
    button = gm_801A36A0(4);
    if ((button & 0x1100) | (button & 0)) {
        lbAudioAx_80024030(1);
        *gmCamera_80479C20.x0 = 0;
        gm_801A4B60();
        return;
    }
    _button = gm_801A36A0(4);
    if ((_button & 0x200) | (_button & 0)) {
        lbAudioAx_80024030(0);
        *gmCamera_80479C20.x0 = 1;
        gm_801A4B60();
    }
}

void gmCamera_801A3634_OnEnter(UNK_T arg0)
{
    PAD_STACK(8);

    gmCamera_80479C20.x0 = (u32* ) arg0;
    gmCamera_801A2650();
    gmCamera_80479C20.slot_a = NULL;
    gmCamera_80479C20.slot_b = NULL;
    gmCamera_80479C20.bottom_text = NULL;
    gmCamera_801A33BC();
}

void gmCamera_801A367C_OnLeave(UNK_T unused) {}

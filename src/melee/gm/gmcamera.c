#include "gmcamera.h"

#include "gm/gmcamera.static.h"
#include <placeholder.h>
#include <platform.h>

#include "baselib/controller.h"

#include "baselib/forward.h"

#include "baselib/jobj.h"
#include "baselib/sislib.h"
#include "cm/cmsnap.h"
#include "gm/gm_16AE.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A45.h"
#include "gm/gmpause.h"
#include "gm/types.h"
#include "if/ifall.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardnew.h"
#include "lb/lbsnap.h"
#include "mn/mnmain.h"

/// void* HSD_SisLib_803A5ACC(u8, int, float, float, float); /* extern */
/// void HSD_SisLib_803A6368(void*, u32);                    /* extern */
/// void HSD_SisLib_803A6530(u32, u32, u32);                 /* extern */
/// void HSD_SisLib_803A660C(u32, u32, u32);                 /* extern */
/// void HSD_SisLib_803A62A0(s32, char*, char*);
/// s32 HSD_SisLib_803A611C(int, u32, u16, u8, u8, u8, u8, u32);

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
/// extern SisLibUnkStruct HSD_SisLib_804D1124;

gmCameraUnkFuncTable gmCamera_803DA6B4[9] = {
    { { 1, 0, 0 }, gmCamera_801A26C0, gmCamera_801A2798 },
    { { 0, 0, 4 }, gmCamera_801A2800, gmCamera_801A28AC },
    { { 0, 0, 2 }, gmCamera_801A292C, gmCamera_801A2AAC },
    { { 0, 0, 0x54 }, NULL, gmCamera_801A2BB0 },
    { { 0, 0, 0x34 }, NULL, gmCamera_801A2BB0 },
    { { 0, 0, 0x94 }, NULL, gmCamera_801A2BB0 },
    { { 0, 0, 0x1204 }, gmCamera_801A2BF0, gmCamera_801A2D44 },
    { { 0, 0, 0x1604 }, gmCamera_801A2FBC, gmCamera_801A2FFC },
    { { 0, 0, 0x1A14 }, NULL, gmCamera_801A2BB0 },
};

u8* gmCamera_801A2224(u8* arg0, u32 arg1)
{
    u32 masked_arg1;
    u32 cond_flag = 0;
    u8* slus2_arr_ptr =
        ((SisLibUnkStruct*) HSD_SisLib_804D1124)->x0C_ptr->x08_arr;

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

    text = HSD_SisLib_803A5ACC(3, (s32) gmCamera_80479BC8.gcus.x54, arg1, arg2,
                               0.0f, 640.0f, 32.0f);
    text->font_size.x = arg3;
    text->font_size.y = arg4;
    text->default_kerning = 1;
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

void gmCamera_801A253C(s32* arg0, s32* arg1)
{
    gmCameraUnkStruct* gcus = &gmCamera_80479BC8.gcus;
    gcus->x44 = MIN(gcus->x30, gcus->x40);
    if (arg0 != NULL) {
        *arg0 = gcus->x44;
    }
    if (arg1 != NULL) {
        u32 var_r3 = 0;
        u32 var_r6 = 0;
        if (gcus->x30 == 1) {
            var_r3 = gcus->x28;
        }
        if (gcus->x40 == 0) {
            var_r6 = gcus->x38;
        }
        *arg1 = MAX(var_r3, var_r6);
    }
}

void gmCamera_801A25C8(void)
{
    s32 i;
    for (i = 0; i < 2; i++) {
        gmCamera_80479BC8.gcus4.x24[i].x0 = lbSnap_8001D40C(i);
        if (!gmCamera_80479BC8.gcus4.x24[i].x0) {
            gmCamera_80479BC8.gcus4.x24[i].x4 = lbSnap_8001D3B0(i);
            gmCamera_80479BC8.gcus4.x24[i].x8 = lbSnap_8001D3CC(i);
        }
    }
}

s32 gmCamera_801A2640(void)
{
    return M2C_FIELD(&gmCamera_80479BC8, s32*, 0x54);
}

#pragma dont_inline on
void gmCamera_801A2650(void)
{
    gmCamera_80479BC8.gcus.x20 = 2;
    HSD_SisLib_803A62A0(3, "SdVsCam", "SIS_VsCameraData");
    gmCamera_80479BC8.gcus.x54 =
        HSD_SisLib_803A611C(3, 0, 9, 13, 0, 14, 0, 11);
}
#pragma dont_inline reset

void gmCamera_801A26C0(void)
{
    lbl_8046B6A0_t* temp_r31;
    gmCameraUnkStruct* unk;
    s32 i;
    PAD_STACK(4);

    temp_r31 = gm_8016AE38();
    if (gm_801A45E8(3)) {
        gm_801A4674(3);
        if (gm_801A45E8(1)) {
            gm_801A0FEC(temp_r31->pauser, 1);
        } else {
            lbAudioAx_80024E84(0);
            ifAll_802F33CC();
            HSD_PadRumbleUnpauseAll();
        }
        temp_r31->hud_enabled = 1;
        temp_r31->unk_3 = 0;
    }
    unk = &gmCamera_80479BC8.gcus;
    if (unk->x48[0] != NULL) {
        for (i = 0; i < 3; i++) {
            HSD_SisLib_803A5CC4(unk->x48[i]);
            unk->x48[i] = NULL;
        }
    }
}

void gmCamera_801A2798(void)
{
    if (HSD_PadCopyStatus[3].trigger & 0x200) {
        gmCamera_80479BC8.gcus.x14 = (gmCamera_80479BC8.gcus.x14 + 1) % 2;
        return;
    }
    if (HSD_PadCopyStatus[3].trigger & 0x10) {
        lbAudioAx_80024030(6);
        gmCamera_801A3048(1);
    }
}

void gmCamera_801A2800(void)
{
    HSD_JObj* jobj;
    lbl_8046B6A0_t* temp_r3;

    temp_r3 = gm_8016AE38();
    gmCamera_80479BC8.gcus.x10 = 0;
    lb_80011E24(gmCamera_80479BC8.gcus.x8, &jobj, 2, -1);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    gm_801A4634(3);
    if (gm_801A45E8(1) != 0) {
        gm_801A10FC(temp_r3->pauser);
    } else {
        lbAudioAx_80024E84(1);
        ifAll_802F3394();
        HSD_PadRumblePauseAll();
    }
    temp_r3->hud_enabled = 0;
    temp_r3->unk_3 = 1;
    cmSnap_800315C8();
}

void gmCamera_801A28AC(void)
{
    if (++gmCamera_80479BC8.gcus.x10 > 2) {
        void* temp_r4 = cmSnap_80031618();
        gmCamera_80479BC8.gcus.x1C = temp_r4;
        if (temp_r4) {
            if (lbSnap_8001DC0C((int) gmCamera_80479BC8.gcus.x1C) != 0) {
                gmCamera_80479BC8.gcus.x20 = lbSnap_8001DF20();
                gmCamera_801A3048(2);
            } else {
                gmCamera_801A3048(0);
            }
        }
    }
}

/// #gmCamera_801A292C

void gmCamera_801A2AAC(void)
{
    s32 temp_r0;
    PAD_STACK(8);

    if ((lbSnap_8001D338(0) != 0) || (lbSnap_8001D338(1) != 0)) {
        gmCamera_801A3048(2);
    } else if (HSD_PadCopyStatus[3].trigger & 0x100) {
        lbAudioAx_80024030(1);
        if ((gmCamera_80479BC8.gcus.x44 < 2) &&
            (gmCamera_80479BC8.gcus.x44 >= 0))
        {
            gmCamera_801A3048(6);
        } else {
            lbAudioAx_80024030(3);
            temp_r0 = gmCamera_80479BC8.gcus.x44;
            if (temp_r0 != 4) {
                if ((temp_r0 < 4) && (temp_r0 >= 2)) {
                    gmCamera_801A3048(4);
                    return;
                } else if (temp_r0 < 6) {
                    gmCamera_801A3048(3);
                    return;
                }
            }
            gmCamera_801A3048(5);
        }
    } else if (HSD_PadCopyStatus[3].trigger & 0x200) {
        lbAudioAx_80024030(0);
        gmCamera_801A3048(0);
    }
}

void gmCamera_801A2BB0(void)
{
    if (HSD_PadCopyStatus[3].trigger & 0x200) {
        lbAudioAx_80024030(0);
        gmCamera_801A3048(0);
    }
}

/// #gmCamera_801A2BF0

/// #gmCamera_801A2D44

void gmCamera_801A2FBC(void)
{
    s32 chan;
    if (gmCamera_80479BC8.gcus.x44 == 0) {
        chan = 1;
    } else {
        chan = 0;
    }
    lbSnap_8001DF6C(chan);
}

void gmCamera_801A2FFC(void)
{
    s32 i = lb_8001B6F8();
    if (i != 0xB) {
        if (i == 0) {
            gmCamera_801A3048(0);
        } else {
            lbAudioAx_80024030(3);
            gmCamera_801A3048(8);
        }
    }
}

void gmCamera_801A3048(s32 i)
{
    gmCamera_80479BC8.gcus.xC = i;
    if (gmCamera_803DA6B4[gmCamera_80479BC8.gcus.xC].x4 != NULL) {
        gmCamera_803DA6B4[gmCamera_80479BC8.gcus.xC].x4();
    }
}

void gmCamera_801A3098(void)
{
    if (gmCamera_803DA6B4[gmCamera_80479BC8.gcus.xC].x8 != NULL) {
        gmCamera_803DA6B4[gmCamera_80479BC8.gcus.xC].x8();
    }
}

void gmCamera_801A30E4(void)
{
    s32 i;
    if ((gmCamera_803DA6B4[gmCamera_80479BC8.gcus.xC].flags.x0 != 0) &&
        (gmCamera_80479BC8.gcus.x14 != 0) && (gm_801A45E8(1) == 0))
    {
        HSD_JObjClearFlagsAll(gmCamera_80479BC8.gcus.x4, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(gmCamera_80479BC8.gcus.x4, JOBJ_HIDDEN);
    }
    HSD_JObjSetFlagsAll(gmCamera_80479BC8.gcus.x8, JOBJ_HIDDEN);
    for (i = 0; i < 16; i++) {
        if ((1 << i) & gmCamera_803DA6B4[gmCamera_80479BC8.gcus.xC].flags.x2) {
            HSD_JObj* jobj;
            lb_80011E24(gmCamera_80479BC8.gcus.x8, &jobj, i, -1);
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
}

void fn_801A31D8(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(gobj->hsd_obj);
}

/// #gmCamera_801A31FC

static void gmCamera_801A25C8_no_inline(void)
{
    gmCamera_801A25C8();
}

static void gmCamera_801A253C_no_inline(s32* arg0, s32* arg1)
{
    gmCamera_801A253C(arg0, arg1);
}

void gmCamera_801A34FC_OnFrame(void)
{
    CameraVsData* data;
    s32 i;
    u64 button;

    data = &gmCamera_80479C20;
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
        *gmCamera_80479C20.x0 = 2;
        gm_801A4B60();
    } else if (button = gm_801A36A0(4), (button & 0x1100) | (button & 0)) {
        lbAudioAx_80024030(1);
        *gmCamera_80479C20.x0 = 0;
        gm_801A4B60();
    } else if (button = gm_801A36A0(4), (button & 0x200) | (button & 0)) {
        lbAudioAx_80024030(0);
        *gmCamera_80479C20.x0 = 1;
        gm_801A4B60();
    }
}

void gmCamera_801A3634_OnEnter(UNK_T arg0)
{
    PAD_STACK(8);

    gmCamera_80479C20.x0 = (u32*) arg0;
    gmCamera_801A2650();
    gmCamera_80479C20.slot_a = NULL;
    gmCamera_80479C20.slot_b = NULL;
    gmCamera_80479C20.bottom_text = NULL;
    gmCamera_801A33BC();
}

void gmCamera_801A367C_OnLeave(UNK_T unused) {}

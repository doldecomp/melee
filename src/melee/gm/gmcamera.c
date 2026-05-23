#include "gmcamera.h"

#include "gm/gmcamera.static.h"
#include <placeholder.h>
#include <platform.h>

#include "baselib/archive.h"
#include "baselib/controller.h"

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "baselib/sislib.h"
#include "cm/cmsnap.h"
#include "gm/gm_1601.h"
#include "gm/gm_16AE.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A45.h"
#include "gm/gmpause.h"
#include "gm/types.h"
#include "if/ifall.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardnew.h"
#include "lb/lbsnap.h"
#include "mn/mnmain.h"
#include "sc/types.h"

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

f32 gmCamera_803DA630[12] = {
    0.6f,   0.6f,   40.0f, 416.0f, 0.6f,  0.6f,
    340.0f, 416.0f, 0.6f,  0.6f,   40.0f, 44.0f,
};

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

#pragma dont_inline on
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
#pragma dont_inline reset

#pragma dont_inline on
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
#pragma dont_inline reset

#pragma dont_inline on
s32 gmCamera_801A2640(void)
{
    return M2C_FIELD(&gmCamera_80479BC8, s32*, 0x54);
}
#pragma dont_inline reset

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
    unsigned int new_var;
    if (HSD_PadCopyStatus[3].trigger & 0x200) {
        new_var = gmCamera_80479BC8.gcus.x14 + 1;
        gmCamera_80479BC8.gcus.x14 = new_var % 2;
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

void gmCamera_801A292C(void)
{
    HSD_Text* text;
    s32 i;
    HSD_Text** texts = &gmCamera_80479BC8.gcus.x48[0];
    gmCameraUnkStruct2* p;
    s32 x44;

    if (gmCamera_80479BC8.gcus.x48[0] != NULL) {
        i = 0;
        do {
            HSD_SisLib_803A5CC4(gmCamera_80479BC8.gcus.x48[i]);
            i++;
            gmCamera_80479BC8.gcus.x48[i - 1] = NULL;
        } while (i < 3);
    }
    i = 0;
    p = (gmCameraUnkStruct2*) &gmCamera_80479BC8;
    do {
        p->x24 = lbSnap_8001D40C(i);
        if ((s32) p->x24 == 0) {
            p->x28 = lbSnap_8001D3B0(i);
            p->x2C = lbSnap_8001D3CC(i);
        }
        i++;
        p = (gmCameraUnkStruct2*) ((u8*) p + 0x10);
    } while (i < 2);
    text = HSD_SisLib_803A5ACC(3, (s32) gmCamera_80479BC8.gcus.x54,
                               gmCamera_803DA630[10], gmCamera_803DA630[11],
                               0.0f, 640.0f, 32.0f);
    text->font_size.x = gmCamera_803DA630[8];
    text->font_size.y = gmCamera_803DA630[9];
    text->default_kerning = 1;
    HSD_SisLib_803A6530(3, 3, 4);
    gmCamera_801A2224((u8*) text, gmCamera_80479BC8.gcus.x20);
    HSD_SisLib_803A660C(3, 3, 5);
    HSD_SisLib_803A6368(text, 3);
    texts[2] = text;
    texts[0] = gmCamera_801A2334(0, gmCamera_803DA630[2], gmCamera_803DA630[3],
                                 gmCamera_803DA630[0], gmCamera_803DA630[1]);
    gmCamera_80479BC8.gcus.x48[1] =
        gmCamera_801A2334(1, gmCamera_803DA630[6], gmCamera_803DA630[7],
                          gmCamera_803DA630[4], gmCamera_803DA630[5]);
    x44 = gmCamera_80479BC8.gcus.x30;
    if (x44 >= (s32) gmCamera_80479BC8.gcus.x40) {
        x44 = gmCamera_80479BC8.gcus.x40;
    }
    gmCamera_80479BC8.gcus.x44 = x44;
}

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

void gmCamera_801A2BF0(void)
{
    HSD_JObj* jobj_a;
    HSD_JObj* jobj_b;
    f32 var_f1;
    f32 var_f31;
    gmCameraUnkStruct* gcus = &gmCamera_80479BC8.gcus;

    lb_80011E24(gcus->x8, &jobj_a, 9, -1);
    if ((s32) gcus->x44 == 1) {
        var_f1 = 1.0f;
    } else {
        var_f1 = 2.0f;
    }
    HSD_JObjReqAnimAll(jobj_a, var_f1);
    HSD_JObjAnimAll(jobj_a);
    HSD_ForeachAnim(jobj_a, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                    AOBJ_ARG_AOV, 0, 0);
    gcus->x18 = 0;
    lb_80011E24(gcus->x8, &jobj_b, 0xC, -1);
    if ((s32) gcus->x18 != 0) {
        var_f31 = 5.0f;
    } else {
        var_f31 = -5.0f;
    }
    HSD_JObjSetTranslateX(jobj_b, var_f31);
}

void gmCamera_801A2D44(void)
{
    HSD_JObj* jobj;
    HSD_JObj* jobj_b;
    f32 var_f31;
    gmCameraUnkStruct* gcus = &gmCamera_80479BC8.gcus;
    PAD_STACK(24);

    if ((lbSnap_8001D338(0) != 0) || (lbSnap_8001D338(1) != 0)) {
        gmCamera_801A3048(2);
        return;
    }
    if (HSD_PadCopyStatus[3].trigger & 0x1100) {
        if ((s32) gcus->x18 == 0) {
            lbAudioAx_80024030(1);
            gmCamera_801A3048(7);
            return;
        }
        lbAudioAx_80024030(0);
        gmCamera_801A3048(0);
        return;
    }
    if (HSD_PadCopyStatus[3].trigger & 0x200) {
        lbAudioAx_80024030(0);
        gmCamera_801A3048(0);
        return;
    }
    if ((HSD_PadCopyStatus[3].trigger & 0x40001) && (s32) gcus->x18 != 0) {
        lbAudioAx_80024030(2);
        gcus->x18 = 0;
        lb_80011E24(gcus->x8, &jobj, 0xC, -1);
        if ((s32) gcus->x18 != 0) {
            var_f31 = 5.0f;
        } else {
            var_f31 = -5.0f;
        }
        HSD_JObjSetTranslateX(jobj, var_f31);
    } else if ((HSD_PadCopyStatus[3].trigger & 0x80002) &&
               (s32) gcus->x18 != 1)
    {
        lbAudioAx_80024030(2);
        gcus->x18 = 1;
        lb_80011E24(gcus->x8, &jobj_b, 0xC, -1);
        if ((s32) gcus->x18 != 0) {
            var_f31 = 5.0f;
        } else {
            var_f31 = -5.0f;
        }
        HSD_JObjSetTranslateX(jobj_b, var_f31);
    }
}

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

void gmCamera_801A31FC(void)
{
    HSD_GObj* gobj_a;
    HSD_GObj* gobj_b;
    HSD_JObj* jobj_b;
    HSD_Joint** joint_a;
    DynamicModelDesc* mdl_b;
    gmCameraUnkStruct* gcus = &gmCamera_80479BC8.gcus;

    cmSnap_800316B4();
    gcus->x14 = 1;
    gcus->xC = 0;
    if (gmCamera_803DA6B4[gcus->xC].x4 != NULL) {
        gmCamera_803DA6B4[gcus->xC].x4();
    }
    gcus->ifvscam = lbArchive_LoadArchive("IfVsCam");
    joint_a = HSD_ArchiveGetPublicAddress(gcus->ifvscam, "IfCamera");
    gobj_a = GObj_Create(0xE, 0x10, 0);
    gcus->x4 = HSD_JObjLoadJoint(*joint_a);
    HSD_GObjObject_80390A70(gobj_a, HSD_GObj_804D7849, gcus->x4);
    GObj_SetupGXLink(gobj_a, HSD_GObj_JObjCallback, 0xB, 0);
    mdl_b =
        HSD_ArchiveGetPublicAddress(gcus->ifvscam, "IfCamera_Top_model_set");
    gobj_b = GObj_Create(0xE, 0x10, 0);
    jobj_b = HSD_JObjLoadJoint(mdl_b->joint);
    gcus->x8 = jobj_b;
    HSD_GObjObject_80390A70(gobj_b, HSD_GObj_804D7849, jobj_b);
    GObj_SetupGXLink(gobj_b, HSD_GObj_JObjCallback, 0xB, 0);
    gm_8016895C(jobj_b, mdl_b, 0);
    HSD_JObjReqAnimAll(jobj_b, 0.0f);
    HSD_JObjAnimAll(jobj_b);
    HSD_JObjSetFlagsAll(jobj_b, 0x10);
    HSD_GObj_SetupProc(gobj_b, fn_801A31D8, 0);
    gcus->x20 = 2;
    HSD_SisLib_803A62A0(3, "SdVsCam", "SIS_VsCameraData");
    gcus->x54 = HSD_SisLib_803A611C(3, NULL, 9, 0xD, 0, 0xE, 0, 0xB);
    gcus->x48[0] = NULL;
    gcus->x48[1] = NULL;
    gcus->x48[2] = NULL;
}

void gmCamera_801A33BC(void)
{
    HSD_Text* text;
    s32 sp10;
    s32 spC;

    gmCamera_801A25C8();
    gmCamera_80479C20.slot_a =
        gmCamera_801A2334(0, gmCamera_803DA758[2], gmCamera_803DA758[3],
                          gmCamera_803DA758[0], gmCamera_803DA758[1]);
    gmCamera_80479C20.slot_b =
        gmCamera_801A2334(1, gmCamera_803DA758[6], gmCamera_803DA758[7],
                          gmCamera_803DA758[4], gmCamera_803DA758[5]);
    gmCamera_801A253C(&sp10, &spC);
    text = HSD_SisLib_803A5ACC(3, gmCamera_801A2640(), gmCamera_803DA758[10],
                               gmCamera_803DA758[11], 0.0f, 914.2857f, 64.0f);
    gmCamera_80479C20.bottom_text = text;
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
    if (sp10 == 2) {
        goto label_13;
    }
    if (sp10 >= 2) {
        goto label_14;
    }
    if (sp10 >= 0) {
        goto label_11;
    }
    goto label_14;
label_11:
    HSD_SisLib_803A6530(3, 0x15, 0x11);
    gmCamera_801A2224((u8*) spC, spC);
    HSD_SisLib_803A660C(3, 0x15, 0x12);
    return;
label_13:
    HSD_SisLib_803A6530(3, 0x15, 0x13);
    return;
label_14:
    HSD_SisLib_803A6530(3, 0x15, 0x14);
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

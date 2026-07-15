#include "gmcamera.h"

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
#include "dolphin/pad.h"
#include "gm/gm_1601.h"
#include "gm/gm_16AE.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A45.h"
#include "gm/gmpause.h"
#include "gm/types.h"
#include "if/ifall.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardnew.h"
#include "lb/lbsnap.h"
#include "lb/lbspdisplay.h"
#include "mn/mnmain.h"
#include "sc/types.h"

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

static gmCameraUnkStruct gmCamera_VsCamUiState;

f32 gmCamera_803DA630[12] = {
    0.6f,   0.6f,   40.0f, 416.0f, 0.6f,  0.6f,
    340.0f, 416.0f, 0.6f,  0.6f,   40.0f, 44.0f,
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
    struct _gmCameraUnkStruct* gcu = &gmCamera_VsCamUiState;
    s32 blocks;
    s32 result;
    s32 group;
    s32 label;
    u32 status;
    int* blocks_ptr;
    u8* digits;

    text = HSD_SisLib_803A5ACC(3, gcu->x54, arg1, arg2, 0.0f, 640.0f, 32.0f);
    text->font_size.x = arg3;
    text->font_size.y = arg4;
    text->default_kerning = 1;
    if (arg0 == 0) {
        group = 6;
        digits = HSD_SisLib_803A6530(3, 6, 8);
    } else {
        group = 7;
        digits = HSD_SisLib_803A6530(3, 7, 9);
    }
    status = gcu->x24[arg0].x0;
    (void) status;
    switch (status) {
    case 0:
        if (gcu->x24[arg0].x8 == 0) {
            gcu->x24[arg0].xC = 3;
            HSD_SisLib_803A660C(3, group, 0xC);
        } else {
            gmCameraUnkStruct4* entries = gcu->x24;
            blocks_ptr = &entries[arg0].x4;
            blocks = *blocks_ptr;
            if (blocks == 0) {
                gcu->x24[arg0].xC = 2;
                HSD_SisLib_803A660C(3, group, 0xC);
            } else {
                if (blocks >= gcu->x20) {
                    if (arg0 != 0) {
                        result = 0;
                    } else {
                        result = 1;
                    }
                } else {
                    result = 2;
                }
                gcu->x24[arg0].xC = result;
                gmCamera_801A2224(digits, *blocks_ptr);
                if (*blocks_ptr != 1) {
                    label = 0xB;
                } else {
                    label = 0xA;
                }
                HSD_SisLib_803A660C(3, group, label);
            }
        }
        break;
    case 15:
        gcu->x24[arg0].xC = 5;
        HSD_SisLib_803A660C(3, group, 0x10);
        break;
    case 9:
        gcu->x24[arg0].xC = 4;
        HSD_SisLib_803A660C(3, group, 0xD);
        break;
    case 12:
        gcu->x24[arg0].xC = 4;
        HSD_SisLib_803A660C(3, group, 0xE);
        break;
    default:
        gcu->x24[arg0].xC = 4;
        HSD_SisLib_803A660C(3, group, 0xF);
        break;
    }
    HSD_SisLib_803A6368(text, group);
    return text;
}

void gmCamera_801A253C(s32* arg0, s32* arg1)
{
    s32 result =
        MIN(gmCamera_VsCamUiState.x24[0].xC, gmCamera_VsCamUiState.x24[1].xC);

    gmCamera_VsCamUiState.x44 = result;
    if (arg0 != NULL) {
        *arg0 = gmCamera_VsCamUiState.x44;
    }
    if (arg1 != NULL) {
        s32 var_r3;
        s32 var_r6 = 0;
        var_r3 = 0;
        if (gmCamera_VsCamUiState.x24[0].xC == 1) {
            var_r3 = gmCamera_VsCamUiState.x24[0].x4;
        }
        if (gmCamera_VsCamUiState.x24[1].xC == 0) {
            var_r6 = gmCamera_VsCamUiState.x24[1].x4;
        }
        *arg1 = MAX(var_r3, var_r6);
    }
}

void gmCamera_801A25C8(void)
{
    s32 i;
    for (i = 0; i < 2; i++) {
        gmCamera_VsCamUiState.x24[i].x0 = lbSnap_8001D40C(i);
        if (!gmCamera_VsCamUiState.x24[i].x0) {
            gmCamera_VsCamUiState.x24[i].x4 = lbSnap_8001D3B0(i);
            gmCamera_VsCamUiState.x24[i].x8 = lbSnap_8001D3CC(i);
        }
    }
}

s32 gmCamera_801A2640(void)
{
    return gmCamera_VsCamUiState.x54;
}

void gmCamera_801A2650(void)
{
    gmCamera_VsCamUiState.x20 = 2;
    HSD_SisLib_803A62A0(3, "SdVsCam", "SIS_VsCameraData");
    gmCamera_VsCamUiState.x54 = HSD_SisLib_803A611C(3, 0, 9, 13, 0, 14, 0, 11);
}

/// Per-mode handler table of the VS camera-mode state machine: one row of
/// { flags, on_enter, on_update } per mode index (gmCamera_VsCamUiState
/// .xC, switched via gmCamera_801A3048/801A3098/801A30E4).
gmCameraUnkFuncTable gmCamera_VsCamStateTable[9] = {
    { { 1, 0 }, gmCamera_801A26C0, gmCamera_801A2798 },
    { { 0, 4 }, gmCamera_801A2800, gmCamera_801A28AC },
    { { 0, 2 }, gmCamera_801A292C, gmCamera_801A2AAC },
    { { 0, 0x54 }, NULL, gmCamera_801A2BB0 },
    { { 0, 0x34 }, NULL, gmCamera_801A2BB0 },
    { { 0, 0x94 }, NULL, gmCamera_801A2BB0 },
    { { 0, 0x1204 }, gmCamera_801A2BF0, gmCamera_801A2D44 },
    { { 0, 0x1604 }, gmCamera_801A2FBC, gmCamera_801A2FFC },
    { { 0, 0x1A14 }, NULL, gmCamera_801A2BB0 },
};

static inline void gmCamera_801A26C0_FreeTexts(gmCameraUnkStruct* unk)
{
    s32 i;
    s32 zero;

    if (unk->x48[0] != NULL) {
        i = 0;
        zero = i;
        for (; i < 3; i++) {
            HSD_SisLib_803A5CC4(unk->x48[i]);
            unk->x48[i] = (HSD_Text*) zero;
        }
    }
}

static inline void gmCamera_FreeTextsWithZero(HSD_Text* zero)
{
    s32 i;

    if (gmCamera_VsCamUiState.x48[0] != NULL) {
        i = 0;
        for (; i < 3; i++) {
            HSD_SisLib_803A5CC4(gmCamera_VsCamUiState.x48[i]);
            gmCamera_VsCamUiState.x48[i] = zero;
        }
    }
}

void gmCamera_801A26C0(void)
{
    lbl_8046B6A0_t* hud;
    PAD_STACK(4);

    hud = gm_8016AE38();
    if (gm_801A45E8(3)) {
        gm_801A4674(3);
        if (gm_801A45E8(1)) {
            gm_801A0FEC(hud->pauser, 1);
        } else {
            lbAudioAx_80024E84(0);
            ifAll_802F33CC();
            HSD_PadRumbleUnpauseAll();
        }
        hud->hud_enabled = 1;
        hud->unk_3 = 0;
    }
    gmCamera_801A26C0_FreeTexts(&gmCamera_VsCamUiState);
}

void gmCamera_801A2798(void)
{
    unsigned int new_var;
    if (HSD_PadCopyStatus[3].trigger & 0x200) {
        new_var = gmCamera_VsCamUiState.x14 + 1;
        gmCamera_VsCamUiState.x14 = new_var % 2;
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
    gmCamera_VsCamUiState.x10 = 0;
    lb_80011E24(gmCamera_VsCamUiState.x8, &jobj, 2, -1);
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
    if (++gmCamera_VsCamUiState.x10 > 2) {
        void* snap_buf = cmSnap_80031618();
        gmCamera_VsCamUiState.x1C = snap_buf;
        if (snap_buf) {
            if (lbSnap_8001DC0C(gmCamera_VsCamUiState.x1C) != 0) {
                gmCamera_VsCamUiState.x20 = lbSnap_8001DF20();
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
    f32 new_var;
    f32* tbl = gmCamera_803DA630;
    PAD_STACK(16);

    gmCamera_FreeTextsWithZero(NULL);

    for (i = 0; i < 2; i++) {
        gmCamera_VsCamUiState.x24[i].x0 = lbSnap_8001D40C(i);
        if (!gmCamera_VsCamUiState.x24[i].x0) {
            gmCamera_VsCamUiState.x24[i].x4 = lbSnap_8001D3B0(i);
            gmCamera_VsCamUiState.x24[i].x8 = lbSnap_8001D3CC(i);
        }
    }

    text = HSD_SisLib_803A5ACC(3, gmCamera_VsCamUiState.x54, tbl[10], tbl[11],
                               0.0f, 640.0f, 32.0f);
    new_var = tbl[9];
    text->font_size.x = tbl[8];
    text->font_size.y = new_var;
    text->default_kerning = 1;
    gmCamera_801A2224(HSD_SisLib_803A6530(3, 3, 4), gmCamera_VsCamUiState.x20);
    HSD_SisLib_803A660C(3, 3, 5);
    HSD_SisLib_803A6368(text, 3);
    gmCamera_VsCamUiState.x48[2] = text;
    gmCamera_VsCamUiState.x48[0] =
        gmCamera_801A2334(0, tbl[2], tbl[3], tbl[0], tbl[1]);
    gmCamera_VsCamUiState.x48[1] =
        gmCamera_801A2334(1, tbl[6], tbl[7], tbl[4], tbl[5]);
    gmCamera_VsCamUiState.x44 =
        MIN(gmCamera_VsCamUiState.x24[0].xC, gmCamera_VsCamUiState.x24[1].xC);
}

void gmCamera_801A2AAC(void)
{
    s32 save_state;

    if ((lbSnap_8001D338(0) != 0) || (lbSnap_8001D338(1) != 0)) {
        gmCamera_801A3048(2);
    } else if (HSD_PadCopyStatus[3].trigger & 0x100) {
        lbAudioAx_80024030(1);
        switch (gmCamera_VsCamUiState.x44) {
        case 0:
        case 1:
            gmCamera_801A3048(6);
            return;
        }
        lbAudioAx_80024030(3);
        save_state = gmCamera_VsCamUiState.x44;
        switch (save_state) {
        case 5:
            gmCamera_801A3048(3);
            return;
        case 2:
        case 3:
            gmCamera_801A3048(4);
            return;
        default:
            gmCamera_801A3048(5);
            break;
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

f32 gmCamera_801A2BF0_get_translate_x(s32* px18)
{
    if (*px18 != 0) {
        return 5.0f;
    }
    return -5.0f;
}

static inline HSD_JObj* gmCamera_801A2BF0_get_jobj(HSD_JObj** px8)
{
    return *px8;
}

void gmCamera_801A2BF0(void)
{
    HSD_JObj* jobj_a;
    HSD_JObj* jobj_b;
    HSD_JObj** px8;
    s32* px18;
    f32 var_f1;
    f32 translate_x;
    gmCameraUnkStruct* gcus = &gmCamera_VsCamUiState;

    px8 = &gcus->x8;
    lb_80011E24(gmCamera_801A2BF0_get_jobj(px8), &jobj_a, 9, -1);
    if (gcus->x44 == 1) {
        var_f1 = 1.0f;
    } else {
        var_f1 = 2.0f;
    }
    HSD_JObjReqAnimAll(jobj_a, var_f1);
    HSD_JObjAnimAll(jobj_a);
    HSD_ForeachAnim(jobj_a, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                    AOBJ_ARG_AOV, 0, 0);
    px18 = &gcus->x18;
    *px18 = 0;
    lb_80011E24(*px8, &jobj_b, 0xC, -1);
    translate_x = gmCamera_801A2BF0_get_translate_x(px18);
    HSD_JObjSetTranslateX(jobj_b, translate_x);
}

static inline void gmCamera_801A2D44_update_selection(HSD_JObj** jobj_b,
                                                      HSD_JObj** jobj)
{
    gmCameraUnkStruct* gcus = &gmCamera_VsCamUiState;
    s32* px18;
    f32 translate_x;

    if (HSD_PadCopyStatus[3].trigger & 0x40001) {
        if (*(px18 = &gcus->x18) != 0) {
            lbAudioAx_80024030(2);
            *px18 = 0;
            lb_80011E24(gcus->x8, &(*jobj), 0xC, -1);
            if (*px18 != 0) {
                translate_x = 5.0f;
            } else {
                translate_x = -5.0f;
            }
            HSD_JObjSetTranslateX(*jobj, translate_x);
            return;
        }
    }
    if (HSD_PadCopyStatus[3].trigger & 0x80002) {
        if (*(px18 = &gcus->x18) != 1) {
            lbAudioAx_80024030(2);
            *px18 = 1;
            lb_80011E24(gcus->x8, &(*jobj_b), 0xC, -1);
            if (*px18 != 0) {
                translate_x = 5.0f;
            } else {
                translate_x = -5.0f;
            }
            HSD_JObjSetTranslateX(*jobj_b, translate_x);
        }
    }
}

void gmCamera_801A2D44(void)
{
    gmCameraUnkStruct* gcus = &gmCamera_VsCamUiState;
    HSD_JObj* jobj;
    HSD_JObj* jobj_b;
    PAD_STACK(16);

    if ((lbSnap_8001D338(0) != 0) || (lbSnap_8001D338(1) != 0)) {
        gmCamera_801A3048(2);
        return;
    }
    if (HSD_PadCopyStatus[3].trigger & 0x1100) {
        if (gcus->x18 == 0) {
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
    gmCamera_801A2D44_update_selection(&jobj_b, &jobj);
}

void gmCamera_801A2FBC(void)
{
    s32 chan;
    if (gmCamera_VsCamUiState.x44 == 0) {
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
    gmCamera_VsCamUiState.xC = i;
    if (gmCamera_VsCamStateTable[gmCamera_VsCamUiState.xC].x4 != NULL) {
        gmCamera_VsCamStateTable[gmCamera_VsCamUiState.xC].x4();
    }
}

void gmCamera_801A3098(void)
{
    if (gmCamera_VsCamStateTable[gmCamera_VsCamUiState.xC].x8 != NULL) {
        gmCamera_VsCamStateTable[gmCamera_VsCamUiState.xC].x8();
    }
}

void gmCamera_801A30E4(void)
{
    gmCameraUnkStruct* gcus = &gmCamera_VsCamUiState;
    s32* pxc = &gcus->xC;
    HSD_JObj** px8;
    s32 i;
    if ((gmCamera_VsCamStateTable[*pxc].flags.x0 != 0) && (gcus->x14 != 0) &&
        (gm_801A45E8(1) == 0))
    {
        HSD_JObjClearFlagsAll(gcus->x4, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(gcus->x4, JOBJ_HIDDEN);
    }
    px8 = &gcus->x8;
    HSD_JObjSetFlagsAll((0, gcus->x8), JOBJ_HIDDEN);
    for (i = 0; i < 16; i++) {
        if ((1 << i) & gmCamera_VsCamStateTable[*pxc].flags.x2) {
            HSD_JObj* jobj;
            lb_80011E24(*px8, &jobj, i, -1);
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
}

void fn_801A31D8(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(gobj->hsd_obj);
}

static inline void gmCamera_801A31FC_inline(DynamicModelDesc* mdl)
{
    HSD_JObj* jobj;
    HSD_GObj* gobj;
    gobj = GObj_Create(0xE, 0x10, 0);
    jobj = gmCamera_VsCamUiState.x8 = HSD_JObjLoadJoint(mdl->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    gm_8016895C(jobj, mdl, 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    HSD_GObj_SetupProc(gobj, fn_801A31D8, 0);
}

void gmCamera_801A31FC(void)
{
    PAD_STACK(24);

    cmSnap_800316B4();
    gmCamera_VsCamUiState.x14 = 1;
    gmCamera_VsCamUiState.xC = 0;
    if (gmCamera_VsCamStateTable[gmCamera_VsCamUiState.xC].x4 != NULL) {
        gmCamera_VsCamStateTable[gmCamera_VsCamUiState.xC].x4();
    }
    gmCamera_VsCamUiState.ifvscam = lbArchive_LoadArchive("IfVsCam");
    {
        HSD_Joint** joint_a = HSD_ArchiveGetPublicAddress(
            gmCamera_VsCamUiState.ifvscam, "IfCameraInfo_Top_model_set");
        HSD_GObj* gobj_a = GObj_Create(0xE, 0x10, 0);
        HSD_JObj* jobj_a = gmCamera_VsCamUiState.x4 =
            HSD_JObjLoadJoint(*joint_a);
        HSD_GObjObject_80390A70(gobj_a, HSD_GObj_804D7849, jobj_a);
        GObj_SetupGXLink(gobj_a, HSD_GObj_JObjCallback, 0xB, 0);
    }
    gmCamera_801A31FC_inline(HSD_ArchiveGetPublicAddress(
        gmCamera_VsCamUiState.ifvscam, "IfCamera_Top_model_set"));
    gmCamera_VsCamUiState.x20 = 2;
    HSD_SisLib_803A62A0(3, "SdVsCam", "SIS_VsCameraData");
    gmCamera_VsCamUiState.x54 =
        HSD_SisLib_803A611C(3, NULL, 9, 0xD, 0, 0xE, 0, 0xB);
    gmCamera_VsCamUiState.x48[0] = NULL;
    gmCamera_VsCamUiState.x48[1] = NULL;
    gmCamera_VsCamUiState.x48[2] = NULL;
}

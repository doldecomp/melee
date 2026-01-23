#include "mnsoundtest.h"

#include <platform.h>

#include "gm/gm_unsplit.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "mn/inlines.h"
#include "mn/types.h"
#include "sc/types.h"

#include <baselib/forward.h>

#include <dolphin/os.h>
#include <baselib/controller.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>

extern HSD_PadStatus HSD_PadCopyStatus[4];

static HSD_GObj* mnSoundTest_804D6C40;
static u8 mnSoundTest_804D6C44;
static s32 mnSoundTest_804D6C48;
static s32 mnSoundTest_804D6C4C;

void fn_8024B2B0(HSD_GObj*);

#if 0
Vec3 mnSoundTest_803EF0A8[] = {
    { 0, 19, -0.1, },
    { 20, 39, -0.1, },
    { 0, 20, -0.1, },
    { 0, 0, -0.1, },
    { 0, 200, 0, },
    { 0, 10, -0.1, }
};
#else
Vec3 vec_0 = {
    0,
    19,
    -0.1,
};
Vec3 vec_1 = {
    20,
    39,
    -0.1,
};
Vec3 vec_2 = {
    0,
    20,
    -0.1,
};
Vec3 vec_3 = {
    0,
    0,
    -0.1,
};
Vec3 vec_4 = {
    0,
    200,
    0,
};
Vec3 vec_5 = {
    0,
    10,
    -0.1,
};
Vec3 vec_6 = { -2, -6.6, 0 };
Vec3 vec_7 = { -1.7, -4.7, 0 };
#endif

f32 floats_2[] = { -1.7, 2 };

typedef struct {
    u16 text_id;
    u32 idx;
} soundtest_data;

u8 text_ids[] = { 0x2A, 0x02, 0x2D, 0x20, 0x15, 0x16, 0x2F, 0x34, 0x21, 0x33,
                  0x32, 0x1F, 0x17, 0x04, 0x31, 0x2B, 0x2C, 0x24, 0x01, 0x28,
                  0x13, 0x19, 0x1A, 0x1B, 0x1C, 0x18, 0x3A, 0x25, 0x27, 0x26,
                  0x3C, 0x2E, 0x3B, 0x00, 0x37, 0x29, 0x3D, 0x3E, 0x0E, 0x07,
                  0x0D, 0x11, 0x12, 0x0C, 0x09, 0x10, 0x0A, 0x0F, 0x08, 0x3F,
                  0x0B, 0x38, 0x40, 0x41, 0x22, 0x35, 0x4F, 0x39, 0x43, 0x44,
                  0x36, 0x45, 0x46, 0x23, 0x1D, 0x1E, 0x05, 0x06, 0x03, 0x14,
                  0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x30, 0x42 };

soundtest_data data_2[] = {
    { 0x00E7, 0x01 }, { 0x00E8, 0x03 }, { 0x00E9, 0x04 }, { 0x00EA, 0x05 },
    { 0x00EB, 0x06 }, { 0x00ED, 0x0A }, { 0x00EE, 0x0B }, { 0x00EF, 0x0D },
    { 0x00F0, 0x0E }, { 0x00F1, 0x10 }, { 0x00F2, 0x11 }, { 0x00F3, 0x13 },
    { 0x00F4, 0x14 }, { 0x00F5, 0x15 }, { 0x00F6, 0x16 }, { 0x00F7, 0x17 },
    { 0x00F8, 0x18 }, { 0x00F9, 0x19 }, { 0x00FA, 0x1D }, { 0x00FB, 0x1F },
    { 0x00FC, 0x20 }, { 0x00FD, 0x32 }, { 0x00FE, 0x22 }, { 0x00FF, 0x23 },
    { 0x0100, 0x28 }, { 0x0101, 0x29 }, { 0x0102, 0x2A }, { 0x0103, 0x2B },
    { 0x0104, 0x2C }, { 0x0105, 0x2D }, { 0x0106, 0x2E }, { 0x0107, 0x31 },
    { 0x0108, 0x21 }, { 0x0109, 0x33 }, { 0x010A, 0x34 }, { 0x010B, 0x35 },
    { 0x010C, 0x38 }, { 0x010D, 0x39 }, { 0x010E, 0x3A }, { 0x010F, 0x3B },
    { 0x0110, 0x3C }, { 0x0111, 0x3D }, { 0x0112, 0x3E }, { 0x0113, 0x40 },
    { 0x0114, 0x41 }, { 0x0115, 0x42 }, { 0x0116, 0x4A }, { 0x0117, 0x4B },
    { 0x0118, 0x4C }, { 0x0119, 0x54 }, { 0x011A, 0x5F }, { 0x011B, 0x60 },
    { 0x011C, 0x61 }, { 0x011D, 0x36 }, { 0x011E, 0x00 }, { 0x011F, 0x37 },
    { 0x0120, 0x50 }, { 0x0121, 0x53 }, { 0x0122, 0x1E }, { 0x0123, 0x3F },
    { 0x0124, 0x4D }, { 0x0125, 0x07 }, { 0x0126, 0x02 }, { 0x0127, 0x0F },
    { 0x0128, 0x51 }, { 0x0129, 0x4E }, { 0x012A, 0x08 }, { 0x012B, 0x26 },
    { 0x012C, 0x27 }, { 0x012F, 0x5D }, { 0x0130, 0x5E }, { 0x0132, 0x46 },
    { 0x0133, 0x47 }, { 0x0134, 0x48 }, { 0x0135, 0x43 }, { 0x0136, 0x44 },
    { 0x0137, 0x45 }, { 0x0138, 0x2F }, { 0x0139, 0x30 }, { 0x013D, 0x25 }
};

u8 data_3[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
                15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };

u32 data_4[] = { 25, 8,  1,  6,  16, 17, 4,  2,  13, 0,  11, 5,  12, 14, 18,
                 7,  15, 10, 9,  3,  21, 20, 24, 19, 23, 22, 29, 28, 26, 27,
                 6,  8,  11, 18, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 13,
                 25, 26, 28, 27, 10, 7,  9,  31, 23, 30, 4,  0,  39, 3,  32 };

void mnSoundTest_8024A790(HSD_GObj* arg0)
{
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f30;
    f32 temp_f31;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r3;
    s32 temp_r3_2;

    soundtest_user_data* temp_r31 = (soundtest_user_data*) arg0->user_data;
    // control the volume by holding down L trigger
    temp_f31 = 1.0f * (1.0f - HSD_PadCopyStatus->nml_analogL) *
               (1.0f - HSD_PadCopyStatus[1].nml_analogL) *
               (1.0f - HSD_PadCopyStatus[2].nml_analogL) *
               (1.0f - HSD_PadCopyStatus[3].nml_analogL);
    // R trigger doesn't seem to do anything
    temp_f30 = 1.0f * (1.0f - HSD_PadCopyStatus->nml_analogR) *
               (1.0f - HSD_PadCopyStatus[1].nml_analogR) *
               (1.0f - HSD_PadCopyStatus[2].nml_analogR) *
               (1.0f - HSD_PadCopyStatus[3].nml_analogR);
    if ((temp_f31 < 0.9f) || (temp_r31->unk8 < 1.0f)) {
        temp_f1 = temp_f31 * (f32) gm_801601C4(gmMainLib_8015ED74());
        temp_r30 = (s32) (temp_r31->unk8 * temp_f1);
        lbAudioAx_80024614(temp_r30);
        mnSoundTest_804D6C48 = temp_r30;
    } else {
        temp_r3 = gm_801601C4(gmMainLib_8015ED74());
        if (temp_r3 != (s32) mnSoundTest_804D6C48) {
            lbAudioAx_80024614(temp_r3);
            mnSoundTest_804D6C48 = temp_r3;
        }
    }
    if ((temp_f30 < 0.9f) || (temp_r31->unkC < 1.0f)) {
        temp_f1_2 = temp_f30 * gm_80160244(gmMainLib_8015ED74());
        temp_r30_2 = (s32) (temp_r31->unkC * temp_f1_2);
        lbAudioAx_800245F4(temp_r30_2);
        mnSoundTest_804D6C4C = temp_r30_2;
        return;
    }
    temp_r3_2 = gm_80160244(gmMainLib_8015ED74());
    if (temp_r3_2 != (s32) mnSoundTest_804D6C4C) {
        lbAudioAx_800245F4(temp_r3_2);
        mnSoundTest_804D6C4C = temp_r3_2;
    }
}

void mnSoundTest_8024A958(Soundtest_GObj* arg0)
{
    char string[3];
    HSD_Text* temp_r3;
    HSD_Text* temp_r3_2;
    HSD_Text* temp_r3_3;
    HSD_Text* temp_r3_4;
    soundtest_user_data* temp_r30;

    temp_r30 = arg0->user_data;
    if (temp_r30->unk14 != NULL) {
        HSD_SisLib_803A5CC4(temp_r30->unk14);
    }
    if (temp_r30->unk18 != NULL) {
        HSD_SisLib_803A5CC4(temp_r30->unk18);
    }
    temp_r3_3 =
        HSD_SisLib_803A5ACC(0, 0, vec_6.x, vec_6.y, 18.0f, 350.0f, 10.0f);
    temp_r30->unk14 = temp_r3_3;
    temp_r3_3->font_size.x = 0.035f;
    temp_r3_3->font_size.y = 0.035f;
    temp_r3_3->default_alignment = 2;
    HSD_SisLib_803A6368(temp_r3_3, data_2[text_ids[temp_r30->unk1]].text_id);
    temp_r3_4 = HSD_SisLib_803A6754(0, 0);
    temp_r30->unk18 = temp_r3_4;
    temp_r3_4->pos_x = 0.0f; // mnSoundTest_803EF0A8[0xB];
    temp_r3_4->pos_y = 0.0f; // mnSoundTest_803EF0A8[0xB];
    temp_r3_4->pos_z = 18.0f;
    temp_r3_4->font_size.x = 0.04f;
    temp_r3_4->font_size.y = 0.04f;
    mn_8022EA08((char*) &string, temp_r30->unk1);
    temp_r3_4->default_alignment = 1;
    HSD_SisLib_803A6B98(temp_r3_4, 0.0f, 0.0f, string);
}

f32 mn_8022F298(HSD_JObj*);

void mnSoundTest_8024AA70(HSD_GObj* arg0, u8 arg1)
{
    HSD_JObj* sp38;
    HSD_JObj* sp34;
    char string[3];
    HSD_JObj* temp_r31;
    HSD_Text* temp_r3;
    HSD_Text* temp_r3_2;
    HSD_Text* temp_r3_4;
    f32 temp_f1;
    void* temp_r30;
    void* temp_r30_2;
    Vec3* temp_r3_3;

    HSD_JObj* jobj = GET_JOBJ(arg0);
    soundtest_user_data* user_data = arg0->user_data;
    lb_80011E24(jobj, &sp38, 0x13, -1);
    lb_80011E24(jobj, &sp34, 0x14, -1);
    if (arg1 == 2) {
        soundtest_user_data* temp_r30_2 = arg0->user_data;
        temp_r3 = temp_r30_2->unk1C;
        if (temp_r3 != NULL) {
            HSD_SisLib_803A5CC4(temp_r3);
        }
        temp_r3_2 = HSD_SisLib_803A6754(0, 0);
        temp_r3_3 = &vec_7;
        temp_r30_2->unk1C = temp_r3_2;
        temp_f1 = temp_r3_3->y;
        temp_r3_2->pos_x = temp_r3_3->x;
        temp_r3_2->pos_y = temp_f1;
        temp_r3_2->pos_z = 18.0f;
        temp_r3_2->font_size.x = 0.04f;
        temp_r3_2->font_size.y = 0.04f;
        mn_8022EA08((char*) &string, temp_r30_2->unk4);
        temp_r3_2->default_alignment = 1;
        HSD_SisLib_803A6B98(temp_r3_2, 0.0f, 0.0f, string);
        HSD_JObjClearFlagsAll(sp38, 0x10U);
    } else {
        temp_r3_4 = user_data->unk1C;
        if (temp_r3_4 != NULL) {
            HSD_SisLib_803A5CC4(temp_r3_4);
            user_data->unk1C = NULL;
        }
        HSD_JObjSetFlagsAll(sp38, 0x10U);
    }
    HSD_JObjReqAnimAll(sp34, (f32) (arg1 == 1));
    mn_8022F3D8(sp34, 0xFFU, 0x420);
    HSD_JObjAnimAll(sp34);
}

void mnSoundTest_8024ABF8(HSD_GObj* arg0, u8 arg1)
{
    HSD_JObj* sp1C;
    HSD_JObj* sp18;
    HSD_JObj* sp14;
    HSD_JObj* temp_r31;
    f32 temp_f31;
    f32 temp_f30;

    temp_r31 = GET_JOBJ(arg0);
    lb_80011E24(temp_r31, &sp18, 2, -1);
    lb_80011E24(temp_r31, &sp1C, 5, -1);
    lb_80011E24(temp_r31, &sp14, 4, -1);
    temp_f31 = mn_8022F298(sp18);
    temp_f30 = mn_8022F298(sp14);
    HSD_JObjReqAnimAll(sp18, (f32) arg1);
    mn_8022F3D8(sp18, 0xFFU, 0x420);
    HSD_JObjAnimAll(sp18);
    HSD_JObjReqAnim(sp18, temp_f31);
    HSD_JObjAnim(sp18);
    HSD_JObjReqAnimAll(sp14, temp_f30);
    mn_8022F3D8(sp14, 0xFFU, MOBJ_MASK);
    HSD_JObjAnimAll(sp14);
    if (arg1 != 0) {
        HSD_JObjReqAnimAll(sp1C, vec_2.x);
    } else {
        HSD_JObjReqAnimAll(sp1C, vec_3.y);
    }
    mn_8022F3D8(sp1C, 0xFFU, MOBJ_MASK);
    HSD_JObjAnimAll(sp1C);
}

void mnSoundTest_8024AD58(HSD_GObj* arg0, u8 arg1)
{
    HSD_JObj* sp1C;
    HSD_JObj* sp18;
    HSD_JObj* sp14;
    HSD_JObj* temp_r30;
    f32 temp_f31;
    u8 temp_r0;

    temp_r30 = GET_JOBJ(arg0);
    lb_80011E24(temp_r30, &sp18, 0xB, -1);
    lb_80011E24(temp_r30, &sp1C, 0xE, -1);
    lb_80011E24(temp_r30, &sp14, 0xD, -1);
    temp_r0 = !!arg1;
    temp_f31 = mn_8022F298(sp18);
    HSD_JObjReqAnimAll(sp18, temp_r0);
    mn_8022F3D8(sp18, 0xFFU, 0x420);
    HSD_JObjAnimAll(sp18);
    HSD_JObjReqAnimAll(sp18, temp_f31);
    HSD_JObjAnim(sp18);
    HSD_JObjReqAnimAll(sp14, vec_5.y);
    mn_8022F3D8(sp14, 0xFFU, MOBJ_MASK);
    HSD_JObjAnimAll(sp14);
    if (temp_r0 != 0) {
        HSD_JObjReqAnimAll(sp1C, vec_2.x);
    } else {
        HSD_JObjReqAnimAll(sp1C, vec_3.y);
    }
    mn_8022F3D8(sp1C, 0xFFU, MOBJ_MASK);
    HSD_JObjAnimAll(sp1C);
    mnSoundTest_8024AA70(arg0, arg1);
}

static inline void fn_8024AED0_inline(HSD_GObj* arg0)
{
    char string[3];
    HSD_Text* temp_r3_6;
    soundtest_user_data* temp_r28_4 = mnSoundTest_804D6C40->user_data;
    HSD_Text* temp_r3_5 = temp_r28_4->unk1C;
    if (temp_r3_5 != NULL) {
        HSD_SisLib_803A5CC4(temp_r3_5);
    }
    temp_r3_6 = HSD_SisLib_803A6754(0, 0);
    temp_r28_4->unk1C = temp_r3_6;
    temp_r3_6->pos_x = vec_6.x;
    temp_r3_6->pos_y = vec_6.y;
    temp_r3_6->pos_z = 18.0f;
    temp_r3_6->font_size.x = 0.04f;
    temp_r3_6->font_size.y = 0.04f;
    mn_8022EA08((char*) &string, temp_r28_4->unk4);
    temp_r3_6->default_alignment = 1;
    HSD_SisLib_803A6B98(temp_r3_6, 0.0f, 0.0f, string);
}

void fn_8024AED0(HSD_GObj* arg0)
{
    HSD_JObj* sp7C;
    void* sp50;
    HSD_GObjProc* temp_r3_2;
    HSD_Text* temp_r3_7;
    HSD_Text* temp_r3_8;
    f32 temp_f1;
    f32 temp_f1_2;
    s32 temp_r28_3;
    s32 temp_r31;
    s32 temp_r3_3;
    s32 temp_r5;
    u16 temp_r30;
    u16 temp_r4;
    u8 temp_r28_2;
    soundtest_user_data* temp_r26;
    soundtest_user_data* temp_r27;
    soundtest_user_data* temp_r28_5;
    HSD_JObj* temp_r27_2;
    soundtest_user_data* temp_r3_4;
    u64 events;

    soundtest_user_data* user_data = arg0->user_data;
    if ((u16) mn_804D6BC8.cooldown != 0) {
        Menu_DecrementAnimTimer();
        return;
    }
    events = Menu_GetAllInputs();
    if (events & MenuInput_Back) {
        lbAudioAx_80023694();
        user_data->unk0 = 1U;
        mnSoundTest_8024AA70(mnSoundTest_804D6C40, user_data->unk0);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        temp_r3_2 = HSD_GObjProc_8038FD54(arg0, fn_8024B2B0, 0U);
        temp_r3_2->flags_3 = HSD_GObj_804D783C;
        return;
    }
    temp_r26 = mnSoundTest_804D6C40->user_data;
    temp_f1 = temp_r26->unk8;
    if (temp_f1 < 1.0f) {
        temp_r26->unk8 = (f32) (temp_f1 - 0.02f);
        if (temp_r26->unk8 <= 0.0f) {
            temp_r26->unk8 = 1.0f;
            temp_r27 = mnSoundTest_804D6C40->user_data;
            lbAudioAx_800236DC();
            temp_r27->unk2 = 0x50;
        }
    }
    temp_f1_2 = temp_r26->unkC;
    if (temp_f1_2 < 1.0f) {
        temp_r26->unkC = (f32) (temp_f1_2 - 0.02f);
        if (temp_r26->unkC <= 0.0f) {
            temp_r26->unkC = 1.0f;
            lbAudioAx_80023694();
        }
    }
    if ((u8) mnSoundTest_804D6C44 == 0) {
        temp_r3_3 = lbAudioAx_80023968(data_3[user_data->unk3]);
        temp_r5 = 0 & 0;
        if (events & MenuInput_RTrigger) {
            temp_r30 = user_data->unk4;
            temp_r28_2 = data_3[user_data->unk3];
            temp_r3_4 = mnSoundTest_804D6C40->user_data;
            temp_r27_2 = mnSoundTest_804D6C40->hsd_obj;
            temp_r3_4->unkC = 1.0f;
            mnSoundTest_804D6C4C =
                lbAudioAx_800245F4(gm_80160244(gmMainLib_8015ED74()));
            temp_r28_3 = lbAudioAx_80023A44(temp_r28_2, temp_r30);
            lbAudioAx_80023694();
            lbAudioAx_80023B24(temp_r28_3);
            lb_80011E24(temp_r27_2, &sp7C, 0xD, -1);
            HSD_JObjReqAnimAll(sp7C, vec_4.x);
            mn_8022F3D8(sp7C, 0xFFU, MOBJ_MASK);
            HSD_JObjAnimAll(sp7C);
        } else if (events & MenuInput_LTrigger) {
            if (user_data->unkC == 1.0f) {
                user_data->unkC = 0.98f;
            }
        } else if (events & MenuInput_Left) {
            temp_r4 = user_data->unk4;
            if (temp_r4 != 0) {
                user_data->unk4 = (u16) (temp_r4 - 1);
            } else {
                user_data->unk4 = (u16) (temp_r3_3 - 1);
            }
            fn_8024AED0_inline(arg0);
        } else if (events & MenuInput_Right) {
            user_data->unk4 += 1;
            if (user_data->unk4 >= temp_r3_3) {
                user_data->unk4 = 0;
            }
            fn_8024AED0_inline(arg0);
        }
        mnSoundTest_8024A790(mnSoundTest_804D6C40);
    }
}

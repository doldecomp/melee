#include "mnsoundtest.h"

#include <platform.h>

#include "gm/gm_unsplit.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"

#include "mn/forward.h"

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

typedef struct {
    void* joint;
    void* animjoint;
    void* matanim_joint;
    void* shapeanim_joint;
} SoundTestModelDesc;

void fn_8024B2B0(HSD_GObj*);
static SoundTestModelDesc mnSoundTest_804A08C8;

AnimLoopSettings vec_0 = {
    0,
    19,
    -0.1,
};
AnimLoopSettings vec_1 = {
    20,
    39,
    -0.1,
};
AnimLoopSettings vec_2 = {
    0,
    20,
    -0.1,
};
AnimLoopSettings vec_3 = {
    0,
    0,
    -0.1,
};
AnimLoopSettings vec_4 = {
    0,
    200,
    0,
};
AnimLoopSettings vec_5 = {
    0,
    10,
    -0.1,
};
Vec3 vec_6 = { -2, -6.6, 0 };
Vec3 vec_7 = { -1.7, -4.7, 0 };

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

static char mnSoundTest_803EF4F4[] = "Can't get user_data.\n";
static char mnSoundTest_803EF50C[] = "mnsoundtest.c";
static char mnSoundTest_803EF51C[] = "user_data";
static char mnSoundTest_803EF528[] = "MenMainConTs_Top_joint";
static char mnSoundTest_803EF540[] = "MenMainConTs_Top_animjoint";
static char mnSoundTest_803EF55C[] = "MenMainConTs_Top_matanim_joint";
static char mnSoundTest_803EF57C[] = "MenMainConTs_Top_shapeanim_joint";

void mnSoundTest_8024A790(HSD_GObj* arg0)
{
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
    PAD_STACK(24);
    if ((temp_f31 < 0.9f) || (temp_r31->unk8 < 1.0f)) {
        temp_r30 =
            (s32) (temp_r31->unk8 *
                   (temp_f31 * (f32) gm_801601C4(gmMainLib_8015ED74())));
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
        temp_r30_2 =
            (s32) (temp_r31->unkC *
                   (temp_f30 * gm_80160244(gmMainLib_8015ED74())));
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
    f32 temp_f1;
    HSD_Text* temp_r3;
    HSD_Text* temp_r3_2;
    HSD_Text* temp_r3_3;
    HSD_Text* temp_r3_4;
    soundtest_user_data* temp_r30;
    PAD_STACK(16);

    PAD_STACK(4);

    temp_r30 = arg0->user_data;
    temp_r3 = temp_r30->unk14;
    if (temp_r3 != NULL) {
        HSD_SisLib_803A5CC4(temp_r3);
    }
    temp_r3_2 = temp_r30->unk18;
    if (temp_r3_2 != NULL) {
        HSD_SisLib_803A5CC4(temp_r3_2);
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
    temp_f1 = vec_7.y;
    temp_r3_4->pos_x = vec_7.x;
    temp_r3_4->pos_y = temp_f1;
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
    u8 _padA[16];
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
        temp_r30_2->unk1C = temp_r3_2;
        temp_f1 = vec_7.y;
        temp_r3_2->pos_x = vec_7.x;
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
        HSD_JObjReqAnimAll(sp1C, vec_2.start_frame);
    } else {
        HSD_JObjReqAnimAll(sp1C, vec_3.end_frame);
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
    HSD_JObjReqAnimAll(sp14, vec_5.end_frame);
    mn_8022F3D8(sp14, 0xFFU, MOBJ_MASK);
    HSD_JObjAnimAll(sp14);
    if (temp_r0 != 0) {
        HSD_JObjReqAnimAll(sp1C, vec_2.start_frame);
    } else {
        HSD_JObjReqAnimAll(sp1C, vec_3.end_frame);
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
    PAD_STACK(88);
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
        temp_r3_2 = HSD_GObj_SetupProc(arg0, fn_8024B2B0, 0U);
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
            HSD_JObjReqAnimAll(sp7C, vec_4.start_frame);
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

void fn_8024B2B0(HSD_GObj* arg0)
{
    HSD_JObj* sp54;
    HSD_JObj* sp48;
    HSD_JObj* sp3C;
    HSD_GObjProc* proc;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    soundtest_user_data* user_data;
    soundtest_user_data* menu_data;
    u32 inputs;
    u8 state;
    u8 anim_idx;
    u16 sound_id;
    s32 audio_id;
    s32 sound_kind;

    user_data = mnSoundTest_804D6C40->user_data;
    if ((u16) mn_804D6BC8.cooldown != 0) {
        mn_804D6BC8.cooldown -= 1;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }
    inputs = mn_80229624(4U);
    mn_804A04F0.buttons = inputs;
    mn_804A04F0.x10 = 0;
    if (inputs & 0x20) {
        mn_804A04F0.entering_menu = 0;
        mn_80229894(5, 2U, 3);
        lbAudioAx_80023694();
        gm_801603B0();
        lbAudioAx_80023F28(gmMainLib_8015ECB0());
        return;
    }
    if (inputs & 3) {
        state = 0;
        if ((u8) user_data->unk0 == 0) {
            state = 1;
        }
        user_data->unk0 = state;
        gobj = mnSoundTest_804D6C40;
        mnSoundTest_8024ABF8(gobj, (u8) (-(s32) state == 0));
        mnSoundTest_8024AD58(gobj, state);
        return;
    }
    menu_data = mnSoundTest_804D6C40->user_data;
    if (menu_data->unk8 < 1.0f) {
        menu_data->unk8 -= 0.02f;
        if (menu_data->unk8 <= 0.0f) {
            menu_data->unk8 = 1.0f;
            menu_data = mnSoundTest_804D6C40->user_data;
            lbAudioAx_800236DC();
            menu_data->unk2 = 0x50;
        }
    }
    if (menu_data->unkC < 1.0f) {
        menu_data->unkC -= 0.02f;
        if (menu_data->unkC <= 0.0f) {
            menu_data->unkC = 1.0f;
            lbAudioAx_80023694();
        }
    }
    if ((u8) mnSoundTest_804D6C44 != 0) {
        return;
    }
    if ((u8) user_data->unk0 == 0) {
        if (inputs & 0x200) {
            sound_id = user_data->unk1;
            if ((u8) user_data->unk2 == sound_id) {
                menu_data = mnSoundTest_804D6C40->user_data;
                lbAudioAx_800236DC();
                menu_data->unk2 = 0x50;
            } else {
                menu_data = mnSoundTest_804D6C40->user_data;
                jobj = GET_JOBJ(mnSoundTest_804D6C40);
                menu_data->unk8 = 1.0f;
                audio_id = gm_801601C4(gmMainLib_8015ED74());
                lbAudioAx_80024614(audio_id);
                mnSoundTest_804D6C48 = audio_id;
                sound_kind = data_2[text_ids[sound_id]].idx;
                lbAudioAx_80023F28(sound_kind);
                menu_data->unk2 = sound_id;
                lb_80011E24(jobj, &sp54, 4, -1);
                HSD_JObjReqAnimAll(sp54, mn_8022F298(sp54));
                mn_8022F3D8(sp54, 0xFFU, MOBJ_MASK);
                HSD_JObjAnimAll(sp54);
                if (lbAudioAx_80023090(sound_kind) != 0) {
                    gmMainLib_8015ED68(sound_kind);
                }
            }
        } else if (inputs & 0x100) {
            if (user_data->unk8 == 1.0f) {
                user_data->unk8 = 0.98f;
            }
        } else if (inputs & 4) {
            if (user_data->unk1 != 0) {
                user_data->unk1 -= 1;
            } else {
                user_data->unk1 = 0x4F;
            }
            mnSoundTest_8024A958((Soundtest_GObj*) mnSoundTest_804D6C40);
        } else if (inputs & 8) {
            user_data->unk1 += 1;
            if ((u8) user_data->unk1 >= 0x50U) {
                user_data->unk1 = 0U;
            }
            mnSoundTest_8024A958((Soundtest_GObj*) mnSoundTest_804D6C40);
        }
    } else {
        if (inputs & 0x200) {
            user_data->unk0 = 2U;
            mnSoundTest_8024AA70(mnSoundTest_804D6C40, user_data->unk0);
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            proc = HSD_GObj_SetupProc(arg0, fn_8024AED0, 0U);
            proc->flags_3 = HSD_GObj_804D783C;
            return;
        }
        if (inputs & 4) {
            if (user_data->unk3 != 0) {
                user_data->unk3 -= 1;
            } else {
                user_data->unk3 = 0x1D;
            }
            user_data->unk4 = 0;
            anim_idx = data_4[user_data->unk3];
            lb_80011E24(GET_JOBJ(mnSoundTest_804D6C40), &sp48, 0x15, -1);
            HSD_JObjReqAnimAll(sp48, (f32) data_4[anim_idx + 30]);
            mn_8022F3D8(sp48, 0xFFU, 0xA0);
            HSD_JObjAnimAll(sp48);
        } else if (inputs & 8) {
            user_data->unk3 += 1;
            if ((s32) user_data->unk3 >= 0x1E) {
                user_data->unk3 = 0U;
            }
            user_data->unk4 = 0;
            anim_idx = data_4[user_data->unk3];
            lb_80011E24(GET_JOBJ(mnSoundTest_804D6C40), &sp3C, 0x15, -1);
            HSD_JObjReqAnimAll(sp3C, (f32) data_4[anim_idx + 30]);
            mn_8022F3D8(sp3C, 0xFFU, 0xA0);
            HSD_JObjAnimAll(sp3C);
        }
    }
    mnSoundTest_8024A790(mnSoundTest_804D6C40);
}

void fn_8024B7E4(HSD_GObj* arg0)
{
    HSD_JObj* sp20;
    HSD_JObj* sp1C;
    HSD_JObj* sp18;
    AnimLoopSettings* temp_r31;
    HSD_JObj* temp_r30;
    f32 temp_f31;

    PAD_STACK(8);

    temp_r30 = GET_JOBJ(arg0);
    (lb_80011E24(temp_r30, &sp20, 0xB, -1),
     lb_80011E24(temp_r30, &sp1C, 2, -1),
     lb_80011E24(temp_r30, &sp18, 1, -1));
    temp_f31 = mn_8022EFD8(sp20, &vec_1);
    mn_8022EFD8(sp1C, &vec_1);
    mn_8022EFD8(sp18, &vec_1);
    if (temp_f31 == vec_1.end_frame) {
        HSD_GObjPLink_80390228(arg0);
    }
}

void fn_8024B8B4(HSD_GObj* arg0, f32 farg0)
{
    HSD_JObj* sp20;
    HSD_JObj* sp1C;
    HSD_JObj* sp18;
    HSD_JObj* sp14;
    HSD_JObj* sp10;
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    soundtest_user_data* user_data;
    HSD_Text* text;
    f32 var_f1;

    var_f1 = farg0;
    user_data = arg0->user_data;
    jobj = GET_JOBJ(arg0);
    if ((u8) mn_804A04F0.cur_menu != 0x1B) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(arg0, fn_8024B7E4, 0U);
        proc->flags_3 = HSD_GObj_804D783C;
        text = user_data->unk10;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
            user_data->unk10 = NULL;
        }
        text = user_data->unk14;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
            user_data->unk14 = NULL;
        }
        text = user_data->unk18;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
            user_data->unk18 = NULL;
        }
        text = user_data->unk1C;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
            user_data->unk1C = NULL;
        }
        (lb_80011E24(jobj, &sp1C, 0xB, -1), lb_80011E24(jobj, &sp18, 2, -1),
         lb_80011E24(jobj, &sp14, 1, -1));
        HSD_JObjReqAnim(sp1C, vec_1.start_frame);
        HSD_JObjAnim(sp1C);
        HSD_JObjReqAnim(sp18, vec_1.start_frame);
        HSD_JObjAnim(sp18);
        HSD_JObjReqAnim(sp14, vec_1.start_frame);
        HSD_JObjAnim(sp14);
        return;
    }
    if ((u8) user_data->unk0 == 0) {
        lb_80011E24(jobj, &sp20, 5, -1);
        var_f1 = mn_8022EC18(sp20, (AnimLoopSettings*) &vec_2, MOBJ_MASK);
    }
    if ((u8) user_data->unk0 != 0) {
        lb_80011E24(jobj, &sp20, 0xE, -1);
        var_f1 = mn_8022EC18(sp20, (AnimLoopSettings*) &vec_2, MOBJ_MASK);
    }
    if ((u8) user_data->unk2 != 0x50) {
        lb_80011E24(jobj, &sp10, 4, -1);
        var_f1 = mn_8022EC18(sp10, (AnimLoopSettings*) &vec_4, MOBJ_MASK);
    }
    lb_80011E24(jobj, &sp10, 0xD, -1);
    mn_8022EC18(sp10, (AnimLoopSettings*) &vec_5, MOBJ_MASK);
}

void fn_8024BAF0(HSD_GObj* arg0)
{
    HSD_JObj* sp1C;
    HSD_JObj* sp18;
    HSD_JObj* sp14;
    HSD_GObjProc* proc;
    HSD_GObjProc* proc2;
    HSD_JObj* jobj;
    soundtest_user_data* user_data;
    HSD_Text* text;
    f32 temp_f31;

    PAD_STACK(8);

    jobj = GET_JOBJ(arg0);
    (lb_80011E24(jobj, &sp1C, 0xB, -1), lb_80011E24(jobj, &sp18, 2, -1),
     lb_80011E24(jobj, &sp14, 1, -1));
    if ((u8) mn_804A04F0.cur_menu != 0x1B) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(arg0, fn_8024B7E4, 0U);
        proc->flags_3 = HSD_GObj_804D783C;
        user_data = arg0->user_data;
        if (user_data->unk10 != NULL) {
            HSD_SisLib_803A5CC4(user_data->unk10);
            user_data->unk10 = NULL;
        }
        if (user_data->unk14 != NULL) {
            HSD_SisLib_803A5CC4(user_data->unk14);
            user_data->unk14 = NULL;
        }
        text = user_data->unk18;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
            user_data->unk18 = NULL;
        }
        text = user_data->unk1C;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
            user_data->unk1C = NULL;
        }
    } else {
        temp_f31 = mn_8022EE84(sp1C, &vec_0, MOBJ_MASK);
        mn_8022EE84(sp18, &vec_0, MOBJ_MASK);
        mn_8022EFD8(sp14, &vec_0);
        if (temp_f31 == vec_0.end_frame) {
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            proc2 = HSD_GObj_SetupProc(arg0, (void (*)(HSD_GObj*)) fn_8024B8B4,
                                      0U);
            proc2->flags_3 = HSD_GObj_804D783C;
            mnSoundTest_8024A958((Soundtest_GObj*) arg0);
            mnSoundTest_804D6C44 = 0;
        }
    }
}

void mnSoundTest_8024BCA0(int arg0)
{
    HSD_JObj* sp24;
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    soundtest_user_data* user_data;
    HSD_Text* text;
    u8 temp_r29_2;
    u8 temp_r29_3;

    gobj = GObj_Create(6U, 7U, 0x80U);
    mnSoundTest_804D6C40 = gobj;
    jobj = HSD_JObjLoadJoint(mnSoundTest_804A08C8.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4U, 0x80U);
    HSD_JObjAddAnimAll(jobj, mnSoundTest_804A08C8.animjoint,
                       mnSoundTest_804A08C8.matanim_joint,
                       mnSoundTest_804A08C8.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    proc = HSD_GObj_SetupProc(gobj, (void (*)(HSD_GObj*)) fn_8024BAF0, 0U);
    proc->flags_3 = HSD_GObj_804D783C;
    user_data = HSD_MemAlloc(0x20);
    if (user_data == NULL) {
        OSReport(mnSoundTest_803EF4F4);
        __assert(mnSoundTest_803EF50C, 0x5F4U, mnSoundTest_803EF51C);
    }
    user_data->unk1 = 0;
    user_data->unk2 = 0x50;
    user_data->unk4 = 0;
    user_data->unk3 = 0U;
    user_data->unk0 = 0U;
    user_data->unk8 = 1.0f;
    user_data->unkC = 1.0f;
    user_data->unk10 = NULL;
    user_data->unk14 = NULL;
    user_data->unk18 = NULL;
    user_data->unk1C = NULL;
    GObj_InitUserData(gobj, 0U, HSD_Free, user_data);
    text = user_data->unk10;
    if (text != NULL) {
        HSD_SisLib_803A5CC4(text);
    }
    text = HSD_SisLib_803A5ACC(0, 1, -9.5f, 9.1f, 17.0f, 364.68332f, 38.38772f);
    user_data->unk10 = text;
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    HSD_SisLib_803A6368(text, 0xBE);
    temp_r29_2 = user_data->unk0;
    mnSoundTest_8024ABF8(gobj, (u8) (-(s32) temp_r29_2 == 0));
    mnSoundTest_8024AD58(gobj, temp_r29_2);
    temp_r29_3 = data_4[user_data->unk3];
    lb_80011E24(GET_JOBJ(gobj), &sp24, 0x15, -1);
    HSD_JObjReqAnimAll(sp24, (f32) data_4[temp_r29_3 + 30]);
    mn_8022F3D8(sp24, 0xFFU, 0xA0);
    HSD_JObjAnimAll(sp24);
}

s32 mnSoundTest_8024BEE0(s32 arg0)
{
    HSD_GObjProc* proc;
    s32 temp_ret;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x1B;
    mn_804A04F0.hovered_selection = 0;
    mnSoundTest_804D6C48 = gm_801601C4(gmMainLib_8015ED74());
    temp_ret = gm_80160244(gmMainLib_8015ED74());
    mnSoundTest_804D6C4C = temp_ret;
    mnSoundTest_804D6C44 = 1;
    lbArchive_LoadSections(
        mn_804D6BB8, (void**) &mnSoundTest_804A08C8.joint,
        mnSoundTest_803EF528, &mnSoundTest_804A08C8.animjoint,
        mnSoundTest_803EF540, &mnSoundTest_804A08C8.matanim_joint,
        mnSoundTest_803EF55C, &mnSoundTest_804A08C8.shapeanim_joint,
        mnSoundTest_803EF57C, 0);
    mnSoundTest_8024BCA0(arg0);
    proc = HSD_GObj_SetupProc(GObj_Create(0U, 1U, 0x80U), fn_8024B2B0, 0U);
    proc->flags_3 = HSD_GObj_804D783C;
    return (s32) proc;
}

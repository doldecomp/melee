#include "tyfigupon.h"

#include "inlines.h"
#include "toy.h"
#include "tylist.h"
#include "types.h"

#include "if/textlib.h"
#include "if/types.h"
#include "gm/gm_1601.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"

#include <baselib/archive.h>
#include <baselib/cobj.h>
#include <baselib/controller.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/random.h>

#include <dolphin/mtx.h>

extern void* un_804D6EF0;
extern HSD_CObjDesc* un_804D6F04;

typedef struct {
    /* 0x00 */ HSD_GObj* x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ HSD_GObj* x8;
    /* 0x0C */ u8 pad_0C[0x4];
    /* 0x10 */ s32 x10;
    /* 0x14 */ u8 pad_14[0x4];
    /* 0x18 */ void* x18;
    /* 0x1C */ u8 pad_1C[0x8];
    /* 0x24 */ s32 x24;
} TyFiguponData;

typedef struct {
    u8 pad[0x4D];
    u8 x4D;
} TyFiguponInner;

typedef struct {
    /* 0x00 */ u32 x0;
    /* 0x04 */ u32 x4;
    /* 0x08 */ s32 x8;
    /* 0x0C */ u8 pad_0C[0x38];
    /* 0x44 */ f32 x44;
    /* 0x48 */ u8 pad_48[0x10];
} TyFiguponUD;

typedef struct {
    /* 0x00 */ u32 x0;
    /* 0x04 */ u32 x4;
    /* 0x08 */ u8 pad_08[0x4];
    /* 0x0C */ u32 xC;
} TyFiguponED4;

typedef struct {
    /* 0x00 */ u32 x0;
    /* 0x04 */ HSD_JObj* x4;
    /* 0x08 */ HSD_JObj* x8;
} TyFiguponAA8;

void tyFigupon_80314AA8(HSD_JObj* jobj, char* anim_str, char* matanim_str,
                        char* shapeanim_str)
{
    HSD_AnimJoint* ajoint;
    HSD_MatAnimJoint* majoint;
    HSD_ShapeAnimJoint* sajoint;
    struct un_804D6EF4_t* data = un_804D6EF4;
    PAD_STACK(16);

    if (anim_str != NULL) {
        ajoint = HSD_ArchiveGetPublicAddress(data->archive, anim_str);
    } else {
        ajoint = NULL;
    }
    if (matanim_str != NULL) {
        majoint = HSD_ArchiveGetPublicAddress(data->archive, matanim_str);
    } else {
        majoint = NULL;
    }
    if (shapeanim_str != NULL) {
        sajoint = HSD_ArchiveGetPublicAddress(data->archive, shapeanim_str);
    } else {
        sajoint = NULL;
    }
    HSD_JObjAddAnimAll(jobj, ajoint, majoint, sajoint);
    HSD_JObjReqAnimAll(jobj, 0.0f);
}

s32 un_80314B54(void)
{
    s32 i;
    s32 count = 0;

    for (i = 0; i < 0x125; i++) {
        if (un_80304CC8(i) != 0) {
            if (un_803048C0(i) != 0) {
                s32 result = (s32) un_803060BC(i, 6);
                if (result != 8 && (u32) result > 1) {
                    count++;
                }
            }
        }
    }
    return count;
}

void tyFigupon_80314BE4(HSD_GObj* gobj, int unused)
{
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        HSD_SetEraseColor(0x19, 0x19, 0x33, 0xFF);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 0);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(NULL);
        HSD_CObjEndCurrent();
    }
}

void tyFigupon_80314C5C(HSD_GObj* gobj)
{
    Toy* tp1 = GET_TOY(gobj);
    struct un_804D6EF4_t* temp_r29 = un_804D6EF4;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(0x38);
    if (tp1 != NULL) {
        if (tp1->x8 % 30 == 0) {
            HSD_JObjReqAnimAll(jobj, 0.0f);
        }
        HSD_JObjAnimAll(jobj);
        if (--tp1->x8 != 0) {
            tp1->translate.y += tp1->offset.y;
            if (jobj->translate.x > HSD_JObjGetTranslationX(temp_r29->jobjs[3])) {
                HSD_JObjAddTranslationX(jobj, tp1->translate.x);
            }
            if (jobj->translate.z > HSD_JObjGetTranslationZ(temp_r29->jobjs[3])) {
                HSD_JObjAddTranslationZ(jobj, tp1->translate.z);
            }
            HSD_JObjAddTranslationY(jobj, tp1->translate.y);
        } else {
            lbAudioAx_800237A8(146, 127, 64);
            tp1->x8 = 0;
            HSD_GObjPLink_80390228(gobj);
        }
    } else {
        Toy* tp = HSD_MemAlloc(sizeof(Toy));
        if (tp != NULL) {
            GObj_InitUserData(gobj, 0, Toy_RemoveUserData, tp);
        }
        HSD_JObjReqAnimAll(jobj, HSD_Randi(15));
        HSD_AObjSetRate(jobj->child->aobj, 1.0f);
        {
            float temp_f30 = HSD_JObjGetTranslationX(temp_r29->jobjs[2]);
            float temp_f29_6 = HSD_JObjGetTranslationY(temp_r29->jobjs[2]);
            float temp_f31 = HSD_JObjGetTranslationZ(temp_r29->jobjs[2]);
            float temp_f28 = HSD_JObjGetTranslationX(temp_r29->jobjs[3]);
            float temp_f27 = HSD_JObjGetTranslationY(temp_r29->jobjs[3]);
            float temp_f26 = HSD_JObjGetTranslationZ(temp_r29->jobjs[3]);
            float temp_f30_2 = (3.0f * HSD_Randf()) + temp_f30;
            float var_f3 = temp_f28 - temp_f30_2;
            float temp_f29_7 = (3.0f * HSD_Randf()) + temp_f29_6;
            float var_f3_2;
            float var_f2;
            {
                if (var_f3 < 0.0f) {
                    var_f3 = -var_f3;
                }
                var_f2 = temp_f26 - temp_f31;
                tp->translate.x = -0.74f * (var_f3 / 30.0f);
                if (var_f2 < 0.0f) {
                    var_f2 = -var_f2;
                }
                var_f3_2 = temp_f27 - temp_f29_7;
            }
            tp->translate.z = -0.72f * (var_f2 / 30.0f);
            tp->translate.y = 0.4f;
            tp->offset.y = -0.026666667f;
            if (var_f3_2 < 0.0f) {
                var_f3_2 = -var_f3_2;
            }
            tp->x8 = 35.0f + var_f3_2;
            temp_r29->x56 = tp->x8;
            HSD_JObjSetTranslateX(jobj, temp_f30_2);
            HSD_JObjSetTranslateY(jobj, temp_f29_7);
            HSD_JObjSetTranslateZ(jobj, temp_f31);
        }
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        lbAudioAx_80023870(147, 127, 64, 26);
    }
}

void fn_803152BC(HSD_GObj* arg0)
{
    s32 temp_r3;
    struct un_804D6EF4_t* temp_r31;
    TyFiguponUD* temp_r30;
    TyFiguponUD* temp_r3_2;

    temp_r30 = HSD_GObjGetUserData(arg0);
    temp_r31 = un_804D6EF4;
    if (temp_r30 != NULL) {
        temp_r3 = temp_r30->x8;
        temp_r30->x8 = temp_r3 - 1;
        if (temp_r3 != 0) {
            HSD_JObjAnimAll(temp_r31->jobjs[0]);
            if ((temp_r30->x8 % 30) == 0) {
                HSD_JObjReqAnimAll(temp_r31->jobjs[0], 0.0f);
            }
        } else {
            temp_r30->x8 = 0;
            GObj_RemoveUserData(arg0);
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        }
    } else {
        temp_r3_2 = HSD_MemAlloc(0x58);
        if (temp_r3_2 != NULL) {
            GObj_InitUserData(arg0, 0, Toy_RemoveUserData, temp_r3_2);
        }
        HSD_JObjReqAnimAll(temp_r31->jobjs[0], 0.0f);
        temp_r3_2->x8 = 0x1E;
        temp_r3_2->x8 = (s32) (temp_r3_2->x8 + (((temp_r31->x5E * 2) / 30) * 0x1E));
    }
}

void un_803153EC(u32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 digits[4] = { 0, 0, 0, 0 };
    struct un_804D6EF4_t* temp_r30;
    HSD_JObj** jobj_ptr;
    s32 i;
    s32 digit;
    s32 num;
    s32 count;

    num = (s32) arg0;
    count = 0;
    temp_r30 = un_804D6EF4;
    do {
        digits[count] = num % 10;
        num /= 10;
        count += 1;
    } while (num > 0);

    for (i = 0; i < arg2; i++) {
        digit = digits[i];
        if (digit != 0) {
            if (arg3 == 1) {
                HSD_JObjReqAnimAll(temp_r30->jobjs[arg1 + i],
                                   (f32) (0x32 - (digit * 5)));
            } else {
                HSD_JObjReqAnimAll(temp_r30->jobjs[arg1 + i], (f32) digit);
            }
        } else {
            HSD_JObjReqAnimAll(temp_r30->jobjs[arg1 + i], 0.0f);
        }
        jobj_ptr = &temp_r30->jobjs[arg1 + i];
        HSD_AObjSetRate((*jobj_ptr)->aobj, 1.0f);
        HSD_JObjAnimAll(*jobj_ptr);
    }
}

void fn_80315574(void)
{
    TyFiguponData* data = un_804D6EF0;

    if (data->x24 == 0) {
        TyFiguponInner* inner = data->x18;
        inner->x4D = 1;
        data->x10 = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
    } else {
        data->x24 = data->x24 - 1;
    }
}

/// #fn_803155C8

/// #fn_80315C44

void fn_80316170(HSD_GObj* arg0)
{
    u8* arr = un_804A2AA8;
    f32 y = HSD_JObjGetTranslationY(GET_JOBJ(arg0));
    TyFiguponUD* ud = HSD_GObjGetUserData(arg0);

    if (ud != NULL) {
        if (y + ud->x44 <= -6.2f) {
            if (un_803048C0(*(s16*)(arr + 0xC)) == 1) {
                un_80306D14();
            }
            ((TyModeState*) un_804A284C)->x0 = 1;
            lbAudioAx_800237A8(0xA7, 0x7F, 0x40);
            HSD_JObjSetTranslateY(GET_JOBJ(arg0), -7.2f);
            gm_801678F8((s32) gm_801677F0(), 0xC, 0);
            GObj_RemoveUserData(arg0);
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            return;
        }
        ud->x44 -= 0.6f;
        HSD_JObjAddTranslationY(GET_JOBJ(arg0), ud->x44);
    } else {
        TyFiguponUD* new_ud = HSD_MemAlloc(0x58);
        if (new_ud != NULL) {
            GObj_InitUserData(arg0, 0, Toy_RemoveUserData, new_ud);
        }
        new_ud->x44 = 0.0f;
    }
}

s32 fn_8031638C(s16 arg0)
{
    s32 temp_r0;
    s32 var_r30;

    temp_r0 = (s32) un_803060BC((s32) arg0, 6);
    var_r30 = 0;
    switch (temp_r0) {
    case 0:
    case 1:
    case 4:
    case 6:
    case 8:
        break;
    case 7:
        if (un_803048C0((s32) arg0) > 0xFA) {
            var_r30 = 1;
        }
        break;
    case 5:
        var_r30 = 1;
        break;
    case 2:
    case 3:
        var_r30 = 1;
        break;
    }
    return var_r30;
}

/// #un_80316420

/// #fn_803168DC
static const Vec3 un_803B8968 = { 0.0f, 1.0f, 0.0f };

void fn_803168DC(HSD_GObj* arg0)
{
    TyFiguponAA8* data = (TyFiguponAA8*) un_804A2AA8;
    HSD_CObj* cobj = arg0->hsd_obj;
    Vec3 interest;
    Vec3 eye_pos;
    Vec3 up_copy;
    Vec3 eye_vec;
    Vec3 cross;
    Mtx mtx;
    f32 cx;
    f32 cy;
    f32 rot_x;
    f32 rot_y;
    f32 dead;

    cx = HSD_PadCopyStatus[0].nml_subStickX;
    cy = HSD_PadCopyStatus[0].nml_subStickY;
    if (-0.4f < cx && cx < 0.4f && -0.4f < cy && cy < 0.4f) {
        cx = HSD_PadCopyStatus[1].nml_subStickX;
        cy = HSD_PadCopyStatus[1].nml_subStickY;
        if (-0.4f < cx && cx < 0.4f && -0.4f < cy && cy < 0.4f) {
            cx = HSD_PadCopyStatus[2].nml_subStickX;
            cy = HSD_PadCopyStatus[2].nml_subStickY;
            if (-0.4f < cx && cx < 0.4f && -0.4f < cy && cy < 0.4f) {
                cx = HSD_PadCopyStatus[3].nml_subStickX;
                cy = HSD_PadCopyStatus[3].nml_subStickY;
            }
        }
    }

    if (-0.4f < cx && cx < 0.4f && -0.4f < cy && cy < 0.4f) {
        rot_y = 0.0f;
        rot_x = 0.0f;
    } else {
        if (-0.4f < cx && cx < 0.4f) {
            rot_x = 0.0f;
        } else {
            if (cx < 0.0f) {
                dead = -0.4f;
            } else {
                dead = 0.4f;
            }
            rot_x = 30.0f * ((cx - dead) / 0.6f);
        }
        if (-0.4f < cy && cy < 0.4f) {
            rot_y = 0.0f;
        } else {
            if (cy < 0.0f) {
                dead = -0.4f;
            } else {
                dead = 0.4f;
            }
            rot_y = 30.0f * ((cy - dead) / 0.6f);
        }
    }

    HSD_CObjInit(cobj, un_804D6F04);
    up_copy = un_803B8968;
    HSD_CObjGetEyeVector(cobj, &eye_vec);
    HSD_CObjGetInterest(cobj, &interest);
    PSVECCrossProduct(&up_copy, &eye_vec, &cross);
    lbVector_Normalize(&cross);
    PSMTXRotAxisRad(mtx, &cross, 0.017453292f * rot_y);
    PSMTXMultVec(mtx, &eye_vec, &eye_vec);
    PSMTXRotAxisRad(mtx, &up_copy, 0.017453292f * rot_x);
    PSMTXMultVec(mtx, &eye_vec, &eye_vec);
    PSVECScale(&eye_vec, &eye_vec, HSD_CObjGetEyeDistance(cobj));
    PSVECSubtract(&interest, &eye_vec, &eye_pos);
    HSD_CObjSetEyePosition(cobj, &eye_pos);

    if (data->x0 != 0) {
        if (rot_y > 10.0f) {
            HSD_JObjClearFlagsAll(data->x4, 0x10);
            HSD_JObjSetFlagsAll(data->x8, 0x10);
            return;
        }
        if (rot_y < -10.0f) {
            HSD_JObjClearFlagsAll(data->x8, 0x10);
            HSD_JObjSetFlagsAll(data->x4, 0x10);
        }
    }
}

void tyFigupon_80316BF8(void)
{
    lbAudioAx_80023F28(0x35);
    HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
}

/// #fn_80316C24

/// #un_8031753C

/// #un_80317A60

/// #un_80317D80_OnEnter

s32 un_803181BC(void)
{
    TyFiguponData* temp_r31;
    struct un_804D6EF4_t* ef4;
    TyFiguponED4* ed4;
    PAD_STACK(8);

    ef4 = un_804D6EF4;
    temp_r31 = un_804D6EF0;
    ed4 = un_804D6ED4;
    if (ef4->archive != NULL) {
        ef4->archive = NULL;
    }
    if (un_804D6EC8 != NULL) {
        un_804D6EC8 = NULL;
    }
    if (ed4->xC != 0U) {
        ed4->xC = 0U;
    }
    if (ef4->x00 != 0U) {
        ef4->x00 = 0U;
    }
    if (ef4->x08 != 0U) {
        ef4->x08 = 0U;
    }
    if (ef4->x0C != 0U) {
        ef4->x0C = 0U;
    }
    if (ed4->x0 != 0U) {
        ed4->x0 = 0U;
    }
    if (ed4->x4 != 0U) {
        ed4->x4 = 0U;
    }
    if (temp_r31->x0 != NULL) {
        HSD_GObjProc_8038FED4(temp_r31->x0);
        temp_r31->x0 = NULL;
    }
    if ((u32) temp_r31->x4 != 0U) {
        temp_r31->x4 = 0;
    }
    if (temp_r31->x8 != NULL) {
        HSD_GObjPLink_80390228(temp_r31->x8);
        temp_r31->x8 = NULL;
    }
    return lbAudioAx_800236DC();
}

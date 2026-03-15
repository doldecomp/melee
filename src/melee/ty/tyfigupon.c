#include "tyfigupon.h"

#include "inlines.h"
#include "toy.h"
#include "tylist.h"
#include "types.h"

#include "if/textlib.h"
#include "if/types.h"
#include "gm/gm_1601.h"
#include "lb/lbaudio_ax.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lblanguage.h"
#include "lb/lbvector.h"

#include <baselib/archive.h>
#include <baselib/cobj.h>
#include <baselib/controller.h>
#include <baselib/displayfunc.h>
#include <baselib/dobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/mobj.h>
#include <baselib/random.h>
#include <baselib/sislib.h>
#include <baselib/tobj.h>

#include <dolphin/mtx.h>
#include <dolphin/os.h>

extern void* un_804D6EF0;
extern HSD_CObjDesc* un_804D6F04;
extern void* un_804D6F08;
extern s32 un_804D6EFC;
extern s32 un_804D6F00;
extern char un_803FE5E8[];
extern u8 un_803FEA10[];
extern void* un_804D6EF8;

typedef struct {
    /* 0x00 */ HSD_GObj* x0;
    /* 0x04 */ HSD_GObj* x4;
    /* 0x08 */ HSD_GObj* x8;
    /* 0x0C */ u8 pad_0C[0x4];
    /* 0x10 */ s32 x10;
    /* 0x14 */ HSD_Text* x14;
    /* 0x18 */ HSD_Text* x18;
    /* 0x1C */ u8 pad_1C[0x4];
    /* 0x20 */ s32 x20;
    /* 0x24 */ s32 x24;
    /* 0x28 */ u8 x28;
    /* 0x29 */ u8 x29;
} TyFiguponData;

typedef struct {
    u8 pad[0x4D];
    u8 x4D;
} TyFiguponInner;

typedef struct {
    /* 0x00 */ u32 x0;
    /* 0x04 */ u32 x4;
    /* 0x08 */ s32 x8;
    /* 0x0C */ u8 pad_0C[0x4];
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ u8 pad_1C[0xC];
    /* 0x28 */ s32 x28;
    /* 0x2C */ s32 x2C;
    /* 0x30 */ s32 x30;
    /* 0x34 */ u8 pad_34[0x10];
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

#pragma dont_inline on
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
#pragma dont_inline reset

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
        if (tp1->x8-- != 0) {
            tp1->translate.y += tp1->offset.y;
            if (HSD_JObjGetTranslationX(jobj) > HSD_JObjGetTranslationX(temp_r29->jobjs[3])) {
                HSD_JObjAddTranslationX(jobj, tp1->translate.x);
            }
            if (HSD_JObjGetTranslationZ(jobj) > HSD_JObjGetTranslationZ(temp_r29->jobjs[3])) {
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
            float temp_f29_7 = (3.0f * HSD_Randf()) + temp_f29_6;
            float var_f3 = temp_f28 - temp_f30_2;
            float var_f2;
            float var_f3_2;
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
            tp->x8 = (f32)(s32)var_f3_2 + 35.0f;
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

void un_803153EC(u32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
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
        data->x18->hidden = 1;
        data->x10 = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
    } else {
        data->x24 = data->x24 - 1;
    }
}

/// #fn_803155C8
void fn_803155C8(void)
{
    TyFiguponAA8* aa8 = (TyFiguponAA8*) un_804A2AA8;
    struct un_804D6EF4_t* ef4 = un_804D6EF4;
    TyFiguponData* data = un_804D6EF0;
    HSD_JObj* jobj = GET_JOBJ((HSD_GObj*) ef4->x08);
    s32 sc;
    s32 total;
    s32 i;
    f32 fval;
    f32 pct;
    PAD_STACK(16);

    switch ((s8)(u8) ef4->x5C) {
    case 2:
        ef4->x58 -= 1;
        if ((s16) ef4->x58 == 0) {
            data->x29 = 1;
            ef4->x58 = 0x14;
            HSD_JObjReqAnimAll(jobj, 0.0f);
            ef4->x5C = 3;
            gm_801678F8((s32) gm_801677F0(), 0x1E, 0);
            return;
        }
        break;
    case 3:
        if ((s16) ef4->x54 != 0) {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 0.0f);
        } else {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 1.0f);
        }
        HSD_JObjAnimAll(jobj);
        ef4->x58 -= 1;
        if ((s16) ef4->x58 == 0) {
            lbAudioAx_800237A8(0xA8, 0x7F, 0x40);
            ef4->x58 = 0xA;
            ef4->x58 += 0xA;
            ef4->x5C = 4;
            return;
        }
        break;
    case 4:
        if ((s16) ef4->x54 != 0) {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 0.0f);
        } else {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 1.0f);
        }
        HSD_JObjAnimAll(jobj);
        if ((s16) ef4->x58 < 0xE) {
            HSD_JObjReqAnimAll(jobj, 30.0f);
        }
        ef4->x58 -= 1;
        if ((s16) ef4->x58 == 0) {
            ef4->x58 = 0xE;
            ef4->x5C = 5;
            return;
        }
        break;
    case 5:
        ef4->x58 -= 1;
        if ((s16) ef4->x58 == 0) {
            sc = (s8)(u8) ef4->x5D;
            if (sc >= 3) {
                ef4->x58 = (s16)(1.62f * (f32) sc);
                ef4->x58 += 0xE;
                HSD_JObjReqAnimAll(jobj, 50.0f);
                HSD_JObjReqAnimAll(ef4->jobjs[0xE], 0.0f);
                lbAudioAx_80023870(0xA9, 0x7F, 0x40, 0x8A);
            } else {
                ef4->x58 = 1;
            }
            ef4->x5C = 6;
            return;
        }
        break;
    case 6:
        if ((s8)(u8) ef4->x5D >= 3) {
            if ((s16) ef4->x54 != 0) {
                HSD_JObjReqAnimAll(ef4->jobjs[0xE], 0.0f);
            } else {
                HSD_JObjReqAnimAll(ef4->jobjs[0xE], 1.0f);
            }
            HSD_JObjAnimAll(jobj);
            if ((ef4->x58 % 40) == 0) {
                HSD_JObjReqAnimAll(jobj, 50.0f);
                lbAudioAx_80023870(0xA9, 0x7F, 0x40, 0x8A);
            }
            if ((s16) ef4->x58 < 0xE) {
                HSD_JObjReqAnimAll(jobj, 50.0f);
            }
        }
        ef4->x58 -= 1;
        if ((s16) ef4->x58 == 0) {
            if ((s8) data->x29 != 0) {
                sc = (s8)(u8) ef4->x5D;
                fval = (f32)(ef4->x54 + un_80314B54());
                lbAudioAx_80023694();
                if (sc != 0) {
                    sc -= 1;
                }
                pct = 100.0f * (((f32) ef4->x54 / fval) + ((f32)(sc * 5) / 100.0f));
                if (pct >= 100.0f) {
                    pct = 99.9f;
                }
                data->x20 = un_80305058(0x63, 3, 0, pct);
                un_80316420((s16) data->x20);
                {
                    s32 inv = un_80314B54();
                    total = 0;
                    i = 0;
                    do {
                        if (i != 8 && (u32) i > 1U && un_80304B0C(i) != 0) {
                            total += un_80304B94(i);
                        }
                        i++;
                    } while (i < 9);
                    ef4->x54 = total - inv;
                }
                data->x29 = 0;
                ef4->x58 = 0x78;
                ef4->x5C = 8;
                return;
            }
            ef4->x5C = 9;
            return;
        }
        break;
    case 8:
        ef4->x58 -= 1;
        if ((s16) ef4->x58 == 0) {
            if (((HSD_Archive**) un_804D6EF8)[5] != NULL) {
                lbArchive_80016EFC(((HSD_Archive**) un_804D6EF8)[5]);
                ((HSD_Archive**) un_804D6EF8)[5] = NULL;
            }
            if (aa8->x0 != 0) {
                HSD_GObjPLink_80390228((HSD_GObj*) aa8->x0);
                aa8->x0 = 0;
                aa8->x8 = 0;
                aa8->x4 = 0;
            }
            HSD_SisLib_803A6368(data->x14, 0);
            un_803083D8(ef4->jobjs[0xC], 0x3E7);
            if ((s16) ef4->x54 == 0) {
                HSD_JObjReqAnimAll(ef4->jobjs[0xE], 1.0f);
                HSD_JObjAnimAll(jobj);
            }
            ef4->x5C = 9;
            return;
        }
        break;
    case 9:
        if (((u32) gm_801623D8() / 10u) != 0) {
            i = 1;
            ef4->x5E = 1;
            un_803153EC((u32)(s8)(u8) ef4->x5E, 6, 2, 0, 0);
            {
                struct un_804D6EF4_t* ef4_2 = un_804D6EF4;
                if ((s32)(u8) ef4_2->x5E == 0x14) {
                    i = 3;
                }
                if ((s8)(u8) ef4_2->x5E <= 1) {
                    i = 4;
                }
                HSD_JObjReqAnimAll(ef4_2->jobjs[8], (f32) i);
                HSD_AObjSetRate(ef4_2->jobjs[8]->aobj, 1.0f);
                HSD_JObjAnimAll(ef4_2->jobjs[8]);
            }
        }
        {
            struct un_804D6EF4_t* ef4_3 = un_804D6EF4;
            sc = (s8)(u8) ef4->x5E;
            fval = (f32)(ef4_3->x54 + un_80314B54());
            if (sc != 0) {
                sc -= 1;
            }
            if (ef4_3->x54 == 0) {
                pct = 0.0f;
            } else {
                pct = ((f32) ef4_3->x54 / fval) + ((f32)(sc * 5) / 100.0f);
            }
            if (pct >= 1.0f) {
                pct = 999.0f;
            } else {
                pct = pct * 1000.0f;
            }
            un_803153EC((u32)(s32) pct, 9, 3, 2, 0);
            ef4->x58 = 0;
            ef4->x56 = 0;
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            ef4->x5C = 0;
        }
        break;
    }
}

/// #fn_80315C44
void fn_80315C44(HSD_GObj* arg0)
{
    TyFiguponUD* ud = arg0->user_data;
    struct un_804D6EF4_t* ef4 = un_804D6EF4;
    u8* fea10 = un_803FEA10;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 total;
    s32 count;
    s32 anim;
    s32 i;

    PAD_STACK(24);

    if (ud != NULL) {
        if (ud->x8 != 0) {
            if (ud->x10 == 0 && ud->x14 == 0 && ud->x18 != 0) {
                HSD_JObjAnimAll(ef4->jobjs[5]);
            }
            if (ud->x10 == 0) {
                if (ud->x14 == 0) {
                    HSD_JObjReqAnimAll(ef4->jobjs[4], 0.0f);
                }
                HSD_JObjAnimAll(ef4->jobjs[4]);
            }
            if (ud->x10 == 0) {
                HSD_JObjReqAnimAll(ef4->jobjs[3], 0.0f);
            }
            HSD_JObjAnimAll(ef4->jobjs[3]);
            ud->x8 = ud->x8 - 1;
            if (ud->x8 % 2 == 0) {
                ef4 = un_804D6EF4;
                gobj = GObj_Create(9, 9, 0);
                jobj = HSD_JObjLoadJoint(
                    HSD_ArchiveGetPublicAddress(ef4->archive,
                                                (char*)(fea10 + 0x58)));
                HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
                GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0x3C, 0);
                tyFigupon_80314AA8(jobj, (char*)(fea10 + 0x74),
                                   (char*)(fea10 + 0x94),
                                   (char*)(fea10 + 0xB8));
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
                HSD_JObjSetFlagsAll(jobj, 0x10);
                HSD_GObjProc_8038FD54(gobj, tyFigupon_80314C5C, 0);
                HSD_GObj_80390CD4(gobj);
                gm_801623FC(gm_801623D8() - 0xA);
                ef4->x5E = (u8) ef4->x5E - 1;
                total = gm_801623D8() / 10u;
                i = 0;
                ud->x18 = i;
                ud->x14 = i;
                ud->x10 = i;
                do {
                    (&ud->x10)[i] = total % 10;
                    total /= 10;
                    i++;
                } while (total > 0);
                count = (s8)(u8) ef4->x5E;
                i = 0;
                ud->x30 = i;
                ud->x2C = i;
                ud->x28 = i;
                do {
                    (&ud->x28)[i] = count % 10;
                    count = (s8)(count / 10);
                    i++;
                } while (count > 0);
                un_803153EC(gm_801623D8() / 10u, 3, 3, 1, 0);
                un_803153EC((u32)(s8)(u8) ef4->x5E, 6, 2, 0, 0);
                ef4 = un_804D6EF4;
                anim = 2;
                if ((s32)(u8) ef4->x5E == 0x14) {
                    anim = 3;
                }
                if ((s8)(u8) ef4->x5E <= 1) {
                    anim = 4;
                }
                HSD_JObjReqAnimAll(ef4->jobjs[8], (f32) anim);
                HSD_AObjSetRate(ef4->jobjs[8]->aobj, 1.0f);
                HSD_JObjAnimAll(ef4->jobjs[8]);
                gm_801678F8((s32) gm_801677F0(), 0x10, 0);
            }
        } else {
            anim = 0;
            ud->x8 = 0;
            ef4->x5E = 0;
            un_803153EC(gm_801623D8() / 10u, 3, 3, 1, 0);
            un_803153EC((u32)(s8)(u8) ef4->x5E, 6, 2, 0, 0);
            ef4 = un_804D6EF4;
            if ((s32)(u8) ef4->x5E == 0x14) {
                anim = 3;
            }
            if ((s8)(u8) ef4->x5E <= 1) {
                anim = 4;
            }
            HSD_JObjReqAnimAll(ef4->jobjs[8], (f32) anim);
            HSD_AObjSetRate(ef4->jobjs[8]->aobj, 1.0f);
            HSD_JObjAnimAll(ef4->jobjs[8]);
            GObj_RemoveUserData(arg0);
            ef4->x58 = ef4->x56;
            ef4->x58 += 0xE;
            ef4->x5C = 2;
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        }
    } else {
        ud = HSD_MemAlloc(0x58);
        if (ud != NULL) {
            GObj_InitUserData(arg0, 0, Toy_RemoveUserData, ud);
            total = gm_801623D8() / 10u;
            i = 0;
            ud->x18 = i;
            ud->x14 = i;
            ud->x10 = i;
            do {
                (&ud->x10)[i] = total % 10;
                total /= 10;
                i++;
            } while (total > 0);
            un_803153EC(gm_801623D8() / 10u, 3, 3, 1, 0);
            HSD_AObjSetRate(ef4->jobjs[3]->child->u.dobj->mobj->tobj->aobj, 2.0f);
            HSD_AObjSetRate(ef4->jobjs[4]->child->u.dobj->mobj->tobj->aobj, 2.0f);
            HSD_AObjSetRate(ef4->jobjs[5]->child->u.dobj->mobj->tobj->aobj, 2.0f);
            ud->x8 = (s8)(u8) ef4->x5E * 2;
        }
    }
}

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
void un_80316420(s16 arg0)
{
    struct un_804D6EF4_t* ef4 = un_804D6EF4;
    TyFiguponData* data = un_804D6EF0;
    TyFiguponAA8* aa8 = (TyFiguponAA8*) un_804A2AA8;
    s32 temp_r31;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    f32 angle;

    PAD_STACK(32);

    temp_r31 = un_803048C0(arg0);
    un_80308250(un_804D6EF8, arg0, 0);
    gobj = un_803087F4(un_804D6EF8);
    HSD_JObjClearFlagsAll(aa8->x4, 0x10);
    HSD_JObjSetFlagsAll(aa8->x8, 0x10);
    jobj = GET_JOBJ(gobj);
    HSD_JObjSetTranslateX(jobj, -1.8f);
    HSD_JObjSetTranslateY(jobj, 18.6f);
    HSD_JObjSetTranslateZ(jobj, 12.0f);
    HSD_JObjSetScaleX(jobj, 0.79f);
    HSD_JObjSetScaleY(jobj, 0.79f);
    HSD_JObjSetScaleZ(jobj, 0.79f);
    angle = 30.0f * (2.0f * (HSD_Randf() - 0.5f));
    HSD_JObjSetRotationY(jobj, 0.017453292f * angle);
    HSD_GObjProc_8038FD54(gobj, fn_80316170, 0);
    HSD_GObj_80390CD4(gobj);
    if (temp_r31 == 0) {
        un_80306B18(data->x8, 0, 0x48, 1);
        HSD_GObj_80390CD4(data->x8);
    }
    Trophy_SetUnlockState(arg0, 1);
    un_8031234C(1);
    lb_8001CE00();
    un_80308328(arg0);
    HSD_SisLib_803A6368(data->x14, temp_r31);
    un_803083D8(ef4->jobjs[0xC], arg0);
    if (((TyModeState*) un_804A284C)->x0 == 2) {
        if ((u32) data->x10 == 0) {
            data->x10 = (s32) HSD_GObjProc_8038FD54(data->x0,
                (void (*)(HSD_GObj*)) fn_80315574, 0);
        }
        data->x24 = 0x12C;
        ((TyFiguponData*) un_804D6EF0)->x18->hidden = 0;
    }
}

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

static u16 un_804D5AA0 = 0xC;
static char un_804D5AA4 = 0;

typedef struct {
    s32 x0, x4, x8, xC;
} DigitInit;

static const DigitInit un_803B8974 = { 0, 0, 0, 0 };

/// #un_8031753C
void un_8031753C(void)
{
    struct un_804D6EF4_t* ef4 = un_804D6EF4;
    u8* fea10 = un_803FEA10;
    HSD_Joint* joint;
    HSD_JObj* jobj;
    s32 total;
    DigitInit digits_s;
    s32* digit_ptr;
    s32 i;
    s32 trophy_total;
    s32 new_count;

    if (ef4->archive == NULL) {
        OSReport((char*)(fea10 + 0x194));
        OSPanic((char*)(fea10 + 0x120), 0x55C, &un_804D5AA4);
    }
    if (ef4->x00 != 0) {
        HSD_GObjPLink_80390228((HSD_GObj*) ef4->x00);
        ef4->x00 = 0;
    }
    joint = HSD_ArchiveGetPublicAddress(ef4->archive, (char*) fea10);
    if (joint != NULL) {
        ef4->x00 = (u32) GObj_Create(9, 9, 0);
        jobj = HSD_JObjLoadJoint(joint);
        HSD_GObjObject_80390A70((HSD_GObj*) ef4->x00, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink((HSD_GObj*) ef4->x00, HSD_GObj_JObjCallback, 0x3C, 1);
        lb_8001204C(jobj, ef4->jobjs, (u16*)(fea10 + 0x178), 0xD);
        tyFigupon_80314AA8(ef4->jobjs[0xC], NULL, (char*)(fea10 + 0x1B8), NULL);
        un_803083D8(ef4->jobjs[0xC], 0x3E7);
        joint = HSD_ArchiveGetPublicAddress(ef4->archive, (char*)(fea10 + 0x1C));
        ef4->unk4 = GObj_Create(9, 9, 0);
        jobj = HSD_JObjLoadJoint(joint);
        HSD_GObjObject_80390A70(ef4->unk4, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(ef4->unk4, HSD_GObj_JObjCallback, 0x3C, 0);
        tyFigupon_80314AA8(jobj, (char*)(fea10 + 0x1E0),
                           (char*)(fea10 + 0x200), (char*)(fea10 + 0x224));
        HSD_GObjProc_8038FD54(ef4->unk4, un_80306BB8, 0);
        HSD_GObj_80390CD4(ef4->unk4);
        jobj = HSD_JObjLoadJoint(
            HSD_ArchiveGetPublicAddress(ef4->archive, (char*)(fea10 + 0x58)));
        HSD_JObjAddChild(ef4->jobjs[0], jobj);
        tyFigupon_80314AA8(jobj, (char*)(fea10 + 0x74),
                           (char*)(fea10 + 0x94), (char*)(fea10 + 0xB8));
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);

        i = 0;
        digits_s = un_803B8974;
        total = (s32)(gm_801623D8() / 10u);
        joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                            (char*)(fea10 + 0x248));
        digit_ptr = &digits_s.x0;
        do {
            digit_ptr[i] = total % 10;
            total /= 10;
            i++;
        } while (total > 0);

        for (i = 0; i < 3; i++) {
            jobj = HSD_JObjLoadJoint(joint);
            HSD_JObjAddChild(ef4->jobjs[3 + i], jobj);
            tyFigupon_80314AA8(jobj, (char*)(fea10 + 0x264),
                               (char*)(fea10 + 0x284), (char*)(fea10 + 0x2A8));
            if (digit_ptr[i] != 0) {
                HSD_JObjReqAnimAll(jobj, (f32)(50 - digit_ptr[i] * 5));
            } else {
                HSD_JObjReqAnimAll(jobj, 0.0f);
            }
            HSD_JObjAnimAll(jobj);
        }

        joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                            (char*)(fea10 + 0x2CC));
        for (i = 0; i < 2; i++) {
            jobj = HSD_JObjLoadJoint(joint);
            HSD_JObjAddChild(ef4->jobjs[6 + i], jobj);
            tyFigupon_80314AA8(jobj, (char*)(fea10 + 0x2E8),
                               (char*)(fea10 + 0x308), (char*)(fea10 + 0x32C));
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
        }

        tyFigupon_80314AA8(ef4->jobjs[8], NULL, (char*)(fea10 + 0x350), NULL);

        joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                            (char*)(fea10 + 0x378));
        ef4->x08 = (u32) GObj_Create(9, 9, 0);
        jobj = HSD_JObjLoadJoint(joint);
        HSD_GObjObject_80390A70((HSD_GObj*) ef4->x08, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink((HSD_GObj*) ef4->x08, HSD_GObj_JObjCallback, 0x3C, 0);
        tyFigupon_80314AA8(jobj, (char*)(fea10 + 0x394),
                           (char*)(fea10 + 0x3B4), (char*)(fea10 + 0x3D8));
        lb_8001204C(jobj, &ef4->jobjs[0xE], &un_804D5AA0, 1);

        trophy_total = un_80314B54();
        new_count = 0;
        for (i = 0; i < 9; i++) {
            if (i != 8 && (u32) i > 1U && un_80304B0C(i) != 0) {
                new_count += un_80304B94(i);
            }
        }
        if (new_count - trophy_total != 0) {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 0.0f);
        } else {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 1.0f);
        }
        HSD_JObjAnimAll(ef4->jobjs[0xE]);

        ef4->x0C = (u32) GObj_Create(9, 9, 0);
        joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                            (char*)(fea10 + 0x400));
        for (i = 0; i < 3; i++) {
            jobj = HSD_JObjLoadJoint(joint);
            HSD_JObjAddChild(ef4->jobjs[9 + i], jobj);
            tyFigupon_80314AA8(jobj, (char*)(fea10 + 0x41C),
                               (char*)(fea10 + 0x43C), (char*)(fea10 + 0x460));
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
        }
        return;
    }
    OSReport((char*)(fea10 + 0x484), fea10, joint);
    OSPanic((char*)(fea10 + 0x120), 0x610, &un_804D5AA4);
}

/// #un_80317A60

void un_80317A60(void)
{
    u8* fea10 = un_803FEA10;
    TyFiguponData* data = un_804D6EF0;
    HSD_CameraDescPerspective* cam_desc;
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    HSD_Text* text;
    PAD_STACK(40);

    cam_desc = HSD_ArchiveGetPublicAddress(un_804D6EF4->archive, un_803FE5E8);
    data->x0 = GObj_Create(1, 2, 0);
    cobj = lb_80013B14(cam_desc);
    un_804D6F04 = (HSD_CObjDesc*) cam_desc;
    HSD_GObjObject_80390A70(data->x0, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(data->x0, tyFigupon_80314BE4, 0);
    gobj = data->x0;
    gobj->gxlink_prios = 0x5010000000000000ULL;
    data->x4 = GObj_Create(1, 2, 0);
    cobj = lb_80013B14((HSD_CameraDescPerspective*)(fea10 + 0x4EC));
    un_804D6F08 = fea10 + 0x4EC;
    HSD_GObjObject_80390A70(data->x4, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(data->x4, (GObj_RenderFunc) un_803068E0, 0);
    gobj = data->x4;
    gobj->gxlink_prios = 0x2680000000000000ULL;

    if (lbLang_IsSavedLanguageJP() != 0) {
        HSD_SisLib_803A62A0(0, (char*)(fea10 + 0x524),
                            (char*)(fea10 + 0x530));
    } else {
        HSD_SisLib_803A62A0(0, (char*)(fea10 + 0x53C),
                            (char*)(fea10 + 0x548));
    }

    un_804D6EFC = HSD_SisLib_803A611C(0, data->x0, 0xB, 0xB, 0, 0x3E, 0, 0);
    data->x14 = HSD_SisLib_803A5ACC(0, un_804D6EFC, 5.2f, 5.2f, 17.2f,
                                     448.0f, 64.0f);
    if (lbLang_IsSavedLanguageUS() != 0) {
        text = data->x14;
        text->x34.x = 1.6f;
        text->x34.y = 0.7f;
    } else {
        text = data->x14;
        text->x34.x = 2.0f;
        text->x34.y = 1.0f;
    }
    text = data->x14;
    text->font_size.x = 0.0235f;
    text->font_size.y = 0.0715f;
    data->x14->default_alignment = 1;
    if (lbLang_IsSavedLanguageUS() != 0) {
        data->x14->default_kerning = 1;
    }
    data->x14->default_fitting = 1;

    un_804D6F00 = HSD_SisLib_803A611C(0, data->x0, 0xD, 0xB, 0, 0x3E, 0, 0);
    data->x18 = HSD_SisLib_803A5ACC(0, un_804D6F00, -13.2f, 9.4f, 17.2f,
                                     320.0f, 32.0f);
    text = data->x18;
    text->font_size.x = 0.027f;
    text->font_size.y = 0.028f;
    data->x18->default_kerning = 1;
    if (lbLang_IsSavedLanguageUS() != 0) {
        text = data->x18;
        text->x34.x = 0.8f;
        text->x34.y = 0.8f;
        data->x18->pos_x = -13.599999f;
        data->x18->pos_y = 9.599999f;
    }
    HSD_SisLib_803A6368(data->x18, 0x13C);
    data->x10 = 0;
    data->x24 = 0;
    data->x28 = 8;
    ((TyFiguponData*) un_804D6EF0)->x18->hidden = 1;

    HSD_GObjProc_8038FD54(data->x0, (void (*)(HSD_GObj*)) fn_80316C24, 0);
    HSD_GObjProc_8038FD54(data->x0, fn_803168DC, 0);
    HSD_GObjProc_8038FD54(data->x4, fn_803168DC, 0);
    HSD_GObjProc_8038FD54(data->x0,
                           (void (*)(HSD_GObj*)) tyFigupon_80316BF8, 0);
    HSD_GObj_80390CD4(data->x0);
}

/// #un_80317D80_OnEnter
void un_80317D80_OnEnter(void* arg0)
{
    u8* fea10 = un_803FEA10;
    TyFiguponData* data;
    struct un_804D6EF4_t* ef4;
    void* ed4;
    HSD_Joint* joint;
    HSD_JObj* jobj;
    void* ud;
    s32 total_b54;
    s32 var_r28;
    s32 i;
    s8 x5E;
    s16 x54;
    f32 total;
    f32 pct;
    char* archive_name;
    void* sp20;
    PAD_STACK(24);

    un_804D6EF0 = HSD_MemAlloc(0x34);
    un_804D6EF4 = HSD_MemAlloc(0x60);
    un_804D6EF8 = HSD_MemAlloc(0x18);
    un_804D6ED4 = HSD_MemAlloc(0xE4);
    memzero(un_804D6EF0, 0x34);
    memzero(un_804D6EF4, 0x60);
    memzero(un_804D6EF8, 0x18);
    memzero(un_804D6ED4, 0xE4);
    data = un_804D6EF0;
    un_804D6EC8 = NULL;
    ef4 = un_804D6EF4;
    un_8031263C();
    un_80305918(3, 0, 1);
    *(u8*) un_804A284C = 1;
    if (lbLang_IsSavedLanguageJP() != 0) {
        archive_name = (char*)(fea10 + 0x38);
    } else {
        archive_name = (char*)(fea10 + 0x48);
    }
    ef4->archive = lbArchive_LoadSymbols(archive_name, &sp20, fea10, 0);
    ef4->x58 = 0;
    un_80317A60();
    ef4 = un_804D6EF4;
    ed4 = un_804D6ED4;
    if (ef4->archive == NULL) {
        OSReport((char*)(fea10 + 0x194));
        OSPanic((char*)(fea10 + 0x120), 0x627, "");
    }
    {
        void* temp = HSD_ArchiveGetPublicAddress(ef4->archive, (char*)(fea10 + 0x4A8));
        if (temp != NULL) {
            *(HSD_GObj**)ed4 = GObj_Create(2, 3, 0);
            HSD_GObjObject_80390A70(*(HSD_GObj**)ed4, HSD_GObj_804D784A,
                                     un_80306EEC(temp, 0));
            GObj_SetupGXLink(*(HSD_GObj**)ed4, HSD_GObj_LObjCallback, 0x34, 0);
        }
    }
    memzero(un_804D6ED4, 0xE4);
    un_80306D70(0);
    un_8031753C();
    joint = HSD_ArchiveGetPublicAddress(ef4->archive, (char*)(fea10 + 0x558));
    data->x8 = GObj_Create(0xA, 0xA, 0);
    jobj = HSD_JObjLoadJoint(joint);
    HSD_GObjObject_80390A70(data->x8, HSD_GObj_804D7849, jobj);
    tyFigupon_80314AA8(jobj, (char*)(fea10 + 0x574), (char*)(fea10 + 0x594),
                        (char*)(fea10 + 0x5B8));
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjAddTranslationZ(jobj, 0.5f);
    ud = HSD_MemAlloc(0x58);
    if (ud != NULL) {
        GObj_InitUserData(data->x8, 0, Toy_RemoveUserData, ud);
    }
    GObj_SetupGXLink(data->x8, HSD_GObj_JObjCallback, 0x3D, 0);
    HSD_JObjSetFlagsAll(jobj, 0x10);
    {
        s8 var_r0;
        if (((u32) gm_801623D8() / 10u) != 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        ef4->x5E = var_r0;
    }
    un_803153EC((s8) ef4->x5E, 6, 2, 0, 0);
    var_r28 = 0;
    total_b54 = un_80314B54();
    i = 0;
    do {
        if (i != 8 && (u32) i > 1U && un_80304B0C(i) != 0) {
            var_r28 += un_80304B94(i);
        }
        i += 1;
    } while (i < 9);
    ef4->x54 = var_r28 - total_b54;
    ef4 = un_804D6EF4;
    x5E = (s8) ef4->x5E;
    {
        s32 b54 = un_80314B54();
        x54 = ef4->x54;
        total = (f32)(x54 + b54);
    }
    if (x5E != 0) {
        x5E -= 1;
    }
    if (x54 == 0) {
        pct = 0.0f;
    } else {
        pct = ((f32) x54 / total) + ((f32)(x5E * 5) / 100.0f);
    }
    if (pct >= 1.0f) {
        pct = 999.0f;
    } else {
        pct = pct * 1000.0f;
    }
    un_803153EC((s32) pct, 9, 3, 2, 0);
    HSD_PadRenewStatus();
}

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

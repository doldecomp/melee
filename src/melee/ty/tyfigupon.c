#include "tyfigupon.h"

#include "math.h"
#include "math_ppc.h" // IWYU pragma: keep
#include "placeholder.h"
#include "platform.h"
#include "stddef.h"
#include "toy.h"
#include "trigf.h" // IWYU pragma: keep

#include <placeholder.h>
#include <platform.h>

#include "baselib/archive.h"
#include "baselib/cobj.h"
#include "baselib/controller.h"
#include "baselib/displayfunc.h"
#include "baselib/dobj.h"
#include "baselib/fog.h"
#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/gobjuserdata.h"
#include "baselib/jobj.h"
#include "baselib/lobj.h"
#include "baselib/memory.h"
#include "baselib/mobj.h"
#include "baselib/random.h"
#include "baselib/sislib.h"
#include "baselib/tobj.h"
#include "baselib/wobj.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"
#include "gm/gm_1601.h"
#include "gm/gm_1A45.h"
#include "if/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lblanguage.h"
#include "lb/lbspdisplay.h"
#include "lb/lbvector.h"
#include "mn/mnmain.h"
#include "MSL/math.h"
#include "MSL/math_ppc.h"
#include "sc/types.h"
#include "ty/inlines.h"
#include "ty/toy.h"
#include "ty/types.h"

/* 314AA8 */ static void _tyFigupon_80314AA8(HSD_JObj*, char*, char*, char*);
/* 314B54 */ static s32 _tyFigupon_80314B54(void);
/* 314BE4 */ static void _tyFigupon_80314BE4(HSD_GObj* gobj, int unused);
/* 314C5C */ static void _tyFigupon_80314C5C(HSD_GObj*);
/* 3152BC */ static void _tyFigupon_803152BC(HSD_GObj*);
/* 3153EC */ static void _tyFigupon_803153EC(s32, s32, s32, s32, s32);
/* 315574 */ static void _tyFigupon_80315574(void);
/* 3155C8 */ static void _tyFigupon_803155C8(void);
/* 315C44 */ static void _tyFigupon_80315C44(HSD_GObj*);
/* 316170 */ static void _tyFigupon_80316170(HSD_GObj*);
/* 31638C */ static s32 _tyFigupon_8031638C(s16);
/* 316420 */ static void _tyFigupon_80316420(s16);
/* 3168DC */ static void _tyFigupon_803168DC(HSD_GObj*);
/* 316BF8 */ static void _tyFigupon_80316BF8(HSD_GObj*);
/* 316C24 */ static void _tyFigupon_80316C24(HSD_GObj*);
/* 31753C */ static void _tyFigupon_8031753C(void);
/* 317A60 */ static void _tyFigupon_80317A60(void);
/* 3181BC */ static s32 _tyFigupon_803181BC(void);
/* 4D6EF0 */ static TyFiguponData* _tyFigupon_804D6EF0;
/* 4D6EF4 */ static struct un_804D6EF4_t* _tyFigupon_804D6EF4;
/* 4D6EF8 */ static HSD_Archive* _tyFigupon_804D6EF8;
/* 4D6EFC */ static s32 _tyFigupon_804D6EFC;
/* 4D6F00 */ static s32 _tyFigupon_804D6F00;
/* 4D6F04 */ static HSD_CObjDesc* _tyFigupon_804D6F04;
/* 4D6F08 */ static HSD_CameraDescPerspective* _tyFigupon_804D6F08;

/// @todo .data order hack
static void order_data_0(void)
{
    /*   +0 */ (void) "ToyFigurePonPanel_Top_joint";
    /*  +1C */ (void) "ToyFigurePonBg_Top_joint";
    /*  +38 */ (void) "TyMnFigp.dat";
    /*  +48 */ (void) "TyMnFigp.usd";
    /*  +58 */ (void) "ToyFigurePonCoin_Top_joint";
    /*  +74 */ (void) "ToyFigurePonCoin_Top_animjoint";
    /*  +94 */ (void) "ToyFigurePonCoin_Top_matanim_joint";
    /*  +B8 */ (void) "ToyFigurePonCoin_Top_shapeanim_joint";
}

/// @todo .sdata2 order hack
static void order_sdata2_0(void)
{
    /*  +0 */ (void) 0.0f;
    /*  +8 */ (void) S32_TO_F32;
    /* +10 */ (void) 1.0f;
    /* +14 */ (void) 3.0f;
    /* +18 */ (void) -0.74f;
    /* +1C */ (void) 30.0f;
    /* +20 */ (void) -0.72f;
    /* +24 */ (void) 0.4f;
    /* +28 */ (void) -0.026666667f;
    /* +2C */ (void) 35.0f;
    /* +30 */ (void) 100.0f;
    /* +34 */ (void) 999.0f;
    /* +38 */ (void) 1000.0f;
    /* +3C */ (void) 1.62f;
    /* +40 */ (void) 50.0f;
    /* +44 */ (void) 99.9f;
    /* +48 */ (void) 2.0f;
    /* +4C */ (void) -6.2f;
    /* +50 */ (void) -7.2f;
    /* +54 */ (void) 0.6f;
    /* +58 */ (void) -1.8f;
    /* +5C */ (void) 18.6f;
    /* +60 */ (void) 12.0f;
    /* +64 */ (void) 0.79f;
    /* +68 */ (void) 0.5f;
    /* +6C */ (void) deg_to_rad;
    /* +70 */ (void) -0.4f;
    /* +74 */ (void) 10.0f;
    /* +78 */ (void) -10.0f;
    /* +7C */ (void) -0.2f;
    /* +80 */ (void) 0.2f;
    /* +84 */ (void) 0.8f;
    /* +88 */ (void) -0.1f;
    /* +8C */ (void) 0.1f;
    /* +90 */ (void) 5.2f;
    /* +94 */ (void) 17.2f;
    /* +98 */ (void) 448.0f;
    /* +9C */ (void) 64.0f;
    /* +A0 */ (void) 1.6f;
    /* +A4 */ (void) 0.7f;
    /* +A8 */ (void) 0.0235f;
    /* +AC */ (void) 0.0715f;
    /* +B0 */ (void) -13.2f;
    /* +B4 */ (void) 9.4f;
    /* +B8 */ (void) 320.0f;
    /* +BC */ (void) 32.0f;
    /* +C0 */ (void) 0.027f;
    /* +C4 */ (void) 0.028f;
    /* +C8 */ (void) -13.599999f;
    /* +CC */ (void) 9.599999f;
}

void _tyFigupon_80314AA8(HSD_JObj* jobj, char* anim_str, char* matanim_str,
                         char* shapeanim_str)
{
    HSD_AnimJoint* ajoint;
    HSD_MatAnimJoint* majoint;
    HSD_ShapeAnimJoint* sajoint;
    struct un_804D6EF4_t* data = _tyFigupon_804D6EF4;
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
s32 _tyFigupon_80314B54(void)
{
    s32 i;
    s32 count = 0;

    for (i = 0; i < 0x125; i++) {
        if (Toy_80304CC8(i) != 0) {
            if (Toy_803048C0(i) != 0) {
                s32 result = (s32) Toy_803060BC(i, 6);
                if (result != 8 && (u32) result > 1) {
                    count++;
                }
            }
        }
    }
    return count;
}
#pragma dont_inline reset

void _tyFigupon_80314BE4(HSD_GObj* gobj, int unused)
{
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        HSD_SetEraseColor(0x19, 0x19, 0x33, 0xFF);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 0);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(NULL);
        HSD_CObjEndCurrent();
    }
}

void _tyFigupon_80314C5C(HSD_GObj* gobj)
{
    Toy* tp1 = GET_TOY(gobj);
    HSD_JObj* tmp_jobj = GET_JOBJ(gobj);
    HSD_JObj* jobj = tmp_jobj;
    struct un_804D6EF4_t* temp_r29 = _tyFigupon_804D6EF4;
    PAD_STACK(40);
    if (tp1 != NULL) {
        if (tp1->x8 % 30 == 0) {
            HSD_JObjReqAnimAll(jobj, 0.0f);
        }
        HSD_JObjAnimAll(jobj);
        if (tp1->x8-- != 0) {
            tp1->translate.y += tp1->offset.y;
            if (HSD_JObjGetTranslationX(jobj) >
                HSD_JObjGetTranslationX(temp_r29->jobjs[2]))
            {
                HSD_JObjAddTranslationX(jobj, tp1->translate.x);
            }
            if (HSD_JObjGetTranslationZ(jobj) >
                HSD_JObjGetTranslationZ(temp_r29->jobjs[2]))
            {
                HSD_JObjAddTranslationZ(jobj, tp1->translate.z);
            }
            HSD_JObjAddTranslationY(jobj, tp1->translate.y);
        } else {
            lbAudioAx_800237A8(146, 127, 64);
            tp1->x8 = 0;
            HSD_GObjPLink_80390228(gobj);
        }
    } else {
        Toy* tp = HSD_MemAlloc(0x58);
        if (tp != NULL) {
            GObj_InitUserData(gobj, 0, Toy_RemoveUserData, tp);
        }
        HSD_JObjReqAnimAll(jobj, HSD_Randi(15));
        HSD_AObjSetRate(jobj->child->aobj, 1.0f);
        {
            float temp_f30 = HSD_JObjGetTranslationX(temp_r29->jobjs[1]);
            float temp_f29 = HSD_JObjGetTranslationY(temp_r29->jobjs[1]);
            float temp_f31 = HSD_JObjGetTranslationZ(temp_r29->jobjs[1]);
            float temp_f28 = HSD_JObjGetTranslationX(temp_r29->jobjs[2]);
            float temp_f27 = HSD_JObjGetTranslationY(temp_r29->jobjs[2]);
            float temp_f26 = HSD_JObjGetTranslationZ(temp_r29->jobjs[2]);
            temp_f30 = (3.0f * HSD_Randf()) + temp_f30;
            temp_f29 = (3.0f * HSD_Randf()) + temp_f29;
            {
                float var_f3 = ABS(temp_f28 - temp_f30);
                tp->translate.x = -0.74f * (var_f3 / 30.0f);
                tp->translate.z = -0.72f * (ABS(temp_f26 - temp_f31) / 30.0f);
                tp->translate.y = 0.4f;
                tp->offset.y = -0.026666667f;
                tp->x8 = (s32) ABS(temp_f27 - temp_f29) + 35.0f;
            }
            temp_r29->x56 = tp->x8;
            HSD_JObjSetTranslateX(jobj, temp_f30);
            HSD_JObjSetTranslateY(jobj, temp_f29);
            HSD_JObjSetTranslateZ(jobj, temp_f31);
        }
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        lbAudioAx_80023870(147, 127, 64, 26);
    }
}

void _tyFigupon_803152BC(HSD_GObj* arg0)
{
    s32 temp_r3;
    struct un_804D6EF4_t* temp_r31;
    TyFiguponUD* temp_r30;
    TyFiguponUD* temp_r3_2;

    temp_r30 = HSD_GObjGetUserData(arg0);
    temp_r31 = _tyFigupon_804D6EF4;
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
        temp_r3_2->x8 =
            (s32) (temp_r3_2->x8 + (((temp_r31->x5E * 2) / 30) * 0x1E));
    }
}

typedef union {
    struct {
        s32 x0, x4, x8, xC;
    } s;
    s32 digits[4];
} TyFiguponDigitInit;

static const TyFiguponDigitInit _tyFigupon_803B8958 = { { 0, 0, 0, 0 } };

void _tyFigupon_803153EC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 count;
    TyFiguponDigitInit digits_s = _tyFigupon_803B8958;
    struct un_804D6EF4_t* temp_r30;
    HSD_JObj** jobj_ptr;
    s32 num;
    s32 i;
    s32 digit;

    num = arg0;
    temp_r30 = _tyFigupon_804D6EF4;
    digits_s.s.x8 = 0;
    digits_s.s.x4 = (count = 0);
    digits_s.s.x0 = (count = 0);
    do {
        digits_s.digits[count++] = num % 10;
        num /= 10;
    } while (num > 0);

    for (i = 0; i < arg2; i++) {
        digit = digits_s.digits[i];
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

void _tyFigupon_80315574(void)
{
    TyFiguponData* data = _tyFigupon_804D6EF0;

    if (data->x24 == 0) {
        data->x18->hidden = 1;
        data->x10 = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
    } else {
        data->x24 = data->x24 - 1;
    }
}

void _tyFigupon_803155C8(void)
{
    // TODO: One more regswap for 100%
    s32 new_var;
    ToyAnimState* aa8 = &Toy_804A2AA8;
    struct un_804D6EF4_t* ef4 = _tyFigupon_804D6EF4;
    TyFiguponData* data = _tyFigupon_804D6EF0;
    HSD_JObj* jobj = GET_JOBJ((HSD_GObj*) ef4->x08);
    s32 sc;
    s32 total;
    s32 i;
    f32 fval;
    f32 pct;
    PAD_STACK(16);

    switch (ef4->x5C) {
    case 2:
        ef4->x58 -= 1;
        if (ef4->x58 == 0) {
            data->x29 = 1;
            ef4->x58 = 0x14;
            HSD_JObjReqAnimAll(jobj, 0.0f);
            ef4->x5C = 3;
            gm_801678F8((s32) gm_801677F0(), 0x1E, 0);
            return;
        }
        break;
    case 3:
        if (ef4->x54 != 0) {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 0.0f);
        } else {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 1.0f);
        }
        HSD_JObjAnimAll(jobj);
        ef4->x58 -= 1;
        if (ef4->x58 == 0) {
            lbAudioAx_800237A8(0xA8, 0x7F, 0x40);
            ef4->x58 = 0xA;
            ef4->x58 += 0xA;
            ef4->x5C = 4;
            return;
        }
        break;
    case 4:
        if (ef4->x54 != 0) {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 0.0f);
        } else {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 1.0f);
        }
        HSD_JObjAnimAll(jobj);
        if (ef4->x58 < 0xE) {
            HSD_JObjReqAnimAll(jobj, 30.0f);
        }
        ef4->x58 -= 1;
        if (ef4->x58 == 0) {
            ef4->x58 = 0xE;
            ef4->x5C = 5;
            return;
        }
        break;
    case 5:
        ef4->x58 -= 1;
        if (ef4->x58 == 0) {
            sc = ef4->x5D;
            if (sc >= 3) {
                ef4->x58 = (s16) (1.62f * (f32) sc);
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
        if (ef4->x5D >= 3) {
            if (ef4->x54 != 0) {
                HSD_JObjReqAnimAll(ef4->jobjs[0xE], 0.0f);
            } else {
                HSD_JObjReqAnimAll(ef4->jobjs[0xE], 1.0f);
            }
            HSD_JObjAnimAll(jobj);
            if ((ef4->x58 % 40) == 0) {
                HSD_JObjReqAnimAll(jobj, 50.0f);
                lbAudioAx_80023870(0xA9, 0x7F, 0x40, 0x8A);
            }
            if (ef4->x58 < 0xE) {
                HSD_JObjReqAnimAll(jobj, 50.0f);
            }
        }
        ef4->x58 -= 1;
        if (ef4->x58 == 0) {
            if ((s8) data->x29 != 0) {
                s32 bet_count;
                new_var = _tyFigupon_80314B54();
                bet_count = ef4->x5D;
                fval = (f32) (ef4->x54 + new_var);
                lbAudioAx_80023694();
                if (bet_count != 0) {
                    bet_count -= 1;
                }
                pct = 100.0f * (((f32) ef4->x54 / fval) +
                                ((f32) (bet_count * 5) / 100.0f));
                if (pct >= 100.0f) {
                    pct = 99.9f;
                }
                data->x20 = Toy_80305058(0x63, 3, 0, pct);
                _tyFigupon_80316420(data->x20);
                {
                    s32 inv = _tyFigupon_80314B54();
                    // TODO: Initialization of this for loop is off
                    total = 0;
                    for (i = 0; i < 9; i++) {
                        if (i != 8 && i > 1U && Toy_80304B0C(i) != 0) {
                            total += Toy_80304B94(i);
                        }
                    }
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
        if (ef4->x58 == 0) {
            if (((HSD_Archive**) _tyFigupon_804D6EF8)[5] != NULL) {
                lbArchive_80016EFC(((HSD_Archive**) _tyFigupon_804D6EF8)[5]);
                ((HSD_Archive**) _tyFigupon_804D6EF8)[5] = NULL;
            }
            if (aa8->gobj != NULL) {
                HSD_GObjPLink_80390228(aa8->gobj);
                aa8->gobj = NULL;
                aa8->jobj[1] = NULL;
                aa8->jobj[0] = NULL;
            }
            HSD_SisLib_803A6368(data->x14, 0);
            Toy_803083D8(ef4->jobjs[0xC], 0x3E7);
            if ((s16) ef4->x54 == 0) {
                HSD_JObjReqAnimAll(ef4->jobjs[0xE], 1.0f);
                HSD_JObjAnimAll(jobj);
            }
            ef4->x5C = 9;
            return;
        }
        break;
    case 9:
        if ((gm_801623D8() / 10u) != 0) {
            i = 1;
            ef4->x5E = 1;
            _tyFigupon_803153EC(ef4->x5E, 6, 2, 0, 0);
            {
                struct un_804D6EF4_t* ef4_2 = _tyFigupon_804D6EF4;
                if (ef4_2->x5E == 0x14) {
                    i = 3;
                }
                if (ef4_2->x5E <= 1) {
                    i = 4;
                }
                HSD_JObjReqAnimAll(ef4_2->jobjs[8], (f32) i);
                HSD_AObjSetRate(ef4_2->jobjs[8]->aobj, 1.0f);
                HSD_JObjAnimAll(ef4_2->jobjs[8]);
            }
        }
        {
            struct un_804D6EF4_t* ef4_3 = _tyFigupon_804D6EF4;
            sc = ef4->x5E;
            fval = (f32) (ef4_3->x54 + _tyFigupon_80314B54());
            if (sc != 0) {
                sc -= 1;
            }
            if (ef4_3->x54 == 0) {
                pct = 0.0f;
            } else {
                pct = ((f32) ef4_3->x54 / fval) + ((f32) (sc * 5) / 100.0f);
            }
            if (pct >= 1.0f) {
                pct = 999.0f;
            } else {
                pct *= 1000.0f;
            }
            _tyFigupon_803153EC((u32) (s32) pct, 9, 3, 2, 0);
            ef4->x58 = 0;
            ef4->x56 = 0;
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            ef4->x5C = 0;
        }
        break;
    }
}

/// @todo .data order hack
static void order_data_108(void)
{
    /* +108 */ (void) "*** Not Get Figure!\n";
    /* +120 */ (void) __FILE__;
}

void _tyFigupon_80315C44(HSD_GObj* arg0)
{
    TyFiguponUD* ud;
    struct un_804D6EF4_t* ef4 = _tyFigupon_804D6EF4;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 total;
    s32 count;
    s32 anim;
    s32 i;

    PAD_STACK(24);

    ud = arg0->user_data;
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
                ef4 = _tyFigupon_804D6EF4;
                gobj = GObj_Create(9, 9, 0);
                jobj = HSD_JObjLoadJoint(HSD_ArchiveGetPublicAddress(
                    ef4->archive, "ToyFigurePonCoin_Top_joint"));
                HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
                GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0x3C, 0);
                _tyFigupon_80314AA8(jobj, "ToyFigurePonCoin_Top_animjoint",
                                    "ToyFigurePonCoin_Top_matanim_joint",
                                    "ToyFigurePonCoin_Top_shapeanim_joint");
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                HSD_GObj_SetupProc(gobj, _tyFigupon_80314C5C, 0);
                HSD_GObj_80390CD4(gobj);
                gm_801623FC(gm_801623D8() - 0xA);
                ef4->x5E = ef4->x5E - 1;
                total = gm_801623D8() / 10u;
                i = 0;
                ud->x18 = i;
                ud->x14 = i;
                ud->x10 = i;
                do {
                    ((s32*) ud)[i + 4] = total % 10;
                    total /= 10;
                    i++;
                } while (total > 0);
                count = ef4->x5E;
                i = 0;
                ud->x30 = i;
                ud->x2C = i;
                ud->x28 = i;
                do {
                    ((s32*) ud)[i + 10] = count % 10;
                    count /= 10;
                    i++;
                } while (count > 0);
                _tyFigupon_803153EC(gm_801623D8() / 10u, 3, 3, 1, 0);
                _tyFigupon_803153EC((u32) ef4->x5E, 6, 2, 0, 0);
                ef4 = _tyFigupon_804D6EF4;
                anim = 2;
                if (ef4->x5E == 0x14) {
                    anim = 3;
                }
                if (ef4->x5E <= 1) {
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
            _tyFigupon_803153EC(gm_801623D8() / 10u, 3, 3, 1, 0);
            _tyFigupon_803153EC((u32) ef4->x5E, 6, 2, 0, 0);
            ef4 = _tyFigupon_804D6EF4;
            if (ef4->x5E == 0x14) {
                anim = 3;
            }
            if (ef4->x5E <= 1) {
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
                ((s32*) ud)[i + 4] = total % 10;
                total /= 10;
                i++;
            } while (total > 0);
            _tyFigupon_803153EC(gm_801623D8() / 10u, 3, 3, 1, (s32) &ud->x10);
            HSD_AObjSetRate(ef4->jobjs[3]->child->u.dobj->mobj->tobj->aobj,
                            2.0f);
            HSD_AObjSetRate(ef4->jobjs[4]->child->u.dobj->mobj->tobj->aobj,
                            2.0f);
            HSD_AObjSetRate(ef4->jobjs[5]->child->u.dobj->mobj->tobj->aobj,
                            2.0f);
            ud->x8 = ef4->x5E * 2;
        }
    }
}

void _tyFigupon_80316170(HSD_GObj* arg0)
{
    ToyAnimState* aa8 = &Toy_804A2AA8;
    f32 y = HSD_JObjGetTranslationY(GET_JOBJ(arg0));
    TyFiguponUD* ud = HSD_GObjGetUserData(arg0);

    if (ud != NULL) {
        if (y + ud->x44 <= -6.2f) {
            if (Toy_803048C0(aa8->xC) == 1) {
                Toy_80306D14();
            }
            ((TyModeState*) Toy_804A284C)->x0 = 1;
            lbAudioAx_800237A8(0xA7, 0x7F, 0x40);
            HSD_JObjSetTranslateY(HSD_GObjGetHSDObj(arg0), -7.2f);
            gm_801678F8((s32) gm_801677F0(), 0xC, 0);
            GObj_RemoveUserData(arg0);
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            return;
        }
        ud->x44 -= 0.6f;
        HSD_JObjAddTranslationY(HSD_GObjGetHSDObj(arg0), ud->x44);
    } else {
        ud = HSD_MemAlloc(0x58);
        if (ud != NULL) {
            GObj_InitUserData(arg0, 0, Toy_RemoveUserData, ud);
        }
        ud->x44 = 0.0f;
    }
}

s32 _tyFigupon_8031638C(s16 arg0)
{
    s32 temp_r0;
    s32 var_r30;

    temp_r0 = (s32) Toy_803060BC((s32) arg0, 6);
    var_r30 = 0;
    switch (temp_r0) {
    case 0:
    case 1:
    case 4:
    case 6:
    case 8:
        break;
    case 7:
        if (Toy_803048C0((s32) arg0) > 0xFA) {
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

void _tyFigupon_80316420(s16 arg0)
{
    struct un_804D6EF4_t* ef4 = _tyFigupon_804D6EF4;
    TyFiguponData* data = _tyFigupon_804D6EF0;
    ToyAnimState* aa8 = &Toy_804A2AA8;
    s32 temp_r31;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    f32 angle;

    PAD_STACK(32);

    temp_r31 = Toy_803048C0(arg0);
    Toy_80308250((void*) _tyFigupon_804D6EF8, arg0, 0);
    gobj = Toy_803087F4(_tyFigupon_804D6EF8);
    HSD_JObjClearFlagsAll(aa8->jobj[0], JOBJ_HIDDEN);
    HSD_JObjSetFlagsAll(aa8->jobj[1], JOBJ_HIDDEN);
    jobj = HSD_GObjGetHSDObj(gobj);
    HSD_JObjSetTranslateX(jobj, -1.8f);
    HSD_JObjSetTranslateY(jobj, 18.6f);
    HSD_JObjSetTranslateZ(jobj, 12.0f);
    HSD_JObjSetScaleX(jobj, 0.79f);
    HSD_JObjSetScaleY(jobj, 0.79f);
    HSD_JObjSetScaleZ(jobj, 0.79f);
    angle = 30.0f * (2.0f * (HSD_Randf() - 0.5f));
    HSD_JObjSetRotationY(jobj, 0.017453292f * angle);
    HSD_GObj_SetupProc(gobj, _tyFigupon_80316170, 0);
    HSD_GObj_80390CD4(gobj);
    if (temp_r31 == 0) {
        Toy_80306B18(data->x8, 0, 0x48, 1);
        HSD_GObj_80390CD4(data->x8);
    }
    Toy_SetUnlockState(arg0, 1);
    Toy_8031234C(1);
    lb_8001CE00();
    Toy_80308328(arg0);
    HSD_SisLib_803A6368(data->x14, temp_r31);
    Toy_803083D8(ef4->jobjs[0xC], arg0);
    if (((TyModeState*) Toy_804A284C)->x0 == 2) {
        if ((u32) data->x10 == 0) {
            data->x10 = (s32) HSD_GObj_SetupProc(
                data->x0, (void (*)(HSD_GObj*)) _tyFigupon_80315574, 0);
        }
        data->x24 = 0x12C;
        ((TyFiguponData*) _tyFigupon_804D6EF0)->x18->hidden = 0;
    }
}
static const Vec3 _tyFigupon_803B8968 = { 0.0f, 1.0f, 0.0f };

static inline void tyFigupon_CalcCameraRot(f32* cy, f32* cx, f32* rot_y,
                                           f32* rot_x)
{
    HSD_PadStatus* pad;
    s32 i;
    f32 dead;

    if (-0.4f < *cx && *cx < 0.4f && -0.4f < *cy && *cy < 0.4f) {
        pad = &HSD_PadCopyStatus[i = 1];
        *cx = pad->nml_subStickX;
        *cy = pad->nml_subStickY;
        if (-0.4f < *cx && *cx < 0.4f && -0.4f < *cy && *cy < 0.4f) {
            pad = &HSD_PadCopyStatus[i = 2];
            *cx = pad->nml_subStickX;
            *cy = pad->nml_subStickY;
            if (-0.4f < *cx && *cx < 0.4f && -0.4f < *cy && *cy < 0.4f) {
                pad = &HSD_PadCopyStatus[i = 3];
                *cx = pad->nml_subStickX;
                *cy = pad->nml_subStickY;
                if (-0.4f < *cx && *cx < 0.4f && -0.4f < *cy && *cy < 0.4f) {
                }
            }
        }
    }

    if (-0.4f < *cx && *cx < 0.4f && -0.4f < *cy && *cy < 0.4f) {
        *rot_y = 0.0f;
        *rot_x = 0.0f;
    } else {
        if (-0.4f < *cx && *cx < 0.4f) {
            *rot_x = 0.0f;
        } else {
            if (*cx < 0.0f) {
                dead = -0.4f;
            } else {
                dead = 0.4f;
            }
            *rot_x = 30.0f * ((*cx - dead) / 0.6f);
        }
        if (-0.4f < *cy && *cy < 0.4f) {
            *rot_y = 0.0f;
        } else {
            if (*cy < 0.0f) {
                dead = -0.4f;
            } else {
                dead = 0.4f;
            }
            *rot_y = 30.0f * ((*cy - dead) / 0.6f);
        }
    }
}

void _tyFigupon_803168DC(HSD_GObj* arg0)
{
    u8 _padA[16];
    ToyAnimState* data = &Toy_804A2AA8;
    HSD_CObj* cobj = arg0->hsd_obj;
    Vec3 interest;
    Vec3 eye_pos;
    Vec3 up_copy;
    Vec3 cross;
    Vec3 eye_vec;
    Mtx mtx;
    f32 cx;
    f32 cy;
    f32 rot_x;
    f32 rot_y;
    f32 dead;
    s32 i;
    HSD_PadStatus* pad;

    PAD_STACK(8);

    pad = &HSD_PadCopyStatus[i = 0];
    cx = pad->nml_subStickX;
    cy = pad->nml_subStickY;
    tyFigupon_CalcCameraRot(&cy, &cx, &rot_y, &rot_x);
    HSD_CObjInit(cobj, _tyFigupon_804D6F04);
    up_copy = _tyFigupon_803B8968;
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

    if (data->gobj != NULL) {
        if (rot_y > 10.0f) {
            HSD_JObjClearFlagsAll(data->jobj[0], JOBJ_HIDDEN);
            HSD_JObjSetFlagsAll(data->jobj[1], JOBJ_HIDDEN);
            return;
        }
        if (rot_y < -10.0f) {
            HSD_JObjClearFlagsAll(data->jobj[1], JOBJ_HIDDEN);
            HSD_JObjSetFlagsAll(data->jobj[0], JOBJ_HIDDEN);
        }
    }
}

void _tyFigupon_80316BF8(HSD_GObj* arg0)
{
    lbAudioAx_80023F28(0x35);
    HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
}

void _tyFigupon_80316C24(HSD_GObj* arg0)
{
    struct un_804D6EF4_t* ef4 = _tyFigupon_804D6EF4;
    TyFiguponData* data = _tyFigupon_804D6EF0;
    f32 stick_scroll;
    s32 anim_frame;
    PAD_STACK(8);

    if (ef4->x5C != 0) {
        return;
    }

    {
        f32 stick = Toy_80305DB0();
        if (stick > -0.2f && stick < 0.2f) {
            stick_scroll = 0.0f;
        } else {
            s32 dir;
            if (stick > 0.0f) {
                dir = 1;
            } else {
                dir = -1;
            }
            stick_scroll = -((0.2f * (f32) dir) - stick) / 0.8f;
        }
    }

    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        mn_8022F268();
        ((TyModeState*) Toy_804A284C)->x4 = 1;
        return;
    }

    if (Toy_80305B88() & 0x200) {
        if (((u32) gm_801623D8() / 10u) == 0 || ef4->x5E <= 1) {
            lbAudioAx_80024030(0);
            ((TyModeState*) Toy_804A284C)->x4 = 1;
            return;
        }
        ef4->x5E = 1;
        _tyFigupon_803153EC(ef4->x5E, 6, 2, 0, 0);
        {
            struct un_804D6EF4_t* ef4_2 = _tyFigupon_804D6EF4;
            anim_frame = 2;
            if (ef4_2->x5E == 0x14) {
                anim_frame = 3;
            }
            if (ef4_2->x5E <= 1) {
                anim_frame = 4;
            }
            HSD_JObjReqAnimAll(ef4_2->jobjs[8], (f32) anim_frame);
            HSD_AObjSetRate(ef4_2->jobjs[8]->aobj, 1.0f);
            HSD_JObjAnimAll(ef4_2->jobjs[8]);
        }
        {
            struct un_804D6EF4_t* ef4_3 = _tyFigupon_804D6EF4;
            s32 sc;
            f32 pct;
            f32 fval;
            sc = ef4->x5E;
            fval = (f32) (ef4_3->x54 + _tyFigupon_80314B54());
            if (sc != 0) {
                sc -= 1;
            }
            if (ef4_3->x54 == 0) {
                pct = 0.0f;
            } else {
                pct = ((f32) ef4_3->x54 / fval) + ((f32) (sc * 5) / 100.0f);
            }
            if (pct >= 1.0f) {
                pct = 999.0f;
            } else {
                pct *= 1000.0f;
            }
            _tyFigupon_803153EC((u32) (s32) pct, 9, 3, 2, 0);
        }
        lbAudioAx_80024030(2);
        data->x28 = 1;
        return;
    }

    {
        u8 x28_val = data->x28;
        if ((s8) x28_val != 0) {
            data->x28 = (u8) (x28_val - 1);
            return;
        }
    }

    if (((u32) gm_801623D8() / 10u) == 0 || ef4->x5E == 0) {
        if (stick_scroll || (Toy_80305B88() & 0x1D7C)) {
            lbAudioAx_80024030(3);
            data->x28 = 0x1E;
        }
    } else {
        if (Toy_80305B88() & 0x10) {
            if ((u32) gm_801623D8() / 10u > 0x14U) {
                ef4->x5E = 0x14;
            } else {
                ef4->x5E = gm_801623D8() / 10u;
            }
            _tyFigupon_803153EC(ef4->x5E, 6, 2, 0, 0);
            {
                struct un_804D6EF4_t* ef4_4 = _tyFigupon_804D6EF4;
                anim_frame = 1;
                if (ef4_4->x5E == 0x14) {
                    anim_frame = 3;
                }
                if (ef4_4->x5E <= 1) {
                    anim_frame = 4;
                }
                HSD_JObjReqAnimAll(ef4_4->jobjs[8], (f32) anim_frame);
                HSD_AObjSetRate(ef4_4->jobjs[8]->aobj, 1.0f);
                HSD_JObjAnimAll(ef4_4->jobjs[8]);
            }
            {
                struct un_804D6EF4_t* ef4_5 = _tyFigupon_804D6EF4;
                s32 sc;
                f32 pct;
                f32 fval;
                sc = ef4->x5E;
                fval = (f32) (ef4_5->x54 + _tyFigupon_80314B54());
                if (sc != 0) {
                    sc -= 1;
                }
                if (ef4_5->x54 == 0) {
                    pct = 0.0f;
                } else {
                    pct =
                        ((f32) ef4_5->x54 / fval) + ((f32) (sc * 5) / 100.0f);
                }
                if (pct >= 1.0f) {
                    pct = 999.0f;
                } else {
                    pct *= 1000.0f;
                }
                _tyFigupon_803153EC((u32) (s32) pct, 9, 3, 2, 0);
            }
            lbAudioAx_80024030(2);
            data->x28 = 1;
            return;
        }
        if (Toy_80305B88() & 0x1160) {
            u8 temp = ef4->x5E;
            if ((s8) temp != 0) {
                ef4->x5D = temp;
                ef4->x56 = 0x1E;
                HSD_GObj_SetupProc((HSD_GObj*) ef4->x00, _tyFigupon_80315C44,
                                   0);
                HSD_GObj_80390CD4((HSD_GObj*) ef4->x00);
                HSD_GObj_SetupProc((HSD_GObj*) ef4->x0C, _tyFigupon_803152BC,
                                   0);
                HSD_GObj_80390CD4((HSD_GObj*) ef4->x0C);
                ef4->x5C = 1;
                HSD_GObj_SetupProc(
                    arg0, (void (*)(HSD_GObj*)) _tyFigupon_803155C8, 0);
                HSD_GObj_80390CD4(arg0);
                return;
            }
        }
        if (stick_scroll <= -0.1f || (Toy_80305C44() & 0x400) ||
            (Toy_80305B88() & 4))
        {
            u8 temp = ef4->x5E;
            if ((s8) temp > 1) {
                ef4->x5E = temp - 1;
                _tyFigupon_803153EC(ef4->x5E, 6, 2, 0, 0);
                {
                    struct un_804D6EF4_t* ef4_6 = _tyFigupon_804D6EF4;
                    anim_frame = 2;
                    if (ef4_6->x5E == 0x14) {
                        anim_frame = 3;
                    }
                    if (ef4_6->x5E <= 1) {
                        anim_frame = 4;
                    }
                    HSD_JObjReqAnimAll(ef4_6->jobjs[8], (f32) anim_frame);
                    HSD_AObjSetRate(ef4_6->jobjs[8]->aobj, 1.0f);
                    HSD_JObjAnimAll(ef4_6->jobjs[8]);
                }
                {
                    struct un_804D6EF4_t* ef4_7 = _tyFigupon_804D6EF4;
                    s32 sc;
                    f32 pct;
                    f32 fval;
                    sc = ef4->x5E;
                    fval = (f32) (ef4_7->x54 + _tyFigupon_80314B54());
                    if (sc != 0) {
                        sc -= 1;
                    }
                    if (ef4_7->x54 == 0) {
                        pct = 0.0f;
                    } else {
                        pct = ((f32) ef4_7->x54 / fval) +
                              ((f32) (sc * 5) / 100.0f);
                    }
                    if (pct >= 1.0f) {
                        pct = 999.0f;
                    } else {
                        pct *= 1000.0f;
                    }
                    _tyFigupon_803153EC((u32) (s32) pct, 9, 3, 2, 0);
                }
                lbAudioAx_80024030(2);
                data->x28 = 3;
            }
        } else if (stick_scroll >= 0.1f || (Toy_80305C44() & 0x800) ||
                   (Toy_80305B88() & 8))
        {
            u8 temp;
            u32 total = gm_801623D8() / 10u;
            temp = ef4->x5E;
            if ((u32) (s8) temp < total && (s8) temp < 0x14) {
                ef4->x5E = temp + 1;
                _tyFigupon_803153EC(ef4->x5E, 6, 2, 0, 0);
                {
                    struct un_804D6EF4_t* ef4_8 = _tyFigupon_804D6EF4;
                    anim_frame = 1;
                    if (ef4_8->x5E == 0x14) {
                        anim_frame = 3;
                    }
                    if (ef4_8->x5E <= 1) {
                        anim_frame = 4;
                    }
                    HSD_JObjReqAnimAll(ef4_8->jobjs[8], (f32) anim_frame);
                    HSD_AObjSetRate(ef4_8->jobjs[8]->aobj, 1.0f);
                    HSD_JObjAnimAll(ef4_8->jobjs[8]);
                }
                {
                    struct un_804D6EF4_t* ef4_9 = _tyFigupon_804D6EF4;
                    s32 sc;
                    f32 pct;
                    f32 fval;
                    sc = ef4->x5E;
                    fval = (f32) (ef4_9->x54 + _tyFigupon_80314B54());
                    if (sc != 0) {
                        sc -= 1;
                    }
                    if (ef4_9->x54 == 0) {
                        pct = 0.0f;
                    } else {
                        pct = ((f32) ef4_9->x54 / fval) +
                              ((f32) (sc * 5) / 100.0f);
                    }
                    if (pct >= 1.0f) {
                        pct = 999.0f;
                    } else {
                        pct *= 1000.0f;
                    }
                    _tyFigupon_803153EC((u32) (s32) pct, 9, 3, 2, 0);
                }
                lbAudioAx_80024030(2);
                data->x28 = 3;
            }
        } else {
            struct un_804D6EF4_t* ef4_10 = _tyFigupon_804D6EF4;
            anim_frame = 0;
            if (ef4_10->x5E == 0x14) {
                anim_frame = 3;
            }
            if (ef4_10->x5E <= 1) {
                anim_frame = 4;
            }
            HSD_JObjReqAnimAll(ef4_10->jobjs[8], (f32) anim_frame);
            HSD_AObjSetRate(ef4_10->jobjs[8]->aobj, 1.0f);
            HSD_JObjAnimAll(ef4_10->jobjs[8]);
        }
    }
}

/* 3B8974 */ static TyFiguponDigitInit const _tyFigupon_803B8974 = {
    { 0, 0, 0, 0 }
};
/* 3FEB88 */ static u16 _tyFigupon_803FEB88[] = {
    4, 2, 3, 5, 6, 7, 8, 9, 13, 10, 11, 12, 14,
};
/* 4D5AA0 */ static u16 _tyFigupon_804D5AA0[2] = { 12, 0 };

void _tyFigupon_8031753C(void)
{
    s32 new_count;
    struct un_804D6EF4_t* ef4 = _tyFigupon_804D6EF4;
    HSD_Joint* joint;
    HSD_Joint* bet_joint;
    HSD_Joint* par_joint;
    HSD_Joint* panel_joint;
    HSD_JObj* jobj;
    s32 count;
    s32 i;
    s32 trophy_total;
    u8 _padA[24];

    if (ef4->archive == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        OSPanic(__FILE__, 1372, "");
    }
    if (ef4->x00 != 0) {
        HSD_GObjPLink_80390228((HSD_GObj*) ef4->x00);
        ef4->x00 = 0;
    }
    panel_joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                              "ToyFigurePonPanel_Top_joint");
    if (panel_joint != NULL) {
        s32 total;
        TyFiguponDigitInit digits_s;
        ef4->x00 = (u32) GObj_Create(9, 9, 0);
        jobj = HSD_JObjLoadJoint(panel_joint);
        {
            HSD_GObj* gobj = (HSD_GObj*) ef4->x00;
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        }
        GObj_SetupGXLink((HSD_GObj*) ef4->x00, HSD_GObj_JObjCallback, 0x3C, 1);
        lb_8001204C(jobj, ef4->jobjs, _tyFigupon_803FEB88, 0xD);
        _tyFigupon_80314AA8(ef4->jobjs[0xC], NULL,
                            "ToyFigurePonPanel_zsmash_matanim_joint", NULL);
        Toy_803083D8(ef4->jobjs[0xC], 0x3E7);
        joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                            "ToyFigurePonBg_Top_joint");
        ef4->unk4 = GObj_Create(9, 9, 0);
        jobj = HSD_JObjLoadJoint(joint);
        {
            HSD_GObj* gobj = ef4->unk4;
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        }
        GObj_SetupGXLink(ef4->unk4, HSD_GObj_JObjCallback, 0x3C, 0);
        _tyFigupon_80314AA8(jobj, "ToyFigurePonBg_Top_animjoint",
                            "ToyFigurePonBg_Top_matanim_joint",
                            "ToyFigurePonBg_Top_shapeanim_joint");
        HSD_GObj_SetupProc(ef4->unk4, Toy_80306BB8, 0);
        HSD_GObj_80390CD4(ef4->unk4);
        jobj = HSD_JObjLoadJoint(HSD_ArchiveGetPublicAddress(
            ef4->archive, "ToyFigurePonCoin_Top_joint"));
        HSD_JObjAddChild(ef4->jobjs[0], jobj);
        _tyFigupon_80314AA8(jobj, "ToyFigurePonCoin_Top_animjoint",
                            "ToyFigurePonCoin_Top_matanim_joint",
                            "ToyFigurePonCoin_Top_shapeanim_joint");
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);

        digits_s = _tyFigupon_803B8974;
        count = 0;
        total = (s32) (gm_801623D8() / 10u);
        joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                            "ToyFigurePonNm_Top_joint");
        do {
            digits_s.digits[count++] = total % 10;
            total /= 10;
        } while (total > 0);

        for (i = 0; i < 3; i++) {
            jobj = HSD_JObjLoadJoint(joint);
            HSD_JObjAddChild(ef4->jobjs[3 + i], jobj);
            _tyFigupon_80314AA8(jobj, "ToyFigurePonNm_Top_animjoint",
                                "ToyFigurePonNm_Top_matanim_joint",
                                "ToyFigurePonNm_Top_shapeanim_joint");
            if (digits_s.digits[i] != 0) {
                HSD_JObjReqAnimAll(jobj, (f32) (50 - digits_s.digits[i] * 5));
            } else {
                HSD_JObjReqAnimAll(jobj, 0.0f);
            }
            HSD_JObjAnimAll(jobj);
        }

        bet_joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                                "ToyFigurePonBet_Top_joint");
        for (count = 0; count < 2; count++) {
            jobj = HSD_JObjLoadJoint(bet_joint);
            HSD_JObjAddChild(ef4->jobjs[6 + count], jobj);
            _tyFigupon_80314AA8(jobj, "ToyFigurePonBet_Top_animjoint",
                                "ToyFigurePonBet_Top_matanim_joint",
                                "ToyFigurePonBet_Top_shapeanim_joint");
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
        }

        _tyFigupon_80314AA8(ef4->jobjs[8], NULL,
                            "ToyFigurePonPanel_zarrow_matanim_joint", NULL);

        joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                            "ToyFigurePonLever_Top_joint");
        ef4->x08 = (u32) GObj_Create(9, 9, 0);
        jobj = HSD_JObjLoadJoint(joint);
        {
            HSD_GObj* gobj = (HSD_GObj*) ef4->x08;
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        }
        GObj_SetupGXLink((HSD_GObj*) ef4->x08, HSD_GObj_JObjCallback, 0x3C, 0);
        _tyFigupon_80314AA8(jobj, "ToyFigurePonLever_Top_animjoint",
                            "ToyFigurePonLever_Top_matanim_joint",
                            "ToyFigurePonLever_Top_shapeanim_joint");
        lb_8001204C(jobj, &ef4->jobjs[0xE], _tyFigupon_804D5AA0, 1);

        trophy_total = _tyFigupon_80314B54();
        new_count = 0;
        i = new_count;
        do {
            if (i != 8 && (u32) i > 1U && Toy_80304B0C(i) != 0) {
                new_count += Toy_80304B94(i);
            }
            i += 1;
        } while (i < 9);
        if (new_count - trophy_total != 0) {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 0.0f);
        } else {
            HSD_JObjReqAnimAll(ef4->jobjs[0xE], 1.0f);
        }
        HSD_JObjAnimAll(ef4->jobjs[0xE]);

        ef4->x0C = (u32) GObj_Create(9, 9, 0);
        par_joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                                "ToyFigurePonPar_Top_joint");
        for (count = 0; count < 3; count++) {
            jobj = HSD_JObjLoadJoint(par_joint);
            HSD_JObjAddChild(ef4->jobjs[9 + count], jobj);
            _tyFigupon_80314AA8(jobj, "ToyFigurePonPar_Top_animjoint",
                                "ToyFigurePonPar_Top_matanim_joint",
                                "ToyFigurePonPar_Top_shapeanim_joint");
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
        }
        return;
    }
    OSReport("*** Can not Load Panel Label(%s)\n",
             "ToyFigurePonPanel_Top_joint");
    OSPanic(__FILE__, 1552, "");
}

/// @todo .data order hack
static void order_data_4A8(void)
{
    /* +4A8 */ (void) "ScMenFigure_scene_lights";
}

/* 3FEED4 */ static HSD_WObjDesc _tyFigupon_803FEED4 = {
    NULL,
    { 0.0f, 0.0f, 50.0f },
    NULL,
};
/* 3FEEE8 */ static HSD_WObjDesc _tyFigupon_803FEEE8 = {
    NULL,
    { 0.0f, 0.0f, 0.0f },
    NULL,
};
/* 3FEEFC */ static HSD_CameraDescPerspective _tyFigupon_803FEEFC = {
    NULL,
    0,
    PROJ_PERSPECTIVE,
    { 0, 640, 0, 480 },
    { 0, 640, 0, 480 },
    &_tyFigupon_803FEED4,
    &_tyFigupon_803FEEE8,
    0.0f,
    NULL,
    0.1f,
    (float) 0x8000,
    40.0f,
    913.0f / 750.0f,
};

void _tyFigupon_80317A60(void)
{
    TyFiguponData* data = _tyFigupon_804D6EF0;
    HSD_CameraDescPerspective* cam_desc;
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    struct un_804D6EF4_t* new_var; // Permuter slop
    HSD_Text* text;
    PAD_STACK(40);
    new_var = _tyFigupon_804D6EF4;
    cam_desc = HSD_ArchiveGetPublicAddress(new_var->archive,
                                           "ScMenFigure_scene_lights");
    data->x0 = GObj_Create(1, 2, 0);
    cobj = lb_80013B14(cam_desc);
    _tyFigupon_804D6F04 = (HSD_CObjDesc*) cam_desc;
    HSD_GObjObject_80390A70(data->x0, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(data->x0, _tyFigupon_80314BE4, 0);
    gobj = data->x0;
    gobj->gxlink_prios = 0x5010000000000000ULL;
    data->x4 = GObj_Create(1, 2, 0);
    // cobj = lb_80013B14(&_Toy_803FE68C);
    // _tyFigupon_804D6F08 = &_Toy_803FE68C;
    // Unholiest of Permuter slop
    HSD_GObjObject_80390A70(
        data->x4,
        (((((((((((HSD_GObj_804D784B & 0xFFFFFFFFFFFFFFFFu) &
                  0xFFFFFFFFFFFFFFFFu) &
                 0xFFFFFFFFFFFFFFFFu) &
                0xFFFFFFFFFFFFFFFFu) &
               0xFFFFFFFFFFFFFFFFu) &
              0xFFFFFFFFFFFFFFFFu) &
             0xFFFFFFFFFFFFFFFFu) &
            0xFFFFFFFFFFFFFFFFu) &
           0xFFFFFFFFFFFFFFFFu) &
          0xFFFFFFFFFFFFFFFFu) &
         0xFFFFFFFFFFFFFFFFu) &
            0xFFFFFFFFFFFFFFFFu,
        cobj);
    GObj_SetupGXLinkMax(data->x4, (GObj_RenderFunc) (Event) Toy_803068E0, 0);
    gobj = data->x4;
    gobj->gxlink_prios = 0x2680000000000000ULL;

    if (lbLang_IsSavedLanguageJP() != 0) {
        HSD_SisLib_803A62A0(0, "SdToy.dat", "SIS_ToyData");
    } else {
        HSD_SisLib_803A62A0(0, "SdToy.usd", "SIS_ToyData_E");
    }

    _tyFigupon_804D6EFC =
        HSD_SisLib_803A611C(0, data->x0, 0xB, 0xB, 0, 0x3E, 0, 0);
    data->x14 = HSD_SisLib_803A5ACC(0, _tyFigupon_804D6EFC, 5.2f, 5.2f, 17.2f,
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

    _tyFigupon_804D6F00 =
        HSD_SisLib_803A611C(0, data->x0, 0xD, 0xB, 0, 0x3E, 0, 0);
    data->x18 = HSD_SisLib_803A5ACC(0, _tyFigupon_804D6F00, -13.2f, 9.4f,
                                    17.2f, 320.0f, 32.0f);
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
    _tyFigupon_804D6EF0->x18->hidden = 1;

    HSD_GObj_SetupProc(data->x0, _tyFigupon_80316C24, 0);
    HSD_GObj_SetupProc(data->x0, _tyFigupon_803168DC, 0);
    HSD_GObj_SetupProc(data->x4, _tyFigupon_803168DC, 0);
    HSD_GObj_SetupProc(data->x0, _tyFigupon_80316BF8, 0);
    HSD_GObj_80390CD4(data->x0);
}

static inline TyFiguponED4* tyFigupon_GetED4(void)
{
    return (TyFiguponED4*) Toy_sbss_804D6ED4;
}

static inline void tyFigupon_UpdateRemainingCount(struct un_804D6EF4_t* ef4)
{
    s32 total_b54;
    s32 count;
    s32 i;

    total_b54 = _tyFigupon_80314B54();
    count = 0;
    i = 0;
    do {
        if (i != 8 && (u32) i > 1U && Toy_80304B0C(i) != 0) {
            count += Toy_80304B94(i);
        }
        i += 1;
    } while (i < 9);
    ef4->x54 = count - total_b54;
}

static inline void tyFigupon_InitScene(struct un_804D6EF4_t** ef4_2,
                                       TyFiguponED4** ed4)
{
    _tyFigupon_80317A60();
    *ef4_2 = _tyFigupon_804D6EF4;
    *ed4 = tyFigupon_GetED4();
    if ((*ef4_2)->archive == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        OSPanic(__FILE__, 1575, "");
    }
}

void tyFigupon_OnEnter_80317D80(void* arg0)
{
    s16 x54;
    s32 x5E;
    TyFiguponData* data;
    struct un_804D6EF4_t* ef4;
    TyFiguponED4* ed4;
    struct un_804D6EF4_t* ef4_2;
    HSD_Joint* joint;
    HSD_JObj* jobj;
    void* ud;
    f32 total;
    f32 pct;
    char* archive_name;
    void* sp20;
    PAD_STACK(16);

    _tyFigupon_804D6EF0 = HSD_MemAlloc(0x34);
    _tyFigupon_804D6EF4 = HSD_MemAlloc(0x60);
    _tyFigupon_804D6EF8 = HSD_MemAlloc(0x18);
    Toy_sbss_804D6ED4 = HSD_MemAlloc(0xE4);
    memzero(_tyFigupon_804D6EF0, 0x34);
    memzero(_tyFigupon_804D6EF4, 0x60);
    memzero(_tyFigupon_804D6EF8, 0x18);
    memzero(Toy_sbss_804D6ED4, 0xE4);
    data = _tyFigupon_804D6EF0;
    Toy_sbss_804D6EC8 = NULL;
    ef4 = _tyFigupon_804D6EF4;
    Toy_8031263C();
    Toy_80305918(3, 0, 1);
    ((TyModeState*) Toy_804A284C)->x0 = 1;
    if (lbLang_IsSavedLanguageJP() != 0) {
        archive_name = "TyMnFigp.dat";
    } else {
        archive_name = "TyMnFigp.usd";
    }
    ef4->archive = lbArchive_LoadSymbols(archive_name, &sp20,
                                         "ToyFigurePonPanel_Top_joint", 0);
    ef4->x58 = 0;
    tyFigupon_InitScene(&ef4_2, &ed4);
    {
        LightList** temp = HSD_ArchiveGetPublicAddress(
            ef4_2->archive, "ScMenFigure_scene_lights");
        if (temp != NULL) {
            HSD_LObj* lobj;
            ed4->x0 = (u32) GObj_Create(2, 3, 0);
            lobj = Toy_LoadLObjList(temp, 0);
            {
                HSD_GObj* gobj = (HSD_GObj*) ed4->x0;
                HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
            }
            {
                HSD_GObj* gobj = (HSD_GObj*) ed4->x0;
                GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0x34, 0);
            }
        }
    }
    memzero(Toy_sbss_804D6ED4, 0xE4);
    Toy_80306D70(0);
    _tyFigupon_8031753C();
    joint = HSD_ArchiveGetPublicAddress(ef4->archive,
                                        "ToyFigurePonNget_Top_joint");
    data->x8 = GObj_Create(0xA, 0xA, 0);
    jobj = HSD_JObjLoadJoint(joint);
    {
        HSD_GObj* gobj = data->x8;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    }
    _tyFigupon_80314AA8(jobj, "ToyFigurePonNget_Top_animjoint",
                        "ToyFigurePonNget_Top_matanim_joint",
                        "ToyFigurePonNget_Top_shapeanim_joint");
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjAddTranslationZ(jobj, 0.5f);
    ud = HSD_MemAlloc(0x58);
    if (ud != NULL) {
        GObj_InitUserData(data->x8, 0, Toy_RemoveUserData, ud);
    }
    GObj_SetupGXLink(data->x8, HSD_GObj_JObjCallback, 0x3D, 0);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    {
        s32 has_coin_credit;
        if (((u32) gm_801623D8() / 10u) != 0) {
            has_coin_credit = 1;
        } else {
            has_coin_credit = 0;
        }
        ef4->x5E = has_coin_credit;
    }
    _tyFigupon_803153EC((s8) ef4->x5E, 6, 2, 0, 0);
    tyFigupon_UpdateRemainingCount(ef4);
    x5E = ef4->x5E;
    ef4 = _tyFigupon_804D6EF4;
    {
        s32 b54 = _tyFigupon_80314B54();
        x54 = ef4->x54;
        total = (f32) (x54 + b54);
    }
    if (x5E != 0) {
        x5E -= 1;
    }
    if (x54 == 0) {
        pct = 0.0f;
    } else {
        pct = ((f32) x54 / total) + ((f32) (x5E * 5) / 100.0f);
    }
    if (pct >= 1.0f) {
        pct = 999.0f;
    } else {
        pct *= 1000.0f;
    }
    _tyFigupon_803153EC((s32) pct, 9, 3, 2, 0);
    HSD_PadRenewStatus();
}

s32 _tyFigupon_803181BC(void)
{
    TyFiguponData* temp_r31;
    struct un_804D6EF4_t* ef4;
    TyFiguponED4* ed4;
    PAD_STACK(8);

    ef4 = _tyFigupon_804D6EF4;
    temp_r31 = _tyFigupon_804D6EF0;
    ed4 = (TyFiguponED4*) Toy_sbss_804D6ED4;
    if (ef4->archive != NULL) {
        ef4->archive = NULL;
    }
    if (Toy_sbss_804D6EC8 != NULL) {
        Toy_sbss_804D6EC8 = NULL;
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

void tyFigupon_OnFrame_803182D4(void)
{
    TyModeState* state = (TyModeState*) Toy_804A284C;

    if (state->x4 != 0) {
        _tyFigupon_803181BC();
        gm_801A4B60();
    }
}

#include "mncharsel.h"

#include "mncharsel.static.h"

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/types.h>
#include <melee/mn/mncharsel.h>
#include <melee/mn/mnname.h>

TextKerning* mnCharSel_8025BC20(TextKerning* arg0, u32 arg1)
{
    TextKerning* kerning;
    u32 render_zeroes;
    render_zeroes = 0;
    kerning = HSD_SisLib_804D1124[0][41].kerning;
    if (arg1 >= 10000) {
        arg1 = 9999;
    }
    if (arg1 >= 1000) {
        arg0->left = kerning[arg1 / 1000].left;
        arg0->right = kerning[arg1 / 1000].right;
        arg0 += 1;
        arg1 = arg1 % 1000;
        render_zeroes = 1;
    }
    if ((arg1 >= 100) || render_zeroes) {
        arg0->left = kerning[arg1 / 100].left;
        arg0->right = kerning[arg1 / 100].right;
        arg0 = arg0 + 1;
        arg1 = arg1 % 100;
        render_zeroes++;
    }
    if ((arg1 >= 10) || render_zeroes) {
        arg0->left = kerning[arg1 / 10].left;
        arg0->right = kerning[arg1 / 10].right;
        arg0 = arg0 + 1;
        arg1 = arg1 % 10;
    }
    arg0->left = kerning[arg1].left;
    arg0->right = kerning[arg1].right;
    arg0[1].left = 0;
    return ++arg0;
}

void mnCharSel_8025BD30(void)
{
    TextKerning* kerning;
    u32 match_type;

    kerning = HSD_SisLib_804D1124[0][37].kerning;

    match_type = mnCharSel_804D6CB0->match_type;

    if (match_type == 1) {
        HSD_SisLib_803A6530(0, 0x4A, 0x4F);
        return;
    }
    if (match_type == 2) {
        HSD_SisLib_803A6530(0, 0x4A, 0x50);
        return;
    }
    if (lbLang_IsSavedLanguageJP()) {
        if (gmMainLib_8015CC34()->mode == 1) {
            mnCharSel_8025BC20(kerning, gmMainLib_8015CC34()->stock_count);
        } else if (gmMainLib_8015CC34()->time_limit != 0) {
            mnCharSel_8025BC20(kerning, gmMainLib_8015CC34()->time_limit);
            HSD_SisLib_803A660C(0, 0x4A, 0x53);
        } else {
            HSD_SisLib_803A6530(0, 0x4A, 0x51);
        }
        switch (gmMainLib_8015CC34()->mode) {
        case Mode_Time:
            HSD_SisLib_803A660C(0, 0x4A, 0x4B);
            return;
        case Mode_Stock:
            HSD_SisLib_803A660C(0, 0x4A, 0x4C);
            return;
        case Mode_Coin:
            HSD_SisLib_803A660C(0, 0x4A, 0x4D);
            return;
        case Mode_Bonus:
            HSD_SisLib_803A660C(0, 0x4A, 0x4E);
            return;
        }
    } else {
        switch (gmMainLib_8015CC34()->mode) {
        case Mode_Time:
            if (gmMainLib_8015CC34()->time_limit != 0) {
                mnCharSel_8025BC20(kerning, gmMainLib_8015CC34()->time_limit);
                HSD_SisLib_803A660C(0, 0x4A, 0x53);
            } else {
                HSD_SisLib_803A6530(0, 0x4A, 0x51);
            }
            HSD_SisLib_803A660C(0, 0x4A, 0x4B);
            return;
        case Mode_Stock:
            mnCharSel_8025BC20(kerning, gmMainLib_8015CC34()->stock_count);
            if (gmMainLib_8015CC34()->stock_count < 2U) {
                HSD_SisLib_803A660C(0, 0x4A, 0x55);
            } else {
                HSD_SisLib_803A660C(0, 0x4A, 0x54);
            }
            HSD_SisLib_803A660C(0, 0x4A, 0x4C);
            return;
        case Mode_Coin:
            if (gmMainLib_8015CC34()->time_limit != 0) {
                mnCharSel_8025BC20(kerning, gmMainLib_8015CC34()->time_limit);
                HSD_SisLib_803A660C(0, 0x4A, 0x53);
            } else {
                HSD_SisLib_803A6530(0, 0x4A, 0x51);
            }
            HSD_SisLib_803A660C(0, 0x4A, 0x4D);
            return;
        case Mode_Bonus:
            if (gmMainLib_8015CC34()->time_limit != 0) {
                mnCharSel_8025BC20(kerning, gmMainLib_8015CC34()->time_limit);
                HSD_SisLib_803A660C(0, 0x4A, 0x53);
            } else {
                HSD_SisLib_803A6530(0, 0x4A, 0x51);
            }
            HSD_SisLib_803A660C(0, 0x4A, 0x4E);
            return;
        }
    }
}

static inline void inline1(HSD_Text* x, HSD_Text* y, int r6, int r7, int r8,
                           int r31)
{
    if (r6 == 0) {
        HSD_SisLib_803A70A0(x, 0, "%02d:%02d", r7, r8);
        HSD_SisLib_803A70A0(y, 0, "%02d", r31);
    } else if (r6 < 0x64) {
        HSD_SisLib_803A70A0(x, 0, "%d:%02d:%02d", r6, r7, r8);
        HSD_SisLib_803A70A0(y, 0, "%02d", r31);
    } else {
        HSD_SisLib_803A70A0(x, 0, "99:59:59");
        HSD_SisLib_803A70A0(y, 0, "99");
    }
}

static inline HSD_JObj* inline3(int i, float x)
{
    HSD_JObj* sp5C;
    float temp_f1_6 = x + 1;
    lb_80011E24(mnCharSel_804D6CC0, &sp5C, i, -1);
    HSD_ForeachAnim(sp5C, JOBJ_TYPE, MOBJ_MASK, HSD_AObjReqAnim, AOBJ_ARG_AF,
                    temp_f1_6);
    HSD_JObjAnimAll(sp5C);
    HSD_ForeachAnim(sp5C, JOBJ_TYPE, MOBJ_MASK, HSD_AObjStopAnim, AOBJ_ARG_AOV,
                    0, 0);
    return sp5C;
}

#define show_kos(x, y)                                                        \
    (lbLang_IsSavedLanguageJP()                                               \
         ? HSD_SisLib_803A70A0((x), 0, "%d 人抜き", (y))                      \
         : HSD_SisLib_803A70A0((x), 0, "%d ＫＯｓ", (y)))

void mnCharSel_8025C020(int arg0)
{
    HSD_JObj* sp7C;
    u8 sp7B;
    u8 sp7A;
    u8 sp79;
    u8 sp78;
    u8 sp74[4];
    HSD_JObj* sp70;

    int i = mnCharSel_803F0DFC.doors[0].sel_icon;
    int temp_r31 = icons[i].ft_hudindex;
    if (arg0 != 0) {
        if (mnCharSel_804D6CDC != 0U) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, NULL);
        }
        if (mnCharSel_804D6CE0 != 0U) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE0, 0, NULL);
        }
    }
    switch (mnCharSel_804D6CB0->match_type) {
    case 11:
        sp7C = inline3(0x42, *gmMainLib_8015D194(temp_r31));
        if (arg0 != 0) {
            HSD_JObjSetFlags(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%08d",
                                gm_80162BD8(temp_r31));
            if (gmMainLib_8015D0D8(temp_r31) != 0) {
                HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
            }
        }
        HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%09d", gm_80162C48());
        if (gm_80162D1C() != 0) {
            sp7C = inline3(0x43, gm_80162D6C());
            HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
        }
        break;
    case 12:
        sp7C = inline3(0x42, *gmMainLib_8015D2BC(temp_r31));
        if (arg0 != 0) {
            HSD_JObjSetFlags(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%08d",
                                gm_80162DD4(temp_r31));
            if (gmMainLib_8015D200(temp_r31) != 0) {
                HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
            }
        }
        HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%09d", gm_80162E44());
        if (gm_80162F18() != 0) {
            sp7C = inline3(0x43, gm_80162F68());
            HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
        }
        break;
    case 13:
        sp7C = inline3(0x42, *gmMainLib_8015D3E4(temp_r31));
        if (arg0 != 0) {
            HSD_JObjSetFlags(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%08d",
                                gm_80162FD0(temp_r31));
            if (gmMainLib_8015D328(temp_r31) != 0) {
                HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
            }
        }
        HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%09d", gm_80163040());
        if (gm_80163114() != 0) {
            sp7C = inline3(0x43, gm_80163164());
            HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
        }
        break;
    case 15:
        if (arg0 == 0) {
            int temp_r29 = gm_8016332C(temp_r31);
            if (temp_r29 != -1U) {
                if (lbLang_IsSavedLanguageJP() != 0) {
                    HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d 個",
                                        temp_r29);
                } else {
                    HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0,
                                        &mnCharSel_804D5108, temp_r29);
                }
            } else {
                gm_80163374(temp_r31, &sp7B, &sp7A, &sp79, &sp78);
                inline1(mnCharSel_804D6CDC, mnCharSel_804D6CE0, sp7B, sp7A,
                        sp79, sp78);
            }
        }
        lb_80011E24(mnCharSel_804D6CC8, &sp7C, 3, -1);
        if (gm_801634D4(&sp7B, &sp7A, &sp79, &sp78) != 0) {
            inline1(mnCharSel_804D6CE4, mnCharSel_804D6CE8, sp7B, sp7A, sp79,
                    sp78);
            HSD_JObjClearFlagsAll(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, NULL);
            HSD_SisLib_803A70A0(mnCharSel_804D6CE8, 0, NULL);
            HSD_JObjSetFlagsAll(sp7C, JOBJ_HIDDEN);
        }
        break;
    case 16:
        if (arg0 == 0) {
            if (lbLang_IsSavedLanguageJP()) {
                HSD_SisLib_803A70A0(
                    mnCharSel_804D6CDC, 0, "%.1f",
                    (f32) (int) (10.0f * (gm_801631CC(temp_r31) / 100.0f)) /
                        10.0f);
            } else {
                HSD_SisLib_803A70A0(
                    mnCharSel_804D6CDC, 0, "%.1f",
                    (f32) (int) (10.0f * (gm_801631CC(temp_r31) / 30.4788f)) /
                        10.0f);
            }
        }
        if (lbLang_IsSavedLanguageJP()) {
            HSD_SisLib_803A70A0(
                mnCharSel_804D6CE4, 0, "%.1f",
                (f32) (int) (10.0f * (gm_801631F0() / 100.0f)) / 10.0f);
        } else {
            HSD_SisLib_803A70A0(
                mnCharSel_804D6CE4, 0, "%.1f",
                (f32) (int) (10.0f * (gm_801631F0() / 30.4788f)) / 10.0f);
        }
        break;
    case 23:
        if (arg0 == 0) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d",
                                gm_80163274(temp_r31));
        }
        break;
    case 17:
        if (arg0 == 0) {
            if (gm_8016365C(temp_r31) != 0) {
                show_kos(mnCharSel_804D6CDC, gm_80163690(temp_r31));
            } else {
                gm_801636D8(temp_r31, &sp7B, &sp7A, &sp79, &sp78);
                inline1(mnCharSel_804D6CDC, mnCharSel_804D6CE0, sp7B, sp7A,
                        sp79, sp78);
            }
        }
        lb_80011E24(mnCharSel_804D6CC8, &sp7C, 3, -1);
        if (gm_80163838(&sp7B, &sp7A, &sp79, &sp78) != 0) {
            inline1(mnCharSel_804D6CE4, mnCharSel_804D6CE8, sp7B, sp7A, sp79,
                    sp78);
            HSD_JObjClearFlagsAll(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, NULL);
            HSD_SisLib_803A70A0(mnCharSel_804D6CE8, 0, NULL);
            HSD_JObjSetFlagsAll(sp7C, JOBJ_HIDDEN);
        }
        break;
    case 18:
        if (arg0 == 0) {
            if (gm_801639C0(temp_r31) != 0) {
                show_kos(mnCharSel_804D6CDC, gm_801639F4(temp_r31));
            } else {
                gm_80163A3C(temp_r31, &sp7B, &sp7A, &sp79, &sp78);
                inline1(mnCharSel_804D6CDC, mnCharSel_804D6CE0, sp7B, sp7A,
                        sp79, sp78);
            }
        }
        lb_80011E24(mnCharSel_804D6CC8, &sp7C, 3, -1);
        if (gm_80163B9C(&sp7B, &sp7A, &sp79, &sp78) != 0) {
            inline1(mnCharSel_804D6CE4, mnCharSel_804D6CE8, sp7B, sp7A, sp79,
                    sp78);
            HSD_JObjClearFlagsAll(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, NULL);
            HSD_SisLib_803A70A0(mnCharSel_804D6CE8, 0, NULL);
            HSD_JObjSetFlagsAll(sp7C, JOBJ_HIDDEN);
        }
        break;
    case 19:
        if (arg0 == 0) {
            if (lbLang_IsSavedLanguageJP()) {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d 人抜き",
                                    gm_80163DC4(temp_r31));
            } else {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d ＫＯｓ",
                                    gm_80163DC4(temp_r31));
            }
        }
        if (lbLang_IsSavedLanguageJP()) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%d 人抜き",
                                gm_80163DE8());
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%d ＫＯｓ",
                                gm_80163DE8());
        }
        break;
    case 20:
        if (!arg0) {
            if (lbLang_IsSavedLanguageJP()) {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d 人抜き",
                                    gm_80163E3C(temp_r31));
            } else {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d ＫＯｓ",
                                    gm_80163E3C(temp_r31));
            }
        }
        if (lbLang_IsSavedLanguageJP()) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%d 人抜き",
                                gm_80163E60());
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%d ＫＯｓ",
                                gm_80163E60());
        }
        break;
    case 21:
        if (!arg0) {
            show_kos(mnCharSel_804D6CDC, gm_80163EB4(temp_r31));
        }
        show_kos(mnCharSel_804D6CE4, gm_80163ED8());
        break;
    case 22:
        if (!arg0) {
            show_kos(mnCharSel_804D6CDC, gm_80163F2C(temp_r31));
        }
        show_kos(mnCharSel_804D6CE4, gm_80163F50());
        break;
    }
}

/// #mnCharSel_8025D1C4

static inline void sethidden(HSD_JObj* jobj, bool hidden)
{
    if (hidden) {
        HSD_JObjSetFlags(jobj, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlags(jobj, JOBJ_HIDDEN);
    }
}

void mnCharSel_8025D5AC(int door, int var_r31, bool hidden)
{
    HSD_JObj* sp5C;
    HSD_JObj* sp58;
    HSD_JObj* sp54;
    HSD_JObj* sp50;
    HSD_JObj* sp4C;
    HSD_JObj* sp48;
    HSD_JObj* sp44;
    int i;

    PAD_STACK(0x30);

    if (mnCharSel_804D6CF5 == 1) {
        if (door != 0) {
            lb_80011E24(mnCharSel_804D6CC4, &sp5C, 4, -1);
            HSD_ForeachAnim(sp5C, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                            AOBJ_ARG_AF, (float) var_r31);
            HSD_JObjAnimAll(sp5C);
            HSD_ForeachAnim(sp5C, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
            sethidden(sp5C, hidden);

            lb_80011E24(mnCharSel_804D6CC4, &sp58, 6, -1);
            HSD_ForeachAnim(sp58, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                            AOBJ_ARG_AF, (float) var_r31);
            HSD_JObjAnimAll(sp58);
            HSD_ForeachAnim(sp58, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
            sethidden(sp58, hidden);
            return;
        }
        lb_80011E24(mnCharSel_804D6CC0, &sp54, 0x2B, -1);
        HSD_ForeachAnim(sp54, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, (float) var_r31);
        HSD_JObjAnimAll(sp54);
        HSD_ForeachAnim(sp54, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                        AOBJ_ARG_AOV, 0, 0);
        sethidden(sp54, hidden);

        lb_80011E24(mnCharSel_804D6CC0, &sp50, 0x2D, -1);
        HSD_ForeachAnim(sp50, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, (float) var_r31);
        HSD_JObjAnimAll(sp50);
        HSD_ForeachAnim(sp50, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                        AOBJ_ARG_AOV, 0, 0);
        sethidden(sp50, hidden);
        if (hidden) {
            var_r31 = 0xB9;
        }
        for (i = 0; i < 5; i++) {
            u8 tmp = data2.xf0[i];
            lb_80011E24(mnCharSel_804D6CC0, &sp4C, tmp, -1);
            HSD_ForeachAnim(sp4C, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                            AOBJ_ARG_AF, (float) var_r31);
            HSD_JObjAnimAll(sp4C);
            HSD_ForeachAnim(sp4C, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        }
        mnCharSel_8025C020(hidden);
        return;
    }

    lb_80011E24(mnCharSel_804D6CC0, &sp48,
                mnCharSel_803F0DFC.doors[door].costume_joint, -1);
    HSD_ForeachAnim(sp48, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim, AOBJ_ARG_AF,
                    (float) var_r31);
    HSD_JObjAnimAll(sp48);
    HSD_ForeachAnim(sp48, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim, AOBJ_ARG_AOV,
                    0, 0);
    sethidden(sp48, hidden);

    lb_80011E24(mnCharSel_804D6CC0, &sp44,
                mnCharSel_803F0DFC.doors[door].emblem_joint, -1);
    HSD_ForeachAnim(sp44, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim, AOBJ_ARG_AF,
                    (float) var_r31);
    HSD_JObjAnimAll(sp44);
    HSD_ForeachAnim(sp44, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim, AOBJ_ARG_AOV,
                    0, 0);
    sethidden(sp44, hidden);
}

bool mnCharSel_8025DAA0(int door)
{
    int num_doors;
    int j;

    if (mnCharSel_804D6CB0->match_type == 0x17) {
        num_doors = 2;
    } else {
        num_doors = mnCharSel_804D6CF5;
    }

    for (j = 0; j < num_doors; j++) {
        if (door != j && mnCharSel_803F0DFC.doors[j].p_kind != 3 &&
            mnCharSel_803F0DFC.doors[j].sel_icon < 0x19 &&
            mnCharSel_803F0DFC.doors[j].sel_icon ==
                mnCharSel_803F0DFC.doors[door].sel_icon &&
            mnCharSel_803F0DFC.doors[door].costume ==
                mnCharSel_803F0DFC.doors[j].costume)
        {
            return true;
        }
    }
    return false;
}

/// #mnCharSel_8025DB34

inline HSD_JObj* lb_80011E24_inline(int i)
{
    HSD_JObj* jobj;
    lb_80011E24(mnCharSel_804D6CC0, &jobj, i, -1);
    return jobj;
}

inline void anim_inline(int i, float f)
{
    HSD_JObj* jobj;
    lb_80011E24(mnCharSel_804D6CC0, &jobj, i, -1);
    HSD_ForeachAnim(jobj, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim, AOBJ_ARG_AF,
                    f);
    HSD_JObjAnimAll(jobj);
    HSD_ForeachAnim(jobj, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim, AOBJ_ARG_AOV,
                    0, 0);
}

void mnCharSel_8025EE8C(u8 idx)
{
    float temp_f31;
    int i;

    u8 _[8];

    HSD_JObj* sp14;
    HSD_JObj* sp10;
    HSD_JObj* spC;

    if (mnCharSel_804D6CF5 == 1) {
        temp_f31 = mnCharSel_803F0A48.mode_info[idx].mode_ffa_frame;
        lb_80011E24(mnCharSel_804D6CC0, &sp14, 0x24, -1);
        HSD_ForeachAnim(sp14, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, temp_f31);
        HSD_JObjAnimAll(sp14);
        HSD_ForeachAnim(sp14, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                        AOBJ_ARG_AOV, 0, 0);
        mnCharSel_8025DB34(0);
        if (mnCharSel_804D6CB0->match_type == 0x17) {
            mnCharSel_8025DB34(1);
        }
    } else {
        if (mnCharSel_804D6CB0->data.data.rules.x8 != 0) {
            temp_f31 = mnCharSel_803F0A48.mode_info[idx].mode_teams_frame;
            lb_80011E24(mnCharSel_804D6CC0, &sp10, 0x24, -1);
            HSD_ForeachAnim(sp10, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                            AOBJ_ARG_AF, temp_f31);
            HSD_JObjAnimAll(sp10);
            HSD_ForeachAnim(sp10, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        } else {
            temp_f31 = mnCharSel_803F0A48.mode_info[idx].mode_ffa_frame;
            lb_80011E24(mnCharSel_804D6CC0, &spC, 0x24, -1);
            HSD_ForeachAnim(spC, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                            AOBJ_ARG_AF, temp_f31);
            HSD_JObjAnimAll(spC);
            HSD_ForeachAnim(spC, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        }
        for (i = 0; i < mnCharSel_804D6CF5; i++) {
            mnCharSel_8025DB34(i);
        }
    }
}

/// #fn_8025F0E0

void fn_8025FAC0(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (mnCharSel_804D6CEC % 40 == 0) {
        if (jobj == NULL) {
            child = NULL;
        } else {
            child = jobj->child;
        }
        HSD_JObjReqAnimAll(child, 0.0F);
    }
    HSD_JObjAnimAll(jobj);
}

void fn_8025FB2C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

/// #mnCharSel_8025FB50

/// #mnCharSel_8025FDEC

static inline bool isDuplicateCostume(int door)
{
    int num_doors;
    int j;
    CSSDoor* temp_r30 = &mnCharSel_803F0DFC.doors[door];

    if (mnCharSel_804D6CB0->match_type == 0x17) {
        num_doors = 2;
    } else {
        num_doors = mnCharSel_804D6CF5;
    }

    for (j = 0; j < num_doors; j++) {
        CSSDoor* var_r5 = &mnCharSel_803F0DFC.doors[j];
        if (door != j && var_r5->p_kind != 3 && var_r5->sel_icon < 0x19 &&
            var_r5->sel_icon == temp_r30->sel_icon &&
            temp_r30->costume == var_r5->costume)
        {
            return true;
        }
    }
    return false;
}

void mnCharSel_CostumeChange(int door, u32 input)
{
    u8 prev_costume = mnCharSel_803F0DFC.doors[door].costume;
    PAD_STACK(4);

    if (mnCharSel_803F0DFC.doors[door].sel_icon >= 0x19) {
        return;
    }
    if (mnCharSel_803F0DFC.doors[door].sel_icon_prev >= 0x19) {
        return;
    }

    if (input & HSD_PAD_X) {
        do {
            mnCharSel_803F0DFC.doors[door].costume =
                (mnCharSel_803F0DFC.doors[door].costume + 1) %
                gm_80169238(
                    icons[mnCharSel_803F0DFC.doors[door].sel_icon].char_kind);
        } while (mnCharSel_8025DAA0(door));
    } else if (input & HSD_PAD_Y) {
        do {
            if (mnCharSel_803F0DFC.doors[door].costume != 0) {
                mnCharSel_803F0DFC.doors[door].costume--;
            } else {
                mnCharSel_803F0DFC.doors[door].costume =
                    gm_80169238(icons[mnCharSel_803F0DFC.doors[door].sel_icon]
                                    .char_kind) -
                    1;
            }
        } while (mnCharSel_8025DAA0(door));
    }
    if (prev_costume != mnCharSel_803F0DFC.doors[door].costume) {
        mnCharSel_8025DB34(door);
        lbAudioAx_80024030(2);
    }
}

/// #mnCharSel_CursorThink

/// #fn_80262648

/// #fn_80262F44

void fn_80263354(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (mnCharSel_804D6CEC % 200 == 0) {
        HSD_JObjReqAnimAll(jobj, 0.0F);
    }
    HSD_JObjAnimAll(jobj);
}

/// #fn_802633B0

void mnCharSel_80264070(void)
{
    mnCharSel_804D6CF4 = 1;
}

void fn_8026407C(HSD_GObj* gobj)
{
    HSD_FogSet(GET_FOG(gobj));
}

/// #mnCharSel_802640A0

static u8 data_pad[0x138] = { 0 };

void mnCharSel_8026688C_OnEnter(void* arg0)
{
    PAD_STACK(8);

    lb_8001C550();
    lb_8001D164(0);
    mnCharSel_804D6CB0 = arg0;

    mnCharSel_804D6CF0 = mnCharSel_804D6CB0->unk_0x0 - 1;

    for (mnCharSel_804D6CF8 = 0; mnCharSel_804D6CF8 < 0x78;
         mnCharSel_804D6CF8++)
    {
        if (GetNameText(mnCharSel_804D6CF8) == NULL) {
            break;
        }
    }
    mnCharSel_804D6CF9 = -1;
    mnCharSel_804D6CF8++;

    mnCharSel_803F0DFC.doors[0].selected_since_load = 0;
    mnCharSel_803F0DFC.doors[1].selected_since_load = 0;
    mnCharSel_803F0DFC.doors[2].selected_since_load = 0;
    mnCharSel_803F0DFC.doors[3].selected_since_load = 0;

    lbAudioAx_80026F2C(0x12);

    lbAudioAx_8002702C(2, 8);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    if (lbLang_IsSavedLanguageJP() != 0) {
        mnCharSel_804D6CD0 = lbArchive_LoadArchive("MnSlChr.dat");
        mnCharSel_804D6CD4 = lbArchive_LoadArchive("MnExtAll.dat");
    } else {
        mnCharSel_804D6CD0 = lbArchive_LoadArchive("MnSlChr.usd");
        mnCharSel_804D6CD4 = lbArchive_LoadArchive("MnExtAll.usd");
    }
    mnCharSel_804D6CB4 = HSD_ArchiveGetPublicAddress(mnCharSel_804D6CD0,
                                                     "MnSelectChrDataTable");
    mnCharSel_804D6CD8 = (u8*) mnCharSel_804D6CB4 + 0x10;
    if (lbLang_IsSavedLanguageJP() != 0) {
        HSD_SisLib_803A62A0(0, "SdSlChr.dat", "SIS_SelCharData");
    } else {
        HSD_SisLib_803A62A0(0, "SdSlChr.usd", "SIS_SelCharData");
    }
    mnCharSel_804D6CF4 = 0;
    mnCharSel_802640A0();
}

/// #mnCharSel_802669F4_OnFrame

static u8 bss_pad[0x10];
static struct asdf {
    u8 pad[0x5];
    u8 x5;
}* mnCharSel_804A0BD0[4];

void mnCharSel_80266D70_OnLeave(void* unused)
{
    int var_r28;
    u64 tmp;
    CSSData* data;
    int i;
    u8 type;

    HSD_SisLib_803A5FBC();
    if (mnCharSel_804D6CD0 != NULL) {
        lbArchive_80016EFC(mnCharSel_804D6CD0);
        mnCharSel_804D6CD0 = NULL;
    }
    if (mnCharSel_804D6CD4 != NULL) {
        lbArchive_80016EFC(mnCharSel_804D6CD4);
        mnCharSel_804D6CD4 = NULL;
    }
    mnCharSel_804D6CB0->pending_scene_change = mnCharSel_804D6CF6;
    if (mnCharSel_804D6CF6 != 0) {
        return;
    }

    tmp = 0;
    if (mnCharSel_804D6CF5 == 1) {
        data = mnCharSel_804D6CB0;
        type = data->data.data.players[mnCharSel_804D6CF0].slot_type;
        if ((type == 0 || type == 1) && mnCharSel_804A0BD0[0]->x5 == 0) {
            tmp |= lbAudioAx_80026E84(
                data->data.data.players[mnCharSel_804D6CF0].c_kind);
        }
        data = mnCharSel_804D6CB0;
        type = data->data.data.players[mnCharSel_804D6CF1].slot_type;
        if ((type == 0 || type == 1) && mnCharSel_804A0BD0[1]->x5 == 0) {
            tmp |= lbAudioAx_80026E84(
                data->data.data.players[mnCharSel_804D6CF1].c_kind);
        }
    } else {
        if (mnCharSel_804D6CB0->match_type == 1) {
            var_r28 = 3;
        } else {
            var_r28 = 4;
        }
        for (i = 0; i < var_r28; i++) {
            data = mnCharSel_804D6CB0;
            type = data->data.data.players[i].slot_type;
            if ((type == 0 || type == 1) && mnCharSel_804A0BD0[i]->x5 == 0) {
                tmp |= lbAudioAx_80026E84(data->data.data.players[i].c_kind);
            }
        }
    }

    lbAudioAx_80026F2C(0x14);
    lbAudioAx_8002702C(4, tmp);
    lbAudioAx_80027168();
}

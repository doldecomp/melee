#include "mncharsel.h"

#include "mncharsel.static.h"

#include "types.h"

#include <MSL/trigf.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gm_1601.h>
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
#include <melee/mn/mnmain.h>
#include <melee/mn/mnmainrule.h>
#include <melee/mn/mnname.h>
#include <melee/mn/mnnamenew.h>

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

    if (match_type == VS_CAMERA) {
        HSD_SisLib_803A6530(0, 0x4A, 0x4F);
        return;
    }
    if (match_type == VS_STAMINA) {
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

static inline void drawTimeText(HSD_Text* x, HSD_Text* y, int hours,
                                int minutes, int seconds, int microseconds)
{
    if (hours == 0) {
        HSD_SisLib_803A70A0(x, 0, "%02d:%02d", minutes, seconds);
        HSD_SisLib_803A70A0(y, 0, "%02d", microseconds);
    } else if (hours < 100) {
        HSD_SisLib_803A70A0(x, 0, "%d:%02d:%02d", hours, minutes, seconds);
        HSD_SisLib_803A70A0(y, 0, "%02d", microseconds);
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
    case REG_CLASSIC:
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
    case REG_ADVENTURE:
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
    case REG_ALLSTAR:
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
    case STADIUM_TARGET:
        if (arg0 == 0) {
            int temp_r29 = gm_8016332C(temp_r31);
            if (temp_r29 != -1U) {
                if (lbLang_IsSavedLanguageJP() != 0) {
                    HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d 個",
                                        temp_r29);
                } else {
                    HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d", temp_r29);
                }
            } else {
                gm_80163374(temp_r31, &sp7B, &sp7A, &sp79, &sp78);
                drawTimeText(mnCharSel_804D6CDC, mnCharSel_804D6CE0, sp7B,
                             sp7A, sp79, sp78);
            }
        }
        lb_80011E24(mnCharSel_804D6CC8, &sp7C, 3, -1);
        if (gm_801634D4(&sp7B, &sp7A, &sp79, &sp78) != 0) {
            drawTimeText(mnCharSel_804D6CE4, mnCharSel_804D6CE8, sp7B, sp7A,
                         sp79, sp78);
            HSD_JObjClearFlagsAll(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, NULL);
            HSD_SisLib_803A70A0(mnCharSel_804D6CE8, 0, NULL);
            HSD_JObjSetFlagsAll(sp7C, JOBJ_HIDDEN);
        }
        break;
    case STADIUM_HOMERUN:
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
    case STADIUM_MULTIMAN_10:
        if (arg0 == 0) {
            if (gm_8016365C(temp_r31) != 0) {
                show_kos(mnCharSel_804D6CDC, gm_80163690(temp_r31));
            } else {
                gm_801636D8(temp_r31, &sp7B, &sp7A, &sp79, &sp78);
                drawTimeText(mnCharSel_804D6CDC, mnCharSel_804D6CE0, sp7B,
                             sp7A, sp79, sp78);
            }
        }
        lb_80011E24(mnCharSel_804D6CC8, &sp7C, 3, -1);
        if (gm_80163838(&sp7B, &sp7A, &sp79, &sp78) != 0) {
            drawTimeText(mnCharSel_804D6CE4, mnCharSel_804D6CE8, sp7B, sp7A,
                         sp79, sp78);
            HSD_JObjClearFlagsAll(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, NULL);
            HSD_SisLib_803A70A0(mnCharSel_804D6CE8, 0, NULL);
            HSD_JObjSetFlagsAll(sp7C, JOBJ_HIDDEN);
        }
        break;
    case STADIUM_MULTIMAN_100:
        if (arg0 == 0) {
            if (gm_801639C0(temp_r31) != 0) {
                show_kos(mnCharSel_804D6CDC, gm_801639F4(temp_r31));
            } else {
                gm_80163A3C(temp_r31, &sp7B, &sp7A, &sp79, &sp78);
                drawTimeText(mnCharSel_804D6CDC, mnCharSel_804D6CE0, sp7B,
                             sp7A, sp79, sp78);
            }
        }
        lb_80011E24(mnCharSel_804D6CC8, &sp7C, 3, -1);
        if (gm_80163B9C(&sp7B, &sp7A, &sp79, &sp78) != 0) {
            drawTimeText(mnCharSel_804D6CE4, mnCharSel_804D6CE8, sp7B, sp7A,
                         sp79, sp78);
            HSD_JObjClearFlagsAll(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, NULL);
            HSD_SisLib_803A70A0(mnCharSel_804D6CE8, 0, NULL);
            HSD_JObjSetFlagsAll(sp7C, JOBJ_HIDDEN);
        }
        break;
    case STADIUM_3_MIN_MELEE:
        if (arg0 == 0) {
            if (lbLang_IsSavedLanguageJP()) {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d 人抜き",
                                    gm_Get3MinMultimanHighscore(temp_r31));
            } else {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d ＫＯｓ",
                                    gm_Get3MinMultimanHighscore(temp_r31));
            }
        }
        if (lbLang_IsSavedLanguageJP()) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%d 人抜き",
                                gm_Get3MinMultimanTotalHighscore());
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%d ＫＯｓ",
                                gm_Get3MinMultimanTotalHighscore());
        }
        break;
    case STADIUM_15_MIN_MELEE:
        if (!arg0) {
            if (lbLang_IsSavedLanguageJP()) {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d 人抜き",
                                    gm_Get15MinMultimanHighscore(temp_r31));
            } else {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d ＫＯｓ",
                                    gm_Get15MinMultimanHighscore(temp_r31));
            }
        }
        if (lbLang_IsSavedLanguageJP()) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%d 人抜き",
                                gm_Get15MinMultimanTotalHighscore());
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%d ＫＯｓ",
                                gm_Get15MinMultimanTotalHighscore());
        }
        break;
    case STADIUM_ENDLESS_MELEE:
        if (!arg0) {
            show_kos(mnCharSel_804D6CDC, gm_GetEndlessHighscore(temp_r31));
        }
        show_kos(mnCharSel_804D6CE4, gm_GetEndlessTotalHighscore());
        break;
    case STADIUM_CRUEL_MELEE:
        if (!arg0) {
            show_kos(mnCharSel_804D6CDC, gm_GetCruelHighscore(temp_r31));
        }
        show_kos(mnCharSel_804D6CE4, gm_GetCruelTotalHighscore());
        break;
    }
}

void mnCharSel_8025D1C4(int arg0, int arg1)
{
    u8* temp_r31;
    HSD_JObj* var_r0_2;
    HSD_JObj* var_r0_3;
    HSD_JObj* var_r0_4;
    HSD_JObj* var_r0_5;
    HSD_Text* temp_r30;
    f32 var_f31;
    s32 var_r0;
    int temp_r29;
    CSSData* css = mnCharSel_804D6CB0;
    CSSKOStar* stars;
    u8 joint;

    HSD_JObj* sp10;

    switch (css->match_type) {
    case VS_MELEE:
    case VS_SUDDEN_DEATH:
    case VS_GIANT:
    case VS_TINY:
    case VS_INVISIBLE:
    case VS_FIXED_CAMERA:
    case VS_SINGLE_BUTTON:
    case VS_LIGHTNING:
    case VS_SLOWMO:
        var_r0 = true;
        break;
    default:
        var_r0 = false;
        break;
    }

    if (var_r0) {
        stars = &data2.ko_stars[arg0];
        temp_r31 = &data2.ko_stars[arg0].joint2;
        temp_r30 = data2.ko_stars[arg0].text;
        temp_r29 = css->ko_star_counts[arg0];
        var_f31 = data2.ko_stars[arg0].x4;

        joint = stars->joint;
        lb_80011E24(mnCharSel_804D6CC0, &sp10, joint, -1);

        if (arg1 == 0 || temp_r29 == 0) {
            temp_r30->hidden = 1;
            HSD_JObjSetFlagsAll(sp10, JOBJ_HIDDEN);
            return;
        }
        HSD_JObjClearFlagsAll(sp10, JOBJ_HIDDEN);
        if (temp_r29 < 6) {
            temp_r30->hidden = 1;
            HSD_JObjSetTranslateX(sp10, 0.9f * temp_r29 + var_f31 - 4.5f);
            if (sp10 == NULL) {
                var_r0_2 = NULL;
            } else {
                var_r0_2 = sp10->child;
            }
            sp10 = var_r0_2;
            if (temp_r29 < 5) {
                HSD_JObjSetFlags(sp10, JOBJ_HIDDEN);
            }
            if (sp10 == NULL) {
                var_r0_3 = NULL;
            } else {
                var_r0_3 = sp10->next;
            }
            sp10 = var_r0_3;
            if (temp_r29 < 4) {
                HSD_JObjSetFlags(sp10, JOBJ_HIDDEN);
            }
            if (sp10 == NULL) {
                var_r0_4 = NULL;
            } else {
                var_r0_4 = sp10->next;
            }
            sp10 = var_r0_4;
            if (temp_r29 < 3) {
                HSD_JObjSetFlags(sp10, JOBJ_HIDDEN);
            }
            if (sp10 == NULL) {
                var_r0_5 = NULL;
            } else {
                var_r0_5 = sp10->next;
            }
            sp10 = var_r0_5;
            if (temp_r29 < 2) {
                HSD_JObjSetFlags(sp10, JOBJ_HIDDEN);
            }
        } else {
            temp_r30->hidden = 0;
            if (temp_r29 >= 0x3E8) {
                var_f31 -= 3.0F;
            } else if (temp_r29 >= 100) {
                var_f31 -= 1.5F;
            }

            HSD_JObjSetTranslateX(sp10, var_f31);

            temp_r30->pos_x = 0.6F + var_f31;
            if (arg1 == 1) {
                temp_r30->text_color.a = 0x50;
            } else {
                temp_r30->text_color.a = 0xA0;
            }
            {
                UNK_T tmp = HSD_SisLib_803A6478(
                    temp_r31, &HSD_SisLib_804D1124[0][43].kerning->left);
                mnCharSel_8025BC20(tmp, temp_r29);
            }
            HSD_SisLib_803A6368(temp_r30, 0x56);
            temp_r30->sis_buffer = (SIS*) temp_r31;
            HSD_JObjSetFlags(sp10 = HSD_JObjGetChild(sp10), JOBJ_HIDDEN);
            HSD_JObjSetFlags(sp10 = HSD_JObjGetNext(sp10), JOBJ_HIDDEN);
            HSD_JObjSetFlags(sp10 = HSD_JObjGetNext(HSD_JObjGetNext(sp10)),
                             JOBJ_HIDDEN);
            HSD_JObjSetFlags(sp10 = HSD_JObjGetNext(sp10), JOBJ_HIDDEN);
        }
    }
}

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

#pragma dont_inline on
bool mnCharSel_8025DAA0(int door)
{
    int num_doors;
    int j;

    if (mnCharSel_804D6CB0->match_type == TRAINING_MODE) {
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
#pragma dont_inline off

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
    HSD_JObj* cc0;

    u8 _[8];

    HSD_JObj* sp14;
    HSD_JObj* sp10;
    HSD_JObj* spC;

    if (mnCharSel_804D6CF5 == 1) {
        temp_f31 = mnCharSel_803F0A48.mode_info[idx].mode_ffa_frame;
        cc0 = mnCharSel_804D6CC0;
        lb_80011E24(cc0, &sp14, 0x24, -1);
        HSD_ForeachAnim(sp14, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, temp_f31);
        HSD_JObjAnimAll(sp14);
        HSD_ForeachAnim(sp14, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                        AOBJ_ARG_AOV, 0, 0);
        mnCharSel_8025DB34(0);
        if (mnCharSel_804D6CB0->match_type == TRAINING_MODE) {
            mnCharSel_8025DB34(1);
        }
    } else {
        if (mnCharSel_804D6CB0->data.data.rules.is_teams) {
            temp_f31 = mnCharSel_803F0A48.mode_info[idx].mode_teams_frame;
            cc0 = mnCharSel_804D6CC0;
            lb_80011E24(cc0, &sp10, 0x24, -1);
            HSD_ForeachAnim(sp10, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                            AOBJ_ARG_AF, temp_f31);
            HSD_JObjAnimAll(sp10);
            HSD_ForeachAnim(sp10, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        } else {
            temp_f31 = mnCharSel_803F0A48.mode_info[idx].mode_ffa_frame;
            cc0 = mnCharSel_804D6CC0;
            lb_80011E24(cc0, &spC, 0x24, -1);
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

static HSD_GObj** mnCharSel_804A0BC0[4];
static struct CSSCharModel {
    /* 0x00 */ HSD_GObj* gobj;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
    /* 0x07 */ u8 x7;
    /* 0x08 */ float x8;
    /* 0x0C */ float xC;
    /* 0x10 */ float x10;
    /* 0x14 */ float x14;
}* mnCharSel_804A0BD0[4];

/// #fn_8025F0E0
void fn_8025F0E0(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    void (*sp5C)(HSD_AObj*, f32);
    void (*sp60)(HSD_AObj*, void*, HSD_ObjUpdateFunc);
    HSD_JObj* sp54;
    HSD_JObj* sp4C;
    HSD_JObj* sp48;
    HSD_JObj* sp44;
    HSD_JObj* sp40;
    HSD_JObj* sp3C;
    HSD_JObj* sp38;
    HSD_JObj* sp34;
    HSD_JObj* sp30;
    HSD_JObj* sp2C;
    CSSIcon* icons;
    CSSDoor* doors;
    GameRules* rules;
    HSD_DObj* dobj;
    HSD_MObj* mobj;
    void* sp58;
    int i;
    int door_offset;
    u8 timer;
    u8 val;
    int anim;
    float fval;

    sp58 = &mnCharSel_804A0BC0;

    if ((mnCharSel_804D6CEC % 10) != 0) {
        if ((u8) mnCharSel_804D6CF5 == 1) {
            lb_80011E24(jobj, &sp54, 0x27, -1);
        } else {
            lb_80011E24(jobj, &sp54, 0x27, -1);
        }
        HSD_ForeachAnim(sp54, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjReqAnim,
                         AOBJ_ARG_AF, 0.0f);
    }

    icons = (CSSIcon*) ((u8*) &mnCharSel_803F0A48 + 0xDC);
    i = 0;
    do {
        timer = icons[i].anim_timer;
        if (timer != 0) {
            timer = timer - 1;
            icons[i].anim_timer = timer;
            if (timer == 0) {
                if ((u8) mnCharSel_804D6CF5 == 1) {
                    lb_80011E24(jobj, &sp4C, icons[i].joint_id_1p, -1);
                    HSD_ForeachAnim(sp4C, JOBJ_TYPE, TOBJ_MASK,
                                     HSD_AObjReqAnim, AOBJ_ARG_AF, 0.0f);
                    HSD_JObjAnimAll(sp4C);
                    HSD_ForeachAnim(sp4C, JOBJ_TYPE, TOBJ_MASK,
                                     HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                } else {
                    lb_80011E24(jobj, &sp48, icons[i].joint_id_vs, -1);
                    HSD_ForeachAnim(sp48, JOBJ_TYPE, TOBJ_MASK,
                                     HSD_AObjReqAnim, AOBJ_ARG_AF, 0.0f);
                    HSD_JObjAnimAll(sp48);
                    HSD_ForeachAnim(sp48, JOBJ_TYPE, TOBJ_MASK,
                                     HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                }
            }
        }
        i += 1;
    } while (i < 25);

    if ((u8) mnCharSel_804D6CF5 == 4) {
        doors = (CSSDoor*) ((u8*) &mnCharSel_803F0A48 + 0x3B4);
        sp5C = HSD_AObjReqAnim;
        sp60 = HSD_AObjStopAnim;
        i = 0;
        door_offset = i * 0x24;
        while (i < (s32) mnCharSel_804D6CF5) {
            timer = doors->dooranim_timer;
            if (timer != 0) {
                timer = timer - 1;
                doors->dooranim_timer = timer;
                if (timer == 0) {
                    lb_80011E24(jobj, &sp54, doors->door_joint, -1);
                    HSD_ForeachAnim(sp54, JOBJ_TYPE, ALL_TYPE_MASK,
                                     HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                }
            }

            timer = doors->slideranim_timer;
            if (timer != 0) {
                timer = timer - 1;
                doors->slideranim_timer = timer;
                if (timer == 0) {
                    rules = gmMainLib_8015CC34();
                    if ((u8) rules->handicap != 0) {
                        if ((u8) doors->p_kind == 1) {
                            rules = gmMainLib_8015CC34();
                            if ((u8) rules->handicap == 1) {
                                anim = 0x5A;
                            } else {
                                anim = 0x1E;
                            }
                            fval = (f32) anim;
                            lb_80011E24(mnCharSel_804D6CC0, &sp44,
                                         doors->slidername_joint, -1);
                            HSD_ForeachAnim(sp44, JOBJ_TYPE, ALL_TYPE_MASK,
                                             HSD_AObjReqAnim, AOBJ_ARG_AF,
                                             fval);
                            HSD_JObjAnimAll(sp44);
                            HSD_ForeachAnim(sp44, JOBJ_TYPE, ALL_TYPE_MASK,
                                             HSD_AObjStopAnim, AOBJ_ARG_AOV,
                                             0, 0);
                        } else {
                            rules = gmMainLib_8015CC34();
                            if ((u8) rules->handicap == 1) {
                                anim = 0x50;
                            } else {
                                anim = 0x14;
                            }
                            fval = (f32) anim;
                            lb_80011E24(mnCharSel_804D6CC0, &sp40,
                                         doors->slidername_joint, -1);
                            HSD_ForeachAnim(sp40, JOBJ_TYPE, ALL_TYPE_MASK,
                                             HSD_AObjReqAnim, AOBJ_ARG_AF,
                                             fval);
                            HSD_JObjAnimAll(sp40);
                            HSD_ForeachAnim(sp40, JOBJ_TYPE, ALL_TYPE_MASK,
                                             HSD_AObjStopAnim, AOBJ_ARG_AOV,
                                             0, 0);
                        }

                        rules = gmMainLib_8015CC34();
                        if ((u8) rules->handicap == 1) {
                            val = gm_801685D4((u8) i,
                                *((u8*) mnCharSel_804D6CB0 + door_offset + 0x7A));
                        } else {
                            val = *((u8*) mnCharSel_804D6CB0 + door_offset + 0x78);
                        }
                        {
                            f32 val_f;
                            if ((s32) val != 0) {
                            } else {
                                val = 1;
                            }
                            val_f = (f32) val;
                            lb_80011E24(mnCharSel_804D6CC0, &sp3C,
                                         doors->cpuslider_joint, -1);
                            HSD_ForeachAnim(sp3C, JOBJ_TYPE, TOBJ_MASK,
                                             HSD_AObjReqAnim, AOBJ_ARG_AF,
                                             val_f);
                        }
                        HSD_JObjAnimAll(sp3C);
                        HSD_ForeachAnim(sp3C, JOBJ_TYPE, TOBJ_MASK,
                                         HSD_AObjStopAnim, AOBJ_ARG_AOV,
                                         0, 0);

                        fval = (f32) *((u8*) mnCharSel_804D6CB0 + door_offset + 0x7F);
                        lb_80011E24(mnCharSel_804D6CC0, &sp38,
                                     doors->cpuslider2_joint, -1);
                        HSD_ForeachAnim(sp38, JOBJ_TYPE, TOBJ_MASK,
                                         HSD_AObjReqAnim, AOBJ_ARG_AF, fval);
                        HSD_JObjAnimAll(sp38);
                        HSD_ForeachAnim(sp38, JOBJ_TYPE, TOBJ_MASK,
                                         HSD_AObjStopAnim, AOBJ_ARG_AOV,
                                         0, 0);
                    } else {
                        if ((u8) doors->p_kind == 1) {
                            lb_80011E24(mnCharSel_804D6CC0, &sp34,
                                         doors->slidername_joint, -1);
                            HSD_ForeachAnim(sp34, JOBJ_TYPE, ALL_TYPE_MASK,
                                             sp5C, AOBJ_ARG_AF,
                                             50.0f);
                            HSD_JObjAnimAll(sp34);
                            HSD_ForeachAnim(sp34, JOBJ_TYPE, ALL_TYPE_MASK,
                                             sp60, AOBJ_ARG_AOV,
                                             0, 0);
                        } else {
                            lb_80011E24(mnCharSel_804D6CC0, &sp30,
                                         doors->slidername_joint, -1);
                            HSD_ForeachAnim(sp30, JOBJ_TYPE, ALL_TYPE_MASK,
                                             sp5C, AOBJ_ARG_AF,
                                             40.0f);
                            HSD_JObjAnimAll(sp30);
                            HSD_ForeachAnim(sp30, JOBJ_TYPE, ALL_TYPE_MASK,
                                             sp60, AOBJ_ARG_AOV,
                                             0, 0);
                        }
                        fval = (f32) *((u8*) mnCharSel_804D6CB0 + door_offset + 0x7F);
                        lb_80011E24(mnCharSel_804D6CC0, &sp2C,
                                     doors->cpuslider_joint, -1);
                        HSD_ForeachAnim(sp2C, JOBJ_TYPE, TOBJ_MASK,
                                         sp5C, AOBJ_ARG_AF, fval);
                        HSD_JObjAnimAll(sp2C);
                        HSD_ForeachAnim(sp2C, JOBJ_TYPE, TOBJ_MASK,
                                         sp60, AOBJ_ARG_AOV,
                                         0, 0);
                    }
                }
            }

            doors = (CSSDoor*)((u8*)doors + 0x24);
            door_offset += 0x24;
            i += 1;
        }
    } else {
        u8* base = (u8*) &mnCharSel_803F0A48;
        u8* scroll_flag = base + 0x483;
        u8* page_target = base + 0x481;
        u8* page_current = base + 0x482;

        if (*scroll_flag != 0) {
            if (*page_target != *page_current) {
                if (*page_target < *page_current) {
                    *(f32*)(base + 0x484) = *(f32*)(base + 0x484) + 31.0f;
                    if (*(f32*)(base + 0x484) >= -(248.0f * (f32) *page_target - 124.0f)) {
                        *page_current = *page_target;
                    }
                } else {
                    *(f32*)(base + 0x484) = *(f32*)(base + 0x484) - 31.0f;
                    if (*(f32*)(base + 0x484) <= -(248.0f * (f32) *page_target - 124.0f)) {
                        *page_current = *page_target;
                    }
                }
            }
            if (*page_target == *page_current) {
                *scroll_flag = 0;
                *(f32*)(base + 0x484) = -(248.0f * (f32) *page_target - 124.0f);
            }
            {
                int j;
                for (j = 0; j < 5; j++) {
                    HSD_SisLib_803A746C(*(HSD_Text**)(base + 0x488), j,
                                         248.0f * (f32) j + *(f32*)(base + 0x484),
                                         0.0f);
                }
            }
        }
    }

    if ((u8) mnCharSel_804D6CF5 == 1) {
        lb_80011E24(mnCharSel_804D6CC0, &sp54, 0x2D, -1);
        if ((u8) mnCharSel_804A0BD0[0]->x5 != 0) {
            dobj = HSD_JObjGetDObj(sp54);
            if (dobj != NULL) {
                mobj = dobj->mobj;
            } else {
                mobj = NULL;
            }
            HSD_MObjSetAlpha(mobj, 0.5f);
        } else {
            dobj = HSD_JObjGetDObj(sp54);
            if (dobj != NULL) {
                mobj = dobj->mobj;
            } else {
                mobj = NULL;
            }
            HSD_MObjSetAlpha(mobj, 1.0f);
        }
        if ((u8) mnCharSel_804D6CB0->match_type == 0x17) {
            lb_80011E24(mnCharSel_804D6CC4, &sp54, 6, -1);
            if ((u8) mnCharSel_804A0BD0[1]->x5 != 0) {
                dobj = HSD_JObjGetDObj(sp54);
                if (dobj != NULL) {
                    mobj = dobj->mobj;
                } else {
                    mobj = NULL;
                }
                HSD_MObjSetAlpha(mobj, 0.5f);
            } else {
                dobj = HSD_JObjGetDObj(sp54);
                if (dobj != NULL) {
                    mobj = dobj->mobj;
                } else {
                    mobj = NULL;
                }
                HSD_MObjSetAlpha(mobj, 1.0f);
            }
        }
    } else {
        CSSDoor* door_ptr;
        struct CSSCharModel** model_ptr;
        door_ptr = (CSSDoor*) ((u8*) &mnCharSel_803F0A48 + 0x3B4);
        i = 0;
        model_ptr = (struct CSSCharModel**)((u8*)sp58 + 0x10);
        while (i < (s32) mnCharSel_804D6CF5) {
            lb_80011E24(mnCharSel_804D6CC0, &sp54,
                         door_ptr->costume_joint, -1);
            if ((u8) (*model_ptr)->x5 != 0) {
                dobj = HSD_JObjGetDObj(sp54);
                if (dobj != NULL) {
                    mobj = dobj->mobj;
                } else {
                    mobj = NULL;
                }
                HSD_MObjSetAlpha(mobj, 0.5f);
            } else {
                dobj = HSD_JObjGetDObj(sp54);
                if (dobj != NULL) {
                    mobj = dobj->mobj;
                } else {
                    mobj = NULL;
                }
                HSD_MObjSetAlpha(mobj, 1.0f);
            }
            door_ptr = (CSSDoor*)((u8*)door_ptr + 0x24);
            model_ptr += 1;
            i += 1;
        }
    }
    HSD_JObjAnimAll(jobj);
    PAD_STACK(40);
}

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


static inline bool isDuplicateCostume(int door)
{
    int num_doors;
    int j;
    CSSDoor* temp_r30 = &mnCharSel_803F0DFC.doors[door];

    if (mnCharSel_804D6CB0->match_type == TRAINING_MODE) {
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

/// #mnCharSel_8025FB50

void mnCharSel_8025FB50(u8 door, s32 arg1)
{
    HSD_JObj* sp18;
    s32 icon_idx;
    s8 player;

    do {
        icon_idx = HSD_Randi(0x19);
    } while (icons[icon_idx].state == 0);

    if (mnCharSel_804D6CF5 == 1) {
        if (door != 0) {
            player = mnCharSel_804D6CF1;
        } else {
            player = mnCharSel_804D6CF0;
        }
    } else {
        player = (s8) door;
    }

    mnCharSel_804D6CB0->data.data.players[player].c_kind =
        icons[icon_idx].char_kind;

    mnCharSel_803F0DFC.doors[door].sel_icon = (u8) icon_idx;
    if (mnCharSel_803F0DFC.doors[door].sel_icon !=
        mnCharSel_803F0DFC.doors[door].sel_icon_prev)
    {
        u8 costume = 0;
        mnCharSel_803F0DFC.doors[door].costume = costume;
        while (isDuplicateCostume(door)) {
            costume++;
            mnCharSel_803F0DFC.doors[door].costume = costume;
        }
    }

    mnCharSel_804A0BD0[door]->x5 = 0;
    mnCharSel_804A0BD0[door]->x8 = 3.4f + icons[icon_idx].bound_l;
    mnCharSel_804A0BD0[door]->xC = -3.0f + icons[icon_idx].bound_u;
    if (arg1 != 0) {
        mnCharSel_804A0BD0[door]->x10 = mnCharSel_804A0BD0[door]->x8;
        mnCharSel_804A0BD0[door]->x14 = mnCharSel_804A0BD0[door]->xC;
    }
    HSD_GObjGXLink_803909D8(mnCharSel_804A0BD0[door]->gobj,
                            *mnCharSel_804A0BC0[mnCharSel_804D6CF5 - 1]);

    if (mnCharSel_804D6CF5 == 1) {
        lb_80011E24(mnCharSel_804D6CC0, &sp18,
                    icons[icon_idx].joint_id_1p, -1);
    } else {
        lb_80011E24(mnCharSel_804D6CC0, &sp18,
                    icons[icon_idx].joint_id_vs, -1);
    }
    HSD_ForeachAnim(sp18, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                    AOBJ_ARG_AF, 10.0);

    icons[icon_idx].anim_timer = 0xC;

    {
        u8 sel = mnCharSel_803F0DFC.doors[door].sel_icon;
        lbAudioAx_80023870(icons[sel].sfx, 0x7F, 0x40, sel + 0x8A);
        gm_80168C5C((u32) icons[sel].char_kind);
    }
}

#pragma auto_inline off
s32 mnCharSel_8025FDEC(u8 door)
{
    HSD_JObj* sp10;
    s8 player;
    u8 c_kind;
    u8 icon_idx;

    if (mnCharSel_804D6CF5 == 1) {
        if (door != 0) {
            player = mnCharSel_804D6CF1;
        } else {
            player = mnCharSel_804D6CF0;
        }
    } else {
        player = (s8) door;
    }

    c_kind = mnCharSel_804D6CB0->data.data.players[player].c_kind;

    if ((s8) c_kind >= 0x1A) {
        return 1;
    }

    if ((s8) c_kind !=
        (s8) icons[mnCharSel_803F0DFC.doors[door].sel_icon].char_kind)
    {
        mnCharSel_803F0DFC.doors[door].costume = 0;
    }

    for (icon_idx = 0; icon_idx < 0x19; icon_idx++) {
        if ((s8) c_kind == (s8) icons[icon_idx].char_kind) {
            break;
        }
    }

    mnCharSel_804A0BD0[door]->x8 = 3.4f + icons[icon_idx].bound_l;
    mnCharSel_804A0BD0[door]->xC = -3.0f + icons[icon_idx].bound_u;

    mnCharSel_803F0DFC.doors[door].sel_icon_prev = icon_idx;
    mnCharSel_803F0DFC.doors[door].sel_icon = icon_idx;

    HSD_GObjGXLink_803909D8(mnCharSel_804A0BD0[door]->gobj,
                            *mnCharSel_804A0BC0[door]);

    mnCharSel_804A0BD0[door]->x5 = 0;

    if (mnCharSel_804D6CF5 == 1) {
        lb_80011E24(mnCharSel_804D6CC0, &sp10,
                    icons[icon_idx].joint_id_1p, -1);
    } else {
        lb_80011E24(mnCharSel_804D6CC0, &sp10,
                    icons[icon_idx].joint_id_vs, -1);
    }
    HSD_ForeachAnim(sp10, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                    AOBJ_ARG_AF, 10.0);

    icons[icon_idx].anim_timer = 0xC;

    if (mnCharSel_8025DAA0(door)) {
        s8 costume = 0;
        do {
            mnCharSel_803F0DFC.doors[door].costume = costume;
            if (!mnCharSel_8025DAA0(door)) {
                break;
            }
            costume++;
        } while (1);
    }

    if (mnCharSel_804D6CF6 != 3 && mnCharSel_804D6CF6 != 4) {
        u8 sel = mnCharSel_803F0DFC.doors[door].sel_icon;
        lbAudioAx_80023870(icons[sel].sfx, 0x7F, 0x40, sel + 0x8A);
        gm_80168C5C((u32) icons[sel].char_kind);
    }

    return 0;
}
#pragma auto_inline on

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
        } while (isDuplicateCostume(door));
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
        } while (isDuplicateCostume(door));
    }
    if (prev_costume != mnCharSel_803F0DFC.doors[door].costume) {
        mnCharSel_8025DB34(door);
        lbAudioAx_80024030(2);
    }
}

/// #mnCharSel_CursorThink

/// #fn_80262648
void fn_80262648(HSD_GObj* gobj)
{
    HSD_JObj* sp24;
    HSD_JObj* sp18;
    HSD_JObj* sp14;
    HSD_JObj* sp10;
    struct CSSCharModel* model = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    u8 prev_port = model->x6;
    u8 n_doors;

    if ((u8) mnCharSel_804D6CB0->match_type == 0x17) {
        n_doors = 2;
    } else {
        n_doors = mnCharSel_804D6CF5;
    }

    {
        u8 door = model->x4;
        CSSDoor* d = &mnCharSel_803F0DFC.doors[door];
        u8 p_kind = d->p_kind;

        if (p_kind == 3 || (u8) d->sel_icon >= 0x19U) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            return;
        }

        if ((u8) mnCharSel_804D6CF5 == 1) {
            if (door != 0) {
                model->x6 = 8;
            } else {
                model->x6 = (u8) mnCharSel_804D6CF0;
            }
        } else if ((u8) mnCharSel_804D6CB0->data.data.rules.is_teams == 0) {
            if (p_kind == 1) {
                model->x6 = 8;
            } else {
                model->x6 = door;
            }
        } else if (p_kind == 1) {
            model->x6 = (u8) (mnCharSel_804D50E0[d->team] + 4);
        } else {
            model->x6 = (u8) mnCharSel_804D50E0[d->team];
        }
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    model->x7 = (u8) (model->x7 + 1);

    {
        u8 port = model->x6;
        if (prev_port != port || (u8) model->x7 > 0x27U) {
            if (port < 4U) {
                if ((u8) mnCharSel_804D6CF5 == 1) {
                    f32 f24 = (f32) ((s8) (u8) mnCharSel_804D6CF0 * 4);
                    lb_80011E24(jobj, &sp18, 4, -1);
                    HSD_ForeachAnim(sp18, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjReqAnim, AOBJ_ARG_AF, f24);
                    HSD_JObjAnimAll(sp18);
                    HSD_ForeachAnim(sp18, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                } else {
                    f32 f24 = (f32) (model->x4 * 4);
                    lb_80011E24(jobj, &sp14, 4, -1);
                    HSD_ForeachAnim(sp14, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjReqAnim, AOBJ_ARG_AF, f24);
                    HSD_JObjAnimAll(sp14);
                    HSD_ForeachAnim(sp14, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                }
            } else {
                lb_80011E24(jobj, &sp10, 4, -1);
                HSD_ForeachAnim(sp10, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                                AOBJ_ARG_AF, 16.0f);
                HSD_JObjAnimAll(sp10);
                HSD_ForeachAnim(sp10, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                                AOBJ_ARG_AOV, 0, 0);
            }
            lb_80011E24(jobj, &sp24, 3, -1);
            HSD_ForeachAnim(sp24, JOBJ_TYPE, MOBJ_MASK, HSD_AObjReqAnim,
                            AOBJ_ARG_AF, (f32) (model->x6 * 0x28));
            model->x7 = 0;
        }
    }

    {
        u8 status = model->x5;
        if (status == 0) {
            s32 iter;
            for (iter = 0; iter < 0x14; iter++) {
                s32 j;
                struct CSSCharModel** bdp = mnCharSel_804A0BD0;
                CSSDoor* dp = mnCharSel_803F0DFC.doors;

                for (j = 0; j < (s32) n_doors; j++) {
                    if (j != (s32) model->x4 &&
                        (u8) (*bdp)->x5 == 0 &&
                        (u8) dp->p_kind != 3 &&
                        (u8) dp->sel_icon < 0x19U)
                    {
                        f32 angle;
                        f32 dx;
                        f32 dy;
                        do {
                            dx = (0.1f * (HSD_Randf() - 0.5f)) +
                                 (model->x8 - (*bdp)->x8);
                        } while (dx == 0.0f);

                        do {
                            dy = (0.1f * (HSD_Randf() - 0.5f)) +
                                 (model->xC - (*bdp)->xC);
                        } while (dy == 0.0f);

                        if ((dx * dx + dy * dy) < 8.0f) {
                            if (dy < 0.01f && dy > -0.01f) {
                                f64 half_pi;
                                if (dx < 0.0f) {
                                    half_pi = 1.5707963267948966;
                                } else {
                                    half_pi = -1.5707963267948966;
                                }
                                angle = (f32) half_pi;
                            } else {
                                f64 base_a;
                                if (dy < 0.0f) {
                                    base_a = 0.0;
                                } else {
                                    base_a = 3.141592653589793;
                                }
                                angle = (f32) (base_a + atanf(dx / dy));
                            }
                            model->x8 =
                                -((0.01f * sinf(angle)) - model->x8);
                            model->xC =
                                -((0.01f * cosf(angle)) - model->xC);
                        }
                    }
                    bdp++;
                    dp++;
                }

                {
                    f32 x;

                    x = model->x8;
                    if (x < 1.5f + icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_l) {
                        model->x8 = x + 0.02f;
                        if (model->x8 < icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_l) {
                            model->x8 = icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_l;
                        }
                    }

                    x = model->x8;
                    if (x > icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_r - 1.5f) {
                        model->x8 = x - 0.02f;
                        if (model->x8 > icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_r) {
                            model->x8 = icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_r;
                        }
                    }

                    x = model->xC;
                    if (x > icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_u - 1.5f) {
                        model->xC = x - 0.02f;
                        if (model->xC > icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_u) {
                            model->xC = icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_u;
                        }
                    }

                    x = model->xC;
                    if (x < 1.5f + icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_d) {
                        model->xC = x + 0.02f;
                        if (model->xC < icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_d) {
                            model->xC = icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon].bound_d;
                        }
                    }
                }
            }
        } else {
            model->x8 = 2.7f + mnCharSel_804A0BD0[status - 1]->xC;
            model->xC = -2.0f + mnCharSel_804A0BD0[model->x5 - 1]->x10;
        }
    }

    {
        f32 dy = model->x14 - model->xC;
        f32 tx = model->x8;
        f32 dx = model->x10 - tx;

        if ((dx * dx + dy * dy) < 4.0f) {
            model->x10 = tx;
            model->x14 = model->xC;
        } else {
            f32 angle;
            if (dy < 0.01f && dy > -0.01f) {
                f64 half_pi;
                if (dx < 0.0f) {
                    half_pi = 1.5707963267948966;
                } else {
                    half_pi = -1.5707963267948966;
                }
                angle = (f32) half_pi;
            } else {
                f64 base_a;
                if (dy < 0.0f) {
                    base_a = 0.0;
                } else {
                    base_a = 3.141592653589793;
                }
                angle = (f32) (base_a + atanf(dx / dy));
            }
            model->x10 = (3.0f * sinf(angle)) + model->x10;
            model->x14 = (3.0f * cosf(angle)) + model->x14;
        }
    }

    HSD_JObjSetTranslateX(jobj, model->x10);
    HSD_JObjSetTranslateY(jobj, model->x14);
    HSD_JObjSetTranslateZ(jobj, 1.0f);
    HSD_JObjAnimAll(jobj);
}

/// #fn_80262F44
void fn_80262F44(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int i;
    PAD_STACK(16);

    if (mnCharSel_804D6CB0->match_type == VS_CAMERA) {
        if (HSD_PadCopyStatus[3].err != 0) {
            HSD_JObjClearFlagsAll(
                mnCharSel_804D6CCC != NULL ? mnCharSel_804D6CCC->child : NULL,
                JOBJ_HIDDEN);
            goto hide;
        }
        HSD_JObjSetFlagsAll(
            mnCharSel_804D6CCC != NULL ? mnCharSel_804D6CCC->child : NULL,
            JOBJ_HIDDEN);
    }

    if (mnCharSel_804D6CF5 == 1) {
        if (mnCharSel_804A0BD0[0]->x5 == 1 ||
            mnCharSel_803F0DFC.doors[0].sel_icon >= 0x19)
        {
            mnCharSel_804D6CF7 = 0;
        } else {
            mnCharSel_804D6CF7 = 1;
        }
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    } else {
        s32 valid_count = 0;

        for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
            if (mnCharSel_803F0DFC.doors[i].p_kind != 3) {
                if (mnCharSel_803F0DFC.doors[i].sel_icon >= 0x19) {
                    goto hide;
                }
                valid_count++;
            }
        }

        if (valid_count >= 2) {
            if (mnCharSel_804D6CB0->data.data.rules.is_teams == 1) {
                for (i = 0; i < (s32) (mnCharSel_804D6CF5 - 1); i++) {
                    s32 j;
                    if (mnCharSel_803F0DFC.doors[i].p_kind == 3) {
                        continue;
                    }
                    for (j = i; j < (s32) mnCharSel_804D6CF5; j++) {
                        if (mnCharSel_803F0DFC.doors[j].p_kind != 3 &&
                            mnCharSel_803F0DFC.doors[i].team !=
                                mnCharSel_803F0DFC.doors[j].team)
                        {
                            goto teams_ok;
                        }
                    }
                }
                goto hide;
            }
        teams_ok: {
            CSSTag* tag = mnCharSel_803F0DFC.tags;
            for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
                if (mnCharSel_804A0BD0[i]->x5 == 1 ||
                    tag[i].data->state != 0)
                {
                    goto hide;
                }
            }
        }

            if (mnCharSel_804D6CF7 == 0) {
                HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjReqAnim, AOBJ_ARG_AF, 0.0);
            } else if (mnCharSel_804D6CF7 > 100) {
                HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjReqAnim, AOBJ_ARG_AF, 10.0);
                mnCharSel_804D6CF7 = 10;
            }
            mnCharSel_804D6CF7++;
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            HSD_JObjAnimAll(jobj);
        } else {
        hide:
            mnCharSel_804D6CF7 = 0;
            mnCharSel_804D6CF2 = 10;
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }

    {
        u32 trigger;
        if (mnCharSel_804D6CF5 == 1) {
            trigger = HSD_PadCopyStatus[(u8) mnCharSel_804D6CF0].trigger;
        } else {
            u8 p = 0;
            trigger = 0;
            for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
                if (mnCharSel_804A0BD0[i]->x5 != 3) {
                    trigger |= HSD_PadCopyStatus[p].trigger;
                }
                p++;
            }
        }

        if (mnCharSel_804D6CF2 == 0 && (trigger & HSD_PAD_START)) {
            if (mnCharSel_804D6CF7 != 0) {
                mnCharSel_804D6CF6 = 1;
                mnCharSel_804D6CF2 = 0xFF;
                if (mnCharSel_804D6CF5 == 1) {
                    if (gm_801677F8(
                            mnCharSel_804D6CF0,
                            mnCharSel_804D6CB0->data.data
                                .players[mnCharSel_804D6CF0]
                                .xA))
                    {
                        lb_80014574(mnCharSel_804D6CF0, 0, 0xB, 0x1E);
                    }
                } else {
                    for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
                        if (mnCharSel_803F0DFC.doors[i].p_kind == 0 &&
                            gm_801677F8(
                                i,
                                mnCharSel_804D6CB0->data.data.players[i].xA))
                        {
                            lb_80014574(i, 0, 0xB, 0x1E);
                        }
                    }
                }
            } else {
                lbAudioAx_80024030(3);
            }
        }
    }
}

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

void mnCharSel_802669F4_OnFrame(void)
{
    int num_slots;
    u8 temp_r0;
    struct GameCache* temp_r3;
    int i;

    PAD_STACK(8);

    mnCharSel_804D6CEC += 1;
    if (mnCharSel_804D6CF6 <= 1) {
        temp_r3 = &lbDvd_8001822C()->game_cache;
        if (mnCharSel_804D6CF5 == 1) {
            CSSData* css = mnCharSel_804D6CB0;
            temp_r0 = css->data.data.players[mnCharSel_804D6CF0].slot_type;
            if (!(temp_r0 != 0 && temp_r0 != 1) &&
                mnCharSel_804A0BD0[0]->x5 == 0)
            {
                temp_r3->entries[0].char_id =
                    css->data.data.players[mnCharSel_804D6CF0].c_kind;
                temp_r3->entries[0].color =
                    mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF0]
                        .color;
            } else {
                temp_r3->entries[0].char_id = CHKIND_NONE;
            }
            css = mnCharSel_804D6CB0;
            temp_r0 = css->data.data.players[mnCharSel_804D6CF1].slot_type;
            if (!(temp_r0 != 0 && temp_r0 != 1)) {
                if (mnCharSel_804A0BD0[1]->x5 == 0) {
                    temp_r3->entries[1].char_id =
                        css->data.data.players[mnCharSel_804D6CF1].c_kind;
                    temp_r3->entries[1].color =
                        mnCharSel_804D6CB0->data.data
                            .players[mnCharSel_804D6CF1]
                            .color;
                } else {
                    temp_r3->entries[1].char_id = CHKIND_NONE;
                }
            }
        } else {
            if (mnCharSel_804D6CB0->match_type == VS_CAMERA) {
                num_slots = 3;
            } else {
                num_slots = 4;
            }

            for (i = 0; i < num_slots; i++) {
                CSSData* css = mnCharSel_804D6CB0;
                temp_r0 = css->data.data.players[i].slot_type;
                if (!(temp_r0 != 0 && temp_r0 != 1) &&
                    mnCharSel_804A0BD0[i]->x5 == 0)
                {
                    temp_r3->entries[i].char_id =
                        css->data.data.players[i].c_kind;
                    temp_r3->entries[i].color =
                        mnCharSel_804D6CB0->data.data.players[i].color;
                } else {
                    temp_r3->entries[i].char_id = CHKIND_NONE;
                }
            }
        }
        lbDvd_80018254();
    }
    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        lb_800145F4();
        mn_8022F138(1, 8);
        HSD_SisLib_803A5E70();
        mn_8022F268();
        gm_801A42F8(MJ_MENU);
        gm_801A4B60();
        return;
    }
    if (mnCharSel_804D6CF2 != 0) {
        mnCharSel_804D6CF2--;
    }
    switch (mnCharSel_804D6CF6) {
    case 1:
        for (i = 0; i < 4; i++) {
            if (mnCharSel_803F0DFC.doors[i].p_kind != 3 &&
                mnCharSel_804A0BD0[0]->x5 != 0)
            {
                mnCharSel_804D6CF6 = 0;
            }
        }
        if (mnCharSel_804D6CF6 != 0) {
            gm_801A4B60();
            if ((u8) mnCharSel_804D6CF5 == 4) {
                lbAudioAx_8002411C(0x147);
            }
            lbAudioAx_80024030(1);
        }
        break;
    case 2:
        gm_801A4B60();
        lbAudioAx_80024030(0);
        break;
    case 3:
        mn_8022F138(1, 8);
        HSD_SisLib_803A5E70();
        mn_80231804(mnCharSel_804D6CD4, 1);
        mnCharSel_804D6CF6 = 5;
        lbAudioAx_80024030(1);
        break;
    case 4:
        mn_8022F138(1, 8);
        HSD_SisLib_803A5E70();
        mnNameNew_EnterFromMnCharSel(mnCharSel_804D6CD4, mnCharSel_804D6CF9);
        mnCharSel_804D6CF6 = 5;
        lbAudioAx_80024030(1);
        break;
    }
}

void mnCharSel_80266D70_OnLeave(void* unused)
{
    int num_slots;
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
        if ((type == Gm_PKind_Human || type == Gm_PKind_Cpu) &&
            mnCharSel_804A0BD0[0]->x5 == 0)
        {
            tmp |= lbAudioAx_80026E84(
                data->data.data.players[mnCharSel_804D6CF0].c_kind);
        }
        data = mnCharSel_804D6CB0;
        type = data->data.data.players[mnCharSel_804D6CF1].slot_type;
        if ((type == Gm_PKind_Human || type == Gm_PKind_Cpu) &&
            mnCharSel_804A0BD0[1]->x5 == 0)
        {
            tmp |= lbAudioAx_80026E84(
                data->data.data.players[mnCharSel_804D6CF1].c_kind);
        }
    } else {
        if (mnCharSel_804D6CB0->match_type == VS_CAMERA) {
            num_slots = 3;
        } else {
            num_slots = 4;
        }
        for (i = 0; i < num_slots; i++) {
            data = mnCharSel_804D6CB0;
            type = data->data.data.players[i].slot_type;
            if ((type == Gm_PKind_Human || type == Gm_PKind_Cpu) &&
                mnCharSel_804A0BD0[i]->x5 == 0)
            {
                tmp |= lbAudioAx_80026E84(data->data.data.players[i].c_kind);
            }
        }
    }

    lbAudioAx_80026F2C(0x14);
    lbAudioAx_8002702C(4, tmp);
    lbAudioAx_80027168();
}

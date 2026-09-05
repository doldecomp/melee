#include "gmregclear.h"

#include "gm_unsplit.h"
#include "types.h"

#include "forward.h"
#include <sysdolphin/baselib/forward.h>

#include <dolphin/pad.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/tobj.h>
#include <melee/cm/camera.h>
#include <melee/gr/ground.h>
#include <melee/gr/grpushon.h>
#include <melee/if/ifcoget.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/mn/inlines.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>
#include <Runtime/platform.h>

struct lbl_80472D28_t {
    /*   +0 */ char pad_0[0x20];
    /* +20 */ HSD_JObj* x20;
    /* +24 */ HSD_JObj* x24;
    /* +28 */ char pad_28[4];
    /* +2C */ HSD_GObj* x2C;
    /* +30 */ HSD_ImageDesc x30;
    /* +48 */ HSD_Archive* x48;
    /* +4C */ DynamicModelDesc x4C;
    /* +5C */ void* x5C;
    /* +60 */ void* x60;
    /* +64 */ char pad_64[0x20];
    /* +84 */ HSD_Text* x84;
    /* +88 */ char pad_88[0x38];
    /* +C0 */ u16 xC0;
    /* +C2 */ u16 pad_C2;
    /* +C4 */ u32 xC4;
    /* +C8 */ u8 xC8;
    /* +C9 */ u8 pad_C9[3];
    /* +CC */ s32 xCC;
    /* +D0 */ s32 xD0;
    /* +D4 */ s32 xD4;
    /* +D8 */ s32 xD8;
    /* +DC */ s32 xDC;
    /* +E0 */ s32 xE0;
    /* +E4 */ s32 xE4;
    /* +E8 */ s32 xE8;
    /* +EC */ s32 xEC;
    /* +F0 */ s32 xF0;
    /* +F4 */ s32 xF4;
    /* +F8 */ s32 xF8;
    /* +FC */ s32 xFC;
    /* +100 */ s32 x100;
    /* +104 */ int x104;
    /* +108 */ s16 x108;
    /* +10A */ s16 x10A;
    /* +10C */ f32 x10C;
    /* +110 */ u32 x110;
    /* +114 */ u8 x114;
    /* +115 */ u8 x115;
    /* +116 */ u8 x116;
    /* +117 */ u8 x117;
    /* +118 */ u8 x118;
    /* +119 */ u8 x119;
    /* +11A */ u8 x11A;
    /* +11B */ u8 x11B;
    /* +11C */ u8 x11C;
    /* +11D */ u8 x11D;
    /* +11E */ u8 x11E;
    /* +11F */ u8 x11F;
};

typedef struct RegClearEv {
    /* 0x00 */ char pad_0[0x1C];
    /* 0x1C */ HSD_ImageDesc* x1C;
    /* 0x20 */ f32 x20;
} RegClearEv;

static struct lbl_80472D28_t lbl_80472D28;

u16 lbl_803D8B88[] = { 0x18, 0x16, 0x12, 0x3, 0x5, 0x4, 0x6, 0x1a, 0x19, 0x7 };

/// @todo .data order hack
#ifdef MUST_MATCH
static void order_data(void)
{
    (void) "GmRegClr";
    (void) "ScGamRegClear_scene_data";
    (void) "Error : Cannot open archive file (File Name : %s).";
    (void) "SdDec.usd";
    (void) "SIS_DecisionData";
    (void) "SdDec.dat";
    (void) "          ";
    (void) "               ";
    (void) "Error : gobj don\'t get (gmRegClearAddModel)\n";
    (void) "gmregclear.c";
    (void) "Error : jobj don\'t get (gmRegClearAddModel)\n";
    (void) "SdClr.usd";
    (void) "SIS_ClearData";
    (void) "SdClr.dat";
}
#endif

int fn_8017F008(void)
{
    int r3 = fn_80171A88();
    if (r3 == 3) {
        return 4;
    } else if (r3 == 1) {
        return 1;
    } else if (r3 == 2) {
        return 8;
    } else if (r3 == 7) {
        return 0x20;
    } else if (r3 == 6) {
        return 0x80;
    } else if (r3 == 8) {
        return 0x40;
    } else if (r3 == 4) {
        return 0x10;
    } else {
        return 0xFD;
    }
}

s32 fn_8017F09C(void)
{
    struct lbl_80472D28_t* data = &lbl_80472D28;
    lbl_8046B6A0_t* p = gm_16AE_GetUnkData_0();
    if (p->x24C8.x4_6) {
        lbl_8046B6A0_t* p2 = gm_16AE_GetUnkData_0();
        int flag;
        if (data->x118 != 0 || (data->x11A != 0 && data->x11B == 0) ||
            p2->x24C8.timer_counts_up)
        {
            flag = 0;
        } else {
            flag = 1;
        }
        if (flag != 0) {
            s32 product = p->timer_seconds * data->x108;
            s32 ret = product;
            if (product < 0) {
                ret = 0;
            }
            return ret;
        }
    }
    return 0;
}

typedef struct fn_8017F14C_arg {
    /* 0x00 */ char pad_0[0x98];
    /* 0x98 */ s32 x98;
} fn_8017F14C_arg;

#ifdef MUST_MATCH
#pragma dont_inline on
#endif
s32 fn_8017F14C(void* arg0)
{
    fn_8017F14C_arg* p = arg0;
    struct lbl_80472D28_t* data = &lbl_80472D28;
    if (gm_16AE_GetUnkData_0()->x24C8.x4_7) {
        s32 val = p->x98;
        s32 ret = val;
        if (val > 9999) {
            ret = 9999;
        }
        return ret * data->x10A;
    }
    return 0;
}
#ifdef MUST_MATCH
#pragma dont_inline off
#endif

s32 fn_8017F1B8(void)
{
    int i;
    int mask;
    int output;

    for (i = 0; i < 256; i++) {
        if (fn_8016F1F0(i) < 0xD7) {
            mask = fn_8017F008();
            output = (u8) fn_8016F180(i);
            if (output & mask) {
                if ((u32) fn_8016F160(0, i) != 0) {
                    fn_8016F140(i);
                }
            }
        } else {
            mask = fn_8017F008();
            output = (u8) fn_8016F180(i);
            if (output & mask) {
                if ((u32) fn_801701C0(gm_8016B774(), 0, i) != 0) {
                    fn_8016F140(i);
                }
            }
        }
    }

    mask = (u8) fn_8017F008();
    return fn_8016FFD4(gm_8016B774(), mask, 0);
}

int fn_8017F294(void)
{
    return lbl_80472D28.x104;
}

s32 fn_8017F2A4(HSD_Text** arg0, f32 farg0, f32 farg1)
{
    HSD_Text* text;
    HSD_Text** ptr;
    u8* data;
    f32 y;
    f32 x_end;
    s32 i;
    s32 temp;

    temp = HSD_SisLib_803A611C(3, NULL, 9U, 0xDU, 0U, 0x14U, 0U, 0x13U);
    if (lbLang_IsSavedLanguageUS()) {
        HSD_SisLib_803A62A0(3, "SdDec.usd", "SIS_DecisionData");
    } else {
        HSD_SisLib_803A62A0(3, "SdDec.dat", "SIS_DecisionData");
    }
    *arg0 = HSD_SisLib_803A6754(3, temp);
    ptr = arg0;

    (*arg0)->default_kerning = 1;
    text = *arg0;
    text->x34.x = 0.56f;
    text->x34.y = 0.6f;
    (*arg0)->default_alignment = 2;
    x_end = 281.0f + farg0;
    for (i = 0; i < 7; i++) {
        y = (0.6f * (32.0f * (f32) i)) + farg1;
        ptr[1] = HSD_SisLib_803A5ACC(3, 0, farg0, y, 0.0f, 2.0f, 2.0f);
        text = ptr[1];
        text->x34.x = 0.56f;
        text->x34.y = 0.6f;
        ptr[1]->default_kerning = 1;
        HSD_SisLib_803A6B98(*arg0, x_end, -12.0f + y, "          ");
        ptr++;
    }
    return HSD_SisLib_803A6B98(*arg0, x_end, 9.0f + (134.40001f + farg1),
                               "               ");
    PAD_STACK(8);
}

s32 fn_8017F47C(HSD_Text** arg0, int arg1)
{
    u8 mask;
    s32 val;
    s32* p;
    s32 i;
    int entry;
    s32 prev_idx;
    s32 idx;

    entry = arg1;
    prev_idx = -999;
    mask = fn_8017F008();
    fn_8016F39C(arg0 + 1, gm_8016B774(), 7, arg1, mask, 0);

    i = 0;
    p = (s32*) arg0;

    do {
        mask = fn_8017F008();
        idx = fn_8016F548(gm_8016B774(), entry, mask, 0);
        mask = fn_8017F008();
        val = fn_8016FAD4(gm_8016B774(), (u32) idx, (s32) mask, 0);

        if (prev_idx == idx || idx < 0) {
            break;
        }

        if (p[8] != val) {
            if (val < 0) {
                HSD_SisLib_803A70A0(*arg0, i, "%s%d", "－", -val);
            } else {
                HSD_SisLib_803A70A0(*arg0, i, "%d", val);
            }
            p[8] = val;
        }

        prev_idx = idx;
        entry = idx + 1;
        p++;
        i++;
    } while (i < 7);

    mask = fn_8017F008();
    val = fn_8016FFD4(gm_8016B774(), (s32) mask, 0);

    if (val < 0) {
        HSD_SisLib_803A70A0(*arg0, 7, "%s%d", "\x81\x7c", -val);
    } else {
        HSD_SisLib_803A70A0(*arg0, 7, "%d", val);
    }

    mask = fn_8017F008();
    return fn_8016F548(gm_8016B774(), arg1, mask, 0);
    PAD_STACK(0x18);
}

typedef struct fn_8017FA1C_arg {
    /* 0x000 */ HSD_GObj* x0;
    /* 0x004 */ HSD_JObj* x4;
    /* 0x008 */ HSD_JObj* x8;
    /* 0x00C */ HSD_JObj* xC;
    /* 0x010 */ HSD_JObj* x10;
    /* 0x014 */ HSD_JObj* x14;
    /* 0x018 */ HSD_JObj* x18;
    /* 0x01C */ HSD_JObj* x1C;
    /* 0x020 */ HSD_JObj* x20;
    /* 0x024 */ HSD_JObj* x24;
    /* 0x028 */ char pad_28[0x24];
    /* 0x04C */ DynamicModelDesc x4C;
    /* 0x05C */ char pad_5C[0x10];
    /* 0x06C */ HSD_Text* x6C;
    /* 0x070 */ HSD_Text* x70;
    /* 0x074 */ HSD_Text* x74;
    /* 0x078 */ HSD_Text* x78;
    /* 0x07C */ HSD_Text* x7C;
    /* 0x080 */ HSD_Text* x80;
    /* 0x084 */ char pad_84[0x48];
    /* 0x0CC */ s32 xCC;
    /* 0x0D0 */ s32 xD0;
    /* 0x0D4 */ s32 xD4;
    /* 0x0D8 */ s32 xD8;
    /* 0x0DC */ s32 xDC;
    /* 0x0E0 */ s32 xE0;
    /* 0x0E4 */ s32 xE4;
    /* 0x0E8 */ char pad_E8[0x08];
    /* 0x0F0 */ s32 xF0;
    /* 0x0F4 */ s32 xF4;
    /* 0x0F8 */ s32 xF8;
    /* 0x0FC */ s32 xFC;
    /* 0x100 */ s32 x100;
    /* 0x104 */ s32 x104;
    /* 0x108 */ s16 x108;
    /* 0x10A */ s16 x10A;
    /* 0x10C */ char pad_10C[0x08];
    /* 0x114 */ u8 x114;
    /* 0x115 */ u8 x115;
    /* 0x116 */ char pad_116[2];
    /* 0x118 */ u8 x118;
    /* 0x119 */ char pad_119;
    /* 0x11A */ u8 x11A;
    /* 0x11B */ u8 x11B;
} fn_8017FA1C_arg;

static const Vec3 lbl_803B7C18 = { -41.0f, -0.25f, 0.0f };

void fn_8017F608(void* arg0)
{
    fn_8017FA1C_arg* p = arg0;
    Vec3 sp4C;
    Vec3 sp40;
    HSD_Text* text;
    lbl_8046B6A0_t* gm;
    s32 show;

    sp40 = lbl_803B7C18;

    if (p->x6C == NULL) {
        p->x6C = HSD_SisLib_803A5ACC(0, 0, 0.0f, 0.0f, 0.0f, 6.0f, 300.0f);
        HSD_SisLib_803A6368(p->x6C, 2);
    }
    if (p->x70 == NULL) {
        text = HSD_SisLib_803A5ACC(0, 0, 0.0f, 0.0f, 0.0f, 6.0f, 300.0f);
        p->x70 = text;
        if (p->x11A != 0) {
            HSD_SisLib_803A6368(p->x70, 4);
        } else {
            HSD_SisLib_803A6368(p->x70, 3);
        }
    }
    if (p->xD0 != p->xD4) {
        s32 str;
        p->xD8 = p->xD8 + 1;
        text = p->x74;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
        }
        p->x74 = HSD_SisLib_803A6754(0, 0);
        {
            struct lbl_80472D28_t* state = &lbl_80472D28;
            p->x74->pos_z = -10.0f;
            p->x74->default_alignment = 2;
            gm = gm_16AE_GetUnkData_0();
            if (state->x118 != 0 || (state->x11A != 0 && state->x11B == 0) ||
                gm->x24C8.timer_counts_up)
            {
                show = 0;
            } else {
                show = 1;
            }
            if (show == 0) {
                str = HSD_SisLib_803A6B98(p->x74, 0.0f, 0.0f, "\x81|");
                HSD_SisLib_803A7548(p->x74, str, 0.1f, 0.065f);
                p->xD4 = p->xD0;
            } else if (p->xD8 < 0x3C) {
                p->x74->default_kerning = 1;
                str = HSD_SisLib_803A6B98(p->x74, 0.0f, 0.0f, "%dＸ%d",
                                          p->xD0 / p->x108, p->x108);
                HSD_SisLib_803A7548(p->x74, str, 0.089999996f, 0.065f);
            } else {
                str = HSD_SisLib_803A6B98(p->x74, 0.0f, 0.0f, "%d", p->xD0);
                HSD_SisLib_803A7548(p->x74, str, 0.1f, 0.065f);
                p->xD4 = p->xD0;
            }
        }
    }
    if (p->x11A == 0 && p->xDC != p->xE0) {
        s32 str;
        p->xE4 = p->xE4 + 1;
        text = p->x78;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
        }
        p->x78 = HSD_SisLib_803A6754(0, 0);
        p->x78->default_alignment = 2;
        if (p->xE4 < 0x3C) {
            p->x78->default_kerning = 1;
            str = HSD_SisLib_803A6B98(p->x78, 0.0f, 0.0f, "%d\x82w%d",
                                      p->xDC / p->x10A, p->x10A);
            HSD_SisLib_803A7548(p->x78, str, 0.1f, 0.065f);
        } else {
            str = HSD_SisLib_803A6B98(p->x78, 0.0f, 0.0f, "%d", p->xDC);
            HSD_SisLib_803A7548(p->x78, str, 0.1f, 0.065f);
            p->xE0 = p->xDC;
        }
    }
    lb_8000B1CC(p->x10, &sp40, &sp4C);
    text = p->x70;
    if (text != NULL) {
        f32 px, py, pz;
        px = sp4C.x;
        py = -sp4C.y;
        pz = sp4C.z;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }
    text = p->x6C;
    if (text != NULL) {
        f32 px, py, pz;
        px = 0.1f + sp4C.x;
        py = -sp4C.y - 6.0f;
        pz = sp4C.z;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }
    text = p->x74;
    if (text != NULL) {
        f32 px, py, pz;
        px = 6.5f + sp4C.x;
        py = -sp4C.y - 33.5f;
        pz = sp4C.z;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }
    text = p->x78;
    if (text != NULL) {
        f32 px, py, pz;
        px = 6.5f + sp4C.x;
        py = -sp4C.y - 27.5f;
        pz = sp4C.z;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }
    PAD_STACK(0x24);
}

s32 lbl_804D65C0;

s32 fn_8017FA1C(void* arg0)
{
    fn_8017FA1C_arg* p = arg0;
    Vec3 sp14;
    s32 step;
    s32 target_val;
    s32 diff;
    s32 abs_step;
    f32 px, py, pz;

    PAD_STACK(4);

    if (HSD_JObjGetFlags(p->xC) & 0x10) {
        if (p->x80 != NULL) {
            HSD_SisLib_803A5CC4(p->x80);
        }
        p->x80 = NULL;
        p->x100 = p->xFC - 1;
        return 0;
    }
    if ((p->xFC && p->xFC) && p->xFC) {
    }
    abs_step = p->x104;
    step = lbl_804D65C0;
    target_val = abs_step;
    diff = target_val - p->xFC;

    if (step < 0) {
        abs_step = -step;
    } else {
        abs_step = step;
    }

    if (diff < 0) {
        diff = -diff;
    }

    if (diff <= abs_step) {
        p->xFC = target_val;
        p->x115 = 1;
    } else {
        p->xFC += step;
        p->x115 = 0;
    }

    if (p->xFC != p->x100) {
        int str;
        if (p->x80 != NULL) {
            HSD_SisLib_803A5CC4(p->x80);
        }
        p->x80 = HSD_SisLib_803A6754(0, 0);
        p->x80->default_alignment = 2;
        str = HSD_SisLib_803A6B98(p->x80, 0.0f, 0.0f, "%d", p->xFC);
        HSD_SisLib_803A7548(p->x80, str, 0.1f, 0.08f);
        p->x100 = p->xFC;
    }

    if (p->x80 != NULL) {
        HSD_Text* text;
        lb_8000B1CC(p->xC, NULL, &sp14);
        py = -sp14.y - 30.6f;
        px = 16.0f + sp14.x;
        pz = sp14.z;
        text = p->x80;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }

    return 1;
}

void fn_8017FBA4(void* arg0)
{
    fn_8017FA1C_arg* p = arg0;
    int tmp;
    Vec3 sp24;
    f32 sx, sy;
    int str;

    if (HSD_JObjGetFlags(p->x8) & 0x10) {
        if (p->x7C != NULL) {
            HSD_SisLib_803A5CC4(p->x7C);
        }
        p->x7C = NULL;
        p->xF4 = p->xF0 - 1;
        return;
    }

    if (p->xF0 != p->xF4) {
        if (p->x7C != NULL) {
            HSD_SisLib_803A5CC4(p->x7C);
        }
        p->x7C = HSD_SisLib_803A6754(0, 0);
        tmp = HSD_SisLib_803A6B98(p->x7C, 0.0f, 0.0f, "%d", p->xF0);
        HSD_SisLib_803A7548(p->x7C, tmp, 0.1f, 0.065f);
        p->xF4 = p->xF0;
    }

    sx = HSD_JObjGetScaleX(p->x8->parent);
    sy = HSD_JObjGetScaleY(p->x8->parent);

    if (p->x7C != NULL) {
        HSD_SisLib_803A5CC4(p->x7C);
    }
    p->x7C = HSD_SisLib_803A6754(0, 0);
    p->x7C->default_alignment = 2;
    p->xF8 = p->xF8 + 1;

    if (p->xF8 < 0xC) {
        HSD_SisLib_803A7548(
            p->x7C,
            HSD_SisLib_803A6B98(p->x7C, 0.0f, 0.0f, "%s %d", "\x81{", p->xCC),
            0.1f * sx, 0.065f * sy);
    } else if (p->xF8 < 0x20) {
        HSD_SisLib_803A7548(p->x7C,
                            HSD_SisLib_803A6B98(p->x7C, 0.0f, 0.0f, "%s %d",
                                                "\x81{", p->xDC + p->xD0),
                            0.1f * sx, 0.065f * sy);
    } else {
        if (p->xF0 >= 0) {
            str = HSD_SisLib_803A6B98(p->x7C, 0.0f, 0.0f, "%s %d", "\x81{",
                                      p->xF0);
        } else {
            str =
                HSD_SisLib_803A6B98(p->x7C, 0.0f, 0.0f, "%d", p->xF0, p->xF0);
        }
        HSD_SisLib_803A7548(p->x7C, str, 0.1f * sx, 0.065f * sy);
    }

    if (p->x7C != NULL) {
        f32 px, py, pz;
        HSD_Text* text;
        lb_8000B1CC(p->x8, NULL, &sp24);
        py = -sp24.y - 31.0f;
        px = 8.5f + sp24.x;
        pz = sp24.z;
        text = p->x7C;
        text->pos_x = px;
        text->pos_y = py;
        text->pos_z = pz;
    }
    PAD_STACK(4);
}

void fn_8017FE54(HSD_GObj* gobj)
{
    RegClearEv* ev = gobj->user_data;
    struct lbl_80472D28_t* state = &lbl_80472D28;

    lb_800122C8(ev->x1C, 0, 0, 1);
    lb_800138D8(state->x2C, (int) (120.0F * state->x10C) + 1);

    ev->x20 = 0.0225F * (f32) state->x110 - 0.175F;

    if (ev->x20 < 0.05F) {
        ev->x20 = 0.0F;
    }
    if (ev->x20 > 1.0F) {
        ev->x20 = 1.0F;
    }
}

void fn_8017FF1C(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    /// @todo Consolidate these split-derived views of the same state object.
    union {
        struct lbl_80472D28_t* state;
        fn_8017FA1C_arg* arg;
    } data;
    s32 result;
    s32 i;
    u8 mask;
    HSD_JObj* sp28;

    data.state = (data.state = &lbl_80472D28);
    jobj = gobj->hsd_obj;
    HSD_JObjAnimAll(jobj);

    if (data.arg->x118 == 0) {
        fn_8017F608(data.arg);
    }

    {
        fn_8017FA1C_arg* arg = data.arg;
        result = fn_8017FA1C(arg);
    }
    fn_8017FBA4(data.arg);

    if (data.state->x117 != 0 && data.state->x110 > 0x29U) {
        data.state->xC0 = fn_8017F47C(&data.state->x84, (s32) data.state->xC0);

        mask = fn_8017F008();
        if (fn_8016F9A8(gm_8016B774(), data.state->xC0, mask, 0) > 7) {
            data.state->x11F = 0;
        } else {
            data.state->x11F = 1;
        }

        mask = fn_8017F008();
        if (fn_8016F870(gm_8016B774(), data.state->xC0, mask, 0) < 0) {
            data.state->x11E = 1;
        } else {
            data.state->x11E = 0;
        }

        if (data.state->x110 % 30 == 0 && data.state->xC8 == 0) {
            mask = fn_8017F008();
            if (fn_8016F9A8(gm_8016B774(), data.state->xC0, mask, 0) > 7) {
                data.state->xC0 = (u16) (data.state->xC0 + 1);
            } else {
                data.state->xC8 = 1;
                data.state->xC4 = data.state->x110;
            }
        }

        {
            u64 buttons = gm_GetButtonsTriggered(Player_GetPlayerId(0));
            u64 repeat = gm_801A36C0(Player_GetPlayerId(0));
            if (((repeat | buttons) & (PAD_BUTTON_DOWN | PAD_STICK_DOWN)) |
                ((repeat | buttons) & 0))
            {
                mask = fn_8017F008();
                if (fn_8016F740(gm_8016B774(), data.state->xC0, mask, 0) > 0) {
                    mask = fn_8017F008();
                    if (fn_8016F9A8(gm_8016B774(), data.state->xC0, mask, 0) >
                        7)
                    {
                        mask = fn_8017F008();
                        data.state->xC0 = fn_8016F740(
                            gm_8016B774(), data.state->xC0, mask, 0);
                        data.state->xC8 = 1;
                        data.state->xC4 = data.state->x110;
                    }
                }
            } else {
                buttons = gm_GetButtonsTriggered(Player_GetPlayerId(0));
                repeat = gm_801A36C0(Player_GetPlayerId(0));
                if (((repeat | buttons) & (PAD_BUTTON_UP | PAD_STICK_UP)) |
                    ((repeat | buttons) & 0))
                {
                    if (fn_8016F870(gm_8016B774(), data.state->xC0,
                                    (u8) fn_8017F008(), 0) >= 0)
                    {
                        data.state->xC0 =
                            fn_8016F870(gm_8016B774(), data.state->xC0,
                                        (u8) fn_8017F008(), 0);
                        data.state->xC8 = 1;
                        data.state->xC4 = data.state->x110;
                    }
                }
            }
        }
    }

    if (data.state->x11A != 0 && data.state->x110 > 0x14U &&
        data.state->x11D < data.state->x11C &&
        (s32) (0.5f * (f32) (data.state->x110 - 0x14)) >
            (s32) data.state->x11D)
    {
        lb_80011E24(jobj, &sp28, data.state->x11D + 7, -1);
        HSD_JObjClearFlagsAll(sp28, JOBJ_HIDDEN);
        data.state->x11D = (u8) (data.state->x11D + 1);
    }

    if (data.state->x115 == 0 && result != 0) {
        fn_80168F2C(0);
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) == Gm_PKind_Human &&
            (HSD_PadMasterStatus[(u8) Player_GetPlayerId(i)].trigger &
             HSD_PAD_A))
        {
            data.state->xFC = data.state->x104;
            data.state->x115 = 1;
            break;
        }
    }

    if (data.state->x110 > 0x3EU) {
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) == Gm_PKind_Human &&
                (HSD_PadMasterStatus[(u8) Player_GetPlayerId(i)].trigger &
                 0x1000))
            {
                data.state->xFC = data.state->x104;
                data.state->x116 = 1;
                sfxForward();
                break;
            }
        }
    }

    if (data.state->x11E != 0) {
        HSD_JObjSetFlagsAll(data.state->x20, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(data.state->x20, JOBJ_HIDDEN);
    }

    if (data.state->x11F != 0) {
        HSD_JObjSetFlagsAll(data.state->x24, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(data.state->x24, JOBJ_HIDDEN);
    }

    if (data.state->x10C < 1.0f) {
        data.state->x10C += 0.05f;
    } else {
        data.state->x10C = 1.0f;
    }

    if (data.state->x110 + 0x10000 != 0xFFFF) {
        data.state->x110 = data.state->x110 + 1;
    }
    PAD_STACK(0x1C);
}

s32 fn_801803FC(void* arg0)
{
    fn_8017FA1C_arg* p = arg0;
    HSD_JObj* sp10;
    struct lbl_80472D28_t* state = &lbl_80472D28;
    DynamicModelDesc* mdl = &p->x4C;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* temp;
    f32 frame;
    s32 i;

    gobj = GObj_Create(0xEU, 0xEU, 0U);
    p->x0 = gobj;
    if (gobj == NULL) {
        HSD_JObjAnimAll((HSD_JObj*) gobj->hsd_obj);
        OSReport("Error : gobj don\'t get (gmRegClearAddModel)\n");
        OSPanic(__FILE__, 0x42C, "");
    }
    jobj = HSD_JObjLoadJoint(mdl->joint);
    if (jobj == NULL) {
        OSReport("Error : jobj don\'t get (gmRegClearAddModel)\n");
        OSPanic(__FILE__, 0x432, "");
    }
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xBU, 0U);
    HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_8017FF1C, 0x11U);
    fn_801689E4(jobj, mdl, 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    {
        lb_8001204C(jobj, &p->x4, lbl_803D8B88, 0xA);
    }
    if (state->x117 == 0) {
        HSD_JObjSetFlagsAll(p->x14, JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(p->x20, JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(p->x24, JOBJ_HIDDEN);
    }
    if (p->x11A != 0) {
        for (i = 0; i < 0xA; i++) {
            lb_80011E24(jobj, &sp10, i + 7, -1);
            HSD_JObjSetFlagsAll(sp10, JOBJ_HIDDEN);
        }
        HSD_JObjSetFlagsAll(p->x10, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(p->x1C, JOBJ_HIDDEN);
        if (p->x118 != 0) {
            HSD_JObjSetFlagsAll(p->x18, JOBJ_HIDDEN);
        }
    }
    temp = p->x4;
    if (p->x114 != 0) {
        frame = 1.0f;
    } else {
        frame = 0.0f;
    }
    HSD_AObjSetCurrentFrame(temp->u.dobj->mobj->tobj->aobj, frame);
    HSD_AObjSetRate(temp->u.dobj->mobj->tobj->aobj, 0.0f);
    if (p->x118 == 0) {
        fn_8017F608(arg0);
    }
    fn_8017FBA4(arg0);
    return fn_8017FA1C(arg0);
    PAD_STACK(4);
}

static inline HSD_GObj* fn_80180630_CreateCameraGObj(void)
{
    return GObj_Create(0xEU, 0xEU, 0U);
}

static inline void* fn_80180630_LoadLightList(struct lbl_80472D28_t* state)
{
    return lb_80011AC4(state->x5C);
}

static inline void* fn_80180630_LoadCameraDesc(struct lbl_80472D28_t* state)
{
    return HSD_CObjLoadDesc(state->x60);
}

static inline DynamicModelDesc*
fn_80180630_GetModelDesc(struct lbl_80472D28_t* state)
{
    return &state->x4C;
}

static inline void fn_80180630_SetupSisLib(HSD_GObj* cam_gobj)
{
    HSD_SisLib_803A611C(0, cam_gobj, 9U, 0xDU, 0U, 0xEU, 0U, 0x13U);
    if (lbLang_IsSavedLanguageUS() != 0) {
        HSD_SisLib_803A62A0(0, "SdClr.usd", "SIS_ClearData");
    } else {
        HSD_SisLib_803A62A0(0, "SdClr.dat", "SIS_ClearData");
    }
}

static inline void
fn_80180630_CreateLightAndCamera(struct lbl_80472D28_t* state,
                                 HSD_GObj** cam_gobj)
{
    HSD_GObj* light_gobj;

    light_gobj = GObj_Create(0xBU, 3U, 0U);
    HSD_GObjObject_80390A70(light_gobj, (u8) HSD_GObj_LightKind,
                            fn_80180630_LoadLightList(state));
    GObj_SetupGXLink(light_gobj, HSD_GObj_LObjCallback, 0xAU, 0U);

    *cam_gobj = fn_80180630_CreateCameraGObj();
}

inline u8 fn_80180630_GetX118(const struct lbl_80472D28_t* state)
{
    return state->x118;
}

void fn_80180630(int arg0, int arg1, int arg2, bool arg3,
                 lbl_8046B6A0_24C_t* arg4)
{
    s32 sp64;
    s32 sp60;
    int special_score_value;
    int coin_count;
    u16 coins;
    HSD_Archive* archive;
    HSD_GObj* cam_gobj;
    lbl_8046B6A0_t* temp;
    s32 total;
    s32 var_r4;
    union {
        struct lbl_80472D28_t* state;
        fn_8017FA1C_arg* model;
    } data;
    s32 special_score;
    s32 var_r3;
    struct lbl_80472D28_t* state;
    u8 mask;
    u8 var_r0;

    special_score = 0;
    coins = arg4->x58[0].xE;
    state = (data.state = &lbl_80472D28);
    memzero(state, sizeof(*state));
    state->xD4 = -1;
    state->xD8 = 0;
    state->xE0 = -1;
    state->xE4 = 0;
    state->xEC = -1;
    state->xF4 = -1;
    state->x100 = -1;
    state->x11E = 1;
    state->x11F = 1;
    state->x108 = 0x64;
    state->x10A = 0x64;
    state->x114 = (u8) arg3;

    switch (arg2) {
    case 1: {
        s32* first = &sp60;
        Ground_801C1DE4(first, &sp64);
        state->x11A = 1;
        state->x11C = (u8) (sp64 - sp60);
        state->x108 = 0xC8;
        if (sp60 == 0) {
            state->x11B = 1;
        }
        break;
    }
    case 3:
        temp = gm_16AE_GetUnkData_0();
        state->x118 = 1;
        if (temp->match_result == OUTCOME_UNK_1P_BONUS_STAGE_END) {
            grPushOn_80219204(Ground_801C1DD4(), &special_score_value,
                              &coin_count);
            special_score = special_score_value;
            /* Keep the 64-bit round trip for register allocation. */
            coins = (s32) (s64) coin_count;
            state->x108 = 0x1F4;
        }
        break;
    case 2:
        state->x119 = 1;
        break;
    }

    {
        struct lbl_8046B6A0_24C_t* tmp = gm_8016B774();
        fn_8016F344(tmp);
    }

    if (state->x11A == 0 && state->x118 == 0 && state->x119 == 0 &&
        (mask = fn_8017F008(), fn_8016F9A8(gm_8016B774(), 0, mask, 0) != 0))
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    state->x117 = var_r0;

    if (state->x117 != 0) {
        state->xC8 = 0;
    } else {
        state->xC8 = 1;
    }

    if (state->x118 == 0) {
        state->xD0 = fn_8017F09C();
        state->xDC = fn_8017F14C(arg4);
    }

    if (state->x117 != 0) {
        state->xE8 = fn_8017F1B8();
    }

    state->xF0 = state->xE8 + (state->xDC + state->xD0 + special_score);
    state->xFC = arg0 + arg1;
    state->xCC = arg1;

    total = arg0 + state->xCC + state->xF0;
    var_r4 = total;
    if (total > 999999999) {
        var_r4 = 999999999;
    } else if (var_r4 < 0) {
        var_r4 = 0;
    }
    state->x104 = var_r4;
    lbl_804D65C0 = (var_r4 - (arg0 + arg1)) / 10;

    PAD_STACK(0x18);
    {
        void* scene_data;

        archive = lbArchive_80016DBC("GmRegClr", &scene_data,
                                     "ScGamRegClear_scene_data", 0);
        state->x48 = archive;
        if (scene_data == NULL) {
            OSReport("Error : Cannot open archive file (File Name : %s).",
                     "GmRegClr");
        }
        fn_80168A6C(scene_data, fn_80180630_GetModelDesc(state), 0);
    }

    fn_80180630_CreateLightAndCamera(state, &cam_gobj);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_CameraKind,
                            fn_80180630_LoadCameraDesc(state));
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 8U);
    cam_gobj->gxlink_prios = 0x4C00;

    fn_80180630_SetupSisLib(cam_gobj);

    fn_801803FC(data.model);
    fn_80168F7C();

    if (HSD_Randi(2) != 0) {
        var_r3 = 0xA;
    } else {
        var_r3 = 0xB;
    }
    lbAudioAx_80023F28(var_r3);

    Camera_8002F7AC(0);
    lb_800121FC(&state->x30, 0x280, 0x1E0, GX_TF_RGB5A3, 0);
    state->x2C =
        lb_800138EC(&state->x30, NULL, 2U, 0x32, 0.0f, 0.0f, 1.0f, 1.0f);
    lb_800138D8(state->x2C, 1);
    lb_800138CC(state->x2C, fn_8017FE54);

    if (gm_GetRules()->x1_1 && coins != 0) {
        if (fn_80180630_GetX118(state) == 0U) {
            un_802FF128(0x5A, 0x1AE, (s32) coins, 5);
        } else {
            un_802FF128(0x86, 0xC8, (s32) coins, 5);
        }
    }

    arg4->x58[0].xE = coins;
    fn_8017F2A4(&state->x84, 264.0f, 211.0f);
    PAD_STACK(0x18);
}

int fn_80180AC0(void)
{
    if (lbl_80472D28.x116 == 1) {
        return 1;
    }
    return 0;
}

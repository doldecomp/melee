#include "gmregclear.h"

#include "gm_17C0.h"
#include "gm_17C9.h"
#include "platform.h"

#include "baselib/forward.h"

#include "dolphin/pad.h"

#include "gm/forward.h"

#include <math_ppc.h>
#include <dolphin/gx.h>
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
#include <sysdolphin/baselib/util.h>
#include <melee/cm/camera.h>
#include <melee/db/db.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_16AE.h>
#include <melee/gm/gm_16F1.h>
#include <melee/gm/gm_17AD.h>
#include <melee/gm/gm_17BA.h>
#include <melee/gm/gm_1832.h>
#include <melee/gm/gm_19EF.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/gm_1A7A.h>
#include <melee/gm/gm_1ADD.h>
#include <melee/gm/gm_1AED.h>
#include <melee/gm/gm_1B03.h>
#include <melee/gm/gm_1BA8.h>
#include <melee/gm/gm_1BFA.h>
#include <melee/gm/gmadventure.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmregcommon.h>
#include <melee/gm/gmtoulib.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/gr/grpushon.h>
#include <melee/gr/stage.h>
#include <melee/if/ifcoget.h>
#include <melee/if/ifnametag.h>
#include <melee/if/ifstatus.h>
#include <melee/if/ifstock.h>
#include <melee/if/iftime.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/lb/lbtime.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>
#include <melee/ty/toy.h>

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

struct lbl_80472E48_t {
    /* 0x00 */ u8 b76 : 2, b54 : 2, b32 : 2, b10 : 2;
    /* 0x01 */ char pad_1[3];
    /* 0x04 */ s32 unk_4; /* inferred */
    /* 0x08 */ s32 unk_8; /* inferred */
    /* 0x0C */ u32 xC;
    /* 0x10 */ u8 x10;
    /* 0x11 */ char pad_11[3];
    /* 0x14 */ s32 x14[0x1B];
}; /* size = 0x80 */
STATIC_ASSERT(sizeof(struct lbl_80472E48_t) == 0x80);

typedef struct RegClearEv {
    /* 0x00 */ char pad_0[0x1C];
    /* 0x1C */ HSD_ImageDesc* x1C;
    /* 0x20 */ f32 x20;
} RegClearEv;

static struct lbl_80472D28_t lbl_80472D28;
static struct lbl_80472E48_t lbl_80472E48;
static int lbl_80472EC8[4];
typedef struct RegClearSpawnEntry {
    /* 0x00 */ s32 x0;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
    /* 0x07 */ u8 x7;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
} RegClearSpawnEntry;

typedef struct RegClearRecordState {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 x2;
    /* 0x04 */ int x4;
    /* 0x08 */ int x8;
    /* 0x0C */ int xC;
    /* 0x10 */ s8 x10;
    /* 0x11 */ u8 x11;
    /* 0x12 */ u8 pad_12[2];
} RegClearRecordState;
STATIC_ASSERT(sizeof(RegClearRecordState) == 0x14);

typedef struct RegClearRecordOverlay {
    u8 pad_0[0x6BC];
    RegClearRecordState record;
} RegClearRecordOverlay;

typedef struct lbl_80472ED8_t {
    /* 0x000 */ s32 x0;
    /* 0x004 */ s32 x4;
    /* 0x008 */ s32 x8;
    /* 0x00C */ PlayerInitData xC;
    /* 0x030 */ u8 pad_30[0x24];
    /* 0x054 */ RegClearSpawnEntry x54[101];
    /* 0x6A4 */ RegClearSpawnEntry* x6A4;
    /* 0x6A8 */ RegClearSpawnEntry* x6A8;
    /* 0x6AC */ RegClearSpawnEntry* x6AC;
    /* 0x6B0 */ RegClearSpawnEntry* x6B0;
    /* 0x6B4 */ RegClearSpawnEntry* x6B4;
    /* 0x6B8 */ RegClearSpawnEntry* x6B8;
    /* 0x6BC */ RegClearRecordState record[0];
} lbl_80472ED8_t;
STATIC_ASSERT(sizeof(lbl_80472ED8_t) == 0x6BC);

lbl_80472ED8_t lbl_80472ED8;

u16 lbl_803D8B88[] = { 0x18, 0x16, 0x12, 0x3, 0x5, 0x4, 0x6, 0x1a, 0x19, 0x7 };

static char gmRegClearArchiveName[] = "GmRegClr";
static char gmRegClearSceneData[] = "ScGamRegClear_scene_data";
static char gmRegClearArchiveError[] =
    "Error : Cannot open archive file (File Name : %s).";
static char gmRegClearDecisionUsd[] = "SdDec.usd";
static char gmRegClearDecisionData[] = "SIS_DecisionData";
static char gmRegClearDecisionDat[] = "SdDec.dat";
static char gmRegClearShortBlank[] = "          ";
static char gmRegClearLongBlank[] = "               ";
static char gmRegClearGObjError[] =
    "Error : gobj don\'t get (gmRegClearAddModel)\n";
static char gmRegClearFilename[] = "gmregclear.c";
static char gmRegClearJObjError[] =
    "Error : jobj don\'t get (gmRegClearAddModel)\n";

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
            p2->x24C8.x0_7)
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

#pragma dont_inline on
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
#pragma dont_inline off

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
        HSD_SisLib_803A62A0(3, gmRegClearDecisionUsd, gmRegClearDecisionData);
    } else {
        HSD_SisLib_803A62A0(3, gmRegClearDecisionDat, gmRegClearDecisionData);
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
        HSD_SisLib_803A6B98(*arg0, x_end, -12.0f + y, gmRegClearShortBlank);
        ptr++;
    }
    return HSD_SisLib_803A6B98(*arg0, x_end, 9.0f + (134.40001f + farg1),
                               gmRegClearLongBlank);
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

extern Vec3 lbl_803B7C18;

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
                (gm->x24C8.x0_7))
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

extern s32 lbl_804D65C0;

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
    struct lbl_80472D28_t* state = &lbl_80472D28;
    s32 result;
    s32 i;
    u8 mask;
    HSD_JObj* sp28;

    jobj = gobj->hsd_obj;
    HSD_JObjAnimAll(gobj->hsd_obj);

    if (state->x118 == 0) {
        fn_8017F608(state);
    }

    result = fn_8017FA1C(state);
    fn_8017FBA4(state);

    if (state->x117 != 0 && state->x110 > 0x29U) {
        state->xC0 = fn_8017F47C(&state->x84, (s32) state->xC0);

        mask = fn_8017F008();
        if (fn_8016F9A8(gm_8016B774(), state->xC0, mask, 0) > 7) {
            state->x11F = 0;
        } else {
            state->x11F = 1;
        }

        mask = fn_8017F008();
        if (fn_8016F870(gm_8016B774(), state->xC0, mask, 0) < 0) {
            state->x11E = 1;
        } else {
            state->x11E = 0;
        }

        if (state->x110 % 30 == 0 && state->xC8 == 0) {
            mask = fn_8017F008();
            if (fn_8016F9A8(gm_8016B774(), state->xC0, mask, 0) > 7) {
                state->xC0 = (u16) (state->xC0 + 1);
            } else {
                state->xC8 = 1;
                state->xC4 = state->x110;
            }
        }

        {
            u64 buttons = gm_GetButtonsTriggered(Player_GetPlayerId(0));
            u64 repeat = gm_801A36C0(Player_GetPlayerId(0));
            if (((repeat | buttons) & 0x20004) | ((repeat | buttons) & 0)) {
                mask = fn_8017F008();
                if (fn_8016F740(gm_8016B774(), state->xC0, mask, 0) > 0) {
                    mask = fn_8017F008();
                    if (fn_8016F9A8(gm_8016B774(), state->xC0, mask, 0) > 7) {
                        mask = fn_8017F008();
                        state->xC0 =
                            fn_8016F740(gm_8016B774(), state->xC0, mask, 0);
                        state->xC8 = 1;
                        state->xC4 = state->x110;
                    }
                }
            } else {
                buttons = gm_GetButtonsTriggered(Player_GetPlayerId(0));
                repeat = gm_801A36C0(Player_GetPlayerId(0));
                if (((repeat | buttons) & 0x10008) | ((repeat | buttons) & 0))
                {
                    mask = fn_8017F008();
                    if (fn_8016F870(gm_8016B774(), state->xC0, mask, 0) >= 0) {
                        mask = fn_8017F008();
                        state->xC0 =
                            fn_8016F870(gm_8016B774(), state->xC0, mask, 0);
                        state->xC8 = 1;
                        state->xC4 = state->x110;
                    }
                }
            }
        }
    }

    if (state->x11A != 0 && state->x110 > 0x14U && state->x11D < state->x11C &&
        (s32) (0.5f * (f32) (state->x110 - 0x14)) > (s32) state->x11D)
    {
        lb_80011E24(jobj, &sp28, state->x11D + 7, -1);
        HSD_JObjClearFlagsAll(sp28, JOBJ_HIDDEN);
        state->x11D = (u8) (state->x11D + 1);
    }

    if (state->x115 == 0 && result != 0) {
        fn_80168F2C(0);
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) == Gm_PKind_Human &&
            (HSD_PadMasterStatus[(u8) Player_GetPlayerId(i)].trigger & 0x100))
        {
            state->xFC = state->x104;
            state->x115 = 1;
            break;
        }
    }

    if (state->x110 > 0x3EU) {
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) == Gm_PKind_Human &&
                (HSD_PadMasterStatus[(u8) Player_GetPlayerId(i)].trigger &
                 0x1000))
            {
                state->xFC = state->x104;
                state->x116 = 1;
                lbAudioAx_80024030(1);
                break;
            }
        }
    }

    if (state->x11E != 0) {
        HSD_JObjSetFlagsAll(state->x20, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(state->x20, JOBJ_HIDDEN);
    }

    if (state->x11F != 0) {
        HSD_JObjSetFlagsAll(state->x24, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(state->x24, JOBJ_HIDDEN);
    }

    if (state->x10C < 1.0f) {
        state->x10C += 0.05f;
    } else {
        state->x10C = 1.0f;
    }

    if (state->x110 + 0x10000 != 0xFFFF) {
        state->x110 = state->x110 + 1;
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
        OSReport(gmRegClearGObjError);
        OSPanic(gmRegClearFilename, 0x42C, "");
    }
    jobj = HSD_JObjLoadJoint(mdl->joint);
    if (jobj == NULL) {
        OSReport(gmRegClearJObjError);
        OSPanic(gmRegClearFilename, 0x432, "");
    }
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
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

static inline void fn_80180630_CheckArchive(HSD_Archive* archive, void* sp38)
{
    struct lbl_80472D28_t* state = &lbl_80472D28;
    state->x48 = archive;
    if (sp38 == NULL) {
        OSReport(gmRegClearArchiveError, gmRegClearArchiveName);
    }
}

static inline HSD_GObj* fn_80180630_CreateCameraGObj(void)
{
    return GObj_Create(0xEU, 0xEU, 0U);
}

static inline void* fn_80180630_LoadLightList(struct lbl_80472D28_t* state)
{
    return lb_80011AC4(state->x5C);
}

static inline void
fn_80180630_CreateLightAndCamera(struct lbl_80472D28_t* state,
                                 HSD_GObj** cam_gobj)
{
    HSD_GObj* light_gobj;

    light_gobj = GObj_Create(0xBU, 3U, 0U);
    HSD_GObjObject_80390A70(light_gobj, (u8) HSD_GObj_804D784A,
                            fn_80180630_LoadLightList(state));
    GObj_SetupGXLink(light_gobj, HSD_GObj_LObjCallback, 0xAU, 0U);

    *cam_gobj = fn_80180630_CreateCameraGObj();
}

void fn_80180630(int arg0, int arg1, int arg2, bool arg3,
                 lbl_8046B6A0_24C_t* arg4)
{
    struct lbl_80472D28_t* state = &lbl_80472D28;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    void* sp38;
    HSD_Archive* archive;
    HSD_GObj* cam_gobj;
    lbl_8046B6A0_t* temp;
    s32 total;
    s32 var_r4;
    s32 special_score;
    s32 var_r3;
    u16 coins;
    u8 mask;
    u8 var_r0;

    special_score = 0;
    coins = arg4->x58[0].xE;
    memzero(state, 0x120);
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
    case 1:
        Ground_801C1DE4(&sp60, &sp64);
        state->x11A = 1;
        state->x11C = (u8) (sp64 - sp60);
        state->x108 = 0xC8;
        if (sp60 == 0) {
            state->x11B = 1;
        }
        break;
    case 3:
        temp = gm_16AE_GetUnkData_0();
        state->x118 = 1;
        if ((u8) temp->match_result == OUTCOME_UNK_1P_BONUS_STAGE_END) {
            grPushOn_80219204(Ground_801C1DD4(), (int*) &sp5C, (int*) &sp58);
            special_score = sp5C;
            coins = (u16) sp58;
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

    total = state->xF0;
    total += state->xCC;
    total = arg0 + total;
    var_r4 = total;
    if (total > 999999999) {
        var_r4 = 999999999;
    } else if (var_r4 < 0) {
        var_r4 = 0;
    }
    state->x104 = var_r4;
    lbl_804D65C0 = (var_r4 - (arg0 + arg1)) / 10;

    archive = lbArchive_80016DBC(gmRegClearArchiveName, &sp38,
                                 gmRegClearSceneData, 0);
    state->x48 = archive;
    if (sp38 == NULL) {
        OSReport(gmRegClearArchiveError, gmRegClearArchiveName);
    }
    fn_80168A6C(sp38, &state->x4C, 0);

    fn_80180630_CreateLightAndCamera(state, &cam_gobj);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B,
                            HSD_CObjLoadDesc(state->x60));
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 8U);
    cam_gobj->gxlink_prios = 0x4C00;

    HSD_SisLib_803A611C(0, cam_gobj, 9U, 0xDU, 0U, 0xEU, 0U, 0x13U);
    if (lbLang_IsSavedLanguageUS() != 0) {
        HSD_SisLib_803A62A0(0, "SdClr.usd", "SIS_ClearData");
    } else {
        HSD_SisLib_803A62A0(0, "SdClr.dat", "SIS_ClearData");
    }

    fn_801803FC(state);
    fn_80168F7C();

    if (HSD_Randi(2) != 0) {
        var_r3 = 0xA;
    } else {
        var_r3 = 0xB;
    }
    lbAudioAx_80023F28(var_r3);

    Camera_8002F7AC(0);
    lb_800121FC(&state->x30, 0x280, 0x1E0, GX_TF_RGB5A3, 0);
    lb_800138EC((s32) &state->x30, NULL, 2U, 0x32, 0.0f, 0.0f, 1.0f, 1.0f);
    lb_800138D8(state->x2C, 1);
    lb_800138CC(state->x2C, fn_8017FE54);

    if (gm_GetRules()->x1_1 && coins != 0) {
        if (state->x118 == 0) {
            un_802FF128(0x5A, 0x1AE, (s32) coins, 5);
        } else {
            un_802FF128(0x86, 0xC8, (s32) coins, 5);
        }
    }

    arg4->x58[0].xE = coins;
    fn_8017F2A4(&state->x84, 264.0f, 211.0f);
    PAD_STACK(0x38);
}

int fn_80180AC0(void)
{
    if (lbl_80472D28.x116 == 1) {
        return 1;
    }
    return 0;
}
s32 gm_80180AE4(void)
{
    return lbl_80472EC8[0] * 0xA;
}

Fighter_GObj* gm_80180AF4(void)
{
    return Player_GetEntity(1);
}

void gm_80180B18(void)
{
    int i;

    for (i = 0; i < 0x1B; i++) {
        u8 idx = gm_CKindToSelKind((u8) i);
        lbl_80472E48.x14[gm_CKindToSelKind((u8) i)] =
            (u32) *gmMainLib_8015D06C(idx) / 10;
    }
}

void gm_80180BA0(void)
{
    int i;

    for (i = 0; i < 0x1B; i++) {
        u8 idx = gm_CKindToSelKind((u8) i);
        *gmMainLib_8015D06C(gm_CKindToSelKind((u8) i)) =
            lbl_80472E48.x14[idx] * 0xA;
    }
}

void fn_80180C14(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;

    if (lbl_80472E48.b10 != 0) {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        HSD_JObjAnimAll(jobj);
    }
}

static s32 lbl_804D65D4;

void fn_80180C60(HSD_GObj* gobj)
{
    typedef struct fn_80180C60_state {
        struct lbl_80472E48_t e48;
        s32 ec8[4];
    } fn_80180C60_state;
    fn_80180C60_state* state = (fn_80180C60_state*) &lbl_80472E48;
    s32 d;
    s32* max_dist;
    s32 dist;
    s32 disp;
    HSD_JObj* jobj;
    u32 b76;

    dist = (s32) (0.1f * Ground_801C57F0(0));
    jobj = gobj->hsd_obj;
    if (dist < 0) {
        dist = 0;
    }

    state->ec8[0] = dist;
    b76 = state->e48.b76;

    if (b76 != 0 && state->e48.b54) {
        ifTime_HideTimers();
        if (state->ec8[0] == state->ec8[1]) {
            state->ec8[3] = state->ec8[3] + 1;
        } else {
            state->ec8[3] = 0;
        }
        if (state->ec8[3] > 0x3C) {
            state->e48.b32 = 1;
            if (dist == 0 && !state->e48.b10) {
                state->e48.b10 = 1;
            }
        }
    } else {
        if (b76 != 0) {
            ifTime_HideTimers();
            if (state->ec8[0] == state->ec8[1]) {
                state->ec8[3] = state->ec8[3] + 1;
            } else {
                state->ec8[3] = 0;
            }
            if (state->ec8[3] > 0x78) {
                state->e48.b32 = 1;
                if (!state->e48.b10) {
                    state->e48.b10 = 1;
                }
            }
        } else if (gm_8016AEEC() == 0 && gm_8016AEFC() == 0x3B) {
            state->e48.b76 = 1;
            ifTime_HideTimers();
            Player_80031790(0);
        }
        if (Ground_801C1DC0() != 0) {
            if (!(state->e48.b76)) {
                state->e48.b76 = 1;
                ifTime_HideTimers();
                Player_80031790(0);
            }
            if (!(state->e48.b54)) {
                state->e48.b54 = 1;
                Player_80031790(0);
            }
            state->ec8[3] = 0;
        }
    }

    if (!(state->e48.b32)) {
        HSD_JObjReqAnimAll(jobj, 0.0f);
    } else if (state->e48.b10) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    } else if (dist > state->e48.x14[gm_CKindToSelKind((u8) state->e48.unk_4)])
    {
        if (lbl_804D65D4 == 0) {
            lbAudioAx_800237A8(0x9C40, 0x7F, 0x40);
            lbAudioAx_800237A8(0x144, 0x7F, 0x40);
            gm_80167858((s32) (s8) state->e48.x10,
                        (s32) Player_GetNametagSlotID(0), 0xD, 0x5A);
            lbl_804D65D4 = 1;
        }
        HSD_JObjClearFlagsAll(
            HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj))),
            JOBJ_HIDDEN);
    }

    d = lbLang_IsSavedLanguageUS() != 0 ? (s32) ((f64) (f32) dist / 0.304788)
                                        : dist;
    disp = d;
    if (d > 0x1869F) {
        disp = 0x1869F;
    }

    /* ones digit */
    HSD_JObjReqAnimAll(HSD_JObjGetNext(HSD_JObjGetNext(
                           HSD_JObjGetChild(HSD_JObjGetChild(jobj)))),
                       (f32) (disp % 10));

    /* tens digit */
    HSD_JObjReqAnimAll(HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                           HSD_JObjGetChild(HSD_JObjGetChild(jobj))))),
                       (f32) ((disp / 10) % 10));

    /* hundreds digit */
    d = disp / 100;
    if (d != 0) {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj)))))),
            (f32) (d % 10));
    } else {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj)))))),
            10.0f);
    }

    /* thousands digit */
    d = disp / 1000;
    if (d != 0) {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj))))))),
            (f32) (d % 10));
    } else {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj))))))),
            10.0f);
    }

    /* ten-thousands digit */
    d = disp / 10000;
    if (d != 0) {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                    HSD_JObjGetChild(HSD_JObjGetChild(jobj)))))))),
            (f32) (d % 10));
    } else {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                    HSD_JObjGetChild(HSD_JObjGetChild(jobj)))))))),
            10.0f);
    }

    HSD_JObjAnimAll(jobj);
    state->ec8[1] = state->ec8[0];
    max_dist = &state->ec8[2];
    if (state->ec8[0] > *max_dist + 0xA) {
        *max_dist = state->ec8[0];
        lbAudioAx_80023870(0xBB, 0x7F, 0x40, 0x8A);
    }
}

extern s32 lbl_804D65D8;

void fn_80181598(void)
{
    typedef struct {
        struct lbl_80472E48_t x0;
        int x80[4];
    } lbl_80472E48_with_ec8;
    lbl_80472E48_with_ec8* state = (lbl_80472E48_with_ec8*) &lbl_80472E48;
    s32* unk_4;
    s32 val;
    s32 idx;
    u32 mode;

    PAD_STACK(0x20);

    if (gm_801A4624() != 0) {
        return;
    }

    mode = state->x0.b10;

    if (mode != 0) {
        if (mode == 1) {
            lbAudioAx_800237A8(0xC0, 0x7F, 0x40);
            lbAudioAx_800237A8(0x148, 0x7F, 0x40);
            state->x0.b10 = 2;
        }
        lbl_804D65D8 += 1;
        if (lbl_804D65D8 >= 0xF0 ||
            (lbl_804D65D8 > 0x3C &&
             (HSD_PadCopyStatus[state->x0.x10].trigger & 0x100)))
        {
            gm_8016B328();
            return;
        }
    }

    if (state->x0.b32 != 0 && ((mode = state->x0.b10, mode == 0) || mode == 3))
    {
        state->x0.xC += 1;
        if (state->x0.xC > 0x3C &&
            (state->x0.xC >= 0xF0 ||
             (HSD_PadCopyStatus[state->x0.x10].trigger & 0x100)))
        {
            unk_4 = &state->x0.unk_4;
            idx = gm_CKindToSelKind((u8) *unk_4);
            val = state->x80[0];
            idx = (u8) idx << 2;
            state = (lbl_80472E48_with_ec8*) state->x0.x14;
            if (val > *(s32*) ((unsigned char*) state + idx)) {
                *(s32*) ((unsigned char*) state +
                         (gm_CKindToSelKind((u8) *unk_4) << 2)) = val;
            }
            gm_8016B328();
        }
    }
}

static DynamicModelDesc** lbl_804D65CC;
static DynamicModelDesc** lbl_804D65D0;
extern HSD_Archive* lbl_804D65C8;

void fn_80181708(void)
{
    HSD_GObj* new_var;
    typedef struct {
        struct lbl_80472E48_t x0;
        int x80[4];
    } lbl_80472E48_with_ec8;
    HSD_JObj* jobj;
    HSD_GObj* gobj;
    lbl_80472E48_with_ec8* state = (lbl_80472E48_with_ec8*) &lbl_80472E48;

    state->x80[0] = 0;
    state->x80[1] = 0;
    state->x80[2] = 0;
    state->x80[3] = 0;
    state->x0.b76 = 0;
    state->x0.b54 = 0;
    state->x0.b32 = 0;
    state->x0.b10 = 0;
    state->x0.xC = 0;
    state->x0.x10 = (s8) Player_GetPlayerId(0);
    lbl_804D65D4 = 0;
    lbl_804D65D8 = 0;

    HSD_GObj_SetupProc(GObj_Create(0xEU, 0x11U, 0U),
                       (void (*)(HSD_GObj*)) fn_80181598, 0x15U);

    gobj = GObj_Create(0xEU, 0xFU, 0U);
    jobj = HSD_JObjLoadJoint((*lbl_804D65CC)->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xBU, 0U);
    HSD_GObj_SetupProc(gobj, fn_80180C14, 0x15U);
    gm_8016895C(jobj, *lbl_804D65CC, 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);

    gobj = (new_var = GObj_Create(0xEU, 0xFU, 0U));
    jobj = HSD_JObjLoadJoint((*lbl_804D65D0)->joint);
    HSD_GObjObject_80390A70(new_var, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(new_var, HSD_GObj_JObjCallback, 0xBU, 0U);
    HSD_GObj_SetupProc(new_var, fn_80180C60, 0x15U);
    gm_8016895C(jobj, *lbl_804D65D0, 0);
    HSD_JObjReqAnimAll(jobj, 10.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    HSD_JObjSetFlagsAll(
        HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj))),
        JOBJ_HIDDEN);
    HSD_JObjClearFlagsAll(HSD_JObjGetNext(HSD_JObjGetNext(
                              HSD_JObjGetChild(HSD_JObjGetChild(jobj)))),
                          JOBJ_HIDDEN);

    gm_80168F88();
}

void gm_80181998(void)
{
    lbl_804D65C8 = lbArchive_80016DBC("IfHrNoCn", &lbl_804D65CC,
                                      "ScInfCnt_scene_models", 0);
    lbl_804D65C8 = lbArchive_80016DBC("IfHrReco", &lbl_804D65D0,
                                      "ScInfCnt_scene_models", 0);
    fn_80181708();
    /// @todo Keep #lbl_80472ED8 before #lbl_80473594 in `.bss`.
    (void) &lbl_80472ED8;
}

void gm_80181A00(s32 arg0, s32 arg1)
{
    lbl_80472E48.unk_4 = arg0;
    lbl_80472E48.unk_8 = arg1;
}

struct {
    u8 x0;
    u16 x2;
    int x4;
    int x8;
    int xC;
    int x10;
} lbl_80473594;

int gm_80181A14(void)
{
    return lbl_80473594.x0;
}

u32 gm_80181A24(void)
{
    return lbl_80473594.x2;
}

s32 gm_80181A34(void)
{
    return lbl_80473594.x4;
}

typedef struct {
    /* 0x00 */ u32 scores[27];
    /* 0x6C */ u8 icons[28];
    /* 0x88 */ u16 times[28];
} RecordBlock; /* 0xC0 */

static RecordBlock lbl_803D8D08[6] = {
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
};

void gm_80181A44(int c_kind, int arg1, bool arg2)
{
    RecordBlock* base = lbl_803D8D08;

    switch (arg1) {
    case 0x21:
        base[0].icons[c_kind] = arg2;
        break;
    case 0x22:
        base[1].icons[c_kind] = arg2;
        break;
    case 0x23:
        base[2].icons[c_kind] = arg2;
        break;
    case 0x24:
        base[3].icons[c_kind] = arg2;
        break;
    case 0x25:
        base[4].icons[c_kind] = arg2;
        break;
    case 0x26:
        base[5].icons[c_kind] = arg2;
        break;
    }
}

void gm_80181AC8(int c_kind, int arg1, u16 arg2)
{
    RecordBlock* base = lbl_803D8D08;

    switch (arg1) {
    case 0x21:
        base[0].times[c_kind] = arg2;
        break;
    case 0x22:
        base[1].times[c_kind] = arg2;
        break;
    case 0x23:
        base[2].times[c_kind] = arg2;
        break;
    case 0x24:
        base[3].times[c_kind] = arg2;
        break;
    case 0x25:
        base[4].times[c_kind] = arg2;
        break;
    case 0x26:
        base[5].times[c_kind] = arg2;
        break;
    }
}

void gm_80181B64(int c_kind, int arg1, s32 arg2)
{
    RecordBlock* base = lbl_803D8D08;

    switch (arg1) {
    case 0x21:
        base[0].scores[c_kind] = arg2;
        break;
    case 0x22:
        base[1].scores[c_kind] = arg2;
        break;
    case 0x23:
        base[2].scores[c_kind] = arg2;
        break;
    case 0x24:
        base[3].scores[c_kind] = arg2;
        break;
    case 0x25:
        base[4].scores[c_kind] = arg2;
        break;
    case 0x26:
        base[5].scores[c_kind] = arg2;
        break;
    }
}

#pragma dont_inline on
int fn_80181BFC(int* arg0)
{
    int i;
    int count = 0;

    for (i = 1; i < 6; i++) {
        if (Player_GetFalls(i) == 0 &&
            Player_GetPlayerSlotType(i) != Gm_PKind_NA)
        {
            count += 1;
        } else if (arg0 != NULL) {
            *arg0 = i;
        }
    }
    return count;
}
#pragma dont_inline reset

static inline s32 fn_80181C80_CountPlayers(volatile s32* out)
{
    s32 i;
    s32 count = 0;

    for (i = 1; i < 6; i++) {
        if (Player_GetFalls(i) == 0 &&
            Player_GetPlayerSlotType(i) != Gm_PKind_NA)
        {
            count++;
        } else {
            *out = i;
        }
    }
    return count;
}

void fn_80181C80(s32 arg0)
{
    lbl_80472ED8_t* data = &lbl_80472ED8;
    s32 count;
    volatile s32 sp38;
    volatile s32 sp3C;
    PlayerInitData sp10;

    gm_GetCurrentGameMode();
    sp10 = data->xC;
    count = fn_80181C80_CountPlayers(&sp38);

    if (data->x54[arg0].x4 > count && data->x8 > 0x5A) {
        if (Player_GetPlayerSlotType(sp38) != Gm_PKind_NA) {
            Player_SetFalls(sp38, 0);
            Player_SetSuicideCount(sp38, 0);
            fn_8016EF98(sp38);
        }
        data->x54[arg0].x0 = -2;
        sp10.team = !Player_GetTeam(0);
        sp10.c_kind = data->x54[arg0].x5;
        sp10.cpu_level = data->x54[arg0].x6;
        sp10.xE = data->x54[arg0].x7;
        sp10.x18 = data->x54[arg0].x8;
        sp10.x1C = data->x54[arg0].xC;
        gm_8016EDDC(sp38, &sp10);
        Player_SetNametagSlotID(sp38, 0x78);
        un_802FD28C(sp38);
        data->x0++;
    }
}

static inline s32 fn_80181E18_ComputeRemaining100(s32 count)
{
    return 0x64 - (count + lbl_80472ED8.x4);
}

void fn_80181E18(void)
{
    s32 entry_idx;
    s32 next;
    s32 temp;
    s32 count;
    s32 i;
    s32 mode = gm_GetCurrentGameMode();

    if (lbl_80472ED8.x8 <= 0x5A) {
        lbl_80472ED8.x8 += 1;
    }

    switch (mode) {
    case 0x21:
    case 0x22:
        Player_GetFalls(0);
        break;
    case 0x23:
    case 0x24:
        if (gm_8016AEEC() == 0 && gm_8016AEFC() == 0x3B) {
            lbl_80473594.x0 = 1;
            gm_8016B33C(7);
            gm_8016B328();
        }
        break;
    case 0x25:
    case 0x26:
        if (Player_GetFalls(0) != 0) {
            gm_8016B33C(5);
            gm_8016B328();
        }
        break;
    }

    for (entry_idx = 0; entry_idx < 101; entry_idx++) {
        if (lbl_80472ED8.x54[entry_idx].x0 == -2) {
            continue;
        }

        switch (lbl_80473594.x8) {
        case 0x21:
        case 0x22:
            lbl_80473594.x4 = gm_8016AEDC();
            break;
        }

        temp = entry_idx - fn_80181BFC(NULL);
        if (temp < 0) {
            temp = 0;
        }
        lbl_80473594.x2 = (s16) (temp + lbl_80472ED8.x4);

        switch (mode) {
        case 0x21:
            temp = entry_idx - fn_80181BFC(NULL);
            if (temp < 0) {
                temp = 0;
            }
            ifStock_802FA2D0(0xA - (temp + lbl_80472ED8.x4));
            break;
        case 0x22:
            temp = entry_idx - fn_80181BFC(NULL);
            if (temp < 0) {
                temp = 0;
            }
            ifStock_802FA2D0(fn_80181E18_ComputeRemaining100(temp));
            break;
        default:
            temp = entry_idx - fn_80181BFC(NULL);
            if (temp < 0) {
                temp = 0;
            }
            ifStock_802FA2D0(temp + lbl_80472ED8.x4);
            break;
        }

        next = lbl_80472ED8.x54[entry_idx].x0;

        if (next == -1) {
            fn_80181C80(entry_idx);
            return;
        }

        if (next == 0x3E7) {
            count = 0;
            for (i = 1; i < 6; i++) {
                if (Player_GetFalls(i) == 0 &&
                    Player_GetPlayerSlotType(i) != Gm_PKind_NA)
                {
                    count += 1;
                }
            }
            if (count == 0) {
                lbl_80473594.x0 = 1;
                gm_8016B33C(7);
                gm_8016B328();
            }
        } else {
            s32 k;
            for (k = next; k < entry_idx; k++) {
                lbl_80472ED8.x54[k].x0 = -1;
                lbl_80472ED8.x4 += 1;
            }
            fn_80181C80(lbl_80472ED8.x54[entry_idx].x0);
            temp = entry_idx - fn_80181BFC(NULL);
            if (temp < 0) {
                temp = 0;
            }
            ifStock_802FA2D0(temp + lbl_80472ED8.x4);
        }
        break;
    }
    PAD_STACK(16);
}

void gm_80182174(void)
{
    s32 i;
    RegClearSpawnEntry* src;
    RegClearSpawnEntry* dst;
    RegClearSpawnEntry** spawn_table_22;
    RegClearSpawnEntry** spawn_table_23;
    RegClearSpawnEntry** spawn_table_24;
    RegClearSpawnEntry** spawn_table_25;
    RegClearSpawnEntry** spawn_table_26;
    s32 mode;

    mode = gm_GetCurrentGameMode();
    spawn_table_25 = &lbl_80472ED8.x6B4;
    spawn_table_22 = &lbl_80472ED8.x6A8;
    spawn_table_23 = &lbl_80472ED8.x6AC;
    spawn_table_26 = &lbl_80472ED8.x6B8;
    spawn_table_24 = &lbl_80472ED8.x6B0;

    lbArchive_80016DBC(
        "GmKumite.dat", &lbl_80472ED8.x6A4, "gmKumiteSystemTable10man",
        spawn_table_22, "gmKumiteSystemTable100man", spawn_table_23,
        "gmKumiteSystemTable10min", spawn_table_24, "gmKumiteSystemTable60min",
        spawn_table_25, "gmKumiteSystemTableEndless", spawn_table_26,
        "gmKumiteSystemTableMercilessly", 0);

    lbl_80472ED8.x0 = 0;
    lbl_80472ED8.x4 = 0;
    lbl_80472ED8.x8 = 0;

    gm_8016795C(&lbl_80472ED8.xC);

    ((volatile lbl_80472ED8_t*) &lbl_80472ED8)->xC.c_kind = 0x1B;
    ((volatile lbl_80472ED8_t*) &lbl_80472ED8)->xC.slot_type = 1;
    ((volatile lbl_80472ED8_t*) &lbl_80472ED8)->xC.stocks = 1;
    ((volatile lbl_80472ED8_t*) &lbl_80472ED8)->xC.xD_b4 = 1;

    switch (mode) {
    case 0x21:
        src = ((volatile lbl_80472ED8_t*) &lbl_80472ED8)->x6A4;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    case 0x22:
        src = *spawn_table_22;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    case 0x23:
        src = *spawn_table_23;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    case 0x24:
        src = *spawn_table_24;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    case 0x25:
        src = *spawn_table_25;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    case 0x26:
        src = *spawn_table_26;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    }

    lbl_80472ED8.record[0].x10 = Player_GetPlayerId(0);
    lbl_80472ED8.record[0].x11 = Player_GetNametagSlotID(0);
    HSD_GObj_SetupProc(GObj_Create(0xFU, 0x11U, 0U),
                       (HSD_GObjEvent) fn_80181E18, 0x15U);
    gm_80168F88();
    PAD_STACK(8);
}

bool gm_IsMultimanSmashMode(void)
{
    switch (gm_GetCurrentGameMode()) {
    case GM_10MAN_VS:
    case GM_100MAN_VS:
    case GM_3MIN_VS:
    case GM_15MIN_VS:
    case GM_ENDLESS_VS:
    case GM_CRUEL_VS:
        return true;
    }
    return false;
}

/// @todo Original addresses these fields relative to #lbl_80472ED8 (reference
/// relocations are lbl_80472ED8+0x6BC..+0x6C8): lbl_80473594 overlays
/// lbl_80472ED8+0x6BC (0x80472ED8 + 0x6BC == 0x80473594), and gm_80182578
/// below already reads the same storage via lbl_80472ED8.record[0].
void gm_80182554(int arg0, int arg1)
{
    typedef struct {
        u8 pad_0[0x6BC];
        u8 x6BC;
        u8 pad_6BD;
        u16 x6BE;
        int x6C0;
        int x6C4;
        int x6C8;
    } regclear_record_state;
    regclear_record_state* s = (regclear_record_state*) &lbl_80472ED8;

    s->x6C8 = arg0;
    s->x6C4 = arg1;
    s->x6BC = 0;
    s->x6C0 = 0;
    s->x6BE = 0;
}

static inline u16 gm_80182578_GetTime(void)
{
    return lbl_80472ED8.record[0].x2;
}

static inline int gm_80182578_GetRecordTime(RecordBlock* blocks, int idx,
                                            int mode)
{
    switch (mode) {
    case 33:
        return blocks[0].times[idx];
    case 34:
        return blocks[1].times[idx];
    case 35:
        return blocks[2].times[idx];
    case 36:
        return blocks[3].times[idx];
    case 37:
        return blocks[4].times[idx];
    case 38:
        return blocks[5].times[idx];
    default:
        return 0;
    }
}

static inline u32 gm_80182578_GetRecordScore(RecordBlock* blocks, int idx,
                                             int mode)
{
    switch (mode) {
    case 33:
        return blocks[0].scores[idx];
    case 34:
        return blocks[1].scores[idx];
    case 35:
        return blocks[2].scores[idx];
    case 36:
        return blocks[3].scores[idx];
    case 37:
        return blocks[4].scores[idx];
    case 38:
        return blocks[5].scores[idx];
    default:
        return 0;
    }
}

s32 gm_80182578(void)
{
    RecordBlock* blocks = lbl_803D8D08;
    int time_val;
    int idx;
    s32 mode;
    u32 score_val;

    mode = lbl_80472ED8.record[0].x8;
    idx = lbl_80472ED8.record[0].xC;
    time_val = gm_80182578_GetRecordTime(blocks, idx, mode);

    score_val = gm_80182578_GetRecordScore(blocks, idx, mode);

    switch (mode) {
    case 0x21:
    case 0x22:
        if (mode == 0x21) {
            mode = gmMainLib_8015D6BC(gm_CKindToSelKind((u8) idx));
        } else {
            mode = gmMainLib_8015D710(gm_CKindToSelKind((u8) idx));
        }
        if ((u8) lbl_80472ED8.record[0].x0 != 0) {
            u32 score_store = (u32) lbl_80472ED8.record[0].x4;
            if (score_store < score_val) {
                int i = lbl_80472ED8.record[0].xC;
                int m = lbl_80472ED8.record[0].x8;
                switch (m) {
                case 33:
                    blocks[0].icons[i] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                case 34:
                    blocks[1].icons[i] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                case 35:
                    blocks[2].icons[i] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                case 36:
                    blocks[3].icons[i] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                case 37:
                    blocks[4].icons[i] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                case 38:
                    blocks[5].icons[i] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                }
                switch (m) {
                case 33:
                    blocks[0].scores[i] = score_store;
                    break;
                case 34:
                    blocks[1].scores[i] = score_store;
                    break;
                case 35:
                    blocks[2].scores[i] = score_store;
                    break;
                case 36:
                    blocks[3].scores[i] = score_store;
                    break;
                case 37:
                    blocks[4].scores[i] = score_store;
                    break;
                case 38:
                    blocks[5].scores[i] = score_store;
                    break;
                }
                {
                    u16 time_store = lbl_80472ED8.record[0].x2;
                    switch (m) {
                    case 33:
                        blocks[0].times[i] = time_store;
                        break;
                    case 34:
                        blocks[1].times[i] = time_store;
                        break;
                    case 35:
                        blocks[2].times[i] = time_store;
                        break;
                    case 36:
                        blocks[3].times[i] = time_store;
                        break;
                    case 37:
                        blocks[4].times[i] = time_store;
                        break;
                    case 38:
                        blocks[5].times[i] = time_store;
                        break;
                    }
                }
            }
            return mode;
        }
        if ((s32) lbl_80472ED8.record[0].x2 > (s32) time_val && mode == 0) {
            int i = lbl_80472ED8.record[0].xC;
            int m = lbl_80472ED8.record[0].x8;
            switch (m) {
            case 33:
                blocks[0].times[i] = (u16) lbl_80472ED8.record[0].x2;
                break;
            case 34:
                blocks[1].times[i] = (u16) lbl_80472ED8.record[0].x2;
                break;
            case 35:
                blocks[2].times[i] = (u16) lbl_80472ED8.record[0].x2;
                break;
            case 36:
                blocks[3].times[i] = (u16) lbl_80472ED8.record[0].x2;
                break;
            case 37:
                blocks[4].times[i] = (u16) lbl_80472ED8.record[0].x2;
                break;
            case 38:
                blocks[5].times[i] = (u16) lbl_80472ED8.record[0].x2;
                break;
            }
        }
        break;
    case 0x23:
    case 0x24:
        if ((u8) lbl_80472ED8.record[0].x0 != 0) {
            u16 time_store = gm_80182578_GetTime();
            if ((s32) time_store > (s32) time_val) {
                switch (mode) {
                case 33:
                    blocks[0].icons[idx] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                case 34:
                    blocks[1].icons[idx] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                case 35:
                    blocks[2].icons[idx] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                case 36:
                    blocks[3].icons[idx] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                case 37:
                    blocks[4].icons[idx] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                case 38:
                    blocks[5].icons[idx] = (u8) lbl_80472ED8.record[0].x0;
                    break;
                }
                switch (mode) {
                case 33:
                    blocks[0].times[idx] = time_store;
                    break;
                case 34:
                    blocks[1].times[idx] = time_store;
                    break;
                case 35:
                    blocks[2].times[idx] = time_store;
                    break;
                case 36:
                    blocks[3].times[idx] = time_store;
                    break;
                case 37:
                    blocks[4].times[idx] = time_store;
                    break;
                case 38:
                    blocks[5].times[idx] = time_store;
                    break;
                }
            }
        }
        break;
    case 0x25:
    case 0x26:
        if ((s32) lbl_80472ED8.record[0].x2 > (s32) time_val) {
            switch (mode) {
            case 33:
                blocks[0].times[idx] = (u16) lbl_80472ED8.record[0].x2;
                break;
            case 34:
                blocks[1].times[idx] = (u16) lbl_80472ED8.record[0].x2;
                break;
            case 35:
                blocks[2].times[idx] = (u16) lbl_80472ED8.record[0].x2;
                break;
            case 36:
                blocks[3].times[idx] = (u16) lbl_80472ED8.record[0].x2;
                break;
            case 37:
                blocks[4].times[idx] = (u16) lbl_80472ED8.record[0].x2;
                break;
            case 38:
                blocks[5].times[idx] = (u16) lbl_80472ED8.record[0].x2;
                break;
            }
        }
        break;
    }

    return mode;
    PAD_STACK(0x40);
}

static inline RecordBlock* fn_80182B5C_GetRecordBlocks(void)
{
    return lbl_803D8D08;
}

static inline u32 fn_80182B5C_GetScore(RecordBlock* blocks,
                                       RegClearRecordOverlay* data)
{
    int idx = data->record.xC;
    int mode = data->record.x8;

    switch (mode) {
    case 33:
        return blocks[0].scores[idx];
    case 34:
        return blocks[1].scores[idx];
    case 35:
        return blocks[2].scores[idx];
    case 36:
        return blocks[3].scores[idx];
    case 37:
        return blocks[4].scores[idx];
    case 38:
        return blocks[5].scores[idx];
    default:
        return 0;
    }
}

static inline int fn_80182B5C_GetTime(RecordBlock* blocks,
                                      RegClearRecordOverlay* data)
{
    int idx = data->record.xC;
    int mode = data->record.x8;

    switch (mode) {
    case 33:
        return blocks[0].times[idx];
    case 34:
        return blocks[1].times[idx];
    case 35:
        return blocks[2].times[idx];
    case 36:
        return blocks[3].times[idx];
    case 37:
        return blocks[4].times[idx];
    case 38:
        return blocks[5].times[idx];
    default:
        return 0;
    }
}

void fn_80182B5C(void)
{
    RegClearRecordOverlay* data = (RegClearRecordOverlay*) &lbl_80472ED8;
    RecordBlock* blocks = fn_80182B5C_GetRecordBlocks();
    int time;
    int idx = data->record.xC;
    u32 score;
    int mode = data->record.x8;

    time = fn_80182B5C_GetTime(blocks, data);
    score = fn_80182B5C_GetScore(blocks, data);

    switch (mode) {
    case 0x21:
    case 0x22:
        if (mode == 0x21) {
            gmMainLib_8015D6BC(gm_CKindToSelKind((u8) idx));
        } else {
            gmMainLib_8015D710(gm_CKindToSelKind((u8) idx));
        }
        if (data->record.x0 != 0) {
            if ((u32) data->record.x4 < score) {
                gm_8016B350(0x9C40);
                gm_8016B364(0x144);
                gm_80167858((s32) data->record.x10, (s32) data->record.x11,
                            0xD, 0x5A);
            }
        } else {
            gm_8016B364(0x148);
            gm_8016B378(0x28);
        }
        break;
    case 0x23:
    case 0x24:
        if (data->record.x0 != 0 && (s32) data->record.x2 > time) {
            gm_8016B350(0x9C40);
            gm_8016B364(0x144);
            gm_80167858((s32) data->record.x10, (s32) data->record.x11, 0xD,
                        0x5A);
        }
        break;
    case 0x25:
    case 0x26:
        if ((s32) data->record.x2 > time) {
            gm_8016B350(0x9C40);
            gm_8016B364(0x144);
            gm_80167858((s32) data->record.x10, (s32) data->record.x11, 0xD,
                        0x5A);
        }
        break;
    }
}

static UnkMultimanData lbl_804D65E0;

UnkMultimanData* gm_80182DF0(int c_kind, int arg1)
{
    UnkMultimanData* result = &lbl_804D65E0;
    RecordBlock* base = lbl_803D8D08;

    switch (arg1) {
    case 33:
        result->x0_0 = base[0].icons[c_kind];
        result->x2 = base[0].times[c_kind];
        result->x4 = base[0].scores[c_kind];
        break;
    case 34:
        result->x0_0 = base[1].icons[c_kind];
        result->x2 = base[1].times[c_kind];
        result->x4 = base[1].scores[c_kind];
        break;
    case 35:
        result->x0_0 = base[2].icons[c_kind];
        result->x2 = base[2].times[c_kind];
        break;
    case 36:
        result->x0_0 = base[3].icons[c_kind];
        result->x2 = base[3].times[c_kind];
        break;
    case 37:
        result->x0_0 = base[4].icons[c_kind];
        result->x2 = base[4].times[c_kind];
        break;
    case 38:
        result->x0_0 = base[5].icons[c_kind];
        result->x2 = base[5].times[c_kind];
        break;
    }
    return result;
}

extern u8 lbl_804D65E8;

void fn_80182F40(HSD_GObj* unused)
{
    int i;
    int temp_r31;
    int temp_r31_2;

    if (gm_GetButtonsTriggered(PAD_ALL_CONTROLLERS) &
        (HSD_PAD_START | HSD_PAD_A))
    {
        lbAudioAx_80024C84();
        lbAudioAx_80023694();
        lbAudioAx_80024030(1);
        gm_801A4B60();
        gm_SetPendingGameMode(GM_TITLE);
        gm_SetNewGameModePending();
        return;
    }
    if (gm_801A4BA8() >= 0x4B0) {
        lbAudioAx_80024C84();
        lbAudioAx_80023694();
        if (gm_GetCurrentSceneIndex() == 3 && gmMainLib_8015DB00() % 2 == 0) {
            gmMainLib_8015DB18();
            gm_SetPendingSceneIndex(0);
        }
        gm_801A4B60();
        return;
    }
    switch (lbl_804D65E8) {
    case 0:
        if (gm_801A4BA8() == 0x190) {
            lbl_804D65E8 = 1;
            temp_r31 = gm_801BF6D8();
            Camera_8002EEC8(60.0F);
            Camera_8002E6FC(temp_r31);
            Camera_8002ED9C(30.0F);
            Camera_8002EC7C(0.017453292F * (HSD_Randi(0x47) - 0x23));
            Camera_8002EB5C(0.017453292F * HSD_Randi(0x10));
            for (i = 0; i < 4; i++) {
                if (i != gm_801BF6D8()) {
                    Player_SetPlayerAndEntityCpuLevel(i, 2);
                }
                Player_SetMoreFlagsBit4(i, 1);
            }
        }
        break;
    case 1:
        if (gm_801A4BA8() == 0x280 || Player_800368F8(gm_801BF6D8()) == 0) {
            lbl_804D65E8 = 2;
            temp_r31_2 = gm_801BF6F8();
            Camera_8002EEC8(60.0F);
            Camera_8002E6FC(temp_r31_2);
            Camera_8002ED9C(30.0F);
            Camera_8002EC7C(0.017453292F * (HSD_Randi(0x47) - 0x23));
            Camera_8002EB5C(0.017453292F * HSD_Randi(0x10));
            Player_SetPlayerAndEntityCpuLevel(gm_801BF6F8(), 9);
            for (i = 0; i < 4; i++) {
                if (i != gm_801BF6F8()) {
                    Player_SetPlayerAndEntityCpuLevel(i, 2);
                }
            }
        }
        break;
    case 2:
        if (gm_801A4BA8() == 0x370 || Player_800368F8(gm_801BF6F8()) == 0) {
            Camera_SetModeToStandard();
            for (i = 0; i < 4; i++) {
                Player_SetPlayerAndEntityCpuLevel(i, 9);
                Player_SetMoreFlagsBit4(i, 0);
            }
        }
        break;
    case 3:
        break;
    }
}

void gm_80183218(void)
{
    lbl_804D65E8 = 0;
    HSD_GObj_SetupProc(GObj_Create(0xF, 0x11, 0), fn_80182F40, 0x15);
}

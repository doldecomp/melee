#include "gmtoulib.h"

#include "gm_1601.h"
#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmtoulib.h"

#include "gmtoulib.static.h"

#include "types.h"

#include <placeholder.h>

#include "baselib/fog.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"

#include "ft/forward.h"

#include "lb/lb_00F9.h"
#include "lb/lblanguage.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"
#include "mn/mnstagesel.h"

#include "pl/forward.h"

#include "pl/player.h"
#include "sc/types.h"

#include <printf.h>
#include <dolphin/os.h>
#include <baselib/controller.h>
#include <baselib/dobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/mobj.h>
#include <baselib/particle.h>
#include <baselib/random.h>
#include <baselib/sislib.h>

extern SceneDesc* lbl_804D666C;
extern SceneDesc* lbl_804D6670;
extern SceneDesc* lbl_804D6674;
extern u8 lbl_804D6680[8];
extern char* lbl_804DA6B4;
extern char* lbl_804DA6B8;
extern char* lbl_804DA6BC;
extern char* lbl_804DA6C0;
extern char* lbl_804DA6C8;
extern char* lbl_804DA6CC;
extern char* lbl_804DA6D0;
static s32 lbl_804D6630;
static s32 lbl_804D6634;
extern struct lbl_803B7C80_t {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} lbl_803B7C80;
typedef struct CamDesc {
    s32 d[14];
} CamDesc;
extern CamDesc lbl_803B7CA8;

typedef struct BracketEntrySlot {
    /* 0x00 */ HSD_GObj* x2C;
    /* 0x04 */ u8 x30;
    /* 0x05 */ u8 pad31;
    /* 0x06 */ u8 x32;
    /* 0x07 */ u8 pad33;
    /* 0x08 */ s32 x34;
    /* 0x0C */ s32 x38;
    /* 0x10 */ s32 x3C;
    /* 0x14 */ s32 x40;
    /* 0x18 */ s32 x44;
    /* 0x1C */ s32 x48;
    /* 0x20 */ u8 x4C;
    /* 0x21 */ u8 x4D;
    /* 0x22 */ u8 x4E;
    /* 0x23 */ u8 x4F;
    /* 0x24 */ u8 x50;
    /* 0x25 */ u8 x51;
    /* 0x26 */ u8 x52;
    /* 0x27 */ u8 pad53;
    /* 0x28 */ u16 x54;
    /* 0x2A */ u8 pad56[0x2C - 0x2A];
} BracketEntrySlot;
STATIC_ASSERT(sizeof(BracketEntrySlot) == 0x2C);

static inline BracketEntrySlot* BracketEntry_GetSlot(BracketEntry* entry,
                                                     s32 slot_idx)
{
    return &((BracketEntrySlot*) &entry->x2C)[slot_idx];
}

void fn_8018A514(int count, float val)
{
    BracketEntry* entries = lbl_80473AB8;
    s32 region;
    BracketSrcEntry* src;
    int i;
    s32 n;

    if (count < 9) {
        region = 0;
    } else if (count >= 14) {
        region = 2;
    } else {
        region = 1;
    }

    src = ((BracketSrcEntry**) ((u8*) entries + 0x3700))[region];

    if (count < 9) {
        for (i = 0; i < count; i++) {
            src += lbl_803D9D20.x0[i + 0x20];
        }
    } else if (count < 14) {
        for (i = 9; i < count; i++) {
            src += lbl_803D9D20.x0[i + 0x20];
        }
    } else {
        for (i = 14; i < count; i++) {
            src += lbl_803D9D20.x0[i + 0x20];
        }
    }

    n = lbl_803D9D20.x0[count + 0x20];

    for (i = 0; i < n; i++) {
        entries[i].x0 = src->x0;
        entries[i].x1 = src->x1;
        entries[i].x2 = src->x2;
        entries[i].x3 = src->x3;
        entries[i].x4 = src->x4;
        entries[i].x5 = src->x5;
        entries[i].x6 = src->x6;
        entries[i].x1C = val;
        entries[i].xC = src->x8;
        entries[i].x14 = src->xC;
        entries[i].x10 = src->x10;
        entries[i].x18 = src->x14;
        entries[i].x20.r = src->x18;
        entries[i].x20.g = src->x1A;
        entries[i].x20.b = src->x1C;
        entries[i].x20.a = src->x1E;
        entries[i].x24 = src->x19;
        entries[i].x25 = src->x1B;
        entries[i].x26 = src->x1D;
        entries[i].x27 = src->x1F;
        entries[i].x28 = src->x20;
        entries[i].x52 = 9;
        entries[i].x32 = 0;
        entries[i].x7E = 9;
        entries[i].x5E = 0;
        entries[i].xAA = 9;
        entries[i].x8A = 0;
        entries[i].xD6 = 9;
        entries[i].xB6 = 0;
        entries[i].x30 = src->x21;
        entries[i].x5C = src->x22;
        entries[i].x88 = src->x23;
        entries[i].xB4 = src->x24;
        src++;
    }

    if (region == 0) {
        if (count == 1) {
            entries[5].x5E = 1;
        } else if (count == 3) {
            entries[10].x32 = 1;
            entries[11].x5E = 1;
        } else if (count == 5) {
            entries[23].x5E = 1;
        } else if (count == 7) {
            entries[46].x5E = 1;
            entries[47].x5E = 1;
        }
    }
    PAD_STACK(24);
}

void fn_8018A970(int arg0)
{
    int i;
    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x0 != 0) {
            HSD_GObj* gobj = GObj_Create(0xE, 0x1B, 0);
            gobj->user_data = &lbl_80473AB8[i];
            if (i == 0) {
                HSD_GObj_SetupProc(gobj, fn_8018B090, 0);
            }
            GObj_SetupGXLink(gobj, fn_8018E46C, 4, 1);
        }
    }

    if (arg0 < 9) {
        if (arg0 == 1) {
            lbl_80473AB8[5].x5E = 1;
        } else if (arg0 == 3) {
            lbl_80473AB8[10].x32 = 1;
            lbl_80473AB8[11].x5E = 1;
        } else if (arg0 == 5) {
            lbl_80473AB8[23].x5E = 1;
        } else if (arg0 == 7) {
            lbl_80473AB8[46].x5E = 1;
            lbl_80473AB8[47].x5E = 1;
        }
    }
}

void fn_8018AA74(HSD_JObj* jobj, s32 entry_idx, s32 slot_idx)
{
    BracketEntry* entries = lbl_80473AB8;
    BracketEntry* entry;
    u8* sub;
    s32* p34;
    s32* p3C;
    s32* p44;
    s32* p38;
    s32* p40;
    s32* p48;
    u8* px3;
    u8 x3;

    TmData* tm = gm_8018F634();

    entry = &entries[entry_idx];
    sub = (u8*) entry + slot_idx * (s32) 0x2C;

    p34 = (s32*) (sub + 0x34);
    p3C = (s32*) (sub + 0x3C);
    p44 = (s32*) (sub + 0x44);
    p38 = (s32*) (sub + 0x38);
    p40 = (s32*) (sub + 0x40);
    p48 = (s32*) (sub + 0x48);

    if (entry->x1 != 0) {
        px3 = &entry->x3;
        x3 = *px3;
        if (x3 == 0 && entry->x4 != 0) {
            switch (entry->x4) {
            case 1: {
                s32 xC = entry->xC;
                s32* pX18 = &entry->x18;
                s32* pX10 = &entry->x10;
                *p3C = xC;
                *p44 = xC;
                *p34 = xC;
                {
                    s32 x18 = entry->x18;
                    s32 x10 = *pX10;
                    s32 val = x10 + x18 - slot_idx * x18;
                    *p40 = val;
                    *p48 = val;
                    *p38 = val;
                }
                *p40 = *pX10 + *pX18 / 2;
                break;
            }
            case 2:
                switch (slot_idx) {
                case 0: {
                    s32 xC = entry->xC;
                    s32* pX10 = &entry->x10;
                    s32 val1 = xC + 0x2B;
                    *p3C = val1;
                    *p44 = val1;
                    *p34 = val1;
                    {
                        s32 x10 = entry->x10;
                        s32 x18 = entry->x18;
                        s32 val2 = x10 + x18;
                        *p40 = val2;
                        *p48 = val2;
                        *p38 = val2;
                    }
                    *p40 = *pX10 + entry->x18 / 2;
                    break;
                }
                case 1: {
                    s32 xC = entry->xC;
                    s32 x14 = entry->x14;
                    s32* pX10 = &entry->x10;
                    s32* pX18 = &entry->x18;
                    s32 val1 = xC + x14;
                    *p3C = val1;
                    *p44 = val1;
                    *p34 = val1;
                    {
                        s32 x10 = entry->x10;
                        s32 x18 = *pX18;
                        s32 val2 = x10 + x18;
                        *p40 = val2;
                        *p48 = val2;
                        *p38 = val2;
                    }
                    *p40 = *pX10 + *pX18 / 2;
                    break;
                }
                default: {
                    BracketEntry* ep = &entries[entry_idx];
                    s32 x14 = ep->x14;
                    s32 xC = ep->xC;
                    s32 val1 = xC + x14 / 2;
                    *p3C = val1;
                    *p44 = val1;
                    *p34 = val1;
                    {
                        s32 x10 = ep->x10;
                        *p40 = x10;
                        *p48 = x10;
                        *p38 = x10;
                    }
                    *p40 = ep->x10 + ep->x18 / 2;
                    break;
                }
                }
                break;
            case 3:
                switch (slot_idx) {
                case 0: {
                    s32 xC = entry->xC;
                    s32* pX10 = &entry->x10;
                    s32* pX18 = &entry->x18;
                    *p3C = xC;
                    *p44 = xC;
                    *p34 = xC;
                    {
                        s32 x10 = entry->x10;
                        s32 x18 = *pX18;
                        s32 val = x10 + x18;
                        *p40 = val;
                        *p48 = val;
                        *p38 = val;
                    }
                    *p40 = *pX10 + *pX18 - *pX18 / 3;
                    break;
                }
                case 1: {
                    s32 xC = entry->xC;
                    s32 x14 = entry->x14;
                    s32* pX10 = &entry->x10;
                    s32* pX18 = &entry->x18;
                    s32 val1 = xC + x14;
                    *p3C = val1;
                    *p44 = val1;
                    *p34 = val1;
                    {
                        s32 x10 = entry->x10;
                        s32 x18 = *pX18;
                        s32 val = x10 + x18;
                        *p40 = val;
                        *p48 = val;
                        *p38 = val;
                    }
                    *p40 = *pX10 + *pX18 - *pX18 / 3;
                    break;
                }
                case 2: {
                    s32 xC = entry->xC;
                    *p3C = xC;
                    *p44 = xC;
                    *p34 = xC;
                    {
                        s32 x10 = entry->x10;
                        *p40 = x10;
                        *p48 = x10;
                        *p38 = x10;
                    }
                    *p40 = entry->x10 + entry->x18 / 3;
                    break;
                }
                default: {
                    BracketEntry* ep = &entries[entry_idx];
                    s32 xC = ep->xC;
                    s32 x14 = ep->x14;
                    s32 val1 = xC + x14;
                    *p3C = val1;
                    *p44 = val1;
                    *p34 = val1;
                    {
                        s32 x10 = ep->x10;
                        *p40 = x10;
                        *p48 = x10;
                        *p38 = x10;
                    }
                    *p40 = ep->x10 + ep->x18 / 3;
                    break;
                }
                }
                break;
            }
        } else {
            BracketEntry* ep = &entries[entry_idx];
            s32 x14 = ep->x14;
            s32* pX18 = &ep->x18;
            s32 xC = ep->xC;
            s32 val1 = xC + slot_idx * (x14 / (s32) x3);
            *p3C = val1;
            *p44 = val1;
            *p34 = val1;
            {
                s32 x18 = ep->x18;
                u8 x2 = ep->x2;
                s32 x10 = ep->x10;
                s32 val2 = x10 + x18 - x18 * x2;
                *p40 = val2;
                *p48 = val2;
                *p38 = val2;
            }
            *p40 = ep->x10 + *pX18 * ep->x2;

            if (*px3 == 1) {
                u8 tm_x2E = tm->x2E;
                if (tm_x2E == 6) {
                    if (entry_idx == 5 && slot_idx == 1) {
                        s32 tmp = *p48 + 0x46;
                        *p48 = tmp;
                        *p38 = tmp;
                    }
                } else if (tm_x2E == 0xC) {
                    if ((entry_idx == 0xA && slot_idx == 0) ||
                        (entry_idx == 0xB && slot_idx == 1))
                    {
                        s32 tmp = *p48 + 0x3C;
                        *p48 = tmp;
                        *p38 = tmp;
                    }
                } else if (tm_x2E == 0x18) {
                    if (entry_idx == 0x17 && slot_idx == 1) {
                        s32 tmp = *p48 + 0x28;
                        *p48 = tmp;
                        *p38 = tmp;
                    }
                } else if (tm_x2E == 0x30) {
                    if (entry_idx == 0x2E && slot_idx == 1) {
                        s32 tmp = *p48 + 0x1E;
                        *p48 = tmp;
                        *p38 = tmp;
                    } else if (entry_idx == 0x2F && slot_idx == 1) {
                        s32 tmp = *p48 - 0x1E;
                        *p48 = tmp;
                        *p38 = tmp;
                    }
                }
            }
        }
    }

    HSD_JObjSetTranslateX(jobj, (f32) *p44);
    HSD_JObjSetTranslateY(jobj, -(f32) *p48);
}

void fn_8018B090(HSD_GObj* arg0)
{
    TmData* tm = gm_8018F634();
    s32 var_r24 = 0;
    s32 idx = fn_8018F74C();
    BracketEntry* base;
    u8* bb;
    f32* cam;
    u8* p;
    s32 i;

    switch (tm->cur_option) {
    case 20:
        lbl_804D6630 = 0;
        return;
    case 21:
        base = &lbl_80473AB8[idx];
        bb = (u8*) base;
        if (base->x18 != 0) {
            p = bb;
            for (i = 0; i < 4; i++, p += 0x2C) {
                if (p[0x30] != 0) {
                    HSD_JObj* jobj = (*(HSD_GObj**) (p + 0x2C))->hsd_obj;
                    if (bb[2] != 0) {
                        HSD_JObjSetTranslateY(jobj,
                                              -((f32) * (s32*) (p + 0x48) -
                                                (0.3f * (f32) lbl_804D6630)));
                    } else {
                        s8 t0 = bb[4];
                        if (t0 != 1) {
                            if (t0 >= 1 && t0 < 4) {
                                if (i <= 1) {
                                    HSD_JObjSetTranslateY(
                                        jobj, -((0.3f * (f32) lbl_804D6630) +
                                                (f32) * (s32*) (p + 0x48)));
                                } else {
                                    HSD_JObjSetTranslateY(
                                        jobj, -((f32) * (s32*) (p + 0x48) -
                                                (0.3f * (f32) lbl_804D6630)));
                                }
                            } else {
                                HSD_JObjSetTranslateY(
                                    jobj, -((0.3f * (f32) lbl_804D6630) +
                                            (f32) * (s32*) (p + 0x48)));
                            }
                        } else if (i == 0) {
                            HSD_JObjSetTranslateY(
                                jobj, -((0.3f * (f32) lbl_804D6630) +
                                        (f32) * (s32*) (p + 0x48)));
                        } else {
                            HSD_JObjSetTranslateY(
                                jobj, -((f32) * (s32*) (p + 0x48) -
                                        (0.3f * (f32) lbl_804D6630)));
                        }
                    }
                }
            }
        }
        lbl_804D6630 += 1;
        return;
    case 22:
        base = &lbl_80473AB8[idx];
        cam = (f32*) ((u8*) &lbl_803D9D20 + 0x8C);
        if (base->x18 != 0) {
            f32 d;
            cam[0] = 320.0f;
            cam[1] = -240.0f;
            cam[2] = 0.0f;
            cam[3] = (f32) (base->xC + (base->x14 / 2));
            cam[4] = -(f32) (base->x10 + (base->x18 / 2));
            cam[5] = -150.0f;
            d = 0.033333f * (cam[3] - cam[0]);
            if (d < 0.0f) {
                d = -d;
            }
            cam[6] = 1.0f + d;
            d = 0.033333f * (cam[4] - cam[1]);
            if (d < 0.0f) {
                d = -d;
            }
            cam[7] = 1.0f + d;
            d = 0.033333f * (cam[5] - cam[2]);
            if (d < 0.0f) {
                d = -d;
            }
            cam[8] = 1.0f + d;
        }
        lbl_804D6630 = 0;
        /* fallthrough */
    case 23:
        base = &lbl_80473AB8[idx];
        bb = (u8*) base;
        cam = (f32*) ((u8*) &lbl_803D9D20 + 0x8C);
        if (base->x18 != 0) {
            s32 t5 = lbl_804D6630 / 6;
            s32 t3 = t5 >> 0x1F;
            lbl_804D6630 += 1;
            if (mn_8022F410(&cam[0], &cam[3], cam[6]) < 0) {
                mn_8022F410(&cam[0], &cam[3], cam[6]);
            } else {
                mn_8022F410(&cam[0], &cam[3], cam[6]);
            }
            if (mn_8022F410(&cam[1], &cam[4], cam[7]) < 0) {
                mn_8022F410(&cam[1], &cam[4], cam[7]);
            } else {
                mn_8022F410(&cam[1], &cam[4], cam[7]);
            }
            if (mn_8022F410(&cam[2], &cam[5], cam[8]) < 0) {
                mn_8022F410(&cam[2], &cam[5], cam[8]);
            } else {
                mn_8022F410(&cam[2], &cam[5], cam[8]);
            }
            fn_80190520(cam[0], cam[1], cam[2]);
            if (base->x4 != 1) {
                p = bb;
                for (i = 0; i < 4; i++, p += 0x2C) {
                    if (p[0x30] != 0) {
                        HSD_JObj* jobj = (*(HSD_GObj**) (p + 0x2C))->hsd_obj;
                        mn_8022F470((int*) (p + 0x48), (int*) (p + 0x40),
                                    t5 + t3);
                        HSD_JObjSetTranslateY(jobj,
                                              -(f32) * (s32*) (p + 0x48));
                    }
                }
                return;
            }
            if (bb[0x30] != 0) {
                *(s32*) (bb + 0x40) = *(s32*) (bb + 0x48);
            }
            if (bb[0x5C] != 0) {
                *(s32*) (bb + 0x6C) = *(s32*) (bb + 0x74);
            }
            if (bb[0x88] != 0) {
                *(s32*) (bb + 0x58 + 0x40) = *(s32*) (bb + 0x58 + 0x48);
            }
            if (bb[0x58 + 0x5C] != 0) {
                *(s32*) (bb + 0x84 + 0x40) = *(s32*) (bb + 0x84 + 0x48);
                return;
            }
        }
        return;
    case 24:
        base = &lbl_80473AB8[idx];
        bb = (u8*) base;
        if (base->x18 != 0) {
            s32 sp[10];
            sp[0] = lbl_803B7C80.unk0;
            sp[1] = lbl_803B7C80.unk4;
            sp[2] = lbl_803B7C80.unk8;
            sp[3] = lbl_803B7C80.unkC;
            sp[4] = lbl_803B7C80.unk10;
            sp[5] = lbl_803B7C80.unk14;
            sp[6] = lbl_803B7C80.unk18;
            sp[7] = lbl_803B7C80.unk1C;
            sp[8] = lbl_803B7C80.unk20;
            sp[9] = lbl_803B7C80.unk24;
            lbl_804D6630 += 1;
            p = bb;
            for (i = 0; i < 4; i++, p += 0x2C) {
                if (p[0x30] != 0) {
                    HSD_JObj* jobj = (*(HSD_GObj**) (p + 0x2C))->hsd_obj;
                    if (bb[2] != 0) {
                        HSD_JObjSetTranslateY(
                            jobj, -((f32) * (s32*) (p + 0x40) -
                                    (0.1f * (f32) sp[lbl_804D6630 % 10])));
                    } else {
                        s8 t0 = bb[4];
                        if (t0 != 1) {
                            if (t0 >= 1 && t0 < 4) {
                                if (i <= 1) {
                                    HSD_JObjSetTranslateY(
                                        jobj, -((0.1f *
                                                 (f32) sp[lbl_804D6630 % 10]) +
                                                (f32) * (s32*) (p + 0x40)));
                                } else {
                                    HSD_JObjSetTranslateY(
                                        jobj,
                                        -((f32) * (s32*) (p + 0x40) -
                                          (0.1f *
                                           (f32) sp[lbl_804D6630 % 10])));
                                }
                            } else {
                                HSD_JObjSetTranslateY(
                                    jobj,
                                    -((0.1f * (f32) sp[lbl_804D6630 % 10]) +
                                      (f32) * (s32*) (p + 0x40)));
                            }
                        } else if (i == 0) {
                            HSD_JObjSetTranslateY(
                                jobj, -((0.1f * (f32) sp[lbl_804D6630 % 10]) +
                                        (f32) * (s32*) (p + 0x40)));
                        } else {
                            HSD_JObjSetTranslateY(
                                jobj, -((f32) * (s32*) (p + 0x40) -
                                        (0.1f * (f32) sp[lbl_804D6630 % 10])));
                        }
                    }
                }
            }
            return;
        }
        return;
    case 25:
        base = &lbl_80473AB8[idx];
        bb = (u8*) base;
        if (bb[0x30] != 0) {
            *(s32*) (bb + 0x48) = *(s32*) (bb + 0x40);
        }
        if (bb[0x5C] != 0) {
            *(s32*) (bb + 0x74) = *(s32*) (bb + 0x6C);
        }
        if (bb[0x88] != 0) {
            *(s32*) (bb + 0x58 + 0x48) = *(s32*) (bb + 0x58 + 0x40);
        }
        if (bb[0x58 + 0x5C] != 0) {
            *(s32*) (bb + 0x84 + 0x48) = *(s32*) (bb + 0x84 + 0x40);
            return;
        }
        return;
    case 32:
        base = &lbl_80473AB8[idx];
        bb = (u8*) base;
        if (base->x18 != 0) {
            fn_80190520((f32) (base->xC + (base->x14 / 2)),
                        -(f32) (base->x10 + (base->x18 / 2)), -150.0f);
            if (bb[0x4C] == 0) {
                *(s32*) (bb + 0x3C) = base->xC + (base->x14 / 2);
            } else {
                s32 t = *(s32*) (bb + 0x40);
                *(s32*) (bb + 0x40) = *(s32*) (bb + 0x38);
                *(s32*) (bb + 0x38) = t;
            }
            if (bb[0x78] == 0) {
                *(s32*) (bb + 0x68) = base->xC + (base->x14 / 2);
            } else {
                s32 t = *(s32*) (bb + 0x6C);
                *(s32*) (bb + 0x6C) = *(s32*) (bb + 0x64);
                *(s32*) (bb + 0x64) = t;
            }
            if (bb[0x58 + 0x78] == 0) {
                *(s32*) (bb + 0x58 + 0x3C) = base->xC + (base->x14 / 2);
            } else {
                s32 t = *(s32*) (bb + 0x58 + 0x40);
                *(s32*) (bb + 0x58 + 0x40) = *(s32*) (bb + 0x58 + 0x38);
                *(s32*) (bb + 0x58 + 0x38) = t;
            }
            if (bb[0x84 + 0x78] == 0) {
                *(s32*) (bb + 0x84 + 0x3C) = base->xC + (base->x14 / 2);
            } else {
                s32 t = *(s32*) (bb + 0x84 + 0x40);
                *(s32*) (bb + 0x84 + 0x40) = *(s32*) (bb + 0x84 + 0x38);
                *(s32*) (bb + 0x84 + 0x38) = t;
            }
        } else {
            fn_801904D0();
        }
        tm->cur_option = 0x21;
        return;
    case 33:
        base = &lbl_80473AB8[idx];
        bb = (u8*) base;
        if (base->x18 != 0) {
            p = bb;
            for (i = 0; i < 4; i++, p += 0x2C) {
                if (p[0x30] == 0) {
                    var_r24 += 1;
                } else {
                    s32 t5 = *(s32*) (p + 0x4C);
                    if (t5 == 0) {
                        lbl_804D6634 = i;
                        if (base->x4 != 1) {
                            HSD_JObj* jobj =
                                (*(HSD_GObj**) (p + 0x2C))->hsd_obj;
                            s32 v;
                            mn_8022F470((int*) (p + 0x44), (int*) (p + 0x3C),
                                        2);
                            v = *(s32*) (p + 0x44);
                            if (v == *(s32*) (p + 0x3C)) {
                                var_r24 += 1;
                            }
                            HSD_JObjSetTranslateX(jobj, (f32) v);
                        } else {
                            var_r24 += 1;
                        }
                    } else {
                        HSD_JObj* jobj = (*(HSD_GObj**) (p + 0x2C))->hsd_obj;
                        s32 v;
                        mn_8022F470((int*) (p + 0x48), (int*) (p + 0x40),
                                    t5 + ((t5 + 1) / 2));
                        v = *(s32*) (p + 0x48);
                        if (v == *(s32*) (p + 0x40)) {
                            var_r24 += 1;
                        }
                        HSD_JObjSetTranslateY(jobj, -(f32) v);
                    }
                }
            }
            if (var_r24 == 4) {
                u8* w = bb + lbl_804D6634 * 0x2C;
                u8* e = (u8*) &lbl_803D9D20 + tm->entrants * 4;
                *(s32*) (w + 0x3C) = *(s32*) (e + 0xFC);
                *(s32*) (w + 0x40) = *(s32*) (e + 0xFE);
                tm->cur_option = 0x22;
                return;
            }
        } else {
            tm->cur_option = 0x22;
            return;
        }
        return;
    case 34:
        base = &lbl_80473AB8[idx];
        bb = (u8*) base;
        if (base->x18 != 0) {
            if (tm->x33 == 5) {
                u8* w = bb + lbl_804D6634 * 0x2C;
                HSD_JObj* jobj = (*(HSD_GObj**) (w + 0x2C))->hsd_obj;
                mn_8022F470((int*) (w + 0x44), (int*) (w + 0x3C), 2);
                HSD_JObjSetTranslateX(jobj, (f32) * (s32*) (w + 0x44));
                if (*(s32*) (w + 0x44) == *(s32*) (w + 0x3C)) {
                    tm->cur_option = 0x23;
                    return;
                }
            } else {
                lbl_804D6630 = 0;
                tm->cur_option = 0x24;
                return;
            }
        } else {
            lbl_804D6630 = 0;
            tm->cur_option = 0x24;
            return;
        }
        return;
    case 35:
        base = &lbl_80473AB8[idx];
        bb = (u8*) base;
        if (base->x18 != 0) {
            if (tm->x33 == 5) {
                u8* w = bb + lbl_804D6634 * 0x2C;
                HSD_JObj* jobj = (*(HSD_GObj**) (w + 0x2C))->hsd_obj;
                mn_8022F470((int*) (w + 0x48), (int*) (w + 0x40), 2);
                HSD_JObjSetTranslateY(jobj, -(f32) * (s32*) (w + 0x48));
                if (*(s32*) (w + 0x48) == *(s32*) (w + 0x40)) {
                    tm->x33 = 6;
                    return;
                }
            } else {
                lbl_804D6630 = 0;
                tm->cur_option = 0x24;
                return;
            }
        } else {
            lbl_804D6630 = 0;
            tm->cur_option = 0x24;
            return;
        }
        return;
    case 36:
        base = &lbl_80473AB8[idx];
        cam = (f32*) ((u8*) &lbl_803D9D20 + 0x8C);
        if (base->x18 != 0) {
            f32 d;
            cam[0] = (f32) (base->xC + (base->x14 / 2));
            cam[1] = -(f32) ((base->x18 / 2) + base->x10);
            cam[2] = -150.0f;
            cam[3] = 320.0f;
            cam[4] = -240.0f;
            cam[5] = 0.0f;
            d = 0.04f * (cam[3] - cam[0]);
            if (d < 0.0f) {
                d = -d;
            }
            cam[6] = d;
            d = 0.04f * (cam[4] - cam[1]);
            if (d < 0.0f) {
                d = -d;
            }
            cam[7] = d;
            d = 0.04f * (cam[5] - cam[2]);
            if (d < 0.0f) {
                d = -d;
            }
            cam[8] = d;
        }
        tm->cur_option = 0x25;
        return;
    case 37:
        base = &lbl_80473AB8[idx];
        cam = (f32*) ((u8*) &lbl_803D9D20 + 0x8C);
        if (base->x18 == 0) {
            lbl_804D6630 = 0x78;
        }
        if (lbl_804D6630 < 0x78) {
            lbl_804D6630 += 1;
            mn_8022F410(&cam[0], &cam[3], cam[6]);
            mn_8022F410(&cam[1], &cam[4], cam[7]);
            mn_8022F410(&cam[2], &cam[5], cam[8]);
            fn_80190520(cam[0], cam[1], cam[2]);
            return;
        }
        lbl_804D6630 = 0;
        fn_801904D0();
        tm->cur_option = 0x26;
        return;
    case 38:
        base = &lbl_80473AB8[idx];
        bb = (u8*) base;
        if (base->x18 == 0) {
            lbl_804D6630 = 0x78;
        }
        if (lbl_804D6630 < 0x78) {
            lbl_804D6630 += 1;
            return;
        }
        {
            s32 r = 0;
            BracketEntry* src;
            u8* sb;
            u8* pick;
            if (bb[0x4C] != 0) {
                r = 1;
                if (bb[0x78] != 0) {
                    r = 2;
                    if (bb[0xA4] != 0) {
                        r = 3;
                        if (bb[0x58 + 0x78] != 0) {
                            r = 4;
                        }
                    }
                }
            }
            src = &lbl_80473AB8[fn_8018F74C()];
            sb = (u8*) src;
            sb[1] = 0;
            ((u8*) &lbl_80473AB8[sb[5]] + sb[6] * 0x2C)[0x30] = 1;
            pick = sb + r * 0x2C;
            ((u8*) &lbl_80473AB8[sb[5]] + sb[6] * 0x2C)[0x50] = pick[0x50];
            ((u8*) &lbl_80473AB8[sb[5]] + sb[6] * 0x2C)[0x51] = pick[0x51];
            ((u8*) &lbl_80473AB8[sb[5]] + sb[6] * 0x2C)[0x52] = pick[0x52];
            ((u8*) &lbl_80473AB8[sb[5]] + sb[6] * 0x2C)[0x4D] = pick[0x4D];
            ((u8*) &lbl_80473AB8[sb[5]] + sb[6] * 0x2C)[0x4E] = pick[0x4E];
            ((u8*) &lbl_80473AB8[sb[5]] + sb[6] * 0x2C)[0x4F] = pick[0x4F];
            pick[0x30] = 0;
            pick[0x4E] = 3;
            tm->cur_option = 0x27;
        }
        break;
    }
    PAD_STACK(0x48);
}

/* 3D9EE8 */ static char lbl_803D9EE8[] = {
    131, 81, 131, 88, 131, 103, 32, 48, 48,
};
char* const lbl_804DA6C4 = lbl_803D9EE8;
/* 3D9EF4 */ static char lbl_803D9EF4[] = {
    130, 103, 130, 108, 130, 109, 32, 48, 48,
};
/* 3D9EF4 */ static char lbl_803D9F00[] = {
    130, 98, 130, 111, 130, 116, 32, 48, 48,
};

static GXColor const lbl_804DA67C = { 0xFF, 0xFF, 0, 0xFF };

/// Draws tournament bracket lines for different bracket types (0-3).
void fn_8018C8D4(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                 s32 arg6, f32 farg0)
{
    BracketEntry* data = (BracketEntry*) arg0;
    f32 thickness;
    f32 neg_thickness;
    f32 total_width;
    s32 half, center, right;
    s32 half_h, third_h;
    s32 mid_y, bot_y, two_third_y;
    GXColor c0, c1, c2, c3, c4, c5, c6, c7, c8, c9;
    GXColor c10, c11, c12, c13, c14, c15, c16, c17, c18, c19;
    GXColor c20, c21, c22, c23, c24, c25, c26, c27, c28, c29;
    GXColor c30, c31, c32, c33;

    c0 = lbl_804DA67C;
    thickness = data->x1C;

    switch ((s32) data->x4) {
    case 0:
        c1 = c0;
        DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4, &c1);
        if (data->x20.g == 0) {
            c2 = data->x20;
            DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4, &c2);
        }
        return;

    case 1:
        c3 = c0;
        DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4, &c3);
        if (data->x20.g == 0) {
            if (data->x4C == 0) {
                half_h = arg4 / 2;
                c4 = data->x20;
                DrawRectangle((f32) arg1, (f32) (arg2 + half_h), thickness,
                              (f32) half_h, &c4);
                return;
            }
            c5 = data->x20;
            DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) (arg4 / 2),
                          &c5);
        }
        break;

    case 2:
        half = arg3 / 2;
        center = arg1 + half;
        half_h = arg4 / 2;
        c6 = c0;
        DrawRectangle((f32) center, (f32) arg2, thickness, (f32) half_h, &c6);

        neg_thickness = -thickness;
        mid_y = arg2 + half_h;
        c7 = c0;
        DrawRectangle((f32) (arg1 + 0x2B), (f32) mid_y,
                      ((f32) arg3 + thickness) - 43.0f, neg_thickness, &c7);

        c8 = c0;
        DrawRectangle((f32) (arg1 + 0x2B), (f32) mid_y, thickness,
                      (f32) half_h, &c8);

        right = arg1 + arg3;
        c9 = c0;
        DrawRectangle((f32) right, (f32) mid_y, thickness, (f32) half_h, &c9);

        if (data->x20.g == 0) {
            if (data->x4C == 0) {
                c10 = data->x20;
                DrawRectangle((f32) (arg1 + 0x2B), (f32) mid_y, thickness,
                              (f32) half_h, &c10);
                c11 = data->x20;
                DrawRectangle((f32) (arg1 + 0x2B), (f32) mid_y,
                              (f32) (half - 0x2B), neg_thickness, &c11);
                return;
            }
            if (data->x78 == 0) {
                c12 = data->x20;
                DrawRectangle((f32) right, (f32) mid_y, thickness,
                              (f32) half_h, &c12);
                c13 = data->x20;
                DrawRectangle((f32) center, (f32) mid_y,
                              (f32) half + thickness, neg_thickness, &c13);
                return;
            }
            c14 = data->x20;
            DrawRectangle((f32) center, (f32) arg2, thickness, (f32) half_h,
                          &c14);
        }
        break;

    case 3:
        half = arg3 / 2;
        third_h = arg4 / 3;
        center = arg1 + half;
        mid_y = arg2 + third_h;

        c15 = c0;
        DrawRectangle((f32) center, (f32) mid_y, thickness,
                      (f32) (third_h - 2), &c15);

        c16 = c0;
        DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) third_h, &c16);

        right = arg1 + arg3;
        c17 = c0;
        DrawRectangle((f32) right, (f32) arg2, thickness, (f32) third_h, &c17);

        bot_y = (arg2 + arg4) - third_h;
        c18 = c0;
        DrawRectangle((f32) arg1, (f32) bot_y, thickness, (f32) third_h, &c18);

        c19 = c0;
        DrawRectangle((f32) right, (f32) bot_y, thickness, (f32) third_h,
                      &c19);

        neg_thickness = -thickness;
        total_width = (f32) arg3 + thickness;
        c20 = c0;
        DrawRectangle((f32) arg1, (f32) mid_y, total_width, neg_thickness,
                      &c20);

        c21 = c0;
        DrawRectangle((f32) arg1, (f32) bot_y, total_width, neg_thickness,
                      &c21);

        if (data->x20.g == 0) {
            if (data->x4C == 0) {
                two_third_y = arg2 + ((arg4 * 2) / 3);
                c22 = data->x20;
                DrawRectangle((f32) arg1, (f32) two_third_y, thickness,
                              (f32) third_h, &c22);
                c23 = data->x20;
                DrawRectangle((f32) arg1, (f32) two_third_y, (f32) half,
                              neg_thickness, &c23);
                c24 = data->x20;
                DrawRectangle((f32) center, (f32) (arg2 + (arg4 / 2)),
                              thickness, (f32) ((arg4 / 6) - 1), &c24);
                return;
            }
            if (data->x78 == 0) {
                two_third_y = arg2 + ((arg4 * 2) / 3);
                c25 = data->x20;
                DrawRectangle((f32) right, (f32) two_third_y, thickness,
                              (f32) third_h, &c25);
                c26 = data->x20;
                DrawRectangle((f32) center, (f32) two_third_y, (f32) half,
                              neg_thickness, &c26);
                c27 = data->x20;
                DrawRectangle((f32) center, (f32) (arg2 + (arg4 / 2)),
                              thickness, (f32) ((arg4 / 6) - 1), &c27);
                return;
            }
            if (data->xA4 == 0) {
                c28 = data->x20;
                DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) third_h,
                              &c28);
                c29 = data->x20;
                DrawRectangle((f32) arg1, (f32) mid_y, (f32) half,
                              neg_thickness, &c29);
                c30 = data->x20;
                DrawRectangle((f32) center, (f32) mid_y, thickness,
                              (f32) ((arg4 / 6) - 1), &c30);
                return;
            }
            c31 = data->x20;
            DrawRectangle((f32) right, (f32) arg2, thickness, (f32) third_h,
                          &c31);
            c32 = data->x20;
            DrawRectangle((f32) center, (f32) mid_y, (f32) half, neg_thickness,
                          &c32);
            c33 = data->x20;
            DrawRectangle((f32) center, (f32) mid_y, thickness,
                          (f32) ((arg4 / 6) - 1), &c33);
        }
        break;
    }
}

static GXColor const lbl_804DA684 = { 255, 255, 0, 255 };

/// Draws tournament bracket connector lines with optional tail segments.
void fn_8018D50C(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                 s32 arg6, f32 farg0)
{
    TmData* tm;
    BracketEntry* data = (BracketEntry*) arg0;
    f32 thickness;
    f32 neg_thickness;
    s32 right;
    s32 bottom;
    GXColor c0, c1, c2, c3, c4, c5, c6, c7, c8, c9;
    GXColor c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20;

    tm = gm_8018F634();
    c20 = lbl_804DA684;
    c0 = lbl_804DA684;
    thickness = data->x1C;
    c1 = lbl_804DA684;
    {
        GXColor* color = &c1;
        DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4, color);
    }

    right = arg3 + arg1;
    c2 = c0;
    {
        GXColor* color = &c2;
        DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4, color);
    }

    neg_thickness = -thickness;
    c3 = c0;
    {
        GXColor* color = &c3;
        DrawRectangle((f32) arg1, (f32) arg5, (f32) arg3 + thickness,
                      neg_thickness, color);
    }

    if (data->x20.g == 0) {
        if (data->x4C == 0) {
            c4 = data->x20;
            {
                GXColor* color = &c4;
                DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                              color);
            }
            c5 = data->x20;
            {
                GXColor* color = &c5;
                DrawRectangle((f32) arg1, (f32) arg5,
                              (f32) (arg3 / 2) + thickness, neg_thickness,
                              color);
            }
        } else {
            c6 = data->x20;
            {
                GXColor* color = &c6;
                DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4,
                              color);
            }
            {
                s32 half2 = arg3 / 2;
                c7 = data->x20;
                {
                    GXColor* color = &c7;
                    f32 y = (f32) arg5;
                    DrawRectangle((f32) (arg1 + half2), y,
                                  (f32) half2 + thickness, neg_thickness,
                                  color);
                }
            }
        }
    }

    if (tm->entrants == 1) {
        if (data->x5E != 0) {
            bottom = arg2 + arg4;
            c8 = c0;
            {
                GXColor* color = &c8;
                DrawRectangle((f32) right, (f32) bottom, thickness, -70.0f,
                              color);
            }
            if (data->x20.g == 0 && data->x4C != 0) {
                c9 = data->x20;
                DrawRectangle((f32) right, (f32) bottom, thickness, -70.0f,
                              &c9);
            }
        }
        return;
    } else if (tm->entrants == 3) {
        if (data->x32 != 0) {
            bottom = arg2 + arg4;
            c10 = c0;
            {
                GXColor* color = &c10;
                DrawRectangle((f32) arg1, (f32) bottom, thickness, -60.0f,
                              color);
            }
            if (data->x20.g == 0 && data->x4C == 0) {
                c11 = data->x20;
                DrawRectangle((f32) arg1, (f32) bottom, thickness, -60.0f,
                              &c11);
            }
        } else if (data->x5E != 0) {
            bottom = arg2 + arg4;
            c12 = c0;
            {
                GXColor* color = &c12;
                DrawRectangle((f32) right, (f32) bottom, thickness, -60.0f,
                              color);
            }
            if (data->x20.g == 0 && data->x4C != 0) {
                c13 = data->x20;
                DrawRectangle((f32) right, (f32) bottom, thickness, -60.0f,
                              &c13);
            }
        }
    } else if (tm->entrants == 5) {
        if (data->x5E != 0) {
            bottom = arg2 + arg4;
            c14 = c0;
            {
                GXColor* color = &c14;
                DrawRectangle((f32) right, (f32) bottom, thickness, -40.0f,
                              color);
            }
            if (data->x20.g == 0 && data->x4C != 0) {
                c15 = data->x20;
                DrawRectangle((f32) right, (f32) bottom, thickness, -40.0f,
                              &c15);
            }
        }
    } else if (tm->entrants == 7) {
        if (data->x5E != 0) {
            if (data->x2 == 0) {
                bottom = arg2 + arg4;
                c16 = c0;
                {
                    GXColor* color = &c16;
                    DrawRectangle((f32) right, (f32) bottom, thickness, -30.0f,
                                  color);
                }
                if (data->x20.g == 0 && data->x4C != 0) {
                    c17 = data->x20;
                    {
                        GXColor* color = &c17;
                        DrawRectangle((f32) right, (f32) bottom, thickness,
                                      -30.0f, color);
                    }
                }
            } else {
                bottom = arg2 + 0x1E;
                c18 = c0;
                {
                    GXColor* color = &c18;
                    DrawRectangle((f32) right, (f32) bottom, thickness, -30.0f,
                                  color);
                }
                if (data->x20.g == 0 && data->x4C != 0) {
                    c19 = data->x20;
                    DrawRectangle((f32) right, (f32) bottom, thickness, -30.0f,
                                  &c19);
                }
            }
        }
    }
}

static GXColor const col = { 0xFF, 0xFF, 0x00, 0xFF };

void fn_8018DC18(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                 s32 arg6, f32 farg0)
{
    // TODO: Make arg0 BracketEntry (forward.h? idk how that works)
    BracketEntry* data = (BracketEntry*) arg0;
    f32 thickness;
    f32 neg_thickness;
    s32 right;
    s32 half;
    s32 center;
    GXColor c0, c1, c2, c3, c4, c5, c6, c7, c8;

    c8 = col;
    thickness = data->x1C;
    c1 = col;
    DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4, &c1);

    right = arg1 + arg3;
    c2 = c8;
    DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4, &c2);

    half = arg3 / 2;
    center = arg1 + half;
    c3 = c8;
    DrawRectangle((f32) center, (f32) arg2, thickness, (f32) arg4, &c3);

    neg_thickness = -thickness;
    c4 = c8;
    DrawRectangle((f32) arg1, (f32) arg5, (f32) arg3 + thickness,
                  neg_thickness, &c4);

    if (data->x20.g == 0) {
        if (data->x4C == 0) {
            c5 = data->x20;
            DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4, &c5);
            c6 = data->x20;
            DrawRectangle((f32) arg1, (f32) arg5, (f32) half + thickness,
                          neg_thickness, &c6);
            return;
        }
        if (data->x78 == 0) {
            c7 = data->x20;
            DrawRectangle((f32) center, (f32) arg2, thickness, (f32) arg4,
                          &c7);
            return;
        }
        c0 = data->x20;
        DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4, &c0);
        c8 = data->x20;
        DrawRectangle((f32) center, (f32) arg5, (f32) half + thickness,
                      neg_thickness, &c8);
    }
}

static const GXColor lbl_804DA69C = { 255, 255, 0, 255 };

void fn_8018DF68(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                 s32 arg6, f32 farg0)
{
    BracketEntry* data = (BracketEntry*) arg0;
    GXColor sp58;
    GXColor sp54;
    GXColor sp50;
    GXColor sp4C;
    GXColor sp48;
    GXColor sp44;
    GXColor sp40;
    GXColor sp3C;
    GXColor sp38;
    GXColor sp34;
    GXColor sp30;
    GXColor sp2C;
    GXColor sp28;
    GXColor sp24;
    GXColor sp20;
    f32 thickness;
    f32 neg_thickness;
    s32 right;
    s32 third;
    s32 left_third;
    s32 right_third;
    s32 half;

    sp20 = lbl_804DA69C;
    sp58 = sp20;
    thickness = data->x1C;
    sp54 = sp20;
    DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4, &sp54);

    right = arg1 + arg3;
    sp50 = sp58;
    DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4, &sp50);

    third = arg3 / 3;
    left_third = arg1 + third;
    sp4C = sp58;
    DrawRectangle((f32) left_third, (f32) arg2, thickness, (f32) arg4, &sp4C);

    right_third = right - third;
    sp48 = sp58;
    DrawRectangle((f32) right_third, (f32) arg2, thickness, (f32) arg4, &sp48);

    neg_thickness = -thickness;
    sp44 = sp58;
    DrawRectangle((f32) arg1, (f32) arg5, (f32) arg3 + thickness,
                  neg_thickness, &sp44);

    if (data->x20.g == 0) {
        if (data->x4C == 0) {
            sp40 = data->x20;
            DrawRectangle((f32) arg1, (f32) arg2, thickness, (f32) arg4,
                          &sp40);
            sp3C = data->x20;
            DrawRectangle((f32) arg1, (f32) arg5, (f32) (arg3 / 2) + thickness,
                          neg_thickness, &sp3C);
            return;
        }
        if (data->x78 == 0) {
            sp38 = data->x20;
            DrawRectangle((f32) left_third, (f32) arg2, thickness, (f32) arg4,
                          &sp38);
            sp34 = data->x20;
            DrawRectangle((f32) left_third, (f32) arg5,
                          ((f32) (arg3 / 2) + thickness) - (f32) third,
                          neg_thickness, &sp34);
            return;
        }
        if (data->xA4 == 0) {
            sp30 = data->x20;
            DrawRectangle((f32) right_third, (f32) arg2, thickness, (f32) arg4,
                          &sp30);
            half = arg3 / 2;
            sp2C = data->x20;
            DrawRectangle((f32) (arg1 + half), (f32) arg5,
                          ((f32) half + thickness) - (f32) third,
                          neg_thickness, &sp2C);
            return;
        }
        sp28 = data->x20;
        DrawRectangle((f32) right, (f32) arg2, thickness, (f32) arg4, &sp28);
        half = arg3 / 2;
        sp24 = data->x20;
        DrawRectangle((f32) (arg1 + half), (f32) arg5, (f32) half + thickness,
                      neg_thickness, &sp24);
    }
}

/// @todo Currently 98.8% match - permuter couldn't improve beyond score 140

void fn_8018E46C(HSD_GObj* gobj, int unused)
{
    BracketEntry* data;
    s32 temp;
    int new_var;
    s32 r30;

    data = gobj->user_data;
    data->x3 = data->x3;

    if (data->x2 != 0) {
        temp = -(data->x10 + data->x18);
    } else {
        temp = -data->x10;
    }
    r30 = temp;
    HSD_FogSet(NULL);
    hsd_80391A04(1.0F, 1.0F, 1);
    switch (data->x3) {
    case 0:
        new_var = data->x18;
        fn_8018C8D4(data, data->xC - (s32) (0.5f * data->x1C), -data->x10,
                    data->x14, -new_var, r30, data->xC, 0.5f);
        break;
    case 1:
        new_var = data->x18;
        fn_8018D50C(data, data->xC - (s32) (0.5f * data->x1C), -data->x10,
                    data->x14, -new_var, r30, data->xC, 0.5f);
        break;
    case 2:
        new_var = data->x18;
        fn_8018DC18(data, data->xC - (s32) (0.5f * data->x1C), -data->x10,
                    data->x14, -new_var, r30, data->xC, 0.5f);
        break;
    case 3:
        new_var = data->x18;
        fn_8018DF68(data, data->xC - (s32) (0.5f * data->x1C), -data->x10,
                    data->x14, -new_var, r30, data->xC, 0.5f);
        break;
    }
}

/// Initializes the tournament bracket camera and optionally resets bracket
/// data. Removes all existing GObjs from two entity lists, inits lbl_80473AB8
/// entries, creates camera GObj with CObjDesc loaded from lbl_803B7CA8 rodata.
#pragma push
#pragma auto_inline off
void fn_8018E618(int arg0, f32 farg0, int arg1)
{
    CamDesc cam;
    HSD_GObj* gobj;
    HSD_GObj* tmp;
    s32 i;
    PAD_STACK(16);

    cam = lbl_803B7CA8;

    while ((tmp = M2C_FIELD(HSD_GObj_Entities, HSD_GObj**, 0x6C)) != NULL) {
        HSD_GObjPLink_80390228(tmp);
    }
    while ((tmp = M2C_FIELD(HSD_GObj_Entities, HSD_GObj**, 0x50)) != NULL) {
        HSD_GObjPLink_80390228(tmp);
    }

    for (i = 0; i < 0x40; i++) {
        if (arg1 != 0) {
            lbl_80473AB8[i].x0 = 0;
            lbl_80473AB8[i].x4E = 3;
            lbl_80473AB8[i].x7A = 3;
            lbl_80473AB8[i].xA6 = 3;
            lbl_80473AB8[i].xD2 = 3;
        }
    }

    gobj = GObj_Create(9, 0x14, 1);
    {
        typedef struct CObjData {
            f32 pos[9];
            struct lbl_803D9DD0_t cobj_data;
        } CObjData;
        HSD_CObj* cobj = HSD_CObjLoadDesc((HSD_CObjDesc*) &cam);
        CObjData* cobj_data = (CObjData*) lbl_803D9DAC;
        cobj_data->cobj_data.cobj = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B,
                                cobj_data->cobj_data.cobj);
    }
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 1);
    ((u32*) &gobj->gxlink_prios)[1] = 0x10;
    ((u32*) &gobj->gxlink_prios)[0] = 0;

    if (arg1 != 0) {
        fn_8018A514(arg0, farg0);
    }
    fn_8018A970(arg0);
}
#pragma pop

void fn_8018E85C(DynamicModelDesc* model, s32 flag)
{
    u8* sub;
    BracketEntry* entry;
    TmData* td;
    HSD_JObj* jobj;
    s32 outer_idx;
    s32 inner_idx;
    s32 bracket_idx;
    s32 j;
    u8* ptr;
    HSD_GObj* gobj;
    s32 anim_frame;
    f32 final_pos;
    f32 pos;
    f32 pos_multiplier;

    td = gm_8018F634();
    bracket_idx = 0;
    entry = lbl_80473AB8;

    for (outer_idx = 0; outer_idx < 0x40; outer_idx++) {
        if (entry->x0 == 0) {
            goto next_entry;
        }
        inner_idx = 0;
        sub = (u8*) entry;
        for (; inner_idx < 4; inner_idx++) {
            if (sub[0x30] == 0) {
                goto next_sub;
            }

            if (flag != 0) {
                ptr = (u8*) td;
                for (j = 0; j < 64; j++) {
                    if (ptr[0x44 + j * 0x12] == bracket_idx) {
                        break;
                    }
                }
                sub[0x50] = (u8) j;
                ptr = (u8*) td + j * 0x12;
                sub[0x4D] = ptr[0x3A];
                sub[0x4E] = ptr[0x37];
                sub[0x4F] = ptr[0x3E];
                sub[0x51] = ptr[0x38];
                sub[0x52] = ptr[0x39];
                *(u16*) (sub + 0x54) = *(u16*) (ptr + 0x40);
                bracket_idx++;
            }

            gobj = GObj_Create(0xE, 0x1B, 0);
            *(HSD_GObj**) (sub + 0x2C) = gobj;
            gobj = *(HSD_GObj**) (sub + 0x2C);
            jobj = HSD_JObjLoadJoint(model->joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 2);
            gm_8016895C(jobj, model, 0);

            anim_frame = sub[0x4D] + sub[0x4F] * 0x1E;
            HSD_JObjReqAnimAll(jobj, (f32) anim_frame);
            HSD_JObjAnimAll(jobj);

            if (outer_idx == fn_8018F74C()) {
                pos_multiplier = 10.0f;
            } else {
                pos_multiplier = 7.0f;
            }

            pos = 0.0083f * (f32) (0x40 - (s32) td->x2E) + 1.0f;
            final_pos = pos_multiplier * pos;
            HSD_JObjSetScaleX(jobj, final_pos);

            pos = 0.0083f * (f32) (0x40 - (s32) td->x2E) + 1.0f;
            final_pos = pos_multiplier * pos;
            HSD_JObjSetScaleY(jobj, final_pos);

            if (td->cur_option < 0x1F) {
                fn_8018AA74(jobj, outer_idx, inner_idx);
            } else {
                fn_8018FDC4(jobj, (f32) * (s32*) (sub + 0x44),
                            -(f32) * (s32*) (sub + 0x48), 666.0f);
            }

        next_sub:
            sub += 0x2C;
        }
    next_entry:
        entry++;
    }
}

#pragma push
#pragma auto_inline off
void fn_8018EC48(void)
{
    mn_8022F138(0x19, 0x1C);
    mn_8022F138(0x12, 0x15);
}
#pragma pop

#pragma push
#pragma auto_inline off
void fn_8018EC7C(void)
{
    mn_8022F0F0(0x1B);
    mn_8022F0F0(0x14);
}
#pragma pop

void fn_8018ECA8(s32 char_id, s32 name_type, s32 jobj_idx1, f32 pos_x,
                 f32 pos_y, s32 jobj_idx2)
{
    char* hmn_texts[2];
    char* cpu_texts[2];
    TmData* tm;
    s32 num;

    tm = gm_8018F634();

    hmn_texts[0] = lbl_804DA6B4;
    cpu_texts[0] = lbl_804DA6BC;
    hmn_texts[1] = lbl_804DA6B8;
    cpu_texts[1] = lbl_804DA6C0;

    if (name_type == 0xFF) {
        HSD_SisLib_803A6B98(tm->x518[jobj_idx1], pos_x, pos_y,
                            GetNameText((u8) char_id));
        return;
    }

    if (char_id >= 0x320) {
        if (char_id < 0x384) {
            num = char_id - 0x320;
            if (num >= 10) {
                hmn_texts[!!lbLang_IsSavedLanguageUS()][7] =
                    (s8) (num / 10 + 0x30);
                hmn_texts[!!lbLang_IsSavedLanguageUS()][8] =
                    (s8) (num % 10 + 0x30);
                hmn_texts[!!lbLang_IsSavedLanguageUS()][9] = 0;
            } else {
                hmn_texts[!!lbLang_IsSavedLanguageUS()][7] =
                    (s8) (char_id - 0x2F0);
                hmn_texts[!!lbLang_IsSavedLanguageUS()][8] = 0;
            }
            HSD_SisLib_803A6B98(tm->x518[jobj_idx1], pos_x, pos_y,
                                hmn_texts[!!lbLang_IsSavedLanguageUS()]);
            return;
        }
        if (char_id >= 0x3E7) {
            return;
        }
        num = char_id - 0x384;
        if (num >= 10) {
            cpu_texts[!!lbLang_IsSavedLanguageUS()][7] =
                (s8) (num / 10 + 0x30);
            cpu_texts[!!lbLang_IsSavedLanguageUS()][8] =
                (s8) (num % 10 + 0x30);
            cpu_texts[!!lbLang_IsSavedLanguageUS()][9] = 0;
        } else {
            cpu_texts[!!lbLang_IsSavedLanguageUS()][7] =
                (s8) (char_id - 0x354);
            cpu_texts[!!lbLang_IsSavedLanguageUS()][8] = 0;
        }
        HSD_SisLib_803A6B98(tm->x518[jobj_idx2], pos_x, pos_y,
                            cpu_texts[!!lbLang_IsSavedLanguageUS()]);
        return;
    }

    if (name_type == 0) {
        HSD_SisLib_803A6B98(tm->x518[jobj_idx1], pos_x, pos_y,
                            GetNameText((u8) char_id));
    } else if (name_type == 1) {
        HSD_SisLib_803A6B98(tm->x518[jobj_idx2], pos_x, pos_y,
                            GetNameText((u8) char_id));
    }
}

/// Formats a tournament slot display name into a destination buffer.
void fn_8018F00C(char* dest, s32 slot_id)
{
    char* templates_800[2];
    char* templates_900[2];
    char* tmpl_800;
    char* tmpl_900;

    templates_800[0] = lbl_804DA6C4;
    templates_900[0] = lbl_804DA6CC;
    templates_800[1] = lbl_804DA6C8;
    templates_900[1] = lbl_804DA6D0;

    tmpl_800 = templates_800[!!lbLang_IsSavedLanguageUS()];
    tmpl_900 = templates_900[!!lbLang_IsSavedLanguageUS()];

    if (slot_id >= 0x320) {
        if (slot_id < 0x384) {
            /* Slot IDs 800-899: format as 2-digit number (00-99) */
            s32 diff = slot_id - 0x320;
            if (diff < 10) {
                /* Single digit: write digit + null terminator */
                tmpl_800[7] = (s8) (slot_id - 0x2F0);
                tmpl_800[8] = 0;
            } else {
                /* Double digit: write tens, ones, null terminator */
                tmpl_800[7] = (s8) (diff / 10 + 0x30);
                tmpl_800[8] = (s8) (diff % 10 + 0x30);
                tmpl_800[9] = 0;
            }
            strcpy(dest, tmpl_800);
        } else if (slot_id != 0x3E7) {
            /* Slot IDs 900-998: format as 2-digit number (00-98) */
            s32 diff = slot_id - 0x384;
            if (diff < 10) {
                /* Single digit: write digit + null terminator */
                tmpl_900[7] = (s8) (slot_id - 0x354);
                tmpl_900[8] = 0;
            } else {
                /* Double digit: write tens, ones, null terminator */
                tmpl_900[7] = (s8) (diff / 10 + 0x30);
                tmpl_900[8] = (s8) (diff % 10 + 0x30);
                tmpl_900[9] = 0;
            }
            strcpy(dest, tmpl_900);
        }
    } else {
        /* Slot IDs below 800: use player nametag text */
        strcpy(dest, GetNameText((u8) slot_id));
    }
}

s32 gm_8018F1B0(MatchEnd* me)
{
    TmData* tm;

    tm = gm_8018F634();

    switch (gm_804771C4.match_type) {
    case 0:
        return 1;

    case 1:
        switch (tm->hmn_cpu_count) {
        case 1:
            return 1;

        case 2:
            if (tm->x30 == 3) {
                if (me->n_winners == 3) {
                    return 1;
                }
            } else if (tm->x30 == 4) {
                if (me->n_winners >= 3) {
                    return 1;
                }
            }
            break;

        case 3:
            if (me->n_winners == 4) {
                return 1;
            }
            break;
        }
        break;

    case 2:
        switch (tm->hmn_cpu_count) {
        case 1:
            if (tm->x30 == me->n_winners) {
                return 1;
            }
            break;

        case 2:
            if (tm->x30 == 3) {
                return 1;
            } else if (tm->x30 == 4) {
                if (me->n_winners >= 3) {
                    return 1;
                }
            }
            break;

        case 3:
            return 1;
        }
        break;
    }

    return 0;
}

#pragma push
#pragma auto_inline off
int fn_8018F310(int arg0)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(lbl_803D9D20.x59); i++) {
        if (lbl_803D9D20.x59[i] == arg0) {
            return i;
        }
    }
    return -1;
}
#pragma pop

#pragma push
#pragma auto_inline off
int fn_8018F3BC(s32 arg0)
{
    return lbl_803D9D20.x59[arg0];
}
#pragma pop

#pragma push
#pragma auto_inline off
int fn_8018F3D0(int arg0)
{
    if (arg0 == 0xE || (arg0 >= 0x10 && arg0 <= 0x13) || arg0 == 0xA) {
        return 1;
    }
    if (arg0 <= 0xD) {
        return 0;
    }
    return 2;
}
#pragma pop

/* 3D9F0C */ struct lbl_803D9F0C_t lbl_803D9F0C = { -1, -1, -1 };

int fn_8018F410(void)
{
    int temp_r3;
    int* temp_r30;
    int* temp_r29;

    temp_r30 = &lbl_803D9F0C.x8;
    temp_r29 = &lbl_803D9F0C.x4;
    do {
        temp_r3 = HSD_Randi(0x19);
    } while (lbl_803D9D20.x72[temp_r3] == 0 || lbl_803D9F0C.x0 == temp_r3 ||
             *temp_r29 == temp_r3 || *temp_r30 == temp_r3);
    *temp_r30 = *temp_r29;
    *temp_r29 = lbl_803D9F0C.x0;
    lbl_803D9F0C.x0 = temp_r3;
    return temp_r3;
}

/// #fn_8018F410

#pragma push
#pragma auto_inline off
int fn_8018F4A0(void)
{
    int temp_r3 = mnStageSel_8025BBD4();
    if (!gm_80164430(temp_r3)) {
        printf("This is impossible stage num from mnSelStageRandom() -> stage "
               "%d \n",
               temp_r3);
        __assert("gmtoulib.c", 0x53D, "0");
    }
    return temp_r3;
}
#pragma pop

/// Counts available tournament slots and returns the last found index.
#pragma push
#pragma auto_inline off
s32 fn_8018F508(s32* out_index)
{
    s32 count;
    u8* base_ptr;
    u8* slot_ptr;
    s32 i;

    count = 0;
    base_ptr = (u8*) &lbl_80473AB8[fn_8018F74C()];
    slot_ptr = base_ptr;

    if (slot_ptr[0x0] == 0) {
        return -1;
    }

    for (i = 0; i < 4; i++) {
        if (slot_ptr[0x4E] != 3) {
            if (out_index != NULL) {
                *out_index = i;
            }
            count++;
        }
        slot_ptr += 0x2C;
    }

    return count;
}
#pragma pop

#pragma push
#pragma dont_inline on
char* fn_8018F5F0(void)
{
    if (lbLang_IsSavedLanguageUS()) {
        return "SdTou.usd";
    } else {
        return "SdTou.dat";
    }
}
#pragma pop

/// @todo Maybe static to #gmtou_1
struct TmSettingTable lbl_803D9F80 = {
    0, 74,  0, 74,  0, 77,  0, 75, 0,  75,  0,  77, 0, 80,  0, 78, 0, 79,
    0, 79,  0, 81,  0, 0,   0, 82, 0,  82,  0,  92, 0, 92,  0, 96, 0, 93,
    0, 93,  0, 96,  0, 95,  0, 97, 0,  98,  0,  98, 0, 100, 0, 0,  0, 83,
    0, 111, 0, 111, 0, 111, 0, 88, 0,  101, 0,  0,  2, 3,   0, 2,  0, 1,
    0, 0,   0, 0,   2, 2,   4, 16, 31, 3,   63, 3,  3, 3,   9, 0,
};

/// ???
/// tournament uses the user data as just an int
/// it controls various menu jobj states ie animation state, visibility, etc
#pragma dont_inline on
u32 fn_8018F62C(HSD_GObj* gobj)
{
    return (u32) gobj->user_data;
}
#pragma dont_inline off

#pragma push
#pragma dont_inline on
TmData* gm_8018F634(void)
{
    return &gm_804771C4;
}
#pragma pop

#pragma dont_inline on
u32 fn_8018F640(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A36A0(arg0);
}

u32 fn_8018F674(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A36C0(arg0);
}
#pragma dont_inline off

#pragma push
#pragma auto_inline off
u32 fn_8018F6A8(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A3680((u8) arg0);
}
#pragma pop

#pragma push
#pragma auto_inline off
int fn_8018F6DC(int arg0)
{
    if (arg0 >= 0x13) {
        if (arg0 == 0x1D) {
            return 5;
        }
        return arg0 - 1;
    }
    return arg0;
}
#pragma pop

#pragma push
#pragma auto_inline off
CharacterKind fn_8018F6FC(CSSIconHud arg0)
{
    if (arg0 >= 0x13) {
        if (arg0 == 0x1D) {
            return 5;
        }
        return arg0 + 1;
    }
    return (CharacterKind) arg0;
}
#pragma pop

#pragma push
#pragma auto_inline off
float fn_8018F71C(int arg0, int arg1)
{
    return arg0 + arg1 * 0x1E;
}
#pragma pop

#pragma push
#pragma auto_inline off
int fn_8018F74C(void)
{
    int i;

    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x1 != 0) {
            break;
        }
    }

    return i;
}
#pragma pop

#pragma push
#pragma auto_inline off
int fn_8018F808(void)
{
    int i;
    int noerrcount = 0;
    for (i = 0; i < 4; i++) {
        if (HSD_PadMasterStatus[(u8) i].err == 0) {
            noerrcount += 1;
        }
    }
    return noerrcount;
}
#pragma pop

static inline s32 fn_8018F888_inline0(void)
{
    s32 i;

    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x1 != 0) {
            break;
        }
    }

    return i;
}

#pragma push
#pragma auto_inline off
void fn_8018F888(void)
{
    s32 i = fn_8018F888_inline0();

    lbl_80473AB8[i].x20.g = 0;

    if (gm_804771C4.x33 != 5) {
        return;
    }

    i = fn_8018F888_inline0();

    lbl_80473AB8[i + 1].x20.g = 0;
}
#pragma pop

void fn_8018FA24(void)
{
    u8* ptr;
    u8* dst;
    u8* tmdata;
    s32 player_idx;
    s32 player_count;
    s32 i;
    BracketEntry* entry;
    s32 char_kind;

    PAD_STACK(8);

    tmdata = (u8*) &gm_804771C4 + 0xc;

    entry = lbl_80473AB8;
    for (i = 0; i < 64; entry++, i++) {
        if (entry->x1 != 0) {
            break;
        }
    }

    dst = tmdata;
    ptr = (u8*) lbl_80473AB8 + i * (s32) 0xDC;
    player_count = 0;

    for (player_idx = 0; player_idx < 4; player_idx++) {
        dst[0x4B6] = ptr[0x30];
        dst[0x4B7] = ptr[0x50];
        *(u16*) (dst + 0x4BE) = *(u16*) (tmdata + 0x40 + ptr[0x50] * 0x12);
        dst[0x4BC] = ptr[0x51];
        dst[0x4BD] = ptr[0x52];
        dst[0x4B9] = ptr[0x4D];
        char_kind = dst[0x4B9];
        if (char_kind >= 0x13) {
            if (char_kind == 0x1D) {
                char_kind = 5;
            } else {
                char_kind += 1;
            }
        }
        Player_SetPlayerCharacter(player_idx, char_kind);
        dst[0x4B8] = ptr[0x4E];
        char_kind = dst[0x4B8];
        if ((u32) char_kind != 3) {
            player_count += 1;
        }
        Player_SetSlottype(player_idx, char_kind);
        dst[0x4BB] = ptr[0x4F];
        Player_SetCostumeId(player_idx, dst[0x4BB]);
        dst[0x4BC] = ptr[0x51];
        ptr += 0x2C;
        dst += 0xA;
    }

    tmdata[0x30] = player_count;
}

#pragma push
#pragma auto_inline off
void fn_8018FBD8(void* arg0, s32 arg1)
{
    ((HSD_GObj*) arg0)->user_data = (void*) arg1;
}
#pragma pop

void fn_8018FBE0(s32 arg0, s32 arg1, s32 arg2, s8 arg3, s8 arg4, s16 arg5,
                 s8 arg6)
{
    s32 i;

    PAD_STACK(8);

    gm_804771C4.cur_option = arg0;
    gm_804771C4.x1C = arg1;
    gm_804771C4.x20 = arg2;

    for (i = 0; 64 > i; i++) {
        gm_804771C4.x37[i].x2 = (u8) arg3;
        gm_804771C4.x37[i].x1 = (u8) arg4;
        gm_804771C4.x37[i].xD = (u8) i;
        gm_804771C4.x37[i].x9 = (u16) arg5;
        gm_804771C4.x37[i].x0 = (u8) arg6;
    }
}

#pragma push
#pragma auto_inline off
void fn_8018FDC4(HSD_JObj* jobj, float x, float y, float z)
{
    if ((int) x != 666) {
        HSD_JObjSetTranslateX(jobj, x);
    }
    if ((int) y != 666) {
        HSD_JObjSetTranslateY(jobj, y);
    }
    if ((int) z != 666) {
        HSD_JObjSetTranslateZ(jobj, z);
    }
}
#pragma pop

#pragma push
#pragma auto_inline off
void fn_8018FF9C(HSD_JObj* jobj, float x, float y, float z)
{
    if ((int) x != 666) {
        HSD_JObjSetScaleX(jobj, x);
    }
    if ((int) y != 666) {
        HSD_JObjSetScaleY(jobj, y);
    }
    if ((int) z != 666) {
        HSD_JObjSetScaleZ(jobj, z);
    }
}
#pragma pop

#pragma push
#pragma auto_inline off
HSD_GObj* fn_80190174(HSD_CObjDesc* cobjdesc)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x12, 0);
    HSD_CObj* cobj = HSD_CObjLoadDesc(cobjdesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
    gobj->gxlink_prios = 7;
    return gobj;
}
#pragma pop

#pragma push
#pragma auto_inline off
HSD_GObj* fn_801901F8(HSD_CObjDesc* cobjdesc)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x15, 2);
    HSD_CObj* cobj = HSD_CObjLoadDesc(cobjdesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 2);
    gobj->gxlink_prios = 0xA;
    return gobj;
}
#pragma pop

#pragma push
#pragma auto_inline off
void fn_8019027C(UNK_T lights)
{
    HSD_GObj* gobj = GObj_Create(0xB, 0x1A, 0);
    HSD_LObj* lobj = lb_80011AC4(lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 1, 0);
}
#pragma pop

/// Initializes SIS library text rendering for tournament mode.
#pragma push
#pragma auto_inline off
void fn_801902F0(int sis_param)
{
    s32 value;
    PAD_STACK(8);

    value = sis_param;
    HSD_SisLib_803A5E70();
    if (gm_804771C4.x1C == 0) {
        value = 0;
    }
    lbl_804D663C = (HSD_GObj*) HSD_SisLib_803A611C(0, (HSD_GObj*) value, 9,
                                                   0x12, 0, 3, 0, 0x13);
}
#pragma pop

#pragma push
#pragma auto_inline off
HSD_GObj* fn_8019035C(bool arg0, DynamicModelDesc* model, int arg2, int arg3,
                      int arg4, bool arg5, void (*arg6)(HSD_GObj*), f32 arg8)
{
    HSD_GObj* gobj = GObj_Create(0xE, arg3, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(model->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, arg4, 0);
    if (arg6 != NULL) {
        HSD_GObj_SetupProc(gobj, arg6, 0);
    }
    if (arg5) {
        gm_8016895C(jobj, model, arg2);
        HSD_JObjReqAnimAll(jobj, arg8);
        HSD_JObjAnimAll(jobj);
        if (arg0) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
    return gobj;
}
#pragma pop

#pragma dont_inline on
void fn_8019044C(HSD_JObj* jobj, float arg1)
{
    HSD_JObjReqAnimAll(jobj, arg1);
    HSD_JObjAnimAll(jobj);
}
#pragma dont_inline off

#pragma push
#pragma auto_inline off
void fn_80190480(float arg8)
{
    if ((int) arg8 == 0) {
        HSD_CObjSetFov(lbl_803D9DD0.cobj, lbl_803D9DD0.xD0);
        return;
    }
    HSD_CObjSetFov(lbl_803D9DD0.cobj, arg8);
}
#pragma pop

void fn_801904D0(void)
{
    struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
    HSD_CObjSetInterest(tmp->cobj, &lbl_803D9DD0.interest);
    HSD_CObjSetEyePosition(tmp->cobj, &lbl_803D9DD0.eye_position);
}

#pragma push
#pragma auto_inline off

void fn_80190520(f32 x, f32 y, f32 z)
{
    Vec3 sp14;

    if (((s32) x == 0) && ((s32) y == 0) && ((s32) z == 0)) {
        struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
        HSD_CObjSetInterest(tmp->cobj, &lbl_803D9DD0.interest);
        HSD_CObjSetEyePosition(tmp->cobj, &lbl_803D9DD0.eye_position);
        return;
    } else {
        struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
        sp14.x = x;
        sp14.y = y;
        sp14.z = z;
        HSD_CObjSetInterest(tmp->cobj, &sp14);
        sp14.z = 415.6922f + z;
        HSD_CObjSetEyePosition(tmp->cobj, &sp14);
    }
}
#pragma pop

/// #fn_80190520

static inline int gm_801905F0_inline0(int c_kind)
{
    if (c_kind < CKIND_SEAK) {
        return c_kind;
    }
    if (c_kind == CKIND_GKOOPS) {
        return CKIND_KOOPA;
    }
    return c_kind + 1;
}

void gm_801905F0(StartMeleeData* arg0)
{
    u8 _padA[8];
    TmData* tm = &gm_804771C4;
    GameRules* temp_r31 = gmMainLib_8015CC34();
    int i;
    TmVsData sp18;

    gm_80168FC4();
    gm_80167A64(&arg0->rules);
    arg0->rules.is_teams = false;
    arg0->rules.xE = tm->x28;
    fn_801640B0(&arg0->rules.x20);
    arg0->rules.x0_0 = temp_r31->mode;
    if (temp_r31->mode != 1) {
        arg0->rules.x0_6 = true;
    } else if (temp_r31->stock_time_limit != 0) {
        arg0->rules.x0_6 = true;
    } else {
        arg0->rules.x0_6 = false;
    }
    if (arg0->rules.x0_6) {
        if (temp_r31->mode != 1) {
            if (temp_r31->time_limit == 0) {
                arg0->rules.x10 = 99 * 60;
            } else {
                arg0->rules.x10 = temp_r31->time_limit * 60;
            }
        } else {
            if (temp_r31->stock_time_limit == 0) {
                arg0->rules.x10 = 99 * 60;
            } else {
                arg0->rules.x10 = temp_r31->stock_time_limit * 60;
            }
        }
    }
    if (arg0->rules.x0_0 == 1) {
        arg0->rules.x2_0 = true;
    }
    arg0->rules.x0_7 = false;
    arg0->rules.x4_2 = false;
    arg0->rules.x4_4 = false;
    arg0->rules.xB = gmMainLib_8015CC58()->item_freq;
    arg0->rules.x2_2 = false;
    arg0->rules.x18 = 0;
    arg0->rules.x34 = 1.0f;
    arg0->rules.x30 = fn_801653E8(temp_r31->damage_ratio);
    arg0->rules.x3_4 = false;
    arg0->rules.x3_5 = false;
    arg0->rules.x3_2 = false;
    arg0->rules.x3_3 = false;
    switch (gmMainLib_8015ED30()) {
    case 1:
        arg0->rules.xC = 0;
        break;
    case 0:
        arg0->rules.xC = -1;
        break;
    case 2:
        arg0->rules.xC = -2;
        break;
    }
    if (temp_r31->pause != 0) {
        arg0->rules.x2_4 = false;
    } else {
        arg0->rules.x2_4 = true;
    }
    if (temp_r31->score_display != 0 && !arg0->rules.x0_0) {
        arg0->rules.x3_0 = true;
    } else {
        arg0->rules.x3_0 = false;
    }
    gm_80167A14(arg0->players);

    for (i = 0; i < 4; i++) {
        if (i < tm->x30) {
            arg0->players[i].x20 = 1.0f;
            arg0->players[i].xA = (u8) MIN(tm->x4B8[i].x6, 0x78);
            if (tm->x4B8[i].x2 != 0) {
                arg0->players[i].c_kind = gm_801905F0_inline0(fn_8018F410());
                arg0->players[i].color =
                    HSD_Randi(gm_80169238(arg0->players[i].c_kind));
            } else {
                arg0->players[i].c_kind = gm_801905F0_inline0(tm->x4B8[i].x1);
                arg0->players[i].color = tm->x4B8[i].x3;
            }
            arg0->players[i].slot_type = tm->x4B8[i].x0;
            arg0->players[i].stocks = temp_r31->stock_count;
            arg0->players[i].sub_color = 0;
            arg0->players[i].team = 0xFF;
            arg0->players[i].xC_b0 = gm_801677F8(i, arg0->players[i].xA);
            if (tm->x4B8[i].x0 == 1) {
                arg0->players[i].xC_b0 = false;
            }
            arg0->players[i].xE = 4;
            arg0->players[i].cpu_level = tm->x4B8[i].x4;
            arg0->players[i].x12 = 0;
            if (gmMainLib_8015CC34()->handicap != 0) {
                arg0->players[i].x18 = fn_8016419C(tm->x4B8[i].x5);
                arg0->players[i].x1C = fn_801641B4(tm->x4B8[i].x5);
            } else {
                arg0->players[i].x18 = arg0->players[i].x1C = 1.0F;
            }
        } else {
            arg0->players[i].slot_type = Gm_PKind_NA;
        }
    }

    sp18.stage_id = arg0->rules.xE;
    for (i = 0; i < 4; i++) {
        sp18.slot_type[i] = arg0->players[i].slot_type;
        sp18.char_id[i] = arg0->players[i].c_kind;
        sp18.color[i] = arg0->players[i].color;
    }

    fn_8019EF08(&sp18);
}

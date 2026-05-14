#include "tylist.h"

#include "gm/gmmain_lib.h"
#include "if/textlib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "mn/mnmain.h"
#include "ty/toy.h"
#include "ty/types.h"

#include <m2c_macros.h>
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
#include <baselib/mobj.h>
#include <baselib/sislib.h>
#include <baselib/tobj.h>
#include <baselib/video.h>

typedef struct {
    u8 pad[0x28];
    HSD_CObj* cobj;
} TyListData;

typedef struct {
    u8 pad[0x4E8];
    u8* digits;
} SisFontData;

typedef struct {
    HSD_GObj* gobj;
    u8 pad[0x4C];
    void* data;
} TyArchiveData;

void un_803124BC(void)
{
    u16* table1;
    s16* list;
    u16* table2;
    s32 i;

    table1 = gmMainLib_8015CC78();
    table2 = gmMainLib_8015CC84();

    if (un_804D6ED0 == NULL) {
        char* archiveName;
        if (lbLang_IsSavedLanguageJP()) {
            archiveName = "TyDatai.dat";
        } else {
            archiveName = "TyDatai.usd";
        }
        un_804D6ED0 = lbArchive_LoadSymbols(
            archiveName, &un_804D6EC4, "tyInitModelTbl", &un_804D6EC0,
            "tyInitModelDTbl", &un_804D6EBC, "tyModelSortTbl", &un_804D6EB8,
            "tyExpDifferentTbl", &un_804D6EB4, "tyNoGetUsTbl", &un_804D6EB0,
            "tyDisplayModelTbl", &un_804D6EAC, "tyDisplayModelUsTbl", NULL);
    }

    i = 0;
loop: {
    s32 skip;
    s16 val;

    list = un_804D6EB4;
    if (lbLang_IsSettingUS()) {
        while ((val = *list) != -1) {
            if (val == i) {
                skip = 0;
                goto check;
            }
            list++;
        }
    }
    skip = 1;
check:
    if (skip != 0 && (s32) un_803060BC(i, 6) == 2) {
        *table1 |= 0x4000;
    }
}
    i++;
    table1++;
    if (i < 0x125) {
        goto loop;
    }

    *table2 |= 4;
    un_804A284C[3] |= 4;
}

void un_8031263C(void)
{
    s32 i;
    u16* table1;
    u16* table2;

    ((TyModeState*) un_804A284C)->x4 = 0;
    table1 = gmMainLib_8015CC78();
    table2 = gmMainLib_8015CC84();

    if (un_804D6ED0 == NULL) {
        char* archiveName;
        if (lbLang_IsSavedLanguageJP()) {
            archiveName = "TyDatai.dat";
        } else {
            archiveName = "TyDatai.usd";
        }
        un_804D6ED0 = lbArchive_LoadSymbols(
            archiveName, &un_804D6EC4, "tyInitModelTbl", &un_804D6EC0,
            "tyInitModelDTbl", &un_804D6EBC, "tyModelSortTbl", &un_804D6EB8,
            "tyExpDifferentTbl", &un_804D6EB4, "tyNoGetUsTbl", &un_804D6EB0,
            "tyDisplayModelTbl", &un_804D6EAC, "tyDisplayModelUsTbl", NULL);
    }

    i = 0;
    do {
        if (un_80304CC8(i) != 0) {
            if ((s32) un_803060BC(i, 6) == 2) {
                *table1 |= 0x4000;
            }
        }
        i++;
        table1++;
    } while (i < 0x125);

    *table2 |= 4;
    un_804A284C[3] |= 4;

    if (un_804D6ECC == NULL) {
        un_804D6ECC = lbArchive_LoadSymbols(str_TyDataf_dat, &un_804D6EA8,
                                            str_tyModelFileTbl, &un_804D6EA4,
                                            str_tyModelFileUsTbl, NULL);
    }

    un_8031234C(0);
}
void un_803127D4(void)
{
    un_804D6ED0 = NULL;
    un_804D6EC4 = NULL;
    un_804D6EC0 = NULL;
    un_804D6EBC = NULL;
    un_804D6EB8 = NULL;
    un_804D6EB4 = NULL;
    un_804D6EB0 = NULL;
    un_804D6EAC = NULL;
    un_804D6ECC = NULL;
    un_804D6EA8 = NULL;
    un_804D6EA4 = NULL;
    un_804D6EC8 = NULL;
    memzero(&un_804A2AA8, sizeof(ToyAnimState));
}

/// Formats a number into a string buffer using digit glyphs from the font.
char* un_80312834(char* buf, u32 num)
{
    u8* lookup = ((SisFontData*) HSD_SisLib_804D1124[0])->digits;
    u32 idx;
    u32 original = num;

    if (num >= 100) {
        idx = (num / 100) * 2;
        *buf++ = lookup[idx];
        *buf++ = lookup[idx + 1];
        num = num % 100;
    }

    if (num >= 10) {
        idx = (num / 10) * 2;
        *buf++ = lookup[idx];
        *buf++ = lookup[idx + 1];
        num = num % 10;
    } else if (original >= 100) {
        *buf++ = lookup[0];
        *buf++ = lookup[1];
    }

    idx = num * 2;
    *buf++ = lookup[idx];
    *buf++ = lookup[idx + 1];
    *buf = 0;
    return buf;
}

extern f32 un_804DDE28;
extern f32 un_804DDE2C;
extern f32 un_804DDE30;
extern f32 un_804DDE34;
extern f32 un_804DDE38;
extern f32 un_804DDE3C;
extern f32 un_804DDE40;
extern f32 un_804DDE44;
extern f32 un_804DDE48;
extern f32 un_804DDE4C;
extern f32 un_804DDE50;

extern GXColor lb_804D3760;
extern GXColor lb_804D3764;

typedef struct TyListGobjEntry {
    /* 0x00 */ HSD_GObj* x0;
    /* 0x04 */ HSD_GObj* x4;
    /* 0x08 */ u8 pad_8[0x0C - 0x08];
    /* 0x0C */ s8 x0C;
    /* 0x0D */ u8 pad_0D[0x16 - 0x0D];
    /* 0x16 */ s8 x16;
} TyListGobjEntry;

extern TyListGobjEntry un_804A2D6C;

typedef struct TyListRow {
    /* 0x00 */ u8 pad_0[0xC];
    /* 0x0C */ HSD_JObj* jobj;
    /* 0x10 */ u8 pad_10[0x18 - 0x10];
    /* 0x18 */ HSD_Text* text0;
    /* 0x1C */ HSD_Text* text1;
    /* 0x20 */ HSD_Text* text2;
    /* 0x24 */ s8 x24;
    /* 0x25 */ u8 pad_25;
    /* 0x26 */ s16 idx;
    /* 0x28 */ s32 x28;
    /* 0x2C */ u8 pad_2C[0x30 - 0x2C];
    /* 0x30 */ f32 x30;
} TyListRow;

void un_80312904(void* arg0, s8 arg1)
{
    TyListState* state = (TyListState*) un_804A2AC0;
    TyListRow* row = (TyListRow*) arg0;
    f32 f30;
    f32 f29;
    f32 f31;
    s32 skip;
    u8* digits;
    PAD_STACK(0x78);

    if (row->idx == -1) {
        return;
    }

    if (un_GetTrophyTotal() < 0xB) {
        s8 v = row->x24;
        if (v == -1 || v == (s8) state->entryCount - 2) {
            skip = 0;
        } else {
            skip = 1;
        }
    } else {
        skip = 1;
    }

    if (skip == 0) {
        return;
    }

    f30 = HSD_JObjGetTranslationX(row->jobj) - un_804DDE28;
    f29 = (-row->x30 - HSD_JObjGetTranslationY(state->gobj->hsd_obj)) -
          un_804DDE2C;
    f31 = HSD_JObjGetTranslationZ(state->gobj->hsd_obj);

    if (arg1 != 0x63) {
        if ((s8) row->x24 == arg1) {
            row->text0->text_color = lb_804D3764;
            row->text1->text_color = lb_804D3764;
            row->text2->text_color = lb_804D3764;
        } else {
            row->text0->text_color = lb_804D3760;
            row->text1->text_color = lb_804D3760;
            row->text2->text_color = lb_804D3760;
        }
    }

    row->text0->pos_x = f30;
    row->text0->pos_y = f29;
    row->text0->pos_z = f31;
    row->text0->font_size.x = un_804DDE30;
    row->text0->font_size.y = un_804DDE34;
    row->text0->default_kerning = 1;
    HSD_SisLib_803A6368(row->text0, un_80308354(row->idx));

    row->text1->pos_x = un_804DDE38 + f30;
    row->text1->pos_y = f29;
    row->text1->pos_z = f31;
    row->text1->font_size.x = un_804DDE30;
    row->text1->font_size.y = un_804DDE34;
    HSD_SisLib_803A6368(row->text1, 0x13B);

    digits = ((u8**) ((char*) HSD_SisLib_804D1124[0] + 0x4B8))[row->x28];
    un_80312834((char*) digits, un_803048C0(un_80308354(row->idx)));

    row->text2->default_alignment = 2;
    row->text2->default_kerning = 1;
    row->text2->pos_x = un_804DDE3C + f30;
    row->text2->pos_y = f29;
    row->text2->pos_z = f31;
    row->text2->font_size.x = un_804DDE40;
    row->text2->font_size.y = un_804DDE34;
    HSD_SisLib_803A6368(row->text2, row->x28 + 0x12E);
}

void un_80312BAC(TyListState* state, s8 arg1)
{
    void* archive = un_804D6ED8;
    s16 old_idx;
    s32 var_r28;
    s32 i;
    TyListArg* row;
    HSD_JObj* jobj;

    old_idx = un_804D6EDC[state->selectedIdx];
    un_803067BC((s8) state->x29B, (s8) state->x29C);
    state->selectedIdx = un_803062BC((s32) old_idx);

    if (un_GetTrophyTotal() <= 0xA) {
        var_r28 = state->selectedIdx;
        i = 0;
        while (i < (s8) state->x278->x24 + 1) {
            if (--var_r28 < 0) {
                var_r28 = un_GetTrophyTotal() - 1;
            }
            i++;
        }
    } else {
        var_r28 = state->selectedIdx;
        i = 0;
        while (i < (s8) state->x278->x24 + 1) {
            if (--var_r28 < 0) {
                var_r28 = un_GetTrophyTotal() - 1;
            }
            i++;
        }
    }

    jobj = state->jobj;
    row = state->x270;
    if (jobj != NULL) {
        f32 y = row->x30;
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3B3, &un_804D5A80);
        }
        jobj->translate.y = y;
        if (!(jobj->flags & 0x02000000)) {
            if (jobj == NULL) {
                goto done_first_dirty;
            }
            if (jobj == NULL) {
                __assert(&un_804D5A78, 0x234, &un_804D5A80);
            }
            {
                u32 flags = jobj->flags;
                s32 skip = 0;
                if (!(flags & 0x800000) && (flags & 0x40)) {
                    skip = 1;
                }
                if (skip == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    }
done_first_dirty:

    for (i = 0; i < (s8) state->entryCount; i++) {
        row->idx = var_r28;
        un_80312904(row, arg1);
        un_80313464(row);
        if (row->x24 >= 0 && row->x24 < (s8) state->entryCount - 2 &&
            row->idx == un_GetTrophyTotal() - 1)
        {
            HSD_JObj* jobj2 = state->jobj;
            if (jobj2 != NULL) {
                f32 y = row->x30;
                if (jobj2 == NULL) {
                    __assert(&un_804D5A78, 0x3B3, &un_804D5A80);
                }
                jobj2->translate.y = y;
                if (!(jobj2->flags & 0x02000000)) {
                    if (jobj2 == NULL) {
                        goto done_inner_dirty;
                    }
                    if (jobj2 == NULL) {
                        __assert(&un_804D5A78, 0x234, &un_804D5A80);
                    }
                    {
                        u32 flags = jobj2->flags;
                        s32 skip = 0;
                        if (!(flags & 0x800000) && (flags & 0x40)) {
                            skip = 1;
                        }
                        if (skip == 0) {
                            HSD_JObjSetMtxDirtySub(jobj2);
                        }
                    }
                }
            }
        }
    done_inner_dirty:
        row = row->x4;
        var_r28++;
        if (var_r28 >= un_GetTrophyTotal()) {
            var_r28 = 0;
        }
    }

    i = 0;
    while (i < 3) {
        HSD_JObj* anim_jobj = *((HSD_JObj**) ((u8*) archive + i * 4 + 0x18));
        if (i == (s8) state->x29B) {
            HSD_JObjReqAnim(anim_jobj, un_804DDE44);
        } else {
            HSD_JObjReqAnim(anim_jobj, un_804DDE48);
        }
        HSD_AObjSetRate(anim_jobj->u.dobj->mobj->tobj->aobj, un_804DDE48);
        HSD_JObjAnim(anim_jobj);
        i++;
    }
}

void un_80312E88(TyListArg* arg, float delta)
{
    TyListArg* ptr;
    HSD_JObj* jobj;
    char* data;
    s32 i;
    PAD_STACK(8);

    arg->x30 = arg->x30 + delta;

    if (un_804DDE4C == delta) {
        arg->x30 = arg->x2C;
    } else if (delta < un_804DDE48) {
        if (arg->x30 < arg->x2C) {
            arg->x30 = arg->x2C;
        }
    } else {
        if (arg->x30 > arg->x2C) {
            arg->x30 = arg->x2C;
        }
    }

    ptr = arg;
    data = un_804A2AC0;
    i = 0;
loop:
    if ((jobj = ptr->xC) == NULL) {
        goto next;
    }
    if (i == 2) {
        goto next;
    }
    {
        float pos = arg->x30;
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3B3, &un_804D5A80);
        }
        jobj->translate.y = pos;
    }

    if ((jobj->flags & 0x02000000) == 0) {
        if (jobj == NULL) {
            goto skip_dirty;
        }
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x234, &un_804D5A80);
        }
        {
            u32 flags = jobj->flags;
            s32 skip = 0;
            if ((flags & 0x800000) == 0 && (flags & 0x40)) {
                skip = 1;
            }
            if (skip == 0) {
                HSD_JObjSetMtxDirtySub(jobj);
            }
        }
    }
skip_dirty:

    if (arg->idx == un_GetTrophyTotal() - 1) {
        float pos;
        jobj = ((TyListState*) data)->jobj;
        pos = arg->x30;
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3B3, &un_804D5A80);
        }
        jobj->translate.y = pos;

        if ((jobj->flags & 0x02000000) == 0) {
            if (jobj == NULL) {
                goto next;
            }
            if (jobj == NULL) {
                __assert(&un_804D5A78, 0x234, &un_804D5A80);
            }
            {
                u32 flags = jobj->flags;
                s32 skip = 0;
                if ((flags & 0x800000) == 0 && (flags & 0x40)) {
                    skip = 1;
                }
                if (skip == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    }

next:
    i = i + 1;
    ptr = (TyListArg*) ((s8*) ptr + 4);
    if (i < 3) {
        goto loop;
    }

    un_80312904(arg, 0x63);
    un_80313464(arg);
}
s8 un_8031305C(void* a, TyListState* state, s8 movedFlag)
{
    TyListArg* entry;
    f32 delta;
    s32 i;
    PAD_STACK(8);

    if ((s8) state->x29F > 0) {
        delta = state->x2A4;
        if ((s8) state->x2A1 == 0) {
            delta *= un_804DDE50;
        }
        entry = state->entries;
        i = 0;
        while (i < (s8) state->entryCount) {
            s8 x2A1 = state->x2A1;
            if (((s8) x2A1 != 0 || (entry->x24 != -1)) &&
                ((s8) x2A1 != 1 || (s8) state->entryCount - 1 != entry->x24))
            {
                un_80312E88(entry, delta);
            }
            entry = (TyListArg*) ((u8*) entry + 0x34);
            i++;
        }
        state->x29F = (u8) (state->x29F - 1);
        if ((s8) state->x29F == 0) {
            i = 0;
            entry = state->entries;
            while (i < (s8) state->entryCount) {
                un_80312E88(entry, un_804DDE4C);
                if ((s8) state->x2A1 == 0) {
                    entry->x24 = (s8) (entry->x24 - 1);
                    if (entry->x24 < -1) {
                        entry->x24 = (s8) (state->entryCount - 2);
                    }
                } else {
                    entry->x24 = (s8) (entry->x24 + 1);
                    if (entry->x24 >= (s8) state->entryCount - 1) {
                        entry->x24 = (s8) -1;
                    }
                }
                entry = entry->x4;
                i++;
            }
            if ((s8) state->x2A1 == 0) {
                state->x270->idx = (s16) (state->x274->idx + 1);
                if (state->x270->idx >= un_GetTrophyTotal()) {
                    state->x270->idx = 0;
                }
                un_80312904(state->x270, un_804A2D6C.x0C);
                state->x278 = state->x278->x4;
                state->selectedIdx = state->x278->idx;
                state->x270 = state->x270->x4;
                state->x274 = state->x274->x4;
            } else {
                state->x274->idx = (s16) (state->x270->idx - 1);
                if (state->x274->idx < 0) {
                    state->x274->idx = (s16) (un_GetTrophyTotal() - 1);
                }
                un_80312904(entry, un_804A2D6C.x0C);
                state->x278 = state->x278->x0;
                state->selectedIdx = state->x278->idx;
                state->x270 = state->x270->x0;
                state->x274 = state->x274->x0;
            }
            if ((s8) state->x29E > 0) {
                state->x29E = (u8) (state->x29E - 1);
            }
            if ((s8) state->x29E == 0) {
                HSD_JObjClearFlagsAll(state->x288, 0x10U);
                un_80312904(state->x278, (s8) state->x278->x24);
                if (HSD_PadCopyStatus->button & 0xC00) {
                    state->pad_2A0 = 5;
                } else {
                    state->pad_2A0 = 0;
                }
            }
            if (movedFlag != 0) {
                lbAudioAx_80024030(2);
            }
        }
    }
    return (s8) state->x29F;
}

void un_80313358(TyListState* state, s8 arg2, s8 arg3, s8 arg4)
{
    int i;

    if (arg2 != -1) {
        state->x29E = arg2;
        state->x2A1 = arg4;
    }

    state->x29F = arg3;
    state->x2A4 = state->x2A8 / (float) arg3;

    if (state->x2A1 == 0) {
        for (i = 0; i < state->entryCount; i++) {
            TyListArg* entry = &state->entries[i];
            TyListArg* sub = entry->x0;
            entry->x2C = sub->x30;
            un_80312904(entry, state->entryCount + 1);
        }
    } else {
        for (i = 0; i < state->entryCount; i++) {
            TyListArg* entry = &state->entries[i];
            TyListArg* sub = entry->x4;
            entry->x2C = sub->x30;
            un_80312904(entry, state->entryCount + 1);
        }
    }
}

void un_80313464(TyListArg* arg)
{
    char* data = un_804A2AC0;
    s32 val;
    PAD_STACK(24);

    val = un_804D6EDC[arg->idx];

    un_803083D8(arg->x14, val);

    if (arg->x10 != NULL) {
        HSD_JObjUnref(arg->x10);
        arg->x10 = NULL;
    }

    if (un_80304924(val) != 0) {
        arg->x10 = un_80313508(((TyListState*) data)->gobj, un_803FE8D0,
                               un_804DDE60, arg->x30, un_804DDE48);
    }
}
HSD_JObj* un_80313508(void* parent, void* symbol, float x, float y, float z)
{
    HSD_JObj* jobj;
    TyArchiveData* archive;
    void* joint;
    PAD_STACK(8);

    archive = un_804D6ED8;
    joint = HSD_ArchiveGetPublicAddress(archive->data, symbol);

    if (joint == NULL) {
        OSPanic(un_803FE8F0, 0x337, un_803FE8FC);
        return NULL;
    }

    jobj = HSD_JObjLoadJoint(joint);

    if (x != un_804DDE48 || y != un_804DDE48 || z != un_804DDE48) {
        // Set X
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3A4, &un_804D5A80);
        }
        jobj->translate.x = x;

        if ((jobj->flags & 0x02000000) == 0) {
            if (jobj == NULL) {
                goto skip_x;
            }
            if (jobj == NULL) {
                __assert(&un_804D5A78, 0x234, &un_804D5A80);
            }
            {
                u32 flags = jobj->flags;
                s32 skip = 0;
                if ((flags & 0x800000) == 0 && (flags & 0x40)) {
                    skip = 1;
                }
                if (skip == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    skip_x:

        // Set Y
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3B3, &un_804D5A80);
        }
        jobj->translate.y = y;

        if ((jobj->flags & 0x02000000) == 0) {
            if (jobj == NULL) {
                goto skip_y;
            }
            if (jobj == NULL) {
                __assert(&un_804D5A78, 0x234, &un_804D5A80);
            }
            {
                u32 flags = jobj->flags;
                s32 skip = 0;
                if ((flags & 0x800000) == 0 && (flags & 0x40)) {
                    skip = 1;
                }
                if (skip == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    skip_y:

        // Set Z
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3C2, &un_804D5A80);
        }
        jobj->translate.z = z;

        if ((jobj->flags & 0x02000000) == 0) {
            if (jobj == NULL) {
                goto skip_z;
            }
            if (jobj == NULL) {
                __assert(&un_804D5A78, 0x234, &un_804D5A80);
            }
            {
                u32 flags = jobj->flags;
                s32 skip = 0;
                if ((flags & 0x800000) == 0 && (flags & 0x40)) {
                    skip = 1;
                }
                if (skip == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    skip_z:;
    }

    if (parent != NULL) {
        HSD_JObj* parentJobj = ((HSD_GObj*) parent)->hsd_obj;
        HSD_JObj* child;
        HSD_JObjAddChild(parentJobj, jobj);
        child = parentJobj->child;
        while (child->next != NULL) {
            child = child->next;
        }
    } else {
        HSD_GObj* gobj;
        gobj = GObj_Create(6, 7, 0);
        HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0x39, 0);
    }

    return jobj;
}

/// #un_80313774

extern s32 un_804D6EE8;
extern s32 un_804D6EEC;
extern f32 un_804DDE44;
extern f32 un_804DDE48;
extern f32 un_804DDE50;
extern f32 un_804DDE68;
extern f32 un_804DDE78;
extern f32 un_804DDE7C;
extern f32 un_804DDE80;
extern f32 un_804DDE84;
extern f32 un_804DDE88;
extern f32 un_804DDE8C;
extern f32 un_804DDE90;
extern f32 un_804DDE94;
extern f32 un_804DDE98;
extern char un_803FE5E8[];
extern char un_804D5A88[3];

s8 un_8031305C(void* a, TyListState* state, s8 movedFlag);
void un_80312BAC(TyListState* state, s8 arg1);

void fn_80313BD8(HSD_GObj* gobj)
{
    TyListState* state = (TyListState*) un_804A2AC0;
    s8* g = ((s8*) state) + 0x2AC;
    f32 f30;
    f32 f31;
    HSD_JObj* jobj;
    f32 ftmp;
    s32 i;
    TyListArg* p;
    s8 v;

    if (un_GetTrophyTotal() > 10) {
        if (un_8031305C(g, state, 1) != 0) {
            return;
        }
        if ((s8) state->pad_2A0 != 0) {
            state->pad_2A0 = state->pad_2A0 - 1;
            return;
        }
        if ((s8) state->x29E != 0) {
            s32 d = (s8) state->pad_29D;
            s32 half = d / 2;
            s32 r;
            if ((d % 2) != 0) {
                if ((s8) state->x29E <= half) {
                    r = 5 - (s8) state->x29E;
                } else {
                    r = 4 - (d - (s8) state->x29E);
                }
            } else if ((s8) state->x29E == half) {
                r = 4 - (d - ((s8) state->x29E + 1));
            } else if ((s8) state->x29E < half) {
                r = 4 - (s8) state->x29E;
            } else {
                r = 4 - (d - (s8) state->x29E);
            }
            if (r < 2) {
                r = 2;
            }
            un_80313358(state, -1, (s8) r, -1);
            return;
        }
    }

    /* Fall-through label: block_17 */
    f30 = un_80305D00();
    f31 = un_80305DB0();
    if (f30 < un_804DDE78) {
        g[0x12] = g[0x12] + 1;
        f30 = un_804DDE50;
        f31 = un_804DDE48;
    } else if (f30 > un_804DDE7C) {
        g[0x12] = g[0x12] + 1;
        f30 = un_804DDE44;
        f31 = un_804DDE48;
    } else if (f31 < un_804DDE80 || (un_80305C44() & 4)) {
        g[0x12] = g[0x12] + 1;
        f30 = un_804DDE48;
        f31 = un_804DDE44;
    } else if (f31 > un_804DDE84 || (un_80305C44() & 8)) {
        g[0x12] = g[0x12] + 1;
        f30 = un_804DDE48;
        f31 = un_804DDE50;
    } else {
        f31 = un_804DDE48;
        g[0xF] = 0;
        f30 = f31;
        g[0x12] = 0;
        g[0x14] = 6;
        g[0x13] = 0;
        g[0x11] = 0;
        g[0x10] = 0;
    }

    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        un_80310660(0);
        un_803148E4(0);
        mn_8022F268();
        ((TyModeState*) un_804A284C)->x4 = 1;
        return;
    }

    if (un_80305B88() & 0x200) {
        lbAudioAx_80024030(0);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        un_80310660(0);
        un_803148E4(0);
        ((TyModeState*) un_804A284C)->x4 = 1;
        return;
    }

    if (un_GetTrophyTotal() == 0) {
        return;
    }

    if (un_80305B88() & 0x1100) {
        lbAudioAx_80024030(1);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        un_80310660(0);
        un_803148E4(1);
        un_80310324();
        return;
    }

    if ((s8) g[0x12] > (s8) g[0x14]) {
        g[0x12] = g[0x14] + 1;
        g[0x14] = 3;
        g[0xF] = 0;
    }

    if ((f30 < un_804DDE48 && f30 != (f32) (s8) g[0x10]) ||
        (un_80305B88() & 0x41))
    {
        g[0x10] = (s8) f30;
        state->x29B = state->x29B - 1;
        if ((s8) state->x29B < 0) {
            state->x29B = 2;
        }
        un_80312BAC(state, g[0xC]);
        lbAudioAx_80024030(1);
        return;
    }

    if ((f30 > un_804DDE48 && f30 != (f32) (s8) g[0x10]) ||
        (un_80305B88() & 0x22))
    {
        g[0x10] = (s8) f30;
        state->x29B = state->x29B + 1;
        if ((s8) state->x29B >= 3) {
            state->x29B = 0;
        }
        un_80312BAC(state, g[0xC]);
        lbAudioAx_80024030(1);
        return;
    }

    if (un_GetTrophyTotal() < 2) {
        return;
    }

    if (un_GetTrophyTotal() > 10) {
        if (un_80305C44() & 0x400) {
            HSD_JObjSetFlagsAll(state->jobj, 0x10);
            if (state->entries[0].idx == 0 ||
                state->entries[0].x0->idx + 9 < un_GetTrophyTotal())
            {
                un_80313358(state, 9, 4, 0);
            } else {
                un_80313358(state,
                            (s8) (un_GetTrophyTotal() - state->entries[0].idx),
                            4, 0);
            }
            state->pad_29D = state->x29E;
            return;
        }
        if (un_80305C44() & 0x800) {
            s16 idx;
            HSD_JObjSetFlagsAll(state->jobj, 0x10);
            idx = state->entries[0].idx;
            if (idx == un_GetTrophyTotal() - 1 ||
                state->entries[0].x4->idx - 9 > 0)
            {
                un_80313358(state, 9, 4, 1);
            } else {
                un_80313358(state, (s8) idx, 4, 1);
            }
            state->pad_29D = state->x29E;
            return;
        }
    }

    if (f31 == un_804DDE48) {
        return;
    }
    if ((s8) g[0xF] != 0) {
        return;
    }
    g[0xF] = 1;
    g[0xC] = (s8) ((f32) (s8) g[0xC] + f31);
    if ((s8) g[0xC] < 0) {
        g[0xC] = 0;
    } else if ((s8) g[0xC] > (s8) state->entryCount - 3) {
        g[0xC] = state->entryCount - 3;
    }

    if ((s8) g[0xC] != (s8) g[0xD]) {
        i = 0;
        g[0x12] = 0;
        p = &state->entries[0];
        g[0x13] = 0;
        g[0x11] = (s8) f31;
        for (; i < (s8) state->entryCount; i++, p++) {
            if (((s8*) p)[0x24] == g[0xC]) {
                state->selectedIdx = p->idx;
                state->entries[10].x0 = (TyListArg*) p;
                lbAudioAx_80024030(2);
                jobj = state->jobj;
                ftmp = p->x30;
                if (jobj == NULL) {
                    __assert(&un_804D5A78, 0x3B3, &un_804D5A80);
                }
                jobj->translate.y = ftmp;
                if (!(jobj->flags & 0x02000000)) {
                    if (jobj != NULL) {
                        u32 flags = jobj->flags;
                        s32 skip = 0;
                        if (!(flags & 0x800000) && (flags & 0x40)) {
                            skip = 1;
                        }
                        if (skip == 0) {
                            HSD_JObjSetMtxDirtySub(jobj);
                        }
                    }
                }
            }
            un_80312904(p, state->x2B8);
        }
        g[0xD] = g[0xC];
        return;
    }

    if (un_GetTrophyTotal() <= 10) {
        return;
    }
    if ((s8) g[0x11] == 0) {
        g[0x13] = 5;
        g[0x12] = g[0x14] + 1;
        g[0x14] = 3;
        g[0xF] = 0;
    }
    g[0x11] = (s8) f31;
    v = g[0x13];
    if (v == 0) {
        g[0x13] = 1;
        return;
    }
    if (v < 5) {
        g[0x13] = v + 1;
        return;
    }

    p = &state->entries[0];
    for (i = 0; i < (s8) state->entryCount; i++, p++) {
        un_80312904(p, state->entryCount);
    }
    HSD_JObjSetFlagsAll(state->jobj, 0x10);
    if (f31 > un_804DDE48) {
        un_80313358(state, 1, 6, 0);
    } else {
        un_80313358(state, 1, 6, 1);
    }
}

typedef struct TyListArchive {
    /* 0x00 */ HSD_JObj** x0;
    /* 0x04 */ u8 pad_4[0x18 - 0x4];
    /* 0x18 */ HSD_JObj* jobjs[3];
} TyListArchive;

void fn_8031438C(HSD_GObj* arg0)
{
    TyListState* state = (TyListState*) un_804A2AC0;
    TyListGobjEntry* entry = (TyListGobjEntry*) &state->gobj_2AC;
    TyListArchive* archive = un_804D6ED8;
    s32 i;
    HSD_GObj* tmp;
    PAD_STACK(0x18);

    if (((s8*) state)[0x2C2] != 0) {
        if (entry->x16 > 1) {
            for (i = 0; i < 3; i++) {
                u8* base_p = (u8*) archive + i * 4;
                if (i == (s8) state->x29B) {
                    HSD_JObjReqAnim(*(HSD_JObj**) (base_p + 0x18),
                                    un_804DDE44);
                } else {
                    HSD_JObjReqAnim(*(HSD_JObj**) (base_p + 0x18),
                                    un_804DDE48);
                }
                HSD_AObjSetRate(archive->jobjs[0]->u.dobj->mobj->tobj->aobj,
                                un_804DDE48);
            }
            HSD_JObjAnimAll((HSD_JObj*) archive->x0[10]);
        } else {
            tmp = entry->x4;
            if (tmp != NULL) {
                ((s32*) tmp)[9] = 0;
                ((s32*) tmp)[8] = 0x42100000;
            }
            state->x290 = HSD_SisLib_803A6754(3, un_804D6EEC);
            state->x290->pos_z = un_804DDE68;
            state->x290->font_size.x = un_804DDE40;
            state->x290->font_size.y = un_804DDE34;
            state->x290->default_kerning = 1;
            state->x290->default_alignment = 2;
            HSD_SisLib_803A6B98(state->x290, un_804DDE88, un_804DDE8C,
                                un_804D5A88, un_GetTrophyTotal());
        }
        entry->x16--;
        return;
    }

    HSD_GObjProc_8038FED4(arg0);
    HSD_GObj_SetupProc(entry->x0, fn_80313BD8, 0);
    HSD_GObj_80390CD4(entry->x0);
}

void fn_80314504(HSD_GObj* gobj)
{
    TyListData* data = (TyListData*) gobj;

    if ((s32) HSD_CObjSetCurrent(data->cobj) != 0) {
        HSD_SetEraseColor(0, 0, 0, 0xFF);
        HSD_CObjEraseScreen(data->cobj, 1, 0, 0);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(0);
        HSD_CObjEndCurrent();
    }
}

void un_8031457C(void)
{
    TyListGobjEntry* entry = &un_804A2D6C;
    TyArchiveData* archive = un_804D6ED8;
    HSD_CameraDescPerspective* desc;
    HSD_CObj* cobj;
    Vec3 interest;
    Vec3 eye;
    Scissor scissor;
    HSD_RectS16 viewport;

    desc = HSD_ArchiveGetPublicAddress(archive->data, un_803FE5E8);
    if (desc != NULL) {
        entry->x0 = GObj_Create(1, 2, 0);
        HSD_GObjObject_80390A70(entry->x0, HSD_GObj_804D784B,
                                lb_80013B14(desc));
        GObj_SetupGXLinkMax(entry->x0, (GObj_RenderFunc) un_80306954, 0);
        entry->x0->gxlink_prios = 0x9010000000000000ULL;
        HSD_GObj_SetupProc(entry->x0, fn_8031438C, 0);
        HSD_GObj_80390CD4(entry->x0);
        entry->x16 = 0x1A;
    }
    un_804D6EEC = HSD_SisLib_803A611C(3, entry->x0, 0xC, 0xC, 0, 0x3F, 0, 0);
    if (desc != NULL) {
        entry->x4 = GObj_Create(1, 2, 0);
        cobj = lb_80013B14(desc);
        HSD_GObjObject_80390A70(entry->x4, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(entry->x4, (GObj_RenderFunc) fn_80314504, 0);
        entry->x4->gxlink_prios = 0x0210000000000000ULL;
        interest.x = un_804DDE90;
        interest.y = un_804DDE94;
        interest.z = un_804DDE48;
        HSD_CObjSetInterest(cobj, &interest);
        eye.x = un_804DDE90;
        eye.y = un_804DDE94;
        eye.z = un_804DDE98;
        HSD_CObjSetEyePosition(cobj, &eye);
        viewport.xmin = 0x76;
        viewport.xmax = 0x230;
        viewport.ymin = 0x4E;
        viewport.ymax = 0x19C;
        HSD_CObjSetViewport(cobj, &viewport);
        viewport.ymin = 0x60;
        if (un_GetTrophyTotal() < 10) {
            viewport.ymax = un_GetTrophyTotal() * 0x1E + 0x60;
        } else {
            viewport.ymax = 0x18A;
        }
        scissor.left = viewport.xmin;
        scissor.right = viewport.xmax;
        scissor.top = viewport.ymin;
        scissor.bottom = viewport.ymax;
        HSD_CObjSetScissor(cobj, &scissor);
        un_804D6EE8 =
            HSD_SisLib_803A611C(0, entry->x4, 0xB, 0xB, 0, 0x3E, 0, 0);
    }
}

void un_803147C4(void)
{
    TyListState* state = (TyListState*) un_804A2AC0;
    char* strs = un_803FE880;
    TyArchiveData* archive;
    PAD_STACK(8);

    memzero(&state->gobj_2AC, 0x18);
    un_8031457C();
    memzero(&state->gobj_2C4, 0x14);

    archive = un_804D6ED8;

    if (archive->data == NULL) {
        OSReport(strs + 0x14C);
        OSPanic(strs + 0x70, 0x636, un_804D5A8C);
    }

    {
        LightList** jobj =
            HSD_ArchiveGetPublicAddress(archive->data, strs + 0x170);
        if (jobj != NULL) {
            state->gobj_2C4 = GObj_Create(2, 3, 0);
            HSD_GObjObject_80390A70(state->gobj_2C4, (u8) HSD_GObj_804D784A,
                                    Toy_LoadLObjList(jobj, 0));
            GObj_SetupGXLink(state->gobj_2C4, HSD_GObj_LObjCallback, 0x34, 0);
        }
    }

    un_80307470(0);
    if (un_GetTrophyTotal() != 0) {
        memzero(state, 0x2AC);
        un_80313774();
    }
    HSD_PadRenewStatus();
}

void un_803148E4(s32 arg0)
{
    TyListState* state = (TyListState*) un_804A2AC0;
    TyModeState* mode = (TyModeState*) un_804A284C;
    TyArchiveData* archive = un_804D6ED8;
    PAD_STACK(8);

    if (un_GetTrophyTotal() != 0) {
        if (arg0 != 0) {
            un_804A284C[0x12A] = state->selectedIdx;
            un_804A284C[0x12B] = un_804D6EDC[state->selectedIdx];
            mode->x1 = state->x29B;
            mode->x2 = state->x29C;
            mode->x3 = state->x2B8;
        } else {
            if (un_GetTrophyTotal() != 0) {
                s16 val = un_804D6EDC[state->selectedIdx];
                un_803067BC(0, 0);
                state->selectedIdx = un_803062BC(val);
            }
            un_804A284C[0x12A] = state->selectedIdx;
            un_804A284C[0x12B] = un_804D6EDC[state->selectedIdx];
            mode->x1 = 0;
            mode->x2 = 0;
            mode->x3 = 0;
        }

        if (un_80304924(un_804D6EDC[state->selectedIdx]) != 0) {
            un_80304988(un_804D6EDC[state->selectedIdx]);
        }
    }

    if (state->gobj != NULL) {
        if (arg0 != 0) {
            HSD_GObjPLink_80390228(state->gobj);
        }
        state->gobj = NULL;
    }

    if (arg0 != 0) {
        HSD_SisLib_803A5E70();
    }

    if (archive->gobj != NULL) {
        if (arg0 != 0) {
            HSD_GObjPLink_80390228(archive->gobj);
        }
        archive->gobj = NULL;
    }

    if (state->gobj_2C4 != NULL && arg0 != 0) {
        HSD_GObjPLink_80390228(state->gobj_2C4);
    }

    if (state->gobj_2AC != NULL) {
        HSD_GObjProc_8038FED4(state->gobj_2AC);
        if (arg0 != 0) {
            HSD_GObjPLink_80390228(state->gobj_2AC);
        }
    }

    if (state->gobj_2B0 != NULL && arg0 != 0) {
        HSD_GObjPLink_80390228(state->gobj_2B0);
    }
}

#include "tylist.h"

#include "m2c_macros.h"
#include "math_ppc.h" // IWYU pragma: keep
#include "placeholder.h"
#include "platform.h"
#include "stddef.h"
#include "toy.h"
#include "trigf.h" // IWYU pragma: keep
#include "types.h"

#include <placeholder.h>

#include "baselib/archive.h"
#include "baselib/cobj.h"
#include "baselib/controller.h"
#include "baselib/debug.h"
#include "baselib/displayfunc.h"
#include "baselib/dobj.h"
#include "baselib/fog.h"
#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "baselib/lobj.h"
#include "baselib/mobj.h"
#include "baselib/sislib.h"
#include "baselib/tobj.h"
#include "baselib/wobj.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbspdisplay.h"
#include "mn/mnmain.h"
#include "mn/mnsoundtest.h"
#include "MSL/math_ppc.h"
#include "ty/toy.h"
#include "ty/types.h"

/* 312834 */ static char* _tyList_80312834(char* buf, u32 num);
/* 312904 */ static void _tyList_80312904(void*, s8);
/* 312BAC */ static void _tyList_80312BAC(TyListState* state, s8 arg1);
/* 312E88 */ static void _tyList_80312E88(struct TyListArg* arg, float delta);
/* 31305C */ static s32 _tyList_8031305C(void* a, TyListState* state,
                                         s8 movedFlag);
/* 313358 */ static void _tyList_80313358(TyListState* state, s8 arg2, s8 arg3,
                                          s8 arg4);
/* 313464 */ static void _tyList_80313464(struct TyListArg* arg);
/* 313508 */ static void* _tyList_80313508(HSD_GObj* parent, char* symbol_name,
                                           float x, float y, float z);
/* 313774 */ static void _tyList_80313774(void);
/* 313BD8 */ static void _tyList_80313BD8(HSD_GObj* gobj);
/* 31438C */ static void _tyList_8031438C(HSD_GObj* arg0);
/* 314504 */ static void _tyList_80314504(HSD_GObj* gobj, int);
/* 31457C */ static void _tyList_8031457C(void);
/* 3148E4 */ static void _tyList_803148E4(s32 arg0);
/* 4A2AC0 */ static TyListState _tyList_804A2AC0;
/* 4A2D6C */ static TyListGobjEntry _tyList_804A2D6C;
/* 4D6EE8 */ static s32 _tyList_804D6EE8;
/* 4D6EEC */ static s32 _tyList_804D6EEC;

/// @todo .data order hack
static void order_data_0(void)
{
    /*  +0 */ (void) "Pos : %f, %f,%f\n";
    /* +14 */ (void) "WinSize = %f, %f\n";
    /* +28 */ (void) "WinScale = %f, %f\n";
    /* +3C */ (void) "FontSize = %f, %f\n";
    /* +50 */ (void) "ToyFigureListMarkN_Top_joint";
    /* +70 */ (void) "tylist.c";
}

/// Formats a number into a string buffer using digit glyphs from the font.
char* _tyList_80312834(char* buf, u32 num)
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

void _tyList_80312904(void* arg0, s8 arg1)
{
    TyListState* state = (TyListState*) &_tyList_804A2AC0;
    TyListRow* row = (TyListRow*) arg0;
    f32 f30;
    f32 f29;
    f32 f31;
    s32 skip;
    u8* digits;
    HSD_Text* text;
    PAD_STACK(0x60);

    if (row->idx == -1) {
        return;
    }

    if (Toy_GetTrophyTotal() < 0xB) {
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

    f30 = HSD_JObjGetTranslationX(row->jobj) - 6.5f;
    f29 = (-row->x30 - HSD_JObjGetTranslationY(state->gobj->hsd_obj)) - 0.41f;
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

    text = row->text0;
    text->pos_x = f30;
    text->pos_y = f29;
    text->pos_z = f31;
    text = row->text0;
    text->font_size.x = 0.028f;
    text->font_size.y = 0.029f;
    row->text0->default_kerning = 1;
    HSD_SisLib_803A6368(row->text0, Toy_803082F8(row->idx));

    text = row->text1;
    text->pos_x = 14.7f + f30;
    text->pos_y = f29;
    text->pos_z = f31;
    text = row->text1;
    text->font_size.x = 0.028f;
    text->font_size.y = 0.029f;
    HSD_SisLib_803A6368(row->text1, 0x13B);

    digits = ((u8**) ((char*) HSD_SisLib_804D1124[0] + 0x4B8))[row->x28];
    _tyList_80312834((char*) digits, Toy_803048C0(Toy_80308354(row->idx)));

    row->text2->default_alignment = 2;
    row->text2->default_kerning = 1;
    text = row->text2;
    text->pos_x = 10.5f + f30;
    text->pos_y = f29;
    text->pos_z = f31;
    text = row->text2;
    text->font_size.x = 0.038f;
    text->font_size.y = 0.029f;
    HSD_SisLib_803A6368(row->text2, row->x28 + 0x12E);
}

void _tyList_80312BAC(TyListState* state, s8 arg1)
{
    s32 i;
    s16 old_idx;
    s32 var_r28;
    ToyED8Data* archive = Toy_sbss_804D6ED8;
    TyListArg* row;
    HSD_JObj* jobj;

    old_idx = Toy_sbss_804D6EDC[state->selectedIdx];
    Toy_803067BC((s8) state->x29B, (s8) state->x29C);
    state->selectedIdx = Toy_803062BC((s32) old_idx);

    if (Toy_GetTrophyTotal() <= 0xA) {
        var_r28 = state->selectedIdx;
        i = 0;
        while (i < (s8) state->x278->x24 + 1) {
            if (--var_r28 < 0) {
                var_r28 = Toy_GetTrophyTotal() - 1;
            }
            i++;
        }
    } else {
        var_r28 = state->selectedIdx;
        i = 0;
        while (i < (s8) state->x278->x24 + 1) {
            if (--var_r28 < 0) {
                var_r28 = Toy_GetTrophyTotal() - 1;
            }
            i++;
        }
    }

    jobj = state->jobj;
    row = state->x270;
    (void) row;
    if (jobj != NULL) {
        f32 y = row->x30;
        if (jobj == NULL) {
            __assert("jobj.h", 0x3B3, "jobj");
        }
        jobj->translate.y = y;
        if (!(jobj->flags & 0x02000000)) {
            if (jobj == NULL) {
                goto done_first_dirty;
            }
            if (jobj == NULL) {
                __assert("jobj.h", 0x234, "jobj");
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
        _tyList_80312904(row, arg1);
        _tyList_80313464(row);
        if (row->x24 >= 0 && row->x24 < (s8) state->entryCount - 2 &&
            row->idx == Toy_GetTrophyTotal() - 1)
        {
            HSD_JObj* jobj2 = state->jobj;
            if (jobj2 != NULL) {
                f32 y = row->x30;
                if (jobj2 == NULL) {
                    __assert("jobj.h", 0x3B3, "jobj");
                }
                jobj2->translate.y = y;
                if (!(jobj2->flags & 0x02000000)) {
                    if (jobj2 == NULL) {
                        goto done_inner_dirty;
                    }
                    if (jobj2 == NULL) {
                        __assert("jobj.h", 0x234, "jobj");
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
        row = row->links[1];
        var_r28++;
        if (var_r28 >= Toy_GetTrophyTotal()) {
            var_r28 = 0;
        }
    }

    i = 0;
    while (i < 3) {
        HSD_JObj* anim_jobj = *((HSD_JObj**) ((u8*) archive + i * 4 + 0x18));
        if (i == state->x29B) {
            HSD_JObjReqAnim(anim_jobj, 1.0f);
        } else {
            HSD_JObjReqAnim(anim_jobj, 0.0f);
        }
        HSD_AObjSetRate(anim_jobj->u.dobj->mobj->tobj->aobj, 0.0f);
        HSD_JObjAnim(anim_jobj);
        i++;
    }
}

void _tyList_80312E88(TyListArg* arg, float delta)
{
    TyListArg* ptr;
    HSD_JObj* jobj;
    char* data;
    s32 i;
    PAD_STACK(8);

    arg->x30 = arg->x30 + delta;

    if (delta == 999.0f) {
        arg->x30 = arg->x2C;
    } else if (delta < 0.0f) {
        if (arg->x30 < arg->x2C) {
            arg->x30 = arg->x2C;
        }
    } else {
        if (arg->x30 > arg->x2C) {
            arg->x30 = arg->x2C;
        }
    }

    ptr = arg;
    data = (char*) &_tyList_804A2AC0;
    i = 0;
loop:
    if ((jobj = ptr->jobjs[0]) == NULL) {
        goto next;
    }
    if (i == 2) {
        goto next;
    }
    HSD_JObjSetTranslateY(jobj, arg->x30);

    if (arg->idx == Toy_GetTrophyTotal() - 1) {
        jobj = ((TyListState*) data)->jobj;
        HSD_JObjSetTranslateY(jobj, arg->x30);
    }

next:
    i = i + 1;
    ptr = (TyListArg*) ((s8*) ptr + 4);
    if (i < 3) {
        goto loop;
    }

    _tyList_80312904(arg, 0x63);
    _tyList_80313464(arg);
}

s32 _tyList_8031305C(void* a, TyListState* state, s8 movedFlag)
{
    TyListArg* entry;
    f32 delta;
    s32 i;
    PAD_STACK(0xC);
    i = ((s8) state->x29F) > 0;
    if (i) {
        delta = state->x2A4;
        if ((s8) state->x2A1 == 0) {
            delta *= -1.0f;
        }
        entry = state->entries;
        i = 0;
        while (i < (s8) state->entryCount) {
            s8 x2A1 = state->x2A1;
            if (((s8) x2A1 != 0 || (entry->x24 != -1)) &&
                ((s8) x2A1 != 1 || (s8) state->entryCount - 1 != entry->x24))
            {
                _tyList_80312E88(entry, delta);
            }
            entry = (TyListArg*) ((u8*) entry + 0x34);
            i++;
        }
        state->x29F = (u8) (state->x29F - 1);
        if ((s8) state->x29F == 0) {
            i = 0;
            entry = state->entries;
            while (i < (s8) state->entryCount) {
                _tyList_80312E88(entry, 999.0f);
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
                entry = entry->links[1];
                i++;
            }
            if ((s8) state->x2A1 == 0) {
                state->x270->idx = (s16) (state->x274->idx + 1);
                if (state->x270->idx >= Toy_GetTrophyTotal()) {
                    state->x270->idx = 0;
                }
                _tyList_80312904(state->x270, _tyList_804A2D6C.x0C);
                state->x278 = state->x278->links[1];
                state->selectedIdx = state->x278->idx;
                state->x270 = state->x270->links[1];
                state->x274 = state->x274->links[1];
            } else {
                state->x274->idx = (s16) (state->x270->idx - 1);
                if (state->x274->idx < 0) {
                    state->x274->idx = (s16) (Toy_GetTrophyTotal() - 1);
                }
                _tyList_80312904(entry, _tyList_804A2D6C.x0C);
                state->x278 = state->x278->links[0];
                state->selectedIdx = state->x278->idx;
                state->x270 = state->x270->links[0];
                state->x274 = state->x274->links[0];
            }
            if ((s8) state->x29E > 0) {
                state->x29E = (u8) (state->x29E - 1);
            }
            if ((s8) state->x29E == 0) {
                HSD_JObjClearFlagsAll(state->x288, JOBJ_HIDDEN);
                _tyList_80312904(state->x278, (s8) state->x278->x24);
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

void _tyList_80313358(TyListState* state, s8 arg2, s8 arg3, s8 arg4)
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
            TyListArg* sub = entry->links[0];
            entry->x2C = sub->x30;
            _tyList_80312904(entry, state->entryCount + 1);
        }
    } else {
        for (i = 0; i < state->entryCount; i++) {
            TyListArg* entry = &state->entries[i];
            TyListArg* sub = entry->links[1];
            entry->x2C = sub->x30;
            _tyList_80312904(entry, state->entryCount + 1);
        }
    }
}

void _tyList_80313464(TyListArg* arg)
{
    TyListState* state = &_tyList_804A2AC0;
    s32 val;
    PAD_STACK(24);

    val = Toy_sbss_804D6EDC[arg->idx];

    Toy_803083D8(arg->jobjs[2], val);

    if (arg->jobjs[1] != NULL) {
        HSD_JObjUnref(arg->jobjs[1]);
        arg->jobjs[1] = NULL;
    }

    if (Toy_80304924(val) != 0) {
        arg->jobjs[1] = _tyList_80313508(((TyListState*) state)->gobj,
                                         "ToyFigureListMarkN_Top_joint", -8.4f,
                                         arg->x30, 0.0f);
    }
}

/// @todo Suspicious return
void* _tyList_80313508(HSD_GObj* parent, char* symbol_name, float x, float y,
                       float z)
{
    HSD_JObj* jobj;
    ToyED8Data* archive;
    void* joint;
    PAD_STACK(8);

    archive = Toy_sbss_804D6ED8;
    joint = HSD_ArchiveGetPublicAddress(archive->archive, symbol_name);

    if (joint == NULL) {
        OSPanic(__FILE__, 823,
                "*** Can't Get Public Address!(tyList Model)\n");
    } else {
        jobj = HSD_JObjLoadJoint(joint);

        if (x || y || z) {
            HSD_JObjSetTranslateX(jobj, x);
            HSD_JObjSetTranslateY(jobj, y);
            HSD_JObjSetTranslateZ(jobj, z);
        }

        if (parent != NULL) {
            HSD_JObj* parentJobj = GET_JOBJ(parent);
            HSD_JObj* child;
            HSD_JObjAddChild(parentJobj, jobj);
            child = parentJobj->child;
            while (child->next != NULL) {
                child = child->next;
            }
            return child;
        } else {
            HSD_GObj* gobj;
            gobj = GObj_Create(6, 7, 0);
            HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0x39, 0);
            return gobj;
        }
    }
}

void _tyList_80313774(void)
{
    TyListState* state = &_tyList_804A2AC0;
    TyModeState* mode = (TyModeState*) Toy_804A284C;
    ToyGlobalsS_* disp = (ToyGlobalsS_*) Toy_sbss_804D6EE0;
    TyArchiveData* archive = (TyArchiveData*) Toy_sbss_804D6ED8;
    s8* state_tail = (s8*) M2C_FIELD(&state, HSD_GObj**, 0x2AC);
    TyListArg* entry;
    HSD_JObj* root_jobj;
    f32 step;
    f32 pos;
    s16 idx;
    s32 i;
    s32 trophy_total;

    PAD_STACK(0x40);

    state->selectedIdx = Toy_804A284C[0x12A];
    state->x29B = mode->x1;
    state->x29C = mode->x2;

    if (Toy_GetTrophyTotal() <= 0xA) {
        state_tail[0xD] = mode->x3;
        state_tail[0xC] = mode->x3;
    } else {
        state_tail[0xD] = mode->x3;
        state_tail[0xC] = mode->x3;
    }

    trophy_total = Toy_GetTrophyTotal();
    if (Toy_GetTrophyTotal() <= 0xA) {
        state->entryCount = trophy_total + 2;
        idx = Toy_803062BC(disp->x140->x10);
    } else {
        state->entryCount = 0xC;
        idx = Toy_803062BC(disp->x140->x10);
    }

    for (i = 0; i < state->entryCount; i++) {
        entry = &state->entries[i];
        if (i == 0) {
            entry->links[0] = &state->entries[state->entryCount - 1];
        } else {
            entry->links[0] = &state->entries[i - 1];
        }
        if (i == state->entryCount - 1) {
            entry->links[1] = &state->entries[0];
        } else {
            entry->links[1] = &state->entries[i + 1];
        }
    }

    state->x278 = &state->entries[1];
    state->x270 = &state->entries[0];
    state->x274 = &state->entries[state->entryCount - 1];

    state->gobj = (HSD_GObj*) _tyList_80313508(
        NULL, "ToyFigurePanel_listpos01_joint", 0.0f, 0.0f, 0.0f);
    root_jobj = (HSD_JObj*) state->gobj;
    HSD_ASSERTMSG(0x3E1, root_jobj != NULL, "jobj");

    step = 5.11f - root_jobj->translate.y;
    pos = -step;
    state->x2A8 = step;

    entry = &state->entries[0];
    for (i = 0; i < state->entryCount; i++) {
        *(s32*) &entry->x28 = i;
        entry->jobjs[0] = _tyList_80313508(
            state->gobj, "ToyFigureListBase_Top_joint", 0.0f, pos, 0.0f);
        entry->jobjs[2] =
            entry->jobjs[0] != NULL ? entry->jobjs[0]->child : NULL;
        Toy_80306A48(entry->jobjs[0], NULL,
                     "ToyFigureListBase_Top_matanim_joint", NULL,
                     archive->data, 0);
        entry->texts[0] = HSD_SisLib_803A5ACC(0, _tyList_804D6EE8, 0.0f, 0.0f,
                                              17.2f, 640.0f, 64.0f);
        entry->texts[1] = HSD_SisLib_803A5ACC(0, _tyList_804D6EE8, 0.0f, 0.0f,
                                              17.2f, 64.0f, 64.0f);
        entry->texts[2] = HSD_SisLib_803A5ACC(0, _tyList_804D6EE8, 0.0f, 0.0f,
                                              17.2f, 192.0f, 64.0f);
        entry->x30 = pos;
        entry->x24 = i - 1;
        entry->idx = idx;
        idx++;
        if (idx >= Toy_GetTrophyTotal()) {
            idx = 0;
        }
        pos += step;
        entry = entry->links[1];
    }

    state->selectedIdx = state->x278->idx;
    state->jobj =
        _tyList_80313508(state->gobj, "ToyFigureListBaseend_Top_joint", 0.0f,
                         state->entries[0].x30, 0.0f);
    if (Toy_GetTrophyTotal() <= 0xA) {
        state->x288 = _tyList_80313508(
            state->gobj, "ToyFigureListCursor_Top_joint", 0.0f,
            state->entries[state_tail[0xC] + 1].x30, 0.0f);
    } else {
        state->x288 = _tyList_80313508(
            state->gobj, "ToyFigureListCursor_Top_joint", 0.0f,
            state->entries[state_tail[0xC] + 1].x30, 0.0f);
    }

    for (i = 0; i < state_tail[0xC]; i++) {
        _tyList_80313358(state, 0, 1, 1);
        _tyList_8031305C(state_tail, state, 0);
    }

    entry = &state->entries[0];
    for (i = 0; i < state->entryCount; i++) {
        if (entry->x24 == state_tail[0xC]) {
            state->selectedIdx = entry->idx;
            state->x278 = entry;
            break;
        }
        entry++;
    }

    _tyList_80312BAC(state, state_tail[0xC]);
}

void _tyList_80313BD8(HSD_GObj* gobj)
{
    TyListState* state = (TyListState*) &_tyList_804A2AC0;
    s32 i;
    TyListArg* p;
    TyListGobjEntry* g = &_tyList_804A2D6C;
    f32 f30;
    f32 f31;
    s8 v;

    if (Toy_GetTrophyTotal() > 10) {
        if (_tyList_8031305C(g, state, 1) != 0) {
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
            _tyList_80313358(state, -1, (s8) r, -1);
            return;
        }
    }

    /* Fall-through label: block_17 */
    f30 = Toy_80305D00();
    f31 = Toy_80305DB0();
    if (f30 < -0.8f) {
        M2C_FIELD(g, s8*, 0x12) = M2C_FIELD(g, s8*, 0x12) + 1;
        f30 = -1.0f;
        f31 = 0.0f;
    } else if (f30 > 0.8f) {
        M2C_FIELD(g, s8*, 0x12) = M2C_FIELD(g, s8*, 0x12) + 1;
        f30 = 1.0f;
        f31 = 0.0f;
    } else if (f31 < -0.6f || (Toy_80305C44() & 4)) {
        M2C_FIELD(g, s8*, 0x12) = M2C_FIELD(g, s8*, 0x12) + 1;
        f30 = 0.0f;
        f31 = 1.0f;
    } else if (f31 > 0.6f || (Toy_80305C44() & 8)) {
        M2C_FIELD(g, s8*, 0x12) = M2C_FIELD(g, s8*, 0x12) + 1;
        f30 = 0.0f;
        f31 = -1.0f;
    } else {
        f31 = 0.0f;
        M2C_FIELD(g, s8*, 0xF) = 0;
        f30 = f31;
        M2C_FIELD(g, s8*, 0x12) = 0;
        M2C_FIELD(g, s8*, 0x14) = 6;
        M2C_FIELD(g, s8*, 0x13) = 0;
        M2C_FIELD(g, s8*, 0x11) = 0;
        M2C_FIELD(g, s8*, 0x10) = 0;
    }

    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        Toy_80310660(0);
        _tyList_803148E4(0);
        mn_8022F268();
        ((TyModeState*) Toy_804A284C)->x4 = 1;
        return;
    }

    if (Toy_80305B88() & 0x200) {
        lbAudioAx_80024030(0);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        Toy_80310660(0);
        _tyList_803148E4(0);
        ((TyModeState*) Toy_804A284C)->x4 = 1;
        return;
    }

    if (Toy_GetTrophyTotal() == 0) {
        return;
    }

    if (Toy_80305B88() & 0x1100) {
        lbAudioAx_80024030(1);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        Toy_80310660(0);
        _tyList_803148E4(1);
        Toy_80310324();
        return;
    }

    if ((s8) M2C_FIELD(g, s8*, 0x12) > (s8) M2C_FIELD(g, s8*, 0x14)) {
        M2C_FIELD(g, s8*, 0x12) = M2C_FIELD(g, s8*, 0x14) + 1;
        M2C_FIELD(g, s8*, 0x14) = 3;
        M2C_FIELD(g, s8*, 0xF) = 0;
    }

    if ((f30 < 0.0f && f30 != (f32) (s8) M2C_FIELD(g, s8*, 0x10)) ||
        (Toy_80305B88() & 0x41))
    {
        M2C_FIELD(g, s8*, 0x10) = (s8) f30;
        state->x29B = state->x29B - 1;
        if ((s8) state->x29B < 0) {
            state->x29B = 2;
        }
        _tyList_80312BAC(state, M2C_FIELD(g, s8*, 0xC));
        lbAudioAx_80024030(1);
        return;
    }

    if ((f30 > 0.0f && f30 != (f32) (s8) M2C_FIELD(g, s8*, 0x10)) ||
        (Toy_80305B88() & 0x22))
    {
        M2C_FIELD(g, s8*, 0x10) = (s8) f30;
        state->x29B = state->x29B + 1;
        if ((s8) state->x29B >= 3) {
            state->x29B = 0;
        }
        _tyList_80312BAC(state, M2C_FIELD(g, s8*, 0xC));
        lbAudioAx_80024030(1);
        return;
    }

    if (Toy_GetTrophyTotal() < 2) {
        return;
    }

    if (Toy_GetTrophyTotal() > 10) {
        if (Toy_80305C44() & 0x400) {
            HSD_JObjSetFlagsAll(state->x288, JOBJ_HIDDEN);
            if (state->x274->idx == 0 ||
                state->x274->links[0]->idx + 9 < Toy_GetTrophyTotal())
            {
                _tyList_80313358(state, 9, 4, 0);
            } else {
                _tyList_80313358(
                    state, (s8) (Toy_GetTrophyTotal() - state->x274->idx), 4,
                    0);
            }
            state->pad_29D = state->x29E;
            return;
        }
        if (Toy_80305C44() & 0x800) {
            HSD_JObjSetFlagsAll(state->x288, JOBJ_HIDDEN);
            if (state->x270->idx == Toy_GetTrophyTotal() - 1 ||
                state->x270->links[1]->idx - 9 > 0)
            {
                _tyList_80313358(state, 9, 4, 1);
            } else {
                _tyList_80313358(state, (s8) state->x270->idx, 4, 1);
            }
            state->pad_29D = state->x29E;
            return;
        }
    }

    if (f31 == 0.0f) {
        return;
    }
    if ((s8) M2C_FIELD(g, s8*, 0xF) != 0) {
        return;
    }
    M2C_FIELD(g, s8*, 0xF) = 1;
    M2C_FIELD(g, s8*, 0xC) = (s8) ((f32) (s8) M2C_FIELD(g, s8*, 0xC) + f31);
    if ((s8) M2C_FIELD(g, s8*, 0xC) < 0) {
        M2C_FIELD(g, s8*, 0xC) = 0;
    } else if ((s8) M2C_FIELD(g, s8*, 0xC) > (s8) state->entryCount - 3) {
        M2C_FIELD(g, s8*, 0xC) = state->entryCount - 3;
    }

    if ((s8) M2C_FIELD(g, s8*, 0xC) != (s8) M2C_FIELD(g, s8*, 0xD)) {
        i = 0;
        M2C_FIELD(g, s8*, 0x12) = 0;
        p = &state->entries[0];
        M2C_FIELD(g, s8*, 0x13) = 0;
        M2C_FIELD(g, s8*, 0x11) = (s8) f31;
        for (; i < (s8) state->entryCount; i++, p++) {
            if (((s8*) p)[0x24] == M2C_FIELD(g, s8*, 0xC)) {
                state->selectedIdx = p->idx;
                state->x278 = p;
                lbAudioAx_80024030(2);
                HSD_JObjSetTranslateY(state->x288, p->x30);
            }
            _tyList_80312904(p, M2C_FIELD(state, s8*, 0x2B8));
        }
        M2C_FIELD(g, s8*, 0xD) = M2C_FIELD(g, s8*, 0xC);
        return;
    }

    if (Toy_GetTrophyTotal() <= 10) {
        return;
    }
    if ((s8) M2C_FIELD(g, s8*, 0x11) == 0) {
        M2C_FIELD(g, s8*, 0x13) = 5;
        M2C_FIELD(g, s8*, 0x12) = M2C_FIELD(g, s8*, 0x14) + 1;
        M2C_FIELD(g, s8*, 0x14) = 3;
        M2C_FIELD(g, s8*, 0xF) = 0;
    }
    M2C_FIELD(g, s8*, 0x11) = (s8) f31;
    v = M2C_FIELD(g, s8*, 0x13);
    if (v == 0) {
        M2C_FIELD(g, s8*, 0x13) = 1;
        return;
    }
    if (v < 5) {
        M2C_FIELD(g, s8*, 0x13) = v + 1;
        return;
    }

    p = &state->entries[0];
    for (i = 0; i < (s8) state->entryCount; i++, p++) {
        _tyList_80312904(p, state->entryCount);
    }
    HSD_JObjSetFlagsAll(state->x288, JOBJ_HIDDEN);
    if (f31 > 0.0f) {
        _tyList_80313358(state, 1, 6, 0);
    } else {
        _tyList_80313358(state, 1, 6, 1);
    }
}

void _tyList_8031438C(HSD_GObj* gobj)
{
    TyListState* state = &_tyList_804A2AC0;
    TyListGobjEntry* entry = &_tyList_804A2D6C;
    ToyED8Data* archive = Toy_sbss_804D6ED8;
    s32 i;
    HSD_Text* new_var;

    PAD_STACK(0x18);

    if (entry->x16) {
        if (entry->x16 > 1) {
            for (i = 0; i < 3; i++) {
                if (i == (s8) state->x29B) {
                    HSD_JObjReqAnim(archive->jobjs[i], 1.0f);
                } else {
                    HSD_JObjReqAnim(archive->jobjs[i], 0.0f);
                }
                HSD_AObjSetRate(archive->jobjs[0]->u.dobj->mobj->tobj->aobj,
                                0.0f);
            }
            HSD_JObjAnimAll((HSD_JObj*) archive->x0[10]);
        } else {
            TyListWaitData* wait_data = (TyListWaitData*) entry->x4;
            if (wait_data != NULL) {
                wait_data->x24 = 0;
                wait_data->x20 = 0x42100000;
            }
            state->x290 = HSD_SisLib_803A6754(3, _tyList_804D6EEC);
            state->x290->pos_z = 17.2f;
            new_var = state->x290;
            state->x290->font_size.x = 0.038f;
            new_var->font_size.y = 0.029f;
            state->x290->default_kerning = 1;
            state->x290->default_alignment = (double) 2;
            HSD_SisLib_803A6B98(state->x290, 290.0f, 320.0f, "%d",
                                Toy_GetTrophyTotal());
        }
        entry->x16--;
        return;
    }

    HSD_GObjProc_8038FED4(gobj);
    HSD_GObj_SetupProc(entry->x0, _tyList_80313BD8, 0);
    HSD_GObj_80390CD4(entry->x0);
}

void _tyList_80314504(HSD_GObj* gobj, int unused)
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

void _tyList_8031457C(void)
{
    TyListGobjEntry* entry = &_tyList_804A2D6C;
    ToyED8Data* archive = Toy_sbss_804D6ED8;
    HSD_CameraDescPerspective* desc;
    HSD_CObj* cobj;
    HSD_RectS16 viewport;
    Scissor scissor;
    Vec3 interest;
    Vec3 eye;
    PAD_STACK(8);

    /// @todo Is this really a reference to
    ///       #Toy_str_ScMenFigure_cam_int1_camera, or de-duplicated?
    desc = HSD_ArchiveGetPublicAddress(archive->archive,
                                       Toy_str_ScMenFigure_cam_int1_camera);
    if (desc != NULL) {
        entry->x0 = GObj_Create(1, 2, 0);
        cobj = lb_80013B14(desc);
        HSD_GObjObject_80390A70(entry->x0, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(entry->x0, Toy_80306954, 0);
        entry->x0->gxlink_prios = 0x9010000000000000ULL;
        HSD_GObj_SetupProc(entry->x0, _tyList_8031438C, 0);
        HSD_GObj_80390CD4(entry->x0);
        entry->x16 = 0x1A;
    }
    _tyList_804D6EEC =
        HSD_SisLib_803A611C(3, entry->x0, 0xC, 0xC, 0, 0x3F, 0, 0);
    if (desc != NULL) {
        entry->x4 = GObj_Create(1, 2, 0);
        cobj = lb_80013B14(desc);
        HSD_GObjObject_80390A70(entry->x4, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(entry->x4, _tyList_80314504, 0);
        entry->x4->gxlink_prios = 0x0210000000000000ULL;
        interest.x = 1.1f;
        interest.y = -0.24f;
        interest.z = 0.0f;
        HSD_CObjSetInterest(cobj, &interest);
        eye.x = 1.1f;
        eye.y = -0.24f;
        eye.z = 40.0596313f;
        HSD_CObjSetEyePosition(cobj, &eye);
        viewport.xmin = 0x76;
        viewport.ymin = 0x4E;
        viewport.xmax = 0x230;
        viewport.ymax = 0x19C;
        HSD_CObjSetViewport(cobj, &viewport);
        viewport.ymin = 0x60;
        if (Toy_GetTrophyTotal() < 10) {
            viewport.ymax = Toy_GetTrophyTotal() * 0x1E + 0x60;
        } else {
            viewport.ymax = 0x18A;
        }
        scissor.left = viewport.xmin;
        scissor.right = viewport.xmax;
        scissor.top = viewport.ymin;
        scissor.bottom = viewport.ymax;
        HSD_CObjSetScissor(cobj, &scissor);
        _tyList_804D6EE8 =
            HSD_SisLib_803A611C(0, entry->x4, 0xB, 0xB, 0, 0x3E, 0, 0);
    }
}

void tyList_803147C4(void)
{
    char* data = (char*) &_tyList_804A2AC0;
    TyArchiveData* archive;
    LightList** jobj;
    u8 new_var;
    HSD_GObj** gobj;
    PAD_STACK(8);

    memzero(data + 0x2AC, 0x18);
    _tyList_8031457C();
    memzero(data + 0x2C4, 0x14);

    gobj = (HSD_GObj**) (data + 0x2C4);
    archive = (TyArchiveData*) Toy_sbss_804D6ED8;

    if (archive->data == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        OSPanic(__FILE__, 1590, "");
    }

    jobj =
        HSD_ArchiveGetPublicAddress(archive->data, "ScMenFigure_scene_lights");
    if (jobj != NULL) {
        *gobj = GObj_Create(2, 3, 0);
        HSD_GObjObject_80390A70(*gobj, new_var = (u8) HSD_GObj_804D784A,
                                Toy_LoadLObjList(jobj, 0));
        GObj_SetupGXLink(*gobj, HSD_GObj_LObjCallback, 52, 0);
    }

    Toy_80307470(0);
    if (Toy_GetTrophyTotal() != 0) {
        memzero(data, 0x2AC);
        _tyList_80313774();
    }
    HSD_PadRenewStatus();
}

void _tyList_803148E4(s32 arg0)
{
    TyListState* state = (TyListState*) &_tyList_804A2AC0;
    TyListGobjEntry* entry = M2C_FIELD(state, TyListGobjEntry**, 0x2AC);
    TyArchiveData* archive;
    HSD_GObj** gobj_2C4;
    PAD_STACK(8);

    gobj_2C4 = M2C_FIELD(state, HSD_GObj***, 0x2C4);
    archive = (TyArchiveData*) Toy_sbss_804D6ED8;

    if (Toy_GetTrophyTotal() != 0) {
        if (arg0 != 0) {
            TyModeState* mode = (TyModeState*) Toy_804A284C;
            ((s16*) Toy_804A284C)[0x12A] = state->selectedIdx;
            ((s16*) Toy_804A284C)[0x12B] =
                Toy_sbss_804D6EDC[state->selectedIdx];
            mode->x1 = state->x29B;
            mode->x2 = state->x29C;
            mode->x3 = entry->x0C;
        } else {
            if (Toy_GetTrophyTotal() != 0) {
                s16 val = Toy_sbss_804D6EDC[state->selectedIdx];
                Toy_803067BC(0, 0);
                state->selectedIdx = Toy_803062BC(val);
            }
            {
                TyModeState* mode = (TyModeState*) Toy_804A284C;
                ((s16*) Toy_804A284C)[0x12A] = state->selectedIdx;
                ((s16*) Toy_804A284C)[0x12B] =
                    Toy_sbss_804D6EDC[state->selectedIdx];
                mode->x1 = 0;
                mode->x2 = 0;
                mode->x3 = 0;
            }
        }

        if (Toy_80304924(Toy_sbss_804D6EDC[state->selectedIdx]) != 0) {
            Toy_80304988(Toy_sbss_804D6EDC[state->selectedIdx]);
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

    if (*gobj_2C4 != NULL && arg0 != 0) {
        HSD_GObjPLink_80390228(*gobj_2C4);
    }

    if (entry->x0 != NULL) {
        HSD_GObjProc_8038FED4(entry->x0);
        if (arg0 != 0) {
            HSD_GObjPLink_80390228(entry->x0);
        }
    }

    if (entry->x4 != NULL && arg0 != 0) {
        HSD_GObjPLink_80390228(entry->x4);
    }
}

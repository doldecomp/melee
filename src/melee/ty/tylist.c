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
#include <baselib/aobj.h>
#include <baselib/archive.h>
#include <baselib/cobj.h>
#include <baselib/controller.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/sislib.h>
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

typedef struct {
    HSD_GObj* gobj;
    u8 pad[0x14];
    HSD_JObj* jobjs[3];
} TyListArchiveAnimData;

typedef struct {
    u8 pad[0x20];
    f32 x20;
    s32 x24;
} TyListWaitData;

typedef struct {
    HSD_GObj* x0;
    HSD_GObj* x4;
    u8 pad_8[4];
    s8 xC;
    u8 pad_D[9];
    s8 x16;
} TyListCameraState;

typedef struct {
    u8 pad[0x10];
    s16 x10;
} TyListDispEntry;

typedef struct {
    u8 pad[0x140];
    TyListDispEntry* x140;
} TyListDispState;

static void fn_80313BD8(HSD_GObj* gobj);

extern char un_803FE5E8[];
extern TyListCameraState un_804A2D6C;
extern s32 un_804D6EE8;
extern s32 un_804D6EEC;
extern GXColor lb_804D3760;
extern GXColor lb_804D3764;

static char un_804D5A88[3] = "%d";

void un_803124BC(void)
{
    char* data = un_803FDD18;
    u16* table1;
    s16* list;
    u16* table2;
    s32 i;

    table1 = gmMainLib_8015CC78();
    table2 = gmMainLib_8015CC84();

    if (un_804D6ED0 == NULL) {
        char* archiveName;
        if (lbLang_IsSavedLanguageJP()) {
            archiveName = data + 0x608;
        } else {
            archiveName = data + 0x614;
        }
        un_804D6ED0 = lbArchive_LoadSymbols(archiveName, &un_804D6EC4,
                                            data + 0x9DC, &un_804D6EC0,
                                            data + 0x9EC, &un_804D6EBC,
                                            data + 0x9FC, &un_804D6EB8,
                                            data + 0xA0C, &un_804D6EB4,
                                            data + 0xA20, &un_804D6EB0,
                                            data + 0xA30, &un_804D6EAC,
                                            data + 0xA44, NULL);
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
    char* data = un_803FDD18;
    s32 i;
    u16* table1;
    u16* table2;

    ((TyModeState*) un_804A284C)->x4 = 0;
    table1 = gmMainLib_8015CC78();
    table2 = gmMainLib_8015CC84();

    if (un_804D6ED0 == NULL) {
        char* archiveName;
        if (lbLang_IsSavedLanguageJP()) {
            archiveName = data + 0x608;
        } else {
            archiveName = data + 0x614;
        }
        un_804D6ED0 = lbArchive_LoadSymbols(archiveName, &un_804D6EC4,
                                            data + 0x9DC, &un_804D6EC0,
                                            data + 0x9EC, &un_804D6EBC,
                                            data + 0x9FC, &un_804D6EB8,
                                            data + 0xA0C, &un_804D6EB4,
                                            data + 0xA20, &un_804D6EB0,
                                            data + 0xA30, &un_804D6EAC,
                                            data + 0xA44, NULL);
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
        un_804D6ECC = lbArchive_LoadSymbols(data + 0xA58, &un_804D6EA8,
                                            data + 0xA64, &un_804D6EA4,
                                            data + 0xA74, NULL);
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

void un_80312904(TyListArg* arg, s8 arg1)
{
    TyListState* state = (TyListState*) un_804A2AC0;
    HSD_JObj* jobj;
    HSD_JObj* parent_jobj;
    f32 pos_x;
    f32 pos_y;
    f32 pos_z;
    s32 show;

    if (arg->idx != -1) {
        if (un_GetTrophyTotal() < 0xB) {
            if (arg->x24 == -1 || arg->x24 == state->entryCount - 2) {
                show = 0;
            } else {
                show = 1;
            }
        } else {
            show = 1;
        }
        if (show != 0) {
            jobj = arg->jobjs[0];
            pos_x = HSD_JObjGetTranslationX(jobj) - 6.5f;
            parent_jobj = GET_JOBJ(state->gobj);
            pos_y = (-arg->x30 - HSD_JObjGetTranslationY(parent_jobj)) - 0.41f;
            pos_z = HSD_JObjGetTranslationZ(parent_jobj);
            if (arg1 != 0x63) {
                if (arg->x24 == arg1) {
                    arg->texts[0]->text_color = lb_804D3764;
                    arg->texts[1]->text_color = lb_804D3764;
                    arg->texts[2]->text_color = lb_804D3764;
                } else {
                    arg->texts[0]->text_color = lb_804D3760;
                    arg->texts[1]->text_color = lb_804D3760;
                    arg->texts[2]->text_color = lb_804D3760;
                }
            }
            arg->texts[0]->pos_x = pos_x;
            arg->texts[0]->pos_y = pos_y;
            arg->texts[0]->pos_z = pos_z;
            arg->texts[0]->font_size.x = 0.028f;
            arg->texts[0]->font_size.y = 0.029f;
            arg->texts[0]->default_kerning = 1;
            HSD_SisLib_803A6368(arg->texts[0],
                                un_803063D4(un_80308354(arg->idx), 2, 0x128));

            arg->texts[1]->pos_x = pos_x + 14.7f;
            arg->texts[1]->pos_y = pos_y;
            arg->texts[1]->pos_z = pos_z;
            arg->texts[1]->font_size.x = 0.028f;
            arg->texts[1]->font_size.y = 0.029f;
            HSD_SisLib_803A6368(arg->texts[1], 0x13B);

            un_80312834(arg->texts[2]->string_buffer,
                        un_803048C0(un_80308354(arg->idx)));
            arg->texts[2]->default_alignment = 2;
            arg->texts[2]->default_kerning = 1;
            arg->texts[2]->pos_x = pos_x + 10.5f;
            arg->texts[2]->pos_y = pos_y;
            arg->texts[2]->pos_z = pos_z;
            arg->texts[2]->font_size.x = 0.038f;
            arg->texts[2]->font_size.y = 0.029f;
            HSD_SisLib_803A6368(arg->texts[2], arg->x28 + 0x12E);
        }
    }
}

void un_80312BAC(TyListState* state, s8 arg1)
{
    TyListArchiveAnimData* archive = un_804D6ED8;
    TyListArg* entry;
    HSD_JObj* jobj;
    s16 idx;
    s32 i;

    idx = un_804D6EDC[state->selectedIdx];
    un_803067BC(state->x29B, state->x29C);
    state->selectedIdx = un_803062BC(idx);

    idx = state->selectedIdx;
    for (i = 0; i < state->x278->x24 + 1; i++) {
        idx--;
        if (idx < 0) {
            idx = un_GetTrophyTotal() - 1;
        }
    }

    jobj = state->jobj;
    entry = state->x270;
    if (jobj != NULL) {
        HSD_JObjSetTranslateY(jobj, entry->x30);
    }

    for (i = 0; i < state->entryCount; i++) {
        entry->idx = idx;
        un_80312904(entry, arg1);
        un_80313464(entry);
        if (entry->x24 >= 0 && entry->x24 < state->entryCount - 2 &&
            entry->idx == un_GetTrophyTotal() - 1)
        {
            jobj = state->jobj;
            if (jobj != NULL) {
                HSD_JObjSetTranslateY(jobj, entry->x30);
            }
        }
        entry = entry->links[1];
        idx++;
        if (idx >= un_GetTrophyTotal()) {
            idx = 0;
        }
    }

    for (i = 0; i < 3; i++) {
        HSD_JObj* anim_jobj = archive->jobjs[i];
        HSD_JObjReqAnim(anim_jobj, i == state->x29B ? 1.0f : 0.0f);
        HSD_AObjSetRate(anim_jobj->aobj, 0.0f);
        HSD_JObjAnim(anim_jobj);
    }
}

inline void un_80312E88_inline(TyListArg* arg)
{
    HSD_JObj* jobj;
    char* data = un_804A2AC0;

    s32 i;
    for (i = 0; i < 3; i++) {
        jobj = arg->jobjs[i];
        if (jobj == NULL) {
            continue;
        }
        if (i == 2) {
            continue;
        }
        HSD_JObjSetTranslateY(jobj, arg->x30);

        if (arg->idx == un_GetTrophyTotal() - 1) {
            jobj = ((TyListState*) data)->jobj;
            HSD_JObjSetTranslateY(jobj, arg->x30);
        }
    }
}

void un_80312E88(TyListArg* arg, float delta)
{
    TyListArg* ptr;

    arg->x30 = arg->x30 + delta;

    if (999.0f == delta) {
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

    un_80312E88_inline(arg);

    un_80312904(arg, 0x63);
    un_80313464(arg);
}

s8 un_8031305C(TyListState* state, s8 arg2)
{
    TyListArg* entry;
    s16 idx;
    s32 i;
    f32 delta;

    if (state->x29F > 0) {
        delta = state->x2A4;
        if (state->x2A1 == 0) {
            delta = -delta;
        }

        entry = state->entries;
        for (i = 0; i < state->entryCount; i++) {
            if ((state->x2A1 != 0 || entry->x24 != -1) &&
                (state->x2A1 != 1 || state->entryCount - 1 != entry->x24))
            {
                un_80312E88(entry, delta);
            }
            entry++;
        }

        state->x29F--;
        if (state->x29F == 0) {
            entry = state->entries;
            for (i = 0; i < state->entryCount; i++) {
                un_80312E88(entry, un_804DDE4C);
                if (state->x2A1 == 0) {
                    entry->x24--;
                    if (entry->x24 < -1) {
                        entry->x24 = state->entryCount - 2;
                    }
                } else {
                    entry->x24++;
                    if (entry->x24 >= state->entryCount - 1) {
                        entry->x24 = -1;
                    }
                }
                entry = entry->links[1];
            }

            if (state->x2A1 == 0) {
                state->x270->idx = state->x274->idx + 1;
                if (state->x270->idx >= un_GetTrophyTotal()) {
                    state->x270->idx = 0;
                }
                un_80312904(state->x270, un_804A2D6C.xC);
                state->x278 = state->x278->links[1];
                state->selectedIdx = state->x278->idx;
                state->x270 = state->x270->links[1];
                state->x274 = state->x274->links[1];
            } else {
                state->x274->idx = state->x270->idx - 1;
                if (state->x274->idx < 0) {
                    state->x274->idx = un_GetTrophyTotal() - 1;
                }
                un_80312904(state->x274, un_804A2D6C.xC);
                state->x278 = state->x278->links[0];
                state->selectedIdx = state->x278->idx;
                state->x270 = state->x270->links[0];
                state->x274 = state->x274->links[0];
            }

            if (state->x29E > 0) {
                state->x29E--;
            }
            if (state->x29E == 0) {
                HSD_JObjClearFlagsAll(state->jobj, 0x10);
                entry = state->x278;
                un_80312904(entry, entry->x24);
                if (HSD_PadCopyStatus->button & 0xC00) {
                    state->x2A0 = 5;
                } else {
                    state->x2A0 = 0;
                }
            }
            if (arg2 != 0) {
                lbAudioAx_80024030(2);
            }
        }
    }
    idx = state->x29F;
    return idx;
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
            TyListArg* sub = entry->links[0];
            entry->x2C = sub->x30;
            un_80312904(entry, state->entryCount + 1);
        }
    } else {
        for (i = 0; i < state->entryCount; i++) {
            TyListArg* entry = &state->entries[i];
            TyListArg* sub = entry->links[1];
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

    un_803083D8(arg->jobjs[2], val);

    if (arg->jobjs[1] != NULL) {
        HSD_JObjUnref(arg->jobjs[1]);
        arg->jobjs[1] = NULL;
    }

    if (un_80304924(val) != 0) {
        arg->jobjs[1] = un_80313508(((TyListState*) data)->gobj, un_803FE8D0,
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
        HSD_JObjSetTranslateX(jobj, x);
        HSD_JObjSetTranslateY(jobj, y);
        HSD_JObjSetTranslateZ(jobj, z);
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

void un_80313774(void)
{
    TyListState* state = (TyListState*) un_804A2AC0;
    TyArchiveData* archive = un_804D6ED8;
    TyListDispState* disp = un_804D6EE0;
    TyListArg* entry;
    HSD_JObj* root_jobj;
    f32 step;
    f32 pos;
    s16 idx;
    s32 i;

    state->selectedIdx = un_804A284C[0x12A];
    state->x29B = un_804A284C[1];
    state->x29C = un_804A284C[2];
    state->x2B8 = un_804A284C[3];
    *(u8*) ((u8*) state + 0x2B9) = un_804A284C[3];

    if (un_GetTrophyTotal() <= 0xA) {
        state->entryCount = un_GetTrophyTotal() + 2;
    } else {
        state->entryCount = 0xC;
    }

    idx = un_803062BC(disp->x140->x10);
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

    state->gobj = (HSD_GObj*) un_80313508(NULL, un_803FE880 + 0xAC, 0.0f, 0.0f,
                                          0.0f);
    root_jobj = (HSD_JObj*) state->gobj;
    HSD_ASSERTMSG(0x3E1, root_jobj != NULL, "jobj");

    step = 5.11f - root_jobj->translate.y;
    pos = -step;
    state->x2A8 = step;

    entry = &state->entries[0];
    for (i = 0; i < state->entryCount; i++) {
        entry->x28 = i;
        entry->jobjs[0] = un_80313508(state->gobj, un_803FE880 + 0xCC, 0.0f, pos, 0.0f);
        entry->jobjs[2] = entry->jobjs[0] != NULL ? entry->jobjs[0]->child : NULL;
        un_80306A48(entry->jobjs[0], NULL, un_803FE880 + 0xE8, NULL, archive->data, 0);
        entry->texts[0] = HSD_SisLib_803A5ACC(0, un_804D6EE8, 0.0f, 0.0f, 17.2f,
                                              640.0f, 64.0f);
        entry->texts[1] = HSD_SisLib_803A5ACC(0, un_804D6EE8, 0.0f, 0.0f, 17.2f,
                                              64.0f, 64.0f);
        entry->texts[2] = HSD_SisLib_803A5ACC(0, un_804D6EE8, 0.0f, 0.0f, 17.2f,
                                              192.0f, 64.0f);
        entry->x30 = pos;
        entry->x24 = i - 1;
        entry->idx = idx;
        idx++;
        if (idx >= un_GetTrophyTotal()) {
            idx = 0;
        }
        pos += step;
        entry = entry->links[1];
    }

    state->selectedIdx = state->x278->idx;
    state->jobj =
        un_80313508(state->gobj, un_803FE880 + 0x10C, 0.0f, state->x278->x30, 0.0f);
    state->x288 = un_80313508(state->gobj, un_803FE880 + 0x12C, 0.0f,
                              state->entries[state->x2B8].x30, 0.0f);

    for (i = 0; i < state->x2B8; i++) {
        un_80313358(state, 0, 1, 1);
        un_8031305C(state, 0);
    }

    entry = &state->entries[0];
    for (i = 0; i < state->entryCount; i++) {
        if (entry->x24 == state->x2B8) {
            state->selectedIdx = entry->idx;
            state->x278 = entry;
            break;
        }
        entry++;
    }

    un_80312BAC(state, state->x2B8);
}

void fn_80313BD8(HSD_GObj* gobj)
{
    TyListState* state = (TyListState*) un_804A2AC0;
    u8* scroll = (u8*) state + 0x2AC;
    f32 stick_x;
    f32 stick_y;
    f32 move_x;
    f32 move_y;
    s32 i;
    TyListArg* entry;

    if (un_GetTrophyTotal() > 0xA && un_8031305C(state, 1) != 0) {
        return;
    }

    if (state->x2A0 != 0) {
        state->x2A0--;
        return;
    }

    if (state->x29E != 0) {
        s32 half = state->x29D / 2;
        s8 count;
        if ((state->x29D % 2) != 0) {
            if (state->x29E <= half) {
                count = 5 - state->x29E;
            } else {
                count = 4 - (state->x29D - state->x29E);
            }
        } else if (state->x29E == half) {
            count = 4 - (state->x29D - (state->x29E + 1));
        } else if (state->x29E < half) {
            count = 4 - state->x29E;
        } else {
            count = 4 - (state->x29D - state->x29E);
        }
        if (count < 2) {
            count = 2;
        }
        un_80313358(state, -1, count, -1);
        return;
    }

    stick_x = un_80305D00();
    stick_y = un_80305DB0();
    move_x = 0.0f;
    move_y = 0.0f;

    if (stick_x < -0.8f) {
        scroll[0x12]++;
        move_x = -1.0f;
    } else if (stick_x > 0.8f) {
        scroll[0x12]++;
        move_x = 1.0f;
    } else if (stick_y < -0.6f || (un_80305C44() & 4)) {
        scroll[0x12]++;
        move_y = 1.0f;
    } else if (stick_y > 0.6f || (un_80305C44() & 8)) {
        scroll[0x12]++;
        move_y = -1.0f;
    } else {
        move_y = 0.0f;
        scroll[0xF] = 0;
        scroll[0x12] = 0;
        scroll[0x14] = 6;
        scroll[0x13] = 0;
        scroll[0x11] = 0;
        scroll[0x10] = 0;
        move_x = 0.0f;
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

    if (un_GetTrophyTotal() != 0 && (un_80305B88() & 0x1100)) {
        lbAudioAx_80024030(1);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        un_80310660(0);
        un_803148E4(1);
        un_80310324();
        return;
    }

    if (scroll[0x12] > scroll[0x14]) {
        scroll[0x12] = scroll[0x14] + 1;
        scroll[0x14] = 3;
        scroll[0xF] = 0;
    }

    if (((move_x < 0.0f) && (move_x != (s8) scroll[0x10])) ||
        (un_80305B88() & 0x41))
    {
        scroll[0x10] = (s8) move_x;
        state->x29B--;
        if (state->x29B < 0) {
            state->x29B = 2;
        }
        un_80312BAC(state, scroll[0xC]);
        lbAudioAx_80024030(1);
        return;
    }

    if (((move_x > 0.0f) && (move_x != (s8) scroll[0x10])) ||
        (un_80305B88() & 0x22))
    {
        scroll[0x10] = (s8) move_x;
        state->x29B++;
        if (state->x29B >= 3) {
            state->x29B = 0;
        }
        un_80312BAC(state, scroll[0xC]);
        lbAudioAx_80024030(1);
        return;
    }

    if (un_GetTrophyTotal() >= 2) {
        if (un_GetTrophyTotal() > 0xA) {
            if (un_80305C44() & 0x400) {
                HSD_JObjSetFlagsAll(state->x288, 0x10);
                if (state->x274->idx == 0 ||
                    state->x274->links[0]->idx + 9 < un_GetTrophyTotal())
                {
                    un_80313358(state, 9, 4, 0);
                } else {
                    un_80313358(state, un_GetTrophyTotal() - state->x274->idx, 4,
                                0);
                }
                state->x29D = state->x29E;
                return;
            }
            if (un_80305C44() & 0x800) {
                HSD_JObjSetFlagsAll(state->x288, 0x10);
                if (state->x270->idx == un_GetTrophyTotal() - 1 ||
                    state->x270->links[1]->idx - 9 > 0)
                {
                    un_80313358(state, 9, 4, 1);
                } else {
                    un_80313358(state, state->x270->links[1]->idx, 4, 1);
                }
                state->x29D = state->x29E;
                return;
            }
        }

        if (move_y != 0.0f && scroll[0xF] == 0) {
            scroll[0xF] = 1;
            scroll[0xC] = (s8) ((s8) scroll[0xC] + move_y);
            if ((s8) scroll[0xC] < 0) {
                scroll[0xC] = 0;
            } else if ((s8) scroll[0xC] > state->entryCount - 3) {
                scroll[0xC] = state->entryCount - 3;
            }
            if ((s8) scroll[0xC] != (s8) scroll[0xD]) {
                scroll[0x12] = 0;
                scroll[0x13] = 0;
                scroll[0x11] = (s8) move_y;
                entry = state->entries;
                for (i = 0; i < state->entryCount; i++) {
                    if (entry->x24 == (s8) scroll[0xC]) {
                        state->selectedIdx = entry->idx;
                        state->x278 = entry;
                        lbAudioAx_80024030(2);
                        if (state->jobj != NULL) {
                            state->jobj->translate.y = entry->x30;
                            HSD_JObjSetMtxDirtySub(state->jobj);
                        }
                    }
                    un_80312904(entry, state->x2B8);
                    entry++;
                }
                scroll[0xD] = scroll[0xC];
                return;
            }

            if (un_GetTrophyTotal() > 0xA) {
                if ((s8) scroll[0x11] == 0) {
                    scroll[0x13] = 5;
                    scroll[0x12] = scroll[0x14] + 1;
                    scroll[0x14] = 3;
                    scroll[0xF] = 0;
                }
                scroll[0x11] = (s8) move_y;
                if ((s8) scroll[0x13] == 0) {
                    scroll[0x13] = 1;
                    return;
                }
                if ((s8) scroll[0x13] < 5) {
                    scroll[0x13]++;
                    return;
                }
                entry = state->entries;
                for (i = 0; i < state->entryCount; i++) {
                    un_80312904(entry, state->entryCount);
                    entry++;
                }
                HSD_JObjSetFlagsAll(state->x288, 0x10);
                if (move_y > 0.0f) {
                    un_80313358(state, 1, 6, 0);
                    return;
                }
                un_80313358(state, 1, 6, 1);
            }
        }
    }
}

void fn_8031438C(HSD_GObj* gobj)
{
    char* data = un_804A2AC0;
    char* state = data + 0x2AC;
    TyListArchiveAnimData* archive = un_804D6ED8;
    HSD_JObj** jobjs = archive->jobjs;
    s32 i;

    if ((s8) state[0x16] != 0) {
        if ((s8) state[0x16] > 1) {
            for (i = 0; i < 3; i++) {
                HSD_JObj* jobj = jobjs[i];
                HSD_JObjReqAnim(jobj, i == *(s8*) (data + 0x29B) ? 1.0f : 0.0f);
                HSD_AObjSetRate(jobj->aobj, 0.0f);
            }
            HSD_JObjAnimAll(GET_JOBJ(archive->gobj));
        } else {
            TyListWaitData* wait_data = *(TyListWaitData**) (state + 4);
            if (wait_data != NULL) {
                wait_data->x24 = 0;
                wait_data->x20 = 36.0f;
            }
            *(HSD_Text**) (data + 0x290) = HSD_SisLib_803A6754(3, un_804D6EEC);
            (*(HSD_Text**) (data + 0x290))->pos_z = 17.2f;
            (*(HSD_Text**) (data + 0x290))->font_size.x = 0.038f;
            (*(HSD_Text**) (data + 0x290))->font_size.y = 0.029f;
            (*(HSD_Text**) (data + 0x290))->default_kerning = 1;
            (*(HSD_Text**) (data + 0x290))->default_alignment = 2;
            HSD_SisLib_803A6B98(*(HSD_Text**) (data + 0x290), 290.0f, 320.0f,
                                un_804D5A88,
                                un_GetTrophyTotal());
        }
        state[0x16] = state[0x16] - 1;
        return;
    }
    HSD_GObjProc_8038FED4(gobj);
    HSD_GObj_SetupProc(*(HSD_GObj**) state, fn_80313BD8, 0);
    HSD_GObj_80390CD4(*(HSD_GObj**) state);
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
    HSD_CameraDescPerspective* cam_desc;
    HSD_CObj* cobj;
    HSD_RectS16 viewport;
    Scissor scissor;
    Vec3 interest;
    Vec3 eye;
    PAD_STACK(8);

    cam_desc = HSD_ArchiveGetPublicAddress(((TyArchiveData*) un_804D6ED8)->data,
                                           un_803FE5E8);
    if (cam_desc != NULL) {
        un_804A2D6C.x0 = GObj_Create(1, 2, 0);
        HSD_GObjObject_80390A70(un_804A2D6C.x0, HSD_GObj_804D784B,
                                lb_80013B14(cam_desc));
        GObj_SetupGXLinkMax(un_804A2D6C.x0, (GObj_RenderFunc) un_80306954, 0);
        un_804A2D6C.x0->gxlink_prios = 0x9010000000000000ULL;
        HSD_GObj_SetupProc(un_804A2D6C.x0, fn_8031438C, 0);
        HSD_GObj_80390CD4(un_804A2D6C.x0);
        un_804A2D6C.x16 = 0x1A;
    }

    un_804D6EEC =
        HSD_SisLib_803A611C(3, un_804A2D6C.x0, 0xC, 0xC, 0, 0x3F, 0, 0);

    if (cam_desc != NULL) {
        un_804A2D6C.x4 = GObj_Create(1, 2, 0);
        cobj = lb_80013B14(cam_desc);
        HSD_GObjObject_80390A70(un_804A2D6C.x4, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(un_804A2D6C.x4, (GObj_RenderFunc) fn_80314504, 0);
        un_804A2D6C.x4->gxlink_prios = 0x0210000000000000ULL;

        interest.x = 1.1f;
        interest.y = -0.24f;
        interest.z = 0.0f;
        HSD_CObjSetInterest(cobj, &interest);

        eye.x = 1.1f;
        eye.y = -0.24f;
        eye.z = 40.05963f;
        HSD_CObjSetEyePosition(cobj, &eye);

        viewport.xmin = 0x76;
        viewport.xmax = 0x230;
        viewport.ymin = 0x4E;
        viewport.ymax = 0x19C;
        HSD_CObjSetViewport(cobj, &viewport);

        scissor.left = 0x76;
        scissor.right = 0x230;
        scissor.top = 0x60;
        if (un_GetTrophyTotal() < 0xA) {
            scissor.bottom = un_GetTrophyTotal() * 0x1E + 0x60;
        } else {
            scissor.bottom = 0x18A;
        }
        HSD_CObjSetScissor(cobj, &scissor);

        un_804D6EE8 =
            HSD_SisLib_803A611C(0, un_804A2D6C.x4, 0xB, 0xB, 0, 0x3E, 0, 0);
    }
}

void un_803147C4(void)
{
    char* data = un_804A2AC0;
    char* strs = un_803FE880;
    TyArchiveData* archive;
    HSD_JObj* jobj;
    HSD_GObj** gobj;
    PAD_STACK(8);

    memzero(data + 0x2AC, 0x18);
    un_8031457C();
    gobj = (HSD_GObj**) (data + 0x2C4);
    memzero(gobj, 0x14);

    archive = un_804D6ED8;

    if (archive->data == NULL) {
        OSReport(strs + 0x14C);
        OSPanic(strs + 0x70, 0x636, un_804D5A8C);
    }

    jobj = HSD_ArchiveGetPublicAddress(archive->data, strs + 0x170);
    if (jobj != NULL) {
        *gobj = GObj_Create(2, 3, 0);
        HSD_GObjObject_80390A70(*gobj, (u8) HSD_GObj_804D784A,
                                un_80306EEC(jobj, 0));
        GObj_SetupGXLink(*gobj, HSD_GObj_LObjCallback, 0x34, 0);
    }

    un_80307470(0);
    if (un_GetTrophyTotal() != 0) {
        memzero(data, 0x2AC);
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

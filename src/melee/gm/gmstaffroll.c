#include "gmstaffroll.h"

#include "gm_unsplit.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gm/gmmain_lib.h"
#include "if/textlib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbbgflash.h"
#include "lb/lblanguage.h"
#include "sc/types.h"

#include <baselib/particle.h>
#include <math_ppc.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <trigf.h>

#include "baselib/psappsrt.h"
#include "baselib/psstructs.h"

struct staffInfo_t {
    char pad_0[0x948];
};
STATIC_ASSERT(sizeof(struct staffInfo_t) == 0x948);

/* 4D67F8 */ static struct {
    HSD_Text* win[2];
    int x8;
}* staffInfo;

struct staffInfoSortBuf_t {
    char pad_0[0x2E68];
};
STATIC_ASSERT(sizeof(struct staffInfoSortBuf_t) == 0x2E68);

typedef struct {
    int index;
    HSD_JObj* jobj;
    Mtx mtx;
    s32 x38;
} SortBufEntry;

/* 4D67FC */ static SortBufEntry* staffInfoSortBuf;

struct gm_804D6804_t {
    /* +0 */ float x0;
    /* +4 */ float x4;
};

/* 4D6804 */ static struct gm_804D6804_t gm_804D6804;
/* 4D680C */ static HSD_Text* gm_804D680C;

/* 4D6810 */ static s32 gm_804D6810;
/* 4D6814 */ static s32 gm_804D6814;
/* 4D6818 */ static s32 gm_804D6818;
/* 4D681C */ static s32 gm_804D681C;
/* 4D6820 */ static s32 gm_804D6820;
/* 4D6824 */ static f32 gm_804D6824;
/* 4D6828 */ static f32 gm_804D6828;
/* 4D682C */ static HSD_JObj* gm_804D682C;
/* 4D6830 */ static HSD_CObj* gm_804D6830;
/* 4D6834 */ static HSD_CObj* gm_804D6834;
/* 4D6838 */ static HSD_Fog* gm_804D6838;
/* 4D683C */ static UNK_T gm_804D683C;
/* 4D6840 */ static SceneDesc* gm_804D6840;
/* 4D6844 */ static DynamicModelDesc** gm_804D6844;
/* 4D6848 */ static s32 gm_804D6848;
/* 4D684C */ static s32 gm_804D684C;

typedef struct {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 pad_01[3];
    /* 0x04 */ int (*check)(s16);
    /* 0x08 */ s16 check_arg;
    /* 0x0A */ u8 pad_0A[2];
    /* 0x0C */ int alt_page;
    /* 0x10 */ u8 has_check;
    /* 0x11 */ u8 x11[2];
    /* 0x13 */ u8 pad_13;
} StaffEntryData;

/* 3DBFD8 */ static StaffEntryData gm_803DBFD8[198] = { 0 };
extern f32 gm_803DD1C8[0x13];
extern GXColor gm_804D42B8;
extern GXColor gm_804D42BC;
extern GXColor gm_804D42C0;
extern GXColor gm_804D42C4;
extern GXColor gm_804D42C8;
extern GXColor gm_804D42CC;
extern s32 gm_804DAAEC;

bool gm_801AA644(void)
{
    return gmMainLib_8015EDD4();
}

bool gm_801AA664(CharacterKind arg0)
{
    return gm_80164840(arg0);
}

bool gm_801AA688(void)
{
    PAD_STACK(4);
    return gm_80164840(CKIND_MARS) || gm_80164840(CKIND_EMBLEM);
}

void gm_801AA6D8(s16 arg0)
{
    un_803048C0(arg0);
}

bool gm_801AA6FC(void)
{
    PAD_STACK(4);
    return un_803048C0(0x10B) || un_803048C0(0x10A) || un_803048C0(0x109);
}

bool gm_801AA774(void)
{
    PAD_STACK(4);
    return un_803048C0(0x107) || un_803048C0(0x108);
}

void gm_801AA7C4_OnFrame(void)
{
    if (gm_804D6814 >= 0x134D) {
        lbAudioAx_80028B90();
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}

void fn_801AA7F8(HSD_GObj* gobj)
{
    HSD_CObj* cobj = gobj->hsd_obj;
    int i;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_CObjAnim(cobj);
        }
    }
}

static int gm_804D6800;
const int Gm_GObj_GXLink_PlyCursor = 9;
void fn_801AA854(HSD_GObj* gobj, int code)
{
    int i;
    HSD_CObj* cobj = gobj->hsd_obj;
    Mtx sp10;

    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(gm_804D6838->color.r, gm_804D6838->color.g,
                          gm_804D6838->color.b, 0xFF);
        HSD_CObjEraseScreen(cobj, 1, 0, 0);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(NULL);
        PSMTXCopy(cobj->view_mtx, sp10);
        gobj = HSD_GObjGXLinkHead[9];
        while (gobj != NULL) {
            HSD_ASSERT(0x167, gobj == HSD_GObjGXLinkHead[Gm_GObj_GXLink_PlyCursor]);
            for (i = gm_804D6800 - 1; i >= 0; i--) {
                HSD_ASSERT(0x169, staffInfo[staffInfoSortBuf[i].index].win[0]);

                HSD_ASSERT(0x16A, staffInfo[staffInfoSortBuf[i].index].win[1]);

                PSMTXConcat(cobj->view_mtx, staffInfoSortBuf[i].jobj->mtx,
                            cobj->view_mtx);
                if (cobj->view_mtx[2][2] >= 0.0F) {
                    HSD_SisLib_803A84BC(
                        staffInfo[staffInfoSortBuf[i].index].win[0]->entity,
                        2);
                    HSD_SisLib_803A84BC(
                        staffInfo[staffInfoSortBuf[i].index].win[1]->entity,
                        2);
                }
                PSMTXCopy(sp10, cobj->view_mtx);
            }
            gobj = gobj->next_gx;
        }
        HSD_CObjEndCurrent();
    }
}

static HSD_Text* gm_80480D58[6];

void fn_801AAA28(HSD_GObj* gobj, int code)
{
    int i;
    HSD_GObj_803910D8(gobj, code);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        for (i = 0; i < 6; i++) {
            if (gm_80480D58[i] != NULL) {
                HSD_SisLib_803A84BC(gm_80480D58[i]->entity, 2);
            }
        }
        if (gm_804D680C != NULL) {
            HSD_SisLib_803A84BC(gm_804D680C->entity, 2);
        }
    }
    HSD_CObjEndCurrent();
}

void fn_801AAABC(HSD_GObj* gobj)
{
    HSD_LObj* lobj = gobj->hsd_obj;
    int i;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_LObjAnimAll(lobj);
        }
    }
}

void fn_801AAB18(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int i;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_JObjAnimAll(jobj);
        }
    }
}

void fn_801AAB74(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;
    HSD_JObj* leaf;
    HSD_Text* text;
    int entry_idx;
    int staff_idx;
    int name_page_jp;
    int name_page_en;
    int title_page;
    StaffEntryData* entry_data;
    int i;
    SortBufEntry bsort_temp;
    PAD_STACK(0x20);

    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_JObjAnimAll(jobj);
        }
    }

    entry_idx = 0;
    child = jobj->child;
    staff_idx = 0;
    gm_804D6800 = 0;
    entry_data = gm_803DBFD8;
    {
        int temp = entry_idx * 15;
        name_page_jp = temp + 3;
        name_page_en = temp + 4;
        title_page = temp + 2;
    }

    while (child != NULL) {
        leaf = child->child->child;

        if (!(HSD_JObjGetFlags(leaf) & 0x10) &&
            staffInfo[staff_idx].win[0] == NULL &&
            (entry_data->has_check == 0 ||
             entry_data->check(entry_data->check_arg) != 0 ||
             entry_idx == 0xC5) &&
            (entry_idx != 0x5E || lbLang_IsSavedLanguageJP() != 0))
        {
            staffInfo[staff_idx].win[0] =
                HSD_SisLib_803A5ACC(0, 0, 0.0f, -3.3f, 0.0f, 0.0f, 100.0f);
            staffInfo[staff_idx].win[0]->x4C = 1;
            staffInfo[staff_idx].win[0]->default_alignment = 1;
            staffInfo[staff_idx].win[0]->default_kerning = 1;

            if (lbLang_IsSavedLanguageJP() != 0 && entry_idx < 0xB7 &&
                entry_idx != 0xB0)
            {
                text = staffInfo[staff_idx].win[0];
                text->font_size.x = 0.209f;
                text->font_size.y = 0.209f;
            } else {
                text = staffInfo[staff_idx].win[0];
                text->font_size.x = 0.13679999f;
                text->font_size.y = 0.209f;
            }

            if (entry_data->has_check != 0 &&
                entry_data->check(entry_data->check_arg) == 0)
            {
                if (lbLang_IsSavedLanguageJP() != 0) {
                    HSD_SisLib_803A6368(staffInfo[staff_idx].win[0],
                                        entry_data->alt_page);
                } else {
                    HSD_SisLib_803A6368(staffInfo[staff_idx].win[0],
                                        entry_data->alt_page + 1);
                }
            } else if ((entry_idx != 0xB7 && entry_idx != 0xC1 &&
                        entry_idx != 0xC3 &&
                        lbLang_IsSavedLanguageJP() != 0) ||
                       ((entry_idx == 0xB7 || entry_idx == 0xC1 ||
                         entry_idx == 0xC3) &&
                        lbLang_IsSettingJP() != 0))
            {
                HSD_SisLib_803A6368(staffInfo[staff_idx].win[0], name_page_jp);
            } else {
                HSD_SisLib_803A6368(staffInfo[staff_idx].win[0], name_page_en);
            }

            staffInfo[staff_idx].win[1] =
                HSD_SisLib_803A5ACC(0, 0, 0.0f, -7.8f, 0.0f, 0.0f, 100.0f);
            staffInfo[staff_idx].win[1]->x4C = 1;
            staffInfo[staff_idx].win[1]->default_alignment = 1;
            staffInfo[staff_idx].win[1]->default_kerning = 1;
            {
                text = staffInfo[staff_idx].win[1];
                text->font_size.x = 0.1f;
                text->font_size.y = 0.1f;
            }

            if (entry_data->has_check == 0 ||
                entry_data->check(entry_data->check_arg) != 0)
            {
                HSD_SisLib_803A6368(staffInfo[staff_idx].win[1], title_page);
            }

            if (staffInfo[staff_idx].x8 >= 1) {
                staffInfo[staff_idx].win[0]->active_color = gm_804D42C8;
                staffInfo[staff_idx].win[1]->active_color = gm_804D42C8;
            }
        } else if (HSD_JObjGetFlags(leaf) & 0x10) {
            text = staffInfo[staff_idx].win[0];
            if (text != NULL) {
                HSD_SisLib_803A5CC4(text);
                HSD_SisLib_803A5CC4(staffInfo[staff_idx].win[1]);
                staffInfo[staff_idx].win[0] = NULL;
            }
        }

        if (!(HSD_JObjGetFlags(leaf) & 0x10) &&
            (entry_data->has_check == 0 ||
             entry_data->check(entry_data->check_arg) != 0 ||
             entry_idx == 0xC5) &&
            (entry_idx != 0x5E || lbLang_IsSavedLanguageJP() != 0))
        {
            HSD_JObjSetupMatrix(leaf);
            staffInfoSortBuf[gm_804D6800].index = entry_idx;
            staffInfoSortBuf[gm_804D6800].jobj = leaf;
            gm_804D6800++;
        }

        child = child->next;
        staff_idx++;
        entry_data++;
        name_page_jp += 15;
        name_page_en += 15;
        title_page += 15;
        entry_idx++;
    }

    HSD_CObjSetupViewingMtx(gm_804D6830);

    for (i = 0; i < gm_804D6800; i++) {
        leaf = staffInfoSortBuf[i].jobj;
        HSD_ASSERT(0x478, leaf);
        HSD_JObjSetupMatrix(leaf);
        PSMTXConcat(gm_804D6830->view_mtx, leaf->mtx, staffInfoSortBuf[i].mtx);
    }

    {
        int n;
        int j;
        for (n = gm_804D6800 - 1; n > 0; n--) {
            for (j = 0; j < n; j++) {
                if (staffInfoSortBuf[j].mtx[2][3] <
                    staffInfoSortBuf[j + 1].mtx[2][3])
                {
                    bsort_temp = staffInfoSortBuf[j];
                    staffInfoSortBuf[j] = staffInfoSortBuf[j + 1];
                    staffInfoSortBuf[j + 1] = bsort_temp;
                }
            }
        }
    }
}

void fn_801AB200(HSD_GObj* gobj)
{
    HSD_JObj* root = GET_JOBJ(gobj);
    HSD_JObj* cursor_jobj;
    HSD_JObj* temp_jobj;
    HSD_JObj* jobj_pair[2];
    Vec3 xform_result;
    f32 proj[8];
    s32 tally_color;
    s32 tally_color2;
    HSD_JObj* ptcl_jobj;
    HSD_JObj* ptcl_jobj2;
    HSD_JObj* ptcl_jobj3;
    s32 selected;
    s32 button;
    HSD_JObj* hover_jobj;
    int i, j;
    s8 raw_stick;
    s32 adj_val;
    f32 vel_x, vel_y;
    f32 sq_x, sq_y;
    f32 cursor_vy;
    void* p;
    int entry_idx;
    int broke;
    s32 base_page;
    s32 jp_page, en_page, jp_page1;
    s32 page_5, page_6, page_8;
    HSD_Text** text_arr;
    StaffEntryData* entry_data;
    f32 x_pos;
    s32 tally_count;
    s32 check_failed;
    s32 line_num;
    HSD_Generator* gen;
    HSD_psAppSRT* appsrt;
    HSD_GObj* leaf;
    HSD_JObj* child_jobj;
    f32 fov_scale;
    f32 half_size;
    Vec3* corners;
    f32 highlight_val;
    f32 offset1, offset2;
    StaffEntryData* tree_base;
    HSD_Text* tally_text;
    PAD_STACK(0x60);

    lb_80011E24(root, &cursor_jobj, 7, -1);

    raw_stick = HSD_PadCopyStatus[(u8)gm_801BF010()].stickX;
    if (raw_stick > 4) {
        adj_val = raw_stick - 4;
    } else if (raw_stick < -4) {
        adj_val = raw_stick + 4;
    } else {
        adj_val = 0;
    }
    vel_x = (f32)adj_val;

    raw_stick = HSD_PadCopyStatus[(u8)gm_801BF010()].stickY;
    if (raw_stick > 4) {
        adj_val = raw_stick - 4;
    } else if (raw_stick < -4) {
        adj_val = raw_stick + 4;
    } else {
        adj_val = 0;
    }

    sq_x = vel_x * vel_x + 6400.0f;
    vel_y = (f32)adj_val;
    sq_x = sqrtf(sq_x);
    vel_x *= 0.00038461538f * sq_x;
    sq_y = vel_y * vel_y + 6400.0f;
    sq_y = sqrtf(sq_y);

    cursor_vy = vel_y * (0.00038461538f * sq_y);
    if (cursor_vy < -2.6f) {
        cursor_vy = -2.6f;
    }
    if (cursor_vy > 2.6f) {
        cursor_vy = 2.6f;
    }

    gm_804D6804.x0 = vel_x;
    gm_804D6804.x4 = cursor_vy;

    HSD_JObjSetTranslateX(cursor_jobj, gm_804D6804.x0);
    HSD_JObjSetTranslateY(cursor_jobj, gm_804D6804.x4);

    selected = -1;
    for (i = 0; i < gm_804D6800; i++) {
        entry_idx = staffInfoSortBuf[i].index;
        if (staffInfo[entry_idx].x8 < 1) {
            if (entry_idx < 7) {
                tree_base = &gm_803DBFD8[entry_idx];
                lb_80011E24(gm_804D682C, &ptcl_jobj,
                            *(s32*)(tree_base + 0x11F0),
                            -1);
                if (entry_idx == 0) {
                    p = ptcl_jobj->u.ptcl;
                    tally_color = *(s32*)&gm_804D42C4;
                    p = *(void**)((u8*)p + 4);
                    p = *(void**)((u8*)p + 4);
                    p = *(void**)((u8*)p + 4);
                    p = *(void**)((u8*)p + 8);
                    p = *(void**)((u8*)p + 0xC);
                    *(s32*)((u8*)p + 4) = tally_color;
                } else if ((unsigned)(entry_idx - 2) <= 1u) {
                    p = ptcl_jobj->u.ptcl;
                    tally_color = *(s32*)&gm_804D42C4;
                    p = *(void**)((u8*)p + 4);
                    p = *(void**)((u8*)p + 8);
                    p = *(void**)((u8*)p + 0xC);
                    *(s32*)((u8*)p + 4) = tally_color;
                } else {
                    p = ptcl_jobj->u.ptcl;
                    tally_color = *(s32*)&gm_804D42C4;
                    p = *(void**)((u8*)p + 8);
                    p = *(void**)((u8*)p + 0xC);
                    *(s32*)((u8*)p + 4) = tally_color;
                }
            } else {
                staffInfo[entry_idx].win[0]->active_color = gm_804D42C4;
                staffInfo[entry_idx].win[1]->active_color = gm_804D42C4;
            }
        }
    }

    gm_804D6804.x0 *= 0.29411763f;
    gm_804D6804.x4 *= 0.29411763f;
    fov_scale = (f32)(1.1917536 *
                      tanf((f32)(0.008726646471282037 *
                                 HSD_CObjGetFov(gm_804D6830))));
    gm_804D6804.x0 *= fov_scale;
    gm_804D6804.x4 *= fov_scale;

    if (gm_804D6814 < 0x1285) {
        for (i = 0; i < gm_804D6800; i++) {
            SortBufEntry* sort_entry = &staffInfoSortBuf[i];
            if (sort_entry->mtx[2][3] < -1.0f) {
                entry_idx = sort_entry->index;
                if (entry_idx != 0xB7 && entry_idx < 0xC0) {
                    hover_jobj = sort_entry->jobj;
                    half_size =
                        0.16875f *
                        (f32)gm_803DBFD8[entry_idx]
                            .x11[lbLang_IsSavedLanguageUS()];
                    gm_803DD1C8[0xa] = -half_size;
                    gm_803DD1C8[0x7] = -half_size;
                    gm_803DD1C8[0x10] = half_size;
                    gm_803DD1C8[0xd] = half_size;
                    broke = 0;
                    for (j = 0; j < 4; j++) {
                        PSMTXMultVec(sort_entry->mtx,
                                     (Vec3*)((u8*)gm_803DBFD8 + 0x120C) + j,
                                     &xform_result);
                        if (xform_result.z >= -1.0f) {
                            broke = 1;
                            break;
                        }
                        proj[j * 2] = -xform_result.x / xform_result.z;
                        proj[j * 2 + 1] =
                            -xform_result.y / xform_result.z;
                    }

                    if (broke == 0 &&
                        (proj[3] - proj[1]) *
                                (gm_804D6804.x0 - proj[0]) >=
                            (gm_804D6804.x4 - proj[1]) *
                                (proj[2] - proj[0]) &&
                        (proj[5] - proj[3]) *
                                (gm_804D6804.x0 - proj[2]) >=
                            (gm_804D6804.x4 - proj[3]) *
                                (proj[4] - proj[2]) &&
                        (proj[7] - proj[5]) *
                                (gm_804D6804.x0 - proj[4]) >=
                            (gm_804D6804.x4 - proj[5]) *
                                (proj[6] - proj[4]) &&
                        (proj[1] - proj[7]) *
                                (gm_804D6804.x0 - proj[6]) >=
                            (gm_804D6804.x4 - proj[7]) *
                                (proj[0] - proj[6]))
                    {
                        entry_idx = staffInfoSortBuf[i].index;
                        selected = entry_idx;
                        if (staffInfo[entry_idx].x8 < 1) {
                            if (entry_idx < 7) {
                                tree_base = &gm_803DBFD8[entry_idx];
                                lb_80011E24(
                                    gm_804D682C, &ptcl_jobj2,
                                    *(s32*)(tree_base + 0x11F0),
                                    -1);
                                if (entry_idx == 0) {
                                    p = ptcl_jobj2->u.ptcl;
                                    tally_color = *(s32*)&gm_804D42CC;
                                    p = *(void**)((u8*)p + 4);
                                    p = *(void**)((u8*)p + 4);
                                    p = *(void**)((u8*)p + 4);
                                    p = *(void**)((u8*)p + 8);
                                    p = *(void**)((u8*)p + 0xC);
                                    *(s32*)((u8*)p + 4) = tally_color;
                                } else if ((unsigned)(entry_idx - 2) <=
                                           1u) {
                                    p = ptcl_jobj2->u.ptcl;
                                    tally_color = *(s32*)&gm_804D42CC;
                                    p = *(void**)((u8*)p + 4);
                                    p = *(void**)((u8*)p + 8);
                                    p = *(void**)((u8*)p + 0xC);
                                    *(s32*)((u8*)p + 4) = tally_color;
                                } else {
                                    p = ptcl_jobj2->u.ptcl;
                                    tally_color = *(s32*)&gm_804D42CC;
                                    p = *(void**)((u8*)p + 8);
                                    p = *(void**)((u8*)p + 0xC);
                                    *(s32*)((u8*)p + 4) = tally_color;
                                }
                            } else {
                                staffInfo[entry_idx].win[0]->active_color =
                                    gm_804D42CC;
                                staffInfo[entry_idx].win[1]->active_color =
                                    gm_804D42CC;
                            }
                            staffInfo[selected].win[0]->active_color.r = 0xB4;
                            staffInfo[selected].win[1]->active_color.r = 0xB4;
                        }
                        break;
                    }
                }
            }
        }
    }

    button = 0;
    if (HSD_PadCopyStatus[(u8)gm_801BF010()].trigger & 0x100) {
        button = 0x100;
    } else if (HSD_PadCopyStatus[(u8)gm_801BF010()].trigger & 0x200) {
        button = 0x200;
    } else if (HSD_PadCopyStatus[(u8)gm_801BF010()].trigger & 0x1000) {
        button = 0x1000;
    } else if (HSD_PadCopyStatus[(u8)gm_801BF010()].trigger & 0x10) {
        button = 0x10;
    }

    if (button != 0) {
        if (gm_804D6818 == 0 && button == 0x100 && gm_804D6820 == 0) {
            lb_80011E24(root, &temp_jobj, 5, -1);
            HSD_JObjReqAnim(temp_jobj, 0.0f);
            lbAudioAx_800237A8(0x7A12D, 0x7F, 0x40);
        }

        if (selected != -1 &&
            (button == 0x200 ||
             (gm_804D6818 == 0 && button == 0x100)))
        {
            lb_80011E24(root, &temp_jobj, 8, -1);
            HSD_JObjReqAnimAll(temp_jobj, 0.0f);
            lbAudioAx_800237A8(0x7A12A, 0x7F, 0x40);

            entry_data = &gm_803DBFD8[selected];
            check_failed = 0;
            if (entry_data->check != NULL &&
                entry_data->check(entry_data->check_arg) == 0)
            {
                check_failed = 1;
            }

            base_page = selected * 0xF;
            jp_page = base_page + 7;
            jp_page1 = jp_page;
            en_page = base_page + 0xB;
            page_5 = base_page + 5;
            page_6 = base_page + 6;
            page_8 = base_page + 8;
            text_arr = gm_80480D58;
            for (j = 0; j < 6; j++) {
                if (text_arr[j] != NULL) {
                    HSD_SisLib_803A5CC4(text_arr[j]);
                }

                gm_804D6810 = entry_data->x0;

                if (j == 0) {
                    tree_base = &gm_803DBFD8[gm_804D6810];
                    x_pos = *(f32*)(tree_base + 0xF78);
                    gm_80480D58[0] = HSD_SisLib_803A5ACC(
                        0, 0, 1.45f + x_pos, 0.86f, 0.0f, 0.0f,
                        100.0f);
                } else if (j == 1) {
                    if (selected == 0xAC) {
                        offset1 = 0.2f;
                    } else {
                        offset1 = 0.0f;
                    }
                    if (selected == 0xAF) {
                        offset2 = 0.1f;
                    } else {
                        offset2 = 0.0f;
                    }
                    tree_base = &gm_803DBFD8[gm_804D6810];
                    x_pos = *(f32*)(tree_base + 0xF78);
                    gm_80480D58[1] = HSD_SisLib_803A5ACC(
                        0, 0,
                        offset2 + (3.0f + x_pos + offset1),
                        0.86f, 0.0f, 0.0f, 100.0f);
                } else {
                    tree_base = &gm_803DBFD8[gm_804D6810];
                    x_pos = *(f32*)(tree_base + 0xF78);
                    text_arr[j] = HSD_SisLib_803A5ACC(
                        0, 0, 1.45f + x_pos, (0.19f * (f32) j) + 0.67f, 0.0f,
                        0.0f, 100.0f);
                }

                text_arr[j]->default_kerning = 1;
                text_arr[j]->font_size.x = 0.00376f;
                text_arr[j]->font_size.y = 0.0045f;

                if (j == 0) {
                    if (check_failed == 0 ||
                        entry_data->has_check == 0)
                    {
                        text_arr[j]->text_color.r = 0xC3;
                        text_arr[j]->text_color.g = 0xC3;
                        text_arr[j]->text_color.b = 0xC3;
                        if (lbLang_IsSavedLanguageJP() != 0) {
                            HSD_SisLib_803A6368(gm_80480D58[0],
                                                page_5);
                        } else {
                            HSD_SisLib_803A6368(gm_80480D58[0],
                                                page_6);
                        }
                    }
                } else if (j == 1) {
                    if (check_failed == 0 ||
                        entry_data->has_check == 0)
                    {
                        text_arr[j]->text_color.r = 0xE8;
                        text_arr[j]->text_color.g = 0x37;
                        text_arr[j]->text_color.b = 0xE0;
                        if (lbLang_IsSavedLanguageJP() != 0) {
                            HSD_SisLib_803A6368(gm_80480D58[1],
                                                jp_page1);
                        } else {
                            HSD_SisLib_803A6368(gm_80480D58[1],
                                                page_8);
                        }
                    }
                } else {
                    text_arr[j]->text_color.r = 0xFF;
                    text_arr[j]->text_color.g = 0xB4;
                    text_arr[j]->text_color.b = 0;
                    if (selected == 0x4B && j == 2) {
                        line_num = gm_80164840(0x16U) * 2;
                        HSD_SisLib_803A6368(text_arr[j], gm_80164840(7U) +
                                                             line_num + 0xBEC);
                    } else if (j == 2 && check_failed == 1) {
                        if (lbLang_IsSavedLanguageJP() != 0) {
                            HSD_SisLib_803A6368(text_arr[j],
                                                entry_data->alt_page + 2);
                        } else {
                            HSD_SisLib_803A6368(text_arr[j],
                                                entry_data->alt_page + 3);
                        }
                    } else if (lbLang_IsSavedLanguageJP() != 0) {
                        HSD_SisLib_803A6368(text_arr[j], jp_page + j);
                    } else {
                        HSD_SisLib_803A6368(text_arr[j], en_page + j);
                    }
                }
            }

            if (button == 0x100 && gm_804D6820 == 0) {
                gen = hsd_8039F05C(0, 0, 0x27);
                appsrt = gen->appsrt;
                if (appsrt == NULL) {
                    appsrt = psAddGeneratorAppSRT_begin(gen, 1);
                }

                appsrt->translate.x = hover_jobj->mtx[0][3];
                appsrt->translate.y = hover_jobj->mtx[1][3];
                appsrt->translate.z = hover_jobj->mtx[2][3];
                appsrt->scale.x = 1.3f * hover_jobj->scale.x;
                appsrt->scale.y = 1.3f * hover_jobj->scale.y;
                appsrt->scale.z = 1.3f * hover_jobj->scale.z;

                staffInfo[selected].x8 += 1;
                if (staffInfo[selected].x8 >= 1) {
                    if (selected < 7) {
                        tree_base = &gm_803DBFD8[selected];
                        lb_80011E24(
                            gm_804D682C, &ptcl_jobj3,
                            *(s32*)(tree_base + 0x11F0),
                            -1);
                        if (selected == 0) {
                            p = ptcl_jobj3->u.ptcl;
                            tally_color = *(s32*)&gm_804D42C8;
                            p = *(void**)((u8*)p + 4);
                            p = *(void**)((u8*)p + 4);
                            p = *(void**)((u8*)p + 4);
                            p = *(void**)((u8*)p + 8);
                            p = *(void**)((u8*)p + 0xC);
                            *(s32*)((u8*)p + 4) = tally_color;
                        } else if ((unsigned)(selected - 2) <= 1u) {
                            p = ptcl_jobj3->u.ptcl;
                            tally_color = *(s32*)&gm_804D42C8;
                            p = *(void**)((u8*)p + 4);
                            p = *(void**)((u8*)p + 8);
                            p = *(void**)((u8*)p + 0xC);
                            *(s32*)((u8*)p + 4) = tally_color;
                        } else {
                            p = ptcl_jobj3->u.ptcl;
                            tally_color = *(s32*)&gm_804D42C8;
                            p = *(void**)((u8*)p + 8);
                            p = *(void**)((u8*)p + 0xC);
                            *(s32*)((u8*)p + 4) = tally_color;
                        }
                    } else {
                        staffInfo[selected].win[0]->active_color = gm_804D42C8;
                        staffInfo[selected].win[1]->active_color = gm_804D42C8;
                    }
                }

                gm_804D6828 = (0.5f * gm_804D6828) + 1.7f;
            }
        }
    }

    gm_804D6828 -= 0.017f;
    if (gm_804D6828 < 0.0f) {
        gm_804D6828 = 0.0f;
    }
    highlight_val = 0.25f + gm_804D6824;
    if (highlight_val < gm_804D6828) {
        gm_804D6824 = highlight_val;
    } else {
        gm_804D6824 = gm_804D6828;
    }

    lb_80011E24(root, &temp_jobj, 0x18, -1);
    HSD_JObjSetRotationZ(temp_jobj,
                          (f32)(-gm_804D6824 - 0.7853981633974483));

    lb_80011E24(root, &temp_jobj, 5, -1);
    HSD_JObjAnimAll(temp_jobj);
    lb_80011E24(root, jobj_pair, 0x1C, 0x1A, -1);

    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            lb_80011E24(root, &temp_jobj, 2, -1);
            HSD_JObjAnimAll(temp_jobj);
            lb_80011E24(root, &temp_jobj, 0x14, -1);
            HSD_JObjAnimAll(temp_jobj);
        }

        gm_804D6814 += gm_804D681C;

        if (gm_804D6814 >= 0x1285 && gm_804D680C == NULL) {
            tally_count = 0;
            tally_color = gm_804DAAEC;
            for (j = 0; j < 6; j++) {
                HSD_SisLib_803A5CC4(gm_80480D58[j]);
                gm_80480D58[j] = NULL;
            }

            gm_804D6810 = 0;
            tally_text = HSD_SisLib_803A6754(0, 0);
            gm_804D680C = tally_text;
            tally_text->default_kerning = 1;
            tally_text->pos_x = 85.0f;
            tally_text->pos_y = 130.0f;
            tally_text->pos_z = -280.0f;

            for (i = 0; i < 198; i++) {
                if (staffInfo[i].x8 >= 1) {
                    tally_count++;
                }
            }

            line_num = HSD_SisLib_803A6B98(
                gm_804D680C, 0.0f, 0.0f,
                (char*)((u8*)gm_803DBFD8 + 0x1264), tally_count);
            tally_color2 = tally_color;
            HSD_SisLib_803A74F0(gm_804D680C, line_num,
                                (GXColor*)&tally_color2);

            child_jobj = jobj_pair[0]->child;
            HSD_JObjSetTranslateY(child_jobj, -0.4f);

            child_jobj = jobj_pair[1]->child;
            HSD_JObjSetTranslateY(child_jobj, -0.4f);

            gm_804D681C = 1;
        }

        if (gm_804D6814 >= 0x12D5) {
            lbAudioAx_80028B6C();
        }

        if (gm_804D6814 == 0x1311) {
            if (gm_804D6848 == 0) {
                lbBgFlash_800206D4(&gm_804D42B8, &gm_804D42C0, 0x3C);
            } else {
                lbBgFlash_800206D4(&gm_804D42BC, &gm_804D42C0, 0x3C);
            }
            lbAudioAx_80023694();
        }
    }

    tree_base = &gm_803DBFD8[gm_804D6810];
    HSD_JObjSetTranslateX(
        jobj_pair[0],
        *(f32*)(tree_base + 0xF78));

    if (button == 0x1000) {
        if (gm_804D681C == 1) {
            if (gm_804D6814 < 0x1285) {
                gm_804D681C = 6;
                lbBgFlash_800206D4(&gm_804D42BC, &gm_804D42BC, 1);
                gm_804D6848 = 1;
            } else {
                gm_804D681C = 1;
            }
        } else if (gm_804D6814 < 0x1285) {
            gm_804D681C = 1;
            lbBgFlash_800206D4(&gm_804D42B8, &gm_804D42B8, 1);
            gm_804D6848 = 0;
        } else {
            gm_804D681C = 1;
        }
    }

    for (i = 1; i < gm_804D681C; i++) {
        efLib_particles_proc_main(NULL);
    }

    if (gm_804D6820 != 0) {
        gm_804D6820 -= 1;
    }

    if (gm_804D6818 == 0 && button == 0x200) {
        if (gm_804D6814 < 0x1285) {
            gm_804D6818 = 1;
            leaf = HSD_GObjObject_80390A3C(8U, 0xBU);
            HSD_ASSERT(0X12A, leaf);
            HSD_GObj_80390C5C(leaf);
        }
    } else if (gm_804D6818 == 1 && button != 0 &&
               (button != 0x200 || selected == -1))
    {
        gm_804D6818 = 0;
        leaf = HSD_GObjObject_80390A3C(8U, 0xBU);
        HSD_ASSERT(0x136, leaf);
        HSD_GObj_80390C84(leaf);
        gm_804D6820 = 0x3C;
    }

    if (gm_804D6814 >= gm_803DBFD8[gm_804D684C * 2 + 0x3E2].x0) {
        lbAudioAx_800237A8(
            *(s32*)((u8*)gm_803DBFD8 + gm_804D684C * 8 + 0xF8C),
            0x7F, 0x40);
        gm_804D684C += 1;
    }
}

void fn_801AC67C(HSD_GObj* gobj)
{
    int i;
    HSD_Fog* fog = gobj->hsd_obj;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_FogInterpretAnim(fog);
        }
    }
}

/* 3DD0F0 */ static HSD_CObjDesc gm_803DD0F0 = { 0 };

void gm_801AC6D8_OnEnter(void* unused)
{
    HSD_JObj* jobj_arr[2];
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    int i;
    int const gx_link = 11;
    PAD_STACK(0x10);

    efLib_Init();
    efAsync_LoadSync(0);
    staffInfo = HSD_MemAlloc(sizeof(struct staffInfo_t));
    staffInfoSortBuf = HSD_MemAlloc(sizeof(struct staffInfoSortBuf_t));
    HSD_SisLib_803A62A0(0, "SdStRoll.dat", "SIS_StRollData");
    HSD_SisLib_803A611C(0, (void*) -1, 9, 13, 0, 18, 0, 19);
    lbAudioAx_80026F2C(28);
    lbAudioAx_8002702C(16, 0x4000000000000ULL);
    lbAudioAx_80027168();
    gm_804D683C = lbArchive_80016DBC(
        "GmStRoll.dat", &gm_804D6840, "ScGamRegStaffroll_scene_data",
        &gm_804D6844, "ScGamRegStaffrollNames_scene_modelset", 0);
    {
        gobj = GObj_Create(17, 19, 0);
        cobj = HSD_CObjLoadDesc(gm_804D6840->cameras[0].desc);
        gm_804D6830 = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(gobj, fn_801AA854, 5);
        gobj->gxlink_prios = 0x189;
        HSD_CObjAddAnim(cobj, gm_804D6840->cameras[0].anims[0]);
        HSD_CObjReqAnim(cobj, 0.0F);
        HSD_GObj_SetupProc(gobj, fn_801AA7F8, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(19, 20, 0);
        HSD_CObj* cobj = HSD_CObjLoadDesc(&gm_803DD0F0);
        gm_804D6834 = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(gobj, fn_801AAA28, 8);
        gobj->gxlink_prios = 1LL << gx_link;
    }
    {
        HSD_GObj* gobj = GObj_Create(gx_link, 3, 0);
        HSD_LObj* lobj = lb_80011AC4(gm_804D6840->lights);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
        GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
        HSD_LObjReqAnimAll(lobj, 0.0F);
        HSD_GObj_SetupProc(gobj, fn_801AAABC, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(0xA, 3, 0);
        HSD_Fog* fog = HSD_FogLoadDesc(gm_804D6840->fogs[0].desc);
        gm_804D6838 = fog;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
        GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 3, 0);
        HSD_Fog_8037DE7C(fog, gm_804D6840->fogs[0].anims[0]->aobjdesc);
        HSD_FogReqAnim(fog, 0.0F);
        HSD_GObj_SetupProc(gobj, fn_801AC67C, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(3, 5, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6840->models[1]->joint);
        gm_804D682C = jobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 3, 0);
        gm_8016895C(jobj, gm_804D6840->models[1], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        {
            if (lbLang_IsSettingUS()) {
                lb_80011E24(jobj, jobj_arr, 103, 20, -1);
                jobj_arr[0]->u.dobj->mobj->tobj->imagedesc =
                    jobj_arr[1]->u.dobj->mobj->tobj->imagedesc;
            }
        }
        HSD_GObj_SetupProc(gobj, fn_801AAB18, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(14, 15, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6844[0]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, NULL, 9, 0);
        gm_8016895C(jobj, gm_804D6844[0], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        {
            /// @todo Length of #gm_804D6844 is 10
            for (i = 1; i < 10; i++) {
                HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6844[i]->joint);
                gm_8016895C(jobj, gm_804D6844[i], 0);
                HSD_JObjReqAnimAll(jobj, 0.0F);
                while (jobj->child != NULL) {
                    HSD_JObjReparent(jobj->child, jobj);
                }
            }
        }
        HSD_GObj_SetupProc(gobj, fn_801AAB74, 1);
    }
    {
        HSD_GObj* gobj = GObj_Create(14, 15, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6840->models[0]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, gx_link, 0);
        gm_8016895C(jobj, gm_804D6840->models[0], 0);
        lb_80011E24(jobj, jobj_arr, ARRAY_SIZE(jobj_arr), 20, -1);
        HSD_JObjReqAnimAll(jobj_arr[0], 0.0F);
        HSD_JObjReqAnimAll(jobj_arr[1], 0.0F);
        HSD_GObj_SetupProc(gobj, fn_801AB200, 13);
    }
    lbAudioAx_80027648();
    {
        u32 r = HSD_Randi(5);
        lbAudioAx_80023F28(lbAudioAx_8002305C(gm_801BEFB0(), !-r));
        lbBgFlash_800209F4();
        gm_804D6804.x0 = gm_804D6804.x4 = 0.0F;
        memzero(staffInfo, sizeof(struct staffInfo_t));
        gm_80480D58[0] = 0;
        gm_80480D58[1] = 0;
        gm_80480D58[2] = 0;
        gm_80480D58[3] = 0;
        gm_80480D58[4] = 0;
        gm_80480D58[5] = 0;
        gm_804D680C = NULL;
        gm_804D6810 = 0;
        gm_804D6814 = 0;
        gm_804D6818 = 0;
        gm_804D681C = 1;
        gm_804D6820 = 0;
        gm_804D6824 = gm_804D6828 = 0.0F;
        gm_804D6848 = 0;
        gm_804D684C = 0;
    }
}

void gm_801ACC90_OnLeave(void* unused) {}

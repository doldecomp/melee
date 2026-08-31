#include "sislib.h"

#include "cobj.h"
#include "gobj.h"
#include "gobjgxlink.h"
#include "gobjobject.h"
#include "gobjplink.h"
#include "gobjuserdata.h"
#include "memory.h"
#include "wobj.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

#include <printf.h> // IWYU pragma: keep
#include <stdio.h>
#include <dolphin/os.h>
#include <dolphin/types.h>

static HSD_WObjDesc HSD_SisLib_8040C490 = {
    NULL,
    { 0, 0, 1 },
    NULL,
};

static HSD_WObjDesc HSD_SisLib_8040C4A4 = {
    NULL,
    { 0, 0, 0 },
    NULL,
};

static u32 HSD_SisLib_804D7968;

static HSD_CameraDescPerspective HSD_SisLib_8040C4B8 = {
    NULL,
    0,
    PROJ_PERSPECTIVE,
    { 0, 640, 0, 480 },
    { 0, 640, 0, 480 },
    &HSD_SisLib_8040C490,
    &HSD_SisLib_8040C4A4,
    0.0f,
    NULL,
    0.0f,
    0xFFFF,
    30.0f,
    1.3333f,
};

sislib_UnkAlloc3* HSD_SisLib_804D797C;
HSD_Text* HSD_SisLib_804D7978;
SisBlock* used_head;
SisBlock* free_head;

/// extern ? *HSD_SisLib_804D796C;
/// extern u8 *HSD_SisLib_804D7978;
/// sislib_UnknownType001 HSD_SisLib_8040C490 = { 0, 1.0F };

/// u8 HSD_SisLib_8040C490[0x60] = { 0 };

static HSD_Archive* HSD_SisLib_804D1110[5];
SIS* HSD_SisLib_804D1124[5];

void* HSD_SisLib_Alloc(s32 size)
{
    SisBlock* best;
    SisBlock* alloc_tail;
    s32 remainder;
    s32 best_size;
    SisBlock* free_cur;
    SisBlock* alloc_cur;

    best = NULL;
    alloc_tail = NULL;
    free_cur = free_head;
    alloc_cur = used_head;
    if (size == 0) {
        OSReport("ZERO byte alloc\n");
        OSPanic(__FILE__, 60, "");
    }
    remainder = size % 4;
    if (remainder != 0) {
        size += 4 - remainder;
    }
    while (alloc_cur != NULL) {
        alloc_tail = alloc_cur;
        alloc_cur = alloc_cur->next;
    }
    for (;;) {
        if (free_cur->size == size) {
            best = free_cur;
            break;
        }
        if (free_cur->size > size) {
            if (best != NULL) {
                if (best->size > free_cur->size) {
                    best = free_cur;
                }
            } else {
                best = free_cur;
            }
        }
        free_cur = free_cur->next;
        if (free_cur == NULL) {
            break;
        }
    }
    if (best == NULL) {
        OSReport("Memory Empty\n");
        OSPanic(__FILE__, 0x56, "");
    }

    free_cur = free_head;

    if (free_cur == best) {
        u8* data_ptr;
        SisBlock* next_free;
        int remaining_size;

        data_ptr = (u8*) free_head->data;
        next_free = free_cur->next;
        remaining_size = (free_cur->size - size) - (sizeof(SisBlock));
        if (remaining_size < 0) {
            OSReport("Memory Empty\n");
            OSPanic(__FILE__, 0x5F, "");
        }

        free_head = (SisBlock*) (data_ptr + size);
        free_head->next = next_free;
        free_head->data = (HSD_Text*) (free_head + 1);
        free_head->size = remaining_size;
        best->size = size;
    } else {
        while (free_cur->next != best) {
            free_cur = free_cur->next;
        }
        free_cur->next = best->next;
    }
    best->next = NULL;
    if (alloc_tail != NULL) {
        alloc_tail->next = best;
    }
    if (used_head == NULL) {
        used_head = best;
    }
    return best->data;
}

void HSD_SisLib_Free(void* ptr)
{
    SisBlock* free_cur;
    SisBlock* free_tail;
    SisBlock* alloc_prev;
    SisBlock* alloc_cur;

    free_cur = free_head;
    free_tail = NULL;
    alloc_cur = used_head;
    alloc_prev = NULL;
    while (alloc_cur != NULL) {
        if (alloc_cur->data == ptr) {
            break;
        }
        alloc_prev = alloc_cur;
        alloc_cur = alloc_cur->next;
    }
    if (alloc_cur == NULL) {
        return;
    }
    if ((u8*) free_cur == ((u8*) alloc_cur->data + alloc_cur->size)) {
        SisBlock* old_next;
        u32 new_size;

        old_next = free_cur->next;
        new_size = free_cur->size + alloc_cur->size + sizeof(SisBlock);

        if (alloc_prev != NULL) {
            alloc_prev->next = alloc_cur->next;
        } else {
            used_head = alloc_cur->next;
        }
        free_head = alloc_cur;
        alloc_cur->next = old_next;
        free_head->data = (HSD_Text*) (free_head + 1);
        free_head->size = new_size;
        return;
    }
    while (free_cur != NULL) {
        free_tail = free_cur;
        free_cur = free_cur->next;
    }
    if (free_tail != NULL) {
        free_tail->next = alloc_cur;
    }
    if (alloc_prev != NULL) {
        alloc_prev->next = alloc_cur->next;
    } else {
        used_head = alloc_cur->next;
    }
    alloc_cur->next = NULL;
}

void HSD_SisLib_803A5A2C(void* ptr)
{
    HSD_Text* next_text;
    SisBlock* alloc;
    HSD_Text* curr;
    HSD_Text* last;

    last = NULL;
    curr = HSD_SisLib_804D7978;
    while (curr != NULL) {
        next_text = curr->next;
        if (curr == ptr) {
            if (last != NULL) {
                last->next = next_text;
            } else {
                HSD_SisLib_804D7978 = next_text;
            }
            alloc = curr->alloc_data;
            if (alloc != NULL) {
                if (alloc->data != NULL) {
                    HSD_SisLib_Free(alloc->data);
                }
                HSD_SisLib_Free(curr->alloc_data);
            }
            if (curr->string_buffer != NULL) {
                HSD_SisLib_Free(curr->string_buffer);
            }
            HSD_SisLib_Free(curr);
            return;
        }
        last = curr;
        curr = next_text;
    }
}

HSD_Text* HSD_SisLib_803A5ACC(int font_idx, s32 context_id, f32 pos_x,
                              f32 pos_y, f32 pos_z, f32 box_w, f32 box_h)
{
    HSD_Text* list_cur;
    HSD_Text* list_tail;
    sislib_UnkAlloc3* cam_entry;
    HSD_GObj* gobj;
    int cam_idx;
    HSD_Text* text;

    cam_idx = context_id; /// this is the context id that comes from
                          /// HSD_SisLib_803A611C, it essentially tells us
                          /// which camera to use
    list_tail = NULL;
    cam_entry = NULL;
    gobj = NULL;
    list_cur = HSD_SisLib_804D7978;
    if (cam_idx >= 0) {
        cam_entry = HSD_SisLib_804D797C;
        while (1) {
            if (cam_entry->xA == font_idx && --cam_idx < 0) {
                break;
            }

            if (cam_entry == NULL) {
                OSReport("unknow camera\n");
                return NULL;
            }
            cam_entry = cam_entry->x0;
        }
        gobj = GObj_Create(cam_entry->x8, cam_entry->xC, cam_entry->xD);
        GObj_SetupGXLink(gobj, HSD_SisLib_803A84BC, cam_entry->xE,
                         cam_entry->xF);
    }
    while (list_cur != NULL) {
        list_tail = list_cur;
        list_cur = list_cur->next;
    }
    text = HSD_SisLib_Alloc(sizeof(HSD_Text));
    if (HSD_SisLib_804D7978 == NULL) {
        HSD_SisLib_804D7978 = text;
    }
    if (list_tail != NULL) {
        list_tail->next = text;
    }
    if (gobj != NULL) {
        GObj_InitUserData(gobj, cam_entry->x8, HSD_SisLib_803A5A2C, text);
    }
    text->next = NULL;
    text->entity = gobj;
    text->pos_x = pos_x;
    text->pos_y = pos_y;
    text->pos_z = pos_z;
    text->box_size_x = box_w;
    text->box_size_y = box_h;
    text->x14.w = 0.0F;
    text->x14.z = 0.0F;
    text->x14.y = 0.0F;
    text->x14.x = 0.0F;
    text->font_size.y = 1.0F;
    text->font_size.x = 1.0F;
    text->alloc_data = NULL;
    text->string_buffer = 0;
    text->sis_buffer = 0;
    text->bg_color.a = 0;
    text->bg_color.b = 0;
    text->bg_color.g = 0;
    text->bg_color.r = 0;
    text->text_color.a = 0xFF;
    text->text_color.b = 0xFF;
    text->text_color.g = 0xFF;
    text->text_color.r = 0xFF;
    text->x34.y = 1.0F;
    text->x34.x = 1.0F;
    text->x3C.y = 0.0F;
    text->x3C.x = 0.0F;
    text->x46 = 0;
    text->x44 = 0;
    text->default_alignment = 0;
    text->default_fitting = 0;
    text->default_kerning = 0;
    text->x6E = 0;
    text->x6C = 0;
    text->x4E = 0;
    text->hidden = 0;
    text->x4C = 0;
    text->render_callback = 0;
    text->font_idx = font_idx;
    return text;
}

void HSD_SisLib_803A5CC4(HSD_Text* text)
{
    HSD_Text* curr = HSD_SisLib_804D7978;
    while (curr != NULL) {
        HSD_Text* next = curr->next;
        if (curr == text) {
            if (curr->entity != NULL) {
                HSD_GObjPLink_80390228(curr->entity);
                curr->entity = NULL;
            } else {
                HSD_SisLib_803A5A2C(curr);
            }
            return;
        }
        curr = next;
    }
}

void HSD_SisLib_803A5D30(void)
{
    HSD_Text* curr = HSD_SisLib_804D7978;
    while (curr != NULL) {
        HSD_Text* next = curr->next;
        if (curr->entity != NULL) {
            HSD_GObjPLink_80390228(curr->entity);
            curr->entity = NULL;
        } else {
            HSD_SisLib_803A5A2C(curr);
        }
        curr = next;
    }
}

static inline void HSD_SisLib_803A5DA0_inline0(s32 font_idx)
{
    HSD_Text* curr = HSD_SisLib_804D7978;
    while (curr != NULL) {
        HSD_Text* next = curr->next;
        if (curr->font_idx == font_idx) {
            if (curr->entity != NULL) {
                HSD_GObjPLink_80390228(curr->entity);
                curr->entity = NULL;
            } else {
                HSD_SisLib_803A5A2C(curr);
            }
        }
        curr = next;
    }
}

void HSD_SisLib_803A5DA0(s32 font_idx)
{
    sislib_UnkAlloc3* last = NULL;
    sislib_UnkAlloc3* curr;

    HSD_SisLib_803A5DA0_inline0(font_idx);

    curr = HSD_SisLib_804D797C;
    while (curr != NULL) {
        sislib_UnkAlloc3* next = curr->x0;
        if (curr->xA == font_idx) {
            if (curr->x4 != 0U) {
                HSD_GObjPLink_80390228(curr->x4);
                curr->x4 = 0;
            }
            if (last != NULL) {
                last->x0 = next;
            } else {
                HSD_SisLib_804D797C = next;
            }
            HSD_SisLib_Free(curr);
        }
        last = curr;
        curr = next;
    }
}

static SisBlock* HSD_SisLib_804D796C;

void HSD_SisLib_803A5E70(void)
{
    sislib_UnkAlloc3* curr;

    HSD_SisLib_803A5D30();

    curr = HSD_SisLib_804D797C;
    while (curr != NULL) {
        sislib_UnkAlloc3* next = curr->x0;
        if (curr->x4 != 0) {
            HSD_GObjPLink_80390228(curr->x4);
            curr->x4 = 0;
        }
        HSD_SisLib_Free(curr);
        curr = next;
    }

    HSD_SisLib_804D797C = NULL;
    free_head = HSD_SisLib_804D796C;
    used_head = NULL;
    free_head->next = NULL;
    free_head->data = (HSD_Text*) (free_head + 1);
    free_head->size = HSD_SisLib_804D7968 - sizeof(SisBlock);
}

void HSD_SisLib_803A5F50(s32 font_idx)
{
    HSD_Archive** archive_ptr;

    HSD_SisLib_803A5DA0(font_idx);
    archive_ptr = &HSD_SisLib_804D1110[font_idx];
    if (*archive_ptr != NULL) {
        HSD_SisLib_803A947C(*archive_ptr);
        *archive_ptr = NULL;
        HSD_SisLib_804D1124[font_idx] = NULL;
    }
}

void HSD_SisLib_803A5FBC(void)
{
    int i;
    HSD_SisLib_803A5E70();
    for (i = 0; i < 5; i++) {
        if (HSD_SisLib_804D1110[i] != NULL) {
            HSD_SisLib_803A947C(HSD_SisLib_804D1110[i]);
            HSD_SisLib_804D1110[i] = NULL;
            HSD_SisLib_804D1124[i] = NULL;
        }
    }
    HSD_Free(HSD_SisLib_804D796C);
}

/// @todo Currently 97.56% match - extra lwz reload optimized away by
/// compiler after dual global store
void HSD_SisLib_803A6048(size_t size)
{
    int i;

    HSD_SisLib_804D7968 = size;
    used_head = NULL;
    HSD_SisLib_804D796C = free_head = HSD_MemAlloc(HSD_SisLib_804D7968);
    free_head->next = NULL;
    free_head->data = (HSD_Text*) (free_head + 1);
    free_head->size = HSD_SisLib_804D7968 - sizeof(SisBlock);
    HSD_SisLib_804D7978 = NULL;
    HSD_SisLib_804D797C = NULL;

    for (i = 0; i < 5; i++) {
        HSD_SisLib_804D1110[i] = NULL;
        HSD_SisLib_804D1124[i] = NULL;
    }
}

/// GObj "remove" function callback
void fn_803A60EC(void* gobj)
{
    sislib_UnkAlloc3* curr = HSD_SisLib_804D797C;
    while (curr != NULL) {
        if (curr->x4 == gobj) {
            curr->x4 = 0U;
            return;
        }
        curr = curr->x0;
    }
}

int HSD_SisLib_803A611C(int font_idx, HSD_GObj* parent_gobj, u16 class_id,
                        u8 p_link, u8 p_prio, u8 gx_link, u8 gx_prio,
                        u32 render_prio)
{
    int count;
    sislib_UnkAlloc3* list_tail;
    sislib_UnkAlloc3* entry;
    sislib_UnkAlloc3* list_cur;

    list_tail = NULL;
    count = 0;
    list_cur = HSD_SisLib_804D797C;
    while (list_cur != NULL) {
        list_tail = list_cur;
        if (list_cur->xA == font_idx) {
            count += 1;
        }
        list_cur = list_cur->x0;
    }
    entry = HSD_SisLib_Alloc(sizeof(sislib_UnkAlloc3));
    if (HSD_SisLib_804D797C == NULL) {
        HSD_SisLib_804D797C = entry;
    }
    if (list_tail != NULL) {
        list_tail->x0 = entry;
    }
    entry->x8 = class_id;
    entry->xC = p_link;
    entry->xD = p_prio;
    entry->xE = gx_link;
    entry->xF = gx_prio;
    entry->xA = font_idx;
    entry->x0 = NULL;
    if (parent_gobj != NULL) {
        entry->x4 = NULL;
    } else {
        entry->x4 = GObj_Create(class_id, p_link, p_prio);
        if (entry->x4 != NULL) {
            HSD_CObj* cobj =
                HSD_CObjLoadDesc((HSD_CObjDesc*) &HSD_SisLib_8040C4B8);
            if (cobj != NULL) {
                HSD_CObjSetOrtho(cobj, 0.0F, -480.0F, 0.0F, 640.0F);
                {
                    u8 tmp = HSD_GObj_CameraKind;
                    HSD_GObjObject_80390A70(entry->x4, tmp, cobj);
                }
                GObj_SetupGXLinkMax(entry->x4, HSD_GObj_803910D8, render_prio);
                entry->x4->gxlink_prios = (u64) 1 << gx_link;
                GObj_InitUserData(entry->x4, class_id, fn_803A60EC, entry->x4);
            } else {
                HSD_GObjPLink_80390228(entry->x4);
                entry->x4 = NULL;
            }
        }
    }
    return count;
}

void HSD_SisLib_803A62A0(s32 font_idx, char* archive_name, char* symbol_name)
{
    HSD_Archive* tmp = HSD_SisLib_803A945C(archive_name);
    HSD_SisLib_804D1110[font_idx] = tmp;
    if (tmp == NULL) {
        OSReport("Cannot open archive %s.\n", archive_name);
        OSPanic(__FILE__, 0x24A, "");
    }
    {
        SIS* sis = HSD_ArchiveGetPublicAddress(HSD_SisLib_804D1110[font_idx],
                                               symbol_name);
        HSD_SisLib_804D1124[font_idx] = sis;
        if (sis == NULL) {
            OSReport("Cannot find symbol %s.\n", symbol_name);
            OSPanic(__FILE__, 0x24F, "");
        }
    }
}

void HSD_SisLib_803A6368(HSD_Text* text, s32 sis_idx)
{
    SIS** sis_table;
    s32 i;

    sis_table = (SIS**) HSD_SisLib_804D1124[text->font_idx];
    if (sis_table != NULL) {
        text->sis_buffer = sis_table[sis_idx];
    }
    text->x60 = NULL;
    text->current_height = 0.0F;
    text->current_width = 0.0F;
    text->active_color = text->text_color;
    text->x80.x = text->x34.x;
    text->x80.y = text->x34.y;
    text->x78.x = text->x3C.x;
    text->x78.y = text->x3C.y;
    text->x90 = text->x44;
    text->x92 = text->x46;
    text->alignment = text->default_alignment;
    text->kerning = text->default_kerning;
    text->fitting = text->default_fitting;
    text->x6C = 0;
    text->x98 = 0;
    text->x94 = 0;
    text->x4B = 0;
    if (text->string_buffer != NULL) {
        HSD_SisLib_Free(text->string_buffer);
    }
    text->string_buffer = HSD_SisLib_Alloc(0x10);
    i = 0;
    text->x6E = 0x10;
    while (i < text->x6E) {
        text->string_buffer[i] = 0;
        i += 1;
    }
}

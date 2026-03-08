#include "grzakogenerator.h"
#include "grzakogenerator.static.h"

#include "it/it_26B1.h"

#include <baselib/gobj.h>
#include <baselib/memory.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/random.h>

#include "it/types.h"
#include "it/item.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

HSD_GObjProc* HSD_GObjProc_8038FD54(HSD_GObj*, HSD_GObjEvent, u8);
void it_8027CE18(HSD_GObj*);
void lb_8000B1CC(void*, void*, void*);
void grLib_801C9874(void*);

int grZakoGenerator_801CA394(void* arg0, int arg1, void* arg2, f32 arg3)
{
    u8* result;
    void* arr;

    result = (u8*) HSD_MemAlloc(0x1C);
    if (result != NULL) {
        arr = HSD_MemAlloc(arg1 * 0x18);
        *(void**) (result + 0x04) = arr;
        if (arr != NULL) {
            *(void**) (result + 0x00) = arg0;
            *(int*) (result + 0x08) = arg1;
            *(void**) (result + 0x0C) = arg2;
            *(f32*) (result + 0x10) = arg3;
            *(int*) (result + 0x14) = 0;
            *(int*) (result + 0x18) = 0;
        } else {
            HSD_Free(result);
            result = NULL;
        }
    }
    return (int) result;
}

int grZakoGenerator_801CA43C(struct ZakoConfig* config, void* arg1_ptr, f32 arg1_f)
{
    int i;
    int count = 0;
    struct ConfigElement {
        f32 x0, x4, x8, xC, x10, x14;
    } *src, *dst;

    if (config == NULL || config->x4 == NULL) {
        return 0;
    }

    src = config->x0;
    dst = config->x4;
    for (i = 0; i < config->x8; i++) {
        lb_8000B1CC(arg1_ptr, src, dst);
        lb_8000B1CC(arg1_ptr, (u8*)src + 0xC, (u8*)dst + 0xC);
        src++;
        dst++;
    }

    dst = config->x4;
    for (i = 0; i < config->x8; i++) {
        if ((dst->x4 > arg1_f && dst->x10 > arg1_f) || (dst->x4 < arg1_f && dst->x10 < arg1_f)) {
            if (config->x10 > 0.0f) {
                if (HSD_Randf() < config->x10) {
                    continue;
                }
            }
        } else {
            f32 diff = dst->x10 - dst->x4;
            f32 results[3];
            if (diff < 0.0f) diff = -diff;
            if (diff > 0.0001f) {
                f32 t = (arg1_f - dst->x4) / (dst->x10 - dst->x4);
                results[0] = t * (dst->xC - dst->x0) + dst->x0;
                results[1] = arg1_f;
                results[2] = t * (dst->x14 - dst->x8) + dst->x8;
            } else {
                f32 t = HSD_Randf();
                results[0] = t * (dst->xC - dst->x0) + dst->x0;
                results[1] = arg1_f;
                results[2] = t * (dst->x14 - dst->x8) + dst->x8;
            }
            ((void (*)(f32*, int))config->xC)(results, i);
            count++;
            continue;
        }

        if (config->x10 > 0.0f) {
            if (config->x14 != 0) {
                grLib_801C9874((void*)config->x14);
                config->x14 = 0;
            }
        }
    }
    return count;
}

void* grZakoGenerator_801CA67C(void)
{
    struct grZakoGenerator_Data* data;
    int i;

    data = HSD_MemAlloc(0x3CC);
    if (data == NULL) {
        __assert("grzakogenerator.c", 82, "data");
    }
    for (i = 0; i < 80; i++) {
        data->entries[i].x0 = -1;
        data->entries[i].x2 = 0;
        data->entries[i].x4 = NULL;
    }
    data->x3C0 = -1;
    data->x3C2 = 0;
    data->x3C4 = NULL;
    data->x3C8 = 0;

    lbl_8049F030.xA_b0 = 1;
    lbl_8049F030.x8 = 0;
    return data;
}

HSD_GObj* Ground_801C58E0(void*, int, void*);
HSD_GObj* it_802EA9FC(void*, int);
HSD_GObj* it_802DD7F0(int, void*, int, int);
HSD_GObj* it_802E16F8(int, void*, int);
HSD_GObj* it_802DC4BC(int, void*, int);

s32 grZakoGenerator_801CA8B4(HSD_GObj* gobj, int arg1)
{
    struct StageZakoEntry {
        u8 x0, x1, x2, x3;
    }* stage_entries;
    struct grZakoGenerator_Data* data;
    int i, j;
    int idx;
    int max_idx;

    if (!lbl_8049F030.xA_b0) {
        return 0;
    }

    data = lbl_8049F030.x4;
    stage_entries = lbl_8049F030.x0;
    idx = lbl_8049F030.x8;
    max_idx = arg1 ? 81 : 80;

    for (j = 0; j < max_idx; j++) {
        if (idx < 80) {
            struct grZakoGenerator_Entry* element = &data->entries[idx];
            if (element->x4 == NULL) {
                if (element->x2 > 0) {
                    element->x2--;
                } else {
                    if (element->x0 == -1) {
                        if (arg1 == 1) {
                            element->x0 = idx;
                        }
                    }
                    if (element->x0 != -1) {
                        struct StageZakoEntry* entry = &stage_entries[element->x0 - 0x20];
                        u8 kind = entry->x0;
                        HSD_GObj* spawned = NULL;
                        Vec3 pos;

                        pos.x = 0; pos.y = 0; pos.z = 0; // Placeholder

                        if (kind >= 0xDC && kind <= 0xFB) {
                            if (element->x8 != -1) {
                                spawned = Ground_801C58E0(lbl_8049F030.x0, element->x8, gobj);
                            }
                        } else {
                            switch (kind) {
                                case 0x2B: spawned = it_8027B5B0(0x2B, &pos, NULL, NULL, 1); break;
                                case 0x2D: spawned = it_8027B5B0(0x2D, &pos, NULL, NULL, 1); break;
                                case 0x2E: spawned = it_8027B5B0(0x2E, &pos, NULL, NULL, 1); break;
                                case 0xD3: spawned = it_802DD7F0(entry->x2, &pos, 0, -1); break;
                                case 0xD5: spawned = it_802DC4BC(entry->x2, &pos, -1); break;
                                case 0xD9: spawned = it_8027B5B0(0xD9, &pos, NULL, NULL, 1); break;
                            }
                            if (spawned == NULL && kind < 0x2F) {
                                spawned = it_802EA9FC(&pos, -1);
                            }
                            if (spawned == NULL) {
                                spawned = it_802E16F8(entry->x2, &pos, -1);
                            }
                        }

                        if (spawned != NULL) {
                            element->x4 = spawned;
                            *(s32*)((u8*)spawned->user_data + 0xDD8) = idx;
                        }
                    }
                }
            }
        } else if (idx == 80 && arg1) {
            if (data->x3C4 == NULL) {
                if (data->x3C2 > 0) {
                    data->x3C2--;
                } else {
                    if (data->x3C0 != -1) {
                        struct StageZakoEntry* entry = &stage_entries[data->x3C0 - 0x20];
                        u8 kind = entry->x0;
                        HSD_GObj* spawned = NULL;
                        Vec3 pos;
                        pos.x = 0; pos.y = 0; pos.z = 0;

                        if (kind >= 0xDC && kind <= 0xFB) {
                            if (data->x3C8 != -1) {
                                spawned = Ground_801C58E0(lbl_8049F030.x0, data->x3C8, gobj);
                            }
                        } else {
                            switch (kind) {
                                case 0x2B: spawned = it_8027B5B0(0x2B, &pos, NULL, NULL, 1); break;
                                case 0x2D: spawned = it_8027B5B0(0x2D, &pos, NULL, NULL, 1); break;
                                case 0x2E: spawned = it_8027B5B0(0x2E, &pos, NULL, NULL, 1); break;
                                case 0xD3: spawned = it_802DD7F0(entry->x2, &pos, 0, -1); break;
                                case 0xD5: spawned = it_802DC4BC(entry->x2, &pos, -1); break;
                                case 0xD9: spawned = it_8027B5B0(0xD9, &pos, NULL, NULL, 1); break;
                            }
                            if (spawned == NULL && kind < 0x2F) {
                                spawned = it_802EA9FC(&pos, -1);
                            }
                            if (spawned == NULL) {
                                spawned = it_802E16F8(entry->x2, &pos, -1);
                            }
                        }
                        if (spawned != NULL) {
                            data->x3C4 = spawned;
                            *(s32*)((u8*)spawned->user_data + 0xDD8) = 80;
                        }
                    }
                }
            }
        }
        idx++;
        if (idx >= 81) idx = 0;
        if (idx == lbl_8049F030.x8) break;
    }
    lbl_8049F030.x8 = idx;
    return 0;
}

void grZakoGenerator_801CAC14(HSD_GObj* gobj)
{
    void* ip = gobj->user_data;
    enum_t kind = itGetKind(gobj);

    if (kind == 0x9F) {
        struct grZakoGenerator_Data* data = lbl_8049F030.x4;
        if (data->x3C4 == gobj) {
            data->x3C4 = NULL;
        }
    } else {
        s32 idx = *(s32*) ((u8*) ip + 0xDD8);
        if (idx != -1) {
            lbl_8049F030.x4->entries[idx].x4 = NULL;
            lbl_8049F030.x4->entries[idx].x2 = 2;
        }
    }
}

void grZakoGenerator_801CACB8(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    enum_t kind = itGetKind(item_gobj);
    struct StageZakoEntry {
        u8 x0, x1, x2, x3;
    }* stage_entries;

    it_8027CE18(item_gobj);

    if (kind == 0x9F) {
        struct grZakoGenerator_Data* data = lbl_8049F030.x4;
        if (data->x3C4 == item_gobj) {
            data->x3C0 = -1;
            data->x3C4 = NULL;
        }
    } else {
        s32 unk_idx = *(s32*) ((u8*) item_data + 0xDD8);
        if (unk_idx != -1) {
            struct grZakoGenerator_Data* data = lbl_8049F030.x4;
            s16 x0;
            data->entries[unk_idx].x4 = NULL;
            x0 = data->entries[unk_idx].x0;
            stage_entries = lbl_8049F030.x0;
            if (stage_entries[x0 - 0x20].x3 == 1) {
                data->entries[unk_idx].x2 = 0x708;
            } else {
                data->entries[unk_idx].x2 = -1;
            }
            *(s32*) ((u8*) item_data + 0xDD8) = -1;
        }
    }
}

s32 fn_801CADBC(HSD_GObj* gobj)
{
    grZakoGenerator_801CA8B4(gobj, 0);
    return 0;
}

s32 grZakoGenerator_801CADE0(HSD_GObj* gobj)
{
    return grZakoGenerator_801CA8B4(gobj, 1);
}

HSD_GObj* grZakoGenerator_801CAE04(void* arg0)
{
    HSD_GObj* gobj;
    struct grZakoGenerator_Data* data = (struct grZakoGenerator_Data*) grZakoGenerator_801CA67C();
    gobj = GObj_Create(2, 4, 0);
    if (gobj == NULL) {
        OSReport("%s(%d): error: create gobj\n", "grzakogenerator.c", 358);
        HSD_Free(data);
        return NULL;
    }
    HSD_GObjProc_8038FD54(gobj, (HSD_GObjEvent) fn_801CADBC, 0);
    lbl_8049F030.x0 = arg0;
    lbl_8049F030.x4 = data;
    return gobj;
}

void grZakoGenerator_801CAEB0(int arg0, int arg1)
{
    struct grZakoGenerator_Data* data = lbl_8049F030.x4;
    s16 val = (s16) arg1;

    if (data->x3C0 != -1) {
        return;
    }
    data->x3C0 = val;
    lbl_8049F030.x4->x3C8 = arg0;
    lbl_8049F030.x4->x3C4 = NULL;
}

void grZakoGenerator_801CAEF0(bool arg0)
{
    lbl_8049F030.xA_b0 = arg0;
}

void grZakoGenerator_801CAF08(void)
{
    HSD_GObj* next;
    HSD_GObj* item_gobj;

    for (item_gobj = HSD_GObj_Entities->items; item_gobj != NULL; item_gobj = next) {
        enum_t kind;
        next = item_gobj->next;
        kind = itGetKind(item_gobj);
        if ((kind >= 0x2b && kind < 0x30) || (kind >= 0xd0 && kind < 0xe8)) {
            if (it_8026C1E8(item_gobj)) {
                Item_8026A8EC(item_gobj);
            }
        } else if (kind == 0x9f) {
            Item_8026A8EC(item_gobj);
        }
    }
}

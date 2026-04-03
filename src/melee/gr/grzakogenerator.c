#include "grzakogenerator.h"

#include "grzakogenerator.static.h"

#include "placeholder.h"

#include "baselib/forward.h"

#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itleadead.h"
#include "it/items/itlikelike.h"
#include "it/items/itnokonoko.h"
#include "it/items/itpatapata.h"
#include "it/types.h"
#include "lb/lb_00B0.h"

#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/memory.h>
#include <baselib/psstructs.h>
#include <sysdolphin/baselib/random.h>

grZakoGenerator_Config*
grZakoGenerator_801CA394(grZakoGenerator_Spawn* spawn_descs, int count,
                         grZakoGenerator_SpawnFunc callback, f32 arg4)
{
    grZakoGenerator_Config* config =
        HSD_MemAlloc(sizeof(grZakoGenerator_Config));
    if (config != NULL) {
        grZakoGenerator_Spawn* spawns =
            HSD_MemAlloc(count * sizeof(grZakoGenerator_Spawn));
        config->spawns = spawns;
        if (spawns != NULL) {
            config->spawn_descs = spawn_descs;
            config->count = count;
            config->callback = callback;
            config->x10 = arg4;
            config->gen = NULL;
            config->x18 = 0;
        } else {
            HSD_Free(config);
            config = NULL;
        }
    }
    return config;
}

static inline void
grZakoGenerator_801CA43C_inline(f32 t, grZakoGenerator_Spawn* spawns,
                                f32 height, Vec3* pos)
{
    pos->x = t * (spawns->pos1.x - spawns->pos0.x) + spawns->pos0.x;
    pos->y = height,
    pos->z = t * (spawns->pos1.z - spawns->pos0.z) + spawns->pos0.z;
}

s32 grZakoGenerator_801CA43C(grZakoGenerator_Config* config, HSD_JObj* jobj,
                             f32 height)
{
    Vec3 pos;
    s32 spawned = 0;
    f32 t;
    int i;
    grZakoGenerator_Spawn* descs;
    grZakoGenerator_Spawn* spawns;
    PAD_STACK(4);

    if (config == NULL || jobj == NULL) {
        return 0;
    }

    descs = config->spawn_descs;
    spawns = config->spawns;
    for (i = 0; i < config->count; i++, descs++, spawns++) {
        lb_8000B1CC(jobj, &descs->pos0, &spawns->pos0);
        lb_8000B1CC(jobj, &descs->pos1, &spawns->pos1);
    }

    spawns = config->spawns;
    for (i = 0; i < config->count; i++, spawns++) {
        if (!((spawns->pos0.y > height && spawns->pos1.y > height) ||
              (spawns->pos0.y < height && spawns->pos1.y < height)))
        {
            if (config->x10 < 0.0f || HSD_Randf() < config->x10) {
                f32 dy = spawns->pos1.y - spawns->pos0.y;
                if (ABS(dy) > 0.0001f) {
                    t = (height - spawns->pos0.y) / dy;
                    grZakoGenerator_801CA43C_inline(t, spawns, height, &pos);
                } else {
                    grZakoGenerator_801CA43C_inline(HSD_Randf(), spawns,
                                                    height, &pos);
                }

                if (config->x10 < 0.0f) {
                    HSD_Generator* gen = config->gen;
                    if (gen == NULL) {
                        config->gen = config->callback(&pos, i);
                    } else {
                        gen->pos.x = pos.x;
                        gen->pos.y = pos.y;
                        gen->pos.z = pos.z;
                    }
                } else {
                    config->callback(&pos, i);
                }
                spawned++;
            }
        } else if (config->x10 < 0.0f) {
            if (config->gen != NULL) {
                grLib_801C9874(config->gen);
                config->gen = NULL;
            }
        }
    }
    return spawned;
}

grZakoGenerator_Data* grZakoGenerator_801CA67C(void)
{
    grZakoGenerator_Data* data = HSD_MemAlloc(sizeof(grZakoGenerator_Data));
    int i;
    PAD_STACK(8);

    if (data == NULL) {
        __assert("grzakogenerator.c", 0x52, "pointp");
    }

    for (i = 0; i < 80; i++) {
        data->entries[i].x0 = i + 0x20;
        data->entries[i].x2 = 0;
        data->entries[i].x4 = 0;
    }
    // NOTE: this actually intializes data->sentinel
    for (; i < 81; i++) {
        data->entries[i].x0 = -1;
        data->entries[i].x2 = 0;
        data->entries[i].x4 = 0;
    }

    lbl_8049F030.xA_b0 = true;
    lbl_8049F030.x8 = 0;
    return data;
}

void grZakoGenerator_801CA8B4(int arg0)
{
    if (lbl_8049F030.x4 != NULL && lbl_8049F030.xA_b0) {
        f32 right = Stage_GetBlastZoneRightOffset();
        f32 left = Stage_GetBlastZoneLeftOffset();
        f32 top = Stage_GetBlastZoneTopOffset();
        f32 bottom = Stage_GetBlastZoneBottomOffset();
        f32 cam_right = 0.5f * (right + Stage_GetCamBoundsRightOffset());
        f32 cam_left = 0.5f * (left + Stage_GetCamBoundsLeftOffset());
        f32 cam_top = 0.5f * (top + Stage_GetCamBoundsTopOffset());
        f32 cam_bottom = 0.5f * (bottom + Stage_GetCamBoundsBottomOffset());
        int start = lbl_8049F030.x8;
        int idx = start;
        int max_iter;
        Vec3 pos;

        for (max_iter = 0xFF; max_iter > 0; max_iter--) {
            grZakoGenerator_Entry* entry = &lbl_8049F030.x4->entries[idx];

            if (entry->x0 != -1 && entry->x4 == 0) {
                if (lbl_8049F030.x4->entries[idx].x2 != -1) {
                    if (lbl_8049F030.x4->entries[idx].x2 > 0) {
                        lbl_8049F030.x4->entries[idx].x2--;
                    } else if (Ground_801C2D24(entry->x0, &pos)) {
                        if (left < pos.x && pos.x < right && bottom < pos.y &&
                            pos.y < top &&
                            (arg0 != 0 || !(cam_left < pos.x) ||
                             !(pos.x < cam_right) || !(cam_bottom < pos.y) ||
                             !(pos.y < cam_top)))
                        {
                            Item_GObj* gobj = NULL;
                            grZakoGenerator_Entry* e2 =
                                &lbl_8049F030.x4->entries[idx];

                            s16 k = e2->x0;
                            if (k >= 0xDC && k <= 0xFB) {
                                if (e2->x8 != -1) {
                                    gobj = Ground_801C58E0(e2->x8, k);
                                    if (gobj != NULL) {
                                        lbl_8049F030.x4->entries[idx].x4 =
                                            gobj;
                                    }
                                }
                            } else if (lbl_8049F030.x0 != NULL) {
                                s32 desc_idx = k - 0x20;
                                switch (lbl_8049F030.x0[desc_idx].kind) {
                                case 0x2B:
                                    gobj = it_8027B5B0(It_Kind_Kuriboh, &pos,
                                                       NULL, NULL, 1);
                                    break;
                                case 0x2C:
                                    gobj = it_802EA9FC(&pos, -1);
                                    break;
                                case 0x2D:
                                    gobj = it_8027B5B0(It_Kind_Octarock, &pos,
                                                       NULL, NULL, 1);
                                    break;
                                case 0x2E:
                                    gobj = it_8027B5B0(It_Kind_Ottosea, &pos,
                                                       NULL, NULL, 1);
                                    break;
                                case 0xD3:
                                    gobj = it_802DD7F0(
                                        lbl_8049F030.x0[desc_idx].x2, &pos,
                                        NULL, -1);
                                    break;
                                case 0xD4:
                                    gobj = it_802E16F8(
                                        lbl_8049F030.x0[desc_idx].x2, &pos,
                                        -1);
                                    break;
                                case 0xD5:
                                    gobj = it_802DC4BC(
                                        lbl_8049F030.x0[desc_idx].x2, &pos,
                                        -1);
                                    break;
                                case 0xD9:
                                    gobj = it_8027B5B0(It_Kind_Whitebea, &pos,
                                                       NULL, NULL, 1);
                                    break;
                                }
                                if (gobj != NULL) {
                                    Item* ip = GET_ITEM(gobj);
                                    lbl_8049F030.x4->entries[idx].x4 = gobj;
                                    ip->xDD4_itemVar.zako.idx = idx;
                                }
                            }
                        }
                    }
                }
            }

            idx++;
            if (idx >= 0x51) {
                idx = 0;
            }
            if (idx == start) {
                break;
            }
        }

        lbl_8049F030.x8 = idx;
    }
}

void grZakoGenerator_801CAC14(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 kind = itGetKind(gobj);

    if (kind == 0x9F) {
        grZakoGenerator_Data* data = lbl_8049F030.x4;
        if (data->sentinel.x4 == gobj) {
            data->sentinel.x4 = NULL;
        }
    } else {
        s32 idx = ip->xDD4_itemVar.zako.idx;
        if (idx != -1) {
            lbl_8049F030.x4->entries[idx].x4 = NULL;
            lbl_8049F030.x4->entries[idx].x2 = 2;
        }
    }
}

void grZakoGenerator_801CACB8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 kind = itGetKind(gobj);

    it_8027CE18(gobj);

    if (kind == 0x9F) {
        if (lbl_8049F030.x4->sentinel.x4 == gobj) {
            lbl_8049F030.x4->sentinel.x0 = -1;
            lbl_8049F030.x4->sentinel.x4 = NULL;
        }
    } else {
        s32 idx = ip->xDD4_itemVar.zako.idx;
        if (idx != -1) {
            int off = lbl_8049F030.x4->entries[idx].x0 - 0x20;
            lbl_8049F030.x4->entries[idx].x4 = NULL;
            if (lbl_8049F030.x0[off].respawn == 1) {
                lbl_8049F030.x4->entries[idx].x2 = 0x708;
            } else {
                lbl_8049F030.x4->entries[idx].x2 = -1;
            }
            ip->xDD4_itemVar.zako.idx = -1;
        }
    }
}

void fn_801CADBC(HSD_GObj* gobj)
{
    grZakoGenerator_801CA8B4(0);
}

void grZakoGenerator_801CADE0(void)
{
    grZakoGenerator_801CA8B4(1);
}

HSD_GObj* grZakoGenerator_801CAE04(grZakoGenerator_SpawnDesc* arg0)
{
    HSD_GObj* gobj;
    grZakoGenerator_Data* data = grZakoGenerator_801CA67C();
    gobj = GObj_Create(2, 4, 0);

    if (gobj == NULL) {
        OSReport("%s:%d: couldn t get gobj!\n", "grzakogenerator.c", 0x166);
        HSD_Free(data);
        return NULL;
    }

    HSD_GObj_SetupProc(gobj, fn_801CADBC, 0);
    lbl_8049F030.x0 = arg0;
    lbl_8049F030.x4 = data;
    return gobj;
}

void grZakoGenerator_801CAEB0(int arg0, int arg1)
{
    s16 val = arg1;
    if (lbl_8049F030.x4->sentinel.x0 == -1) {
        lbl_8049F030.x4->sentinel.x0 = val;
        lbl_8049F030.x4->sentinel.x8 = arg0;
        lbl_8049F030.x4->sentinel.x4 = NULL;
    }
}

void grZakoGenerator_801CAEF0(bool arg0)
{
    lbl_8049F030.xA_b0 = arg0;
}

void grZakoGenerator_801CAF08(void)
{
    HSD_GObj* next;
    HSD_GObj* cur;
    PAD_STACK(8);

    lbl_8049F030.xA_b0 = false;
    cur = HSD_GObj_Entities->items;

    while (cur != NULL) {
        next = cur->next;
        {
            s32 kind = itGetKind(cur);
            if ((kind >= 0x2B && kind < 0x30) || (kind >= 0xD0 && kind < 0xE8))
            {
                if (it_8026C1E8(cur)) {
                    Item_8026A8EC(cur);
                }
            } else if (kind == 0x9F) {
                Item_8026A8EC(cur);
            }
        }
        cur = next;
    }
}

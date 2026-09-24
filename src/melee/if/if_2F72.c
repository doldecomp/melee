#include "if_2F72.h"

#include "if_2F6E.h"
#include "ifall.h"
#include "ifstatus.h"
#include "types.h"
#include <melee/gm/gm_1601.h>
#include <melee/gm/gmvs.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>

/// Orphaned data strings from original ROM
static char lbl_803F9780[] = "ScInfStc_scene_models";

/// The GObjs one player slot has spawned from ScInfStc_scene_models.
struct ScInfStcSlot {
    HSD_GObj* gobj;  ///< spawned when a KO is recorded
    HSD_GObj* gobj2; ///< spawned by gobj's proc once it passes frame 12
};

/// ScInfStc_scene_models, plus the GObjs spawned from it per player slot.
struct ScInfStcModels {
    DynamicModelDesc** scene_models;
    struct ScInfStcSlot slots[6];
};

static struct ScInfStcModels scinfstc_models;

s32 fn_802F7288(HSD_GObj* gobj, Element_803F9628* entry)
{
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    f32 frame = lbGetJObjCurrFrame(jobj);

    HSD_JObjAnimAll(jobj);

    if (!entry->x12.x0) {
        if (frame >= (f32) entry->x10) {
            if (entry->x20 >= 0) {
                lbAudioAx_800237A8(entry->x20, 127, 64);
                entry->x12.x0 = 1;
            } else if (entry->xC >= 0) {
                lbAudioAx_800237A8(entry->xC, 127, 64);
                entry->x12.x0 = 1;
            }
        }
    }

    if (!entry->x12.x1) {
        if (frame >= (f32) entry->x11) {
            if (entry->x24 >= 0) {
                lbAudioAx_800237A8(entry->x24, 127, 64);
                entry->x12.x1 = 1;
            }
        }
    }

    return lb_8000B09C(jobj);
}

static inline Element_803F9628* FindEntry(Element_803F9628* entries,
                                          HSD_GObj* gobj)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        if (entries[i].x0 == gobj) {
            return &entries[i];
        }
    }
    return NULL;
}

void if_802F73C4(HSD_GObj* gobj)
{
    Element_803F9628* const entries = ifStatus_803F9628;
    Element_803F9628* entry = FindEntry(entries, gobj);
    s32 idx = ((u8*) entry - (u8*) entries) / sizeof(*entry);

    if (entry != NULL && !entry->x12.x2) {
        if (entry->x18 != NULL) {
            entry->x18(idx);
        }
        entry->x12.x2 = 1;
    }
    if (entry != NULL) {
        if (fn_802F7288(gobj, entry) == 0) {
            if (entry->x1C != NULL) {
                entry->x1C(idx);
            }
            entry->x0 = NULL;
            HSD_GObjFree(gobj);
        }
    }
}

void if_802F74D0(HSD_GObj* gobj)
{
    Element_803F9628* const entries = ifStatus_803F9628;
    Element_803F9628* entry;
    s32 i;
    Element_803F9628* curr;
    s32 idx;

    curr = entries;
    for (i = 0; i < 8; curr++, i++) {
        if (curr->x0 == gobj) {
            entry = &entries[i];
            goto found;
        }
    }
    entry = NULL;

found:
    idx = ((u8*) entry - (u8*) entries) / sizeof(*entry);
    if (entry != NULL && !entry->x12.x2) {
        if (entry->x18 != NULL) {
            entry->x18(idx);
        }
        entry->x12.x2 = 1;
    }
    if (entry != NULL) {
        if (fn_802F7288(gobj, entry) == 0) {
            if (entry->x1C != NULL) {
                entry->x1C(idx);
            }
            entry->x1C = NULL;
        }
    }
}

void fn_802F75D4(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    struct ScInfStcModels* models;
    s32 i;

    if (lb_8000B09C(jobj) == 0) {
        models = &scinfstc_models;
        for (i = 0; i < 6; i++) {
            if (models->slots[i].gobj == gobj) {
                models->slots[i].gobj = NULL;
                break;
            }
        }
        HSD_GObjFree(gobj);
    } else {
        HSD_JObjAnimAll(jobj);
    }
}

void fn_802F7670(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    struct ScInfStcModels* models;
    s32 i;

    if (lb_8000B09C(jobj) == 0) {
        models = &scinfstc_models;
        for (i = 0; i < 6; i++) {
            if (models->slots[i].gobj2 == gobj) {
                models->slots[i].gobj2 = NULL;
                break;
            }
        }
        HSD_GObjFree(gobj);
    } else {
        HSD_JObjAnimAll(jobj);
    }
}

/// Slot whose first GObj is @p gobj, or -1.
static inline s32 GetSlot(HSD_GObj* gobj)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        if (scinfstc_models.slots[i].gobj == gobj) {
            return i;
        }
    }
    return -1;
}

void fn_802F770C(HSD_GObj* gobj, intptr_t callback)
{
    HudIndex* status = ifStatus_GetHUDInfo();
    s32 slot = GetSlot(gobj);

    if (!status->players[slot].flags.hide_all_digits) {
        HSD_GObj_JObjCallback(gobj, callback);
    }
}

HSD_GObj* fn_802F77F8(HSD_GObj* gobj, u8 slot, u16 arg2)
{
    struct ScInfStcModels* models = &scinfstc_models;
    HSD_JObj* jobj;
    Vec3* pos;
    HSD_JObj* j;

    if (models->scene_models == NULL) {
        return NULL;
    }

    if (gobj != NULL) {
        HSD_GObjFree(gobj);
    }

    gobj = GObj_Create(14, 15, 0);
    if (gobj != NULL) {
        jobj = HSD_JObjLoadJoint((*models->scene_models)->joint);
        if (jobj != NULL) {
            HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
            GObj_SetupGXLink(gobj, fn_802F770C, 11, 0);
            j = jobj;
            gm_8016895C(j, *models->scene_models, (u8) arg2);
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);

            pos = ifAll_GetPlayerHUDPosition(slot);
            HSD_JObjSetTranslate(jobj, pos);
        } else {
            HSD_GObjFree(gobj);
            gobj = NULL;
        }
    }

    return gobj;
}

/// (Re)spawns the second GObj of @p slot.
static inline void SpawnGObj2(s32 slot)
{
    struct ScInfStcModels* models = &scinfstc_models;
    s32 idx = (u8) slot;
    HSD_GObj** gobjp = &models->slots[(u8) slot].gobj - 1;

    models->slots[idx].gobj2 = fn_802F77F8(*(gobjp += 2), (u8) slot, 1);
    if (models->slots[idx].gobj2 != NULL) {
        HSD_GObj_SetupProc(*gobjp, fn_802F7670, 0x11);
    }
}

void fn_802F7994(HSD_GObj* gobj)
{
    struct ScInfStcModels* models = &scinfstc_models;
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 frame = lbGetJObjCurrFrame(jobj);
    s32 slot = GetSlot(gobj);

    if (slot >= 0) {
        if (frame > 12.0f && models->slots[slot].gobj2 == NULL) {
            SpawnGObj2(slot);
        }
        if (lb_8000B09C(jobj) == 0) {
            models->slots[slot].gobj = NULL;
            HSD_GObjFree(gobj);
        } else {
            HSD_JObjAnimAll(jobj);
        }
    }
}

/// (Re)spawns the first GObj of @p slot with animation @p anim.
/// @todo The spawn sites point one entry before the slot's GObj and
/// pre-increment onto it; a direct pointer allocates differently.
static inline void SpawnGObj(s32 slot, u16 anim, HSD_GObjEvent proc)
{
    struct ScInfStcModels* models = &scinfstc_models;
    u8 idx = slot;
    HSD_GObj** gobjp = &models->slots[idx].gobj - 1;

    models->slots[idx].gobj = fn_802F77F8(*++gobjp, idx, anim);
    if (models->slots[idx].gobj != NULL) {
        HSD_GObj_SetupProc(*gobjp, proc, 0x11);
    }
}

void if_802F7AF8(s32 slot)
{
    struct ScInfStcModels* models = &scinfstc_models;
    struct ScInfStcSlot* slots;
    s32 slot2 = Player_80036428(slot);
    s32 idx;
    HSD_GObj* result;

    idx = (u8) slot;
    result = fn_802F77F8(models->slots[idx].gobj, (u8) slot, 1);
    slots = models->slots;
    slots[idx].gobj = result;
    if (slots[idx].gobj != NULL) {
        HSD_GObj_SetupProc(models->slots[idx].gobj, fn_802F75D4, 0x11);
    }

    idx = (u8) slot2;
    result = fn_802F77F8(models->slots[idx].gobj, (u8) slot2, 2);
    slots[idx].gobj = result;
    if (slots[idx].gobj != NULL) {
        HSD_GObj_SetupProc(models->slots[idx].gobj, fn_802F75D4, 0x11);
    }
}

void if_802F7BB4(s32 player_idx)
{
    struct ScInfStcModels* models = &scinfstc_models;
    u8 idx = player_idx;
    HSD_GObj** gobjp = &models->slots[idx].gobj - 1;

    models->slots[idx].gobj = fn_802F77F8(*++gobjp, idx, 1);
    if (models->slots[idx].gobj != NULL) {
        HSD_GObj_SetupProc(*gobjp, fn_802F75D4, 0x11);
    }
}

void if_802F7C30(s32 slot)
{
    struct ScInfStcModels* models = &scinfstc_models;
    s32 ret = gm_8016AEC8();
    u8 idx;
    HSD_GObj** gobjp;

    if (ret == -2) {
        idx = slot;
        gobjp = &models->slots[idx].gobj - 1;
        models->slots[idx].gobj = fn_802F77F8(*++gobjp, idx, 0);
        if (models->slots[idx].gobj != NULL) {
            HSD_GObj_SetupProc(*gobjp, fn_802F75D4, 0x11);
        }
    } else if (ret == -1) {
        SpawnGObj(slot, 1, fn_802F75D4);
    }
}

void if_802F7D08(s32 slot)
{
    struct ScInfStcModels* models = &scinfstc_models;
    s32 ret = gm_8016AEC8();
    u8 idx;
    HSD_GObj** gobjp;

    if (ret == -2) {
        idx = slot;
        gobjp = &models->slots[idx].gobj - 1;
        models->slots[idx].gobj = fn_802F77F8(*++gobjp, idx, 0);
        if (models->slots[idx].gobj != NULL) {
            HSD_GObj_SetupProc(*gobjp, fn_802F7994, 0x11);
        }
    } else if (ret == -1) {
        SpawnGObj(slot, 1, fn_802F7994);
    } else {
        SpawnGObj(slot, 1, fn_802F75D4);
    }
}

void if_802F7E24(void)
{
    memzero(&scinfstc_models, sizeof(scinfstc_models));
    lbArchive_LoadSections(*ifAll_GetArchive(), &scinfstc_models.scene_models,
                           lbl_803F9780, 0);
}

void if_802F7E7C(void)
{
    s32 i;
    struct ScInfStcModels* models = &scinfstc_models;

    for (i = 0; i < 6; i++) {
        if (models->slots[i].gobj != NULL) {
            HSD_GObjFree(models->slots[i].gobj);
        }
        if (models->slots[i].gobj2 != NULL) {
            HSD_GObjFree(models->slots[i].gobj2);
        }
    }

    memzero(models, sizeof(scinfstc_models));
}

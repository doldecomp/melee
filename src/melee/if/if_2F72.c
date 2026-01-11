#include "if_2F72.h"

#include "gm/gm_1601.h"
#include "gm/gm_16AE.h"
#include "if/ifall.h"
#include "if/ifstatus.h"
#include "if/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "pl/player.h"

#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

// Orphaned data strings from original ROM
static char lbl_803F9780[] = "ScInfStc_scene_models";
static char lbl_803F9798[] = "translate";

static void* lbl_804A1340[13];

s32 fn_802F7288(HSD_GObj* gobj, Element_803F9628* entry)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 frame = lbGetJObjCurrFrame(jobj);
    s32 unused;

    HSD_JObjAnimAll(jobj);

    if (!entry->x12.x0) {
        if (frame >= (f32) entry->x10) {
            if ((s32) entry->x20 >= 0) {
                lbAudioAx_800237A8(entry->x20, 127, 64);
                entry->x12.x0 = 1;
            } else if ((s32) entry->xC >= 0) {
                lbAudioAx_800237A8(entry->xC, 127, 64);
                entry->x12.x0 = 1;
            }
        }
    }

    if (!entry->x12.x1) {
        if (frame >= (f32) entry->x11) {
            if ((s32) entry->x24 >= 0) {
                lbAudioAx_800237A8(entry->x24, 127, 64);
                entry->x12.x1 = 1;
            }
        }
    }

    return lb_8000B09C(jobj);
}

void if_802F73C4(HSD_GObj* gobj)
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
    idx = ((u8*) entry - (u8*) entries) / sizeof(Element_803F9628);
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
            HSD_GObjPLink_80390228(gobj);
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
    idx = ((u8*) entry - (u8*) entries) / sizeof(Element_803F9628);
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
    void** base;
    void** data;
    s32 i;

    if (lb_8000B09C(jobj) == 0) {
        base = lbl_804A1340;
        data = base;
        for (i = 0; i < 6; data += 2, i++) {
            if (data[1] == gobj) {
                base[i * 2 + 1] = NULL;
                goto done;
            }
        }
    done:
        HSD_GObjPLink_80390228(gobj);
    } else {
        HSD_JObjAnimAll(jobj);
    }
}

void fn_802F7670(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    void** base;
    void** data;
    s32 i;

    if (lb_8000B09C(jobj) == 0) {
        base = lbl_804A1340;
        data = base;
        for (i = 0; i < 6; data += 2, i++) {
            if (data[2] == gobj) {
                base[i * 2 + 2] = NULL;
                goto done;
            }
        }
    done:
        HSD_GObjPLink_80390228(gobj);
    } else {
        HSD_JObjAnimAll(jobj);
    }
}

void fn_802F770C(HSD_GObj* gobj, int callback)
{
    HudIndex* status = ifStatus_802F4910();
    void** ptr = lbl_804A1340;
    s32 slot;
    void* temp;

    if (ptr[1] == gobj) {
        slot = 0;
    } else {
        ptr += 2;
        temp = ptr[1];
        if (temp == gobj) {
            slot = 1;
        } else {
            temp = ptr[3];
            ptr += 2;
            if (temp == gobj) {
                slot = 2;
            } else {
                temp = ptr[3];
                ptr += 2;
                if (temp == gobj) {
                    slot = 3;
                } else {
                    temp = ptr[3];
                    ptr += 2;
                    if (temp == gobj) {
                        slot = 4;
                    } else {
                        temp = ptr[3];
                        if (temp == gobj) {
                            slot = 5;
                        } else {
                            slot = -1;
                        }
                    }
                }
            }
        }
    }

    if (!((((u8*) status)[slot * 100 + 16] >> 3) & 1)) {
        HSD_GObj_JObjCallback(gobj, callback);
    }
}

HSD_GObj* fn_802F77F8(HSD_GObj* gobj, u8 slot, s32 arg2)
{
    void** base = lbl_804A1340;
    HSD_GObj* new_gobj = gobj;
    s32 arg2_copy = arg2;
    HSD_JObj* jobj;
    Vec3* pos;

    if (base[0] == NULL) {
        return NULL;
    }

    if (new_gobj != NULL) {
        HSD_GObjPLink_80390228(new_gobj);
    }

    new_gobj = GObj_Create(14, 15, 0);
    if (new_gobj == NULL) {
        goto end;
    }

    jobj = HSD_JObjLoadJoint(*(*(HSD_Joint***) base[0]));
    if (jobj == NULL) {
        HSD_GObjPLink_80390228(new_gobj);
        new_gobj = NULL;
        goto end;
    }

    HSD_GObjObject_80390A70(new_gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(new_gobj, fn_802F770C, 11, 0);
    gm_8016895C(jobj, *(DynamicModelDesc**) base[0], (u8) arg2_copy);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);

    pos = ifAll_802F3424(slot);
    if (jobj == NULL) {
        __assert("jobj.h", 0x394, "jobj");
    }
    if (pos == NULL) {
        __assert("jobj.h", 0x395, "jobj");
    }

    jobj->translate = *pos;

    if (!(jobj->flags & 0x02000000)) {
        s32 is_dirty;
        u32 flags;

        if (jobj == NULL) {
            __assert("jobj.h", 0x234, "jobj");
        }
        flags = jobj->flags;
        is_dirty = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            is_dirty = 1;
        }
        if (is_dirty == 0) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }

end:
    return new_gobj;
}

void fn_802F7994(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    void** base = lbl_804A1340;
    void** ptr;
    s32 slot;
    void* cmp;
    f32 frame;

    jobj = gobj->hsd_obj;
    frame = lbGetJObjCurrFrame(jobj);

    if (base[1] == gobj) {
        slot = 0;
    } else {
        ptr = base + 2;
        cmp = base[3];
        if (cmp == gobj) {
            slot = 1;
        } else {
            cmp = ptr[3];
            ptr += 2;
            if (cmp == gobj) {
                slot = 2;
            } else {
                cmp = ptr[3];
                ptr += 2;
                if (cmp == gobj) {
                    slot = 3;
                } else {
                    cmp = ptr[3];
                    ptr += 2;
                    if (cmp == gobj) {
                        slot = 4;
                    } else {
                        cmp = ptr[3];
                        if (cmp == gobj) {
                            slot = 5;
                        } else {
                            slot = -1;
                        }
                    }
                }
            }
        }
    }

    if (slot >= 0) {
        if (frame > 0.0f && base[slot * 2 + 2] == NULL) {
            s32 idx = (u8) slot << 3;
            void** entry = base + idx;
            base[idx + 2] = fn_802F77F8(*++entry, (u8) slot, 1);
            if (base[idx + 2] != NULL) {
                HSD_GObjProc_8038FD54(*entry, (HSD_GObjEvent) fn_802F7670,
                                      0x11);
            }
        }
        if (lb_8000B09C(jobj) == 0) {
            base[slot * 2 + 1] = NULL;
            HSD_GObjPLink_80390228(gobj);
        } else {
            HSD_JObjAnimAll(jobj);
        }
    }
}

void if_802F7AF8(s32 slot)
{
    s32 idx;
    void** entry;
    void** base1;
    void** base = lbl_804A1340;
    s32 slot2 = Player_80036428(slot);
    HSD_GObj* result;

    idx = (u8) slot << 1;
    entry = base + idx;
    result = fn_802F77F8(*++entry, (u8) slot, 1);
    base1 = &base[1];
    base1[idx] = result;
    if (base1[idx] != NULL) {
        HSD_GObjProc_8038FD54(*entry, (HSD_GObjEvent) fn_802F75D4, 0x11);
    }

    idx = (u8) slot2 << 1;
    entry = base + idx;
    result = fn_802F77F8(*++entry, (u8) slot2, 2);
    base1[idx] = result;
    if (base1[idx] != NULL) {
        HSD_GObjProc_8038FD54(*entry, (HSD_GObjEvent) fn_802F75D4, 0x11);
    }
}

void if_802F7BB4(s32 player_idx)
{
    void** base;
    u8 idx;
    s32 offset;
    void** entry;

    base = lbl_804A1340;
    idx = (u8) player_idx;
    offset = idx << 1;
    entry = base + offset;
    (base + offset)[1] = fn_802F77F8(*++entry, idx, 1);
    if ((base + offset)[1] != NULL) {
        HSD_GObjProc_8038FD54(*entry, (HSD_GObjEvent) fn_802F75D4, 0x11);
    }
}

void if_802F7C30(s32 slot)
{
    void** base = lbl_804A1340;
    s32 idx;
    void** entry;
    s32 ret = gm_8016AEC8();
    HSD_GObj* result;

    if (ret == -2) {
        idx = (u8) slot << 1;
        entry = base + idx;
        result = fn_802F77F8(*++entry, (u8) slot, 0);
        base[idx + 1] = result;
        if (base[idx + 1] != NULL) {
            HSD_GObjProc_8038FD54(*entry, (HSD_GObjEvent) fn_802F75D4, 0x11);
        }
    } else if (ret == -1) {
        idx = (u8) slot << 1;
        entry = base + idx;
        result = fn_802F77F8(*++entry, (u8) slot, 1);
        base[idx + 1] = result;
        if (base[idx + 1] != NULL) {
            HSD_GObjProc_8038FD54(*entry, (HSD_GObjEvent) fn_802F75D4, 0x11);
        }
    }
}

void if_802F7D08(s32 slot)
{
    void** base = lbl_804A1340;
    s32 idx;
    void** entry;
    s32 ret = gm_8016AEC8();
    HSD_GObj* result;

    if (ret == -2) {
        idx = (u8) slot << 1;
        entry = base + idx;
        result = fn_802F77F8(*++entry, (u8) slot, 0);
        base[idx + 1] = result;
        if (base[idx + 1] != NULL) {
            HSD_GObjProc_8038FD54(*entry, (HSD_GObjEvent) fn_802F7994, 0x11);
        }
    } else if (ret == -1) {
        idx = (u8) slot << 1;
        entry = base + idx;
        result = fn_802F77F8(*++entry, (u8) slot, 1);
        base[idx + 1] = result;
        if (base[idx + 1] != NULL) {
            HSD_GObjProc_8038FD54(*entry, (HSD_GObjEvent) fn_802F7994, 0x11);
        }
    } else {
        idx = (u8) slot << 1;
        entry = base + idx;
        result = fn_802F77F8(*++entry, (u8) slot, 1);
        base[idx + 1] = result;
        if (base[idx + 1] != NULL) {
            HSD_GObjProc_8038FD54(*entry, (HSD_GObjEvent) fn_802F75D4, 0x11);
        }
    }
}

void if_802F7E24(void)
{
    memzero(lbl_804A1340, 0x34);
    lbArchive_LoadSections(*ifAll_802F3690(), lbl_804A1340, lbl_803F9780, 0);
}

void if_802F7E7C(void)
{
    HSD_GObj** data = (HSD_GObj**) lbl_804A1340;
    s32 i = 0;
    HSD_GObj** base = (HSD_GObj**) lbl_804A1340;

    do {
        if (data[1] != NULL) {
            HSD_GObjPLink_80390228(data[1]);
        }
        if (data[2] != NULL) {
            HSD_GObjPLink_80390228(data[2]);
        }
        i++;
        data += 2;
    } while (i < 6);
    memzero(base, 0x34);
}

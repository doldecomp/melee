#include "mnsnap.h"

#include <placeholder.h>

#include "baselib/debug.h"

#include <baselib/aobj.h>
#include <baselib/dobj.h>
#include <baselib/gobjobject.h>
#include <baselib/jobj.h>
#include <baselib/mobj.h>
#include <baselib/sislib.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbsnap.h>
#include <melee/mn/inlines.h>
#include <melee/mn/mnmain.h>

static const f32 mnSnap_804DC2C0 = 0.0F;
static const f32 mnSnap_804DC2C4 = 50.0F;
static const f32 mnSnap_804DC2C8 = 5.0F;
static const f32 mnSnap_804DC2CC = 25.0F;
static const f32 mnSnap_804DC2D0 = 1.0F;
static const f32 mnSnap_804DC2D4 = 4.0F;
static const f64 mnSnap_804DC2D8 = 4503601774854144.0; // 0x4330000000000000
static const f32 mnSnap_804DC2E0 = 2.0F;
static const f32 mnSnap_804DC2E4 = -6.9F;
static const f32 mnSnap_804DC2E8 = -3.5F;
static const f32 mnSnap_804DC2EC = 3.5F;
static const f32 mnSnap_804DC2F0 = -2.9F;
static const f32 mnSnap_804DC2F4 = 23.0F;
static const f32 mnSnap_804DC2F8 = 440.0F;
static const f32 mnSnap_804DC2FC = 10.0F;
static const f32 mnSnap_804DC300 = 0.03F;
static const f32 mnSnap_804DC304 = 6.0F;
static const f32 mnSnap_804DC308 = -3.0F;
static const f32 mnSnap_804DC30C = 3.0F;
static const f32 mnSnap_804DC310 = 3.3F;
static const f32 mnSnap_804DC314 = -11.2F;
static const f32 mnSnap_804DC318 = -2.6F;
static const f32 mnSnap_804DC31C = 19.8F;
static const f32 mnSnap_804DC320 = 0.028F;
static const f32 mnSnap_804DC324 = 0.031F;
static const f32 mnSnap_804DC328 = 4.4F;
static const f32 mnSnap_804DC32C = 10.9F;
static const f32 mnSnap_804DC330 = -11.6F;
static const f32 mnSnap_804DC334 = 9.0F;
static const f32 mnSnap_804DC338 = 17.3F;
static const f32 mnSnap_804DC33C = 0.045F;
static const f32 mnSnap_804DC340 = 11.0F;
static const f32 mnSnap_804DC344 = -1.8F;
static const f32 mnSnap_804DC348 = 9.2F;
static const f32 mnSnap_804DC34C = 17.0F;
static const f32 mnSnap_804DC350 = 0.04F;
static const f32 mnSnap_804DC354 = 1.6F;

typedef struct mnSnap_State {
    /* 0x000 */ s32 frame_count;
    /* 0x004 */ s32 timer;
    /* 0x008 */ HSD_GObj* main_gobj;
    /* 0x00C */ HSD_GObj* cursor_gobj;
    /* 0x010 */ HSD_GObj* sub_gobj;
    /* 0x014 */ HSD_GObj* warn_gobj;
    /* 0x018 */ void* main_joint;
    /* 0x01C */ void* main_animjoint;
    /* 0x020 */ void* main_matanim;
    /* 0x024 */ void* main_shapeanim;
    /* 0x028 */ void* csr_joint;
    /* 0x02C */ void* csr_animjoint;
    /* 0x030 */ void* csr_matanim;
    /* 0x034 */ void* csr_shapeanim;
    /* 0x038 */ void* photo_joint;
    /* 0x03C */ void* sub_animjoint;
    /* 0x040 */ void* sub_matanim;
    /* 0x044 */ void* sub_shapeanim;
    /* 0x048 */ void* page_joint;
    /* 0x04C */ void* load_joint;
    /* 0x050 */ void* load_animjoint;
    /* 0x054 */ void* load_matanim;
    /* 0x058 */ void* arrows_joint;
    /* 0x05C */ void* arrows_animjoint;
    /* 0x060 */ void* arrows_matanim;
    /* 0x064 */ void* arrows_shapeanim;
    /* 0x068 */ void* warn_joint;
    /* 0x06C */ void* warn_animjoint;
    /* 0x070 */ void* warn_matanim;
    /* 0x074 */ void* warn_shapeanim;
    /* 0x078 */ HSD_JObj* thumb_jobjs[4];
    /* 0x088 */ HSD_JObj* select_jobj;
    /* 0x08C */ HSD_JObj* move_jobj;
    /* 0x090 */ HSD_JObj* arrow_jobj;
    /* 0x094 */ HSD_JObj* scroll_jobj;
    /* 0x098 */ HSD_JObj* slot_a_jobj;
    /* 0x09C */ HSD_JObj* slot_a_anim;
    /* 0x0A0 */ HSD_JObj* slot_b_jobj;
    /* 0x0A4 */ HSD_JObj* slot_b_anim;
    /* 0x0A8 */ HSD_JObj* thumb_root;
    /* 0x0AC */ HSD_JObj* submenu_jobj;
    /* 0x0B0 */ HSD_JObj* thumb_start;
    /* 0x0B4 */ HSD_JObj* thumb_end;
    /* 0x0B8 */ HSD_JObj* option_jobjs[5];
    /* 0x0CC */ HSD_JObj* fullview_jobj;
    /* 0x0D0 */ HSD_JObj* dlg_root;
    /* 0x0D4 */ HSD_JObj* dlg_pos;
    /* 0x0D8 */ HSD_JObj* dlg_x36;
    /* 0x0DC */ HSD_JObj* dlg_x37;
    /* 0x0E0 */ HSD_JObj* yes_jobj;
    /* 0x0E4 */ HSD_JObj* no_jobj;
    /* 0x0E8 */ HSD_JObj* dlg_frame;
    /* 0x0EC */ HSD_JObj* dlg_btn_l;
    /* 0x0F0 */ HSD_JObj* dlg_btn_r;
    /* 0x0F4 */ HSD_JObj* progress_jobj;
    /* 0x0F8 */ HSD_Text* thumb_labels[4];
    /* 0x108 */ HSD_Text* count_texts[2];
    /* 0x110 */ HSD_Text* page_text;
    /* 0x114 */ HSD_Text* total_text;
    /* 0x118 */ HSD_Text* dlg_text;
    /* 0x11C */ s32 state;
    /* 0x120 */ s32 photo_count[2];
    /* 0x128 */ s16 card_status[2];
    /* 0x12C */ s32 cursor_idx;
    /* 0x130 */ s32 move_idx;
    /* 0x134 */ s32 menu_sel;
    /* 0x138 */ s32 x4E;
    /* 0x13C */ s32 cur_page;
    /* 0x140 */ s32 active_slot;
    /* 0x144 */ s32 pending_loads;
    /* 0x148 */ s32 load_idx;
    /* 0x14C */ s32 dlg_active;
    /* 0x150 */ s32 dlg_timer;
    /* 0x154 */ s32 dlg_type;
    /* 0x158 */ s32 dlg_result;
    /* 0x15C */ s32 card_result;
    /* 0x160 */ s32 thumb_loaded[4];
    /* 0x170 */ HSD_JObj* left_btn;
    /* 0x174 */ HSD_JObj* right_btn;
    /* 0x178 */ s32 btn_idx;
    /* 0x17C */ void* blank_img;
} mnSnap_State;

static mnSnap_State mnSnap_804A0A10;
static void* mnSnap_thumb_imgs[4];

void mnSnap_80254298(void);

// @TODO: Currently 92.61% match - needs register allocation fix
// Recursively loads snapshot thumbnails from memory card.
void mnSnap_80253184(void)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    s32* p4F;
    s32* p52;
    s32* p50;
    s32* p57;
    s32* flags;
    s32* p51;

    p4F = &snap->cur_page;
    p52 = &snap->load_idx;
    p50 = &snap->active_slot;
    p57 = &snap->card_result;
    flags = &snap->thumb_loaded[0];
    *p57 = lbSnap_8001E058(*p50, *p52 + (*p4F * 4));
    if (*p57 == 8) {
        mnSnap_80254298();
        return;
    }
    if (*p57 != 11) {
        flags[*p52] = 1;
        *p52 += 1;
        p51 = &snap->pending_loads;
        *p51 -= 1;
        if (*p51 != 0) {
            *p57 = lbSnap_8001E058(*p50, *p52 + (*p4F * 4));
            if (*p57 == 8) {
                mnSnap_80254298();
                return;
            }
            if (*p57 != 11) {
                flags[*p52] = 1;
                *p52 += 1;
                *p51 -= 1;
                if (*p51 != 0) {
                    mnSnap_80253184();
                }
            }
        }
    }
}

// @TODO: Currently 88.85% match - needs register allocation fix
// Polls card read result and updates thumbnail display.
static void mnSnap_8025329C(void)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    s32* p52;
    s32* p51;
    s32* flags;
    s32 result;
    PAD_STACK(24);

    result = lb_8001B6F8();
    if (result == 11) {
        return;
    }
    if (result == 0) {
        HSD_JObj* jobj;
        void* img;
        s32 idx;

        p52 = &snap->load_idx;
        idx = snap->load_idx % 4;
        if (lbSnap_8001DE8C((void*) mnSnap_thumb_imgs[idx]) == 1) {
            jobj = snap->thumb_jobjs[snap->load_idx];
            img = (void*) mnSnap_thumb_imgs[idx];
            HSD_ASSERT(193, jobj);
            HSD_ASSERT(194, jobj->u.dobj);
            HSD_ASSERT(195, jobj->u.dobj->next);
            HSD_ASSERT(196, jobj->u.dobj->next->next);
            HSD_ASSERT(197, jobj->u.dobj->next->next->mobj);
            HSD_ASSERT(198, jobj->u.dobj->next->next->mobj->tobj);
            HSD_ASSERT(199, jobj->u.dobj->next->next->mobj->tobj->imagedesc);
            jobj->u.dobj->next->next->mobj->tobj->imagedesc->image_ptr = img;
            jobj->u.dobj->next->next->mobj->tobj->imagedesc->width = 0x280;
            jobj->u.dobj->next->next->mobj->tobj->imagedesc->height = 0x1E0;
        } else {
            flags = &snap->thumb_loaded[0];
            flags[idx] = 1;
        }

        p51 = &snap->pending_loads;
        *p52 += 1;
        *p51 -= 1;
        if (*p51 != 0) {
            snap->card_result = lbSnap_8001E058(snap->active_slot,
                                                *p52 + (snap->cur_page * 4));
            if (snap->card_result == 8) {
                mnSnap_80254298();
                return;
            }
            if (snap->card_result != 11) {
                flags = &snap->thumb_loaded[0];
                flags[*p52] = 1;
                *p52 += 1;
                *p51 -= 1;
                if (*p51 != 0) {
                    mnSnap_80253184();
                }
            }
        }
    } else if ((u32) (result - 2) <= 1) {
        p52 = &snap->load_idx;
        flags = &snap->thumb_loaded[0];
        flags[*p52 % 4] = 1;
        p51 = &snap->pending_loads;
        *p52 += 1;
        *p51 -= 1;
        if (*p51 != 0) {
            snap->card_result = lbSnap_8001E058(snap->active_slot,
                                                *p52 + (snap->cur_page * 4));
            if (snap->card_result == 8) {
                mnSnap_80254298();
                return;
            }
            if (snap->card_result != 11) {
                flags[*p52] = 1;
                *p52 += 1;
                *p51 -= 1;
                if (*p51 != 0) {
                    mnSnap_80253184();
                }
            }
        }
    } else if (result == 8) {
        mnSnap_80254298();
    } else {
        mnSnap_80254298();
    }
}

// @TODO: Currently 94.60% match - needs register allocation fix
// Loads a page of snapshot thumbnails and updates navigation arrows.
void mnSnap_80253640(s32 page)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    s32* p48 = &snap->photo_count[0];
    s32* p4F = &snap->cur_page;
    s32* p50 = &snap->active_slot;
    s32* p51;
    s32* p52;
    s32* p58;
    s32 count;
    s32 i;
    f32 t;
    PAD_STACK(28);

    *p4F = page;
    count = p48[*p50] - (page * 4);
    if (count > 4) {
        count = 4;
    }
    p51 = &snap->pending_loads;
    *p51 = count;
    i = 0;
    p52 = &snap->load_idx;
    *p52 = 0;
    p58 = &snap->thumb_loaded[0];
    *p58 = 0;
    snap->thumb_loaded[1] = 0;
    snap->thumb_loaded[2] = 0;
    snap->thumb_loaded[3] = 0;

    while (i < count) {
        HSD_JObj* jobj;
        void* img;

        HSD_DObjClearFlags(snap->thumb_jobjs[i]->u.dobj->next->next, 1);
        jobj = snap->thumb_jobjs[i];
        img = snap->blank_img;
        HSD_ASSERT(193, jobj);
        HSD_ASSERT(194, jobj->u.dobj);
        HSD_ASSERT(195, jobj->u.dobj->next);
        HSD_ASSERT(196, jobj->u.dobj->next->next);
        HSD_ASSERT(197, jobj->u.dobj->next->next->mobj);
        HSD_ASSERT(198, jobj->u.dobj->next->next->mobj->tobj);
        HSD_ASSERT(199, jobj->u.dobj->next->next->mobj->tobj->imagedesc);
        i += 1;
        jobj->u.dobj->next->next->mobj->tobj->imagedesc->image_ptr = img;
        jobj->u.dobj->next->next->mobj->tobj->imagedesc->width = 0x40;
        jobj->u.dobj->next->next->mobj->tobj->imagedesc->height = 0x30;
    }

    while (i < 4) {
        HSD_DObjSetFlags(snap->thumb_jobjs[i]->u.dobj->next->next, 1);
        i += 1;
    }

    snap->card_result = lbSnap_8001E058(*p50, *p52 + (*p4F * 4));
    if (snap->card_result == 8) {
        mnSnap_80254298();
    } else if (snap->card_result != 0xB) {
        p58[*p52] = 1;
        *p52 += 1;
        *p51 -= 1;
        if (*p51 != 0) {
            mnSnap_80253184();
        }
    }

    if (*p50 == 0) {
        t = 0.0F;
    } else {
        t = 50.0F;
    }
    HSD_JObjReqAnimAll(snap->scroll_jobj, t);
    HSD_JObjAnimAll(snap->scroll_jobj);

    if (p48[*p50] <= 4) {
        HSD_JObjSetFlagsAll(snap->arrow_jobj, 0x10);
    } else {
        HSD_JObjClearFlagsAll(snap->arrow_jobj, 0x10);
    }
}

// @TODO: Currently 95.82% match - needs register allocation fix
// Updates the SIS text labels showing thumbnail numbers and page info.
void mnSnap_80253964(void)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    s32 i;
    s32 page = snap->cur_page;
    s32 base = page * 4;

    PAD_STACK(8);

    for (i = 0; i < 4; i++, base++) {
        HSD_SisLib_803A7664(snap->thumb_labels[i]);
        if (snap->state >= 4 && base < snap->photo_count[snap->active_slot]) {
            HSD_SisLib_803A6B98(snap->thumb_labels[i], mnSnap_804DC2C0,
                                mnSnap_804DC2C0, "%03d", base + 1);
        }
    }

    for (i = 0; i < 2; i++) {
        HSD_SisLib_803A7664(snap->count_texts[i]);
        if (snap->state >= 4 && snap->card_status[i] == 1) {
            HSD_SisLib_803A6B98(snap->count_texts[i], mnSnap_804DC2C0,
                                mnSnap_804DC2C0, "%d", snap->photo_count[i]);
        }
    }

    {
        HSD_Text** p = &snap->page_text;
        HSD_SisLib_803A7664(*p);
        if (snap->state >= 4) {
            HSD_SisLib_803A6B98(*p, mnSnap_804DC2C0, mnSnap_804DC2C0, "%d",
                                page + 1);
        }

        p = &snap->total_text;
        HSD_SisLib_803A7664(*p);
        if (snap->state >= 4) {
            HSD_SisLib_803A6B98(*p, mnSnap_804DC2C0, mnSnap_804DC2C0, "%d",
                                (snap->photo_count[snap->active_slot] + 3) /
                                    4);
        }
    }
}

// Animates the 5 sub-menu option buttons. mode=0 for enter, mode=1 for exit.
void mnSnap_80253AE4(s32 mode)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    s32 i;

    for (i = 0; i < 5; i++) {
        HSD_JObj* jobj = snap->option_jobjs[i];
        f32 t = mnSnap_804DC2C8 * i;

        if (i == 4 && snap->active_slot == 0) {
            t = mnSnap_804DC2CC;
        }

        if (i == snap->menu_sel) {
            if (mode == 0) {
                t += mnSnap_804DC2D0;
            } else {
                t += mnSnap_804DC2D4;
            }
        }

        HSD_JObjReqAnimAll(jobj, t);
        HSD_JObjAnimAll(jobj);
    }

    if (mode == 0) {
        snap->timer = 3;
    } else {
        snap->timer = 0;
    }
}

// @TODO: Currently 98.70% match - needs minor register allocation fix
// Processes D-pad/trigger inputs to navigate a 2D grid of snapshots.
// Returns 0 if no movement, 1 if moved within page, 2 if page changed.
s32 mnSnap_80253BE0(u64 buttons, s32* cursor, s32 count)
{
    s32 cur = *cursor;
    s32 next = cur;

    if (buttons & 1) {
        if ((next & 1) == 1) {
            next -= 1;
        }
    } else if (buttons & 2) {
        if (!(next & 1) && (next + 1 < count)) {
            next += 1;
        }
    } else if (buttons & 4) {
        if (next >= 2) {
            next -= 2;
        }
    } else if (buttons & 8) {
        if (((next & ~1) + 2) < count) {
            next += 2;
            if (next == count) {
                next -= 1;
            }
        }
    } else if (buttons & 0x40) {
        if (next >= 4) {
            next -= 4;
        } else {
            next = ((count - 1) & ~3) + (cur % 4);
            if (next >= count) {
                next &= ~3;
            }
        }
    } else if (buttons & 0x80) {
        if (((next & ~3) + 4) < count) {
            next += 4;
            if (next >= count) {
                next &= ~3;
            }
        } else {
            next &= 3;
        }
    }

    *cursor = next;
    if (next == cur) {
        return 0;
    }

    lbAudioAx_80024030(2);
    if ((next / 4) == (cur / 4)) {
        return 1;
    }
    return 2;
}

// Renders the main content GObj only when in photo-browsing states (>= 4).
void fn_80253DB4(HSD_GObj* gobj, s32 rendermode)
{
    if (mnSnap_804A0A10.state >= 4) {
        HSD_GObj_JObjCallback(gobj, rendermode);
    }
}

// Renders the arrow/slot selector GObj only during slot selection (state 2).
void fn_80253DE8(HSD_GObj* gobj, s32 rendermode)
{
    if (mnSnap_804A0A10.state == 2) {
        HSD_GObj_JObjCallback(gobj, rendermode);
    }
}

// Renders the cursor GObj during menu (state 6) or full-screen view (10-11).
void fn_80253E1C(HSD_GObj* gobj, s32 rendermode)
{
    s32 state = mnSnap_804A0A10.state;
    if (state == 6 || (u32) (state - 10) <= 1) {
        HSD_GObj_JObjCallback(gobj, rendermode);
    }
}

// Renders the warning/dialog GObj only when a dialog is active.
void fn_80253E5C(HSD_GObj* gobj, s32 rendermode)
{
    if (mnSnap_804A0A10.dlg_active == 1) {
        HSD_GObj_JObjCallback(gobj, rendermode);
    }
}

// Queries memory card status for slot idx and stores the photo count/error.
void mnSnap_80253E90(s32 idx)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    s32 result = lbSnap_8001D40C(idx);

    if (result == 0) {
        snap->photo_count[idx] = lbSnap_8001D394(idx);
        snap->card_status[idx] = 1;
    } else if (result == 0xF) {
        snap->card_status[idx] = 0;
    } else if (result == 9) {
        snap->card_status[idx] = -1;
    } else if (result == 0xC) {
        snap->card_status[idx] = -2;
    } else {
        snap->card_status[idx] = -3;
    }
}

// @TODO: Currently 96.22% match - needs register allocation fix
// Animates the memory card slot selector highlights.
// Pointer arithmetic required to match: walk[0x94] reads card_status[i],
// and (snap + byte_off + 0x98) accesses slot_a_jobj / slot_b_jobj.
void mnSnap_80253F60(void)
{
    s32 byte_off = 4;
    mnSnap_State* snap = &mnSnap_804A0A10;
    /* walk strides through card_status (s16 at byte 0x128) */
    s16* walk = (s16*) snap;
    s32 i;
    for (i = 0; i < 2; i++, walk++, byte_off += 8) {
        if (walk[0x94] != 0) { /* snap->card_status[i] */
            f32 t;
            if (snap->active_slot == i) {
                t = mnSnap_804DC2D0;
            } else {
                t = mnSnap_804DC2C0;
            }
            HSD_JObjReqAnimAll(*(HSD_JObj**) ((u32) snap + byte_off + 0x98),
                               t);
        } else {
            HSD_JObjReqAnimAll(*(HSD_JObj**) ((u32) snap + byte_off + 0x98),
                               mnSnap_804DC2E0);
        }
        HSD_JObjAnimAll(*(HSD_JObj**) ((u32) snap + byte_off + 0x98));
    }
}

// Resets the sub-menu view and shows all 5 option buttons.
void mnSnap_80254014(void)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    HSD_JObj** ptr;
    s32 i;

    ptr = &snap->submenu_jobj;
    HSD_JObjReqAnimAll(*ptr, mnSnap_804DC2C0);
    HSD_JObjAnimAll(*ptr);

    for (i = 0; i < 5; i++) {
        HSD_JObjClearFlagsAll(snap->option_jobjs[i], 0x10);
    }

    HSD_JObjSetFlagsAll(snap->move_jobj, 0x10);
}

// @TODO: Currently 96.14% match - needs register allocation fix
// Configures the Yes/No dialog button positions based on language setting.
void mnSnap_8025409C(HSD_JObj* jobj_flag)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    HSD_JObj* left;
    HSD_JObj* right;
    s32* p5E;
    HSD_JObj** p38;
    HSD_JObj** p39;

    snap->dlg_type = (s32) jobj_flag;

    if (jobj_flag == NULL) {
        HSD_JObjSetFlags(snap->yes_jobj, 0x10);
        HSD_JObjSetFlags(snap->no_jobj, 0x10);
        return;
    }

    p38 = &snap->yes_jobj;
    HSD_JObjClearFlags(*p38, 0x10);
    p39 = &snap->no_jobj;
    HSD_JObjClearFlags(*p39, 0x10);

    p5E = &snap->btn_idx;
    *p5E = 0;

    if ((s32) jobj_flag == 1) {
        left = *p38;
        right = *p39;
    } else if (lbLang_IsSavedLanguageJP() != 0) {
        left = *p39;
        right = *p38;
    } else {
        left = *p38;
        right = *p39;
        *p5E = 1;
    }

    if (left == NULL) {
        __assert("jobj.h", 0x3A4, "jobj");
    }
    left->translate.x = mnSnap_804DC2E8;
    if (!(left->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(left);
    }

    if (right == NULL) {
        __assert("jobj.h", 0x3A4, "jobj");
    }
    right->translate.x = mnSnap_804DC2EC;
    if (!(right->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(right);
    }

    {
        f32 f;
        if (*p5E == 0) {
            f = mnSnap_804DC2D0;
        } else {
            f = mnSnap_804DC2C0;
        }
        HSD_JObjReqAnimAll(left, f);
    }
    {
        f32 f;
        if (*p5E == 1) {
            f = mnSnap_804DC2D0;
        } else {
            f = mnSnap_804DC2C0;
        }
        HSD_JObjReqAnimAll(right, f);
    }

    HSD_JObjAnimAll(left);
    HSD_JObjAnimAll(right);

    snap->left_btn = left;
    snap->right_btn = right;
}

// @TODO: Currently 94.60% match - needs register allocation fix
// Resets to slot selection state after a card error or empty card.
void mnSnap_80254298(void)
{
    s32* p50 = &mnSnap_804A0A10.active_slot;
    s32* p51;
    s32 i;
    mnSnap_State* snap = &mnSnap_804A0A10;
    void** slot;
    PAD_STACK(24);

    snap->timer = 0xB;
    *p50 = 0;

    slot = (void**) &snap->slot_a_jobj;
    HSD_JObjReqAnim((HSD_JObj*) *slot, mnSnap_804DC2C0);
    HSD_JObjAnim((HSD_JObj*) *slot);

    slot = (void**) &snap->slot_b_jobj;
    HSD_JObjReqAnim((HSD_JObj*) *slot, mnSnap_804DC2C0);
    HSD_JObjAnim((HSD_JObj*) *slot);

    p51 = &snap->pending_loads;
    *p51 = 0;
    snap->state = 2;

    HSD_JObjSetFlagsAll(snap->fullview_jobj, 0x10);
    snap->dlg_active = 0;
    slot = (void**) &snap->dlg_text;
    snap->dlg_timer = 0;

    if (snap->dlg_text != NULL) {
        HSD_SisLib_803A5CC4(snap->dlg_text);
        *slot = NULL;
    }

    slot = (void**) &snap->submenu_jobj;
    HSD_JObjReqAnimAll((HSD_JObj*) *slot, mnSnap_804DC2C0);
    HSD_JObjAnimAll((HSD_JObj*) *slot);

    for (i = 0; i < 5; i++) {
        HSD_JObjClearFlagsAll(snap->option_jobjs[i], 0x10);
    }
    HSD_JObjSetFlagsAll(snap->move_jobj, 0x10);

    mnSnap_80253964();
    mnSnap_80253E90(0);
    mnSnap_80253E90(1);

    {
        /* walk strides through card_status (s16 at byte 0x128) */
        s16* walk = (s16*) snap;
        s32 byte_off = 4;

        for (i = 0; i < 2; i++, byte_off += 8, walk++) {
            if (walk[0x94] != 0) { /* snap->card_status[i] */
                f32 t;
                if (*p50 == i) {
                    t = mnSnap_804DC2D0;
                } else {
                    t = mnSnap_804DC2C0;
                }
                HSD_JObjReqAnimAll(
                    *(HSD_JObj**) ((u32) snap + byte_off + 0x98), t);
            } else {
                HSD_JObjReqAnimAll(
                    *(HSD_JObj**) ((u32) snap + byte_off + 0x98),
                    mnSnap_804DC2E0);
            }
            HSD_JObjAnimAll(*(HSD_JObj**) ((u32) snap + byte_off + 0x98));
        }
    }

    *p51 = 0;
}

// Handles Yes/No dialog button inputs. Sets snap->dlg_result to the selection
// result.
s32 mnSnap_8025441C(u64 buttons)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    s32* result = &mnSnap_804A0A10.dlg_result;

    *result = 0;

    if (buttons & 0x20) {
        *result = 2;
        return;
    }

    if (buttons & 0x200) {
        if (mnSnap_804A0A10.dlg_type == 0) {
            *result = 2;
        } else if (((HSD_JObj**) &mnSnap_804A0A10
                        .left_btn)[mnSnap_804A0A10.btn_idx] ==
                   mnSnap_804A0A10.no_jobj)
        {
            *result = 2;
        } else {
            *result = 1;
        }
        return;
    }

    if (mnSnap_804A0A10.dlg_type != 0 && (buttons & 0x8) &&
        mnSnap_804A0A10.btn_idx == 0)
    {
        lbAudioAx_80024030(2);
        HSD_JObjReqAnimAll(mnSnap_804A0A10.left_btn, mnSnap_804DC2C0);
        mnSnap_804A0A10.btn_idx = 1;
        HSD_JObjAnimAll(mnSnap_804A0A10.left_btn);
        HSD_JObjAnimAll(mnSnap_804A0A10.right_btn);
        return;
    }

    if (mnSnap_804A0A10.dlg_type != 0 && (buttons & 0x4) &&
        mnSnap_804A0A10.btn_idx == 1)
    {
        lbAudioAx_80024030(2);
        HSD_JObjReqAnimAll(mnSnap_804A0A10.right_btn, mnSnap_804DC2C0);
        mnSnap_804A0A10.btn_idx = 0;
        HSD_JObjAnimAll(snap->left_btn);
        HSD_JObjAnimAll(mnSnap_804A0A10.right_btn);
    }
}

// @TODO: Currently 80.82% match - needs control flow and register fixes
// Main per-frame update for the Snap menu. Handles all state transitions
// including slot selection, photo browsing, copy/move/delete operations,
// and dialog confirmations via a large switch on snap->state.
void fn_802545C4(void)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    u32 buttons;
    s32 state;
    s32 i;
    s32 byte_off;
    s32 result;
    s32 next_state;
    s32 slot;
    s32 other_slot;
    f32 t;
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    Vec3* translate;

    buttons = mn_804A04F0.buttons = mn_80229624(4);

    HSD_JObjAnimAll(snap->select_jobj);
    HSD_JObjAnimAll(snap->move_jobj);

    state = snap->state;

    /* Early card-removed handling for states >= 4 */
    if (state >= 4) {
        if ((u32) (state - 15) > 1) {
            slot = snap->active_slot;
            if (lbSnap_8001D338(slot) != 0) {
                mnSnap_80253E90(slot);
            }
        }
        if (snap->card_status[snap->active_slot] != 1) {
            if (snap->state == 15 || snap->state == 16) {
                do {
                } while (lb_8001B6F8() == 0xB);
            }
            snap->timer = 0xB;
            snap->active_slot = 0;
            HSD_JObjReqAnim(snap->slot_a_jobj, 0.0F);
            HSD_JObjAnim(snap->slot_a_jobj);
            HSD_JObjReqAnim(snap->slot_b_jobj, 0.0F);
            HSD_JObjAnim(snap->slot_b_jobj);
            snap->pending_loads = 0;
            snap->state = 2;
            HSD_JObjSetFlagsAll(snap->fullview_jobj, 0x10);
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
            mnSnap_80254014();
            mnSnap_80253964();
            mnSnap_80253E90(0);
            mnSnap_80253E90(1);
            mnSnap_80253F60();
            snap->pending_loads = 0;
            goto end_loop;
        }
        other_slot = snap->active_slot ^ 1;
        if (snap->card_status[other_slot] == 1) {
            if (snap->state != 15 && snap->state != 16) {
                if (snap->card_status[other_slot] == 1) {
                    if (lbSnap_8001D350(other_slot) != 0) {
                        snap->card_status[other_slot] = 0;
                    }
                }
                if (snap->card_status[snap->active_slot ^ 1] != 1) {
                    mnSnap_80253964();
                }
            }
        }
    }

    /* Dialog button handler */
    if (snap->dlg_active != 0) {
        mnSnap_8025441C(buttons);
        if (snap->dlg_timer != 0) {
            snap->dlg_timer -= 1;
            HSD_JObjReqAnim(snap->dlg_frame, (f32) (9 - snap->dlg_timer));
            HSD_JObjAnim(snap->dlg_frame);
            HSD_JObjReqAnim(snap->dlg_pos, (f32) (9 - snap->dlg_timer));
            HSD_JObjAnim(snap->dlg_pos);
            jobj = snap->dlg_pos;
            if (jobj == NULL) {
                __assert("jobj.h", 0x3E1, "jobj");
            }
            if (snap->dlg_text != NULL) {
                (snap->dlg_text)->pos_x = jobj->translate.x - 6.0F;
            }
        }
    }

    state = snap->state;
    if ((u32) state > 0x17) {
        goto end_switch;
    }

    switch (state) {
    case 0:
        /* Intro countdown */
        if (snap->timer != 0) {
            snap->timer -= 1;
            if (snap->timer == 5) {
                mnSnap_80253E90(0);
            } else if (snap->timer == 2) {
                mnSnap_80253E90(1);
            }
        } else {
            snap->state = 2;
            snap->timer = 0xB;
            snap->active_slot = 0;
            HSD_JObjReqAnim(snap->slot_a_jobj, 0.0F);
            HSD_JObjAnim(snap->slot_a_jobj);
            HSD_JObjReqAnim(snap->slot_b_jobj, 0.0F);
            HSD_JObjAnim(snap->slot_b_jobj);
            snap->pending_loads = 0;

            if (snap->card_status[0] != 0) {
                snap->active_slot = 0;
            } else if (snap->card_status[1] != 0) {
                snap->active_slot = 1;
            } else {
                snap->active_slot = -1;
                snap->dlg_timer = 9;
                snap->dlg_active = 1;
                mnSnap_8025409C((HSD_JObj*) 0);
                HSD_JObjSetFlags(snap->dlg_btn_l, 0x10);
                HSD_JObjSetFlags(snap->dlg_btn_r, 0x10);
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                }
                snap->dlg_text = HSD_SisLib_803A5ACC(0, 1, 0.0F, -2.9F, 23.0F,
                                                     440.0F, 10.0F);
                (snap->dlg_text)->default_alignment = 1;
                (snap->dlg_text)->default_kerning = 1;
                (snap->dlg_text)->font_size.x = 0.03F;
                (snap->dlg_text)->font_size.y = 0.03F;
                HSD_SisLib_803A6368(snap->dlg_text, 0x140);
                HSD_JObjReqAnim(snap->dlg_frame, (f32) (9 - snap->dlg_timer));
                HSD_JObjAnim(snap->dlg_frame);
                HSD_JObjReqAnim(snap->dlg_pos, (f32) (9 - snap->dlg_timer));
                HSD_JObjAnim(snap->dlg_pos);
                jobj = snap->dlg_pos;
                if (jobj == NULL) {
                    __assert("jobj.h", 0x3E1, "jobj");
                }
                (snap->dlg_text)->pos_x = jobj->translate.x - 6.0F;
                lbAudioAx_80024030(3);
            }

            i = 0;
            byte_off = 4;
            do {
                if (snap->card_status[i] != 0) {
                    if (snap->active_slot == i) {
                        t = 1.0F;
                    } else {
                        t = 0.0F;
                    }
                    HSD_JObjReqAnimAll(
                        *(HSD_JObj**) ((u32) snap + byte_off + 0x98), t);
                } else {
                    HSD_JObjReqAnimAll(
                        *(HSD_JObj**) ((u32) snap + byte_off + 0x98), 2.0F);
                }
                HSD_JObjAnimAll(*(HSD_JObj**) ((u32) snap + byte_off + 0x98));
                i++;
                byte_off += 8;
            } while (i < 2);
        }
        break;

    case 2:
        /* Main browsing state */
        result = 0;
        if (snap->dlg_timer == 0 && snap->timer == 0) {
            if (lbSnap_8001D338(0) != 0) {
                mnSnap_80253E90(0);
            }
            if (lbSnap_8001D338(1) != 0) {
                mnSnap_80253E90(1);
            }
            result = 1;
        }

        if (snap->timer != 0) {
            snap->timer -= 1;
            HSD_JObjAnim(snap->slot_a_jobj);
            HSD_JObjAnim(snap->slot_b_jobj);
        }

        if (result != 0) {
            if (snap->card_status[0] != 0 || snap->card_status[1] != 0) {
                snap->dlg_active = 0;
                snap->dlg_timer = 0;
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                    snap->dlg_text = NULL;
                }
            }

            if (snap->active_slot >= 0) {
                if (snap->card_status[snap->active_slot] == 0) {
                    other_slot = snap->active_slot ^ 1;
                    if (snap->card_status[other_slot] != 0) {
                        snap->active_slot = other_slot;
                    } else {
                        snap->active_slot = -1;
                        snap->dlg_timer = 9;
                        snap->dlg_active = 1;
                        mnSnap_8025409C((HSD_JObj*) 0);
                        HSD_JObjSetFlags(snap->dlg_btn_l, 0x10);
                        HSD_JObjSetFlags(snap->dlg_btn_r, 0x10);
                        if (snap->dlg_text != NULL) {
                            HSD_SisLib_803A5CC4(snap->dlg_text);
                        }
                        snap->dlg_text = HSD_SisLib_803A5ACC(
                            0, 1, 0.0F, -2.9F, 23.0F, 440.0F, 10.0F);
                        (snap->dlg_text)->default_alignment = 1;
                        (snap->dlg_text)->default_kerning = 1;
                        (snap->dlg_text)->font_size.x = 0.03F;
                        (snap->dlg_text)->font_size.y = 0.03F;
                        HSD_SisLib_803A6368(snap->dlg_text, 0x140);
                        HSD_JObjReqAnim(snap->dlg_frame,
                                        (f32) (9 - snap->dlg_timer));
                        HSD_JObjAnim(snap->dlg_frame);
                        HSD_JObjReqAnim(snap->dlg_pos,
                                        (f32) (9 - snap->dlg_timer));
                        HSD_JObjAnim(snap->dlg_pos);
                        jobj = snap->dlg_pos;
                        if (jobj == NULL) {
                            __assert("jobj.h", 0x3E1, "jobj");
                        }
                        (snap->dlg_text)->pos_x = jobj->translate.x - 6.0F;
                        lbAudioAx_80024030(3);
                    }
                }
            } else {
                if (snap->card_status[0] != 0) {
                    snap->active_slot = 0;
                } else if (snap->card_status[1] != 0) {
                    snap->active_slot = 1;
                }
            }

            byte_off = 4;
            for (i = 0; i < 2; i++, byte_off += 8) {
                if (snap->card_status[i] != 0) {
                    if (snap->active_slot == i) {
                        t = 1.0F;
                    } else {
                        t = 0.0F;
                    }
                    HSD_JObjReqAnimAll(
                        *(HSD_JObj**) ((u32) snap + byte_off + 0x98), t);
                } else {
                    HSD_JObjReqAnimAll(
                        *(HSD_JObj**) ((u32) snap + byte_off + 0x98), 2.0F);
                }
                HSD_JObjAnimAll(*(HSD_JObj**) ((u32) snap + byte_off + 0x98));
            }

            /* Handle slot switching and selection */
            if (snap->active_slot == 0) {
                if (snap->card_status[1] != 0 && (buttons & 8)) {
                    lbAudioAx_80024030(2);
                    snap->active_slot = 1;
                    byte_off = 4;
                    for (i = 0; i < 2; i++, byte_off += 8) {
                        if (snap->card_status[i] != 0) {
                            if (snap->active_slot == i) {
                                t = 1.0F;
                            } else {
                                t = 0.0F;
                            }
                            HSD_JObjReqAnimAll(
                                *(HSD_JObj**) ((u32) snap + byte_off + 0x98),
                                t);
                        } else {
                            HSD_JObjReqAnimAll(
                                *(HSD_JObj**) ((u32) snap + byte_off + 0x98),
                                2.0F);
                        }
                        HSD_JObjAnimAll(
                            *(HSD_JObj**) ((u32) snap + byte_off + 0x98));
                    }
                } else if (snap->active_slot >= 0 && (buttons & 0x200)) {
                    goto handle_select;
                }
            } else if (snap->active_slot == 1 && snap->card_status[0] != 0 &&
                       (buttons & 4))
            {
                lbAudioAx_80024030(2);
                snap->active_slot = 0;
                byte_off = 4;
                for (i = 0; i < 2; i++, byte_off += 8) {
                    if (snap->card_status[i] != 0) {
                        if (snap->active_slot == i) {
                            t = 1.0F;
                        } else {
                            t = 0.0F;
                        }
                        HSD_JObjReqAnimAll(
                            *(HSD_JObj**) ((u32) snap + byte_off + 0x98), t);
                    } else {
                        HSD_JObjReqAnimAll(
                            *(HSD_JObj**) ((u32) snap + byte_off + 0x98),
                            2.0F);
                    }
                    HSD_JObjAnimAll(
                        *(HSD_JObj**) ((u32) snap + byte_off + 0x98));
                }
            } else if (snap->active_slot >= 0 && (buttons & 0x200)) {
            handle_select:
                slot = snap->active_slot;
                if (snap->card_status[slot] != 1) {
                    snap->state = 3;
                    lbAudioAx_80024030(3);
                    snap->dlg_timer = 9;
                    snap->dlg_active = 1;
                    mnSnap_8025409C((HSD_JObj*) 0);
                    HSD_JObjSetFlags(snap->dlg_btn_l, 0x10);
                    HSD_JObjSetFlags(snap->dlg_btn_r, 0x10);
                    if (snap->dlg_text != NULL) {
                        HSD_SisLib_803A5CC4(snap->dlg_text);
                    }
                    snap->dlg_text = HSD_SisLib_803A5ACC(0, 1, 0.0F, -2.9F,
                                                         23.0F, 440.0F, 10.0F);
                    (snap->dlg_text)->default_alignment = 1;
                    (snap->dlg_text)->default_kerning = 1;
                    (snap->dlg_text)->font_size.x = 0.03F;
                    (snap->dlg_text)->font_size.y = 0.03F;

                    if (snap->card_status[slot] == -1) {
                        if (slot == 0) {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x14B);
                        } else {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x14C);
                        }
                    } else if (snap->card_status[slot] == -2) {
                        if (slot == 0) {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x14D);
                        } else {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x14E);
                        }
                    } else {
                        if (slot == 0) {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x149);
                        } else {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x14A);
                        }
                    }

                    HSD_JObjReqAnim(snap->dlg_frame,
                                    (f32) (9 - snap->dlg_timer));
                    HSD_JObjAnim(snap->dlg_frame);
                    HSD_JObjReqAnim(snap->dlg_pos,
                                    (f32) (9 - snap->dlg_timer));
                    HSD_JObjAnim(snap->dlg_pos);
                    jobj = snap->dlg_pos;
                    if (jobj == NULL) {
                        __assert("jobj.h", 0x3E1, "jobj");
                    }
                    (snap->dlg_text)->pos_x = jobj->translate.x - 6.0F;
                } else if (snap->photo_count[slot] == 0) {
                    snap->state = 3;
                    lbAudioAx_80024030(3);
                    snap->dlg_timer = 9;
                    snap->dlg_active = 1;
                    mnSnap_8025409C((HSD_JObj*) 0);
                    HSD_JObjSetFlags(snap->dlg_btn_l, 0x10);
                    HSD_JObjSetFlags(snap->dlg_btn_r, 0x10);
                    if (snap->dlg_text != NULL) {
                        HSD_SisLib_803A5CC4(snap->dlg_text);
                    }
                    snap->dlg_text = HSD_SisLib_803A5ACC(0, 1, 0.0F, -2.9F,
                                                         23.0F, 440.0F, 10.0F);
                    (snap->dlg_text)->default_alignment = 1;
                    (snap->dlg_text)->default_kerning = 1;
                    (snap->dlg_text)->font_size.x = 0.03F;
                    (snap->dlg_text)->font_size.y = 0.03F;
                    if (snap->active_slot == 0) {
                        HSD_SisLib_803A6368(snap->dlg_text, 0x141);
                    } else {
                        HSD_SisLib_803A6368(snap->dlg_text, 0x142);
                    }
                    HSD_JObjReqAnim(snap->dlg_frame,
                                    (f32) (9 - snap->dlg_timer));
                    HSD_JObjAnim(snap->dlg_frame);
                    HSD_JObjReqAnim(snap->dlg_pos,
                                    (f32) (9 - snap->dlg_timer));
                    HSD_JObjAnim(snap->dlg_pos);
                    jobj = snap->dlg_pos;
                    if (jobj == NULL) {
                        __assert("jobj.h", 0x3E1, "jobj");
                    }
                    (snap->dlg_text)->pos_x = jobj->translate.x - 6.0F;
                    lbAudioAx_80024030(3);
                } else {
                    lbAudioAx_80024030(1);
                    snap->state = 4;
                    snap->cursor_idx = 0;
                    mnSnap_80253640(0);
                    mnSnap_80253964();
                    if (snap->cursor_idx / 4 == snap->cur_page) {
                        jobj = snap->select_jobj;
                        translate = &(snap->thumb_jobjs[snap->cursor_idx % 4])
                                         ->translate;
                        HSD_JObjSetTranslate(jobj, translate);
                        HSD_JObjClearFlagsAll(snap->select_jobj, 0x10);
                    } else {
                        HSD_JObjSetFlagsAll(snap->select_jobj, 0x10);
                    }
                }
            }
        }
        break;

    case 3:
        /* Error/loading message state */
        slot = snap->active_slot;
        if (lbSnap_8001D338(slot) != 0) {
            mnSnap_80253E90(slot);
        }
        if (snap->dlg_result != 0) {
            lbAudioAx_80024030(0);
        }
        if (snap->card_status[snap->active_slot] == 0 || snap->dlg_result != 0)
        {
            snap->state = 2;
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
        }
        break;

    case 4:
        /* Photo selection state */
        if (buttons & 0x200) {
            if (snap->thumb_loaded[snap->cursor_idx % 4] != 0) {
                snap->state = 5;
                snap->dlg_timer = 9;
                snap->dlg_active = 1;
                mnSnap_8025409C((HSD_JObj*) 1);
                HSD_JObjSetFlags(snap->dlg_btn_l, 0x10);
                HSD_JObjSetFlags(snap->dlg_btn_r, 0x10);
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                }
                snap->dlg_text = HSD_SisLib_803A5ACC(0, 1, 0.0F, -2.9F, 23.0F,
                                                     440.0F, 10.0F);
                (snap->dlg_text)->default_alignment = 1;
                (snap->dlg_text)->default_kerning = 1;
                (snap->dlg_text)->font_size.x = 0.03F;
                (snap->dlg_text)->font_size.y = 0.03F;
                HSD_SisLib_803A6368(snap->dlg_text, 0x153);
                HSD_JObjReqAnim(snap->dlg_frame, (f32) (9 - snap->dlg_timer));
                HSD_JObjAnim(snap->dlg_frame);
                HSD_JObjReqAnim(snap->dlg_pos, (f32) (9 - snap->dlg_timer));
                HSD_JObjAnim(snap->dlg_pos);
                jobj = snap->dlg_pos;
                if (jobj == NULL) {
                    __assert("jobj.h", 0x3E1, "jobj");
                }
                (snap->dlg_text)->pos_x = jobj->translate.x - 6.0F;
                lbAudioAx_80024030(3);
            } else {
                snap->state = 6;
                lbAudioAx_80024030(1);
                snap->menu_sel = 0;
                mnSnap_80253AE4(0);
            }
        } else if (buttons & 0xCF) {
            result = mnSnap_80253BE0(buttons, &snap->cursor_idx,
                                     snap->photo_count[snap->active_slot]);
            if (result == 2) {
                mnSnap_80253640(snap->cursor_idx / 4);
                mnSnap_80253964();
                if (snap->cursor_idx / 4 == snap->cur_page) {
                    jobj = snap->select_jobj;
                    translate =
                        &(snap->thumb_jobjs[snap->cursor_idx % 4])->translate;
                    HSD_JObjSetTranslate(jobj, translate);
                    HSD_JObjClearFlagsAll(snap->select_jobj, 0x10);
                } else {
                    HSD_JObjSetFlagsAll(snap->select_jobj, 0x10);
                }
            } else if (result == 1) {
                if (snap->cursor_idx / 4 == snap->cur_page) {
                    jobj = snap->select_jobj;
                    translate =
                        &(snap->thumb_jobjs[snap->cursor_idx % 4])->translate;
                    HSD_JObjSetTranslate(jobj, translate);
                    HSD_JObjClearFlagsAll(snap->select_jobj, 0x10);
                } else {
                    HSD_JObjSetFlagsAll(snap->select_jobj, 0x10);
                }
            }
        }
        break;

    case 5:
        /* Save confirmation */
        if (snap->dlg_result == 1) {
            s32 poll_result;
            lbAudioAx_80024030(1);
            result = lbSnap_8001D5FC(snap->active_slot, snap->cursor_idx);
            if (result != 0xB) {
                mnSnap_80254298();
                result = 1;
            } else {
                do {
                    poll_result = lb_8001B6F8();
                } while (poll_result == 0xB);
                if (poll_result != 0) {
                    mnSnap_80254298();
                    result = 1;
                } else {
                    mnSnap_80253E90(snap->active_slot);
                    result = 0;
                }
            }
            if (result == 0) {
                snap->dlg_active = 0;
                snap->dlg_timer = 0;
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                    snap->dlg_text = NULL;
                }
                if (snap->cursor_idx >= snap->photo_count[snap->active_slot]) {
                    snap->cursor_idx -= 1;
                    if (snap->photo_count[snap->active_slot] == 0) {
                        snap->timer = 0xB;
                        snap->active_slot = 0;
                        HSD_JObjReqAnim(snap->slot_a_jobj, 0.0F);
                        HSD_JObjAnim(snap->slot_a_jobj);
                        HSD_JObjReqAnim(snap->slot_b_jobj, 0.0F);
                        HSD_JObjAnim(snap->slot_b_jobj);
                        snap->pending_loads = 0;
                        snap->state = 2;
                        HSD_JObjSetFlagsAll(snap->fullview_jobj, 0x10);
                        snap->dlg_active = 0;
                        snap->dlg_timer = 0;
                        if (snap->dlg_text != NULL) {
                            HSD_SisLib_803A5CC4(snap->dlg_text);
                            snap->dlg_text = NULL;
                        }
                        mnSnap_80254014();
                        mnSnap_80253964();
                        mnSnap_80253E90(0);
                        mnSnap_80253E90(1);
                        mnSnap_80253F60();
                        snap->pending_loads = 0;
                    } else {
                        mnSnap_80253640(snap->cursor_idx / 4);
                        if (snap->cursor_idx / 4 == snap->cur_page) {
                            jobj = snap->select_jobj;
                            translate =
                                &(snap->thumb_jobjs[snap->cursor_idx % 4])
                                     ->translate;
                            HSD_JObjSetTranslate(jobj, translate);
                            HSD_JObjClearFlagsAll(snap->select_jobj, 0x10);
                        } else {
                            HSD_JObjSetFlagsAll(snap->select_jobj, 0x10);
                        }
                        mnSnap_80253964();
                        snap->state = 4;
                    }
                }
            }
        } else if (snap->dlg_result == 2) {
            lbAudioAx_80024030(0);
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
            snap->state = 4;
        }
        break;

    case 6:
        /* Menu state */
        if (snap->timer != 0) {
            HSD_JObjAnimAll(snap->option_jobjs[snap->menu_sel]);
            snap->timer -= 1;
        }
        if (buttons & 1) {
            lbAudioAx_80024030(2);
            snap->menu_sel -= 1;
            if (snap->menu_sel < 0) {
                snap->menu_sel = 4;
            }
            mnSnap_80253AE4(0);
        } else if (buttons & 2) {
            lbAudioAx_80024030(2);
            snap->menu_sel += 1;
            if (snap->menu_sel > 4) {
                snap->menu_sel = 0;
            }
            mnSnap_80253AE4(0);
        } else if (buttons & 0x20) {
            lbAudioAx_80024030(0);
            snap->state = 4;
        } else if (buttons & 0x200) {
            while (snap->timer != 0) {
                HSD_JObjAnimAll(snap->option_jobjs[snap->menu_sel]);
                snap->timer -= 1;
            }
            switch (snap->menu_sel) {
            case 0:
                /* View photo */
                lbAudioAx_80024030(1);
                snap->state = 0xA;
                HSD_JObjClearFlagsAll(snap->fullview_jobj, 0x10);
                jobj = snap->fullview_jobj;
                HSD_ASSERT(181, jobj);
                HSD_ASSERT(182, jobj->u.dobj);
                HSD_ASSERT(183, jobj->u.dobj->mobj);
                HSD_ASSERT(184, jobj->u.dobj->mobj->tobj);
                HSD_ASSERT(185, jobj->u.dobj->mobj->tobj->imagedesc );
                jobj->u.dobj->mobj->tobj->imagedesc->image_ptr =
                    (void*) mnSnap_thumb_imgs[snap->cursor_idx % 4];
                jobj->u.dobj->mobj->tobj->imagedesc->width = 640;
                jobj->u.dobj->mobj->tobj->imagedesc->height = 480;
                break;

            case 1:
                /* Move photo */
                lbAudioAx_80024030(1);
                snap->state = 0xB;
                HSD_JObjAnimAll(snap->submenu_jobj);
                snap->timer = 4;
                for (i = 0; i < 5; i++) {
                    HSD_JObjSetFlagsAll(snap->option_jobjs[i], 0x10);
                }
                HSD_JObjClearFlagsAll(snap->move_jobj, 0x10);
                snap->move_idx = snap->cursor_idx;
                if (snap->move_idx / 4 == snap->cur_page) {
                    jobj = snap->move_jobj;
                    translate =
                        &(snap->thumb_jobjs[snap->move_idx % 4])->translate;
                    HSD_JObjSetTranslate(jobj, translate);
                    HSD_JObjClearFlagsAll(snap->move_jobj, 0x10);
                } else {
                    HSD_JObjSetFlagsAll(snap->move_jobj, 0x10);
                }
                break;

            case 2:
                /* Copy photo */
                lbAudioAx_80024030(1);
                snap->dlg_timer = 9;
                snap->dlg_active = 1;
                mnSnap_8025409C((HSD_JObj*) 1);
                HSD_JObjSetFlags(snap->dlg_btn_l, 0x10);
                HSD_JObjSetFlags(snap->dlg_btn_r, 0x10);
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                }
                snap->dlg_text = HSD_SisLib_803A5ACC(0, 1, 0.0F, -2.9F, 23.0F,
                                                     440.0F, 10.0F);
                (snap->dlg_text)->default_alignment = 1;
                (snap->dlg_text)->default_kerning = 1;
                (snap->dlg_text)->font_size.x = 0.03F;
                (snap->dlg_text)->font_size.y = 0.03F;
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x144);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x143);
                }
                HSD_JObjReqAnim(snap->dlg_frame, (f32) (9 - snap->dlg_timer));
                HSD_JObjAnim(snap->dlg_frame);
                HSD_JObjReqAnim(snap->dlg_pos, (f32) (9 - snap->dlg_timer));
                HSD_JObjAnim(snap->dlg_pos);
                jobj = snap->dlg_pos;
                if (jobj == NULL) {
                    __assert("jobj.h", 0x3E1, "jobj");
                }
                (snap->dlg_text)->pos_x = jobj->translate.x - 6.0F;
                snap->state = 0xC;
                break;

            case 3:
                /* Send to printer */
                snap->dlg_timer = 9;
                snap->dlg_active = 1;
                mnSnap_8025409C((HSD_JObj*) 2);
                HSD_JObjSetFlags(snap->dlg_btn_l, 0x10);
                HSD_JObjSetFlags(snap->dlg_btn_r, 0x10);
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                }
                snap->dlg_text = HSD_SisLib_803A5ACC(0, 1, 0.0F, -2.9F, 23.0F,
                                                     440.0F, 10.0F);
                (snap->dlg_text)->default_alignment = 1;
                (snap->dlg_text)->default_kerning = 1;
                (snap->dlg_text)->font_size.x = 0.03F;
                (snap->dlg_text)->font_size.y = 0.03F;
                HSD_SisLib_803A6368(snap->dlg_text, 0x150);
                HSD_JObjReqAnim(snap->dlg_frame, (f32) (9 - snap->dlg_timer));
                HSD_JObjAnim(snap->dlg_frame);
                HSD_JObjReqAnim(snap->dlg_pos, (f32) (9 - snap->dlg_timer));
                HSD_JObjAnim(snap->dlg_pos);
                jobj = snap->dlg_pos;
                if (jobj == NULL) {
                    __assert("jobj.h", 0x3E1, "jobj");
                }
                (snap->dlg_text)->pos_x = jobj->translate.x - 6.0F;
                lbAudioAx_80024030(7);
                snap->state = 0x14;
                break;

            case 4:
                /* Erase photo */
                lbAudioAx_80024030(1);
                snap->dlg_timer = 9;
                snap->dlg_active = 1;
                mnSnap_8025409C((HSD_JObj*) 1);
                HSD_JObjSetFlags(snap->dlg_btn_l, 0x10);
                HSD_JObjSetFlags(snap->dlg_btn_r, 0x10);
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                }
                snap->dlg_text = HSD_SisLib_803A5ACC(0, 1, 0.0F, -2.9F, 23.0F,
                                                     440.0F, 10.0F);
                (snap->dlg_text)->default_alignment = 1;
                (snap->dlg_text)->default_kerning = 1;
                (snap->dlg_text)->font_size.x = 0.03F;
                (snap->dlg_text)->font_size.y = 0.03F;
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x152);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x151);
                }
                HSD_JObjReqAnim(snap->dlg_frame, (f32) (9 - snap->dlg_timer));
                HSD_JObjAnim(snap->dlg_frame);
                HSD_JObjReqAnim(snap->dlg_pos, (f32) (9 - snap->dlg_timer));
                HSD_JObjAnim(snap->dlg_pos);
                jobj = snap->dlg_pos;
                if (jobj == NULL) {
                    __assert("jobj.h", 0x3E1, "jobj");
                }
                (snap->dlg_text)->pos_x = jobj->translate.x - 6.0F;
                snap->state = 0x15;
                break;
            }
        }
        break;

    case 10:
        /* Full-screen view */
        if (buttons & 0x200) {
            snap->state = 4;
            lbAudioAx_80024030(0);
            HSD_JObjSetFlagsAll(snap->fullview_jobj, 0x10);
        } else if (buttons & 0x20) {
            snap->state = 6;
            lbAudioAx_80024030(0);
            HSD_JObjSetFlagsAll(snap->fullview_jobj, 0x10);
        }
        break;

    case 11:
        /* Move photo mode */
        next_state = 0;
        if (snap->timer != 0) {
            HSD_JObjAnimAll(snap->submenu_jobj);
            snap->timer -= 1;
        }
        if (buttons & 0x200) {
            if (snap->move_idx != snap->cursor_idx) {
                lbAudioAx_80024030(1);
                result = lbSnap_8001D7B0(snap->active_slot, snap->cursor_idx,
                                         snap->move_idx);
                if (result != 8) {
                    do {
                    } while (lb_8001B6F8() == 0xB);
                    mnSnap_80253E90(snap->active_slot);
                }
                snap->cur_page = -1;
                next_state = 4;
            } else {
                lbAudioAx_80024030(3);
            }
        } else if (buttons & 0x20) {
            next_state = 6;
            lbAudioAx_80024030(0);
        } else if (buttons & 0xCF) {
            result = mnSnap_80253BE0(buttons, &snap->move_idx,
                                     snap->photo_count[snap->active_slot]);
            if (result == 2) {
                mnSnap_80253640(snap->move_idx / 4);
                mnSnap_80253964();
                if (snap->cursor_idx / 4 == snap->cur_page) {
                    jobj = snap->select_jobj;
                    translate =
                        &(snap->thumb_jobjs[snap->cursor_idx % 4])->translate;
                    HSD_JObjSetTranslate(jobj, translate);
                    HSD_JObjClearFlagsAll(snap->select_jobj, 0x10);
                } else {
                    HSD_JObjSetFlagsAll(snap->select_jobj, 0x10);
                }
                if (snap->move_idx / 4 == snap->cur_page) {
                    jobj2 = snap->move_jobj;
                    translate =
                        &(snap->thumb_jobjs[snap->move_idx % 4])->translate;
                    HSD_JObjSetTranslate(jobj2, translate);
                    HSD_JObjClearFlagsAll(snap->move_jobj, 0x10);
                } else {
                    HSD_JObjSetFlagsAll(snap->move_jobj, 0x10);
                }
            } else if (result == 1) {
                if (snap->move_idx / 4 == snap->cur_page) {
                    jobj2 = snap->move_jobj;
                    translate =
                        &(snap->thumb_jobjs[snap->move_idx % 4])->translate;
                    HSD_JObjSetTranslate(jobj2, translate);
                    HSD_JObjClearFlagsAll(snap->move_jobj, 0x10);
                } else {
                    HSD_JObjSetFlagsAll(snap->move_jobj, 0x10);
                }
            }
        }
        if (next_state != 0) {
            snap->state = next_state;
            HSD_JObjReqAnimAll(snap->submenu_jobj, 0.0F);
            HSD_JObjAnimAll(snap->submenu_jobj);
            for (i = 0; i < 5; i++) {
                HSD_JObjClearFlagsAll(snap->option_jobjs[i], 0x10);
            }
            HSD_JObjSetFlagsAll(snap->move_jobj, 0x10);
            mnSnap_80253AE4(1);
            if (snap->cursor_idx / 4 != snap->cur_page) {
                mnSnap_80253640(snap->cursor_idx / 4);
                mnSnap_80253964();
                if (snap->cursor_idx / 4 == snap->cur_page) {
                    jobj = snap->select_jobj;
                    translate =
                        &(snap->thumb_jobjs[snap->cursor_idx % 4])->translate;
                    HSD_JObjSetTranslate(jobj, translate);
                    HSD_JObjClearFlagsAll(snap->select_jobj, 0x10);
                } else {
                    HSD_JObjSetFlagsAll(snap->select_jobj, 0x10);
                }
            }
        }
        break;

    case 12:
        /* Copy confirmation */
        if (snap->dlg_result == 1) {
            other_slot = snap->active_slot ^ 1;
            if (lbSnap_8001D338(other_slot) != 0) {
                mnSnap_80253E90(other_slot);
            }
            slot = snap->active_slot;
            other_slot = snap->active_slot ^ 1;
            result = snap->card_status[other_slot];
            switch (result) {
            case 0:
                result = 2;
                break;
            case -1:
                result = 3;
                break;
            case -2:
                result = 4;
                break;
            case -3:
                result = 5;
                break;
            default:
                if (lbSnap_8001D3CC(other_slot) == 0) {
                    result = 1;
                } else {
                    if (lbSnap_8001D3E8(slot, snap->cursor_idx) >
                        lbSnap_8001D3B0(other_slot))
                    {
                        result = 1;
                    } else {
                        result = 0;
                    }
                }
                break;
            }
            switch (result) {
            case 0:
                lbAudioAx_80024030(1);
                snap->state = 0xF;
                HSD_JObjClearFlags(snap->dlg_btn_r, 0x10);
                jobj = snap->progress_jobj;
                if (jobj == NULL) {
                    __assert("jobj.h", 0x3A4, "jobj");
                }
                jobj->translate.x = mnSnap_804DC2E4;
                if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
                    HSD_JObjSetMtxDirty(jobj);
                }
                HSD_JObjSetFlags(snap->yes_jobj, 0x10);
                HSD_JObjSetFlags(snap->no_jobj, 0x10);
                snap->card_result =
                    lbSnap_8001E058(snap->active_slot, snap->cursor_idx);
                if (snap->card_result == 8 || snap->card_result != 0xB) {
                    snap->timer = 0xB;
                    snap->active_slot = 0;
                    HSD_JObjReqAnim(snap->slot_a_jobj, 0.0F);
                    HSD_JObjAnim(snap->slot_a_jobj);
                    HSD_JObjReqAnim(snap->slot_b_jobj, 0.0F);
                    HSD_JObjAnim(snap->slot_b_jobj);
                    snap->pending_loads = 0;
                    snap->state = 2;
                    HSD_JObjSetFlagsAll(snap->fullview_jobj, 0x10);
                    snap->dlg_active = 0;
                    snap->dlg_timer = 0;
                    if (snap->dlg_text != NULL) {
                        HSD_SisLib_803A5CC4(snap->dlg_text);
                        snap->dlg_text = NULL;
                    }
                    mnSnap_80254014();
                    mnSnap_80253964();
                    mnSnap_80253E90(0);
                    mnSnap_80253E90(1);
                    mnSnap_80253F60();
                    snap->pending_loads = 0;
                }
                break;
            case 2:
                lbAudioAx_80024030(3);
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x148);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x147);
                }
                mnSnap_8025409C((HSD_JObj*) 0);
                snap->state = 0xD;
                break;
            case 1:
                lbAudioAx_80024030(3);
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x146);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x145);
                }
                mnSnap_8025409C((HSD_JObj*) 0);
                snap->state = 0xE;
                break;
            case 3:
                lbAudioAx_80024030(3);
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x14C);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x14B);
                }
                mnSnap_8025409C((HSD_JObj*) 0);
                snap->state = 0xE;
                break;
            case 4:
                lbAudioAx_80024030(3);
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x14E);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x14D);
                }
                mnSnap_8025409C((HSD_JObj*) 0);
                snap->state = 0xE;
                break;
            case 5:
                lbAudioAx_80024030(3);
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x14A);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x149);
                }
                mnSnap_8025409C((HSD_JObj*) 0);
                snap->state = 0xE;
                break;
            }
        } else if (snap->dlg_result == 2) {
            lbAudioAx_80024030(0);
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
            snap->state = 6;
        }
        break;

    case 13:
        /* Post-copy error/continue */
        if (snap->dlg_result == 2) {
            lbAudioAx_80024030(0);
            snap->state = 6;
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
        } else {
            other_slot = snap->active_slot ^ 1;
            if (lbSnap_8001D338(other_slot) != 0) {
                mnSnap_80253E90(other_slot);
            }
            if (snap->card_status[snap->active_slot ^ 1] != 0) {
                snap->state = 0xC;
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x144);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x143);
                }
                mnSnap_8025409C((HSD_JObj*) 1);
            }
        }
        break;

    case 14:
        /* Error state after copy */
        if (snap->dlg_result != 0) {
            lbAudioAx_80024030(0);
            snap->state = 6;
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
        } else {
            other_slot = snap->active_slot ^ 1;
            if (lbSnap_8001D338(other_slot) != 0) {
                mnSnap_80253E90(other_slot);
            }
            if (snap->card_status[snap->active_slot ^ 1] == 0) {
                snap->state = 0xC;
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x144);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x143);
                }
                mnSnap_8025409C((HSD_JObj*) 1);
            }
        }
        break;

    case 15:
        /* Card write wait */
        result = lb_8001B6F8();
        if (result != 0xB) {
            if (lb_8001B6F8() != 0) {
                snap->timer = 0xB;
                snap->active_slot = 0;
                HSD_JObjReqAnim(snap->slot_a_jobj, 0.0F);
                HSD_JObjAnim(snap->slot_a_jobj);
                HSD_JObjReqAnim(snap->slot_b_jobj, 0.0F);
                HSD_JObjAnim(snap->slot_b_jobj);
                snap->pending_loads = 0;
                snap->state = 2;
                HSD_JObjSetFlagsAll(snap->fullview_jobj, 0x10);
                snap->dlg_active = 0;
                snap->dlg_timer = 0;
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                    snap->dlg_text = NULL;
                }
                mnSnap_80254014();
                mnSnap_80253964();
                mnSnap_80253E90(0);
                mnSnap_80253E90(1);
                mnSnap_80253F60();
                snap->pending_loads = 0;
            } else {
                result = lbSnap_8001DF6C(snap->active_slot ^ 1);
                if (result != 0xB) {
                    snap->timer = 0xB;
                    snap->active_slot = 0;
                    HSD_JObjReqAnim(snap->slot_a_jobj, 0.0F);
                    HSD_JObjAnim(snap->slot_a_jobj);
                    HSD_JObjReqAnim(snap->slot_b_jobj, 0.0F);
                    HSD_JObjAnim(snap->slot_b_jobj);
                    snap->pending_loads = 0;
                    snap->state = 2;
                    HSD_JObjSetFlagsAll(snap->fullview_jobj, 0x10);
                    snap->dlg_active = 0;
                    snap->dlg_timer = 0;
                    if (snap->dlg_text != NULL) {
                        HSD_SisLib_803A5CC4(snap->dlg_text);
                        snap->dlg_text = NULL;
                    }
                    mnSnap_80254014();
                    mnSnap_80253964();
                    mnSnap_80253E90(0);
                    mnSnap_80253E90(1);
                    mnSnap_80253F60();
                    snap->pending_loads = 0;
                } else {
                    snap->state = 0x10;
                    jobj = snap->progress_jobj;
                    if (jobj == NULL) {
                        __assert("jobj.h", 0x3A4, "jobj");
                    }
                    jobj->translate.x = -3.0F;
                    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
                        HSD_JObjSetMtxDirty(jobj);
                    }
                    snap->timer = 0x50;
                }
            }
        }
        break;

    case 16:
        /* Timer animation */
        snap->timer -= 1;
        if (snap->timer == 0) {
            snap->timer = 0x64;
            jobj = snap->progress_jobj;
            if (jobj == NULL) {
                __assert("jobj.h", 0x3E1, "jobj");
            }
            t = jobj->translate.x;
            if (t < 3.0F) {
                if (jobj == NULL) {
                    __assert("jobj.h", 0x3A4, "jobj");
                }
                jobj->translate.x = t + 3.0F;
                if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
                    HSD_JObjSetMtxDirty(jobj);
                }
            }
        }
        result = lb_8001B6F8();
        if (result != 0xB) {
            if (lb_8001B6F8() != 0) {
                snap->timer = 0xB;
                snap->active_slot = 0;
                HSD_JObjReqAnim(snap->slot_a_jobj, 0.0F);
                HSD_JObjAnim(snap->slot_a_jobj);
                HSD_JObjReqAnim(snap->slot_b_jobj, 0.0F);
                HSD_JObjAnim(snap->slot_b_jobj);
                snap->pending_loads = 0;
                snap->state = 2;
                HSD_JObjSetFlagsAll(snap->fullview_jobj, 0x10);
                snap->dlg_active = 0;
                snap->dlg_timer = 0;
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                    snap->dlg_text = NULL;
                }
                mnSnap_80254014();
                mnSnap_80253964();
                mnSnap_80253E90(0);
                mnSnap_80253E90(1);
                mnSnap_80253F60();
                snap->pending_loads = 0;
            } else {
                mnSnap_80253E90(snap->active_slot ^ 1);
                mnSnap_80253964();
                HSD_SisLib_803A6368(snap->dlg_text, 0x14F);
                snap->state = 0x11;
                snap->timer = 0x1E;
                jobj = snap->progress_jobj;
                if (jobj == NULL) {
                    __assert("jobj.h", 0x3A4, "jobj");
                }
                jobj->translate.x = 5.0F;
                if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
                    HSD_JObjSetMtxDirty(jobj);
                }
            }
        }
        break;

    case 17:
        /* Timer countdown */
        if (snap->timer != 0) {
            snap->timer -= 1;
        } else {
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
            snap->state = 4;
        }
        break;

    case 20:
        /* Delete confirmation */
        if (snap->dlg_result == 1) {
            s32 do_delete = 0;
            s32 poll_result;
            lbAudioAx_80024030(1);
            if (lbSnap_8001D5FC(snap->active_slot, snap->cursor_idx) != 0xB) {
                mnSnap_80254298();
                do_delete = 1;
            } else {
                do {
                    poll_result = lb_8001B6F8();
                } while (poll_result == 0xB);
                if (poll_result != 0) {
                    mnSnap_80254298();
                    do_delete = 1;
                } else {
                    mnSnap_80253E90(snap->active_slot);
                    do_delete = 0;
                }
            }
            if (do_delete == 0) {
                s32 idx;
                snap->dlg_active = 0;
                snap->dlg_timer = 0;
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                    snap->dlg_text = NULL;
                }
                idx = snap->cursor_idx;
                if (idx >= snap->photo_count[snap->active_slot]) {
                    snap->cursor_idx = idx - 1;
                    if (snap->photo_count[snap->active_slot] == 0) {
                        snap->timer = 0xB;
                        snap->active_slot = 0;
                        HSD_JObjReqAnim(snap->slot_a_jobj, 0.0F);
                        HSD_JObjAnim(snap->slot_a_jobj);
                        HSD_JObjReqAnim(snap->slot_b_jobj, 0.0F);
                        HSD_JObjAnim(snap->slot_b_jobj);
                        snap->pending_loads = 0;
                        snap->state = 2;
                        HSD_JObjSetFlagsAll(snap->fullview_jobj, 0x10);
                        snap->dlg_active = 0;
                        snap->dlg_timer = 0;
                        if (snap->dlg_text != NULL) {
                            HSD_SisLib_803A5CC4(snap->dlg_text);
                            snap->dlg_text = NULL;
                        }
                        mnSnap_80254014();
                        mnSnap_80253964();
                        mnSnap_80253E90(0);
                        mnSnap_80253E90(1);
                        mnSnap_80253F60();
                        snap->pending_loads = 0;
                    } else {
                        mnSnap_80253640(snap->cursor_idx / 4);
                        if (snap->cursor_idx / 4 == snap->cur_page) {
                            jobj = snap->select_jobj;
                            translate =
                                &(snap->thumb_jobjs[snap->cursor_idx % 4])
                                     ->translate;
                            HSD_JObjSetTranslate(jobj, translate);
                            HSD_JObjClearFlagsAll(snap->select_jobj, 0x10);
                        } else {
                            HSD_JObjSetFlagsAll(snap->select_jobj, 0x10);
                        }
                        mnSnap_80253964();
                        snap->state = 4;
                    }
                } else {
                    mnSnap_80253640(snap->cursor_idx / 4);
                    if (snap->cursor_idx / 4 == snap->cur_page) {
                        jobj = snap->select_jobj;
                        translate = &(snap->thumb_jobjs[snap->cursor_idx % 4])
                                         ->translate;
                        HSD_JObjSetTranslate(jobj, translate);
                        HSD_JObjClearFlagsAll(snap->select_jobj, 0x10);
                    } else {
                        HSD_JObjSetFlagsAll(snap->select_jobj, 0x10);
                    }
                    mnSnap_80253964();
                    snap->state = 4;
                }
            }
        } else if (snap->dlg_result == 2) {
            lbAudioAx_80024030(0);
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
            snap->state = 6;
        }
        break;

    case 21:
        /* Copy to other card confirmation */
        if (snap->dlg_result == 1) {
            s32 other_slot = snap->active_slot ^ 1;
            s32 card_status;
            if (lbSnap_8001D338(other_slot) != 0) {
                mnSnap_80253E90(other_slot);
            }
            card_status = snap->card_status[other_slot];
            if (card_status == 0) {
                lbAudioAx_80024030(3);
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x148);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x147);
                }
                mnSnap_8025409C((HSD_JObj*) 0);
                snap->state = 0x16;
            } else if (card_status < 0) {
                if (card_status == -1) {
                    if (snap->active_slot == 0) {
                        HSD_SisLib_803A6368(snap->dlg_text, 0x14C);
                    } else {
                        HSD_SisLib_803A6368(snap->dlg_text, 0x14B);
                    }
                } else if (card_status == -2) {
                    if (snap->active_slot == 0) {
                        HSD_SisLib_803A6368(snap->dlg_text, 0x14E);
                    } else {
                        HSD_SisLib_803A6368(snap->dlg_text, 0x14D);
                    }
                } else {
                    if (snap->active_slot == 0) {
                        HSD_SisLib_803A6368(snap->dlg_text, 0x14A);
                    } else {
                        HSD_SisLib_803A6368(snap->dlg_text, 0x149);
                    }
                }
                mnSnap_8025409C((HSD_JObj*) 0);
                lbAudioAx_80024030(3);
                snap->state = 0x17;
            } else if (snap->photo_count[other_slot] == 0) {
                lbAudioAx_80024030(3);
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x142);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x141);
                }
                mnSnap_8025409C((HSD_JObj*) 0);
                snap->state = 0x17;
                lbAudioAx_80024030(3);
            } else {
                s32 new_slot;
                lbAudioAx_80024030(1);
                snap->dlg_active = 0;
                snap->dlg_timer = 0;
                if (snap->dlg_text != NULL) {
                    HSD_SisLib_803A5CC4(snap->dlg_text);
                    snap->dlg_text = NULL;
                }
                snap->state = 4;
                new_slot = snap->active_slot ^ 1;
                snap->active_slot = new_slot;
                snap->cursor_idx = 0;
                mnSnap_80253640(0);
                mnSnap_80253964();
                if (snap->cursor_idx / 4 == snap->cur_page) {
                    jobj = snap->select_jobj;
                    translate =
                        &(snap->thumb_jobjs[snap->cursor_idx % 4])->translate;
                    HSD_JObjSetTranslate(jobj, translate);
                    HSD_JObjClearFlagsAll(snap->select_jobj, 0x10);
                } else {
                    HSD_JObjSetFlagsAll(snap->select_jobj, 0x10);
                }
            }
        } else if (snap->dlg_result == 2) {
            lbAudioAx_80024030(0);
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
            snap->state = 6;
        }
        break;

    case 22:
        /* Copy card check - no space */
        if (snap->dlg_result == 2) {
            lbAudioAx_80024030(0);
            snap->state = 6;
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
        } else {
            s32 other_slot = snap->active_slot ^ 1;
            s32 card_status;
            if (lbSnap_8001D338(other_slot) != 0) {
                mnSnap_80253E90(other_slot);
            }
            card_status = snap->card_status[other_slot];
            if (card_status != 0) {
                if (card_status < 0) {
                    if (card_status == -1) {
                        if (snap->active_slot == 0) {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x14C);
                        } else {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x14B);
                        }
                    } else if (card_status == -2) {
                        if (snap->active_slot == 0) {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x14E);
                        } else {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x14D);
                        }
                    } else {
                        if (snap->active_slot == 0) {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x14A);
                        } else {
                            HSD_SisLib_803A6368(snap->dlg_text, 0x149);
                        }
                    }
                    mnSnap_8025409C((HSD_JObj*) 0);
                    lbAudioAx_80024030(3);
                    snap->state = 0x17;
                } else if (snap->photo_count[other_slot] == 0) {
                    if (snap->active_slot == 0) {
                        HSD_SisLib_803A6368(snap->dlg_text, 0x142);
                    } else {
                        HSD_SisLib_803A6368(snap->dlg_text, 0x141);
                    }
                    mnSnap_8025409C((HSD_JObj*) 0);
                    snap->state = 0x17;
                    lbAudioAx_80024030(3);
                } else {
                    s32 new_slot;
                    snap->dlg_active = 0;
                    snap->dlg_timer = 0;
                    if (snap->dlg_text != NULL) {
                        HSD_SisLib_803A5CC4(snap->dlg_text);
                        snap->dlg_text = NULL;
                    }
                    snap->state = 4;
                    new_slot = snap->active_slot ^ 1;
                    snap->active_slot = new_slot;
                    snap->cursor_idx = 0;
                    mnSnap_80253640(0);
                    mnSnap_80253964();
                    if (snap->cursor_idx / 4 == snap->cur_page) {
                        jobj = snap->select_jobj;
                        translate = &(snap->thumb_jobjs[snap->cursor_idx % 4])
                                         ->translate;
                        HSD_JObjSetTranslate(jobj, translate);
                        HSD_JObjClearFlagsAll(snap->select_jobj, 0x10);
                    } else {
                        HSD_JObjSetFlagsAll(snap->select_jobj, 0x10);
                    }
                }
            }
        }
        break;

    case 23:
        /* Print confirmation state */
        if (snap->dlg_result == 2) {
            lbAudioAx_80024030(0);
            snap->state = 6;
            snap->dlg_active = 0;
            snap->dlg_timer = 0;
            if (snap->dlg_text != NULL) {
                HSD_SisLib_803A5CC4(snap->dlg_text);
                snap->dlg_text = NULL;
            }
        } else {
            s32 other_slot = snap->active_slot ^ 1;
            s32 card_status;
            if (lbSnap_8001D338(other_slot) != 0) {
                mnSnap_80253E90(other_slot);
            }
            card_status = snap->card_status[other_slot];
            if (card_status == 0) {
                if (snap->active_slot == 0) {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x152);
                } else {
                    HSD_SisLib_803A6368(snap->dlg_text, 0x151);
                }
                mnSnap_8025409C((HSD_JObj*) 1);
                snap->state = 0x15;
            }
        }
        break;
    }

end_switch:
end_loop:
    while (snap->pending_loads != 0) {
        mnSnap_8025329C();
    }
}

// @TODO: Currently 99.25% match - needs minor register allocation fix
// Handles the Back button to exit the Snap menu and cleans up GObjs/text.
void fn_80257D7C(void)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    s32 i;
    u64 buttons;

    if (mn_804D6BC8.cooldown != 0) {
        Menu_DecrementAnimTimer();
        return;
    }

    buttons = Menu_GetAllInputs();

    if (mnSnap_804A0A10.state == 4 || mnSnap_804A0A10.state == 2) {
        if (buttons & MenuInput_Back) {
            sfxBack();
            mn_804A04F0.entering_menu = 0;
            mn_80229894(5, 0, 3);

            if (mnSnap_804A0A10.main_gobj != NULL) {
                HSD_GObjPLink_80390228(mnSnap_804A0A10.main_gobj);
            }
            if (mnSnap_804A0A10.sub_gobj != NULL) {
                HSD_GObjPLink_80390228(mnSnap_804A0A10.sub_gobj);
            }
            if (snap->cursor_gobj != NULL) {
                HSD_GObjPLink_80390228(mnSnap_804A0A10.cursor_gobj);
            }
            if (mnSnap_804A0A10.warn_gobj != NULL) {
                HSD_GObjPLink_80390228(mnSnap_804A0A10.warn_gobj);
            }

            for (i = 0; i < 4; i++) {
                if (mnSnap_804A0A10.thumb_labels[i] != NULL) {
                    HSD_SisLib_803A5CC4(mnSnap_804A0A10.thumb_labels[i]);
                }
            }

            for (i = 0; i < 2; i++) {
                if (mnSnap_804A0A10.count_texts[i] != NULL) {
                    HSD_SisLib_803A5CC4(mnSnap_804A0A10.count_texts[i]);
                }
            }

            if (mnSnap_804A0A10.page_text != NULL) {
                HSD_SisLib_803A5CC4(mnSnap_804A0A10.page_text);
            }
            if (mnSnap_804A0A10.total_text != NULL) {
                HSD_SisLib_803A5CC4(mnSnap_804A0A10.total_text);
            }
            if (mnSnap_804A0A10.dlg_text != NULL) {
                HSD_SisLib_803A5CC4(mnSnap_804A0A10.dlg_text);
            }

            return;
        }
    }

    mnSnap_804A0A10.frame_count += 1;
}

// @TODO: Currently 84.05% match - needs register allocation and struct fixes
// Entry point: initializes the Snap menu scene. Loads assets, creates GObjs,
// sets up thumbnail grid positions, SIS text labels, and dialog widgets.
void mnSnap_80257F24(void)
{
    mnSnap_State* snap = &mnSnap_804A0A10;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    HSD_JObj* pos_start;
    HSD_JObj* pos_end;
    HSD_GObjProc* proc;
    HSD_Text* text;
    Vec3 start_pos;
    Vec3 end_pos;
    Vec3 pos;
    s32 i;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x19;
    mn_804A04F0.hovered_selection = 0;

    lb_8001CDB4();
    memzero(&mnSnap_804A0A10, sizeof(mnSnap_State));

    snap->state = 0;
    snap->timer = 6;
    snap->photo_count[0] = 0;
    snap->photo_count[1] = 0;
    snap->card_status[0] = 0;
    snap->card_status[1] = 0;

    lbArchive_LoadSections(
        mn_804D6BB8, (void**) &snap->main_joint, "MenMainConSn_Top_joint",
        (void**) &snap->main_animjoint, "MenMainConSn_Top_animjoint",
        (void**) &snap->main_matanim, "MenMainConSn_Top_matanim_joint",
        (void**) &snap->main_shapeanim, "MenMainConSn_Top_shapeanim_joint",
        (void**) &snap->csr_joint, "MenMainSubCsrSn_Top_joint",
        (void**) &snap->csr_animjoint, "MenMainSubCsrSn_Top_animjoint",
        (void**) &snap->csr_matanim, "MenMainSubCsrSn_Top_matanim_joint",
        (void**) &snap->csr_shapeanim, "MenMainSubCsrSn_Top_shapeanim_joint",
        (void**) &snap->photo_joint, "MenMainPhotoSn_Top_joint",
        (void**) &snap->sub_animjoint, "MenMainSubSn_Top_animjoint",
        (void**) &snap->sub_matanim, "MenMainSubSn_Top_matanim_joint",
        (void**) &snap->sub_shapeanim, "MenMainSubSn_Top_shapeanim_joint",
        (void**) &snap->page_joint, "MenMainSubSn_Top_joint",
        (void**) &snap->load_joint, "MenMainLoadSn_Top_joint",
        (void**) &snap->load_animjoint, "MenMainLoadSn_Top_animjoint",
        (void**) &snap->load_matanim, "MenMainLoadSn_Top_matanim_joint",
        (void**) &snap->arrows_joint, "MenMainSubSn_Top_joint",
        (void**) &snap->arrows_animjoint, "MenMainSubSn_Top_animjoint",
        (void**) &snap->arrows_matanim, "MenMainSubSn_Top_matanim_joint",
        (void**) &snap->arrows_shapeanim, "MenMainSubSn_Top_shapeanim_joint",
        (void**) &snap->warn_joint, "MenMainWarCmn_Top_joint",
        (void**) &snap->warn_animjoint, "MenMainWarCmn_Top_animjoint",
        (void**) &snap->warn_matanim, "MenMainWarCmn_Top_matanim_joint",
        (void**) &snap->warn_shapeanim, "MenMainWarCmn_Top_shapeanim_joint",
        0);

    /* Main GObj */
    gobj = GObj_Create(6, 7, 0x80);
    snap->main_gobj = gobj;
    jobj = HSD_JObjLoadJoint((HSD_Joint*) snap->main_joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, (GObj_RenderFunc) fn_80253DB4, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, (HSD_AnimJoint*) snap->main_animjoint,
                       (HSD_MatAnimJoint*) snap->main_matanim,
                       (HSD_ShapeAnimJoint*) snap->main_shapeanim);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    lb_80011E24(jobj, (HSD_JObj**) &snap->thumb_jobjs[0], 8, 9, 0xA, 0xB, 0xC,
                0xD);

    snap->blank_img = *(void**) (snap->slot_a_jobj)->u.dobj->next->next->aobj;

    if (snap->photo_count[snap->active_slot] <= 4) {
        HSD_JObjSetFlagsAll(snap->arrow_jobj, 0x10);
    } else {
        HSD_JObjClearFlagsAll(snap->arrow_jobj, 0x10);
    }

    HSD_AObjSetFlags((snap->select_jobj)->u.dobj->next->next->aobj,
                     0x20000000);

    HSD_JObjSetFlagsAll(snap->move_jobj, 0x10);
    HSD_AObjSetFlags((snap->move_jobj)->u.dobj->next->next->aobj, 0x20000000);

    HSD_GObjProc_8038FD54(gobj, (HSD_GObjEvent) fn_802545C4, 0);

    /* Sub GObj (arrows/cursor) */
    gobj = GObj_Create(6, 7, 0x80);
    snap->sub_gobj = gobj;
    jobj = HSD_JObjLoadJoint((HSD_Joint*) snap->arrows_joint);
    HSD_JObjSetTranslateX(jobj, 3.3F);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, (GObj_RenderFunc) fn_80253DE8, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, (HSD_AnimJoint*) snap->arrows_animjoint,
                       (HSD_MatAnimJoint*) snap->arrows_matanim,
                       (HSD_ShapeAnimJoint*) snap->arrows_shapeanim);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    lb_80011E24(jobj, (HSD_JObj**) &snap->slot_a_jobj, 1, 2, 3, 4, -1);

    /* Cursor GObj */
    gobj = GObj_Create(6, 7, 0x80);
    snap->cursor_gobj = gobj;
    jobj = HSD_JObjLoadJoint((HSD_Joint*) snap->csr_joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, (GObj_RenderFunc) fn_80253E1C, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, (HSD_AnimJoint*) snap->csr_animjoint,
                       (HSD_MatAnimJoint*) snap->csr_matanim,
                       (HSD_ShapeAnimJoint*) snap->csr_shapeanim);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    lb_80011E24(jobj, (HSD_JObj**) &snap->thumb_root, 0, 1, 7, 8, -1);

    /* Get thumbnail start/end positions */
    pos_start = snap->thumb_start;
    HSD_JObjGetTranslation(pos_start, &start_pos);

    pos_end = snap->thumb_end;
    end_pos.x = pos_end->translate.x;
    end_pos.y = pos_end->translate.y;
    end_pos.z = pos_end->translate.z;

    /* Create 5 thumbnail position JObjs by interpolating */
    for (i = 0; i < 5; i++) {
        jobj2 = HSD_JObjLoadJoint((HSD_Joint*) snap->photo_joint);
        HSD_JObjAddAnimAll(jobj2, (HSD_AnimJoint*) snap->sub_animjoint,
                           (HSD_MatAnimJoint*) snap->sub_matanim,
                           (HSD_ShapeAnimJoint*) snap->sub_shapeanim);
        pos.x = (end_pos.x - start_pos.x) * (f32) i + start_pos.x;
        pos.y = (end_pos.y - start_pos.y) * (f32) i + start_pos.y;
        pos.z = (end_pos.z - start_pos.z) * (f32) i + start_pos.z;
        HSD_JObjSetTranslate(jobj2, &pos);
        snap->option_jobjs[i] = jobj2;
        HSD_JObjAddChild(snap->thumb_root, jobj2);
    }

    /* Load page indicator */
    jobj2 = HSD_JObjLoadJoint((HSD_Joint*) snap->page_joint);
    snap->fullview_jobj = jobj2;
    HSD_JObjAddChild(snap->thumb_root, jobj2);
    HSD_JObjSetFlagsAll(jobj2, 0x10);

    /* Create 4 SIS text objects for thumbnail labels */
    for (i = 0; i < 4; i++) {
        snap->thumb_labels[i] = HSD_SisLib_803A6754(0, 0);
    }

    /* Set text positions for 4 thumbnail labels */
    text = snap->thumb_labels[0];
    text->pos_x = -11.2F;
    text->pos_y = -2.6F;
    text->pos_z = 19.8F;
    text->font_size.x = 0.028F;
    text->font_size.y = 0.031F;
    text->default_alignment = 1;

    text = snap->thumb_labels[1];
    text->pos_x = -11.2F;
    text->pos_y = 4.4F;
    text->pos_z = 19.8F;
    text->font_size.x = 0.028F;
    text->font_size.y = 0.031F;
    text->default_alignment = 1;

    text = snap->thumb_labels[2];
    text->pos_x = 10.9F;
    text->pos_y = -2.6F;
    text->pos_z = 19.8F;
    text->font_size.x = 0.028F;
    text->font_size.y = 0.031F;
    text->default_alignment = 1;

    text = snap->thumb_labels[3];
    text->pos_x = 10.9F;
    text->pos_y = 4.4F;
    text->pos_z = 19.8F;
    text->font_size.x = 0.028F;
    text->font_size.y = 0.031F;
    text->default_alignment = 1;

    /* Create 2 SIS text objects for camera counts */
    for (i = 0; i < 2; i++) {
        snap->count_texts[i] = HSD_SisLib_803A6754(0, 0);
    }

    text = snap->count_texts[0];
    text->pos_x = -11.6F;
    text->pos_y = 9.0F;
    text->pos_z = 17.3F;
    text->font_size.x = 0.045F;
    text->font_size.y = 0.045F;
    text->default_alignment = 1;

    text = snap->count_texts[1];
    text->pos_x = 11.0F;
    text->pos_y = 9.0F;
    text->pos_z = 17.3F;
    text->font_size.x = 0.045F;
    text->font_size.y = 0.045F;
    text->default_alignment = 1;

    /* Create page text objects */
    snap->page_text = HSD_SisLib_803A6754(0, 0);
    text = snap->page_text;
    text->pos_x = -1.8F;
    text->pos_y = 9.2F;
    text->pos_z = 17.0F;
    text->font_size.x = 0.04F;
    text->font_size.y = 0.04F;
    text->default_alignment = 1;

    snap->total_text = HSD_SisLib_803A6754(0, 0);
    text = snap->total_text;
    text->pos_x = 1.6F;
    text->pos_y = 9.2F;
    text->pos_z = 17.0F;
    text->font_size.x = 0.04F;
    text->font_size.y = 0.04F;
    text->default_alignment = 1;

    mnSnap_80253964();

    /* Warning cmn GObj */
    gobj = GObj_Create(6, 7, 0x80);
    snap->warn_gobj = gobj;
    jobj = HSD_JObjLoadJoint((HSD_Joint*) snap->warn_joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, (GObj_RenderFunc) fn_80253E5C, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, (HSD_AnimJoint*) snap->warn_animjoint,
                       (HSD_MatAnimJoint*) snap->warn_matanim,
                       (HSD_ShapeAnimJoint*) snap->warn_shapeanim);
    HSD_JObjReqAnimAll(jobj, 10.0F);
    HSD_JObjAnimAll(jobj);
    lb_80011E24(jobj, (HSD_JObj**) &snap->dlg_root, 0, 2, 4, 5, 6, 7);

    snap->dlg_active = 0;

    /* Timer/input GObj */
    gobj = GObj_Create(0, 1, 0x80);
    proc = HSD_GObjProc_8038FD54(gobj, (HSD_GObjEvent) fn_80257D7C, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}

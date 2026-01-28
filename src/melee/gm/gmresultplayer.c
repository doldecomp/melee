#include "gmresultplayer.h"

#include "gm_unsplit.h"

#include "cm/camera.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/mtx.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/sc/types.h>

extern ResultsData lbl_8046DBE8;

/* 46E38C */ static int lbl_8046E38C[4];

void gm_80177724(struct ResultsMatchInfo* arg0)
{
    memzero(arg0, sizeof(*arg0));
}

static inline void inline0(HSD_JObj* jobj, float f)
{
    HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                    AOBJ_ARG_AF, 0.0);
    HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetCurrentFrame,
                    AOBJ_ARG_AF, f);
    HSD_JObjAnimAll(jobj);
}

void fn_80177748(void)
{
    MatchEnd* temp_r3;
    int i;
    CharacterKind ckind;
    int var_r24;

    ResultsData* data = &lbl_8046DBE8;

    temp_r3 = fn_80174274();

    for (i = 0; i < 4; i++) {
        if (temp_r3->player_standings[i].slot_type != Gm_PKind_NA) {
            ckind = temp_r3->player_standings[i].character_kind;
            HSD_JObjClearFlagsAll(data->player_data[i].jobjs[0], JOBJ_HIDDEN);
            inline0(data->player_data[i].jobjs[0], gm_80168B34(ckind, 0, 0));
            HSD_JObjClearFlagsAll(data->player_data[i].jobjs[4], JOBJ_HIDDEN);
            if (gm_801743A4(temp_r3->result) != 0) {
                var_r24 = 4;
            } else if (temp_r3->is_teams == 0) {
                if (temp_r3->player_standings[i].is_small_loser == 0) {
                    var_r24 = 5;
                } else {
                    var_r24 = temp_r3->player_standings[i].is_big_loser;
                }
            } else if (temp_r3->is_teams == 1) {
                if (data->x6 == i) {
                    var_r24 = 5;
                } else {
                    var_r24 =
                        temp_r3
                            ->team_standings[temp_r3->player_standings[i].team]
                            .is_big_loser;
                }
            }
            inline0(data->player_data[i].jobjs[4], var_r24);
        }
    }
}

void fn_80177920(HSD_GObj* gobj)
{
    MatchEnd* end;
    int human_controller_count;
    int i;

    ResultsData* data = &lbl_8046DBE8;

    PAD_STACK(8);

    end = fn_80174274();
    human_controller_count = 0;

    for (i = 0; i < 4; i++) {
        if (end->player_standings[i].slot_type == Gm_PKind_Human &&
            HSD_PadMasterStatus[(u8) i].err == 0)
        {
            human_controller_count++;
            if (HSD_PadCopyStatus[(u8) i].trigger != 0) {
                data->x1 = 3;
                break;
            }
        }
    }

    if (human_controller_count == 0) {
        for (i = 0; i < 4; i++) {
            if (HSD_PadMasterStatus[(u8) i].err == 0 &&
                HSD_PadCopyStatus[(u8) i].trigger != 0)
            {
                data->x1 = 3;
                break;
            }
        }
    }
    if (data->x1 == 3) {
        lb_8000BA0C(gobj->hsd_obj, 1.0F);
        fn_80177748();
    }
}

extern UNK_T lbl_803D6878[];

static inline bool pagePrev(int slot)
{
    ResultsData* data = &lbl_8046DBE8;
    if (data->player_data[slot].page != 0) {
        data->player_data[slot].page--;
        data->player_data[slot].scroll_offset = 0.0F;
        fn_80174380();
        return true;
    } else {
        return false;
    }
}

static inline bool pageNext(int slot)
{
    ResultsData* data = &lbl_8046DBE8;
    if (data->player_data[slot].page < data->num_pages - 1) {
        data->player_data[slot].page++;
        data->player_data[slot].scroll_offset = 0.0F;
        fn_80174380();
        return true;
    } else {
        return false;
    }
}

static const float scroll_speed = 0.2F;

static inline bool scrollDown(int slot, float amount)
{
    int scroll_max;
    ResultsData* data = &lbl_8046DBE8;
    amount *= scroll_speed;

    scroll_max = fn_80174A60(fn_801748EC(&lbl_803D6878,
                                         data->player_data[slot].page, slot),
                             slot) -
                 10;
    if (data->player_data[slot].scroll_offset < scroll_max) {
        data->player_data[slot].scroll_offset += amount;
        if (data->player_data[slot].scroll_offset > scroll_max) {
            data->player_data[slot].scroll_offset = scroll_max;
        }
        return true;
    } else {
        return false;
    }
}

static inline bool scrollUp(int slot, float amount)
{
    ResultsData* data = &lbl_8046DBE8;
    amount *= scroll_speed;

    if (data->player_data[slot].scroll_offset > 0) {
        data->player_data[slot].scroll_offset -= amount;
        if (data->player_data[slot].scroll_offset < 0) {
            data->player_data[slot].scroll_offset = 0;
        }
        return true;
    } else {
        return false;
    }
}

/**
 * Handles result screen controller input for a given player slot.
 *
 * Pressing triggers moves to next/previous page, and moving the
 * stick up/down scrolls within the current page.
 *
 * @returns True if the input was handled and the screen needs updating;
 * false if nothing changed.
 */
bool fn_80177B7C(int slot)
{
    static const float scroll_deadzone = 0.3F;

    {
        float stick_y = HSD_PadCopyStatus[(u8) slot].nml_stickY;
        u32 trigger;
        bool result = false;

        if (fabsf_bitwise(stick_y) < scroll_deadzone) {
            stick_y = 0;
        }
        trigger = HSD_PadCopyStatus[(u8) slot].trigger;
        if (trigger & 0x40200) {
            result = pagePrev(slot);
        } else if (trigger & 0x80100) {
            result = pageNext(slot);
        } else if (stick_y < 0) {
            result = scrollDown(slot, -stick_y);
        } else if (stick_y > 0) {
            result = scrollUp(slot, stick_y);
        }
        return result;
    }
}

bool fn_80177DD0(int slot)
{
    ResultsData* data;
    void* unk;
    int result;
    int scroll_max;

    data = &lbl_8046DBE8;
    unk = &lbl_803D6878;

    result = false;
    if (HSD_PadCopyStatus[slot].err == 0) {
        return fn_80177B7C(slot);
    }
    scroll_max =
        fn_80174A60(fn_801748EC(unk, data->player_data[slot].page, slot),
                    slot) -
        10;
    if (scroll_max < 0) {
        scroll_max = 0;
    }
    switch (data->player_data[slot].page) {
    case 0:
        if (data->player_data[slot].x2++ > 180) {
            data->player_data[slot].x2 = 0;
            data->player_data[slot].scroll_offset = 0.0F;
            data->player_data[slot].page = 1;
            result = true;
        } else {
            data->player_data[slot].scroll_offset += 0.05F;
            if (data->player_data[slot].scroll_offset > scroll_max) {
                data->player_data[slot].scroll_offset = scroll_max;
            } else {
                result = true;
            }
        }
        break;
    case 1:
        if (data->player_data[slot].x2++ > 1000) {
            if (data->player_data[slot].page < data->num_pages - 1) {
                data->player_data[slot].x2 = 0;
                data->player_data[slot].scroll_offset = 0.0F;
                data->player_data[slot].page = 2;
                result = true;
            } else {
                data->player_data[slot].x2--;
            }
        } else {
            data->player_data[slot].scroll_offset += 0.05F;
            if (data->player_data[slot].scroll_offset > scroll_max) {
                data->player_data[slot].scroll_offset = scroll_max;
            } else {
                result = true;
            }
        }
        break;
    case 2:
        if (data->player_data[slot].x2 < 1000) {
            data->player_data[slot].scroll_offset += 0.05F;
            if (data->player_data[slot].scroll_offset > scroll_max) {
                data->player_data[slot].scroll_offset = scroll_max;
            } else {
                result = true;
            }
            data->player_data[slot].x2++;
        }
        break;
    }
    return result;
}

/// #fn_80178050

/// #fn_801785B0

/// #fn_80178BB4

/// #fn_801791E4

/// #fn_80179350

/// #fn_801795D4

/// #fn_801796F0

/// #fn_80179854

/// #fn_80179990

void fn_80179D3C(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 0);
}

void fn_80179D60(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 1);
}

void fn_80179D84(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 2);
}

void fn_80179DA8(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 3);
}

void fn_80179DCC(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179E34(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179E9C(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179F04(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179F6C(int idx, int value)
{
    lbl_8046E38C[idx] = value;
}

/// #fn_80179F84

void fn_8017A004(void)
{
    ResultsData* data = &lbl_8046DBE8;
    HSD_GObj* gobj = GObj_Create(0xB, 3, 0);
    HSD_LObj* lobj = lb_80011AC4(data->pnlsce->lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
}

/// #fn_8017A078

/// #fn_8017A318

/// #fn_8017A67C

/// #fn_8017A9B4

/// #fn_8017AA78

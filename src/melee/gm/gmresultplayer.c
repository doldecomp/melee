#include "gmresultplayer.h"

#include "gm_unsplit.h"

#include "cm/camera.h"

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/tobj.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ftdemo.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/gr/stage.h>
#include <melee/if/ifcoget.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/mn/mnmain.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>
#include <sysdolphin/baselib/random.h>

extern ResultsData lbl_8046DBE8;

extern u8 lbl_8046E1B0[];

typedef struct {
    /* 0x00 */ u8 pad_00[0x20];
    /* 0x20 */ f32 x20[4];
} CharScaleEntry;

extern CharScaleEntry lbl_803D6A18[];
extern f32 lbl_803D7058[];

typedef struct {
    /* 0x00 */ u8 pad_00[0x74];
    /* 0x74 */ f32 x74;
    /* 0x78 */ f32 x78;
    /* 0x7C */ f32 x7C;
    /* 0x80 */ f32 x80;
    /* 0x84 */ f32 x84;
    /* 0x88 */ f32 x88;
    /* 0x8C */ f32 x8C;
    /* 0x90 */ f32 x90;
    /* 0x94 */ f32 x94;
    /* 0x98 */ f32 x98;
} ResultsPlayerConfig;

extern ResultsPlayerConfig lbl_803B7B68;

extern int lbl_8046E38C[4];

extern HSD_JObj* lbl_8046E39C[4];

typedef struct {
    u8 x0_0 : 1;
    u8 x0_1 : 1;
    u8 x0_2 : 1;
    u8 x0_3 : 1;
    u8 x0_4 : 2;
    u8 x0_6 : 2;
    u8 pad_01[0x2313];
} lbl_8046E3AC_t;

extern lbl_8046E3AC_t lbl_8046E3AC;

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
        PAD_STACK(8);

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

static s32 lbl_804D3FC8 = 1;

void fn_80178050(HSD_GObj* arg0)
{
    ResultsData* data = &lbl_8046DBE8;
    MatchEnd* match_end;
    HSD_JObj* jobj;
    s32 var_r24;

    PAD_STACK(16);

    match_end = fn_80174274();
    jobj = arg0->hsd_obj;
    var_r24 = 0;

    if (lbGetJObjCurrFrame(jobj) >= 50.0f && !data->x0_23) {
        lb_8000BA0C(jobj, 0.0f);
        data->x0_23 = 1;
        lbl_804D3FC8 = 1;
        {
            MatchEnd* me = match_end;
            s32 j;
            for (j = 0; j < 4; j++) {
                if ((u8) me->player_standings[0].slot_type == 0) {
                    lbl_804D3FC8 = 0;
                    break;
                }
                me = (MatchEnd*) ((u8*) me + 0xA8);
            }
        }
        if ((s32) lbl_804D3FC8 != 0) {
            ((u8*) data)[3] = 0x14;
        } else {
            ((u8*) data)[3] = 0x0A;
        }
    }

    fn_80175D34();

    {
        u32 phase = data->x0_23;
        if (phase != 0) {
            if (phase == 1) {
                data->x0_23 = 2;
                {
                    MatchEnd* me = match_end;
                    ResultsData* rd = data;
                    s32 k = 0;
                    do {
                        switch ((s32) me->player_standings[0].slot_type) {
                        case 2:
                            break;
                        case 3:
                            rd->player_data[0].x0_0 = 1;
                            break;
                        case 0:
                            fn_80174B4C(data, k);
                            break;
                        case 1:
                            fn_80174B4C(data, k);
                            rd->player_data[0].x0_0 = 1;
                            break;
                        }
                        k++;
                        me = (MatchEnd*) ((u8*) me + 0xA8);
                        rd = (ResultsData*) ((u8*) rd + 0xD8);
                    } while (k < 4);
                }
            }

            {
                MatchEnd* me2 = match_end;
                ResultsData* rd2 = data;
                HSD_PadStatus* pad = HSD_PadCopyStatus;
                s32 k2 = 0;
                do {
                    u8 slot = me2->player_standings[0].slot_type;
                    if (slot == 0) {
                        if (!rd2->player_data[0].x0_0) {
                            if (fn_80177B7C(k2) != 0) {
                                fn_80174B4C(data, k2);
                            }
                            if (((s8) pad->err != 0) ||
                                (HSD_PadCopyStatus[(u8) k2].trigger &
                                 0x1000))
                            {
                                rd2->player_data[0].x0_0 = 1;
                                fn_80174920(&rd2->player_data[0]);
                                lbDObjSetRateAll(
                                    HSD_JObjGetDObj(
                                        rd2->player_data[0].jobjs[6]),
                                    1.0f);
                                lbDObjReqAnimAll(
                                    HSD_JObjGetDObj(
                                        rd2->player_data[0].jobjs[6]),
                                    50.0f);
                                HSD_AObjSetRate(
                                    rd2->player_data[0].jobjs[1]->aobj,
                                    1.0f);
                                HSD_AObjReqAnim(
                                    rd2->player_data[0].jobjs[1]->aobj,
                                    50.0f);
                                HSD_JObjAnimAll(
                                    rd2->player_data[0].jobjs[6]);
                                HSD_JObjAnimAll(
                                    rd2->player_data[0].jobjs[1]);
                                HSD_JObjSetFlagsAll(
                                    rd2->player_data[0].jobjs[0], 0x10U);
                                HSD_JObjSetFlagsAll(
                                    rd2->player_data[0].jobjs[4], 0x10U);
                                rd2->player_data[0].x0_1 = 0;
                                rd2->player_data[0].x0_2 = 0;
                                rd2->player_data[0].x0_3 = 0;
                                rd2->player_data[0].x0_4 = 0;
                                fn_80174338();
                            }
                        } else if (HSD_PadCopyStatus[(u8) k2].trigger &
                                   0x1000)
                        {
                            fn_80174920(&rd2->player_data[0]);
                            rd2->player_data[0].x0_0 = 0;
                            fn_80174B4C(data, k2);
                            lbDObjSetRateAll(
                                HSD_JObjGetDObj(
                                    rd2->player_data[0].jobjs[6]),
                                0.0f);
                            lbDObjReqAnimAll(
                                HSD_JObjGetDObj(
                                    rd2->player_data[0].jobjs[6]),
                                50.0f);
                            HSD_AObjSetRate(
                                rd2->player_data[0].jobjs[1]->aobj, 0.0f);
                            HSD_AObjReqAnim(
                                rd2->player_data[0].jobjs[1]->aobj,
                                50.0f);
                            HSD_JObjAnimAll(rd2->player_data[0].jobjs[6]);
                            HSD_JObjAnimAll(rd2->player_data[0].jobjs[1]);
                            HSD_JObjClearFlagsAll(
                                rd2->player_data[0].jobjs[0], 0x10U);
                            HSD_JObjClearFlagsAll(
                                rd2->player_data[0].jobjs[4], 0x10U);
                            fn_8017435C();
                        }
                    } else if (slot == 1) {
                        if (fn_80177DD0(k2) != 0) {
                            fn_80174B4C(data, k2);
                        }
                        if ((s32) lbl_804D3FC8 != 0) {
                            rd2->player_data[0].x0_0 = 0;
                            if (((s8) pad->err == 0) &&
                                (HSD_PadCopyStatus[(u8) k2].trigger &
                                 0x1000))
                            {
                                fn_80174338();
                                var_r24 = 1;
                            }
                        }
                    } else if (slot == 3) {
                        if (((s32) lbl_804D3FC8 != 0) &&
                            ((s8) pad->err == 0) &&
                            (HSD_PadCopyStatus[(u8) k2].trigger & 0x1000))
                        {
                            fn_80174338();
                            var_r24 = 1;
                        }
                    }
                    k2++;
                    me2 = (MatchEnd*) ((u8*) me2 + 0xA8);
                    rd2 = (ResultsData*) ((u8*) rd2 + 0xD8);
                    pad = (HSD_PadStatus*) ((u8*) pad + 0x44);
                } while (k2 < 4);
            }

            {
                ResultsData* rd3 = data;
                s32 k3 = 0;
                do {
                    if ((u8) match_end->player_standings[0].slot_type !=
                        3)
                    {
                        if (!rd3->player_data[0].x0_1) {
                            HSD_JObjSetFlagsAll(
                                rd3->player_data[0].jobjs[8], 0x10U);
                        } else {
                            HSD_JObjClearFlagsAll(
                                rd3->player_data[0].jobjs[8], 0x10U);
                        }
                        if (!rd3->player_data[0].x0_2) {
                            HSD_JObjSetFlagsAll(
                                rd3->player_data[0].jobjs[9], 0x10U);
                        } else {
                            HSD_JObjClearFlagsAll(
                                rd3->player_data[0].jobjs[9], 0x10U);
                        }
                        if (!rd3->player_data[0].x0_3) {
                            HSD_JObjSetFlagsAll(
                                rd3->player_data[0].jobjs[0xA], 0x10U);
                        } else {
                            HSD_JObjClearFlagsAll(
                                rd3->player_data[0].jobjs[0xA], 0x10U);
                        }
                        if (!rd3->player_data[0].x0_4) {
                            HSD_JObjSetFlagsAll(
                                rd3->player_data[0].jobjs[0xB], 0x10U);
                        } else {
                            HSD_JObjClearFlagsAll(
                                rd3->player_data[0].jobjs[0xB], 0x10U);
                        }
                    }
                    k3++;
                    match_end =
                        (MatchEnd*) ((u8*) match_end + 0xA8);
                    rd3 = (ResultsData*) ((u8*) rd3 + 0xD8);
                } while (k3 < 4);
            }

            {
                s32 all_done = 0;
                if (!data->player_data[0].x0_0) {
                    all_done = 1;
                } else if (!data->player_data[1].x0_0) {
                    all_done = 1;
                } else if (!data->player_data[2].x0_0) {
                    all_done = 1;
                } else if (!data->player_data[3].x0_0) {
                    all_done = 1;
                }
                if (all_done == 0) {
                    var_r24 = 1;
                }
                if (var_r24 != 0) {
                    data->x1 = 4;
                }
            }
        }
    }
}

void fn_801785B0(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObj* child;
    HSD_JObj* node;
    MatchEnd* match_end = fn_80174274();
    u8 mode = match_end->x5;
    int frame_val;
    f32 fv;
    int unused;

    if (mode == 2) {
        lb_80011E24(jobj, &child, 0x15, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x11, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x10, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0xC, -1);
        node = child;
        {
            u8 raw = fn_80174274()->xC;
            if ((s8) raw < 0) {
                frame_val = -(s8) raw;
            } else {
                frame_val = (s8) raw;
            }
        }
        fv = (f32) frame_val;
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, fv);
        HSD_JObjAnimAll(node);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 1.0f);
        mn_8022F3D8(node, 1, TOBJ_MASK);
        return;
    } else if (mode == 1) {
        lb_80011E24(jobj, &child, 0x15, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0xC, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x10, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x11, -1);
        node = child;
        {
            u8 raw = fn_80174274()->xC;
            if ((s8) raw < 0) {
                frame_val = -(s8) raw;
            } else {
                frame_val = (s8) raw;
            }
        }
        fv = (f32) frame_val;
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, fv);
        HSD_JObjAnimAll(node);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 1.0f);
        mn_8022F3D8(node, 1, TOBJ_MASK);
        return;
    } else if (mode == 3) {
        lb_80011E24(jobj, &child, 0x11, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0xC, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x15, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x10, -1);
        node = child;
        {
            u8 raw = fn_80174274()->xC;
            if ((s8) raw < 0) {
                frame_val = -(s8) raw;
            } else {
                frame_val = (s8) raw;
            }
        }
        fv = (f32) frame_val;
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, fv);
        HSD_JObjAnimAll(node);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 1.0f);
        mn_8022F3D8(node, 1, TOBJ_MASK);
        return;
    } else {
        lb_80011E24(jobj, &child, 0x11, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0xC, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x10, -1);
        HSD_JObjRemoveAnimAll(child);
        lb_80011E24(jobj, &child, 0x15, -1);
        node = child;
        {
            u8 raw = fn_80174274()->xC;
            if ((s8) raw < 0) {
                frame_val = -(s8) raw;
            } else {
                frame_val = (s8) raw;
            }
        }
        fv = (f32) frame_val;
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, fv);
        HSD_JObjAnimAll(node);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjSetCurrentFrame, AOBJ_ARG_AF, 0.0f);
        HSD_ForeachAnim(node, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                        AOBJ_ARG_AF, 1.0f);
        mn_8022F3D8(node, 1, TOBJ_MASK);
        return;
    }
}

void fn_80178BB4(HSD_GObj* gobj)
{
    ResultsData* data = &lbl_8046DBE8;
    MatchEnd* match_end = fn_80174274();
    int ko_count = 0;
    int i;

    fn_80179854();
    fn_80175DC8(gobj);
    fn_80175C5C();

    if (gm_801743A4(match_end->result) != 0) {
        int anim_n = 0xB8;
        HSD_TObj* tobj = data->x30->u.dobj->next->mobj->tobj;
        HSD_AObj* aobj = tobj->aobj;
        int start;
        HSD_TObjReqAnim(tobj, (f32) anim_n);
        HSD_TObjAnim(data->x30->u.dobj->next->mobj->tobj);
        start = (int) (30.0f * (f32) (anim_n - 0xB4));
        HSD_AObjSetCurrentFrame(aobj, (f32) start);
        HSD_AObjSetEndFrame(aobj, (30.0f + (f32) start) - 1.0f);
        mn_8022F3D8(data->x30, 1, TOBJ_MASK);
    } else if ((u8) match_end->is_teams == 1) {
        int tex_id = data->x5 + 0xB5;
        HSD_TObj* tobj = data->x30->u.dobj->next->mobj->tobj;
        HSD_AObj* aobj = tobj->aobj;
        HSD_TObjReqAnim(tobj, (f32) tex_id);
        HSD_TObjAnim(data->x30->u.dobj->next->mobj->tobj);
        if (tex_id < 0x19) {
            HSD_AObjSetCurrentFrame(aobj, 0.0f);
            HSD_AObjSetEndFrame(aobj, 29.0f);
        } else {
            int start = (int) (30.0f * (f32) (tex_id - 0xB4));
            HSD_AObjSetCurrentFrame(aobj, (f32) start);
            HSD_AObjSetEndFrame(aobj, (30.0f + (f32) start) - 1.0f);
        }
        mn_8022F3D8(data->x30, 1, TOBJ_MASK);
    }

    i = 0;
    do {
        HSD_JObjSetFlagsAll(data->player_data[i].jobjs[0], 0x10);
        HSD_JObjSetFlagsAll(data->player_data[i].jobjs[4], 0x10);
        HSD_JObjSetFlagsAll(data->player_data[i].jobjs[8], 0x10);
        HSD_JObjSetFlagsAll(data->player_data[i].jobjs[9], 0x10);
        HSD_JObjSetFlagsAll(data->player_data[i].jobjs[10], 0x10);
        HSD_JObjSetFlagsAll(data->player_data[i].jobjs[11], 0x10);
        lbDObjSetRateAll(
            HSD_JObjGetDObj(data->player_data[i].jobjs[6]), 0.0f);

        {
            u8 slot_type = match_end->player_standings[i].slot_type;

            if (slot_type == 0) {
                ko_count += match_end->player_standings[i].xE;
            }

            if (slot_type != 3) {
                int ckind =
                    match_end->player_standings[i].character_kind;
                int cid =
                    match_end->player_standings[i].character_id;
                u8 is_big_loser =
                    match_end->player_standings[i].is_big_loser;

            if (gm_801743A4(match_end->result) == 0 &&
                (u8) match_end->is_teams == 0 &&
                (s32) is_big_loser == 0)
            {
                ResultsData* d2 = &lbl_8046DBE8;
                int tex_id = (int) gm_80168B34(
                    (CharacterKind) ckind, (int) cid, 0);
                HSD_TObj* tobj =
                    d2->x30->u.dobj->next->mobj->tobj;
                HSD_AObj* aobj = tobj->aobj;
                HSD_TObjReqAnim(tobj, (f32) tex_id);
                HSD_TObjAnim(
                    d2->x30->u.dobj->next->mobj->tobj);
                if (tex_id < 0x19) {
                    HSD_AObjSetCurrentFrame(aobj, 0.0f);
                    HSD_AObjSetEndFrame(aobj, 29.0f);
                } else {
                    int start =
                        (int) (30.0f * (f32) (tex_id - 0xB4));
                    HSD_AObjSetCurrentFrame(aobj, (f32) start);
                    HSD_AObjSetEndFrame(
                        aobj, (30.0f + (f32) start) - 1.0f);
                }
                mn_8022F3D8(d2->x30, 1, TOBJ_MASK);
            }

            fn_80174FD0(data->player_data[i].jobjs[5],
                        (s32) gm_80168B34(
                            (CharacterKind) ckind, (int) cid, 0));

            {
                u8 rank_val = (u8) gm_80160854(
                               i,
                               match_end->player_standings[i].team,
                               (u8) (match_end->is_teams == 1),
                               match_end->player_standings[i].slot_type);
                HSD_AObj* rank_aobj =
                    data->player_data[i].jobjs[2]->u.dobj->mobj->aobj;
                HSD_AObjSetCurrentFrame(
                    rank_aobj, 1.0f + (f32) rank_val);
                HSD_AObjSetRate(rank_aobj, 0.0f);
            }

            if ((u8) match_end->x5 != 3) {
                f32 taunt_frame = gm_80168B34(
                    (CharacterKind)(s8)(u8) match_end->player_standings[i].character_kind,
                    (int)(s8)(u8) match_end->player_standings[i].character_id,
                    match_end->player_standings[i].x3);
                HSD_JObj* taunt_jobj =
                    data->player_data[i].jobjs[7];
                HSD_ForeachAnim(taunt_jobj, JOBJ_TYPE,
                                ALL_TYPE_MASK, HSD_AObjSetRate,
                                AOBJ_ARG_AF, 0.0);
                HSD_ForeachAnim(taunt_jobj, JOBJ_TYPE,
                                ALL_TYPE_MASK,
                                HSD_AObjSetCurrentFrame,
                                AOBJ_ARG_AF, taunt_frame);
                HSD_JObjAnimAll(taunt_jobj);
                HSD_AObjSetRate(
                    data->player_data[i].jobjs[7]->aobj, 1.0f);
                HSD_AObjSetCurrentFrame(
                    data->player_data[i].jobjs[7]->aobj, 0.0f);
            } else {
                HSD_JObj* taunt_jobj =
                    data->player_data[i].jobjs[7];
                HSD_ForeachAnim(taunt_jobj, JOBJ_TYPE,
                                ALL_TYPE_MASK, HSD_AObjSetRate,
                                AOBJ_ARG_AF, 0.0);
                HSD_ForeachAnim(taunt_jobj, JOBJ_TYPE,
                                ALL_TYPE_MASK,
                                HSD_AObjSetCurrentFrame,
                                AOBJ_ARG_AF, 0.0);
                HSD_JObjAnimAll(taunt_jobj);
                HSD_JObjSetFlagsAll(
                    data->player_data[i].jobjs[7], 0x10);
            }

            HSD_JObjRemoveAnimAll(data->player_data[i].jobjs[3]);
            HSD_JObjSetFlagsAll(data->player_data[i].jobjs[3], 0x10);
        } else {
            HSD_JObjSetFlagsAll(data->player_data[i].jobjs[1], 0x10);
            HSD_JObjRemoveAnimAll(data->player_data[i].jobjs[1]);
            HSD_JObjSetFlagsAll(data->player_data[i].jobjs[5], 0x10);
            HSD_JObjSetFlagsAll(data->player_data[i].jobjs[7], 0x10);
        }
        }

        i++;
    } while (i < 6);

    if (ko_count > 0) {
        un_802FF128(0x6C, 0x78, ko_count, 5);
    }

    data->x1 = 1;
}

int fn_801791E4(void)
{
    ResultsData* data = &lbl_8046DBE8;
    MatchEnd* end = fn_80174274();
    int i;

    PAD_STACK(8);

    if (gm_801743A4(end->result) != 0) {
        for (i = 0; i < 4; i++) {
            if (end->player_standings[i].slot_type == Gm_PKind_Human &&
                HSD_PadMasterStatus[(u8) i].err == 0 &&
                (HSD_PadCopyStatus[(u8) i].trigger & 0x1000))
            {
                return 1;
            }
        }
    }

    if ((u32) data->x8 == 0xA0U) {
        return 1;
    }
    return 0;
}

/// #fn_80179350
#pragma dont_inline on
void fn_80179350(HSD_GObj* arg0)
{
    ResultsData* data = &lbl_8046DBE8;
    MatchEnd* match_end;
    int i;

    PAD_STACK(8);

    match_end = fn_80174274();

    for (i = 0; i < 6; i++) {
        if (data->player_data[i].jobjs[12] != NULL) {
            lb_8000B1CC(data->player_data[i].jobjs[12], NULL,
                        &data->player_data[i].stats_position);
        }
    }

    if ((u32) data->x8 == 0 && data->x0_4) {
        gm_801A4634(0);
    }

    if ((u32) data->x8 == 0xA2) {
        if (gm_801743A4(match_end->result) == 0) {
            lbAudioAx_800237A8(0xB5, 0x7F, 0x40);
        }
    } else if ((u32) data->x8 == 0x2) {
        if (gm_801743A4(match_end->result) == 0) {
            lbAudioAx_800237A8(0xC355, 0x7F, 0x40);
            lbAudioAx_800237A8(0x144, 0x7F, 0x40);
        } else {
            lbAudioAx_800237A8(0x148, 0x7F, 0x40);
        }
    } else if ((u32) data->x8 == 0x9A) {
        if (gm_801743A4(match_end->result) != 0) {
            lbAudioAx_800237A8(0xC350, 0x7F, 0x40);
        } else {
            fn_80168E54(
                (s8)(u8) match_end->player_standings[data->x6].character_kind,
                (s8)(u8) match_end->player_standings[data->x6].character_id,
                match_end->player_standings[data->x6].team,
                (u8)(match_end->is_teams == 1));
        }
    }

    if (data->x1 < 1) {
        if (fn_801791E4() != 0) {
            fn_80178BB4(arg0);
        }
    } else {
        HSD_JObjAnimAll((HSD_JObj*) arg0->hsd_obj);
        switch (data->x1) {
        case 1:
        {
            ResultsData* d = &lbl_8046DBE8;
            HSD_JObj* jobj = (HSD_JObj*) arg0->hsd_obj;
            float frame = lbGetJObjCurrFrame(jobj);
            if (frame >= 10.0f && !d->x0_1) {
                fn_80177748();
                d->x0_1 = 1;
            }
            if (frame >= 40.0f) {
                lb_8000BA0C(jobj, 0.0f);
                d->x1 = 2;
            }
            break;
        }
        case 2:
            fn_80177920(arg0);
            break;
        case 3:
            fn_80178050(arg0);
            break;
        case 4:
            if ((u8) data->pad_03[0] != 0) {
                data->pad_03[0] = (char)((u8) data->pad_03[0] - 1);
            } else {
                gm_801A4B60();
            }
            break;
        }
    }

    if ((u32) data->x8 < (u32) -1) {
        data->x8++;
    }
}
#pragma dont_inline off

int fn_801795D4(void)
{
    u8* data = (u8*) &lbl_8046E3AC + 0x28;
    int count = 0;
    int i;

    for (i = 0; i < 4; i++) {
        int lookup;

        if (data[6] == 0) {
            lookup = data[i * 0xA8 + 0x5D];
        } else {
            int idx = data[i * 0xA8 + 0x5F];
            lookup = data[idx * 0xC + 0x24];
        }

        if (data[i * 0xA8 + 0x58] != 3 && lookup == 0) {
            count++;
        }
    }

    if (count != 0) {
        return count - 1;
    }
    return count;
}

int fn_801796F0(int arg0)
{
    u8* data = (u8*) &lbl_8046E3AC + 0x28;
    int count = 0;
    int i;

    for (i = 0; i < 4; i++) {
        int lookup;

        if (data[6] == 0) {
            lookup = data[i * 0xA8 + 0x5D];
        } else {
            int idx = data[i * 0xA8 + 0x5F];
            lookup = data[idx * 0xC + 0x24];
        }

        if (data[i * 0xA8 + 0x58] != 3 && lookup == 0) {
            if (arg0 == i) {
                return count;
            }
            count++;
        }
    }

    return count;
}

int fn_80179854(void)
{
    u8* base = lbl_8046E1B0;
    u8* data = base + 0x224;
    GXColor color1 = { 0, 0, 0, 0 };
    GXColor color2 = { 0, 0, 0, 0x3C };
    HSD_GObj** gobjs = (HSD_GObj**) (base + 0x1DC);
    int i;
    int lookup;

    lbBgFlash_800206D4(&color1, &color2, 0x1E);

    for (i = 0; i < 4; i++) {
        if (data[6] == 0) {
            lookup = data[i * 0xA8 + 0x5D];
        } else {
            int idx = data[i * 0xA8 + 0x5F];
            lookup = data[idx * 0xC + 0x24];
        }

        if (data[i * 0xA8 + 0x58] != 3 && lookup != 0) {
            HSD_JObj* jobj = GET_JOBJ(gobjs[i]);
            HSD_JObjSetTranslateX(jobj, -300.0f);
            lookup = 1;
            ((lbl_8046E3AC_t*) (base + 0x1FC))->x0_6 = 1;
        }
    }

    return lookup;
}

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

void fn_80179F84(HSD_JObj* jobj)
{
    HSD_JObj* child;
    HSD_JObj* next;
    int i;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    {
        HSD_JObj** p = lbl_8046E39C;

        *p = child;

        for (i = 0; i < 3; i++) {
            if (child == NULL) {
                next = NULL;
            } else {
                next = child->next;
            }
            *++p = child = next;
        }
    }

    lbl_8046E3AC.x0_4 = 1;
}

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

Fighter_GObj* fn_8017A67C(CharacterKind c_kind, int arg1, int arg2)
{
    u8* base = lbl_8046E1B0;
    u8* standings = base + 0x224;
    ResultsPlayerConfig* config = &lbl_803B7B68;
    CharacterKind kind = c_kind;
    HSD_GObj* gobj = NULL;
    int slot_type;

    if (base[0x22A] == 0) {
        slot_type = standings[arg2 * 0xA8 + 0x5D];
    } else {
        slot_type = standings[standings[arg2 * 0xA8 + 0x5F] * 0xC + 0x24];
    }

    if (gm_80160438(kind) != NULL) {
        f32 cx, cy, cz;
        PAD_STACK(8);
        *(s32*) &cx = *(s32*) &config->x74;
        *(s32*) &cy = *(s32*) &config->x78;
        *(s32*) &cz = *(s32*) &config->x7C;

        if ((u32)(kind - 0x12) <= 1U) {
            if ((int)(s8) standings[arg2 * 0xA8 + 0x5A] == 7) {
                kind = CKIND_SEAK;
            } else {
                kind = CKIND_ZELDA;
            }
        }

        Player_80036E20(kind, lbArchive_LoadArchive(gm_80160438(kind)),
                         0);
        Player_SetPlayerCharacter(arg2, kind);
        Player_SetCostumeId(arg2, arg1);
        Player_SetPlayerId(arg2, arg2);
        Player_SetSlottype(arg2, Gm_PKind_Demo);

        if (kind == CKIND_GAMEWATCH) {
            Player_SetFacingDirection(arg2, -1.0f);
        } else {
            Player_SetFacingDirection(arg2, 0.0f);
        }

        {
            int variant;

            if (slot_type == 0) {
                u32 buttons =
                    HSD_PadCopyStatus[(u8) arg2].button;
                if (buttons & 0x200) {
                    variant = 0;
                } else if (buttons & 0x800) {
                    variant = 1;
                } else if (buttons & 0x400) {
                    variant = 2;
                } else {
                    variant = HSD_Randi(3);
                }
            } else {
                variant = 4;
            }

            if (variant != 4) {
                u8 override = base[arg2 + 0x220];
                if (override != 0) {
                    variant = override - 1;
                }
            }

            if (slot_type == 0) {
                f32 px, py, pz;
                *(s32*) &px = *(s32*) &config->x80;
                *(s32*) &py = *(s32*) &config->x84;
                *(s32*) &pz = *(s32*) &config->x88;
                py = 100.0f * (f32)(arg2 + 1);
                Player_80032A04(arg2, (Vec3*) &px);
                Player_SetScale(arg2, 1.8f * lbl_803D7058[kind]);
                Player_80036F34(arg2, variant);
            } else {
                f32 sp[4];
                int var_idx;
                f32 scale;
                *(s32*) &sp[0] = *(s32*) &config->x8C;
                *(s32*) &sp[1] = *(s32*) &config->x90;
                *(s32*) &sp[2] = *(s32*) &config->x94;
                *(s32*) &sp[3] = *(s32*) &config->x98;
                if (variant <= 2) {
                    var_idx = variant;
                } else {
                    var_idx = 3;
                }
                scale = lbl_803D6A18[kind].x20[var_idx];
                Player_80036F34(arg2, variant);
                Player_SetScale(arg2,
                    scale * (sp[slot_type] *
                             (20.0f / Player_800360D8(arg2))));
                cy = 100.0f * (f32)(arg2 + 1);
                Player_80032A04(arg2, (Vec3*) &cx);
            }

            base[arg2 + 0x20A] = (u8) variant;
            ((s32*)(base + 0x210))[arg2] = (s32) kind;
            gobj = Player_GetEntity(arg2);
        }
    }

    return (Fighter_GObj*) gobj;
}

void fn_8017A9B4(int slot)
{
    u8* base = lbl_8046E1B0;
    u8* data = base + 0x224;
    int lookup;
    int off;
    u8* tbl;
    HSD_ImageDesc* desc;

    if (base[0x22A] == 0) {
        lookup = data[slot * 0xA8 + 0x5D];
    } else {
        int idx = data[slot * 0xA8 + 0x5F];
        lookup = data[idx * 0xC + 0x24];
    }

    off = slot * 0x18;
    tbl = base + (lookup << 1);

    desc = (HSD_ImageDesc*) &base[off + 0x104];
    desc->image_ptr = NULL;
    lb_800121FC(desc, *(u16*) &tbl[0x24B0], *(u16*) &tbl[0x24C0], 5, 0);

    desc = (HSD_ImageDesc*) &base[off + 0x164];
    desc->image_ptr = NULL;
    lb_800121FC(desc, *(u16*) &tbl[0x24B8], *(u16*) &tbl[0x24C8], 5, 0);
}

/// #fn_8017AA78

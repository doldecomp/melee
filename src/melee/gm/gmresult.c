#include "gmresult.h"

#include "gm/gmresult.static.h"

#include "placeholder.h"

#include "baselib/dobj.h"

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/jobj.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/types.h"

#include "gm/forward.h"

#include "gm/gm_1601.h"
#include "gm/gm_16AE.h"
#include "gm/gm_16F1.h"
#include "gm/gm_17AD.h"
#include "gm/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbvector.h"
#include "sc/types.h"

#include <melee/pl/forward.h>

MatchEnd* fn_80174274(void)
{
    return lbl_8046DBE8.x94;
}

s32 fn_80174284(u8 slot)
{
    bool do_call;
    s32 count;
    s32 i;
    u8* buf;
    struct UnkResultPlayerData* tmp = lbl_8046DBE8.x94->x44C;

    count = 0;
    do_call =
        (lbl_8046DBE8.x94->player_standings[slot].slot_type == Gm_PKind_Human)
            ? true
            : false;

    for (i = 0; i < 0x100; i++) {
        if (tmp[slot].x0[i] != 0) {
            if (do_call) {
                fn_8016F140(i);
            }
            count++;
        }
    }

    return count;
}

void fn_80174338(void)
{
    lbAudioAx_80024030(1);
}

void fn_8017435C(void)
{
    lbAudioAx_80024030(0);
}

void fn_80174380(void)
{
    lbAudioAx_80024030(2);
}

bool gm_801743A4(enum MatchOutcome outcome)
{
    /// outcome == OUTCOME_LRASTART || outcome == OUTCOME_RETRY?
    if ((u8) (outcome - OUTCOME_LRASTART) <= OUTCOME_TIMEOUT) {
        return true;
    }
    return false;
}

/// #fn_801743C4

/// #fn_80174468

/// #fn_801748EC

void fn_80174920(struct ResultsPlayerData* data)
{
    s32 i;

    for (i = 0; i < 10; i++) {
        if (data->stats_text[0][i] != NULL) {
            HSD_SisLib_803A5CC4(data->stats_text[0][i]);
            data->stats_text[0][i] = NULL;
        }
        if (data->stats_text[1][i] != NULL) {
            HSD_SisLib_803A5CC4(data->stats_text[1][i]);
            data->stats_text[1][i] = NULL;
        }
        if (data->stats_text[2][i] != NULL) {
            HSD_SisLib_803A5CC4(data->stats_text[2][i]);
            data->stats_text[2][i] = NULL;
        }
    }
}

void fn_801749B8(HSD_GObj* unused)
{
    Vec3 sp24;
    Vec3 sp18;
    Vec3 spC;
    u32 temp_r4;

    if (lbl_8046DBE8.cobj != NULL) {
        lbVector_WorldToScreen(lbl_8046DBE8.cobj,
                               &lbl_8046DBE8.player_data[0].stats_position,
                               &sp24, 0);
        lb_8000B1CC(lbl_8046DBE8.player_data[0].jobjs[0xD], NULL, &sp18);
        lbVector_WorldToScreen(lbl_8046DBE8.cobj, &sp18, &spC, 0);
        temp_r4 = (s32) sp24.y & 0xFFFC;
        GXSetScissor(0U, temp_r4, 0x27FU,
                     (u16) ((s32) spC.y & 0xFFDC) - temp_r4);
    }
}

/// #fn_80174A60

/// #fn_80174B4C

void fn_80174FD0(HSD_JObj* jobj, s32 arg1)
{
    HSD_TObj* tobj = jobj->u.dobj->mobj->tobj;

    HSD_AObjSetCurrentFrame(tobj->aobj, (f32) arg1);
    HSD_AObjSetRate(tobj->aobj, 0.0f);
    HSD_TObjAnim(tobj);
}

void fn_80175038(HSD_GObj* gobj, s32 flag)
{
    HSD_JObjDispAll(GET_JOBJ(gobj), NULL, HSD_GObj_80390EB8(flag), 0U);
}

GXColor fn_8017507C(s32 slot)
{
    f32 current_color;
    u8 _[8];
    GXColor color;

    if (lbl_8046DBE8.x94->is_teams == 1) {
        if (lbl_8046DBE8.x94->player_standings[slot].slot_type == Gm_PKind_NA)
        {
            color = gm_80160968(4);
        } else {
            switch (lbl_8046DBE8.x94->player_standings[slot].team) {
            case 0:
                color = gm_80160968(0);
                break;
            case 1:
                color = gm_80160968(1);
                break;
            case 2:
                color = gm_80160968(3);
                break;
            case 3:
                color = gm_80160968(2);
                break;
            default:
                color = gm_80160968(4);
                break;
            }
        }

        current_color = (0.9f * (f32) color.r) + 100.0f;
        if (current_color > 255.0f) {
            current_color = 255.0f;
        }
        color.r = current_color;

        current_color = (0.9f * (f32) color.g) + 100.0f;
        if (current_color > 255.0f) {
            current_color = 255.0f;
        }
        color.g = (s8) current_color;

        current_color = (0.9f * (f32) color.b) + 100.0f;
        if (current_color > 255.0f) {
            current_color = 255.0f;
        }
        color.b = (s8) current_color;
    } else {
        color.r = color.g = color.b = color.a = 0xFF;
    }
    return color;
}

void fn_80175240(s32 slot)
{
    GXColor sp2C;
    GXColor sp30;
    GXColor sp28;
    GXColor sp24;
    GXColor sp20;
    GXColor sp1C;
    GXColor sp18;
    HSD_Text** temp_r31;
    HSD_Text* ko_count;
    MatchEnd* me;
    f32 temp_f31;
    f32 temp_f30;
    s32 temp_r3;
    s32 var_r3;
    s32 var_r5;
    PAD_STACK(16);

    me = lbl_8046DBE8.x94;
    if (me->x5 != 3) {
        /// maybe x4C is an array of Vec2's
        temp_f31 = 1.14f * (lbl_8046DBE8.x4C[4].y - lbl_8046DBE8.x4C[0].y);
        temp_f30 = 1.12f * (lbl_8046DBE8.x4C[5].y - lbl_8046DBE8.x4C[4].y);
        sp30 = fn_8017507C(slot);
        ko_count = HSD_SisLib_803A6754(0, 0);
        ko_count = lbl_8046DBE8.player_data[slot].ko_count;
        ko_count->x0 = lbl_8046DBE8.x4C[slot].x;
        ko_count->x4 = -lbl_8046DBE8.x4C[slot].y - 30.0f;
        ko_count->x8 = lbl_8046DBE8.x4C[slot].z;
        lbl_8046DBE8.player_data[slot].ko_count->x4A = 1;
        lbl_8046DBE8.player_data[slot].ko_count->x49 = 1;
        temp_r31 = &lbl_8046DBE8.player_data[slot].ko_count;
        if (me->player_standings[slot].slot_type != Gm_PKind_NA) {
            var_r3 = fn_8017AE0C(slot);
            if (var_r3 > 0x3E7) {
                var_r3 = 0x3E7;
            }
            temp_r3 = HSD_SisLib_803A6B98(*temp_r31, 0.0f, 0.0f, "%d", var_r3);
            HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
            sp2C = sp30;
            HSD_SisLib_803A74F0(*temp_r31, temp_r3, (u8*) &sp2C);
            var_r5 = fn_8017B010(slot);
            if (var_r5 > 0x3E7) {
                var_r5 = 0x3E7;
            }

            temp_r3 =
                HSD_SisLib_803A6B98(*temp_r31, 0.0f, -temp_f31, "%d", var_r5);
            HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
            sp28 = sp30;
            HSD_SisLib_803A74F0(*temp_r31, temp_r3, (u8*) &sp28);
            var_r5 = fn_8017B21C(slot);
            if (var_r5 > 0x3E7) {
                var_r5 = 0x3E7;
            }
            temp_r3 = HSD_SisLib_803A6B98(*temp_r31, 0.0f,
                                          -temp_f31 - temp_f30, "%d", var_r5);
            HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
            sp24 = sp30;
            HSD_SisLib_803A74F0(*temp_r31, temp_r3, (u8*) &sp24);
            return;
        }
        sp30.r = 0xA0;
        sp30.g = 0xA0;
        sp30.b = 0xA0;
        temp_r3 =
            HSD_SisLib_803A6B98(*temp_r31, 0.0f, 0.0f, "%s", &lbl_804D3FA0);
        HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
        sp20 = sp30;
        HSD_SisLib_803A74F0(*temp_r31, temp_r3, (u8*) &sp20);
        temp_r3 = HSD_SisLib_803A6B98(*temp_r31, 0.0f, -temp_f31, "%s",
                                      &lbl_804D3FA0);
        HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
        sp1C = sp30;
        HSD_SisLib_803A74F0(*temp_r31, temp_r3, (u8*) &sp1C);
        temp_r3 = HSD_SisLib_803A6B98(*temp_r31, 0.0f, -temp_f31 - temp_f30,
                                      "%s", &lbl_804D3FA0);
        HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
        sp18 = sp30;
        HSD_SisLib_803A74F0(*temp_r31, temp_r3, (u8*) &sp18);
    }
}

void fn_8017556C(s32 slot)
{
    MatchEnd* me;
    HSD_Text** ko_time;
    s32 var_r28;
    s32 var_r6;
    GXColor sp10; /* compiler-managed */
    GXColor spC;

    me = lbl_8046DBE8.x94;
    sp10 = fn_8017507C(slot);
    if (me->player_standings[slot].slot_type != Gm_PKind_NA) {
        var_r6 = fn_8017AD28(me->player_standings[slot].score);
        if (var_r6 < 0) {
            if (var_r6 < 0) {
                var_r6 = -var_r6;
            }
            var_r28 = HSD_SisLib_803A6B98(
                lbl_8046DBE8.player_data[slot].ko_time, 0.0f, -30.0f, "%s%d",
                &lbl_804D3FA0, var_r6);
        } else if (var_r6 > 0) {
            var_r28 = HSD_SisLib_803A6B98(
                lbl_8046DBE8.player_data[slot].ko_time, 0.0f, -30.0f, "%s%d",
                &lbl_804D3FA4, var_r6);
        } else {
            var_r28 =
                HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time,
                                    0.0f, -30.0f, "%d", var_r6);
        }
    } else {
        sp10.r = 0xA0;
        sp10.g = 0xA0;
        sp10.b = 0xA0;
        var_r28 = HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time,
                                      0.0f, -30.0f, "%s", &lbl_804D3FA0);
    }
    ko_time = &lbl_8046DBE8.player_data[slot].ko_time;
    HSD_SisLib_803A7548(*ko_time, var_r28, 0.11f, 0.08f);
    spC = sp10;
    HSD_SisLib_803A74F0(*ko_time, var_r28, (u8*) &spC);
}

/// #fn_801756E0

/// #fn_80175880

/// #fn_80175A94

void fn_80175C5C(void)
{
    s32 i;
    u8 _[4];
    Vec3 position;
    PAD_STACK(4);

    lb_8000B1CC(lbl_8046DBE8.x24, NULL, &position);
    for (i = 0; i < 6; i++) {
        lb_8000B1CC(lbl_8046DBE8.x34[i], NULL, &lbl_8046DBE8.x4C[i]);
    }

    lbl_8046DBE8.xC = lbl_8046DBE8.x4C[0].y - position.y;
    HSD_SisLib_803A6754(0, 0);
    HSD_SisLib_803A6754(0, 0);
    for (i = 0; i < 4; i++) {
        fn_80175A94(i, &position);
        fn_80175240(i);
    }
}

void fn_80175D34(void)
{
    u8 _[12];
    Vec3 pos;
    HSD_Text* ko_count;
    HSD_Text* ko_time;
    s32 i;
    PAD_STACK(8); // TODO :: why does this have so much stack space

    lb_8000B1CC(lbl_8046DBE8.x24, NULL, &pos);

    for (i = 0; i < 4; i++) {
        if (lbl_8046DBE8.player_data[i].ko_count != NULL) {
            HSD_SisLib_803A5CC4(lbl_8046DBE8.player_data[i].ko_count);
            lbl_8046DBE8.player_data[i].ko_count = NULL;
        }

        ko_time = lbl_8046DBE8.player_data[i].ko_time;
        if (ko_time != NULL) {
            ko_time->x4 = -pos.y;
        }
    }
}

/// #fn_80175DC8

void fn_80176A6C(void)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;

    gobj = GObj_Create(0x13U, 0x14U, 0U);
    if (gobj == NULL) {
        OSReport("Error : gobj dont\'t get (gmResultAddPanelCamera)\n");
        HSD_ASSERT(0x662, 0);
    }

    cobj = HSD_CObjLoadDesc(lbl_8046DBE8.pnlsce->cameras->desc);
    if (cobj == NULL) {
        OSReport("Error : cobj dont\'t get (gmResultAddPanelCamera)\n");
        HSD_ASSERT(0x668, 0);
    }

    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 8U);
    if ((lbl_8046DBE8.x0 >> 2U) & 1) {
        gobj->gxlink_prios = 1;
    } else {
        gobj->gxlink_prios = 0x4D81;
    }

    HSD_SisLib_803A611C(0, gobj, 9U, 0xDU, 0U, 0xEU, 0U, 0x13U);
    if (lbLang_IsSavedLanguageUS() != 0) {
        HSD_SisLib_803A62A0(0, "SdRst.usd", "SIS_ResultData");
    } else {
        HSD_SisLib_803A62A0(0, "SdRst.dat", "SIS_ResultData");
    }
    lbl_8046DBE8.cobj = cobj;
}

void fn_80176BCC(HSD_GObj* gobj)
{
    HSD_JObjAnimAll((HSD_JObj*) gobj->hsd_obj);
}

/// #fn_80176BF0

void fn_80176D18(HSD_GObj* gobj)
{
    HSD_JObjAnimAll((HSD_JObj*) gobj->hsd_obj);
}

/// #fn_80176D3C

/// #fn_80176F60

/// #fn_801771C0

/// #gm_80177368_OnEnter

void gm_80177704_OnLeave(void* unused)
{
    fn_801701AC();
}

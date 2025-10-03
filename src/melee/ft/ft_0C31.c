#include "ft_0C31.h"

#include "ft_081B.h"
#include "ft_0852.h"
#include "ftcommon.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/types.h"
#include "ft/ftcolanim.h"
#include "ef/efasync.h"
#include "lb/lbaudio_ax.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_DownBound.h"
#include "ftCommon/types.h"
#include "it/it_26B1.h"
#include "it/items/itgreatfoxlaser.h"
#include "it/items/itleadead.h"
#include "it/items/itlikelike.h"
#include "pl/player.h"

#include <dolphin/mtx.h>
#include <baselib/dobj.h>
#include <baselib/jobj.h>

/* 0C63BC */ static void fn_800C63BC(Fighter_GObj* gobj);
/* 0C63E0 */ static void fn_800C63E0(Fighter_GObj* gobj);
/* 0C74CC */ static void fn_800C74CC(Fighter_GObj* gobj);
/* 0C7568 */ void fn_800C7568(Fighter_GObj* gobj);
/* 0C7890 */ void fn_800C7890(Fighter_GObj* gobj);

void ftCo_800C61B0(Fighter_GObj* gobj)
{
    Fighter* fp;
    HSD_JObj* jobj;

    fp = GET_FIGHTER(gobj);
    jobj = GET_JOBJ(gobj);

    fp->mv.co.entry.timer = Player_GetUnk4C(fp->player_id);

    HSD_JObjGetScale(jobj, &fp->mv.co.entry.x8);
    fp->mv.co.entry.x14.x = fp->mv.co.entry.x8.x;
    fp->mv.co.entry.x14.y = p_ftCommonData->x6C4;
    fp->mv.co.entry.x14.z = fp->mv.co.entry.x8.z;
    HSD_JObjSetScale(jobj, &fp->mv.co.entry.x14);

    fp->mv.co.common.x4 = fp->cur_pos.y;
    Fighter_ChangeMotionState(gobj, ftCo_MS_Entry, 0, 0.0F, 1.0F, 0.0F, NULL);
    fp->invisible = true;
    fp->x2219_b1 = true;
    fp->x221E_b1 = true;
    fp->x221E_b2 = true;
    fp->x221F_b1 = true;
    ft_80084CB0(fp, &fp->mv.co.entry.x2C);
}

void ftCo_Entry_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.entry.timer == 0) {
        ftCo_800C6408(gobj);
    }
    --fp->mv.co.entry.timer;
}

void ftCo_Entry_IASA(Fighter_GObj* gobj) {}

void ftCo_Entry_Phys(Fighter_GObj* gobj) {}

void fn_800C63BC(Fighter_GObj* gobj)
{
    ftCommon_8007D7FC(GET_FIGHTER(gobj));
}

void fn_800C63E0(Fighter_GObj* gobj)
{
    ftCommon_8007D5D4(GET_FIGHTER(gobj));
}

void ftCo_Entry_Coll(Fighter_GObj* gobj) {}

void ftCo_800C6408(Fighter_GObj* gobj)
{
    Vec3 sp48;

    Fighter* temp_r29_3;
    Fighter* temp_r31;
    f32 temp_f0;
    f32 temp_f0_2;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;

    Quaternion sp2C;
    Vec3 sp20;

    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    Fighter* fp;

    temp_r31 = GET_FIGHTER(gobj);
    temp_r31->mv.co.entry.timer = p_ftCommonData->x6BC;
    Fighter_ChangeMotionState(gobj, ftCo_MS_EntryStart, 0, 0.0F, 1.0F, 0.0F, NULL);
    temp_r31->x2219_b1 = true;
    if (!temp_r31->x221F_b4) {
        ftCommon_SetAccessory(temp_r31, Fighter_804D6514);
        temp_f0 = temp_r31->x34_scale.y * temp_r31->co_attrs.trophy_scale;
        sp48.z = temp_f0;
        sp48.y = temp_f0;
        sp48.x = temp_f0;
        temp_r31->mv.co.entry.x24 = temp_f0;

        HSD_JObjSetScale(temp_r31->x20A0_accessory, &sp48);

        sp2C.w = 0.0F;
        sp2C.z = 0.0F;
        sp2C.x = 0.0F;
        sp2C.y = 1.5707963267948966 * temp_r31->facing_dir;

        HSD_JObjSetRotation(temp_r31->x20A0_accessory, &sp2C);

        temp_f0_2 = 1.497345 * sp48.y;
        temp_r31->mv.co.entry.x28 = temp_f0_2;
        temp_r31->mv.co.entry.x20 = temp_f0_2;
        temp_r29_3 = gobj->user_data;
        sp20.x = -(temp_r29_3->facing_dir * ftCommon_800804EC(temp_r29_3) - temp_r29_3->cur_pos.x);
        sp20.y = temp_r29_3->cur_pos.y;
        sp20.z = temp_r29_3->cur_pos.z;

        HSD_JObjSetTranslate(temp_r29_3->x20A0_accessory, &sp20);
    }
    temp_r31->accessory1_cb = fn_800C69F4;

    fp = GET_FIGHTER(gobj);
    efAsync_Spawn(gobj, &fp->x60C, 3, 0x43E, gobj->hsd_obj, &temp_r31->mv.co.entry.x8);
    lbAudioAx_80024304(0x8B);
    ftCo_800BFFD0(temp_r31, 0x75, 0);
}

void ftCo_EntryStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    --fp->mv.co.entry.timer;
    if (fp->mv.co.entry.timer == 0) {
        ftCo_800C6B6C(gobj);
    }
}

void ftCo_EntryStart_IASA(Fighter_GObj* gobj) {}

void ftCo_EntryStart_Phys(Fighter_GObj* gobj)
{
    Vec3 sp20;

    Fighter* temp_r31;
    f32 temp_f1;
    f32 temp_f31;
    f32 temp_f4;
    int temp_r6;
    int var_r3;
    int var_r3_2;
    u32 temp_r4;

    temp_r31 = GET_FIGHTER(gobj);
    temp_r6 = p_ftCommonData->x6BC;
    temp_f4 = p_ftCommonData->x6C4;
    temp_f31 = (f32) (temp_r6 - temp_r31->mv.co.entry.timer) / temp_r6;
    temp_r31->mv.co.entry.x14.y = (temp_f31 * (temp_r31->mv.co.entry.x8.y - temp_f4)) + temp_f4;

    HSD_JObjSetScale(gobj->hsd_obj, &temp_r31->mv.co.entry.x14);

    if (!temp_r31->x221F_b4) {
        temp_f1 = temp_r31->mv.co.entry.x24;
        sp20.x = temp_f1;
        sp20.y = temp_f1 * temp_f31;
        sp20.z = temp_f1;
        HSD_JObjSetScale(temp_r31->x20A0_accessory, &sp20);
        temp_r31->mv.co.entry.x28 = temp_r31->mv.co.entry.x20 * temp_f31;
        temp_r31->cur_pos.y = temp_r31->mv.co.entry.x4 + temp_r31->mv.co.entry.x28;
    } else {
        Fighter_GObj* gobj = Player_GetEntityAtIndex(temp_r31->player_id, 0);
        temp_r31->cur_pos.y = GET_FIGHTER(gobj)->cur_pos.y;
    }
}

void ftCo_EntryStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (!fp->x221F_b4) {
        fp->mv.co.entry.x2C.bottom = -fp->mv.co.entry.x28;
    } else {
        HSD_GObj* gobj = Player_GetEntityAtIndex(fp->player_id, 0);
        Fighter* fp2 = GET_FIGHTER(gobj);
        fp->mv.co.entry.x2C.bottom = -fp2->mv.co.entry.x28;
    }
    if (fp->ground_or_air == GA_Air) {
        ft_80083E64(gobj, &fp->mv.co.entry.x2C, fn_800C63BC);
    } else {
        ft_800846B0(gobj, &fp->mv.co.entry.x2C, fn_800C63E0);
    }
}

// you have to ask the compiler nicely for it to work
static inline void ftCo_800C6AFC_please_dontinline(HSD_JObj* jobj)
{
    ftCo_800C6AFC(jobj);
}

static inline void ftCo_800C6AFC_dontinline(HSD_JObj* jobj)
{
    ftCo_800C6AFC_please_dontinline(jobj);
}

// @todo figure out proper inlining for this function
inline void fake_HSD_JObjSetTranslate(HSD_JObj* jobj, Vec3* translate)
{
#undef __FILE__
#define __FILE__ "jobj.h"
    HSD_ASSERT(916, jobj);
    HSD_ASSERT(917, translate);
    jobj->translate = *translate;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC_dontinline(jobj);
    }
}

void fn_800C69F4(Fighter_GObj* gobj)
{
    u8 _[8];
    Vec3 sp20;
    Fighter* temp_r31;
    Fighter* temp_r31_2;
    HSD_GObj* temp_r3;
    Fighter* temp_r3_2;

    temp_r31 = GET_FIGHTER(gobj);
    if (!temp_r31->x221F_b4) {
        temp_r3 = Player_GetEntityAtIndex((s32) temp_r31->player_id, 1);
        if (temp_r3 != NULL) {
            temp_r3_2 = GET_FIGHTER(temp_r3);
            if (!temp_r3_2->x221F_b3) {
                if (temp_r3_2->cur_pos.y > temp_r31->cur_pos.y) {
                    temp_r31->cur_pos.y = temp_r3_2->cur_pos.y;
                }
            }
        }
        temp_r31_2 = GET_FIGHTER(gobj);
        sp20.x = -(temp_r31_2->facing_dir * ftCommon_800804EC(temp_r31_2) - temp_r31_2->cur_pos.x);
        sp20.y = temp_r31_2->cur_pos.y;
        sp20.z = temp_r31_2->cur_pos.z;
        fake_HSD_JObjSetTranslate(temp_r31_2->x20A0_accessory, &sp20);
    } else {
        HSD_GObj* gobj = Player_GetEntityAtIndex(temp_r31->player_id, 0);
        Fighter* fp2 = GET_FIGHTER(gobj);
        temp_r31->cur_pos.y = fp2->cur_pos.y;;
    }
}

void ftCo_800C6AFC(HSD_JObj* jobj)
{
    if (jobj == NULL || HSD_JObjMtxIsDirty(jobj)) {
        return;
    }
    HSD_JObjSetMtxDirtySub(jobj);
}

void ftCo_800C6B6C(Fighter_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    temp_r31->mv.co.entry.timer = p_ftCommonData->x6C0;

    HSD_JObjSetScale(GET_JOBJ(gobj), &temp_r31->mv.co.entry.x8);

    if (!temp_r31->x221F_b4) {
        temp_r31->cur_pos.y = temp_r31->mv.co.entry.x4 + temp_r31->mv.co.entry.x20;
    } else {
        HSD_GObj* gobj2 = Player_GetEntityAtIndex(temp_r31->player_id, 0);
        Fighter* fp2 = GET_FIGHTER(gobj2);
        temp_r31->cur_pos.y = fp2->cur_pos.y;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_EntryEnd, 0x3000, 0.0F, 1.0F, 0.0F, NULL);
    temp_r31->x2219_b1 = true;
    temp_r31->accessory1_cb = fn_800C6F34;
}

void ftCo_EntryEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    --fp->mv.co.entry.timer;
    if (fp->mv.co.entry.timer == 0) {
        if (Player_GetFlagsBit4(fp->player_id)) {
            ftColl_8007B760(gobj, p_ftCommonData->x6C8);
        }
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_EntryEnd_IASA(Fighter_GObj* gobj) {}

void ftCo_EntryEnd_Phys(Fighter_GObj* gobj)
{
    Vec3 sp1C;
    Fighter* fp;
    f32 temp_f31;
    f32 temp_f3;
    u32 temp_r4;

    fp = GET_FIGHTER(gobj);
    if (!fp->x221F_b4) {
        temp_f31 = (f32) fp->mv.co.entry.timer / (f32) p_ftCommonData->x6BC;
        temp_f3 = fp->mv.co.entry.x24;
        sp1C.x = temp_f3;
        sp1C.y = temp_f3 * temp_f31;
        sp1C.z = temp_f3;
        HSD_JObjSetScale(fp->x20A0_accessory, &sp1C);
        fp->mv.co.entry.x28 = fp->mv.co.entry.x20 * temp_f31;
        fp->cur_pos.y = fp->mv.co.entry.x4 + fp->mv.co.entry.x28;
    } else {
        HSD_GObj* gobj2 = Player_GetEntityAtIndex(fp->player_id, 0);
        Fighter* fp2 = GET_FIGHTER(gobj2);
        fp->cur_pos.y = fp2->cur_pos.y;
    }
}

void ftCo_EntryEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4);
    if (!fp->x221F_b4) {
        fp->mv.co.entry.x2C.bottom = -fp->mv.co.entry.x28;
    } else {
        HSD_GObj* gobj2 = Player_GetEntityAtIndex(fp->player_id, 0);
        Fighter* fp2 = GET_FIGHTER(gobj2);
        fp->mv.co.entry.x2C.bottom = -fp2->mv.co.entry.x28;
    }
    if (fp->ground_or_air == GA_Air) {
        ft_80083E64(gobj, &fp->mv.co.entry.x2C, fn_800C63BC);
    } else {
        ft_800846B0(gobj, &fp->mv.co.entry.x2C, fn_800C63E0);
    }
}

void fn_800C6F34(Fighter_GObj* gobj)
{
    Fighter* fp;
    Fighter_GObj* temp_r3;
    Fighter* temp_r3_2;
    u8 _[8];
    Vec3 sp20;

    fp = GET_FIGHTER(gobj);
    if (!fp->x221F_b4) {
        temp_r3 = Player_GetEntityAtIndex(fp->player_id, 1);
        if (temp_r3 != NULL) {
            temp_r3_2 = GET_FIGHTER(temp_r3);
            if (!temp_r3_2->x221F_b3) {
                if (temp_r3_2->cur_pos.y > fp->cur_pos.y) {
                    fp->cur_pos.y = temp_r3_2->cur_pos.y;
                }
            }
        }
        fp = GET_FIGHTER(gobj);
        sp20.x = -((fp->facing_dir * ftCommon_800804EC(fp)) - fp->cur_pos.x);
        sp20.y = fp->cur_pos.y;
        sp20.z = fp->cur_pos.z;

        fake_HSD_JObjSetTranslate(fp->x20A0_accessory, &sp20);
    } else {
        HSD_GObj* gobj2 = Player_GetEntityAtIndex(fp->player_id, 0);
        Fighter* fp2 = GET_FIGHTER(gobj2);
        fp->cur_pos.y = fp2->cur_pos.y;
    }
}

void ftCo_800C703C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->xA4_unk_vel.x = fp->self_vel.x;
    fp->xA4_unk_vel.y = p_ftCommonData->x6D0;
    fp->xA4_unk_vel.z = 0;
    fp->dmg.x1948 = fp->dmg.x194C = p_ftCommonData->x6CC;
}

/// @todo #ftCo_800C6150
void ftCo_800C7070(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_RebirthWait, 0, 0, 1, 0, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}

static inline void inlineB0(Fighter_GObj* gobj)
{
    ftCo_800C7070(gobj);
}

static inline void inlineB1(Fighter_GObj* gobj)
{
    inlineB0(gobj);
}

static inline void inlineB2(Fighter_GObj* gobj)
{
    inlineB1(gobj);
}

void ftCo_800C70D0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_MotionState ms;
    if (fp->kind == FTKIND_MARIO) {
        ms = ftCo_MS_Wait;
    } else if (fp->kind == FTKIND_LUIGI) {
        ms = ftCo_MS_Wait;
    } else {
        inlineB2(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, ms, 0, 0.0F, 1.0F, 0.0F, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}

void ftCo_800C7158(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}

void ftCo_800C7178(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_MotionState ms;
    if (fp->kind == FTKIND_MARIO) {
        ms = ftCo_MS_WalkSlow;
    } else if (fp->kind == FTKIND_LUIGI) {
        ms = ftCo_MS_WalkSlow;
    } else {
        inlineB2(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, ms, 0, 0.0F, 1.0F, 0.0F, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}

void ftCo_800C7200(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}

void ftCo_800C7220(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind != FTKIND_KIRBY) {
        inlineB2(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_Wait, 0, 0, 1, 0, NULL);
        fp->x2219_b2 = true;
        fp->x2219_b1 = true;
    }
}

void ftCo_800C7294(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind != FTKIND_KIRBY) {
        inlineB2(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_WalkSlow, 0, 0, 1, 0, NULL);
        fp->x2219_b2 = true;
        fp->x2219_b1 = true;
    }
}

void ftCo_800C7308(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind != FTKIND_KIRBY) {
        inlineB2(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_WalkMiddle, 0, 0, 1, 0, NULL);
        fp->x2219_b2 = true;
        fp->x2219_b1 = true;
    }
}

void ftCo_800C737C(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}

void ftCo_800C739C(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C7414(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}

static inline void inlineC0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0xE, 0, 0, 1, 0, NULL);
    fp->x2219_b1 = true;
    fp->x2219_b2 = true;
}

static inline void inlineC1(Fighter_GObj* gobj)
{
    inlineC0(gobj);
}

static inline void inlineC2(Fighter_GObj* gobj)
{
    inlineC1(gobj);
}

void ftCo_800C7434(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind == FTKIND_GKOOPS) {
        inlineC2(gobj);
    } else {
        inlineB2(gobj);
    }
}

void ftCo_800C74AC(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}

void fn_800C74CC(Fighter_GObj* gobj)
{
    it_802EADD8(GET_FIGHTER(gobj)->mv.co.captureleadead.x0);
}

bool ftCo_800C74F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x1860_element == 16 && fp->capture_timer == 0 &&
        fp->motion_id != ftCo_MS_CaptureLeadead &&
        it_802EAF28(fp->dmg.x1868_source) == NULL)
    {
        ftCo_800C7590(gobj);
        return true;
    }
    return false;
}

void fn_800C7568(Fighter_GObj* gobj)
{
    it_802EADD8(GET_FIGHTER(gobj)->mv.co.captureleadead.x0);
}

void ftCo_800C7590(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_CaptureLeadead_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->grab_timer -= p_ftCommonData->x734;
    ftCommon_GrabMash(fp, p_ftCommonData->x738);
    if (fp->grab_timer <= 0.0F) {
        it_802EAE80(fp->mv.co.captureleadead.x0);
        ftCo_800C7800(gobj);
    }
}

void ftCo_CaptureLeadead_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureLeadead_Phys(Fighter_GObj* gobj) {}

static void fn_800C77E0(Fighter_GObj* arg0)
{
    ftCo_80090780(arg0);
}

void ftCo_CaptureLeadead_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800C77E0);
}

void ftCo_800C7800(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        fp->gr_vel = -fp->facing_dir * p_ftCommonData->x370;
    } else {
        fp->self_vel.x = -fp->facing_dir * p_ftCommonData->x370;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureCut, 0, 0.0F, 1.0F, 0.0F, NULL);
    fp->capture_timer = p_ftCommonData->x73C;
}

void fn_800C7890(Fighter_GObj* gobj)
{
    ftCo_800C7A30(gobj);
}

UNK_RET ftCo_800C78B0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C7A30(Fighter_GObj* gobj)
{
    it_802DBA68(GET_FIGHTER(gobj)->mv.co.capturelikelike.x0);
}

void ftCo_CaptureLikelike_Anim(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_CaptureLikelike_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureLikelike_Phys(Fighter_GObj* gobj) {}

void ftCo_CaptureLikelike_Coll(Fighter_GObj* gobj) {}

void fn_800C7AE0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_8026B294(fp->mv.co.captureleadead.x0, &fp->cur_pos);
}

UNK_RET ftCo_800C7B0C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C7C60(Fighter_GObj* gobj, int damage_amount)
{
    Fighter_TakeDamage_8006CC7C(GET_FIGHTER(gobj), damage_amount);
}

bool ftCo_800C7CA0(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_DownReflect_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80090780(gobj);
    }
}

void ftCo_DownReflect_IASA(Fighter_GObj* gobj) {}

void ftCo_DownReflect_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_DownReflect_Coll(Fighter_GObj* gobj)
{
    if (ft_80081DD4(gobj)) {
        ftCo_80097D88(gobj);
    }
}

void ftCo_800C8064(void)
{
    HSD_DObj* temp_r3;
    HSD_MObj* var_r0;

    temp_r3 = HSD_JObjGetDObj(HSD_JObjLoadJoint(Fighter_804D6504));
    if (temp_r3 != NULL) {
        var_r0 = temp_r3->mobj;
    } else {
        var_r0 = NULL;
    }
    ft_804D6580 = var_r0;
}

/// @todo maybe uses a shared inline with ftmetal functions?
void ft_800C80A4(Fighter* fp)
{
    size_t i;
    int idx;

    for (i = idx = 0; i < ftPartsTable[fp->kind]->parts_num; idx++, i++) {
        FighterBone* bone = &fp->parts[idx];
        if (bone->flags_b1) {
            HSD_JObj* jobj = bone->joint;
            HSD_DObj* dobj = HSD_JObjGetDObj(jobj);
            HSD_JObjSetFlags(jobj, JOBJ_LIGHTING | JOBJ_TEXGEN |
                                       JOBJ_SPECULAR | JOBJ_UNK_B18);
            HSD_JObjClearFlags(jobj, JOBJ_UNK_B19 | JOBJ_UNK_B20);
            while (dobj != NULL) {
                HSD_DObj* cur;
                HSD_DObjModifyFlags(dobj, 2, 0xE);
                if (dobj != NULL) {
                    cur = dobj->next;
                } else {
                    cur = NULL;
                }
                dobj = cur;
            }
        }
    }
}

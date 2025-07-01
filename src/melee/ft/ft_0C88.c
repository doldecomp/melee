#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft/ft_0C88.h"

#include "math.h"
#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0CEE.h"
#include "ft/ft_0D14.h"
#include "ft/ftchangeparam.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftlib.h"
#include "ft/ftmetal.h"
#include "ft/ftparts.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_AirCatch.h"
#include "ftCommon/ftCo_Attack1.h"
#include "ftCommon/ftCo_AttackAir.h"
#include "ftCommon/ftCo_AttackDash.h"
#include "ftCommon/ftCo_AttackHi3.h"
#include "ftCommon/ftCo_AttackHi4.h"
#include "ftCommon/ftCo_AttackLw3.h"
#include "ftCommon/ftCo_AttackLw4.h"
#include "ftCommon/ftCo_AttackS3.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_DownBound.h"
#include "ftCommon/ftCo_Escape.h"
#include "ftCommon/ftCo_EscapeAir.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_HammerFall.h"
#include "ftCommon/ftCo_HammerJump.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Lift.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftCommon/ftCo_SpecialS.h"
#include "ftCrazyHand/ftCh_Init.h"
#include "ftMasterHand/ftMh_Damage_0.h"
#include "ftMasterHand/ftMh_Wait1_2.h"
#include "ftPeach/ftPe_Float.h"
#include "gm/gm_1601.h"
#include "it/items/ittarucann.h"
#include "lb/lbbgflash.h"
#include "lb/lbrefract.h"
#include "pl/player.h"

#include <baselib/gobj.h>

/* 0C8E74 */ static void fn_800C8E74(Fighter_GObj* gobj);
/* 0C9198 */ static void ftCo_Barrel_Take_Dmg_Cb(Fighter_GObj* gobj);
/* 0C9264 */ static void ftCo_Barrel_Accessory1_Cb(Fighter_GObj* gobj);
/* 0C9528 */ void ftCo_Walk_Enter(Fighter_GObj* gobj, f32 arg8);
/* 0C98AC */ void ftCo_Turn_Enter_Basic(Fighter_GObj* gobj);
/* 0C9C2C */ static bool fn_800C9C2C(Fighter_GObj* gobj);
/* 0C9D94 */ static void ftCo_TurnRun_Enter(Fighter_GObj* gobj,
                                            float anim_start);
/* 0CA644 */ static bool fn_800CA644(ftCo_GObj* gobj);
/* 0CABC4 */ static bool ftCo_RunBrake_CheckInput(ftCo_GObj* gobj);
/* 0CAC18 */ static void ftCo_RunBrake_Enter(ftCo_GObj* gobj);
/* 0CAF78 */ static bool fn_800CAF78(ftCo_GObj* gobj);
/* 0CB4E0 */ static void ftCo_KneeBend_Enter(ftCo_GObj* gobj,
                                             ftCo_JumpInput jump_input);
/* 0CC3C4 */ static void ftYs_JumpAerial_Anim_Cb(ftCo_GObj* gobj);
/* 0CC654 */ static void ftNs_JumpAerial_Phys_Cb(ftCo_GObj* gobj);

void ftCo_800C884C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2040 = HSD_ObjAlloc(&fighter_x2040_alloc_data);
    ftParts_80074148();
    ft_800C85B8(gobj);
    ftParts_80074170();
}

void ftCo_800C88A0(Fighter* fp)
{
    fp->x2226_b4 = false;
    fp->x2226_b5 = false;
    fp->smash_attrs.x2134_vibrateFrame = 0;
    fp->x2030 = 0;
    fp->x2226_b7 = false;
}

static inline void ftCo_800C88D4_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2226_b5 = true;
    fp->x2226_b7 = false;
    fn_800C8B1C(gobj);
    ft_800C80A4(fp);
    lbRefract_80022BB8();
    fp->x221F_b2 = true;
}

void ftCo_800C88D4(Fighter_GObj* gobj, int arg1, bool arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x2030 = arg1;
    if (!fp->x2226_b4 || fp->x2226_b7) {
        fp->x2226_b4 = true;
        ftCo_800C88D4_inline(gobj);

        if (arg2) {
            ftCo_800C8B2C(fp, 0x7C, 0);
        } else {
            ft_800C0098(fp);
        }
    }
}

void ftCo_800C89A0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_800C88A0(fp);
    fp->x2226_b4 = fp->x2226_b3;
    if (fp->x2226_b4) {
        ftCo_800C88D4_inline(gobj);
    }
    ft_800C0098(fp);
}

void ftCo_800C8A64(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x2030 = 0;
    if (!fp->x2226_b3) {
        ftCo_800C88A0(fp);
        ft_800C0098(fp);
        ft_800C8170(fp);
        lbRefract_80022BD0();
        fp->x221F_b2 = false;
    }
}

void ftCo_800C8AF0(Fighter* fp)
{
    if (fp->x2226_b5) {
        lbRefract_800225D4();
    }
}

void fn_800C8B1C(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->smash_attrs.x2134_vibrateFrame = 0;
}

bool ftCo_800C8B2C(Fighter* gobj, int arg1, bool arg2)
{
    if (!gobj->x2226_b6) {
        return ftCo_800BFFD0(gobj, arg1, arg2);
    }
    return false;
}

void ftCo_800C8B60(Fighter* fp, int arg1, s8 arg2)
{
    fp->x2226_b5 = arg1;
    fp->smash_attrs.x2134_vibrateFrame = arg2;
}

void ftCo_DownSpot_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    if (ftData_80085FD4(fp, ftCo_MS_DownSpotU)->x14) {
        msid = ftCo_MS_DownSpotU;
    } else {
        msid = ftCo_MS_DownSpotD;
    }
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->mv._[4] = 0;
}

void ftCo_DownSpot_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80097E8C(gobj);
    }
}

void ftCo_DownSpot_IASA(Fighter_GObj* gobj) {}

void ftCo_DownSpot_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DownSpot_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}

bool ftCo_800C8C84(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2224_b2 && fp->x2225_b7 && fp->dmg.x18F0 == 0 &&
        Player_GetRemainingHPByIndex(fp->player_id, fp->x221F_b4) == 0)
    {
        fn_800C8E74(gobj);
        return true;
    }

    return false;
}

/// #ftCo_800C8D00

/// #fn_800C8E40

static inline void fn_800C8E74_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2224_b2 = true;
    Fighter_ResetInputData_80068854(gobj);
    ftCo_800BFFD0(fp, 0x7A, 0);
    ft_80088148(fp, fp->ft_data->x4C_sfx->xC, SFX_VOLUME_MAX, SFX_PAN_MID);
    fp->x2225_b6 = true;
    lbBgFlash_80021C48(0xEU, 0U);
    gm_80167470(fp->player_id, fp->x221F_b4);
}

void fn_800C8E74(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->kind == FTKIND_MASTERH || fp->kind == FTKIND_CREZYH) {
        if (fp->kind == FTKIND_MASTERH) {
            ftMh_MS_343_80151484(gobj);
        } else {
            ftCh_GrabUnk1_8015ADD0(gobj);
        }
        gm_80167470(fp->player_id, fp->x221F_b4);
        return;
    }

    fp->x2224_b3 = true;
    if (fp->dmg.kb_applied) {
        fn_800C8E74_inline(gobj);
    }
}

void ftCo_800C8F6C(void)
{
    HSD_DObj* dobj = HSD_JObjGetDObj(HSD_JObjLoadJoint(Fighter_804D6504));
    HSD_MObj* mobj;
    HSD_Material* mat;

    if (dobj != NULL) {
        mobj = dobj->mobj;
    } else {
        mobj = NULL;
    }

    ft_804D6588 = mobj;
    mat = mobj->mat;
    if (mat != NULL) {
        mat->diffuse = p_ftCommonData->x7D8;
    }
}

void ftCo_800C8FC4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (Player_GetMoreFlagsBit0(fp->player_id)) {
        fp->x2034 = p_ftCommonData->x7DC;
        fp->x2038 = p_ftCommonData->x7E0;
        fp->x2227_b3 = true;
        ft_800C80A4(fp);
        ftCommon_80080460(fp);
    }
}

void ftCo_800C9034(Fighter_GObj* gobj)
{
    ftCo_800D4F24(gobj, 0);
}

void ftCo_Barrel_Death2_Cb(Fighter_GObj* gobj)
{
    ftCo_Barrel_Take_Dmg_Cb(gobj);
}

void ftCo_Barrel_Enter(Fighter_GObj* gobj, Item_GObj* item_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Barrel, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    fp->death2_cb = ftCo_Barrel_Death2_Cb;
    fp->accessory1_cb = ftCo_Barrel_Accessory1_Cb;
    fp->take_dmg_cb = ftCo_Barrel_Take_Dmg_Cb;
    fp->x221D_b5 = true;
    fp->mv.co.barrel.x0 = it_802960B8(item_gobj);
    fp->mv.co.barrel.x4 = it_802960CC(item_gobj);
    fp->mv.co.barrel.x8 = item_gobj;
    ftCommon_8007D5D4(fp);
    ftCommon_8007E2FC(gobj);
    fp->x1988 = 2;
    fp->x221E_b0 = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007EFC0(fp, 1U);
    ftColl_800787B4(fp->mv.co.barrel.x8, gobj, 0);
}

void ftCo_Barrel_Take_Dmg_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    it_80295F38(fp->mv.co.barrel.x8);
}

void ftCo_Barrel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.co.barrel.x0 != 0) {
        fp->mv.co.barrel.x0 -= 1;
        if (fp->mv.co.barrel.x0 == 0) {
            it_80295F38(fp->mv.co.barrel.x8);
        }
    }
}

void ftCo_Barrel_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.co.barrel.x4 != 0) {
        fp->mv.co.barrel.x4 -= 1;
    }

    if (fp->mv.co.barrel.x4 == 0 && fp->input.x668 & HSD_PAD_AB) {
        it_80295F38(fp->mv.co.barrel.x8);
    }
}

void ftCo_Barrel_Phys(Fighter_GObj* gobj) {}

void ftCo_Barrel_Coll(Fighter_GObj* gobj) {}

void ftCo_Barrel_Accessory1_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    it_8026C334(fp->mv.co.barrel.x8, &fp->cur_pos);
}

void fn_800C9290(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* owner = it_8026BC78(fp->mv.co.barrel.x8);
    if (ftLib_80086960(owner)) {
        ftColl_8007B8CC(fp, owner);
    }
}

/// #ftCo_800C92E4

bool ftCo_Walk_CheckInput(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (ftWalkCommon_800DFC70(gobj)) {
        ftCo_Walk_Enter(gobj, 0.0F);
        return true;
    }
    return false;
}

bool ftCo_Walk_CheckInput_Ottotto(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick.x * fp->facing_dir >= p_ftCommonData->x474 &&
        ftWalkCommon_800DFC70(gobj))
    {
        ftCo_Walk_Enter(gobj, 0.0F);
        return true;
    }
    return false;
}

void ftCo_Walk_Enter(Fighter_GObj* gobj, f32 arg8)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 accel_mul = 1.0F;
    float* anim_vars = &fp->x2DC;

    if (fp->x2223_b7) {
        accel_mul = *Fighter_804D651C;
    }

    if (fp->x34_scale.y != 1.0F) {
        accel_mul = ftCo_CalcYScaledKnockback(
            Fighter_804D6524, accel_mul, fp->x34_scale.y, Fighter_804D6524[3]);
    }
    if ((u32) fp->x197C != NULL) {
        accel_mul *= *Fighter_804D6520;
    }
    ftWalkCommon_800DFCA4(
        gobj, ftCo_MS_WalkSlow, Ft_MF_None, arg8, anim_vars[0], anim_vars[1],
        anim_vars[2], fp->co_attrs.slow_walk_max, fp->co_attrs.mid_walk_point,
        fp->co_attrs.fast_walk_min, accel_mul);
}

void ftCo_Walk_Anim(Fighter_GObj* gobj)
{
    ftWalkCommon_800DFDDC(gobj);
}

void ftCo_Walk_IASA(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    RETURN_IF(ftCo_Attack1_CheckInput(gobj));
    RETURN_IF(ftCo_80091A4C(gobj));
    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(ftCo_Jump_CheckInput(gobj));
    RETURN_IF(ftCo_Dash_CheckInput(gobj));
    RETURN_IF(ftCo_800D5FB0(gobj));
    RETURN_IF(ft_8008A244(gobj));
    ftWalkCommon_800DFEC8(gobj, ftCo_Walk_Enter);
}

void ftCo_Walk_Phys(Fighter_GObj* gobj)
{
    ftWalkCommon_800E0060(gobj);
}

void ftCo_Walk_Coll(Fighter_GObj* gobj)
{
    ft_80084280(gobj);
}

bool ftCo_800C97A8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick.x * fp->facing_dir <= p_ftCommonData->x34) {
        return true;
    }
    return false;
}

bool ftCo_Turn_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_800C97A8(gobj)) {
        ftCo_Turn_Enter_Basic(gobj);
        return true;
    }
    return false;
}

void ftCo_Turn_Enter(Fighter_GObj* gobj, FtMotionId msid, MotionFlags flags,
                     f32 arg3, f32 frames_to_turn, f32 anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.co.turn.has_turned = false;
    fp->mv.co.turn.just_turned = 0;
    fp->mv.co.turn.facing_after = -fp->facing_dir;
    fp->mv.co.turn.frames_to_turn = frames_to_turn;
    fp->mv.co.turn.x8 = arg3;
    fp->mv.co.turn.x1C = 0;
    Fighter_ChangeMotionState(gobj, msid, flags, anim_start, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCo_Turn_Enter_Basic(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float frames = fp->co_attrs.frames_to_change_direction_on_standing_turn;
    PAD_STACK(8);
    ftCo_Turn_Enter(gobj, ftCo_MS_Turn, Ft_MF_None, 0.0F, frames, 0.0F);
}

void ftCo_Turn_Anim_Inner(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.co.turn.frames_to_turn > 0.0F) {
        fp->mv.co.turn.frames_to_turn -= 1.0F;
        return;
    }

    if (!fp->mv.co.turn.has_turned) {
        fp->mv.co.turn.has_turned = true;
        fp->mv.co.turn.just_turned = true;
        fp->facing_dir = -fp->facing_dir;
    }
}

void ftCo_Turn_Anim(Fighter_GObj* gobj)
{
    ftCo_Turn_Anim_Inner(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Turn_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.co.turn.just_turned) {
        fp->input.x668 |= fp->mv.co.turn.x1C;
    }
    if (!fp->mv.co.turn.has_turned) {
        fp->facing_dir = -fp->facing_dir;
    }

    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    RETURN_IF(ftCo_Attack1_CheckInput(gobj));

    if (!fp->mv.co.turn.has_turned) {
        fp->facing_dir = -fp->facing_dir;
    }

    RETURN_IF(ftCo_80091A4C(gobj));
    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(ftCo_Jump_CheckInput(gobj));

    fn_800C9C2C(gobj);
    if (fp->mv.co.turn.just_turned && fp->mv.co.turn.x8) {
        if (fp->input.lstick.x * fp->mv.co.turn.facing_after >=
            p_ftCommonData->x3C)
        {
            ftCo_Dash_Enter(gobj, 0);
        }
    }

    if (fp->input.x668 & HSD_PAD_A) {
        fp->mv.co.turn.x1C |= HSD_PAD_A;
    }

    if (fp->input.x668 & HSD_PAD_B) {
        fp->mv.co.turn.x1C |= HSD_PAD_B;
    }

    if (fp->mv.co.turn.just_turned) {
        fp->mv.co.turn.just_turned = false;
    }
}

void ftCo_Turn_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_Turn_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}

bool fn_800C9C2C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.x * fp->mv.co.turn.facing_after >=
            p_ftCommonData->x3C &&
        fp->x670_timer_lstick_tilt_x < p_ftCommonData->x40)
    {
        fp->mv.co.turn.x8 = fp->mv.co.turn.facing_after;
        return true;
    }
    return false;
}

void ftCo_SmashTurn_Enter(Fighter_GObj* gobj)
{
    Fighter* fp_r7 = GET_FIGHTER(gobj);
    float facing = fp_r7->facing_dir;
    PAD_STACK(1);

    fp_r7->mv.co.turn.has_turned = false;
    fp_r7->mv.co.turn.just_turned = false;
    fp_r7->mv.co.turn.facing_after = -fp_r7->facing_dir;
    fp_r7->mv.co.turn.frames_to_turn = 0.0F;
    fp_r7->mv.co.turn.x8 = facing;
    fp_r7->mv.co.turn.x1C = 0;

    Fighter_ChangeMotionState(gobj, ftCo_MS_Turn, Ft_MF_None, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

bool fn_800C9CEC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.x * fp->facing_dir <=
        p_ftCommonData->x38_someLStickXThreshold)
    {
        ftCo_TurnRun_Enter(gobj, fp->cur_anim_frame);
        return true;
    }
    return false;
}

void ftCo_TurnRun_Enter(Fighter_GObj* gobj, float anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->mv.co.turnrun.accel_mul = fp->facing_dir;
    Fighter_ChangeMotionState(gobj, ftCo_MS_TurnRun, Ft_MF_SkipAnimVel,
                              anim_start, 1.0F, 0.0F, NULL);
    fp->mv.co.turnrun.x14 = 0;
    if (fp->x197C != NULL) {
        ft_80088148(fp, 0x119, 0x7F, 0x40);
    }
}

#pragma push
#pragma dont_inline on
bool fn_800C9D40(Fighter_GObj* gobj)
{
    // We can't use GET_FIGHTER due to dont_inline
    Fighter* fp = gobj->user_data;

    float facing = fp->facing_dir;
    float threshold = p_ftCommonData->x38_someLStickXThreshold;
    float lsx = fp->input.lstick.x;

    if ((lsx * facing) <= threshold) {
        ftCo_TurnRun_Enter(gobj, 0.0F);
        return true;
    }
    return false;
}
#pragma pop

static inline void getAccelAndTarget(Fighter* fp, float* accel,
                                     float* target_vel)
{
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;
    *accel = fp->input.lstick.x * fp->co_attrs.dash_run_acceleration_a;
    *accel += fp->input.lstick.x > 0 ? +co_attrs->dash_run_acceleration_b
                                     : -co_attrs->dash_run_acceleration_b;
    *target_vel = fp->input.lstick.x * co_attrs->dash_run_terminal_velocity;
}

void ftCo_TurnRun_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);

    if (fp->cmd_vars[1] != 0) {
        if (fp->mv.co.turnrun.x14 == 0) {
            ftAnim_SetAnimRate(gobj, 0.0F);
            fp->mv.co.turnrun.x14 = 1;
        } else {
            if ((fp->mv.co.walk.middle_anim_frame * fp->gr_vel) <= 0.01F) {
                ftAnim_SetAnimRate(gobj, 1.0F);
                fp->cmd_vars[1] = 0;
                fp->facing_dir = -fp->facing_dir;
            }
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj) && !fn_800CA644(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_TurnRun_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(fn_800CAF78(gobj));
}

void ftCo_TurnRun_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;
    float accel, target_vel;
    getAccelAndTarget(fp, &accel, &target_vel);

    if (!target_vel) {
        ftCommon_8007C930(fp, co_attrs->gr_friction *
                                  p_ftCommonData->x60_someFrictionMul);
    } else if (fp->mv.co.turnrun.accel_mul * accel < 0) {
        if (accel > 0) {
            if (fp->gr_vel + accel > target_vel) {
                accel -= co_attrs->gr_friction *
                         p_ftCommonData->x60_someFrictionMul;
                if (fp->gr_vel + accel < target_vel) {
                    accel = target_vel - fp->gr_vel;
                }
            }
        } else {
            if (fp->gr_vel + accel < target_vel) {
                accel += co_attrs->gr_friction *
                         p_ftCommonData->x60_someFrictionMul;
                if (fp->gr_vel + accel > target_vel) {
                    accel = target_vel - fp->gr_vel;
                }
            }
        }
        fp->xE4_ground_accel_1 = accel;
    } else {
        ftCommon_8007C930(fp, co_attrs->gr_friction *
                                  p_ftCommonData->x60_someFrictionMul);
    }
    ftCommon_8007CB74(gobj);
}

void ftCo_TurnRun_Coll(Fighter_GObj* gobj)
{
    s32 env_flags;
    bool var_r4;

    if (!ft_800827A0(gobj)) {
        ftCo_800CC730(gobj);
        return;
    }
    var_r4 = true;
    env_flags = GET_FIGHTER(gobj)->coll_data.env_flags;
    if (!(env_flags & MPCOLL_FLAGS_B20) && !(env_flags & MPCOLL_FLAGS_B21)) {
        var_r4 = false;
    }
    if (var_r4) {
        ftCommon_8007E2FC(gobj);
    }
}

#pragma push
#pragma dont_inline on
bool ftCo_Dash_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    float lsx_abs = fp->input.lstick.x;
    if (lsx_abs < 0.0F) {
        lsx_abs = -lsx_abs;
    }

    if ((lsx_abs >= p_ftCommonData->x3C) &&
        ((int) fp->x670_timer_lstick_tilt_x < p_ftCommonData->x40))
    {
        if ((fp->input.lstick.x * fp->facing_dir) < 0.0F) {
            ftCo_SmashTurn_Enter(gobj);
        } else {
            ftCo_Dash_Enter(gobj, 1);
        }
        return true;
    }
    return false;
}
#pragma pop

#pragma push
#pragma dont_inline on
static inline bool ftCo_Dash_CheckInput_inline(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    float var_f1 = fp->input.lstick.x;
    if (var_f1 < 0.0F) {
        var_f1 = -var_f1;
    }

    if ((var_f1 >= p_ftCommonData->x3C) &&
        ((s32) fp->x670_timer_lstick_tilt_x < (s32) p_ftCommonData->x40))
    {
        if ((fp->input.lstick.x * fp->facing_dir) < 0.0F) {
            ftCo_SmashTurn_Enter(gobj);
        } else {
            ftCo_Dash_Enter(gobj, 1);
        }
        return true;
    }
    return false;
}
#pragma pop

void ftCo_Dash_Enter(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 init_vel;
    PAD_STACK(8);

    fp->cmd_vars[0] = 0;

    Fighter_ChangeMotionState(gobj, ftCo_MS_Dash, Ft_MF_None, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->x670_timer_lstick_tilt_x = 0xFE;
    init_vel = fp->facing_dir * fp->co_attrs.dash_initial_velocity;
    if ((fp->gr_vel * fp->facing_dir) < 0.0F) {
        fp->mv.co.dash.x0 = init_vel;
    } else {
        fp->mv.co.dash.x0 = init_vel - fp->gr_vel;
    }
    ftCommon_800804A0(fp, fp->mv.ca.specials.grav);
    fp->mv.co.dash.x4 = arg1;
    if (fp->x197C != NULL) {
        ft_80088148(fp, 0x118, 0x7F, 0x40);
    }
}

void ftCo_Dash_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Dash_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->mv.co.dash.x4 != 0) &&
        (fp->cur_anim_frame <= p_ftCommonData->x44))
    {
        if (!ftCo_SpecialS_CheckInput(gobj)) {
            if ((fp->item_gobj != NULL) && ftCo_80094E54(fp)) {
                ftCo_800957F4(gobj, ftCo_MS_LightThrowF4);
            } else if (ftCo_800D8A38(gobj)) {
                return;
            } else {
                if (!ftCo_AttackS4_8008C114(gobj)) {
                    if (!(fp->cur_anim_frame <= p_ftCommonData->x48 &&
                          ftCo_80099264(gobj)))
                    {
                        goto block_42;
                    }
                }
            }
        }
    } else if (fp->cur_anim_frame <= p_ftCommonData->x4C) {
        if (!ftCo_SpecialS_CheckInput(gobj)) {
            RETURN_IF(ftCo_800D8A38(gobj));
            if (ftCo_AttackDash_CheckInput(gobj)) {
                ftCo_AttackDash_SetMv0(gobj);
                return;
            }
            if (!(fp->input.lstick.x * fp->facing_dir < 0.0F) ||
                !ftCo_Dash_CheckInput_inline(gobj))
            {
                if (ftCo_80091AD8(gobj, (s32) (p_ftCommonData->x4C -
                                               fp->cur_anim_frame)))
                {
                } else {
                    goto block_42;
                }
            }
        }
    } else {
        RETURN_IF(ftCo_800D8A38(gobj));
        if (!ftCo_Dash_CheckInput_inline(gobj)) {
            if (ftCo_80091A4C(gobj)) {
                ftCo_80091B9C(gobj);
            } else {
            block_42:
                if (!ftCo_800DE9D8(gobj)) {
                    RETURN_IF(fn_800CAF78(gobj));
                    RETURN_IF(!fp->cmd_vars[0]);
                    RETURN_IF(fn_800CA5F0(gobj));
                    return;
                }
            }
        }
    }

    {
        float friction = ft_GetGroundFrictionMultiplier(fp);
        float temp_f0 = fp->gr_vel * p_ftCommonData->x54;
        fp->gr_vel += -temp_f0 * friction;
    }
}

void ftCo_Dash_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(1);

    if (fp->mv.co.dash.x0) {
        fp->mv.co.dash.x0 = 0;
    } else {
        ftCo_DatAttrs* attrs = &fp->co_attrs;
        float accel, target_vel;
        getAccelAndTarget(fp, &accel, &target_vel);
        ftCommon_8007C98C(fp, accel, target_vel,
                          attrs->gr_friction *
                              p_ftCommonData->x60_someFrictionMul);
    }
    ftCommon_8007CB74(gobj);
}

void ftCo_Dash_Coll(Fighter_GObj* gobj)
{
    ft_800844EC();
}

bool fn_800CA5F0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick.x * fp->facing_dir >=
        p_ftCommonData->x58_someLStickXThreshold)
    {
        ftCo_Run_Enter(gobj, 0.0F);
        return true;
    }
    return false;
}

bool fn_800CA644(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.lstick.x * fp->facing_dir) >=
        p_ftCommonData->x58_someLStickXThreshold)
    {
        ftCo_Run_Enter(gobj, p_ftCommonData->x430);
        return true;
    }
    return false;
}

bool fn_800CA698(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.x * fp->facing_dir >=
        p_ftCommonData->x58_someLStickXThreshold)
    {
        ftCo_Run_Enter_Full(gobj, 0.0F, fp->cur_anim_frame,
                            fp->frame_speed_mul);
        return true;
    }
    return false;
}

void ftCo_Run_Enter(Fighter_GObj* gobj, float arg0)
{
    ftCo_Run_Enter_Full(gobj, arg0, 0.0F, 1.0F);
}

void ftCo_Run_Enter_Full(Fighter_GObj* gobj, float arg0, float anim_start,
                         float anim_speed)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Run, Ft_MF_None, anim_start,
                              anim_speed, 0.0F, NULL);
    fp->mv.co.run.x0 = arg0;
    fp->mv.co.run.x4 = fp->gr_vel;
}

void ftCo_Run_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 vel;
    f32 anim_rate;
    PAD_STACK(1);

    if (ft_GetGroundFrictionMultiplier(fp) < 1.0F) {
        vel = fp->mv.co.run.x4;
    } else {
        vel = fp->gr_vel;
    }

    if (vel * fp->facing_dir <= 0.0F) {
        anim_rate = 0.0F;
    } else {
        anim_rate = fabs_inline(vel) / fp->co_attrs.run_animation_scaling;
    }

    ftAnim_SetAnimRate(gobj, anim_rate);
    if (fp->mv.co.run.x0 > 0.0F) {
        fp->mv.co.run.x0 -= 1.0F;
    }
}

void ftCo_Run_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_800D8A38(gobj));

    if (ftCo_AttackDash_CheckInput(gobj)) {
        ftCo_AttackDash_SetMv0(gobj);
        return;
    }

    if (ftCo_80091A4C(gobj)) {
        ftCo_80091B90(gobj, p_ftCommonData->x410);
        ftCo_80091B9C(gobj);
        return;
    }

    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(fn_800CAF78(gobj));

    RETURN_IF((fp->mv.co.run.x0 <= 0.0F) && fn_800C9D40(gobj));
    RETURN_IF(!(fp->mv.co.run.x0 <= 0.0F));
    RETURN_IF(ftCo_RunBrake_CheckInput(gobj));
}

void ftCo_Run_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* attrs = &fp->co_attrs;
    float accel, target_vel;
    getAccelAndTarget(fp, &accel, &target_vel);
    if (target_vel) {
        float gr_frac = fp->gr_vel / target_vel;
        if ((gr_frac > 0.0F) && (gr_frac < 1.0F)) {
            accel *= (1.0F - gr_frac) * p_ftCommonData->x5C;
        }
    }
    fp->mv.co.run.x4 = target_vel * p_ftCommonData->x440;
    ftCommon_8007C98C(fp, accel, target_vel,
                      attrs->gr_friction *
                          p_ftCommonData->x60_someFrictionMul);
    ftCommon_8007CB74(gobj);
}

void ftCo_Run_Coll(Fighter_GObj* gobj)
{
    ft_800844EC();
}

#pragma push
#pragma dont_inline on
void ftCo_RunDirect_Anim(Fighter_GObj* gobj)
{
    ftCo_Run_Anim(gobj);
}
#pragma pop

#pragma push
#pragma dont_inline on
void ftCo_RunDirect_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_800D8A38(gobj));

    if (ftCo_AttackDash_CheckInput(gobj)) {
        ftCo_AttackDash_SetMv0(gobj);
        return;
    }

    if (ftCo_80091A4C(gobj)) {
        ftCo_80091B90(gobj, p_ftCommonData->x410);
        ftCo_80091B9C(gobj);
        return;
    }

    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(fn_800CAF78(gobj));
    RETURN_IF(fp->mv.ca.specials.grav <= 0.0F && fn_800CA698(gobj));
    RETURN_IF(ft_8008A244(gobj));
}
#pragma pop

#pragma push
#pragma dont_inline on
void ftCo_RunDirect_Phys(Fighter_GObj* gobj)
{
    ftCo_Run_Phys(gobj);
}
#pragma pop

#pragma push
#pragma dont_inline on
void ftCo_RunDirect_Coll(Fighter_GObj* gobj)
{
    ftCo_Run_Coll(gobj);
}
#pragma pop

bool ftCo_RunBrake_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float lsx_abs = fp->input.lstick.x;
    if (lsx_abs < 0.0F) {
        lsx_abs = -lsx_abs;
    }
    if (lsx_abs < p_ftCommonData->x58_someLStickXThreshold) {
        ftCo_RunBrake_Enter(gobj);
        return true;
    }
    return false;
}

void ftCo_RunBrake_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(1);

    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    Fighter_ChangeMotionState(gobj, ftCo_MS_RunBrake, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->mv.co.runbrake.x0 = false;
    fp->mv.co.runbrake.frames = fp->co_attrs.max_run_brake_frames;
    if (fp->x197C != NULL) {
        ft_80088148(fp, 0x119, 0x7F, 0x40);
    }
}

void ftCo_RunBrake_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[1]) {
        float maybe_max_vel = p_ftCommonData->x42C;
        if (!fp->mv.co.runbrake.x0) {
            if (fabs_inline(fp->gr_vel) >= maybe_max_vel) {
                ftAnim_SetAnimRate(gobj, 0.0F);
                fp->mv.co.runbrake.x0 = true;
            }
        } else {
            if (fabs_inline(fp->gr_vel) <= maybe_max_vel) {
                ftAnim_SetAnimRate(gobj, 1.0F);
                fp->cmd_vars[1] = 0;
            }
        }
    }

    if (fp->mv.co.runbrake.frames) {
        fp->mv.co.runbrake.frames -= 1.0F;
        if (fp->mv.co.runbrake.frames < 0.0F) {
            fp->mv.co.runbrake.frames = 0.0F;
        }
    }

    if (!(ftAnim_IsFramesRemaining(gobj) && fp->mv.co.runbrake.frames)) {
        ft_8008A2BC(gobj);
    }
}

#pragma push
#pragma dont_inline on
void ftCo_RunBrake_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    RETURN_IF(fn_800CAF78(gobj));
    RETURN_IF(fp->cmd_vars[0] && fn_800C9CEC(gobj));
    RETURN_IF(ftCo_800D5FB0(gobj));
}
#pragma pop

void ftCo_RunBrake_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007C930(fp, p_ftCommonData->x60_someFrictionMul *
                              fp->co_attrs.gr_friction);
    ftCommon_8007CB74(gobj);
}

void ftCo_RunBrake_Coll(Fighter_GObj* gobj)
{
    ft_80084280(gobj);
}

ftCo_JumpInput ftCo_Jump_GetInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->input.lstick.y >= p_ftCommonData->tap_jump_threshold) &&
        (fp->x671_timer_lstick_tilt_y < p_ftCommonData->x74))
    {
        return JumpInput_Stick;
    }

    if (fp->input.x668 & HSD_PAD_XY) {
        return JumpInput_XY;
    }

    return JumpInput_None;
}

bool ftCo_Jump_CheckInput(Fighter_GObj* gobj)
{
    ftCo_JumpInput jump_input;
    if (ftCo_800C5240(gobj) != 0) {
        return ftCo_800C5A50(gobj);
    }

    jump_input = ftCo_Jump_GetInput(gobj);

    if (jump_input) {
        ftCo_KneeBend_Enter(gobj, jump_input);
        return true;
    }
    return false;
}

bool fn_800CAF78(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_800C5240(gobj)) {
        return ftCo_800C5A50(gobj);
    }

    if ((fp->input.lstick.y >= p_ftCommonData->x80) &&
        (fp->x671_timer_lstick_tilt_y < p_ftCommonData->x74))
    {
        ftCo_KneeBend_Enter(gobj, 1);
        return true;
    }

    if (fp->input.x668 & HSD_PAD_XY) {
        ftCo_KneeBend_Enter(gobj, 3);
        return true;
    }
    return false;
}

/// #ftCo_800CB024

/// #ftCo_800CB110

void fn_800CB250(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    ftCommon_8007D5D4(fp);
    msid = (fp->input.lstick.x * fp->facing_dir) > -p_ftCommonData->x78
               ? ftCo_MS_JumpF
               : ftCo_MS_JumpB;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0.0F, 1.0F, 0.0F, NULL);
    ftCo_800CB110(gobj, 1, 1.0F);
    fp->x2227_b0 = true;
}

/// #ftCo_Jump_Anim

void ftCo_Jump_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
    RETURN_IF(ftCo_80095328(gobj, NULL));
    RETURN_IF(ftCo_800D7100(gobj));
    RETURN_IF(ftCo_800C3B10(gobj));
    RETURN_IF(ftCo_80099A58(gobj));
    RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
    RETURN_IF(ftCo_800D705C(gobj));
    RETURN_IF(!(fp->mv.co.jump.x4 == 0) && ftCo_800CEE70(gobj));
    RETURN_IF(!(fp->mv.co.jump.x4 == 0) && ftPe_8011BA54(gobj));
    RETURN_IF(ftCo_800CB870(gobj));
    RETURN_IF(fp->mv.co.jump.x4 == 0);
    RETURN_IF(ftPe_8011BAD8(gobj));
}

/// #ftCo_800CB438

/// #ftCo_Jump_Phys

/// #ftCo_Jump_Coll

void ftCo_KneeBend_Enter(Fighter_GObj* gobj, ftCo_JumpInput jump_input)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.kneebend.jump_input = jump_input;
    fp->mv.co.kneebend.x0 = 0;
    Fighter_ChangeMotionState(gobj, ftCo_MS_KneeBend, 0U, 0.0F, 1.0F, 0.0F,
                              NULL);
}

/// #ftCo_KneeBend_Anim

/// #ftCo_800CB59C

/// #ftCo_KneeBend_IASA

/// #ftCo_KneeBend_Phys

/// #ftCo_KneeBend_Coll

void ft_800CB6EC(Fighter* fp, s32 arg1)
{
    if (fp->mv.co.jumpaerial.x0 != 0) {
        fp->mv.co.jumpaerial.x0 -= 1;
        HSD_JObjAddRotationY(fp->parts->joint,
                             -(deg_to_rad * (180.0F / arg1)));
        if (fp->mv.co.jumpaerial.x0 == (arg1 / 2)) {
            fp->facing_dir = -fp->facing_dir;
        }
    }
}

bool ft_did_jump(Fighter* fp, bool arg1)
{
    if (fp->x1968_jumpsUsed < fp->co_attrs.max_jumps &&
        ((fp->input.lstick.y >= p_ftCommonData->tap_jump_threshold &&
          fp->x671_timer_lstick_tilt_y < p_ftCommonData->x74) ||
         fp->input.x668 & HSD_PAD_XY) &&
        !(arg1 && (fp->x68A < p_ftCommonData->x1C)))
    {
        return true;
    }

    return false;
}

bool ftCo_800CB870(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_800C5240(gobj)) {
        return false;
    }
    if (fp->x2222_b1) {
        return ftCo_800D730C(gobj, false);
    }
    return ftCo_JumpAerial_CheckInput(gobj, false);
}

/// #ftCo_800CB8E0

bool ftCo_JumpAerial_CheckInput(Fighter_GObj* gobj, bool arg1)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    co_attrs = &fp->co_attrs;
    if (ft_did_jump(fp, arg1)) {
        if (ft_800D2D0C(gobj)) {
            Vec3 v;
            PAD_STACK(8);
            v.x = fp->input.lstick.x * co_attrs->air_jump_h_multiplier;
            v.y = co_attrs->jump_v_initial_velocity *
                  co_attrs->air_jump_v_multiplier;
            v.z = 0.0F;
            ft_800D2E7C(gobj, &v);
            return true;
        }
        switch (fp->kind) {
        case FTKIND_NESS:
            ftNs_JumpAerial_Enter(gobj);
            break;
        case FTKIND_YOSHI:
            ftYs_JumpAerial_Enter(gobj);
            break;
        case FTKIND_PEACH:
            ftPe_JumpAerial_Enter(gobj);
            break;
        case FTKIND_MEWTWO:
            ftMt_JumpAerial_Enter(gobj);
            break;
        default:
            ftCo_JumpAerial_Enter_Basic(gobj);
            break;
        }
        return true;
    }
    return false;
}

static inline void ft_SetVec(Vec3* dst, Vec3* src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

static inline void ft_JumpAerial_Sound(Fighter* fp, FighterKind ftkind)
{
    if (ftkind != FTKIND_MEWTWO && (ftkind >= 0x10 || ftkind != FTKIND_NESS) &&
        fp->x197C != NULL)
    {
        ft_80088148(fp, 0x11B, SFX_VOLUME_MAX, SFX_PAN_MID);
    }
}

void ftCo_800CBAC4(Fighter_GObj* gobj, FtMotionId msid, Vec3* vel, bool arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, msid, Ft_MF_SkipNametagVis, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->x2221_b7 = true;
    ft_SetVec(&fp->self_vel, vel);
    if (arg3) {
        fp->x671_timer_lstick_tilt_y = 0xFE;
    }
    fp->x1968_jumpsUsed += 1;
    ft_80088770(fp);
    ft_80088328(fp, fp->ft_data->x4C_sfx->x14, SFX_VOLUME_MAX, SFX_PAN_MID);
    ft_JumpAerial_Sound(fp, fp->kind);
}

void ftCo_JumpAerial_Enter_Basic(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;
    Vec3 vel;
    co_attrs = &fp->co_attrs;
    PAD_STACK(8);

    ftCommon_8007D5D4(fp);
    fp->cmd_vars[0] = 1;
    msid = (fp->input.lstick.x * fp->facing_dir) > -p_ftCommonData->x78
               ? ftCo_MS_JumpAerialF
               : ftCo_MS_JumpAerialB;
    vel.x = fp->input.lstick.x * co_attrs->air_jump_h_multiplier;
    vel.y =
        co_attrs->jump_v_initial_velocity * co_attrs->air_jump_v_multiplier;
    vel.z = 0.0F;
    ftCo_800CBAC4(gobj, msid, &vel, true);
}

void ftNs_JumpAerial_Enter(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs_r31;
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 vel = { 0.0F, 0.0F, 0.0F };
    FtMotionId msid;
    PAD_STACK(4);
    co_attrs_r31 = &fp->co_attrs;

    ftCommon_8007D5D4(fp);
    fp->cmd_vars[0] = 1;
    msid = (fp->input.lstick.x * fp->facing_dir) > -p_ftCommonData->x78
               ? ftCo_MS_JumpAerialF
               : ftCo_MS_JumpAerialB;

    ftCo_800CBAC4(gobj, msid, &vel, true);
    fp->phys_cb = (HSD_GObjEvent) ftNs_JumpAerial_Phys_Cb;
    fp->mv.co.jumpaerial.init_h_vel =
        fp->input.lstick.x * co_attrs_r31->air_jump_h_multiplier;
}

void ftYs_JumpAerial_Enter(Fighter_GObj* gobj)
{
    // mv.co.jumpaerial.x0 could also be mv.ys.jumpaerial.x0
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* ys_attrs = fp->dat_attrs;
    Vec3 vel;
    int arg1;
    PAD_STACK(16);

    ftCommon_8007D5D4(fp);
    fp->cmd_vars[0] = 1;
    vel.x = fp->input.lstick.x * fp->co_attrs.air_jump_h_multiplier;
    vel.y = 0.0F;
    vel.z = 0.0F;
    ftCo_800CBAC4(gobj, ftCo_MS_JumpAerialF, &vel, true);
    fp->phys_cb = (HSD_GObjEvent) ftCo_JumpAerial_Phys_Cb;
    fp->anim_cb = (HSD_GObjEvent) ftYs_JumpAerial_Anim_Cb;
    fp->dmg.armor1 = ys_attrs->x8;
    if ((fp->input.lstick.x * fp->facing_dir) < -ys_attrs->x4) {
        fp->mv.co.jumpaerial.x0 = ys_attrs->x0;
    } else {
        fp->mv.co.jumpaerial.x0 = 0;
    }

    arg1 = ys_attrs->x0;
    ft_800CB6EC(fp, arg1);
}

void ftPe_JumpAerial_Enter(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp_r31 = GET_FIGHTER(gobj);
    FtMotionId msid;
    Vec3 vel;
    co_attrs = &fp_r31->co_attrs;
    PAD_STACK(8);

    ftCommon_8007D5D4(fp_r31);
    fp_r31->cmd_vars[0] = 1;
    msid = (fp_r31->input.lstick.x * fp_r31->facing_dir) > -p_ftCommonData->x78
               ? ftCo_MS_JumpAerialF
               : ftCo_MS_JumpAerialB;
    vel.x = fp_r31->input.lstick.x * co_attrs->air_jump_h_multiplier;
    vel.y = 0.0F;
    vel.z = 0.0F;
    ftCo_800CBAC4(gobj, msid, &vel, true);
    fp_r31->phys_cb = (HSD_GObjEvent) ftCo_JumpAerial_Phys_Cb;
}

void ftMt_JumpAerial_Enter(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co_attrs;
    Fighter* fp_r31 = GET_FIGHTER(gobj);
    FtMotionId msid;
    Vec3 vel;
    co_attrs = &fp_r31->co_attrs;
    PAD_STACK(8);

    ftCommon_8007D5D4(fp_r31);
    fp_r31->cmd_vars[0] = 1;
    msid = (fp_r31->input.lstick.x * fp_r31->facing_dir) > -p_ftCommonData->x78
               ? ftCo_MS_JumpAerialF
               : ftCo_MS_JumpAerialB;
    vel.x = fp_r31->input.lstick.x * co_attrs->air_jump_h_multiplier;
    vel.y = 0.0F;
    vel.z = 0.0F;
    ftCo_800CBAC4(gobj, msid, &vel, true);
    fp_r31->phys_cb = (HSD_GObjEvent) ftCo_JumpAerial_Phys_Cb;
}

void ftCo_JumpAerial_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_FallAerial_Enter(gobj);
    }
}

void ftYs_JumpAerial_Anim_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* ys_attrs = fp->dat_attrs;
    PAD_STACK(8);
    ftCo_JumpAerial_Anim(gobj);
    ft_800CB6EC(fp, ys_attrs->x0);
}

void ftCo_JumpAerial_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
    RETURN_IF(ftCo_80095328(gobj, NULL));
    RETURN_IF(ftCo_800D7100(gobj));
    RETURN_IF(ftCo_800C3B10(gobj));
    RETURN_IF(ftCo_80099A58(gobj));
    RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
    RETURN_IF(ftCo_800D705C(gobj));
    RETURN_IF(ftPe_8011BA54(gobj));
    RETURN_IF(ftCo_800CB870(gobj));
    RETURN_IF(fp->cmd_vars[0] && ftPe_8011BAD8(gobj));
    RETURN_IF(!fp->cmd_vars[0]);
    RETURN_IF(ftCo_800CEE70(gobj));
}

void ftCo_JumpAerial_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftNs_JumpAerial_Phys_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D28C(fp, fp->mv.co.jumpaerial.init_h_vel);
    fp->mv.co.jumpaerial.init_h_vel += fp->x74_anim_vel.x;
    fp->x74_anim_vel.x = 0.0F;
    fp->self_vel.x = fp->x6A4_transNOffset.z * fp->facing_dir +
                     fp->mv.co.jumpaerial.init_h_vel;
    ft_800851D0(gobj);
}

void ftCo_JumpAerial_Phys_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D268(fp);
    ft_800851D0(gobj);
}

void ftCo_JumpAerial_Coll(Fighter_GObj* gobj)
{
    ft_800835B0(gobj, ftCo_80096CC8, (HSD_GObjEvent) ft_80082B1C);
}

static inline bool ftCo_Fall_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2224_b2) {
        ftCo_80090780(gobj);
        return true;
    }

    if (ftCo_800C5240(gobj)) {
        ftCo_800C5D34(gobj);
        return true;
    }

    return false;
}

void ftCo_800CC730(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftLib_800872A4(gobj) == FTKIND_MASTERH) {
        ftMh_MS_389_80151018(gobj);
        return;
    }

    if (ftLib_800872A4(gobj) == FTKIND_CREZYH) {
        ftCh_GrabUnk1_8015BC88(gobj);
        return;
    }

    if (!ftCo_Fall_inline(gobj)) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_Fall, Ft_MF_KeepFastFall, 0.0F,
                                  1.0F, 0.0F, NULL);
        ftCommon_8007D468(fp);
        fp->mv.co.fall.x0 = 20;
        fp->mv.co.fall.x4 = 0.0F;
        if (fp->ground_or_air == GA_Ground) {
            ftCommon_8007D5D4(fp);
        }
    }
}

void ftCo_800CC830(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftCo_Fall_inline(gobj)) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_Fall, Ft_MF_Unk06, 0.0F, 1.0F,
                                  -1.0F, NULL);
        fp->mv.co.fall.x0 = 20;
        fp->mv.co.fall.x4 = 0.0F;
    }
}

void ftCo_800CC8DC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftCo_Fall_inline(gobj)) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_Fall, Ft_MF_Unk06, 0.0F, 1.0F,
                                  -1.0F, NULL);
        fp->mv.co.fall.x0 = 20;
        fp->mv.co.fall.x4 = 0.0F;
    }
}

void ftCo_800CC988(Fighter_GObj* gobj, f32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (arg1) {
        HSD_JObjAnimAll(fp->x8AC_animSkeleton);
        if (arg1 != 1.0F) {
            ftAnim_8006FE9C(fp, 1, arg1, 1.0F - arg1);
        } else {
            ftAnim_8006FF74(fp, 1);
        }
    }
}

void ftCo_Fall_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2228_b2) {
        ftCo_Fall_Anim_Inner(gobj, &fp->mv.co.fall.x4, ftCo_SM_Fall,
                             ftCo_SM_FallF, ftCo_SM_FallB);
        ftCo_800CC988(gobj, fp->mv.co.fall.x4);
    }
}

#pragma push
#pragma dont_inline on
bool ftCo_Fall_IASA_Inner(Fighter_GObj* gobj)
{
    if (ftCo_SpecialAir_CheckInput(gobj)) {
        return true;
    }
    if (ftCo_80095328(gobj, NULL)) {
        return true;
    }
    if (ftCo_800D7100(gobj)) {
        return true;
    }
    if (ftCo_800C3B10(gobj)) {
        return true;
    }
    if (ftCo_80099A58(gobj)) {
        return true;
    }
    if (ftCo_AttackAir_CheckItemThrowInput(gobj)) {
        return true;
    }
    if (ftCo_800D705C(gobj)) {
        return true;
    }
    if (ftCo_800CEE70(gobj)) {
        return true;
    }
    if (ftPe_8011BA54(gobj)) {
        return true;
    }
    if (ftCo_800CB870(gobj)) {
        return true;
    }
    if (ftPe_8011BAD8(gobj)) {
        return true;
    }

    return false;
}
#pragma pop

void ftCo_Fall_Anim_Inner(Fighter_GObj* gobj, f32* arg1,
                          FtMotionId neutral_smid, FtMotionId forwards_smid,
                          FtMotionId backwards_smid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 var_f0;
    f32 air_drift_frac = fp->self_vel.x / fp->co_attrs.air_drift_max;
    f32 air_drift_frac_abs;
    FtMotionId smid;
    PAD_STACK(8);

    // limits air drift to +/- air_drift_max
    if (air_drift_frac > 1.0F) {
        air_drift_frac = 1.0F;
    } else if (air_drift_frac < -1.0F) {
        air_drift_frac = -1.0F;
    }

    air_drift_frac_abs = fabs_inline(air_drift_frac);
    if (air_drift_frac_abs > p_ftCommonData->x444) {
        if (air_drift_frac * fp->facing_dir > 0.0F) {
            smid = forwards_smid;
        } else {
            smid = backwards_smid;
        }
        var_f0 = (air_drift_frac_abs - p_ftCommonData->x444) /
                 (1.0F - p_ftCommonData->x444);
    } else {
        smid = neutral_smid;
        var_f0 = 0.0F;
    }

    *arg1 += p_ftCommonData->x448 * (var_f0 - *arg1);
    if (*arg1 && smid != fp->mv.co.fall.x0) {
        ftAnim_8006EDD0(fp, smid, fp->cur_anim_frame, 1.0F);
        HSD_JObjAnimAll(fp->x8AC_animSkeleton);
        if (*arg1 != 1.0F) {
            ftAnim_8006FE9C(fp, 1, *arg1, 1.0F - *arg1);
        } else {
            ftAnim_8006FF74(fp, 1);
        }
        fp->mv.co.fall.x0 = smid;
    }
}

void ftCo_Fall_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_Fall_IASA_Inner(gobj));
}

void ftCo_Fall_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_Fall_Coll(Fighter_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, (HSD_GObjEvent) ft_80082B1C);
}

void ftCo_FallAerial_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_FallAerial, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->mv.co.fallaerial.x0 = 23;
    fp->mv.co.fallaerial.x4 = 0.0F;
}

#pragma push
#pragma dont_inline on
void ftCo_FallAerial_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCo_Fall_Anim_Inner(gobj, &fp->mv.co.fallaerial.x4, ftCo_SM_FallAerial,
                         ftCo_SM_FallAerialF, ftCo_SM_FallAerialB);
    ftCo_800CC988(gobj, fp->mv.co.fallaerial.x4);
}
#pragma pop

void ftCo_FallAerial_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_Fall_IASA_Inner(gobj));
}

void ftCo_FallAerial_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

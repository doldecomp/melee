#include "ftCommon/ftCo_Attack100.h"

#include "placeholder.h"
#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Throw.h"

#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

/* 0D8BFC */ static void fn_800D8BFC(Fighter_GObj* arg0);
/* 0D9CE8 */ static void fn_800D9CE8(Fighter_GObj* arg0);
/* 0DAADC */ static void fn_800DAADC(Fighter_GObj* arg0, Fighter_GObj* arg1);

/// #ftCo_800D67C4

/// #ftCo_800D6824

/// #ftCo_800D688C

/// #ftCo_800D68C0

/// #ftCo_800D6928

/// #ftCo_Attack100_CheckInput

/// #ftCo_800D69C4

/// #ftCo_Attack_800D6A50

/// #fn_800D6AC4

/// #ftCo_800D6B00

/// #fn_800D6B8C

/// #ftCo_Attack100Start_Anim

/// #ftCo_800D6C60

/// #ftCo_Attack100Loop_Anim

/// #ftCo_Attack100End_Anim

/// #ftCo_Attack100Loop_IASA

/// #ftCo_Attack100Start_Phys

/// #ftCo_Attack100Loop_Phys

/// #ftCo_Attack100End_Phys

/// #ftCo_Attack100Start_Coll

/// #ftCo_Attack100Loop_Coll

/// #ftCo_Attack100End_Coll

/// #fn_800D6F58

/// #ftCo_800D705C

/// #ftCo_800D7100

/// #ftCo_800D71D8

/// #ftCo_800D7268

/// #ftCo_800D72A0

/// #ftCo_800D730C

/// #ftCo_800D74A4

/// #ftCo_JumpAerialF1_Anim

/// #ftCo_JumpAerialF1_IASA

/// #ftCo_JumpAerialF1_Phys

/// #ftCo_JumpAerialF1_Coll

/// #fn_800D769C

/// #ft_800D76B8

/// #ft_800D7770

/// #fn_800D7830

/// #fn_800D78B0

/// #fn_800D7938

void ftCo_ItemScopeStart_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirStart_Anim(Fighter_GObj* gobj) {}

/// #fn_800D79B4

/// #ftCo_ItemScopeStart_IASA

/// #ftCo_ItemScopeAirStart_IASA

/// #ftCo_ItemScopeStart_Phys

/// #ftCo_ItemScopeAirStart_Phys

/// #ftCo_ItemScopeStart_Coll

/// #ftCo_ItemScopeAirStart_Coll

/// #fn_800D7BDC

/// #fn_800D7C60

/// #fn_800D7CEC

/// #fn_800D7D70

/// #ftCo_ItemScopeRapid_Anim

/// #ftCo_ItemScopeAirRapid_Anim

/// #ftCo_ItemScopeRapid_IASA

/// #ftCo_ItemScopeAirRapid_IASA

/// #ftCo_ItemScopeRapid_Phys

/// #ftCo_ItemScopeAirRapid_Phys

/// #ftCo_ItemScopeRapid_Coll

/// #ftCo_ItemScopeAirRapid_Coll

/// #fn_800D80F4

/// #fn_800D8140

/// #fn_800D81D0

/// #fn_800D8268

/// #fn_800D82EC

/// #fn_800D8378

void ftCo_ItemScopeFire_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
        ftCommon_8007E7E4(gobj, 1);
    }
}

void ftCo_ItemScopeAirFire_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
        ftCommon_8007E7E4(gobj, 1);
    }
}

void ftCo_ItemScopeFire_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirFire_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeFire_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE54(gobj);
}

void ftCo_ItemScopeAirFire_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE74(gobj);
}

/// #ftCo_ItemScopeFire_Coll

/// #ftCo_ItemScopeAirFire_Coll

/// #fn_800D84D4

/// #fn_800D86B8

/// #fn_800D86E0

/// #fn_800D874C

/// #fn_800D87C0

/// #fn_800D8838

#pragma push
#pragma dont_inline on

void ftCo_ItemScopeEnd_Anim(Fighter_GObj* gobj)
{
    ftCo_ItemScopeFire_Anim(gobj);
}

void ftCo_ItemScopeAirEnd_Anim(Fighter_GObj* gobj)
{
    ftCo_ItemScopeFire_Anim(gobj);
}

#pragma pop

void ftCo_ItemScopeEnd_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirEnd_IASA(Fighter_GObj* gobj) {}

/// #ftCo_ItemScopeEnd_Phys

/// #ftCo_ItemScopeAirEnd_Phys

/// #ftCo_ItemScopeEnd_Coll

/// #ftCo_ItemScopeAirEnd_Coll

/// #ftCo_Catch_CheckInput

bool ftCo_800D8A38(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_80095254(gobj)) {
        return true;
    }
    if (!fn_800D8E94(gobj)) {
        return false;
    }
    if (!fn_800D952C(gobj)) {
        return false;
    }
    if ((fp->input.held_inputs & HSD_PAD_LR) && (fp->input.x668 & HSD_PAD_A)) {
        ftCo_800D8C54(gobj, ftCo_MS_CatchDash);
        return true;
    }
    return false;
}

/// #ftCo_800D8AE0

/// #ftCo_800D8B9C

void fn_800D8BFC(Fighter_GObj* arg0)
{
    NOT_IMPLEMENTED;
}

void ftCo_800D8C54(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);

    temp_r31->x74_anim_vel.z = 0.0F;
    temp_r31->x74_anim_vel.y = 0.0F;
    temp_r31->x74_anim_vel.x = 0.0F;
    temp_r31->mv.co.catch.x0 = 0.0F;
    Fighter_ChangeMotionState(gobj, msid, 0U, 0.0F, 1.0F, 0.0F, NULL);
    ftCommon_8007E2D0(temp_r31, 1, fn_800D9CE8, fn_800D8BFC, fn_800DAADC);
}

void ftCo_Catch_Anim(Fighter_GObj* gobj)
{
    u8 _[8];

    if (fn_800D8EC8(gobj)) {
        return;
    }
    if (fn_800D9558(gobj)) {
        return;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// #ftCo_CatchDash_Anim

void ftCo_Catch_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchDash_IASA(Fighter_GObj* gobj) {}

/// #ftCo_Catch_Phys

/// #ftCo_CatchDash_Phys

/// #ftCo_Catch_Coll

/// #fn_800D8E30

/// #ftCo_CatchDash_Coll

bool fn_800D8E94(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FighterKind kind = fp->kind;
    if (((kind == FTKIND_LINK) || (kind == FTKIND_CLINK)) &&
        (fp->fv.lk.xC != NULL))
    {
        return false;
    }
    return true;
}

/// #fn_800D8EC8

/// #fn_800D9228

/// #fn_800D949C

/// #ftCo_800D94D8

bool fn_800D952C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->kind == FTKIND_SAMUS) && (fp->fv.ss.x223C != NULL)) {
        return false;
    }
    return true;
}

/// #fn_800D9558

/// #fn_800D9930

/// #fn_800D9C64

/// #ftCo_800D9C98

void fn_800D9CE8(Fighter_GObj* arg0)
{
    NOT_IMPLEMENTED;
}

/// #ftCo_CatchPull_Anim

void ftCo_CatchPull_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CatchPull_Phys

/// #ftCo_CatchPull_Coll

/// #fn_800DA004

/// #fn_800DA054

/// #fn_800DA190

/// #fn_800DA1D8

/// #fn_800DA2B0

void ftCo_CatchWait_Anim(Fighter_GObj* gobj) {}

/// #ftCo_CatchWait_IASA

/// #ftCo_CatchWait_Phys

/// #ftCo_CatchWait_Coll

/// #fn_800DA440

void fn_800DA490(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

/// #fn_800DA4A0

/// #fn_800DA4C0

/// #fn_800DA4FC

void ftCo_CatchAttack_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DA2B0(gobj);
    }
}

void ftCo_CatchAttack_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CatchAttack_Phys

/// #ftCo_CatchAttack_Coll

/// #fn_800DA618

void fn_800DA668(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

/// #fn_800DA678

/// #ftCo_800DA698

void ftCo_CatchCut_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CatchCut_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CatchCut_Phys

/// #ftCo_CatchCut_Coll

/// #ftCo_800DA824

/// #fn_800DA8E4

/// #fn_800DAA40

void fn_800DAADC(Fighter_GObj* arg0, Fighter_GObj* arg1)
{
    NOT_IMPLEMENTED;
}

void ftCo_CapturePulledHi_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledHi_IASA(Fighter_GObj* gobj) {}

/// #fn_800DAC78

/// #fn_800DAD18

/// #ftCo_CapturePulledHi_Phys

/// #ftCo_CapturePulledHi_Coll

/// #fn_800DAECC

/// #fn_800DAEEC

void ftCo_CapturePulledLw_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledLw_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CapturePulledLw_Phys

/// #ftCo_CapturePulledLw_Coll

/// #fn_800DB230

/// #ftCo_800DB368

/// #ftCo_800DB464

/// #ftCo_800DB500

/// #fn_800DB5D8

/// #fn_800DB6C8

/// #fn_800DB790

/// #fn_800DB8A4

/// #ftCo_CaptureWaitHi_Anim

void ftCo_CaptureWaitHi_IASA(Fighter_GObj* gobj)
{
    fn_800DC014(gobj);
}

/// #ftCo_CaptureWaitHi_Phys

/// #ftCo_CaptureWaitHi_Coll

/// #fn_800DBAC4

/// #fn_800DBAE4

/// #fn_800DBBF8

/// #ftCo_CaptureWaitLw_Anim

/// #ftCo_CaptureWaitLw_IASA

/// #ftCo_CaptureWaitLw_Phys

/// #ftCo_CaptureWaitLw_Coll

/// #fn_800DBED4

/// #fn_800DC014

/// #fn_800DC044

/// #fn_800DC070

/// #ftCo_CaptureJump_Anim

/// #ftCo_CaptureJump_IASA

/// #ftCo_CaptureJump_Phys

void ftCo_CaptureJump_Coll(Fighter_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

/// #ftCo_800DC284

void ftCo_CaptureDamageHi_Anim(Fighter_GObj* gobj)
{
    fn_800DB8A4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DB790(gobj);
    }
}

void ftCo_CaptureDamageHi_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CaptureDamageHi_Phys

/// #ftCo_CaptureDamageHi_Coll

/// #fn_800DC384

/// #ftCo_800DC3A4

/// #fn_800DC404

void ftCo_CaptureDamageLw_Anim(Fighter_GObj* gobj)
{
    fn_800DB8A4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DBAE4(gobj);
    }
}

void ftCo_CaptureDamageLw_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CaptureDamageLw_Phys

/// #ftCo_CaptureDamageLw_Coll

/// #fn_800DC624

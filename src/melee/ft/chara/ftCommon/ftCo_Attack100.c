#include "ftCommon/ftCo_Attack100.h"

#include "placeholder.h"
#include "platform.h"
#include "stdbool.h"

#include "ft/chara/ftCommon/ftCo_AirCatch.h"
#include "ft/chara/ftCommon/ftCo_AttackAir.h"
#include "ft/chara/ftCommon/ftCo_EscapeAir.h"
#include "ft/chara/ftCommon/ftCo_SpecialAir.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Throw.h"
#include "it/items/itsscope.h"

#include <math.h>
#include <melee/cm/camera.h>
#include <melee/ef/efasync.h>
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
#include <melee/ft/chara/ftCommon/ftCo_Fall.h>
#include <melee/ft/chara/ftCommon/ftCo_FallAerial.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_JumpAerial.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/chara/ftCommon/ftpickupitem.h>
#include <melee/ft/chara/ftGameWatch/ftGw_Attack100.h>
#include <melee/ft/chara/ftYoshi/ftYs_Init.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftdata.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/ft/ftparts.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/lb/lb_00B0.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

/* 0D8BFC */ static void fn_800D8BFC(Fighter_GObj* arg0);
/* 0D9CE8 */ static void fn_800D9CE8(Fighter_GObj* arg0);
/* 0DA054 */ void fn_800DA054(Fighter_GObj* gobj);
/* 0DAADC */ static void fn_800DAADC(Fighter_GObj* arg0, Fighter_GObj* arg1);
/* 0DAECC */ static void fn_800DAECC(Fighter_GObj* gobj);
/* 0DAEEC */ void fn_800DAEEC(Fighter_GObj* gobj);
/* 0DB230 */ static void fn_800DB230(Fighter_GObj* gobj);
/* 0DBBF8 */ void fn_800DBBF8(Fighter_GObj* gobj);

extern f32 ftCo_804D90D0; // 0.0f
extern f32 ftCo_804D90D4; // Decrement value
extern f64 ftCo_804D90D8; // Increment value (Double)

typedef struct {
    u8 pad_1A4C[0x1A4C];
    f32 x1A4C; // 0x1A4C
    u8 pad_1A58[0x1A58 - 0x1A50];
    void* x1A58; // 0x1A58
    u8 pad_2340[0x2340 - 0x1A5C];
    f32 x2340; // 0x2340
    f32 x2344; // 0x2344
    s32 x2348; // 0x2348
    u8 x234C;  // 0x234C
} FighterOverlay;

bool ftCo_800D67C4(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_B) {
        if (ABS(fp->input.lstick.x) < p_ftCommonData->x218 &&
            ABS(fp->input.lstick.y) < p_ftCommonData->x21C)
        {
            return true;
        }
    }
    return false;
}

bool ftCo_800D6824(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftData_SpecialN[fp->kind] == NULL) {
        return false;
    }
    if (fp->x689 == 0) {
        ftData_SpecialN[fp->kind](gobj);
        return true;
    }
    return false;
}

bool ftCo_800D688C(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_B) {
        if (fp->input.lstick.y < -p_ftCommonData->x21C) {
            return true;
        }
    }
    return false;
}

bool ftCo_800D68C0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftData_SpecialLw[fp->kind] == NULL) {
        return false;
    }
    if (fp->x687 == 0) {
        ftData_SpecialLw[fp->kind](gobj);
        return true;
    }
    return false;
}

bool ftCo_800D6928(Fighter* fp)
{
    if (fp->input.x668 & 0x200) {
        if (fp->input.lstick.y >= p_ftCommonData->x21C) {
            return true;
        }
    }
    return false;
}

bool ftCo_Attack100_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftData_SpecialHi[fp->kind] == NULL) {
        return false;
    }
    if (fp->x686 == 0) {
        ftData_SpecialHi[fp->kind](gobj);
        return true;
    }
    return false;
}

bool ftCo_800D69C4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (ftData_SpecialHi[fp->kind] == NULL) {
        return false;
    }
    if (fp->x686 == 0 && fp->x68B >= p_ftCommonData->x1C) {
        ftData_SpecialAirHi[fp->kind](gobj);
        return true;
    }
    return false;
}

bool ftCo_Attack_800D6A50(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co;
    Fighter* fp = GET_FIGHTER(gobj);
    co = &fp->co_attrs;
    if ((fp->input.x668 & HSD_PAD_A) || (fp->input.x66C & HSD_PAD_A)) {
        fp->x1A54++;
    }
    if (fp->x1A54 >= co->rapid_jab_window && fp->x2218_b2) {
        fn_800D6AC4(gobj);
        return true;
    }
    return false;
}

void fn_800D6AC4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->kind) {
    case FTKIND_GAMEWATCH:
        ftGw_Attack100Start_Enter(gobj);
        break;
    default:
        fn_800D6B8C(gobj);
        break;
    }
}

void ftCo_800D6B00(Fighter_GObj* gobj, enum_t msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftpickupitem_80094790(gobj)) {
        fp->throw_flags = 0;
        Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
        ftAnim_8006EBA4(gobj);
        fp->mv.co.attack100.x0 = false;
        fp->mv.co.attack100.x4 = false;
    }
}

void fn_800D6B8C(Fighter_GObj* gobj)
{
    PAD_STACK(4);
    ftCo_800D6B00(gobj, ftCo_MS_Attack100Start);
}

void ftCo_Attack100Start_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_Attack100Loop,
                                  Ft_MF_SkipAttackCount, 0.0F, 1.0F, 0.0F,
                                  NULL);
    }
}

void ftCo_800D6C60(Fighter_GObj* gobj, HSD_GObjEvent callback)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool var_r0;
    if (fp->cur_anim_frame >= 0.0F && fp->cur_anim_frame < fp->frame_speed_mul)
    {
        fp->mv.co.attack100.x0 = true;
        ft_800892A0(gobj);
        ft_80089824(gobj);
    }
    if (fp->throw_flags_b3) {
        fp->throw_flags_b3 = false;
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        if (fp->mv.co.attack100.x0 && !fp->mv.co.attack100.x4) {
            callback(gobj);
        } else if (!ftpickupitem_80094790(gobj)) {
            fp->mv.co.attack100.x4 = false;
        }
    }
}

void ftCo_Attack100Loop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool var_r0;
    PAD_STACK(4);
    if (fp->cur_anim_frame >= 0.0F && fp->cur_anim_frame < fp->frame_speed_mul)
    {
        fp->mv.co.attack100.x0 = true;
        ft_800892A0(gobj);
        ft_80089824(gobj);
    }
    if (fp->throw_flags_b3) {
        fp->throw_flags_b3 = false;
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        if (fp->mv.co.attack100.x0 && !fp->mv.co.attack100.x4) {
            Fighter_ChangeMotionState(gobj, ftCo_MS_Attack100End, 0, 0.0F,
                                      1.0F, 0.0F, NULL);
        } else if (!ftpickupitem_80094790(gobj)) {
            fp->mv.co.attack100.x4 = false;
        }
    }
}

void ftCo_Attack100End_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Attack100Loop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->input.x668 & HSD_PAD_A) || (fp->input.x66C & HSD_PAD_A)) {
        fp->mv.co.attack100.x4 = true;
    }
}

void ftCo_Attack100Start_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_Attack100Loop_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_Attack100End_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_Attack100Start_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}

void ftCo_Attack100Loop_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}

void ftCo_Attack100End_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}

void fn_800D6F58(Fighter_GObj* gobj, Item_GObj* item_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_Part part;
    if (fp->item_gobj != NULL) {
        fp->x1978 = item_gobj;
    } else {
        fp->item_gobj = item_gobj;
    }
    ftpickupitem_80094818(gobj, true);
    if (itGetKind(fp->item_gobj) == It_Kind_WStar) {
        part = FtPart_TopN;
    } else {
        part = fp->ft_data->x8->x10;
    }
    pl_8003E854(fp->player_id, fp->x221F_b4, item_gobj);
    Item_8026AB54(item_gobj, gobj, part);
    ftpickupitem_8009447C(gobj, item_gobj);
    {
        HSD_JObj* jobj = fp->parts[fp->ft_data->x8->x10].joint;
        efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 0, 0x422, jobj);
    }
    fp->x2224_b1 = true;
}

bool ftCo_800D705C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool tmp = fp->item_gobj == NULL && (fp->input.held_inputs & HSD_PAD_LR) &&
               (fp->input.x668 & HSD_PAD_A) && !fp->x2224_b1 &&
               fp->x683 >= p_ftCommonData->x1C;
    if (tmp) {
        fp->x209C = p_ftCommonData->x414;
        return true;
    }
    return false;
}

bool ftCo_800D7100(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    bool tmp = fp->item_gobj == NULL && (fp->input.held_inputs & HSD_PAD_LR) &&
               (fp->input.x668 & HSD_PAD_A) && !fp->x2224_b1 &&
               fp->x683 >= p_ftCommonData->x1C;
    if (tmp) {
        Item_GObj* item_gobj = ftpickupitem_800942A0(gobj, 1);
        if (item_gobj != NULL) {
            fn_800D6F58(gobj, item_gobj);
            return true;
        }
    }
    return false;
}

void ftCo_800D71D8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x209C != 0) {
        Item_GObj* item_gobj = ftpickupitem_800942A0(gobj, 1U);
        fp->x209C -= 1;
        if (fp->x209C == 0) {
            fp->x2224_b1 = true;
        }
        if (item_gobj != NULL) {
            fn_800D6F58(gobj, item_gobj);
            fp->x209C = 0;
        }
    }
}

/// #ftCo_800D7268

/// #ftCo_800D72A0

/// #ftCo_800D730C

/// #ftCo_800D74A4

void ftCo_JumpAerialF1_Anim(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* co;
    Fighter* temp_r30 = GET_FIGHTER(gobj);
    int tmp = temp_r30->x2D0->x0;
    PAD_STACK(4);
    co = &temp_r30->co_attrs;
    ft_800CB6EC(temp_r30, tmp);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        if (temp_r30->x1968_jumpsUsed >= co->max_jumps) {
            ftCo_FallAerial_Enter(gobj);
        } else {
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftCo_JumpAerialF1_IASA(Fighter_GObj* gobj)
{
    ftCo_JumpAerial_IASA(gobj);
}

void ftCo_JumpAerialF1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co = &fp->co_attrs;
    struct Fighter_x2D0_t* temp_r6 = fp->x2D0;
    ft_80084E1C(gobj, p_ftCommonData->x258,
                co->air_drift_stick_mul * temp_r6->xC,
                co->air_drift_max * temp_r6->x10);
}

void ftCo_JumpAerialF1_Coll(Fighter_GObj* gobj)
{
    ft_80082F28(gobj);
}

static FtMotionId fn_800D769C(Fighter* ft, FtMotionId msid)
{
    if (ft->motion_id >= ftCo_MS_ItemScopeStartEmpty) {
        return msid + 8;
    }
    return msid;
}

/// #ft_800D76B8

/// #ft_800D7770

/// #fn_800D7830

/// #fn_800D78B0

/// #fn_800D7938

void ftCo_ItemScopeStart_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirStart_Anim(Fighter_GObj* gobj) {}

void fn_800D79B4(HSD_GObj* gobj, void (*cb_ground)(HSD_GObj*),
                 void (*cb_air)(HSD_GObj*, int))
{
    Fighter* fp = GET_FIGHTER(gobj);
    int item_val;
    s32 stack_var;

    // Define an overlay struct to force direct offset access (prevents address
    // caching in r26/r27)
    typedef struct {
        u8 pad[0x2340];
        f32 timer; // 0x2340
        s32 flag;  // 0x2344
    } FighterOverlay;
    FighterOverlay* fp_ovl = (FighterOverlay*) fp;

    // Use this specific cast to generate the correct 'lfs' instruction for the
    // global int
    extern int ftCo_804D9024;

    if (fp->item_gobj == NULL) {
        return;
    }

    // Access 0x2344 (Flag) via overlay
    if (fp_ovl->flag == 0) {
        // Access 0x65C (Input) via raw pointer to match ASM
        if (*(u32*) ((u8*) fp + 0x65C) & HSD_PAD_A) {
            // Access 0x2340 (Timer) via overlay
            fp_ovl->timer += *(f32*) &ftCo_804D9024;
        }
    }

    if (!(*(u32*) ((u8*) fp + 0x65C) & HSD_PAD_A)) {
        fp_ovl->flag = 1;
    }

    // Timer to int conversion
    stack_var = (s32) fp_ovl->timer;

    item_val = it_80291DAC(fp->item_gobj, stack_var);

    // Threshold check (Float vs Float)
    if (fp_ovl->timer >= *(f32*) ((u8*) p_ftCommonData + 0x5B8)) {
        if (!ftAnim_IsFramesRemaining(gobj)) {
            cb_air(gobj, item_val);
        }
    }

    if (fp_ovl->flag == 0) {
        return;
    }

    if (ftAnim_IsFramesRemaining(gobj)) {
        return;
    }

    stack_var = (s32) fp_ovl->timer;

    if (it_80291CF4(fp->item_gobj, stack_var) == 0) {
        cb_ground(gobj);
    } else {
        cb_air(gobj, item_val);
    }
}

void ftCo_ItemScopeStart_IASA(Fighter_GObj* gobj)
{
    fn_800D79B4(gobj, fn_800D7BDC, fn_800D8140);
}

void ftCo_ItemScopeAirStart_IASA(Fighter_GObj* gobj)
{
    fn_800D79B4(gobj, fn_800D7C60, fn_800D81D0);
}

void ftCo_ItemScopeStart_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE54(gobj);
}

void ftCo_ItemScopeAirStart_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE74(gobj);
}

void ftCo_ItemScopeStart_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D78B0);
}

void ftCo_ItemScopeAirStart_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D7830);
}

/// #fn_800D7BDC

/// #fn_800D7C60

/// #fn_800D7CEC

/// #fn_800D7D70

/// #ftCo_ItemScopeRapid_Anim

/// #ftCo_ItemScopeAirRapid_Anim

void ftCo_ItemScopeRapid_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_PAD_A) {
        *(s32*) ((u8*) fp + 0x2340) = *(s32*) ((u8*) p_ftCommonData + 0x5BC);
    }
}

void ftCo_ItemScopeAirRapid_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = *(Fighter**) ((u8*) gobj + 0x2C);

    if (fp->input.x668 & HSD_PAD_A) {
        *(s32*) ((u8*) fp + 0x2340) = *(s32*) ((u8*) p_ftCommonData + 0x5BC);
    }
}

void ftCo_ItemScopeRapid_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE54(gobj);
}

void ftCo_ItemScopeAirRapid_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE74(gobj);
}

void ftCo_ItemScopeRapid_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D7D70);
}

void ftCo_ItemScopeAirRapid_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D7CEC);
}

/// #fn_800D80F4

/// #fn_800D8140

/// #fn_800D81D0

/// #fn_800D8268

/// #fn_800D82EC

void fn_800D8378(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((u32) fp->item_gobj != NULL) {
        ftCommon_8007E7E4(gobj, 1);
    }
}

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

void ftCo_ItemScopeFire_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D82EC);
}

void ftCo_ItemScopeAirFire_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D8268);
}

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

void ftCo_ItemScopeEnd_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE54(gobj);
}

void ftCo_ItemScopeAirEnd_Phys(Fighter_GObj* gobj)
{
    ftCo_800CDE74(gobj);
}

void ftCo_ItemScopeEnd_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D8838);
}

void ftCo_ItemScopeAirEnd_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D87C0);
}

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

void fn_800D8BFC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftpickupitem_800948A8(gobj, fp->target_item_gobj);
    fp->x1A64 = NULL;
    fp->target_item_gobj = NULL;
    ftpickupitem_80094694(gobj, 0x5D, 1);
}

void ftCo_800D8C54(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x74_anim_vel.z = 0.0F;
    fp->x74_anim_vel.y = 0.0F;
    fp->x74_anim_vel.x = 0.0F;
    fp->mv.co.catch.x0 = 0.0F;
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftCommon_8007E2D0(fp, 1, fn_800D9CE8, fn_800D8BFC, fn_800DAADC);
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

void ftCo_CatchDash_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (!fn_800D9228(gobj) && !fn_800D9930(gobj) &&
        !ftAnim_IsFramesRemaining(gobj))
    {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Catch_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchDash_IASA(Fighter_GObj* gobj) {}

void ftCo_Catch_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_ApplyFrictionGround(fp, p_ftCommonData->x64 *
                                         fp->co_attrs.gr_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftCo_CatchDash_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ft_80085030(gobj, p_ftCommonData->x64 * fp->co_attrs.gr_friction,
                fp->facing_dir);
}
void ftCo_Catch_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D8E30);
}

/// #fn_800D8E30

void ftCo_CatchDash_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800D8E30);
}

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

void ftCo_CatchPull_Phys(Fighter_GObj* gobj)
{
    ftCo_Catch_Phys(gobj);
}

void ftCo_CatchPull_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800DA004);
}

void fn_800DA004(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim = fp->victim_gobj;
    ftCo_800DC920(gobj, victim);
    ftCo_Fall_Enter(gobj);
    ftCo_Fall_Enter(victim);
}

/// #fn_800DA054

/// #fn_800DA190

/// #fn_800DA1D8

/// #fn_800DA2B0

void ftCo_CatchWait_Anim(Fighter_GObj* gobj) {}

/// #ftCo_CatchWait_IASA

void ftCo_CatchWait_Phys(Fighter_GObj* gobj)
{
    ftCo_Catch_Phys(gobj);
}

void ftCo_CatchWait_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800DA440);
}

void fn_800DA440(Fighter_GObj* gobj)
{
    fn_800DA004(gobj);
}

void fn_800DA490(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

void fn_800DA4A0(Fighter_GObj* gobj)
{
    fn_800DA054(gobj);
}

/// #fn_800DA4C0

/// #fn_800DA4FC

void ftCo_CatchAttack_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DA2B0(gobj);
    }
}

void ftCo_CatchAttack_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchAttack_Phys(Fighter_GObj* gobj)
{
    ftCo_Catch_Phys(gobj);
}

void ftCo_CatchAttack_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800DA618);
}

void fn_800DA618(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim = fp->victim_gobj;

    ftCo_800DC920(gobj, victim);
    ftCo_Fall_Enter(gobj);
    ftCo_Fall_Enter(victim);
}

void fn_800DA668(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

void fn_800DA678(Fighter_GObj* gobj)
{
    fn_800DA054(gobj);
}

/// #ftCo_800DA698

void ftCo_CatchCut_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CatchCut_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchCut_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_ApplyFrictionGround(fp, p_ftCommonData->x64 *
                                             fp->co_attrs.gr_friction);
        ftCommon_ApplyGroundMovement(gobj);
        return;
    }
    ft_80084DB0(gobj);
}

/// #ftCo_CatchCut_Coll

/// #ftCo_800DA824

/// #fn_800DA8E4

void fn_800DAA40(Fighter_GObj* arg0, Fighter_GObj* arg1)
{
    Vec3 sp18;
    Fighter* temp_r31 = GET_FIGHTER(arg0);
    Fighter* temp_r30 = GET_FIGHTER(arg1);
    fn_800DAC78(arg0, &sp18);
    if (temp_r31->ground_or_air == GA_Ground) {
        temp_r30->x2170 = sp18.y + temp_r31->cur_pos.y - temp_r30->cur_pos.y;
    } else {
        temp_r30->x2170 = 0.0F;
        temp_r31->cur_pos.x += sp18.x;
        temp_r31->cur_pos.y += sp18.y;
        temp_r31->cur_pos.z += sp18.z;
    }
}

void fn_800DAADC(Fighter_GObj* arg0, Fighter_GObj* arg1)
{
    NOT_IMPLEMENTED;
}

void ftCo_CapturePulledHi_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledHi_IASA(Fighter_GObj* gobj) {}

/// #fn_800DAC78

static bool fn_800DAD18(Fighter_GObj* gobj)
{
    Fighter* temp_r31;
    bool var_r3;

    Vec3 tmp;
    Vec3 sp2C;
    Vec3 sp20;

    PAD_STACK(0x8);

    temp_r31 = GET_FIGHTER(gobj);
    lb_8000B1CC(GET_FIGHTER(temp_r31->victim_gobj)->mv.co.capturedamage.x18,
                NULL, &sp20);
    lb_8000B1CC(
        temp_r31->parts[ftParts_GetBoneIndex(temp_r31, FtPart_XRotN)].joint,
        NULL, &sp2C);

    tmp.x = sp20.x - sp2C.x;
    tmp.y = sp20.y - sp2C.y;
    tmp.z = sp20.z - sp2C.z;

    if (tmp.y > p_ftCommonData->x3C4 * temp_r31->x34_scale.y) {
        var_r3 = true;
    } else {
        var_r3 = false;
    }
    temp_r31->cur_pos.x += tmp.x;
    temp_r31->cur_pos.y += tmp.y;
    temp_r31->cur_pos.z += tmp.z;
    return var_r3;
}

/// #ftCo_CapturePulledHi_Phys

void ftCo_CapturePulledHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_80083C00(gobj, fn_800DAECC);
    }
}

static void fn_800DAECC(Fighter_GObj* gobj)
{
    fn_800DAEEC(gobj);
}

/// #fn_800DAEEC

void ftCo_CapturePulledLw_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledLw_IASA(Fighter_GObj* gobj) {}

/// #ftCo_CapturePulledLw_Phys

void ftCo_CapturePulledLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_8008403C(gobj, fn_800DB230);
    }
}

/// #fn_800DB230

/// #ftCo_800DB368

/// #ftCo_800DB464

/// #ftCo_800DB500

static void fn_800DB5D8(Fighter_GObj* gobj)
{
    ftHurtboxInit sp18;
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(fp->victim_gobj);
    if (victim_fp->kind == FTKIND_YOSHI) {
        fp->invisible = true;
        fp->accessory1_cb = ftCo_800DB464;
        ftColl_8007B0C0(gobj, Intangible);
        sp18.bone_idx = ftParts_GetBoneIndex(fp, FtPart_XRotN);
        sp18.height = HurtHeight_Mid;
        sp18.is_grabbable = false;
        sp18.a_offset.x = sp18.a_offset.y = sp18.a_offset.z = 0.0F;
        sp18.b_offset.x = sp18.b_offset.y = sp18.b_offset.z = 0.0F;
        sp18.scale =
            ftYs_Init_8012BAC0(victim_fp) / ftCommon_GetModelScale(fp);
        ftColl_HurtboxInit(fp, fp->hurt_capsules, &sp18);
    }
    ftCommon_8007E2F4(fp, 0x1FF);
}

/// #fn_800DB6C8

/// #fn_800DB790

/// #fn_800DB8A4

void ftCo_CaptureWaitHi_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    Fighter* fp;
    FighterOverlay* fp_ovl;
    f32 dec;
    f32 zero;
    fp = GET_FIGHTER(gobj);
    fp_ovl = (FighterOverlay*) fp;
    fp_ovl->x2340 = (f32) ((f64) fp_ovl->x2340 + ftCo_804D90D8);
    fp_ovl->x1A4C -= *(f32*) ((u8*) p_ftCommonData + 0x3A4);
    fp_ovl->x2348 =
        ftCommon_GrabMash(fp, *(f32*) ((u8*) p_ftCommonData + 0x3A8));
    if (fp_ovl->x1A4C <= ftCo_804D90D0) {
        ftCo_800DA698(fp_ovl->x1A58, 0);
        if (fp_ovl->x234C != 0 || fn_800DC044(gobj)) {
            fn_800DC070(gobj);
            return;
        }

        ftCo_CaptureCut_Enter(gobj);
        return;
    }

    zero = ftCo_804D90D0;
    if (fp_ovl->x2344 != zero) {
        dec = ftCo_804D90D4;
        fp_ovl->x2344 -= dec;
        if (fp_ovl->x2344 <= zero && fp_ovl->x2348 == 0) {
            ftAnim_SetAnimRate(gobj, dec);
            fp_ovl->x2344 = ftCo_804D90D0;
        }
    }

    if (*(volatile f32*) &fp_ovl->x2344 <= ftCo_804D90D0 && fp_ovl->x2348 != 0)
    {
        fp_ovl->x2344 = *(f32*) ((u8*) p_ftCommonData + 0x3B0);
        ftAnim_SetAnimRate(gobj, *(f32*) ((u8*) p_ftCommonData + 0x3B4));
    }
}

void ftCo_CaptureWaitHi_IASA(Fighter_GObj* gobj)
{
    fn_800DC014(gobj);
}

#pragma push
#pragma dont_inline on
void ftCo_CaptureWaitHi_Phys(Fighter_GObj* gobj)
{
    fn_800DAD18(gobj);
}
#pragma pop

void ftCo_CaptureWaitHi_Coll(Fighter_GObj* gobj)
{
    ftCo_CapturePulledHi_Coll(gobj);
}

void fn_800DBAC4(Fighter_GObj* gobj)
{
    fn_800DBBF8(gobj);
}

/// #fn_800DBAE4

/// #fn_800DBBF8

void ftCo_CaptureWaitLw_Anim(Fighter_GObj* gobj)
{
    ftCo_CaptureWaitHi_Anim(gobj);
}

void ftCo_CaptureWaitLw_IASA(Fighter_GObj* gobj)
{
    fn_800DC014(gobj);
}

/// #ftCo_CaptureWaitLw_Phys

void ftCo_CaptureWaitLw_Coll(Fighter_GObj* gobj)
{
    ftCo_CapturePulledLw_Coll(gobj);
}

/// #fn_800DBED4

/// #fn_800DC014

/// #fn_800DC044

/// #fn_800DC070

void ftCo_CaptureJump_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.buryjump.x0 += 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

/// #ftCo_CaptureJump_IASA

void ftCo_CaptureJump_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    ftCommon_Fall(fp, fp->co_attrs.grav, fp->co_attrs.terminal_vel);
    ftCommon_8007D268(fp);
}

void ftCo_CaptureJump_Coll(Fighter_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

#pragma push
#pragma dont_inline on
void ftCo_800DC284(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageHi, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->mv.co.capturedamage.x4 = 0.0F;
    fn_800DB5D8(gobj);
}
#pragma pop

/// #ftCo_800DC284

void ftCo_CaptureDamageHi_Anim(Fighter_GObj* gobj)
{
    fn_800DB8A4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DB790(gobj);
    }
}

void ftCo_CaptureDamageHi_IASA(Fighter_GObj* gobj) {}

#pragma push
#pragma dont_inline on
void ftCo_CaptureDamageHi_Phys(Fighter_GObj* gobj)
{
    fn_800DAD18(gobj);
}
#pragma pop

void ftCo_CaptureDamageHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_80083C00(gobj, fn_800DC384);
    }
}

void fn_800DC384(Fighter_GObj* gobj)
{
    fn_800DC404(gobj);
}

#pragma push
#pragma dont_inline on
void ftCo_800DC3A4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageLw, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->mv.co.capturedamage.x4 = 0.0F;
    fn_800DB5D8(gobj);
}

void fn_800DC404(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageLw, Ft_MF_UpdateCmd,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);
    fn_800DB5D8(gobj);
    fn_800DAA40(gobj, fp->victim_gobj);
}
#pragma pop

void ftCo_CaptureDamageLw_Anim(Fighter_GObj* gobj)
{
    fn_800DB8A4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DBAE4(gobj);
    }
}

void ftCo_CaptureDamageLw_IASA(Fighter_GObj* gobj) {}

static inline void ftCo_CaptureDamageLw_Phys_inline(Fighter_GObj* gobj)
{
    Fighter* fp2;
    Vec3* pos;

    if (fn_800DAD18(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageHi,
                                  Ft_MF_UpdateCmd, fp->cur_anim_frame, 1.0F,
                                  0.0F, NULL);
        fn_800DB5D8(gobj);
        fn_800DAA40(gobj, fp->victim_gobj);

        fp2 = GET_FIGHTER(gobj);
        if (!fp2->x2226_b2) {
            ft_80083C00(gobj, fn_800DC384);
        }

        pos = &fp->cur_pos;
        HSD_JObjSetTranslate(GET_JOBJ(gobj), pos);
    }
}

void ftCo_CaptureDamageLw_Phys(Fighter_GObj* gobj)
{
    ftCo_CaptureDamageLw_Phys_inline(gobj);
}

void ftCo_CaptureDamageLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_8008403C(gobj, fn_800DC624);
    }
}

static inline void fn_800DC624_inline(HSD_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageHi, Ft_MF_UpdateCmd,
                              temp_r31->cur_anim_frame, 1.0F, 0.0F, NULL);
    fn_800DB5D8(gobj);
    fn_800DAA40(gobj, temp_r31->victim_gobj);
    if (!GET_FIGHTER(gobj)->x2226_b2) {
        ft_80083C00(gobj, fn_800DC384);
    }
    HSD_JObjSetTranslate(GET_JOBJ(gobj), &temp_r31->cur_pos);
}

void fn_800DC624(HSD_GObj* gobj)
{
    PAD_STACK(4);
    fn_800DC624_inline(gobj);
}

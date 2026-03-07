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

#include "ftCommon/types.h"

#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Throw.h"
#include "it/items/itsamusgrapple.h"
#include "it/items/itsscope.h"
#include "it/items/itlinkhookshot.h"
#include "it/items/itsamusgrapple.h"
#include "it/inlines.h"
#include "mp/mplib.h"

#include <math.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
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
#include <melee/ft/chara/ftKirby/ftKb_Init.h>
#include <melee/ft/chara/ftLink/ftLk_Init.h>
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

/* 0D769C */ static FtMotionId fn_800D769C(Fighter* ft, FtMotionId msid);
/* 0D84D4 */ static void fn_800D84D4(Fighter_GObj*, int);
/* 0D8BFC */ static void fn_800D8BFC(Fighter_GObj* arg0);
/* 0952DC */ bool ftCo_800952DC(Fighter_GObj* gobj);
/* 0D949C */ static void fn_800D949C(Fighter_GObj* gobj);
/* 0D9C64 */ static void fn_800D9C64(Fighter_GObj* gobj);
/* 0D9CE8 */ static void fn_800D9CE8(Fighter_GObj* arg0);
/* 0DA054 */ void fn_800DA054(Fighter_GObj* gobj);
/* 0DAADC */ static void fn_800DAADC(Fighter_GObj* arg0, Fighter_GObj* arg1);
/* 0DAECC */ static void fn_800DAECC(Fighter_GObj* gobj);
/* 0DAEEC */ void fn_800DAEEC(Fighter_GObj* gobj);
/* 0DB230 */ static void fn_800DB230(Fighter_GObj* gobj);
/* 0DB230 */ static inline void fn_800DB230_inline(Fighter_GObj* gobj);
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

typedef struct {
    u8 pad_0[0x9C];
    s32 x9C;
    s32 xA0;
    s32 xA4;
    s32 xA8;
} ftCo_SamusCatchAttrs;

typedef struct {
    u8 pad_0[0x84];
    s32 x84;
    s32 x88;
    s32 x8C;
    s32 x90;
    s32 x94;
    s32 x98;
    s32 x9C;
    s32 xA0;
    u8 pad_A4[0xBC - 0xA4];
    s32 xBC;
} ftCo_LinkCatchAttrs;

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

s32 ftCo_800D7268(Fighter* fp)
{
    if (fp->kind == FTKIND_KIRBY) {
        return ftKb_SpecialN_800F1CD8(fp->gobj);
    }
    return 0;
}

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

void ft_800D76B8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    extern int ftCo_804D9020;
    extern int ftCo_804D9024;

    if (it_8026B594(fp->item_gobj) == false) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeStart, Ft_MF_None,
                                  *(f32*) &ftCo_804D9020,
                                  *(f32*) &ftCo_804D9024,
                                  *(f32*) &ftCo_804D9020, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeStartEmpty,
                                  Ft_MF_None, *(f32*) &ftCo_804D9020,
                                  *(f32*) &ftCo_804D9024,
                                  *(f32*) &ftCo_804D9020, NULL);
    }

    {
        typedef struct {
            u8 x0[0x2340];
            f32 x2340;
            s32 x2344;
        } ItemScopeVars;
        ItemScopeVars* vars = (ItemScopeVars*) fp;

        ftAnim_8006EBA4(gobj);
        vars->x2340 = *(f32*) &ftCo_804D9020;
        vars->x2344 = 0;
    }

    ftCommon_8007E79C(fp->gobj, 1);
    fp->take_dmg_cb = (HSD_GObjEvent) fn_800D7938;
}

void ft_800D7770(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    extern int ftCo_804D9020;
    extern int ftCo_804D9024;

    if (it_8026B594(fp->item_gobj) == false) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeAirStart, Ft_MF_None,
                                  *(f32*) &ftCo_804D9020,
                                  *(f32*) &ftCo_804D9024,
                                  *(f32*) &ftCo_804D9020, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeAirStartEmpty,
                                  Ft_MF_None, *(f32*) &ftCo_804D9020,
                                  *(f32*) &ftCo_804D9024,
                                  *(f32*) &ftCo_804D9020, NULL);
    }

    {
        typedef struct {
            u8 x0[0x2340];
            f32 x2340;
            s32 x2344;
        } ItemScopeVars;
        ItemScopeVars* vars = (ItemScopeVars*) fp;

        ftAnim_8006EBA4(gobj);
        ftCommon_ClampAirDrift(fp);
        vars->x2340 = *(f32*) &ftCo_804D9020;
        vars->x2344 = 0;
    }

    ftCommon_8007E79C(fp->gobj, 1);
    fp->take_dmg_cb = (HSD_GObjEvent) fn_800D7938;
}

void fn_800D7830(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    ftCommon_8007D7FC(fp);
    if (fp->motion_id >= ftCo_MS_ItemScopeStartEmpty) {
        msid = ftCo_MS_ItemScopeStartEmpty;
    } else {
        msid = ftCo_MS_ItemScopeStart;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5280, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    fp->take_dmg_cb = (HSD_GObjEvent) fn_800D7938;
}

void fn_800D78B0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    ftCommon_8007D5D4(fp);
    if (fp->motion_id >= ftCo_MS_ItemScopeStartEmpty) {
        msid = ftCo_MS_ItemScopeAirStartEmpty;
    } else {
        msid = ftCo_MS_ItemScopeAirStart;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5280, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->take_dmg_cb = (HSD_GObjEvent) fn_800D7938;
}

void fn_800D7938(Fighter_GObj* gobj)
{
    Fighter_GObj* temp_r30;
    Fighter* temp_r31;
    s32 temp_r4;

    temp_r30 = gobj;
    temp_r31 = GET_FIGHTER(temp_r30);
    if (temp_r31->item_gobj != NULL) {
        temp_r4 =
            it_80291DAC(temp_r31->item_gobj, (s32) ((FighterOverlay*) temp_r31)->x2340);
        if (temp_r4 != -1) {
            ((void (*)(Item_GObj*, s32)) it_80291F14)(temp_r31->item_gobj,
                                                      temp_r4);
        }
        ftCommon_8007E7E4(temp_r30, 1);
    }
}

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

#pragma push
#pragma dont_inline on

void fn_800D7BDC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_GObj* temp_gobj;
    FtMotionId msid;
    f32 zero;

    msid = fn_800D769C(fp, ftCo_MS_ItemScopeRapid);
    zero = 0.0F;
    temp_gobj = gobj;
    Fighter_ChangeMotionState(temp_gobj, msid, 0x02000000, zero, 1.0F, zero,
                              NULL);
    fp->mv.co.common.x0 = *(s32*) ((u8*) p_ftCommonData + 0x5BC);
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}



#pragma pop

#pragma push
#pragma dont_inline on

void fn_800D7CEC(Fighter_GObj* gobj)
{
    extern int ftCo_804D9028;
    Fighter* fp = gobj->user_data;
    FtMotionId msid;

    ftCommon_8007D7FC(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeRapid);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, *(f32*) &ftCo_804D9028,
                              NULL);
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}

#pragma pop

#pragma push
#pragma dont_inline on

void fn_800D7D70(Fighter_GObj* gobj)
{
    extern int ftCo_804D9028;
    Fighter* fp = gobj->user_data;
    FtMotionId msid;

    ftCommon_8007D5D4(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeAirRapid);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, *(f32*) &ftCo_804D9028,
                              NULL);
    ftCommon_ClampAirDrift(fp);
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}

#pragma pop

void ftCo_ItemScopeRapid_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    PAD_STACK(8);

    if (fp->cur_anim_frame >= 0.0F && fp->cur_anim_frame < fp->frame_speed_mul) {
        ft_800892A0(gobj);
        ft_80089824(gobj);
        fp->mv.co.common.x0--;

        if (fp->mv.co.common.x0 == 0) {
            fn_800D86E0(gobj);
        } else if (fp->item_gobj != NULL && it_8026B594(fp->item_gobj) != 0) {
            fp = gobj->user_data;

            if (fp->ground_or_air == GA_Ground) {
                Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeRapidEmpty,
                                          0x0C4C5080, fp->cur_anim_frame,
                                          fp->frame_speed_mul, 0.0F, NULL);
            } else {
                Fighter_ChangeMotionState(gobj,
                                          ftCo_MS_ItemScopeAirRapidEmpty,
                                          0x0C4C5080, fp->cur_anim_frame,
                                          fp->frame_speed_mul, 0.0F, NULL);
            }
            fp->accessory4_cb = fn_800D80F4;
            fp->take_dmg_cb = fn_800D8378;
        }
    }
}

void ftCo_ItemScopeAirRapid_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    PAD_STACK(8);

    if (fp->cur_anim_frame >= 0.0F && fp->cur_anim_frame < fp->frame_speed_mul) {
        ft_800892A0(gobj);
        ft_80089824(gobj);
        fp->mv.co.common.x0--;

        if (fp->mv.co.common.x0 == 0) {
            fn_800D874C(gobj);
        } else if (fp->item_gobj != NULL && it_8026B594(fp->item_gobj) != 0) {
            fp = gobj->user_data;

            if (fp->ground_or_air == GA_Ground) {
                Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScopeRapidEmpty,
                                          0x0C4C5080, fp->cur_anim_frame,
                                          fp->frame_speed_mul, 0.0F, NULL);
            } else {
                Fighter_ChangeMotionState(gobj,
                                          ftCo_MS_ItemScopeAirRapidEmpty,
                                          0x0C4C5080, fp->cur_anim_frame,
                                          fp->frame_speed_mul, 0.0F, NULL);
            }
            fp->accessory4_cb = fn_800D80F4;
            fp->take_dmg_cb = fn_800D8378;
        }
    }
}

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

void fn_800D80F4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->item_gobj != NULL) {
        fn_800D84D4(gobj, it_80291DAC(fp->item_gobj, 0));
    }
}

#pragma push
#pragma dont_inline on

void fn_800D8140(Fighter_GObj* gobj, int arg1)
{
    extern int ftCo_804D9030;
    extern int ftCo_804D9034;
    Fighter* fp = gobj->user_data;
    FtMotionId msid;
    PAD_STACK(8);

    fp->throw_flags = 0;
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeFire);
    {
        HSD_GObj* gobj2 = gobj;

        Fighter_ChangeMotionState(gobj2, msid, Ft_MF_None,
                                  *(f32*) &ftCo_804D9030,
                                  *(f32*) &ftCo_804D9034,
                                  *(f32*) &ftCo_804D9030, NULL);
    }
    fp->mv.co.common.x0 = arg1;
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}

#pragma pop

#pragma push
#pragma dont_inline on

void fn_800D8268(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid;

    ftCommon_8007D7FC(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeFire);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}

#pragma pop

#pragma push
#pragma dont_inline on

void fn_800D82EC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid;

    ftCommon_8007D5D4(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeAirFire);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}

#pragma pop

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

void fn_800D86B8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fn_800D84D4(gobj, fp->mv.co.common.x0);
}

#pragma push
#pragma dont_inline on

void fn_800D86E0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, ftCo_MS_ItemScopeEnd), 0,
                              0.0F, 1.0F, 0.0F, NULL);
    fp->take_dmg_cb = fn_800D8378;
}

#pragma pop

/// #fn_800D874C

#pragma push
#pragma dont_inline on

void fn_800D874C(Fighter_GObj* gobj)
{
    extern int ftCo_804D9038;
    extern int ftCo_804D903C;
    Fighter* fp = gobj->user_data;
    Fighter_GObj* temp_gobj;
    FtMotionId msid;
    f32 zero;

    msid = fn_800D769C(fp, ftCo_MS_ItemScopeAirEnd);
    zero = *(f32*) &ftCo_804D9038;
    temp_gobj = gobj;
    Fighter_ChangeMotionState(temp_gobj, msid, 0, zero, *(f32*) &ftCo_804D903C,
                              zero, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D87C0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid;

    ftCommon_8007D7FC(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeEnd);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    fp->take_dmg_cb = fn_800D8378;
}

void fn_800D8838(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid;

    ftCommon_8007D5D4(fp);
    msid = fn_800D769C(fp, ftCo_MS_ItemScopeAirEnd);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C5080, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0F, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->take_dmg_cb = fn_800D8378;
}

#pragma pop

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

bool ftCo_Catch_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_800951D0(gobj)) {
        return true;
    }
    if (!fn_800D8E94(gobj)) {
        return false;
    }
    if (!fn_800D952C(gobj)) {
        return false;
    }
    if ((fp->input.held_inputs & HSD_PAD_LR) && (fp->input.x668 & HSD_PAD_A)) {
        ftCo_800D8C54(gobj, ftCo_MS_Catch);
        return true;
    }
    return false;
}

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

bool ftCo_800D8AE0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (ftCo_800952DC(gobj)) {
        return true;
    }
    if (!fn_800D8E94(gobj)) {
        return false;
    }
    if (!fn_800D952C(gobj)) {
        return false;
    }
    if ((fp->input.held_inputs & HSD_PAD_LR) && fp->mv.co.common.x0 != 0) {
        ftCo_800D8C54(gobj, ftCo_MS_CatchDash);
        return true;
    }
    if (fp->mv.co.common.x0 != 0) {
        fp->mv.co.common.x0--;
    }
    return false;
}

bool ftCo_800D8B9C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if ((fp->input.x668 & HSD_PAD_A) && fp->mv.co.guard.x24 != 0) {
        ftCo_800D8C54(gobj, ftCo_MS_CatchDash);
        return true;
    }
    if (fp->mv.co.guard.x24 != 0) {
        fp->mv.co.guard.x24--;
    }
    return false;
}

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

void fn_800D8E30(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    fn_800D949C(gobj);
    fn_800D9C64(gobj);
    ftCo_Fall_Enter(gobj);
}

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



bool fn_800D9228(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->kind == FTKIND_LINK) || (fp->kind == FTKIND_CLINK)) {
        ftCo_LinkCatchAttrs* da = fp->dat_attrs;

        fp->mv.co.catch.x0 += 1.0;
        if (fp->mv.co.catch.x0 == (f32) da->x94) {
            Vec3 pos;

            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint,
                NULL, &pos);
            fp->fv.lk.xC = it_802A2BA4(gobj, &pos, fp->facing_dir, da->xBC);
            if (fp->fv.lk.xC == NULL) {
                ft_8008A2BC(gobj);
                return true;
            }
            fp->accessory2_cb = it_802A7AF0;
            fp->death1_cb = it_802A7AAC;
            fp->accessory3_cb = it_802A7B34;
        } else if (fp->mv.co.catch.x0 > (f32) da->x94 &&
                   fp->mv.co.catch.x0 <= (f32) da->xA0)
        {
            Item_GObj* tether_gobj = fp->fv.lk.xC;
            Item* tether_ip = tether_gobj->user_data;
            struct TetherAttributes* tether_data =
                tether_ip->xC4_article_data->x4_specialAttributes;

            if (fp->mv.co.catch.x0 == (f32) da->x98) {
                f32 x = tether_data->pos_x_0 * fp->facing_dir;
                Vec3 pos;
                UNUSED volatile u8 pad_b[8];

                pos.x = x;
                pos.y = 0.0F;
                pos.z = 0.0F;
                it_802A78B8(tether_gobj, &pos, x);
                if (fp->kind == FTKIND_CLINK) {
                    ft_PlaySFX(fp, 0x111B9, 0x7F, 0x40);
                } else {
                    ft_PlaySFX(fp, 0x27149, 0x7F, 0x40);
                }
            } else if (fp->mv.co.catch.x0 == (f32) da->x9C) {
                it_802A77DC(tether_gobj);
                if (fp->kind == FTKIND_CLINK) {
                    ft_PlaySFX(fp, 0x111BC, 0x7F, 0x40);
                } else {
                    ft_PlaySFX(fp, 0x2714C, 0x7F, 0x40);
                }
            } else if (fp->mv.co.catch.x0 == (f32) da->xA0) {
                it_802A2B10(tether_gobj);
            }
        }
    }

    return false;
}

static void fn_800D949C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
        it_802A2B10(fp->fv.lk.xC);
    }
}

void ftCo_800D94D8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.lk.xC != NULL) {
        it_802A2B10(fp->fv.lk.xC);
        fp->fv.lk.xC = NULL;
    }
    ftLk_Init_BoomerangExists(gobj);
}

bool fn_800D952C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->kind == FTKIND_SAMUS) && (fp->fv.ss.x223C != NULL)) {
        return false;
    }
    return true;
}



/// #fn_800D9930

void fn_800D9C64(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->kind == FTKIND_SAMUS) {
        it_802B7B84(fp->fv.ss.x223C);
    }
}

void ftCo_800D9C98(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.ss.x223C != NULL) {
        it_802B7B84(fp->fv.ss.x223C);
        fp->fv.ss.x223C = NULL;
    }

    fp->death2_cb = NULL;
    fp->take_dmg_2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

/// #fn_800D9CE8

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


void fn_800DA190(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 state = *(s32*) ((u8*) fp + 0x4);

    switch (state) {
    case 6:
    case 13:
    case 20:
        break;
    default:
        fn_800DA054(gobj);
        break;
    }
}

/// #fn_800DA1D8

void fn_800DA2B0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CatchWait, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    fp->accessory1_cb = fn_800DA4A0;
    fp->take_dmg_cb = fn_800DA490;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftCo_CatchWait_Anim(Fighter_GObj* gobj) {}

void ftCo_CatchWait_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fn_800DA4C0(gobj)) {
        if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
            it_802A7AAC(gobj);
        } else if (fp->kind == FTKIND_SAMUS) {
            it_802BAC3C(gobj);
        }
    } else if (ftCo_800DD1E4(gobj)) {
        if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
            it_802A7AAC(gobj);
        } else if (fp->kind == FTKIND_SAMUS) {
            it_802BAC3C(gobj);
        }
    }
}

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

bool fn_800DA4C0(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->input.x668 & 0x100) {
        fn_800DA4FC(gobj);
        return true;
    }
    return false;
}

void fn_800DA4FC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->gr_vel = 0.0F;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CatchAttack, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    fp->accessory1_cb = fn_800DA678;
    fp->take_dmg_cb = fn_800DA668;
    ftCommon_8007E2F4(fp, 0x1FF);
}

#pragma push
#pragma dont_inline on

void ftCo_CatchAttack_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DA2B0(gobj);
    }
}

#pragma pop

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

#pragma push
#pragma dont_inline on

void ftCo_800DA698(Fighter_GObj* gobj, bool arg1)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    if (fp->ground_or_air == GA_Air) {
        fp->self_vel.x = -fp->facing_dir * p_ftCommonData->x374;
        fp->self_vel.y = p_ftCommonData->x378;
    } else {
        fp->gr_vel = -fp->facing_dir * p_ftCommonData->x370;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_CatchCut, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    if (arg1) {
        ftCo_CaptureCut_Enter(fp->victim_gobj);
    }
}

#pragma pop

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

void ftCo_CatchCut_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        ft_80084104(gobj);
        return;
    }
    ft_8008370C(gobj, ft_80082B1C);
}

/// #ftCo_800DA824
float ftCo_800DA824(Fighter* fp)
{
    ftCommonData* co = p_ftCommonData;
    s32 slot;
    s32 handicap;
    f32 temp;
    f32 value;

    slot = Player_80033BB8(fp->player_id) + 1;
    temp = (f32) slot;
    value = co->x364 - temp;
    value = co->x360 * value;
    handicap = Player_GetHandicap(fp->player_id);
    temp = (f32) handicap;
    temp = co->x35C - temp;
    temp = co->x358 * temp + co->x354;
    temp += value;
    return fp->dmg.x1830_percent * co->x368 + temp;
}

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

void fn_800DAC78(Fighter_GObj* gobj, Vec3* arg1)
{
    Fighter* fp = gobj->user_data;
    Vec3 sp2C;
    Vec3 sp20;

    PAD_STACK(8);

    lb_8000B1CC(GET_FIGHTER(fp->victim_gobj)->mv.co.capturedamage.x18, NULL,
                &sp2C);
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &sp20);

    arg1->x = sp2C.x - sp20.x;
    arg1->y = sp2C.y - sp20.y;
    arg1->z = sp2C.z - sp20.z;
}

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



void fn_800DAEEC(Fighter_GObj* gobj)
{
    register Fighter* temp_r31;
    register Fighter_GObj* temp_r30;
    Fighter* fp;
    Fighter* victim_fp;
    f32 dz;
    f32 dy;
    f32 dx;
    volatile u8 pad10[0x10];
    Vec3 sp34;
    Vec3 sp28;

    temp_r30 = gobj;
    temp_r31 = GET_FIGHTER(temp_r30);

    ftCommon_8007D7FC(temp_r31);
    Fighter_ChangeMotionState(temp_r30, ftCo_MS_CapturePulledLw,
                              Ft_MF_UpdateCmd, temp_r31->cur_anim_frame, 1.0F,
                              0.0F, NULL);

    fp = GET_FIGHTER(temp_r30);
    victim_fp = GET_FIGHTER(temp_r31->victim_gobj);

    lb_8000B1CC(GET_FIGHTER(fp->victim_gobj)->mv.co.capturedamage.x18, NULL,
                &sp28);
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &sp34);

    dx = sp28.x - sp34.x;
    dy = sp28.y - sp34.y;
    dz = sp28.z - sp34.z;

    if (fp->ground_or_air == GA_Ground) {
        victim_fp->x2170 = dy + fp->cur_pos.y - victim_fp->cur_pos.y;
    } else {
        victim_fp->x2170 = 0.0F;
        fp->cur_pos.x += dx;
        fp->cur_pos.y += dy;
        fp->cur_pos.z += dz;
    }
}

void ftCo_CapturePulledLw_Anim(Fighter_GObj* gobj) {}

void ftCo_CapturePulledLw_IASA(Fighter_GObj* gobj) {}

static inline void fn_800DB230_inline(Fighter_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    Vec3* pos;

    ftCommon_8007D5D4(temp_r31);
    ftCommon_UnlockECB(temp_r31);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CapturePulledHi, Ft_MF_UpdateCmd,
                              temp_r31->cur_anim_frame, 1.0F, 0.0F, NULL);
    fn_800DAA40(gobj, temp_r31->victim_gobj);
    if (!GET_FIGHTER(gobj)->x2226_b2) {
        ft_80083C00(gobj, fn_800DAECC);
    }
    pos = &temp_r31->cur_pos;
    HSD_JObjSetTranslate(GET_JOBJ(gobj), pos);
}

void ftCo_CapturePulledLw_Phys(Fighter_GObj* gobj)
{
    Fighter_GObj* temp_r30;
    Fighter* temp_r31;
    bool var_r0;
    f32 dz;
    f32 dy;
    f32 dx;
    volatile u8 pad10[0x10];
    Vec3 sp2C;
    Vec3 sp20;
    volatile u8 pad8[8];

    temp_r30 = gobj;
    temp_r31 = GET_FIGHTER(temp_r30);

    lb_8000B1CC(GET_FIGHTER(temp_r31->victim_gobj)->mv.co.capturedamage.x18, NULL,
                &sp20);
    lb_8000B1CC(
        temp_r31->parts[ftParts_GetBoneIndex(temp_r31, FtPart_XRotN)].joint,
        NULL, &sp2C);

    dy = sp20.y - sp2C.y;
    dx = sp20.x - sp2C.x;
    dz = sp20.z - sp2C.z;

    if (dy > p_ftCommonData->x3C4 * temp_r31->x34_scale.y) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }

    temp_r31->cur_pos.x += dx;
    temp_r31->cur_pos.y += dy;
    temp_r31->cur_pos.z += dz;

    if (var_r0) {
        fn_800DB230_inline(temp_r30);
    }
}

void ftCo_CapturePulledLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_8008403C(gobj, fn_800DB230);
    }
}

static void fn_800DB230(Fighter_GObj* gobj)
{
    PAD_STACK(4);
    fn_800DB230_inline(gobj);
}

void ftCo_800DB368(Fighter* attacker_fp, Fighter* fp)
{
    register HSD_JObj* jobj;
    register HSD_JObj* constraint;

    constraint =
        attacker_fp->parts[ftParts_GetBoneIndex(attacker_fp, FtPart_TransN2)]
            .joint;

    if (!fp->x2226_b2) {
        Quaternion rotate;

        jobj = fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
        PAD_STACK(0x4);

        rotate.x = rotate.y = rotate.z = rotate.w = 0.0F;
        ftParts_JObjSetRotation(jobj, &rotate);
        HSD_JObjGetTranslation(jobj, &fp->x2174);
        lb_8000C1C0(jobj, constraint);
        fp->x2226_b2 = true;
    }
}

void ftCo_800DB464(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &pos);
    pos.x = (fp->facing_dir * (fp->x1A70.z * fp->x34_scale.y)) + pos.x;
    pos.y += fp->x1A70.y * fp->x34_scale.y;
    pos.z = 0.0f;
    fp->cur_pos = pos;
}

void ftCo_800DB500(Fighter_GObj* gobj)
{
    HSD_JObj* jobj;
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2226_b2) {
        if (ftAnim_8006F368(fp, ftParts_GetBoneIndex(fp, FtPart_XRotN))) {
            jobj = fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
            HSD_JObjGetTranslation(jobj, &fp->x2174);
        }
    }

    if (fp->x2226_b2) {
        ftAnim_8006DF0C(fp);
    }
}

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



void fn_800DB790(Fighter_GObj* gobj)
{
    ftHurtboxInit hurt;
    Fighter* victim_fp;
    Fighter* fp;

    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitHi, 0, 0.0F, 1.0F, 0.0F,
                              NULL);

    if ((victim_fp = GET_FIGHTER((fp = GET_FIGHTER(gobj))->victim_gobj))
            ->kind == FTKIND_YOSHI)
    {
        fp->invisible = true;
        fp->accessory1_cb = ftCo_800DB464;
        ftColl_8007B0C0(gobj, Intangible);
        hurt.bone_idx = ftParts_GetBoneIndex(fp, FtPart_XRotN);
        hurt.height = HurtHeight_Mid;
        hurt.is_grabbable = false;
        hurt.a_offset.x = hurt.a_offset.y = hurt.a_offset.z = 0.0F;
        hurt.b_offset.x = hurt.b_offset.y = hurt.b_offset.z = 0.0F;
        hurt.scale = ftYs_Init_8012BAC0(victim_fp) / ftCommon_GetModelScale(fp);
        ftColl_HurtboxInit(fp, fp->hurt_capsules, &hurt);
    }

    ftCommon_8007E2F4(fp, 0x1FF);
}

#pragma push
#pragma dont_inline on
void fn_800DB8A4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->mv.co.capturewait.x0 += ftCo_804D90D8;
    fp->grab_timer -= p_ftCommonData->grab_timer_decrement;
    fp->mv.co.capturewait.x8 = ftCommon_GrabMash(fp, p_ftCommonData->x3A8);
}
#pragma pop

void ftCo_CaptureWaitHi_Anim(Fighter_GObj* gobj)
{
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

void fn_800DBAE4(Fighter_GObj* gobj)
{
    ftHurtboxInit hurt;
    Fighter* victim_fp;
    Fighter* fp;

    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitLw, 0, 0.0F, 1.0F, 0.0F,
                              NULL);

    if ((victim_fp = GET_FIGHTER((fp = GET_FIGHTER(gobj))->victim_gobj))
            ->kind == FTKIND_YOSHI)
    {
        fp->invisible = true;
        fp->accessory1_cb = ftCo_800DB464;
        ftColl_8007B0C0(gobj, Intangible);
        hurt.bone_idx = ftParts_GetBoneIndex(fp, FtPart_XRotN);
        hurt.height = HurtHeight_Mid;
        hurt.is_grabbable = false;
        hurt.a_offset.x = hurt.a_offset.y = hurt.a_offset.z = 0.0F;
        hurt.b_offset.x = hurt.b_offset.y = hurt.b_offset.z = 0.0F;
        hurt.scale = ftYs_Init_8012BAC0(victim_fp) / ftCommon_GetModelScale(fp);
        ftColl_HurtboxInit(fp, fp->hurt_capsules, &hurt);
    }

    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800DBBF8(Fighter_GObj* gobj)
{
    ftHurtboxInit hurt;
    Fighter* victim_fp;
    Fighter* fp;
    Fighter* fp_before = gobj->user_data;
    s32 one;
    f32 model_scale;

    ftCommon_8007D7FC(fp_before);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitLw, Ft_MF_UpdateCmd,
                              fp_before->cur_anim_frame, ftCo_804D90D4,
                              ftCo_804D90D0, NULL);

    if ((victim_fp = GET_FIGHTER((fp = GET_FIGHTER(gobj))->victim_gobj))
            ->kind == FTKIND_YOSHI)
    {
        one = true;
        fp->invisible = one;
        fp->accessory1_cb = ftCo_800DB464;
        ftColl_8007B0C0(gobj, Intangible);
        hurt.bone_idx = ftParts_GetBoneIndex(fp, FtPart_XRotN);
        hurt.height = one;
        hurt.is_grabbable = false;
        hurt.a_offset.x = hurt.a_offset.y = hurt.a_offset.z = 0.0F;
        hurt.b_offset.x = hurt.b_offset.y = hurt.b_offset.z = 0.0F;
        model_scale = ftCommon_GetModelScale(fp);
        hurt.scale = ftYs_Init_8012BAC0(victim_fp) / model_scale;
        ftColl_HurtboxInit(fp, fp->hurt_capsules, &hurt);
    }

    ftCommon_8007E2F4(fp, 0x1FF);
    fn_800DAA40(gobj, fp_before->victim_gobj);
}

void ftCo_CaptureWaitLw_Anim(Fighter_GObj* gobj)
{
    ftCo_CaptureWaitHi_Anim(gobj);
}

void ftCo_CaptureWaitLw_IASA(Fighter_GObj* gobj)
{
    fn_800DC014(gobj);
}

/// #ftCo_CaptureWaitLw_Phys

static inline void ftCo_CaptureWaitLw_Phys_inline(Fighter_GObj* gobj)
{
    register Fighter* temp_r31;
    temp_r31 = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(temp_r31);
    ftCommon_UnlockECB(temp_r31);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitHi, Ft_MF_UpdateCmd,
                              temp_r31->cur_anim_frame, ftCo_804D90D4,
                              ftCo_804D90D0, NULL);
    fn_800DB5D8(gobj);
    fn_800DAA40(gobj, temp_r31->victim_gobj);
    if (!GET_FIGHTER(gobj)->x2226_b2) {
        ft_80083C00(gobj, fn_800DBAC4);
    }
    HSD_JObjSetTranslate(GET_JOBJ(gobj), &temp_r31->cur_pos);
}

void ftCo_CaptureWaitLw_Phys(Fighter_GObj* gobj)
{
    PAD_STACK(8);

    if (fn_800DAD18(gobj)) {
        ftCo_CaptureWaitLw_Phys_inline(gobj);
    }
}

void ftCo_CaptureWaitLw_Coll(Fighter_GObj* gobj)
{
    ftCo_CapturePulledLw_Coll(gobj);
}

static inline void fn_800DBED4_inline(Fighter_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(temp_r31);
    ftCommon_UnlockECB(temp_r31);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitHi, Ft_MF_UpdateCmd,
                              temp_r31->cur_anim_frame, ftCo_804D90D4,
                              ftCo_804D90D0, NULL);
    fn_800DB5D8(gobj);
    fn_800DAA40(gobj, temp_r31->victim_gobj);
    if (!GET_FIGHTER(gobj)->x2226_b2) {
        ft_80083C00(gobj, fn_800DBAC4);
    }
    HSD_JObjSetTranslate(GET_JOBJ(gobj), &temp_r31->cur_pos);
}

void fn_800DBED4(gobj)
Fighter_GObj* gobj;
{
    PAD_STACK(4);
    fn_800DBED4_inline(gobj);
}

void fn_800DC014(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.capturewait.x0 < p_ftCommonData->x3AC) {
        if (fp->input.x668 & HSD_PAD_XY) {
            fp->mv.co.capturewait.xC = true;
        }
    }
}

bool fn_800DC044(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.y >= p_ftCommonData->tap_jump_threshold) {
        return true;
    }
    return false;
}

/// #fn_800DC070

void ftCo_CaptureJump_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.buryjump.x0 += 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

#pragma dont_inline on
void ftCo_CaptureJump_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    if (fp->mv.ca.specials.grav >= p_ftCommonData->x3B8) {
        RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
        RETURN_IF(ftCo_80095328(gobj, NULL));
        RETURN_IF(ftCo_800D7100(gobj));
        RETURN_IF(ftCo_800C3B10(gobj));
        RETURN_IF(ftCo_80099A58(gobj));
        RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
        RETURN_IF(ftCo_800D705C(gobj));
        RETURN_IF(ftCo_800CB870(gobj));
    }
}
#pragma dont_inline reset

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

#pragma push
#pragma dont_inline on
void ftCo_CaptureDamageHi_Anim(Fighter_GObj* gobj)
{
    fn_800DB8A4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DB790(gobj);
    }
}
#pragma pop

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
void ftCo_CaptureDamageLw_Anim(Fighter_GObj* gobj)
{
    fn_800DB8A4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DBAE4(gobj);
    }
}
#pragma pop

#pragma pop

#pragma push
#pragma dont_inline on
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

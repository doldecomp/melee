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
#include <melee/ft/chara/ftKirby/ftKb_Init.h>
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
#include <melee/it/items/itlinkhookshot.h>
#include <melee/it/items/itsamusgrapple.h>
#include <melee/it/items/itsscope.h>
#include <melee/lb/lb_00B0.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

/* 0D7938 */ void fn_800D7938(Fighter_GObj* gobj);
/* 0D80F4 */ static void fn_800D80F4(Fighter_GObj* gobj);
/* 0D8378 */ void fn_800D8378(Fighter_GObj* gobj);
/* 0D84D4 */ static void fn_800D84D4(Fighter_GObj* gobj, s32 arg1);
/* 0D86B8 */ static void fn_800D86B8(Fighter_GObj* gobj);
/* 0D86E0 */ extern void fn_800D86E0(Fighter_GObj* gobj);
/* 0D874C */ static void fn_800D874C(Fighter_GObj* gobj);
/* 0D8BFC */ static void fn_800D8BFC(Fighter_GObj* arg0);
/* 0D949C */ static void fn_800D949C(Fighter_GObj* gobj);
/* 0D9C64 */ static void fn_800D9C64(Fighter_GObj* gobj);
/* 0D9CE8 */ void fn_800D9CE8(Fighter_GObj* gobj);
/* 0DA004 */ static void fn_800DA004(Fighter_GObj* gobj);
/* 0DA054 */ static void fn_800DA054(Fighter_GObj* gobj);
/* 0DA190 */ static void fn_800DA190(Fighter_GObj* gobj);
/* 0DA1D8 */ static void fn_800DA1D8(Fighter_GObj* gobj);
/* 0DA2B0 */ static void fn_800DA2B0(Fighter_GObj* gobj);
/* 0DA4A0 */ static void fn_800DA4A0(Fighter_GObj* gobj);
/* 0DA4C0 */ static bool fn_800DA4C0(Fighter_GObj* gobj);
/* 0DAADC */ static void fn_800DAADC(Fighter_GObj* arg0, Fighter_GObj* arg1);
/* 0DA8E4 */ static void fn_800DA8E4(Fighter_GObj*, Fighter_GObj*, FtMotionId);
/* 0DAC78 */ static void fn_800DAC78(Fighter_GObj*, Vec3*);

void fn_800D9CE8(Fighter_GObj* gobj)
{
    Fighter* fp;
    FtMotionId msid;
    f32 anim_frame;
    void* dat_attrs;
    void* item;
    u8 pad[0x18];

    fp = gobj->user_data;
    fp->gr_vel = 0.0f;
    {
        register f32 f2 = fp->cur_anim_frame;
        anim_frame = f2;

        if (fp->motion_id == 0xD4) {
            msid = 0xD5;
            if (fp->kind == 0xE) {
                dat_attrs = fp->dat_attrs;
                if (f2 >= *(f32*)((u8*)dat_attrs + 0x124) &&
                    f2 < *(f32*)((u8*)dat_attrs + 0x128))
                {
                    anim_frame = f2 - *(f32*)((u8*)dat_attrs + 0x124);
                    ftAnim_SetAnimRate(gobj, anim_frame);
                    ftAnim_8006EBA4(gobj);
                    {
                        s32 idx = (s32)anim_frame;
                        anim_frame = (f32)((u8*)dat_attrs + 0x12C)[idx];
                    }
                }
            }
        } else {
            msid = 0xD7;
        }
    }

    switch (fp->kind) {
    case 0x6:
    case 0x14: {
        HSD_GObj* item_gobj = *(HSD_GObj**)((u8*)fp + 0x2238);
        item = item_gobj->user_data;
        it_802A7840(item_gobj);
        *(u32*)((u8*)fp + 0x2358) = *(u32*)((u8*)item + 0xDE0);
        break;
    }
    case 0xD: {
        HSD_GObj* item_gobj = *(HSD_GObj**)((u8*)fp + 0x223C);
        item = item_gobj->user_data;
        it_802BAA94(item_gobj);
        *(u32*)((u8*)fp + 0x2358) = *(u32*)((u8*)item + 0xDE0);
        break;
    }
    default: {
        u8* ptr = *(u8**)((u8*)fp->ft_data + 0x8);
        u32* parts = (u32*)fp->parts;
        *(u32*)((u8*)fp + 0x2358) = parts[ptr[0x11] * 4];
        break;
    }
    }

    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, msid, 0, anim_frame, 1.0f, 0.0f, NULL);
    fp->accessory1_cb = fn_800DA190;
    fp->x221B_b7 = false;
}

bool ftCo_800D67C4(Fighter* fp)
{
    if (fp->input.x668 & 0x200) {
        f32 x = fp->input.lstick.x;
        if (x < 0.0f) {
            x = -x;
        }
        if (x < p_ftCommonData->x218) {
            f32 y = fp->input.lstick.y;
            if (y < 0.0f) {
                y = -y;
            }
            if (y < p_ftCommonData->x21C) {
                return true;
            }
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

M2C_UNK ftCo_800D7268(void* arg0)
{
    struct { Fighter_GObj* x0; int x4; }* s = arg0;
    if (s->x4 == 4) {
        return ftKb_SpecialN_800F1CD8(s->x0);
    }
    return 0;
}

M2C_UNK ftCo_800D72A0(Fighter* fp)
{
    s32 x2C;
    s32 motion_id;
    s32 x30;
    struct Fighter_x2D0_t* x2D0 = fp->x2D0;
    
    x2C = x2D0->x2C;
    if (x2C != -1) {
        motion_id = fp->motion_id;
        if (x2C <= motion_id && motion_id < x2C + x2D0->x28) {
            return 1;
        }
    }
    x30 = x2D0->x30;
    if (x30 != -1) {
        motion_id = fp->motion_id;
        if (x30 <= motion_id && motion_id < x30 + x2D0->x28) {
            return 1;
        }
    }
    return 0;
}
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

void fn_800D7830(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 motion;

    ftCommon_8007D7FC(fp);

    if (M2C_FIELD(fp, s32*, 0x10) >= 0xA6) {
        motion = 0xA6;
    } else {
        motion = 0x9E;
    }

    Fighter_ChangeMotionState(gobj, motion, 0x0C4C5280, M2C_FIELD(fp, f32*, 0x894), M2C_FIELD(fp, f32*, 0x89C), 0.0f, NULL);
    M2C_FIELD(fp, void**, 0x21DC) = fn_800D7938;
}
/// #ftCo_ItemScopeStart_GroundToAir

void fn_800D7938(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->item_gobj != NULL) {
        s32 result = it_80291DAC(fp->item_gobj, (s32)*(f32*)((u8*)fp + 0x2340));
        if (result != -1) {
            it_80291F14(fp->item_gobj, result);
        }
        ftCommon_8007E7E4(gobj, 1);
    }
}
void ftCo_ItemScopeStart_Anim(Fighter_GObj* gobj) {}

void ftCo_ItemScopeAirStart_Anim(Fighter_GObj* gobj) {}

/// #fn_800D79B4

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
    ft_800841B8(gobj, ftCo_ItemScopeStart_GroundToAir);
}

void ftCo_ItemScopeAirStart_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D7830);
}

void fn_800D7BDC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, ftCo_MS_ItemScopeRapid), 
                              Ft_MF_SkipAttackCount, 0.0F, 1.0F, 0.0F, NULL);
    fp->mv.co.common.x0 = (int)p_ftCommonData->x5BC;
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}
void fn_800D7C60(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0xA3), 0x02000000, 0.0f, 1.0f, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
    *(s32*)((u8*)fp + 0x2340) = (s32)p_ftCommonData->x5BC;
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}
void fn_800D7CEC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0x9F), 0x0c4c5080, fp->cur_anim_frame, fp->frame_speed_mul, 0.0f, NULL);
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}
void fn_800D7D70(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0xA3), 0x0c4c5080, fp->cur_anim_frame, fp->frame_speed_mul, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->accessory4_cb = fn_800D80F4;
    fp->take_dmg_cb = fn_800D8378;
}
void ftCo_ItemScopeRapid_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);

    if (fp->cur_anim_frame >= 0.0f && fp->cur_anim_frame < fp->frame_speed_mul) {
        ft_800892A0(gobj);
        ft_80089824(gobj);
        *(s32*)((u8*)fp + 0x2340) = *(s32*)((u8*)fp + 0x2340) - 1;
        if (*(s32*)((u8*)fp + 0x2340) == 0) {
            fn_800D86E0(gobj);
        } else if (fp->item_gobj != NULL && it_8026B594(fp->item_gobj)) {
            fp = gobj->user_data;
            if (fp->ground_or_air == GA_Ground) {
                Fighter_ChangeMotionState(gobj, 0xA7, 0x0c4c5080, fp->cur_anim_frame, fp->frame_speed_mul, 0.0f, NULL);
            } else {
                Fighter_ChangeMotionState(gobj, 0xAB, 0x0c4c5080, fp->cur_anim_frame, fp->frame_speed_mul, 0.0f, NULL);
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

    if (fp->cur_anim_frame >= 0.0f && fp->cur_anim_frame < fp->frame_speed_mul) {
        ft_800892A0(gobj);
        ft_80089824(gobj);
        *(s32*)((u8*)fp + 0x2340) = *(s32*)((u8*)fp + 0x2340) - 1;
        if (*(s32*)((u8*)fp + 0x2340) == 0) {
            fn_800D874C(gobj);
        } else if (fp->item_gobj != NULL && it_8026B594(fp->item_gobj)) {
            fp = gobj->user_data;
            if (fp->ground_or_air == GA_Ground) {
                Fighter_ChangeMotionState(gobj, 0xA7, 0x0c4c5080, fp->cur_anim_frame, fp->frame_speed_mul, 0.0f, NULL);
            } else {
                Fighter_ChangeMotionState(gobj, 0xAB, 0x0c4c5080, fp->cur_anim_frame, fp->frame_speed_mul, 0.0f, NULL);
            }
            fp->accessory4_cb = fn_800D80F4;
            fp->take_dmg_cb = fn_800D8378;
        }
    }
}
void ftCo_ItemScopeRapid_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->input.x668 & 0x100) {
        *(s32*)((u8*)fp + 0x2340) = (s32)p_ftCommonData->x5BC;
    }
}
void ftCo_ItemScopeAirRapid_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->input.x668 & 0x100) {
        *(s32*)((u8*)fp + 0x2340) = (s32)p_ftCommonData->x5BC;
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

static void fn_800D80F4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->item_gobj != NULL) {
        fn_800D84D4(gobj, it_80291DAC(fp->item_gobj, 0));
    }
}
void fn_800D8140(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0xa0), 0, 0.0f, 1.0f, 0.0f, NULL);
    *(int*)((u8*)fp + 0x2340) = arg1;
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}
void fn_800D81D0(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0xa4), 0, 0.0f, 1.0f, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
    *(int*)((u8*)fp + 0x2340) = arg1;
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}
void fn_800D8268(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0xa0), 0xc4c5080, fp->cur_anim_frame, fp->frame_speed_mul, 0.0f, NULL);
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}
void fn_800D82EC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0xa4), 0xc4c5080, fp->cur_anim_frame, fp->frame_speed_mul, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->accessory4_cb = fn_800D86B8;
    fp->take_dmg_cb = fn_800D8378;
}
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

static void fn_800D86B8(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fn_800D84D4(gobj, *(s32*)((u8*)fp + 0x2340));
}

void fn_800D86E0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0xA1), 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->take_dmg_cb = fn_800D8378;
}
static void fn_800D874C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0xa5), 0, 0.0f, 1.0f, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->take_dmg_cb = fn_800D8378;
}
static void fn_800D87C0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0xa1), 0xc4c5080, fp->cur_anim_frame, fp->frame_speed_mul, 0.0f, NULL);
    fp->take_dmg_cb = fn_800D8378;
}
void fn_800D8838(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, fn_800D769C(fp, 0xa5), 0xc4c5080, fp->cur_anim_frame, fp->frame_speed_mul, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
    fp->take_dmg_cb = fn_800D8378;
}
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

static void fn_800D87C0(Fighter_GObj* gobj);

void ftCo_ItemScopeAirEnd_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800D87C0);
}

bool ftCo_Catch_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (ftCo_800951D0(gobj)) {
        return true;
    }
    if (!fn_800D8E94(gobj)) {
        return false;
    }
    if (!fn_800D952C(gobj)) {
        return false;
    }
    if ((fp->input.held_inputs & 0x80000000) && (fp->input.x668 & 0x100)) {
        ftCo_800D8C54(gobj, 0xD4);
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
    s32 x2340_val;

    if (ftCo_800952DC(gobj)) {
        return true;
    }
    if (!fn_800D8E94(gobj)) {
        return false;
    }
    if (!fn_800D952C(gobj)) {
        return false;
    }
    if ((fp->input.held_inputs & 0x80000000) && *(s32*)&fp->mv.co.catch.x0 != 0) {
        ftCo_800D8C54(gobj, 0xD6);
        return true;
    }
    x2340_val = *(s32*)&fp->mv.co.catch.x0;
    if (x2340_val != 0) {
        *(s32*)&fp->mv.co.catch.x0 = x2340_val - 1;
    }
    return false;
}
bool ftCo_800D8B9C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 x2364_val;

    if ((fp->input.x668 & 0x100) && fp->mv.co.guard.x24 != 0) {
        ftCo_800D8C54(gobj, 0xD6);
        return true;
    }
    x2364_val = fp->mv.co.guard.x24;
    if (x2364_val != 0) {
        fp->mv.co.guard.x24 = x2364_val - 1;
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
    Fighter* fp = gobj->user_data;
    ftCommon_ApplyFrictionGround(fp, p_ftCommonData->x64 * fp->co_attrs.gr_friction);
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

/// #ftCo_CatchPull_Anim

void ftCo_CatchPull_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchPull_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_ApplyFrictionGround(fp, p_ftCommonData->x64 * fp->co_attrs.gr_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

static void fn_800DA004(Fighter_GObj* gobj);

void ftCo_CatchPull_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800DA004);
}

void fn_800DA004(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_GObj* victim = fp->victim_gobj;
    ftCo_800DC920(gobj, victim);
    ftCo_Fall_Enter(gobj);
    ftCo_Fall_Enter(victim);
}

/// #fn_800DA054

void fn_800DA190(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    switch (fp->kind) {
    case 0x6:
    case 0xD:
    case 0x14:
        break;
    default:
        fn_800DA054(gobj);
        break;
    }
}

/// #fn_800DA1D8

/// #fn_800DA2B0

void ftCo_CatchWait_Anim(Fighter_GObj* gobj) {}

void ftCo_CatchWait_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fn_800DA4C0(gobj)) {
        s32 kind = fp->kind;
        if (kind == 6 || kind == 0x14) {
            it_802A7AAC(gobj);
        } else if (kind == 0xD) {
            it_802BAC3C(gobj);
        }
    } else if (ftCo_800DD1E4(gobj)) {
        s32 kind = fp->kind;
        if (kind == 6 || kind == 0x14) {
            it_802A7AAC(gobj);
        } else if (kind == 0xD) {
            it_802BAC3C(gobj);
        }
    }
}
void ftCo_CatchWait_Phys(Fighter_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    ftCommon_ApplyFrictionGround(fp, *(float*)&p_ftCommonData->x64 * fp->co_attrs.gr_friction);
    ftCommon_ApplyGroundMovement(gobj);
}
void ftCo_CatchWait_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, fn_800DA440);
}

void fn_800DA440(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_GObj* victim = fp->victim_gobj;

    PAD_STACK(8);

    ftCo_800DC920(gobj, victim);
    ftCo_Fall_Enter(gobj);
    ftCo_Fall_Enter(victim);
}
void fn_800DA490(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->take_dmg_cb = NULL;
}

void fn_800DA4A0(Fighter_GObj* gobj) {
    fn_800DA054(gobj);
}

void fn_800DA4FC(Fighter_GObj* gobj);

bool fn_800DA4C0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (fp->input.x668 & 0x100) {
        fn_800DA4FC(gobj);
        return true;
    }
    return false;
}

void fn_800DA668(Fighter_GObj* gobj);
void fn_800DA678(Fighter_GObj* gobj);

void fn_800DA4FC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->gr_vel = 0.0f;
    Fighter_ChangeMotionState(gobj, 0xD9, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->accessory1_cb = fn_800DA678;
    fp->take_dmg_cb = fn_800DA668;
    ftCommon_8007E2F4(fp, 0x1FF);
}
void ftCo_CatchAttack_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fn_800DA2B0(gobj);
    }
}

void ftCo_CatchAttack_IASA(Fighter_GObj* gobj) {}

void ftCo_CatchAttack_Phys(Fighter_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    ftCommon_ApplyFrictionGround(fp, *(float*)&p_ftCommonData->x64 * fp->co_attrs.gr_friction);
    ftCommon_ApplyGroundMovement(gobj);
}
void ftCo_CatchAttack_Coll(Fighter_GObj* gobj) {
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

void fn_800DA678(Fighter_GObj* gobj) {
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

void ftCo_CatchCut_Phys(Fighter_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_ApplyFrictionGround(fp, *(float*)&p_ftCommonData->x64 * fp->co_attrs.gr_friction);
        ftCommon_ApplyGroundMovement(gobj);
    } else {
        ft_80084DB0(gobj);
    }
}
void ftCo_CatchCut_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    
    if (fp->ground_or_air == GA_Ground) {
        ft_80084104(gobj);
    } else {
        ft_8008370C(gobj, ft_80082B1C);
    }
}
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

void fn_800DAADC(Fighter_GObj* gobj, Fighter_GObj* victim_gobj)
{
    FtMotionId msid;
    Fighter* fp1;
    Fighter* fp2;
    HSD_JObj* jobj;
    u8 pad0[4];
    Vec3 sp24;
    u8 pad1[0x14];
    Fighter* fp;

    fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        msid = 0xE2;
    } else {
        msid = 0xDF;
    }
    fn_800DA8E4(gobj, victim_gobj, msid);
    fp1 = gobj->user_data;
    fp2 = victim_gobj->user_data;
    fn_800DAC78(gobj, &sp24);
    if (fp1->ground_or_air == GA_Ground) {
        fp2->x2170 = (sp24.y + fp1->cur_pos.y) - fp2->cur_pos.y;
    } else {
        fp2->x2170 = 0.0f;
        fp1->cur_pos.x += sp24.x;
        fp1->cur_pos.y += sp24.y;
        fp1->cur_pos.z += sp24.z;
    }
    fp->coll_cb(gobj);
    jobj = gobj->hsd_obj;
    if (jobj == NULL) {
        __assert(__FILE__, 0x394, "jobj");
    }
    if (&fp->cur_pos == NULL) {
        __assert(__FILE__, 0x395, "pos");
    }
    jobj->translate = fp->cur_pos;
    HSD_JObjSetMtxDirtySub(jobj);
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

void ftCo_CaptureWaitLw_Anim(Fighter_GObj* gobj)
{
    ftCo_CaptureWaitHi_Anim(gobj);
}

void ftCo_CaptureWaitLw_IASA(Fighter_GObj* gobj)
{
    fn_800DC014(gobj);
}

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

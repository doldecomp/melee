#include "ftCo_Attack100.h"

#include "placeholder.h"
#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_084E.h"
#include "ft/ft_0892.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/types.h"

#include <hsd/jobj.h>
#include <melee/ef/efasync.h>
#include <melee/ft/chara/ftCommon/ftpickupitem.h>
#include <melee/ft/chara/ftGameWatch/ftGw_Attack100.h>
#include <melee/ft/chara/ftKirby/ftkirby.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ftdata.h>
#include <melee/it/item.h>
#include <melee/pl/plbonuslib.h>

/* 0D769C */ FtMotionId fn_800D769C(Fighter* ft, FtMotionId msid);
/* 0DA054 */ void fn_800DA054(Fighter_GObj* gobj);
/* 0DAEEC */ void fn_800DAEEC(Fighter_GObj* gobj);

extern f32 ftCo_804D90D0; // 0.0f
extern f32 ftCo_804D90D4; // Decrement value
extern f64 ftCo_804D90D8; // Increment value (Double)

typedef struct {
    u8 pad_0[0x9C];
    s32 x9C;
    s32 xA0;
    s32 xA4;
    s32 xA8;
} ftCo_SamusCatchAttrs;

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

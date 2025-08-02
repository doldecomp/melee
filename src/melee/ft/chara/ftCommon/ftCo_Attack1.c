#include <platform.h>

#include "ftCo_Attack1.h"

#include "ftCo_AttackHi3.h"
#include "ftCo_AttackHi4.h"
#include "ftCo_AttackLw3.h"
#include "ftCo_AttackLw4.h"
#include "ftCo_AttackS3.h"
#include "ftCo_AttackS4.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_Wait.h"
#include "ftpickupitem.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0CDD.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftswing.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Dash.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_Turn.h"
#include "ftCommon/ftCo_Walk.h"
#include "ftCommon/types.h"
#include "ftGameWatch/ftGw_Attack11.h"
#include "it/it_26B1.h"

#include <common_structs.h>

/* 08AB50 */ static void onPkPc21EC(Fighter_GObj* gobj);
/* 08AB84 */ static void decideAttack11(Fighter_GObj* gobj);
/* 08ABC0 */ static void checkAttack11(Fighter_GObj* gobj);
/* 08AE30 */ static void doAttack12(Fighter_GObj* gobj);
/* 08AF0C */ static bool checkAttack12(Fighter_GObj* gobj);
/* 08B194 */ static void doAttack13(Fighter_GObj* gobj);
/* 08B248 */ static bool checkAttack13(Fighter_GObj* gobj);

bool ftCo_Attack1_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_PAD_A) {
        if (fp->item_gobj != NULL) {
            if (it_8026B30C(fp->item_gobj) == 0) {
                ftCo_800957F4(gobj, ftCo_MS_LightThrowF);
                return true;
            }
            if (fp->input.held_inputs & HSD_PAD_LR) {
                ftCo_800957F4(gobj, ftCo_MS_LightThrowDrop);
                return true;
            }
            switch (it_8026B30C(fp->item_gobj)) {
            case 2:
                ftCo_Attack_800CCF58(gobj, false);
                return true;
            case 3:
                ftCo_Attack_800CDD14(gobj);
                return true;
            }
        }
        if (fp->hitlag_mul > 0 && fp->x2218_b1) {
            switch (fp->unk_msid) {
            case 44:
                doAttack12(gobj);
                return true;
            case 45:
                doAttack13(gobj);
                return true;
            }
        } else {
            decideAttack11(gobj);
            return true;
        }
    }
    if (fp->hitlag_mul > 0) {
        fp->hitlag_mul -= 1;
    }
    return false;
}

static void onPkPc21EC(Fighter_GObj* gobj)
{
    ft_800892A0(gobj);
    ft_80089824(gobj);
}

static void decideAttack11(Fighter_GObj* gobj)
{
    switch (GET_FIGHTER(gobj)->kind) {
    case FTKIND_GAMEWATCH:
        ftGw_Attack11_Enter(gobj);
        return;
    default:
        checkAttack11(gobj);
        return;
    }
}

static MotionFlags getMotionFlags(Fighter* fp)
{
    switch (fp->kind) {
    case FTKIND_PICHU:
    case FTKIND_PIKACHU:
        fp->x21EC = onPkPc21EC;
        return Ft_MF_SkipAttackCount;
    default:
        return Ft_MF_None;
    }
}

static void checkAttack11(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftpickupitem_80094790(gobj)) {
        fp->allow_interrupt = false;
        fp->x2218_b1 = false;
        Fighter_ChangeMotionState(gobj, ftCo_MS_Attack11, getMotionFlags(fp),
                                  0, 1, 0, NULL);
        ftAnim_8006EBA4(gobj);
        fp->hitlag_mul = fp->co_attrs.jab_2_input_window;
        fp->unk_msid = ftCo_MS_Attack11;
        fp->x2218_b2 = false;
        fp->mv.co.attack1.x0 = 0;
        fp->x1A54 = 0;
    }
}

void ftCo_Attack11_Anim(Fighter_GObj* arg0)
{
    u8 _[8] = { 0 };
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ft_8008A2BC(arg0);
    }
}

void ftCo_Attack11_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->allow_interrupt) {
        RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
        RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
        RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
        RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
        RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
        RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    }
    RETURN_IF(ftCo_Attack_800D6A50(gobj));
    RETURN_IF(checkAttack12(gobj));
    if (fp->allow_interrupt) {
        RETURN_IF(ftCo_Jump_CheckInput(gobj));
        RETURN_IF(ftCo_Dash_CheckInput(gobj));
        RETURN_IF(ftCo_800D5FB0(gobj));
        RETURN_IF(ftCo_Turn_CheckInput(gobj));
        RETURN_IF(ftCo_Walk_CheckInput(gobj));
    }
}

void ftCo_Attack11_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_Attack11_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}

static void doAttack12Rapid(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->kind) {
    case FTKIND_GAMEWATCH:
        ftGw_Attack11_Enter(gobj);
        return;
    default:
        checkAttack11(gobj);
        return;
    }
}

static void doAttack12Normal(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftpickupitem_80094790(gobj)) {
        fp->allow_interrupt = false;
        fp->x2218_b1 = false;
        Fighter_ChangeMotionState(gobj, ftCo_MS_Attack12, Ft_MF_None, 0, 1, 0,
                                  NULL);
        fp->hitlag_mul = fp->co_attrs.jab_3_input_window;
        fp->unk_msid = ftCo_MS_Attack12;
        fp->mv.co.attack1.x0 = 0;
    }
}

static void doAttack12(Fighter_GObj* gobj)
{
    switch (GET_FIGHTER(gobj)->kind) {
    case FTKIND_PIKACHU:
    case FTKIND_PICHU:
        doAttack12Rapid(gobj);
        return;
    default:
        doAttack12Normal(gobj);
        return;
    }
}

bool checkAttack12(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->hitlag_mul > 0) {
        fp->hitlag_mul -= 1;
        if (fp->input.x668 & HSD_PAD_A) {
            fp->mv.co.attack1.x0 = true;
        }
    }
    if (fp->mv.co.attack1.x0 && fp->x2218_b1) {
        doAttack12(gobj);
        return true;
    }
    return false;
}

void ftCo_Attack12_Anim(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Attack12_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->allow_interrupt) {
        RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
        RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
        RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
        RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
        RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
        RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    }
    RETURN_IF(ftCo_Attack_800D6A50(gobj));
    RETURN_IF(checkAttack13(gobj));
    if (fp->allow_interrupt) {
        RETURN_IF(ftCo_Jump_CheckInput(gobj));
        RETURN_IF(ftCo_Dash_CheckInput(gobj));
        RETURN_IF(ftCo_800D5FB0(gobj));
        RETURN_IF(ftCo_Turn_CheckInput(gobj));
        RETURN_IF(ftCo_Walk_CheckInput(gobj));
    }
}

static void doAttack13(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->kind) {
    case FTKIND_MARS:
        doAttack12Rapid(gobj);
        return;
    default:
        if (!ftpickupitem_80094790(gobj)) {
            fp->allow_interrupt = false;
            fp->x2218_b1 = false;
            Fighter_ChangeMotionState(gobj, ftCo_MS_Attack13, Ft_MF_None, 0, 1,
                                      0, NULL);
        }
        return;
    }
}

bool checkAttack13(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->hitlag_mul > 0) {
        fp->hitlag_mul -= 1;
        if (fp->input.x668 & HSD_PAD_A) {
            fp->mv.co.attack1.x0 = true;
        }
    }
    if (fp->mv.co.attack1.x0 && fp->x2218_b1) {
        doAttack13(gobj);
        return true;
    }
    return false;
}

void ftCo_Attack13_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Attack13_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftCo_Attack_800D6A50(gobj) && fp->allow_interrupt) {
        ftCo_Wait_IASA(gobj);
    }
}

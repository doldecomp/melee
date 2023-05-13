#include <platform.h>
#include "forward.h"
#include "ft/forward.h"
#include <baselib/forward.h>

#include "ftCo_Attack1.h"

#include "ftCo_08A6.h"
#include "ftCo_AttackS3.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ftGameWatch/ftGw_Attack11.h"

#include <common_structs.h>
#include <placeholder.h>

/* 08AB50 */ static void onPkPc21EC(ftCo_GObj* gobj);
/* 08AB84 */ static void decideAttack11(ftCo_GObj* gobj);
/* 08ABC0 */ static void checkAttack11(ftCo_GObj* gobj);
/* 08AE30 */ static void doAttack12(ftCo_GObj* gobj);
/* 08AF0C */ static bool checkAttack12(ftCo_GObj* gobj);
/* 08B194 */ static void doAttack13(ftCo_GObj* gobj);
/* 08B248 */ static bool checkAttack13(ftCo_GObj* gobj);

bool ftCo_Attack1_DecideMotion(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_Pad_A) {
        if (fp->item_gobj != NULL) {
            if (it_8026B30C(fp->item_gobj) == 0) {
                ft_800957F4(gobj, ftCo_MS_LightThrowF);
                return true;
            }
            if (fp->input.held_inputs & HSD_Pad_LR) {
                ft_800957F4(gobj, ftCo_MS_LightThrowDrop);
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

static void onPkPc21EC(ftCo_GObj* gobj)
{
    ft_800892A0(gobj);
    ft_80089824(gobj);
}

static void decideAttack11(ftCo_GObj* gobj)
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

static MotionFlags getMotionFlags(ftCo_Fighter* fp)
{
    switch (fp->kind) {
    case FTKIND_PICHU:
    case FTKIND_PIKACHU:
        fp->cb.x21EC_callback = onPkPc21EC;
        return Ft_MF_SkipAttackCount;
    default:
        return Ft_MF_None;
    }
}

static void checkAttack11(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80094790(gobj)) {
        fp->x2218_b0 = false;
        fp->x2218_b1 = false;
        Fighter_ChangeMotionState(gobj, ftCo_MS_Attack11, getMotionFlags(fp),
                                  NULL, 0, 1, 0);
        ftAnim_8006EBA4(gobj);
        fp->hitlag_mul = fp->co_attrs.x18C_Jab_2InputWindow;
        fp->unk_msid = ftCo_MS_Attack11;
        fp->x2218_b2 = false;
        fp->mv.co.attack1.x0 = 0;
        fp->x1A54 = 0;
    }
}

void ftCo_Attack11_Anim(ftCo_GObj* arg0)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ft_8008A2BC(arg0);
    }
}

void ftCo_Attack11_IASA(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if ((!fp->x2218_b0 ||
         (!ft_8008BFC4(gobj) && !ft_8008C830(gobj) && !ft_8008CB44(gobj) &&
          !ftCo_AttackS3_8008B658(gobj) && !ft_8008B980(gobj) &&
          !ft_8008BB44(gobj))) &&
        !ftCo_Attack_800D6A50(gobj) && !checkAttack12(gobj) && fp->x2218_b0 &&
        !ft_800CAED0(gobj) && !ft_800CA094(gobj) && !ft_800D5FB0(gobj) &&
        !ft_800C97DC(gobj) && !ft_800C9468(gobj))
    {
        return;
    }
}

void ftCo_Attack11_Phys(ftCo_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_Attack11_Coll(ftCo_GObj* gobj)
{
    ft_80084104(gobj);
}

static void doAttack12Rapid(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->kind) {
    case FTKIND_GAMEWATCH:
        ftGw_Attack11_Enter(gobj);
        return;
    default:
        checkAttack11(gobj);
        return;
    }
}

static void doAttack12Normal(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80094790(gobj)) {
        fp->x2218_b0 = false;
        fp->x2218_b1 = false;
        Fighter_ChangeMotionState(gobj, ftCo_MS_Attack12, Ft_MF_None, NULL, 0,
                                  1, 0);
        fp->hitlag_mul = fp->co_attrs.x190_Jab_3InputWindow;
        fp->unk_msid = ftCo_MS_Attack12;
        fp->mv.co.attack1.x0 = 0;
    }
}

static void doAttack12(ftCo_GObj* gobj)
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

bool checkAttack12(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->hitlag_mul > 0) {
        fp->hitlag_mul -= 1;
        if (fp->input.x668 & HSD_Pad_A) {
            fp->mv.co.attack1.x0 = true;
        }
    }
    if (fp->mv.co.attack1.x0 && fp->x2218_b1) {
        doAttack12(gobj);
        return true;
    }
    return false;
}

void ftCo_Attack12_Anim(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Attack12_IASA(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if ((!fp->x2218_b0 ||
         (!ft_8008BFC4(gobj) && !ft_8008C830(gobj) && !ft_8008CB44(gobj) &&
          !ftCo_AttackS3_8008B658(gobj) && !ft_8008B980(gobj) &&
          !ft_8008BB44(gobj))) &&
        !ftCo_Attack_800D6A50(gobj) && !checkAttack13(gobj) && fp->x2218_b0 &&
        !ft_800CAED0(gobj) && !ft_800CA094(gobj) && !ft_800D5FB0(gobj) &&
        !ft_800C97DC(gobj) && !ft_800C9468(gobj))
    {
        return;
    }
}

static void doAttack13(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->kind) {
    case FTKIND_MARS:
        doAttack12Rapid(gobj);
        return;
    default:
        if (!ft_80094790(gobj)) {
            fp->x2218_b0 = false;
            fp->x2218_b1 = false;
            Fighter_ChangeMotionState(gobj, ftCo_MS_Attack13, Ft_MF_None, NULL,
                                      0, 1, 0);
        }
        return;
    }
}

bool checkAttack13(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->hitlag_mul > 0) {
        fp->hitlag_mul -= 1;
        if (fp->input.x668 & HSD_Pad_A) {
            fp->mv.co.attack1.x0 = true;
        }
    }
    if (fp->mv.co.attack1.x0 && fp->x2218_b1) {
        doAttack13(gobj);
        return true;
    }
    return false;
}

void ftCo_Attack13_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Attack13_IASA(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (!ftCo_Attack_800D6A50(gobj) && fp->x2218_b0) {
        ftCo_Wait_IASA(gobj);
    }
}

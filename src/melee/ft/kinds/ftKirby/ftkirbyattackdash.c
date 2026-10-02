/**
 * @file ftkirbyattackdash.c
 * @brief Dash Attack
 * @details Kirby's Dash Attack logic in Melee
 * Module prefix: ft (Fighter)
 */
#include "ftkirbyattackdash.h"

#include <melee/ft/forward.h>

#include <stddef.h>

#include "forward.h"
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackDash.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/types.h>

/* 0F1FDC */ static void fn_800F1FDC(Fighter_GObj* gobj);
/* 0F20C4 */ static void fn_800F20C4(Fighter_GObj* gobj);

/**
 * @brief Dash Attack logic for ftKb_SpecialN_800F1F68
 * @param gobj 
 */
void ftKb_SpecialN_800F1F68(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = false;
    Fighter_ChangeMotionState(gobj, ftKb_MS_AttackDash, Ft_MF_None, 0.0f, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.co.attackdash.x0 = 0;
}

/**
 * @brief Dash Attack logic for fn_800F1FDC
 * @param gobj 
 */
void fn_800F1FDC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_AttackDash, 0x0C4C5082U,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0,
                              NULL);
}

/**
 * @brief Dash Attack logic for ftKb_AttackDash_Anim
 * @param gobj 
 */
void ftKb_AttackDash_Anim(Fighter_GObj* gobj)
{
    ftCo_AttackDash_Anim(gobj);
}

/**
 * @brief Dash Attack logic for ftKb_AttackDash_IASA
 * @param gobj 
 */
void ftKb_AttackDash_IASA(Fighter_GObj* gobj)
{
    ftCo_AttackDash_IASA(gobj);
}

/**
 * @brief Dash Attack logic for ftKb_AttackDash_Phys
 * @param gobj 
 */
void ftKb_AttackDash_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

/**
 * @brief Dash Attack logic for ftKb_AttackDash_Coll
 * @param gobj 
 */
void ftKb_AttackDash_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F20C4);
}

/**
 * @brief Dash Attack logic for fn_800F20C4
 * @param gobj 
 */
void fn_800F20C4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_AttackDashAir, 0x0C4C5082,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0f,
                              NULL);
}

/**
 * @brief Dash Attack logic for ftKb_AttackDashAir_Anim
 * @param gobj 
 */
void ftKb_AttackDashAir_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_AttackDashAir_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Dash Attack logic for ftKb_AttackDashAir_Phys
 * @param gobj 
 */
void ftKb_AttackDashAir_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_80085204(gobj);
    ftCommon_FallBasic(fp);
}

/**
 * @brief Dash Attack logic for ftKb_AttackDashAir_Coll
 * @param gobj 
 */
void ftKb_AttackDashAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F1FDC);
}

/**
 * @brief Dash Attack logic for ftKb_AttackDashAir_800F21C0
 * @param gobj 
 */
float ftKb_AttackDashAir_800F21C0(Fighter_GObj* gobj)
{
    return ftPartGetRotX(GET_FIGHTER(gobj), 0);
}

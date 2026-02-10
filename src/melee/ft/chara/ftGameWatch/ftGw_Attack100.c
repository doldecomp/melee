#include "ftGw_Attack100.h"

#include "ftGw_Attack11.h"
#include "ftGw_Init.h"

#include "forward.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ftCommon/ftCo_Attack100.h"

#include <stddef.h>

/// 0x8014C1E8
/// https://decomp.me/scratch/AyScb // Mr. Game & Watch's Rapid Jab Start Action
/// State handler
void ftGw_Attack100Start_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_800D6B00(gobj, ftGw_MS_Attack100Start);
    fp->accessory4_cb = ftGw_Attack11_ItemGreenhouseSetup;
}

/// 0x8014C224
/// https://decomp.me/scratch/sBY5w // Mr. Game & Watch's Rapid Jab Start
/// Animation callback
void ftGw_Attack100Start_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftGw_Attack100Loop_Enter(gobj);
    }
}

/// 0x8014C260 - Mr. Game & Watch's Rapid Jab Start IASA callback
void ftGw_Attack100Start_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x8014C264 - Mr. Game & Watch's Rapid Jab Start Physics callback
void ftGw_Attack100Start_Phys(HSD_GObj* gobj)
{
    ft_80084FA8(gobj);
}

/// 0x8014C284 - Mr. Game & Watch's Rapid Jab Start Collision callback
void ftGw_Attack100Start_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
    ftGw_Init_8014A538(gobj);
}

/// 0x8014C2B8
/// https://decomp.me/scratch/npI0e // Mr. Game & Watch's Rapid Jab Loop Acion
/// State handler
void ftGw_Attack100Loop_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, ftGw_MS_Attack100Loop, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    fp->accessory4_cb = ftGw_Attack11_DecideAction;
}

/// 0x8014C308
/// https://decomp.me/scratch/39K2l // Mr. Game & Watch's Rapid Jab Loop
/// Animation callback
void ftGw_Attack100Loop_Anim(HSD_GObj* gobj)
{
    ftCo_800D6C60(gobj, ftGw_Attack100End_Enter);
}

/// 0x8014C330 - Mr. Game & Watch's Rapid Jab Loop IASA callback
void ftGw_Attack100Loop_IASA(HSD_GObj* gobj)
{
    ftCo_Attack100Loop_IASA(gobj);
}

/// 0x8014C350 - Mr. Game & Watch's Rapid Jab Loop Physics callback
void ftGw_Attack100Loop_Phys(HSD_GObj* gobj)
{
    ft_80084FA8(gobj);
}

/// 0x8014C370 - Mr. Game & Watch's Rapid Jab Loop Collision callback
void ftGw_Attack100Loop_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
    ftGw_Init_8014A538(gobj);
}

/// 0x8014C3A4 - Mr. Game & Watch's Rapid Jab End Motion State handler
void ftGw_Attack100End_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, ftGw_MS_Attack100End, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    fp->accessory4_cb = ftGw_Attack11_DecideAction;
}

/// 0x8014C3F4 - Mr. Game & Watch's Rapid Jab End Animation callback
void ftGw_Attack100End_Anim(HSD_GObj* gobj)
{
    ftCo_Attack100End_Anim(gobj);
}

/// 0x8014C414 - Mr. Game & Watch's Rapid Jab End IASA callback
void ftGw_Attack100End_IASA(HSD_GObj* gobj)
{
    return;
}

/// 0x8014C418 - Mr. Game & Watch's Rapid Jab End Physics callback
void ftGw_Attack100End_Phys(HSD_GObj* gobj)
{
    ft_80084FA8(gobj);
}

/// 0x8014C438 - Mr. Game & Watch's Rapid Jab End Collision callback
void ftGw_Attack100End_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
    ftGw_Init_8014A538(gobj);
}

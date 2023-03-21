#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>

// 0x8014C1E8
// https://decomp.me/scratch/AyScb // Mr. Game & Watch's Rapid Jab Start Action
// State handler
void ftGameWatch_Attack100Start_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_800D6B00(gobj, AS_GAMEWATCH_ATTACK100START);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemGreenhouseSetup;
}

// 0x8014C224
// https://decomp.me/scratch/sBY5w // Mr. Game & Watch's Rapid Jab Start
// Animation callback
void ftGameWatch_Attack100Start_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        ftGameWatch_Attack100Loop_Action(gobj);
}

// 0x8014C260 - Mr. Game & Watch's Rapid Jab Start IASA callback
void ftGameWatch_Attack100Start_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014C264 - Mr. Game & Watch's Rapid Jab Start Physics callback
void ftGameWatch_Attack100Start_Phys(HSD_GObj* gobj)
{
    func_80084FA8(gobj);
}

// 0x8014C284 - Mr. Game & Watch's Rapid Jab Start Collision callback
void ftGameWatch_Attack100Start_Coll(HSD_GObj* gobj)
{
    func_80084104(gobj);
    ftGameWatch_8014A538(gobj);
}

// 0x8014C2B8
// https://decomp.me/scratch/npI0e // Mr. Game & Watch's Rapid Jab Loop Acion
// State handler
void ftGameWatch_Attack100Loop_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ActionStateChange_800693AC(gobj, AS_GAMEWATCH_ATTACK100LOOP, 0,
                                       NULL, 0.0f, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_Attack11_DecideAction;
}

// 0x8014C308
// https://decomp.me/scratch/39K2l // Mr. Game & Watch's Rapid Jab Loop
// Animation callback
void ftGameWatch_Attack100Loop_Anim(HSD_GObj* gobj)
{
    func_800D6C60(gobj, ftGameWatch_Attack100End_Action);
}

// 0x8014C330 - Mr. Game & Watch's Rapid Jab Loop IASA callback
void ftGameWatch_Attack100Loop_IASA(HSD_GObj* gobj)
{
    func_800D6E70(gobj);
}

// 0x8014C350 - Mr. Game & Watch's Rapid Jab Loop Physics callback
void ftGameWatch_Attack100Loop_Phys(HSD_GObj* gobj)
{
    func_80084FA8(gobj);
}

// 0x8014C370 - Mr. Game & Watch's Rapid Jab Loop Collision callback
void ftGameWatch_Attack100Loop_Coll(HSD_GObj* gobj)
{
    func_80084104(gobj);
    ftGameWatch_8014A538(gobj);
}

// 0x8014C3A4 - Mr. Game & Watch's Rapid Jab End Action State handler
void ftGameWatch_Attack100End_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ActionStateChange_800693AC(gobj, AS_GAMEWATCH_ATTACK100END, 0,
                                       NULL, 0.0f, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_Attack11_DecideAction;
}

// 0x8014C3F4 - Mr. Game & Watch's Rapid Jab End Animation callback
void ftGameWatch_Attack100End_Anim(HSD_GObj* gobj)
{
    func_800D6E34(gobj);
}

// 0x8014C414 - Mr. Game & Watch's Rapid Jab End IASA callback
void ftGameWatch_Attack100End_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014C418 - Mr. Game & Watch's Rapid Jab End Physics callback
void ftGameWatch_Attack100End_Phys(HSD_GObj* gobj)
{
    func_80084FA8(gobj);
}

// 0x8014C438 - Mr. Game & Watch's Rapid Jab End Collision callback
void ftGameWatch_Attack100End_Coll(HSD_GObj* gobj)
{
    func_80084104(gobj);
    ftGameWatch_8014A538(gobj);
}

#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>

extern HSD_GObj* func_802C68F8(HSD_GObj*, Vec3*, s32, f32);

// 0x8014A848 //
// https://decomp.me/scratch/hi2oZ // Spawn Fire Attack Torch and set up callbacks //
void ftGameWatch_ItemTorchSetup(HSD_GObj* fighter_gobj)
{
    Vec3 sp10;
    Fighter* fp;
    HSD_GObj* x2254_fireGObj;

    fp = getFighter(fighter_gobj);
    func_8000B1CC(fp->x5E8_fighterBones[0x20].x0_jobj, NULL, &sp10);
    fp->sa.gaw.x2254_fireGObj = func_802C68F8(fighter_gobj, &sp10, 0x20, fp->x2C_facing_direction);
    if (fp->sa.gaw.x2254_fireGObj != NULL)
    {
        if (fp->cb.x21E4_callback_OnDeath2 == NULL)
        {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        }
        if (fp->cb.x21DC_callback_OnTakeDamage == NULL)
        {
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        }
    }
    fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_ItemTorchEnterHitlag;
    fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_ItemTorchExitHitlag;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014A904
// https://decomp.me/scratch/rtVt4 // Set flags on Mr. Game & Watch's Torch //
void ftGameWatch_ItemTorchSetFlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftGameWatch_ItemTorchExitHitlag(fighter_gobj);
    fp->sa.gaw.x2254_fireGObj = NULL;
}

extern void func_802C6A2C(HSD_GObj*);

// 0x8014A938 //
// https://decomp.me/scratch/mIWB3 // Remove Mr. Game & Watch's Torch //
void ftGameWatch_ItemTorchOnDamage(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* fireGObj;

    if (fp->sa.gaw.x2254_fireGObj != NULL)
    {
        func_802C6A2C(fp->sa.gaw.x2254_fireGObj);
        ftGameWatch_ItemTorchSetFlag(fighter_gobj);
    }
}

extern void func_802C6A78(HSD_GObj*);
extern void func_802C6A98(HSD_GObj*);

// 0x8014A990
// https://decomp.me/scratch/Y9bAE // Apply hitlag to Mr. Game & Watch's item
void ftGameWatch_ItemTorchEnterHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->sa.gaw.x2254_fireGObj != NULL)
    {
        func_802C6A78(fp->sa.gaw.x2254_fireGObj);
    }
}

// 0x8014A9C0 
// https://decomp.me/scratch/OGia3 // End hitlag for Mr. Game & Watch's item
void ftGameWatch_ItemTorchExitHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->sa.gaw.x2254_fireGObj != NULL)
    {
        func_802C6A98(fp->sa.gaw.x2254_fireGObj);
    }
}

// 0x8014A9F0 
// https://decomp.me/scratch/cYfwo // Check if Mr. Game & Watch is performing Forward Smash 
BOOL ftGameWatch_ItemCheckTorchRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x10_action_state_index == AS_GAMEWATCH_ATTACKS4)
    {
        return FALSE;
    }
    return TRUE;
}

// 0x8014AA10 
// https://decomp.me/scratch/GDWNx // Mr. Game & Watch's Forward Smash Action State handler
void ftGameWatch_AttackS4_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 unused;

    fp->x2218_flag.bits.b0 = 0;
    fp->x2200_ftcmd_var0 = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_ATTACKS4, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemTorchSetup;
}

// 0x8014AA88 
// https://decomp.me/scratch/41MqW // Mr. Game & Watch's Forward Smash Animation callback
void ftGameWatch_AttackS4_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

extern void func_8008A4D4(HSD_GObj*);

// 0x8014AAC4 
// https://decomp.me/scratch/njlQ8 // Mr. Game & Watch's Forward Smash IASA callback
void ftGameWatch_AttackS4_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x2218_flag.bits.b0 != 0)
    {
        func_8008A4D4(fighter_gobj);
    }
}

// 0x8014AAF4 
// https://decomp.me/scratch/hNIyC // Mr. Game & Watch's Forward Smash Physics callback
void ftGameWatch_AttackS4_Phys(HSD_GObj* fighter_gobj)
{
    func_80084FA8(fighter_gobj);
}

// 0x8014AB14
// https://decomp.me/scratch/OHANe
void ftGameWatch_AttackS4_Coll(HSD_GObj* fighter_gobj) // Mr. Game & Watch's Forward Smash Collision callback
{
    func_80084104(fighter_gobj);
    ftGameWatch_8014A538(fighter_gobj);
}

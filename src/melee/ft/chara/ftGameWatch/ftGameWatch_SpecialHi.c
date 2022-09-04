#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>

extern HSD_GObj* func_802C8038(HSD_GObj*, Vec3*, s32, s32, f32, f32);
void ftGameWatch_ItemRescueEnterHitlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemRescueExitHitlag(HSD_GObj* fighter_gobj);

// 0x8014DEF0
// https://decomp.me/scratch/6Vtu9 // Create Fire Rescue item
void ftGameWatch_ItemRescueSetup(HSD_GObj* fighter_gobj)
{
    Vec3 sp10;
    f32 temp;
    Fighter* fp;
    HSD_GObj* rescueGObj;

    fp = fighter_gobj->user_data;
    if ((u32)fp->sa.gaw.x226C_rescueGObj == 0)
    {
        func_8000B1CC(fp->x5E8_fighterBones[0].x0_jobj, NULL, &sp10);
        sp10.y = -((2.5f * Fighter_GetModelScale(fp)) - sp10.y);
        rescueGObj = func_802C8038(fighter_gobj, &sp10, 0, fp->x10_action_state_index - 0x175, fp->x2C_facing_direction, 2.5f);
        fp->sa.gaw.x226C_rescueGObj = rescueGObj;
        if (rescueGObj != NULL)
        {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        }
        fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_ItemRescueEnterHitlag;
        fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_ItemRescueExitHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014DFB8
// https://decomp.me/scratch/Wu4WV // Check if Mr. Game & Watch is performing Fire Rescue
BOOL ftGameWatch_ItemCheckRescueRemove(HSD_GObj* fighter_gobj)
{
    s32 ASID = ((Fighter*)fighter_gobj->user_data)->x10_action_state_index;

    switch (ASID)
    {
    case AS_GAMEWATCH_SPECIALHI:
    case AS_GAMEWATCH_SPECIALAIRHI:
        return FALSE;
    default:
        return TRUE;
    }
}

// 0x8014DFE4 - Set Fire Rescue GObj pointer and callbacks to NULL
void ftGameWatch_ItemRescueSetNULL(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    fp->sa.gaw.x226C_rescueGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

extern void func_802C8158(HSD_GObj*);

// 0x8014DFFC - Remove Fire Rescue item
void ftGameWatch_ItemRescueRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* rescueGObj;
    HSD_GObj* rescueGObj2;

    if (fp->sa.gaw.x226C_rescueGObj != NULL)
    {
        func_802C8158(fp->sa.gaw.x226C_rescueGObj);
        ftGameWatch_ItemRescueSetNULL(fighter_gobj);
    }
}

extern void func_802C81C8(HSD_GObj*);
extern void func_802C81E8(HSD_GObj*);

// 0x8014E04C - Apply hitlag to Fire Rescue item
void ftGameWatch_ItemRescueEnterHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.gaw.x226C_rescueGObj != NULL)
    {
        func_802C81C8(fp->sa.gaw.x226C_rescueGObj);
    }
}

// 0x8014E06C - Remove hitlag for Fire Rescue item
void ftGameWatch_ItemRescueExitHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.gaw.x226C_rescueGObj != NULL)
    {
        func_802C81E8(fp->sa.gaw.x226C_rescueGObj);
    }
}

extern void func_8007D60C(Fighter*);
extern void func_80088510(Fighter*, s32, u8, u8);

inline void ftGameWatch_SpecialHi_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemRescueSetup;
}

// 0x8014E0AC
// https://decomp.me/scratch/4Dc4b // Mr. Game & Watch's grounded Fire Rescue Action State handler
void ftGameWatch_SpecialHi_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* rescueGObj;
    void(*cb_Accessory4)(HSD_GObj*);
    s32 sfx;
    s8 pan;
    s8 volume;
    f32 temp;
    f32 vel;

    fp->x74_anim_vel.y = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALHI, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftGameWatch_SpecialHi_SetVars(fighter_gobj);
    func_8006EBA4(fighter_gobj);
    func_80088510(fp, 0x46D12, 0x7F, 0x40);
}

// 0x8014E158 - Mr. Game & Watch's aerial Fire Rescue Action State handler
void ftGameWatch_SpecialAirHi_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* rescueGObj;
    void(*cb_Accessory4)(HSD_GObj*);
    s32 var;
    s32 var2;
    s32 sfx;
    s8 pan;
    s8 volume;
    f32 temp;
    f32 vel;

    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_GAMEWATCH_SPECIALAIRHI, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftGameWatch_SpecialHi_SetVars(fighter_gobj);
    func_8006EBA4(fighter_gobj);
    func_80088510(fp, 0x46D12, 0x7F, 0x40);
}

// 0x8014E1F8 - Mr. Game & Watch's grounded Fire Rescue Animation callback
void ftGameWatch_SpecialHi_Anim(HSD_GObj* fighter_gobj)
{
    ftGameWatch_SpecialAirHi_Anim(fighter_gobj);
}

// 0x8014E218
// https://decomp.me/scratch/QRkS8 // Mr. Game & Watch's aerial Fire Rescue Animation callback
void ftGameWatch_SpecialAirHi_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftGameWatchAttributes* gawAttrs;
    f32 temp;

    gawAttrs = ((Fighter*)fighter_gobj->user_data)->x2D4_specialAttributes;
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) 
    {
        if (0.0f == gawAttrs->x60_GAMEWATCH_RESCUE_LANDING)
        {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 0, 1, 1.0f, gawAttrs->x60_GAMEWATCH_RESCUE_LANDING);
    }
}

void ftGameWatch_SpecialAirHi_IASA(HSD_GObj*);

// 0x8014E290 - Mr. Game & Watch's grounded Fire Rescue IASA callback
void ftGameWatch_SpecialHi_IASA(HSD_GObj* fighter_gobj)
{
    ftGameWatch_SpecialAirHi_IASA(fighter_gobj);
}

// 0x8014E2B0
// https://decomp.me/scratch/2aEQN // Mr. Game & Watch's aerial Fire Rescue IASA callback
void ftGameWatch_SpecialAirHi_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftGameWatchAttributes* gawAttrs = fp->x2D4_specialAttributes;
    f32 stick_x;
    f32 stick_range_min;
    f32 temp;
    f32 angle;
    f32 facing_dir;
    f32 stick_range_threshold;

    if ((u32)fp->x2200_ftcmd_var0 == 0)
    {
        stick_x = stickGetDir(fp->input.x620_lstick_x, 0.0f);
        if (stick_x > gawAttrs->x58_GAMEWATCH_RESCUE_STICK_RANGE)
        {
            stick_range_threshold = stick_x - gawAttrs->x58_GAMEWATCH_RESCUE_STICK_RANGE;
            if (fp->input.x620_lstick_x > 0.0f)
            {
                facing_dir = 1.0f;
            }
            else facing_dir = -1.0f;

            temp = stick_range_threshold * facing_dir;
            angle = temp * gawAttrs->x5C_GAMEWATCH_RESCUE_ANGLE_UNK;
            func_8007D9FC(fp);
            func_80075AF0(fp, 0, (M_PI / 2) * fp->x2C_facing_direction);
            fp->x6BC_inputStickangle = -angle;
            fp->x2200_ftcmd_var0 = 1;
        }
    }
}

// 0x8014E374 - Mr. Game & Watch's grounded Fire Rescue Physics callback
void ftGameWatch_SpecialHi_Phys(HSD_GObj* fighter_gobj)
{
    ftGameWatch_SpecialAirHi_Phys(fighter_gobj);
}

// 0x8014E394 - Mr. Game & Watch's aerial Fire Rescue Physics callback
void ftGameWatch_SpecialAirHi_Phys(HSD_GObj* fighter_gobj)
{
    func_80085154(fighter_gobj);
}

// 0x8014E3B4 - Mr. Game & Watch's grounded Fire Rescue Collision callback
void ftGameWatch_SpecialHi_Coll(HSD_GObj* fighter_gobj)
{
    ftGameWatch_SpecialAirHi_Coll(fighter_gobj);
}

extern BOOL EnvColl_CheckGroundAndLedge(HSD_GObj*, s32);
extern BOOL func_80081298(HSD_GObj*);
extern void func_80081370(HSD_GObj*);

// 0x8014E3D4
// https://decomp.me/scratch/4IC4C // Mr. Game & Watch's aerial Fire Rescue Collision callback
void ftGameWatch_SpecialAirHi_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftGameWatchAttributes* gawAttrs;
    f32 animFrame;
    s32 ledgeGrabDir;

    fp = getFighter(fighter_gobj);
    gawAttrs = getFtSpecialAttrs(fp);
    if (fp->x894_currentAnimFrame > 4.0f)
    {
        if (fp->x80_self_vel.y >= 0.0f)
        {
            if (func_80081D0C(fighter_gobj) != FALSE)
            {
                ftGameWatch_ItemRescueRemove(fighter_gobj);
                func_8007D7FC(fp);
                func_800D5CB0(fighter_gobj, 0, gawAttrs->x60_GAMEWATCH_RESCUE_LANDING);
                fp->cb.x21E4_callback_OnDeath2 = NULL;
                fp->cb.x21DC_callback_OnTakeDamage = NULL;
            }
        }
        else
        {
            if (1.0f == fp->x2C_facing_direction)
            {
                ledgeGrabDir = 1;
            }
            else ledgeGrabDir = -1;
            if (EnvColl_CheckGroundAndLedge(fighter_gobj, ledgeGrabDir) != FALSE)
            {
                func_800D5CB0(fighter_gobj, 0, gawAttrs->x60_GAMEWATCH_RESCUE_LANDING);
                return;
            }
            if (func_80081298(fighter_gobj) != FALSE)
            {
                func_80081370(fighter_gobj);
            }
        }
    }
}

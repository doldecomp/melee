#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>

extern HSD_GObj* func_802C6C38(HSD_GObj*, Vec3*, s32, f32);

// 0x8014AFC0
// https://decomp.me/scratch/wJ5b7 // Create Parachute Item
void ftGameWatch_ItemParachuteSetup(HSD_GObj* fighter_gobj)
{
    Vec3 sp10;
    HSD_GObj* parachuteGObj;
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x2258_parachuteGObj != NULL)
    {
        ftGameWatch_ItemParachuteOnLand(fighter_gobj);
    }
    else
    {
        func_8000B1CC(fp->x5E8_fighterBones[0x1].x0_jobj, NULL, &sp10);
        fp->sa.gaw.x2258_parachuteGObj = func_802C6C38(fighter_gobj, &sp10, 1, fp->x2C_facing_direction);
        if (fp->sa.gaw.x2258_parachuteGObj != NULL)
        {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
            fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_AttackAir_EnterItemHitlag;
            fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_AttackAir_ExitItemHitlag;
        }
    }
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

extern void func_802C6E50(HSD_GObj*);

// 0x8014B074
// https://decomp.me/scratch/TaqkV // Parachute Accessory Callback - Landing Lag
void ftGameWatch_ItemParachuteOnLand(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x2258_parachuteGObj != NULL)
    {
        ftGameWatch_AttackAir_ExitItemHitlag(fighter_gobj);
        if (fp->x10_action_state_index == AS_GAMEWATCH_LANDINGAIRN)
        {
            func_802C6E50(fp->sa.gaw.x2258_parachuteGObj);
        }
        fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_AttackAir_EnterItemHitlag;
        fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_AttackAir_ExitItemHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

void ftGameWatch_AttackAir_ExitItemHitlag(HSD_GObj*);

// 0x8014B0F0
// https://decomp.me/scratch/8jiZT // Parachute item flag update on land + clear pointers
void ftGameWatch_ItemParachuteSetFlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    ftGameWatch_AttackAir_ExitItemHitlag(fighter_gobj);
    fp->sa.gaw.x2258_parachuteGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

extern void func_802C6D6C(HSD_GObj*);

// 0x8014B12C
// https://decomp.me/scratch/KYJBx // Remove Parachute item
void ftGameWatch_ItemParachuteRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* parachuteGObj;

    if (fp->sa.gaw.x2258_parachuteGObj != NULL)
    {
        func_802C6D6C(fp->sa.gaw.x2258_parachuteGObj);
        ftGameWatch_ItemParachuteSetFlag(fighter_gobj);
    }
}

// 0x8014B18C
// https://decomp.me/scratch/hJ3U1 // Check if Mr. Game & Watch is performing Neutral Aerial / Neutral Aerial landing
BOOL ftGameWatch_ItemCheckParachuteRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 ASID = fp->x10_action_state_index;

    if ((ASID >= AS_GAMEWATCH_ATTACKAIRN) && (ASID <= AS_GAMEWATCH_LANDINGAIRN))
    {
        return FALSE;
    }
    return TRUE;
}

void ftGameWatch_ItemTurtleOnLand(HSD_GObj*);
extern HSD_GObj* func_802C6F40(HSD_GObj*, Vec3*, s32, f32);

// 0x8014B1B4 
// https://decomp.me/scratch/1sOUQ // Create Turtle Item
void ftGameWatch_ItemTurtleSetup(HSD_GObj* fighter_gobj)
{
    Vec3 sp10;
    HSD_GObj* turtleGObj;
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x225C_turtleGObj != NULL)
    {
        ftGameWatch_ItemTurtleOnLand(fighter_gobj);
    }
    else
    {
        func_8000B1CC(fp->x5E8_fighterBones[0x11].x0_jobj, NULL, &sp10);
        fp->sa.gaw.x225C_turtleGObj = func_802C6F40(fighter_gobj, &sp10, 0x11, fp->x2C_facing_direction);
        if (fp->sa.gaw.x225C_turtleGObj != NULL)
        {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
            fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_AttackAir_EnterItemHitlag;
            fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_AttackAir_ExitItemHitlag;
        }
    }
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014B268
// https://decomp.me/scratch/R20Hy // Turtle Accessory Callback - Landing Lag
void ftGameWatch_ItemTurtleOnLand(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x225C_turtleGObj != NULL)
    {
        ftGameWatch_AttackAir_ExitItemHitlag(fighter_gobj);
        if (fp->x10_action_state_index == AS_GAMEWATCH_LANDINGAIRN) // Deliberate ASID mismatch to prevent item animation from freezing???
        {
            func_802C7158(fp->sa.gaw.x225C_turtleGObj);
        }
        fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_AttackAir_EnterItemHitlag;
        fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_AttackAir_ExitItemHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014B2E4
// https://decomp.me/scratch/bOMxY // Turtle item flag update on land + clear pointers
void ftGameWatch_ItemTurtleSetFlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    ftGameWatch_AttackAir_ExitItemHitlag(fighter_gobj);
    fp->sa.gaw.x225C_turtleGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

extern void func_802C7074(HSD_GObj*);

// 0x8014B320
// https://decomp.me/scratch/jzWrr // Remove Turtle item
void ftGameWatch_ItemTurtleRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* turtleGObj;

    if (fp->sa.gaw.x225C_turtleGObj != NULL)
    {
        func_802C7074(fp->sa.gaw.x225C_turtleGObj);
        ftGameWatch_ItemTurtleSetFlag(fighter_gobj);
    }
}

// 0x8014B380
// https://decomp.me/scratch/xFOBA // Check if Mr. Game & Watch is performing Back Aerial / Back Aerial Landing Lag
BOOL ftGameWatch_ItemCheckTurtleRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 ASID = fp->x10_action_state_index;

    if ((ASID >= AS_GAMEWATCH_ATTACKAIRB) && (ASID <= AS_GAMEWATCH_LANDINGAIRB))
    {
        return FALSE;
    }
    return TRUE;
}

extern HSD_GObj* func_802C720C(HSD_GObj*, Vec3*, s32, f32);

// 0x8014B3A8 
// https://decomp.me/scratch/Ax8pD // Create Sparky Item
void ftGameWatch_ItemSparkySetup(HSD_GObj* fighter_gobj)
{
    Vec3 sp10;
    HSD_GObj* sparkyGObj;
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x2260_sparkyGObj != NULL)
    {
        ftGameWatch_ItemSparkyOnLand(fighter_gobj);
    }
    else
    {
        func_8000B1CC(fp->x5E8_fighterBones[0x15].x0_jobj, NULL, &sp10);
        fp->sa.gaw.x2260_sparkyGObj = func_802C720C(fighter_gobj, &sp10, 0x15, fp->x2C_facing_direction);
        if (fp->sa.gaw.x2260_sparkyGObj != NULL)
        {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
            fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_AttackAir_EnterItemHitlag;
            fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_AttackAir_ExitItemHitlag;
        }
    }
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014B45C
// https://decomp.me/scratch/9eoJs // Sparky Accessory Callback - Landing Lag
void ftGameWatch_ItemSparkyOnLand(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x2260_sparkyGObj != NULL)
    {
        ftGameWatch_AttackAir_ExitItemHitlag(fighter_gobj);
        if (fp->x10_action_state_index == AS_GAMEWATCH_LANDINGAIRN)
        {
            func_802C7424(fp->sa.gaw.x2260_sparkyGObj);
        }
        fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_AttackAir_EnterItemHitlag;
        fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_AttackAir_ExitItemHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014B4D8
// https://decomp.me/scratch/bdjqs // Sparky item flag update on land + clear pointers
void ftGameWatch_ItemSparkySetFlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    ftGameWatch_AttackAir_ExitItemHitlag(fighter_gobj);
    fp->sa.gaw.x2260_sparkyGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

extern void func_802C7340(HSD_GObj*);

// 0x8014B514
// https://decomp.me/scratch/xkjj4 // Remove Sparky item
void ftGameWatch_ItemSparkyRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* sparkyGObj;

    if (fp->sa.gaw.x2260_sparkyGObj != NULL)
    {
        func_802C7340(fp->sa.gaw.x2260_sparkyGObj);
        ftGameWatch_ItemSparkySetFlag(fighter_gobj);
    }
}

extern void func_802C6DB8(HSD_GObj*);
extern void func_802C70C0(HSD_GObj*);
extern void func_802C738C(HSD_GObj*);
extern void func_802C6DD8(HSD_GObj*);
extern void func_802C70E0(HSD_GObj*);
extern void func_802C73AC(HSD_GObj*);

// 0x8014B574
// https://decomp.me/scratch/EsqL3 // Apply hitlag for available AttackAir items
void ftGameWatch_AttackAir_EnterItemHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x2258_parachuteGObj != NULL)
    {
        func_802C6DB8(fp->sa.gaw.x2258_parachuteGObj);
    }
    if (fp->sa.gaw.x225C_turtleGObj != NULL)
    {
        func_802C70C0(fp->sa.gaw.x225C_turtleGObj);
    }
    if (fp->sa.gaw.x2260_sparkyGObj != NULL)
    {
        func_802C738C(fp->sa.gaw.x2260_sparkyGObj);
    }
}

// 0x8014B5CC - Remove hitlag for available AttackAir items
void ftGameWatch_AttackAir_ExitItemHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x2258_parachuteGObj != NULL)
    {
        func_802C6DD8(fp->sa.gaw.x2258_parachuteGObj);
    }
    if (fp->sa.gaw.x225C_turtleGObj != NULL)
    {
        func_802C70E0(fp->sa.gaw.x225C_turtleGObj);
    }
    if (fp->sa.gaw.x2260_sparkyGObj != NULL)
    {
        func_802C73AC(fp->sa.gaw.x2260_sparkyGObj);
    }
}

// 0x8014B624 
// https://decomp.me/scratch/vpCdl // Check if Mr. Game & Watch is performing Up Aerial / Up Aerial Landing Lag
BOOL ftGameWatch_ItemCheckSparkyRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 ASID = fp->x10_action_state_index;

    if ((ASID >= AS_GAMEWATCH_ATTACKAIRHI) && (ASID <= AS_GAMEWATCH_LANDINGAIRHI))
    {
        return FALSE;
    }
    return TRUE;
}

extern s32 func_8008CE68(Fighter*);
extern void func_8008CFAC(HSD_GObj*, s32);
extern void ftGameWatch_AttackAirB_Action(HSD_GObj*, s32);
extern void ftGameWatch_AttackAirHi_Action(HSD_GObj*, s32);

// 0x8014B64C
// https://decomp.me/scratch/Ads9W // Decide Mr. Game & Watch's Aerial Attack Action State
void ftGameWatch_AttackAir_DecideAction(HSD_GObj* fighter_gobj)
{
    s32 ASID = func_8008CE68(fighter_gobj->user_data);

    switch (ASID)
    {
    case ASID_ATTACKAIRN:
        ftGameWatch_AttackAirN_Action(fighter_gobj, ASID);
        return;
    case ASID_ATTACKAIRF:
        func_8008CFAC(fighter_gobj, ASID);
        return;
    case ASID_ATTACKAIRB:
        ftGameWatch_AttackAirB_Action(fighter_gobj, ASID);
        return;
    case ASID_ATTACKAIRHI:
        ftGameWatch_AttackAirHi_Action(fighter_gobj, ASID);
        return;
    case ASID_ATTACKAIRLW:
        func_8008CFAC(fighter_gobj, ASID);
        return;
    }
}

// 0x8014B6E4 
// https://decomp.me/scratch/iunEP // Mr. Game & Watch's Neutral Aerial Action State handler 
void ftGameWatch_AttackAirN_Action(HSD_GObj* fighter_gobj, s32 ASID)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8008CFAC(fighter_gobj, AS_GAMEWATCH_ATTACKAIRN);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemParachuteSetup;
}

extern void func_8008D010(HSD_GObj*);

// 0x8014B720
// https://decomp.me/scratch/AxMcb // Mr. Game & Watch's Neutral Aerial Animation callback
void ftGameWatch_AttackAirN_Anim(HSD_GObj* fighter_gobj)
{
    func_8008D010(fighter_gobj);
}

extern void func_8008D08C(HSD_GObj*);

// 0x8014B740
// https://decomp.me/scratch/PnNzC // Mr. Game & Watch's Neutral Aerial IASA callback
void ftGameWatch_AttackAirN_IASA(HSD_GObj* fighter_gobj)
{
    func_8008D08C(fighter_gobj);
}

extern void func_80084DB0(HSD_GObj*);

// 0x8014B760
// https://decomp.me/scratch/EBIVr // Mr. Game & Watch's Neutral Aerial Physics callback
void ftGameWatch_AttackAirN_Phys(HSD_GObj* fighter_gobj)
{
    func_80084DB0(fighter_gobj);
}

extern void func_80082C74(HSD_GObj*, void cb_OnLand(HSD_GObj*));

// 0x8014B780
// https://decomp.me/scratch/aIqYH // Mr. Game & Watch's Neutral Aerial Collision callback
void ftGameWatch_AttackAirN_Coll(HSD_GObj* fighter_gobj)
{
    func_80082C74(fighter_gobj, ftGameWatch_LandingAirN_Action);
}

void ftGameWatch_LandingAirN_Init(HSD_GObj*);

// 0x8014B7A8
// https://decomp.me/scratch/Y3A1Z // Mr. Game & Watch - LandingAirN Think
void ftGameWatch_LandingAirN_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* parachute;
    HSD_GObj* turtle;
    HSD_GObj* sparky;

    if (fp->sa.gaw.x2258_parachuteGObj != NULL)
    {
        func_802C6DD8(fp->sa.gaw.x2258_parachuteGObj);
    }
    if (fp->sa.gaw.x225C_turtleGObj != NULL)
    {
        func_802C70E0(fp->sa.gaw.x225C_turtleGObj);
    }
    if (fp->sa.gaw.x2260_sparkyGObj != NULL)
    {
        func_802C73AC(fp->sa.gaw.x2260_sparkyGObj);
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        ftGameWatch_LandingAirN_Init(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemParachuteOnLand;
        return;
    }
    func_800D5BF8(fighter_gobj);
    ftGameWatch_OnDamage(fighter_gobj);
}

// 0x8014B840
// https://decomp.me/scratch/iunEP // Mr. Game & Watch's Back Aerial Action State handler 
void ftGameWatch_AttackAirB_Action(HSD_GObj* fighter_gobj, s32 ASID)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8008CFAC(fighter_gobj, AS_GAMEWATCH_ATTACKAIRB);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemTurtleSetup;
}

// 0x8014B87C
// https://decomp.me/scratch/AxMcb // Mr. Game & Watch's Back Aerial Animation callback
void ftGameWatch_AttackAirB_Anim(HSD_GObj* fighter_gobj)
{
    func_8008D010(fighter_gobj);
}

extern void func_8008D29C(HSD_GObj*);

// 0x8014B89C
// https://decomp.me/scratch/PnNzC // Mr. Game & Watch's Back Aerial IASA callback
void ftGameWatch_AttackAirB_IASA(HSD_GObj* fighter_gobj)
{
    func_8008D29C(fighter_gobj);
}

// 0x8014B8BC
// https://decomp.me/scratch/EBIVr // Mr. Game & Watch's Back Aerial Physics callback
void ftGameWatch_AttackAirB_Phys(HSD_GObj* fighter_gobj)
{
    func_80084DB0(fighter_gobj);
}

// 0x8014B8DC
// https://decomp.me/scratch/aIqYH // Mr. Game & Watch's Back Aerial Collision callback
void ftGameWatch_AttackAirB_Coll(HSD_GObj* fighter_gobj)
{
    func_80082C74(fighter_gobj, ftGameWatch_LandingAirB_Action);
}

// 0x8014B904
// https://decomp.me/scratch/Y3A1Z // Mr. Game & Watch - LandingAirB Think
void ftGameWatch_LandingAirB_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* parachute;
    HSD_GObj* turtle;
    HSD_GObj* sparky;

    if (fp->sa.gaw.x2258_parachuteGObj != NULL)
    {
        func_802C6DD8(fp->sa.gaw.x2258_parachuteGObj);
    }
    if (fp->sa.gaw.x225C_turtleGObj != NULL)
    {
        func_802C70E0(fp->sa.gaw.x225C_turtleGObj);
    }
    if (fp->sa.gaw.x2260_sparkyGObj != NULL)
    {
        func_802C73AC(fp->sa.gaw.x2260_sparkyGObj);
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        ftGameWatch_LandingAirB_Init(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemTurtleOnLand;
        return;
    }
    func_800D5BF8(fighter_gobj);
    ftGameWatch_OnDamage(fighter_gobj);
}

// 0x8014B99C
// https://decomp.me/scratch/iunEP // Mr. Game & Watch's Up Aerial Action State handler 
void ftGameWatch_AttackAirHi_Action(HSD_GObj* fighter_gobj, s32 ASID)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8008CFAC(fighter_gobj, AS_GAMEWATCH_ATTACKAIRHI);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemSparkySetup;
}

// 0x8014B9D8
// https://decomp.me/scratch/AxMcb // Mr. Game & Watch's Up Aerial Animation callback
void ftGameWatch_AttackAirHi_Anim(HSD_GObj* fighter_gobj)
{
    func_8008D010(fighter_gobj);
}

extern void func_8008D3A4(HSD_GObj*);

// 0x8014B9F8
// https://decomp.me/scratch/PnNzC // Mr. Game & Watch's Up Aerial IASA callback
void ftGameWatch_AttackAirHi_IASA(HSD_GObj* fighter_gobj)
{
    func_8008D3A4(fighter_gobj);
}

// 0x8014BA18
// https://decomp.me/scratch/EBIVr // Mr. Game & Watch's Back Aerial Physics callback
void ftGameWatch_AttackAirHi_Phys(HSD_GObj* fighter_gobj)
{
    func_80084DB0(fighter_gobj);
}

// 0x8014BA38
// https://decomp.me/scratch/aIqYH // Mr. Game & Watch's Back Aerial Collision callback
void ftGameWatch_AttackAirHi_Coll(HSD_GObj* fighter_gobj)
{
    func_80082C74(fighter_gobj, ftGameWatch_LandingAirHi_Action);
}

// 0x8014BA60
// https://decomp.me/scratch/Y3A1Z // Mr. Game & Watch - LandingAirHi Think
void ftGameWatch_LandingAirHi_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    HSD_GObj* parachute;
    HSD_GObj* turtle;
    HSD_GObj* sparky;

    if (fp->sa.gaw.x2258_parachuteGObj != NULL)
    {
        func_802C6DD8(fp->sa.gaw.x2258_parachuteGObj);
    }
    if (fp->sa.gaw.x225C_turtleGObj != NULL)
    {
        func_802C70E0(fp->sa.gaw.x225C_turtleGObj);
    }
    if (fp->sa.gaw.x2260_sparkyGObj != NULL)
    {
        func_802C73AC(fp->sa.gaw.x2260_sparkyGObj);
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        ftGameWatch_LandingAirHi_Init(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemSparkyOnLand;
        return;
    }
    func_800D5BF8(fighter_gobj);
    ftGameWatch_OnDamage(fighter_gobj);
}

extern void func_8008D708(HSD_GObj*, s32, f32);

// 0x8014BAF8
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Neutral Aerial Landing prefunction
void ftGameWatch_LandingAirN_Init(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8008D708(fighter_gobj, AS_GAMEWATCH_LANDINGAIRN, fp->x110_attr.x1F8_NAirLandingLag);
}

extern void func_800D5D3C(HSD_GObj*);

// 0x8014BB24
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Neutral Aerial Landing Animation callback
void ftGameWatch_LandingAirN_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_800D5D3C(fighter_gobj);
    if (fp->x10_action_state_index != AS_GAMEWATCH_LANDINGAIRN)
    {
        ftGameWatch_OnDamage(fighter_gobj);
    }
}

// 0x8014BB70 - Mr. Game & Watch's Neutral Aerial Landing IASA callback
void ftGameWatch_LandingAirN_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

extern void func_800D5F18(HSD_GObj*);

// 0x8014BB74
// https://decomp.me/scratch/SqMil // Mr. Game & Watch's Neutral Aerial Landing Physics callback 
void ftGameWatch_LandingAirN_Phys(HSD_GObj* fighter_gobj)
{
    func_800D5F18(fighter_gobj);
}

extern void func_800D5F38(HSD_GObj*);

// 0x8014BB94
// https://decomp.me/scratch/2K68T // Mr. Game & Watch's Neutral Aerial Landing Collision callback
void ftGameWatch_LandingAirN_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_800D5F38(fighter_gobj);
    if (fp->x10_action_state_index != AS_GAMEWATCH_LANDINGAIRN)
    {
        ftGameWatch_OnDamage(fighter_gobj);
    }
}

// 0x8014BBE0
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Back Aerial Landing prefunction
void ftGameWatch_LandingAirB_Init(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8008D708(fighter_gobj, AS_GAMEWATCH_LANDINGAIRB, fp->x110_attr.x200_BAirLandingLag);
}

// 0x8014BC0C
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Back Aerial Landing Animation callback
void ftGameWatch_LandingAirB_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_800D5D3C(fighter_gobj);
    if (fp->x10_action_state_index != AS_GAMEWATCH_LANDINGAIRB)
    {
        ftGameWatch_OnDamage(fighter_gobj);
    }
}

// 0x8014BC58 - Mr. Game & Watch's Back Aerial Landing IASA callback
void ftGameWatch_LandingAirB_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x8014BC5C
// https://decomp.me/scratch/SqMil // Mr. Game & Watch's Back Aerial Landing Physics callback 
void ftGameWatch_LandingAirB_Phys(HSD_GObj* fighter_gobj)
{
    func_800D5F18(fighter_gobj);
}

// 0x8014BC7C
// https://decomp.me/scratch/2K68T // Mr. Game & Watch's Back Aerial Landing Collision callback
void ftGameWatch_LandingAirB_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_800D5F38(fighter_gobj);
    if (fp->x10_action_state_index != AS_GAMEWATCH_LANDINGAIRB)
    {
        ftGameWatch_OnDamage(fighter_gobj);
    }
}

// 0x8014BCC8
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Up Aerial Landing prefunction
void ftGameWatch_LandingAirHi_Init(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8008D708(fighter_gobj, AS_GAMEWATCH_LANDINGAIRHI, fp->x110_attr.x200_BAirLandingLag); // Erroneously using Back Aerial's landing lag
}

// 0x8014BCF4
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Up Aerial Landing Animation callback
void ftGameWatch_LandingAirHi_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_800D5D3C(fighter_gobj);
    if (fp->x10_action_state_index != AS_GAMEWATCH_LANDINGAIRHI)
    {
        ftGameWatch_OnDamage(fighter_gobj);
    }
}

// 0x8014BD40 - Mr. Game & Watch's Up Aerial Landing IASA callback
void ftGameWatch_LandingAirHi_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x8014BD44
// https://decomp.me/scratch/SqMil // Mr. Game & Watch's Up Aerial Landing Physics callback 
void ftGameWatch_LandingAirHi_Phys(HSD_GObj* fighter_gobj)
{
    func_800D5F18(fighter_gobj);
}

// 0x8014BD64
// https://decomp.me/scratch/2K68T // Mr. Game & Watch's Up Aerial Landing Collision callback
void ftGameWatch_LandingAirHi_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_800D5F38(fighter_gobj);
    if (fp->x10_action_state_index != AS_GAMEWATCH_LANDINGAIRHI)
    {
        ftGameWatch_OnDamage(fighter_gobj);
    }
}

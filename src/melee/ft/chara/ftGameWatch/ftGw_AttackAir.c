#include "ft/chara/ftGameWatch/ftGw_Init.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

static void ftGw_AttackAirN_ExitItemHitlag(HSD_GObj*);

// 0x8014AFC0
// https://decomp.me/scratch/wJ5b7 // Create Parachute Item
void ftGw_AttackAirN_ItemParachuteSetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.gw.x2258_parachuteGObj != NULL) {
        ftGw_AttackAirN_ItemParachuteOnLand(gobj);
    } else {
        lb_8000B1CC(fp->x5E8_fighterBones[1].x0_jobj, NULL, &sp10);
        fp->ev.gw.x2258_parachuteGObj =
            it_802C6C38(gobj, &sp10, 1, fp->facing_dir);
        if (fp->ev.gw.x2258_parachuteGObj != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftGw_Init_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGw_Init_OnDamage;
            fp->cb.x21D4_callback_EnterHitlag =
                ftGw_AttackAirN_EnterItemHitlag;
            fp->cb.x21D8_callback_ExitHitlag =
                ftGw_AttackAirN_ExitItemHitlag;
        }
    }
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014B074
// https://decomp.me/scratch/TaqkV // Parachute Accessory Callback - Landing
// Lag
void ftGw_AttackAirN_ItemParachuteOnLand(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.gw.x2258_parachuteGObj != NULL) {
        ftGw_AttackAirN_ExitItemHitlag(gobj);
        if (fp->action_id == AS_GAMEWATCH_LANDINGAIRN) {
            it_802C6E50(fp->ev.gw.x2258_parachuteGObj);
        }
        fp->cb.x21E4_callback_OnDeath2 = ftGw_Init_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGw_Init_OnDamage;
        fp->cb.x21D4_callback_EnterHitlag =
            ftGw_AttackAirN_EnterItemHitlag;
        fp->cb.x21D8_callback_ExitHitlag =
            ftGw_AttackAirN_ExitItemHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014B0F0
// https://decomp.me/scratch/8jiZT // Parachute item flag update on land +
// clear pointers
void ftGw_AttackAirN_ItemParachuteSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGw_AttackAirN_ExitItemHitlag(gobj);
    fp->ev.gw.x2258_parachuteGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

/// Remove Parachute item
void ftGw_AttackAirN_ItemParachuteRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.gw.x2258_parachuteGObj != NULL) {
        it_802C6D6C(fp->ev.gw.x2258_parachuteGObj);
        ftGw_AttackAirN_ItemParachuteSetFlag(gobj);
    }
}

// 0x8014B18C
// https://decomp.me/scratch/hJ3U1 // Check if Mr. Game & Watch is performing
// Neutral Aerial / Neutral Aerial landing
bool ftGw_AttackAirN_ItemCheckParachuteRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = fp->action_id;

    if (msid >= AS_GAMEWATCH_ATTACKAIRN && msid <= AS_GAMEWATCH_LANDINGAIRN) {
        return false;
    }

    return true;
}

static void ftGw_AttackAirN_ItemTurtleOnLand(HSD_GObj*);

// 0x8014B1B4
// https://decomp.me/scratch/1sOUQ // Create Turtle Item
void ftGw_AttackAirN_ItemTurtleSetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->ev.gw.x225C_turtleGObj != NULL) {
        ftGw_AttackAirN_ItemTurtleOnLand(gobj);
    } else {
        lb_8000B1CC(fp->x5E8_fighterBones[0x11].x0_jobj, NULL, &sp10);
        fp->ev.gw.x225C_turtleGObj =
            it_802C6F40(gobj, &sp10, 0x11, fp->facing_dir);
        if (fp->ev.gw.x225C_turtleGObj != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftGw_Init_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGw_Init_OnDamage;
            fp->cb.x21D4_callback_EnterHitlag =
                ftGw_AttackAirN_EnterItemHitlag;
            fp->cb.x21D8_callback_ExitHitlag =
                ftGw_AttackAirN_ExitItemHitlag;
        }
    }
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014B268
// https://decomp.me/scratch/R20Hy // Turtle Accessory Callback - Landing Lag
static void ftGw_AttackAirN_ItemTurtleOnLand(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.gw.x225C_turtleGObj != NULL) {
        ftGw_AttackAirN_ExitItemHitlag(gobj);

        // Deliberate ASID mismatch to prevent item animation from freezing???
        if (fp->action_id == AS_GAMEWATCH_LANDINGAIRN) {
            it_802C7158(fp->ev.gw.x225C_turtleGObj);
        }

        fp->cb.x21E4_callback_OnDeath2 = ftGw_Init_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGw_Init_OnDamage;
        fp->cb.x21D4_callback_EnterHitlag =
            ftGw_AttackAirN_EnterItemHitlag;
        fp->cb.x21D8_callback_ExitHitlag =
            ftGw_AttackAirN_ExitItemHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014B2E4
// https://decomp.me/scratch/bOMxY // Turtle item flag update on land + clear
// pointers
void ftGw_AttackAirN_ItemTurtleSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGw_AttackAirN_ExitItemHitlag(gobj);
    fp->ev.gw.x225C_turtleGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

// 0x8014B320
// https://decomp.me/scratch/jzWrr // Remove Turtle item
void ftGw_AttackAirN_ItemTurtleRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.gw.x225C_turtleGObj != NULL) {
        it_802C7074(fp->ev.gw.x225C_turtleGObj);
        ftGw_AttackAirN_ItemTurtleSetFlag(gobj);
    }
}

// 0x8014B380
// https://decomp.me/scratch/xFOBA // Check if Mr. Game & Watch is performing
// Back Aerial / Back Aerial Landing Lag
bool ftGw_AttackAirN_ItemCheckTurtleRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ASID = fp->action_id;

    if ((ASID >= AS_GAMEWATCH_ATTACKAIRB) &&
        (ASID <= AS_GAMEWATCH_LANDINGAIRB))
    {
        return false;
    }
    return true;
}

/// Create Sparky Item
void ftGw_AttackAirN_ItemSparkySetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->ev.gw.x2260_sparkyGObj != NULL) {
        ftGw_AttackAirN_ItemSparkyOnLand(gobj);
    } else {
        lb_8000B1CC(fp->x5E8_fighterBones[0x15].x0_jobj, NULL, &sp10);
        fp->ev.gw.x2260_sparkyGObj =
            it_802C720C(gobj, &sp10, 0x15, fp->facing_dir);
        if (fp->ev.gw.x2260_sparkyGObj != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftGw_Init_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGw_Init_OnDamage;
            fp->cb.x21D4_callback_EnterHitlag =
                ftGw_AttackAirN_EnterItemHitlag;
            fp->cb.x21D8_callback_ExitHitlag =
                ftGw_AttackAirN_ExitItemHitlag;
        }
    }
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014B45C
// https://decomp.me/scratch/9eoJs // Sparky Accessory Callback - Landing Lag
void ftGw_AttackAirN_ItemSparkyOnLand(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.gw.x2260_sparkyGObj != NULL) {
        ftGw_AttackAirN_ExitItemHitlag(gobj);

        if (fp->action_id == AS_GAMEWATCH_LANDINGAIRN) {
            it_802C7424(fp->ev.gw.x2260_sparkyGObj);
        }

        fp->cb.x21E4_callback_OnDeath2 = ftGw_Init_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGw_Init_OnDamage;
        fp->cb.x21D4_callback_EnterHitlag =
            ftGw_AttackAirN_EnterItemHitlag;
        fp->cb.x21D8_callback_ExitHitlag =
            ftGw_AttackAirN_ExitItemHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014B4D8
// https://decomp.me/scratch/bdjqs // Sparky item flag update on land + clear
// pointers
void ftGw_AttackAirN_ItemSparkySetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGw_AttackAirN_ExitItemHitlag(gobj);
    fp->ev.gw.x2260_sparkyGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

// 0x8014B514
// https://decomp.me/scratch/xkjj4 // Remove Sparky item
void ftGw_AttackAirN_ItemSparkyRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.gw.x2260_sparkyGObj != NULL) {
        it_802C7340(fp->ev.gw.x2260_sparkyGObj);
        ftGw_AttackAirN_ItemSparkySetFlag(gobj);
    }
}

// 0x8014B574
// https://decomp.me/scratch/EsqL3 // Apply hitlag for available AttackAir
// items
void ftGw_AttackAirN_EnterItemHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.gw.x2258_parachuteGObj != NULL) {
        it_802C6DB8(fp->ev.gw.x2258_parachuteGObj);
    }
    if (fp->ev.gw.x225C_turtleGObj != NULL) {
        it_802C70C0(fp->ev.gw.x225C_turtleGObj);
    }
    if (fp->ev.gw.x2260_sparkyGObj != NULL) {
        it_802C738C(fp->ev.gw.x2260_sparkyGObj);
    }
}

// 0x8014B5CC - Remove hitlag for available AttackAir items
static void ftGw_AttackAirN_ExitItemHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.gw.x2258_parachuteGObj != NULL) {
        it_802C6DD8(fp->ev.gw.x2258_parachuteGObj);
    }
    if (fp->ev.gw.x225C_turtleGObj != NULL) {
        it_802C70E0(fp->ev.gw.x225C_turtleGObj);
    }
    if (fp->ev.gw.x2260_sparkyGObj != NULL) {
        it_802C73AC(fp->ev.gw.x2260_sparkyGObj);
    }
}

// 0x8014B624
// https://decomp.me/scratch/vpCdl // Check if Mr. Game & Watch is performing
// Up Aerial / Up Aerial Landing Lag
bool ftGw_AttackAirN_ItemCheckSparkyRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ASID = fp->action_id;

    if ((ASID >= AS_GAMEWATCH_ATTACKAIRHI) &&
        (ASID <= AS_GAMEWATCH_LANDINGAIRHI))
    {
        return false;
    }
    return true;
}

static void ftGw_AttackAirB_Enter(HSD_GObj*);
static void ftGw_AttackAirHi_Enter(HSD_GObj*);

// 0x8014B64C
// https://decomp.me/scratch/Ads9W // Decide Mr. Game & Watch's Aerial Attack
// Motion State
void ftGw_AttackAirN_DecideAction(HSD_GObj* gobj)
{
    enum_t ASID = ft_8008CE68(GET_FIGHTER(gobj));

    switch (ASID) {
    case ASID_ATTACKAIRN:
        ftGw_AttackAirN_Enter(gobj);
        return;
    case ASID_ATTACKAIRF:
        ft_8008CFAC(gobj, ASID);
        return;
    case ASID_ATTACKAIRB:
        ftGw_AttackAirB_Enter(gobj);
        return;
    case ASID_ATTACKAIRHI:
        ftGw_AttackAirHi_Enter(gobj);
        return;
    case ASID_ATTACKAIRLW:
        ft_8008CFAC(gobj, ASID);
        return;
    }
}

// 0x8014B6E4
// https://decomp.me/scratch/iunEP // Mr. Game & Watch's Neutral Aerial Action
// State handler
void ftGw_AttackAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_8008CFAC(gobj, AS_GAMEWATCH_ATTACKAIRN);
    fp->cb.x21BC_callback_Accessory4 = ftGw_AttackAirN_ItemParachuteSetup;
}

// 0x8014B720
// https://decomp.me/scratch/AxMcb // Mr. Game & Watch's Neutral Aerial
// Animation callback
void ftGw_AttackAirN_Anim(HSD_GObj* gobj)
{
    ftCo_AttackAir_Anim(gobj);
}

// 0x8014B740
// https://decomp.me/scratch/PnNzC // Mr. Game & Watch's Neutral Aerial IASA
// callback
void ftGw_AttackAirN_IASA(HSD_GObj* gobj)
{
    ftCo_AttackAirN_IASA(gobj);
}

// 0x8014B760
// https://decomp.me/scratch/EBIVr // Mr. Game & Watch's Neutral Aerial Physics
// callback
void ftGw_AttackAirN_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

// 0x8014B780
// https://decomp.me/scratch/aIqYH // Mr. Game & Watch's Neutral Aerial
// Collision callback
void ftGw_AttackAirN_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftGw_LandingAirN_Enter);
}

static void ftGw_LandingAirN_Init(HSD_GObj*);

/// Mr. Game & Watch - LandingAirN Think
void ftGw_LandingAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->ev.gw.x2258_parachuteGObj != NULL) {
        it_802C6DD8(fp->ev.gw.x2258_parachuteGObj);
    }

    if (fp->ev.gw.x225C_turtleGObj != NULL) {
        it_802C70E0(fp->ev.gw.x225C_turtleGObj);
    }

    if (fp->ev.gw.x2260_sparkyGObj != NULL) {
        it_802C73AC(fp->ev.gw.x2260_sparkyGObj);
    }

    if ((u32) fp->x2200_ftcmd_var0 != 0U) {
        ftGw_LandingAirN_Init(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGw_AttackAirN_ItemParachuteOnLand;
        return;
    }

    ft_800D5BF8(gobj);
    ftGw_Init_OnDamage(gobj);
}

// 0x8014B840
// https://decomp.me/scratch/iunEP // Mr. Game & Watch's Back Aerial Action
// State handler
static void ftGw_AttackAirB_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_8008CFAC(gobj, AS_GAMEWATCH_ATTACKAIRB);
    fp->cb.x21BC_callback_Accessory4 = ftGw_AttackAirN_ItemTurtleSetup;
}

// 0x8014B87C
// https://decomp.me/scratch/AxMcb // Mr. Game & Watch's Back Aerial Animation
// callback
void ftGw_AttackAirB_Anim(HSD_GObj* gobj)
{
    ftCo_AttackAir_Anim(gobj);
}

// 0x8014B89C
// https://decomp.me/scratch/PnNzC // Mr. Game & Watch's Back Aerial IASA
// callback
void ftGw_AttackAirB_IASA(HSD_GObj* gobj)
{
    ftCo_AttackAirB_IASA(gobj);
}

// 0x8014B8BC
// https://decomp.me/scratch/EBIVr // Mr. Game & Watch's Back Aerial Physics
// callback
void ftGw_AttackAirB_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

// 0x8014B8DC
// https://decomp.me/scratch/aIqYH // Mr. Game & Watch's Back Aerial Collision
// callback
void ftGw_AttackAirB_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftGw_LandingAirB_Enter);
}

/// Mr. Game & Watch - LandingAirB Think
void ftGw_LandingAirB_Enter(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->ev.gw.x2258_parachuteGObj != NULL) {
        it_802C6DD8(fp->ev.gw.x2258_parachuteGObj);
    }

    if (fp->ev.gw.x225C_turtleGObj != NULL) {
        it_802C70E0(fp->ev.gw.x225C_turtleGObj);
    }

    if (fp->ev.gw.x2260_sparkyGObj != NULL) {
        it_802C73AC(fp->ev.gw.x2260_sparkyGObj);
    }

    if ((u32) fp->x2200_ftcmd_var0 != 0) {
        ftGw_LandingAirB_Init(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGw_AttackAirN_ItemTurtleOnLand;
        return;
    }

    ft_800D5BF8(gobj);
    ftGw_Init_OnDamage(gobj);
}

/// Mr. Game & Watch's Up Aerial Motion State handler
static void ftGw_AttackAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_8008CFAC(gobj, AS_GAMEWATCH_ATTACKAIRHI);
    fp->cb.x21BC_callback_Accessory4 = ftGw_AttackAirN_ItemSparkySetup;
}

/// Mr. Game & Watch's Up Aerial Animation callback
void ftGw_AttackAirHi_Anim(HSD_GObj* gobj)
{
    ftCo_AttackAir_Anim(gobj);
}

/// Mr. Game & Watch's Up Aerial IASA callback
void ftGw_AttackAirHi_IASA(HSD_GObj* gobj)
{
    ftCo_AttackAirHi_IASA(gobj);
}

/// Mr. Game & Watch's Back Aerial Physics callback
void ftGw_AttackAirHi_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// Mr. Game & Watch's Back Aerial Collision callback
void ftGw_AttackAirHi_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftGw_LandingAirHi_Enter);
}

/// Mr. Game & Watch - LandingAirHi Think
void ftGw_LandingAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->ev.gw.x2258_parachuteGObj != NULL) {
        it_802C6DD8(fp->ev.gw.x2258_parachuteGObj);
    }

    if (fp->ev.gw.x225C_turtleGObj != NULL) {
        it_802C70E0(fp->ev.gw.x225C_turtleGObj);
    }

    if (fp->ev.gw.x2260_sparkyGObj != NULL) {
        it_802C73AC(fp->ev.gw.x2260_sparkyGObj);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftGw_LandingAirHi_Init(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGw_AttackAirN_ItemSparkyOnLand;
        return;
    }

    ft_800D5BF8(gobj);
    ftGw_Init_OnDamage(gobj);
}

// 0x8014BAF8
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Neutral Aerial Landing
// prefunction
static void ftGw_LandingAirN_Init(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    ft_8008D708(gobj, AS_GAMEWATCH_LANDINGAIRN,
                fp->x110_attr.x1F8_NAirLandingLag);
}

// 0x8014BB24
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Neutral Aerial Landing
// Animation callback
void ftGw_LandingAirN_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_Landing_Anim(gobj);
    if (fp->action_id != AS_GAMEWATCH_LANDINGAIRN) {
        ftGw_Init_OnDamage(gobj);
    }
}

// 0x8014BB70 - Mr. Game & Watch's Neutral Aerial Landing IASA callback
void ftGw_LandingAirN_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014BB74
// https://decomp.me/scratch/SqMil // Mr. Game & Watch's Neutral Aerial Landing
// Physics callback
void ftGw_LandingAirN_Phys(HSD_GObj* gobj)
{
    ftCo_Landing_Phys(gobj);
}

// 0x8014BB94
// https://decomp.me/scratch/2K68T // Mr. Game & Watch's Neutral Aerial Landing
// Collision callback
void ftGw_LandingAirN_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_Landing_Coll(gobj);
    if (fp->action_id != AS_GAMEWATCH_LANDINGAIRN) {
        ftGw_Init_OnDamage(gobj);
    }
}

// 0x8014BBE0
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Back Aerial Landing
// prefunction
void ftGw_LandingAirB_Init(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_8008D708(gobj, AS_GAMEWATCH_LANDINGAIRB,
                fp->x110_attr.x200_BAirLandingLag);
}

// 0x8014BC0C
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Back Aerial Landing
// Animation callback
void ftGw_LandingAirB_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_Landing_Anim(gobj);
    if (fp->action_id != AS_GAMEWATCH_LANDINGAIRB) {
        ftGw_Init_OnDamage(gobj);
    }
}

// 0x8014BC58 - Mr. Game & Watch's Back Aerial Landing IASA callback
void ftGw_LandingAirB_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014BC5C
// https://decomp.me/scratch/SqMil // Mr. Game & Watch's Back Aerial Landing
// Physics callback
void ftGw_LandingAirB_Phys(HSD_GObj* gobj)
{
    ftCo_Landing_Phys(gobj);
}

// 0x8014BC7C
// https://decomp.me/scratch/2K68T // Mr. Game & Watch's Back Aerial Landing
// Collision callback
void ftGw_LandingAirB_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_Landing_Coll(gobj);
    if (fp->action_id != AS_GAMEWATCH_LANDINGAIRB) {
        ftGw_Init_OnDamage(gobj);
    }
}

// 0x8014BCC8
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Up Aerial Landing
// prefunction
void ftGw_LandingAirHi_Init(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_8008D708(gobj, AS_GAMEWATCH_LANDINGAIRHI,
                fp->x110_attr.x200_BAirLandingLag); // Erroneously using Back
                                                    // Aerial's landing lag
}

// 0x8014BCF4
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Up Aerial Landing
// Animation callback
void ftGw_LandingAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_Landing_Anim(gobj);
    if (fp->action_id != AS_GAMEWATCH_LANDINGAIRHI) {
        ftGw_Init_OnDamage(gobj);
    }
}

// 0x8014BD40 - Mr. Game & Watch's Up Aerial Landing IASA callback
void ftGw_LandingAirHi_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014BD44
// https://decomp.me/scratch/SqMil // Mr. Game & Watch's Up Aerial Landing
// Physics callback
void ftGw_LandingAirHi_Phys(HSD_GObj* gobj)
{
    ftCo_Landing_Phys(gobj);
}

// 0x8014BD64
// https://decomp.me/scratch/2K68T // Mr. Game & Watch's Up Aerial Landing
// Collision callback
void ftGw_LandingAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_Landing_Coll(gobj);
    if (fp->action_id != AS_GAMEWATCH_LANDINGAIRHI) {
        ftGw_Init_OnDamage(gobj);
    }
}

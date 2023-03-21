#include "forward.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ftGameWatch/ftgamewatch.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"

#include <dolphin/mtx/types.h>

static void ftGameWatch_AttackAir_ExitItemHitlag(HSD_GObj*);

// 0x8014AFC0
// https://decomp.me/scratch/wJ5b7 // Create Parachute Item
void ftGameWatch_ItemParachuteSetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        ftGameWatch_ItemParachuteOnLand(gobj);
    } else {
        func_8000B1CC(fp->x5E8_fighterBones[1].x0_jobj, NULL, &sp10);
        fp->fv.gw.x2258_parachuteGObj =
            func_802C6C38(gobj, &sp10, 1, fp->facing_dir);
        if (fp->fv.gw.x2258_parachuteGObj != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
            fp->cb.x21D4_callback_EnterHitlag =
                ftGameWatch_AttackAir_EnterItemHitlag;
            fp->cb.x21D8_callback_ExitHitlag =
                ftGameWatch_AttackAir_ExitItemHitlag;
        }
    }
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014B074
// https://decomp.me/scratch/TaqkV // Parachute Accessory Callback - Landing
// Lag
void ftGameWatch_ItemParachuteOnLand(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        ftGameWatch_AttackAir_ExitItemHitlag(gobj);
        if (fp->action_id == ftGw_MS_LandingAirN) {
            func_802C6E50(fp->fv.gw.x2258_parachuteGObj);
        }
        fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        fp->cb.x21D4_callback_EnterHitlag =
            ftGameWatch_AttackAir_EnterItemHitlag;
        fp->cb.x21D8_callback_ExitHitlag =
            ftGameWatch_AttackAir_ExitItemHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014B0F0
// https://decomp.me/scratch/8jiZT // Parachute item flag update on land +
// clear pointers
void ftGameWatch_ItemParachuteSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGameWatch_AttackAir_ExitItemHitlag(gobj);
    fp->fv.gw.x2258_parachuteGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

/// Remove Parachute item
void ftGameWatch_ItemParachuteRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        func_802C6D6C(fp->fv.gw.x2258_parachuteGObj);
        ftGameWatch_ItemParachuteSetFlag(gobj);
    }
}

// 0x8014B18C
// https://decomp.me/scratch/hJ3U1 // Check if Mr. Game & Watch is performing
// Neutral Aerial / Neutral Aerial landing
bool ftGameWatch_ItemCheckParachuteRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 asid = fp->action_id;

    if (asid >= ftGw_MS_AttackAirN && asid <= ftGw_MS_LandingAirN)
        return false;

    return true;
}

static void ftGameWatch_ItemTurtleOnLand(HSD_GObj*);

// 0x8014B1B4
// https://decomp.me/scratch/1sOUQ // Create Turtle Item
void ftGameWatch_ItemTurtleSetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        ftGameWatch_ItemTurtleOnLand(gobj);
    } else {
        func_8000B1CC(fp->x5E8_fighterBones[0x11].x0_jobj, NULL, &sp10);
        fp->fv.gw.x225C_turtleGObj =
            func_802C6F40(gobj, &sp10, 0x11, fp->facing_dir);
        if (fp->fv.gw.x225C_turtleGObj != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
            fp->cb.x21D4_callback_EnterHitlag =
                ftGameWatch_AttackAir_EnterItemHitlag;
            fp->cb.x21D8_callback_ExitHitlag =
                ftGameWatch_AttackAir_ExitItemHitlag;
        }
    }
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014B268
// https://decomp.me/scratch/R20Hy // Turtle Accessory Callback - Landing Lag
static void ftGameWatch_ItemTurtleOnLand(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        ftGameWatch_AttackAir_ExitItemHitlag(gobj);

        // Deliberate ASID mismatch to prevent item animation from freezing???
        if (fp->action_id == ftGw_MS_LandingAirN)
            func_802C7158(fp->fv.gw.x225C_turtleGObj);

        fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        fp->cb.x21D4_callback_EnterHitlag =
            ftGameWatch_AttackAir_EnterItemHitlag;
        fp->cb.x21D8_callback_ExitHitlag =
            ftGameWatch_AttackAir_ExitItemHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014B2E4
// https://decomp.me/scratch/bOMxY // Turtle item flag update on land + clear
// pointers
void ftGameWatch_ItemTurtleSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGameWatch_AttackAir_ExitItemHitlag(gobj);
    fp->fv.gw.x225C_turtleGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

// 0x8014B320
// https://decomp.me/scratch/jzWrr // Remove Turtle item
void ftGameWatch_ItemTurtleRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        func_802C7074(fp->fv.gw.x225C_turtleGObj);
        ftGameWatch_ItemTurtleSetFlag(gobj);
    }
}

// 0x8014B380
// https://decomp.me/scratch/xFOBA // Check if Mr. Game & Watch is performing
// Back Aerial / Back Aerial Landing Lag
bool ftGameWatch_ItemCheckTurtleRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ASID = fp->action_id;

    if ((ASID >= ftGw_MS_AttackAirB) && (ASID <= ftGw_MS_LandingAirB)) {
        return false;
    }
    return true;
}

/// Create Sparky Item
void ftGameWatch_ItemSparkySetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        ftGameWatch_ItemSparkyOnLand(gobj);
    } else {
        func_8000B1CC(fp->x5E8_fighterBones[0x15].x0_jobj, NULL, &sp10);
        fp->fv.gw.x2260_sparkyGObj =
            func_802C720C(gobj, &sp10, 0x15, fp->facing_dir);
        if (fp->fv.gw.x2260_sparkyGObj != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
            fp->cb.x21D4_callback_EnterHitlag =
                ftGameWatch_AttackAir_EnterItemHitlag;
            fp->cb.x21D8_callback_ExitHitlag =
                ftGameWatch_AttackAir_ExitItemHitlag;
        }
    }
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014B45C
// https://decomp.me/scratch/9eoJs // Sparky Accessory Callback - Landing Lag
void ftGameWatch_ItemSparkyOnLand(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        ftGameWatch_AttackAir_ExitItemHitlag(gobj);

        if (fp->action_id == ftGw_MS_LandingAirN)
            func_802C7424(fp->fv.gw.x2260_sparkyGObj);

        fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        fp->cb.x21D4_callback_EnterHitlag =
            ftGameWatch_AttackAir_EnterItemHitlag;
        fp->cb.x21D8_callback_ExitHitlag =
            ftGameWatch_AttackAir_ExitItemHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014B4D8
// https://decomp.me/scratch/bdjqs // Sparky item flag update on land + clear
// pointers
void ftGameWatch_ItemSparkySetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGameWatch_AttackAir_ExitItemHitlag(gobj);
    fp->fv.gw.x2260_sparkyGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

// 0x8014B514
// https://decomp.me/scratch/xkjj4 // Remove Sparky item
void ftGameWatch_ItemSparkyRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        func_802C7340(fp->fv.gw.x2260_sparkyGObj);
        ftGameWatch_ItemSparkySetFlag(gobj);
    }
}

// 0x8014B574
// https://decomp.me/scratch/EsqL3 // Apply hitlag for available AttackAir
// items
void ftGameWatch_AttackAir_EnterItemHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        func_802C6DB8(fp->fv.gw.x2258_parachuteGObj);
    }
    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        func_802C70C0(fp->fv.gw.x225C_turtleGObj);
    }
    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        func_802C738C(fp->fv.gw.x2260_sparkyGObj);
    }
}

// 0x8014B5CC - Remove hitlag for available AttackAir items
static void ftGameWatch_AttackAir_ExitItemHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        func_802C6DD8(fp->fv.gw.x2258_parachuteGObj);
    }
    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        func_802C70E0(fp->fv.gw.x225C_turtleGObj);
    }
    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        func_802C73AC(fp->fv.gw.x2260_sparkyGObj);
    }
}

// 0x8014B624
// https://decomp.me/scratch/vpCdl // Check if Mr. Game & Watch is performing
// Up Aerial / Up Aerial Landing Lag
bool ftGameWatch_ItemCheckSparkyRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ASID = fp->action_id;

    if ((ASID >= ftGw_MS_AttackAirHi) && (ASID <= ftGw_MS_LandingAirHi)) {
        return false;
    }
    return true;
}

static void ftGameWatch_AttackAirB_Action(HSD_GObj*);
static void ftGameWatch_AttackAirHi_Action(HSD_GObj*);

// 0x8014B64C
// https://decomp.me/scratch/Ads9W // Decide Mr. Game & Watch's Aerial Attack
// Action State
void ftGameWatch_AttackAir_DecideAction(HSD_GObj* gobj)
{
    enum_t ASID = func_8008CE68(GET_FIGHTER(gobj));

    switch (ASID) {
    case ftCo_MS_AttackAirN:
        ftGameWatch_AttackAirN_Action(gobj);
        return;
    case ftCo_MS_AttackAirF:
        func_8008CFAC(gobj, ASID);
        return;
    case ftCo_MS_AttackAirB:
        ftGameWatch_AttackAirB_Action(gobj);
        return;
    case ftCo_MS_AttackAirHi:
        ftGameWatch_AttackAirHi_Action(gobj);
        return;
    case ftCo_MS_AttackAirLw:
        func_8008CFAC(gobj, ASID);
        return;
    }
}

// 0x8014B6E4
// https://decomp.me/scratch/iunEP // Mr. Game & Watch's Neutral Aerial Action
// State handler
void ftGameWatch_AttackAirN_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8008CFAC(gobj, ftGw_MS_AttackAirN);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemParachuteSetup;
}

// 0x8014B720
// https://decomp.me/scratch/AxMcb // Mr. Game & Watch's Neutral Aerial
// Animation callback
void ftGameWatch_AttackAirN_Anim(HSD_GObj* gobj)
{
    func_8008D010(gobj);
}

// 0x8014B740
// https://decomp.me/scratch/PnNzC // Mr. Game & Watch's Neutral Aerial IASA
// callback
void ftGameWatch_AttackAirN_IASA(HSD_GObj* gobj)
{
    func_8008D08C(gobj);
}

// 0x8014B760
// https://decomp.me/scratch/EBIVr // Mr. Game & Watch's Neutral Aerial Physics
// callback
void ftGameWatch_AttackAirN_Phys(HSD_GObj* gobj)
{
    func_80084DB0(gobj);
}

// 0x8014B780
// https://decomp.me/scratch/aIqYH // Mr. Game & Watch's Neutral Aerial
// Collision callback
void ftGameWatch_AttackAirN_Coll(HSD_GObj* gobj)
{
    func_80082C74(gobj, ftGameWatch_LandingAirN_Action);
}

static void ftGameWatch_LandingAirN_Init(HSD_GObj*);

/// Mr. Game & Watch - LandingAirN Think
void ftGameWatch_LandingAirN_Action(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->fv.gw.x2258_parachuteGObj != NULL)
        func_802C6DD8(fp->fv.gw.x2258_parachuteGObj);

    if (fp->fv.gw.x225C_turtleGObj != NULL)
        func_802C70E0(fp->fv.gw.x225C_turtleGObj);

    if (fp->fv.gw.x2260_sparkyGObj != NULL)
        func_802C73AC(fp->fv.gw.x2260_sparkyGObj);

    if ((u32) fp->x2200_ftcmd_var0 != 0U) {
        ftGameWatch_LandingAirN_Init(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemParachuteOnLand;
        return;
    }

    func_800D5BF8(gobj);
    ftGameWatch_OnDamage(gobj);
}

// 0x8014B840
// https://decomp.me/scratch/iunEP // Mr. Game & Watch's Back Aerial Action
// State handler
static void ftGameWatch_AttackAirB_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8008CFAC(gobj, ftGw_MS_AttackAirB);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemTurtleSetup;
}

// 0x8014B87C
// https://decomp.me/scratch/AxMcb // Mr. Game & Watch's Back Aerial Animation
// callback
void ftGameWatch_AttackAirB_Anim(HSD_GObj* gobj)
{
    func_8008D010(gobj);
}

// 0x8014B89C
// https://decomp.me/scratch/PnNzC // Mr. Game & Watch's Back Aerial IASA
// callback
void ftGameWatch_AttackAirB_IASA(HSD_GObj* gobj)
{
    func_8008D29C(gobj);
}

// 0x8014B8BC
// https://decomp.me/scratch/EBIVr // Mr. Game & Watch's Back Aerial Physics
// callback
void ftGameWatch_AttackAirB_Phys(HSD_GObj* gobj)
{
    func_80084DB0(gobj);
}

// 0x8014B8DC
// https://decomp.me/scratch/aIqYH // Mr. Game & Watch's Back Aerial Collision
// callback
void ftGameWatch_AttackAirB_Coll(HSD_GObj* gobj)
{
    func_80082C74(gobj, ftGameWatch_LandingAirB_Action);
}

/// Mr. Game & Watch - LandingAirB Think
void ftGameWatch_LandingAirB_Action(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->fv.gw.x2258_parachuteGObj != NULL)
        func_802C6DD8(fp->fv.gw.x2258_parachuteGObj);

    if (fp->fv.gw.x225C_turtleGObj != NULL)
        func_802C70E0(fp->fv.gw.x225C_turtleGObj);

    if (fp->fv.gw.x2260_sparkyGObj != NULL)
        func_802C73AC(fp->fv.gw.x2260_sparkyGObj);

    if ((u32) fp->x2200_ftcmd_var0 != 0) {
        ftGameWatch_LandingAirB_Init(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemTurtleOnLand;
        return;
    }

    func_800D5BF8(gobj);
    ftGameWatch_OnDamage(gobj);
}

/// Mr. Game & Watch's Up Aerial Action State handler
static void ftGameWatch_AttackAirHi_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8008CFAC(gobj, ftGw_MS_AttackAirHi);
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemSparkySetup;
}

/// Mr. Game & Watch's Up Aerial Animation callback
void ftGameWatch_AttackAirHi_Anim(HSD_GObj* gobj)
{
    func_8008D010(gobj);
}

/// Mr. Game & Watch's Up Aerial IASA callback
void ftGameWatch_AttackAirHi_IASA(HSD_GObj* gobj)
{
    func_8008D3A4(gobj);
}

/// Mr. Game & Watch's Back Aerial Physics callback
void ftGameWatch_AttackAirHi_Phys(HSD_GObj* gobj)
{
    func_80084DB0(gobj);
}

/// Mr. Game & Watch's Back Aerial Collision callback
void ftGameWatch_AttackAirHi_Coll(HSD_GObj* gobj)
{
    func_80082C74(gobj, ftGameWatch_LandingAirHi_Action);
}

/// Mr. Game & Watch - LandingAirHi Think
void ftGameWatch_LandingAirHi_Action(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->fv.gw.x2258_parachuteGObj != NULL)
        func_802C6DD8(fp->fv.gw.x2258_parachuteGObj);

    if (fp->fv.gw.x225C_turtleGObj != NULL)
        func_802C70E0(fp->fv.gw.x225C_turtleGObj);

    if (fp->fv.gw.x2260_sparkyGObj != NULL)
        func_802C73AC(fp->fv.gw.x2260_sparkyGObj);

    if (fp->x2200_ftcmd_var0 != 0) {
        ftGameWatch_LandingAirHi_Init(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemSparkyOnLand;
        return;
    }

    func_800D5BF8(gobj);
    ftGameWatch_OnDamage(gobj);
}

// 0x8014BAF8
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Neutral Aerial Landing
// prefunction
static void ftGameWatch_LandingAirN_Init(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    func_8008D708(gobj, ftGw_MS_LandingAirN,
                  fp->x110_attr.x1F8_NAirLandingLag);
}

// 0x8014BB24
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Neutral Aerial Landing
// Animation callback
void ftGameWatch_LandingAirN_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_800D5D3C(gobj);
    if (fp->action_id != ftGw_MS_LandingAirN) {
        ftGameWatch_OnDamage(gobj);
    }
}

// 0x8014BB70 - Mr. Game & Watch's Neutral Aerial Landing IASA callback
void ftGameWatch_LandingAirN_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014BB74
// https://decomp.me/scratch/SqMil // Mr. Game & Watch's Neutral Aerial Landing
// Physics callback
void ftGameWatch_LandingAirN_Phys(HSD_GObj* gobj)
{
    func_800D5F18(gobj);
}

// 0x8014BB94
// https://decomp.me/scratch/2K68T // Mr. Game & Watch's Neutral Aerial Landing
// Collision callback
void ftGameWatch_LandingAirN_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_800D5F38(gobj);
    if (fp->action_id != ftGw_MS_LandingAirN) {
        ftGameWatch_OnDamage(gobj);
    }
}

// 0x8014BBE0
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Back Aerial Landing
// prefunction
void ftGameWatch_LandingAirB_Init(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8008D708(gobj, ftGw_MS_LandingAirB,
                  fp->x110_attr.x200_BAirLandingLag);
}

// 0x8014BC0C
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Back Aerial Landing
// Animation callback
void ftGameWatch_LandingAirB_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_800D5D3C(gobj);
    if (fp->action_id != ftGw_MS_LandingAirB) {
        ftGameWatch_OnDamage(gobj);
    }
}

// 0x8014BC58 - Mr. Game & Watch's Back Aerial Landing IASA callback
void ftGameWatch_LandingAirB_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014BC5C
// https://decomp.me/scratch/SqMil // Mr. Game & Watch's Back Aerial Landing
// Physics callback
void ftGameWatch_LandingAirB_Phys(HSD_GObj* gobj)
{
    func_800D5F18(gobj);
}

// 0x8014BC7C
// https://decomp.me/scratch/2K68T // Mr. Game & Watch's Back Aerial Landing
// Collision callback
void ftGameWatch_LandingAirB_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_800D5F38(gobj);
    if (fp->action_id != ftGw_MS_LandingAirB) {
        ftGameWatch_OnDamage(gobj);
    }
}

// 0x8014BCC8
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Up Aerial Landing
// prefunction
void ftGameWatch_LandingAirHi_Init(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8008D708(gobj, ftGw_MS_LandingAirHi,
                  fp->x110_attr.x200_BAirLandingLag); // Erroneously using Back
                                                      // Aerial's landing lag
}

// 0x8014BCF4
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Up Aerial Landing
// Animation callback
void ftGameWatch_LandingAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_800D5D3C(gobj);
    if (fp->action_id != ftGw_MS_LandingAirHi) {
        ftGameWatch_OnDamage(gobj);
    }
}

// 0x8014BD40 - Mr. Game & Watch's Up Aerial Landing IASA callback
void ftGameWatch_LandingAirHi_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014BD44
// https://decomp.me/scratch/SqMil // Mr. Game & Watch's Up Aerial Landing
// Physics callback
void ftGameWatch_LandingAirHi_Phys(HSD_GObj* gobj)
{
    func_800D5F18(gobj);
}

// 0x8014BD64
// https://decomp.me/scratch/2K68T // Mr. Game & Watch's Up Aerial Landing
// Collision callback
void ftGameWatch_LandingAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_800D5F38(gobj);
    if (fp->action_id != ftGw_MS_LandingAirHi) {
        ftGameWatch_OnDamage(gobj);
    }
}

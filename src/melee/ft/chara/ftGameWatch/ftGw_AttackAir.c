#include "ftGw_AttackAir.h"

#include "ftGw_Init.h"

#include <platform.h>

#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AttackAir.h"
#include "ftCommon/ftCo_LandingAir.h"
#include "ftGameWatch/types.h"
#include "it/items/it_27CF.h"
#include "it/items/itgamewatchbreath.h"
#include "it/items/itgamewatchturtle.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>

static void ftGw_AttackAirN_ExitItemHitlag(HSD_GObj*);

// 0x8014AFC0
// https://decomp.me/scratch/wJ5b7 // Create Parachute Item
void ftGw_AttackAirN_ItemParachuteSetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        ftGw_AttackAirN_ItemParachuteOnLand(gobj);
    } else {
        lb_8000B1CC(fp->parts[FtPart_TransN].joint, NULL, &sp10);
        fp->fv.gw.x2258_parachuteGObj =
            it_802C6C38(gobj, &sp10, FtPart_TransN, fp->facing_dir);
        if (fp->fv.gw.x2258_parachuteGObj != NULL) {
            fp->death2_cb = ftGw_Init_OnDamage;
            fp->take_dmg_cb = ftGw_Init_OnDamage;
            fp->pre_hitlag_cb = ftGw_AttackAirN_EnterItemHitlag;
            fp->post_hitlag_cb = ftGw_AttackAirN_ExitItemHitlag;
        }
    }
    fp->accessory4_cb = NULL;
}

// 0x8014B074
// https://decomp.me/scratch/TaqkV // Parachute Accessory Callback - Landing
// Lag
void ftGw_AttackAirN_ItemParachuteOnLand(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        ftGw_AttackAirN_ExitItemHitlag(gobj);
        if (fp->motion_id == ftGw_MS_LandingAirN) {
            it_802C6E50(fp->fv.gw.x2258_parachuteGObj);
        }
        fp->death2_cb = ftGw_Init_OnDamage;
        fp->take_dmg_cb = ftGw_Init_OnDamage;
        fp->pre_hitlag_cb = ftGw_AttackAirN_EnterItemHitlag;
        fp->post_hitlag_cb = ftGw_AttackAirN_ExitItemHitlag;
        fp->accessory4_cb = NULL;
    }
}

// 0x8014B0F0
// https://decomp.me/scratch/8jiZT // Parachute item flag update on land +
// clear pointers
void ftGw_AttackAirN_ItemParachuteSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGw_AttackAirN_ExitItemHitlag(gobj);
    fp->fv.gw.x2258_parachuteGObj = NULL;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

/// Remove Parachute item
void ftGw_AttackAirN_ItemParachuteRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        it_802C6D6C(fp->fv.gw.x2258_parachuteGObj);
        ftGw_AttackAirN_ItemParachuteSetFlag(gobj);
    }
}

// 0x8014B18C
// https://decomp.me/scratch/hJ3U1 // Check if Mr. Game & Watch is performing
// Neutral Aerial / Neutral Aerial landing
bool ftGw_AttackAirN_ItemCheckParachuteRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = fp->motion_id;

    if (msid >= ftGw_MS_AttackAirN && msid <= ftGw_MS_LandingAirN) {
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

    u8 _[4];

    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        ftGw_AttackAirN_ItemTurtleOnLand(gobj);
    } else {
        lb_8000B1CC(fp->parts[FtPart_LShoulderN].joint, NULL, &sp10);
        fp->fv.gw.x225C_turtleGObj =
            it_802C6F40(gobj, &sp10, FtPart_LShoulderN, fp->facing_dir);
        if (fp->fv.gw.x225C_turtleGObj != NULL) {
            fp->death2_cb = ftGw_Init_OnDamage;
            fp->take_dmg_cb = ftGw_Init_OnDamage;
            fp->pre_hitlag_cb = ftGw_AttackAirN_EnterItemHitlag;
            fp->post_hitlag_cb = ftGw_AttackAirN_ExitItemHitlag;
        }
    }
    fp->accessory4_cb = NULL;
}

// 0x8014B268
// https://decomp.me/scratch/R20Hy // Turtle Accessory Callback - Landing Lag
static void ftGw_AttackAirN_ItemTurtleOnLand(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        ftGw_AttackAirN_ExitItemHitlag(gobj);

        // Deliberate msid mismatch to prevent item animation from freezing???
        if (fp->motion_id == ftGw_MS_LandingAirN) {
            it_802C7158(fp->fv.gw.x225C_turtleGObj);
        }

        fp->death2_cb = ftGw_Init_OnDamage;
        fp->take_dmg_cb = ftGw_Init_OnDamage;
        fp->pre_hitlag_cb = ftGw_AttackAirN_EnterItemHitlag;
        fp->post_hitlag_cb = ftGw_AttackAirN_ExitItemHitlag;
        fp->accessory4_cb = NULL;
    }
}

// 0x8014B2E4
// https://decomp.me/scratch/bOMxY // Turtle item flag update on land + clear
// pointers
void ftGw_AttackAirN_ItemTurtleSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGw_AttackAirN_ExitItemHitlag(gobj);
    fp->fv.gw.x225C_turtleGObj = NULL;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

// 0x8014B320
// https://decomp.me/scratch/jzWrr // Remove Turtle item
void ftGw_AttackAirN_ItemTurtleRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        it_802C7074(fp->fv.gw.x225C_turtleGObj);
        ftGw_AttackAirN_ItemTurtleSetFlag(gobj);
    }
}

// 0x8014B380
// https://decomp.me/scratch/xFOBA // Check if Mr. Game & Watch is performing
// Back Aerial / Back Aerial Landing Lag
bool ftGw_AttackAirN_ItemCheckTurtleRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = fp->motion_id;

    if ((msid >= ftGw_MS_AttackAirB) && (msid <= ftGw_MS_LandingAirB)) {
        return false;
    }
    return true;
}

/// Create Sparky Item
void ftGw_AttackAirN_ItemSparkySetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp = getFighter(gobj);

    u8 _[4];

    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        ftGw_AttackAirN_ItemSparkyOnLand(gobj);
    } else {
        lb_8000B1CC(fp->parts[FtPart_LHandN].joint, NULL, &sp10);
        fp->fv.gw.x2260_sparkyGObj =
            it_802C720C(gobj, &sp10, FtPart_LHandN, fp->facing_dir);
        if (fp->fv.gw.x2260_sparkyGObj != NULL) {
            fp->death2_cb = ftGw_Init_OnDamage;
            fp->take_dmg_cb = ftGw_Init_OnDamage;
            fp->pre_hitlag_cb = ftGw_AttackAirN_EnterItemHitlag;
            fp->post_hitlag_cb = ftGw_AttackAirN_ExitItemHitlag;
        }
    }
    fp->accessory4_cb = NULL;
}

// 0x8014B45C
// https://decomp.me/scratch/9eoJs // Sparky Accessory Callback - Landing Lag
void ftGw_AttackAirN_ItemSparkyOnLand(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        ftGw_AttackAirN_ExitItemHitlag(gobj);

        if (fp->motion_id == ftGw_MS_LandingAirN) {
            it_802C7424(fp->fv.gw.x2260_sparkyGObj);
        }

        fp->death2_cb = ftGw_Init_OnDamage;
        fp->take_dmg_cb = ftGw_Init_OnDamage;
        fp->pre_hitlag_cb = ftGw_AttackAirN_EnterItemHitlag;
        fp->post_hitlag_cb = ftGw_AttackAirN_ExitItemHitlag;
        fp->accessory4_cb = NULL;
    }
}

// 0x8014B4D8
// https://decomp.me/scratch/bdjqs // Sparky item flag update on land + clear
// pointers
void ftGw_AttackAirN_ItemSparkySetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGw_AttackAirN_ExitItemHitlag(gobj);
    fp->fv.gw.x2260_sparkyGObj = NULL;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

// 0x8014B514
// https://decomp.me/scratch/xkjj4 // Remove Sparky item
void ftGw_AttackAirN_ItemSparkyRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        it_802C7340(fp->fv.gw.x2260_sparkyGObj);
        ftGw_AttackAirN_ItemSparkySetFlag(gobj);
    }
}

// 0x8014B574
// https://decomp.me/scratch/EsqL3 // Apply hitlag for available AttackAir
// items
void ftGw_AttackAirN_EnterItemHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        it_802C6DB8(fp->fv.gw.x2258_parachuteGObj);
    }
    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        it_802C70C0(fp->fv.gw.x225C_turtleGObj);
    }
    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        it_802C738C(fp->fv.gw.x2260_sparkyGObj);
    }
}

// 0x8014B5CC - Remove hitlag for available AttackAir items
static void ftGw_AttackAirN_ExitItemHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        it_802C6DD8(fp->fv.gw.x2258_parachuteGObj);
    }
    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        it_802C70E0(fp->fv.gw.x225C_turtleGObj);
    }
    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        it_802C73AC(fp->fv.gw.x2260_sparkyGObj);
    }
}

// 0x8014B624
// https://decomp.me/scratch/vpCdl // Check if Mr. Game & Watch is performing
// Up Aerial / Up Aerial Landing Lag
bool ftGw_AttackAirN_ItemCheckSparkyRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = fp->motion_id;

    if ((msid >= ftGw_MS_AttackAirHi) && (msid <= ftGw_MS_LandingAirHi)) {
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
    FtMotionId msid = ftCo_AttackAir_GetMsidFromCStick(GET_FIGHTER(gobj));

    switch (msid) {
    case ftCo_MS_AttackAirN:
        ftGw_AttackAirN_Enter(gobj);
        return;
    case ftCo_MS_AttackAirF:
        ftCo_AttackAir_EnterFromMsid(gobj, msid);
        return;
    case ftCo_MS_AttackAirB:
        ftGw_AttackAirB_Enter(gobj);
        return;
    case ftCo_MS_AttackAirHi:
        ftGw_AttackAirHi_Enter(gobj);
        return;
    case ftCo_MS_AttackAirLw:
        ftCo_AttackAir_EnterFromMsid(gobj, msid);
        return;
    }
}

// 0x8014B6E4
// https://decomp.me/scratch/iunEP // Mr. Game & Watch's Neutral Aerial Action
// State handler
void ftGw_AttackAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_AttackAir_EnterFromMsid(gobj, ftGw_MS_AttackAirN);
    fp->accessory4_cb = ftGw_AttackAirN_ItemParachuteSetup;
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

    u8 _[8];

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        it_802C6DD8(fp->fv.gw.x2258_parachuteGObj);
    }

    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        it_802C70E0(fp->fv.gw.x225C_turtleGObj);
    }

    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        it_802C73AC(fp->fv.gw.x2260_sparkyGObj);
    }

    if ((u32) fp->cmd_vars[0] != 0U) {
        ftGw_LandingAirN_Init(gobj);
        fp->accessory4_cb = ftGw_AttackAirN_ItemParachuteOnLand;
        return;
    }

    ftCo_800D5BF8(gobj);
    ftGw_Init_OnDamage(gobj);
}

// 0x8014B840
// https://decomp.me/scratch/iunEP // Mr. Game & Watch's Back Aerial Action
// State handler
static void ftGw_AttackAirB_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_AttackAir_EnterFromMsid(gobj, ftGw_MS_AttackAirB);
    fp->accessory4_cb = ftGw_AttackAirN_ItemTurtleSetup;
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

    u8 _[8];

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        it_802C6DD8(fp->fv.gw.x2258_parachuteGObj);
    }

    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        it_802C70E0(fp->fv.gw.x225C_turtleGObj);
    }

    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        it_802C73AC(fp->fv.gw.x2260_sparkyGObj);
    }

    if ((u32) fp->cmd_vars[0] != 0) {
        ftGw_LandingAirB_Init(gobj);
        fp->accessory4_cb = ftGw_AttackAirN_ItemTurtleOnLand;
        return;
    }

    ftCo_800D5BF8(gobj);
    ftGw_Init_OnDamage(gobj);
}

/// Mr. Game & Watch's Up Aerial Motion State handler
static void ftGw_AttackAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_AttackAir_EnterFromMsid(gobj, ftGw_MS_AttackAirHi);
    fp->accessory4_cb = ftGw_AttackAirN_ItemSparkySetup;
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

    u8 _[8];

    if (fp->fv.gw.x2258_parachuteGObj != NULL) {
        it_802C6DD8(fp->fv.gw.x2258_parachuteGObj);
    }

    if (fp->fv.gw.x225C_turtleGObj != NULL) {
        it_802C70E0(fp->fv.gw.x225C_turtleGObj);
    }

    if (fp->fv.gw.x2260_sparkyGObj != NULL) {
        it_802C73AC(fp->fv.gw.x2260_sparkyGObj);
    }

    if (fp->cmd_vars[0] != 0) {
        ftGw_LandingAirHi_Init(gobj);
        fp->accessory4_cb = ftGw_AttackAirN_ItemSparkyOnLand;
        return;
    }

    ftCo_800D5BF8(gobj);
    ftGw_Init_OnDamage(gobj);
}

// 0x8014BAF8
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Neutral Aerial Landing
// prefunction
static void ftGw_LandingAirN_Init(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    ftCo_LandingAir_EnterWithMsidLag(gobj, ftGw_MS_LandingAirN,
                                     fp->co_attrs.landingairn_lag);
}

// 0x8014BB24
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Neutral Aerial Landing
// Animation callback
void ftGw_LandingAirN_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_Landing_Anim(gobj);
    if (fp->motion_id != ftGw_MS_LandingAirN) {
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
    if (fp->motion_id != ftGw_MS_LandingAirN) {
        ftGw_Init_OnDamage(gobj);
    }
}

// 0x8014BBE0
// https://decomp.me/scratch/8ClCw // Mr. Game & Watch's Back Aerial Landing
// prefunction
void ftGw_LandingAirB_Init(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_LandingAir_EnterWithMsidLag(gobj, ftGw_MS_LandingAirB,
                                     fp->co_attrs.landingairb_lag);
}

// 0x8014BC0C
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Back Aerial Landing
// Animation callback
void ftGw_LandingAirB_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_Landing_Anim(gobj);
    if (fp->motion_id != ftGw_MS_LandingAirB) {
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
    if (fp->motion_id != ftGw_MS_LandingAirB) {
        ftGw_Init_OnDamage(gobj);
    }
}

/// Mr. Game & Watch's Up Aerial Landing prefunction
void ftGw_LandingAirHi_Init(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    // Erroneously using Back Aerial's landing lag
    ftCo_LandingAir_EnterWithMsidLag(gobj, ftGw_MS_LandingAirHi,
                                     fp->co_attrs.landingairb_lag);
}

// 0x8014BCF4
// https://decomp.me/scratch/xQdJ2 // Mr. Game & Watch's Up Aerial Landing
// Animation callback
void ftGw_LandingAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_Landing_Anim(gobj);
    if (fp->motion_id != ftGw_MS_LandingAirHi) {
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
    if (fp->motion_id != ftGw_MS_LandingAirHi) {
        ftGw_Init_OnDamage(gobj);
    }
}

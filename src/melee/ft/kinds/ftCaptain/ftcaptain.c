/**
 * @file ftcaptain.c
 * @brief Captain Falcon character initialization, state table, and lifecycle
 * callbacks
 * @details Implements lifecycle callbacks (load, death, item handling) and
 * defines the motion state table binding animation, physics, collision, and
 * camera callbacks for Captain Falcon (and Ganondorf). Module prefix: ftCa
 */

#include "ftcaptain.h"

#include <melee/ft/kinds/ftCommon/forward.h>

#include "forward.h"
#include "ftcaptainspecialhi.h"
#include "ftcaptainspeciallw.h"
#include "ftcaptainspecialn.h"
#include "ftcaptainspecials.h"
#include "types.h"
#include <melee/ft/ft_0CD1.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftlipstickswing.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/ftstarrodswing.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>

/// Costume metadata list for Captain Falcon's 6 costume colors
/* 459A98 */ UnkCostumeStruct ftCa_CostumeList[6];

/// Motion state table defining animation, IASA, physics, and collision
/// callbacks for Captain Falcon
MotionState ftCa_Init_MotionStateTable[ftCa_MS_SelfCount] = {
    {
        // ftCa_MS_SwordSwing4 = 341 (Beam Sword Forward Smash)
        ftCa_SM_SwordSwing4,
        ftCo_MF_SwordSwing4,
        FtMoveId_SwordSwing4 << 24,
        ftCo_SwordSwing_Anim,
        ftCo_SwordSwing_IASA,
        ftCo_SwordSwing_Phys,
        ftCo_SwordSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_BatSwing4 = 342 (Home-Run Bat Forward Smash)
        ftCa_SM_BatSwing4,
        ftCo_MF_BatSwing4,
        FtMoveId_BatSwing4 << 24,
        ftCo_BatSwing_Anim,
        ftCo_BatSwing_IASA,
        ftCo_BatSwing_Phys,
        ftCo_BatSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_ParasolSwing4 = 343 (Parasol Forward Smash)
        ftCa_SM_ParasolSwing4,
        ftCo_MF_ParasolSwing4,
        FtMoveId_ParasolSwing4 << 24,
        ftCo_ParasolSwing_Anim,
        ftCo_ParasolSwing_IASA,
        ftCo_ParasolSwing_Phys,
        ftCo_ParasolSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_HarisenSwing4 = 344 (Fan Forward Smash)
        ftCa_SM_HarisenSwing4,
        ftCo_MF_HarisenSwing4,
        FtMoveId_HarisenSwing4 << 24,
        ftCo_HarisenSwing_Anim,
        ftCo_HarisenSwing_IASA,
        ftCo_HarisenSwing_Phys,
        ftCo_HarisenSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_StarRodSwing4 = 345 (Star Rod Forward Smash)
        ftCa_SM_StarRodSwing4,
        ftCo_MF_StarRodSwing4,
        FtMoveId_StarRodSwing4 << 24,
        ftCo_StarRodSwing_Anim,
        ftCo_StarRodSwing_IASA,
        ftCo_StarRodSwing_Phys,
        ftCo_StarRodSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_LipstickSwing4 = 346 (Lip's Stick Forward Smash)
        ftCa_SM_LipstickSwing4,
        ftCo_MF_LipstickSwing4,
        FtMoveId_LipstickSwing4 << 24,
        ftCo_LipstickSwing_Anim,
        ftCo_LipstickSwing_IASA,
        ftCo_LipstickSwing_Phys,
        ftCo_LipstickSwing_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialN = 347 (Neutral-B: Grounded Falcon Punch / Warlock
        // Punch)
        ftCa_SM_SpecialN,
        ftCa_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftCa_SpecialN_Anim,
        ftCa_SpecialN_IASA,
        ftCa_SpecialN_Phys,
        ftCa_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialAirN = 348 (Neutral-B: Aerial Falcon Punch / Aerial
        // Warlock Punch)
        ftCa_SM_SpecialAirN,
        ftCa_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftCa_SpecialAirN_Anim,
        ftCa_SpecialAirN_IASA,
        ftCa_SpecialAirN_Phys,
        ftCa_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialSStart = 349 (Side-B: Grounded Raptor Boost Startup
        // Dash)
        ftCa_SM_SpecialSStart,
        ftCa_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftCa_SpecialSStart_Anim,
        ftCa_SpecialSStart_IASA,
        ftCa_SpecialSStart_Phys,
        ftCa_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialS = 350 (Side-B: Grounded Raptor Boost Uppercut Hit)
        ftCa_SM_SpecialS,
        ftCa_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftCa_SpecialS_Anim,
        ftCa_SpecialS_IASA,
        ftCa_SpecialS_Phys,
        ftCa_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialAirSStart = 351 (Side-B: Aerial Raptor Boost Startup
        // Dive)
        ftCa_SM_SpecialAirSStart,
        ftCa_MF_SpecialAirSStart,
        FtMoveId_SpecialS << 24,
        ftCa_SpecialAirSStart_Anim,
        ftCa_SpecialAirSStart_IASA,
        ftCa_SpecialAirSStart_Phys,
        ftCa_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialAirS = 352 (Side-B: Aerial Raptor Boost Meteor Spike
        // Hit)
        ftCa_SM_SpecialAirS,
        ftCa_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftCa_SpecialAirS_Anim,
        ftCa_SpecialAirS_IASA,
        ftCa_SpecialAirS_Phys,
        ftCa_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialHi = 353 (Up-B: Falcon Dive Grounded/Air Startup &
        // Leap)
        ftCa_SM_SpecialHi,
        ftCa_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftCa_SpecialHi_Anim,
        ftCa_SpecialHi_IASA,
        ftCa_SpecialHi_Phys,
        ftCa_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialAirHi = 354 (Up-B: Aerial Falcon Dive Leap)
        ftCa_SM_SpecialAirHi,
        ftCa_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftCa_SpecialAirHi_Anim,
        ftCa_SpecialAirHi_IASA,
        ftCa_SpecialAirHi_Phys,
        ftCa_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialHiCatch = 355 (Up-B: Falcon Dive Command Grab
        // Contact)
        ftCa_SM_SpecialHiCatch,
        ftCa_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftCa_SpecialHiCatch_Anim,
        ftCa_SpecialHiCatch_IASA,
        ftCa_SpecialHiCatch_Phys,
        ftCa_SpecialHiCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialHiThrow = 356 (Up-B: Falcon Dive Explosion Throw
        // Release)
        ftCa_SM_SpecialHiThrow0,
        ftCa_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftCa_SpecialHiThrow0_Anim,
        ftCa_SpecialHiThrow0_IASA,
        ftCa_SpecialHiThrow0_Phys,
        ftCa_SpecialHiThrow0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialLw = 357 (Down-B: Grounded Falcon Kick Dash)
        ftCa_SM_SpecialLw,
        ftCa_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialLw_Anim,
        NULL,
        ftCa_SpecialLw_Phys,
        ftCa_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialLwEnd = 358 (Down-B: Grounded Falcon Kick Ground
        // Recovery)
        ftCa_SM_SpecialLwEnd,
        ftCa_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialLwEnd_Anim,
        NULL,
        ftCa_SpecialLwEnd_Phys,
        ftCa_SpecialLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialAirLw = 359 (Down-B: Aerial Falcon Kick Downward
        // Dive)
        ftCa_SM_SpecialAirLw,
        ftCa_MF_SpecialLwRebound,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialAirLw_Anim,
        NULL,
        ftCa_SpecialAirLw_Phys,
        ftCa_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialAirLwEnd = 360 (Down-B: Aerial Falcon Kick Ground
        // Landing Recovery)
        ftCa_SM_SpecialAirLwEnd,
        ftCa_MF_SpecialLwRebound,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialAirLwEnd_Anim,
        NULL,
        ftCa_SpecialAirLwEnd_Phys,
        ftCa_SpecialAirLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialAirLwEndAir = 361 (Down-B: Aerial Falcon Kick Air End
        // Recovery)
        ftCa_SM_SpecialAirLwEndAir,
        ftCa_MF_SpecialLwRebound,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialAirLwEndAir_Anim,
        NULL,
        ftCa_SpecialAirLwEndAir_Phys,
        ftCa_SpecialAirLwEndAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialLwEndAir = 362 (Down-B: Grounded Falcon Kick Edge
        // Slip Off into Air)
        ftCa_SM_SpecialLwEndAir,
        ftCa_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialLwEndAir_Anim,
        NULL,
        ftCa_SpecialLwEndAir_Phys,
        ftCa_SpecialLwEndAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftCa_MS_SpecialHiThrow1 = 363 (Down-B: Falcon Kick Wall Rebound /
        // Wall Bonk)
        ftCa_SM_SpecialHiThrow1,
        ftCa_MF_SpecialLwRebound,
        FtMoveId_SpecialLw << 24,
        ftCa_SpecialHiThrow1_Anim,
        NULL,
        ftCa_SpecialHiThrow1_Phys,
        ftCa_SpecialHiThrow1_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftCa_Init_DatFilename[] = "PlCa.dat";
char ftCa_Init_DataName[] = "ftDataCaptain";
static char nr_dat[] = "PlCaNr.dat";
static char nr_joint[] = "PlyCaptain5K_Share_joint";
static char gy_dat[] = "PlCaGy.dat";
static char gy_joint[] = "PlyCaptain5KGy_Share_joint";

/**
 * @note The trailing dot is intentional: ::lbFileGetFullName appends "usd" or
 * "dat" to a bare-dot basename based on the language setting, selecting
 * between "PlCaRe.usd" and "PlCaRe.dat" on disc.
 */
char re_dat[] = "PlCaRe.";

static char re_joint[] = "PlyCaptain5KRe_Share_joint";
static char wh_dat[] = "PlCaWh.dat";
static char wh_joint[] = "PlyCaptain5KWh_Share_joint";
static char gr_dat[] = "PlCaGr.dat";
static char gr_joint[] = "PlyCaptain5KGr_Share_joint";
static char bu_dat[] = "PlCaBu.dat";
static char bu_joint[] = "PlyCaptain5KBu_Share_joint";
char ftCa_Init_AnimDatFilename[] = "PlCaAJ.dat";

Fighter_DemoStrings ftCa_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileCaptain",
    "ftDemoIntroMotionFileCaptain",
    "ftDemoEndingMotionFileCaptain",
    "ftDemoViWaitMotionFileCaptain",
};

Fighter_CostumeStrings ftCa_Init_CostumeStrings[] = {
    { nr_dat, nr_joint, NULL }, { gy_dat, gy_joint, NULL },
    { re_dat, re_joint, NULL }, { wh_dat, wh_joint, NULL },
    { gr_dat, gr_joint, NULL }, { bu_dat, bu_joint, NULL },
};

/**
 * @brief Resets character-specific state flags upon Captain Falcon's death.
 * @details Resets model parts and clears Raptor Boost startup and active state
 * flags.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
void ftCa_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->u.ca.during_specials = 0;
    fp->u.ca.during_specials_start = false;
}

/**
 * @brief Callback invoked when Captain Falcon takes damage or dies during
 * Raptor Boost.
 * @details Cleans up lingering flame visual effects by calling
 * ftCa_SpecialS_RemoveGFX.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
void ftCa_Init_800E28C8(HSD_GObj* gobj)
{
    ftCa_SpecialS_RemoveGFX(gobj);
}

/**
 * @brief Handles item pickup for Captain Falcon.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 * @param bool1 Whether item pickup is triggered during an action state
 * transition
 */
void ftCa_Init_OnItemPickup(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemPickup(gobj, bool1, true, true);
}

/**
 * @brief Hides held item when Captain Falcon becomes invisible (e.g. Cloaking
 * Device).
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
void ftCa_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

/**
 * @brief Restores held item visibility when Captain Falcon becomes visible
 * again.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
void ftCa_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

/**
 * @brief Handles item drop/release for Captain Falcon.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 * @param bool1 Flag passed to standard item drop handler
 * @remarks Used for both OnItemRelease and OnUnknownItemRelated
 */
void ftCa_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

/**
 * @brief Initializes character attributes for Ganondorf using Captain Falcon's
 * attribute structure.
 * @details Ganondorf is Captain Falcon's clone in Melee and shares this
 * attribute layout.
 * @param fp Pointer to Ganondorf's Fighter data
 */
void ftCa_Init_OnLoadForGanon(Fighter* fp)
{
    PUSH_ATTRS(fp, ftCaptain_DatAttrs);
}

/**
 * @brief Character initialization callback executed when Captain Falcon is
 * spawned.
 * @details Enables wall jumping (Captain Falcon can wall jump) and loads
 * attribute data.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
void ftCa_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->can_walljump = true;
    PUSH_ATTRS(fp, ftCaptain_DatAttrs);
}

/**
 * @brief Reloads Captain Falcon's special move attributes from the DAT file
 * archive.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
void ftCa_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCaptain_DatAttrs);
}

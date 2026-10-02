/**
 * @file ftseak.c
 * @brief Sheik character callbacks, motion state table, and data attributes.
 * @details Implements Sheik's fighter initialization, death cleanup, item
 * handling, knockback responses, and character motion state definitions for
 * Super Smash Bros. Melee. Module prefix: ftSk (Fighter: Sheik)
 */

#include "ftseak.h"

#include "forward.h"
#include "ftseakspecialhi.h"
#include "ftseakspeciallw.h"
#include "ftseakspecialn.h"
#include "ftseakspecials.h"
#include "types.h"
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftcolanim.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>
#include <melee/it/it_26B1.h>

/* 459D18 */ UnkCostumeStruct ftSk_CostumeList[5];

/// Motion state table mapping Sheik's special move actions (341-364)
MotionState ftSk_Init_MotionStateTable[ftSk_MS_SelfCount] = {
    {
        // ftSk_MS_SpecialNStart = 341: Grounded Neutral-B (Needle Storm)
        // startup
        ftSk_SM_SpecialNStart,
        ftSk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialNStart_Anim,
        ftSk_SpecialNStart_IASA,
        ftSk_SpecialNStart_Phys,
        ftSk_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialNLoop = 342: Grounded Neutral-B (Needle Storm)
        // charging loop
        ftSk_SM_SpecialNLoop,
        ftSk_MF_SpecialNLoop,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialNLoop_Anim,
        ftSk_SpecialNLoop_IASA,
        ftSk_SpecialNLoop_Phys,
        ftSk_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialNCancel = 343: Grounded Neutral-B (Needle Storm)
        // shield cancel
        ftSk_SM_SpecialNCancel,
        ftSk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialNCancel_Anim,
        ftSk_SpecialNCancel_IASA,
        ftSk_SpecialNCancel_Phys,
        ftSk_SpecialNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialNEnd = 344: Grounded Neutral-B (Needle Storm) throw
        // needles
        ftSk_SM_SpecialNEnd,
        ftSk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialNEnd_Anim,
        ftSk_SpecialNEnd_IASA,
        ftSk_SpecialNEnd_Phys,
        ftSk_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirNStart = 345: Aerial Neutral-B (Needle Storm)
        // startup
        ftSk_SM_SpecialAirNStart,
        ftSk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialAirNStart_Anim,
        ftSk_SpecialAirNStart_IASA,
        ftSk_SpecialAirNStart_Phys,
        ftSk_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirNLoop = 346: Aerial Neutral-B (Needle Storm)
        // charging loop
        ftSk_SM_SpecialAirNLoop,
        ftSk_MF_SpecialAirNLoop,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialAirNLoop_Anim,
        ftSk_SpecialAirNLoop_IASA,
        ftSk_SpecialAirNLoop_Phys,
        ftSk_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirNCancel = 347: Aerial Neutral-B (Needle Storm)
        // cancel
        ftSk_SM_SpecialAirNCancel,
        ftSk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialAirNCancel_Anim,
        ftSk_SpecialAirNCancel_IASA,
        ftSk_SpecialAirNCancel_Phys,
        ftSk_SpecialAirNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirNEnd = 348: Aerial Neutral-B (Needle Storm) throw
        // needles
        ftSk_SM_SpecialAirNEnd,
        ftSk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftSk_SpecialAirNEnd_Anim,
        ftSk_SpecialAirNEnd_IASA,
        ftSk_SpecialAirNEnd_Phys,
        ftSk_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialSStart = 349: Grounded Side-B (Chain) startup
        ftSk_SM_SpecialSStart,
        ftSk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialSStart_Anim,
        ftSk_SpecialSStart_IASA,
        ftSk_SpecialSStart_Phys,
        ftSk_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialS = 350: Grounded Side-B (Chain) active whip loop
        ftSk_SM_SpecialS,
        ftSk_MF_SpecialSLoop,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialS_Anim,
        ftSk_SpecialS_IASA,
        ftSk_SpecialS_Phys,
        ftSk_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialSEnd = 351: Grounded Side-B (Chain) retract/end
        ftSk_SM_SpecialSEnd,
        ftSk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialSEnd_Anim,
        ftSk_SpecialSEnd_IASA,
        ftSk_SpecialSEnd_Phys,
        ftSk_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirSStart = 352: Aerial Side-B (Chain) startup
        ftSk_SM_SpecialAirSStart,
        ftSk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialAirSStart_Anim,
        ftSk_SpecialAirSStart_IASA,
        ftSk_SpecialAirSStart_Phys,
        ftSk_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirS = 353: Aerial Side-B (Chain) active whip loop
        ftSk_SM_SpecialAirS,
        ftSk_MF_SpecialAirSLoop,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialAirS_Anim,
        ftSk_SpecialAirS_IASA,
        ftSk_SpecialAirS_Phys,
        ftSk_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirSEnd = 354: Aerial Side-B (Chain) retract/end
        ftSk_SM_SpecialAirSEnd,
        ftSk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftSk_SpecialAirSEnd_Anim,
        ftSk_SpecialAirSEnd_IASA,
        ftSk_SpecialAirSEnd_Phys,
        ftSk_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialHiStart_0 = 355: Grounded Up-B (Vanish) startup /
        // explosion
        ftSk_SM_SpecialHiStart,
        ftSk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialHiStart_0_Anim,
        ftSk_SpecialHiStart_0_IASA,
        ftSk_SpecialHiStart_0_Phys,
        ftSk_SpecialHiStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialHiStart_1 = 356: Grounded Up-B (Vanish) invisible
        // travel
        ftSk_SM_SpecialHiStart,
        ftSk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialHiStart_1_Anim,
        ftSk_SpecialHiStart_1_IASA,
        ftSk_SpecialHiStart_1_Phys,
        ftSk_SpecialHiStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialHi = 357: Grounded Up-B (Vanish) reappearance / end
        ftSk_SM_SpecialHi,
        ftSk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialHi_Anim,
        ftSk_SpecialHi_IASA,
        ftSk_SpecialHi_Phys,
        ftSk_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirHiStart_0 = 358: Aerial Up-B (Vanish) startup /
        // explosion
        ftSk_SM_SpecialAirHiStart,
        ftSk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialAirHiStart_0_Anim,
        ftSk_SpecialAirHiStart_0_IASA,
        ftSk_SpecialAirHiStart_0_Phys,
        ftSk_SpecialAirHiStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirHiStart_1 = 359: Aerial Up-B (Vanish) invisible
        // travel
        ftSk_SM_SpecialAirHiStart,
        ftSk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialAirHiStart_1_Anim,
        ftSk_SpecialAirHiStart_1_IASA,
        ftSk_SpecialAirHiStart_1_Phys,
        ftSk_SpecialAirHiStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirHi = 360: Aerial Up-B (Vanish) reappearance / end
        ftSk_SM_SpecialAirHi,
        ftSk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftSk_SpecialAirHi_Anim,
        ftSk_SpecialAirHi_IASA,
        ftSk_SpecialAirHi_Phys,
        ftSk_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialLw = 361: Grounded Down-B (Transform) phase 1
        // (disappearing)
        ftSk_SM_SpecialLw,
        ftSk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftSk_SpecialLw_Anim,
        ftSk_SpecialLw_IASA,
        ftSk_SpecialLw_Phys,
        ftSk_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialLw2 = 362: Grounded Down-B (Transform) phase 2
        // (reappearing)
        ftSk_SM_SpecialLw2,
        ftSk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftSk_SpecialLw2_Anim,
        ftSk_SpecialLw2_IASA,
        ftSk_SpecialLw2_Phys,
        ftSk_SpecialLw2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirLw = 363: Aerial Down-B (Transform) phase 1
        // (disappearing)
        ftSk_SM_SpecialAirLw,
        ftSk_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftSk_SpecialAirLw_Anim,
        ftSk_SpecialAirLw_IASA,
        ftSk_SpecialAirLw_Phys,
        ftSk_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftSk_MS_SpecialAirLw2 = 364: Aerial Down-B (Transform) phase 2
        // (reappearing)
        ftSk_SM_SpecialAirLw2,
        ftSk_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftSk_SpecialAirLw2_Anim,
        ftSk_SpecialAirLw2_IASA,
        ftSk_SpecialAirLw2_Phys,
        ftSk_SpecialAirLw2_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftSk_Init_DatFilename[] = "PlSk.dat";
char ftSk_Init_DataName[] = "ftDataSeak";
char ftSk_Init_803CC378[] = "PlSkNr.dat";
char ftSk_Init_803CC384[] = "PlySeak5K_Share_joint";
char ftSk_Init_803CC39C[] = "PlySeak5K_Share_matanim_joint";
char ftSk_Init_803CC3BC[] = "PlSkRe.dat";
char ftSk_Init_803CC3C8[] = "PlySeak5KRe_Share_joint";
char ftSk_Init_803CC3E0[] = "PlySeak5KRe_Share_matanim_joint";
char ftSk_Init_803CC400[] = "PlSkBu.dat";
char ftSk_Init_803CC40C[] = "PlySeak5KBu_Share_joint";
char ftSk_Init_803CC424[] = "PlySeak5KBu_Share_matanim_joint";
char ftSk_Init_803CC444[] = "PlSkGr.dat";
char ftSk_Init_803CC450[] = "PlySeak5KGr_Share_joint";
char ftSk_Init_803CC468[] = "PlySeak5KGr_Share_matanim_joint";
char ftSk_Init_803CC488[] = "PlSkWh.dat";
char ftSk_Init_803CC494[] = "PlySeak5KWh_Share_joint";
char ftSk_Init_803CC4AC[] = "PlySeak5KWh_Share_matanim_joint";
char ftSk_Init_AnimDatFilename[] = "PlSkAJ.dat";

Fighter_DemoStrings ftSk_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileSeak",
    "ftDemoIntroMotionFileSeak",
    "ftDemoEndingMotionFileSeak",
    "ftDemoViWaitMotionFileSeak",
};

Fighter_CostumeStrings ftSk_Init_CostumeStrings[] = {
    { ftSk_Init_803CC378, ftSk_Init_803CC384, ftSk_Init_803CC39C },
    { ftSk_Init_803CC3BC, ftSk_Init_803CC3C8, ftSk_Init_803CC3E0 },
    { ftSk_Init_803CC400, ftSk_Init_803CC40C, ftSk_Init_803CC424 },
    { ftSk_Init_803CC444, ftSk_Init_803CC450, ftSk_Init_803CC468 },
    { ftSk_Init_803CC488, ftSk_Init_803CC494, ftSk_Init_803CC4AC },
};

/**
 * @brief Resets Sheik's character variables upon death / respawn.
 * @details Clears stored needle charge count (0 needles), held item pointers,
 * and resets model part visibility.
 * @param gobj Fighter game object
 */
void ftSk_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->u.sk.x0 = 0; // needle count = 0
    fp->u.sk.x4 = 0; // needle item pointer = NULL
    fp->u.sk.x8 = 0; // chain item pointer = NULL
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, -1);
}

/**
 * @brief Initializes Sheik upon fighter load.
 * @details Enables wall jump capability, pushes Sheik-specific DAT attributes,
 * and registers Sheik item kinds (NeedleThrow, NeedleHeld, Vanish explosion,
 * Chain).
 * @param gobj Fighter game object
 */
void ftSk_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    fp->can_walljump = true;

    PUSH_ATTRS(fp, ftSeakAttributes);

    // Pre-register item types needed for Sheik's moves
    it_8026B3F8(item_list[0], It_Kind_Seak_NeedleThrow);
    it_8026B3F8(item_list[1], It_Kind_Seak_NeedleHeld);
    it_8026B3F8(item_list[2], It_Kind_Seak_Vanish);
    it_8026B3F8(item_list[3], It_Kind_Seak_Chain);
}

/**
 * @brief Cleans up active special move items (needles, chain) upon
 * interruption or damage.
 * @param gobj Fighter game object
 */
void ftSk_Init_80110198(HSD_GObj* gobj)
{
    ftSk_SpecialN_80111FBC(gobj);             // Drop/destroy held needles
    ftSk_SpecialS_CheckAndDestroyChain(gobj); // Despawn chain whip
}

/**
 * @brief Displays the full needle charge visual effect if Sheik has 6 needles.
 * @param gobj Fighter game object
 */
void ftSk_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    // 6 needles is the maximum charge capacity
    if (fp->u.sk.x0 == 6) {
        ftCo_800BFFD0(fp, 86, 0);
    }
}

/**
 * @brief Handles item pickup for Sheik.
 * @param gobj Fighter game object
 * @param flag Item pickup flag
 */
void ftSk_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

/**
 * @brief Handles item invisibility for Sheik.
 * @param gobj Fighter game object
 */
void ftSk_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

/**
 * @brief Handles item visibility for Sheik.
 * @param gobj Fighter game object
 */
void ftSk_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

/**
 * @brief Handles item drop for Sheik.
 * @param gobj Fighter game object
 * @param flag Item drop flag
 */
void ftSk_Init_OnItemDrop(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemDrop(gobj, flag, 1, 1);
}

/**
 * @brief Copies character-specific special attributes from DAT file.
 * @param gobj Fighter game object
 */
void ftSk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftSeakAttributes);
}

/**
 * @brief Called when Sheik enters knockback / hitstun.
 * @param gobj Fighter game object
 */
void ftSk_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

/**
 * @brief Called when Sheik exits knockback / hitstun.
 * @param gobj Fighter game object
 */
void ftSk_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

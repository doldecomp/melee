/**
 * @file ftpopo.c
 * @brief Main character module and callback setup for Ice Climbers (Popo)
 * @details Implements motion state table configuration, item handling
 * callbacks, death/damage reset handlers, and DAT asset loading for Popo.
 * Module prefix: ftPp
 */

#include "ftpopo.h"

#include "forward.h"
#include "ftpopospecialhi.h"
#include "ftpopospeciallw.h"
#include "ftpopospecialn.h"
#include "ftpopospecials.h"
#include "types.h"
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftNana/ftnana.h>
#include <melee/ft/types.h>
#include <melee/it/it_26B1.h>
#include <melee/it/kinds/itclimbersice.h>
#include <sysdolphin/baselib/gobj.h>

/* 459E68 */ UnkCostumeStruct ftPp_CostumeList[4];

/// Motion state table defining animation, IASA, physics, and collision
/// callbacks
MotionState ftPp_Init_MotionStateTable[ftPp_MS_SelfCount] = {
    {
        // ftPp_MS_SpecialN = 341: Neutral-B (Ice Shot) Grounded
        ftPp_SM_SpecialN,
        ftPp_MF_SpecialN,
        (FtMoveId_SpecialN << 24) | (1 << 23),
        ftPp_SpecialN_Anim,
        ftPp_SpecialN_IASA,
        ftPp_SpecialN_Phys,
        ftPp_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirN = 342: Neutral-B (Ice Shot) Aerial
        ftPp_SM_SpecialAirN,
        ftPp_MF_SpecialAirN,
        (FtMoveId_SpecialN << 24) | (1 << 23),
        ftPp_SpecialAirN_Anim,
        ftPp_SpecialAirN_IASA,
        ftPp_SpecialAirN_Phys,
        ftPp_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS1 = 343: Side-B (Squall Hammer) Solo Grounded
        ftPp_SM_SpecialS1,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS1_Anim,
        ftPp_SpecialS1_IASA,
        ftPp_SpecialS1_Phys,
        ftPp_SpecialS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS2 = 344: Side-B (Squall Hammer) Paired Grounded
        ftPp_SM_SpecialS2,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS2_Anim,
        ftPp_SpecialS2_IASA,
        ftPp_SpecialS2_Phys,
        ftPp_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirS1 = 345: Side-B (Squall Hammer) Solo Aerial
        ftPp_SM_SpecialAirS1,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialAirS1_Anim,
        ftPp_SpecialAirS1_IASA,
        ftPp_SpecialAirS1_Phys,
        ftPp_SpecialAirS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirS2 = 346: Side-B (Squall Hammer) Paired Aerial
        ftPp_SM_SpecialAirS2,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialAirS2_Anim,
        ftPp_SpecialAirS2_IASA,
        ftPp_SpecialAirS2_Phys,
        ftPp_SpecialAirS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiStart_0 = 347: Up-B (Belay) Partnered Grounded
        // Start
        ftPp_SM_SpecialHiStart_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiStart_0_Anim,
        ftPp_SpecialHiStart_0_IASA,
        ftPp_SpecialHiStart_0_Phys,
        ftPp_SpecialHiStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiThrow_0 = 348: Up-B (Belay) Partnered Grounded
        // Throw
        ftPp_SM_SpecialHiThrow_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiThrow_0_Anim,
        ftPp_SpecialHiThrow_0_IASA,
        ftPp_SpecialHiThrow_0_Phys,
        ftPp_SpecialHiThrow_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiThrow2 = 349: Up-B (Belay) Partnered Grounded Popo
        // Rise
        ftPp_SM_SpecialHiThrow2,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiThrow2_Anim,
        ftPp_SpecialHiThrow2_IASA,
        ftPp_SpecialHiThrow2_Phys,
        ftPp_SpecialHiThrow2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiStart_1 = 350: Up-B (Belay) Solo Fail Grounded
        // Start
        ftPp_SM_SpecialHiStart_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiStart_1_Anim,
        ftPp_SpecialHiStart_1_IASA,
        ftPp_SpecialHiStart_1_Phys,
        ftPp_SpecialHiStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiThrow_1 = 351: Up-B (Belay) Solo Fail Grounded
        // Throw
        ftPp_SM_SpecialHiThrow_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiThrow_1_Anim,
        ftPp_SpecialHiThrow_1_IASA,
        ftPp_SpecialHiThrow_1_Phys,
        ftPp_SpecialHiThrow_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiStart_0 = 352: Up-B (Belay) Partnered Aerial
        // Start
        ftPp_SM_SpecialAirHiStart_0,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiStart_0_Anim,
        ftPp_SpecialAirHiStart_0_IASA,
        ftPp_SpecialAirHiStart_0_Phys,
        ftPp_SpecialAirHiStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiThrow_0 = 353: Up-B (Belay) Partnered Aerial
        // Throw
        ftPp_SM_SpecialAirHiThrow_0,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiThrow_0_Anim,
        ftPp_SpecialAirHiThrow_0_IASA,
        ftPp_SpecialAirHiThrow_0_Phys,
        ftPp_SpecialAirHiThrow_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiThrow2 = 354: Up-B (Belay) Partnered Aerial Popo
        // Rise
        ftPp_SM_SpecialAirHiThrow2,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiThrow2_Anim,
        ftPp_SpecialAirHiThrow2_IASA,
        ftPp_SpecialAirHiThrow2_Phys,
        ftPp_SpecialAirHiThrow2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiStart_1 = 355: Up-B (Belay) Solo Fail Aerial
        // Start
        ftPp_SM_SpecialAirHiStart_1,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiStart_1_Anim,
        ftPp_SpecialAirHiStart_1_IASA,
        ftPp_SpecialAirHiStart_1_Phys,
        ftPp_SpecialAirHiStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiThrow_1 = 356: Up-B (Belay) Solo Fail Aerial
        // Throw
        ftPp_SM_SpecialAirHiThrow_1,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiThrow_1_Anim,
        ftPp_SpecialAirHiThrow_1_IASA,
        ftPp_SpecialAirHiThrow_1_Phys,
        ftPp_SpecialAirHiThrow_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialLw = 357: Down-B (Blizzard) Grounded
        ftPp_SM_SpecialLw,
        ftPp_MF_SpecialLw,
        (FtMoveId_SpecialLw << 24) | (1 << 23),
        ftPp_SpecialLw_Anim,
        ftPp_SpecialLw_IASA,
        ftPp_SpecialLw_Phys,
        ftPp_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirLw = 358: Down-B (Blizzard) Aerial
        ftPp_SM_SpecialAirLw,
        ftPp_MF_MS_358,
        (FtMoveId_SpecialLw << 24) | (1 << 23),
        ftPp_SpecialAirLw_Anim,
        ftPp_SpecialAirLw_IASA,
        ftPp_SpecialAirLw_Phys,
        ftPp_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS_0 = 359: Side-B (Squall Hammer) Auxiliary State 0
        ftPp_SM_SpecialS_0,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS_0_Anim,
        ftPp_SpecialS_0_IASA,
        ftPp_SpecialS_0_Phys,
        ftPp_SpecialS_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS_1 = 360: Side-B (Squall Hammer) Auxiliary State 1
        ftPp_SM_SpecialS_1,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS_1_Anim,
        ftPp_SpecialS_1_IASA,
        ftPp_SpecialS_1_Phys,
        ftPp_SpecialS_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_0 = 361: Up-B (Belay) Nana Partnered State 0
        ftPp_SM_SpecialHi_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_0_Anim,
        ftPp_SpecialHi_0_IASA,
        ftPp_SpecialHi_0_Phys,
        ftPp_SpecialHi_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_1 = 362: Up-B (Belay) Nana Partnered State 1
        ftPp_SM_SpecialHi_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_1_Anim,
        ftPp_SpecialHi_1_IASA,
        ftPp_SpecialHi_1_Phys,
        ftPp_SpecialHi_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_2 = 363: Up-B (Belay) Nana Partnered State 2
        ftPp_SM_SpecialHi_2,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_3 = 364: Up-B (Belay) Nana Partnered State 3
        ftPp_SM_SpecialHi_3,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_3_Anim,
        ftPp_SpecialHi_3_IASA,
        ftPp_SpecialHi_3_Phys,
        ftPp_SpecialHi_3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_4 = 365: Up-B (Belay) Nana Partnered State 4
        ftPp_SM_SpecialHi_4,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_4_Anim,
        ftPp_SpecialHi_4_IASA,
        ftPp_SpecialHi_4_Phys,
        ftPp_SpecialHi_4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_5 = 366: Up-B (Belay) Nana Partnered State 5
        ftPp_SM_SpecialHi_5,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
};

char ftPp_Init_DatFilename[] = "PlPp.dat";
char ftPp_Init_DataName[] = "ftDataPopo";
char ftPp_Init_803CD628[] = "PlPpNr.dat";
char ftPp_Init_803CD634[] = "PlyPopo5K_Share_joint";
char ftPp_Init_803CD64C[] = "PlyPopo5K_Share_matanim_joint";
char ftPp_Init_803CD66C[] = "PlPpGr.dat";
char ftPp_Init_803CD678[] = "PlyPopo5KGr_Share_joint";
char ftPp_Init_803CD690[] = "PlyPopo5KGr_Share_matanim_joint";
char ftPp_Init_803CD6B0[] = "PlPpOr.dat";
char ftPp_Init_803CD6BC[] = "PlyPopo5KOr_Share_joint";
char ftPp_Init_803CD6D4[] = "PlyPopo5KOr_Share_matanim_joint";
char ftPp_Init_803CD6F4[] = "PlPpRe.dat";
char ftPp_Init_803CD700[] = "PlyPopo5KRe_Share_joint";
char ftPp_Init_803CD718[] = "PlyPopo5KRe_Share_matanim_joint";
char ftPp_Init_AnimDatFilename[] = "PlPpAJ.dat";

Fighter_DemoStrings ftPp_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFilePopo",
    "ftDemoIntroMotionFilePopo",
    "ftDemoEndingMotionFilePopo",
    "ftDemoViWaitMotionFilePopo",
};

Fighter_CostumeStrings ftPp_Init_CostumeStrings[] = {
    { ftPp_Init_803CD628, ftPp_Init_803CD634, ftPp_Init_803CD64C },
    { ftPp_Init_803CD66C, ftPp_Init_803CD678, ftPp_Init_803CD690 },
    { ftPp_Init_803CD6B0, ftPp_Init_803CD6BC, ftPp_Init_803CD6D4 },
    { ftPp_Init_803CD6F4, ftPp_Init_803CD700, ftPp_Init_803CD718 },
};

/**
 * @brief Handle item pickup animation and flag update
 * @param gobj Fighter game object
 * @param flag Item pickup flag
 */
void ftPp_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

/**
 * @brief Handle item invisibility callback
 * @param gobj Fighter game object
 */
void ftPp_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

/**
 * @brief Handle item visibility callback
 * @param gobj Fighter game object
 */
void ftPp_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

/**
 * @brief Handle item drop callback
 * @param gobj Fighter game object
 * @param flag Drop flag
 */
void ftPp_Init_OnItemDrop(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemDrop(gobj, flag, 1, 1);
}

/**
 * @brief Setup character attributes when initializing partner Nana
 * @param fp Fighter instance pointer
 */
void ftPp_Init_OnLoadForNana(Fighter* fp)
{
    PUSH_ATTRS(fp, ftIceClimberAttributes);
}

/**
 * @brief Character load callback for Popo
 * @details Pushes attributes and registers item archetypes:
 * - item_list[0]: Ice Shot chunk (It_Kind_IceClimber_Ice)
 * - item_list[1]: Blizzard cloud (It_Kind_IceClimber_Blizzard)
 * - item_list[2]: Belay gum string / rope (It_Kind_IceClimber_GumStrings)
 * @param gobj Fighter game object
 */
void ftPp_Init_OnLoad(HSD_GObj* gobj)
{
    u8 _[4];

    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;
    fp->x2222_b5 = 1;

    PUSH_ATTRS(fp, ftIceClimberAttributes);

    {
        ftIceClimberAttributes* da = fp->dat_attrs;
        fp->x40 = da->x0;
        it_8026B3F8(item_list[0], It_Kind_IceClimber_Ice);
        it_8026B3F8(item_list[1], It_Kind_IceClimber_Blizzard);
        it_8026B3F8(item_list[2], It_Kind_IceClimber_GumStrings);
    }
}

/**
 * @brief Reset callbacks and per-character variables when Popo dies
 * @param gobj Fighter game object
 */
void ftPp_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0U, 0);
    ftParts_80074A4C(gobj, 1U, 0);
    fp->u.nn.x2234 = 0;
    fp->u.nn.x222C = 0;
    fp->u.nn.x2230_b0 = false;
    fp->u.nn.x2238 = 0;
    fp->u.nn.x224C = 0;
    fp->u.nn.x2250 = 0.0f;
}

static void ftPp_Init_8011F190(HSD_GObj* gobj);

/**
 * @brief Clean up all special move entities when damaged or KO'd
 * @details Despawns Ice Shot block, Blizzard effects, Belay rope, and Squall
 * partner link.
 * @param gobj Fighter game object
 */
void ftPp_Init_8011F060(HSD_GObj* gobj)
{
    ftPp_Init_8011F190(gobj);
    ftPp_SpecialHi_80122898(gobj);
    ftPp_SpecialS_80121164(gobj);
    ftPp_SpecialS_8011F68C(gobj);
}

/**
 * @brief Copy character special attributes into fighter memory
 * @param gobj Fighter game object
 */
void ftPp_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftIceClimberAttributes);
}

/**
 * @brief Callback when entering knockback
 * @param gobj Fighter game object
 */
void ftPp_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, true);
}

/**
 * @brief Callback when exiting knockback
 * @param gobj Fighter game object
 */
void ftPp_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, true);
}

/**
 * @brief Clear Ice Shot block reference if it matches the specified item
 * @param gobj Fighter game object
 * @param item_gobj Item game object to compare
 */
void ftPp_Init_8011F16C(HSD_GObj* gobj, Item_GObj* item_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (item_gobj != fp->u.nn.x222C) {
        return;
    }

    fp->u.nn.x222C = 0;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

/**
 * @brief Despawn active Ice Shot item and clear associated callbacks
 * @param gobj Fighter game object
 */
static void ftPp_Init_8011F190(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.nn.x222C == 0) {
        return;
    }

    it_802C17DC(fp->u.nn.x222C);
    ftPp_Init_8011F16C(gobj, fp->u.nn.x222C);
}

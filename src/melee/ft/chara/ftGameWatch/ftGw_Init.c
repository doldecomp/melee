#include "forward.h"
#include "ft/forward.h"

#include "ftGw_Init.h"

#include "ftGw_Attack100.h"
#include "ftGw_Attack11.h"
#include "ftGw_AttackAir.h"
#include "ftGw_AttackLw3.h"
#include "ftGw_AttackS4.h"
#include "ftGw_SpecialHi.h"
#include "ftGw_SpecialLw.h"
#include "ftGw_SpecialN.h"
#include "ftGw_SpecialS.h"
#include "types.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftGw_Init_MotionStateTable[] = {
    {
        46,
        ftGw_MF_Attack11,
        (FtMoveId_Attack11 << 24) | (1 << 23),
        ftGw_Attack11_Anim,
        ftGw_Attack11_IASA,
        ftGw_Attack11_Phys,
        ftGw_Attack11_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        49,
        ftGw_MF_Attack100,
        (FtMoveId_Attack100 << 24) | (1 << 23),
        ftGw_Attack100Start_Anim,
        ftGw_Attack100Start_IASA,
        ftGw_Attack100Start_Phys,
        ftGw_Attack100Start_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        50,
        ftGw_MF_Attack100,
        (FtMoveId_Attack100 << 24) | (1 << 23),
        ftGw_Attack100Loop_Anim,
        ftGw_Attack100Loop_IASA,
        ftGw_Attack100Loop_Phys,
        ftGw_Attack100Loop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        51,
        ftGw_MF_Attack100,
        (FtMoveId_Attack100 << 24) | (1 << 23),
        ftGw_Attack100End_Anim,
        ftGw_Attack100End_IASA,
        ftGw_Attack100End_Phys,
        ftGw_Attack100End_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        59,
        ftGw_MF_AttackLw3,
        (FtMoveId_AttackLw3 << 24) | (1 << 23),
        ftGw_AttackLw3_Anim,
        ftGw_AttackLw3_IASA,
        ftGw_AttackLw3_Phys,
        ftGw_AttackLw3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        62,
        ftGw_MF_AttackS4,
        (FtMoveId_AttackS4 << 24) | (1 << 23),
        ftGw_AttackS4_Anim,
        ftGw_AttackS4_IASA,
        ftGw_AttackS4_Phys,
        ftGw_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        68,
        ftGw_MF_AttackAirN,
        (FtMoveId_AttackAirN << 24) | (1 << 23),
        ftGw_AttackAirN_Anim,
        ftGw_AttackAirN_IASA,
        ftGw_AttackAirN_Phys,
        ftGw_AttackAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        70,
        ftGw_MF_AttackAirB,
        (FtMoveId_AttackAirB << 24) | (1 << 23),
        ftGw_AttackAirB_Anim,
        ftGw_AttackAirB_IASA,
        ftGw_AttackAirB_Phys,
        ftGw_AttackAirB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        71,
        ftGw_MF_AttackAirHi,
        (FtMoveId_AttackAirHi << 24) | (1 << 23),
        ftGw_AttackAirHi_Anim,
        ftGw_AttackAirHi_IASA,
        ftGw_AttackAirHi_Phys,
        ftGw_AttackAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        73,
        ftGw_MF_Landing,
        (FtMoveId_AttackAirN << 24) | (1 << 22) | (1 << 23),
        ftGw_LandingAirN_Anim,
        ftGw_LandingAirN_IASA,
        ftGw_LandingAirN_Phys,
        ftGw_LandingAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        75,
        ftGw_MF_LandingAirB,
        (FtMoveId_AttackAirB << 24) | (1 << 22) | (1 << 23),
        ftGw_LandingAirB_Anim,
        ftGw_LandingAirB_IASA,
        ftGw_LandingAirB_Phys,
        ftGw_LandingAirB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        76,
        ftGw_MF_LandingAirHi,
        (FtMoveId_AttackAirHi << 24) | (1 << 22) | (1 << 23),
        ftGw_LandingAirHi_Anim,
        ftGw_LandingAirHi_IASA,
        ftGw_LandingAirHi_Phys,
        ftGw_LandingAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        295,
        ftGw_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftGw_SpecialN_Anim,
        ftGw_SpecialN_IASA,
        ftGw_SpecialN_Phys,
        ftGw_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        296,
        ftGw_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftGw_SpecialAirN_Anim,
        ftGw_SpecialAirN_IASA,
        ftGw_SpecialAirN_Phys,
        ftGw_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        297,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        298,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        299,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        300,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        302,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        303,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        304,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        305,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        306,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        307,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        308,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        310,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        311,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        312,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        313,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        314,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        315,
        ftGw_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftGw_SpecialHi_Anim,
        ftGw_SpecialHi_IASA,
        ftGw_SpecialHi_Phys,
        ftGw_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        316,
        ftGw_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftGw_SpecialAirHi_Anim,
        ftGw_SpecialAirHi_IASA,
        ftGw_SpecialAirHi_Phys,
        ftGw_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        317,
        ftGw_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialLw_Anim,
        ftGw_SpecialLw_IASA,
        ftGw_SpecialLw_Phys,
        ftGw_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        318,
        ftGw_MF_SpecialLwCatch,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialLwCatch_Anim,
        ftGw_SpecialLwCatch_IASA,
        ftGw_SpecialLwCatch_Phys,
        ftGw_SpecialLwCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        319,
        ftGw_MF_SpecialLwCatch,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialLwShoot_Anim,
        ftGw_SpecialLwShoot_IASA,
        ftGw_SpecialLwShoot_Phys,
        ftGw_SpecialLwShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        320,
        ftGw_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialAirLw_Anim,
        ftGw_SpecialAirLw_IASA,
        ftGw_SpecialAirLw_Phys,
        ftGw_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        321,
        ftGw_MF_SpecialAirLwCatch,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialAirLwCatch_Anim,
        ftGw_SpecialAirLwCatch_IASA,
        ftGw_SpecialAirLwCatch_Phys,
        ftGw_SpecialAirLwCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        322,
        ftGw_MF_SpecialAirLwCatch,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialAirLwShoot_Anim,
        ftGw_SpecialAirLwShoot_IASA,
        ftGw_SpecialAirLwShoot_Phys,
        ftGw_SpecialAirLwShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftGw_Init_DatFilename[] = "PlGw.dat";
char ftGw_Init_DataName[] = "ftDataGamewatch";
char ftGw_Init_803D2904[] = "PlGwNr.dat";
char ftGw_Init_803D2910[] = "PlyGamewatch5K_Share_joint";
char ftGw_Init_AnimDatFilename[] = "PlGwAJ.dat";

Fighter_DemoStrings ftGw_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileGamewatch",
    "ftDemoIntroMotionFileGamewatch",
    "ftDemoEndingMotionFileGamewatch",
    "ftDemoViWaitMotionFileGamewatch",
};

Fighter_CostumeStrings ftGw_Init_CostumeStrings[] = {
    { ftGw_Init_803D2904, ftGw_Init_803D2910, NULL },
    { ftGw_Init_803D2904, ftGw_Init_803D2910, NULL },
    { ftGw_Init_803D2904, ftGw_Init_803D2910, NULL },
    { ftGw_Init_803D2904, ftGw_Init_803D2910, NULL },
};

void ftGw_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0U, 0);
    ftParts_80074A4C(gobj, 1U, -1);
    ftParts_80074A4C(gobj, 2U, 0);
    ftParts_80074A4C(gobj, 3U, 0);
    ftParts_80074A4C(gobj, 4U, -1);
    ftParts_80074A4C(gobj, 5U, -1);
    ftParts_80074A4C(gobj, 6U, -1);
    ftParts_80074A4C(gobj, 7U, -1);
    ftParts_80074A4C(gobj, 8U, -1);
    ftParts_80074A4C(gobj, 9U, -1);
    ftParts_80074A4C(gobj, 10, -1);
    fp->fv.gw.x222C_judgeVar1 = 1;
    fp->fv.gw.x2230_judgeVar2 = 0;
    fp->fv.gw.x2234 = 0;
    fp->fv.gw.x223C_panicDamage = 0;
    fp->fv.gw.x2240_chefVar1 = 1;
    fp->fv.gw.x2244_chefVar2 = 3;
    fp->fv.gw.x2248_manholeGObj = NULL;
    fp->fv.gw.x224C_greenhouseGObj = NULL;
    fp->fv.gw.x2250_manholeGObj2 = NULL;
    fp->fv.gw.x2254_fireGObj = NULL;
    fp->fv.gw.x2258_parachuteGObj = NULL;
    fp->fv.gw.x225C_turtleGObj = NULL;
    fp->fv.gw.x2260_sparkyGObj = NULL;
    fp->fv.gw.x2264_judgementGObj = NULL;
    fp->fv.gw.x2268_panicGObj = NULL;
    fp->fv.gw.x226C_rescueGObj = NULL;
}

void ftGw_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** items = fp->ft_data->x48_items;

    fp->x2222_flag.bits.b6 = false;
    fp->x2223_flag.bits.b1 = true;
    fp->x2224_flag.bits.b0 = true;

    PUSH_ATTRS(fp, ftGameWatchAttributes);
    fp->fv.gw.x2238_panicCharge = ftGw_Panic_Empty;

    {
        ftGameWatchAttributes* attr = fp->x2D4_specialAttributes;
        fp->x34_scale.z = attr->x0_GAMEWATCH_WIDTH;
        fp->x614 = attr->x14_GAMEWATCH_OUTLINE;
        ft_800BFB4C(gobj, &attr->x4_GAMEWATCH_COLOR[fp->x619_costume_id]);
        fp->x5C8 = items[10];

        it_8026B3F8(items[0], It_Kind_GameWatch_Greenhouse);
        it_8026B3F8(items[1], It_Kind_GameWatch_Manhole);
        it_8026B3F8(items[2], It_Kind_GameWatch_Fire);
        it_8026B3F8(items[3], It_Kind_GameWatch_Parachute);
        it_8026B3F8(items[4], It_Kind_GameWatch_Turtle);
        it_8026B3F8(items[5], It_Kind_GameWatch_Breath);
        it_8026B3F8(items[6], It_Kind_GameWatch_Judge);
        it_8026B3F8(items[7], It_Kind_GameWatch_Panic);
        it_8026B3F8(items[8], It_Kind_GameWatch_Chef);
        it_8026B3F8(items[9], It_Kind_GameWatch_Rescue);
    }
}

void ftGw_Init_OnDamage(HSD_GObj* gobj)
{
    ftGw_Attack11_ItemGreenhouseRemove(gobj);
    ftGw_AttackLw3_ItemManholeOnDamage(gobj);
    ftGw_AttackS4_ItemTorchOnDamage(gobj);
    ftGw_AttackAirN_ItemParachuteRemove(gobj);
    ftGw_AttackAirN_ItemTurtleRemove(gobj);
    ftGw_AttackAirN_ItemSparkyRemove(gobj);
    ftGw_SpecialS_ItemJudgementRemove(gobj);
    ftGw_SpecialLw_ItemPanicRemove(gobj);
    ftGw_SpecialHi_ItemRescueRemove(gobj);
}

void ftGw_Init_8014A538(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        ftGw_Attack11_ItemGreenhouseRemove(gobj);
        ftGw_AttackLw3_ItemManholeOnDamage(gobj);
        ftGw_AttackS4_ItemTorchOnDamage(gobj);
        ftGw_AttackAirN_ItemParachuteRemove(gobj);
        ftGw_AttackAirN_ItemTurtleRemove(gobj);
        ftGw_AttackAirN_ItemSparkyRemove(gobj);
        ftGw_SpecialS_ItemJudgementRemove(gobj);
        ftGw_SpecialLw_ItemPanicRemove(gobj);
        ftGw_SpecialHi_ItemRescueRemove(gobj);
    }
}

void ftGw_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftGw_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

// 0x8014A6E0
// https://decomp.me/scratch/ibIxi // Make held item visible (restores picked
// up item's hand held animation)
void ftGw_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

// 0x8014A728
// https://decomp.me/scratch/LR8f5 // OnDropItem callback
void ftGw_Init_OnItemDrop(HSD_GObj* gobj, bool dropItemFlag)
{
    Fighter_OnItemDrop(gobj, dropItemFlag, 1, 1);
}

// 0x8014A77C
// https://decomp.me/scratch/SX2FV // Set Oil Panic Color Overlay
void ftGw_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2238_panicCharge >= ftGw_Panic_Full) {
        ft_800BFFD0(fp, 5, 0);
    }
}

// 0x8014A7B4
// https://decomp.me/scratch/RJvAe // Copy Special Attributes from DAT file
// struct to Fighter*
void ftGw_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftGameWatchAttributes);
}

// 0x8014A7F4
// https://decomp.me/scratch/PFWrJ // Apply color to Mr. Game & Watch's items?
void ftGw_Init_8014A7F4(HSD_GObj* gobj, ItemModStruct* item_mod)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);

    item_mod->x0_unk = gawAttrs->x4_GAMEWATCH_COLOR[fp->x619_costume_id];
}

// 0x8014A814
// https://decomp.me/scratch/BRo1r // Apply alt color to Mr. Game & Watch's
// items?
void ftGw_Init_8014A814(HSD_GObj* gobj, ItemModStruct* item_mod)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);

    item_mod->x0_unk = gawAttrs->x14_GAMEWATCH_OUTLINE;
}

// 0x8014A828
// https://decomp.me/scratch/muS2N // Mr. Game & Watch's OnAbsorb callback
void ftGw_Init_OnAbsorb(HSD_GObj* gobj)
{
    ftGw_SpecialLw_AbsorbThink_DecideAction(gobj);
}

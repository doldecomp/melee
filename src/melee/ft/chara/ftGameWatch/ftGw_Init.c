#include "ftCommon/forward.h"

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

#include "ft/ftcamera.h"
#include "ft/ftcolanim.h"
#include "ft/ftmaterial.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "it/it_26B1.h"
#include "it/types.h"

#include <common_structs.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

MotionState ftGw_Init_MotionStateTable[ftGw_MS_SelfCount] = {
    {
        // ftGw_MS_Attack11 = 341
        ftCo_SM_Attack11,
        ftGw_MF_Attack11,
        (FtMoveId_Attack11 << 24) | (1 << 23),
        ftGw_Attack11_Anim,
        ftGw_Attack11_IASA,
        ftGw_Attack11_Phys,
        ftGw_Attack11_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_Attack100Start = 342
        ftCo_SM_Attack100Start,
        ftGw_MF_Attack100,
        (FtMoveId_Attack100 << 24) | (1 << 23),
        ftGw_Attack100Start_Anim,
        ftGw_Attack100Start_IASA,
        ftGw_Attack100Start_Phys,
        ftGw_Attack100Start_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_Attack100Loop = 343
        ftCo_SM_Attack100Loop,
        ftGw_MF_Attack100,
        (FtMoveId_Attack100 << 24) | (1 << 23),
        ftGw_Attack100Loop_Anim,
        ftGw_Attack100Loop_IASA,
        ftGw_Attack100Loop_Phys,
        ftGw_Attack100Loop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_Attack100End = 344
        ftCo_SM_Attack100End,
        ftGw_MF_Attack100,
        (FtMoveId_Attack100 << 24) | (1 << 23),
        ftGw_Attack100End_Anim,
        ftGw_Attack100End_IASA,
        ftGw_Attack100End_Phys,
        ftGw_Attack100End_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_AttackLw3 = 345
        ftCo_SM_AttackLw3,
        ftGw_MF_AttackLw3,
        (FtMoveId_AttackLw3 << 24) | (1 << 23),
        ftGw_AttackLw3_Anim,
        ftGw_AttackLw3_IASA,
        ftGw_AttackLw3_Phys,
        ftGw_AttackLw3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_AttackS4 = 346
        ftCo_SM_AttackS4,
        ftGw_MF_AttackS4,
        (FtMoveId_AttackS4 << 24) | (1 << 23),
        ftGw_AttackS4_Anim,
        ftGw_AttackS4_IASA,
        ftGw_AttackS4_Phys,
        ftGw_AttackS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_AttackAirN = 347
        ftCo_SM_AttackAirN,
        ftGw_MF_AttackAirN,
        (FtMoveId_AttackAirN << 24) | (1 << 23),
        ftGw_AttackAirN_Anim,
        ftGw_AttackAirN_IASA,
        ftGw_AttackAirN_Phys,
        ftGw_AttackAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_AttackAirB = 348
        ftCo_SM_AttackAirB,
        ftGw_MF_AttackAirB,
        (FtMoveId_AttackAirB << 24) | (1 << 23),
        ftGw_AttackAirB_Anim,
        ftGw_AttackAirB_IASA,
        ftGw_AttackAirB_Phys,
        ftGw_AttackAirB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_AttackAirHi = 349
        ftCo_SM_AttackAirHi,
        ftGw_MF_AttackAirHi,
        (FtMoveId_AttackAirHi << 24) | (1 << 23),
        ftGw_AttackAirHi_Anim,
        ftGw_AttackAirHi_IASA,
        ftGw_AttackAirHi_Phys,
        ftGw_AttackAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_LandingAirN = 350
        ftCo_SM_LandingAirN,
        ftGw_MF_Landing,
        (FtMoveId_AttackAirN << 24) | (1 << 22) | (1 << 23),
        ftGw_LandingAirN_Anim,
        ftGw_LandingAirN_IASA,
        ftGw_LandingAirN_Phys,
        ftGw_LandingAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_LandingAirB = 351
        ftCo_SM_LandingAirB,
        ftGw_MF_LandingAirB,
        (FtMoveId_AttackAirB << 24) | (1 << 22) | (1 << 23),
        ftGw_LandingAirB_Anim,
        ftGw_LandingAirB_IASA,
        ftGw_LandingAirB_Phys,
        ftGw_LandingAirB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_LandingAirHi = 352
        ftCo_SM_LandingAirHi,
        ftGw_MF_LandingAirHi,
        (FtMoveId_AttackAirHi << 24) | (1 << 22) | (1 << 23),
        ftGw_LandingAirHi_Anim,
        ftGw_LandingAirHi_IASA,
        ftGw_LandingAirHi_Phys,
        ftGw_LandingAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialN = 353
        ftGw_SM_SpecialN,
        ftGw_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftGw_SpecialN_Anim,
        ftGw_SpecialN_IASA,
        ftGw_SpecialN_Phys,
        ftGw_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirN = 354
        ftGw_SM_SpecialAirN,
        ftGw_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftGw_SpecialAirN_Anim,
        ftGw_SpecialAirN_IASA,
        ftGw_SpecialAirN_Phys,
        ftGw_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialS1 = 355
        ftGw_SM_SpecialS1,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialS2 = 356
        ftGw_SM_SpecialS2,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialS3 = 357
        ftGw_SM_SpecialS3,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialS4 = 358
        ftGw_SM_SpecialS4,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialS5 = 359
        ftGw_SM_SpecialS5,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialS6 = 360
        ftGw_SM_SpecialS6,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialS7 = 361
        ftGw_SM_SpecialS7,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialS8 = 362
        ftGw_SM_SpecialS8,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialS9 = 363
        ftGw_SM_SpecialS9,
        ftGw_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialS_Anim,
        ftGw_SpecialS_IASA,
        ftGw_SpecialS_Phys,
        ftGw_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirS1 = 364
        ftGw_SM_SpecialAirS1,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirS2 = 365
        ftGw_SM_SpecialAirS2,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirS3 = 366
        ftGw_SM_SpecialAirS3,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirS4 = 367
        ftGw_SM_SpecialAirS4,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirS5 = 368
        ftGw_SM_SpecialAirS5,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirS6 = 369
        ftGw_SM_SpecialAirS6,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirS7 = 370
        ftGw_SM_SpecialAirS7,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirS8 = 371
        ftGw_SM_SpecialAirS8,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirS9 = 372
        ftGw_SM_SpecialAirS9,
        ftGw_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftGw_SpecialAirS_Anim,
        ftGw_SpecialAirS_IASA,
        ftGw_SpecialAirS_Phys,
        ftGw_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialHi = 373
        ftGw_SM_SpecialHi,
        ftGw_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftGw_SpecialHi_Anim,
        ftGw_SpecialHi_IASA,
        ftGw_SpecialHi_Phys,
        ftGw_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirHi = 374
        ftGw_SM_SpecialAirHi,
        ftGw_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftGw_SpecialAirHi_Anim,
        ftGw_SpecialAirHi_IASA,
        ftGw_SpecialAirHi_Phys,
        ftGw_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialLw = 375
        ftGw_SM_SpecialLw,
        ftGw_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialLw_Anim,
        ftGw_SpecialLw_IASA,
        ftGw_SpecialLw_Phys,
        ftGw_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialLwCatch = 376
        ftGw_SM_SpecialLwCatch,
        ftGw_MF_SpecialLwCatch,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialLwCatch_Anim,
        ftGw_SpecialLwCatch_IASA,
        ftGw_SpecialLwCatch_Phys,
        ftGw_SpecialLwCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialLwShoot = 377
        ftGw_SM_SpecialLwShoot,
        ftGw_MF_SpecialLwCatch,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialLwShoot_Anim,
        ftGw_SpecialLwShoot_IASA,
        ftGw_SpecialLwShoot_Phys,
        ftGw_SpecialLwShoot_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirLw = 378
        ftGw_SM_SpecialAirLw,
        ftGw_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialAirLw_Anim,
        ftGw_SpecialAirLw_IASA,
        ftGw_SpecialAirLw_Phys,
        ftGw_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirLwCatch = 379
        ftGw_SM_SpecialAirLwCatch,
        ftGw_MF_SpecialAirLwCatch,
        FtMoveId_SpecialLw << 24,
        ftGw_SpecialAirLwCatch_Anim,
        ftGw_SpecialAirLwCatch_IASA,
        ftGw_SpecialAirLwCatch_Phys,
        ftGw_SpecialAirLwCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftGw_MS_SpecialAirLwShoot = 380
        ftGw_SM_SpecialAirLwShoot,
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

    fp->x2222_b6 = false;
    fp->x2223_b1 = true;
    fp->x2224_b0 = true;

    PUSH_ATTRS(fp, ftGameWatchAttributes);
    fp->fv.gw.x2238_panicCharge = ftGw_Panic_Empty;

    {
        ftGameWatchAttributes* da = fp->dat_attrs;
        fp->x34_scale.z = da->x0_GAMEWATCH_WIDTH;
        fp->x614 = da->x14_GAMEWATCH_OUTLINE;
        ftMaterial_800BFB4C(gobj,
                            &da->x4_GAMEWATCH_COLOR[fp->x619_costume_id]);
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

void ftGw_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
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
        ftCo_800BFFD0(fp, 5, 0);
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

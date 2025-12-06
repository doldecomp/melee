#include "ftDonkey/ftDk_Init.h"

#include "ftDk_HeavyFall.h"
#include "ftDk_HeavyJump.h"
#include "ftDk_HeavyLanding.h"
#include "ftDk_HeavyTurn.h"
#include "ftDk_HeavyWait0.h"
#include "ftDk_HeavyWait1.h"
#include "ftDk_HeavyWalk.h"
#include "ftDk_SpecialHi.h"
#include "ftDk_SpecialLw.h"
#include "ftDk_SpecialN.h"
#include "ftDk_SpecialS.h"

#include <platform.h>

#include "forward.h"

#include "ft/ftcamera.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ftCommon/ftCo_CargoFall.h"
#include "ftCommon/ftCo_CargoJump.h"
#include "ftCommon/ftCo_CargoKneebend.h"
#include "ftCommon/ftCo_CargoLanding.h"
#include "ftCommon/ftCo_CargoThrow.h"
#include "ftCommon/ftCo_CargoTurn.h"
#include "ftCommon/ftCo_CargoWait.h"
#include "ftCommon/ftCo_CargoWalk.h"
#include "ftDonkey/types.h"

#include "lb/forward.h"

#include "lb/lbanim.h"
#include "mp/mplib.h"

#include <dolphin/mtx.h>

MotionState ftDk_Init_MotionStateTable[ftDk_MS_SelfCount] = {
    {
        // ftDk_MS_HeavyWait = 341
        ftDk_SM_HeavyWait,
        ftDk_MF_MS_341,
        (FtMoveId_ThrowF << 24) | (1 << 22),
        NULL,
        ftDk_HeavyWait0_IASA,
        ftDk_HeavyWait0_Phys,
        ftDk_HeavyWait0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_HeavyWalkSlow = 342
        ftDk_SM_HeavyWalkSlow,
        ftDk_MF_MS_342,
        FtMoveId_ThrowF << 24,
        ftDk_HeavyWalk_Anim,
        ftDk_HeavyWalk_IASA,
        ftDk_HeavyWalk_Phys,
        ftDk_HeavyWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_HeavyWalkMiddle = 343
        ftDk_SM_HeavyWalkMiddle,
        ftDk_MF_MS_342,
        FtMoveId_ThrowF << 24,
        ftDk_HeavyWalk_Anim,
        ftDk_HeavyWalk_IASA,
        ftDk_HeavyWalk_Phys,
        ftDk_HeavyWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_HeavyWalkFast = 344
        ftDk_SM_HeavyWalkFast,
        ftDk_MF_MS_342,
        FtMoveId_ThrowF << 24,
        ftDk_HeavyWalk_Anim,
        ftDk_HeavyWalk_IASA,
        ftDk_HeavyWalk_Phys,
        ftDk_HeavyWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_HeavyTurn = 345
        ftDk_SM_HeavyTurn,
        ftDk_MF_MS_345,
        FtMoveId_ThrowF << 24,
        ftDk_HeavyTurn_Anim,
        ftDk_HeavyTurn_IASA,
        ftDk_HeavyTurn_Phys,
        ftDk_HeavyTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_HeavyKneebend = 346
        ftDk_SM_HeavyKneebend,
        ftDk_MF_MS_341,
        FtMoveId_ThrowF << 24,
        ftDk_HeavyWait1_Anim,
        ftDk_HeavyWait1_IASA,
        ftDk_HeavyWait1_Phys,
        ftDk_HeavyWait1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_HeavyFall = 347
        ftDk_SM_HeavyFall,
        ftDk_MF_MS_341,
        FtMoveId_ThrowF << 24,
        NULL,
        ftDk_HeavyFall_IASA,
        ftDk_HeavyFall_Phys,
        ftDk_HeavyFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_HeavyJump = 348
        ftDk_SM_HeavyJump,
        ftDk_MF_MS_348,
        FtMoveId_ThrowF << 24,
        NULL,
        ftDk_HeavyJump_IASA,
        ftDk_HeavyJump_Phys,
        ftDk_HeavyJump_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_HeavyLanding = 349
        ftDk_SM_HeavyLanding,
        ftDk_MF_MS_341,
        (FtMoveId_ThrowF << 24) | (1 << 22),
        ftDk_HeavyLanding_Anim,
        NULL,
        ftDk_HeavyLanding_Phys,
        ftDk_HeavyLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_HeavyWait2 = 350
        ftDk_SM_HeavyWait2,
        ftDk_MF_MS_350,
        FtMoveId_ThrowF << 24,
        ftDk_HeavyWait2_Anim,
        NULL,
        ftDk_HeavyWait2_Phys,
        ftDk_HeavyWait2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFWait0 = 351
        ftDk_SM_ThrowFWait0,
        ftDk_MF_CargoWait,
        (FtMoveId_ThrowF << 24) | (1 << 22),
        ftCo_CargoWait_Anim,
        ftCo_CargoWait_IASA,
        ftCo_CargoWait_Phys,
        ftCo_CargoWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFWalkSlow = 352
        ftDk_SM_ThrowFWalkSlow,
        ftDk_MF_CargoWalk,
        FtMoveId_ThrowF << 24,
        ftCo_CargoWalk_Anim,
        ftCo_CargoWalk_IASA,
        ftCo_CargoWalk_Phys,
        ftCo_CargoWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFWalkMiddle = 353
        ftDk_SM_ThrowFWalkMiddle,
        ftDk_MF_CargoWalk,
        FtMoveId_ThrowF << 24,
        ftCo_CargoWalk_Anim,
        ftCo_CargoWalk_IASA,
        ftCo_CargoWalk_Phys,
        ftCo_CargoWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFWalkFast = 354
        ftDk_SM_ThrowFWalkFast,
        ftDk_MF_CargoWalk,
        FtMoveId_ThrowF << 24,
        ftCo_CargoWalk_Anim,
        ftCo_CargoWalk_IASA,
        ftCo_CargoWalk_Phys,
        ftCo_CargoWalk_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFTurn = 355
        ftDk_SM_ThrowFTurn,
        ftDk_MF_CargoTurn,
        FtMoveId_ThrowF << 24,
        ftCo_CargoTurn_Anim,
        ftCo_CargoTurn_IASA,
        ftCo_CargoTurn_Phys,
        ftCo_CargoTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFKneebend = 356
        ftDk_SM_ThrowFKneebend,
        ftDk_MF_CargoWait,
        FtMoveId_ThrowF << 24,
        ftCo_CargoKneebend_Anim,
        ftCo_CargoKneebend_IASA,
        ftCo_CargoKneebend_Phys,
        ftCo_CargoKneebend_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFFall = 357
        ftDk_SM_ThrowFFall,
        ftDk_MF_CargoWait,
        FtMoveId_ThrowF << 24,
        ftCo_CargoFall_Anim,
        ftCo_CargoFall_IASA,
        ftCo_CargoFall_Phys,
        ftCo_CargoFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFJump = 358
        ftDk_SM_ThrowFJump,
        ftDk_MF_CargoJump,
        FtMoveId_ThrowF << 24,
        ftCo_CargoJump_Anim,
        ftCo_CargoJump_IASA,
        ftCo_CargoJump_Phys,
        ftCo_CargoJump_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFLanding = 359
        ftDk_SM_ThrowFLanding,
        ftDk_MF_CargoWait,
        (FtMoveId_ThrowF << 24) | (1 << 22),
        ftCo_CargoLanding_Anim,
        NULL,
        ftCo_CargoLanding_Phys,
        ftCo_CargoLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFWait2 = 360
        ftDk_SM_ThrowFWait2,
        ftDk_MF_MS_360,
        FtMoveId_ThrowF << 24,
        ftCo_CargoWait2_Anim,
        NULL,
        ftCo_CargoWait2_Phys,
        ftCo_CargoWait2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFF = 361
        ftDk_SM_ThrowFF,
        ftDk_MF_CargoThrowF,
        FtMoveId_CargoThrowF << 24,
        ftCo_CargoThrowF_Anim,
        ftCo_CargoThrowF_IASA,
        ftCo_CargoThrowF_Phys,
        ftCo_CargoThrowF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFB = 362
        ftDk_SM_ThrowFB,
        ftDk_MF_CargoThrowB,
        FtMoveId_CargoThrowB << 24,
        ftCo_CargoThrowB_Anim,
        ftCo_CargoThrowB_IASA,
        ftCo_CargoThrowB_Phys,
        ftCo_CargoThrowB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFHi = 363
        ftDk_SM_ThrowFHi,
        ftDk_MF_CargoThrowHi,
        FtMoveId_CargoThrowHi << 24,
        ftCo_CargoThrowHi_Anim,
        ftCo_CargoThrowHi_IASA,
        ftCo_CargoThrowHi_Phys,
        ftCo_CargoThrowHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowFLw = 364
        ftDk_SM_ThrowFLw,
        ftDk_MF_CargoThrowLw,
        FtMoveId_CargoThrowLw << 24,
        ftCo_CargoThrowLw_Anim,
        ftCo_CargoThrowLw_IASA,
        ftCo_CargoThrowLw_Phys,
        ftCo_CargoThrowLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowAirFF = 365
        ftDk_SM_ThrowFF,
        ftDk_MF_CargoThrowF,
        FtMoveId_CargoThrowF << 24,
        ftCo_CargoThrowAir_Anim,
        ftCo_CargoThrowAir_IASA,
        ftCo_CargoThrowAir_Phys,
        ftCo_CargoThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowAirFB = 366
        ftDk_SM_ThrowFB,
        ftDk_MF_CargoThrowB,
        FtMoveId_CargoThrowB << 24,
        ftCo_CargoThrowAir_Anim,
        ftCo_CargoThrowAir_IASA,
        ftCo_CargoThrowAir_Phys,
        ftCo_CargoThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowAirFHi = 367
        ftDk_SM_ThrowFHi,
        ftDk_MF_CargoThrowHi,
        FtMoveId_CargoThrowHi << 24,
        ftCo_CargoThrowAir_Anim,
        ftCo_CargoThrowAir_IASA,
        ftCo_CargoThrowAir_Phys,
        ftCo_CargoThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_ThrowAirFLw = 368
        ftDk_SM_ThrowFLw,
        ftDk_MF_CargoThrowLw,
        FtMoveId_CargoThrowLw << 24,
        ftCo_CargoThrowAir_Anim,
        ftCo_CargoThrowAir_IASA,
        ftCo_CargoThrowAir_Phys,
        ftCo_CargoThrowAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialNStart = 369
        ftDk_SM_SpecialNStart,
        ftDk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialNStart_Anim,
        ftDk_SpecialNStart_IASA,
        ftDk_SpecialNStart_Phys,
        ftDk_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialNLoop = 370
        ftDk_SM_SpecialNLoop,
        ftDk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialNLoop_Anim,
        ftDk_SpecialNLoop_IASA,
        ftDk_SpecialNLoop_Phys,
        ftDk_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialNCancel = 371
        ftDk_SM_SpecialNCancel,
        ftDk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialNCancel_Anim,
        ftDk_SpecialNCancel_IASA,
        ftDk_SpecialNCancel_Phys,
        ftDk_SpecialNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialN = 372
        ftDk_SM_SpecialN,
        ftDk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialN_Anim,
        ftDk_SpecialN_IASA,
        ftDk_SpecialN_Phys,
        ftDk_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialNFull = 373
        ftDk_SM_SpecialNFull,
        ftDk_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialNFull_Anim,
        ftDk_SpecialNFull_IASA,
        ftDk_SpecialNFull_Phys,
        ftDk_SpecialNFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialAirNStart = 374
        ftDk_SM_SpecialAirNStart,
        ftDk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialAirNStart_Anim,
        ftDk_SpecialAirNStart_IASA,
        ftDk_SpecialAirNStart_Phys,
        ftDk_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialAirNLoop = 375
        ftDk_SM_SpecialAirNLoop,
        ftDk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialAirNLoop_Anim,
        ftDk_SpecialAirNLoop_IASA,
        ftDk_SpecialAirNLoop_Phys,
        ftDk_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialAirNCancel = 376
        ftDk_SM_SpecialAirNCancel,
        ftDk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialAirNCancel_Anim,
        ftDk_SpecialAirNCancel_IASA,
        ftDk_SpecialAirNCancel_Phys,
        ftDk_SpecialAirNCancel_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialAirN = 377
        ftDk_SM_SpecialAirN,
        ftDk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialAirN_Anim,
        ftDk_SpecialAirN_IASA,
        ftDk_SpecialAirN_Phys,
        ftDk_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialAirNFull = 378
        ftDk_SM_SpecialAirNFull,
        ftDk_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftDk_SpecialAirNFull_Anim,
        ftDk_SpecialAirNFull_IASA,
        ftDk_SpecialAirNFull_Phys,
        ftDk_SpecialAirNFull_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialS = 379
        ftDk_SM_SpecialS,
        ftDk_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftDk_SpecialS_Anim,
        ftDk_SpecialS_IASA,
        ftDk_SpecialS_Phys,
        ftDk_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialAirS = 380
        ftDk_SM_SpecialAirS,
        ftDk_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftDk_SpecialAirS_Anim,
        ftDk_SpecialAirS_IASA,
        ftDk_SpecialAirS_Phys,
        ftDk_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialHi = 381
        ftDk_SM_SpecialHi,
        ftDk_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftDk_SpecialHi_Anim,
        ftDk_SpecialHi_IASA,
        ftDk_SpecialHi_Phys,
        ftDk_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialAirHi = 382
        ftDk_SM_SpecialAirHi,
        ftDk_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftDk_SpecialAirHi_Anim,
        ftDk_SpecialAirHi_IASA,
        ftDk_SpecialAirHi_Phys,
        ftDk_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialLwStart = 383
        ftDk_SM_SpecialLwStart,
        ftDk_MF_SpecialLwStart,
        FtMoveId_SpecialLw << 24,
        ftDk_SpecialLwStart_Anim,
        ftDk_SpecialLwStart_IASA,
        ftDk_SpecialLwStart_Phys,
        ftDk_SpecialLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialLwLoop = 384
        ftDk_SM_SpecialLwLoop,
        ftDk_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftDk_SpecialLwLoop_Anim,
        ftDk_SpecialLwLoop_IASA,
        ftDk_SpecialLwLoop_Phys,
        ftDk_SpecialLwLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialLwEnd0 = 385
        ftDk_SM_SpecialLwEnd0,
        ftDk_MF_SpecialLwStart,
        FtMoveId_SpecialLw << 24,
        ftDk_SpecialLwEnd0_Anim,
        ftDk_SpecialLwEnd0_IASA,
        ftDk_SpecialLwEnd0_Phys,
        ftDk_SpecialLwEnd0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftDk_MS_SpecialLwEnd1 = 386
        ftDk_SM_SpecialLwEnd1,
        ftDk_MF_MS_386,
        FtMoveId_SpecialLw << 24,
        ftDk_SpecialLwEnd1_Anim,
        ftDk_SpecialLwEnd1_IASA,
        ftDk_SpecialLwEnd1_Phys,
        ftDk_SpecialLwEnd1_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftDk_Init_DatFilename[] = "PlDk.dat";
char ftDk_Init_DataName[] = "ftDataDonkey";
char ftDk_Init_803CBE14[] = "PlDkNr.dat";
char ftDk_Init_803CBE20[] = "PlyDonkey5K_Share_joint";
char ftDk_Init_803CBE38[] = "PlyDonkey5K_Share_matanim_joint";
char ftDk_Init_803CBE58[] = "PlDkBk.dat";
char ftDk_Init_803CBE64[] = "PlyDonkey5KBk_Share_joint";
char ftDk_Init_803CBE80[] = "PlyDonkey5KBk_Share_matanim_joint";
char ftDk_Init_803CBEA4[] = "PlDkRe.dat";
char ftDk_Init_803CBEB0[] = "PlyDonkey5KRe_Share_joint";
char ftDk_Init_803CBECC[] = "PlyDonkey5KRe_Share_matanim_joint";
char ftDk_Init_803CBEF0[] = "PlDkBu.dat";
char ftDk_Init_803CBEFC[] = "PlyDonkey5KBu_Share_joint";
char ftDk_Init_803CBF18[] = "PlyDonkey5KBu_Share_matanim_joint";
char ftDk_Init_803CBF3C[] = "PlDkGr.dat";
char ftDk_Init_803CBF48[] = "PlyDonkey5KGr_Share_joint";
char ftDk_Init_803CBF64[] = "PlyDonkey5KGr_Share_matanim_joint";
char ftDk_Init_AnimDatFilename[] = "PlDkAJ.dat";

Fighter_DemoStrings ftDk_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileDonkey",
    "ftDemoIntroMotionFileDonkey",
    "ftDemoEndingMotionFileDonkey",
    "ftDemoViWaitMotionFileDonkey",
};

Fighter_CostumeStrings ftDk_Init_CostumeStrings[] = {
    { ftDk_Init_803CBE14, ftDk_Init_803CBE20, ftDk_Init_803CBE38 },
    { ftDk_Init_803CBE58, ftDk_Init_803CBE64, ftDk_Init_803CBE80 },
    { ftDk_Init_803CBEA4, ftDk_Init_803CBEB0, ftDk_Init_803CBECC },
    { ftDk_Init_803CBEF0, ftDk_Init_803CBEFC, ftDk_Init_803CBF18 },
    { ftDk_Init_803CBF3C, ftDk_Init_803CBF48, ftDk_Init_803CBF64 },
};

void ftDk_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.dk.x222C = 0;
    ftParts_80074A4C(gobj, 0, 0);
}

void ftDk_Init_8010D774(HSD_GObj* gobj)
{
    ftDk_SpecialN_DestroyAllEffectsPlus(gobj);
    ftDk_SpecialHi_DestroyAllEffects(gobj);
}

void ftDk_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

void ftDk_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftDk_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftDk_Init_OnItemDrop(HSD_GObj* gobj, bool arg1)
{
    Fighter_OnItemDrop(gobj, arg1, true, true);
}

void ftDk_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* da = fp->dat_attrs;
    if (fp->fv.dk.x222C == da->SpecialN.x2C_MAX_ARM_SWINGS) {
        ftCo_800BFFD0(fp, 57, 0);
    }
}

void ftDk_Init_OnLoad(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->ft_data;
    ftDonkeyAttributes* ftData_attr = ftdata->ext_attr;
    ftData_attr->x8 = lbAnim_8001E8F8(ftData_80085E50(fp, 296));
    ftData_attr->xC = lbAnim_8001E8F8(ftData_80085E50(fp, 297));
    ftData_attr->x10 = lbAnim_8001E8F8(ftData_80085E50(fp, 298));
    PUSH_ATTRS(fp, ftDonkeyAttributes);
    fp->x2222_b0 = true;
    fp->x2CC = fp->dat_attrs;
}

void ftDk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftDonkeyAttributes);
}

void ftDk_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, true);
}

void ftDk_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, true);
}

void ftDk_Init_8010DB3C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    CollData* colldata = &fp->coll_data;
    u8 _[8];
    if (ftCheckThrowB3(fp) && (colldata->env_flags & Collide_FloorMask)) {
        Vec3 vec_list[4];
        int i;
        for (i = 0; i < 4; i++) {
            float temp_f5 = (donkey_attr->SpecialLw.x68 * i) -
                            (donkey_attr->SpecialLw.x68 * 1.5f);
            float temp_f3 = donkey_attr->SpecialLw.x6C * fp->facing_dir;
            float temp_f6 = temp_f5 + temp_f3;

            if (!mpLib_80056C54(colldata->floor.index, &fp->cur_pos, 0,
                                &vec_list[i], 0, 0, temp_f6,
                                donkey_attr->SpecialLw.x70,
                                donkey_attr->SpecialLw.x68 * 1.5f,
                                donkey_attr->SpecialLw.x68))
            {
                vec_list[i] = fp->cur_pos;
            }

            vec_list[i].y += 2.0f;
            ftColl_8007B8A8(&fp->x914[i], &vec_list[i]);
        }
    }
}

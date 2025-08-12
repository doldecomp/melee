#include "ftEmblem/ftFe_Init.h"

#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftMars/forward.h"

#include "ftMars/ftMs_Init.h"
#include "ftMars/ftMs_SpecialHi.h"
#include "ftMars/ftMs_SpecialLw.h"
#include "ftMars/ftMs_SpecialN.h"
#include "ftMars/ftMs_SpecialS.h"
#include "ftMars/types.h"

MotionState ftFe_Init_MotionStateTable[ftMs_MS_SelfCount] = {
    {
        // ftMs_MS_SpecialNStart = 341
        ftMs_SM_SpecialNStart,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNStart_Anim,
        ftMs_SpecialNStart_IASA,
        ftMs_SpecialNStart_Phys,
        ftMs_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialNLoop = 342
        ftMs_SM_SpecialNLoop,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNLoop_Anim,
        ftMs_SpecialNLoop_IASA,
        ftMs_SpecialNLoop_Phys,
        ftMs_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialNEnd0 = 343
        ftMs_SM_SpecialNEnd0,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNEnd_Anim,
        ftMs_SpecialNEnd_IASA,
        ftMs_SpecialNEnd_Phys,
        ftMs_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialNEnd1 = 344
        ftMs_SM_SpecialNEnd1,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNEnd_Anim,
        ftMs_SpecialNEnd_IASA,
        ftMs_SpecialNEnd_Phys,
        ftMs_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirNStart = 345
        ftMs_SM_SpecialAirNStart,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNStart_Anim,
        ftMs_SpecialAirNStart_IASA,
        ftMs_SpecialAirNStart_Phys,
        ftMs_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirNLoop = 346
        ftMs_SM_SpecialAirNLoop,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNLoop_Anim,
        ftMs_SpecialAirNLoop_IASA,
        ftMs_SpecialAirNLoop_Phys,
        ftMs_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirNEnd0 = 347
        ftMs_SM_SpecialAirNEnd0,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNEnd_Anim,
        ftMs_SpecialAirNEnd_IASA,
        ftMs_SpecialAirNEnd_Phys,
        ftMs_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirNEnd1 = 348
        ftMs_SM_SpecialAirNEnd1,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNEnd_Anim,
        ftMs_SpecialAirNEnd_IASA,
        ftMs_SpecialAirNEnd_Phys,
        ftMs_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS1 = 349
        ftMs_SM_SpecialS1,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialAirS1_Anim,
        ftMs_SpecialAirS1_IASA,
        ftMs_SpecialAirS1_Phys,
        ftMs_SpecialAirS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS2Hi = 350
        ftMs_SM_SpecialS2Hi,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS2Lw = 351
        ftMs_SM_SpecialS2Lw,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS3Hi = 352
        ftMs_SM_SpecialS3Hi,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS3S = 353
        ftMs_SM_SpecialS3S,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS3Lw = 354
        ftMs_SM_SpecialS3Lw,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS4Hi = 355
        ftMs_SM_SpecialS4Hi,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS4S = 356
        ftMs_SM_SpecialS4S,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialS4Lw = 357
        ftMs_SM_SpecialS4Lw,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS1 = 358
        ftMs_SM_SpecialAirS1,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialAirS1_Anim,
        ftMs_SpecialAirS1_IASA,
        ftMs_SpecialAirS1_Phys,
        ftMs_SpecialAirS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS2Hi = 359
        ftMs_SM_SpecialAirS2Hi,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS2Lw = 360
        ftMs_SM_SpecialAirS2Lw,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS3Hi = 361
        ftMs_SM_SpecialAirS3Hi,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS3S = 362
        ftMs_SM_SpecialAirS3S,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS3Lw = 363
        ftMs_SM_SpecialAirS3Lw,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS4Hi = 364
        ftMs_SM_SpecialAirS4Hi,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS4S = 365
        ftMs_SM_SpecialAirS4S,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirS4Lw = 366
        ftMs_SM_SpecialAirS4Lw,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialHi = 367
        ftMs_SM_SpecialHi,
        ftMs_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftMs_SpecialHi_Anim,
        ftMs_SpecialHi_IASA,
        ftMs_SpecialHi_Phys,
        ftMs_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirHi = 368
        ftMs_SM_SpecialAirHi,
        ftMs_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftMs_SpecialAirHi_Anim,
        ftMs_SpecialAirHi_IASA,
        ftMs_SpecialAirHi_Phys,
        ftMs_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialLw = 369
        ftMs_SM_SpecialLw,
        ftMs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialLw_Anim,
        ftMs_SpecialLw_IASA,
        ftMs_SpecialLw_Phys,
        ftMs_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialLwHit = 370
        ftMs_SM_SpecialLwHit,
        ftMs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialLwHit_Anim,
        ftMs_SpecialLwHit_IASA,
        ftMs_SpecialLwHit_Phys,
        ftMs_SpecialLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirLw = 371
        ftMs_SM_SpecialAirLw,
        ftMs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialAirLw_Anim,
        ftMs_SpecialAirLw_IASA,
        ftMs_SpecialAirLw_Phys,
        ftMs_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMs_MS_SpecialAirLwHit = 372
        ftMs_SM_SpecialAirLwHit,
        ftMs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialAirLwHit_Anim,
        ftMs_SpecialAirLwHit_IASA,
        ftMs_SpecialAirLwHit_Phys,
        ftMs_SpecialAirLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftFe_Init_DatFilename[] = "PlFe.dat";
char ftFe_Init_DataName[] = "ftDataEmblem";
char ftFe_Init_803D329C[] = "PlFeNr.dat";
char ftFe_Init_803D32A8[] = "PlyEmblem5K_Share_joint";
char ftFe_Init_803D32C0[] = "PlyEmblem5K_Share_matanim_joint";
char ftFe_Init_803D32E0[] = "PlFeRe.dat";
char ftFe_Init_803D32EC[] = "PlyEmblem5KRe_Share_joint";
char ftFe_Init_803D3308[] = "PlyEmblem5KRe_Share_matanim_joint";
char ftFe_Init_803D332C[] = "PlFeBu.dat";
char ftFe_Init_803D3338[] = "PlyEmblem5KBu_Share_joint";
char ftFe_Init_803D3354[] = "PlyEmblem5KBu_Share_matanim_joint";
char ftFe_Init_803D3378[] = "PlFeGr.dat";
char ftFe_Init_803D3384[] = "PlyEmblem5KGr_Share_joint";
char ftFe_Init_803D33A0[] = "PlyEmblem5KGr_Share_matanim_joint";
char ftFe_Init_803D33C4[] = "PlFeYe.dat";
char ftFe_Init_803D33D0[] = "PlyEmblem5KYe_Share_joint";
char ftFe_Init_803D33EC[] = "PlyEmblem5KYe_Share_matanim_joint";
char ftFe_Init_AnimDatFilename[] = "PlFeAJ.dat";

Fighter_DemoStrings ftFe_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileEmblem",
    "ftDemoIntroMotionFileEmblem",
    "ftDemoEndingMotionFileEmblem",
    "ftDemoViWaitMotionFileEmblem",
};

Fighter_CostumeStrings ftFe_Init_CostumeStrings[] = {
    { ftFe_Init_803D329C, ftFe_Init_803D32A8, ftFe_Init_803D32C0 },
    { ftFe_Init_803D32E0, ftFe_Init_803D32EC, ftFe_Init_803D3308 },
    { ftFe_Init_803D332C, ftFe_Init_803D3338, ftFe_Init_803D3354 },
    { ftFe_Init_803D3378, ftFe_Init_803D3384, ftFe_Init_803D33A0 },
    { ftFe_Init_803D33C4, ftFe_Init_803D33D0, ftFe_Init_803D33EC },
};

void ftFe_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    ftParts_80074A4C(gobj, 2, -1);
    fp->fv.ms.x222C = 0;
}

void ftFe_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 0, 1);
}

void ftFe_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftFe_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftFe_Init_OnItemDrop(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemDrop(gobj, flag, 0, 1);
}

void ftFe_Init_OnLoad(HSD_GObj* gobj)
{
    ftMs_Init_OnLoadForRoy(gobj->user_data);
}

void ftFe_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftMs_Init_LoadSpecialAttrs(gobj);
}

void ftFe_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftFe_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

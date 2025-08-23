#include "ftFc_Init.h"

#include <platform.h>

#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftFox/forward.h"

#include "ftFox/ftFx_AppealS.h"
#include "ftFox/ftFx_Init.h"
#include "ftFox/ftFx_SpecialHi.h"
#include "ftFox/ftFx_SpecialLw.h"
#include "ftFox/ftFx_SpecialN.h"
#include "ftFox/ftFx_SpecialS.h"
#include "ftFox/types.h"
#include "it/it_26B1.h"

MotionState ftFc_Init_MotionStateTable[ftFx_MS_SelfCount] = {
    {
        // ftFx_MS_SpecialNStart = 341
        ftFx_SM_SpecialNStart,
        ftFx_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftFx_SpecialNStart_Anim,
        ftFx_SpecialNStart_IASA,
        ftFx_SpecialNStart_Phys,
        ftFx_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialNLoop = 342
        ftFx_SM_SpecialNLoop,
        ftFx_MF_SpecialNLoop,
        FtMoveId_SpecialN << 24,
        ftFx_SpecialNLoop_Anim,
        ftFx_SpecialNLoop_IASA,
        ftFx_SpecialNLoop_Phys,
        ftFx_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialNEnd = 343
        ftFx_SM_SpecialNEnd,
        ftFx_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftFx_SpecialNEnd_Anim,
        ftFx_SpecialNEnd_IASA,
        ftFx_SpecialNEnd_Phys,
        ftFx_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirNStart = 344
        ftFx_SM_SpecialAirNStart,
        ftFx_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftFx_SpecialAirNStart_Anim,
        ftFx_SpecialAirNStart_IASA,
        ftFx_SpecialAirNStart_Phys,
        ftFx_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirNLoop = 345
        ftFx_SM_SpecialAirNLoop,
        ftFx_MF_SpecialAirNLoop,
        FtMoveId_SpecialN << 24,
        ftFx_SpecialAirNLoop_Anim,
        ftFx_SpecialAirNLoop_IASA,
        ftFx_SpecialAirNLoop_Phys,
        ftFx_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirNEnd = 346
        ftFx_SM_SpecialAirNEnd,
        ftFx_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftFx_SpecialAirNEnd_Anim,
        ftFx_SpecialAirNEnd_IASA,
        ftFx_SpecialAirNEnd_Phys,
        ftFx_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialSStart = 347
        ftFx_SM_SpecialSStart,
        ftFx_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftFx_SpecialSStart_Anim,
        ftFx_SpecialSStart_IASA,
        ftFx_SpecialSStart_Phys,
        ftFx_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialS = 348
        ftFx_SM_SpecialS,
        ftFx_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftFx_SpecialS_Anim,
        ftFx_SpecialS_IASA,
        ftFx_SpecialS_Phys,
        ftFx_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialSEnd = 349
        ftFx_SM_SpecialSEnd,
        ftFx_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftFx_SpecialSEnd_Anim,
        ftFx_SpecialSEnd_IASA,
        ftFx_SpecialSEnd_Phys,
        ftFx_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirSStart = 350
        ftFx_SM_SpecialAirSStart,
        ftFx_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftFx_SpecialAirSStart_Anim,
        ftFx_SpecialAirSStart_IASA,
        ftFx_SpecialAirSStart_Phys,
        ftFx_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirS = 351
        ftFx_SM_SpecialAirS,
        ftFx_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftFx_SpecialAirS_Anim,
        ftFx_SpecialAirS_IASA,
        ftFx_SpecialAirS_Phys,
        ftFx_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirSEnd = 352
        ftFx_SM_SpecialAirSEnd,
        ftFx_MF_SpecialAirS,
        FtMoveId_SpecialS << 24,
        ftFx_SpecialAirSEnd_Anim,
        ftFx_SpecialAirSEnd_IASA,
        ftFx_SpecialAirSEnd_Phys,
        ftFx_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialHiHold = 353
        ftFx_SM_SpecialHiHold,
        ftFx_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftFx_SpecialHiHold_Anim,
        ftFx_SpecialHiHold_IASA,
        ftFx_SpecialHiHold_Phys,
        ftFx_SpecialHiHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialHiHoldAir = 354
        ftFx_SM_SpecialHiHoldAir,
        ftFx_MF_SpecialAirHiHold,
        FtMoveId_SpecialHi << 24,
        ftFx_SpecialHiHoldAir_Anim,
        ftFx_SpecialHiHoldAir_IASA,
        ftFx_SpecialHiHoldAir_Phys,
        ftFx_SpecialHiHoldAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialHi = 355
        ftFx_SM_SpecialHi,
        ftFx_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftFx_SpecialHi_Anim,
        ftFx_SpecialHi_IASA,
        ftFx_SpecialHi_Phys,
        ftFx_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirHi = 356
        ftFx_SM_SpecialHi,
        ftFx_MF_SpecialAirHiHold,
        FtMoveId_SpecialHi << 24,
        ftFx_SpecialAirHi_Anim,
        ftFx_SpecialAirHi_IASA,
        ftFx_SpecialAirHi_Phys,
        ftFx_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialHiLanding = 357
        ftFx_SM_SpecialHiLanding,
        ftFx_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftFx_SpecialHiLanding_Anim,
        ftFx_SpecialHiLanding_IASA,
        ftFx_SpecialHiLanding_Phys,
        ftFx_SpecialHiLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialHiFall = 358
        ftFx_SM_SpecialHiFall,
        ftFx_MF_SpecialAirHiHold,
        FtMoveId_SpecialHi << 24,
        ftFx_SpecialHiFall_Anim,
        ftFx_SpecialHiFall_IASA,
        ftFx_SpecialHiFall_Phys,
        ftFx_SpecialHiFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialHiBound = 359
        ftFx_SM_SpecialHiBound,
        ftFx_MF_SpecialAirHiHold,
        FtMoveId_SpecialHi << 24,
        ftFx_SpecialHiBound_Anim,
        ftFx_SpecialHiBound_IASA,
        ftFx_SpecialHiBound_Phys,
        ftFx_SpecialHiBound_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialLwStart = 360
        ftFx_SM_SpecialLwStart,
        ftFx_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftFx_SpecialLwStart_Anim,
        ftFx_SpecialLwStart_IASA,
        ftFx_SpecialLwStart_Phys,
        ftFx_SpecialLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialLwLoop = 361
        ftFx_SM_SpecialLwLoop,
        ftFx_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftFx_SpecialLwLoop_Anim,
        ftFx_SpecialLwLoop_IASA,
        ftFx_SpecialLwLoop_Phys,
        ftFx_SpecialLwLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialLwHit = 362
        ftFx_SM_SpecialLwHit,
        ftFx_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftFx_SpecialLwHit_Anim,
        ftFx_SpecialLwHit_IASA,
        ftFx_SpecialLwHit_Phys,
        ftFx_SpecialLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialLwEnd = 363
        ftFx_SM_SpecialLwEnd,
        ftFx_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftFx_SpecialLwEnd_Anim,
        ftFx_SpecialLwEnd_IASA,
        ftFx_SpecialLwEnd_Phys,
        ftFx_SpecialLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialLwTurn = 364
        ftFx_SM_SpecialLwLoop,
        ftFx_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftFx_SpecialLwTurn_Anim,
        ftFx_SpecialLwTurn_IASA,
        ftFx_SpecialLwTurn_Phys,
        ftFx_SpecialLwTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirLwStart = 365
        ftFx_SM_SpecialAirLwStart,
        ftFx_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftFx_SpecialAirLwStart_Anim,
        ftFx_SpecialAirLwStart_IASA,
        ftFx_SpecialAirLwStart_Phys,
        ftFx_SpecialAirLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirLwLoop = 366
        ftFx_SM_SpecialAirLwLoop,
        ftFx_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftFx_SpecialAirLwLoop_Anim,
        ftFx_SpecialAirLwLoop_IASA,
        ftFx_SpecialAirLwLoop_Phys,
        ftFx_SpecialAirLwLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirLwHit = 367
        ftFx_SM_SpecialAirLwHit,
        ftFx_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftFx_SpecialAirLwHit_Anim,
        ftFx_SpecialAirLwHit_IASA,
        ftFx_SpecialAirLwHit_Phys,
        ftFx_SpecialAirLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirLwEnd = 368
        ftFx_SM_SpecialAirLwEnd,
        ftFx_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftFx_SpecialAirLwEnd_Anim,
        ftFx_SpecialAirLwEnd_IASA,
        ftFx_SpecialAirLwEnd_Phys,
        ftFx_SpecialAirLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_SpecialAirLwTurn = 369
        ftFx_SM_SpecialAirLwLoop,
        ftFx_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftFx_SpecialAirLwTurn_Anim,
        ftFx_SpecialAirLwTurn_IASA,
        ftFx_SpecialAirLwTurn_Phys,
        ftFx_SpecialAirLwTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_AppealSStartR = 370
        ftFx_SM_AppealSStartR,
        ftFx_MF_Appeal,
        FtMoveId_Default << 24,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_AppealSStartL = 371
        ftFx_SM_AppealSStartL,
        ftFx_MF_Appeal,
        FtMoveId_Default << 24,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_AppealSR = 372
        ftFx_SM_AppealSR,
        ftFx_MF_Appeal,
        FtMoveId_Default << 24,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_AppealSL = 373
        ftFx_SM_AppealSL,
        ftFx_MF_Appeal,
        FtMoveId_Default << 24,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_AppealSEndR = 374
        ftFx_SM_AppealSEndR,
        ftFx_MF_Appeal,
        FtMoveId_Default << 24,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftFx_MS_AppealSEndL = 375
        ftFx_SM_AppealSEndL,
        ftFx_MF_Appeal,
        FtMoveId_Default << 24,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftFc_Init_DatFilename[] = "PlFc.dat";
char ftFc_Init_DataName[] = "ftDataFalco";
char ftFc_Init_803D1CC0[] = "PlFcNr.dat";
char ftFc_Init_803D1CCC[] = "PlyFalco5K_Share_joint";
char ftFc_Init_803D1CE4[] = "PlyFalco5K_Share_matanim_joint";
char ftFc_Init_803D1D04[] = "PlFcRe.dat";
char ftFc_Init_803D1D10[] = "PlyFalco5KRe_Share_joint";
char ftFc_Init_803D1D2C[] = "PlyFalco5KRe_Share_matanim_joint";
char ftFc_Init_803D1D50[] = "PlFcBu.dat";
char ftFc_Init_803D1D5C[] = "PlyFalco5KBu_Share_joint";
char ftFc_Init_803D1D78[] = "PlyFalco5KBu_Share_matanim_joint";
char ftFc_Init_803D1D9C[] = "PlFcGr.dat";
char ftFc_Init_803D1DA8[] = "PlyFalco5KGr_Share_joint";
char ftFc_Init_803D1DC4[] = "PlyFalco5KGr_Share_matanim_joint";
char ftFc_Init_AnimDatFilename[] = "PlFcAJ.dat";

Fighter_DemoStrings ftFc_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileFalco",
    "ftDemoIntroMotionFileFalco",
    "ftDemoEndingMotionFileFalco",
    "ftDemoViWaitMotionFileFalco",
};

Fighter_CostumeStrings ftFc_Init_CostumeStrings[] = {
    { ftFc_Init_803D1CC0, ftFc_Init_803D1CCC, ftFc_Init_803D1CE4 },
    { ftFc_Init_803D1D04, ftFc_Init_803D1D10, ftFc_Init_803D1D2C },
    { ftFc_Init_803D1D50, ftFc_Init_803D1D5C, ftFc_Init_803D1D78 },
    { ftFc_Init_803D1D9C, ftFc_Init_803D1DA8, ftFc_Init_803D1DC4 },
};

void ftFc_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->fv.fx.x222C_blasterGObj = 0;
    ftParts_80074A4C(gobj, 0, 0);
}

void ftFc_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

void ftFc_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftFc_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftFc_Init_OnItemDrop(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemDrop(gobj, flag, 1, 1);
}

void ftFc_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->ft_data;
    s32* sa2;
    void** items = ftdata->x48_items;

    u8 _[8];

    fp->can_walljump = true;
    ftFx_Init_OnLoadForFalco(fp);

    sa2 = fp->dat_attrs;
    it_8026B3F8(items[0], sa2[7]);
    it_8026B3F8(items[1], sa2[8]);
    it_8026B3F8(items[3], 0x39);
}

void ftFc_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftFx_Init_LoadSpecialAttrs(gobj);
}

void ftFc_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void ftFc_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0.0f);
}

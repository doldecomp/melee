#include "ftCa_Init.h"

#include "ftCa_SpecialHi.h"
#include "ftCa_SpecialLw.h"
#include "ftCa_SpecialN.h"
#include "ftCa_SpecialS.h"
#include "types.h"

#include "ft/ft_0CD1.h"
#include "ft/ftcamera.h"
#include "ft/ftlipstickswing.h"
#include "ft/ftparts.h"
#include "ft/ftstarrodswing.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCaptain/forward.h"
#include "ftCommon/forward.h"

MotionState ftCa_Init_MotionStateTable[ftCa_MS_SelfCount] = {
    {
        // ftCa_MS_SwordSwing4 = 341
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
        // ftCa_MS_BatSwing4 = 342
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
        // ftCa_MS_ParasolSwing4 = 343
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
        // ftCa_MS_HarisenSwing4 = 344
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
        // ftCa_MS_StarRodSwing4 = 345
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
        // ftCa_MS_LipstickSwing4 = 346
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
        // ftCa_MS_SpecialN = 347
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
        // ftCa_MS_SpecialAirN = 348
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
        // ftCa_MS_SpecialSStart = 349
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
        // ftCa_MS_SpecialS = 350
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
        // ftCa_MS_SpecialAirSStart = 351
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
        // ftCa_MS_SpecialAirS = 352
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
        // ftCa_MS_SpecialHi = 353
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
        // ftCa_MS_SpecialAirHi = 354
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
        // ftCa_MS_SpecialHiCatch = 355
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
        // ftCa_MS_SpecialHiThrow = 356
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
        // ftCa_MS_SpecialLw = 357
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
        // ftCa_MS_SpecialLwEnd = 358
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
        // ftCa_MS_SpecialAirLw = 359
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
        // ftCa_MS_SpecialAirLwEnd = 360
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
        // ftCa_MS_SpecialAirLwEndAir = 361
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
        // ftCa_MS_SpecialLwEndAir = 362
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
        // ftCa_MS_SpecialHiThrow1 = 363
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

#ifdef BUGFIX
/// @todo What.
char re_dat[] = "PlCaRe.dat";
#else
char re_dat[] = "PlCaRe.";
#endif

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

void ftCa_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->fv.ca.during_specials = 0;
    fp->fv.ca.during_specials_start = false;
}

void ftCa_Init_800E28C8(HSD_GObj* gobj)
{
    ftCa_SpecialS_RemoveGFX(gobj);
}

void ftCa_Init_OnItemPickup(HSD_GObj* gobj, bool arg1)
{
    Fighter_OnItemPickup(gobj, arg1, true, true);
}

void ftCa_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftCa_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

/// @remarks Used for both OnItemRelease and OnUnknownItemRelated
void ftCa_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftCa_Init_OnLoadForGanon(Fighter* fp)
{
    PUSH_ATTRS(fp, ftCaptain_DatAttrs);
}

void ftCa_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2224_b7 = true;
    PUSH_ATTRS(fp, ftCaptain_DatAttrs);
}

void ftCa_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCaptain_DatAttrs);
}

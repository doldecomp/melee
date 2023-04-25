#include "ftMars/forward.h"

#include "ftEmblem/ftFe_Init.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftMars/ftMs_Init.h"
#include "ftMars/ftMs_SpecialHi.h"
#include "ftMars/ftMs_SpecialLw.h"
#include "ftMars/ftMs_SpecialN.h"
#include "ftMars/ftMs_SpecialS.h"

MotionState ftFe_Init_MotionStateTable[] = {
    {
        ftMs_AnimId_SpecialNChargeStart,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNChargeStart_Anim,
        ftMs_SpecialNChargeStart_IASA,
        ftMs_SpecialNChargeStart_Phys,
        ftMs_SpecialNChargeStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialNChargeLoop,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNChargeLoop_Anim,
        ftMs_SpecialNChargeLoop_IASA,
        ftMs_SpecialNChargeLoop_Phys,
        ftMs_SpecialNChargeLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialNChargeEnd0,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNChargeEnd_Anim,
        ftMs_SpecialNChargeEnd_IASA,
        ftMs_SpecialNChargeEnd_Phys,
        ftMs_SpecialNChargeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialNChargeEnd1,
        ftMs_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialNChargeEnd_Anim,
        ftMs_SpecialNChargeEnd_IASA,
        ftMs_SpecialNChargeEnd_Phys,
        ftMs_SpecialNChargeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialAirNChargeStart,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNChargeStart_Anim,
        ftMs_SpecialAirNChargeStart_IASA,
        ftMs_SpecialAirNChargeStart_Phys,
        ftMs_SpecialAirNChargeStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialAirNChargeLoop,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNChargeLoop_Anim,
        ftMs_SpecialAirNChargeLoop_IASA,
        ftMs_SpecialAirNChargeLoop_Phys,
        ftMs_SpecialAirNChargeLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialAirNChargeEnd0,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNChargeEnd_Anim,
        ftMs_SpecialAirNChargeEnd_IASA,
        ftMs_SpecialAirNChargeEnd_Phys,
        ftMs_SpecialAirNChargeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialAirNChargeEnd1,
        ftMs_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMs_SpecialAirNChargeEnd_Anim,
        ftMs_SpecialAirNChargeEnd_IASA,
        ftMs_SpecialAirNChargeEnd_Phys,
        ftMs_SpecialAirNChargeEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS1_0,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS1_Anim,
        ftMs_SpecialS1_IASA,
        ftMs_SpecialS1_Phys,
        ftMs_SpecialS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS2_0,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS2_2,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS3_0,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS3_2,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS3_4,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS4_0,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS4_2,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS4_4,
        ftMs_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS1_1,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS1_Anim,
        ftMs_SpecialS1_IASA,
        ftMs_SpecialS1_Phys,
        ftMs_SpecialS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS2_1,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS2_3,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS2_Anim,
        ftMs_SpecialS2_IASA,
        ftMs_SpecialS2_Phys,
        ftMs_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS3_1,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS3_3,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS3_5,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS3_Anim,
        ftMs_SpecialS3_IASA,
        ftMs_SpecialS3_Phys,
        ftMs_SpecialS3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS4_1,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS4_3,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialS4_5,
        ftMs_MF_SpecialS1,
        FtMoveId_SpecialS << 24,
        ftMs_SpecialS4_Anim,
        ftMs_SpecialS4_IASA,
        ftMs_SpecialS4_Phys,
        ftMs_SpecialS4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialHi,
        ftMs_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftMs_SpecialHi_Anim,
        ftMs_SpecialHi_IASA,
        ftMs_SpecialHi_Phys,
        ftMs_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialAirHi,
        ftMs_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftMs_SpecialAirHi_Anim,
        ftMs_SpecialAirHi_IASA,
        ftMs_SpecialAirHi_Phys,
        ftMs_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialLw,
        ftMs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialLw_Anim,
        ftMs_SpecialLw_IASA,
        ftMs_SpecialLw_Phys,
        ftMs_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialLwHit,
        ftMs_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialLwHit_Anim,
        ftMs_SpecialLwHit_IASA,
        ftMs_SpecialLwHit_Phys,
        ftMs_SpecialLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialAirLw,
        ftMs_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftMs_SpecialAirLw_Anim,
        ftMs_SpecialAirLw_IASA,
        ftMs_SpecialAirLw_Phys,
        ftMs_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftMs_AnimId_SpecialAirLwHit,
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

void ftFe_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 0, 1);
}

void ftFe_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftFe_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftFe_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 1);
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

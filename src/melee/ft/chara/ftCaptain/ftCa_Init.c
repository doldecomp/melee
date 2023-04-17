#include "ftCa_Init.h"

#include "ftCa_SpecialLw.h"
#include "ftCa_SpecialHi.h"
#include "ftCa_SpecialN.h"
#include "ftCa_SpecialS.h"
#include "types.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"

MotionState ftCa_Init_MotionStateTable[] = {
    { 295, 0x00440842, 0x41000000, ftCo_SwordSwing_Anim, ftCo_SwordSwing_IASA,
      ftCo_SwordSwing_Phys, ftCo_SwordSwing_Coll, ftCamera_UpdateCameraBox },
    { 296, 0x00440846, 0x45000000, ftCo_BatSwing_Anim, ftCo_BatSwing_IASA,
      ftCo_BatSwing_Phys, ftCo_BatSwing_Coll, ftCamera_UpdateCameraBox },
    { 297, 0x0044084A, 0x49000000, ftCo_ParasolSwing_Anim, ftCo_ParasolSwing_IASA,
      ftCo_ParasolSwing_Phys, ftCo_ParasolSwing_Coll, ftCamera_UpdateCameraBox },
    { 298, 0x0044084E, 0x4D000000, ftCo_HarisenSwing_Anim, ftCo_HarisenSwing_IASA,
      ftCo_HarisenSwing_Phys, ftCo_HarisenSwing_Coll, ftCamera_UpdateCameraBox },
    { 299, 0x00440852, 0x51000000, ftCo_StarRodSwing_Anim, ftCo_StarRodSwing_IASA,
      ftCo_StarRodSwing_Phys, ftCo_StarRodSwing_Coll, ftCamera_UpdateCameraBox },
    { 300, 0x00440856, 0x55000000, ftCo_LipstickSwing_Anim, ftCo_LipstickSwing_IASA,
      ftCo_LipstickSwing_Phys, ftCo_LipstickSwing_Coll, ftCamera_UpdateCameraBox },
    { 301, 0x00340211, 0x12000000, ftCa_SpecialN_Anim,
      ftCa_SpecialN_IASA, ftCa_SpecialN_Phys,
      ftCa_SpecialN_Coll, ftCamera_UpdateCameraBox },
    { 302, 0x00340611, 0x12000000, ftCa_SpecialAirN_Anim,
      ftCa_SpecialAirN_IASA, ftCa_SpecialAirN_Phys,
      ftCa_SpecialAirN_Coll, ftCamera_UpdateCameraBox },
    { 303, 0x00340212, 0x13000000, ftCa_SpecialSStart_Anim,
      ftCa_SpecialSStart_IASA, ftCa_SpecialSStart_Phys,
      ftCa_SpecialSStart_Coll, ftCamera_UpdateCameraBox },
    { 304, 0x00340212, 0x13000000, ftCa_SpecialS_Anim,
      ftCa_SpecialS_IASA, ftCa_SpecialS_Phys,
      ftCa_SpecialS_Coll, ftCamera_UpdateCameraBox },
    { 305, 0x00340612, 0x13000000, ftCa_SpecialAirSStart_Anim,
      ftCa_SpecialAirSStart_IASA, ftCa_SpecialAirSStart_Phys,
      ftCa_SpecialAirSStart_Coll, ftCamera_UpdateCameraBox },
    { 306, 0x00340612, 0x13000000, ftCa_SpecialAirS_Anim,
      ftCa_SpecialAirS_IASA, ftCa_SpecialAirS_Phys,
      ftCa_SpecialAirS_Coll, ftCamera_UpdateCameraBox },
    { 307, 0x00340013, 0x14000000, ftCa_SpecialHi_Anim, ftCa_SpecialHi_IASA,
      ftCa_SpecialHi_Phys, ftCa_SpecialHi_Coll, ftCamera_UpdateCameraBox },
    { 308, 0x00340413, 0x14000000, ftCa_SpecialAirHi_Anim, ftCa_SpecialAirHi_IASA,
      ftCa_SpecialAirHi_Phys, ftCa_SpecialAirHi_Coll, ftCamera_UpdateCameraBox },
    { 309, 0x00340013, 0x14000000, ftCa_SpecialHiCatch_Anim, ftCa_SpecialHiCatch_IASA,
      ftCa_SpecialHiCatch_Phys, ftCa_SpecialHiCatch_Coll, ftCamera_UpdateCameraBox },
    { 310, 0x00340013, 0x14000000, ftCa_SpecialHiThrow_Anim, ftCa_SpecialHiThrow_IASA,
      ftCa_SpecialHiThrow_Phys, ftCa_SpecialHiThrow_Coll, ftCamera_UpdateCameraBox },
    { 311, 0x00340214, 0x15000000, ftCa_SpecialLw_Anim, NULL,
      ftCa_SpecialLw_Phys, ftCa_SpecialLwColl, ftCamera_UpdateCameraBox },
    { 312, 0x00340214, 0x15000000, ftCa_SpecialLwGroundEnd_Anim, NULL,
      ftCa_SpecialLwGroundEnd_Phys, ftCa_SpecialLwGroundEnd_Coll, ftCamera_UpdateCameraBox },
    { 313, 0x00340614, 0x15000000, ftCa_SpecialAirLw_Anim, NULL,
      ftCa_SpecialAirLw_Phys, ftCa_SpecialAirLwColl, ftCamera_UpdateCameraBox },
    { 314, 0x00340614, 0x15000000, ftCa_SpecialAirLwGroundEnd_Anim, NULL,
      ftCa_SpecialAirLwGroundEnd_Phys, ftCa_SpecialAirLwGroundEnd_Coll, ftCamera_UpdateCameraBox },
    { 316, 0x00340614, 0x15000000, ftCa_SpecialAirLwAirEnd_Anim, NULL,
      ftCa_SpecialAirLwAirEnd_Phys, ftCa_SpecialAirLwAirEnd_Coll, ftCamera_UpdateCameraBox },
    { 315, 0x00340214, 0x15000000, ftCa_SpecialLwAirEnd_Anim, NULL,
      ftCa_SpecialLwAirEnd_Phys, ftCa_SpecialLwAirEnd_Coll, ftCamera_UpdateCameraBox },
    { 317, 0x00340614, 0x15000000, ftCa_SpecialLwRebound_Anim, NULL,
      ftCa_SpecialLwRebound_Phys, ftCa_SpecialLwRebound_Coll, ftCamera_UpdateCameraBox },
};

char ftCa_Init_DatFilename[] = "PlCa.dat";
char ftCa_Init_DataName[] = "ftDataCaptain";
char ftCa_Init_803C75B4[] = "PlCaNr.dat";
char ftCa_Init_803C75C0[] = "PlyCaptain5K_Share_joint";
char ftCa_Init_803C75DC[] = "PlCaGy.dat";
char ftCa_Init_803C75E8[] = "PlyCaptain5KGy_Share_joint";
char ftCa_Init_803C7604[] = "PlCaRe.";
char ftCa_Init_803C760C[] = "PlyCaptain5KRe_Share_joint";
char ftCa_Init_803C7628[] = "PlCaWh.dat";
char ftCa_Init_803C7634[] = "PlyCaptain5KWh_Share_joint";
char ftCa_Init_803C7650[] = "PlCaGr.dat";
char ftCa_Init_803C765C[] = "PlyCaptain5KGr_Share_joint";
char ftCa_Init_803C7678[] = "PlCaBu.dat";
char ftCa_Init_803C7684[] = "PlyCaptain5KBu_Share_joint";
char ftCa_Init_AnimDatFilename[] = "PlCaAJ.dat";

Fighter_DemoStrings ftCa_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileCaptain",
    "ftDemoIntroMotionFileCaptain",
    "ftDemoEndingMotionFileCaptain",
    "ftDemoViWaitMotionFileCaptain",
};

Fighter_CostumeStrings ftCa_Init_CostumeStrings[] = {
    { ftCa_Init_803C75B4, ftCa_Init_803C75C0, NULL }, { ftCa_Init_803C75DC, ftCa_Init_803C75E8, NULL },
    { ftCa_Init_803C7604, ftCa_Init_803C760C, NULL }, { ftCa_Init_803C7628, ftCa_Init_803C7634, NULL },
    { ftCa_Init_803C7650, ftCa_Init_803C765C, NULL }, { ftCa_Init_803C7678, ftCa_Init_803C7684, NULL },
};

void ftCa_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->ev.ca.during_specials = 0;
    fp->ev.ca.during_specials_start = false;
}

void ftCa_Init_800E28C8(HSD_GObj* gobj)
{
    ftCa_SpecialS_RemoveGFX(gobj);
}

void ftCa_Init_OnItemPickup(HSD_GObj* gobj, bool arg1)
{
    Fighter_OnItemPickup(gobj, arg1, 1, 1);
}

void ftCa_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftCa_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

/// @remarks Used for both OnItemRelease and OnUnknownItemRelated
void ftCa_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftCa_Init_OnLoadForGanon(Fighter* fp)
{
    PUSH_ATTRS(fp, ftCaptainAttributes);
}

void ftCa_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2224_flag.bits.b7 = true;
    PUSH_ATTRS(fp, ftCaptainAttributes);
}

void ftCa_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCaptainAttributes);
}

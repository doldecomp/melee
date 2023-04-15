#include "ftCaptain_Init.h"

#include "ftCaptain_SpecialHi.h"
#include "ftCaptain_SpecialLw.h"
#include "ftCaptain_SpecialN.h"
#include "ftCaptain_SpecialS.h"
#include "types.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftCa_Init_MotionStateTable[] = {
    { 295, 0x00440842, 0x41000000, ftCa_0877_800CD390, ftCa_0877_800CD3B0,
      ftCa_0877_800CD3D0, ftCa_0877_800CD3F0, ftCamera_UpdateCameraBox },
    { 296, 0x00440846, 0x45000000, ftCa_0877_800CD458, ftCa_0877_800CD478,
      ftCa_0877_800CD498, ftCa_0877_800CD4B8, ftCamera_UpdateCameraBox },
    { 297, 0x0044084A, 0x49000000, ftCa_0877_800CD520, ftCa_0877_800CD540,
      ftCa_0877_800CD560, ftCa_0877_800CD580, ftCamera_UpdateCameraBox },
    { 298, 0x0044084E, 0x4D000000, ftCa_0877_800CD6A0, ftCa_0877_800CD7C4,
      ftCa_0877_800CD7E4, ftCa_0877_800CD804, ftCamera_UpdateCameraBox },
    { 299, 0x00440852, 0x51000000, ftCa_0877_800CD88C, ftCa_0877_800CD8AC,
      ftCa_0877_800CD8CC, ftCa_0877_800CD8EC, ftCamera_UpdateCameraBox },
    { 300, 0x00440856, 0x55000000, ftCa_0877_800CDB14, ftCa_0877_800CDB34,
      ftCa_0877_800CDB54, ftCa_0877_800CDB74, ftCamera_UpdateCameraBox },
    { 301, 0x00340211, 0x12000000, ftCa_SpecialN_Anim, ftCa_SpecialN_IASA,
      ftCa_SpecialN_Phys, ftCa_SpecialN_Coll, ftCamera_UpdateCameraBox },
    { 302, 0x00340611, 0x12000000, ftCa_SpecialAirN_Anim,
      ftCa_SpecialAirN_IASA, ftCa_SpecialAirN_Phys, ftCa_SpecialAirN_Coll,
      ftCamera_UpdateCameraBox },
    { 303, 0x00340212, 0x13000000, ftCa_SpecialSStart_Anim,
      ftCa_SpecialSStart_IASA, ftCa_SpecialSStart_Phys,
      ftCa_SpecialSStart_Coll, ftCamera_UpdateCameraBox },
    { 304, 0x00340212, 0x13000000, ftCa_SpecialS_Anim, ftCa_SpecialS_IASA,
      ftCa_SpecialS_Phys, ftCa_SpecialS_Coll, ftCamera_UpdateCameraBox },
    { 305, 0x00340612, 0x13000000, ftCa_SpecialAirSStart_Anim,
      ftCa_SpecialAirSStart_IASA, ftCa_SpecialAirSStart_Phys,
      ftCa_SpecialAirSStart_Coll, ftCamera_UpdateCameraBox },
    { 306, 0x00340612, 0x13000000, ftCa_SpecialAirS_Anim,
      ftCa_SpecialAirS_IASA, ftCa_SpecialAirS_Phys, ftCa_SpecialAirS_Coll,
      ftCamera_UpdateCameraBox },
    { 307, 0x00340013, 0x14000000, ftCa_SpecialLw_800E4B00,
      ftCa_SpecialLw_800E4B60, ftCa_SpecialLw_800E4BF8,
      ftCa_SpecialLw_800E4E1C, ftCamera_UpdateCameraBox },
    { 308, 0x00340413, 0x14000000, ftCa_SpecialLw_800E4EE8,
      ftCa_SpecialLw_800E4F48, ftCa_SpecialLw_800E4FDC,
      ftCa_SpecialLw_800E50D8, ftCamera_UpdateCameraBox },
    { 309, 0x00340013, 0x14000000, ftCa_SpecialLw_800E51F8,
      ftCa_SpecialLw_800E5234, ftCa_SpecialLw_800E5238,
      ftCa_SpecialLw_800E523C, ftCamera_UpdateCameraBox },
    { 310, 0x00340013, 0x14000000, ftCa_SpecialLw_800E5310,
      ftCa_SpecialLw_800E5384, ftCa_SpecialLw_800E5388,
      ftCa_SpecialLw_800E54B8, ftCamera_UpdateCameraBox },
    { 311, 0x00340214, 0x15000000, ftCa_SpecialHi_800E415C, NULL,
      ftCa_SpecialHi_800E4408, ftCa_SpecialHi_800E46B8,
      ftCamera_UpdateCameraBox },
    { 312, 0x00340214, 0x15000000, ftCa_SpecialHi_800E4268, NULL,
      ftCa_SpecialHi_800E449C, ftCa_SpecialHi_800E47B0,
      ftCamera_UpdateCameraBox },
    { 313, 0x00340614, 0x15000000, ftCa_SpecialHi_800E42E0, NULL,
      ftCa_SpecialHi_800E45E4, ftCa_SpecialHi_800E48BC,
      ftCamera_UpdateCameraBox },
    { 314, 0x00340614, 0x15000000, ftCa_SpecialHi_800E4354, NULL,
      ftCa_SpecialHi_800E4618, ftCa_SpecialHi_800E493C,
      ftCamera_UpdateCameraBox },
    { 316, 0x00340614, 0x15000000, ftCa_SpecialHi_800E4390, NULL,
      ftCa_SpecialHi_800E4678, ftCa_SpecialHi_800E495C,
      ftCamera_UpdateCameraBox },
    { 315, 0x00340214, 0x15000000, ftCa_SpecialHi_800E42A4, NULL,
      ftCa_SpecialHi_800E455C, ftCa_SpecialHi_800E4838,
      ftCamera_UpdateCameraBox },
    { 317, 0x00340614, 0x15000000, ftCa_SpecialHi_800E43CC, NULL,
      ftCa_SpecialHi_800E4698, ftCa_SpecialLw_800E49DC,
      ftCamera_UpdateCameraBox },
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
    { ftCa_Init_803C75B4, ftCa_Init_803C75C0, NULL },
    { ftCa_Init_803C75DC, ftCa_Init_803C75E8, NULL },
    { ftCa_Init_803C7604, ftCa_Init_803C760C, NULL },
    { ftCa_Init_803C7628, ftCa_Init_803C7634, NULL },
    { ftCa_Init_803C7650, ftCa_Init_803C765C, NULL },
    { ftCa_Init_803C7678, ftCa_Init_803C7684, NULL },
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

void ftCa_OnLoadForGanon(Fighter* fp)
{
    PUSH_ATTRS(fp, ftCaptain_DatAttrs);
}

void ftCa_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2224_flag.bits.b7 = true;
    PUSH_ATTRS(fp, ftCaptain_DatAttrs);
}

void ftCa_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCaptain_DatAttrs);
}

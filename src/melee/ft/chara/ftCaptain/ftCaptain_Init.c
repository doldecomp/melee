#include "ftCaptain_Init.h"

#include "ftCaptain_SpecialHi.h"
#include "ftCaptain_SpecialLw.h"
#include "ftCaptain_SpecialN.h"
#include "ftCaptain_SpecialS.h"
#include "types.h"

#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftCaptain_MotionStateTable[] = {
    { 295, 0x00440842, 0x41000000, ftCaptain_800CD390, ftCaptain_800CD3B0,
      ftCaptain_800CD3D0, ftCaptain_800CD3F0, Fighter_UpdateCameraBox },
    { 296, 0x00440846, 0x45000000, ftCaptain_800CD458, ftCaptain_800CD478,
      ftCaptain_800CD498, ftCaptain_800CD4B8, Fighter_UpdateCameraBox },
    { 297, 0x0044084A, 0x49000000, ftCaptain_800CD520, ftCaptain_800CD540,
      ftCaptain_800CD560, ftCaptain_800CD580, Fighter_UpdateCameraBox },
    { 298, 0x0044084E, 0x4D000000, ftCaptain_800CD6A0, ftCaptain_800CD7C4,
      ftCaptain_800CD7E4, ftCaptain_800CD804, Fighter_UpdateCameraBox },
    { 299, 0x00440852, 0x51000000, ftCaptain_800CD88C, ftCaptain_800CD8AC,
      ftCaptain_800CD8CC, ftCaptain_800CD8EC, Fighter_UpdateCameraBox },
    { 300, 0x00440856, 0x55000000, ftCaptain_800CDB14, ftCaptain_800CDB34,
      ftCaptain_800CDB54, ftCaptain_800CDB74, Fighter_UpdateCameraBox },
    { 301, 0x00340211, 0x12000000, ftCaptain_SpecialN_Anim,
      ftCaptain_SpecialN_IASA, ftCaptain_SpecialN_Phys,
      ftCaptain_SpecialN_Coll, Fighter_UpdateCameraBox },
    { 302, 0x00340611, 0x12000000, ftCaptain_SpecialAirN_Anim,
      ftCaptain_SpecialAirN_IASA, ftCaptain_SpecialAirN_Phys,
      ftCaptain_SpecialAirN_Coll, Fighter_UpdateCameraBox },
    { 303, 0x00340212, 0x13000000, ftCaptain_SpecialSStart_Anim,
      ftCaptain_SpecialSStart_IASA, ftCaptain_SpecialSStart_Phys,
      ftCaptain_SpecialSStart_Coll, Fighter_UpdateCameraBox },
    { 304, 0x00340212, 0x13000000, ftCaptain_SpecialS_Anim,
      ftCaptain_SpecialS_IASA, ftCaptain_SpecialS_Phys,
      ftCaptain_SpecialS_Coll, Fighter_UpdateCameraBox },
    { 305, 0x00340612, 0x13000000, ftCaptain_SpecialAirSStart_Anim,
      ftCaptain_SpecialAirSStart_IASA, ftCaptain_SpecialAirSStart_Phys,
      ftCaptain_SpecialAirSStart_Coll, Fighter_UpdateCameraBox },
    { 306, 0x00340612, 0x13000000, ftCaptain_SpecialAirS_Anim,
      ftCaptain_SpecialAirS_IASA, ftCaptain_SpecialAirS_Phys,
      ftCaptain_SpecialAirS_Coll, Fighter_UpdateCameraBox },
    { 307, 0x00340013, 0x14000000, ftCaptain_800E4B00, ftCaptain_800E4B60,
      ftCaptain_800E4BF8, ftCaptain_800E4E1C, Fighter_UpdateCameraBox },
    { 308, 0x00340413, 0x14000000, ftCaptain_800E4EE8, ftCaptain_800E4F48,
      ftCaptain_800E4FDC, ftCaptain_800E50D8, Fighter_UpdateCameraBox },
    { 309, 0x00340013, 0x14000000, ftCaptain_800E51F8, ftCaptain_800E5234,
      ftCaptain_800E5238, ftCaptain_800E523C, Fighter_UpdateCameraBox },
    { 310, 0x00340013, 0x14000000, ftCaptain_800E5310, ftCaptain_800E5384,
      ftCaptain_800E5388, ftCaptain_800E54B8, Fighter_UpdateCameraBox },
    { 311, 0x00340214, 0x15000000, ftCaptain_800E415C, NULL,
      ftCaptain_800E4408, ftCaptain_800E46B8, Fighter_UpdateCameraBox },
    { 312, 0x00340214, 0x15000000, ftCaptain_800E4268, NULL,
      ftCaptain_800E449C, ftCaptain_800E47B0, Fighter_UpdateCameraBox },
    { 313, 0x00340614, 0x15000000, ftCaptain_800E42E0, NULL,
      ftCaptain_800E45E4, ftCaptain_800E48BC, Fighter_UpdateCameraBox },
    { 314, 0x00340614, 0x15000000, ftCaptain_800E4354, NULL,
      ftCaptain_800E4618, ftCaptain_800E493C, Fighter_UpdateCameraBox },
    { 316, 0x00340614, 0x15000000, ftCaptain_800E4390, NULL,
      ftCaptain_800E4678, ftCaptain_800E495C, Fighter_UpdateCameraBox },
    { 315, 0x00340214, 0x15000000, ftCaptain_800E42A4, NULL,
      ftCaptain_800E455C, ftCaptain_800E4838, Fighter_UpdateCameraBox },
    { 317, 0x00340614, 0x15000000, ftCaptain_800E43CC, NULL,
      ftCaptain_800E4698, ftCaptain_800E49DC, Fighter_UpdateCameraBox },
};

char lbl_803C7598[] = "PlCa.dat";
char lbl_803C75A4[] = "ftDataCaptain";
char lbl_803C75B4[] = "PlCaNr.dat";
char lbl_803C75C0[] = "PlyCaptain5K_Share_joint";
char lbl_803C75DC[] = "PlCaGy.dat";
char lbl_803C75E8[] = "PlyCaptain5KGy_Share_joint";
char lbl_803C7604[] = "PlCaRe.";
char lbl_803C760C[] = "PlyCaptain5KRe_Share_joint";
char lbl_803C7628[] = "PlCaWh.dat";
char lbl_803C7634[] = "PlyCaptain5KWh_Share_joint";
char lbl_803C7650[] = "PlCaGr.dat";
char lbl_803C765C[] = "PlyCaptain5KGr_Share_joint";
char lbl_803C7678[] = "PlCaBu.dat";
char lbl_803C7684[] = "PlyCaptain5KBu_Share_joint";
char lbl_803C76A0[] = "PlCaAJ.dat";

Fighter_DemoStrings lbl_803C772C = {
    "ftDemoResultMotionFileCaptain",
    "ftDemoIntroMotionFileCaptain",
    "ftDemoEndingMotionFileCaptain",
    "ftDemoViWaitMotionFileCaptain",
};

Fighter_CostumeStrings lbl_803C773C[] = {
    { lbl_803C75B4, lbl_803C75C0, NULL }, { lbl_803C75DC, lbl_803C75E8, NULL },
    { lbl_803C7604, lbl_803C760C, NULL }, { lbl_803C7628, lbl_803C7634, NULL },
    { lbl_803C7650, lbl_803C765C, NULL }, { lbl_803C7678, lbl_803C7684, NULL },
};

void ftCaptain_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_80074A4C(gobj, 0, 0);
    fp->fv.ca.during_specials = 0;
    fp->fv.ca.during_specials_start = false;
}

void ftCaptain_800E28C8(HSD_GObj* gobj)
{
    ftCaptain_SpecialS_RemoveGFX(gobj);
}

void ftCaptain_OnItemPickup(HSD_GObj* gobj, bool arg1)
{
    Fighter_OnItemPickup(gobj, arg1, 1, 1);
}

void ftCaptain_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftCaptain_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

/// @remarks Used for both OnItemRelease and OnUnknownItemRelated
void ftCaptain_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftCaptain_OnLoadForGanon(Fighter* fp)
{
    PUSH_ATTRS(fp, ftCaptain_DatAttrs);
}

void ftCaptain_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2224_flag.bits.b7 = true;
    PUSH_ATTRS(fp, ftCaptain_DatAttrs);
}

void ftCaptain_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftCaptain_DatAttrs);
}

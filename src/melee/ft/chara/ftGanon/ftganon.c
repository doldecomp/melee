#include "ftganon.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCaptain/ftCaptain_Init.h"
#include "ftCaptain/ftCaptain_SpecialN.h"
#include "ftCaptain/ftCaptain_SpecialS.h"

MotionState ftGn_Init_MotionStateTable[] = {
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
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

char ftGn_Init_DatFilename[] = "PlGn.dat";
char ftGn_Init_DataName[] = "ftDataGanon";
char ftGn_Init_803D2CF0[] = "PlGnNr.dat";
char ftGn_Init_803D2CFC[] = "PlyGanon5K_Share_joint";
char ftGn_Init_803D2D14[] = "PlGnRe.dat";
char ftGn_Init_803D2D20[] = "PlyGanon5KRe_Share_joint";
char ftGn_Init_803D2D3C[] = "PlGnBu.dat";
char ftGn_Init_803D2D48[] = "PlyGanon5KBu_Share_joint";
char ftGn_Init_803D2D64[] = "PlGnGr.dat";
char ftGn_Init_803D2D70[] = "PlyGanon5KGr_Share_joint";
char ftGn_Init_803D2D8C[] = "PlGnLa.dat";
char ftGn_Init_803D2D98[] = "PlyGanon5KLa_Share_joint";
char ftGn_Init_AnimDatFilename[] = "PlGnAJ.dat";

Fighter_DemoStrings ftGn_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileGanon",
    "ftDemoIntroMotionFileGanon",
    "ftDemoEndingMotionFileGanon",
    "ftDemoViWaitMotionFileGanon",
};

Fighter_CostumeStrings ftGn_Init_CostumeStrings[] = {
    { ftGn_Init_803D2CF0, ftGn_Init_803D2CFC, NULL },
    { ftGn_Init_803D2D14, ftGn_Init_803D2D20, NULL },
    { ftGn_Init_803D2D3C, ftGn_Init_803D2D48, NULL },
    { ftGn_Init_803D2D64, ftGn_Init_803D2D70, NULL },
    { ftGn_Init_803D2D8C, ftGn_Init_803D2D98, NULL },
};

void ftGn_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, -1);
    fp->fv.gn.during_specials = false;
    fp->fv.gn.during_specials_start = false;
}

void ftGn_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, true, true);
}

void ftGn_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftGn_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftGn_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftGn_Init_OnLoad(HSD_GObj* gobj)
{
    ftCa_OnLoadForGanon(gobj->user_data);
}

void ftGn_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftCa_Init_LoadSpecialAttrs(gobj);
}

void ftGn_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0);
}

void ftGn_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0);
}

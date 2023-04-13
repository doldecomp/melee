#include "ftganon.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCaptain/ftCaptain.h"
#include "ftCaptain/ftCaptain_SpecialN.h"
#include "ftCaptain/ftCaptain_SpecialS.h"

ActionState ftGanon_MotionStateTable[] = {
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { 301, 0x00340211, 0x12000000, ftCaptain_SpecialN_Anim,
      ftCaptain_SpecialN_IASA, ftCaptain_SpecialN_Phys,
      ftCaptain_SpecialN_Coll, ftCamera_UpdateCameraBox },
    { 302, 0x00340611, 0x12000000, ftCaptain_SpecialAirN_Anim,
      ftCaptain_SpecialAirN_IASA, ftCaptain_SpecialAirN_Phys,
      ftCaptain_SpecialAirN_Coll, ftCamera_UpdateCameraBox },
    { 303, 0x00340212, 0x13000000, ftCaptain_SpecialSStart_Anim,
      ftCaptain_SpecialSStart_IASA, ftCaptain_SpecialSStart_Phys,
      ftCaptain_SpecialSStart_Coll, ftCamera_UpdateCameraBox },
    { 304, 0x00340212, 0x13000000, ftCaptain_SpecialS_Anim,
      ftCaptain_SpecialS_IASA, ftCaptain_SpecialS_Phys,
      ftCaptain_SpecialS_Coll, ftCamera_UpdateCameraBox },
    { 305, 0x00340612, 0x13000000, ftCaptain_SpecialAirSStart_Anim,
      ftCaptain_SpecialAirSStart_IASA, ftCaptain_SpecialAirSStart_Phys,
      ftCaptain_SpecialAirSStart_Coll, ftCamera_UpdateCameraBox },
    { 306, 0x00340612, 0x13000000, ftCaptain_SpecialAirS_Anim,
      ftCaptain_SpecialAirS_IASA, ftCaptain_SpecialAirS_Phys,
      ftCaptain_SpecialAirS_Coll, ftCamera_UpdateCameraBox },
    { 307, 0x00340013, 0x14000000, ftCaptain_800E4B00, ftCaptain_800E4B60,
      ftCaptain_800E4BF8, ftCaptain_800E4E1C, ftCamera_UpdateCameraBox },
    { 308, 0x00340413, 0x14000000, ftCaptain_800E4EE8, ftCaptain_800E4F48,
      ftCaptain_800E4FDC, ftCaptain_800E50D8, ftCamera_UpdateCameraBox },
    { 309, 0x00340013, 0x14000000, ftCaptain_800E51F8, ftCaptain_800E5234,
      ftCaptain_800E5238, ftCaptain_800E523C, ftCamera_UpdateCameraBox },
    { 310, 0x00340013, 0x14000000, ftCaptain_800E5310, ftCaptain_800E5384,
      ftCaptain_800E5388, ftCaptain_800E54B8, ftCamera_UpdateCameraBox },
    { 311, 0x00340214, 0x15000000, ftCaptain_800E415C, NULL,
      ftCaptain_800E4408, ftCaptain_800E46B8, ftCamera_UpdateCameraBox },
    { 312, 0x00340214, 0x15000000, ftCaptain_800E4268, NULL,
      ftCaptain_800E449C, ftCaptain_800E47B0, ftCamera_UpdateCameraBox },
    { 313, 0x00340614, 0x15000000, ftCaptain_800E42E0, NULL,
      ftCaptain_800E45E4, ftCaptain_800E48BC, ftCamera_UpdateCameraBox },
    { 314, 0x00340614, 0x15000000, ftCaptain_800E4354, NULL,
      ftCaptain_800E4618, ftCaptain_800E493C, ftCamera_UpdateCameraBox },
    { 316, 0x00340614, 0x15000000, ftCaptain_800E4390, NULL,
      ftCaptain_800E4678, ftCaptain_800E495C, ftCamera_UpdateCameraBox },
    { 315, 0x00340214, 0x15000000, ftCaptain_800E42A4, NULL,
      ftCaptain_800E455C, ftCaptain_800E4838, ftCamera_UpdateCameraBox },
    { 317, 0x00340614, 0x15000000, ftCaptain_800E43CC, NULL,
      ftCaptain_800E4698, ftCaptain_800E49DC, ftCamera_UpdateCameraBox },
};

char lbl_803D2CD8[] = "PlGn.dat";
char lbl_803D2CE4[] = "ftDataGanon";
char lbl_803D2CF0[] = "PlGnNr.dat";
char lbl_803D2CFC[] = "PlyGanon5K_Share_joint";
char lbl_803D2D14[] = "PlGnRe.dat";
char lbl_803D2D20[] = "PlyGanon5KRe_Share_joint";
char lbl_803D2D3C[] = "PlGnBu.dat";
char lbl_803D2D48[] = "PlyGanon5KBu_Share_joint";
char lbl_803D2D64[] = "PlGnGr.dat";
char lbl_803D2D70[] = "PlyGanon5KGr_Share_joint";
char lbl_803D2D8C[] = "PlGnLa.dat";
char lbl_803D2D98[] = "PlyGanon5KLa_Share_joint";
char lbl_803D2DB4[] = "PlGnAJ.dat";

Fighter_DemoStrings lbl_803D2E30 = {
    "ftDemoResultMotionFileGanon",
    "ftDemoIntroMotionFileGanon",
    "ftDemoEndingMotionFileGanon",
    "ftDemoViWaitMotionFileGanon",
};

Fighter_CostumeStrings lbl_803D2E40[] = {
    { lbl_803D2CF0, lbl_803D2CFC, NULL }, { lbl_803D2D14, lbl_803D2D20, NULL },
    { lbl_803D2D3C, lbl_803D2D48, NULL }, { lbl_803D2D64, lbl_803D2D70, NULL },
    { lbl_803D2D8C, lbl_803D2D98, NULL },
};

void ftGanon_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, -1);
    fp->ev.gn.during_specials = false;
    fp->ev.gn.during_specials_start = false;
}

void ftGanon_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, true, true);
}

void ftGanon_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftGanon_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftGanon_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftGanon_OnLoad(HSD_GObj* gobj)
{
    ftCaptain_OnLoadForGanon(gobj->user_data);
}

void ftGanon_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftCaptain_LoadSpecialAttrs(gobj);
}

void ftGanon_OnKnockbackEnter(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0);
}

void ftGanon_OnKnockbackExit(HSD_GObj* gobj)
{
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0);
}

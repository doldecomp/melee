#include "ft/forward.h"

#include "ftSeak/ftSeak_Init.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftSeak/ftSeak_SpecialLw.h"
#include "ftSeak/ftSeak_SpecialN.h"
#include "ftSeak/ftSeak_SpecialS.h"
#include "ftSeak/types.h"

MotionState ftSk_Init_MotionStateTable[] = {
    { 295, 0x00340111, 0x12000000, ftSk_SpecialN_80112248,
      ftSk_SpecialN_801126C8, ftSk_SpecialN_80112878, ftSk_SpecialN_80112978,
      ftCamera_UpdateCameraBox },
    { 296, 0x003C0111, 0x12000000, ftSk_SpecialN_801122D8,
      ftSk_SpecialN_801126CC, ftSk_SpecialN_80112898, ftSk_SpecialN_801129F8,
      ftCamera_UpdateCameraBox },
    { 297, 0x00340111, 0x12000000, ftSk_SpecialN_80112384,
      ftSk_SpecialN_80112798, ftSk_SpecialN_801128B8, ftSk_SpecialN_80112A78,
      ftCamera_UpdateCameraBox },
    { 298, 0x00340111, 0x12000000, ftSk_SpecialN_801123CC,
      ftSk_SpecialN_8011279C, ftSk_SpecialN_801128D8, ftSk_SpecialN_80112B00,
      ftCamera_UpdateCameraBox },
    { 299, 0x00340511, 0x12000000, ftSk_SpecialN_80112450,
      ftSk_SpecialN_801127A0, ftSk_SpecialN_801128F8, ftSk_SpecialN_80112B98,
      ftCamera_UpdateCameraBox },
    { 300, 0x003C0511, 0x12000000, ftSk_SpecialN_801124E0,
      ftSk_SpecialN_801127A4, ftSk_SpecialN_80112918, ftSk_SpecialN_80112C18,
      ftCamera_UpdateCameraBox },
    { 301, 0x00340511, 0x12000000, ftSk_SpecialN_8011258C,
      ftSk_SpecialN_80112870, ftSk_SpecialN_80112938, ftSk_SpecialN_80112C98,
      ftCamera_UpdateCameraBox },
    { 302, 0x00340511, 0x12000000, ftSk_SpecialN_8011260C,
      ftSk_SpecialN_80112874, ftSk_SpecialN_80112958, ftSk_SpecialN_80112CE4,
      ftCamera_UpdateCameraBox },
    { 303, 0x00340012, 0x13000000, ftSk_SpecialS_Anim, ftSk_SpecialS_80111344,
      ftSk_SpecialS_8011134C, ftSk_SpecialS_801113C8,
      ftCamera_UpdateCameraBox },
    { 305, 0x003C0012, 0x13000000, ftSk_SpecialS_80111588,
      ftSk_SpecialS_80111708, ftSk_SpecialS_80111778, ftSk_SpecialS_801117B8,
      ftCamera_UpdateCameraBox },
    { 304, 0x00340012, 0x13000000, ftSk_SpecialS_80111A48,
      ftSk_SpecialS_80111BF0, ftSk_SpecialS_80111BF8, ftSk_SpecialS_80111C38,
      ftCamera_UpdateCameraBox },
    { 306, 0x00340412, 0x13000000, ftSk_SpecialS_80111308,
      ftSk_SpecialS_80111348, ftSk_SpecialS_8011136C, ftSk_SpecialS_80111404,
      ftCamera_UpdateCameraBox },
    { 308, 0x003C0412, 0x13000000, ftSk_SpecialS_80111648,
      ftSk_SpecialS_80111740, ftSk_SpecialS_80111798, ftSk_SpecialS_801117F4,
      ftCamera_UpdateCameraBox },
    { 307, 0x00340412, 0x13000000, ftSk_SpecialS_80111B1C,
      ftSk_SpecialS_80111BF4, ftSk_SpecialS_80111C18, ftSk_SpecialS_80111C74,
      ftCamera_UpdateCameraBox },
    { 309, 0x00340213, 0x14000000, ftSk_SpecialHi_80113194,
      ftSk_SpecialHi_8011320C, ftSk_SpecialHi_80113214,
      ftSk_SpecialHi_80113278, ftCamera_UpdateCameraBox },
    { 309, 0x00340213, 0x14000000, ftSk_SpecialHi_801133FC,
      ftSk_SpecialHi_80113474, ftSk_SpecialHi_8011347C,
      ftSk_SpecialHi_801134A0, ftCamera_UpdateCameraBox },
    { 310, 0x00340213, 0x14000000, ftSk_SpecialHi_80113C40,
      ftSk_SpecialHi_80113CDC, ftSk_SpecialHi_80113CE4,
      ftSk_SpecialHi_80113D80, ftCamera_UpdateCameraBox },
    { 311, 0x00340613, 0x14000000, ftSk_SpecialHi_801131D0,
      ftSk_SpecialHi_80113210, ftSk_SpecialHi_80113234,
      ftSk_SpecialHi_801132B4, ftCamera_UpdateCameraBox },
    { 311, 0x00340613, 0x14000000, ftSk_SpecialHi_80113438,
      ftSk_SpecialHi_80113478, ftSk_SpecialHi_8011349C,
      ftSk_SpecialHi_80113540, ftCamera_UpdateCameraBox },
    { 312, 0x00340613, 0x14000000, ftSk_SpecialHi_80113C7C,
      ftSk_SpecialHi_80113CE0, ftSk_SpecialHi_80113D04,
      ftSk_SpecialHi_80113DBC, ftCamera_UpdateCameraBox },
    { 313, 0x00340014, 0x15000000, ftSk_SpecialLw_801142E8,
      ftSk_SpecialLw_80114368, ftSk_SpecialLw_80114370,
      ftSk_SpecialLw_801143D4, ftCamera_UpdateCameraBox },
    { 314, 0x00340014, 0x15000000, ftSk_SpecialLw_80114524,
      ftSk_SpecialLw_8011459C, ftSk_SpecialLw_801145A4,
      ftSk_SpecialLw_80114608, ftCamera_UpdateCameraBox },
    { 315, 0x00340414, 0x15000000, ftSk_SpecialLw_80114328,
      ftSk_SpecialLw_8011436C, ftSk_SpecialLw_80114390,
      ftSk_SpecialLw_80114410, ftCamera_UpdateCameraBox },
    { 316, 0x00340414, 0x15000000, ftSk_SpecialLw_80114560,
      ftSk_SpecialLw_801145A0, ftSk_SpecialLw_801145C4,
      ftSk_SpecialLw_80114644, ftCamera_UpdateCameraBox },
};

char ftSk_Init_DatFilename[] = "PlSk.dat";
char ftSk_Init_DataName[] = "ftDataSeak";
char ftSk_Init_803CC378[] = "PlSkNr.dat";
char ftSk_Init_803CC384[] = "PlySeak5K_Share_joint";
char ftSk_Init_803CC39C[] = "PlySeak5K_Share_matanim_joint";
char ftSk_Init_803CC3BC[] = "PlSkRe.dat";
char ftSk_Init_803CC3C8[] = "PlySeak5KRe_Share_joint";
char ftSk_Init_803CC3E0[] = "PlySeak5KRe_Share_matanim_joint";
char ftSk_Init_803CC400[] = "PlSkBu.dat";
char ftSk_Init_803CC40C[] = "PlySeak5KBu_Share_joint";
char ftSk_Init_803CC424[] = "PlySeak5KBu_Share_matanim_joint";
char ftSk_Init_803CC444[] = "PlSkGr.dat";
char ftSk_Init_803CC450[] = "PlySeak5KGr_Share_joint";
char ftSk_Init_803CC468[] = "PlySeak5KGr_Share_matanim_joint";
char ftSk_Init_803CC488[] = "PlSkWh.dat";
char ftSk_Init_803CC494[] = "PlySeak5KWh_Share_joint";
char ftSk_Init_803CC4AC[] = "PlySeak5KWh_Share_matanim_joint";
char ftSk_Init_AnimDatFilename[] = "PlSkAJ.dat";

Fighter_DemoStrings ftSk_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileSeak",
    "ftDemoIntroMotionFileSeak",
    "ftDemoEndingMotionFileSeak",
    "ftDemoViWaitMotionFileSeak",
};

Fighter_CostumeStrings ftSk_Init_CostumeStrings[] = {
    { ftSk_Init_803CC378, ftSk_Init_803CC384, ftSk_Init_803CC39C },
    { ftSk_Init_803CC3BC, ftSk_Init_803CC3C8, ftSk_Init_803CC3E0 },
    { ftSk_Init_803CC400, ftSk_Init_803CC40C, ftSk_Init_803CC424 },
    { ftSk_Init_803CC444, ftSk_Init_803CC450, ftSk_Init_803CC468 },
    { ftSk_Init_803CC488, ftSk_Init_803CC494, ftSk_Init_803CC4AC },
};

void ftSk_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.sk.x222C = 0;
    fp->fv.sk.x2230 = 0;
    fp->fv.sk.x2234 = 0;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, -1);
}

void ftSk_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftSeakAttributes);

    it_8026B3F8(item_list[0], 0x4FU);
    it_8026B3F8(item_list[1], 0x50U);
    it_8026B3F8(item_list[2], 0x55U);
    it_8026B3F8(item_list[3], 0x61U);
}

/* static */ void ftSk_SpecialN_80111FBC(HSD_GObj* gobj);
/* static */ void ftSk_SpecialS_CheckAndDestroyChain(HSD_GObj* gobj);

void ftSk_Init_80110198(HSD_GObj* gobj)
{
    ftSk_SpecialN_80111FBC(gobj);
    ftSk_SpecialS_CheckAndDestroyChain(gobj);
}

void ftSk_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.sk.x222C == 6) {
        ft_800BFFD0(fp, 0x56, 0);
    }
}

void ftSk_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftSk_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftSk_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftSk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftSk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftSeakAttributes);
}

void ftSk_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftSk_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

/// @todo Moved to ftSeak_SpecialN.c
#if false

// 8011412C - 80114160
// https://decomp.me/scratch/b1oIZ
void ftSeak_8011412C(HSD_GObj* gobj) {
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21BC_callback_Accessory4 = 0;
    ftCommon_8007EFC8(gobj, &ftZd_SpecialLw_8013B4D8);
}

#endif

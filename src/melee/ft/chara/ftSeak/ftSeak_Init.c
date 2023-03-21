#include "ftSeak/ftSeak_Init.h"

#include "ftSeak/ftSeak_SpecialLw.h"
#include "ftSeak/ftSeak_SpecialN.h"
#include "ftSeak/ftSeak_SpecialS.h"
#include "ftSeak/types.h"

#include <melee/ft/fighter.h>
#include <melee/ft/forward.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>

ActionState as_table_seak[] = {
    { 295, 0x00340111, 0x12000000, ftSeak_80112248, ftSeak_801126C8,
      ftSeak_80112878, ftSeak_80112978, func_800761C8 },
    { 296, 0x003C0111, 0x12000000, ftSeak_801122D8, ftSeak_801126CC,
      ftSeak_80112898, ftSeak_801129F8, func_800761C8 },
    { 297, 0x00340111, 0x12000000, ftSeak_80112384, ftSeak_80112798,
      ftSeak_801128B8, ftSeak_80112A78, func_800761C8 },
    { 298, 0x00340111, 0x12000000, ftSeak_801123CC, ftSeak_8011279C,
      ftSeak_801128D8, ftSeak_80112B00, func_800761C8 },
    { 299, 0x00340511, 0x12000000, ftSeak_80112450, ftSeak_801127A0,
      ftSeak_801128F8, ftSeak_80112B98, func_800761C8 },
    { 300, 0x003C0511, 0x12000000, ftSeak_801124E0, ftSeak_801127A4,
      ftSeak_80112918, ftSeak_80112C18, func_800761C8 },
    { 301, 0x00340511, 0x12000000, ftSeak_8011258C, ftSeak_80112870,
      ftSeak_80112938, ftSeak_80112C98, func_800761C8 },
    { 302, 0x00340511, 0x12000000, ftSeak_8011260C, ftSeak_80112874,
      ftSeak_80112958, ftSeak_80112CE4, func_800761C8 },
    { 303, 0x00340012, 0x13000000, ftSeak_SpecialS_Anim, ftSeak_80111344,
      ftSeak_8011134C, ftSeak_801113C8, func_800761C8 },
    { 305, 0x003C0012, 0x13000000, ftSeak_80111588, ftSeak_80111708,
      ftSeak_80111778, ftSeak_801117B8, func_800761C8 },
    { 304, 0x00340012, 0x13000000, ftSeak_80111A48, ftSeak_80111BF0,
      ftSeak_80111BF8, ftSeak_80111C38, func_800761C8 },
    { 306, 0x00340412, 0x13000000, ftSeak_80111308, ftSeak_80111348,
      ftSeak_8011136C, ftSeak_80111404, func_800761C8 },
    { 308, 0x003C0412, 0x13000000, ftSeak_80111648, ftSeak_80111740,
      ftSeak_80111798, ftSeak_801117F4, func_800761C8 },
    { 307, 0x00340412, 0x13000000, ftSeak_80111B1C, ftSeak_80111BF4,
      ftSeak_80111C18, ftSeak_80111C74, func_800761C8 },
    { 309, 0x00340213, 0x14000000, ftSeak_80113194, ftSeak_8011320C,
      ftSeak_80113214, ftSeak_80113278, func_800761C8 },
    { 309, 0x00340213, 0x14000000, ftSeak_801133FC, ftSeak_80113474,
      ftSeak_8011347C, ftSeak_801134A0, func_800761C8 },
    { 310, 0x00340213, 0x14000000, ftSeak_80113C40, ftSeak_80113CDC,
      ftSeak_80113CE4, ftSeak_80113D80, func_800761C8 },
    { 311, 0x00340613, 0x14000000, ftSeak_801131D0, ftSeak_80113210,
      ftSeak_80113234, ftSeak_801132B4, func_800761C8 },
    { 311, 0x00340613, 0x14000000, ftSeak_80113438, ftSeak_80113478,
      ftSeak_8011349C, ftSeak_80113540, func_800761C8 },
    { 312, 0x00340613, 0x14000000, ftSeak_80113C7C, ftSeak_80113CE0,
      ftSeak_80113D04, ftSeak_80113DBC, func_800761C8 },
    { 313, 0x00340014, 0x15000000, ftSeak_801142E8, ftSeak_80114368,
      ftSeak_80114370, ftSeak_801143D4, func_800761C8 },
    { 314, 0x00340014, 0x15000000, ftSeak_80114524, ftSeak_8011459C,
      ftSeak_801145A4, ftSeak_80114608, func_800761C8 },
    { 315, 0x00340414, 0x15000000, ftSeak_80114328, ftSeak_8011436C,
      ftSeak_80114390, ftSeak_80114410, func_800761C8 },
    { 316, 0x00340414, 0x15000000, ftSeak_80114560, ftSeak_801145A0,
      ftSeak_801145C4, ftSeak_80114644, func_800761C8 },
};

char lbl_803CC360[] = "PlSk.dat";
char lbl_803CC36C[] = "ftDataSeak";
char lbl_803CC378[] = "PlSkNr.dat";
char lbl_803CC384[] = "PlySeak5K_Share_joint";
char lbl_803CC39C[] = "PlySeak5K_Share_matanim_joint";
char lbl_803CC3BC[] = "PlSkRe.dat";
char lbl_803CC3C8[] = "PlySeak5KRe_Share_joint";
char lbl_803CC3E0[] = "PlySeak5KRe_Share_matanim_joint";
char lbl_803CC400[] = "PlSkBu.dat";
char lbl_803CC40C[] = "PlySeak5KBu_Share_joint";
char lbl_803CC424[] = "PlySeak5KBu_Share_matanim_joint";
char lbl_803CC444[] = "PlSkGr.dat";
char lbl_803CC450[] = "PlySeak5KGr_Share_joint";
char lbl_803CC468[] = "PlySeak5KGr_Share_matanim_joint";
char lbl_803CC488[] = "PlSkWh.dat";
char lbl_803CC494[] = "PlySeak5KWh_Share_joint";
char lbl_803CC4AC[] = "PlySeak5KWh_Share_matanim_joint";
char lbl_803CC4CC[] = "PlSkAJ.dat";

Fighter_DemoStrings lbl_803CC548 = {
    "ftDemoResultMotionFileSeak",
    "ftDemoIntroMotionFileSeak",
    "ftDemoEndingMotionFileSeak",
    "ftDemoViWaitMotionFileSeak",
};

Fighter_CostumeStrings lbl_803CC558[] = {
    { lbl_803CC378, lbl_803CC384, lbl_803CC39C },
    { lbl_803CC3BC, lbl_803CC3C8, lbl_803CC3E0 },
    { lbl_803CC400, lbl_803CC40C, lbl_803CC424 },
    { lbl_803CC444, lbl_803CC450, lbl_803CC468 },
    { lbl_803CC488, lbl_803CC494, lbl_803CC4AC },
};

void ftSeak_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->ev.sk.x222C = 0;
    fp->ev.sk.x2230 = 0;
    fp->ev.sk.x2234 = 0;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 1, -1);
}

void ftSeak_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->x10C_ftData->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftSeakAttributes);

    func_8026B3F8(item_list[0], 0x4FU);
    func_8026B3F8(item_list[1], 0x50U);
    func_8026B3F8(item_list[2], 0x55U);
    func_8026B3F8(item_list[3], 0x61U);
}

/* static */ void ftSeak_80111FBC(HSD_GObj* gobj);
/* static */ void ftSeak_CheckAndDestroyChain(HSD_GObj* gobj);

void ftSeak_80110198(HSD_GObj* gobj)
{
    ftSeak_80111FBC(gobj);
    ftSeak_CheckAndDestroyChain(gobj);
}

void ftSeak_801101CC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ev.sk.x222C == 6) {
        func_800BFFD0(fp, 0x56, 0);
    }
}

void ftSeak_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftSeak_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftSeak_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftSeak_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftSeak_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftSeakAttributes);
}

void ftSeak_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftSeak_OnKnockbackExit(HSD_GObj* gobj)
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
    func_8007EFC8(gobj, &ftZelda_8013B4D8);
}

#endif

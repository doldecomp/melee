#include <melee/ft/chara/ftSeak/ftseak.h>

#include "melee/ft/forward.h"
#include <melee/ft/chara/ftSeak/ftseak.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>

ActionState as_table_seak[] = {
    { 295, 0x00340111, 0x12000000, lbl_80112248, lbl_801126C8, lbl_80112878,
      lbl_80112978, func_800761C8 },
    { 296, 0x003C0111, 0x12000000, lbl_801122D8, lbl_801126CC, lbl_80112898,
      lbl_801129F8, func_800761C8 },
    { 297, 0x00340111, 0x12000000, lbl_80112384, lbl_80112798, lbl_801128B8,
      lbl_80112A78, func_800761C8 },
    { 298, 0x00340111, 0x12000000, lbl_801123CC, lbl_8011279C, lbl_801128D8,
      lbl_80112B00, func_800761C8 },
    { 299, 0x00340511, 0x12000000, lbl_80112450, lbl_801127A0, lbl_801128F8,
      lbl_80112B98, func_800761C8 },
    { 300, 0x003C0511, 0x12000000, lbl_801124E0, lbl_801127A4, lbl_80112918,
      lbl_80112C18, func_800761C8 },
    { 301, 0x00340511, 0x12000000, lbl_8011258C, lbl_80112870, lbl_80112938,
      lbl_80112C98, func_800761C8 },
    { 302, 0x00340511, 0x12000000, lbl_8011260C, lbl_80112874, lbl_80112958,
      lbl_80112CE4, func_800761C8 },
    { 303, 0x00340012, 0x13000000, lbl_801112CC, lbl_80111344, lbl_8011134C,
      lbl_801113C8, func_800761C8 },
    { 305, 0x003C0012, 0x13000000, lbl_80111588, lbl_80111708, lbl_80111778,
      lbl_801117B8, func_800761C8 },
    { 304, 0x00340012, 0x13000000, lbl_80111A48, lbl_80111BF0, lbl_80111BF8,
      lbl_80111C38, func_800761C8 },
    { 306, 0x00340412, 0x13000000, lbl_80111308, lbl_80111348, lbl_8011136C,
      lbl_80111404, func_800761C8 },
    { 308, 0x003C0412, 0x13000000, lbl_80111648, lbl_80111740, lbl_80111798,
      lbl_801117F4, func_800761C8 },
    { 307, 0x00340412, 0x13000000, lbl_80111B1C, lbl_80111BF4, lbl_80111C18,
      lbl_80111C74, func_800761C8 },
    { 309, 0x00340213, 0x14000000, lbl_80113194, lbl_8011320C, lbl_80113214,
      lbl_80113278, func_800761C8 },
    { 309, 0x00340213, 0x14000000, lbl_801133FC, lbl_80113474, lbl_8011347C,
      lbl_801134A0, func_800761C8 },
    { 310, 0x00340213, 0x14000000, lbl_80113C40, lbl_80113CDC, lbl_80113CE4,
      lbl_80113D80, func_800761C8 },
    { 311, 0x00340613, 0x14000000, lbl_801131D0, lbl_80113210, lbl_80113234,
      lbl_801132B4, func_800761C8 },
    { 311, 0x00340613, 0x14000000, lbl_80113438, lbl_80113478, lbl_8011349C,
      lbl_80113540, func_800761C8 },
    { 312, 0x00340613, 0x14000000, lbl_80113C7C, lbl_80113CE0, lbl_80113D04,
      lbl_80113DBC, func_800761C8 },
    { 313, 0x00340014, 0x15000000, lbl_801142E8, lbl_80114368, lbl_80114370,
      lbl_801143D4, func_800761C8 },
    { 314, 0x00340014, 0x15000000, lbl_80114524, lbl_8011459C, lbl_801145A4,
      lbl_80114608, func_800761C8 },
    { 315, 0x00340414, 0x15000000, lbl_80114328, lbl_8011436C, lbl_80114390,
      lbl_80114410, func_800761C8 },
    { 316, 0x00340414, 0x15000000, lbl_80114560, lbl_801145A0, lbl_801145C4,
      lbl_80114644, func_800761C8 },
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

void ftSeak_OnDeath(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    fp->sa.seak.x222C = 0;
    fp->sa.seak.x2230 = 0;
    fp->sa.seak.x2234 = 0;
    func_80074A4C(fighter_gobj, 0, 0);
    func_80074A4C(fighter_gobj, 1, -1);
}

void ftSeak_OnLoad(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftSeakAttributes);

    func_8026B3F8(item_list[0], 0x4FU);
    func_8026B3F8(item_list[1], 0x50U);
    func_8026B3F8(item_list[2], 0x55U);
    func_8026B3F8(item_list[3], 0x61U);
}

/* static */ void func_80111FBC(HSD_GObj* fighter_gobj);
/* static */ void func_80110E88(HSD_GObj* fighter_gobj);

void ftSeak_80110198(HSD_GObj* fighter_gobj)
{
    func_80111FBC(fighter_gobj);
    func_80110E88(fighter_gobj);
}

void ftSeak_801101CC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    if (fp->sa.seak.x222C == 6) {
        func_800BFFD0(fp, 0x56, 0);
    }
}

void ftSeak_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftSeak_OnItemInvisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftSeak_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftSeak_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1)
{
    Fighter_OnItemDrop(fighter_gobj, bool1, 1, 1);
}

void ftSeak_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, ftSeakAttributes);
}

void ftSeak_OnKnockbackEnter(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftSeak_OnKnockbackExit(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}

// 8011412C - 80114160
// https://decomp.me/scratch/b1oIZ
// void lbl_8011412C(HSD_GObj* fighter_gobj) {
//     Fighter* fp = fighter_gobj->user_data;
//     fp->cb.x21BC_callback_Accessory4 = 0;
//     func_8007EFC8(fighter_gobj, &ftZelda_8013B4D8);
// }

#include <melee/ft/chara/ftEmblem/ftemblem.h>

#include <melee/ft/chara/ftMars/ftMars.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>

ActionState ftRoy_MotionStateTable[] = {
    { 295, 0x00340211, 0x12000000, ftMars_80136844, ftMars_80136914,
      ftMars_8013691C, ftMars_801369A4, ftCamera_UpdateCameraBox },
    { 296, 0x00340211, 0x12000000, ftMars_80136ADC, ftMars_80136C8C,
      ftMars_80136CFC, ftMars_80136D3C, ftCamera_UpdateCameraBox },
    { 297, 0x00340211, 0x12000000, ftMars_80136EE4, ftMars_8013713C,
      ftMars_80137144, ftMars_80137184, ftCamera_UpdateCameraBox },
    { 298, 0x00340211, 0x12000000, ftMars_80136EE4, ftMars_8013713C,
      ftMars_80137144, ftMars_80137184, ftCamera_UpdateCameraBox },
    { 299, 0x00340611, 0x12000000, ftMars_801368AC, ftMars_80136918,
      ftMars_8013695C, ftMars_801369E0, ftCamera_UpdateCameraBox },
    { 300, 0x00340611, 0x12000000, ftMars_80136BB4, ftMars_80136CC4,
      ftMars_80136D1C, ftMars_80136D78, ftCamera_UpdateCameraBox },
    { 301, 0x00340611, 0x12000000, ftMars_80137010, ftMars_80137140,
      ftMars_80137164, ftMars_801371C0, ftCamera_UpdateCameraBox },
    { 302, 0x00340611, 0x12000000, ftMars_80137010, ftMars_80137140,
      ftMars_80137164, ftMars_801371C0, ftCamera_UpdateCameraBox },
    { 303, 0x00340212, 0x13000000, ftMars_80137558, ftMars_801375B8,
      ftMars_80137618, ftMars_8013767C, ftCamera_UpdateCameraBox },
    { 304, 0x00340212, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, ftCamera_UpdateCameraBox },
    { 305, 0x00340212, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, ftCamera_UpdateCameraBox },
    { 306, 0x00340212, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, ftCamera_UpdateCameraBox },
    { 307, 0x00340212, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, ftCamera_UpdateCameraBox },
    { 308, 0x00340212, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, ftCamera_UpdateCameraBox },
    { 309, 0x00340212, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, ftCamera_UpdateCameraBox },
    { 310, 0x00340212, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, ftCamera_UpdateCameraBox },
    { 311, 0x00340212, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, ftCamera_UpdateCameraBox },
    { 312, 0x00340612, 0x13000000, ftMars_80137558, ftMars_801375B8,
      ftMars_80137618, ftMars_8013767C, ftCamera_UpdateCameraBox },
    { 313, 0x00340612, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, ftCamera_UpdateCameraBox },
    { 314, 0x00340612, 0x13000000, ftMars_801377B0, ftMars_80137810,
      ftMars_80137870, ftMars_801378D4, ftCamera_UpdateCameraBox },
    { 315, 0x00340612, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, ftCamera_UpdateCameraBox },
    { 316, 0x00340612, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, ftCamera_UpdateCameraBox },
    { 317, 0x00340612, 0x13000000, ftMars_80137B34, ftMars_80137B94,
      ftMars_80137BF4, ftMars_80137C50, ftCamera_UpdateCameraBox },
    { 318, 0x00340612, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, ftCamera_UpdateCameraBox },
    { 319, 0x00340612, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, ftCamera_UpdateCameraBox },
    { 320, 0x00340612, 0x13000000, ftMars_80137ECC, ftMars_80137F2C,
      ftMars_80137F30, ftMars_80137F8C, ftCamera_UpdateCameraBox },
    { 321, 0x00340213, 0x14000000, ftMars_801382E8, ftMars_801383A8,
      ftMars_80138638, ftMars_801388B4, ftCamera_UpdateCameraBox },
    { 322, 0x00340613, 0x14000000, ftMars_80138348, ftMars_801384F0,
      ftMars_8013873C, ftMars_80138940, ftCamera_UpdateCameraBox },
    { 323, 0x00340214, 0x15000000, ftMars_80138AA8, ftMars_80138C20,
      ftMars_80138C28, ftMars_80138CC0, ftCamera_UpdateCameraBox },
    { 324, 0x00340214, 0x15000000, ftMars_80138E68, ftMars_80138FC0,
      ftMars_80138FC8, ftMars_80139008, ftCamera_UpdateCameraBox },
    { 325, 0x00340614, 0x15000000, ftMars_80138B64, ftMars_80138C24,
      ftMars_80138C5C, ftMars_80138CFC, ftCamera_UpdateCameraBox },
    { 326, 0x00340614, 0x15000000, ftMars_80138F14, ftMars_80138FC4,
      ftMars_80138FE8, ftMars_80139044, ftCamera_UpdateCameraBox },
};

char lbl_803D3280[] = "PlFe.dat";
char lbl_803D328C[] = "ftDataEmblem";
char lbl_803D329C[] = "PlFeNr.dat";
char lbl_803D32A8[] = "PlyEmblem5K_Share_joint";
char lbl_803D32C0[] = "PlyEmblem5K_Share_matanim_joint";
char lbl_803D32E0[] = "PlFeRe.dat";
char lbl_803D32EC[] = "PlyEmblem5KRe_Share_joint";
char lbl_803D3308[] = "PlyEmblem5KRe_Share_matanim_joint";
char lbl_803D332C[] = "PlFeBu.dat";
char lbl_803D3338[] = "PlyEmblem5KBu_Share_joint";
char lbl_803D3354[] = "PlyEmblem5KBu_Share_matanim_joint";
char lbl_803D3378[] = "PlFeGr.dat";
char lbl_803D3384[] = "PlyEmblem5KGr_Share_joint";
char lbl_803D33A0[] = "PlyEmblem5KGr_Share_matanim_joint";
char lbl_803D33C4[] = "PlFeYe.dat";
char lbl_803D33D0[] = "PlyEmblem5KYe_Share_joint";
char lbl_803D33EC[] = "PlyEmblem5KYe_Share_matanim_joint";
char lbl_803D3410[] = "PlFeAJ.dat";

Fighter_DemoStrings lbl_803D3498 = {
    "ftDemoResultMotionFileEmblem",
    "ftDemoIntroMotionFileEmblem",
    "ftDemoEndingMotionFileEmblem",
    "ftDemoViWaitMotionFileEmblem",
};

Fighter_CostumeStrings lbl_803D34A8[] = {
    { lbl_803D329C, lbl_803D32A8, lbl_803D32C0 },
    { lbl_803D32E0, lbl_803D32EC, lbl_803D3308 },
    { lbl_803D332C, lbl_803D3338, lbl_803D3354 },
    { lbl_803D3378, lbl_803D3384, lbl_803D33A0 },
    { lbl_803D33C4, lbl_803D33D0, lbl_803D33EC },
};

void ftRoy_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    ftParts_80074A4C(gobj, 2, -1);
    fp->ev.ms.x222C = 0;
}

void ftRoy_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, 0, 1);
}

void ftRoy_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftRoy_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftRoy_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 1);
}

void ftRoy_OnLoad(HSD_GObj* gobj)
{
    ftMars_OnLoadForRoy(gobj->user_data);
}

void ftRoy_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftMars_LoadSpecialAttrs(gobj);
}

void ftRoy_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftRoy_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

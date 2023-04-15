#include "ftEmblem/ftemblem.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftMars/ftMars.h"

MotionState ftFe_Init_MotionStateTable[] = {
    { 295, 0x00340211, 0x12000000, ftMs_SpecialN_80136844,
      ftMs_SpecialN_80136914, ftMs_SpecialN_8013691C, ftMs_SpecialN_801369A4,
      ftCamera_UpdateCameraBox },
    { 296, 0x00340211, 0x12000000, ftMs_SpecialN_80136ADC,
      ftMs_SpecialN_80136C8C, ftMs_SpecialN_80136CFC, ftMs_SpecialN_80136D3C,
      ftCamera_UpdateCameraBox },
    { 297, 0x00340211, 0x12000000, ftMs_SpecialN_80136EE4,
      ftMs_SpecialN_8013713C, ftMs_SpecialN_80137144, ftMs_SpecialN_80137184,
      ftCamera_UpdateCameraBox },
    { 298, 0x00340211, 0x12000000, ftMs_SpecialN_80136EE4,
      ftMs_SpecialN_8013713C, ftMs_SpecialN_80137144, ftMs_SpecialN_80137184,
      ftCamera_UpdateCameraBox },
    { 299, 0x00340611, 0x12000000, ftMs_SpecialN_801368AC,
      ftMs_SpecialN_80136918, ftMs_SpecialN_8013695C, ftMs_SpecialN_801369E0,
      ftCamera_UpdateCameraBox },
    { 300, 0x00340611, 0x12000000, ftMs_SpecialN_80136BB4,
      ftMs_SpecialN_80136CC4, ftMs_SpecialN_80136D1C, ftMs_SpecialN_80136D78,
      ftCamera_UpdateCameraBox },
    { 301, 0x00340611, 0x12000000, ftMs_SpecialN_80137010,
      ftMs_SpecialN_80137140, ftMs_SpecialN_80137164, ftMs_SpecialN_801371C0,
      ftCamera_UpdateCameraBox },
    { 302, 0x00340611, 0x12000000, ftMs_SpecialN_80137010,
      ftMs_SpecialN_80137140, ftMs_SpecialN_80137164, ftMs_SpecialN_801371C0,
      ftCamera_UpdateCameraBox },
    { 303, 0x00340212, 0x13000000, ftMs_SpecialS_80137558,
      ftMs_SpecialS_801375B8, ftMs_SpecialS_80137618, ftMs_SpecialS_8013767C,
      ftCamera_UpdateCameraBox },
    { 304, 0x00340212, 0x13000000, ftMs_SpecialS_801377B0,
      ftMs_SpecialS_80137810, ftMs_SpecialS_80137870, ftMs_SpecialS_801378D4,
      ftCamera_UpdateCameraBox },
    { 305, 0x00340212, 0x13000000, ftMs_SpecialS_801377B0,
      ftMs_SpecialS_80137810, ftMs_SpecialS_80137870, ftMs_SpecialS_801378D4,
      ftCamera_UpdateCameraBox },
    { 306, 0x00340212, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 307, 0x00340212, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 308, 0x00340212, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 309, 0x00340212, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 310, 0x00340212, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 311, 0x00340212, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 312, 0x00340612, 0x13000000, ftMs_SpecialS_80137558,
      ftMs_SpecialS_801375B8, ftMs_SpecialS_80137618, ftMs_SpecialS_8013767C,
      ftCamera_UpdateCameraBox },
    { 313, 0x00340612, 0x13000000, ftMs_SpecialS_801377B0,
      ftMs_SpecialS_80137810, ftMs_SpecialS_80137870, ftMs_SpecialS_801378D4,
      ftCamera_UpdateCameraBox },
    { 314, 0x00340612, 0x13000000, ftMs_SpecialS_801377B0,
      ftMs_SpecialS_80137810, ftMs_SpecialS_80137870, ftMs_SpecialS_801378D4,
      ftCamera_UpdateCameraBox },
    { 315, 0x00340612, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 316, 0x00340612, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 317, 0x00340612, 0x13000000, ftMs_SpecialS_80137B34,
      ftMs_SpecialS_80137B94, ftMs_SpecialS_80137BF4, ftMs_SpecialS_80137C50,
      ftCamera_UpdateCameraBox },
    { 318, 0x00340612, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 319, 0x00340612, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 320, 0x00340612, 0x13000000, ftMs_SpecialS_80137ECC,
      ftMs_SpecialS_80137F2C, ftMs_SpecialS_80137F30, ftMs_SpecialS_80137F8C,
      ftCamera_UpdateCameraBox },
    { 321, 0x00340213, 0x14000000, ftMs_SpecialHi_801382E8,
      ftMs_SpecialHi_801383A8, ftMs_SpecialHi_80138638,
      ftMs_SpecialHi_801388B4, ftCamera_UpdateCameraBox },
    { 322, 0x00340613, 0x14000000, ftMs_SpecialHi_80138348,
      ftMs_SpecialHi_801384F0, ftMs_SpecialHi_8013873C,
      ftMs_SpecialHi_80138940, ftCamera_UpdateCameraBox },
    { 323, 0x00340214, 0x15000000, ftMs_SpecialLw_80138AA8,
      ftMs_SpecialLw_80138C20, ftMs_SpecialLw_80138C28,
      ftMs_SpecialLw_80138CC0, ftCamera_UpdateCameraBox },
    { 324, 0x00340214, 0x15000000, ftMs_SpecialLw_80138E68,
      ftMs_SpecialLw_80138FC0, ftMs_SpecialLw_80138FC8,
      ftMs_SpecialLw_80139008, ftCamera_UpdateCameraBox },
    { 325, 0x00340614, 0x15000000, ftMs_SpecialLw_80138B64,
      ftMs_SpecialLw_80138C24, ftMs_SpecialLw_80138C5C,
      ftMs_SpecialLw_80138CFC, ftCamera_UpdateCameraBox },
    { 326, 0x00340614, 0x15000000, ftMs_SpecialLw_80138F14,
      ftMs_SpecialLw_80138FC4, ftMs_SpecialLw_80138FE8,
      ftMs_SpecialLw_80139044, ftCamera_UpdateCameraBox },
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
    ftMs_OnLoadForRoy(gobj->user_data);
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

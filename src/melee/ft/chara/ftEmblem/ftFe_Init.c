#include "ft/chara/ftEmblem/ftFe_Init.h"

#include "ft/chara/ftMars/ftMs_Init.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"

MotionState ftFe_Init_MotionStateTable[] = {
    { 295, 0x00340211, 0x12000000, ftMs_SpecialNChargeStart_Anim, ftMs_SpecialNChargeStart_IASA,
      ftMs_SpecialNChargeStart_Phys, ftMs_SpecialNChargeStart_Coll, ftCamera_UpdateCameraBox },
    { 296, 0x00340211, 0x12000000, ftMs_SpecialNChargeLoop_Anim, ftMs_SpecialNChargeLoop_IASA,
      ftMs_SpecialNChargeLoop_Phys, ftMs_SpecialNChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 297, 0x00340211, 0x12000000, ftMs_SpecialNChargeEnd_Anim, ftMs_SpecialNChargeEnd_IASA,
      ftMs_SpecialNChargeEnd_Phys, ftMs_SpecialNChargeEnd_Coll, ftCamera_UpdateCameraBox },
    { 298, 0x00340211, 0x12000000, ftMs_SpecialNChargeEnd_Anim, ftMs_SpecialNChargeEnd_IASA,
      ftMs_SpecialNChargeEnd_Phys, ftMs_SpecialNChargeEnd_Coll, ftCamera_UpdateCameraBox },
    { 299, 0x00340611, 0x12000000, ftMs_SpecialAirNChargeStart_Anim, ftMs_SpecialAirNChargeStart_IASA,
      ftMs_SpecialAirNChargeStart_Phys, ftMs_SpecialAirNChargeStart_Coll, ftCamera_UpdateCameraBox },
    { 300, 0x00340611, 0x12000000, ftMs_SpecialAirNChargeLoop_Anim, ftMs_SpecialAirNChargeLoop_IASA,
      ftMs_SpecialAirNChargeLoop_Phys, ftMs_SpecialAirNChargeLoop_Coll, ftCamera_UpdateCameraBox },
    { 301, 0x00340611, 0x12000000, ftMs_SpecialAirNChargeEnd_Anim, ftMs_SpecialAirNChargeEnd_IASA,
      ftMs_SpecialAirNChargeEnd_Phys, ftMs_SpecialAirNChargeEnd_Coll, ftCamera_UpdateCameraBox },
    { 302, 0x00340611, 0x12000000, ftMs_SpecialAirNChargeEnd_Anim, ftMs_SpecialAirNChargeEnd_IASA,
      ftMs_SpecialAirNChargeEnd_Phys, ftMs_SpecialAirNChargeEnd_Coll, ftCamera_UpdateCameraBox },
    { 303, 0x00340212, 0x13000000, ftMs_SpecialS1_Anim, ftMs_SpecialS1_IASA,
      ftMs_SpecialS1_Phys, ftMs_SpecialS1_Coll, ftCamera_UpdateCameraBox },
    { 304, 0x00340212, 0x13000000, ftMs_SpecialS2_Anim, ftMs_SpecialS2_IASA,
      ftMs_SpecialS2_Phys, ftMs_SpecialS2_Coll, ftCamera_UpdateCameraBox },
    { 305, 0x00340212, 0x13000000, ftMs_SpecialS2_Anim, ftMs_SpecialS2_IASA,
      ftMs_SpecialS2_Phys, ftMs_SpecialS2_Coll, ftCamera_UpdateCameraBox },
    { 306, 0x00340212, 0x13000000, ftMs_SpecialS3_Anim, ftMs_SpecialS3_IASA,
      ftMs_SpecialS3_Phys, ftMs_SpecialS3_Coll, ftCamera_UpdateCameraBox },
    { 307, 0x00340212, 0x13000000, ftMs_SpecialS3_Anim, ftMs_SpecialS3_IASA,
      ftMs_SpecialS3_Phys, ftMs_SpecialS3_Coll, ftCamera_UpdateCameraBox },
    { 308, 0x00340212, 0x13000000, ftMs_SpecialS3_Anim, ftMs_SpecialS3_IASA,
      ftMs_SpecialS3_Phys, ftMs_SpecialS3_Coll, ftCamera_UpdateCameraBox },
    { 309, 0x00340212, 0x13000000, ftMs_SpecialS4_Anim, ftMs_SpecialS4_IASA,
      ftMs_SpecialS4_Phys, ftMs_SpecialS4_Coll, ftCamera_UpdateCameraBox },
    { 310, 0x00340212, 0x13000000, ftMs_SpecialS4_Anim, ftMs_SpecialS4_IASA,
      ftMs_SpecialS4_Phys, ftMs_SpecialS4_Coll, ftCamera_UpdateCameraBox },
    { 311, 0x00340212, 0x13000000, ftMs_SpecialS4_Anim, ftMs_SpecialS4_IASA,
      ftMs_SpecialS4_Phys, ftMs_SpecialS4_Coll, ftCamera_UpdateCameraBox },
    { 312, 0x00340612, 0x13000000, ftMs_SpecialS1_Anim, ftMs_SpecialS1_IASA,
      ftMs_SpecialS1_Phys, ftMs_SpecialS1_Coll, ftCamera_UpdateCameraBox },
    { 313, 0x00340612, 0x13000000, ftMs_SpecialS2_Anim, ftMs_SpecialS2_IASA,
      ftMs_SpecialS2_Phys, ftMs_SpecialS2_Coll, ftCamera_UpdateCameraBox },
    { 314, 0x00340612, 0x13000000, ftMs_SpecialS2_Anim, ftMs_SpecialS2_IASA,
      ftMs_SpecialS2_Phys, ftMs_SpecialS2_Coll, ftCamera_UpdateCameraBox },
    { 315, 0x00340612, 0x13000000, ftMs_SpecialS3_Anim, ftMs_SpecialS3_IASA,
      ftMs_SpecialS3_Phys, ftMs_SpecialS3_Coll, ftCamera_UpdateCameraBox },
    { 316, 0x00340612, 0x13000000, ftMs_SpecialS3_Anim, ftMs_SpecialS3_IASA,
      ftMs_SpecialS3_Phys, ftMs_SpecialS3_Coll, ftCamera_UpdateCameraBox },
    { 317, 0x00340612, 0x13000000, ftMs_SpecialS3_Anim, ftMs_SpecialS3_IASA,
      ftMs_SpecialS3_Phys, ftMs_SpecialS3_Coll, ftCamera_UpdateCameraBox },
    { 318, 0x00340612, 0x13000000, ftMs_SpecialS4_Anim, ftMs_SpecialS4_IASA,
      ftMs_SpecialS4_Phys, ftMs_SpecialS4_Coll, ftCamera_UpdateCameraBox },
    { 319, 0x00340612, 0x13000000, ftMs_SpecialS4_Anim, ftMs_SpecialS4_IASA,
      ftMs_SpecialS4_Phys, ftMs_SpecialS4_Coll, ftCamera_UpdateCameraBox },
    { 320, 0x00340612, 0x13000000, ftMs_SpecialS4_Anim, ftMs_SpecialS4_IASA,
      ftMs_SpecialS4_Phys, ftMs_SpecialS4_Coll, ftCamera_UpdateCameraBox },
    { 321, 0x00340213, 0x14000000, ftMs_SpecialHi_Anim, ftMs_SpecialHi_IASA,
      ftMs_SpecialHi_Phys, ftMs_SpecialHi_Coll, ftCamera_UpdateCameraBox },
    { 322, 0x00340613, 0x14000000, ftMs_SpecialAirHi_Anim, ftMs_SpecialAirHi_IASA,
      ftMs_SpecialAirHi_Phys, ftMs_SpecialAirHi_Coll, ftCamera_UpdateCameraBox },
    { 323, 0x00340214, 0x15000000, ftMs_SpecialLw_Anim, ftMs_SpecialLw_IASA,
      ftMs_SpecialLw_Phys, ftMs_SpecialLw_Coll, ftCamera_UpdateCameraBox },
    { 324, 0x00340214, 0x15000000, ftMs_SpecialLwHit_Anim, ftMs_SpecialLwHit_IASA,
      ftMs_SpecialLwHit_Phys, ftMs_SpecialLwHit_Coll, ftCamera_UpdateCameraBox },
    { 325, 0x00340614, 0x15000000, ftMs_SpecialAirLw_Anim, ftMs_SpecialAirLw_IASA,
      ftMs_SpecialAirLw_Phys, ftMs_SpecialAirLw_Coll, ftCamera_UpdateCameraBox },
    { 326, 0x00340614, 0x15000000, ftMs_SpecialAirLwHit_Anim, ftMs_SpecialAirLwHit_IASA,
      ftMs_SpecialAirLwHit_Phys, ftMs_SpecialAirLwHit_Coll, ftCamera_UpdateCameraBox },
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
    fp->ev.ms.x222C = 0;
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
    ftMs_Init_OnLoadForRoy(gobj->user_data);
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

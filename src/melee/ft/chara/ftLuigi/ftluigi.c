#include "ftLuigi/ftluigi.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftLuigi_MotionStateTable[] = {
    { 295, 0x00340111, 0x12000000, ftLuigi_SpecialN_Anim,
      ftLuigi_SpecialN_IASA, ftLuigi_SpecialN_Phys, ftLuigi_SpecialN_Coll,
      ftCamera_UpdateCameraBox },
    { 296, 0x00340511, 0x12000000, ftLuigi_SpecialAirN_Anim,
      ftLuigi_SpecialAirN_IASA, ftLuigi_SpecialAirN_Phys,
      ftLuigi_SpecialAirN_Coll, ftCamera_UpdateCameraBox },
    { 297, 0x00340212, 0x13000000, ftLuigi_SpecialSStart_Anim,
      ftLuigi_SpecialSStart_IASA, ftLuigi_SpecialSStart_Phys,
      ftLuigi_SpecialSStart_Coll, ftCamera_UpdateCameraBox },
    { 298, 0x00340212, 0x13000000, ftLuigi_SpecialSHold_Anim,
      ftLuigi_SpecialSHold_IASA, ftLuigi_SpecialSHold_Phys,
      ftLuigi_SpecialSHold_Coll, ftCamera_UpdateCameraBox },
    { 301, 0x00340212, 0x13000000, ftLuigi_SpecialSFly_Anim,
      ftLuigi_SpecialSFly_IASA, ftLuigi_SpecialSFly_Phys,
      ftLuigi_SpecialSFly_Coll, ftCamera_UpdateCameraBox },
    { 302, 0x00340212, 0x13000000, ftLuigi_SpecialSEnd_Anim,
      ftLuigi_SpecialSEnd_IASA, ftLuigi_SpecialSEnd_Phys,
      ftLuigi_SpecialSEnd_Coll, ftCamera_UpdateCameraBox },
    { 299, 0x00340212, 0x13000000, ftLuigi_SpecialSLaunch_Anim,
      ftLuigi_SpecialSLaunch_IASA, ftLuigi_SpecialSLaunch_Phys,
      ftLuigi_SpecialSLaunch_Coll, ftCamera_UpdateCameraBox },
    { 300, 0x00340212, 0x13000000, ftLuigi_SpecialSMisfire_Anim,
      ftLuigi_SpecialSMisfire_IASA, ftLuigi_SpecialSMisfire_Phys,
      ftLuigi_SpecialSMisfire_Coll, ftCamera_UpdateCameraBox },
    { 303, 0x00340612, 0x13000000, ftLuigi_SpecialAirSStart_Anim,
      ftLuigi_SpecialAirSStart_IASA, ftLuigi_SpecialAirSStart_Phys,
      ftLuigi_SpecialAirSStart_Coll, ftCamera_UpdateCameraBox },
    { 304, 0x00340612, 0x13000000, ftLuigi_SpecialAirSHold_Anim,
      ftLuigi_SpecialAirSHold_IASA, ftLuigi_SpecialAirSHold_Phys,
      ftLuigi_SpecialAirSHold_Coll, ftCamera_UpdateCameraBox },
    { 301, 0x00340612, 0x13000000, ftLuigi_SpecialAirSFly_Anim,
      ftLuigi_SpecialAirSFly_IASA, ftLuigi_SpecialAirSFly_Phys,
      ftLuigi_SpecialAirSFly_Coll, ftCamera_UpdateCameraBox },
    { 307, 0x00340612, 0x13000000, ftLuigi_SpecialAirSEnd_Anim,
      ftLuigi_SpecialAirSEnd_IASA, ftLuigi_SpecialAirSEnd_Phys,
      ftLuigi_SpecialAirSEnd_Coll, ftCamera_UpdateCameraBox },
    { 305, 0x00340612, 0x13000000, ftLuigi_SpecialAirSLaunch_Anim,
      ftLuigi_SpecialAirSLaunch_IASA, ftLuigi_SpecialAirSLaunch_Phys,
      ftLuigi_SpecialAirSLaunch_Coll, ftCamera_UpdateCameraBox },
    { 306, 0x00340612, 0x13000000, ftLuigi_SpecialAirSMisfire_Anim,
      ftLuigi_SpecialAirSMisfire_IASA, ftLuigi_SpecialAirSMisfire_Phys,
      ftLuigi_SpecialAirSMisfire_Coll, ftCamera_UpdateCameraBox },
    { 308, 0x00340213, 0x14000000, ftLuigi_SpecialHi_Anim,
      ftLuigi_SpecialHi_IASA, ftLuigi_SpecialHi_Phys, ftLuigi_SpecialHi_Coll,
      ftCamera_UpdateCameraBox },
    { 309, 0x00340613, 0x14000000, ftLuigi_SpecialAirHi_Anim,
      ftLuigi_SpecialAirHi_IASA, ftLuigi_SpecialAirHi_Phys,
      ftLuigi_SpecialAirHi_Coll, ftCamera_UpdateCameraBox },
    { 310, 0x00340214, 0x15000000, ftLuigi_SpecialLw_Anim,
      ftLuigi_SpecialLw_IASA, ftLuigi_SpecialLw_Phys, ftLuigi_SpecialLw_Coll,
      ftCamera_UpdateCameraBox },
    { 311, 0x00340614, 0x15000000, ftLuigi_SpecialAirLw_Anim,
      ftLuigi_SpecialAirLw_IASA, ftLuigi_SpecialAirLw_Phys,
      ftLuigi_SpecialAirLw_Coll, ftCamera_UpdateCameraBox },
};

MotionState lbl_803D0868[] = {
    { 14, 0, 0x01000000, NULL, NULL, ft_800C7158, NULL, NULL },
    { 15, 0, 0x01000000, NULL, NULL, ft_800C7200, NULL, NULL },
};

char lbl_803D08A8[] = "PlLg.dat";
char lbl_803D08B4[] = "ftDataLuigi";
char lbl_803D08C0[] = "PlLgNr.dat";
char lbl_803D08CC[] = "PlyLuigi5K_Share_joint";
char lbl_803D08E4[] = "PlyLuigi5K_Share_matanim_joint";
char lbl_803D0904[] = "PlLgWh.dat";
char lbl_803D0910[] = "PlyLuigi5KWh_Share_joint";
char lbl_803D092C[] = "PlyLuigi5KWh_Share_matanim_joint";
char lbl_803D0950[] = "PlLgAq.dat";
char lbl_803D095C[] = "PlyLuigi5KAq_Share_joint";
char lbl_803D0978[] = "PlyLuigi5KAq_Share_matanim_joint";
char lbl_803D099C[] = "PlLgPi.dat";
char lbl_803D09A8[] = "PlyLuigi5KPi_Share_joint";
char lbl_803D09C4[] = "PlyLuigi5KPi_Share_matanim_joint";
char lbl_803D09E8[] = "PlLgAJ.dat";

Fighter_DemoStrings lbl_803D0A64 = {
    "ftDemoResultMotionFileLuigi",
    "ftDemoIntroMotionFileLuigi",
    "ftDemoEndingMotionFileLuigi",
    "ftDemoViWaitMotionFileLuigi",
};

char* lbl_803D0AAC[] = {
    "ftDemoVi0102MotionFileLuigi",
    "ftDemoVi1101MotionFileLuigi",
};

Fighter_CostumeStrings lbl_803D0AB4[] = {
    { lbl_803D08C0, lbl_803D08CC, lbl_803D08E4 },
    { lbl_803D0904, lbl_803D0910, lbl_803D092C },
    { lbl_803D0950, lbl_803D095C, lbl_803D0978 },
    { lbl_803D099C, lbl_803D09A8, lbl_803D09C4 },
};

void ftLuigi_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, false);
    fp->fv.lg.x2234 = 0;
}

void ftLuigi_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftLuigiAttributes);

    it_8026B3F8(item_list[0], It_Kind_Luigi_Fire);
}

void ftLuigi_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftLuigi_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftLuigi_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftLuigi_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftLuigi_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftLuigiAttributes);
}

void ftLuigi_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftLuigi_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftLuigi_8014260C(s32 arg0, s32* arg1, s32* arg2)
{
    if (arg0 != 0xA) {
        if (arg0 < 0xA && arg0 >= 9) {
            *arg2 = 0xE;
            *arg1 = 0xE;
        }
    } else {
        *arg2 = 0xF;
        *arg1 = 0xF;
    }
}

char* ftLuigi_GetMotionFileString(enum_t arg0)
{
    int offset;

    switch (arg0) {
    case 9:
        offset = 14;
        break;
    case 10:
        offset = 15;
        break;
    }

    return lbl_803D0AAC[offset - 14];
}

#include "ftLuigi/ftluigi.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftLg_Init_MotionStateTable[] = {
    { 295, 0x00340111, 0x12000000, ftLg_SpecialN_Anim, ftLg_SpecialN_IASA,
      ftLg_SpecialN_Phys, ftLg_SpecialN_Coll, ftCamera_UpdateCameraBox },
    { 296, 0x00340511, 0x12000000, ftLg_SpecialAirN_Anim,
      ftLg_SpecialAirN_IASA, ftLg_SpecialAirN_Phys, ftLg_SpecialAirN_Coll,
      ftCamera_UpdateCameraBox },
    { 297, 0x00340212, 0x13000000, ftLg_SpecialSStart_Anim,
      ftLg_SpecialSStart_IASA, ftLg_SpecialSStart_Phys,
      ftLg_SpecialSStart_Coll, ftCamera_UpdateCameraBox },
    { 298, 0x00340212, 0x13000000, ftLg_SpecialSHold_Anim,
      ftLg_SpecialSHold_IASA, ftLg_SpecialSHold_Phys, ftLg_SpecialSHold_Coll,
      ftCamera_UpdateCameraBox },
    { 301, 0x00340212, 0x13000000, ftLg_SpecialSFly_Anim,
      ftLg_SpecialSFly_IASA, ftLg_SpecialSFly_Phys, ftLg_SpecialSFly_Coll,
      ftCamera_UpdateCameraBox },
    { 302, 0x00340212, 0x13000000, ftLg_SpecialSEnd_Anim,
      ftLg_SpecialSEnd_IASA, ftLg_SpecialSEnd_Phys, ftLg_SpecialSEnd_Coll,
      ftCamera_UpdateCameraBox },
    { 299, 0x00340212, 0x13000000, ftLg_SpecialSLaunch_Anim,
      ftLg_SpecialSLaunch_IASA, ftLg_SpecialSLaunch_Phys,
      ftLg_SpecialSLaunch_Coll, ftCamera_UpdateCameraBox },
    { 300, 0x00340212, 0x13000000, ftLg_SpecialSMisfire_Anim,
      ftLg_SpecialSMisfire_IASA, ftLg_SpecialSMisfire_Phys,
      ftLg_SpecialSMisfire_Coll, ftCamera_UpdateCameraBox },
    { 303, 0x00340612, 0x13000000, ftLg_SpecialAirSStart_Anim,
      ftLg_SpecialAirSStart_IASA, ftLg_SpecialAirSStart_Phys,
      ftLg_SpecialAirSStart_Coll, ftCamera_UpdateCameraBox },
    { 304, 0x00340612, 0x13000000, ftLg_SpecialAirSHold_Anim,
      ftLg_SpecialAirSHold_IASA, ftLg_SpecialAirSHold_Phys,
      ftLg_SpecialAirSHold_Coll, ftCamera_UpdateCameraBox },
    { 301, 0x00340612, 0x13000000, ftLg_SpecialAirSFly_Anim,
      ftLg_SpecialAirSFly_IASA, ftLg_SpecialAirSFly_Phys,
      ftLg_SpecialAirSFly_Coll, ftCamera_UpdateCameraBox },
    { 307, 0x00340612, 0x13000000, ftLg_SpecialAirSEnd_Anim,
      ftLg_SpecialAirSEnd_IASA, ftLg_SpecialAirSEnd_Phys,
      ftLg_SpecialAirSEnd_Coll, ftCamera_UpdateCameraBox },
    { 305, 0x00340612, 0x13000000, ftLg_SpecialAirSLaunch_Anim,
      ftLg_SpecialAirSLaunch_IASA, ftLg_SpecialAirSLaunch_Phys,
      ftLg_SpecialAirSLaunch_Coll, ftCamera_UpdateCameraBox },
    { 306, 0x00340612, 0x13000000, ftLg_SpecialAirSMisfire_Anim,
      ftLg_SpecialAirSMisfire_IASA, ftLg_SpecialAirSMisfire_Phys,
      ftLg_SpecialAirSMisfire_Coll, ftCamera_UpdateCameraBox },
    { 308, 0x00340213, 0x14000000, ftLg_SpecialHi_Anim, ftLg_SpecialHi_IASA,
      ftLg_SpecialHi_Phys, ftLg_SpecialHi_Coll, ftCamera_UpdateCameraBox },
    { 309, 0x00340613, 0x14000000, ftLg_SpecialAirHi_Anim,
      ftLg_SpecialAirHi_IASA, ftLg_SpecialAirHi_Phys, ftLg_SpecialAirHi_Coll,
      ftCamera_UpdateCameraBox },
    { 310, 0x00340214, 0x15000000, ftLg_SpecialLw_Anim, ftLg_SpecialLw_IASA,
      ftLg_SpecialLw_Phys, ftLg_SpecialLw_Coll, ftCamera_UpdateCameraBox },
    { 311, 0x00340614, 0x15000000, ftLg_SpecialAirLw_Anim,
      ftLg_SpecialAirLw_IASA, ftLg_SpecialAirLw_Phys, ftLg_SpecialAirLw_Coll,
      ftCamera_UpdateCameraBox },
};

MotionState ftLg_Init_UnkMotionStates0[] = {
    { 14, 0, 0x01000000, NULL, NULL, ft_800C7158, NULL, NULL },
    { 15, 0, 0x01000000, NULL, NULL, ft_800C7200, NULL, NULL },
};

char ftLg_Init_DatFilename[] = "PlLg.dat";
char ftLg_Init_DataName[] = "ftDataLuigi";
char ftLg_Init_803D08C0[] = "PlLgNr.dat";
char ftLg_Init_803D08CC[] = "PlyLuigi5K_Share_joint";
char ftLg_Init_803D08E4[] = "PlyLuigi5K_Share_matanim_joint";
char ftLg_Init_803D0904[] = "PlLgWh.dat";
char ftLg_Init_803D0910[] = "PlyLuigi5KWh_Share_joint";
char ftLg_Init_803D092C[] = "PlyLuigi5KWh_Share_matanim_joint";
char ftLg_Init_803D0950[] = "PlLgAq.dat";
char ftLg_Init_803D095C[] = "PlyLuigi5KAq_Share_joint";
char ftLg_Init_803D0978[] = "PlyLuigi5KAq_Share_matanim_joint";
char ftLg_Init_803D099C[] = "PlLgPi.dat";
char ftLg_Init_803D09A8[] = "PlyLuigi5KPi_Share_joint";
char ftLg_Init_803D09C4[] = "PlyLuigi5KPi_Share_matanim_joint";
char ftLg_Init_AnimDatFilename[] = "PlLgAJ.dat";

Fighter_DemoStrings ftLg_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileLuigi",
    "ftDemoIntroMotionFileLuigi",
    "ftDemoEndingMotionFileLuigi",
    "ftDemoViWaitMotionFileLuigi",
};

char* ftLg_Init_803D0AAC[] = {
    "ftDemoVi0102MotionFileLuigi",
    "ftDemoVi1101MotionFileLuigi",
};

Fighter_CostumeStrings ftLg_Init_CostumeStrings[] = {
    { ftLg_Init_803D08C0, ftLg_Init_803D08CC, ftLg_Init_803D08E4 },
    { ftLg_Init_803D0904, ftLg_Init_803D0910, ftLg_Init_803D092C },
    { ftLg_Init_803D0950, ftLg_Init_803D095C, ftLg_Init_803D0978 },
    { ftLg_Init_803D099C, ftLg_Init_803D09A8, ftLg_Init_803D09C4 },
};

void ftLg_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, false);
    fp->fv.lg.x2234 = 0;
}

void ftLg_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftLuigiAttributes);

    it_8026B3F8(item_list[0], It_Kind_Luigi_Fire);
}

void ftLg_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftLg_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftLg_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftLg_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftLg_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftLuigiAttributes);
}

void ftLg_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftLg_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftLg_Init_UnkDemoCallbacks0(s32 arg0, s32* arg1, s32* arg2)
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

char* ftLg_Init_GetMotionFileString(enum_t arg0)
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

    return ftLg_Init_803D0AAC[offset - 14];
}

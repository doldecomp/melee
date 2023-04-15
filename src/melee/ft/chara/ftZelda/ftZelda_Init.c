#include "ftZelda_Init.h"

#include "ftZelda_SpecialHi.h"
#include "ftZelda_SpecialLw.h"
#include "ftZelda_SpecialN.h"
#include "ftZelda_SpecialS.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftZd_Init_MotionStateTable[] = {
    { 295, 0x00341011, 0x12000000, ftZd_SpecialN_8013AA38,
      ftZd_SpecialN_8013AB60, ftZd_SpecialN_8013AB68, ftZd_SpecialN_8013AC10,
      ftCamera_UpdateCameraBox },
    { 296, 0x00341411, 0x12000000, ftZd_SpecialN_8013AACC,
      ftZd_SpecialN_8013AB64, ftZd_SpecialN_8013AB9C, ftZd_SpecialN_8013AC4C,
      ftCamera_UpdateCameraBox },
    { 297, 0x00340112, 0x13000000, ftZd_SpecialS_8013B780,
      ftZd_SpecialS_8013BDD0, ftZd_SpecialS_8013BED8, ftZd_SpecialS_8013C070,
      ftCamera_UpdateCameraBox },
    { 298, 0x00340112, 0x13000000, ftZd_SpecialS_8013B89C,
      ftZd_SpecialS_8013BDD4, ftZd_SpecialS_8013BF10, ftZd_SpecialS_8013C0DC,
      ftCamera_UpdateCameraBox },
    { 299, 0x00340112, 0x13000000, ftZd_SpecialS_8013BA04,
      ftZd_SpecialS_8013BE50, ftZd_SpecialS_8013BF30, ftZd_SpecialS_8013C148,
      ftCamera_UpdateCameraBox },
    { 300, 0x00340512, 0x13000000, ftZd_SpecialS_8013BA8C,
      ftZd_SpecialS_8013BE54, ftZd_SpecialS_8013BF50, ftZd_SpecialS_8013C1B4,
      ftCamera_UpdateCameraBox },
    { 301, 0x00340512, 0x13000000, ftZd_SpecialS_8013BBA8,
      ftZd_SpecialS_8013BE58, ftZd_SpecialS_8013BFB0, ftZd_SpecialS_8013C220,
      ftCamera_UpdateCameraBox },
    { 302, 0x00340512, 0x13000000, ftZd_SpecialS_8013BD10,
      ftZd_SpecialS_8013BED4, ftZd_SpecialS_8013C010, ftZd_SpecialS_8013C28C,
      ftCamera_UpdateCameraBox },
    { 303, 0x00340013, 0x14000000, ftZd_SpecialHi_801399B4,
      ftZd_SpecialHi_80139A2C, ftZd_SpecialHi_80139A34,
      ftZd_SpecialHi_80139A98, ftCamera_UpdateCameraBox },
    { 303, 0x00340013, 0x14000000, ftZd_SpecialHi_80139C1C,
      ftZd_SpecialHi_80139C94, ftZd_SpecialHi_80139C9C,
      ftZd_SpecialHi_80139CC0, ftCamera_UpdateCameraBox },
    { 304, 0x00340013, 0x14000000, ftZd_SpecialHi_8013A448,
      ftZd_SpecialHi_8013A4E4, ftZd_SpecialHi_8013A4EC,
      ftZd_SpecialHi_8013A588, ftCamera_UpdateCameraBox },
    { 305, 0x00340413, 0x14000000, ftZd_SpecialHi_801399F0,
      ftZd_SpecialHi_80139A30, ftZd_SpecialHi_80139A54,
      ftZd_SpecialHi_80139AD4, ftCamera_UpdateCameraBox },
    { 305, 0x00340413, 0x14000000, ftZd_SpecialHi_80139C58,
      ftZd_SpecialHi_80139C98, ftZd_SpecialHi_80139CBC,
      ftZd_SpecialHi_80139D60, ftCamera_UpdateCameraBox },
    { 306, 0x00340413, 0x14000000, ftZd_SpecialHi_8013A484,
      ftZd_SpecialHi_8013A4E8, ftZd_SpecialHi_8013A50C,
      ftZd_SpecialHi_8013A5C4, ftCamera_UpdateCameraBox },
    { 307, 0x00340014, 0x15000000, ftZd_SpecialLw_8013B068,
      ftZd_SpecialLw_8013B0E8, ftZd_SpecialLw_8013B0F0,
      ftZd_SpecialLw_8013B154, ftCamera_UpdateCameraBox },
    { 308, 0x00340014, 0x15000000, ftZd_SpecialLw_8013B2A4,
      ftZd_SpecialLw_8013B31C, ftZd_SpecialLw_8013B324,
      ftZd_SpecialLw_8013B388, ftCamera_UpdateCameraBox },
    { 309, 0x00340414, 0x15000000, ftZd_SpecialLw_8013B0A8,
      ftZd_SpecialLw_8013B0EC, ftZd_SpecialLw_8013B110,
      ftZd_SpecialLw_8013B190, ftCamera_UpdateCameraBox },
    { 310, 0x00340414, 0x15000000, ftZd_SpecialLw_8013B2E0,
      ftZd_SpecialLw_8013B320, ftZd_SpecialLw_8013B344,
      ftZd_SpecialLw_8013B3C4, ftCamera_UpdateCameraBox },
};

char ftZd_Init_DatFilename[] = "PlZd.dat";
char ftZd_Init_DataName[] = "ftDataZelda";
char ftZd_Init_803CFCB0[] = "PlZdNr.dat";
char ftZd_Init_803CFCBC[] = "PlyZelda5K_Share_joint";
char ftZd_Init_803CFCD4[] = "PlyZelda5K_Share_matanim_joint";
char ftZd_Init_803CFCF4[] = "PlZdRe.dat";
char ftZd_Init_803CFD00[] = "PlyZelda5KRe_Share_joint";
char ftZd_Init_803CFD1C[] = "PlyZelda5KRe_Share_matanim_joint";
char ftZd_Init_803CFD40[] = "PlZdBu.dat";
char ftZd_Init_803CFD4C[] = "PlyZelda5KBu_Share_joint";
char ftZd_Init_803CFD68[] = "PlyZelda5KBu_Share_matanim_joint";
char ftZd_Init_803CFD8C[] = "PlZdGr.dat";
char ftZd_Init_803CFD98[] = "PlyZelda5KGr_Share_joint";
char ftZd_Init_803CFDB4[] = "PlyZelda5KGr_Share_matanim_joint";
char ftZd_Init_803CFDD8[] = "PlZdWh.dat";
char ftZd_Init_803CFDE4[] = "PlyZelda5KWh_Share_joint";
char ftZd_Init_803CFE00[] = "PlyZelda5KWh_Share_matanim_joint";
char ftZd_Init_AnimDatFilename[] = "PlZdAJ.dat";

Fighter_DemoStrings ftZd_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileZelda",
    "ftDemoIntroMotionFileZelda",
    "ftDemoEndingMotionFileZelda",
    "ftDemoViWaitMotionFileZelda",
};

Fighter_CostumeStrings ftZd_Init_CostumeStrings[] = {
    { ftZd_Init_803CFCB0, ftZd_Init_803CFCBC, ftZd_Init_803CFCD4 },
    { ftZd_Init_803CFCF4, ftZd_Init_803CFD00, ftZd_Init_803CFD1C },
    { ftZd_Init_803CFD40, ftZd_Init_803CFD4C, ftZd_Init_803CFD68 },
    { ftZd_Init_803CFD8C, ftZd_Init_803CFD98, ftZd_Init_803CFDB4 },
    { ftZd_Init_803CFDD8, ftZd_Init_803CFDE4, ftZd_Init_803CFE00 },
};

void ftZd_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    fp->fv.zd.x222C = 0;
}

void ftZd_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftZelda_DatAttrs);

    it_8026B3F8(item_list[0], 0x6CU);
    it_8026B3F8(item_list[1], 0x6DU);
}

void ftZd_Init_801393AC(HSD_GObj* gobj)
{
    ftZd_SpecialLw_8013B5EC(gobj);
}

void ftZd_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftZd_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftZd_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftZd_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftZd_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftZelda_DatAttrs);
}

/// Zelda_RemoveDress
void ftZd_Init_801395C8(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    int result = ftParts_80074A74(gobj, 1);
    if (result == -1) {
        ftParts_80074A4C(gobj, 1, 0);
    } else {
        ftParts_80074A4C(gobj, 1, -1);
    }
}

void ftZd_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftZd_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

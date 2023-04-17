#include "ftZd_Init.h"

#include "ftZd_SpecialHi.h"
#include "ftZd_SpecialLw.h"
#include "ftZd_SpecialN.h"
#include "ftZd_SpecialS.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftZd_Init_MotionStateTable[] = {
    {
        295,
        0x00341011,
        0x12000000,
        ftZd_SpecialN_Anim,
        ftZd_SpecialN_IASA,
        ftZd_SpecialN_Phys,
        ftZd_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        296,
        0x00341411,
        0x12000000,
        ftZd_SpecialAirN_Anim,
        ftZd_SpecialAirN_IASA,
        ftZd_SpecialAirN_Phys,
        ftZd_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        297,
        0x00340112,
        0x13000000,
        ftZd_SpecialSStart_Anim,
        ftZd_SpecialSStart_IASA,
        ftZd_SpecialSStart_Phys,
        ftZd_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        298,
        0x00340112,
        0x13000000,
        ftZd_SpecialSHold_Anim,
        ftZd_SpecialSHold_IASA,
        ftZd_SpecialSHold_Phys,
        ftZd_SpecialSHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        299,
        0x00340112,
        0x13000000,
        ftZd_SpecialSEnd_Anim,
        ftZd_SpecialSEnd_IASA,
        ftZd_SpecialSEnd_Phys,
        ftZd_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        300,
        0x00340512,
        0x13000000,
        ftZd_SpecialAirSStart_Anim,
        ftZd_SpecialAirSStart_IASA,
        ftZd_SpecialAirSStart_Phys,
        ftZd_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        0x00340512,
        0x13000000,
        ftZd_SpecialAirSHold_Anim,
        ftZd_SpecialAirSHold_IASA,
        ftZd_SpecialAirSHold_Phys,
        ftZd_SpecialAirSHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        302,
        0x00340512,
        0x13000000,
        ftZd_SpecialAirSEnd_Anim,
        ftZd_SpecialAirSEnd_IASA,
        ftZd_SpecialAirSEnd_Phys,
        ftZd_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        303,
        0x00340013,
        0x14000000,
        ftZd_SpecialHiStart_Anim,
        ftZd_SpecialHiStart_IASA,
        ftZd_SpecialHiStart_Phys,
        ftZd_SpecialHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        303,
        0x00340013,
        0x14000000,
        ftZd_SpecialHi_Anim,
        ftZd_SpecialHi_IASA,
        ftZd_SpecialHi_Phys,
        ftZd_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        304,
        0x00340013,
        0x14000000,
        ftZd_SpecialHiEnd_Anim,
        ftZd_SpecialHiEnd_IASA,
        ftZd_SpecialHiEnd_Phys,
        ftZd_SpecialHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        305,
        0x00340413,
        0x14000000,
        ftZd_SpecialAirHiStart_Anim,
        ftZd_SpecialAirHiStart_IASA,
        ftZd_SpecialAirHiStart_Phys,
        ftZd_SpecialAirHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        305,
        0x00340413,
        0x14000000,
        ftZd_SpecialAirHi_Anim,
        ftZd_SpecialAirHi_IASA,
        ftZd_SpecialAirHi_Phys,
        ftZd_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        306,
        0x00340413,
        0x14000000,
        ftZd_SpecialAirHiEnd_Anim,
        ftZd_SpecialAirHiEnd_IASA,
        ftZd_SpecialAirHiEnd_Phys,
        ftZd_SpecialAirHiEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        307,
        0x00340014,
        0x15000000,
        ftZd_SpecialLw_Anim,
        ftZd_SpecialLw_IASA,
        ftZd_SpecialLw_Phys,
        ftZd_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        308,
        0x00340014,
        0x15000000,
        ftZd_SpecialLwEnd_Anim,
        ftZd_SpecialLwEnd_IASA,
        ftZd_SpecialLwEnd_Phys,
        ftZd_SpecialLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        0x00340414,
        0x15000000,
        ftZd_SpecialAirLw_Anim,
        ftZd_SpecialAirLw_IASA,
        ftZd_SpecialAirLw_Phys,
        ftZd_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        310,
        0x00340414,
        0x15000000,
        ftZd_SpecialAirLwEnd_Anim,
        ftZd_SpecialAirLwEnd_IASA,
        ftZd_SpecialAirLwEnd_Phys,
        ftZd_SpecialAirLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
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

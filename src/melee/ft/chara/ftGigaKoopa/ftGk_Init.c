#include "it/forward.h"

#include "ftGk_Init.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftKoopa/ftKp_Init.h"

MotionState ftGk_Init_MotionStateTable[] = {
    {
        295,
        0x00340011,
        0x12000000,
        ftKp_SpecialNStart_Anim,
        ftKp_SpecialNStart_IASA,
        ftKp_SpecialNStart_Phys,
        ftKp_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        296,
        0x003C0011,
        0x12000000,
        ftKp_SpecialNLoop_Anim,
        ftKp_SpecialNLoop_IASA,
        ftKp_SpecialNLoop_Phys,
        ftKp_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        297,
        0x00340011,
        0x12000000,
        ftKp_SpecialNEnd_Anim,
        ftKp_SpecialNEnd_IASA,
        ftKp_SpecialNEnd_Phys,
        ftKp_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        298,
        0x00340411,
        0x12000000,
        ftKp_SpecialAirNStart_Anim,
        ftKp_SpecialAirNStart_IASA,
        ftKp_SpecialAirNStart_Phys,
        ftKp_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        299,
        0x003C0411,
        0x12000000,
        ftKp_SpecialAirNLoop_Anim,
        ftKp_SpecialAirNLoop_IASA,
        ftKp_SpecialAirNLoop_Phys,
        ftKp_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        300,
        0x00340411,
        0x12000000,
        ftKp_SpecialAirNEnd_Anim,
        ftKp_SpecialAirNEnd_IASA,
        ftKp_SpecialAirNEnd_Phys,
        ftKp_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        0x00340012,
        0x13000000,
        ftKp_SpecialS_Anim,
        NULL,
        ftKp_SpecialS_Phys,
        ftKp_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        302,
        0x00340012,
        0x13000000,
        ftKp_SpecialSCatch_Anim,
        ftKp_SpecialSCatch_IASA,
        ftKp_SpecialSCatch_Phys,
        ftKp_SpecialSCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        303,
        0x00340012,
        0x13000000,
        ftKp_SpecialSCatch_Anim,
        ftKp_SpecialSCatch_IASA,
        ftKp_SpecialSCatch_Phys,
        ftKp_SpecialSCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        -1,
        0x00340012,
        0x13000000,
        ftKp_SpecialSWait_Anim,
        ftKp_SpecialSWait_IASA,
        ftKp_SpecialSWait_Phys,
        ftKp_SpecialSWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        304,
        0x00340012,
        0x13000000,
        ftKp_SpecialSThrowF_Anim,
        NULL,
        ftKp_SpecialSThrowF_Phys,
        ftKp_SpecialSThrowF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        305,
        0x00340012,
        0x13000000,
        ftKp_SpecialSThrowB_Anim,
        NULL,
        ftKp_SpecialSThrowB_Phys,
        ftKp_SpecialSThrowB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        306,
        0x00340412,
        0x13000000,
        ftKp_SpecialAirS_Anim,
        NULL,
        ftKp_SpecialAirS_Phys,
        ftKp_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        307,
        0x00340412,
        0x13000000,
        ftKp_SpecialAirSCatch_Anim,
        ftKp_SpecialAirSCatch_IASA,
        ftKp_SpecialAirSCatch_Phys,
        ftKp_SpecialAirSCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        308,
        0x00340412,
        0x13000000,
        ftKp_SpecialAirSCatch_Anim,
        ftKp_SpecialAirSCatch_IASA,
        ftKp_SpecialAirSCatch_Phys,
        ftKp_SpecialAirSCatch_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        -1,
        0x00340012,
        0x13000000,
        ftKp_SpecialAirSWait_Anim,
        ftKp_SpecialAirSWait_IASA,
        ftKp_SpecialAirSWait_Phys,
        ftKp_SpecialAirSWait_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        0x00340412,
        0x13000000,
        ftKp_SpecialAirSThrowF_Anim,
        NULL,
        ftKp_SpecialAirSThrowF_Phys,
        ftKp_SpecialAirSThrowF_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        310,
        0x00340412,
        0x13000000,
        ftKp_SpecialAirSThrowB_Anim,
        NULL,
        ftKp_SpecialAirSThrowB_Phys,
        ftKp_SpecialAirSThrowB_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        311,
        0x00340213,
        0x14000000,
        ftKp_SpecialHi_Anim,
        ftKp_SpecialHi_IASA,
        ftKp_SpecialHi_Phys,
        ftKp_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        312,
        0x00340613,
        0x14000000,
        ftKp_SpecialAirHi_Anim,
        ftKp_SpecialAirHi_IASA,
        ftKp_SpecialAirHi_Phys,
        ftKp_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        313,
        0x00340214,
        0x15000000,
        ftKp_SpecialLwStart_Anim,
        NULL,
        ftKp_SpecialLwStart_Phys,
        ftKp_SpecialLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        314,
        0x00340614,
        0x15000000,
        ftKp_SpecialAirLw_Anim,
        NULL,
        ftKp_SpecialAirLw_Phys,
        ftKp_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        315,
        0x00340214,
        0x15000000,
        ftKp_SpecialLwLanding_Anim,
        NULL,
        ftKp_SpecialLwLanding_Phys,
        ftKp_SpecialLwLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
};

MotionState ftGk_Init_UnkMotionStates0[] = {
    { 14, 0, 0x01000000, NULL, NULL, ft_800C74AC, NULL, NULL },
};

char ftGk_Init_DatFilename[] = "PlGk.dat";
char ftGk_Init_DataName[] = "ftDataGkoopa";
char ftGk_Init_803D3904[] = "PlGkNr.dat";
char ftGk_Init_803D3910[] = "PlyGkoopa5K_Share_joint";
char ftGk_Init_803D3928[] = "PlyGkoopa5K_Share_matanim_joint";
char ftGk_Init_AnimDatFilename[] = "PlGkAJ.dat";

Fighter_DemoStrings ftGk_Init_DemoMotionFilenames = { 0 };

char* ftGk_Init_803D3984[] = { "ftDemoVi1201V2MotionFileGkoopa" };

Fighter_CostumeStrings ftGk_Init_CostumeStrings[] = {
    { ftGk_Init_803D3904, ftGk_Init_803D3910, ftGk_Init_803D3928 },
};

void ftGk_Init_OnDeath(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* koopaAttr = fp->x2D4_specialAttributes;

    ftParts_80074A4C(gobj, 0, 0);
    fp->dmg.x18B0 = koopaAttr->x0;
    fp->fv.gk.x222C = koopaAttr->x10;
    fp->fv.gk.x2230 = koopaAttr->x18;
}

void ftGk_Init_UnkMotionStates3(HSD_GObj* gobj)
{
    ftKp_Init_UnkMotionStates3(gobj);
}

void ftGk_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->ft_data;
    void** items = ftdata->x48_items;

    ftKp_Init_OnLoadForGKoopa(fp);
    it_8026B3F8(items[0], It_Kind_Koopa_Flame);

    fp->x2226_flag.bits.b1 = true;
    fp->x222A_flag.bits.b0 = true;
}

void ftGk_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, true, true);
}

void ftGk_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftGk_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftGk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftGk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftKp_Init_LoadSpecialAttrs(gobj);
}

void ftGk_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, true);
}

void ftGk_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, true);
}

void ftGk_Init_UnkDemoCallbacks0(s32 arg0, s32* arg1, s32* arg2)
{
    if (arg0 == 0xF) {
        *arg2 = 0xE;
        *arg1 = 0xE;
    }
}

/// @remarks UB warning: this function may use offset uninitialized
char* ftGk_Init_GetMotionFileString(enum_t arg0)
{
    int offset;

    switch (arg0) {
    case 15:
        offset = 14;
    }

    return ftGk_Init_803D3984[offset - 14];
}

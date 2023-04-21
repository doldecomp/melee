#include "it/forward.h"

#include "ftFc_Init.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftFox/ftFx_Appeal.h"
#include "ftFox/ftFx_Init.h"
#include "ftFox/ftFx_SpecialHi.h"
#include "ftFox/ftFx_SpecialLw.h"
#include "ftFox/ftFx_SpecialN.h"
#include "ftFox/ftFx_SpecialS.h"

MotionState ftFc_Init_MotionStateTable[] = {
    {
        295,
        0x00340111,
        0x12000000,
        ftFx_SpecialNStart_Anim,
        ftFx_SpecialNStart_IASA,
        ftFx_SpecialNStart_Phys,
        ftFx_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        296,
        0x003C0111,
        0x12000000,
        ftFx_SpecialNLoop_Anim,
        ftFx_SpecialNLoop_IASA,
        ftFx_SpecialNLoop_Phys,
        ftFx_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        297,
        0x00340111,
        0x12000000,
        ftFx_SpecialNEnd_Anim,
        ftFx_SpecialNEnd_IASA,
        ftFx_SpecialNEnd_Phys,
        ftFx_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        298,
        0x00340511,
        0x12000000,
        ftFx_SpecialAirNStart_Anim,
        ftFx_SpecialAirNStart_IASA,
        ftFx_SpecialAirNStart_Phys,
        ftFx_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        299,
        0x003C0511,
        0x12000000,
        ftFx_SpecialAirNLoop_Anim,
        ftFx_SpecialAirNLoop_IASA,
        ftFx_SpecialAirNLoop_Phys,
        ftFx_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        300,
        0x00340511,
        0x12000000,
        ftFx_SpecialAirNEnd_Anim,
        ftFx_SpecialAirNEnd_IASA,
        ftFx_SpecialAirNEnd_Phys,
        ftFx_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        0x00340212,
        0x13000000,
        ftFx_SpecialSStart_Anim,
        ftFx_SpecialSStart_IASA,
        ftFx_SpecialSStart_Phys,
        ftFx_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        302,
        0x00340212,
        0x13000000,
        ftFx_SpecialS_Anim,
        ftFx_SpecialS_IASA,
        ftFx_SpecialS_Phys,
        ftFx_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        303,
        0x00340212,
        0x13000000,
        ftFx_SpecialSEnd_Anim,
        ftFx_SpecialSEnd_IASA,
        ftFx_SpecialSEnd_Phys,
        ftFx_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        304,
        0x00340612,
        0x13000000,
        ftFx_SpecialAirSStart_Anim,
        ftFx_SpecialAirSStart_IASA,
        ftFx_SpecialAirSStart_Phys,
        ftFx_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        305,
        0x00340612,
        0x13000000,
        ftFx_SpecialAirS_Anim,
        ftFx_SpecialAirS_IASA,
        ftFx_SpecialAirS_Phys,
        ftFx_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        306,
        0x00340612,
        0x13000000,
        ftFx_SpecialAirSEnd_Anim,
        ftFx_SpecialAirSEnd_IASA,
        ftFx_SpecialAirSEnd_Phys,
        ftFx_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        307,
        0x00340213,
        0x14000000,
        ftFx_SpecialHiHold_Anim,
        ftFx_SpecialHiHold_IASA,
        ftFx_SpecialHiHold_Phys,
        ftFx_SpecialHiHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        308,
        0x00340613,
        0x14000000,
        ftFx_SpecialHiHoldAir_Anim,
        ftFx_SpecialHiHoldAir_IASA,
        ftFx_SpecialHiHoldAir_Phys,
        ftFx_SpecialHiHoldAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        0x00340213,
        0x14000000,
        ftFx_SpecialHi_Anim,
        ftFx_SpecialHi_IASA,
        ftFx_SpecialHi_Phys,
        ftFx_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        0x00340613,
        0x14000000,
        ftFx_SpecialAirHi_Anim,
        ftFx_SpecialAirHi_IASA,
        ftFx_SpecialAirHi_Phys,
        ftFx_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        310,
        0x00340213,
        0x14000000,
        ftFx_SpecialHiLanding_Anim,
        ftFx_SpecialHiLanding_IASA,
        ftFx_SpecialHiLanding_Phys,
        ftFx_SpecialHiLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        311,
        0x00340613,
        0x14000000,
        ftFx_SpecialHiFall_Anim,
        ftFx_SpecialHiFall_IASA,
        ftFx_SpecialHiFall_Phys,
        ftFx_SpecialHiFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        312,
        0x00340613,
        0x14000000,
        ftFx_SpecialHiBound_Anim,
        ftFx_SpecialHiBound_IASA,
        ftFx_SpecialHiBound_Phys,
        ftFx_SpecialHiBound_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        313,
        0x00341014,
        0x15000000,
        ftFx_SpecialLwStart_Anim,
        ftFx_SpecialLwStart_IASA,
        ftFx_SpecialLwStart_Phys,
        ftFx_SpecialLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        314,
        0x00341014,
        0x15000000,
        ftFx_SpecialLwLoop_Anim,
        ftFx_SpecialLwLoop_IASA,
        ftFx_SpecialLwLoop_Phys,
        ftFx_SpecialLwLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        315,
        0x00341014,
        0x15000000,
        ftFx_SpecialLwHit_Anim,
        ftFx_SpecialLwHit_IASA,
        ftFx_SpecialLwHit_Phys,
        ftFx_SpecialLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        316,
        0x00341014,
        0x15000000,
        ftFx_SpecialLwEnd_Anim,
        ftFx_SpecialLwEnd_IASA,
        ftFx_SpecialLwEnd_Phys,
        ftFx_SpecialLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        314,
        0x00341014,
        0x15000000,
        ftFx_SpecialLwTurn_Anim,
        ftFx_SpecialLwTurn_IASA,
        ftFx_SpecialLwTurn_Phys,
        ftFx_SpecialLwTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        317,
        0x00341414,
        0x15000000,
        ftFx_SpecialAirLwStart_Anim,
        ftFx_SpecialAirLwStart_IASA,
        ftFx_SpecialAirLwStart_Phys,
        ftFx_SpecialAirLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        318,
        0x00341414,
        0x15000000,
        ftFx_SpecialAirLwLoop_Anim,
        ftFx_SpecialAirLwLoop_IASA,
        ftFx_SpecialAirLwLoop_Phys,
        ftFx_SpecialAirLwLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        319,
        0x00341414,
        0x15000000,
        ftFx_SpecialAirLwHit_Anim,
        ftFx_SpecialAirLwHit_IASA,
        ftFx_SpecialAirLwHit_Phys,
        ftFx_SpecialAirLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        320,
        0x00341414,
        0x15000000,
        ftFx_SpecialAirLwEnd_Anim,
        ftFx_SpecialAirLwEnd_IASA,
        ftFx_SpecialAirLwEnd_Phys,
        ftFx_SpecialAirLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        318,
        0x00341414,
        0x15000000,
        ftFx_SpecialAirLwTurn_Anim,
        ftFx_SpecialAirLwTurn_IASA,
        ftFx_SpecialAirLwTurn_Phys,
        ftFx_SpecialAirLwTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        321,
        0x00000072,
        0x01000000,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        322,
        0x00000072,
        0x01000000,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        323,
        0x00000072,
        0x01000000,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        324,
        0x00000072,
        0x01000000,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        325,
        0x00000072,
        0x01000000,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        326,
        0x00000072,
        0x01000000,
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftFc_Init_DatFilename[] = "PlFc.dat";
char ftFc_Init_DataName[] = "ftDataFalco";
char ftFc_Init_803D1CC0[] = "PlFcNr.dat";
char ftFc_Init_803D1CCC[] = "PlyFalco5K_Share_joint";
char ftFc_Init_803D1CE4[] = "PlyFalco5K_Share_matanim_joint";
char ftFc_Init_803D1D04[] = "PlFcRe.dat";
char ftFc_Init_803D1D10[] = "PlyFalco5KRe_Share_joint";
char ftFc_Init_803D1D2C[] = "PlyFalco5KRe_Share_matanim_joint";
char ftFc_Init_803D1D50[] = "PlFcBu.dat";
char ftFc_Init_803D1D5C[] = "PlyFalco5KBu_Share_joint";
char ftFc_Init_803D1D78[] = "PlyFalco5KBu_Share_matanim_joint";
char ftFc_Init_803D1D9C[] = "PlFcGr.dat";
char ftFc_Init_803D1DA8[] = "PlyFalco5KGr_Share_joint";
char ftFc_Init_803D1DC4[] = "PlyFalco5KGr_Share_matanim_joint";
char ftFc_Init_AnimDatFilename[] = "PlFcAJ.dat";

Fighter_DemoStrings ftFc_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileFalco",
    "ftDemoIntroMotionFileFalco",
    "ftDemoEndingMotionFileFalco",
    "ftDemoViWaitMotionFileFalco",
};

Fighter_CostumeStrings ftFc_Init_CostumeStrings[] = {
    { ftFc_Init_803D1CC0, ftFc_Init_803D1CCC, ftFc_Init_803D1CE4 },
    { ftFc_Init_803D1D04, ftFc_Init_803D1D10, ftFc_Init_803D1D2C },
    { ftFc_Init_803D1D50, ftFc_Init_803D1D5C, ftFc_Init_803D1D78 },
    { ftFc_Init_803D1D9C, ftFc_Init_803D1DA8, ftFc_Init_803D1DC4 },
};

void ftFc_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->fv.fx.x222C_blasterGObj = 0;
    ftParts_80074A4C(gobj, 0, 0);
}

void ftFc_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftFc_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftFc_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftFc_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftFc_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->ft_data;
    s32* sa2;
    void** items = ftdata->x48_items;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->x2224_flag.bits.b7 = 1;
    ftFx_Init_OnLoadForFalco(fp);

    sa2 = fp->x2D4_specialAttributes;
    it_8026B3F8(items[0], sa2[7]);
    it_8026B3F8(items[1], sa2[8]);
    it_8026B3F8(items[3], 0x39);
}

void ftFc_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftFx_Init_LoadSpecialAttrs(gobj);
}

void ftFc_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void ftFc_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0.0f);
}

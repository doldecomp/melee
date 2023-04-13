#include "ftfalco.h"

#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftFox/ftfox.h"
#include "it/itkind.h"

ActionState ftFalco_MotionStateTable[] = {
    { 295, 0x00340111, 0x12000000, ftFox_SpecialNStart_Anim,
      ftFox_SpecialNStart_IASA, ftFox_SpecialNStart_Phys,
      ftFox_SpecialNStart_Coll, ftCamera_UpdateCameraBox },
    { 296, 0x003C0111, 0x12000000, ftFox_SpecialNLoop_Anim,
      ftFox_SpecialNLoop_IASA, ftFox_SpecialNLoop_Phys,
      ftFox_SpecialNLoop_Coll, ftCamera_UpdateCameraBox },
    { 297, 0x00340111, 0x12000000, ftFox_SpecialNEnd_Anim,
      ftFox_SpecialNEnd_IASA, ftFox_SpecialNEnd_Phys, ftFox_SpecialNEnd_Coll,
      ftCamera_UpdateCameraBox },
    { 298, 0x00340511, 0x12000000, ftFox_SpecialAirNStart_Anim,
      ftFox_SpecialAirNStart_IASA, ftFox_SpecialAirNStart_Phys,
      ftFox_SpecialAirNStart_Coll, ftCamera_UpdateCameraBox },
    { 299, 0x003C0511, 0x12000000, ftFox_SpecialAirNLoop_Anim,
      ftFox_SpecialAirNLoop_IASA, ftFox_SpecialAirNLoop_Phys,
      ftFox_SpecialAirNLoop_Coll, ftCamera_UpdateCameraBox },
    { 300, 0x00340511, 0x12000000, ftFox_SpecialAirNEnd_Anim,
      ftFox_SpecialAirNEnd_IASA, ftFox_SpecialAirNEnd_Phys,
      ftFox_SpecialAirNEnd_Coll, ftCamera_UpdateCameraBox },
    { 301, 0x00340212, 0x13000000, ftFox_SpecialSStart_Anim,
      ftFox_SpecialSStart_IASA, ftFox_SpecialSStart_Phys,
      ftFox_SpecialSStart_Coll, ftCamera_UpdateCameraBox },
    { 302, 0x00340212, 0x13000000, ftFox_SpecialS_Anim, ftFox_SpecialS_IASA,
      ftFox_SpecialS_Phys, ftFox_SpecialS_Coll, ftCamera_UpdateCameraBox },
    { 303, 0x00340212, 0x13000000, ftFox_SpecialSEnd_Anim,
      ftFox_SpecialSEnd_IASA, ftFox_SpecialSEnd_Phys, ftFox_SpecialSEnd_Coll,
      ftCamera_UpdateCameraBox },
    { 304, 0x00340612, 0x13000000, ftFox_SpecialAirSStart_Anim,
      ftFox_SpecialAirSStart_IASA, ftFox_SpecialAirSStart_Phys,
      ftFox_SpecialAirSStart_Coll, ftCamera_UpdateCameraBox },
    { 305, 0x00340612, 0x13000000, ftFox_SpecialAirS_Anim,
      ftFox_SpecialAirS_IASA, ftFox_SpecialAirS_Phys, ftFox_SpecialAirS_Coll,
      ftCamera_UpdateCameraBox },
    { 306, 0x00340612, 0x13000000, ftFox_SpecialAirSEnd_Anim,
      ftFox_SpecialAirSEnd_IASA, ftFox_SpecialAirSEnd_Phys,
      ftFox_SpecialAirSEnd_Coll, ftCamera_UpdateCameraBox },
    { 307, 0x00340213, 0x14000000, ftFox_SpecialHiHold_Anim,
      ftFox_SpecialHiHold_IASA, ftFox_SpecialHiHold_Phys,
      ftFox_SpecialHiHold_Coll, ftCamera_UpdateCameraBox },
    { 308, 0x00340613, 0x14000000, ftFox_SpecialHiHoldAir_Anim,
      ftFox_SpecialHiHoldAir_IASA, ftFox_SpecialHiHoldAir_Phys,
      ftFox_SpecialHiHoldAir_Coll, ftCamera_UpdateCameraBox },
    { 309, 0x00340213, 0x14000000, ftFox_SpecialHi_Anim, ftFox_SpecialHi_IASA,
      ftFox_SpecialHi_Phys, ftFox_SpecialHi_Coll, ftCamera_UpdateCameraBox },
    { 309, 0x00340613, 0x14000000, ftFox_SpecialAirHi_Anim,
      ftFox_SpecialAirHi_IASA, ftFox_SpecialAirHi_Phys,
      ftFox_SpecialAirHi_Coll, ftCamera_UpdateCameraBox },
    { 310, 0x00340213, 0x14000000, ftFox_SpecialHiLanding_Anim,
      ftFox_SpecialHiLanding_IASA, ftFox_SpecialHiLanding_Phys,
      ftFox_SpecialHiLanding_Coll, ftCamera_UpdateCameraBox },
    { 311, 0x00340613, 0x14000000, ftFox_SpecialHiFall_Anim,
      ftFox_SpecialHiFall_IASA, ftFox_SpecialHiFall_Phys,
      ftFox_SpecialHiFall_Coll, ftCamera_UpdateCameraBox },
    { 312, 0x00340613, 0x14000000, ftFox_SpecialHiBound_Anim,
      ftFox_SpecialHiBound_IASA, ftFox_SpecialHiBound_Phys,
      ftFox_SpecialHiBound_Coll, ftCamera_UpdateCameraBox },
    { 313, 0x00341014, 0x15000000, ftFox_SpecialLwStart_Anim,
      ftFox_SpecialLwStart_IASA, ftFox_SpecialLwStart_Phys,
      ftFox_SpecialLwStart_Coll, ftCamera_UpdateCameraBox },
    { 314, 0x00341014, 0x15000000, ftFox_SpecialLwLoop_Anim,
      ftFox_SpecialLwLoop_IASA, ftFox_SpecialLwLoop_Phys,
      ftFox_SpecialLwLoop_Coll, ftCamera_UpdateCameraBox },
    { 315, 0x00341014, 0x15000000, ftFox_SpecialLwHit_Anim,
      ftFox_SpecialLwHit_IASA, ftFox_SpecialLwHit_Phys,
      ftFox_SpecialLwHit_Coll, ftCamera_UpdateCameraBox },
    { 316, 0x00341014, 0x15000000, ftFox_SpecialLwEnd_Anim,
      ftFox_SpecialLwEnd_IASA, ftFox_SpecialLwEnd_Phys,
      ftFox_SpecialLwEnd_Coll, ftCamera_UpdateCameraBox },
    { 314, 0x00341014, 0x15000000, ftFox_SpecialLwTurn_Anim,
      ftFox_SpecialLwTurn_IASA, ftFox_SpecialLwTurn_Phys,
      ftFox_SpecialLwTurn_Coll, ftCamera_UpdateCameraBox },
    { 317, 0x00341414, 0x15000000, ftFox_SpecialAirLwStart_Anim,
      ftFox_SpecialAirLwStart_IASA, ftFox_SpecialAirLwStart_Phys,
      ftFox_SpecialAirLwStart_Coll, ftCamera_UpdateCameraBox },
    { 318, 0x00341414, 0x15000000, ftFox_SpecialAirLwLoop_Anim,
      ftFox_SpecialAirLwLoop_IASA, ftFox_SpecialAirLwLoop_Phys,
      ftFox_SpecialAirLwLoop_Coll, ftCamera_UpdateCameraBox },
    { 319, 0x00341414, 0x15000000, ftFox_SpecialAirLwHit_Anim,
      ftFox_SpecialAirLwHit_IASA, ftFox_SpecialAirLwHit_Phys,
      ftFox_SpecialAirLwHit_Coll, ftCamera_UpdateCameraBox },
    { 320, 0x00341414, 0x15000000, ftFox_SpecialAirLwEnd_Anim,
      ftFox_SpecialAirLwEnd_IASA, ftFox_SpecialAirLwEnd_Phys,
      ftFox_SpecialAirLwEnd_Coll, ftCamera_UpdateCameraBox },
    { 318, 0x00341414, 0x15000000, ftFox_SpecialAirLwTurn_Anim,
      ftFox_SpecialAirLwTurn_IASA, ftFox_SpecialAirLwTurn_Phys,
      ftFox_SpecialAirLwTurn_Coll, ftCamera_UpdateCameraBox },
    { 321, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, ftCamera_UpdateCameraBox },
    { 322, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, ftCamera_UpdateCameraBox },
    { 323, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, ftCamera_UpdateCameraBox },
    { 324, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, ftCamera_UpdateCameraBox },
    { 325, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, ftCamera_UpdateCameraBox },
    { 326, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, ftCamera_UpdateCameraBox },
};

char lbl_803D1CA8[] = "PlFc.dat";
char lbl_803D1CB4[] = "ftDataFalco";
char lbl_803D1CC0[] = "PlFcNr.dat";
char lbl_803D1CCC[] = "PlyFalco5K_Share_joint";
char lbl_803D1CE4[] = "PlyFalco5K_Share_matanim_joint";
char lbl_803D1D04[] = "PlFcRe.dat";
char lbl_803D1D10[] = "PlyFalco5KRe_Share_joint";
char lbl_803D1D2C[] = "PlyFalco5KRe_Share_matanim_joint";
char lbl_803D1D50[] = "PlFcBu.dat";
char lbl_803D1D5C[] = "PlyFalco5KBu_Share_joint";
char lbl_803D1D78[] = "PlyFalco5KBu_Share_matanim_joint";
char lbl_803D1D9C[] = "PlFcGr.dat";
char lbl_803D1DA8[] = "PlyFalco5KGr_Share_joint";
char lbl_803D1DC4[] = "PlyFalco5KGr_Share_matanim_joint";
char lbl_803D1DE8[] = "PlFcAJ.dat";

Fighter_DemoStrings lbl_803D1E64 = {
    "ftDemoResultMotionFileFalco",
    "ftDemoIntroMotionFileFalco",
    "ftDemoEndingMotionFileFalco",
    "ftDemoViWaitMotionFileFalco",
};

Fighter_CostumeStrings lbl_803D1E74[] = {
    { lbl_803D1CC0, lbl_803D1CCC, lbl_803D1CE4 },
    { lbl_803D1D04, lbl_803D1D10, lbl_803D1D2C },
    { lbl_803D1D50, lbl_803D1D5C, lbl_803D1D78 },
    { lbl_803D1D9C, lbl_803D1DA8, lbl_803D1DC4 },
};

void ftFalco_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->ev.fx.x222C_blasterGObj = 0;
    ftParts_80074A4C(gobj, 0, 0);
}

void ftFalco_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftFalco_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftFalco_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftFalco_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftFalco_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->x10C_ftData;
    s32* sa2;
    void** items = ftdata->x48_items;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->x2224_flag.bits.b7 = 1;
    ftFox_OnLoadForFalco(fp);

    sa2 = fp->x2D4_specialAttributes;
    it_8026B3F8(items[0], sa2[7]);
    it_8026B3F8(items[1], sa2[8]);
    it_8026B3F8(items[3], 0x39);
}

void ftFalco_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftFox_LoadSpecialAttrs(gobj);
}

void ftFalco_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void ftFalco_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0.0f);
}

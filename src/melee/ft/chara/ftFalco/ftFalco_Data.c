#include <melee/ft/chara/ftFalco/ftfalco.h>
#include <melee/ft/chara/ftFox/ftfox.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_falco[] = {
    { 295, 0x00340111, 0x12000000, ftFox_SpecialNStart_Anim,
      ftFox_SpecialNStart_IASA, ftFox_SpecialNStart_Phys,
      ftFox_SpecialNStart_Coll, func_800761C8 },
    { 296, 0x003C0111, 0x12000000, ftFox_SpecialNLoop_Anim,
      ftFox_SpecialNLoop_IASA, ftFox_SpecialNLoop_Phys, ftFox_SpecialNLoop_Coll,
      func_800761C8 },
    { 297, 0x00340111, 0x12000000, ftFox_SpecialNEnd_Anim,
      ftFox_SpecialNEnd_IASA, ftFox_SpecialNEnd_Phys, ftFox_SpecialNEnd_Coll,
      func_800761C8 },
    { 298, 0x00340511, 0x12000000, ftFox_SpecialAirNStart_Anim,
      ftFox_SpecialAirNStart_IASA, ftFox_SpecialAirNStart_Phys,
      ftFox_SpecialAirNStart_Coll, func_800761C8 },
    { 299, 0x003C0511, 0x12000000, ftFox_SpecialAirNLoop_Anim,
      ftFox_SpecialAirNLoop_IASA, ftFox_SpecialAirNLoop_Phys,
      ftFox_SpecialAirNLoop_Coll, func_800761C8 },
    { 300, 0x00340511, 0x12000000, ftFox_SpecialAirNEnd_Anim,
      ftFox_SpecialAirNEnd_IASA, ftFox_SpecialAirNEnd_Phys,
      ftFox_SpecialAirNEnd_Coll, func_800761C8 },
    { 301, 0x00340212, 0x13000000, ftFox_SpecialSStart_Anim,
      ftFox_SpecialSStart_IASA, ftFox_SpecialSStart_Phys,
      ftFox_SpecialSStart_Coll, func_800761C8 },
    { 302, 0x00340212, 0x13000000, ftFox_SpecialS_Anim, ftFox_SpecialS_IASA,
      ftFox_SpecialS_Phys, ftFox_SpecialS_Coll, func_800761C8 },
    { 303, 0x00340212, 0x13000000, ftFox_SpecialSEnd_Anim,
      ftFox_SpecialSEnd_IASA, ftFox_SpecialSEnd_Phys, ftFox_SpecialSEnd_Coll,
      func_800761C8 },
    { 304, 0x00340612, 0x13000000, ftFox_SpecialAirSStart_Anim,
      ftFox_SpecialAirSStart_IASA, ftFox_SpecialAirSStart_Phys,
      ftFox_SpecialAirSStart_Coll, func_800761C8 },
    { 305, 0x00340612, 0x13000000, ftFox_SpecialAirS_Anim,
      ftFox_SpecialAirS_IASA, ftFox_SpecialAirS_Phys, ftFox_SpecialAirS_Coll,
      func_800761C8 },
    { 306, 0x00340612, 0x13000000, ftFox_SpecialAirSEnd_Anim,
      ftFox_SpecialAirSEnd_IASA, ftFox_SpecialAirSEnd_Phys,
      ftFox_SpecialAirSEnd_Coll, func_800761C8 },
    { 307, 0x00340213, 0x14000000, ftFox_SpecialHiHold_Anim,
      ftFox_SpecialHiHold_IASA, ftFox_SpecialHiHold_Phys,
      ftFox_SpecialHiHold_Coll, func_800761C8 },
    { 308, 0x00340613, 0x14000000, ftFox_SpecialHiHoldAir_Anim,
      ftFox_SpecialHiHoldAir_IASA, ftFox_SpecialHiHoldAir_Phys,
      ftFox_SpecialHiHoldAir_Coll, func_800761C8 },
    { 309, 0x00340213, 0x14000000, ftFox_SpecialHi_Anim, ftFox_SpecialHi_IASA,
      ftFox_SpecialHi_Phys, ftFox_SpecialHi_Coll, func_800761C8 },
    { 309, 0x00340613, 0x14000000, ftFox_SpecialAirHi_Anim,
      ftFox_SpecialAirHi_IASA, ftFox_SpecialAirHi_Phys, ftFox_SpecialAirHi_Coll,
      func_800761C8 },
    { 310, 0x00340213, 0x14000000, ftFox_SpecialHiLanding_Anim,
      ftFox_SpecialHiLanding_IASA, ftFox_SpecialHiLanding_Phys,
      ftFox_SpecialHiLanding_Coll, func_800761C8 },
    { 311, 0x00340613, 0x14000000, ftFox_SpecialHiFall_Anim,
      ftFox_SpecialHiFall_IASA, ftFox_SpecialHiFall_Phys,
      ftFox_SpecialHiFall_Coll, func_800761C8 },
    { 312, 0x00340613, 0x14000000, ftFox_SpecialHiBound_Anim,
      ftFox_SpecialHiBound_IASA, ftFox_SpecialHiBound_Phys,
      ftFox_SpecialHiBound_Coll, func_800761C8 },
    { 313, 0x00341014, 0x15000000, ftFox_SpecialLwStart_Anim,
      ftFox_SpecialLwStart_IASA, ftFox_SpecialLwStart_Phys,
      ftFox_SpecialLwStart_Coll, func_800761C8 },
    { 314, 0x00341014, 0x15000000, ftFox_SpecialLwLoop_Anim,
      ftFox_SpecialLwLoop_IASA, ftFox_SpecialLwLoop_Phys,
      ftFox_SpecialLwLoop_Coll, func_800761C8 },
    { 315, 0x00341014, 0x15000000, ftFox_SpecialLwHit_Anim,
      ftFox_SpecialLwHit_IASA, ftFox_SpecialLwHit_Phys, ftFox_SpecialLwHit_Coll,
      func_800761C8 },
    { 316, 0x00341014, 0x15000000, ftFox_SpecialLwEnd_Anim,
      ftFox_SpecialLwEnd_IASA, ftFox_SpecialLwEnd_Phys, ftFox_SpecialLwEnd_Coll,
      func_800761C8 },
    { 314, 0x00341014, 0x15000000, ftFox_SpecialLwTurn_Anim,
      ftFox_SpecialLwTurn_IASA, ftFox_SpecialLwTurn_Phys,
      ftFox_SpecialLwTurn_Coll, func_800761C8 },
    { 317, 0x00341414, 0x15000000, ftFox_SpecialAirLwStart_Anim,
      ftFox_SpecialAirLwStart_IASA, ftFox_SpecialAirLwStart_Phys,
      ftFox_SpecialAirLwStart_Coll, func_800761C8 },
    { 318, 0x00341414, 0x15000000, ftFox_SpecialAirLwLoop_Anim,
      ftFox_SpecialAirLwLoop_IASA, ftFox_SpecialAirLwLoop_Phys,
      ftFox_SpecialAirLwLoop_Coll, func_800761C8 },
    { 319, 0x00341414, 0x15000000, ftFox_SpecialAirLwHit_Anim,
      ftFox_SpecialAirLwHit_IASA, ftFox_SpecialAirLwHit_Phys,
      ftFox_SpecialAirLwHit_Coll, func_800761C8 },
    { 320, 0x00341414, 0x15000000, ftFox_SpecialAirLwEnd_Anim,
      ftFox_SpecialAirLwEnd_IASA, ftFox_SpecialAirLwEnd_Phys,
      ftFox_SpecialAirLwEnd_Coll, func_800761C8 },
    { 318, 0x00341414, 0x15000000, ftFox_SpecialAirLwTurn_Anim,
      ftFox_SpecialAirLwTurn_IASA, ftFox_SpecialAirLwTurn_Phys,
      ftFox_SpecialAirLwTurn_Coll, func_800761C8 },
    { 321, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, func_800761C8 },
    { 322, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, func_800761C8 },
    { 323, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, func_800761C8 },
    { 324, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, func_800761C8 },
    { 325, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, func_800761C8 },
    { 326, 0x00000072, 0x01000000, ftFox_AppealS_Anim, ftFox_AppealS_IASA,
      ftFox_AppealS_Phys, ftFox_AppealS_Coll, func_800761C8 },
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

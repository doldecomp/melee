#include <melee/ft/chara/ftPurin/ftpurin.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_purin[] = {
    { 295, FLAGS_ZERO, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 296, FLAGS_ZERO, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 297, FLAGS_ZERO, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 298, FLAGS_ZERO, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 299, FLAGS_ZERO, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 300, 0x00340211, 0x12000000, lbl_8013E014, lbl_8013FF00, lbl_80140620,
      lbl_80140FA4, func_800761C8 },
    { 301, 0x00340211, 0x12000000, lbl_8013E014, lbl_8013FF00, lbl_80140620,
      lbl_80140FA4, func_800761C8 },
    { 302, 0x003C0211, 0x12000000, lbl_8013E0F0, lbl_8013FF04, lbl_80140650,
      lbl_80141054, func_800761C8 },
    { 303, 0x003C0211, 0x12000000, lbl_8013E2A0, lbl_80140064, lbl_80140680,
      lbl_80141154, func_800761C8 },
    { 304, 0x00340211, 0x12000000, lbl_8013E410, lbl_801401C4, lbl_801406B0,
      lbl_80141254, func_800761C8 },
    { 305, 0x00340211, 0x12000000, lbl_8013E7E0, lbl_80140344, lbl_801408B8,
      lbl_801415F4, func_800761C8 },
    { 306, 0x00340211, 0x12000000, lbl_8013EAD8, lbl_80140348, lbl_80140BAC,
      lbl_801416D0, func_800761C8 },
    { 307, 0x00340211, 0x12000000, lbl_8013EAD8, lbl_80140348, lbl_80140BAC,
      lbl_801416D0, func_800761C8 },
    { 308, 0x00340611, 0x12000000, lbl_8013EDB0, lbl_8014034C, lbl_80140BE8,
      lbl_80141730, func_800761C8 },
    { 309, 0x00340611, 0x12000000, lbl_8013EDB0, lbl_8014034C, lbl_80140BE8,
      lbl_80141730, func_800761C8 },
    { 310, 0x003C0611, 0x12000000, lbl_8013EE84, lbl_80140350, lbl_80140C18,
      lbl_801417E0, func_800761C8 },
    { 311, 0x003C0611, 0x12000000, lbl_8013F034, lbl_801404B0, lbl_80140C48,
      lbl_801418E0, func_800761C8 },
    { 312, 0x00340611, 0x12000000, lbl_8013F1A4, lbl_80140610, lbl_80140C78,
      lbl_801419E0, func_800761C8 },
    { 313, 0x00340211, 0x12000000, lbl_8013F708, lbl_80140614, lbl_80140DF8,
      lbl_80141FB8, func_800761C8 },
    { 314, 0x00340611, 0x12000000, lbl_8013F9C0, lbl_80140618, lbl_80140F10,
      lbl_80142070, func_800761C8 },
    { 315, 0x00340611, 0x12000000, lbl_8013F9C0, lbl_80140618, lbl_80140F10,
      lbl_80142070, func_800761C8 },
    { 316, 0x00340611, 0x12000000, lbl_8013FCAC, lbl_8014061C, lbl_80140F40,
      lbl_801420D0, func_800761C8 },
    { 317, 0x00340212, 0x13000000, lbl_8013D30C, lbl_8013D384, lbl_8013D38C,
      lbl_8013D518, func_800761C8 },
    { 318, 0x00340612, 0x13000000, lbl_8013D348, lbl_8013D388, lbl_8013D3AC,
      lbl_8013D554, func_800761C8 },
    { 319, 0x00340013, 0x14000000, lbl_8013CB68, lbl_8013CC60, lbl_8013CC68,
      lbl_8013CCA8, func_800761C8 },
    { 320, 0x00340413, 0x14000000, lbl_8013CBE4, lbl_8013CC64, lbl_8013CC88,
      lbl_8013CCE4, func_800761C8 },
    { 321, 0x00340013, 0x14000000, lbl_8013CB68, lbl_8013CC60, lbl_8013CC68,
      lbl_8013CCA8, func_800761C8 },
    { 322, 0x00340413, 0x14000000, lbl_8013CBE4, lbl_8013CC64, lbl_8013CC88,
      lbl_8013CCE4, func_800761C8 },
    { 323, 0x00340014, 0x15000000, lbl_8013CFCC, lbl_8013D044, lbl_8013D04C,
      lbl_8013D08C, func_800761C8 },
    { 324, 0x00340414, 0x15000000, lbl_8013D008, lbl_8013D048, lbl_8013D06C,
      lbl_8013D0C8, func_800761C8 },
    { 325, 0x00340014, 0x15000000, lbl_8013CFCC, lbl_8013D044, lbl_8013D04C,
      lbl_8013D08C, func_800761C8 },
    { 326, 0x00340414, 0x15000000, lbl_8013D008, lbl_8013D048, lbl_8013D06C,
      lbl_8013D0C8, func_800761C8 },
};

char lbl_803D02F0[] = "PlPr.dat";
char lbl_803D02FC[] = "ftDataPurin";
char lbl_803D0308[] = "PlPrNr.dat";
char lbl_803D0314[] = "PlyPurin5K_Share_joint";
char lbl_803D032C[] = "PlyPurin5K_Share_matanim_joint";
char lbl_803D034C[] = "PlPrRe.dat";
char lbl_803D0358[] = "PlyPurin5KRe_Share_joint";
char lbl_803D0374[] = "PlyPurin5KRe_Share_matanim_joint";
char lbl_803D0398[] = "PlPrBu.dat";
char lbl_803D03A4[] = "PlyPurin5KBu_Share_joint";
char lbl_803D03C0[] = "PlyPurin5KBu_Share_matanim_joint";
char lbl_803D03E4[] = "PlPrGr.dat";
char lbl_803D03F0[] = "PlyPurin5KGr_Share_joint";
char lbl_803D040C[] = "PlyPurin5KGr_Share_matanim_joint";
char lbl_803D0430[] = "PlPrYe.dat";
char lbl_803D043C[] = "PlyPurin5KYe_Share_joint";
char lbl_803D0458[] = "PlyPurin5KYe_Share_matanim_joint";
char lbl_803D047C[] = "PlPrAJ.dat";
char lbl_803D0488[] = "ftDemoResultMotionFilePurin";
char lbl_803D04A4[] = "ftDemoIntroMotionFilePurin";
char lbl_803D04C0[] = "ftDemoEndingMotionFilePurin";
char lbl_803D04DC[] = "ftDemoViWaitMotionFilePurin";

Fighter_DemoStrings lbl_803D04F8 = {
    lbl_803D0488,
    lbl_803D04A4,
    lbl_803D04C0,
    lbl_803D04DC,
};

Fighter_CostumeStrings lbl_803D0508[] = {
    { lbl_803D0308, lbl_803D0314, lbl_803D032C },
    { lbl_803D034C, lbl_803D0358, lbl_803D0374 },
    { lbl_803D0398, lbl_803D03A4, lbl_803D03C0 },
    { lbl_803D03E4, lbl_803D03F0, lbl_803D040C },
    { lbl_803D0430, lbl_803D043C, lbl_803D0458 },
};

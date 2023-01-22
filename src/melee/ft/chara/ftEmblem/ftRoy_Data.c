#include <melee/ft/chara/ftMars/ftMars.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_roy[] = {
    { 295, 0x00340211, 0x12000000, lbl_80136844, lbl_80136914, lbl_8013691C,
      lbl_801369A4, func_800761C8 },
    { 296, 0x00340211, 0x12000000, lbl_80136ADC, lbl_80136C8C, lbl_80136CFC,
      lbl_80136D3C, func_800761C8 },
    { 297, 0x00340211, 0x12000000, lbl_80136EE4, lbl_8013713C, lbl_80137144,
      lbl_80137184, func_800761C8 },
    { 298, 0x00340211, 0x12000000, lbl_80136EE4, lbl_8013713C, lbl_80137144,
      lbl_80137184, func_800761C8 },
    { 299, 0x00340611, 0x12000000, lbl_801368AC, lbl_80136918, lbl_8013695C,
      lbl_801369E0, func_800761C8 },
    { 300, 0x00340611, 0x12000000, lbl_80136BB4, lbl_80136CC4, lbl_80136D1C,
      lbl_80136D78, func_800761C8 },
    { 301, 0x00340611, 0x12000000, lbl_80137010, lbl_80137140, lbl_80137164,
      lbl_801371C0, func_800761C8 },
    { 302, 0x00340611, 0x12000000, lbl_80137010, lbl_80137140, lbl_80137164,
      lbl_801371C0, func_800761C8 },
    { 303, 0x00340212, 0x13000000, lbl_80137558, lbl_801375B8, lbl_80137618,
      lbl_8013767C, func_800761C8 },
    { 304, 0x00340212, 0x13000000, lbl_801377B0, lbl_80137810, lbl_80137870,
      lbl_801378D4, func_800761C8 },
    { 305, 0x00340212, 0x13000000, lbl_801377B0, lbl_80137810, lbl_80137870,
      lbl_801378D4, func_800761C8 },
    { 306, 0x00340212, 0x13000000, lbl_80137B34, lbl_80137B94, lbl_80137BF4,
      lbl_80137C50, func_800761C8 },
    { 307, 0x00340212, 0x13000000, lbl_80137B34, lbl_80137B94, lbl_80137BF4,
      lbl_80137C50, func_800761C8 },
    { 308, 0x00340212, 0x13000000, lbl_80137B34, lbl_80137B94, lbl_80137BF4,
      lbl_80137C50, func_800761C8 },
    { 309, 0x00340212, 0x13000000, lbl_80137ECC, lbl_80137F2C, lbl_80137F30,
      lbl_80137F8C, func_800761C8 },
    { 310, 0x00340212, 0x13000000, lbl_80137ECC, lbl_80137F2C, lbl_80137F30,
      lbl_80137F8C, func_800761C8 },
    { 311, 0x00340212, 0x13000000, lbl_80137ECC, lbl_80137F2C, lbl_80137F30,
      lbl_80137F8C, func_800761C8 },
    { 312, 0x00340612, 0x13000000, lbl_80137558, lbl_801375B8, lbl_80137618,
      lbl_8013767C, func_800761C8 },
    { 313, 0x00340612, 0x13000000, lbl_801377B0, lbl_80137810, lbl_80137870,
      lbl_801378D4, func_800761C8 },
    { 314, 0x00340612, 0x13000000, lbl_801377B0, lbl_80137810, lbl_80137870,
      lbl_801378D4, func_800761C8 },
    { 315, 0x00340612, 0x13000000, lbl_80137B34, lbl_80137B94, lbl_80137BF4,
      lbl_80137C50, func_800761C8 },
    { 316, 0x00340612, 0x13000000, lbl_80137B34, lbl_80137B94, lbl_80137BF4,
      lbl_80137C50, func_800761C8 },
    { 317, 0x00340612, 0x13000000, lbl_80137B34, lbl_80137B94, lbl_80137BF4,
      lbl_80137C50, func_800761C8 },
    { 318, 0x00340612, 0x13000000, lbl_80137ECC, lbl_80137F2C, lbl_80137F30,
      lbl_80137F8C, func_800761C8 },
    { 319, 0x00340612, 0x13000000, lbl_80137ECC, lbl_80137F2C, lbl_80137F30,
      lbl_80137F8C, func_800761C8 },
    { 320, 0x00340612, 0x13000000, lbl_80137ECC, lbl_80137F2C, lbl_80137F30,
      lbl_80137F8C, func_800761C8 },
    { 321, 0x00340213, 0x14000000, lbl_801382E8, lbl_801383A8, lbl_80138638,
      lbl_801388B4, func_800761C8 },
    { 322, 0x00340613, 0x14000000, lbl_80138348, lbl_801384F0, lbl_8013873C,
      lbl_80138940, func_800761C8 },
    { 323, 0x00340214, 0x15000000, lbl_80138AA8, lbl_80138C20, lbl_80138C28,
      lbl_80138CC0, func_800761C8 },
    { 324, 0x00340214, 0x15000000, lbl_80138E68, lbl_80138FC0, lbl_80138FC8,
      lbl_80139008, func_800761C8 },
    { 325, 0x00340614, 0x15000000, lbl_80138B64, lbl_80138C24, lbl_80138C5C,
      lbl_80138CFC, func_800761C8 },
    { 326, 0x00340614, 0x15000000, lbl_80138F14, lbl_80138FC4, lbl_80138FE8,
      lbl_80139044, func_800761C8 },
};

char lbl_803D3280[] = "PlFe.dat";
char lbl_803D328C[] = "ftDataEmblem";
char lbl_803D329C[] = "PlFeNr.dat";
char lbl_803D32A8[] = "PlyEmblem5K_Share_joint";
char lbl_803D32C0[] = "PlyEmblem5K_Share_matanim_joint";
char lbl_803D32E0[] = "PlFeRe.dat";
char lbl_803D32EC[] = "PlyEmblem5KRe_Share_joint";
char lbl_803D3308[] = "PlyEmblem5KRe_Share_matanim_joint";
char lbl_803D332C[] = "PlFeBu.dat";
char lbl_803D3338[] = "PlyEmblem5KBu_Share_joint";
char lbl_803D3354[] = "PlyEmblem5KBu_Share_matanim_joint";
char lbl_803D3378[] = "PlFeGr.dat";
char lbl_803D3384[] = "PlyEmblem5KGr_Share_joint";
char lbl_803D33A0[] = "PlyEmblem5KGr_Share_matanim_joint";
char lbl_803D33C4[] = "PlFeYe.dat";
char lbl_803D33D0[] = "PlyEmblem5KYe_Share_joint";
char lbl_803D33EC[] = "PlyEmblem5KYe_Share_matanim_joint";
char lbl_803D3410[] = "PlFeAJ.dat";
char lbl_803D341C[] = "ftDemoResultMotionFileEmblem";
char lbl_803D343C[] = "ftDemoIntroMotionFileEmblem";
char lbl_803D3458[] = "ftDemoEndingMotionFileEmblem";
char lbl_803D3478[] = "ftDemoViWaitMotionFileEmblem";

Fighter_DemoStrings lbl_803D3498 = {
    lbl_803D341C,
    lbl_803D343C,
    lbl_803D3458,
    lbl_803D3478,
};

Fighter_CostumeStrings lbl_803D34A8[] = {
    { lbl_803D329C, lbl_803D32A8, lbl_803D32C0 },
    { lbl_803D32E0, lbl_803D32EC, lbl_803D3308 },
    { lbl_803D332C, lbl_803D3338, lbl_803D3354 },
    { lbl_803D3378, lbl_803D3384, lbl_803D33A0 },
    { lbl_803D33C4, lbl_803D33D0, lbl_803D33EC },
};

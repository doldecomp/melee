#include <melee/ft/chara/ftZelda/ftzelda.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_zelda[] = {
    { 295, 0x00341011, 0x12000000, ftZelda_8013AA38, ftZelda_8013AB60,
      ftZelda_8013AB68, ftZelda_8013AC10, func_800761C8 },
    { 296, 0x00341411, 0x12000000, ftZelda_8013AACC, ftZelda_8013AB64,
      ftZelda_8013AB9C, ftZelda_8013AC4C, func_800761C8 },
    { 297, 0x00340112, 0x13000000, ftZelda_8013B780, ftZelda_8013BDD0,
      ftZelda_8013BED8, ftZelda_8013C070, func_800761C8 },
    { 298, 0x00340112, 0x13000000, ftZelda_8013B89C, ftZelda_8013BDD4,
      ftZelda_8013BF10, ftZelda_8013C0DC, func_800761C8 },
    { 299, 0x00340112, 0x13000000, ftZelda_8013BA04, ftZelda_8013BE50,
      ftZelda_8013BF30, ftZelda_8013C148, func_800761C8 },
    { 300, 0x00340512, 0x13000000, ftZelda_8013BA8C, ftZelda_8013BE54,
      ftZelda_8013BF50, ftZelda_8013C1B4, func_800761C8 },
    { 301, 0x00340512, 0x13000000, ftZelda_8013BBA8, ftZelda_8013BE58,
      ftZelda_8013BFB0, ftZelda_8013C220, func_800761C8 },
    { 302, 0x00340512, 0x13000000, ftZelda_8013BD10, ftZelda_8013BED4,
      ftZelda_8013C010, ftZelda_8013C28C, func_800761C8 },
    { 303, 0x00340013, 0x14000000, ftZelda_801399B4, ftZelda_80139A2C,
      ftZelda_80139A34, ftZelda_80139A98, func_800761C8 },
    { 303, 0x00340013, 0x14000000, ftZelda_80139C1C, ftZelda_80139C94,
      ftZelda_80139C9C, ftZelda_80139CC0, func_800761C8 },
    { 304, 0x00340013, 0x14000000, ftZelda_8013A448, ftZelda_8013A4E4,
      ftZelda_8013A4EC, ftZelda_8013A588, func_800761C8 },
    { 305, 0x00340413, 0x14000000, ftZelda_801399F0, ftZelda_80139A30,
      ftZelda_80139A54, ftZelda_80139AD4, func_800761C8 },
    { 305, 0x00340413, 0x14000000, ftZelda_80139C58, ftZelda_80139C98,
      ftZelda_80139CBC, ftZelda_80139D60, func_800761C8 },
    { 306, 0x00340413, 0x14000000, ftZelda_8013A484, ftZelda_8013A4E8,
      ftZelda_8013A50C, ftZelda_8013A5C4, func_800761C8 },
    { 307, 0x00340014, 0x15000000, ftZelda_8013B068, ftZelda_8013B0E8,
      ftZelda_8013B0F0, ftZelda_8013B154, func_800761C8 },
    { 308, 0x00340014, 0x15000000, ftZelda_8013B2A4, ftZelda_8013B31C,
      ftZelda_8013B324, ftZelda_8013B388, func_800761C8 },
    { 309, 0x00340414, 0x15000000, ftZelda_8013B0A8, ftZelda_8013B0EC,
      ftZelda_8013B110, ftZelda_8013B190, func_800761C8 },
    { 310, 0x00340414, 0x15000000, ftZelda_8013B2E0, ftZelda_8013B320,
      ftZelda_8013B344, ftZelda_8013B3C4, func_800761C8 },
};

char lbl_803CFC98[] = "PlZd.dat";
char lbl_803CFCA4[] = "ftDataZelda";
char lbl_803CFCB0[] = "PlZdNr.dat";
char lbl_803CFCBC[] = "PlyZelda5K_Share_joint";
char lbl_803CFCD4[] = "PlyZelda5K_Share_matanim_joint";
char lbl_803CFCF4[] = "PlZdRe.dat";
char lbl_803CFD00[] = "PlyZelda5KRe_Share_joint";
char lbl_803CFD1C[] = "PlyZelda5KRe_Share_matanim_joint";
char lbl_803CFD40[] = "PlZdBu.dat";
char lbl_803CFD4C[] = "PlyZelda5KBu_Share_joint";
char lbl_803CFD68[] = "PlyZelda5KBu_Share_matanim_joint";
char lbl_803CFD8C[] = "PlZdGr.dat";
char lbl_803CFD98[] = "PlyZelda5KGr_Share_joint";
char lbl_803CFDB4[] = "PlyZelda5KGr_Share_matanim_joint";
char lbl_803CFDD8[] = "PlZdWh.dat";
char lbl_803CFDE4[] = "PlyZelda5KWh_Share_joint";
char lbl_803CFE00[] = "PlyZelda5KWh_Share_matanim_joint";
char lbl_803CFE24[] = "PlZdAJ.dat";
char lbl_803CFE30[] = "ftDemoResultMotionFileZelda";
char lbl_803CFE4C[] = "ftDemoIntroMotionFileZelda";
char lbl_803CFE68[] = "ftDemoEndingMotionFileZelda";
char lbl_803CFE84[] = "ftDemoViWaitMotionFileZelda";

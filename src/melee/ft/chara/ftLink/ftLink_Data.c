#include "melee/ft/forward.h"
#include <melee/ft/chara/ftLink/ftlink.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_link[] = {
    { 295, 0x00240009, 0x0A000000, func_800CEDE0, func_800CEE00, func_800CEE30,
      func_800CEE50, func_800761C8 },
    { -1, FLAGS_ZERO, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, FLAGS_ZERO, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { 296, 0x00340111, 0x12000000, func_800ED15C, func_800EDD88, func_800EDFD8,
      func_800EE098, func_800761C8 },
    { 297, 0x003C0111, 0x12000000, func_800ED480, func_800EDE30, func_800EDFF8,
      func_800EE120, func_800761C8 },
    { 298, 0x00340111, 0x12000000, func_800ED5B4, func_800EDEAC, func_800EE018,
      func_800EE1A8, func_800761C8 },
    { 299, 0x00340511, 0x12000000, func_800ED72C, func_800EDEB0, func_800EE038,
      func_800EE2E0, func_800761C8 },
    { 300, 0x003C0511, 0x12000000, func_800EDA58, func_800EDF58, func_800EE058,
      func_800EE368, func_800761C8 },
    { 301, 0x00340511, 0x12000000, func_800EDB8C, func_800EDFD4, func_800EE078,
      func_800EE3F0, func_800761C8 },
    { 302, 0x00340112, 0x13000000, func_800EC54C, NULL, func_800EC88C,
      func_800EC94C, func_800761C8 },
    { 303, 0x00340112, 0x13000000, func_800EC588, func_800EC71C, func_800EC8AC,
      func_800EC9C4, func_800761C8 },
    { 304, 0x00340112, 0x13000000, func_800EC5F8, NULL, func_800EC8CC,
      func_800ECA1C, func_800761C8 },
    { 305, 0x00340512, 0x13000000, func_800EC634, NULL, func_800EC8EC,
      func_800ECA88, func_800761C8 },
    { 306, 0x00340512, 0x13000000, func_800EC670, func_800EC810, func_800EC90C,
      func_800ECB00, func_800761C8 },
    { 307, 0x00340512, 0x13000000, func_800EC6E0, NULL, func_800EC92C,
      func_800ECB58, func_800761C8 },
    { 308, 0x00340213, 0x14000000, func_800EBC10, func_800EBCAC, func_800EBD30,
      func_800EBDC0, func_800761C8 },
    { 309, 0x00340213, 0x14000000, func_800EBC4C, func_800EBCB0, func_800EBCB4,
      func_800EBDFC, func_800761C8 },
    { 310, 0x00340014, 0x15000000, func_800EB8A4, NULL, func_800EB91C,
      func_800EB95C, func_800761C8 },
    { 311, 0x00340414, 0x15000000, func_800EB8E0, NULL, func_800EB93C,
      func_800EB9D4, func_800761C8 },
    { 312, 0x00200000, 0x01000000, func_800C3D6C, func_800C4384, func_800C438C,
      func_800C447C, func_800761C8 },
    { 313, 0x00C00000, 0x01000000, func_800C4380, func_800C4388, func_800C4438,
      func_80082B78, func_800761C8 },
};

char lbl_803C80B8[] = "PlLk.dat";
char lbl_803C80C4[] = "ftDataLink";
char lbl_803C80D0[] = "PlLkNr.dat";
char lbl_803C80DC[] = "PlyLink5K_Share_joint";
char lbl_803C80F4[] = "PlyLink5K_Share_matanim_joint";
char lbl_803C8114[] = "PlLkRe.dat";
char lbl_803C8120[] = "PlyLink5KRe_Share_joint";
char lbl_803C8138[] = "PlyLink5KRe_Share_matanim_joint";
char lbl_803C8158[] = "PlLkBu.dat";
char lbl_803C8164[] = "PlyLink5KBu_Share_joint";
char lbl_803C817C[] = "PlyLink5KBu_Share_matanim_joint";
char lbl_803C819C[] = "PlLkBk.dat";
char lbl_803C81A8[] = "PlyLink5KBk_Share_joint";
char lbl_803C81C0[] = "PlyLink5KBk_Share_matanim_joint";
char lbl_803C81E0[] = "PlLkWh.dat";
char lbl_803C81EC[] = "PlyLink5KWh_Share_joint";
char lbl_803C8204[] = "PlyLink5KWh_Share_matanim_joint";
char lbl_803C8224[] = "PlLkAJ.dat";
char lbl_803C8230[] = "ftDemoResultMotionFileLink";
char lbl_803C824C[] = "ftDemoIntroMotionFileLink";
char lbl_803C8268[] = "ftDemoEndingMotionFileLink";
char lbl_803C8284[] = "ftDemoViWaitMotionFileLink";

Fighter_DemoStrings lbl_803C82A0 = {
    lbl_803C8230,
    lbl_803C824C,
    lbl_803C8268,
    lbl_803C8284,
};

Fighter_CostumeStrings lbl_803C82B0[] = {
    { lbl_803C80D0, lbl_803C80DC, lbl_803C80F4 },
    { lbl_803C8114, lbl_803C8120, lbl_803C8138 },
    { lbl_803C8158, lbl_803C8164, lbl_803C817C },
    { lbl_803C819C, lbl_803C81A8, lbl_803C81C0 },
    { lbl_803C81E0, lbl_803C81EC, lbl_803C8204 },
};

int lbl_803C82EC[31] = { 0 };

Vec3 const lbl_803B7520[3] = { 0 };

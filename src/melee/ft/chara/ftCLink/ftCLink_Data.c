#include <melee/ft/chara/ftCLink/ftclink.h>
#include <melee/ft/chara/ftLink/ftlink.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_clink[] = {
    { 295, 0x00240009, 0x0A000000, func_800CEDE0, func_800CEE00, func_800CEE30,
      func_800CEE50, func_800761C8 },
    { 239, 0x00000071, 0x01000000, func_80149354, func_8014943C, func_8014945C,
      func_8014947C, func_800761C8 },
    { 240, 0x00000071, 0x01000000, func_80149354, func_8014943C, func_8014945C,
      func_8014947C, func_800761C8 },
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

char lbl_803D1240[] = "PlCl.dat";
char lbl_803D124C[] = "ftDataClink";
char lbl_803D1258[] = "PlClNr.dat";
char lbl_803D1264[] = "PlyClink5K_Share_joint";
char lbl_803D127C[] = "PlyClink5K_Share_matanim_joint";
char lbl_803D129C[] = "PlClRe.dat";
char lbl_803D12A8[] = "PlyClink5KRe_Share_joint";
char lbl_803D12C4[] = "PlyClink5KRe_Share_matanim_joint";
char lbl_803D12E8[] = "PlClBu.dat";
char lbl_803D12F4[] = "PlyClink5KBu_Share_joint";
char lbl_803D1310[] = "PlyClink5KBu_Share_matanim_joint";
char lbl_803D1334[] = "PlClWh.dat";
char lbl_803D1340[] = "PlyClink5KWh_Share_joint";
char lbl_803D135C[] = "PlyClink5KWh_Share_matanim_joint";
char lbl_803D1380[] = "PlClBk.dat";
char lbl_803D138C[] = "PlyClink5KBk_Share_joint";
char lbl_803D13A8[] = "PlyClink5KBk_Share_matanim_joint";
char lbl_803D13CC[] = "PlClAJ.dat";
char lbl_803D13D8[] = "ftDemoResultMotionFileClink";
char lbl_803D13F4[] = "ftDemoIntroMotionFileClink";
char lbl_803D1410[] = "ftDemoEndingMotionFileClink";
char lbl_803D142C[] = "ftDemoViWaitMotionFileClink";

Fighter_DemoStrings lbl_803D1448 = {
    lbl_803D13D8,
    lbl_803D13F4,
    lbl_803D1410,
    lbl_803D142C,
};

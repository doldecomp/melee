#include "melee/ft/forward.h"
#include <melee/ft/chara/ftKoopa/ftkoopa.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_koopa[] = {
    { 295, 0x00340011, 0x12000000, lbl_80134F48, lbl_801351B0, lbl_80135438,
      lbl_801354F8, func_800761C8 },
    { 296, 0x003C0011, 0x12000000, lbl_80134F9C, lbl_801351B4, lbl_80135458,
      lbl_80135564, func_800761C8 },
    { 297, 0x00340011, 0x12000000, lbl_80135040, lbl_801352F0, lbl_80135478,
      lbl_801355D0, func_800761C8 },
    { 298, 0x00340411, 0x12000000, lbl_8013507C, lbl_801352F4, lbl_80135498,
      lbl_8013563C, func_800761C8 },
    { 299, 0x003C0411, 0x12000000, lbl_801350D0, lbl_801352F8, lbl_801354B8,
      lbl_801356A8, func_800761C8 },
    { 300, 0x00340411, 0x12000000, lbl_80135174, lbl_80135434, lbl_801354D8,
      lbl_80135714, func_800761C8 },
    { 301, 0x00340012, 0x13000000, func_80133654, NULL, lbl_80134224,
      lbl_80134388, func_800761C8 },
    { 302, 0x00340012, 0x13000000, func_801336CC, lbl_80133BF4, lbl_80134288,
      lbl_801343D8, func_800761C8 },
    { 303, 0x00340012, 0x13000000, func_801336CC, lbl_80133BF4, lbl_80134288,
      lbl_801343D8, func_800761C8 },
    { 302, 0x00340012, 0x13000000, lbl_801339AC, lbl_80133E4C, lbl_801342C8,
      lbl_80134428, func_800761C8 },
    { 304, 0x00340012, 0x13000000, lbl_801339B4, NULL, lbl_80134308,
      lbl_80134478, func_800761C8 },
    { 305, 0x00340012, 0x13000000, lbl_80133A90, NULL, lbl_80134328,
      lbl_801344A0, func_800761C8 },
    { 306, 0x00340412, 0x13000000, func_80133690, NULL, lbl_80134244,
      lbl_801343B0, func_800761C8 },
    { 307, 0x00340412, 0x13000000, lbl_8013383C, lbl_80133D20, lbl_801342A8,
      lbl_80134400, func_800761C8 },
    { 308, 0x00340412, 0x13000000, lbl_8013383C, lbl_80133D20, lbl_801342A8,
      lbl_80134400, func_800761C8 },
    { 307, 0x00340012, 0x13000000, lbl_801339B0, lbl_80134038, lbl_801342E8,
      lbl_80134450, func_800761C8 },
    { 309, 0x00340412, 0x13000000, lbl_80133AD4, NULL, lbl_80134348,
      lbl_801344C8, func_800761C8 },
    { 310, 0x00340412, 0x13000000, lbl_80133BB0, NULL, lbl_80134368,
      lbl_801344F0, func_800761C8 },
    { 311, 0x00340213, 0x14000000, func_80135C08, lbl_80135D78, lbl_80135D80,
      lbl_80135E4C, func_800761C8 },
    { 312, 0x00340613, 0x14000000, lbl_80135C60, lbl_80135D7C, lbl_80135DE0,
      lbl_80135F6C, func_800761C8 },
    { 313, 0x00340214, 0x15000000, lbl_8013474C, NULL, lbl_801347C4,
      lbl_801348A0, func_800761C8 },
    { 314, 0x00340614, 0x15000000, lbl_80134788, NULL, lbl_80134804,
      func_801348C0, func_800761C8 },
    { 315, 0x00340214, 0x15000000, lbl_801349C4, NULL, lbl_80134A00,
      lbl_80134A20, func_800761C8 },
};

char lbl_803CF0A0[] = "PlKp.dat";
char lbl_803CF0AC[] = "ftDataKoopa";
char lbl_803CF0B8[] = "PlKpNr.dat";
char lbl_803CF0C4[] = "PlyKoopa5K_Share_joint";
char lbl_803CF0DC[] = "PlyKoopa5K_Share_matanim_joint";
char lbl_803CF0FC[] = "PlKpRe.dat";
char lbl_803CF108[] = "PlyKoopa5KRe_Share_joint";
char lbl_803CF124[] = "PlyKoopa5KRe_Share_matanim_joint";
char lbl_803CF148[] = "PlKpBu.dat";
char lbl_803CF154[] = "PlyKoopa5KBu_Share_joint";
char lbl_803CF170[] = "PlyKoopa5KBu_Share_matanim_joint";
char lbl_803CF194[] = "PlKpBk.dat";
char lbl_803CF1A0[] = "PlyKoopa5KBk_Share_joint";
char lbl_803CF1BC[] = "PlyKoopa5KBk_Share_matanim_joint";
char lbl_803CF1E0[] = "PlKpAJ.dat";
char lbl_803CF1EC[] = "ftDemoResultMotionFileKoopa";
char lbl_803CF208[] = "ftDemoIntroMotionFileKoopa";
char lbl_803CF224[] = "ftDemoEndingMotionFileKoopa";
char lbl_803CF240[] = "ftDemoViWaitMotionFileKoopa";

Fighter_DemoStrings lbl_803CF25C = {
    lbl_803CF1EC,
    lbl_803CF208,
    lbl_803CF224,
    lbl_803CF240,
};

/// @todo #Fighter_CostumeStrings array will not align at the end.
///       Likely a missing split.
char* lbl_803CF26C[] = {
    lbl_803CF0B8, lbl_803CF0C4, lbl_803CF0DC, lbl_803CF0FC, lbl_803CF108,
    lbl_803CF124, lbl_803CF148, lbl_803CF154, lbl_803CF170, lbl_803CF194,
    lbl_803CF1A0, lbl_803CF1BC, NULL,
};

enum_t lbl_803CF2A0[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
};

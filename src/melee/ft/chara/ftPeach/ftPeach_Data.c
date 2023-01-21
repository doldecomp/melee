#include <melee/ft/chara/ftPeach/ftpeach.h>
#include <melee/ft/forward.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_peach[] = {
    { 295, FLAGS_ZERO, 0x01000000, ftPeach_8011BC38, ftPeach_8011BC8C,
      ftPeach_8011BD18, ftPeach_8011BD3C, func_800761C8 },
    { 296, FLAGS_ZERO, 0x01000000, ftPeach_8011BDF0, ftPeach_8011BE2C,
      ftPeach_8011BE30, ftPeach_8011BE50, func_800761C8 },
    { 297, FLAGS_ZERO, 0x01000000, ftPeach_8011BDF0, ftPeach_8011BE2C,
      ftPeach_8011BE30, ftPeach_8011BE50, func_800761C8 },
    { 68, 0x0024040C, 0x0D000000, ftPeach_8011BF88, ftPeach_8011C044,
      ftPeach_8011C160, ftPeach_8011C198, func_800761C8 },
    { 69, 0x0024040D, 0x0E000000, ftPeach_8011BF88, ftPeach_8011C044,
      ftPeach_8011C160, ftPeach_8011C198, func_800761C8 },
    { 70, 0x0024040E, 0x0F000000, ftPeach_8011BF88, ftPeach_8011C044,
      ftPeach_8011C160, ftPeach_8011C198, func_800761C8 },
    { 71, 0x0024040F, 0x10000000, ftPeach_8011BF88, ftPeach_8011C044,
      ftPeach_8011C160, ftPeach_8011C198, func_800761C8 },
    { 72, 0x00240410, 0x11000000, ftPeach_8011BF88, ftPeach_8011C044,
      ftPeach_8011C160, ftPeach_8011C198, func_800761C8 },
    { 298, 0x00240A09, 0x0A000000, ftPeach_8011C248, ftPeach_8011C284,
      ftPeach_8011C2B4, ftPeach_8011C2D4, func_800761C8 },
    { 299, 0x00240A09, 0x0A000000, ftPeach_8011C248, ftPeach_8011C284,
      ftPeach_8011C2B4, ftPeach_8011C2D4, func_800761C8 },
    { 300, 0x00240A09, 0x0A000000, ftPeach_8011C248, ftPeach_8011C284,
      ftPeach_8011C2B4, ftPeach_8011C2D4, func_800761C8 },
    { 301, 0x00340014, 0x15000000, ftPeach_8011D2EC, NULL, ftPeach_8011D394,
      ftPeach_8011D3D4, func_800761C8 },
    { 301, 0x00340014, 0x15000000, ftPeach_8011D340, NULL, ftPeach_8011D3B4,
      ftPeach_8011D3FC, func_800761C8 },
    { 302, 0x00340212, 0x13000000, ftPeach_8011C4F0, ftPeach_8011C5E8,
      ftPeach_8011C5F0, ftPeach_8011C664, func_800761C8 },
    { 303, 0x00340212, 0x13000000, ftPeach_8011CA84, ftPeach_8011CAFC,
      ftPeach_8011CB04, ftPeach_8011CB44, func_800761C8 },
    { 304, 0x00340212, 0x13000000, NULL, NULL, NULL, NULL, func_800761C8 },
    { 305, 0x00340612, 0x13000000, ftPeach_8011C588, ftPeach_8011C5EC,
      ftPeach_8011C644, ftPeach_8011C6FC, func_800761C8 },
    { 306, 0x00340612, 0x13000000, ftPeach_8011CAC0, ftPeach_8011CB00,
      ftPeach_8011CB24, ftPeach_8011CB80, func_800761C8 },
    { 307, 0x00340612, 0x13000000, ftPeach_8011CAC0, ftPeach_8011CB00,
      ftPeach_8011CB24, ftPeach_8011CB80, func_800761C8 },
    { 304, 0x00340612, 0x13000000, ftPeach_8011C878, ftPeach_8011C8C8,
      ftPeach_8011C8CC, ftPeach_8011C93C, func_800761C8 },
    { 308, 0x00340013, 0x14000000, ftPeach_8011D8D0, ftPeach_8011DA30,
      ftPeach_8011DCC0, ftPeach_8011DDBC, func_800761C8 },
    { 309, 0x00340013, 0x14000000, ftPeach_8011DE9C, ftPeach_8011DF5C,
      ftPeach_8011DF64, ftPeach_8011E094, func_800761C8 },
    { 310, 0x00340413, 0x14000000, ftPeach_8011D980, ftPeach_8011DB78,
      ftPeach_8011DCF8, ftPeach_8011DE2C, func_800761C8 },
    { 311, 0x00340413, 0x14000000, ftPeach_8011DEFC, ftPeach_8011DF60,
      ftPeach_8011DFD0, ftPeach_8011E104, func_800761C8 },
    { 312, 0x00340011, 0x12000000, ftPeach_8011E4F8, ftPeach_8011E670,
      ftPeach_8011E678, ftPeach_8011E75C, func_800761C8 },
    { 313, 0x00340011, 0x12000000, ftPeach_8011E9A0, ftPeach_8011EA68,
      ftPeach_8011EA70, ftPeach_8011EAE0, func_800761C8 },
    { 314, 0x00340411, 0x12000000, ftPeach_8011E5B4, ftPeach_8011E674,
      ftPeach_8011E6AC, ftPeach_8011E798, func_800761C8 },
    { 315, 0x00340411, 0x12000000, ftPeach_8011EA04, ftPeach_8011EA6C,
      ftPeach_8011EA90, ftPeach_8011EB1C, func_800761C8 },
    { 316, 0x00440058, 0x57800000, func_800CF0B8, func_800CF118, func_800CF1A0,
      func_800CF258, func_800761C8 },
    { 317, 0x004C0058, 0x57800000, func_800CF424, func_800CF428, func_800CF494,
      func_800CF4B4, func_800761C8 },
};

char ftPeach_str_PlPe_dat[] = "PlPe.dat";
char ftPeach_str_ftDataPeach[] = "ftDataPeach";
char str_PlPeNr_dat[] = "PlPeNr.dat";
char str_PlyPeach5K_Share_joint[] = "PlyPeach5K_Share_joint";
char str_PlyPeach5K_Share_matanim_joint[] = "PlyPeach5K_Share_matanim_joint";
char str_PlPeYe_dat[] = "PlPeYe.dat";
char str_PlyPeach5KYe_Share_joint[] = "PlyPeach5KYe_Share_joint";
char str_PlyPeach5KYe_Share_matanim_joint[] =
    "PlyPeach5KYe_Share_matanim_joint";
char str_PlPeWh_dat[] = "PlPeWh.dat";
char str_PlyPeach5KWh_Share_joint[] = "PlyPeach5KWh_Share_joint";
char str_PlyPeach5KWh_Share_matanim_joint[] =
    "PlyPeach5KWh_Share_matanim_joint";
char str_PlPeBu_dat[] = "PlPeBu.dat";
char str_PlyPeach5KBu_Share_joint[] = "PlyPeach5KBu_Share_joint";
char str_PlyPeach5KBu_Share_matanim_joint[] =
    "PlyPeach5KBu_Share_matanim_joint";
char str_PlPeGr_dat[] = "PlPeGr.dat";
char str_PlyPeach5KGr_Share_joint[] = "PlyPeach5KGr_Share_joint";
char str_PlyPeach5KGr_Share_matanim_joint[] =
    "PlyPeach5KGr_Share_matanim_joint";
char str_PlPeAJ_dat[] = "PlPeAJ.dat";
char str_ftDemoResultMotionFilePeach[] = "ftDemoResultMotionFilePeach";
char str_ftDemoIntroMotionFilePeach[] = "ftDemoIntroMotionFilePeach";
char str_ftDemoEndingMotionFilePeach[] = "ftDemoEndingMotionFilePeach";
char str_ftDemoViWaitMotionFilePeach[] = "ftDemoViWaitMotionFilePeach";

Fighter_DemoStrings ftPeach_str_arr_ftDemo = {
    str_ftDemoResultMotionFilePeach,
    str_ftDemoIntroMotionFilePeach,
    str_ftDemoEndingMotionFilePeach,
    str_ftDemoViWaitMotionFilePeach,
};

Fighter_CostumeStrings ftPeach_str_arr_Costumes[] = {
    { str_PlPeNr_dat, str_PlyPeach5K_Share_joint,
      str_PlyPeach5K_Share_matanim_joint },
    { str_PlPeYe_dat, str_PlyPeach5KYe_Share_joint,
      str_PlyPeach5KYe_Share_matanim_joint },
    { str_PlPeWh_dat, str_PlyPeach5KWh_Share_joint,
      str_PlyPeach5KWh_Share_matanim_joint },
    { str_PlPeBu_dat, str_PlyPeach5KBu_Share_joint,
      str_PlyPeach5KBu_Share_matanim_joint },
    { str_PlPeGr_dat, str_PlyPeach5KGr_Share_joint,
      str_PlyPeach5KGr_Share_matanim_joint },
};

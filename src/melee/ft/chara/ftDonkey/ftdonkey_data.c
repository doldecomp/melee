#include <melee/ft/chara/ftDonkey/ftdonkey.h>
#include <melee/ft/chara/ftDonkey/ftdonkey1.h>
#include <melee/ft/chara/ftDonkey/ftdonkey4.h>
#include <melee/ft/chara/ftDonkey/ftdonkey5.h>
#include <melee/ft/chara/ftDonkey/ftdonkey6.h>
#include <melee/ft/chara/ftDonkey/ftdonkey7.h>
#include <melee/ft/chara/ftDonkey/ftdonkey8.h>
#include <melee/ft/chara/ftDonkey/ftdonkey9.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_SpecialHi.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_SpecialLw.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_SpecialN.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_SpecialS.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_walk.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>

ActionState as_table_donkey[] = {
    { 0x00000127, 0x00480000, 0x35400000, NULL, ftDonkey_800DF9F0,
      ftDonkey_800DFA50, ftDonkey_800DFA70, func_800761C8 },
    { 0x00000128, 0x00484066, 0x35000000, ftDonkey_800DFB34, ftDonkey_800DFB54,
      ftDonkey_800DFBB8, ftDonkey_800DFBD8, func_800761C8 },
    { 0x00000129, 0x00484066, 0x35000000, ftDonkey_800DFB34, ftDonkey_800DFB54,
      ftDonkey_800DFBB8, ftDonkey_800DFBD8, func_800761C8 },
    { 0x0000012A, 0x00484066, 0x35000000, ftDonkey_800DFB34, ftDonkey_800DFB54,
      ftDonkey_800DFBB8, ftDonkey_800DFBD8, func_800761C8 },
    { 0x0000012B, 0x00482064, 0x35000000, ftDonkey_800E01BC, ftDonkey_800E0200,
      ftDonkey_800E0254, ftDonkey_800E0274, func_800761C8 },
    { 0x0000012C, 0x00480000, 0x35000000, ftDonkey_800E0518, ftDonkey_800E0568,
      ftDonkey_800E05A4, ftDonkey_800E05C4, func_800761C8 },
    { 0x0000012D, 0x00480000, 0x35000000, NULL, ftDonkey_800E030C,
      ftDonkey_800E0330, ftDonkey_800E0350, func_800761C8 },
    { 0x0000012E, 0x00488069, 0x35000000, NULL, ftDonkey_800E0440,
      ftDonkey_800E0464, ftDonkey_800E0484, func_800761C8 },
    { 0x0000012F, 0x00480000, 0x35400000, ftDonkey_800E0648, NULL,
      ftDonkey_800E0698, ftDonkey_800E06B8, func_800761C8 },
    { 0x00000130, 0x004A0000, 0x35000000, ftDonkey_800E07E4, NULL,
      ftDonkey_800E0848, ftDonkey_800E0868, func_800761C8 },
    { 0x00000131, 0x00A80035, 0x35400000, func_8009B5C0, func_8009B5C4,
      func_8009B634, func_8009B654, func_800761C8 },
    { 0x00000132, 0x00A84035, 0x35000000, func_8009B744, func_8009B764,
      func_8009B7D8, func_8009B7F8, func_800761C8 },
    { 0x00000133, 0x00A84035, 0x35000000, func_8009B744, func_8009B764,
      func_8009B7D8, func_8009B7F8, func_800761C8 },
    { 0x00000134, 0x00A84035, 0x35000000, func_8009B744, func_8009B764,
      func_8009B7D8, func_8009B7F8, func_800761C8 },
    { 0x00000135, 0x00A82035, 0x35000000, func_8009B8B4, func_8009B948,
      func_8009B988, func_8009B9A8, func_800761C8 },
    { 0x00000136, 0x00A80035, 0x35000000, func_8009BA50, func_8009BAA0,
      func_8009BADC, func_8009BAFC, func_800761C8 },
    { 0x00000137, 0x00A80035, 0x35000000, func_8009BCDC, func_8009BCE0,
      func_8009BD04, func_8009BD24, func_800761C8 },
    { 0x00000138, 0x00A88035, 0x35000000, func_8009BBF0, func_8009BBF4,
      func_8009BC18, func_8009BC38, func_800761C8 },
    { 0x00000139, 0x00A80035, 0x35400000, func_8009BDC4, NULL, func_8009BE14,
      func_8009BE34, func_800761C8 },
    { 0x0000013A, 0x00AA0035, 0x35000000, func_8009BE54, NULL, func_8009BEB8,
      func_8009BED8, func_800761C8 },
    { 0x0000013B, 0x00A40039, 0x39000000, func_8009C0EC, func_8009C130,
      func_8009C150, func_8009C20C, func_800761C8 },
    { 0x0000013C, 0x00A4003A, 0x3A000000, func_8009C234, func_8009C254,
      func_8009C274, func_8009C294, func_800761C8 },
    { 0x0000013D, 0x00A4003B, 0x3B000000, func_8009C2BC, func_8009C2DC,
      func_8009C2FC, func_8009C31C, func_800761C8 },
    { 0x0000013E, 0x00A4003C, 0x3C000000, func_8009C344, func_8009C364,
      func_8009C384, func_8009C3A4, func_800761C8 },
    { 0x0000013B, 0x00A40039, 0x39000000, func_8009C3CC, func_8009C410,
      func_8009C414, func_8009C434, func_800761C8 },
    { 0x0000013C, 0x00A4003A, 0x3A000000, func_8009C3CC, func_8009C410,
      func_8009C414, func_8009C434, func_800761C8 },
    { 0x0000013D, 0x00A4003B, 0x3B000000, func_8009C3CC, func_8009C410,
      func_8009C414, func_8009C434, func_800761C8 },
    { 0x0000013E, 0x00A4003C, 0x3C000000, func_8009C3CC, func_8009C410,
      func_8009C414, func_8009C434, func_800761C8 },
    { 0x0000013F, 0x00340211, 0x12000000, ftDonkey_8010E7B4, ftDonkey_8010F094,
      ftDonkey_8010F328, ftDonkey_8010F468, func_800761C8 },
    { 0x00000140, 0x00340211, 0x12000000, ftDonkey_8010E840, ftDonkey_8010F098,
      ftDonkey_8010F348, ftDonkey_8010F50C, func_800761C8 },
    { 0x00000141, 0x00340211, 0x12000000, ftDonkey_8010E8E0, ftDonkey_8010F1D8,
      ftDonkey_8010F368, ftDonkey_8010F5B0, func_800761C8 },
    { 0x00000142, 0x00340211, 0x12000000, ftDonkey_8010E930, ftDonkey_8010F1DC,
      ftDonkey_8010F388, ftDonkey_8010F654, func_800761C8 },
    { 0x00000143, 0x00340211, 0x12000000, ftDonkey_8010EB0C, ftDonkey_8010F1E0,
      ftDonkey_8010F3A8, ftDonkey_8010F6F8, func_800761C8 },
    { 0x00000144, 0x00340611, 0x12000000, ftDonkey_8010EC5C, ftDonkey_8010F1E4,
      ftDonkey_8010F3C8, ftDonkey_8010F79C, func_800761C8 },
    { 0x00000145, 0x00340611, 0x12000000, ftDonkey_8010ECE8, ftDonkey_8010F1E8,
      ftDonkey_8010F3E8, ftDonkey_8010F840, func_800761C8 },
    { 0x00000146, 0x00340611, 0x12000000, ftDonkey_8010ED88, ftDonkey_8010F31C,
      ftDonkey_8010F408, ftDonkey_8010F8E4, func_800761C8 },
    { 0x00000147, 0x00340611, 0x12000000, ftDonkey_8010EDD8, ftDonkey_8010F320,
      ftDonkey_8010F428, ftDonkey_8010F988, func_800761C8 },
    { 0x00000148, 0x00340611, 0x12000000, ftDonkey_8010EF7C, ftDonkey_8010F324,
      ftDonkey_8010F448, ftDonkey_8010FA2C, func_800761C8 },
    { 0x00000149, 0x00340212, 0x13000000, ftDonkey_8010E2BC, ftDonkey_8010E334,
      ftDonkey_8010E33C, ftDonkey_8010E3BC, func_800761C8 },
    { 0x0000014A, 0x00340612, 0x13000000, ftDonkey_8010E2F8, ftDonkey_8010E338,
      ftDonkey_8010E35C, ftDonkey_8010E428, func_800761C8 },
    { 0x0000014B, 0x00340213, 0x14000000, ftDonkey_8010FCD4, ftDonkey_8010FD9C,
      ftDonkey_8010FDA4, ftDonkey_8010FE60, func_800761C8 },
    { 0x0000014C, 0x00340613, 0x14000000, ftDonkey_8010FD10, ftDonkey_8010FDA0,
      ftDonkey_8010FDEC, ftDonkey_8010FF14, func_800761C8 },
    { 0x0000014D, 0x00340214, 0x15000000, ftDonkey_8010DCD8, ftDonkey_8010DD14,
      ftDonkey_8010DD18, ftDonkey_8010DD38, func_800761C8 },
    { 0x0000014E, 0x003C0214, 0x15000000, ftDonkey_8010DD74, ftDonkey_8010DDDC,
      ftDonkey_8010DDF8, ftDonkey_8010DE18, func_800761C8 },
    { 0x0000014F, 0x00340214, 0x15000000, ftDonkey_8010DF5C, ftDonkey_8010DF98,
      ftDonkey_8010DF9C, ftDonkey_8010DFBC, func_800761C8 },
    { 0x00000150, 0x00340614, 0x15000000, ftDonkey_8010E030, ftDonkey_8010E06C,
      ftDonkey_8010E070, ftDonkey_8010E090, func_800761C8 },
};

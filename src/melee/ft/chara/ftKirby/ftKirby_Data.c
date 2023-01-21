#include <melee/ft/chara/ftKirby/ftkirby.h>
#include <melee/ft/forward.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/types.h>

ActionState as_table_kirby[] = {
    { 295, 0x0000006A, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 296, 0x0000006A, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 297, 0x0000006A, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 298, 0x0000006A, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 299, 0x0000006A, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 300, 0x0000006A, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 301, 0x0000006A, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 302, 0x0000006A, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 303, 0x0000006A, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 304, 0x0000006A, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 52, 0x00240005, 0x06000000, func_800F203C, func_800F205C, lbl_800F207C,
      lbl_800F209C, func_800761C8 },
    { 52, 0x00240405, 0x06000000, func_800F2124, func_800F2160, lbl_800F2164,
      lbl_800F2198, func_800761C8 },
    { 305, 0x00340011, 0x12000000, lbl_800F70A0, NULL, lbl_800F8890,
      lbl_800F8C10, func_800761C8 },
    { 306, 0x003C0011, 0x12000000, lbl_800F72F8, lbl_800F7FA0, lbl_800F88D0,
      lbl_800F8C60, func_800761C8 },
    { 307, 0x00340011, 0x12000000, lbl_800F7300, NULL, lbl_800F8910,
      lbl_800F8CB0, func_800761C8 },
    { 308, 0x00340011, 0x12000000, lbl_800F7498, NULL, lbl_800F8970,
      func_800F8D28, func_800761C8 },
    { 308, 0x00340011, 0x12000000, lbl_800F7378, NULL, lbl_800F8950,
      lbl_800F8D00, func_800761C8 },
    { 309, 0x00340011, 0x12000000, lbl_800F75F8, NULL, lbl_800F89D0,
      lbl_800F8DA0, func_800761C8 },
    { 310, 0x00340011, 0x12400000, lbl_800F76F8, lbl_800F8060, lbl_800F8A10,
      lbl_800F8DF0, func_800761C8 },
    { 311, 0x00344011, 0x12000000, lbl_800F7E78, lbl_800F8770, lbl_800F8B90,
      lbl_800F8FD0, func_800761C8 },
    { 312, 0x00344011, 0x12000000, lbl_800F7E78, lbl_800F8770, lbl_800F8B90,
      lbl_800F8FD0, func_800761C8 },
    { 313, 0x00344011, 0x12000000, lbl_800F7E78, lbl_800F8770, lbl_800F8B90,
      lbl_800F8FD0, func_800761C8 },
    { 317, 0x00342011, 0x12000000, lbl_800F7D58, NULL, func_800F8B50,
      func_800F8F80, func_800761C8 },
    { 314, 0x00348011, 0x12000000, lbl_800F7E98, lbl_800F8870, lbl_800F8BB0,
      lbl_800F8FF8, func_800761C8 },
    { 315, 0x00340011, 0x12000000, lbl_800F7F20, NULL, lbl_800F8BD0,
      lbl_800F9020, func_800761C8 },
    { 316, 0x00340011, 0x12400000, lbl_800F7F24, NULL, lbl_800F8BF0,
      lbl_800F9048, func_800761C8 },
    { 318, 0x00340011, 0x12000000, lbl_800F7B20, NULL, lbl_800F8AF0,
      lbl_800F8F08, func_800761C8 },
    { 318, 0x00340011, 0x12000000, lbl_800F7A70, NULL, lbl_800F8AD0,
      lbl_800F8EE0, func_800761C8 },
    { 319, 0x00340011, 0x12000000, lbl_800F7808, NULL, lbl_800F8A70,
      lbl_800F8E68, func_800761C8 },
    { 319, 0x00340011, 0x12000000, func_800F7700, NULL, lbl_800F8A50,
      lbl_800F8E40, func_800761C8 },
    { 320, 0x00340411, 0x12000000, lbl_800F71CC, NULL, lbl_800F88B0,
      lbl_800F8C38, func_800761C8 },
    { 321, 0x003C0411, 0x12000000, lbl_800F72FC, lbl_800F8000, lbl_800F88F0,
      lbl_800F8C88, func_800761C8 },
    { 307, 0x00340411, 0x12000000, lbl_800F733C, NULL, lbl_800F8930,
      lbl_800F8CD8, func_800761C8 },
    { 308, 0x00340411, 0x12000000, lbl_800F75D8, NULL, lbl_800F89B0,
      lbl_800F8D78, func_800761C8 },
    { 308, 0x00340411, 0x12000000, lbl_800F75B8, NULL, lbl_800F8990,
      lbl_800F8D50, func_800761C8 },
    { 309, 0x00340411, 0x12000000, lbl_800F7674, NULL, lbl_800F89F0,
      lbl_800F8DC8, func_800761C8 },
    { 310, 0x00340411, 0x12000000, func_800F76FC, lbl_800F844C, lbl_800F8A30,
      lbl_800F8E18, func_800761C8 },
    { 318, 0x00340411, 0x12000000, lbl_800F7C94, NULL, lbl_800F8B30,
      lbl_800F8F58, func_800761C8 },
    { 318, 0x00340411, 0x12000000, lbl_800F7BE4, NULL, lbl_800F8B10,
      lbl_800F8F30, func_800761C8 },
    { 319, 0x00340411, 0x12000000, lbl_800F79C0, NULL, lbl_800F8AB0,
      lbl_800F8EB8, func_800761C8 },
    { 319, 0x00340411, 0x12000000, lbl_800F78B8, NULL, lbl_800F8A90,
      lbl_800F8E90, func_800761C8 },
    { 317, 0x00342411, 0x12000000, lbl_800F7DE4, NULL, lbl_800F8B70,
      lbl_800F8FA8, func_800761C8 },
    { 322, 0x00340012, 0x13000000, lbl_800F5660, NULL, func_800F56D8,
      func_800F5718, func_800761C8 },
    { 323, 0x00340412, 0x13000000, lbl_800F569C, NULL, lbl_800F56F8,
      lbl_800F5778, func_800761C8 },
    { 324, 0x00340013, 0x14000000, lbl_800F2470, lbl_800F2758, lbl_800F2910,
      lbl_800F2BBC, func_800761C8 },
    { 325, 0x00340013, 0x14000000, lbl_800F24F8, lbl_800F2828, lbl_800F2984,
      lbl_800F2C5C, func_800761C8 },
    { 326, 0x00340013, 0x14000000, lbl_800F2578, lbl_800F282C, lbl_800F29F8,
      lbl_800F2D98, func_800761C8 },
    { 327, 0x00340013, 0x14000000, lbl_800F257C, func_800F2830, lbl_800F2A48,
      lbl_800F2EA0, func_800761C8 },
    { 328, 0x00340413, 0x14000000, lbl_800F25EC, lbl_800F2834, lbl_800F2A68,
      lbl_800F2F70, func_800761C8 },
    { 329, 0x00340413, 0x14000000, lbl_800F266C, lbl_800F2904, lbl_800F2AE4,
      lbl_800F3004, func_800761C8 },
    { 330, 0x00340413, 0x14000000, lbl_800F26E4, lbl_800F2908, lbl_800F2B60,
      lbl_800F3140, func_800761C8 },
    { 331, 0x00340413, 0x14000000, lbl_800F26E8, lbl_800F290C, lbl_800F2B9C,
      lbl_800F3248, func_800761C8 },
    { 332, 0x00340214, 0x15000000, lbl_800F3F80, lbl_800F42D8, lbl_800F451C,
      lbl_800F4628, func_800761C8 },
    { 333, 0x00340214, 0x15000000, lbl_800F402C, lbl_800F42DC, lbl_800F453C,
      lbl_800F4800, func_800761C8 },
    { 334, 0x00340214, 0x15000000, lbl_800F4074, lbl_800F43FC, lbl_800F4584,
      lbl_800F49E4, func_800761C8 },
    { 335, 0x00340614, 0x15000000, lbl_800F412C, func_800F4400, func_800F45A4,
      lbl_800F4B3C, func_800761C8 },
    { 336, 0x00340614, 0x15000000, func_800F41D8, lbl_800F4404, lbl_800F45C4,
      lbl_800F4E78, func_800761C8 },
    { 337, 0x00340614, 0x15000000, lbl_800F4220, lbl_800F4518, lbl_800F4608,
      lbl_800F51C0, func_800761C8 },
    { 338, 0x00340015, 0x16000000, lbl_800F9198, lbl_800F91D4, lbl_800F9204,
      lbl_800F9224, func_800761C8 },
    { 339, 0x00340415, 0x16000000, lbl_800F9454, lbl_800F9490, lbl_800F94C0,
      lbl_800F94E0, func_800761C8 },
    { 340, 0x0034011A, 0x1B000000, lbl_800FBBC4, lbl_800FC374, lbl_800FC70C,
      lbl_800FC7CC, func_800761C8 },
    { 341, 0x003C011A, 0x1B000000, lbl_800FBDFC, lbl_800FC46C, lbl_800FC72C,
      lbl_800FC880, func_800761C8 },
    { 342, 0x0034011A, 0x1B000000, lbl_800FBED0, lbl_800FC53C, lbl_800FC74C,
      lbl_800FC934, func_800761C8 },
    { 343, 0x0034051A, 0x1B000000, lbl_800FBF34, lbl_800FC540, lbl_800FC76C,
      lbl_800FC9F0, func_800761C8 },
    { 344, 0x003C051A, 0x1B000000, lbl_800FC1A0, lbl_800FC638, lbl_800FC78C,
      lbl_800FCAA4, func_800761C8 },
    { 345, 0x0034051A, 0x1B000000, lbl_800FC274, lbl_800FC708, lbl_800FC7AC,
      lbl_800FCB58, func_800761C8 },
    { 346, 0x00340120, 0x21000000, lbl_800FD0BC, lbl_800FD688, lbl_800FD7F0,
      lbl_800FD8B0, func_800761C8 },
    { 347, 0x00340120, 0x21000000, lbl_800FD250, lbl_800FD68C, lbl_800FD810,
      lbl_800FD938, func_800761C8 },
    { 348, 0x00340120, 0x21000000, lbl_800FD418, lbl_800FD7E0, lbl_800FD830,
      lbl_800FD9E0, func_800761C8 },
    { 349, 0x00340120, 0x21000000, lbl_800FD49C, lbl_800FD7E4, lbl_800FD850,
      lbl_800FDA68, func_800761C8 },
    { 350, 0x00340520, 0x21000000, lbl_800FD4E0, lbl_800FD7E8, lbl_800FD870,
      lbl_800FDAF0, func_800761C8 },
    { 351, 0x00340520, 0x21000000, lbl_800FD608, lbl_800FD7EC, lbl_800FD890,
      lbl_800FDB78, func_800761C8 },
    { 352, 0x00340021, 0x22000000, func_80109D6C, NULL, func_8010A5EC,
      func_8010A72C, func_800761C8 },
    { 353, 0x00340021, 0x22000000, func_80109EE8, NULL, lbl_8010A64C,
      lbl_8010A7A4, func_800761C8 },
    { 353, 0x00340021, 0x22000000, lbl_80109E04, NULL, lbl_8010A62C,
      lbl_8010A77C, func_800761C8 },
    { 354, 0x00340021, 0x12000000, func_8010A304, NULL, func_8010A6CC,
      func_8010A844, func_800761C8 },
    { 354, 0x00340021, 0x12000000, func_8010A1A4, NULL, lbl_8010A6AC,
      lbl_8010A81C, func_800761C8 },
    { 355, 0x00340421, 0x22000000, lbl_80109DB8, NULL, lbl_8010A60C,
      lbl_8010A754, func_800761C8 },
    { 356, 0x00340421, 0x22000000, lbl_8010A0B8, NULL, lbl_8010A66C,
      lbl_8010A7F4, func_800761C8 },
    { 356, 0x00340421, 0x22000000, lbl_80109FD4, NULL, lbl_8010A68C,
      lbl_8010A7CC, func_800761C8 },
    { 357, 0x00340421, 0x22000000, lbl_8010A528, NULL, lbl_8010A70C,
      lbl_8010A894, func_800761C8 },
    { 357, 0x00340421, 0x22000000, lbl_8010A3C8, NULL, func_8010A6EC,
      func_8010A86C, func_800761C8 },
    { 358, 0x00340116, 0x17000000, lbl_800FE360, lbl_800FEA50, lbl_800FEAF8,
      lbl_800FEBB8, func_800761C8 },
    { 359, 0x003C0116, 0x17000000, lbl_800FE450, lbl_800FEA78, lbl_800FEB18,
      lbl_800FEBD8, func_800761C8 },
    { 360, 0x00340116, 0x17000000, lbl_800FE5C8, lbl_800FEAA0, func_800FEB38,
      lbl_800FEBF8, func_800761C8 },
    { 361, 0x00340516, 0x17000000, lbl_800FE688, lbl_800FEAA4, lbl_800FEB58,
      lbl_800FEC18, func_800761C8 },
    { 362, 0x003C0516, 0x17000000, lbl_800FE778, lbl_800FEACC, lbl_800FEB78,
      lbl_800FEC38, func_800761C8 },
    { 363, 0x00340516, 0x17000000, func_800FE928, lbl_800FEAF4, lbl_800FEB98,
      lbl_800FEC58, func_800761C8 },
    { 364, 0x0034011F, 0x20000000, lbl_800FA0F4, lbl_800FA418, lbl_800FA420,
      lbl_800FA460, func_800761C8 },
    { 365, 0x0034051F, 0x20000000, func_800FA254, lbl_800FA41C, lbl_800FA440,
      lbl_800FA4F0, func_800761C8 },
    { 366, 0x00340024, 0x25000000, lbl_800F96F4, lbl_800F976C, lbl_800F97CC,
      lbl_800F980C, func_800761C8 },
    { 367, 0x00340424, 0x25000000, lbl_800F9730, lbl_800F979C, lbl_800F97EC,
      lbl_800F9880, func_800761C8 },
    { 368, 0x00340217, 0x18000000, lbl_800F9AEC, lbl_800F9B64, lbl_800F9C58,
      lbl_800F9E8C, func_800761C8 },
    { 369, 0x00340617, 0x18000000, lbl_800F9B28, lbl_800F9B68, lbl_800F9D40,
      lbl_800F9F34, func_800761C8 },
    { 370, 0x0034011C, 0x1D000000, lbl_800FEE70, lbl_800FF3DC, lbl_800FF4CC,
      lbl_800FF664, func_800761C8 },
    { 371, 0x0034011C, 0x1D000000, lbl_800FEF58, lbl_800FF3E0, lbl_800FF504,
      lbl_800FF6D0, func_800761C8 },
    { 372, 0x0034011C, 0x1D000000, lbl_800FEF58, lbl_800FF3E0, lbl_800FF504,
      lbl_800FF6D0, func_800761C8 },
    { 373, 0x0034011C, 0x1D000000, lbl_800FF08C, lbl_800FF450, lbl_800FF524,
      lbl_800FF73C, func_800761C8 },
    { 374, 0x0034051C, 0x1D000000, lbl_800FF10C, lbl_800FF454, lbl_800FF544,
      lbl_800FF7A8, func_800761C8 },
    { 375, 0x0034051C, 0x1D000000, lbl_800FF1F4, lbl_800FF458, lbl_800FF5A4,
      lbl_800FF814, func_800761C8 },
    { 376, 0x0034051C, 0x1D000000, lbl_800FF1F4, lbl_800FF458, lbl_800FF5A4,
      lbl_800FF814, func_800761C8 },
    { 377, 0x0034051C, 0x1D000000, lbl_800FF328, lbl_800FF4C8, lbl_800FF604,
      lbl_800FF880, func_800761C8 },
    { 378, 0x00340019, 0x1A000000, lbl_800FA9FC, lbl_800FACAC, lbl_800FAF74,
      lbl_800FB034, func_800761C8 },
    { 379, 0x003C0019, 0x1A000000, func_800FAA74, lbl_800FACB0, lbl_800FAF94,
      lbl_800FB0C4, func_800761C8 },
    { 380, 0x00340019, 0x1A000000, lbl_800FAB18, lbl_800FAE0C, lbl_800FAFB4,
      lbl_800FB154, func_800761C8 },
    { 381, 0x00340419, 0x1A000000, lbl_800FAB54, lbl_800FAE10, lbl_800FAFD4,
      lbl_800FB1E4, func_800761C8 },
    { 382, 0x003C0419, 0x1A000000, func_800FABCC, func_800FAE14, func_800FAFF4,
      func_800FB274, func_800761C8 },
    { 383, 0x00340419, 0x1A000000, func_800FAC70, func_800FAF70, func_800FB014,
      func_800FB304, func_800761C8 },
    { 384, 0x0034001D, 0x1E000000, lbl_8010C5FC, lbl_8010C774, lbl_8010C77C,
      lbl_8010C860, func_800761C8 },
    { 385, 0x0034001D, 0x1E000000, lbl_8010CAB4, lbl_8010CB7C, lbl_8010CB84,
      lbl_8010CBF4, func_800761C8 },
    { 386, 0x0034041D, 0x1E000000, lbl_8010C6B8, lbl_8010C778, lbl_8010C7B0,
      lbl_8010C89C, func_800761C8 },
    { 387, 0x0034041D, 0x1E000000, lbl_8010CB18, lbl_8010CB80, lbl_8010CBA4,
      lbl_8010CC30, func_800761C8 },
    { 388, 0x0034011E, 0x1F000000, lbl_80108EFC, lbl_80108F74, lbl_80108F7C,
      lbl_80108FBC, func_800761C8 },
    { 389, 0x0034051E, 0x1F000000, lbl_80108F38, lbl_80108F78, lbl_80108F9C,
      lbl_80109030, func_800761C8 },
    { 390, 0x00340218, 0x19000000, lbl_800FFB24, lbl_801003DC, lbl_80100660,
      lbl_801007A0, func_800761C8 },
    { 391, 0x00340218, 0x19000000, lbl_800FFBAC, lbl_801003E0, lbl_80100680,
      lbl_80100840, func_800761C8 },
    { 392, 0x00340218, 0x19000000, lbl_800FFC48, lbl_80100518, lbl_801006A0,
      lbl_801008E0, func_800761C8 },
    { 393, 0x00340218, 0x19000000, lbl_800FFC94, lbl_8010051C, lbl_801006C0,
      lbl_80100980, func_800761C8 },
    { 394, 0x00340218, 0x19000000, lbl_800FFE6C, lbl_80100520, lbl_801006E0,
      lbl_80100A20, func_800761C8 },
    { 395, 0x00340618, 0x19000000, lbl_800FFFB8, lbl_80100524, lbl_80100700,
      lbl_80100AC0, func_800761C8 },
    { 396, 0x00340618, 0x19000000, lbl_80100040, lbl_80100528, lbl_80100720,
      lbl_80100B60, func_800761C8 },
    { 397, 0x00340618, 0x19000000, lbl_801000DC, lbl_80100654, lbl_80100740,
      lbl_80100C00, func_800761C8 },
    { 398, 0x00340618, 0x19000000, lbl_80100128, lbl_80100658, lbl_80100760,
      lbl_80100CA0, func_800761C8 },
    { 399, 0x00340618, 0x19000000, lbl_801002C8, lbl_8010065C, lbl_80100780,
      lbl_80100D40, func_800761C8 },
    { 400, 0x00340026, 0x27000000, lbl_80105C3C, lbl_80105D64, lbl_80105D6C,
      lbl_80105E14, func_800761C8 },
    { 401, 0x00340426, 0x27000000, lbl_80105CD0, lbl_80105D68, lbl_80105DA0,
      lbl_80105E50, func_800761C8 },
    { 402, 0x0034011B, 0x1C000000, lbl_8010629C, lbl_8010672C, lbl_801068FC,
      lbl_801069FC, func_800761C8 },
    { 403, 0x003C011B, 0x1C000000, lbl_80106334, lbl_80106730, lbl_8010691C,
      lbl_80106A84, func_800761C8 },
    { 404, 0x0034011B, 0x1C000000, lbl_801063E0, lbl_8010680C, lbl_8010693C,
      lbl_80106B0C, func_800761C8 },
    { 405, 0x0034011B, 0x1C000000, lbl_80106428, lbl_80106810, lbl_8010695C,
      lbl_80106B84, func_800761C8 },
    { 406, 0x0034051B, 0x1C000000, lbl_801064AC, lbl_80106814, lbl_8010697C,
      lbl_80106C10, func_800761C8 },
    { 407, 0x003C051B, 0x1C000000, lbl_80106544, lbl_80106818, lbl_8010699C,
      lbl_80106C98, func_800761C8 },
    { 408, 0x0034051B, 0x1C000000, lbl_801065F0, lbl_801068F4, lbl_801069BC,
      lbl_80106D20, func_800761C8 },
    { 409, 0x0034051B, 0x1C000000, lbl_80106670, lbl_801068F8, lbl_801069DC,
      lbl_80106D5C, func_800761C8 },
    { 410, 0x00340222, 0x23000000, lbl_801016CC, lbl_801035C8, lbl_80103D10,
      lbl_801046A4, func_800761C8 },
    { 411, 0x00340222, 0x23000000, lbl_801016CC, lbl_801035C8, lbl_80103D10,
      lbl_801046A4, func_800761C8 },
    { 412, 0x003C0222, 0x23000000, lbl_801017B0, lbl_801035CC, lbl_80103D40,
      lbl_8010475C, func_800761C8 },
    { 413, 0x003C0222, 0x23000000, lbl_80101960, lbl_80103734, lbl_80103D70,
      lbl_80104864, func_800761C8 },
    { 414, 0x00340222, 0x23000000, lbl_80101AD0, lbl_8010389C, lbl_80103DA0,
      lbl_8010496C, func_800761C8 },
    { 415, 0x00340222, 0x23000000, lbl_80101EA0, lbl_80103A24, lbl_80103FA8,
      lbl_80104D14, func_800761C8 },
    { 416, 0x00340222, 0x23000000, lbl_80102198, lbl_80103A28, lbl_801042AC,
      lbl_80104DF8, func_800761C8 },
    { 417, 0x00340222, 0x23000000, lbl_80102198, lbl_80103A28, lbl_801042AC,
      lbl_80104DF8, func_800761C8 },
    { 418, 0x00340622, 0x23000000, lbl_80102470, lbl_80103A2C, lbl_801042E8,
      lbl_80104E58, func_800761C8 },
    { 419, 0x00340622, 0x23000000, lbl_80102470, lbl_80103A2C, lbl_801042E8,
      lbl_80104E58, func_800761C8 },
    { 420, 0x003C0622, 0x23000000, lbl_8010254C, lbl_80103A30, lbl_80104318,
      lbl_80104F10, func_800761C8 },
    { 421, 0x003C0622, 0x23000000, lbl_801026FC, lbl_80103B98, lbl_80104348,
      lbl_80105018, func_800761C8 },
    { 422, 0x00340622, 0x23000000, lbl_8010286C, lbl_80103D00, lbl_80104378,
      lbl_80105120, func_800761C8 },
    { 423, 0x00340222, 0x23000000, lbl_80102DD0, lbl_80103D04, lbl_801044F8,
      lbl_801056FC, func_800761C8 },
    { 424, 0x00340622, 0x23000000, lbl_80103088, lbl_80103D08, lbl_80104610,
      lbl_801057BC, func_800761C8 },
    { 425, 0x00340622, 0x23000000, lbl_80103088, lbl_80103D08, lbl_80104610,
      lbl_801057BC, func_800761C8 },
    { 426, 0x00340622, 0x23000000, lbl_80103374, lbl_80103D0C, lbl_80104640,
      lbl_8010581C, func_800761C8 },
    { 427, 0x00340225, 0x26000000, func_8010B65C, lbl_8010B72C, lbl_8010B734,
      lbl_8010B7F0, func_800761C8 },
    { 428, 0x00340225, 0x26000000, lbl_8010B958, lbl_8010BA28, lbl_8010BA98,
      lbl_8010BAD8, func_800761C8 },
    { 429, 0x00340225, 0x26000000, func_8010BCE0, lbl_8010BED0, lbl_8010BED8,
      lbl_8010BF18, func_800761C8 },
    { 430, 0x00340225, 0x26000000, func_8010BCE0, lbl_8010BED0, lbl_8010BED8,
      lbl_8010BF18, func_800761C8 },
    { 431, 0x00340625, 0x26000000, lbl_8010B6C4, lbl_8010B730, lbl_8010B78C,
      lbl_8010B82C, func_800761C8 },
    { 432, 0x00340625, 0x26000000, lbl_8010B9C0, lbl_8010BA60, lbl_8010BAB8,
      lbl_8010BB14, func_800761C8 },
    { 433, 0x00340625, 0x26000000, lbl_8010BDD8, func_8010BED4, func_8010BEF8,
      lbl_8010BF54, func_800761C8 },
    { 434, 0x00340625, 0x26000000, lbl_8010BDD8, func_8010BED4, func_8010BEF8,
      lbl_8010BF54, func_800761C8 },
    { 435, 0x00340123, 0x24000000, lbl_80107700, lbl_80108040, lbl_80108658,
      lbl_80108798, func_800761C8 },
    { 436, 0x003C0123, 0x24000000, lbl_80107884, lbl_80108044, lbl_80108678,
      lbl_80108820, func_800761C8 },
    { 437, 0x003C0123, 0x24000000, lbl_80107A84, lbl_801081F8, lbl_80108698,
      lbl_801088A8, func_800761C8 },
    { 438, 0x00340123, 0x24000000, lbl_80107AB4, lbl_80108394, lbl_801086B8,
      lbl_80108930, func_800761C8 },
    { 439, 0x00340123, 0x24000000, lbl_80107B38, lbl_80108398, lbl_801086D8,
      lbl_801089B8, func_800761C8 },
    { 440, 0x00340523, 0x24000000, lbl_80107B7C, lbl_8010839C, lbl_801086F8,
      lbl_80108A40, func_800761C8 },
    { 441, 0x003C0523, 0x24000000, lbl_80107D0C, lbl_801083A0, lbl_80108718,
      lbl_80108AC8, func_800761C8 },
    { 442, 0x003C0523, 0x24000000, lbl_80107F0C, lbl_80108504, lbl_80108738,
      lbl_80108B50, func_800761C8 },
    { 443, 0x00340523, 0x24000000, lbl_80107F3C, lbl_80108650, lbl_80108758,
      lbl_80108BD8, func_800761C8 },
    { 444, 0x00340523, 0x24000000, lbl_80107FC0, lbl_80108654, lbl_80108778,
      lbl_80108C60, func_800761C8 },
    { 445, 0x0034012B, 0x2C000000, lbl_8010D280, lbl_8010D3C0, lbl_8010D4C8,
      lbl_8010D508, func_800761C8 },
    { 446, 0x0034052B, 0x2C000000, lbl_8010D320, lbl_8010D444, lbl_8010D4E8,
      lbl_8010D544, func_800761C8 },
    { 447, 0x00340028, 0x29000000, lbl_800F9198, lbl_800F91D4, lbl_800F9204,
      lbl_800F9224, func_800761C8 },
    { 448, 0x00340428, 0x29000000, lbl_800F9454, lbl_800F9490, lbl_800F94C0,
      lbl_800F94E0, func_800761C8 },
    { 449, 0x00340127, 0x28000000, lbl_800FBBC4, lbl_800FC374, lbl_800FC70C,
      lbl_800FC7CC, func_800761C8 },
    { 450, 0x003C0127, 0x28000000, lbl_800FBDFC, lbl_800FC46C, lbl_800FC72C,
      lbl_800FC880, func_800761C8 },
    { 451, 0x00340127, 0x28000000, lbl_800FBED0, lbl_800FC53C, lbl_800FC74C,
      lbl_800FC934, func_800761C8 },
    { 452, 0x00340527, 0x28000000, lbl_800FBF34, lbl_800FC540, lbl_800FC76C,
      lbl_800FC9F0, func_800761C8 },
    { 453, 0x003C0527, 0x28000000, lbl_800FC1A0, lbl_800FC638, lbl_800FC78C,
      lbl_800FCAA4, func_800761C8 },
    { 454, 0x00340527, 0x28000000, lbl_800FC274, lbl_800FC708, lbl_800FC7AC,
      lbl_800FCB58, func_800761C8 },
    { 455, 0x00340129, 0x2A000000, lbl_800FE360, lbl_800FEA50, lbl_800FEAF8,
      lbl_800FEBB8, func_800761C8 },
    { 456, 0x003C0129, 0x2A000000, lbl_800FE450, lbl_800FEA78, lbl_800FEB18,
      lbl_800FEBD8, func_800761C8 },
    { 457, 0x00340129, 0x2A000000, lbl_800FE5C8, lbl_800FEAA0, func_800FEB38,
      lbl_800FEBF8, func_800761C8 },
    { 458, 0x00340529, 0x2A000000, lbl_800FE688, lbl_800FEAA4, lbl_800FEB58,
      lbl_800FEC18, func_800761C8 },
    { 459, 0x003C0529, 0x2A000000, lbl_800FE778, lbl_800FEACC, lbl_800FEB78,
      lbl_800FEC38, func_800761C8 },
    { 460, 0x00340529, 0x2A000000, func_800FE928, lbl_800FEAF4, lbl_800FEB98,
      lbl_800FEC58, func_800761C8 },
    { 461, 0x0034012A, 0x2B000000, lbl_800FA0F4, lbl_800FA418, lbl_800FA420,
      lbl_800FA460, func_800761C8 },
    { 462, 0x0034052A, 0x2B000000, func_800FA254, lbl_800FA41C, lbl_800FA440,
      lbl_800FA4F0, func_800761C8 },
    { 463, 0x0034022C, 0x2D000000, lbl_800F9AEC, lbl_800F9B64, lbl_800F9C58,
      lbl_800F9E8C, func_800761C8 },
    { 464, 0x0034062C, 0x2D000000, lbl_800F9B28, lbl_800F9B68, lbl_800F9D40,
      lbl_800F9F34, func_800761C8 },
    { 465, 0x0034022D, 0x2E000000, func_8010B65C, lbl_8010B72C, lbl_8010B734,
      lbl_8010B7F0, func_800761C8 },
    { 466, 0x0034022D, 0x2E000000, lbl_8010B958, lbl_8010BA28, lbl_8010BA98,
      lbl_8010BAD8, func_800761C8 },
    { 467, 0x0034022D, 0x2E000000, func_8010BCE0, lbl_8010BED0, lbl_8010BED8,
      lbl_8010BF18, func_800761C8 },
    { 468, 0x0034022D, 0x2E000000, func_8010BCE0, lbl_8010BED0, lbl_8010BED8,
      lbl_8010BF18, func_800761C8 },
    { 469, 0x0034062D, 0x2E000000, lbl_8010B6C4, lbl_8010B730, lbl_8010B78C,
      lbl_8010B82C, func_800761C8 },
    { 470, 0x0034062D, 0x2E000000, lbl_8010B9C0, lbl_8010BA60, lbl_8010BAB8,
      lbl_8010BB14, func_800761C8 },
    { 471, 0x0034062D, 0x2E000000, lbl_8010BDD8, func_8010BED4, func_8010BEF8,
      lbl_8010BF54, func_800761C8 },
    { 472, 0x0034062D, 0x2E000000, lbl_8010BDD8, func_8010BED4, func_8010BEF8,
      lbl_8010BF54, func_800761C8 },
    { 473, 0x0034002E, 0x2F000000, lbl_800FA9FC, lbl_800FACAC, lbl_800FAF74,
      lbl_800FB034, func_800761C8 },
    { 474, 0x003C002E, 0x2F000000, func_800FAA74, lbl_800FACB0, lbl_800FAF94,
      lbl_800FB0C4, func_800761C8 },
    { 475, 0x0034002E, 0x2F000000, lbl_800FAB18, lbl_800FAE0C, lbl_800FAFB4,
      lbl_800FB154, func_800761C8 },
    { 476, 0x0034042E, 0x2F000000, lbl_800FAB54, lbl_800FAE10, lbl_800FAFD4,
      lbl_800FB1E4, func_800761C8 },
    { 477, 0x003C042E, 0x2F000000, func_800FABCC, func_800FAE14, func_800FAFF4,
      func_800FB274, func_800761C8 },
    { 478, 0x0034042E, 0x2F000000, func_800FAC70, func_800FAF70, func_800FB014,
      func_800FB304, func_800761C8 },
};

HSD_GObjEvent lbl_803C9CC8[] = {
    func_800EFA40, lbl_800EFAF0, lbl_800EFB4C, lbl_800EFBFC, lbl_800EFC58,
    lbl_800EFD08,  lbl_800F0FC0, lbl_800F10A4, NULL,         NULL,
    lbl_800EFD64,  lbl_800EFE1C, lbl_800EFE80, lbl_800EFF38, lbl_800EFF9C,
    lbl_800F0054,  lbl_800F00B8, lbl_800F0168, lbl_800F01C4, lbl_800F0274,
    lbl_800F02D0,  lbl_800F0380, NULL,         NULL,         lbl_800F03DC,
    lbl_800F0494,  lbl_800F04F8, lbl_800F05A8, lbl_800F0604, lbl_800F06B4,
    lbl_800F10D4,  lbl_800F11AC, lbl_800F11F0, lbl_800F12C8, lbl_800F0710,
    lbl_800F07C0,  lbl_800F081C, lbl_800F08D4, lbl_800F0938, lbl_800F09F0,
    lbl_800F0A54,  lbl_800F0B0C, lbl_800F0B70, lbl_800F0C20, lbl_800F130C,
    lbl_800F13F0,  lbl_800F0C7C, lbl_800F0D34, lbl_800F14B4, lbl_800F15D8,
    lbl_800F0D98,  lbl_800F0E48, lbl_800F0EA4, lbl_800F0F5C, NULL,
    NULL,          NULL,         NULL,         NULL,         NULL,
    NULL,          NULL,         lbl_800EFD64, lbl_800EFE1C, NULL,
    NULL,
};

HSD_GObjEvent lbl_803C9DD0[] = {
    lbl_800F9110, lbl_800FE100, lbl_800F99BC, lbl_800FF8EC, func_800F5F68,
    lbl_800FA8B4, lbl_800FB880, lbl_8010612C, lbl_800FED38, lbl_8010C4D4,
    lbl_80108D64, NULL,         lbl_800F9FD4, lbl_800FCF74, lbl_8010941C,
    lbl_80101560, lbl_80107568, lbl_800F9614, lbl_8010B2FC, lbl_80105B2C,
    lbl_800FB880, lbl_800F9110, lbl_800FE100, lbl_800F9FD4, lbl_8010D188,
    lbl_800F99BC, lbl_8010B2FC, NULL,         NULL,         NULL,
    NULL,         lbl_800FA8B4, NULL,
};

HSD_GObjEvent lbl_803C9E54[] = {
    lbl_800F93CC, lbl_800FE240, lbl_800F9A54, lbl_800FFA10, func_800F6070,
    lbl_800FA958, lbl_800FBA00, lbl_801061E4, lbl_800FEDD0, lbl_8010C560,
    lbl_80108E14, NULL,         lbl_800FA064, lbl_800FD020, lbl_801094FC,
    lbl_80101618, lbl_80107638, lbl_800F9684, lbl_8010B4A0, lbl_80105BA8,
    lbl_800FBA00, lbl_800F93CC, lbl_800FE240, lbl_800FA064, lbl_8010D204,
    lbl_800F9A54, lbl_8010B4A0, NULL,         NULL,         NULL,
    NULL,         lbl_800FA958, NULL,
};

// static size_t const unk_array_size = 12;
typedef unk_t ftKirby_UnkArrayThing[12];

ftKirby_UnkArrayThing lbl_803C9ED8 = { 0 };
ftKirby_UnkArrayThing lbl_803C9F08 = { 0 };
ftKirby_UnkArrayThing lbl_803C9F38 = { 0 };
ftKirby_UnkArrayThing lbl_803C9F68 = { 0 };
ftKirby_UnkArrayThing lbl_803C9F98 = { 0 };

ftKirby_UnkArrayThing* lbl_803C9FC8[] = {
    NULL, NULL,          NULL,          &lbl_803C9ED8, NULL, NULL, NULL,
    NULL, NULL,          NULL,          NULL,          NULL, NULL, NULL,
    NULL, &lbl_803C9F08, &lbl_803C9F38, NULL,          NULL, NULL, NULL,
    NULL, &lbl_803C9F68, NULL,          &lbl_803C9F98, NULL, NULL, NULL,
    NULL, NULL,          NULL,          NULL,          NULL,
};

ActionState lbl_803CA04C[] = {
    { 14, FLAGS_ZERO, 0x01000000, NULL, NULL, func_800C737C, NULL, NULL },
    { 15, FLAGS_ZERO, 0x01000000, NULL, NULL, func_800C737C, NULL, NULL },
    { 16, FLAGS_ZERO, 0x01000000, NULL, NULL, func_800C737C, NULL, NULL },
    { 17, FLAGS_ZERO, 0x01000000, NULL, NULL, func_800C7414, NULL, NULL },
};

/* static */ void lbl_800EE854(void);
/* static */ void lbl_800EE904(void);
/* static */ void lbl_800EE904(void);
/* static */ void lbl_800EE904(void);
/* static */ void lbl_800EE8EC(void);
/* static */ void lbl_800EE904(void);
/* static */ void lbl_800EE904(void);
/* static */ void lbl_800EE904(void);
/* static */ void lbl_800EE904(void);
/* static */ void lbl_800EE904(void);
/* static */ void lbl_800EE874(void);
/* static */ void lbl_800EE904(void);
/* static */ void lbl_800EE904(void);
/* static */ void lbl_800EE8B0(void);

jtbl_t jtbl_803CA0CC = {
    lbl_800EE854, lbl_800EE904, lbl_800EE904, lbl_800EE904, lbl_800EE8EC,
    lbl_800EE904, lbl_800EE904, lbl_800EE904, lbl_800EE904, lbl_800EE904,
    lbl_800EE874, lbl_800EE904, lbl_800EE904, lbl_800EE8B0,
};

char ftKirby_assert_msg_0[] = "fighter parts model dobj num over!\n";
char ftKirby_assert_msg_1[] = "ftkirby.c";
char ftKirby_assert_msg_2[] = "fighter dobj num over!\n";

/* static */ void lbl_800F1708(void);
/* static */ void lbl_800F1764(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F186C(void);
/* static */ void lbl_800F17A4(void);
/* static */ void lbl_800F1894(void);
/* static */ void lbl_800F17F8(void);
/* static */ void lbl_800F1744(void);
/* static */ void lbl_800F1730(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F1818(void);
/* static */ void lbl_800F1858(void);
/* static */ void lbl_800F18E8(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F17E4(void);
/* static */ void lbl_800F171C(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F17C4(void);
/* static */ void lbl_800F18B4(void);
/* static */ void lbl_800F1784(void);
/* static */ void lbl_800F1838(void);
/* static */ void lbl_800F18C8(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F18F8(void);
/* static */ void lbl_800F1880(void);

jtbl_t jtbl_803CA14C = {
    lbl_800F1708, lbl_800F1764, lbl_800F18F8, lbl_800F18F8, lbl_800F18F8,
    lbl_800F186C, lbl_800F17A4, lbl_800F1894, lbl_800F17F8, lbl_800F1744,
    lbl_800F1730, lbl_800F18F8, lbl_800F1818, lbl_800F1858, lbl_800F18E8,
    lbl_800F18F8, lbl_800F17E4, lbl_800F171C, lbl_800F18F8, lbl_800F18F8,
    lbl_800F17C4, lbl_800F18B4, lbl_800F1784, lbl_800F1838, lbl_800F18C8,
    lbl_800F18F8, lbl_800F18F8, lbl_800F18F8, lbl_800F18F8, lbl_800F18F8,
    lbl_800F18F8, lbl_800F1880,
};

/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A00(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A64(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A0C(void);
/* static */ void lbl_800F1A44(void);
/* static */ void lbl_800F1A2C(void);
/* static */ void lbl_800F19F4(void);
/* static */ void lbl_800F19E8(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A38(void);
/* static */ void lbl_800F1A50(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A20(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A0C(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A00(void);
/* static */ void lbl_800F1A78(void);
/* static */ void lbl_800F1A70(void);

jtbl_t jtbl_803CA1CC = {
    lbl_800F1A78, lbl_800F1A00, lbl_800F1A78, lbl_800F1A64, lbl_800F1A78,
    lbl_800F1A78, lbl_800F1A0C, lbl_800F1A44, lbl_800F1A2C, lbl_800F19F4,
    lbl_800F19E8, lbl_800F1A78, lbl_800F1A78, lbl_800F1A38, lbl_800F1A50,
    lbl_800F1A78, lbl_800F1A20, lbl_800F1A78, lbl_800F1A78, lbl_800F1A78,
    lbl_800F1A0C, lbl_800F1A78, lbl_800F1A00, lbl_800F1A78, lbl_800F1A70,
};

/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1AE0(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1B44(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1AEC(void);
/* static */ void lbl_800F1B24(void);
/* static */ void lbl_800F1B0C(void);
/* static */ void lbl_800F1AD4(void);
/* static */ void lbl_800F1AC8(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1B18(void);
/* static */ void lbl_800F1B30(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1B00(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1AEC(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1AE0(void);
/* static */ void lbl_800F1B58(void);
/* static */ void lbl_800F1B50(void);

jtbl_t jtbl_803CA230 = {
    lbl_800F1B58, lbl_800F1AE0, lbl_800F1B58, lbl_800F1B44, lbl_800F1B58,
    lbl_800F1B58, lbl_800F1AEC, lbl_800F1B24, lbl_800F1B0C, lbl_800F1AD4,
    lbl_800F1AC8, lbl_800F1B58, lbl_800F1B58, lbl_800F1B18, lbl_800F1B30,
    lbl_800F1B58, lbl_800F1B00, lbl_800F1B58, lbl_800F1B58, lbl_800F1B58,
    lbl_800F1AEC, lbl_800F1B58, lbl_800F1AE0, lbl_800F1B58, lbl_800F1B50,
};

/* static */ void lbl_800F1CD0(void);
/* static */ void lbl_800F1CD0(void);
/* static */ void lbl_800F1CC8(void);
/* static */ void lbl_800F1CD0(void);
/* static */ void lbl_800F1CD0(void);
/* static */ void lbl_800F1CD0(void);
/* static */ void lbl_800F1CD0(void);
/* static */ void lbl_800F1CC8(void);
/* static */ void lbl_800F1CD0(void);
/* static */ void lbl_800F1CD0(void);
/* static */ void lbl_800F1CC8(void);
/* static */ void lbl_800F1CC8(void);
/* static */ void lbl_800F1CD0(void);
/* static */ void lbl_800F1CC8(void);

jtbl_t jtbl_803CA294 = {
    lbl_800F1CD0, lbl_800F1CD0, lbl_800F1CC8, lbl_800F1CD0, lbl_800F1CD0,
    lbl_800F1CD0, lbl_800F1CD0, lbl_800F1CC8, lbl_800F1CD0, lbl_800F1CD0,
    lbl_800F1CC8, lbl_800F1CC8, lbl_800F1CD0, lbl_800F1CC8,
};

/* static */ void lbl_800F1D08(void);
/* static */ void lbl_800F1D08(void);
/* static */ void lbl_800F1D00(void);
/* static */ void lbl_800F1D08(void);
/* static */ void lbl_800F1D08(void);
/* static */ void lbl_800F1D08(void);
/* static */ void lbl_800F1D08(void);
/* static */ void lbl_800F1D00(void);
/* static */ void lbl_800F1D08(void);
/* static */ void lbl_800F1D08(void);
/* static */ void lbl_800F1D00(void);
/* static */ void lbl_800F1D00(void);
/* static */ void lbl_800F1D08(void);
/* static */ void lbl_800F1D00(void);

jtbl_t jtbl_803CA2CC = { lbl_800F1D08, lbl_800F1D08, lbl_800F1D00, lbl_800F1D08,
                         lbl_800F1D08, lbl_800F1D08, lbl_800F1D08, lbl_800F1D00,
                         lbl_800F1D08, lbl_800F1D08, lbl_800F1D00, lbl_800F1D00,
                         lbl_800F1D08, lbl_800F1D00, NULL };

char lbl_803CA308[] = "PlKb.dat";
char lbl_803CA314[] = "ftDataKirby";
char lbl_803CA320[] = "PlKbNr.dat";
char lbl_803CA32C[] = "PlyKirby5K_Share_joint";
char lbl_803CA344[] = "PlyKirby5K_Share_matanim_joint";
char lbl_803CA364[] = "PlKbYe.dat";
char lbl_803CA370[] = "PlyKirby5KYe_Share_joint";
char lbl_803CA38C[] = "PlyKirby5KYe_Share_matanim_joint";
char lbl_803CA3B0[] = "PlKbBu.dat";
char lbl_803CA3BC[] = "PlyKirby5KBu_Share_joint";
char lbl_803CA3D8[] = "PlyKirby5KBu_Share_matanim_joint";
char lbl_803CA3FC[] = "PlKbRe.dat";
char lbl_803CA408[] = "PlyKirby5KRe_Share_joint";
char lbl_803CA424[] = "PlyKirby5KRe_Share_matanim_joint";
char lbl_803CA448[] = "PlKbGr.dat";
char lbl_803CA454[] = "PlyKirby5KGr_Share_joint";
char lbl_803CA470[] = "PlyKirby5KGr_Share_matanim_joint";
char lbl_803CA494[] = "PlKbWh.dat";
char lbl_803CA4A0[] = "PlyKirby5KWh_Share_joint";
char lbl_803CA4BC[] = "PlyKirby5KWh_Share_matanim_joint";
char lbl_803CA4E0[] = "PlKbAJ.dat";
char lbl_803CA4EC[] = "ftDemoResultMotionFileKirby";
char lbl_803CA508[] = "ftDemoIntroMotionFileKirby";
char lbl_803CA524[] = "ftDemoEndingMotionFileKirby";
char lbl_803CA540[] = "ftDemoViWaitMotionFileKirby";

Fighter_DemoStrings lbl_803CA55C = {
    lbl_803CA4EC,
    lbl_803CA508,
    lbl_803CA524,
    lbl_803CA540,
};

char lbl_803CA56C[] = "ftDemoVi0501MotionFileKirby";
char lbl_803CA588[] = "ftDemoVi0502MotionFileKirby";

char* lbl_803CA5A4[] = {
    lbl_803CA56C,
    NULL,
    NULL,
    lbl_803CA588,
};
Fighter_CostumeStrings lbl_803CA5B4[] = {
    lbl_803CA320, lbl_803CA32C, lbl_803CA344, lbl_803CA364, lbl_803CA370,
    lbl_803CA38C, lbl_803CA3B0, lbl_803CA3BC, lbl_803CA3D8, lbl_803CA3FC,
    lbl_803CA408, lbl_803CA424, lbl_803CA448, lbl_803CA454, lbl_803CA470,
    lbl_803CA494, lbl_803CA4A0, lbl_803CA4BC,
};

char lbl_803CA5FC[] = "PlKbCpMr.dat";
char lbl_803CA60C[] = "ftDataKirbyCopyMario";
char lbl_803CA624[] = "PlKbCpFx.dat";
char lbl_803CA634[] = "ftDataKirbyCopyFox";
char lbl_803CA648[] = "PlKbCpCa.dat";
char lbl_803CA658[] = "ftDataKirbyCopyCaptain";
char lbl_803CA670[] = "PlKbCpDk.dat";
char lbl_803CA680[] = "ftDataKirbyCopyDonkey";
char lbl_803CA698[] = "PlKbCpKp.dat";
char lbl_803CA6A8[] = "ftDataKirbyCopyKoopa";
char lbl_803CA6C0[] = "PlKbCpLk.dat";
char lbl_803CA6D0[] = "ftDataKirbyCopyLink";
char lbl_803CA6E4[] = "PlKbCpSk.dat";
char lbl_803CA6F4[] = "ftDataKirbyCopySeak";
char lbl_803CA708[] = "PlKbCpNs.dat";
char lbl_803CA718[] = "ftDataKirbyCopyNess";
char lbl_803CA72C[] = "PlKbCpPe.dat";
char lbl_803CA73C[] = "ftDataKirbyCopyPeach";
char lbl_803CA754[] = "PlKbCpPp.dat";
char lbl_803CA764[] = "ftDataKirbyCopyPopo";
char lbl_803CA778[] = "PlKbCpPk.dat";
char lbl_803CA788[] = "ftDataKirbyCopyPikachu";
char lbl_803CA7A0[] = "PlKbCpSs.dat";
char lbl_803CA7B0[] = "ftDataKirbyCopySamus";
char lbl_803CA7C8[] = "PlKbCpYs.dat";
char lbl_803CA7D8[] = "ftDataKirbyCopyYoshi";
char lbl_803CA7F0[] = "PlKbCpPr.dat";
char lbl_803CA800[] = "ftDataKirbyCopyPurin";
char lbl_803CA818[] = "PlKbCpMt.dat";
char lbl_803CA828[] = "ftDataKirbyCopyMewtwo";
char lbl_803CA840[] = "PlKbCpLg.dat";
char lbl_803CA850[] = "ftDataKirbyCopyLuigi";
char lbl_803CA868[] = "PlKbCpMs.dat";
char lbl_803CA878[] = "ftDataKirbyCopyMars";
char lbl_803CA88C[] = "PlKbCpZd.dat";
char lbl_803CA89C[] = "ftDataKirbyCopyZelda";
char lbl_803CA8B4[] = "PlKbCpCl.dat";
char lbl_803CA8C4[] = "ftDataKirbyCopyClink";
char lbl_803CA8DC[] = "PlKbCpDr.dat";
char lbl_803CA8EC[] = "ftDataKirbyCopyDrmario";
char lbl_803CA904[] = "PlKbCpFc.dat";
char lbl_803CA914[] = "ftDataKirbyCopyFalco";
char lbl_803CA92C[] = "PlKbCpPc.dat";
char lbl_803CA93C[] = "ftDataKirbyCopyPichu";
char lbl_803CA954[] = "PlKbCpGw.dat";
char lbl_803CA964[] = "ftDataKirbyCopyGamewatch";
char lbl_803CA980[] = "PlKbCpGn.dat";
char lbl_803CA990[] = "ftDataKirbyCopyGanon";
char lbl_803CA9A8[] = "PlKbCpFe.dat";
char lbl_803CA9B8[] = "ftDataKirbyCopyEmblem";

Fighter_CostumeStrings lbl_803CA9D0[] = {
    lbl_803CA5FC, lbl_803CA60C, lbl_803CA624, lbl_803CA634, lbl_803CA648,
    lbl_803CA658, lbl_803CA670, lbl_803CA680, NULL,         NULL,
    lbl_803CA698, lbl_803CA6A8, lbl_803CA6C0, lbl_803CA6D0, lbl_803CA6E4,
    lbl_803CA6F4, lbl_803CA708, lbl_803CA718, lbl_803CA72C, lbl_803CA73C,
    lbl_803CA754, lbl_803CA764, NULL,         NULL,         lbl_803CA778,
    lbl_803CA788, lbl_803CA7A0, lbl_803CA7B0, lbl_803CA7C8, lbl_803CA7D8,
    lbl_803CA7F0, lbl_803CA800, lbl_803CA818, lbl_803CA828, lbl_803CA840,
    lbl_803CA850, lbl_803CA868, lbl_803CA878, lbl_803CA88C, lbl_803CA89C,
    lbl_803CA8B4, lbl_803CA8C4, lbl_803CA8DC, lbl_803CA8EC, lbl_803CA904,
    lbl_803CA914, lbl_803CA92C, lbl_803CA93C, lbl_803CA954, lbl_803CA964,
    lbl_803CA980, lbl_803CA990, lbl_803CA9A8, lbl_803CA9B8, NULL,
    NULL,         NULL,         NULL,         NULL,         NULL,
    NULL,         NULL,         NULL,         NULL,         NULL,
    NULL,
};

char lbl_803CAAD8[] = "PlKbNrCpDk.dat";
char lbl_803CAAE8[] = "PlyKirbyDk_Share_joint";
char lbl_803CAB00[] = "PlyKirbyDk_Share_matanim_joint";
char lbl_803CAB20[] = "PlKbYeCpDk.dat";
char lbl_803CAB30[] = "PlyKirbyDkYe_Share_joint";
char lbl_803CAB4C[] = "PlyKirbyDkYe_Share_matanim_joint";
char lbl_803CAB70[] = "PlKbBuCpDk.dat";
char lbl_803CAB80[] = "PlyKirbyDkBu_Share_joint";
char lbl_803CAB9C[] = "PlyKirbyDkBu_Share_matanim_joint";
char lbl_803CABC0[] = "PlKbReCpDk.dat";
char lbl_803CABD0[] = "PlyKirbyDkRe_Share_joint";
char lbl_803CABEC[] = "PlyKirbyDkRe_Share_matanim_joint";
char lbl_803CAC10[] = "PlKbGrCpDk.dat";
char lbl_803CAC20[] = "PlyKirbyDkGr_Share_joint";
char lbl_803CAC3C[] = "PlyKirbyDkGr_Share_matanim_joint";
char lbl_803CAC60[] = "PlKbWhCpDk.dat";
char lbl_803CAC70[] = "PlyKirbyDkWh_Share_joint";
char lbl_803CAC8C[] = "PlyKirbyDkWh_Share_matanim_joint";

Fighter_CostumeStrings lbl_803CACB0[] = {
    { lbl_803CAAD8, lbl_803CAAE8, lbl_803CAB00 },
    { lbl_803CAB20, lbl_803CAB30, lbl_803CAB4C },
    { lbl_803CAB70, lbl_803CAB80, lbl_803CAB9C },
    { lbl_803CABC0, lbl_803CABD0, lbl_803CABEC },
    { lbl_803CAC10, lbl_803CAC20, lbl_803CAC3C },
    { lbl_803CAC60, lbl_803CAC70, lbl_803CAC8C },
};

char lbl_803CACF8[] = "PlKbNrCpPr.dat";
char lbl_803CAD08[] = "PlyKirbyPr_Share_joint";
char lbl_803CAD20[] = "PlyKirbyPr_Share_matanim_joint";
char lbl_803CAD40[] = "PlKbYeCpPr.dat";
char lbl_803CAD50[] = "PlyKirbyPrYe_Share_joint";
char lbl_803CAD6C[] = "PlyKirbyPrYe_Share_matanim_joint";
char lbl_803CAD90[] = "PlKbBuCpPr.dat";
char lbl_803CADA0[] = "PlyKirbyPrBu_Share_joint";
char lbl_803CADBC[] = "PlyKirbyPrBu_Share_matanim_joint";
char lbl_803CADE0[] = "PlKbReCpPr.dat";
char lbl_803CADF0[] = "PlyKirbyPrRe_Share_joint";
char lbl_803CAE0C[] = "PlyKirbyPrRe_Share_matanim_joint";
char lbl_803CAE30[] = "PlKbGrCpPr.dat";
char lbl_803CAE40[] = "PlyKirbyPrGr_Share_joint";
char lbl_803CAE5C[] = "PlyKirbyPrGr_Share_matanim_joint";
char lbl_803CAE80[] = "PlKbWhCpPr.dat";
char lbl_803CAE90[] = "PlyKirbyPrWh_Share_joint";
char lbl_803CAEAC[] = "PlyKirbyPrWh_Share_matanim_joint";

Fighter_CostumeStrings lbl_803CAED0[] = {
    { lbl_803CACF8, lbl_803CAD08, lbl_803CAD20 },
    { lbl_803CAD40, lbl_803CAD50, lbl_803CAD6C },
    { lbl_803CAD90, lbl_803CADA0, lbl_803CADBC },
    { lbl_803CADE0, lbl_803CADF0, lbl_803CAE0C },
    { lbl_803CAE30, lbl_803CAE40, lbl_803CAE5C },
    { lbl_803CAE80, lbl_803CAE90, lbl_803CAEAC },
};

char lbl_803CAF18[] = "PlKbNrCpMt.dat";
char lbl_803CAF28[] = "PlyKirbyMt_Share_joint";
char lbl_803CAF40[] = "PlyKirbyMt_Share_matanim_joint";
char lbl_803CAF60[] = "PlKbYeCpMt.dat";
char lbl_803CAF70[] = "PlyKirbyMtYe_Share_joint";
char lbl_803CAF8C[] = "PlyKirbyMtYe_Share_matanim_joint";
char lbl_803CAFB0[] = "PlKbBuCpMt.dat";
char lbl_803CAFC0[] = "PlyKirbyMtBu_Share_joint";
char lbl_803CAFDC[] = "PlyKirbyMtBu_Share_matanim_joint";
char lbl_803CB000[] = "PlKbReCpMt.dat";
char lbl_803CB010[] = "PlyKirbyMtRe_Share_joint";
char lbl_803CB02C[] = "PlyKirbyMtRe_Share_matanim_joint";
char lbl_803CB050[] = "PlKbGrCpMt.dat";
char lbl_803CB060[] = "PlyKirbyMtGr_Share_joint";
char lbl_803CB07C[] = "PlyKirbyMtGr_Share_matanim_joint";
char lbl_803CB0A0[] = "PlKbWhCpMt.dat";
char lbl_803CB0B0[] = "PlyKirbyMtWh_Share_joint";
char lbl_803CB0CC[] = "PlyKirbyMtWh_Share_matanim_joint";

Fighter_CostumeStrings lbl_803CB0F0[] = {
    { lbl_803CAF18, lbl_803CAF28, lbl_803CAF40 },
    { lbl_803CAF60, lbl_803CAF70, lbl_803CAF8C },
    { lbl_803CAFB0, lbl_803CAFC0, lbl_803CAFDC },
    { lbl_803CB000, lbl_803CB010, lbl_803CB02C },
    { lbl_803CB050, lbl_803CB060, lbl_803CB07C },
    { lbl_803CB0A0, lbl_803CB0B0, lbl_803CB0CC },
};

char lbl_803CB138[] = "PlKbNrCpFc.dat";
char lbl_803CB148[] = "PlyKirbyFc_Share_joint";
char lbl_803CB160[] = "PlyKirbyFc_Share_matanim_joint";
char lbl_803CB180[] = "PlKbYeCpFc.dat";
char lbl_803CB190[] = "PlyKirbyFcYe_Share_joint";
char lbl_803CB1AC[] = "PlyKirbyFcYe_Share_matanim_joint";
char lbl_803CB1D0[] = "PlKbBuCpFc.dat";
char lbl_803CB1E0[] = "PlyKirbyFcBu_Share_joint";
char lbl_803CB1FC[] = "PlyKirbyFcBu_Share_matanim_joint";
char lbl_803CB220[] = "PlKbReCpFc.dat";
char lbl_803CB230[] = "PlyKirbyFcRe_Share_joint";
char lbl_803CB24C[] = "PlyKirbyFcRe_Share_matanim_joint";
char lbl_803CB270[] = "PlKbGrCpFc.dat";
char lbl_803CB280[] = "PlyKirbyFcGr_Share_joint";
char lbl_803CB29C[] = "PlyKirbyFcGr_Share_matanim_joint";
char lbl_803CB2C0[] = "PlKbWhCpFc.dat";
char lbl_803CB2D0[] = "PlyKirbyFcWh_Share_joint";
char lbl_803CB2EC[] = "PlyKirbyFcWh_Share_matanim_joint";

Fighter_CostumeStrings lbl_803CB310[] = {
    { lbl_803CB138, lbl_803CB148, lbl_803CB160 },
    { lbl_803CB180, lbl_803CB190, lbl_803CB1AC },
    { lbl_803CB1D0, lbl_803CB1E0, lbl_803CB1FC },
    { lbl_803CB220, lbl_803CB230, lbl_803CB24C },
    { lbl_803CB270, lbl_803CB280, lbl_803CB29C },
    { lbl_803CB2C0, lbl_803CB2D0, lbl_803CB2EC },
};

char lbl_803CB358[] = "PlKbNrCpGw.dat";
char lbl_803CB368[] = "PlyKirbyGw_Share_joint";
char lbl_803CB380[] = "PlyKirbyGw_Share_matanim_joint";

Fighter_CostumeStrings lbl_803CB3A0[] = {
    { lbl_803CB358, lbl_803CB368, lbl_803CB380 },
    { lbl_803CB358, lbl_803CB368, lbl_803CB380 },
    { lbl_803CB358, lbl_803CB368, lbl_803CB380 },
    { lbl_803CB358, lbl_803CB368, lbl_803CB380 },
    { lbl_803CB358, lbl_803CB368, lbl_803CB380 },
    { lbl_803CB358, lbl_803CB368, lbl_803CB380 },
};

Fighter_CostumeStrings* lbl_803CB3E8[] = {
    NULL, NULL,         NULL,         lbl_803CACB0, NULL, NULL, NULL,
    NULL, NULL,         NULL,         NULL,         NULL, NULL, NULL,
    NULL, lbl_803CAED0, lbl_803CB0F0, NULL,         NULL, NULL, NULL,
    NULL, lbl_803CB310, NULL,         lbl_803CB3A0, NULL, NULL, NULL,
    NULL, NULL,         NULL,         NULL,         NULL,
};

s8 lbl_803CB46C[FTKIND_MAX] = {
    32, 33, 38, 39, -1, 41, 35, 21, 42, 45, 46, 46, 36, 34, 40, 43, 44,
    37, 20, 21, 35, 32, 33, 36, -1, 47, 48, -1, -1, -1, -1, -1, -1,
};

bool lbl_803CB490[] = {
    false, true,  false, false, false, false, true,  true,
    false, false, false, true,  true,  true,  false, false,
    true,  true,  true,  true,  false, true,  true,
};

struct lbl_803CB4EC_t {
    int x0[6];
    Vec3 x18;
} lbl_803CB4EC = {
    { 0, 2, 3, 4, 5, 6 },
    { 0.0F, 1.0F, 0.0F },
};

char lbl_803CB510[] = "Other Dead_Proc Existence";
char lbl_803CB52C[] = "ftkirbyspecials.c";

enum_t lbl_803CB540[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
};

uint lbl_803CB6C0[] = { 260006, 260009, 260012, 260015, 260018, 0 };

char lbl_803CB6D8[] = "ftToSpecialNFox::Caution!!!\n";
char lbl_803CB6F8[] = "ftkirbyspecialfox.c\0\0\0\0";

Vec4 lbl_803CB710 = { 0.65F, 0.7F, 0.8F, 1.0F };
Vec4 lbl_803CB720 = { 1.1F, 1.35F, 1.3F, 1.2F };

char ftKirby_assert_msg_3[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 lbl_803CB758[] = {
    { +8, +0, -4 },
    { +4, +4, +4 },
};

f32 lbl_803CB770[] = {
    -1, -0.75, -0.5, -0.25, 0, +0.25, +0.5, +0.75, +1,
};
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106464(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106464(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106464(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106464(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106464(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106474(void);
/* static */ void lbl_80106464(void);

jtbl_t jtbl_803CB794 = {
    lbl_80106474, lbl_80106474, lbl_80106464, lbl_80106474, lbl_80106474,
    lbl_80106464, lbl_80106474, lbl_80106474, lbl_80106464, lbl_80106474,
    lbl_80106474, lbl_80106464, lbl_80106474, lbl_80106474, lbl_80106464,
    lbl_80106474, lbl_80106474, lbl_80106464,
};
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066B4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066B4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066B4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066B4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066B4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066C4(void);
/* static */ void lbl_801066B4(void);

jtbl_t jtbl_803CB7DC = {
    lbl_801066C4, lbl_801066C4, lbl_801066B4, lbl_801066C4, lbl_801066C4,
    lbl_801066B4, lbl_801066C4, lbl_801066C4, lbl_801066B4, lbl_801066C4,
    lbl_801066C4, lbl_801066B4, lbl_801066C4, lbl_801066C4, lbl_801066B4,
    lbl_801066C4, lbl_801066C4, lbl_801066B4, NULL,
};

uint lbl_803CB828[] = { 0x00030DB9, 0x00030DBC, 0x00030DBF, 0x00030DC2 };

f32 const lbl_803B7548[10] = { 0 };
Vec3 const lbl_803B7570 = { 0, 4, 0 };
Vec3 const lbl_803B757C = { 0, 4, 0 };

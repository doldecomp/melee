#include "ft/forward.h"

#include "ftKirby/ftkirby.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <dolphin/mtx/types.h>

MotionState ftKirby_MotionStateTable[] = {
    { 295, 0x0000006A, 0x01000000, ft_800D7590, ft_800D7614, ft_800D7634,
      ft_800D767C, ftCamera_UpdateCameraBox },
    { 296, 0x0000006A, 0x01000000, ft_800D7590, ft_800D7614, ft_800D7634,
      ft_800D767C, ftCamera_UpdateCameraBox },
    { 297, 0x0000006A, 0x01000000, ft_800D7590, ft_800D7614, ft_800D7634,
      ft_800D767C, ftCamera_UpdateCameraBox },
    { 298, 0x0000006A, 0x01000000, ft_800D7590, ft_800D7614, ft_800D7634,
      ft_800D767C, ftCamera_UpdateCameraBox },
    { 299, 0x0000006A, 0x01000000, ft_800D7590, ft_800D7614, ft_800D7634,
      ft_800D767C, ftCamera_UpdateCameraBox },
    { 300, 0x0000006A, 0x01000000, ft_800D7590, ft_800D7614, ft_800D7634,
      ft_800D767C, ftCamera_UpdateCameraBox },
    { 301, 0x0000006A, 0x01000000, ft_800D7590, ft_800D7614, ft_800D7634,
      ft_800D767C, ftCamera_UpdateCameraBox },
    { 302, 0x0000006A, 0x01000000, ft_800D7590, ft_800D7614, ft_800D7634,
      ft_800D767C, ftCamera_UpdateCameraBox },
    { 303, 0x0000006A, 0x01000000, ft_800D7590, ft_800D7614, ft_800D7634,
      ft_800D767C, ftCamera_UpdateCameraBox },
    { 304, 0x0000006A, 0x01000000, ft_800D7590, ft_800D7614, ft_800D7634,
      ft_800D767C, ftCamera_UpdateCameraBox },
    { 52, 0x00240005, 0x06000000, ftKirby_800F203C, ftKirby_800F205C,
      ftKirby_800F207C, ftKirby_800F209C, ftCamera_UpdateCameraBox },
    { 52, 0x00240405, 0x06000000, ftKirby_800F2124, ftKirby_800F2160,
      ftKirby_800F2164, ftKirby_800F2198, ftCamera_UpdateCameraBox },
    { 305, 0x00340011, 0x12000000, ftKirby_800F70A0, NULL, ftKirby_800F8890,
      ftKirby_800F8C10, ftCamera_UpdateCameraBox },
    { 306, 0x003C0011, 0x12000000, ftKirby_800F72F8, ftKirby_800F7FA0,
      ftKirby_800F88D0, ftKirby_800F8C60, ftCamera_UpdateCameraBox },
    { 307, 0x00340011, 0x12000000, ftKirby_800F7300, NULL, ftKirby_800F8910,
      ftKirby_800F8CB0, ftCamera_UpdateCameraBox },
    { 308, 0x00340011, 0x12000000, ftKirby_800F7498, NULL, ftKirby_800F8970,
      ftKirby_800F8D28, ftCamera_UpdateCameraBox },
    { 308, 0x00340011, 0x12000000, ftKirby_800F7378, NULL, ftKirby_800F8950,
      ftKirby_800F8D00, ftCamera_UpdateCameraBox },
    { 309, 0x00340011, 0x12000000, ftKirby_800F75F8, NULL, ftKirby_800F89D0,
      ftKirby_800F8DA0, ftCamera_UpdateCameraBox },
    { 310, 0x00340011, 0x12400000, ftKirby_800F76F8, ftKirby_800F8060,
      ftKirby_800F8A10, ftKirby_800F8DF0, ftCamera_UpdateCameraBox },
    { 311, 0x00344011, 0x12000000, ftKirby_800F7E78, ftKirby_800F8770,
      ftKirby_800F8B90, ftKirby_800F8FD0, ftCamera_UpdateCameraBox },
    { 312, 0x00344011, 0x12000000, ftKirby_800F7E78, ftKirby_800F8770,
      ftKirby_800F8B90, ftKirby_800F8FD0, ftCamera_UpdateCameraBox },
    { 313, 0x00344011, 0x12000000, ftKirby_800F7E78, ftKirby_800F8770,
      ftKirby_800F8B90, ftKirby_800F8FD0, ftCamera_UpdateCameraBox },
    { 317, 0x00342011, 0x12000000, ftKirby_800F7D58, NULL, ftKirby_800F8B50,
      ftKirby_800F8F80, ftCamera_UpdateCameraBox },
    { 314, 0x00348011, 0x12000000, ftKirby_800F7E98, ftKirby_800F8870,
      ftKirby_800F8BB0, ftKirby_800F8FF8, ftCamera_UpdateCameraBox },
    { 315, 0x00340011, 0x12000000, ftKirby_800F7F20, NULL, ftKirby_800F8BD0,
      ftKirby_800F9020, ftCamera_UpdateCameraBox },
    { 316, 0x00340011, 0x12400000, ftKirby_800F7F24, NULL, ftKirby_800F8BF0,
      ftKirby_800F9048, ftCamera_UpdateCameraBox },
    { 318, 0x00340011, 0x12000000, ftKirby_800F7B20, NULL, ftKirby_800F8AF0,
      ftKirby_800F8F08, ftCamera_UpdateCameraBox },
    { 318, 0x00340011, 0x12000000, ftKirby_800F7A70, NULL, ftKirby_800F8AD0,
      ftKirby_800F8EE0, ftCamera_UpdateCameraBox },
    { 319, 0x00340011, 0x12000000, ftKirby_800F7808, NULL, ftKirby_800F8A70,
      ftKirby_800F8E68, ftCamera_UpdateCameraBox },
    { 319, 0x00340011, 0x12000000, ftKirby_800F7700, NULL, ftKirby_800F8A50,
      ftKirby_800F8E40, ftCamera_UpdateCameraBox },
    { 320, 0x00340411, 0x12000000, ftKirby_800F71CC, NULL, ftKirby_800F88B0,
      ftKirby_800F8C38, ftCamera_UpdateCameraBox },
    { 321, 0x003C0411, 0x12000000, ftKirby_800F72FC, ftKirby_800F8000,
      ftKirby_800F88F0, ftKirby_800F8C88, ftCamera_UpdateCameraBox },
    { 307, 0x00340411, 0x12000000, ftKirby_800F733C, NULL, ftKirby_800F8930,
      ftKirby_800F8CD8, ftCamera_UpdateCameraBox },
    { 308, 0x00340411, 0x12000000, ftKirby_800F75D8, NULL, ftKirby_800F89B0,
      ftKirby_800F8D78, ftCamera_UpdateCameraBox },
    { 308, 0x00340411, 0x12000000, ftKirby_800F75B8, NULL, ftKirby_800F8990,
      ftKirby_800F8D50, ftCamera_UpdateCameraBox },
    { 309, 0x00340411, 0x12000000, ftKirby_800F7674, NULL, ftKirby_800F89F0,
      ftKirby_800F8DC8, ftCamera_UpdateCameraBox },
    { 310, 0x00340411, 0x12000000, ftKirby_800F76FC, ftKirby_800F844C,
      ftKirby_800F8A30, ftKirby_800F8E18, ftCamera_UpdateCameraBox },
    { 318, 0x00340411, 0x12000000, ftKirby_800F7C94, NULL, ftKirby_800F8B30,
      ftKirby_800F8F58, ftCamera_UpdateCameraBox },
    { 318, 0x00340411, 0x12000000, ftKirby_800F7BE4, NULL, ftKirby_800F8B10,
      ftKirby_800F8F30, ftCamera_UpdateCameraBox },
    { 319, 0x00340411, 0x12000000, ftKirby_800F79C0, NULL, ftKirby_800F8AB0,
      ftKirby_800F8EB8, ftCamera_UpdateCameraBox },
    { 319, 0x00340411, 0x12000000, ftKirby_800F78B8, NULL, ftKirby_800F8A90,
      ftKirby_800F8E90, ftCamera_UpdateCameraBox },
    { 317, 0x00342411, 0x12000000, ftKirby_800F7DE4, NULL, ftKirby_800F8B70,
      ftKirby_800F8FA8, ftCamera_UpdateCameraBox },
    { 322, 0x00340012, 0x13000000, ftKirby_800F5660, NULL, ftKirby_800F56D8,
      ftKirby_800F5718, ftCamera_UpdateCameraBox },
    { 323, 0x00340412, 0x13000000, ftKirby_800F569C, NULL, ftKirby_800F56F8,
      ftKirby_800F5778, ftCamera_UpdateCameraBox },
    { 324, 0x00340013, 0x14000000, ftKirby_800F2470, ftKirby_800F2758,
      ftKirby_800F2910, ftKirby_800F2BBC, ftCamera_UpdateCameraBox },
    { 325, 0x00340013, 0x14000000, ftKirby_800F24F8, ftKirby_800F2828,
      ftKirby_800F2984, ftKirby_800F2C5C, ftCamera_UpdateCameraBox },
    { 326, 0x00340013, 0x14000000, ftKirby_800F2578, ftKirby_800F282C,
      ftKirby_800F29F8, ftKirby_800F2D98, ftCamera_UpdateCameraBox },
    { 327, 0x00340013, 0x14000000, ftKirby_800F257C, ftKirby_800F2830,
      ftKirby_800F2A48, ftKirby_800F2EA0, ftCamera_UpdateCameraBox },
    { 328, 0x00340413, 0x14000000, ftKirby_800F25EC, ftKirby_800F2834,
      ftKirby_800F2A68, ftKirby_800F2F70, ftCamera_UpdateCameraBox },
    { 329, 0x00340413, 0x14000000, ftKirby_800F266C, ftKirby_800F2904,
      ftKirby_800F2AE4, ftKirby_800F3004, ftCamera_UpdateCameraBox },
    { 330, 0x00340413, 0x14000000, ftKirby_800F26E4, ftKirby_800F2908,
      ftKirby_800F2B60, ftKirby_800F3140, ftCamera_UpdateCameraBox },
    { 331, 0x00340413, 0x14000000, ftKirby_800F26E8, ftKirby_800F290C,
      ftKirby_800F2B9C, ftKirby_800F3248, ftCamera_UpdateCameraBox },
    { 332, 0x00340214, 0x15000000, ftKirby_800F3F80, ftKirby_800F42D8,
      ftKirby_800F451C, ftKirby_800F4628, ftCamera_UpdateCameraBox },
    { 333, 0x00340214, 0x15000000, ftKirby_800F402C, ftKirby_800F42DC,
      ftKirby_800F453C, ftKirby_800F4800, ftCamera_UpdateCameraBox },
    { 334, 0x00340214, 0x15000000, ftKirby_800F4074, ftKirby_800F43FC,
      ftKirby_800F4584, ftKirby_800F49E4, ftCamera_UpdateCameraBox },
    { 335, 0x00340614, 0x15000000, ftKirby_800F412C, ftKirby_800F4400,
      ftKirby_800F45A4, ftKirby_800F4B3C, ftCamera_UpdateCameraBox },
    { 336, 0x00340614, 0x15000000, ftKirby_800F41D8, ftKirby_800F4404,
      ftKirby_800F45C4, ftKirby_800F4E78, ftCamera_UpdateCameraBox },
    { 337, 0x00340614, 0x15000000, ftKirby_800F4220, ftKirby_800F4518,
      ftKirby_800F4608, ftKirby_800F51C0, ftCamera_UpdateCameraBox },
    { 338, 0x00340015, 0x16000000, ftKirby_800F9198, ftKirby_800F91D4,
      ftKirby_800F9204, ftKirby_800F9224, ftCamera_UpdateCameraBox },
    { 339, 0x00340415, 0x16000000, ftKirby_800F9454, ftKirby_800F9490,
      ftKirby_800F94C0, ftKirby_800F94E0, ftCamera_UpdateCameraBox },
    { 340, 0x0034011A, 0x1B000000, ftKirby_800FBBC4, ftKirby_800FC374,
      ftKirby_800FC70C, ftKirby_800FC7CC, ftCamera_UpdateCameraBox },
    { 341, 0x003C011A, 0x1B000000, ftKirby_800FBDFC, ftKirby_800FC46C,
      ftKirby_800FC72C, ftKirby_800FC880, ftCamera_UpdateCameraBox },
    { 342, 0x0034011A, 0x1B000000, ftKirby_800FBED0, ftKirby_800FC53C,
      ftKirby_800FC74C, ftKirby_800FC934, ftCamera_UpdateCameraBox },
    { 343, 0x0034051A, 0x1B000000, ftKirby_800FBF34, ftKirby_800FC540,
      ftKirby_800FC76C, ftKirby_800FC9F0, ftCamera_UpdateCameraBox },
    { 344, 0x003C051A, 0x1B000000, ftKirby_800FC1A0, ftKirby_800FC638,
      ftKirby_800FC78C, ftKirby_800FCAA4, ftCamera_UpdateCameraBox },
    { 345, 0x0034051A, 0x1B000000, ftKirby_800FC274, ftKirby_800FC708,
      ftKirby_800FC7AC, ftKirby_800FCB58, ftCamera_UpdateCameraBox },
    { 346, 0x00340120, 0x21000000, ftKirby_800FD0BC, ftKirby_800FD688,
      ftKirby_800FD7F0, ftKirby_800FD8B0, ftCamera_UpdateCameraBox },
    { 347, 0x00340120, 0x21000000, ftKirby_800FD250, ftKirby_800FD68C,
      ftKirby_800FD810, ftKirby_800FD938, ftCamera_UpdateCameraBox },
    { 348, 0x00340120, 0x21000000, ftKirby_800FD418, ftKirby_800FD7E0,
      ftKirby_800FD830, ftKirby_800FD9E0, ftCamera_UpdateCameraBox },
    { 349, 0x00340120, 0x21000000, ftKirby_800FD49C, ftKirby_800FD7E4,
      ftKirby_800FD850, ftKirby_800FDA68, ftCamera_UpdateCameraBox },
    { 350, 0x00340520, 0x21000000, ftKirby_800FD4E0, ftKirby_800FD7E8,
      ftKirby_800FD870, ftKirby_800FDAF0, ftCamera_UpdateCameraBox },
    { 351, 0x00340520, 0x21000000, ftKirby_800FD608, ftKirby_800FD7EC,
      ftKirby_800FD890, ftKirby_800FDB78, ftCamera_UpdateCameraBox },
    { 352, 0x00340021, 0x22000000, ftKirby_80109D6C, NULL, ftKirby_8010A5EC,
      ftKirby_8010A72C, ftCamera_UpdateCameraBox },
    { 353, 0x00340021, 0x22000000, ftKirby_80109EE8, NULL, ftKirby_8010A64C,
      ftKirby_8010A7A4, ftCamera_UpdateCameraBox },
    { 353, 0x00340021, 0x22000000, ftKirby_80109E04, NULL, ftKirby_8010A62C,
      ftKirby_8010A77C, ftCamera_UpdateCameraBox },
    { 354, 0x00340021, 0x12000000, ftKirby_8010A304, NULL, ftKirby_8010A6CC,
      ftKirby_8010A844, ftCamera_UpdateCameraBox },
    { 354, 0x00340021, 0x12000000, ftKirby_8010A1A4, NULL, ftKirby_8010A6AC,
      ftKirby_8010A81C, ftCamera_UpdateCameraBox },
    { 355, 0x00340421, 0x22000000, ftKirby_80109DB8, NULL, ftKirby_8010A60C,
      ftKirby_8010A754, ftCamera_UpdateCameraBox },
    { 356, 0x00340421, 0x22000000, ftKirby_8010A0B8, NULL, ftKirby_8010A66C,
      ftKirby_8010A7F4, ftCamera_UpdateCameraBox },
    { 356, 0x00340421, 0x22000000, ftKirby_80109FD4, NULL, ftKirby_8010A68C,
      ftKirby_8010A7CC, ftCamera_UpdateCameraBox },
    { 357, 0x00340421, 0x22000000, ftKirby_8010A528, NULL, ftKirby_8010A70C,
      ftKirby_8010A894, ftCamera_UpdateCameraBox },
    { 357, 0x00340421, 0x22000000, ftKirby_8010A3C8, NULL, ftKirby_8010A6EC,
      ftKirby_8010A86C, ftCamera_UpdateCameraBox },
    { 358, 0x00340116, 0x17000000, ftKirby_800FE360, ftKirby_800FEA50,
      ftKirby_800FEAF8, ftKirby_800FEBB8, ftCamera_UpdateCameraBox },
    { 359, 0x003C0116, 0x17000000, ftKirby_800FE450, ftKirby_800FEA78,
      ftKirby_800FEB18, ftKirby_800FEBD8, ftCamera_UpdateCameraBox },
    { 360, 0x00340116, 0x17000000, ftKirby_800FE5C8, ftKirby_800FEAA0,
      ftKirby_800FEB38, ftKirby_800FEBF8, ftCamera_UpdateCameraBox },
    { 361, 0x00340516, 0x17000000, ftKirby_800FE688, ftKirby_800FEAA4,
      ftKirby_800FEB58, ftKirby_800FEC18, ftCamera_UpdateCameraBox },
    { 362, 0x003C0516, 0x17000000, ftKirby_800FE778, ftKirby_800FEACC,
      ftKirby_800FEB78, ftKirby_800FEC38, ftCamera_UpdateCameraBox },
    { 363, 0x00340516, 0x17000000, ftKirby_800FE928, ftKirby_800FEAF4,
      ftKirby_800FEB98, ftKirby_800FEC58, ftCamera_UpdateCameraBox },
    { 364, 0x0034011F, 0x20000000, ftKirby_800FA0F4, ftKirby_800FA418,
      ftKirby_800FA420, ftKirby_800FA460, ftCamera_UpdateCameraBox },
    { 365, 0x0034051F, 0x20000000, ftKirby_800FA254, ftKirby_800FA41C,
      ftKirby_800FA440, ftKirby_800FA4F0, ftCamera_UpdateCameraBox },
    { 366, 0x00340024, 0x25000000, ftKirby_800F96F4, ftKirby_800F976C,
      ftKirby_800F97CC, ftKirby_800F980C, ftCamera_UpdateCameraBox },
    { 367, 0x00340424, 0x25000000, ftKirby_800F9730, ftKirby_800F979C,
      ftKirby_800F97EC, ftKirby_800F9880, ftCamera_UpdateCameraBox },
    { 368, 0x00340217, 0x18000000, ftKirby_800F9AEC, ftKirby_800F9B64,
      ftKirby_800F9C58, ftKirby_800F9E8C, ftCamera_UpdateCameraBox },
    { 369, 0x00340617, 0x18000000, ftKirby_800F9B28, ftKirby_800F9B68,
      ftKirby_800F9D40, ftKirby_800F9F34, ftCamera_UpdateCameraBox },
    { 370, 0x0034011C, 0x1D000000, ftKirby_800FEE70, ftKirby_800FF3DC,
      ftKirby_800FF4CC, ftKirby_800FF664, ftCamera_UpdateCameraBox },
    { 371, 0x0034011C, 0x1D000000, ftKirby_800FEF58, ftKirby_800FF3E0,
      ftKirby_800FF504, ftKirby_800FF6D0, ftCamera_UpdateCameraBox },
    { 372, 0x0034011C, 0x1D000000, ftKirby_800FEF58, ftKirby_800FF3E0,
      ftKirby_800FF504, ftKirby_800FF6D0, ftCamera_UpdateCameraBox },
    { 373, 0x0034011C, 0x1D000000, ftKirby_800FF08C, ftKirby_800FF450,
      ftKirby_800FF524, ftKirby_800FF73C, ftCamera_UpdateCameraBox },
    { 374, 0x0034051C, 0x1D000000, ftKirby_800FF10C, ftKirby_800FF454,
      ftKirby_800FF544, ftKirby_800FF7A8, ftCamera_UpdateCameraBox },
    { 375, 0x0034051C, 0x1D000000, ftKirby_800FF1F4, ftKirby_800FF458,
      ftKirby_800FF5A4, ftKirby_800FF814, ftCamera_UpdateCameraBox },
    { 376, 0x0034051C, 0x1D000000, ftKirby_800FF1F4, ftKirby_800FF458,
      ftKirby_800FF5A4, ftKirby_800FF814, ftCamera_UpdateCameraBox },
    { 377, 0x0034051C, 0x1D000000, ftKirby_800FF328, ftKirby_800FF4C8,
      ftKirby_800FF604, ftKirby_800FF880, ftCamera_UpdateCameraBox },
    { 378, 0x00340019, 0x1A000000, ftKirby_800FA9FC, ftKirby_800FACAC,
      ftKirby_800FAF74, ftKirby_800FB034, ftCamera_UpdateCameraBox },
    { 379, 0x003C0019, 0x1A000000, ftKirby_800FAA74, ftKirby_800FACB0,
      ftKirby_800FAF94, ftKirby_800FB0C4, ftCamera_UpdateCameraBox },
    { 380, 0x00340019, 0x1A000000, ftKirby_800FAB18, ftKirby_800FAE0C,
      ftKirby_800FAFB4, ftKirby_800FB154, ftCamera_UpdateCameraBox },
    { 381, 0x00340419, 0x1A000000, ftKirby_800FAB54, ftKirby_800FAE10,
      ftKirby_800FAFD4, ftKirby_800FB1E4, ftCamera_UpdateCameraBox },
    { 382, 0x003C0419, 0x1A000000, ftKirby_800FABCC, ftKirby_800FAE14,
      ftKirby_800FAFF4, ftKirby_800FB274, ftCamera_UpdateCameraBox },
    { 383, 0x00340419, 0x1A000000, ftKirby_800FAC70, ftKirby_800FAF70,
      ftKirby_800FB014, ftKirby_800FB304, ftCamera_UpdateCameraBox },
    { 384, 0x0034001D, 0x1E000000, ftKirby_8010C5FC, ftKirby_8010C774,
      ftKirby_8010C77C, ftKirby_8010C860, ftCamera_UpdateCameraBox },
    { 385, 0x0034001D, 0x1E000000, ftKirby_8010CAB4, ftKirby_8010CB7C,
      ftKirby_8010CB84, ftKirby_8010CBF4, ftCamera_UpdateCameraBox },
    { 386, 0x0034041D, 0x1E000000, ftKirby_8010C6B8, ftKirby_8010C778,
      ftKirby_8010C7B0, ftKirby_8010C89C, ftCamera_UpdateCameraBox },
    { 387, 0x0034041D, 0x1E000000, ftKirby_8010CB18, ftKirby_8010CB80,
      ftKirby_8010CBA4, ftKirby_8010CC30, ftCamera_UpdateCameraBox },
    { 388, 0x0034011E, 0x1F000000, ftKirby_80108EFC, ftKirby_80108F74,
      ftKirby_80108F7C, ftKirby_80108FBC, ftCamera_UpdateCameraBox },
    { 389, 0x0034051E, 0x1F000000, ftKirby_80108F38, ftKirby_80108F78,
      ftKirby_80108F9C, ftKirby_80109030, ftCamera_UpdateCameraBox },
    { 390, 0x00340218, 0x19000000, ftKirby_800FFB24, ftKirby_801003DC,
      ftKirby_80100660, ftKirby_801007A0, ftCamera_UpdateCameraBox },
    { 391, 0x00340218, 0x19000000, ftKirby_800FFBAC, ftKirby_801003E0,
      ftKirby_80100680, ftKirby_80100840, ftCamera_UpdateCameraBox },
    { 392, 0x00340218, 0x19000000, ftKirby_800FFC48, ftKirby_80100518,
      ftKirby_801006A0, ftKirby_801008E0, ftCamera_UpdateCameraBox },
    { 393, 0x00340218, 0x19000000, ftKirby_800FFC94, ftKirby_8010051C,
      ftKirby_801006C0, ftKirby_80100980, ftCamera_UpdateCameraBox },
    { 394, 0x00340218, 0x19000000, ftKirby_800FFE6C, ftKirby_80100520,
      ftKirby_801006E0, ftKirby_80100A20, ftCamera_UpdateCameraBox },
    { 395, 0x00340618, 0x19000000, ftKirby_800FFFB8, ftKirby_80100524,
      ftKirby_80100700, ftKirby_80100AC0, ftCamera_UpdateCameraBox },
    { 396, 0x00340618, 0x19000000, ftKirby_80100040, ftKirby_80100528,
      ftKirby_80100720, ftKirby_80100B60, ftCamera_UpdateCameraBox },
    { 397, 0x00340618, 0x19000000, ftKirby_801000DC, ftKirby_80100654,
      ftKirby_80100740, ftKirby_80100C00, ftCamera_UpdateCameraBox },
    { 398, 0x00340618, 0x19000000, ftKirby_80100128, ftKirby_80100658,
      ftKirby_80100760, ftKirby_80100CA0, ftCamera_UpdateCameraBox },
    { 399, 0x00340618, 0x19000000, ftKirby_801002C8, ftKirby_8010065C,
      ftKirby_80100780, ftKirby_80100D40, ftCamera_UpdateCameraBox },
    { 400, 0x00340026, 0x27000000, ftKirby_80105C3C, ftKirby_80105D64,
      ftKirby_80105D6C, ftKirby_80105E14, ftCamera_UpdateCameraBox },
    { 401, 0x00340426, 0x27000000, ftKirby_80105CD0, ftKirby_80105D68,
      ftKirby_80105DA0, ftKirby_80105E50, ftCamera_UpdateCameraBox },
    { 402, 0x0034011B, 0x1C000000, ftKirby_8010629C, ftKirby_8010672C,
      ftKirby_801068FC, ftKirby_801069FC, ftCamera_UpdateCameraBox },
    { 403, 0x003C011B, 0x1C000000, ftKirby_80106334, ftKirby_80106730,
      ftKirby_8010691C, ftKirby_80106A84, ftCamera_UpdateCameraBox },
    { 404, 0x0034011B, 0x1C000000, ftKirby_801063E0, ftKirby_8010680C,
      ftKirby_8010693C, ftKirby_80106B0C, ftCamera_UpdateCameraBox },
    { 405, 0x0034011B, 0x1C000000, ftKirby_80106428, ftKirby_80106810,
      ftKirby_8010695C, ftKirby_80106B84, ftCamera_UpdateCameraBox },
    { 406, 0x0034051B, 0x1C000000, ftKirby_801064AC, ftKirby_80106814,
      ftKirby_8010697C, ftKirby_80106C10, ftCamera_UpdateCameraBox },
    { 407, 0x003C051B, 0x1C000000, ftKirby_80106544, ftKirby_80106818,
      ftKirby_8010699C, ftKirby_80106C98, ftCamera_UpdateCameraBox },
    { 408, 0x0034051B, 0x1C000000, ftKirby_801065F0, ftKirby_801068F4,
      ftKirby_801069BC, ftKirby_80106D20, ftCamera_UpdateCameraBox },
    { 409, 0x0034051B, 0x1C000000, ftKirby_80106670, ftKirby_801068F8,
      ftKirby_801069DC, ftKirby_80106D5C, ftCamera_UpdateCameraBox },
    { 410, 0x00340222, 0x23000000, ftKirby_801016CC, ftKirby_801035C8,
      ftKirby_80103D10, ftKirby_801046A4, ftCamera_UpdateCameraBox },
    { 411, 0x00340222, 0x23000000, ftKirby_801016CC, ftKirby_801035C8,
      ftKirby_80103D10, ftKirby_801046A4, ftCamera_UpdateCameraBox },
    { 412, 0x003C0222, 0x23000000, ftKirby_801017B0, ftKirby_801035CC,
      ftKirby_80103D40, ftKirby_8010475C, ftCamera_UpdateCameraBox },
    { 413, 0x003C0222, 0x23000000, ftKirby_80101960, ftKirby_80103734,
      ftKirby_80103D70, ftKirby_80104864, ftCamera_UpdateCameraBox },
    { 414, 0x00340222, 0x23000000, ftKirby_80101AD0, ftKirby_8010389C,
      ftKirby_80103DA0, ftKirby_8010496C, ftCamera_UpdateCameraBox },
    { 415, 0x00340222, 0x23000000, ftKirby_80101EA0, ftKirby_80103A24,
      ftKirby_80103FA8, ftKirby_80104D14, ftCamera_UpdateCameraBox },
    { 416, 0x00340222, 0x23000000, ftKirby_80102198, ftKirby_80103A28,
      ftKirby_801042AC, ftKirby_80104DF8, ftCamera_UpdateCameraBox },
    { 417, 0x00340222, 0x23000000, ftKirby_80102198, ftKirby_80103A28,
      ftKirby_801042AC, ftKirby_80104DF8, ftCamera_UpdateCameraBox },
    { 418, 0x00340622, 0x23000000, ftKirby_80102470, ftKirby_80103A2C,
      ftKirby_801042E8, ftKirby_80104E58, ftCamera_UpdateCameraBox },
    { 419, 0x00340622, 0x23000000, ftKirby_80102470, ftKirby_80103A2C,
      ftKirby_801042E8, ftKirby_80104E58, ftCamera_UpdateCameraBox },
    { 420, 0x003C0622, 0x23000000, ftKirby_8010254C, ftKirby_80103A30,
      ftKirby_80104318, ftKirby_80104F10, ftCamera_UpdateCameraBox },
    { 421, 0x003C0622, 0x23000000, ftKirby_801026FC, ftKirby_80103B98,
      ftKirby_80104348, ftKirby_80105018, ftCamera_UpdateCameraBox },
    { 422, 0x00340622, 0x23000000, ftKirby_8010286C, ftKirby_80103D00,
      ftKirby_80104378, ftKirby_80105120, ftCamera_UpdateCameraBox },
    { 423, 0x00340222, 0x23000000, ftKirby_80102DD0, ftKirby_80103D04,
      ftKirby_801044F8, ftKirby_801056FC, ftCamera_UpdateCameraBox },
    { 424, 0x00340622, 0x23000000, ftKirby_80103088, ftKirby_80103D08,
      ftKirby_80104610, ftKirby_801057BC, ftCamera_UpdateCameraBox },
    { 425, 0x00340622, 0x23000000, ftKirby_80103088, ftKirby_80103D08,
      ftKirby_80104610, ftKirby_801057BC, ftCamera_UpdateCameraBox },
    { 426, 0x00340622, 0x23000000, ftKirby_80103374, ftKirby_80103D0C,
      ftKirby_80104640, ftKirby_8010581C, ftCamera_UpdateCameraBox },
    { 427, 0x00340225, 0x26000000, ftKirby_8010B65C, ftKirby_8010B72C,
      ftKirby_8010B734, ftKirby_8010B7F0, ftCamera_UpdateCameraBox },
    { 428, 0x00340225, 0x26000000, ftKirby_8010B958, ftKirby_8010BA28,
      ftKirby_8010BA98, ftKirby_8010BAD8, ftCamera_UpdateCameraBox },
    { 429, 0x00340225, 0x26000000, ftKirby_8010BCE0, ftKirby_8010BED0,
      ftKirby_8010BED8, ftKirby_8010BF18, ftCamera_UpdateCameraBox },
    { 430, 0x00340225, 0x26000000, ftKirby_8010BCE0, ftKirby_8010BED0,
      ftKirby_8010BED8, ftKirby_8010BF18, ftCamera_UpdateCameraBox },
    { 431, 0x00340625, 0x26000000, ftKirby_8010B6C4, ftKirby_8010B730,
      ftKirby_8010B78C, ftKirby_8010B82C, ftCamera_UpdateCameraBox },
    { 432, 0x00340625, 0x26000000, ftKirby_8010B9C0, ftKirby_8010BA60,
      ftKirby_8010BAB8, ftKirby_8010BB14, ftCamera_UpdateCameraBox },
    { 433, 0x00340625, 0x26000000, ftKirby_8010BDD8, ftKirby_8010BED4,
      ftKirby_8010BEF8, ftKirby_8010BF54, ftCamera_UpdateCameraBox },
    { 434, 0x00340625, 0x26000000, ftKirby_8010BDD8, ftKirby_8010BED4,
      ftKirby_8010BEF8, ftKirby_8010BF54, ftCamera_UpdateCameraBox },
    { 435, 0x00340123, 0x24000000, ftKirby_80107700, ftKirby_80108040,
      ftKirby_80108658, ftKirby_80108798, ftCamera_UpdateCameraBox },
    { 436, 0x003C0123, 0x24000000, ftKirby_80107884, ftKirby_80108044,
      ftKirby_80108678, ftKirby_80108820, ftCamera_UpdateCameraBox },
    { 437, 0x003C0123, 0x24000000, ftKirby_80107A84, ftKirby_801081F8,
      ftKirby_80108698, ftKirby_801088A8, ftCamera_UpdateCameraBox },
    { 438, 0x00340123, 0x24000000, ftKirby_80107AB4, ftKirby_80108394,
      ftKirby_801086B8, ftKirby_80108930, ftCamera_UpdateCameraBox },
    { 439, 0x00340123, 0x24000000, ftKirby_80107B38, ftKirby_80108398,
      ftKirby_801086D8, ftKirby_801089B8, ftCamera_UpdateCameraBox },
    { 440, 0x00340523, 0x24000000, ftKirby_80107B7C, ftKirby_8010839C,
      ftKirby_801086F8, ftKirby_80108A40, ftCamera_UpdateCameraBox },
    { 441, 0x003C0523, 0x24000000, ftKirby_80107D0C, ftKirby_801083A0,
      ftKirby_80108718, ftKirby_80108AC8, ftCamera_UpdateCameraBox },
    { 442, 0x003C0523, 0x24000000, ftKirby_80107F0C, ftKirby_80108504,
      ftKirby_80108738, ftKirby_80108B50, ftCamera_UpdateCameraBox },
    { 443, 0x00340523, 0x24000000, ftKirby_80107F3C, ftKirby_80108650,
      ftKirby_80108758, ftKirby_80108BD8, ftCamera_UpdateCameraBox },
    { 444, 0x00340523, 0x24000000, ftKirby_80107FC0, ftKirby_80108654,
      ftKirby_80108778, ftKirby_80108C60, ftCamera_UpdateCameraBox },
    { 445, 0x0034012B, 0x2C000000, ftKirby_8010D280, ftKirby_8010D3C0,
      ftKirby_8010D4C8, ftKirby_8010D508, ftCamera_UpdateCameraBox },
    { 446, 0x0034052B, 0x2C000000, ftKirby_8010D320, ftKirby_8010D444,
      ftKirby_8010D4E8, ftKirby_8010D544, ftCamera_UpdateCameraBox },
    { 447, 0x00340028, 0x29000000, ftKirby_800F9198, ftKirby_800F91D4,
      ftKirby_800F9204, ftKirby_800F9224, ftCamera_UpdateCameraBox },
    { 448, 0x00340428, 0x29000000, ftKirby_800F9454, ftKirby_800F9490,
      ftKirby_800F94C0, ftKirby_800F94E0, ftCamera_UpdateCameraBox },
    { 449, 0x00340127, 0x28000000, ftKirby_800FBBC4, ftKirby_800FC374,
      ftKirby_800FC70C, ftKirby_800FC7CC, ftCamera_UpdateCameraBox },
    { 450, 0x003C0127, 0x28000000, ftKirby_800FBDFC, ftKirby_800FC46C,
      ftKirby_800FC72C, ftKirby_800FC880, ftCamera_UpdateCameraBox },
    { 451, 0x00340127, 0x28000000, ftKirby_800FBED0, ftKirby_800FC53C,
      ftKirby_800FC74C, ftKirby_800FC934, ftCamera_UpdateCameraBox },
    { 452, 0x00340527, 0x28000000, ftKirby_800FBF34, ftKirby_800FC540,
      ftKirby_800FC76C, ftKirby_800FC9F0, ftCamera_UpdateCameraBox },
    { 453, 0x003C0527, 0x28000000, ftKirby_800FC1A0, ftKirby_800FC638,
      ftKirby_800FC78C, ftKirby_800FCAA4, ftCamera_UpdateCameraBox },
    { 454, 0x00340527, 0x28000000, ftKirby_800FC274, ftKirby_800FC708,
      ftKirby_800FC7AC, ftKirby_800FCB58, ftCamera_UpdateCameraBox },
    { 455, 0x00340129, 0x2A000000, ftKirby_800FE360, ftKirby_800FEA50,
      ftKirby_800FEAF8, ftKirby_800FEBB8, ftCamera_UpdateCameraBox },
    { 456, 0x003C0129, 0x2A000000, ftKirby_800FE450, ftKirby_800FEA78,
      ftKirby_800FEB18, ftKirby_800FEBD8, ftCamera_UpdateCameraBox },
    { 457, 0x00340129, 0x2A000000, ftKirby_800FE5C8, ftKirby_800FEAA0,
      ftKirby_800FEB38, ftKirby_800FEBF8, ftCamera_UpdateCameraBox },
    { 458, 0x00340529, 0x2A000000, ftKirby_800FE688, ftKirby_800FEAA4,
      ftKirby_800FEB58, ftKirby_800FEC18, ftCamera_UpdateCameraBox },
    { 459, 0x003C0529, 0x2A000000, ftKirby_800FE778, ftKirby_800FEACC,
      ftKirby_800FEB78, ftKirby_800FEC38, ftCamera_UpdateCameraBox },
    { 460, 0x00340529, 0x2A000000, ftKirby_800FE928, ftKirby_800FEAF4,
      ftKirby_800FEB98, ftKirby_800FEC58, ftCamera_UpdateCameraBox },
    { 461, 0x0034012A, 0x2B000000, ftKirby_800FA0F4, ftKirby_800FA418,
      ftKirby_800FA420, ftKirby_800FA460, ftCamera_UpdateCameraBox },
    { 462, 0x0034052A, 0x2B000000, ftKirby_800FA254, ftKirby_800FA41C,
      ftKirby_800FA440, ftKirby_800FA4F0, ftCamera_UpdateCameraBox },
    { 463, 0x0034022C, 0x2D000000, ftKirby_800F9AEC, ftKirby_800F9B64,
      ftKirby_800F9C58, ftKirby_800F9E8C, ftCamera_UpdateCameraBox },
    { 464, 0x0034062C, 0x2D000000, ftKirby_800F9B28, ftKirby_800F9B68,
      ftKirby_800F9D40, ftKirby_800F9F34, ftCamera_UpdateCameraBox },
    { 465, 0x0034022D, 0x2E000000, ftKirby_8010B65C, ftKirby_8010B72C,
      ftKirby_8010B734, ftKirby_8010B7F0, ftCamera_UpdateCameraBox },
    { 466, 0x0034022D, 0x2E000000, ftKirby_8010B958, ftKirby_8010BA28,
      ftKirby_8010BA98, ftKirby_8010BAD8, ftCamera_UpdateCameraBox },
    { 467, 0x0034022D, 0x2E000000, ftKirby_8010BCE0, ftKirby_8010BED0,
      ftKirby_8010BED8, ftKirby_8010BF18, ftCamera_UpdateCameraBox },
    { 468, 0x0034022D, 0x2E000000, ftKirby_8010BCE0, ftKirby_8010BED0,
      ftKirby_8010BED8, ftKirby_8010BF18, ftCamera_UpdateCameraBox },
    { 469, 0x0034062D, 0x2E000000, ftKirby_8010B6C4, ftKirby_8010B730,
      ftKirby_8010B78C, ftKirby_8010B82C, ftCamera_UpdateCameraBox },
    { 470, 0x0034062D, 0x2E000000, ftKirby_8010B9C0, ftKirby_8010BA60,
      ftKirby_8010BAB8, ftKirby_8010BB14, ftCamera_UpdateCameraBox },
    { 471, 0x0034062D, 0x2E000000, ftKirby_8010BDD8, ftKirby_8010BED4,
      ftKirby_8010BEF8, ftKirby_8010BF54, ftCamera_UpdateCameraBox },
    { 472, 0x0034062D, 0x2E000000, ftKirby_8010BDD8, ftKirby_8010BED4,
      ftKirby_8010BEF8, ftKirby_8010BF54, ftCamera_UpdateCameraBox },
    { 473, 0x0034002E, 0x2F000000, ftKirby_800FA9FC, ftKirby_800FACAC,
      ftKirby_800FAF74, ftKirby_800FB034, ftCamera_UpdateCameraBox },
    { 474, 0x003C002E, 0x2F000000, ftKirby_800FAA74, ftKirby_800FACB0,
      ftKirby_800FAF94, ftKirby_800FB0C4, ftCamera_UpdateCameraBox },
    { 475, 0x0034002E, 0x2F000000, ftKirby_800FAB18, ftKirby_800FAE0C,
      ftKirby_800FAFB4, ftKirby_800FB154, ftCamera_UpdateCameraBox },
    { 476, 0x0034042E, 0x2F000000, ftKirby_800FAB54, ftKirby_800FAE10,
      ftKirby_800FAFD4, ftKirby_800FB1E4, ftCamera_UpdateCameraBox },
    { 477, 0x003C042E, 0x2F000000, ftKirby_800FABCC, ftKirby_800FAE14,
      ftKirby_800FAFF4, ftKirby_800FB274, ftCamera_UpdateCameraBox },
    { 478, 0x0034042E, 0x2F000000, ftKirby_800FAC70, ftKirby_800FAF70,
      ftKirby_800FB014, ftKirby_800FB304, ftCamera_UpdateCameraBox },
};

HSD_GObjEvent lbl_803C9CC8[] = {
    ftKirby_800EFA40,
    ftKirby_800EFAF0,
    ftKirby_800EFB4C,
    ftKirby_800EFBFC,
    ftKirby_800EFC58,
    ftKirby_800EFD08,
    ftKirby_800F0FC0,
    ftKirby_800F10A4,
    NULL,
    NULL,
    ftKirby_800EFD64,
    ftKirby_800EFE1C,
    ftKirby_800EFE80,
    ftKirby_800EFF38,
    ftKirby_800EFF9C,
    ftKirby_800F0054,
    ftKirby_800F00B8,
    ftKirby_800F0168,
    ftKirby_800F01C4,
    ftKirby_800F0274,
    ftKirby_800F02D0,
    ftKirby_800F0380,
    NULL,
    NULL,
    ftKirby_800F03DC,
    ftKirby_800F0494,
    ftKirby_800F04F8,
    ftKirby_800F05A8,
    ftKirby_800F0604,
    ftKirby_800F06B4,
    ftKirby_800F10D4,
    ftKirby_800F11AC,
    ftKirby_800F11F0,
    ftKirby_800F12C8,
    ftKirby_800F0710,
    ftKirby_800F07C0,
    ftKirby_800F081C,
    ftKirby_800F08D4,
    ftKirby_800F0938,
    ftKirby_800F09F0,
    ftKirby_800F0A54,
    ftKirby_800F0B0C,
    ftKirby_800F0B70,
    ftKirby_800F0C20,
    ftKirby_800F130C,
    ftKirby_800F13F0,
    ftKirby_800F0C7C,
    ftKirby_800F0D34,
    ftKirby_800F14B4,
    ftKirby_800F15D8,
    ftKirby_800F0D98,
    ftKirby_800F0E48,
    ftKirby_800F0EA4,
    ftKirby_800F0F5C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKirby_800EFD64,
    ftKirby_800EFE1C,
    NULL,
    NULL,
};

HSD_GObjEvent lbl_803C9DD0[] = {
    ftKirby_800F9110,
    ftKirby_800FE100,
    ftKirby_800F99BC,
    ftKirby_800FF8EC,
    ftKirby_800F5F68,
    ftKirby_800FA8B4,
    ftKirby_800FB880,
    ftKirby_8010612C,
    ftKirby_800FED38,
    ftKirby_8010C4D4,
    ftKirby_80108D64,
    NULL,
    ftKirby_800F9FD4,
    ftKirby_800FCF74,
    ftKirby_8010941C,
    ftKirby_80101560,
    ftKirby_80107568,
    ftKirby_800F9614,
    ftKirby_8010B2FC,
    ftKirby_80105B2C,
    ftKirby_800FB880,
    ftKirby_800F9110,
    ftKirby_800FE100,
    ftKirby_800F9FD4,
    ftKirby_8010D188,
    ftKirby_800F99BC,
    ftKirby_8010B2FC,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKirby_800FA8B4,
    NULL,
};

HSD_GObjEvent lbl_803C9E54[] = {
    ftKirby_800F93CC,
    ftKirby_800FE240,
    ftKirby_800F9A54,
    ftKirby_800FFA10,
    ftKirby_800F6070,
    ftKirby_800FA958,
    ftKirby_800FBA00,
    ftKirby_801061E4,
    ftKirby_800FEDD0,
    ftKirby_8010C560,
    ftKirby_80108E14,
    NULL,
    ftKirby_800FA064,
    ftKirby_800FD020,
    ftKirby_801094FC,
    ftKirby_80101618,
    ftKirby_80107638,
    ftKirby_800F9684,
    ftKirby_8010B4A0,
    ftKirby_80105BA8,
    ftKirby_800FBA00,
    ftKirby_800F93CC,
    ftKirby_800FE240,
    ftKirby_800FA064,
    ftKirby_8010D204,
    ftKirby_800F9A54,
    ftKirby_8010B4A0,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKirby_800FA958,
    NULL,
};

typedef unk_t ftKirby_UnkArrayThing[12];

ftKirby_UnkArrayThing lbl_803C9ED8 = { 0 };
ftKirby_UnkArrayThing lbl_803C9F08 = { 0 };
ftKirby_UnkArrayThing lbl_803C9F38 = { 0 };
ftKirby_UnkArrayThing lbl_803C9F68 = { 0 };
ftKirby_UnkArrayThing lbl_803C9F98 = { 0 };

ftKirby_UnkArrayThing* lbl_803C9FC8[FTKIND_MAX] = {
    NULL, NULL,          NULL,          &lbl_803C9ED8, NULL, NULL, NULL,
    NULL, NULL,          NULL,          NULL,          NULL, NULL, NULL,
    NULL, &lbl_803C9F08, &lbl_803C9F38, NULL,          NULL, NULL, NULL,
    NULL, &lbl_803C9F68, NULL,          &lbl_803C9F98, NULL, NULL, NULL,
    NULL, NULL,          NULL,          NULL,          NULL,
};

MotionState lbl_803CA04C[] = {
    { 14, 0, 0x01000000, NULL, NULL, ft_800C737C, NULL, NULL },
    { 15, 0, 0x01000000, NULL, NULL, ft_800C737C, NULL, NULL },
    { 16, 0, 0x01000000, NULL, NULL, ft_800C737C, NULL, NULL },
    { 17, 0, 0x01000000, NULL, NULL, ft_800C7414, NULL, NULL },
};

/* static */ void ftKirby_800EE854(void);
/* static */ void ftKirby_800EE904(void);
/* static */ void ftKirby_800EE904(void);
/* static */ void ftKirby_800EE904(void);
/* static */ void ftKirby_800EE8EC(void);
/* static */ void ftKirby_800EE904(void);
/* static */ void ftKirby_800EE904(void);
/* static */ void ftKirby_800EE904(void);
/* static */ void ftKirby_800EE904(void);
/* static */ void ftKirby_800EE904(void);
/* static */ void ftKirby_800EE874(void);
/* static */ void ftKirby_800EE904(void);
/* static */ void ftKirby_800EE904(void);
/* static */ void ftKirby_800EE8B0(void);

jtbl_t jtbl_803CA0CC = {
    ftKirby_800EE854, ftKirby_800EE904, ftKirby_800EE904, ftKirby_800EE904,
    ftKirby_800EE8EC, ftKirby_800EE904, ftKirby_800EE904, ftKirby_800EE904,
    ftKirby_800EE904, ftKirby_800EE904, ftKirby_800EE874, ftKirby_800EE904,
    ftKirby_800EE904, ftKirby_800EE8B0,
};

char ftKirby_assert_msg_0[] = "fighter parts model dobj num over!\n";
char ftKirby_assert_msg_1[] = "ftkirby.c";
char ftKirby_assert_msg_2[] = "fighter dobj num over!\n";

/* static */ void ftKirby_800F1708(void);
/* static */ void ftKirby_800F1764(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F186C(void);
/* static */ void ftKirby_800F17A4(void);
/* static */ void ftKirby_800F1894(void);
/* static */ void ftKirby_800F17F8(void);
/* static */ void ftKirby_800F1744(void);
/* static */ void ftKirby_800F1730(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F1818(void);
/* static */ void ftKirby_800F1858(void);
/* static */ void ftKirby_800F18E8(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F17E4(void);
/* static */ void ftKirby_800F171C(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F17C4(void);
/* static */ void ftKirby_800F18B4(void);
/* static */ void ftKirby_800F1784(void);
/* static */ void ftKirby_800F1838(void);
/* static */ void ftKirby_800F18C8(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F18F8(void);
/* static */ void ftKirby_800F1880(void);

jtbl_t jtbl_803CA14C = {
    ftKirby_800F1708, ftKirby_800F1764, ftKirby_800F18F8, ftKirby_800F18F8,
    ftKirby_800F18F8, ftKirby_800F186C, ftKirby_800F17A4, ftKirby_800F1894,
    ftKirby_800F17F8, ftKirby_800F1744, ftKirby_800F1730, ftKirby_800F18F8,
    ftKirby_800F1818, ftKirby_800F1858, ftKirby_800F18E8, ftKirby_800F18F8,
    ftKirby_800F17E4, ftKirby_800F171C, ftKirby_800F18F8, ftKirby_800F18F8,
    ftKirby_800F17C4, ftKirby_800F18B4, ftKirby_800F1784, ftKirby_800F1838,
    ftKirby_800F18C8, ftKirby_800F18F8, ftKirby_800F18F8, ftKirby_800F18F8,
    ftKirby_800F18F8, ftKirby_800F18F8, ftKirby_800F18F8, ftKirby_800F1880,
};

/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A00(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A64(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A0C(void);
/* static */ void ftKirby_800F1A44(void);
/* static */ void ftKirby_800F1A2C(void);
/* static */ void ftKirby_800F19F4(void);
/* static */ void ftKirby_800F19E8(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A38(void);
/* static */ void ftKirby_800F1A50(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A20(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A0C(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A00(void);
/* static */ void ftKirby_800F1A78(void);
/* static */ void ftKirby_800F1A70(void);

jtbl_t jtbl_803CA1CC = {
    ftKirby_800F1A78, ftKirby_800F1A00, ftKirby_800F1A78, ftKirby_800F1A64,
    ftKirby_800F1A78, ftKirby_800F1A78, ftKirby_800F1A0C, ftKirby_800F1A44,
    ftKirby_800F1A2C, ftKirby_800F19F4, ftKirby_800F19E8, ftKirby_800F1A78,
    ftKirby_800F1A78, ftKirby_800F1A38, ftKirby_800F1A50, ftKirby_800F1A78,
    ftKirby_800F1A20, ftKirby_800F1A78, ftKirby_800F1A78, ftKirby_800F1A78,
    ftKirby_800F1A0C, ftKirby_800F1A78, ftKirby_800F1A00, ftKirby_800F1A78,
    ftKirby_800F1A70,
};

/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1AE0(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1B44(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1AEC(void);
/* static */ void ftKirby_800F1B24(void);
/* static */ void ftKirby_800F1B0C(void);
/* static */ void ftKirby_800F1AD4(void);
/* static */ void ftKirby_800F1AC8(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1B18(void);
/* static */ void ftKirby_800F1B30(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1B00(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1AEC(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1AE0(void);
/* static */ void ftKirby_800F1B58(void);
/* static */ void ftKirby_800F1B50(void);

jtbl_t jtbl_803CA230 = {
    ftKirby_800F1B58, ftKirby_800F1AE0, ftKirby_800F1B58, ftKirby_800F1B44,
    ftKirby_800F1B58, ftKirby_800F1B58, ftKirby_800F1AEC, ftKirby_800F1B24,
    ftKirby_800F1B0C, ftKirby_800F1AD4, ftKirby_800F1AC8, ftKirby_800F1B58,
    ftKirby_800F1B58, ftKirby_800F1B18, ftKirby_800F1B30, ftKirby_800F1B58,
    ftKirby_800F1B00, ftKirby_800F1B58, ftKirby_800F1B58, ftKirby_800F1B58,
    ftKirby_800F1AEC, ftKirby_800F1B58, ftKirby_800F1AE0, ftKirby_800F1B58,
    ftKirby_800F1B50,
};

/* static */ void ftKirby_800F1CD0(void);
/* static */ void ftKirby_800F1CD0(void);
/* static */ void ftKirby_800F1CC8(void);
/* static */ void ftKirby_800F1CD0(void);
/* static */ void ftKirby_800F1CD0(void);
/* static */ void ftKirby_800F1CD0(void);
/* static */ void ftKirby_800F1CD0(void);
/* static */ void ftKirby_800F1CC8(void);
/* static */ void ftKirby_800F1CD0(void);
/* static */ void ftKirby_800F1CD0(void);
/* static */ void ftKirby_800F1CC8(void);
/* static */ void ftKirby_800F1CC8(void);
/* static */ void ftKirby_800F1CD0(void);
/* static */ void ftKirby_800F1CC8(void);

jtbl_t jtbl_803CA294 = {
    ftKirby_800F1CD0, ftKirby_800F1CD0, ftKirby_800F1CC8, ftKirby_800F1CD0,
    ftKirby_800F1CD0, ftKirby_800F1CD0, ftKirby_800F1CD0, ftKirby_800F1CC8,
    ftKirby_800F1CD0, ftKirby_800F1CD0, ftKirby_800F1CC8, ftKirby_800F1CC8,
    ftKirby_800F1CD0, ftKirby_800F1CC8,
};

/* static */ void ftKirby_800F1D08(void);
/* static */ void ftKirby_800F1D08(void);
/* static */ void ftKirby_800F1D00(void);
/* static */ void ftKirby_800F1D08(void);
/* static */ void ftKirby_800F1D08(void);
/* static */ void ftKirby_800F1D08(void);
/* static */ void ftKirby_800F1D08(void);
/* static */ void ftKirby_800F1D00(void);
/* static */ void ftKirby_800F1D08(void);
/* static */ void ftKirby_800F1D08(void);
/* static */ void ftKirby_800F1D00(void);
/* static */ void ftKirby_800F1D00(void);
/* static */ void ftKirby_800F1D08(void);
/* static */ void ftKirby_800F1D00(void);

jtbl_t jtbl_803CA2CC = { ftKirby_800F1D08, ftKirby_800F1D08, ftKirby_800F1D00,
                         ftKirby_800F1D08, ftKirby_800F1D08, ftKirby_800F1D08,
                         ftKirby_800F1D08, ftKirby_800F1D00, ftKirby_800F1D08,
                         ftKirby_800F1D08, ftKirby_800F1D00, ftKirby_800F1D00,
                         ftKirby_800F1D08, ftKirby_800F1D00, NULL };

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

Fighter_DemoStrings lbl_803CA55C = {
    "ftDemoResultMotionFileKirby",
    "ftDemoIntroMotionFileKirby",
    "ftDemoEndingMotionFileKirby",
    "ftDemoViWaitMotionFileKirby",
};

char* lbl_803CA5A4[] = {
    "ftDemoVi0501MotionFileKirby",
    NULL,
    NULL,
    "ftDemoVi0502MotionFileKirby",
};

Fighter_CostumeStrings lbl_803CA5B4[] = {
    { lbl_803CA320, lbl_803CA32C, lbl_803CA344 },
    { lbl_803CA364, lbl_803CA370, lbl_803CA38C },
    { lbl_803CA3B0, lbl_803CA3BC, lbl_803CA3D8 },
    { lbl_803CA3FC, lbl_803CA408, lbl_803CA424 },
    { lbl_803CA448, lbl_803CA454, lbl_803CA470 },
    { lbl_803CA494, lbl_803CA4A0, lbl_803CA4BC },
};

typedef struct ftKirby_CopyName {
    char* filename;
    char* name;
} ftKirby_CopyName;

ftKirby_CopyName lbl_803CA9D0[FTKIND_MAX] = {
    { "PlKbCpMr.dat", "ftDataKirbyCopyMario" },
    { "PlKbCpFx.dat", "ftDataKirbyCopyFox" },
    { "PlKbCpCa.dat", "ftDataKirbyCopyCaptain" },
    { "PlKbCpDk.dat", "ftDataKirbyCopyDonkey" },
    { NULL, NULL },
    { "PlKbCpKp.dat", "ftDataKirbyCopyKoopa" },
    { "PlKbCpLk.dat", "ftDataKirbyCopyLink" },
    { "PlKbCpSk.dat", "ftDataKirbyCopySeak" },
    { "PlKbCpNs.dat", "ftDataKirbyCopyNess" },
    { "PlKbCpPe.dat", "ftDataKirbyCopyPeach" },
    { "PlKbCpPp.dat", "ftDataKirbyCopyPopo" },
    { NULL, NULL },
    { "PlKbCpPk.dat", "ftDataKirbyCopyPikachu" },
    { "PlKbCpSs.dat", "ftDataKirbyCopySamus" },
    { "PlKbCpYs.dat", "ftDataKirbyCopyYoshi" },
    { "PlKbCpPr.dat", "ftDataKirbyCopyPurin" },
    { "PlKbCpMt.dat", "ftDataKirbyCopyMewtwo" },
    { "PlKbCpLg.dat", "ftDataKirbyCopyLuigi" },
    { "PlKbCpMs.dat", "ftDataKirbyCopyMars" },
    { "PlKbCpZd.dat", "ftDataKirbyCopyZelda" },
    { "PlKbCpCl.dat", "ftDataKirbyCopyClink" },
    { "PlKbCpDr.dat", "ftDataKirbyCopyDrmario" },
    { "PlKbCpFc.dat", "ftDataKirbyCopyFalco" },
    { "PlKbCpPc.dat", "ftDataKirbyCopyPichu" },
    { "PlKbCpGw.dat", "ftDataKirbyCopyGamewatch" },
    { "PlKbCpGn.dat", "ftDataKirbyCopyGanon" },
    { "PlKbCpFe.dat", "ftDataKirbyCopyEmblem" },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
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
    int ints[6];
    Vec3 vec;
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
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106464(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106464(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106464(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106464(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106464(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106474(void);
/* static */ void ftKirby_80106464(void);

jtbl_t jtbl_803CB794 = {
    ftKirby_80106474, ftKirby_80106474, ftKirby_80106464, ftKirby_80106474,
    ftKirby_80106474, ftKirby_80106464, ftKirby_80106474, ftKirby_80106474,
    ftKirby_80106464, ftKirby_80106474, ftKirby_80106474, ftKirby_80106464,
    ftKirby_80106474, ftKirby_80106474, ftKirby_80106464, ftKirby_80106474,
    ftKirby_80106474, ftKirby_80106464,
};
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066B4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066B4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066B4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066B4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066B4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066C4(void);
/* static */ void ftKirby_801066B4(void);

jtbl_t jtbl_803CB7DC = {
    ftKirby_801066C4,
    ftKirby_801066C4,
    ftKirby_801066B4,
    ftKirby_801066C4,
    ftKirby_801066C4,
    ftKirby_801066B4,
    ftKirby_801066C4,
    ftKirby_801066C4,
    ftKirby_801066B4,
    ftKirby_801066C4,
    ftKirby_801066C4,
    ftKirby_801066B4,
    ftKirby_801066C4,
    ftKirby_801066C4,
    ftKirby_801066B4,
    ftKirby_801066C4,
    ftKirby_801066C4,
    ftKirby_801066B4,
    NULL,
};

uint lbl_803CB828[] = { 0x00030DB9, 0x00030DBC, 0x00030DBF, 0x00030DC2 };

f32 const lbl_803B7548[10] = { 0 };
Vec3 const lbl_803B7570 = { 0, 4, 0 };
Vec3 const lbl_803B757C = { 0, 4, 0 };

#ifdef MWERKS_GEKKO
#pragma push
asm void ftKirby_800EE528(void)
{ // clang-format off
    nofralloc
/* 800EE528 00000000  38 00 00 21 */	li r0, 0x21
/* 800EE52C 00000004  3C 80 80 46 */	lis r4, lbl_80459B88@ha
/* 800EE530 00000008  7C 09 03 A6 */	mtctr r0
/* 800EE534 0000000C  3C 60 80 3D */	lis r3, lbl_803C9FC8@ha
/* 800EE538 00000010  38 84 9B 88 */	addi r4, r4, lbl_80459B88@l
/* 800EE53C 00000014  38 A3 9F C8 */	addi r5, r3, lbl_803C9FC8@l
lbl_800EE540:
/* 800EE540 00000018  38 00 00 00 */	li r0, 0x0
/* 800EE544 0000001C  90 04 00 00 */	stw r0, 0x0(r4)
/* 800EE548 00000020  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE54C 00000024  28 03 00 00 */	cmplwi r3, 0x0
/* 800EE550 00000028  41 82 00 60 */	beq lbl_800EE5B0
/* 800EE554 0000002C  90 03 00 00 */	stw r0, 0x0(r3)
/* 800EE558 00000030  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE55C 00000034  90 03 00 04 */	stw r0, 0x4(r3)
/* 800EE560 00000038  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE564 0000003C  90 03 00 08 */	stw r0, 0x8(r3)
/* 800EE568 00000040  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE56C 00000044  90 03 00 0C */	stw r0, 0xc(r3)
/* 800EE570 00000048  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE574 0000004C  90 03 00 10 */	stw r0, 0x10(r3)
/* 800EE578 00000050  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE57C 00000054  90 03 00 14 */	stw r0, 0x14(r3)
/* 800EE580 00000058  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE584 0000005C  90 03 00 18 */	stw r0, 0x18(r3)
/* 800EE588 00000060  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE58C 00000064  90 03 00 1C */	stw r0, 0x1c(r3)
/* 800EE590 00000068  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE594 0000006C  90 03 00 20 */	stw r0, 0x20(r3)
/* 800EE598 00000070  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE59C 00000074  90 03 00 24 */	stw r0, 0x24(r3)
/* 800EE5A0 00000078  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE5A4 0000007C  90 03 00 28 */	stw r0, 0x28(r3)
/* 800EE5A8 00000080  80 65 00 00 */	lwz r3, 0x0(r5)
/* 800EE5AC 00000084  90 03 00 2C */	stw r0, 0x2c(r3)
lbl_800EE5B0:
/* 800EE5B0 00000088  38 84 00 04 */	addi r4, r4, 0x4
/* 800EE5B4 0000008C  38 A5 00 04 */	addi r5, r5, 0x4
/* 800EE5B8 00000090  42 00 FF 88 */	bdnz lbl_800EE540
/* 800EE5BC 00000094  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#elif false

// https://decomp.me/scratch/6dL9q
void ftKirby_800EE528(void)
{
    s32* number_list = lbl_80459B88;
    ftKirby_UnkArrayThing** struct_list = lbl_803C9FC8;

    s32 i;
    for (i = 0; i < FTKIND_MAX; i++) {
        struct S_KIRBY1* unk_struct;
        number_list[i] = 0;
        unk_struct = struct_list[i];
        if (unk_struct) {
            unk_struct->x0 = 0;
            unk_struct = struct_list[i];
            unk_struct->x4 = 0;
            unk_struct = struct_list[i];
            unk_struct->x8 = 0;
            unk_struct = struct_list[i];
            unk_struct->xC = 0;
            unk_struct = struct_list[i];
            unk_struct->x10 = 0;
            unk_struct = struct_list[i];
            unk_struct->x14 = 0;
            unk_struct = struct_list[i];
            unk_struct->x18 = 0;
            unk_struct = struct_list[i];
            unk_struct->x1C = 0;
            unk_struct = struct_list[i];
            unk_struct->x20 = 0;
            unk_struct = struct_list[i];
            unk_struct->x24 = 0;
            unk_struct = struct_list[i];
            unk_struct->x28 = 0;
            unk_struct = struct_list[i];
            unk_struct->x2C = 0;
        }
    }
}

#endif

void ftKirby_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    ftParts_80074A4C(gobj, 1, 0);
    fp->fv.kb.x222C = 0;
    fp->fv.kb.x2230 = (s32) (HSD_Randi(5) + 1);
    fp->fv.kb.x223C = 0;
    fp->fv.kb.x2238 = 4;
    fp->fv.kb.x2244 = 0;
    fp->fv.kb.x228C = 0;
    fp->fv.kb.x2290 = 0;
    if (Player_GetFlagsBit1(fp->xC_playerID) &&
        Player_GetUnk4D(fp->xC_playerID) != 4)
    {
        ftKirby_800F1BAC(gobj, Player_GetUnk4D(fp->xC_playerID), 0);
    }
}

void ftKirby_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftKirbyAttributes);

    fp->x2222_flag.bits.b1 = 1;
    fp->x2D0 = fp->x2D4_specialAttributes;
    fp->fv.kb.x2234.bits.b0 = Player_GetFlagsAEBit1(fp->xC_playerID);
    func_8026B3F8(item_list[0], 0x32);
    func_8026B3F8(item_list[1], 0x33);
    func_8026B3F8(item_list[2], 0x34);
    func_8026B3F8(item_list[3], 0x35);
}

void ftKirby_800EE74C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKirby_800F5524(gobj);
    ftKirby_800F22D4(gobj);
    ftKirby_800F5318(gobj);
    ftKirby_800F9090(gobj);
    ftKirby_800F19AC(gobj);
    ftKirby_800F5D04(gobj, false);
    fp->cb.x21E8_callback_OnDeath3 = NULL;
}

void ftKirby_800EE7B8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKirby_800F5524(gobj);
    ftKirby_800F22D4(gobj);
    ftKirby_800F5318(gobj);
    ftKirby_800F9090(gobj);
    ftKirby_800F1A8C(gobj);
    fp->cb.x21E0_callback_OnDeath = NULL;
}

/// @file
/// @todo Matching, but needs more data moved over for DOL match

#if false

void ftKirby_800EE818(HSD_GObj* gobj)
{
    s32 _[2];
    Fighter* fp = GET_FIGHTER(gobj);
    ftKirbyAttributes* attr = fp->x2D4_specialAttributes;
    switch (fp->fv.kb.x2238) {
    case 3:
        if (fp->fv.kb.x22E8 == attr->x190) {
            ft_800BFFD0(fp, 0x3A, 0);
        }
        break;
    case 13:
        if (fp->fv.kb.x22D4 == attr->x168) {
            ft_800BFFD0(fp, 0x36, 0);
        }
        break;
    case 16:
        if (fp->fv.kb.x22C8 == attr->x384) {
            ft_800BFFD0(fp, 0x5D, 0);
            return;
        }
        break;
    case 7:
        if (fp->fv.kb.x22E0 == 6) {
            ft_800BFFD0(fp, 0x57, 0);
        }
        break;
    }
}

void ftKirby_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftKirby_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftKirby_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftKirby_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftKirbyAttributes);
}

void ftKirby_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftKirby_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

#endif

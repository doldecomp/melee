#include "ft/forward.h"

#include "ftKirby/ftkirby.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <dolphin/mtx/types.h>

MotionState ftKb_Init_MotionStateTable[] = {
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
    { 52, 0x00240005, 0x06000000, ftKb_800F203C, ftKb_800F205C, ftKb_800F207C,
      ftKb_800F209C, ftCamera_UpdateCameraBox },
    { 52, 0x00240405, 0x06000000, ftKb_800F2124, ftKb_800F2160, ftKb_800F2164,
      ftKb_800F2198, ftCamera_UpdateCameraBox },
    { 305, 0x00340011, 0x12000000, ftKb_800F70A0, NULL, ftKb_800F8890,
      ftKb_800F8C10, ftCamera_UpdateCameraBox },
    { 306, 0x003C0011, 0x12000000, ftKb_800F72F8, ftKb_800F7FA0, ftKb_800F88D0,
      ftKb_800F8C60, ftCamera_UpdateCameraBox },
    { 307, 0x00340011, 0x12000000, ftKb_800F7300, NULL, ftKb_800F8910,
      ftKb_800F8CB0, ftCamera_UpdateCameraBox },
    { 308, 0x00340011, 0x12000000, ftKb_800F7498, NULL, ftKb_800F8970,
      ftKb_800F8D28, ftCamera_UpdateCameraBox },
    { 308, 0x00340011, 0x12000000, ftKb_800F7378, NULL, ftKb_800F8950,
      ftKb_800F8D00, ftCamera_UpdateCameraBox },
    { 309, 0x00340011, 0x12000000, ftKb_800F75F8, NULL, ftKb_800F89D0,
      ftKb_800F8DA0, ftCamera_UpdateCameraBox },
    { 310, 0x00340011, 0x12400000, ftKb_800F76F8, ftKb_800F8060, ftKb_800F8A10,
      ftKb_800F8DF0, ftCamera_UpdateCameraBox },
    { 311, 0x00344011, 0x12000000, ftKb_800F7E78, ftKb_800F8770, ftKb_800F8B90,
      ftKb_800F8FD0, ftCamera_UpdateCameraBox },
    { 312, 0x00344011, 0x12000000, ftKb_800F7E78, ftKb_800F8770, ftKb_800F8B90,
      ftKb_800F8FD0, ftCamera_UpdateCameraBox },
    { 313, 0x00344011, 0x12000000, ftKb_800F7E78, ftKb_800F8770, ftKb_800F8B90,
      ftKb_800F8FD0, ftCamera_UpdateCameraBox },
    { 317, 0x00342011, 0x12000000, ftKb_800F7D58, NULL, ftKb_800F8B50,
      ftKb_800F8F80, ftCamera_UpdateCameraBox },
    { 314, 0x00348011, 0x12000000, ftKb_800F7E98, ftKb_800F8870, ftKb_800F8BB0,
      ftKb_800F8FF8, ftCamera_UpdateCameraBox },
    { 315, 0x00340011, 0x12000000, ftKb_800F7F20, NULL, ftKb_800F8BD0,
      ftKb_800F9020, ftCamera_UpdateCameraBox },
    { 316, 0x00340011, 0x12400000, ftKb_800F7F24, NULL, ftKb_800F8BF0,
      ftKb_800F9048, ftCamera_UpdateCameraBox },
    { 318, 0x00340011, 0x12000000, ftKb_800F7B20, NULL, ftKb_800F8AF0,
      ftKb_800F8F08, ftCamera_UpdateCameraBox },
    { 318, 0x00340011, 0x12000000, ftKb_800F7A70, NULL, ftKb_800F8AD0,
      ftKb_800F8EE0, ftCamera_UpdateCameraBox },
    { 319, 0x00340011, 0x12000000, ftKb_800F7808, NULL, ftKb_800F8A70,
      ftKb_800F8E68, ftCamera_UpdateCameraBox },
    { 319, 0x00340011, 0x12000000, ftKb_800F7700, NULL, ftKb_800F8A50,
      ftKb_800F8E40, ftCamera_UpdateCameraBox },
    { 320, 0x00340411, 0x12000000, ftKb_800F71CC, NULL, ftKb_800F88B0,
      ftKb_800F8C38, ftCamera_UpdateCameraBox },
    { 321, 0x003C0411, 0x12000000, ftKb_800F72FC, ftKb_800F8000, ftKb_800F88F0,
      ftKb_800F8C88, ftCamera_UpdateCameraBox },
    { 307, 0x00340411, 0x12000000, ftKb_800F733C, NULL, ftKb_800F8930,
      ftKb_800F8CD8, ftCamera_UpdateCameraBox },
    { 308, 0x00340411, 0x12000000, ftKb_800F75D8, NULL, ftKb_800F89B0,
      ftKb_800F8D78, ftCamera_UpdateCameraBox },
    { 308, 0x00340411, 0x12000000, ftKb_800F75B8, NULL, ftKb_800F8990,
      ftKb_800F8D50, ftCamera_UpdateCameraBox },
    { 309, 0x00340411, 0x12000000, ftKb_800F7674, NULL, ftKb_800F89F0,
      ftKb_800F8DC8, ftCamera_UpdateCameraBox },
    { 310, 0x00340411, 0x12000000, ftKb_800F76FC, ftKb_800F844C, ftKb_800F8A30,
      ftKb_800F8E18, ftCamera_UpdateCameraBox },
    { 318, 0x00340411, 0x12000000, ftKb_800F7C94, NULL, ftKb_800F8B30,
      ftKb_800F8F58, ftCamera_UpdateCameraBox },
    { 318, 0x00340411, 0x12000000, ftKb_800F7BE4, NULL, ftKb_800F8B10,
      ftKb_800F8F30, ftCamera_UpdateCameraBox },
    { 319, 0x00340411, 0x12000000, ftKb_800F79C0, NULL, ftKb_800F8AB0,
      ftKb_800F8EB8, ftCamera_UpdateCameraBox },
    { 319, 0x00340411, 0x12000000, ftKb_800F78B8, NULL, ftKb_800F8A90,
      ftKb_800F8E90, ftCamera_UpdateCameraBox },
    { 317, 0x00342411, 0x12000000, ftKb_800F7DE4, NULL, ftKb_800F8B70,
      ftKb_800F8FA8, ftCamera_UpdateCameraBox },
    { 322, 0x00340012, 0x13000000, ftKb_800F5660, NULL, ftKb_800F56D8,
      ftKb_800F5718, ftCamera_UpdateCameraBox },
    { 323, 0x00340412, 0x13000000, ftKb_800F569C, NULL, ftKb_800F56F8,
      ftKb_800F5778, ftCamera_UpdateCameraBox },
    { 324, 0x00340013, 0x14000000, ftKb_800F2470, ftKb_800F2758, ftKb_800F2910,
      ftKb_800F2BBC, ftCamera_UpdateCameraBox },
    { 325, 0x00340013, 0x14000000, ftKb_800F24F8, ftKb_800F2828, ftKb_800F2984,
      ftKb_800F2C5C, ftCamera_UpdateCameraBox },
    { 326, 0x00340013, 0x14000000, ftKb_800F2578, ftKb_800F282C, ftKb_800F29F8,
      ftKb_800F2D98, ftCamera_UpdateCameraBox },
    { 327, 0x00340013, 0x14000000, ftKb_800F257C, ftKb_800F2830, ftKb_800F2A48,
      ftKb_800F2EA0, ftCamera_UpdateCameraBox },
    { 328, 0x00340413, 0x14000000, ftKb_800F25EC, ftKb_800F2834, ftKb_800F2A68,
      ftKb_800F2F70, ftCamera_UpdateCameraBox },
    { 329, 0x00340413, 0x14000000, ftKb_800F266C, ftKb_800F2904, ftKb_800F2AE4,
      ftKb_800F3004, ftCamera_UpdateCameraBox },
    { 330, 0x00340413, 0x14000000, ftKb_800F26E4, ftKb_800F2908, ftKb_800F2B60,
      ftKb_800F3140, ftCamera_UpdateCameraBox },
    { 331, 0x00340413, 0x14000000, ftKb_800F26E8, ftKb_800F290C, ftKb_800F2B9C,
      ftKb_800F3248, ftCamera_UpdateCameraBox },
    { 332, 0x00340214, 0x15000000, ftKb_800F3F80, ftKb_800F42D8, ftKb_800F451C,
      ftKb_800F4628, ftCamera_UpdateCameraBox },
    { 333, 0x00340214, 0x15000000, ftKb_800F402C, ftKb_800F42DC, ftKb_800F453C,
      ftKb_800F4800, ftCamera_UpdateCameraBox },
    { 334, 0x00340214, 0x15000000, ftKb_800F4074, ftKb_800F43FC, ftKb_800F4584,
      ftKb_800F49E4, ftCamera_UpdateCameraBox },
    { 335, 0x00340614, 0x15000000, ftKb_800F412C, ftKb_800F4400, ftKb_800F45A4,
      ftKb_800F4B3C, ftCamera_UpdateCameraBox },
    { 336, 0x00340614, 0x15000000, ftKb_800F41D8, ftKb_800F4404, ftKb_800F45C4,
      ftKb_800F4E78, ftCamera_UpdateCameraBox },
    { 337, 0x00340614, 0x15000000, ftKb_800F4220, ftKb_800F4518, ftKb_800F4608,
      ftKb_800F51C0, ftCamera_UpdateCameraBox },
    { 338, 0x00340015, 0x16000000, ftKb_800F9198, ftKb_800F91D4, ftKb_800F9204,
      ftKb_800F9224, ftCamera_UpdateCameraBox },
    { 339, 0x00340415, 0x16000000, ftKb_800F9454, ftKb_800F9490, ftKb_800F94C0,
      ftKb_800F94E0, ftCamera_UpdateCameraBox },
    { 340, 0x0034011A, 0x1B000000, ftKb_800FBBC4, ftKb_800FC374, ftKb_800FC70C,
      ftKb_800FC7CC, ftCamera_UpdateCameraBox },
    { 341, 0x003C011A, 0x1B000000, ftKb_800FBDFC, ftKb_800FC46C, ftKb_800FC72C,
      ftKb_800FC880, ftCamera_UpdateCameraBox },
    { 342, 0x0034011A, 0x1B000000, ftKb_800FBED0, ftKb_800FC53C, ftKb_800FC74C,
      ftKb_800FC934, ftCamera_UpdateCameraBox },
    { 343, 0x0034051A, 0x1B000000, ftKb_800FBF34, ftKb_800FC540, ftKb_800FC76C,
      ftKb_800FC9F0, ftCamera_UpdateCameraBox },
    { 344, 0x003C051A, 0x1B000000, ftKb_800FC1A0, ftKb_800FC638, ftKb_800FC78C,
      ftKb_800FCAA4, ftCamera_UpdateCameraBox },
    { 345, 0x0034051A, 0x1B000000, ftKb_800FC274, ftKb_800FC708, ftKb_800FC7AC,
      ftKb_800FCB58, ftCamera_UpdateCameraBox },
    { 346, 0x00340120, 0x21000000, ftKb_800FD0BC, ftKb_800FD688, ftKb_800FD7F0,
      ftKb_800FD8B0, ftCamera_UpdateCameraBox },
    { 347, 0x00340120, 0x21000000, ftKb_800FD250, ftKb_800FD68C, ftKb_800FD810,
      ftKb_800FD938, ftCamera_UpdateCameraBox },
    { 348, 0x00340120, 0x21000000, ftKb_800FD418, ftKb_800FD7E0, ftKb_800FD830,
      ftKb_800FD9E0, ftCamera_UpdateCameraBox },
    { 349, 0x00340120, 0x21000000, ftKb_800FD49C, ftKb_800FD7E4, ftKb_800FD850,
      ftKb_800FDA68, ftCamera_UpdateCameraBox },
    { 350, 0x00340520, 0x21000000, ftKb_800FD4E0, ftKb_800FD7E8, ftKb_800FD870,
      ftKb_800FDAF0, ftCamera_UpdateCameraBox },
    { 351, 0x00340520, 0x21000000, ftKb_800FD608, ftKb_800FD7EC, ftKb_800FD890,
      ftKb_800FDB78, ftCamera_UpdateCameraBox },
    { 352, 0x00340021, 0x22000000, ftKb_80109D6C, NULL, ftKb_8010A5EC,
      ftKb_8010A72C, ftCamera_UpdateCameraBox },
    { 353, 0x00340021, 0x22000000, ftKb_80109EE8, NULL, ftKb_8010A64C,
      ftKb_8010A7A4, ftCamera_UpdateCameraBox },
    { 353, 0x00340021, 0x22000000, ftKb_80109E04, NULL, ftKb_8010A62C,
      ftKb_8010A77C, ftCamera_UpdateCameraBox },
    { 354, 0x00340021, 0x12000000, ftKb_8010A304, NULL, ftKb_8010A6CC,
      ftKb_8010A844, ftCamera_UpdateCameraBox },
    { 354, 0x00340021, 0x12000000, ftKb_8010A1A4, NULL, ftKb_8010A6AC,
      ftKb_8010A81C, ftCamera_UpdateCameraBox },
    { 355, 0x00340421, 0x22000000, ftKb_80109DB8, NULL, ftKb_8010A60C,
      ftKb_8010A754, ftCamera_UpdateCameraBox },
    { 356, 0x00340421, 0x22000000, ftKb_8010A0B8, NULL, ftKb_8010A66C,
      ftKb_8010A7F4, ftCamera_UpdateCameraBox },
    { 356, 0x00340421, 0x22000000, ftKb_80109FD4, NULL, ftKb_8010A68C,
      ftKb_8010A7CC, ftCamera_UpdateCameraBox },
    { 357, 0x00340421, 0x22000000, ftKb_8010A528, NULL, ftKb_8010A70C,
      ftKb_8010A894, ftCamera_UpdateCameraBox },
    { 357, 0x00340421, 0x22000000, ftKb_8010A3C8, NULL, ftKb_8010A6EC,
      ftKb_8010A86C, ftCamera_UpdateCameraBox },
    { 358, 0x00340116, 0x17000000, ftKb_800FE360, ftKb_800FEA50, ftKb_800FEAF8,
      ftKb_800FEBB8, ftCamera_UpdateCameraBox },
    { 359, 0x003C0116, 0x17000000, ftKb_800FE450, ftKb_800FEA78, ftKb_800FEB18,
      ftKb_800FEBD8, ftCamera_UpdateCameraBox },
    { 360, 0x00340116, 0x17000000, ftKb_800FE5C8, ftKb_800FEAA0, ftKb_800FEB38,
      ftKb_800FEBF8, ftCamera_UpdateCameraBox },
    { 361, 0x00340516, 0x17000000, ftKb_800FE688, ftKb_800FEAA4, ftKb_800FEB58,
      ftKb_800FEC18, ftCamera_UpdateCameraBox },
    { 362, 0x003C0516, 0x17000000, ftKb_800FE778, ftKb_800FEACC, ftKb_800FEB78,
      ftKb_800FEC38, ftCamera_UpdateCameraBox },
    { 363, 0x00340516, 0x17000000, ftKb_800FE928, ftKb_800FEAF4, ftKb_800FEB98,
      ftKb_800FEC58, ftCamera_UpdateCameraBox },
    { 364, 0x0034011F, 0x20000000, ftKb_800FA0F4, ftKb_800FA418, ftKb_800FA420,
      ftKb_800FA460, ftCamera_UpdateCameraBox },
    { 365, 0x0034051F, 0x20000000, ftKb_800FA254, ftKb_800FA41C, ftKb_800FA440,
      ftKb_800FA4F0, ftCamera_UpdateCameraBox },
    { 366, 0x00340024, 0x25000000, ftKb_800F96F4, ftKb_800F976C, ftKb_800F97CC,
      ftKb_800F980C, ftCamera_UpdateCameraBox },
    { 367, 0x00340424, 0x25000000, ftKb_800F9730, ftKb_800F979C, ftKb_800F97EC,
      ftKb_800F9880, ftCamera_UpdateCameraBox },
    { 368, 0x00340217, 0x18000000, ftKb_800F9AEC, ftKb_800F9B64, ftKb_800F9C58,
      ftKb_800F9E8C, ftCamera_UpdateCameraBox },
    { 369, 0x00340617, 0x18000000, ftKb_800F9B28, ftKb_800F9B68, ftKb_800F9D40,
      ftKb_800F9F34, ftCamera_UpdateCameraBox },
    { 370, 0x0034011C, 0x1D000000, ftKb_800FEE70, ftKb_800FF3DC, ftKb_800FF4CC,
      ftKb_800FF664, ftCamera_UpdateCameraBox },
    { 371, 0x0034011C, 0x1D000000, ftKb_800FEF58, ftKb_800FF3E0, ftKb_800FF504,
      ftKb_800FF6D0, ftCamera_UpdateCameraBox },
    { 372, 0x0034011C, 0x1D000000, ftKb_800FEF58, ftKb_800FF3E0, ftKb_800FF504,
      ftKb_800FF6D0, ftCamera_UpdateCameraBox },
    { 373, 0x0034011C, 0x1D000000, ftKb_800FF08C, ftKb_800FF450, ftKb_800FF524,
      ftKb_800FF73C, ftCamera_UpdateCameraBox },
    { 374, 0x0034051C, 0x1D000000, ftKb_800FF10C, ftKb_800FF454, ftKb_800FF544,
      ftKb_800FF7A8, ftCamera_UpdateCameraBox },
    { 375, 0x0034051C, 0x1D000000, ftKb_800FF1F4, ftKb_800FF458, ftKb_800FF5A4,
      ftKb_800FF814, ftCamera_UpdateCameraBox },
    { 376, 0x0034051C, 0x1D000000, ftKb_800FF1F4, ftKb_800FF458, ftKb_800FF5A4,
      ftKb_800FF814, ftCamera_UpdateCameraBox },
    { 377, 0x0034051C, 0x1D000000, ftKb_800FF328, ftKb_800FF4C8, ftKb_800FF604,
      ftKb_800FF880, ftCamera_UpdateCameraBox },
    { 378, 0x00340019, 0x1A000000, ftKb_800FA9FC, ftKb_800FACAC, ftKb_800FAF74,
      ftKb_800FB034, ftCamera_UpdateCameraBox },
    { 379, 0x003C0019, 0x1A000000, ftKb_800FAA74, ftKb_800FACB0, ftKb_800FAF94,
      ftKb_800FB0C4, ftCamera_UpdateCameraBox },
    { 380, 0x00340019, 0x1A000000, ftKb_800FAB18, ftKb_800FAE0C, ftKb_800FAFB4,
      ftKb_800FB154, ftCamera_UpdateCameraBox },
    { 381, 0x00340419, 0x1A000000, ftKb_800FAB54, ftKb_800FAE10, ftKb_800FAFD4,
      ftKb_800FB1E4, ftCamera_UpdateCameraBox },
    { 382, 0x003C0419, 0x1A000000, ftKb_800FABCC, ftKb_800FAE14, ftKb_800FAFF4,
      ftKb_800FB274, ftCamera_UpdateCameraBox },
    { 383, 0x00340419, 0x1A000000, ftKb_800FAC70, ftKb_800FAF70, ftKb_800FB014,
      ftKb_800FB304, ftCamera_UpdateCameraBox },
    { 384, 0x0034001D, 0x1E000000, ftKb_8010C5FC, ftKb_8010C774, ftKb_8010C77C,
      ftKb_8010C860, ftCamera_UpdateCameraBox },
    { 385, 0x0034001D, 0x1E000000, ftKb_8010CAB4, ftKb_8010CB7C, ftKb_8010CB84,
      ftKb_8010CBF4, ftCamera_UpdateCameraBox },
    { 386, 0x0034041D, 0x1E000000, ftKb_8010C6B8, ftKb_8010C778, ftKb_8010C7B0,
      ftKb_8010C89C, ftCamera_UpdateCameraBox },
    { 387, 0x0034041D, 0x1E000000, ftKb_8010CB18, ftKb_8010CB80, ftKb_8010CBA4,
      ftKb_8010CC30, ftCamera_UpdateCameraBox },
    { 388, 0x0034011E, 0x1F000000, ftKb_80108EFC, ftKb_80108F74, ftKb_80108F7C,
      ftKb_80108FBC, ftCamera_UpdateCameraBox },
    { 389, 0x0034051E, 0x1F000000, ftKb_80108F38, ftKb_80108F78, ftKb_80108F9C,
      ftKb_80109030, ftCamera_UpdateCameraBox },
    { 390, 0x00340218, 0x19000000, ftKb_800FFB24, ftKb_801003DC, ftKb_80100660,
      ftKb_801007A0, ftCamera_UpdateCameraBox },
    { 391, 0x00340218, 0x19000000, ftKb_800FFBAC, ftKb_801003E0, ftKb_80100680,
      ftKb_80100840, ftCamera_UpdateCameraBox },
    { 392, 0x00340218, 0x19000000, ftKb_800FFC48, ftKb_80100518, ftKb_801006A0,
      ftKb_801008E0, ftCamera_UpdateCameraBox },
    { 393, 0x00340218, 0x19000000, ftKb_800FFC94, ftKb_8010051C, ftKb_801006C0,
      ftKb_80100980, ftCamera_UpdateCameraBox },
    { 394, 0x00340218, 0x19000000, ftKb_800FFE6C, ftKb_80100520, ftKb_801006E0,
      ftKb_80100A20, ftCamera_UpdateCameraBox },
    { 395, 0x00340618, 0x19000000, ftKb_800FFFB8, ftKb_80100524, ftKb_80100700,
      ftKb_80100AC0, ftCamera_UpdateCameraBox },
    { 396, 0x00340618, 0x19000000, ftKb_80100040, ftKb_80100528, ftKb_80100720,
      ftKb_80100B60, ftCamera_UpdateCameraBox },
    { 397, 0x00340618, 0x19000000, ftKb_801000DC, ftKb_80100654, ftKb_80100740,
      ftKb_80100C00, ftCamera_UpdateCameraBox },
    { 398, 0x00340618, 0x19000000, ftKb_80100128, ftKb_80100658, ftKb_80100760,
      ftKb_80100CA0, ftCamera_UpdateCameraBox },
    { 399, 0x00340618, 0x19000000, ftKb_801002C8, ftKb_8010065C, ftKb_80100780,
      ftKb_80100D40, ftCamera_UpdateCameraBox },
    { 400, 0x00340026, 0x27000000, ftKb_80105C3C, ftKb_80105D64, ftKb_80105D6C,
      ftKb_80105E14, ftCamera_UpdateCameraBox },
    { 401, 0x00340426, 0x27000000, ftKb_80105CD0, ftKb_80105D68, ftKb_80105DA0,
      ftKb_80105E50, ftCamera_UpdateCameraBox },
    { 402, 0x0034011B, 0x1C000000, ftKb_8010629C, ftKb_8010672C, ftKb_801068FC,
      ftKb_801069FC, ftCamera_UpdateCameraBox },
    { 403, 0x003C011B, 0x1C000000, ftKb_80106334, ftKb_80106730, ftKb_8010691C,
      ftKb_80106A84, ftCamera_UpdateCameraBox },
    { 404, 0x0034011B, 0x1C000000, ftKb_801063E0, ftKb_8010680C, ftKb_8010693C,
      ftKb_80106B0C, ftCamera_UpdateCameraBox },
    { 405, 0x0034011B, 0x1C000000, ftKb_80106428, ftKb_80106810, ftKb_8010695C,
      ftKb_80106B84, ftCamera_UpdateCameraBox },
    { 406, 0x0034051B, 0x1C000000, ftKb_801064AC, ftKb_80106814, ftKb_8010697C,
      ftKb_80106C10, ftCamera_UpdateCameraBox },
    { 407, 0x003C051B, 0x1C000000, ftKb_80106544, ftKb_80106818, ftKb_8010699C,
      ftKb_80106C98, ftCamera_UpdateCameraBox },
    { 408, 0x0034051B, 0x1C000000, ftKb_801065F0, ftKb_801068F4, ftKb_801069BC,
      ftKb_80106D20, ftCamera_UpdateCameraBox },
    { 409, 0x0034051B, 0x1C000000, ftKb_80106670, ftKb_801068F8, ftKb_801069DC,
      ftKb_80106D5C, ftCamera_UpdateCameraBox },
    { 410, 0x00340222, 0x23000000, ftKb_801016CC, ftKb_801035C8, ftKb_80103D10,
      ftKb_801046A4, ftCamera_UpdateCameraBox },
    { 411, 0x00340222, 0x23000000, ftKb_801016CC, ftKb_801035C8, ftKb_80103D10,
      ftKb_801046A4, ftCamera_UpdateCameraBox },
    { 412, 0x003C0222, 0x23000000, ftKb_801017B0, ftKb_801035CC, ftKb_80103D40,
      ftKb_8010475C, ftCamera_UpdateCameraBox },
    { 413, 0x003C0222, 0x23000000, ftKb_80101960, ftKb_80103734, ftKb_80103D70,
      ftKb_80104864, ftCamera_UpdateCameraBox },
    { 414, 0x00340222, 0x23000000, ftKb_80101AD0, ftKb_8010389C, ftKb_80103DA0,
      ftKb_8010496C, ftCamera_UpdateCameraBox },
    { 415, 0x00340222, 0x23000000, ftKb_80101EA0, ftKb_80103A24, ftKb_80103FA8,
      ftKb_80104D14, ftCamera_UpdateCameraBox },
    { 416, 0x00340222, 0x23000000, ftKb_80102198, ftKb_80103A28, ftKb_801042AC,
      ftKb_80104DF8, ftCamera_UpdateCameraBox },
    { 417, 0x00340222, 0x23000000, ftKb_80102198, ftKb_80103A28, ftKb_801042AC,
      ftKb_80104DF8, ftCamera_UpdateCameraBox },
    { 418, 0x00340622, 0x23000000, ftKb_80102470, ftKb_80103A2C, ftKb_801042E8,
      ftKb_80104E58, ftCamera_UpdateCameraBox },
    { 419, 0x00340622, 0x23000000, ftKb_80102470, ftKb_80103A2C, ftKb_801042E8,
      ftKb_80104E58, ftCamera_UpdateCameraBox },
    { 420, 0x003C0622, 0x23000000, ftKb_8010254C, ftKb_80103A30, ftKb_80104318,
      ftKb_80104F10, ftCamera_UpdateCameraBox },
    { 421, 0x003C0622, 0x23000000, ftKb_801026FC, ftKb_80103B98, ftKb_80104348,
      ftKb_80105018, ftCamera_UpdateCameraBox },
    { 422, 0x00340622, 0x23000000, ftKb_8010286C, ftKb_80103D00, ftKb_80104378,
      ftKb_80105120, ftCamera_UpdateCameraBox },
    { 423, 0x00340222, 0x23000000, ftKb_80102DD0, ftKb_80103D04, ftKb_801044F8,
      ftKb_801056FC, ftCamera_UpdateCameraBox },
    { 424, 0x00340622, 0x23000000, ftKb_80103088, ftKb_80103D08, ftKb_80104610,
      ftKb_801057BC, ftCamera_UpdateCameraBox },
    { 425, 0x00340622, 0x23000000, ftKb_80103088, ftKb_80103D08, ftKb_80104610,
      ftKb_801057BC, ftCamera_UpdateCameraBox },
    { 426, 0x00340622, 0x23000000, ftKb_80103374, ftKb_80103D0C, ftKb_80104640,
      ftKb_8010581C, ftCamera_UpdateCameraBox },
    { 427, 0x00340225, 0x26000000, ftKb_8010B65C, ftKb_8010B72C, ftKb_8010B734,
      ftKb_8010B7F0, ftCamera_UpdateCameraBox },
    { 428, 0x00340225, 0x26000000, ftKb_8010B958, ftKb_8010BA28, ftKb_8010BA98,
      ftKb_8010BAD8, ftCamera_UpdateCameraBox },
    { 429, 0x00340225, 0x26000000, ftKb_8010BCE0, ftKb_8010BED0, ftKb_8010BED8,
      ftKb_8010BF18, ftCamera_UpdateCameraBox },
    { 430, 0x00340225, 0x26000000, ftKb_8010BCE0, ftKb_8010BED0, ftKb_8010BED8,
      ftKb_8010BF18, ftCamera_UpdateCameraBox },
    { 431, 0x00340625, 0x26000000, ftKb_8010B6C4, ftKb_8010B730, ftKb_8010B78C,
      ftKb_8010B82C, ftCamera_UpdateCameraBox },
    { 432, 0x00340625, 0x26000000, ftKb_8010B9C0, ftKb_8010BA60, ftKb_8010BAB8,
      ftKb_8010BB14, ftCamera_UpdateCameraBox },
    { 433, 0x00340625, 0x26000000, ftKb_8010BDD8, ftKb_8010BED4, ftKb_8010BEF8,
      ftKb_8010BF54, ftCamera_UpdateCameraBox },
    { 434, 0x00340625, 0x26000000, ftKb_8010BDD8, ftKb_8010BED4, ftKb_8010BEF8,
      ftKb_8010BF54, ftCamera_UpdateCameraBox },
    { 435, 0x00340123, 0x24000000, ftKb_80107700, ftKb_80108040, ftKb_80108658,
      ftKb_80108798, ftCamera_UpdateCameraBox },
    { 436, 0x003C0123, 0x24000000, ftKb_80107884, ftKb_80108044, ftKb_80108678,
      ftKb_80108820, ftCamera_UpdateCameraBox },
    { 437, 0x003C0123, 0x24000000, ftKb_80107A84, ftKb_801081F8, ftKb_80108698,
      ftKb_801088A8, ftCamera_UpdateCameraBox },
    { 438, 0x00340123, 0x24000000, ftKb_80107AB4, ftKb_80108394, ftKb_801086B8,
      ftKb_80108930, ftCamera_UpdateCameraBox },
    { 439, 0x00340123, 0x24000000, ftKb_80107B38, ftKb_80108398, ftKb_801086D8,
      ftKb_801089B8, ftCamera_UpdateCameraBox },
    { 440, 0x00340523, 0x24000000, ftKb_80107B7C, ftKb_8010839C, ftKb_801086F8,
      ftKb_80108A40, ftCamera_UpdateCameraBox },
    { 441, 0x003C0523, 0x24000000, ftKb_80107D0C, ftKb_801083A0, ftKb_80108718,
      ftKb_80108AC8, ftCamera_UpdateCameraBox },
    { 442, 0x003C0523, 0x24000000, ftKb_80107F0C, ftKb_80108504, ftKb_80108738,
      ftKb_80108B50, ftCamera_UpdateCameraBox },
    { 443, 0x00340523, 0x24000000, ftKb_80107F3C, ftKb_80108650, ftKb_80108758,
      ftKb_80108BD8, ftCamera_UpdateCameraBox },
    { 444, 0x00340523, 0x24000000, ftKb_80107FC0, ftKb_80108654, ftKb_80108778,
      ftKb_80108C60, ftCamera_UpdateCameraBox },
    { 445, 0x0034012B, 0x2C000000, ftKb_8010D280, ftKb_8010D3C0, ftKb_8010D4C8,
      ftKb_8010D508, ftCamera_UpdateCameraBox },
    { 446, 0x0034052B, 0x2C000000, ftKb_8010D320, ftKb_8010D444, ftKb_8010D4E8,
      ftKb_8010D544, ftCamera_UpdateCameraBox },
    { 447, 0x00340028, 0x29000000, ftKb_800F9198, ftKb_800F91D4, ftKb_800F9204,
      ftKb_800F9224, ftCamera_UpdateCameraBox },
    { 448, 0x00340428, 0x29000000, ftKb_800F9454, ftKb_800F9490, ftKb_800F94C0,
      ftKb_800F94E0, ftCamera_UpdateCameraBox },
    { 449, 0x00340127, 0x28000000, ftKb_800FBBC4, ftKb_800FC374, ftKb_800FC70C,
      ftKb_800FC7CC, ftCamera_UpdateCameraBox },
    { 450, 0x003C0127, 0x28000000, ftKb_800FBDFC, ftKb_800FC46C, ftKb_800FC72C,
      ftKb_800FC880, ftCamera_UpdateCameraBox },
    { 451, 0x00340127, 0x28000000, ftKb_800FBED0, ftKb_800FC53C, ftKb_800FC74C,
      ftKb_800FC934, ftCamera_UpdateCameraBox },
    { 452, 0x00340527, 0x28000000, ftKb_800FBF34, ftKb_800FC540, ftKb_800FC76C,
      ftKb_800FC9F0, ftCamera_UpdateCameraBox },
    { 453, 0x003C0527, 0x28000000, ftKb_800FC1A0, ftKb_800FC638, ftKb_800FC78C,
      ftKb_800FCAA4, ftCamera_UpdateCameraBox },
    { 454, 0x00340527, 0x28000000, ftKb_800FC274, ftKb_800FC708, ftKb_800FC7AC,
      ftKb_800FCB58, ftCamera_UpdateCameraBox },
    { 455, 0x00340129, 0x2A000000, ftKb_800FE360, ftKb_800FEA50, ftKb_800FEAF8,
      ftKb_800FEBB8, ftCamera_UpdateCameraBox },
    { 456, 0x003C0129, 0x2A000000, ftKb_800FE450, ftKb_800FEA78, ftKb_800FEB18,
      ftKb_800FEBD8, ftCamera_UpdateCameraBox },
    { 457, 0x00340129, 0x2A000000, ftKb_800FE5C8, ftKb_800FEAA0, ftKb_800FEB38,
      ftKb_800FEBF8, ftCamera_UpdateCameraBox },
    { 458, 0x00340529, 0x2A000000, ftKb_800FE688, ftKb_800FEAA4, ftKb_800FEB58,
      ftKb_800FEC18, ftCamera_UpdateCameraBox },
    { 459, 0x003C0529, 0x2A000000, ftKb_800FE778, ftKb_800FEACC, ftKb_800FEB78,
      ftKb_800FEC38, ftCamera_UpdateCameraBox },
    { 460, 0x00340529, 0x2A000000, ftKb_800FE928, ftKb_800FEAF4, ftKb_800FEB98,
      ftKb_800FEC58, ftCamera_UpdateCameraBox },
    { 461, 0x0034012A, 0x2B000000, ftKb_800FA0F4, ftKb_800FA418, ftKb_800FA420,
      ftKb_800FA460, ftCamera_UpdateCameraBox },
    { 462, 0x0034052A, 0x2B000000, ftKb_800FA254, ftKb_800FA41C, ftKb_800FA440,
      ftKb_800FA4F0, ftCamera_UpdateCameraBox },
    { 463, 0x0034022C, 0x2D000000, ftKb_800F9AEC, ftKb_800F9B64, ftKb_800F9C58,
      ftKb_800F9E8C, ftCamera_UpdateCameraBox },
    { 464, 0x0034062C, 0x2D000000, ftKb_800F9B28, ftKb_800F9B68, ftKb_800F9D40,
      ftKb_800F9F34, ftCamera_UpdateCameraBox },
    { 465, 0x0034022D, 0x2E000000, ftKb_8010B65C, ftKb_8010B72C, ftKb_8010B734,
      ftKb_8010B7F0, ftCamera_UpdateCameraBox },
    { 466, 0x0034022D, 0x2E000000, ftKb_8010B958, ftKb_8010BA28, ftKb_8010BA98,
      ftKb_8010BAD8, ftCamera_UpdateCameraBox },
    { 467, 0x0034022D, 0x2E000000, ftKb_8010BCE0, ftKb_8010BED0, ftKb_8010BED8,
      ftKb_8010BF18, ftCamera_UpdateCameraBox },
    { 468, 0x0034022D, 0x2E000000, ftKb_8010BCE0, ftKb_8010BED0, ftKb_8010BED8,
      ftKb_8010BF18, ftCamera_UpdateCameraBox },
    { 469, 0x0034062D, 0x2E000000, ftKb_8010B6C4, ftKb_8010B730, ftKb_8010B78C,
      ftKb_8010B82C, ftCamera_UpdateCameraBox },
    { 470, 0x0034062D, 0x2E000000, ftKb_8010B9C0, ftKb_8010BA60, ftKb_8010BAB8,
      ftKb_8010BB14, ftCamera_UpdateCameraBox },
    { 471, 0x0034062D, 0x2E000000, ftKb_8010BDD8, ftKb_8010BED4, ftKb_8010BEF8,
      ftKb_8010BF54, ftCamera_UpdateCameraBox },
    { 472, 0x0034062D, 0x2E000000, ftKb_8010BDD8, ftKb_8010BED4, ftKb_8010BEF8,
      ftKb_8010BF54, ftCamera_UpdateCameraBox },
    { 473, 0x0034002E, 0x2F000000, ftKb_800FA9FC, ftKb_800FACAC, ftKb_800FAF74,
      ftKb_800FB034, ftCamera_UpdateCameraBox },
    { 474, 0x003C002E, 0x2F000000, ftKb_800FAA74, ftKb_800FACB0, ftKb_800FAF94,
      ftKb_800FB0C4, ftCamera_UpdateCameraBox },
    { 475, 0x0034002E, 0x2F000000, ftKb_800FAB18, ftKb_800FAE0C, ftKb_800FAFB4,
      ftKb_800FB154, ftCamera_UpdateCameraBox },
    { 476, 0x0034042E, 0x2F000000, ftKb_800FAB54, ftKb_800FAE10, ftKb_800FAFD4,
      ftKb_800FB1E4, ftCamera_UpdateCameraBox },
    { 477, 0x003C042E, 0x2F000000, ftKb_800FABCC, ftKb_800FAE14, ftKb_800FAFF4,
      ftKb_800FB274, ftCamera_UpdateCameraBox },
    { 478, 0x0034042E, 0x2F000000, ftKb_800FAC70, ftKb_800FAF70, ftKb_800FB014,
      ftKb_800FB304, ftCamera_UpdateCameraBox },
};

HSD_GObjEvent ftKb_803C9CC8[] = {
    ftKb_800EFA40, ftKb_800EFAF0, ftKb_800EFB4C, ftKb_800EFBFC, ftKb_800EFC58,
    ftKb_800EFD08, ftKb_800F0FC0, ftKb_800F10A4, NULL,          NULL,
    ftKb_800EFD64, ftKb_800EFE1C, ftKb_800EFE80, ftKb_800EFF38, ftKb_800EFF9C,
    ftKb_800F0054, ftKb_800F00B8, ftKb_800F0168, ftKb_800F01C4, ftKb_800F0274,
    ftKb_800F02D0, ftKb_800F0380, NULL,          NULL,          ftKb_800F03DC,
    ftKb_800F0494, ftKb_800F04F8, ftKb_800F05A8, ftKb_800F0604, ftKb_800F06B4,
    ftKb_800F10D4, ftKb_800F11AC, ftKb_800F11F0, ftKb_800F12C8, ftKb_800F0710,
    ftKb_800F07C0, ftKb_800F081C, ftKb_800F08D4, ftKb_800F0938, ftKb_800F09F0,
    ftKb_800F0A54, ftKb_800F0B0C, ftKb_800F0B70, ftKb_800F0C20, ftKb_800F130C,
    ftKb_800F13F0, ftKb_800F0C7C, ftKb_800F0D34, ftKb_800F14B4, ftKb_800F15D8,
    ftKb_800F0D98, ftKb_800F0E48, ftKb_800F0EA4, ftKb_800F0F5C, NULL,
    NULL,          NULL,          NULL,          NULL,          NULL,
    NULL,          NULL,          ftKb_800EFD64, ftKb_800EFE1C, NULL,
    NULL,
};

HSD_GObjEvent ftKb_803C9DD0[] = {
    ftKb_800F9110, ftKb_800FE100, ftKb_800F99BC, ftKb_800FF8EC, ftKb_800F5F68,
    ftKb_800FA8B4, ftKb_800FB880, ftKb_8010612C, ftKb_800FED38, ftKb_8010C4D4,
    ftKb_80108D64, NULL,          ftKb_800F9FD4, ftKb_800FCF74, ftKb_8010941C,
    ftKb_80101560, ftKb_80107568, ftKb_800F9614, ftKb_8010B2FC, ftKb_80105B2C,
    ftKb_800FB880, ftKb_800F9110, ftKb_800FE100, ftKb_800F9FD4, ftKb_8010D188,
    ftKb_800F99BC, ftKb_8010B2FC, NULL,          NULL,          NULL,
    NULL,          ftKb_800FA8B4, NULL,
};

HSD_GObjEvent ftKb_803C9E54[] = {
    ftKb_800F93CC, ftKb_800FE240, ftKb_800F9A54, ftKb_800FFA10, ftKb_800F6070,
    ftKb_800FA958, ftKb_800FBA00, ftKb_801061E4, ftKb_800FEDD0, ftKb_8010C560,
    ftKb_80108E14, NULL,          ftKb_800FA064, ftKb_800FD020, ftKb_801094FC,
    ftKb_80101618, ftKb_80107638, ftKb_800F9684, ftKb_8010B4A0, ftKb_80105BA8,
    ftKb_800FBA00, ftKb_800F93CC, ftKb_800FE240, ftKb_800FA064, ftKb_8010D204,
    ftKb_800F9A54, ftKb_8010B4A0, NULL,          NULL,          NULL,
    NULL,          ftKb_800FA958, NULL,
};

typedef unk_t ftKirby_UnkArrayThing[12];

ftKirby_UnkArrayThing ftKb_803C9ED8 = { 0 };
ftKirby_UnkArrayThing ftKb_803C9F08 = { 0 };
ftKirby_UnkArrayThing ftKb_803C9F38 = { 0 };
ftKirby_UnkArrayThing ftKb_803C9F68 = { 0 };
ftKirby_UnkArrayThing ftKb_803C9F98 = { 0 };

ftKirby_UnkArrayThing* ftKb_803C9FC8[FTKIND_MAX] = {
    NULL, NULL,           NULL,           &ftKb_803C9ED8, NULL, NULL, NULL,
    NULL, NULL,           NULL,           NULL,           NULL, NULL, NULL,
    NULL, &ftKb_803C9F08, &ftKb_803C9F38, NULL,           NULL, NULL, NULL,
    NULL, &ftKb_803C9F68, NULL,           &ftKb_803C9F98, NULL, NULL, NULL,
    NULL, NULL,           NULL,           NULL,           NULL,
};

MotionState ftKb_Init_UnkMotionStates0[] = {
    { 14, 0, 0x01000000, NULL, NULL, ft_800C737C, NULL, NULL },
    { 15, 0, 0x01000000, NULL, NULL, ft_800C737C, NULL, NULL },
    { 16, 0, 0x01000000, NULL, NULL, ft_800C737C, NULL, NULL },
    { 17, 0, 0x01000000, NULL, NULL, ft_800C7414, NULL, NULL },
};

/* static */ void ftKb_800EE854(void);
/* static */ void ftKb_800EE904(void);
/* static */ void ftKb_800EE904(void);
/* static */ void ftKb_800EE904(void);
/* static */ void ftKb_800EE8EC(void);
/* static */ void ftKb_800EE904(void);
/* static */ void ftKb_800EE904(void);
/* static */ void ftKb_800EE904(void);
/* static */ void ftKb_800EE904(void);
/* static */ void ftKb_800EE904(void);
/* static */ void ftKb_800EE874(void);
/* static */ void ftKb_800EE904(void);
/* static */ void ftKb_800EE904(void);
/* static */ void ftKb_800EE8B0(void);

jtbl_t ftKb_803CA0CC = {
    ftKb_800EE854, ftKb_800EE904, ftKb_800EE904, ftKb_800EE904, ftKb_800EE8EC,
    ftKb_800EE904, ftKb_800EE904, ftKb_800EE904, ftKb_800EE904, ftKb_800EE904,
    ftKb_800EE874, ftKb_800EE904, ftKb_800EE904, ftKb_800EE8B0,
};

char ftKb_assert_msg_0[] = "fighter parts model dobj num over!\n";
char ftKb_assert_msg_1[] = "ftkirby.c";
char ftKb_assert_msg_2[] = "fighter dobj num over!\n";

/* static */ void ftKb_800F1708(void);
/* static */ void ftKb_800F1764(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F186C(void);
/* static */ void ftKb_800F17A4(void);
/* static */ void ftKb_800F1894(void);
/* static */ void ftKb_800F17F8(void);
/* static */ void ftKb_800F1744(void);
/* static */ void ftKb_800F1730(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F1818(void);
/* static */ void ftKb_800F1858(void);
/* static */ void ftKb_800F18E8(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F17E4(void);
/* static */ void ftKb_800F171C(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F17C4(void);
/* static */ void ftKb_800F18B4(void);
/* static */ void ftKb_800F1784(void);
/* static */ void ftKb_800F1838(void);
/* static */ void ftKb_800F18C8(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F18F8(void);
/* static */ void ftKb_800F1880(void);

jtbl_t ftKb_803CA14C = {
    ftKb_800F1708, ftKb_800F1764, ftKb_800F18F8, ftKb_800F18F8, ftKb_800F18F8,
    ftKb_800F186C, ftKb_800F17A4, ftKb_800F1894, ftKb_800F17F8, ftKb_800F1744,
    ftKb_800F1730, ftKb_800F18F8, ftKb_800F1818, ftKb_800F1858, ftKb_800F18E8,
    ftKb_800F18F8, ftKb_800F17E4, ftKb_800F171C, ftKb_800F18F8, ftKb_800F18F8,
    ftKb_800F17C4, ftKb_800F18B4, ftKb_800F1784, ftKb_800F1838, ftKb_800F18C8,
    ftKb_800F18F8, ftKb_800F18F8, ftKb_800F18F8, ftKb_800F18F8, ftKb_800F18F8,
    ftKb_800F18F8, ftKb_800F1880,
};

/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A00(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A64(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A0C(void);
/* static */ void ftKb_800F1A44(void);
/* static */ void ftKb_800F1A2C(void);
/* static */ void ftKb_800F19F4(void);
/* static */ void ftKb_800F19E8(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A38(void);
/* static */ void ftKb_800F1A50(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A20(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A0C(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A00(void);
/* static */ void ftKb_800F1A78(void);
/* static */ void ftKb_800F1A70(void);

jtbl_t ftKb_803CA1CC = {
    ftKb_800F1A78, ftKb_800F1A00, ftKb_800F1A78, ftKb_800F1A64, ftKb_800F1A78,
    ftKb_800F1A78, ftKb_800F1A0C, ftKb_800F1A44, ftKb_800F1A2C, ftKb_800F19F4,
    ftKb_800F19E8, ftKb_800F1A78, ftKb_800F1A78, ftKb_800F1A38, ftKb_800F1A50,
    ftKb_800F1A78, ftKb_800F1A20, ftKb_800F1A78, ftKb_800F1A78, ftKb_800F1A78,
    ftKb_800F1A0C, ftKb_800F1A78, ftKb_800F1A00, ftKb_800F1A78, ftKb_800F1A70,
};

/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1AE0(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1B44(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1AEC(void);
/* static */ void ftKb_800F1B24(void);
/* static */ void ftKb_800F1B0C(void);
/* static */ void ftKb_800F1AD4(void);
/* static */ void ftKb_800F1AC8(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1B18(void);
/* static */ void ftKb_800F1B30(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1B00(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1AEC(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1AE0(void);
/* static */ void ftKb_800F1B58(void);
/* static */ void ftKb_800F1B50(void);

jtbl_t ftKb_803CA230 = {
    ftKb_800F1B58, ftKb_800F1AE0, ftKb_800F1B58, ftKb_800F1B44, ftKb_800F1B58,
    ftKb_800F1B58, ftKb_800F1AEC, ftKb_800F1B24, ftKb_800F1B0C, ftKb_800F1AD4,
    ftKb_800F1AC8, ftKb_800F1B58, ftKb_800F1B58, ftKb_800F1B18, ftKb_800F1B30,
    ftKb_800F1B58, ftKb_800F1B00, ftKb_800F1B58, ftKb_800F1B58, ftKb_800F1B58,
    ftKb_800F1AEC, ftKb_800F1B58, ftKb_800F1AE0, ftKb_800F1B58, ftKb_800F1B50,
};

/* static */ void ftKb_800F1CD0(void);
/* static */ void ftKb_800F1CD0(void);
/* static */ void ftKb_800F1CC8(void);
/* static */ void ftKb_800F1CD0(void);
/* static */ void ftKb_800F1CD0(void);
/* static */ void ftKb_800F1CD0(void);
/* static */ void ftKb_800F1CD0(void);
/* static */ void ftKb_800F1CC8(void);
/* static */ void ftKb_800F1CD0(void);
/* static */ void ftKb_800F1CD0(void);
/* static */ void ftKb_800F1CC8(void);
/* static */ void ftKb_800F1CC8(void);
/* static */ void ftKb_800F1CD0(void);
/* static */ void ftKb_800F1CC8(void);

jtbl_t ftKb_803CA294 = {
    ftKb_800F1CD0, ftKb_800F1CD0, ftKb_800F1CC8, ftKb_800F1CD0, ftKb_800F1CD0,
    ftKb_800F1CD0, ftKb_800F1CD0, ftKb_800F1CC8, ftKb_800F1CD0, ftKb_800F1CD0,
    ftKb_800F1CC8, ftKb_800F1CC8, ftKb_800F1CD0, ftKb_800F1CC8,
};

/* static */ void ftKb_800F1D08(void);
/* static */ void ftKb_800F1D08(void);
/* static */ void ftKb_800F1D00(void);
/* static */ void ftKb_800F1D08(void);
/* static */ void ftKb_800F1D08(void);
/* static */ void ftKb_800F1D08(void);
/* static */ void ftKb_800F1D08(void);
/* static */ void ftKb_800F1D00(void);
/* static */ void ftKb_800F1D08(void);
/* static */ void ftKb_800F1D08(void);
/* static */ void ftKb_800F1D00(void);
/* static */ void ftKb_800F1D00(void);
/* static */ void ftKb_800F1D08(void);
/* static */ void ftKb_800F1D00(void);

jtbl_t ftKb_803CA2CC = { ftKb_800F1D08, ftKb_800F1D08, ftKb_800F1D00,
                         ftKb_800F1D08, ftKb_800F1D08, ftKb_800F1D08,
                         ftKb_800F1D08, ftKb_800F1D00, ftKb_800F1D08,
                         ftKb_800F1D08, ftKb_800F1D00, ftKb_800F1D00,
                         ftKb_800F1D08, ftKb_800F1D00, NULL };

char ftKb_Init_DatFilename[] = "PlKb.dat";
char ftKb_Init_DataName[] = "ftDataKirby";
char ftKb_803CA320[] = "PlKbNr.dat";
char ftKb_803CA32C[] = "PlyKirby5K_Share_joint";
char ftKb_803CA344[] = "PlyKirby5K_Share_matanim_joint";
char ftKb_803CA364[] = "PlKbYe.dat";
char ftKb_803CA370[] = "PlyKirby5KYe_Share_joint";
char ftKb_803CA38C[] = "PlyKirby5KYe_Share_matanim_joint";
char ftKb_803CA3B0[] = "PlKbBu.dat";
char ftKb_803CA3BC[] = "PlyKirby5KBu_Share_joint";
char ftKb_803CA3D8[] = "PlyKirby5KBu_Share_matanim_joint";
char ftKb_803CA3FC[] = "PlKbRe.dat";
char ftKb_803CA408[] = "PlyKirby5KRe_Share_joint";
char ftKb_803CA424[] = "PlyKirby5KRe_Share_matanim_joint";
char ftKb_803CA448[] = "PlKbGr.dat";
char ftKb_803CA454[] = "PlyKirby5KGr_Share_joint";
char ftKb_803CA470[] = "PlyKirby5KGr_Share_matanim_joint";
char ftKb_803CA494[] = "PlKbWh.dat";
char ftKb_803CA4A0[] = "PlyKirby5KWh_Share_joint";
char ftKb_803CA4BC[] = "PlyKirby5KWh_Share_matanim_joint";
char ftKb_Init_AnimDatFilename[] = "PlKbAJ.dat";

Fighter_DemoStrings ftKb_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileKirby",
    "ftDemoIntroMotionFileKirby",
    "ftDemoEndingMotionFileKirby",
    "ftDemoViWaitMotionFileKirby",
};

char* ftKb_803CA5A4[] = {
    "ftDemoVi0501MotionFileKirby",
    NULL,
    NULL,
    "ftDemoVi0502MotionFileKirby",
};

Fighter_CostumeStrings ftKb_Init_CostumeStrings[] = {
    { ftKb_803CA320, ftKb_803CA32C, ftKb_803CA344 },
    { ftKb_803CA364, ftKb_803CA370, ftKb_803CA38C },
    { ftKb_803CA3B0, ftKb_803CA3BC, ftKb_803CA3D8 },
    { ftKb_803CA3FC, ftKb_803CA408, ftKb_803CA424 },
    { ftKb_803CA448, ftKb_803CA454, ftKb_803CA470 },
    { ftKb_803CA494, ftKb_803CA4A0, ftKb_803CA4BC },
};

typedef struct ftKirby_CopyName {
    char* filename;
    char* name;
} ftKirby_CopyName;

ftKirby_CopyName ftKb_803CA9D0[FTKIND_MAX] = {
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

char ftKb_803CAAD8[] = "PlKbNrCpDk.dat";
char ftKb_803CAAE8[] = "PlyKirbyDk_Share_joint";
char ftKb_803CAB00[] = "PlyKirbyDk_Share_matanim_joint";
char ftKb_803CAB20[] = "PlKbYeCpDk.dat";
char ftKb_803CAB30[] = "PlyKirbyDkYe_Share_joint";
char ftKb_803CAB4C[] = "PlyKirbyDkYe_Share_matanim_joint";
char ftKb_803CAB70[] = "PlKbBuCpDk.dat";
char ftKb_803CAB80[] = "PlyKirbyDkBu_Share_joint";
char ftKb_803CAB9C[] = "PlyKirbyDkBu_Share_matanim_joint";
char ftKb_803CABC0[] = "PlKbReCpDk.dat";
char ftKb_803CABD0[] = "PlyKirbyDkRe_Share_joint";
char ftKb_803CABEC[] = "PlyKirbyDkRe_Share_matanim_joint";
char ftKb_803CAC10[] = "PlKbGrCpDk.dat";
char ftKb_803CAC20[] = "PlyKirbyDkGr_Share_joint";
char ftKb_803CAC3C[] = "PlyKirbyDkGr_Share_matanim_joint";
char ftKb_803CAC60[] = "PlKbWhCpDk.dat";
char ftKb_803CAC70[] = "PlyKirbyDkWh_Share_joint";
char ftKb_803CAC8C[] = "PlyKirbyDkWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_803CACB0[] = {
    { ftKb_803CAAD8, ftKb_803CAAE8, ftKb_803CAB00 },
    { ftKb_803CAB20, ftKb_803CAB30, ftKb_803CAB4C },
    { ftKb_803CAB70, ftKb_803CAB80, ftKb_803CAB9C },
    { ftKb_803CABC0, ftKb_803CABD0, ftKb_803CABEC },
    { ftKb_803CAC10, ftKb_803CAC20, ftKb_803CAC3C },
    { ftKb_803CAC60, ftKb_803CAC70, ftKb_803CAC8C },
};

char ftKb_803CACF8[] = "PlKbNrCpPr.dat";
char ftKb_803CAD08[] = "PlyKirbyPr_Share_joint";
char ftKb_803CAD20[] = "PlyKirbyPr_Share_matanim_joint";
char ftKb_803CAD40[] = "PlKbYeCpPr.dat";
char ftKb_803CAD50[] = "PlyKirbyPrYe_Share_joint";
char ftKb_803CAD6C[] = "PlyKirbyPrYe_Share_matanim_joint";
char ftKb_803CAD90[] = "PlKbBuCpPr.dat";
char ftKb_803CADA0[] = "PlyKirbyPrBu_Share_joint";
char ftKb_803CADBC[] = "PlyKirbyPrBu_Share_matanim_joint";
char ftKb_803CADE0[] = "PlKbReCpPr.dat";
char ftKb_803CADF0[] = "PlyKirbyPrRe_Share_joint";
char ftKb_803CAE0C[] = "PlyKirbyPrRe_Share_matanim_joint";
char ftKb_803CAE30[] = "PlKbGrCpPr.dat";
char ftKb_803CAE40[] = "PlyKirbyPrGr_Share_joint";
char ftKb_803CAE5C[] = "PlyKirbyPrGr_Share_matanim_joint";
char ftKb_803CAE80[] = "PlKbWhCpPr.dat";
char ftKb_803CAE90[] = "PlyKirbyPrWh_Share_joint";
char ftKb_803CAEAC[] = "PlyKirbyPrWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_803CAED0[] = {
    { ftKb_803CACF8, ftKb_803CAD08, ftKb_803CAD20 },
    { ftKb_803CAD40, ftKb_803CAD50, ftKb_803CAD6C },
    { ftKb_803CAD90, ftKb_803CADA0, ftKb_803CADBC },
    { ftKb_803CADE0, ftKb_803CADF0, ftKb_803CAE0C },
    { ftKb_803CAE30, ftKb_803CAE40, ftKb_803CAE5C },
    { ftKb_803CAE80, ftKb_803CAE90, ftKb_803CAEAC },
};

char ftKb_803CAF18[] = "PlKbNrCpMt.dat";
char ftKb_803CAF28[] = "PlyKirbyMt_Share_joint";
char ftKb_803CAF40[] = "PlyKirbyMt_Share_matanim_joint";
char ftKb_803CAF60[] = "PlKbYeCpMt.dat";
char ftKb_803CAF70[] = "PlyKirbyMtYe_Share_joint";
char ftKb_803CAF8C[] = "PlyKirbyMtYe_Share_matanim_joint";
char ftKb_803CAFB0[] = "PlKbBuCpMt.dat";
char ftKb_803CAFC0[] = "PlyKirbyMtBu_Share_joint";
char ftKb_803CAFDC[] = "PlyKirbyMtBu_Share_matanim_joint";
char ftKb_803CB000[] = "PlKbReCpMt.dat";
char ftKb_803CB010[] = "PlyKirbyMtRe_Share_joint";
char ftKb_803CB02C[] = "PlyKirbyMtRe_Share_matanim_joint";
char ftKb_803CB050[] = "PlKbGrCpMt.dat";
char ftKb_803CB060[] = "PlyKirbyMtGr_Share_joint";
char ftKb_803CB07C[] = "PlyKirbyMtGr_Share_matanim_joint";
char ftKb_803CB0A0[] = "PlKbWhCpMt.dat";
char ftKb_803CB0B0[] = "PlyKirbyMtWh_Share_joint";
char ftKb_803CB0CC[] = "PlyKirbyMtWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_803CB0F0[] = {
    { ftKb_803CAF18, ftKb_803CAF28, ftKb_803CAF40 },
    { ftKb_803CAF60, ftKb_803CAF70, ftKb_803CAF8C },
    { ftKb_803CAFB0, ftKb_803CAFC0, ftKb_803CAFDC },
    { ftKb_803CB000, ftKb_803CB010, ftKb_803CB02C },
    { ftKb_803CB050, ftKb_803CB060, ftKb_803CB07C },
    { ftKb_803CB0A0, ftKb_803CB0B0, ftKb_803CB0CC },
};

char ftKb_803CB138[] = "PlKbNrCpFc.dat";
char ftKb_803CB148[] = "PlyKirbyFc_Share_joint";
char ftKb_803CB160[] = "PlyKirbyFc_Share_matanim_joint";
char ftKb_803CB180[] = "PlKbYeCpFc.dat";
char ftKb_803CB190[] = "PlyKirbyFcYe_Share_joint";
char ftKb_803CB1AC[] = "PlyKirbyFcYe_Share_matanim_joint";
char ftKb_803CB1D0[] = "PlKbBuCpFc.dat";
char ftKb_803CB1E0[] = "PlyKirbyFcBu_Share_joint";
char ftKb_803CB1FC[] = "PlyKirbyFcBu_Share_matanim_joint";
char ftKb_803CB220[] = "PlKbReCpFc.dat";
char ftKb_803CB230[] = "PlyKirbyFcRe_Share_joint";
char ftKb_803CB24C[] = "PlyKirbyFcRe_Share_matanim_joint";
char ftKb_803CB270[] = "PlKbGrCpFc.dat";
char ftKb_803CB280[] = "PlyKirbyFcGr_Share_joint";
char ftKb_803CB29C[] = "PlyKirbyFcGr_Share_matanim_joint";
char ftKb_803CB2C0[] = "PlKbWhCpFc.dat";
char ftKb_803CB2D0[] = "PlyKirbyFcWh_Share_joint";
char ftKb_803CB2EC[] = "PlyKirbyFcWh_Share_matanim_joint";

Fighter_CostumeStrings ftKb_803CB310[] = {
    { ftKb_803CB138, ftKb_803CB148, ftKb_803CB160 },
    { ftKb_803CB180, ftKb_803CB190, ftKb_803CB1AC },
    { ftKb_803CB1D0, ftKb_803CB1E0, ftKb_803CB1FC },
    { ftKb_803CB220, ftKb_803CB230, ftKb_803CB24C },
    { ftKb_803CB270, ftKb_803CB280, ftKb_803CB29C },
    { ftKb_803CB2C0, ftKb_803CB2D0, ftKb_803CB2EC },
};

char ftKb_803CB358[] = "PlKbNrCpGw.dat";
char ftKb_803CB368[] = "PlyKirbyGw_Share_joint";
char ftKb_803CB380[] = "PlyKirbyGw_Share_matanim_joint";

Fighter_CostumeStrings ftKb_803CB3A0[] = {
    { ftKb_803CB358, ftKb_803CB368, ftKb_803CB380 },
    { ftKb_803CB358, ftKb_803CB368, ftKb_803CB380 },
    { ftKb_803CB358, ftKb_803CB368, ftKb_803CB380 },
    { ftKb_803CB358, ftKb_803CB368, ftKb_803CB380 },
    { ftKb_803CB358, ftKb_803CB368, ftKb_803CB380 },
    { ftKb_803CB358, ftKb_803CB368, ftKb_803CB380 },
};

Fighter_CostumeStrings* ftKb_803CB3E8[] = {
    NULL, NULL,          NULL,          ftKb_803CACB0, NULL, NULL, NULL,
    NULL, NULL,          NULL,          NULL,          NULL, NULL, NULL,
    NULL, ftKb_803CAED0, ftKb_803CB0F0, NULL,          NULL, NULL, NULL,
    NULL, ftKb_803CB310, NULL,          ftKb_803CB3A0, NULL, NULL, NULL,
    NULL, NULL,          NULL,          NULL,          NULL,
};

s8 ftKb_803CB46C[FTKIND_MAX] = {
    32, 33, 38, 39, -1, 41, 35, 21, 42, 45, 46, 46, 36, 34, 40, 43, 44,
    37, 20, 21, 35, 32, 33, 36, -1, 47, 48, -1, -1, -1, -1, -1, -1,
};

bool ftKb_803CB490[] = {
    false, true,  false, false, false, false, true,  true,
    false, false, false, true,  true,  true,  false, false,
    true,  true,  true,  true,  false, true,  true,
};

struct lbl_803CB4EC_t {
    int ints[6];
    Vec3 vec;
} ftKb_803CB4EC = {
    { 0, 2, 3, 4, 5, 6 },
    { 0.0F, 1.0F, 0.0F },
};

char ftKb_803CB510[] = "Other Dead_Proc Existence";
char ftKb_803CB52C[] = "ftkirbyspecials.c";

enum_t ftKb_803CB540[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
};

uint ftKb_803CB6C0[] = { 260006, 260009, 260012, 260015, 260018, 0 };

char ftKb_803CB6D8[] = "ftToSpecialNFox::Caution!!!\n";
char ftKb_803CB6F8[] = "ftkirbyspecialfox.c\0\0\0\0";

Vec4 ftKb_803CB710 = { 0.65F, 0.7F, 0.8F, 1.0F };
Vec4 ftKb_803CB720 = { 1.1F, 1.35F, 1.3F, 1.2F };

char ftKb_assert_msg_3[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 ftKb_803CB758[] = {
    { +8, +0, -4 },
    { +4, +4, +4 },
};

f32 ftKb_803CB770[] = {
    -1, -0.75, -0.5, -0.25, 0, +0.25, +0.5, +0.75, +1,
};
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106464(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106464(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106464(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106464(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106464(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106474(void);
/* static */ void ftKb_80106464(void);

jtbl_t ftKb_803CB794 = {
    ftKb_80106474, ftKb_80106474, ftKb_80106464, ftKb_80106474, ftKb_80106474,
    ftKb_80106464, ftKb_80106474, ftKb_80106474, ftKb_80106464, ftKb_80106474,
    ftKb_80106474, ftKb_80106464, ftKb_80106474, ftKb_80106474, ftKb_80106464,
    ftKb_80106474, ftKb_80106474, ftKb_80106464,
};
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066B4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066B4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066B4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066B4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066B4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066C4(void);
/* static */ void ftKb_801066B4(void);

jtbl_t ftKb_803CB7DC = {
    ftKb_801066C4, ftKb_801066C4, ftKb_801066B4, ftKb_801066C4, ftKb_801066C4,
    ftKb_801066B4, ftKb_801066C4, ftKb_801066C4, ftKb_801066B4, ftKb_801066C4,
    ftKb_801066C4, ftKb_801066B4, ftKb_801066C4, ftKb_801066C4, ftKb_801066B4,
    ftKb_801066C4, ftKb_801066C4, ftKb_801066B4, NULL,
};

uint ftKb_803CB828[] = { 0x00030DB9, 0x00030DBC, 0x00030DBF, 0x00030DC2 };

f32 const lbl_803B7548[10] = { 0 };
Vec3 const lbl_803B7570 = { 0, 4, 0 };
Vec3 const lbl_803B757C = { 0, 4, 0 };

#ifdef MWERKS_GEKKO
#pragma push
asm void ftKb_800EE528(void)
{ // clang-format off
    nofralloc
/* 800EE528 00000000  38 00 00 21 */	li r0, 0x21
/* 800EE52C 00000004  3C 80 80 46 */	lis r4, lbl_80459B88@ha
/* 800EE530 00000008  7C 09 03 A6 */	mtctr r0
/* 800EE534 0000000C  3C 60 80 3D */	lis r3, ftKb_803C9FC8@ha
/* 800EE538 00000010  38 84 9B 88 */	addi r4, r4, lbl_80459B88@l
/* 800EE53C 00000014  38 A3 9F C8 */	addi r5, r3, ftKb_803C9FC8@l
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
void ftKb_800EE528(void)
{
    s32* number_list = lbl_80459B88;
    ftKirby_UnkArrayThing** struct_list = ftKb_803C9FC8;

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

void ftKb_Init_OnDeath(HSD_GObj* gobj)
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
        ftKb_800F1BAC(gobj, Player_GetUnk4D(fp->xC_playerID), 0);
    }
}

void ftKb_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    PUSH_ATTRS(fp, ftKirbyAttributes);

    fp->x2222_flag.bits.b1 = 1;
    fp->x2D0 = fp->x2D4_specialAttributes;
    fp->fv.kb.x2234.bits.b0 = Player_GetFlagsAEBit1(fp->xC_playerID);
    it_8026B3F8(item_list[0], 0x32);
    it_8026B3F8(item_list[1], 0x33);
    it_8026B3F8(item_list[2], 0x34);
    it_8026B3F8(item_list[3], 0x35);
}

void ftKb_800EE74C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_800F5524(gobj);
    ftKb_800F22D4(gobj);
    ftKb_800F5318(gobj);
    ftKb_800F9090(gobj);
    ftKb_800F19AC(gobj);
    ftKb_800F5D04(gobj, false);
    fp->cb.x21E8_callback_OnDeath3 = NULL;
}

void ftKb_800EE7B8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_800F5524(gobj);
    ftKb_800F22D4(gobj);
    ftKb_800F5318(gobj);
    ftKb_800F9090(gobj);
    ftKb_800F1A8C(gobj);
    fp->cb.x21E0_callback_OnDeath = NULL;
}

/// @file
/// @todo Matching, but needs more data moved over for DOL match

#if false

void ftKb_Init_UnkMotionStates4(HSD_GObj* gobj)
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

void ftKb_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftKb_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftKb_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftKb_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftKirbyAttributes);
}

void ftKb_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftKb_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

#endif

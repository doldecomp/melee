#ifndef __GALE01_028B9C
#define __GALE01_028B9C

#include "camera.h" // IWYU pragma: export

#include "baselib/forward.h"

#include "baselib/wobj.h"

#include <math.h>
#include <sysdolphin/baselib/cobj.h>
#include <melee/cm/types.h>

/// .bss
/* 452C68 */ static Camera cm_80452C68;

// .data
/* 3BCB18 */ static CameraModeCallbacks cm_803BCB18 = { Camera_8002B3D4,
                                                        Camera_8002CDDC,
                                                        Camera_8002D318,
                                                        Camera_8002D85C,
                                                        Camera_8002DDC4,
                                                        Camera_8002C908,
                                                        Camera_8002E490,
                                                        0,
                                                        0 };
/* 3BCB3C */ static HSD_WObjDesc cm_803BCB3C = {
    NULL, { 0.0f, 40.241425f, 300.241f }, 0
};
/* 3BCB50 */ static HSD_WObjDesc cm_803BCB50 = { NULL,
                                                 { 0.0f, 10.0f, 0.0f },
                                                 0 };
/* 3BCB64 */ static HSD_CameraDescPerspective cm_803BCB64 = {
    0,
    0,
    1,
    { 0, 0x280, 0, 0x1E0 },
    { 0, 0x280, 0, 0x1E0 },
    &cm_803BCB3C,
    &cm_803BCB50,
    0.0f,
    NULL,
    0.1f,
    16384.0f,
    30.0f,
    1.2173333f
};

/* 3BCB9C */ static f32 cm_803BCB9C[5] = { 0.0f, 1.5f, 1.32f, 1.16f, 1.0f };
/* 3BCBB0 */ static s8 cm_803BCBB0[0x20] = "couldn't get CmSubject struct.\n";
/* 3BCBD0 */ static char cm_803BCBD0[0xB] = "camera.c";
/* 3BCBDC */ static char cm_803BCBDC[0x1B] = "fov_u<MTXDegToRad(90.0F)";
/* 3BCBF8 */ static char cm_803BCBF8[0x1B] = "fov_d<MTXDegToRad(90.0F)";
/* 3BCC14 */ static char cm_803BCC14[0x1B] = "fov_r<MTXDegToRad(90.0F)";
/* 3BCC30 */ static char cm_803BCC30[0x1B] = "fov_l<MTXDegToRad(90.0F)";
// /* 3BCC4C */ static void* jumptable_803BCC4C[8] = {
//     (void*)0x8002a4f8,
//     (void*)0x8002a554,
//     (void*)0x8002a6c0,
//     (void*)0x8002a6c0,
//     (void*)0x8002a52c,
//     (void*)0x8002a6c0,
//     (void*)0x8002a700,
//     (void*)0x8002a728,
// };
/* 3BCC70 */ static char lbl_803BCC70[0x17] = "rate>0.0F&&rate<=1.0F";
/* 3BCC88 */ static char lbl_803BCC88[0x17] = "snapshot! ptr=%08x\n";

/* 3BCCA0 */ static CameraUnkGlobals cm_803BCCA0 = {
    83.0f,  1000.0f, -30.0f,  5.0f,  -7.0f,  17.5f,  -17.5f, 0.0f,  0.0682f,
    60.0f,  120.0f,  0.05f,   0.1f,  120.0f, 900.0f, 0.15f,  38.0f, 0.1f,
    0.1f,   0.001f,  0.1f,    1.0f,  1.0f,   0.6f,   0.6f,   0.05f, 0.1f,
    29.0f,  0.1f,    0.1f,    0.1f,  0.1f,   0.5f,   0.5f,   0.4f,  -11.0f,
    400.0f, 0.2f,    4.0f,    0.05f, 1.0f,   -7.0f,  7.0f,   0.5f,  0.5f,
    0.004f, 0.2f,    0.025f,  0.2f,  0.003f, 0.2f,   0.025f, 0.2f,  0.02f,
    1.0f,   0.14f,   1200.0f, -0.2f, 1.2f,   0.0f,
};

/// .rodata
/* 3B73B8 */ static Vec3 const cm_WorldForward = { 0.0f, 0.0f, -1.0f };
/* 3B73C4 */ static Vec3 const cm_803B73C4 = { 0.0f };
/* 3B73D0 */ static Vec3 const cm_WorldUp = { 0.0f, 1.0f, 0.0f };
/* 3B73DC */ static Vec3 const cm_803B73DC = { 0.0f, 1.0f, 0.0f };

/// .sbss
/* 4D6458 */ static CmSubject* cm_804D6458;
/* 4D645C */ static CmSubject* cm_804D645C;
/* 4D6460 */ static CmSubject* cm_804D6460;
/* 4D6468 */ CmSubject* cm_804D6468; // requires a size of 8?

/// .sdata
/* 4D3938 */ static char cm_804D3938[0x8] = "0";

/// sdata2
/* 4D7E00 */ float const cm_804D7E00 = -3.4028235E+38f;
/* 4D7E04 */ float const cm_804D7E04 = 1.0f;
/* 4D7E08 */ float const cm_804D7E08 = 0.1f;     // near clip
/* 4D7E10 */ float const cm_804D7E0C = 16384.0f; // far clip
/* 4D7E10 */ float const cm_804D7E10 = -1.0f;
/* 4D7E14 */ float const cm_804D7E14 = 0.0f;
/* 4D7E18 */ double const cm_804D7E18 = 1.0f;
/* 4D7E20 */ double const cm_804D7E20 = 4503601774854144.0f;
/* 4D7E28 */ float const cm_804D7E28 = 0.64999998f;
/* 4D7E2C */ float const cm_804D7E2C = 0.34999999f;
/* 4D7E30 */ float const cm_804D7E30 = 0.5f;
/* 4D7E34 */ float const cm_804D7E34 = -0.5f;
/* 4D7E38 */ float const cm_804D7E38 = 3.4028235E+38f;
/* 4D7E3C */ float const cm_804D7E3C = 40.0f;
/* 4D7E40 */ float const cm_804D7E40 = 80.0f;
/* 4D7E44 */ float const cm_804D7E44 = 5000.0f;
/* 4D7E48 */ float const cm_804D7E48 = 4920.0f;
/* 4D7E4C */ float const cm_804D7E4C = 10.0f;
/* 4D7E50 */ float const cm_804D7E50 = 390.0f;
/* 4D7E54 */ float const cm_804D7E54 = 99999.0f;
/* 4D7E58 */ float const cm_804D7E58 = 0.000099999997f;
/* 4D7E5C */ float const cm_804D7E5C = 1000.0f;
/* 4D7E60 */ float const cm_804D7E60 = 0.017453292f; // deg2rad
/* 4D7E64 */ float const cm_804D7E64 = 1.5707964f;   // rad2deg
/* 4D7E68 */ float const cm_804D7E68 = 0.001f;
/* 4D7E6C */ float const cm_804D7E6C = -0.001f;
/* 4D7E70 */ float const cm_804D7E70 = 30.0f;
/* 4D7E74 */ float const cm_804D7E74 = 0.85f;
/* 4D7E78 */ double const cm_804D7E78 = 0.5f;
/* 4D7E80 */ double const cm_804D7E80 = 3.0f;
/* 4D7E88 */ float const cm_804D7E88 = 0.999f;
/* 4D7E8C */ float const cm_804D7E8C = -0.999f;
/* 4D7E90 */ float const cm_804D7E90 = 5.0f;
/* 4D7E94 */ float const cm_804D7E94 = 20.0f;
/* 4D7E98 */ float const cm_804D7E98 = 3.0f;
/* 4D7EA0 */ double const cm_804D7EA0 = 0.125f;
/* 4D7EA8 */ float const cm_804D7EA8 = 2.0f;
/* 4D7EAC */ float const cm_804D7EAC = 2000.0f;
/* 4D7EB0 */ float const cm_804D7EB0 = -2000.0f;
/* 4D7EB8 */ double const cm_804D7EB8 = -1.0f;
/* 4D7EC0 */ float const cm_804D7EC0 = 4.0f;
/* 4D7EC8 */ f64 const cm_804D7EC8 = M_PI / 8;
/* 4D7ED0 */ f64 const cm_804D7ED0 = M_PI / 16;
/* 4D7ED8 */ f64 const cm_804D7ED8 = M_PI * 2;
/* 4D7EE0 */ f64 const cm_804D7EE0 = M_PI;
/* 4D7EE8 */ f64 const cm_804D7EE8 = 0.0001f;
/* 4D7EF0 */ double const cm_804D7EF0 = 0.0f;
/* 4D7EF8 */ float const cm_804D7EF8 = 8.5070587E+37f;
/* 4D7EFC */ float const cm_804D7EFC = -8.5070587E+37f;
/* 4D7F00 */ float const cm_804D7F00 = 2.1474836E+9f;
/* 4D7F04 */ float const cm_804D7F04 = -2.1474836E+9f;
/* 4D7F08 */ float const cm_804D7F08 = 10000.0f;

#endif

#ifndef __GALE01_2FC9B4
#define __GALE01_2FC9B4

#include "baselib/forward.h"
#include "pl/forward.h"

#include "platform.h"
#include "types.h"
#include "un_2FC9.h" // IWYU pragma: export

#include "baselib/objalloc.h"
#include "sc/types.h"

#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/lobj.h>
#include <baselib/sislib.h>
#include <baselib/wobj.h>

// types
struct un_80304138_objalloc_t {
    char pad_0[0x20];
};
STATIC_ASSERT(sizeof(struct un_80304138_objalloc_t) == 0x20);

// .text
/* 2FCAA4 */ static void NameTag_RenderCallback(HSD_GObj* gobj, int pass);

// .data
// IfAll.dat::ScInfPnm_scene_models
//  0- 3 - 1P      - Red, Blue, Yellow, Green
//  4- 7 - 2P      - Red, Blue, Yellow, Green
//  8-11 - 3P      - Red, Blue, Yellow, Green
// 12-15 - 4P      - Red, Blue, Yellow, Green
// 16-19 - CP      - Red, Blue, Gray,   Green
// 20-23 - Nametag - Red, Blue, Yellow, Green
// 24-27 - Heart   - Red, Blue, Yellow, Green
// 28    - Nametag - Gray
// 29-30 - Empty   - Gray
/* 3F98B8 */ static float un_803F98B8[6][5] = {
    {
        0.0,  // 1P Red
        1.0,  // 1P Blue
        3.0,  // 1P Green
        0.0,  // 1P Red
        16.0, // CP Red
    },
    {
        4.0,  // 2P Red
        5.0,  // 2P Blue
        7.0,  // 2P Green
        5.0,  // 2P Blue
        17.0, // CP Blue
    },
    {
        8.0,  // 3P Red
        9.0,  // 3P Blue
        11.0, // 3P Green
        10.0, // 3P Blue
        18.0, // CP Gray
    },
    {
        12.0, // 4P Red
        13.0, // 4P Blue
        15.0, // 4P Green
        15.0, // 4P Green
        19.0, // CP Green
    },
    {
        16.0, // CP Red
        17.0, // CP Blue
        19.0, // CP Green
        18.0, // CP Gray
        18.0, // CP Gray
    },
    {
        24.0, // Heart Red
        25.0, // Heart Blue
        26.0, // Heart Yellow
        27.0, // Heart Green
    },
};
/* 3F992C */ static HSD_WObjDesc nametag_eyepos = { NULL,
                                                    { 0.0f, 0.0f, 300.0f },
                                                    NULL };
/* 3F9940 */ static HSD_WObjDesc nametag_interest = { NULL,
                                                      { 0.0f, 0.0f, 0.0f },
                                                      NULL };
/* 3F9954 */ static HSD_CameraDescFrustum nametag_CObjDesc = {
    NULL,
    0,
    3,
    0,
    640,
    0,
    480,
    0,
    640,
    0,
    480,
    &nametag_eyepos,
    &nametag_interest,
    0.0f,
    NULL,
    0.1f,
    32768.0f,
    0.0f,
    -480.0f,
    0.0f,
    640.0f
};
/* 3F9A00 */ static int un_803F9A00[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 3, 2, 2, 5, 5, 4, 6, 6, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 6, 6, 5, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5
};
/* 3F9B30 */ static int* un_803F9B30;
/* 3F9E08 */ static struct {
    struct {
        unsigned char b0 : 1;
        unsigned char b1 : 1;
        unsigned char b234 : 3;
        unsigned char b567 : 3;
    } x0;
    unsigned char x1;
    unsigned char x2;
    unsigned char x3;
    unsigned int x4;
    unsigned int x8;
    HSD_GObj* xC;
} un_803F9E08;
/* 3F9E60 */ static HSD_CObjDesc un_803F9E60 = { 0 };
/* 3F9ED4 */ static HSD_LightDesc un_803F9ED4 = { 0 };
/* 3FA258 */ static struct {
    int x0;
    int x4;
} un_803FA258 = { 0 };
/* 3FA658 */ static int un_803FA658;
/* 3FDC20 */ static HSD_WObjDesc devtext_eyepos = {
    NULL, { 0.0f, 40.241424560546875f, 300.2409973144531f }, NULL
};
/* 3FDC34 */ static HSD_WObjDesc devtext_interest = { NULL,
                                                      { 0.0f, 10.0f, 0.0f },
                                                      NULL };
/* 3FDC48 */ static HSD_CameraDescPerspective devtext_CObjDesc = {
    NULL,
    0,
    1,
    0,
    640,
    0,
    480,
    0,
    640,
    0,
    480,
    &devtext_eyepos,
    &devtext_interest,
    0,
    NULL,
    0.1f,
    32768.0f,
    30.0f,
    1.3636000156402588f,
};

// .bss
/* 4A1ED0 */ static StaticModelDesc un_804A1ED0;
/* 4A1EE0 */ static HSD_GObj* un_804A1EE0[PL_SLOT_MAX];
/* 4A1EF8 */ static int un_804A1EF8[PL_SLOT_MAX];
/* 4A1F10 */ static struct {
    HSD_Joint*** x0;
    HSD_GObj* x4[4];
    int x14[4];
    unsigned char x24[4];
    unsigned char x28[4];
    unsigned char x2C[4];
    unsigned char x30;
    unsigned char x31;
    unsigned char x32;
} un_804A1F10;
struct un_804A1F58_x8_t {
    HSD_GObj* x0;
    HSD_Text* x4;
    unsigned int x8;
};
/* 4A1F58 */ static struct {
    unsigned int x0;
    unsigned int x4;
    struct un_804A1F58_x8_t x8;
} un_804A1F58[6];
/* 4A1FD8 */ static DevText devtext_pool[32];
/* 4A2688 */ static HSD_ObjAllocData un_804A2688;

// .sbss
/* 4D5850 */ static int un_804D5850;
/* 4D5854 */ static int un_804D5854;
/* 4D5858 */ static int un_804D5858;
/* 4D585C */ static int un_804D585C;
/* 4D6D68 */ static HSD_GObj* un_804D6D68;
/* 4D6D6C */ static u8 un_804D6D6C;
/* 4D6D70 */ static u8 un_804D6D70[PL_SLOT_MAX];
/* 4D6D78 */ static HSD_Text* un_804D6D78;
/* 4D6D7C */ static int un_804D6D7C;
/* 4D6D80 */ static HSD_GObj* un_804D6D80;
/* 4D6D84 */ static int un_804D6D84;
/* 4D6D88 */ static s32 un_804D6D88;
/* 4D6D8C */ static s32 un_804D6D8C;
/* 4D6D90 */ static int un_804D6D90;
/* 4D6D9C */ static SceneDesc* un_804D6D9C;
/* 4D6DA0 */ static void* un_804D6DA0;
/* 4D6DA4 */ static SceneDesc* un_804D6DA4;
/* 4D6DA8 */ static int* un_804D6DA8;
/* 4D6DAC */ static int un_804D6DAC;
/* 4D6DB0 */ static int un_804D6DB0;
/* 4D6DB4 */ static int un_804D6DB4;
/* 4D6DB8 */ static int un_804D6DB8;
/* 4D6DBC */ static int un_804D6DBC;
/* 4D6DC0 */ static int un_804D6DC0;
/* 4D6E18 */ static DevText* devtext_drawlist;
/* 4D6E1C */ static HSD_GObj* devtext_gobj;
/* 4D6E20 */ static HSD_CObj* devtext_cobj;
/* 4D6E24 */ static int devtext_setup_classifier;
/* 4D6E28 */ static int devtext_setup_p_link;
/* 4D6E2C */ static int devtext_setup_priority;
/* 4D6E30 */ static int devtext_setup_gx_link;
/* 4D6E34 */ static int devtext_setup_render_priority;
/* 4D6E38 */ static DevText* devtext_poolhead;
/* 4D6E44 */ static UNK_T un_804D6E44;

// .sdata2
/* 4DDBA8 */ static char un_804DDBA8[4] = { 0, 1, 2, 3 };

#endif

#include "mncharsel.h"

#include "inlines.h"
#include "types.h"

#include "baselib/forward.h"
#include "ft/forward.h"

#include "lb/lb_013B.h"

#include <math.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/lb/types.h>
#include <melee/mn/mncharsel.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnmainrule.h>
#include <melee/mn/mnname.h>
#include <melee/mn/mnnamenew.h>
#include <melee/mn/types.h>

static u8 mnCharSel_804D50C8[4] = { 1, 2, 4, 8 };
static u8 mnCharSel_804D50CC[4] = { 1, 0, 0, 2 };
static u8 mnCharSel_804D50D0[8] = { 2, 0, 1, 0, 5, 3, 4, 0 };
static u8 mnCharSel_804D50D8[8] = { 2, 0, 8, 1, 7, 7, 7, 7 };
static u8 mnCharSel_804D50E0[3] = { 0, 1, 3 };

typedef struct CSSSceneModels {
    /* 0x00 */ HSD_CObjDesc* cam;
    /* 0x04 */ HSD_LightDesc* light0;
    /* 0x08 */ HSD_LightDesc* light1;
    /* 0x0C */ HSD_FogDesc* fog;
} CSSSceneModels;

typedef struct CSSAnimSet {
    /* 0x00 */ HSD_Joint* joint;
    /* 0x04 */ HSD_AnimJoint* anim;
    /* 0x08 */ HSD_MatAnimJoint* matanim;
    /* 0x0C */ HSD_ShapeAnimJoint* shapeanim;
} CSSAnimSet;

static CSSData* mnCharSel_804D6CB0;
static void* mnCharSel_804D6CB4;
static HSD_GObj* mnCharSel_804D6CB8;
static HSD_GObj* mnCharSel_804D6CBC;
static HSD_JObj* mnCharSel_804D6CC0;
static HSD_JObj* mnCharSel_804D6CC4;
static HSD_JObj* mnCharSel_804D6CC8;
static HSD_JObj* mnCharSel_804D6CCC;
static HSD_Archive* mnCharSel_804D6CD0;
static HSD_Archive* mnCharSel_804D6CD4;
static void* mnCharSel_804D6CD8;
static HSD_Text* mnCharSel_804D6CDC;
static HSD_Text* mnCharSel_804D6CE0;
static HSD_Text* mnCharSel_804D6CE4;
static HSD_Text* mnCharSel_804D6CE8;
static u32 mnCharSel_804D6CEC;
static s8 mnCharSel_804D6CF0;
static s8 mnCharSel_804D6CF1;
static u8 mnCharSel_804D6CF2;
static u8 mnCharSel_804D6CF3;
static s8 mnCharSel_804D6CF4;
static u8 mnCharSel_804D6CF5; ///< number of (open? valid?) CSS doors
static u8 mnCharSel_804D6CF6;
static u8 mnCharSel_804D6CF7;
static u8 mnCharSel_804D6CF8;
static s8 mnCharSel_804D6CF9;

/// Can't be enum bc float, but reused values
#define ICONROWHT_TOP_TOP 20.0F
#define ICONROWHT_MID_TOP 13.0F
#define ICONROWHT_BTM_TOP 6.0F
#define ICONROWHT_BTM_BTM (-1.0F)

/// Where each icon row is drawn, as opposed to the bounds it is hit-tested
/// against above.
#define ICONROWY_TOP 20.2F
#define ICONROWY_BTM 5.8F

/// Can't be enum bc float, but reused values
#define ICONBNDS_COL0_L (-30.0F)
#define ICONBNDS_COL1_L (-24.4F)
#define ICONBNDS_COL2_L (-17.4F)
#define ICONBNDS_COL3_L (-10.4F)
#define ICONBNDS_COL4_L (-3.4F)
#define ICONBNDS_COL5_L 3.6F
#define ICONBNDS_COL6_L 10.6F
#define ICONBNDS_COL7_L 17.6F
#define ICONBNDS_COL8_L 24.4F
#define ICONBNDS_COL8_R 30.2F

static CSSIconsData mnCharSel_803F0A48 = {
    {
        // GnW Name
        0x82, 0x6C, 0x82, 0x92, // 0x803F0A48
        0x81, 0x44, 0x82, 0x66, // 0x803F0A4C
        0x82, 0x81, 0x82, 0x8D, // 0x803F0A50
        0x82, 0x85, 0x81, 0x95, // 0x803F0A54
        0x82, 0x76, 0x82, 0x81, // 0x803F0A58
        0x82, 0x94, 0x82, 0x83, // 0x803F0A5C
        0x82, 0x88, 0x00, 0x00  // 0x803F0A60
    },
    {
        // Mode Info
        { 0x0000, 0x0001, 0x00007535 }, // 0x803F0A64
        { 0x0002, 0x000D, 0x0000753A }, // 0x803F0A6C
        { 0x0003, 0x000E, 0x0000753B }, // 0x803F0A74
        { 0x0004, 0x000F, 0x0000753C }, // 0x803F0A7C
        { 0x0007, 0x0011, 0x0000753D }, // 0x803F0A84
        { 0x0008, 0x0012, 0x0000753E }, // 0x803F0A8C
        { 0x0009, 0x0013, 0x0000753F }, // 0x803F0A94
        { 0x0006, 0x0010, 0x00007540 }, // 0x803F0A9C
        { 0x000A, 0x0014, 0x00007541 }, // 0x803F0AA4
        { 0x000B, 0x0015, 0x00007535 }, // 0x803F0AAC
        { 0x000C, 0x0016, 0x00007535 }, // 0x803F0AB4
        { 0x0000, 0x0000, 0x00007534 }, // 0x803F0ABC
        { 0x0001, 0x0000, 0x00007534 }, // 0x803F0AC4
        { 0x0002, 0x0000, 0x00007533 }, // 0x803F0ACC
        { 0x0003, 0x0000, 0x00007534 }, // 0x803F0AD4
        { 0x0004, 0x0000, 0x0007C864 }, // 0x803F0ADC
        { 0x0005, 0x0000, 0x00007531 }, // 0x803F0AE4
        { 0x0008, 0x0000, 0x00007534 }, // 0x803F0AEC
        { 0x0009, 0x0000, 0x00007534 }, // 0x803F0AF4
        { 0x000A, 0x0000, 0x00007534 }, // 0x803F0AFC
        { 0x000B, 0x0000, 0x00007534 }, // 0x803F0B04
        { 0x000C, 0x0000, 0x00007534 }, // 0x803F0B0C
        { 0x000D, 0x0000, 0x00007534 }, // 0x803F0B14
        { 0x0007, 0x0000, 0x00007532 }  // 0x803F0B1C
    },
};

static CSSIcon icons[25 + 1] = {
    // -------- Icons Top Row --------

    { // Dr. Mario -                      0x803F0B24
      ICONHUD_DRMARIO, CKIND_DRMARIO, ICONSTATE_UNLOCKED, 0x00,
      ICONJOINT_DRMARIO, ICONJOINT_DRMARIO, 0x000000C5, ICONBNDS_COL0_L,
      ICONBNDS_COL1_L, ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Mario -                          0x803F0B40
      ICONHUD_MARIO, CKIND_MARIO, ICONSTATE_TEMP, 0x00, ICONJOINT_MARIO,
      ICONJOINT_MARIO, 0x000000CD, ICONBNDS_COL1_L, ICONBNDS_COL2_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Luigi -                          0x803F0B5C
      ICONHUD_LUIGI, CKIND_LUIGI, ICONSTATE_TEMP, 0x00, ICONJOINT_LUIGI,
      ICONJOINT_LUIGI, 0x000000CC, ICONBNDS_COL2_L, ICONBNDS_COL3_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Bowser -                         0x803F0B78
      ICONHUD_KOOPA, CKIND_KOOPA, ICONSTATE_TEMP, 0x00, ICONJOINT_KOOPA,
      ICONJOINT_KOOPA, 0x000000CA, ICONBNDS_COL3_L, ICONBNDS_COL4_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Peach -                          0x803F0B94
      ICONHUD_PEACH, CKIND_PEACH, ICONSTATE_TEMP, 0x00, ICONJOINT_PEACH,
      ICONJOINT_PEACH, 0x000000D1, ICONBNDS_COL4_L, ICONBNDS_COL5_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Yoshi -                          0x803F0BB0
      ICONHUD_YOSHI, CKIND_YOSHI, ICONSTATE_TEMP, 0x00, ICONJOINT_YOSHI,
      ICONJOINT_YOSHI, 0x000000D7, ICONBNDS_COL5_L, ICONBNDS_COL6_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // DK -                             0x803F0BCC
      ICONHUD_DONKEY, CKIND_DONKEY, ICONSTATE_TEMP, 0x00, ICONJOINT_DONKEY,
      ICONJOINT_DONKEY, 0x000000C4, ICONBNDS_COL6_L, ICONBNDS_COL7_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Captain Falcon -                 0x803F0BE8
      ICONHUD_CAPTAIN, CKIND_CAPTAIN, ICONSTATE_TEMP, 0x00, ICONJOINT_CAPTAIN,
      ICONJOINT_CAPTAIN, 0x000000C2, ICONBNDS_COL7_L, ICONBNDS_COL8_L,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
    { // Ganondorf -                      0x803F0C04
      ICONHUD_GANON, CKIND_GANON, ICONSTATE_UNLOCKED, 0x00, ICONJOINT_GANON,
      ICONJOINT_GANON, 0x000000D9, ICONBNDS_COL8_L, ICONBNDS_COL8_R,
      ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },

    // -------- Icons Middle Row --------

    { // Falco -                          0x803F0C20
      ICONHUD_FALCO, CKIND_FALCO, ICONSTATE_UNLOCKED, 0x00, ICONJOINT_FALCO,
      ICONJOINT_FALCO, 0x000000C6, ICONBNDS_COL0_L, ICONBNDS_COL1_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Fox -                            0x803F0C3C
      ICONHUD_FOX, CKIND_FOX, ICONSTATE_TEMP, 0x00, ICONJOINT_FOX,
      ICONJOINT_FOX, 0x000000C7, ICONBNDS_COL1_L, ICONBNDS_COL2_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Ness -                           0x803F0C58
      ICONHUD_NESS, CKIND_NESS, ICONSTATE_TEMP, 0x00, ICONJOINT_NESS,
      ICONJOINT_NESS, 0x000000D0, ICONBNDS_COL2_L, ICONBNDS_COL3_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // ICs -                            0x803F0C74
      ICONHUD_POPONANA, CKIND_POPONANA, ICONSTATE_TEMP, 0x00,
      ICONJOINT_POPONANA, ICONJOINT_POPONANA, 0x000000C8, ICONBNDS_COL3_L,
      ICONBNDS_COL4_L, ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Kirby -                          0x803F0C90
      ICONHUD_KIRBY, CKIND_KIRBY, ICONSTATE_TEMP, 0x00, ICONJOINT_KIRBY,
      ICONJOINT_KIRBY, 0x000000C9, ICONBNDS_COL4_L, ICONBNDS_COL5_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Samus -                          0x803F0CAC
      ICONHUD_SAMUS, CKIND_SAMUS, ICONSTATE_TEMP, 0x00, ICONJOINT_SAMUS,
      ICONJOINT_SAMUS, 0x000000D5, ICONBNDS_COL5_L, ICONBNDS_COL6_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Zelda -                          0x803F0CC8
      ICONHUD_ZELDA, CKIND_ZELDA, ICONSTATE_TEMP, 0x00, ICONJOINT_ZELDA,
      ICONJOINT_ZELDA, 0x000000D6, ICONBNDS_COL6_L, ICONBNDS_COL7_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Link -                           0x803F0CE4
      ICONHUD_LINK, CKIND_LINK, ICONSTATE_TEMP, 0x00, ICONJOINT_LINK,
      ICONJOINT_LINK, 0x000000CB, ICONBNDS_COL7_L, ICONBNDS_COL8_L,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },
    { // Young Link -                     0x803F0D00
      ICONHUD_CLINK, CKIND_CLINK, ICONSTATE_UNLOCKED, 0x00, ICONJOINT_CLINK,
      ICONJOINT_CLINK, 0x000000C3, ICONBNDS_COL8_L, ICONBNDS_COL8_R,
      ICONROWHT_MID_TOP, ICONROWHT_BTM_TOP },

    // -------- Icons Bottom Row --------

    { // Pichu -                          0x803F0D1C
      ICONHUD_PICHU, CKIND_PICHU, ICONSTATE_UNLOCKED, 0x00, ICONJOINT_PICHU,
      ICONJOINT_PICHU, 0x000000D2, -23.4, ICONBNDS_COL2_L, ICONROWHT_BTM_TOP,
      ICONROWHT_BTM_BTM },
    { // Pikachu -                        0x803F0D38
      ICONHUD_PIKACHU, CKIND_PIKACHU, ICONSTATE_TEMP, 0x00, ICONJOINT_PIKACHU,
      ICONJOINT_PIKACHU, 0x000000D3, ICONBNDS_COL2_L, ICONBNDS_COL3_L,
      ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
    { // Jigglypuff -                     0x803F0D54
      ICONHUD_PURIN, CKIND_PURIN, ICONSTATE_TEMP, 0x00, ICONJOINT_PURIN,
      ICONJOINT_PURIN, 0x000000D4, ICONBNDS_COL3_L, ICONBNDS_COL4_L,
      ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
    { // Mewtwo -                         0x803F0D70
      ICONHUD_MEWTWO, CKIND_MEWTWO, ICONSTATE_TEMP, 0x00, ICONJOINT_MEWTWO,
      ICONJOINT_MEWTWO, 0x000000CF, ICONBNDS_COL4_L, ICONBNDS_COL5_L,
      ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
    { // Mr. Game & Watch -               0x803F0D8C
      ICONHUD_GAMEWATCH, CKIND_GAMEWATCH, ICONSTATE_TEMP, 0x00,
      ICONJOINT_GAMEWATCH, ICONJOINT_GAMEWATCH, 0x000000D8, ICONBNDS_COL5_L,
      ICONBNDS_COL6_L, ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
    { // Marth -                          0x803F0DA8
      ICONHUD_MARS, CKIND_MARS, ICONSTATE_TEMP, 0x00, ICONJOINT_MARS,
      ICONJOINT_MARS, 0x000000CE, ICONBNDS_COL6_L, ICONBNDS_COL7_L,
      ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
    { // Roy -                            0x803F0DC4
      ICONHUD_EMBLEM, CKIND_EMBLEM, ICONSTATE_UNLOCKED, 0x00, ICONJOINT_EMBLEM,
      ICONJOINT_EMBLEM, 0x000000DA, ICONBNDS_COL7_L, 23.6, ICONROWHT_BTM_TOP,
      ICONROWHT_BTM_BTM }
};

static CSSDoorsData mnCharSel_803F0DFC = {
    { { 0x2E, 0x33, 0x38, 0x85, 0x29,  0xA6,  0x3D,  0x41,
        0x40, 0,    0,    0,    0,     0,     0,     0,
        0,    0,    0,    0,    -35.6, -28.6, -26.8, -21.0F },
      { 0x2F, 0x34, 0x39, 0x8D, 0x2A,  0xA8,  0x43,  0x47,
        0x46, 0,    0,    0,    0,     0,     0,     0,
        0,    0,    0,    0,    -19.4, -13.4, -11.4, -6.0F },
      { 0x30, 0x35, 0x3A, 0x95, 0x2B, 0xAA, 0x49, 0x4D, 0x4C, 0,   0,   0,
        0,    0,    0,    0,    0,    0,    0,    0,    -4.2, 2.2, 3.5, 9.4 },
      { 0x31, 0x36, 0x3B, 0x9D, 0x2C,  0xAC,  0x4F,  0x53,
        0x52, 0x00, 0x00, 0x00, 0x00,  0x00,  0x00,  0x00,
        0x00, 0x00, 0x00, 0x00, 11.0F, 17.0F, 19.0F, 24.6 } },
};

static CSSTag mnCharSel_803F0E8C[4] = {
    { NULL, 0x70, 0x73, 0x74, 0x72, 0x71 },
    { NULL, 0x75, 0x78, 0x79, 0x77, 0x76 },
    { NULL, 0x7A, 0x7D, 0x7E, 0x7C, 0x7B },
    { NULL, 0x7F, 0x82, 0x83, 0x81, 0x80 },
};

static struct CSSDoorsMisc mnCharSel_803F0EBC = {
    0,    0,    0, 0, 0x4A, 0x4D, 0x4E,  0x4C, 0x4B, 0,    0,    0,
    0x2F, 0x01, 0, 0, 0,    NULL, -10.9, -4.2, 12.5, 19.6, -6.8, -12.1,
};

static struct CSSDoorsData2 data2 = {
    { 0x35, 0x39, 0x36, 0x38, 0x37 },
    0,
    0,
    0,
    -2.2,
    3.7,
    13.7,
    19.3,
    -12.4,
    -16.6,
    {
        { NULL, -22.5, 0x57 },
        { NULL, -7.1, 0x5D },
        { NULL, 8.3, 0x63 },
        { NULL, 23.7, 0x69 },
    },
};

typedef struct CSSAllData {
    u8 gnw_name[0x1C];
    CSSModeInfo mode_info[24];
    CSSIcon icons[26];
    CSSDoorsData doors_data;    // 0x3B4
    CSSTag tags[4];             // 0x444
    struct CSSDoorsMisc misc;   // 0x474
    struct CSSDoorsData2 data2; // 0x4A4
} CSSAllData;

#define CSS_ALL ((CSSAllData*) &mnCharSel_803F0A48)

TextKerning* mnCharSel_8025BC20(TextKerning* arg0, u32 arg1)
{
    TextKerning* kerning;
    u32 render_zeroes;
    render_zeroes = 0;
    kerning = HSD_SisLib_804D1124[0][41].kerning;
    if (arg1 >= 10000) {
        arg1 = 9999;
    }
    if (arg1 >= 1000) {
        arg0->left = kerning[arg1 / 1000].left;
        arg0->right = kerning[arg1 / 1000].right;
        arg0 += 1;
        arg1 = arg1 % 1000;
        render_zeroes = 1;
    }
    if ((arg1 >= 100) || render_zeroes) {
        arg0->left = kerning[arg1 / 100].left;
        arg0->right = kerning[arg1 / 100].right;
        arg0 = arg0 + 1;
        arg1 = arg1 % 100;
        render_zeroes++;
    }
    if ((arg1 >= 10) || render_zeroes) {
        arg0->left = kerning[arg1 / 10].left;
        arg0->right = kerning[arg1 / 10].right;
        arg0 = arg0 + 1;
        arg1 = arg1 % 10;
    }
    arg0->left = kerning[arg1].left;
    arg0->right = kerning[arg1].right;
    arg0[1].left = 0;
    return ++arg0;
}

void mnCharSel_8025BD30(void)
{
    TextKerning* kerning;
    u32 match_type;

    kerning = HSD_SisLib_804D1124[0][37].kerning;

    match_type = mnCharSel_804D6CB0->match_type;

    if (match_type == VS_CAMERA) {
        HSD_SisLib_803A6530(0, 0x4A, 0x4F);
        return;
    }
    if (match_type == VS_STAMINA) {
        HSD_SisLib_803A6530(0, 0x4A, 0x50);
        return;
    }
    if (lbLang_IsSavedLanguageJP()) {
        if (gmMainLib_GetGameRules()->mode == 1) {
            mnCharSel_8025BC20(kerning, gmMainLib_GetGameRules()->stock_count);
        } else if (gmMainLib_GetGameRules()->time_limit != 0) {
            mnCharSel_8025BC20(kerning, gmMainLib_GetGameRules()->time_limit);
            HSD_SisLib_803A660C(0, 0x4A, 0x53);
        } else {
            HSD_SisLib_803A6530(0, 0x4A, 0x51);
        }
        switch (gmMainLib_GetGameRules()->mode) {
        case Mode_Time:
            HSD_SisLib_803A660C(0, 0x4A, 0x4B);
            return;
        case Mode_Stock:
            HSD_SisLib_803A660C(0, 0x4A, 0x4C);
            return;
        case Mode_Coin:
            HSD_SisLib_803A660C(0, 0x4A, 0x4D);
            return;
        case Mode_Bonus:
            HSD_SisLib_803A660C(0, 0x4A, 0x4E);
            return;
        }
    } else {
        switch (gmMainLib_GetGameRules()->mode) {
        case Mode_Time:
            if (gmMainLib_GetGameRules()->time_limit != 0) {
                mnCharSel_8025BC20(kerning,
                                   gmMainLib_GetGameRules()->time_limit);
                HSD_SisLib_803A660C(0, 0x4A, 0x53);
            } else {
                HSD_SisLib_803A6530(0, 0x4A, 0x51);
            }
            HSD_SisLib_803A660C(0, 0x4A, 0x4B);
            return;
        case Mode_Stock:
            mnCharSel_8025BC20(kerning, gmMainLib_GetGameRules()->stock_count);
            if (gmMainLib_GetGameRules()->stock_count < 2U) {
                HSD_SisLib_803A660C(0, 0x4A, 0x55);
            } else {
                HSD_SisLib_803A660C(0, 0x4A, 0x54);
            }
            HSD_SisLib_803A660C(0, 0x4A, 0x4C);
            return;
        case Mode_Coin:
            if (gmMainLib_GetGameRules()->time_limit != 0) {
                mnCharSel_8025BC20(kerning,
                                   gmMainLib_GetGameRules()->time_limit);
                HSD_SisLib_803A660C(0, 0x4A, 0x53);
            } else {
                HSD_SisLib_803A6530(0, 0x4A, 0x51);
            }
            HSD_SisLib_803A660C(0, 0x4A, 0x4D);
            return;
        case Mode_Bonus:
            if (gmMainLib_GetGameRules()->time_limit != 0) {
                mnCharSel_8025BC20(kerning,
                                   gmMainLib_GetGameRules()->time_limit);
                HSD_SisLib_803A660C(0, 0x4A, 0x53);
            } else {
                HSD_SisLib_803A6530(0, 0x4A, 0x51);
            }
            HSD_SisLib_803A660C(0, 0x4A, 0x4E);
            return;
        }
    }

    // Preserve literals from the inlined helpers at their original pool sites.
    (void) 200.0f;
    (void) 0.0f;
    (void) 4503601774854144.0;
    (void) "%02d:%02d";
    (void) "%02d";
    (void) "%d:%02d:%02d";
    (void) "99:59:59";
    (void) "99";
}

static inline f32 loadStickValue(const s8* value)
{
    return (f32) *value;
}

static inline void getStickDelta(int port, f32* dx, f32* dy)
{
    f32 stick_x = loadStickValue(&HSD_PadCopyStatus[(u8) port].stickX);
    f32 stick_y = (f32) HSD_PadCopyStatus[(u8) port].stickY;
    f32 mag_sq = (stick_x * stick_x) + (stick_y * stick_y);
    if (mag_sq < 200.0f) {
        *dy = 0.0f;
        *dx = 0.0f;
    } else {
        f32 angle;
        f32 adj;
        adj = mag_sq - 200.0f;
        angle = atan2f(stick_x, stick_y);
        *dx = adj * sinf(angle);
        *dy = adj * cosf(angle);
    }
}

static inline void drawTimeText(HSD_Text* x, HSD_Text* y, int hours,
                                int minutes, int seconds, int microseconds)
{
    if (hours == 0) {
        HSD_SisLib_803A70A0(x, 0, "%02d:%02d", minutes, seconds);
        HSD_SisLib_803A70A0(y, 0, "%02d", microseconds);
    } else if (hours < 100) {
        HSD_SisLib_803A70A0(x, 0, "%d:%02d:%02d", hours, minutes, seconds);
        HSD_SisLib_803A70A0(y, 0, "%02d", microseconds);
    } else {
        HSD_SisLib_803A70A0(x, 0, "99:59:59");
        HSD_SisLib_803A70A0(y, 0, "99");
    }
}

static inline u32 getClassicHighscore(u8 hud)
{
    return gm_80162BD8(hud);
}

static inline u32 getAdventureHighscore(u8 hud)
{
    return gm_80162DD4(hud);
}

static inline u32 getAllStarHighscore(u8 hud)
{
    return gm_80162FD0(hud);
}

/// Centimetres to metres, truncated to one decimal place.
static inline f32 toMeters(f32 cm)
{
    return (f32) (int) (10.0f * (cm / 100.0f)) / 10.0f;
}

/// Centimetres to feet, truncated to one decimal place.
static inline f32 toFeet(f32 cm)
{
    return (f32) (int) (10.0f * (cm / 30.4788f)) / 10.0f;
}

static inline HSD_JObj* inline3(int i, float x)
{
    HSD_JObj* sp5C;
    HSD_JObj* cc0;
    HSD_JObj* arc = mnCharSel_804D6CC0;
    float frame = x + 1;
    lb_80011E24(arc, &sp5C, i, -1);
    cc0 = sp5C;
    HSD_ForeachAnim(cc0, JOBJ_TYPE, MOBJ_MASK, HSD_AObjReqAnim, AOBJ_ARG_AF,
                    frame);
    HSD_JObjAnimAll(sp5C);
    HSD_ForeachAnim(sp5C, JOBJ_TYPE, MOBJ_MASK, HSD_AObjStopAnim, AOBJ_ARG_AOV,
                    0, 0);
    return sp5C;
}

#define show_kos(x, y)                                                        \
    (lbLang_IsSavedLanguageJP()                                               \
         ? HSD_SisLib_803A70A0((x), 0, "%d \x90\x6c\x94\xb2\x82\xab", (y))    \
         : HSD_SisLib_803A70A0((x), 0, "%d \x82\x6a\x82\x6e\x82\x93", (y)))

void mnCharSel_8025C020(int arg0)
{
    HSD_JObj* sp7C;
    u8 sp7B;
    u8 sp7A;
    u8 sp79;
    u8 sp78;

    s32 i = mnCharSel_803F0DFC.doors[0].sel_icon;
    u8 hud_index = icons[i].ft_hudindex;
    if (arg0 != 0) {
        if (mnCharSel_804D6CDC != 0U) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, NULL);
        }
        if (mnCharSel_804D6CE0 != 0U) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE0, 0, NULL);
        }
    }
    switch (mnCharSel_804D6CB0->match_type) {
    case REG_CLASSIC:
        sp7C = inline3(0x42, *gmMainLib_8015D194(hud_index));
        if (arg0 != 0) {
            HSD_JObjSetFlags(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%08d",
                                getClassicHighscore(hud_index));
            if (gmMainLib_8015D0D8(hud_index) != 0) {
                HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
            }
        }
        HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%09d", gm_80162C48());
        if (gm_80162D1C() != 0) {
            sp7C = inline3(0x43, gm_80162D6C());
            HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
        }
        break;
    case REG_ADVENTURE:
        sp7C = inline3(0x42, *gmMainLib_8015D2BC(hud_index));
        if (arg0 != 0) {
            HSD_JObjSetFlags(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%08d",
                                getAdventureHighscore(hud_index));
            if (gmMainLib_8015D200(hud_index) != 0) {
                HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
            }
        }
        HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%09d", gm_80162E44());
        if (gm_80162F18() != 0) {
            sp7C = inline3(0x43, gm_80162F68());
            HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
        }
        break;
    case REG_ALLSTAR:
        sp7C = inline3(0x42, *gmMainLib_8015D3E4(hud_index));
        if (arg0 != 0) {
            HSD_JObjSetFlags(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%08d",
                                getAllStarHighscore(hud_index));
            if (gmMainLib_8015D328(hud_index) != 0) {
                HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
            }
        }
        HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, "%09d", gm_80163040());
        if (gm_80163114() != 0) {
            sp7C = inline3(0x43, gm_80163164());
            HSD_JObjClearFlags(sp7C, JOBJ_HIDDEN);
        }
        break;
    case STADIUM_TARGET:
        if (arg0 == 0) {
            int target_count = gm_8016332C(hud_index);
            if (target_count != -1U) {
                if (lbLang_IsSavedLanguageJP() != 0) {
                    HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d \x8c\xc2",
                                        target_count);
                } else {
                    HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d \x81\x40",
                                        target_count);
                }
            } else {
                gm_80163374(hud_index, &sp7B, &sp7A, &sp79, &sp78);
                drawTimeText(mnCharSel_804D6CDC, mnCharSel_804D6CE0, sp7B,
                             sp7A, sp79, sp78);
            }
        }
        lb_80011E24(mnCharSel_804D6CC8, &sp7C, 3, -1);
        if (gm_801634D4(&sp7B, &sp7A, &sp79, &sp78) != 0) {
            drawTimeText(mnCharSel_804D6CE4, mnCharSel_804D6CE8, sp7B, sp7A,
                         sp79, sp78);
            HSD_JObjClearFlagsAll(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, NULL);
            HSD_SisLib_803A70A0(mnCharSel_804D6CE8, 0, NULL);
            HSD_JObjSetFlagsAll(sp7C, JOBJ_HIDDEN);
        }
        break;
    case STADIUM_HOMERUN:
        if (arg0 == 0) {
            if (lbLang_IsSavedLanguageJP()) {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%.1f",
                                    toMeters(gm_801631CC(hud_index)));
            } else {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%.1f",
                                    toFeet(gm_801631CC(hud_index)));
            }
        }
        if (lbLang_IsSavedLanguageJP()) {
            HSD_SisLib_803A70A0(
                mnCharSel_804D6CE4, 0, "%.1f",
                (f32) (int) (10.0f * (gm_801631F0() / 100.0f)) / 10.0f);
        } else {
            HSD_SisLib_803A70A0(
                mnCharSel_804D6CE4, 0, "%.1f",
                (f32) (int) (10.0f * (gm_801631F0() / 30.4788f)) / 10.0f);
        }
        break;
    case TRAINING_MODE:
        if (arg0 == 0) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0, "%d",
                                gm_80163274(hud_index));
        }
        break;
    case STADIUM_MULTIMAN_10:
        if (arg0 == 0) {
            if (gm_8016365C(hud_index) != 0) {
                show_kos(mnCharSel_804D6CDC, gm_80163690(hud_index));
            } else {
                gm_801636D8(hud_index, &sp7B, &sp7A, &sp79, &sp78);
                drawTimeText(mnCharSel_804D6CDC, mnCharSel_804D6CE0, sp7B,
                             sp7A, sp79, sp78);
            }
        }
        lb_80011E24(mnCharSel_804D6CC8, &sp7C, 3, -1);
        if (gm_80163838(&sp7B, &sp7A, &sp79, &sp78) != 0) {
            drawTimeText(mnCharSel_804D6CE4, mnCharSel_804D6CE8, sp7B, sp7A,
                         sp79, sp78);
            HSD_JObjClearFlagsAll(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, NULL);
            HSD_SisLib_803A70A0(mnCharSel_804D6CE8, 0, NULL);
            HSD_JObjSetFlagsAll(sp7C, JOBJ_HIDDEN);
        }
        break;
    case STADIUM_MULTIMAN_100:
        if (arg0 == 0) {
            if (gm_801639C0(hud_index) != 0) {
                show_kos(mnCharSel_804D6CDC, gm_801639F4(hud_index));
            } else {
                gm_80163A3C(hud_index, &sp7B, &sp7A, &sp79, &sp78);
                drawTimeText(mnCharSel_804D6CDC, mnCharSel_804D6CE0, sp7B,
                             sp7A, sp79, sp78);
            }
        }
        lb_80011E24(mnCharSel_804D6CC8, &sp7C, 3, -1);
        if (gm_80163B9C(&sp7B, &sp7A, &sp79, &sp78) != 0) {
            drawTimeText(mnCharSel_804D6CE4, mnCharSel_804D6CE8, sp7B, sp7A,
                         sp79, sp78);
            HSD_JObjClearFlagsAll(sp7C, JOBJ_HIDDEN);
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0, NULL);
            HSD_SisLib_803A70A0(mnCharSel_804D6CE8, 0, NULL);
            HSD_JObjSetFlagsAll(sp7C, JOBJ_HIDDEN);
        }
        break;
    case STADIUM_3_MIN_MELEE:
        if (arg0 == 0) {
            if (lbLang_IsSavedLanguageJP()) {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0,
                                    "%d \x90\x6c\x94\xb2\x82\xab",
                                    gm_Get3MinMultimanHighscore(hud_index));
            } else {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0,
                                    "%d \x82\x6a\x82\x6e\x82\x93",
                                    gm_Get3MinMultimanHighscore(hud_index));
            }
        }
        if (lbLang_IsSavedLanguageJP()) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0,
                                "%d \x90\x6c\x94\xb2\x82\xab",
                                gm_Get3MinMultimanTotalHighscore());
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0,
                                "%d \x82\x6a\x82\x6e\x82\x93",
                                gm_Get3MinMultimanTotalHighscore());
        }
        break;
    case STADIUM_15_MIN_MELEE:
        if (!arg0) {
            if (lbLang_IsSavedLanguageJP()) {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0,
                                    "%d \x90\x6c\x94\xb2\x82\xab",
                                    gm_Get15MinMultimanHighscore(hud_index));
            } else {
                HSD_SisLib_803A70A0(mnCharSel_804D6CDC, 0,
                                    "%d \x82\x6a\x82\x6e\x82\x93",
                                    gm_Get15MinMultimanHighscore(hud_index));
            }
        }
        if (lbLang_IsSavedLanguageJP()) {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0,
                                "%d \x90\x6c\x94\xb2\x82\xab",
                                gm_Get15MinMultimanTotalHighscore());
        } else {
            HSD_SisLib_803A70A0(mnCharSel_804D6CE4, 0,
                                "%d \x82\x6a\x82\x6e\x82\x93",
                                gm_Get15MinMultimanTotalHighscore());
        }
        break;
    case STADIUM_ENDLESS_MELEE:
        if (!arg0) {
            show_kos(mnCharSel_804D6CDC, gm_GetEndlessHighscore(hud_index));
        }
        show_kos(mnCharSel_804D6CE4, gm_GetEndlessTotalHighscore());
        break;
    case STADIUM_CRUEL_MELEE:
        if (!arg0) {
            show_kos(mnCharSel_804D6CDC, gm_GetCruelHighscore(hud_index));
        }
        show_kos(mnCharSel_804D6CE4, gm_GetCruelTotalHighscore());
        break;
    }
}

struct CSSCursorData {
    /* 0x00 */ HSD_GObj* gobj;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
    /* 0x07 */ u8 x7;
    /* 0x08 */ u16 x8;
    /* 0x0A */ u16 xA;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
};

void mnCharSel_8025D1C4(int port, int mode)
{
    u8* sis_buf;
    HSD_JObj* child;
    HSD_JObj* next1;
    HSD_JObj* next2;
    HSD_JObj* next3;
    HSD_Text* text;
    f32 star_x;
    s32 show_stars;
    int star_count;
    CSSData* css = mnCharSel_804D6CB0;
    CSSKOStar* stars;

    HSD_JObj* sp10;

    switch (css->match_type) {
    case VS_MELEE:
    case VS_SUDDEN_DEATH:
    case VS_GIANT:
    case VS_TINY:
    case VS_INVISIBLE:
    case VS_FIXED_CAMERA:
    case VS_SINGLE_BUTTON:
    case VS_LIGHTNING:
    case VS_SLOWMO:
        show_stars = true;
        break;
    default:
        show_stars = false;
        break;
    }

    if (show_stars) {
        stars = &data2.ko_stars[port];
        {
            u8* buf = &data2.ko_stars[port].joint2;
            sis_buf = buf;
        }
        star_count = css->ko_star_counts[port];
        star_x = data2.ko_stars[port].x4;
        text = stars->text;

        lb_80011E24(mnCharSel_804D6CC0, &sp10, data2.ko_stars[port].joint, -1);

        if (mode == 0 || star_count == 0) {
            text->hidden = 1;
            HSD_JObjSetFlagsAll(sp10, JOBJ_HIDDEN);
            return;
        }
        HSD_JObjClearFlagsAll(sp10, JOBJ_HIDDEN);
        if (star_count < 6) {
            text->hidden = 1;
            HSD_JObjSetTranslateX(sp10, 0.9f * star_count + star_x - 4.5f);
            if (sp10 == NULL) {
                child = NULL;
            } else {
                child = sp10->child;
            }
            sp10 = child;
            if (star_count < 5) {
                HSD_JObjSetFlags(sp10, JOBJ_HIDDEN);
            }
            if (sp10 == NULL) {
                next1 = NULL;
            } else {
                next1 = sp10->next;
            }
            sp10 = next1;
            if (star_count < 4) {
                HSD_JObjSetFlags(sp10, JOBJ_HIDDEN);
            }
            if (sp10 == NULL) {
                next2 = NULL;
            } else {
                next2 = sp10->next;
            }
            sp10 = next2;
            if (star_count < 3) {
                HSD_JObjSetFlags(sp10, JOBJ_HIDDEN);
            }
            if (sp10 == NULL) {
                next3 = NULL;
            } else {
                next3 = sp10->next;
            }
            sp10 = next3;
            if (star_count < 2) {
                HSD_JObjSetFlags(sp10, JOBJ_HIDDEN);
            }
        } else {
            text->hidden = 0;
            if (star_count >= 0x3E8) {
                star_x -= 3.0F;
            } else if (star_count >= 100) {
                star_x -= 1.5F;
            }

            HSD_JObjSetTranslateX(sp10, star_x);

            text->pos_x = 0.6F + star_x;
            if (mode == 1) {
                text->text_color.a = 0x50;
            } else {
                text->text_color.a = 0xA0;
            }
            {
                TextKerning* tmp = (TextKerning*) HSD_SisLib_803A6478(
                    sis_buf, &HSD_SisLib_804D1124[0][43].kerning->left);
                mnCharSel_8025BC20(tmp, star_count);
            }
            HSD_SisLib_803A6368(text, 0x56);
            text->sis_buffer = (SIS*) sis_buf;
            HSD_JObjSetFlags(sp10 = HSD_JObjGetChild(sp10), JOBJ_HIDDEN);
            HSD_JObjSetFlags(sp10 = HSD_JObjGetNext(sp10), JOBJ_HIDDEN);
            HSD_JObjSetFlags(sp10 = HSD_JObjGetNext(HSD_JObjGetNext(sp10)),
                             JOBJ_HIDDEN);
            HSD_JObjSetFlags(sp10 = HSD_JObjGetNext(sp10), JOBJ_HIDDEN);
        }
    }
}

static inline void sethidden(HSD_JObj* jobj, bool hidden)
{
    if (hidden) {
        HSD_JObjSetFlags(jobj, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlags(jobj, JOBJ_HIDDEN);
    }
}

static inline HSD_JObj* animateJoint(HSD_JObj* root, u8 joint, u32 mask,
                                     f32 frame)
{
    HSD_JObj* jobj;
    HSD_JObj* cc0;
    HSD_JObj* cc1;
    lb_80011E24(root, &jobj, joint, -1);
    cc0 = jobj;
    HSD_ForeachAnim(cc0, JOBJ_TYPE, mask, HSD_AObjReqAnim, AOBJ_ARG_AF, frame);
    HSD_JObjAnimAll(jobj);
    cc1 = jobj;
    HSD_ForeachAnim(cc1, JOBJ_TYPE, mask, HSD_AObjStopAnim, AOBJ_ARG_AOV, 0,
                    0);
    return jobj;
}

static inline HSD_JObj* animateJointPadded(HSD_JObj* root, u8 joint, u32 mask,
                                           f32 frame)
{
    struct {
        HSD_JObj* jobj;
        u8 pad[8];
    } state;
    HSD_JObj* cc0;
    HSD_JObj* cc1;
    lb_80011E24(root, &state.jobj, joint, -1);
    cc0 = state.jobj;
    HSD_ForeachAnim(cc0, JOBJ_TYPE, mask, HSD_AObjReqAnim, AOBJ_ARG_AF, frame);
    HSD_JObjAnimAll(state.jobj);
    cc1 = state.jobj;
    HSD_ForeachAnim(cc1, JOBJ_TYPE, mask, HSD_AObjStopAnim, AOBJ_ARG_AOV, 0,
                    0);
    return state.jobj;
}

static inline HSD_JObj* animateJointLeadingPad(HSD_JObj* root, u8 joint,
                                               u32 mask, f32 frame)
{
    HSD_JObj* pad0;
    HSD_JObj* pad1;
    HSD_JObj* pad2;
    HSD_JObj* pad3;
    HSD_JObj* pad4;
    HSD_JObj* pad5;
    HSD_JObj* jobj;
    HSD_JObj* cc0;
    HSD_JObj* cc1;
    (void) &pad0;
    (void) &pad1;
    (void) &pad2;
    (void) &pad3;
    (void) &pad4;
    (void) &pad5;
    lb_80011E24(root, &jobj, joint, -1);
    cc0 = jobj;
    HSD_ForeachAnim(cc0, JOBJ_TYPE, mask, HSD_AObjReqAnim, AOBJ_ARG_AF, frame);
    HSD_JObjAnimAll(jobj);
    cc1 = jobj;
    HSD_ForeachAnim(cc1, JOBJ_TYPE, mask, HSD_AObjStopAnim, AOBJ_ARG_AOV, 0,
                    0);
    return jobj;
}

void mnCharSel_8025D5AC(int door, int frame, bool hidden)
{
    HSD_JObj* sp5C;
    HSD_JObj* sp58;
    HSD_JObj* sp54;
    HSD_JObj* sp50;

    HSD_JObj* sp48;
    HSD_JObj* sp44;
    int i;

    if (mnCharSel_804D6CF5 == 1) {
        if (door != 0) {
            sp5C =
                animateJoint(mnCharSel_804D6CC4, 4, TOBJ_MASK, (float) frame);
            sethidden(sp5C, hidden);

            sp58 =
                animateJoint(mnCharSel_804D6CC4, 6, TOBJ_MASK, (float) frame);
            sethidden(sp58, hidden);
            return;
        }
        sp54 =
            animateJoint(mnCharSel_804D6CC0, 0x2B, TOBJ_MASK, (float) frame);
        sethidden(sp54, hidden);

        sp50 =
            animateJoint(mnCharSel_804D6CC0, 0x2D, TOBJ_MASK, (float) frame);
        sethidden(sp50, hidden);
        if (hidden) {
            frame = 0xB9;
        }
        for (i = 0; i < 5; i++) {
            u8 tmp = data2.xf0[i];
            animateJoint(mnCharSel_804D6CC0, tmp, TOBJ_MASK, (float) frame);
        }
        mnCharSel_8025C020(hidden);
        return;
    }

    sp48 = animateJoint(mnCharSel_804D6CC0,
                        mnCharSel_803F0DFC.doors[door].costume_joint,
                        TOBJ_MASK, (float) frame);
    sethidden(sp48, hidden);

    sp44 = animateJoint(mnCharSel_804D6CC0,
                        mnCharSel_803F0DFC.doors[door].emblem_joint, TOBJ_MASK,
                        (float) frame);
    sethidden(sp44, hidden);
}

static inline bool isDuplicateCostumeWith(int door, CSSData* css,
                                          u8 door_count)
{
    int num_doors;
    int j;
    CSSDoor* base_door = &mnCharSel_803F0DFC.doors[door];

    if (css->match_type == TRAINING_MODE) {
        num_doors = 2;
    } else {
        num_doors = door_count;
    }

    for (j = 0; j < num_doors; j++) {
        CSSDoor* other_door = &mnCharSel_803F0DFC.doors[j];
        if (door != j && other_door->p_kind != 3 &&
            other_door->sel_icon < 0x19 &&
            other_door->sel_icon == base_door->sel_icon &&
            base_door->costume == other_door->costume)
        {
            return true;
        }
    }
    return false;
}

static inline CSSData* loadCSSValue(CSSData* volatile* css)
{
    return *css;
}

static inline bool equalU8(u8 lhs, u8 rhs)
{
    return lhs == rhs;
}

/// Variant of isDuplicateCostume that reads the base door's icon and
/// costume once before the scan.
static inline bool isDuplicateCostumeCached(int door)
{
    CSSDoor* base_door = &mnCharSel_803F0DFC.doors[door];
    u8 sel;
    u8 cost;
    int num_doors;
    int j;

    if (mnCharSel_804D6CB0->match_type == TRAINING_MODE) {
        num_doors = 2;
    } else {
        num_doors = mnCharSel_804D6CF5;
    }

    sel = base_door->sel_icon;
    cost = base_door->costume;

    (void) sel;
    (void) cost;
    for (j = 0; j < num_doors; j++) {
        if (door != j && mnCharSel_803F0DFC.doors[j].p_kind != 3 &&
            mnCharSel_803F0DFC.doors[j].sel_icon < 0x19 &&
            equalU8(mnCharSel_803F0DFC.doors[j].sel_icon, sel) &&
            cost == mnCharSel_803F0DFC.doors[j].costume)
        {
            return true;
        }
    }
    return false;
}

static inline bool isDuplicateCostumeExact(int door)
{
    int num_doors;
    int j;
    CSSDoor* base_door;

    if (mnCharSel_804D6CB0->match_type == TRAINING_MODE) {
        num_doors = 2;
    } else {
        u8 door_count = mnCharSel_804D6CF5;
        num_doors = door_count;
    }

    base_door = &mnCharSel_803F0DFC.doors[door];
    for (j = 0; j < num_doors; j++) {
        CSSDoor* other_door = &mnCharSel_803F0DFC.doors[j];
        if (door != j && other_door->p_kind != 3 &&
            other_door->sel_icon < 0x19 &&
            other_door->sel_icon == base_door->sel_icon &&
            base_door->costume == other_door->costume)
        {
            return true;
        }
    }
    return false;
}

static inline bool isDuplicateCostume(int door)
{
    int num_doors;
    int j;
    CSSDoor* base_door = &mnCharSel_803F0DFC.doors[door];

    if (mnCharSel_804D6CB0->match_type == TRAINING_MODE) {
        num_doors = 2;
    } else {
        num_doors = mnCharSel_804D6CF5;
    }

    for (j = 0; j < num_doors; j++) {
        CSSDoor* other_door = &mnCharSel_803F0DFC.doors[j];
        if (door != j && other_door->p_kind != 3 &&
            other_door->sel_icon < 0x19 &&
            other_door->sel_icon == base_door->sel_icon &&
            base_door->costume == other_door->costume)
        {
            return true;
        }
    }
    return false;
}

#ifdef MUST_MATCH
#pragma dont_inline on
#endif
bool mnCharSel_8025DAA0(int door)
{
    int num_doors;
    int j;

    if (mnCharSel_804D6CB0->match_type == TRAINING_MODE) {
        num_doors = 2;
    } else {
        num_doors = mnCharSel_804D6CF5;
    }

    for (j = 0; j < num_doors; j++) {
        if (door != j && mnCharSel_803F0DFC.doors[j].p_kind != 3 &&
            mnCharSel_803F0DFC.doors[j].sel_icon < 0x19 &&
            mnCharSel_803F0DFC.doors[j].sel_icon ==
                mnCharSel_803F0DFC.doors[door].sel_icon &&
            mnCharSel_803F0DFC.doors[door].costume ==
                mnCharSel_803F0DFC.doors[j].costume)
        {
            return true;
        }
    }
    return false;
}
#ifdef MUST_MATCH
#pragma dont_inline off
#endif

static inline void pickUniqueCostume(int door)
{
    if (mnCharSel_8025DAA0(door) != 0) {
        int v = 0;
        for (;;) {
            mnCharSel_803F0DFC.doors[door].costume = v;
            if (mnCharSel_8025DAA0(door) == 0) {
                break;
            }
            v += 1;
        }
    }
}

static inline s32 getHandicapValue(int port)
{
    s32 hval;
    if (gmMainLib_GetGameRules()->handicap == 1) {
        hval = (u8) gm_801685D4(
            port, mnCharSel_804D6CB0->data.data.players[port].xA);
    } else {
        hval = (u8) mnCharSel_804D6CB0->data.data.players[port].handicap;
    }
    return hval != 0 ? hval : 1;
}

void mnCharSel_8025DB34(u8 arg0)
{
    struct {
        s32 v;
    } team;
    HSD_JObj* sp90;
    f32 anim_frame;
    u8 joint;
    u8 sel_icon;
    s32 hud_idx;
    s32 color;
    f32 door_frame;
    sel_icon = mnCharSel_803F0DFC.doors[arg0].sel_icon;
    hud_idx = icons[sel_icon].ft_hudindex;
    mnCharSel_8025D5AC((int) arg0, 0, 1);

    /* Name display */
    if (mnCharSel_803F0E8C[arg0].data->use_tag == 0 && (int) sel_icon < 0x19) {
        mnCharSel_803F0E8C[arg0].data->text->default_kerning = 1;
        if (lbLang_IsSavedLanguageUS() != 0 && (int) sel_icon == 0x16) {
            HSD_SisLib_803A70A0(mnCharSel_803F0E8C[arg0].data->text, 0,
                                (char*) mnCharSel_803F0A48.gnw_name);
        } else {
            HSD_SisLib_803A70A0(
                mnCharSel_803F0E8C[arg0].data->text, 0,
                (char*) gm_80160980(icons[sel_icon].char_kind));
        }
    }

    /* Costume duplicate check */
    {
        u8 new_icon = mnCharSel_803F0DFC.doors[arg0].sel_icon;
        if (new_icon != mnCharSel_803F0DFC.doors[arg0].sel_icon_prev) {
            mnCharSel_803F0DFC.doors[arg0].sel_icon_prev = new_icon;
            {
                u8 costume_var;
                for (costume_var = 0;; costume_var++) {
                    mnCharSel_803F0DFC.doors[arg0].costume = costume_var;
                    if (!isDuplicateCostumeExact(arg0)) {
                        break;
                    }
                }
            }
            if (mnCharSel_804D6CF6 != 3 && mnCharSel_804D6CF6 != 4) {
                sfxMove();
            }
        }
    }

    if (mnCharSel_804D6CF5 == 1) {
        /* 1P mode */
        if (arg0 != 0) {
            anim_frame = (f32) mnCharSel_804D50D8[1];
            animateJoint(mnCharSel_804D6CC4, 2, TOBJ_MASK, anim_frame);
            anim_frame = (f32) mnCharSel_804D50D8[1];
            animateJoint(mnCharSel_804D6CC4, 4, MOBJ_MASK, anim_frame);
        } else {
            anim_frame = (f32) mnCharSel_804D50D8[mnCharSel_804D6CF0];
            animateJoint(mnCharSel_804D6CC0, 0x29, TOBJ_MASK, anim_frame);
            anim_frame = (f32) mnCharSel_804D50D8[mnCharSel_804D6CF0];
            animateJoint(mnCharSel_804D6CC0, 0x2B, MOBJ_MASK, anim_frame);
        }
        if (mnCharSel_803F0E8C[arg0].data->use_tag == 0 &&
            mnCharSel_803F0DFC.doors[arg0].sel_icon >= 0x19U)
        {
            mnCharSel_803F0E8C[arg0].data->text->hidden = 1;
        } else {
            mnCharSel_803F0E8C[arg0].data->text->hidden = 0;
        }
    } else {
        /* VS mode */
        joint = mnCharSel_803F0DFC.doors[arg0].door_joint;
        lb_80011E24(mnCharSel_804D6CC0, &sp90, joint, -1);
        if (mnCharSel_803F0DFC.doors[arg0].p_kind_prev == 3) {
            {
                HSD_JObj* anim_jobj = sp90;
                HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjReqAnim, AOBJ_ARG_AF, 0.0f);
            }
            HSD_JObjAnimAll(sp90);
            if (mnCharSel_803F0DFC.doors[arg0].p_kind == 3) {
                HSD_ForeachAnim(sp90, JOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
            } else {
                mnCharSel_8025D1C4((int) arg0, 2);
                pickUniqueCostume((int) arg0);
                mnCharSel_803F0DFC.doors[arg0].dooranim_timer = 0x1E;
                if (mnCharSel_804D6CF6 != 3 && mnCharSel_804D6CF6 != 4) {
                    lbAudioAx_800237A8(0xB9, 0x7F, 0x40);
                }
            }
        } else {
            {
                HSD_JObj* anim_jobj = sp90;
                HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjReqAnim, AOBJ_ARG_AF, 40.0f);
            }
            HSD_JObjAnimAll(sp90);
            if (mnCharSel_803F0DFC.doors[arg0].p_kind == 3) {
                mnCharSel_8025D1C4((int) arg0, 0);
                mnCharSel_803F0DFC.doors[arg0].dooranim_timer = 0x1E;
                if (mnCharSel_804D6CF6 != 3 && mnCharSel_804D6CF6 != 4) {
                    lbAudioAx_800237A8(0xBA, 0x7F, 0x40);
                }
            } else {
                HSD_ForeachAnim(sp90, JOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
            }
        }

        /* Switch on p_kind for handicap/CPU */
        if (mnCharSel_803F0DFC.doors[arg0].p_kind !=
            mnCharSel_803F0DFC.doors[arg0].p_kind_prev)
        {
            joint = mnCharSel_803F0DFC.doors[arg0].slidername_joint;
            lb_80011E24(mnCharSel_804D6CC0, &sp90, joint, -1);
            switch ((int) mnCharSel_803F0DFC.doors[arg0].p_kind) {
            case 2:
                break;
            case 0:
                if (gmMainLib_GetGameRules()->handicap != 0) {
                    if (gmMainLib_GetGameRules()->handicap == 2) {
                        door_frame = 0.0f;
                    } else {
                        door_frame = 60.0f;
                    }
                    {
                        HSD_JObj* anim_jobj = sp90;
                        HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                        HSD_AObjReqAnim, AOBJ_ARG_AF,
                                        door_frame);
                    }

                    anim_frame =
                        (f32) mnCharSel_804D6CB0->data.data.players[arg0]
                            .cpu_level;
                    joint = mnCharSel_803F0DFC.doors[arg0].cpuslider_joint;
                    animateJointPadded(mnCharSel_804D6CC0, joint, TOBJ_MASK,
                                       anim_frame);
                }
                break;
            case 1: {
                if (gmMainLib_GetGameRules()->handicap != 0) {
                    if (gmMainLib_GetGameRules()->handicap == 2) {
                        door_frame = 20.0f;
                    } else {
                        door_frame = 80.0f;
                    }
                    {
                        HSD_JObj* anim_jobj = sp90;
                        HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                        HSD_AObjReqAnim, AOBJ_ARG_AF,
                                        door_frame);
                    }
                    {
                        s32 hval;
                        s32 port = (int) arg0;
                        if (gmMainLib_GetGameRules()->handicap == 1) {
                            hval = (u8) gm_801685D4(
                                port,
                                mnCharSel_804D6CB0->data.data.players[port]
                                    .xA);
                        } else {
                            hval = (u8) mnCharSel_804D6CB0->data.data
                                       .players[port]
                                       .handicap;
                        }
                        anim_frame = (f32) (hval != 0 ? hval : 1);
                    }
                    joint = mnCharSel_803F0DFC.doors[arg0].cpuslider_joint;
                    sp90 = animateJoint(mnCharSel_804D6CC0, joint, TOBJ_MASK,
                                        anim_frame);
                    anim_frame =
                        1.25f * (f32) (getHandicapValue((int) arg0) - 1);
                    HSD_JObjSetTranslateX(sp90, anim_frame);

                    anim_frame =
                        (f32) mnCharSel_804D6CB0->data.data.players[arg0]
                            .cpu_level;
                    joint = mnCharSel_803F0DFC.doors[arg0].cpuslider2_joint;
                    animateJoint(mnCharSel_804D6CC0, joint, TOBJ_MASK,
                                 anim_frame);
                } else {
                    {
                        HSD_JObj* anim_jobj = sp90;
                        HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                        HSD_AObjReqAnim, AOBJ_ARG_AF, 40.0f);
                    }

                    anim_frame =
                        (f32) mnCharSel_804D6CB0->data.data.players[arg0]
                            .cpu_level;
                    joint = mnCharSel_803F0DFC.doors[arg0].cpuslider_joint;
                    animateJoint(mnCharSel_804D6CC0, joint, TOBJ_MASK,
                                 anim_frame);
                }
                break;
            }
            case 3: {
                if (gmMainLib_GetGameRules()->handicap != 0) {
                    if (mnCharSel_803F0DFC.doors[arg0].p_kind !=
                        mnCharSel_803F0DFC.doors[arg0].p_kind_prev)
                    {
                        if (gmMainLib_GetGameRules()->handicap == 2) {
                            door_frame = 30.0f;
                        } else {
                            door_frame = 90.0f;
                        }
                        {
                            HSD_JObj* anim_jobj = sp90;
                            HSD_ForeachAnim(anim_jobj, JOBJ_TYPE,
                                            ALL_TYPE_MASK, HSD_AObjReqAnim,
                                            AOBJ_ARG_AF, door_frame);
                        }
                    }
                    {
                        s32 hval;
                        s32 port = (int) arg0;
                        if (gmMainLib_GetGameRules()->handicap == 1) {
                            hval = (u8) gm_801685D4(
                                port,
                                mnCharSel_804D6CB0->data.data.players[port]
                                    .xA);
                        } else {
                            hval = (u8) mnCharSel_804D6CB0->data.data
                                       .players[port]
                                       .handicap;
                        }
                        anim_frame = (f32) (hval != 0 ? hval : 1);
                    }
                    joint = mnCharSel_803F0DFC.doors[arg0].cpuslider_joint;
                    sp90 = animateJoint(mnCharSel_804D6CC0, joint, TOBJ_MASK,
                                        anim_frame);
                    anim_frame =
                        1.25f * (f32) (getHandicapValue((int) arg0) - 1);
                    HSD_JObjSetTranslateX(sp90, anim_frame);

                    anim_frame =
                        (f32) mnCharSel_804D6CB0->data.data.players[arg0]
                            .cpu_level;
                    joint = mnCharSel_803F0DFC.doors[arg0].cpuslider2_joint;
                    animateJoint(mnCharSel_804D6CC0, joint, TOBJ_MASK,
                                 anim_frame);
                } else {
                    if (mnCharSel_803F0DFC.doors[arg0].p_kind !=
                        mnCharSel_803F0DFC.doors[arg0].p_kind_prev)
                    {
                        {
                            HSD_JObj* anim_jobj = sp90;
                            HSD_ForeachAnim(anim_jobj, JOBJ_TYPE,
                                            ALL_TYPE_MASK, HSD_AObjReqAnim,
                                            AOBJ_ARG_AF, 50.0f);
                        }
                    }

                    anim_frame =
                        (f32) mnCharSel_804D6CB0->data.data.players[arg0]
                            .cpu_level;
                    joint = mnCharSel_803F0DFC.doors[arg0].cpuslider_joint;
                    animateJoint(mnCharSel_804D6CC0, joint, TOBJ_MASK,
                                 anim_frame);
                }
                break;
            }
            }
            mnCharSel_803F0DFC.doors[arg0].slideranim_timer = 0xA;
        }

        /* Update p_kind_prev */
        mnCharSel_803F0DFC.doors[arg0].p_kind_prev =
            mnCharSel_803F0DFC.doors[arg0].p_kind;

        /* Player indicator / status icon */

        anim_frame =
            (f32) mnCharSel_804D50CC[mnCharSel_803F0DFC.doors[arg0].p_kind];
        joint = mnCharSel_803F0DFC.doors[arg0].player_indicator_joint;
        animateJoint(mnCharSel_804D6CC0, joint, ALL_TYPE_MASK, anim_frame);

        /* Team / color */
        lb_80011E24(mnCharSel_804D6CC0, &sp90,
                    mnCharSel_803F0DFC.doors[arg0].team_joint, -1);
        if (mnCharSel_804D6CB0->data.data.rules.is_teams == 0) {
            /* FFA mode */
            s32 port_color_idx;
            HSD_JObjSetFlags(sp90, JOBJ_HIDDEN);
            port_color_idx = (int) arg0;
            if (mnCharSel_803F0DFC.doors[arg0].p_kind != 0) {
                port_color_idx += 4;
            }

            anim_frame = (f32) mnCharSel_804D50D8[port_color_idx];
            joint = mnCharSel_803F0DFC.doors[arg0].bg_joint;
            animateJoint(mnCharSel_804D6CC0, joint, TOBJ_MASK, anim_frame);

            anim_frame = (f32) mnCharSel_804D50D8[port_color_idx];
            joint = mnCharSel_803F0DFC.doors[arg0].emblem_joint;
            animateJoint(mnCharSel_804D6CC0, joint, MOBJ_MASK, anim_frame);
        } else {
            /* Teams mode */
            HSD_JObjClearFlags(sp90, JOBJ_HIDDEN);
            team.v = mnCharSel_803F0DFC.doors[arg0].team;

            anim_frame = (f32) mnCharSel_804D50D0[team.v];
            joint = mnCharSel_803F0DFC.doors[arg0].team_joint;
            animateJoint(mnCharSel_804D6CC0, joint, TOBJ_MASK, anim_frame);
            if (mnCharSel_803F0DFC.doors[arg0].p_kind != 0) {
                team.v += 4;
            }
            {
                anim_frame = (f32) mnCharSel_804D50D0[team.v];
                joint = mnCharSel_803F0DFC.doors[arg0].bg_joint;
                animateJoint(mnCharSel_804D6CC0, joint, TOBJ_MASK, anim_frame);

                anim_frame = (f32) mnCharSel_804D50D0[team.v];
                joint = mnCharSel_803F0DFC.doors[arg0].emblem_joint;
                animateJointLeadingPad(mnCharSel_804D6CC0, joint, MOBJ_MASK,
                                       anim_frame);
            }
            mnCharSel_804D6CB0->data.data.players[arg0].team =
                mnCharSel_803F0DFC.doors[arg0].team;
        }

        /* Hide/show nametag text */
        if (mnCharSel_803F0DFC.doors[arg0].p_kind == 3 ||
            (mnCharSel_803F0E8C[arg0].data->use_tag == 0 &&
             mnCharSel_803F0DFC.doors[arg0].sel_icon >= 0x19U))
        {
            mnCharSel_803F0E8C[arg0].data->text->hidden = 1;
        } else {
            mnCharSel_803F0E8C[arg0].data->text->hidden = 0;
        }
    }

    /* Final: costume color assignment */
    {
        u8 final_icon = mnCharSel_803F0DFC.doors[arg0].sel_icon;
        if (final_icon < 0x19U) {
            if (mnCharSel_804D6CF5 == 1 ||
                mnCharSel_804D6CB0->data.data.rules.is_teams == 0)
            {
                color = mnCharSel_803F0DFC.doors[arg0].costume;
            } else {
                u8 ckind = icons[final_icon].char_kind;
                switch ((int) mnCharSel_803F0DFC.doors[arg0].team) {
                default:
                    color = gm_80169264(ckind);
                    break;
                case 1:
                    color = gm_801692BC(ckind);
                    break;
                case 2:
                    color = gm_80169290(ckind);
                    break;
                }
            }
            {
                int port;
                if (mnCharSel_804D6CF5 == 1) {
                    if ((int) arg0 != 0) {
                        port = mnCharSel_804D6CF1;
                    } else {
                        port = mnCharSel_804D6CF0;
                    }
                } else {
                    port = arg0;
                }
                mnCharSel_804D6CB0->data.data.players[port].color = color;
            }
            hud_idx += color * 0x1E;
            mnCharSel_8025D5AC((int) arg0, hud_idx, 0);
        }
    }
}

void mnCharSel_8025EE8C(u8 idx)
{
    float mode_frame;
    int i;
    HSD_JObj* cc0;

    u8 _[8];

    HSD_JObj* sp14;
    HSD_JObj* sp10;
    HSD_JObj* spC;

    if (mnCharSel_804D6CF5 == 1) {
        mode_frame = mnCharSel_803F0A48.mode_info[idx].mode_ffa_frame;
        cc0 = mnCharSel_804D6CC0;
        lb_80011E24(cc0, &sp14, 0x24, -1);
        cc0 = sp14;
        HSD_ForeachAnim(cc0, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, mode_frame);

        HSD_JObjAnimAll(sp14);
        HSD_ForeachAnim(sp14, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                        AOBJ_ARG_AOV, 0, 0);
        mnCharSel_8025DB34(0);
        if (mnCharSel_804D6CB0->match_type == TRAINING_MODE) {
            mnCharSel_8025DB34(1);
        }
    } else {
        if (mnCharSel_804D6CB0->data.data.rules.is_teams) {
            mode_frame = mnCharSel_803F0A48.mode_info[idx].mode_teams_frame;
            cc0 = mnCharSel_804D6CC0;
            lb_80011E24(cc0, &sp10, 0x24, -1);
            cc0 = sp10;
            HSD_ForeachAnim(cc0, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                            AOBJ_ARG_AF, mode_frame);
            HSD_JObjAnimAll(sp10);
            HSD_ForeachAnim(sp10, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        } else {
            mode_frame = mnCharSel_803F0A48.mode_info[idx].mode_ffa_frame;
            cc0 = mnCharSel_804D6CC0;
            lb_80011E24(cc0, &spC, 0x24, -1);
            cc0 = spC;
            HSD_ForeachAnim(cc0, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                            AOBJ_ARG_AF, mode_frame);
            HSD_JObjAnimAll(spC);
            HSD_ForeachAnim(spC, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        }
        for (i = 0; i < mnCharSel_804D6CF5; i++) {
            mnCharSel_8025DB34(i);
        }
    }

    (void) 7.5f;
}

static struct CSSCursorData* mnCharSel_804A0BC0[4];
static struct CSSCharModel {
    /* 0x00 */ HSD_GObj* gobj;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
    /* 0x07 */ u8 x7;
    /* 0x08 */ float x8;
    /* 0x0C */ float xC;
    /* 0x10 */ float x10;
    /* 0x14 */ float x14;
}* mnCharSel_804A0BD0[4];

static inline void updateStockIcons(struct CSSDoorsData2* stock_data,
                                    HSD_JObj** stock_jobj, s32 i)
{
    lb_80011E24(mnCharSel_804D6CC0, stock_jobj, stock_data->xf0[0], -1);
    HSD_JObjSetTranslateX(*stock_jobj, 7.5f);
    for (i = 1; i < 5; i++) {
        lb_80011E24(mnCharSel_804D6CC0, stock_jobj, stock_data->xf0[i], -1);
        if (stock_data->stocks <= i) {
            HSD_JObjSetFlags(*stock_jobj, JOBJ_HIDDEN);
        } else {
            HSD_JObjClearFlags(*stock_jobj, JOBJ_HIDDEN);
        }
    }
}

void fn_8025F0E0(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* sp54;
    UNUSED int hole;
    HSD_JObj* sp4C;
    HSD_JObj* sp48;
    HSD_JObj* sp44;
    HSD_JObj* sp40;
    HSD_JObj* sp3C;
    HSD_JObj* sp38;
    HSD_JObj* sp34;
    HSD_JObj* sp30;
    HSD_JObj* sp2C;
    CSSDoor* doors;
    GameRules* rules;
    HSD_DObj* dobj;
    HSD_MObj* mobj;
    int i;
    u8 timer;
    s32 val;
    int anim;
    float fval;

    if ((mnCharSel_804D6CEC % 10) != 0) {
        if (mnCharSel_804D6CF5 == 1) {
            lb_80011E24(jobj, &sp54, 0x27, -1);
        } else {
            lb_80011E24(jobj, &sp54, 0x27, -1);
        }
        HSD_ForeachAnim(sp54, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, 0.0f);
    }

    for (i = 0; i < 25; i++) {
        timer = icons[i].anim_timer;
        if (timer != 0) {
            timer = timer - 1;
            icons[i].anim_timer = timer;
            if (timer == 0) {
                if (mnCharSel_804D6CF5 == 1) {
                    lb_80011E24(jobj, &sp4C, icons[i].joint_id_1p, -1);
                    HSD_ForeachAnim(sp4C, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjReqAnim, AOBJ_ARG_AF, 0.0f);
                    HSD_JObjAnimAll(sp4C);
                    HSD_ForeachAnim(sp4C, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                } else {
                    lb_80011E24(jobj, &sp48, icons[i].joint_id_vs, -1);
                    HSD_ForeachAnim(sp48, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjReqAnim, AOBJ_ARG_AF, 0.0f);
                    HSD_JObjAnimAll(sp48);
                    HSD_ForeachAnim(sp48, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                }
            }
        }
    }

    if (mnCharSel_804D6CF5 == 4) {
        doors = mnCharSel_803F0DFC.doors;
        i = 0;
        while (i < (s32) mnCharSel_804D6CF5) {
            timer = doors->dooranim_timer;
            if (timer != 0) {
                timer = timer - 1;
                doors->dooranim_timer = timer;
                if (timer == 0) {
                    lb_80011E24(jobj, &sp54, doors->door_joint, -1);
                    HSD_ForeachAnim(sp54, JOBJ_TYPE, ALL_TYPE_MASK,
                                    HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                }
            }

            timer = doors->slideranim_timer;
            if (timer != 0) {
                timer = timer - 1;
                doors->slideranim_timer = timer;
                if (timer == 0) {
                    rules = gmMainLib_GetGameRules();
                    if (rules->handicap != 0) {
                        if (doors->p_kind == 1) {
                            rules = gmMainLib_GetGameRules();
                            if (rules->handicap == 1) {
                                anim = 0x5A;
                            } else {
                                anim = 0x1E;
                            }
                            {
                                u8 slidername_joint = doors->slidername_joint;
                                fval = (f32) anim;
                                lb_80011E24(mnCharSel_804D6CC0, &sp44,
                                            slidername_joint, -1);
                            }
                            {
                                HSD_JObj* anim_jobj = sp44;
                                HSD_ForeachAnim(anim_jobj, JOBJ_TYPE,
                                                ALL_TYPE_MASK, HSD_AObjReqAnim,
                                                AOBJ_ARG_AF, fval);
                            }
                            HSD_JObjAnimAll(sp44);
                            HSD_ForeachAnim(sp44, JOBJ_TYPE, ALL_TYPE_MASK,
                                            HSD_AObjStopAnim, AOBJ_ARG_AOV, 0,
                                            0);
                        } else {
                            rules = gmMainLib_GetGameRules();
                            if (rules->handicap == 1) {
                                anim = 0x50;
                            } else {
                                anim = 0x14;
                            }
                            {
                                u8 slidername_joint = doors->slidername_joint;
                                fval = (f32) anim;
                                lb_80011E24(mnCharSel_804D6CC0, &sp40,
                                            slidername_joint, -1);
                            }
                            {
                                HSD_JObj* anim_jobj = sp40;
                                HSD_ForeachAnim(anim_jobj, JOBJ_TYPE,
                                                ALL_TYPE_MASK, HSD_AObjReqAnim,
                                                AOBJ_ARG_AF, fval);
                            }
                            HSD_JObjAnimAll(sp40);
                            HSD_ForeachAnim(sp40, JOBJ_TYPE, ALL_TYPE_MASK,
                                            HSD_AObjStopAnim, AOBJ_ARG_AOV, 0,
                                            0);
                        }

                        rules = gmMainLib_GetGameRules();
                        if (rules->handicap == 1) {
                            val = (u8) gm_801685D4(
                                (u8) i,
                                mnCharSel_804D6CB0->data.data.players[i].xA);
                        } else {
                            val = (u8) mnCharSel_804D6CB0->data.data.players[i]
                                      .handicap;
                        }
                        /* switch forces MWCC beq/b double-branch (not bne) */
                        switch (val) {
                        case 0:
                            val = 1;
                        }
                        {
                            u8 cpuslider_joint = doors->cpuslider_joint;
                            fval = (f32) val;
                            lb_80011E24(mnCharSel_804D6CC0, &sp3C,
                                        cpuslider_joint, -1);
                        }
                        {
                            HSD_JObj* anim_jobj = sp3C;
                            HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, TOBJ_MASK,
                                            HSD_AObjReqAnim, AOBJ_ARG_AF,
                                            fval);
                        }
                        HSD_JObjAnimAll(sp3C);
                        HSD_ForeachAnim(sp3C, JOBJ_TYPE, TOBJ_MASK,
                                        HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);

                        {
                            u8 cpuslider2_joint = doors->cpuslider2_joint;
                            fval =
                                (f32) mnCharSel_804D6CB0->data.data.players[i]
                                    .cpu_level;
                            lb_80011E24(mnCharSel_804D6CC0, &sp38,
                                        cpuslider2_joint, -1);
                        }
                        {
                            HSD_JObj* anim_jobj = sp38;
                            HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, TOBJ_MASK,
                                            HSD_AObjReqAnim, AOBJ_ARG_AF,
                                            fval);
                        }
                        HSD_JObjAnimAll(sp38);
                        HSD_ForeachAnim(sp38, JOBJ_TYPE, TOBJ_MASK,
                                        HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                    } else {
                        if (doors->p_kind == 1) {
                            u8 slidername_joint = doors->slidername_joint;
                            lb_80011E24(mnCharSel_804D6CC0, &sp34,
                                        slidername_joint, -1);
                            HSD_ForeachAnim(sp34, JOBJ_TYPE, ALL_TYPE_MASK,
                                            HSD_AObjReqAnim, AOBJ_ARG_AF,
                                            50.0f);
                            HSD_JObjAnimAll(sp34);
                            HSD_ForeachAnim(sp34, JOBJ_TYPE, ALL_TYPE_MASK,
                                            HSD_AObjStopAnim, AOBJ_ARG_AOV, 0,
                                            0);
                        } else {
                            u8 slidername_joint = doors->slidername_joint;
                            lb_80011E24(mnCharSel_804D6CC0, &sp30,
                                        slidername_joint, -1);
                            HSD_ForeachAnim(sp30, JOBJ_TYPE, ALL_TYPE_MASK,
                                            HSD_AObjReqAnim, AOBJ_ARG_AF,
                                            40.0f);
                            HSD_JObjAnimAll(sp30);
                            HSD_ForeachAnim(sp30, JOBJ_TYPE, ALL_TYPE_MASK,
                                            HSD_AObjStopAnim, AOBJ_ARG_AOV, 0,
                                            0);
                        }
                        {
                            u8 cpuslider_joint = doors->cpuslider_joint;
                            fval =
                                (f32) mnCharSel_804D6CB0->data.data.players[i]
                                    .cpu_level;
                            lb_80011E24(mnCharSel_804D6CC0, &sp2C,
                                        cpuslider_joint, -1);
                        }
                        {
                            HSD_JObj* anim_jobj = sp2C;
                            HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, TOBJ_MASK,
                                            HSD_AObjReqAnim, AOBJ_ARG_AF,
                                            fval);
                        }
                        HSD_JObjAnimAll(sp2C);
                        HSD_ForeachAnim(sp2C, JOBJ_TYPE, TOBJ_MASK,
                                        HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                    }
                }
            }

            doors++;
            i += 1;
        }
    } else {
        if (mnCharSel_803F0EBC.scroll_flag != 0) {
            if (mnCharSel_803F0EBC.cpu_level !=
                mnCharSel_803F0EBC.cpu_level_shown)
            {
                if (mnCharSel_803F0EBC.cpu_level <
                    mnCharSel_803F0EBC.cpu_level_shown)
                {
                    mnCharSel_803F0EBC.cpu_slider_x += 31.0f;
                    if (mnCharSel_803F0EBC.cpu_slider_x >=
                        124.0f - 248.0f * (f32) mnCharSel_803F0EBC.cpu_level)
                    {
                        mnCharSel_803F0EBC.cpu_level_shown =
                            mnCharSel_803F0EBC.cpu_level;
                    }
                } else {
                    mnCharSel_803F0EBC.cpu_slider_x =
                        mnCharSel_803F0EBC.cpu_slider_x - 31.0f;
                    if (mnCharSel_803F0EBC.cpu_slider_x <=
                        124.0f - 248.0f * (f32) mnCharSel_803F0EBC.cpu_level)
                    {
                        mnCharSel_803F0EBC.cpu_level_shown =
                            mnCharSel_803F0EBC.cpu_level;
                    }
                }
            }
            if (mnCharSel_803F0EBC.cpu_level ==
                mnCharSel_803F0EBC.cpu_level_shown)
            {
                mnCharSel_803F0EBC.scroll_flag = 0;
                mnCharSel_803F0EBC.cpu_slider_x =
                    124.0f - 248.0f * (f32) mnCharSel_803F0EBC.cpu_level;
            }
            {
                int j;
                for (j = 0; j < 5; j++) {
                    HSD_SisLib_803A746C(mnCharSel_803F0EBC.xd3, j,
                                        248.0f * (f32) j +
                                            mnCharSel_803F0EBC.cpu_slider_x,
                                        0.0f);
                }
            }
        }
    }

    if (mnCharSel_804D6CF5 == 1) {
        lb_80011E24(mnCharSel_804D6CC0, &sp54, 0x2D, -1);
        if (mnCharSel_804A0BD0[0]->x5 != 0) {
            dobj = HSD_JObjGetDObj(sp54);
            if (dobj != NULL) {
                mobj = dobj->mobj;
            } else {
                mobj = NULL;
            }
            HSD_MObjSetAlpha(mobj, 0.5f);
        } else {
            dobj = HSD_JObjGetDObj(sp54);
            if (dobj != NULL) {
                mobj = dobj->mobj;
            } else {
                mobj = NULL;
            }
            HSD_MObjSetAlpha(mobj, 1.0f);
        }
        if (mnCharSel_804D6CB0->match_type == 0x17) {
            lb_80011E24(mnCharSel_804D6CC4, &sp54, 6, -1);
            if (mnCharSel_804A0BD0[1]->x5 != 0) {
                dobj = HSD_JObjGetDObj(sp54);
                if (dobj != NULL) {
                    mobj = dobj->mobj;
                } else {
                    mobj = NULL;
                }
                HSD_MObjSetAlpha(mobj, 0.5f);
            } else {
                dobj = HSD_JObjGetDObj(sp54);
                if (dobj != NULL) {
                    mobj = dobj->mobj;
                } else {
                    mobj = NULL;
                }
                HSD_MObjSetAlpha(mobj, 1.0f);
            }
        }
    } else {
        for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
            lb_80011E24(mnCharSel_804D6CC0, &sp54,
                        mnCharSel_803F0DFC.doors[i].costume_joint, -1);
            if (mnCharSel_804A0BD0[i]->x5 != 0) {
                dobj = HSD_JObjGetDObj(sp54);
                if (dobj != NULL) {
                    mobj = dobj->mobj;
                } else {
                    mobj = NULL;
                }
                HSD_MObjSetAlpha(mobj, 0.5f);
            } else {
                dobj = HSD_JObjGetDObj(sp54);
                if (dobj != NULL) {
                    mobj = dobj->mobj;
                } else {
                    mobj = NULL;
                }
                HSD_MObjSetAlpha(mobj, 1.0f);
            }
        }
    }
    HSD_JObjAnimAll(jobj);
    PAD_STACK(28);
}

void fn_8025FAC0(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (mnCharSel_804D6CEC % 40 == 0) {
        if (jobj == NULL) {
            child = NULL;
        } else {
            child = jobj->child;
        }
        HSD_JObjReqAnimAll(child, 0.0F);
    }
    HSD_JObjAnimAll(jobj);
}

void fn_8025FB2C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static inline s32 getIconOffset(u32 icon_idx)
{
    return icon_idx * sizeof(CSSIcon);
}

static inline s32 getPlayerForDoor(u8 door)
{
    if (mnCharSel_804D6CF5 == 1) {
        if (door != 0) {
            return mnCharSel_804D6CF1;
        }
        return mnCharSel_804D6CF0;
    }
    return door;
}

void mnCharSel_8025FB50(u8 door, s32 arg1)
{
    s32 icon_idx;
    s32 icon_offset;
    CSSAllData* all_data = (CSSAllData*) &mnCharSel_803F0A48;
    HSD_JObj* icon_jobj;

    do {
        s32 temp = HSD_Randi(0x19);
        icon_idx = temp;
        icon_offset = getIconOffset(icon_idx);
    } while (icons[icon_idx].state == 0);

    mnCharSel_804D6CB0->data.data.players[getPlayerForDoor(door)].c_kind =
        (&icons[0].char_kind)[icon_offset];

    mnCharSel_803F0DFC.doors[door].sel_icon = (u8) icon_idx;
    if (mnCharSel_803F0DFC.doors[door].sel_icon !=
        mnCharSel_803F0DFC.doors[door].sel_icon_prev)
    {
        u8 costume;
        for (costume = 0;; costume++) {
            mnCharSel_803F0DFC.doors[door].costume = costume;
            if (!isDuplicateCostumeExact(door)) {
                break;
            }
        }
    }

    mnCharSel_804A0BD0[door]->x5 = 0;
    mnCharSel_804A0BD0[door]->x8 = 3.4f + all_data->icons[icon_idx].bound_l;
    mnCharSel_804A0BD0[door]->xC = -3.0f + all_data->icons[icon_idx].bound_u;
    if (arg1 != 0) {
        mnCharSel_804A0BD0[door]->x10 = mnCharSel_804A0BD0[door]->x8;
        mnCharSel_804A0BD0[door]->x14 = mnCharSel_804A0BD0[door]->xC;
    }
    HSD_GObjGXLink_803909D8(mnCharSel_804A0BD0[door]->gobj,
                            mnCharSel_804A0BC0[mnCharSel_804D6CF5 - 1]->gobj);

    if (mnCharSel_804D6CF5 == 1) {
        lb_80011E24(mnCharSel_804D6CC0, &icon_jobj,
                    all_data->icons[icon_idx].joint_id_1p, -1);
    } else {
        lb_80011E24(mnCharSel_804D6CC0, &icon_jobj,
                    all_data->icons[icon_idx].joint_id_vs, -1);
    }
    HSD_ForeachAnim(icon_jobj, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                    AOBJ_ARG_AF, 10.0);

    all_data->icons[icon_idx].anim_timer = 0xC;

    {
        u8 sel = mnCharSel_803F0DFC.doors[door].sel_icon;
        u8* char_kinds = &icons[0].char_kind;
        lbAudioAx_80023870(all_data->icons[sel].sfx, 0x7F, 0x40, sel + 0x8A);
        gm_80168C5C((u32) char_kinds[sel * sizeof(CSSIcon)]);
    }
}

#ifdef MUST_MATCH
#pragma auto_inline off
#endif
s32 mnCharSel_8025FDEC(u8 door)
{
    CSSData* css;
    HSD_JObj* sp10;
    int player;
    s8 c_kind;
    int icon_idx;
    CSSAllData* all_data = (CSSAllData*) &mnCharSel_803F0A48;

    if (mnCharSel_804D6CF5 == 1) {
        if (door != 0) {
            player = mnCharSel_804D6CF1;
        } else {
            player = mnCharSel_804D6CF0;
        }
    } else {
        player = door;
    }

    css = mnCharSel_804D6CB0;
    c_kind = css->data.data.players[player].c_kind;

    if (c_kind < CKIND_PLAYABLE_COUNT) {
        if (c_kind !=
            all_data->icons[mnCharSel_803F0DFC.doors[door].sel_icon].char_kind)
        {
            mnCharSel_803F0DFC.doors[door].costume = 0;
        }

        {
            CSSIcon* icon = all_data->icons;
            for (icon_idx = 0; icon_idx < 0x19; icon_idx++) {
                if (css->data.data.players[player].c_kind ==
                    icon[icon_idx].char_kind)
                {
                    break;
                }
            }
        }

        mnCharSel_804A0BD0[door]->x8 =
            3.4f + all_data->icons[icon_idx].bound_l;
        mnCharSel_804A0BD0[door]->xC =
            -3.0f + all_data->icons[icon_idx].bound_u;

        mnCharSel_803F0DFC.doors[door].sel_icon_prev = icon_idx;
        mnCharSel_803F0DFC.doors[door].sel_icon = icon_idx;

        HSD_GObjGXLink_803909D8(
            mnCharSel_804A0BD0[door]->gobj,
            mnCharSel_804A0BC0[mnCharSel_804D6CF5 - 1]->gobj);

        mnCharSel_804A0BD0[door]->x5 = 0;

        if (mnCharSel_804D6CF5 == 1) {
            lb_80011E24(mnCharSel_804D6CC0, &sp10,
                        all_data->icons[icon_idx].joint_id_1p, -1);
        } else {
            lb_80011E24(mnCharSel_804D6CC0, &sp10,
                        all_data->icons[icon_idx].joint_id_vs, -1);
        }
        HSD_ForeachAnim(sp10, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, 10.0);

        all_data->icons[icon_idx].anim_timer = 0xC;

        {
            int door_idx = door;
            if (mnCharSel_8025DAA0(door_idx)) {
                s8 costume;
                CSSDoor* selected_door = &mnCharSel_803F0DFC.doors[door_idx];
                for (costume = 0;; costume++) {
                    selected_door->costume = costume;
                    if (!mnCharSel_8025DAA0(door_idx)) {
                        break;
                    }
                }
            }
        }

        if (mnCharSel_804D6CF6 != 3 && mnCharSel_804D6CF6 != 4) {
            u8 sel = mnCharSel_803F0DFC.doors[door].sel_icon;
            lbAudioAx_80023870(all_data->icons[sel].sfx, 0x7F, 0x40,
                               sel + 0x8A);
            gm_80168C5C((u32) all_data->icons[sel].char_kind);
        }
        return 0;
    }
    return 1;
}
#ifdef MUST_MATCH
#pragma auto_inline on
#endif
void mnCharSel_CostumeChange(int door, u32 input)
{
    u8 prev_costume = mnCharSel_803F0DFC.doors[door].costume;

    if (mnCharSel_803F0DFC.doors[door].sel_icon >= 0x19) {
        return;
    }
    if (mnCharSel_803F0DFC.doors[door].sel_icon_prev >= 0x19) {
        return;
    }

    if (input & HSD_PAD_X) {
        do {
            mnCharSel_803F0DFC.doors[door].costume =
                (mnCharSel_803F0DFC.doors[door].costume + 1) %
                gm_80169238(
                    icons[mnCharSel_803F0DFC.doors[door].sel_icon].char_kind);
        } while (isDuplicateCostume(door));
    } else if (input & HSD_PAD_Y) {
        do {
            if (mnCharSel_803F0DFC.doors[door].costume != 0) {
                mnCharSel_803F0DFC.doors[door].costume--;
            } else {
                mnCharSel_803F0DFC.doors[door].costume =
                    gm_80169238(icons[mnCharSel_803F0DFC.doors[door].sel_icon]
                                    .char_kind) -
                    1;
            }
        } while (isDuplicateCostume(door));
    }
    if (prev_costume != mnCharSel_803F0DFC.doors[door].costume) {
        mnCharSel_8025DB34(door);
        sfxMove();
    }
}

static inline void updateCursorDisplay(HSD_JObj* jobj,
                                       struct CSSCursorData* cursor,
                                       HSD_JObj** state_jobj,
                                       HSD_JObj** color_jobj)
{
    CSSAllData* all_data = CSS_ALL;

    if (cursor->x5 != 1) {
        f32 y = cursor->x10;
        if (y < 0.2f || y > 22.0f) {
            cursor->x5 = 0;
        } else {
            cursor->x5 = 2;
        }
    }

    {
        f32 state = (f32) cursor->x5;
        HSD_JObj* cc0;
        lb_80011E24(jobj, state_jobj, 2, -1);
        cc0 = *state_jobj;
        HSD_ForeachAnim(cc0, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, state);
        HSD_JObjAnimAll(*state_jobj);
        HSD_ForeachAnim(*state_jobj, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                        AOBJ_ARG_AOV, 0, 0);
    }

    {
        s32 color_idx;
        if (mnCharSel_804D6CF5 == 1) {
            color_idx = mnCharSel_804D6CF0;
        } else if (mnCharSel_804D6CB0->data.data.rules.is_teams == 0) {
            color_idx = cursor->x4;
        } else {
            color_idx =
                mnCharSel_804D50E0[all_data->doors_data.doors[cursor->x4]
                                       .team];
        }

        {
            if (cursor->x8 != 0) {
                s32 port = cursor->x4;
                if (mnCharSel_804D6CF5 == 1) {
                    if (port != 0) {
                        port = mnCharSel_804D6CF1;
                    } else {
                        port = mnCharSel_804D6CF0;
                    }
                }
                color_idx = (mnCharSel_804D6CEC & 3) + (port * 4);
            } else {
                s32 port = cursor->x4;
                if (mnCharSel_804D6CF5 == 1) {
                    if (port != 0) {
                        port = mnCharSel_804D6CF1;
                    } else {
                        port = mnCharSel_804D6CF0;
                    }
                }
                color_idx = color_idx + (port * 4);
            }

            lb_80011E24(jobj, color_jobj, 3, -1);
            {
                HSD_JObj* anim_jobj = *color_jobj;
                HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, TOBJ_MASK,
                                HSD_AObjReqAnim, AOBJ_ARG_AF, (f32) color_idx);
            }
            HSD_JObjAnimAll(*color_jobj);
            HSD_ForeachAnim(*color_jobj, JOBJ_TYPE, TOBJ_MASK,
                            HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
        }
    }

    HSD_JObjSetTranslateX(jobj, cursor->xC);
    HSD_JObjSetTranslateY(jobj, cursor->x10);
    HSD_JObjSetTranslateZ(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
}

static inline void updateGrabbedSlider(struct CSSCursorData* cursor,
                                       CSSDoor* door, s32 door_idx,
                                       u32 trigger, HSD_JObj** slider_jobj,
                                       Point3d* pos, bool is_handicap)
{
    f32 base_x;
    f32 anim_frame;

    if (is_handicap) {
        lb_80011E24(mnCharSel_804D6CC0, slider_jobj, door->cpuslider_joint,
                    -1);
    } else {
        GameRules* rules = gmMainLib_GetGameRules();
        if (rules->handicap != 0) {
            lb_80011E24(mnCharSel_804D6CC0, slider_jobj,
                        door->cpuslider2_joint, -1);
        } else {
            lb_80011E24(mnCharSel_804D6CC0, slider_jobj, door->cpuslider_joint,
                        -1);
        }
    }
    lb_8000B1CC(*slider_jobj, NULL, pos);

    base_x = HSD_JObjGetTranslationX(*slider_jobj) - pos->x;
    pos->x = (cursor->xC - -2.9f) + base_x;
    if (pos->x < 0.0f) {
        pos->x = 0.0f;
    }
    if (pos->x > 10.0f) {
        pos->x = 10.0f;
    }

    if (is_handicap) {
        mnCharSel_804D6CB0->data.data.players[door_idx].handicap =
            (s32) ((0.8f * pos->x) + 0.5f) + 1;
        anim_frame =
            (u8) mnCharSel_804D6CB0->data.data.players[door_idx].handicap;
    } else {
        mnCharSel_804D6CB0->data.data.players[door_idx].cpu_level =
            (s32) ((0.8f * pos->x) + 0.5f) + 1;
        anim_frame = mnCharSel_804D6CB0->data.data.players[door_idx].cpu_level;
    }

    {
        HSD_JObj* anim_jobj = *slider_jobj;
        HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, anim_frame);
    }
    HSD_JObjAnimAll(*slider_jobj);
    HSD_ForeachAnim(*slider_jobj, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                    AOBJ_ARG_AOV, 0, 0);
    HSD_JObjSetTranslateX(*slider_jobj, pos->x);
    cursor->xC = (f32) (-2.9f + (pos->x - base_x));
    cursor->x10 = (f32) (1.7f + pos->y);

    if (trigger & HSD_PAD_A) {
        cursor->x5 = 2;
        if (is_handicap) {
            door->is_hold_handicap_slider = 0;
        } else {
            door->is_hold_cpu_slider = 0;
        }
        lbAudioAx_800237A8(0xB7, 0x7F, 0x40);
    }
}

/// Advances the door's team colour when the cursor clicks its team box.
static inline void cycleTeam(struct CSSCursorData* cursor, CSSDoor* dp, s32 di)
{
    f32 cx5 = cursor->xC;
    if (cx5 > dp->teambtn_left && cx5 < dp->teambtn_right) {
        f32 cy5 = cursor->x10;
        if (cy5 < -0.9999999046325683 && cy5 > -5.800000095367432) {
            cursor->x10 = -3.4f;
            dp->team = (u8) ((dp->team + 1) % 3);
            mnCharSel_804D6CB0->data.data.players[di].team = dp->team;
            mnCharSel_8025DB34((u8) di);
            sfxMove();
        }
    }
}

void mnCharSel_CursorThink(HSD_GObj* gobj)
{
    HSD_JObj* sp98;
    UNUSED u8 unk94[4];
    Point3d sp88;
    UNUSED u8 unk78[16];
    HSD_JObj* sp74;
    UNUSED u8 unk58[28];
    HSD_JObj* sp54;
    HSD_JObj* sp50;
    s32 cpu_door;
    u32 a_press;
    UNUSED u32 scan_home;
    CSSTagData* current_tag;
    HSD_JObj* state_jobj;
    HSD_JObj* color_jobj;
    u32 next_port;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    struct CSSCursorData* cursor = gobj->user_data;
    CSSAllData* all_data = CSS_ALL;
    u32 trigger;
    int n_doors;
    u32 buttons;
    f32 dx;
    f32 dy;
    int door;

    if (mnCharSel_804D6CB0->match_type == TRAINING_MODE) {
        n_doors = 2;
    } else {
        n_doors = mnCharSel_804D6CF5;
    }

    if (mnCharSel_804D6CF6 == 0) {
        cursor->x8 = 0;

        if (mnCharSel_804D6CF5 == 1) {
            int port = (u8) mnCharSel_804D6CF0;
            trigger = HSD_PadCopyStatus[port].trigger;
            buttons = HSD_PadCopyStatus[port].button;
            getStickDelta(port, &dx, &dy);
            if (buttons & 0x200) {
                if (mnCharSel_804D6CF3 & mnCharSel_804D50C8[cursor->x4]) {
                    u16 new_timer = cursor->xA + 1;
                    cursor->xA = new_timer;
                    if (new_timer > 0x1E) {
                        mnCharSel_804D6CF6 = 2;
                    }
                } else {
                    cursor->xA = 0;
                }
            } else {
                mnCharSel_804D6CF3 |= mnCharSel_804D50C8[cursor->x4];
                cursor->xA = 0;
            }
        } else {
            int port = cursor->x4;
            trigger = HSD_PadCopyStatus[port].trigger;
            buttons = HSD_PadCopyStatus[port].button;
            getStickDelta(port, &dx, &dy);

            if (HSD_PadCopyStatus[cursor->x4].err != 0) {
                if (cursor->x5 != 3) {
                    cursor->xC = (f32) ((15.0f * cursor->x4) - 31.0f);
                    cursor->x10 = -21.5f;
                    cursor->xA = 0;
                    if (cursor->x5 == 1) {
                        door = cursor->x6;
                        if (door <= 3U) {
                            cursor->x5 = 2;
                            if (mnCharSel_8025FDEC(door & 0xFF) != 0) {
                                mnCharSel_8025FB50(door & 0xFF, 1);
                            }
                        } else if (door <= 7U) {
                            cpu_door = door - 4;
                            all_data->doors_data.doors[cpu_door]
                                .is_hold_cpu_slider = 0;
                        }
                    } else {
                        if (all_data->doors_data.doors[cursor->x4].sel_icon >=
                                0x19U &&
                            all_data->doors_data.doors[cursor->x4].p_kind !=
                                3 &&
                            mnCharSel_8025FDEC(cursor->x4) != 0)
                        {
                            mnCharSel_8025FB50(cursor->x4, 1);
                        }
                    }
                    if (all_data->doors_data.doors[cursor->x4].p_kind == 0) {
                        all_data->doors_data.doors[cursor->x4].p_kind = 1;
                        mnCharSel_804D6CB0->data.data.players[cursor->x4]
                            .slot_type = 1;
                        mnCharSel_804D6CB0->data.data.players[cursor->x4].xA =
                            0x78;
                        all_data->tags[cursor->x4].data->use_tag = 0;
                    }
                    mnCharSel_8025DB34(cursor->x4);
                    if (all_data->tags[cursor->x4].data->state != 0) {
                        all_data->tags[cursor->x4].data->state = 4;
                    }
                    all_data->doors_data.doors[cursor->x4]
                        .is_hold_handicap_slider = 0;
                }
                cursor->x5 = 3;
                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                return;
            }

            if (cursor->x5 == 3) {
                cursor->x5 = 2;
                HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            }

            if (buttons & 0x200) {
                if (mnCharSel_804D6CF3 & mnCharSel_804D50C8[cursor->x4]) {
                    u16 new_timer = cursor->xA + 1;
                    cursor->xA = new_timer;
                    if (new_timer > 0x1E) {
                        mnCharSel_804D6CF6 = 2;
                    }
                } else {
                    cursor->xA = 0;
                }
            } else {
                mnCharSel_804D6CF3 |= mnCharSel_804D50C8[cursor->x4];
                cursor->xA = 0;
            }
        }

        cursor->xC = (f32) ((0.0002f * dx) + cursor->xC);
        cursor->x10 = (f32) ((0.0002f * dy) + cursor->x10);

        all_data->tags[cursor->x4].data->scroll_amt = 0.0f;

        {
            current_tag = all_data->tags[cursor->x4].data;
            if (current_tag->state != 0) {
                if (mnCharSel_804D6CF5 == 1) {
                    lb_80011E24(mnCharSel_804D6CC0, &sp98,
                                all_data->misc.name_list_joint, -1);
                } else {
                    lb_80011E24(mnCharSel_804D6CC0, &sp98,
                                all_data->tags[cursor->x4].list_joint, -1);
                }
                lb_8000B1CC(sp98, NULL, &sp88);

                if ((0.8f + sp88.y) < cursor->x10) {
                    all_data->tags[cursor->x4].data->scroll_amt =
                        (f32) (cursor->x10 - (0.8f + sp88.y));
                    cursor->x10 = (f32) (0.8f + sp88.y);
                }
                if ((-14.8f + sp88.y) > cursor->x10) {
                    all_data->tags[cursor->x4].data->scroll_amt =
                        (f32) (cursor->x10 - (-14.8f + sp88.y));
                    cursor->x10 = (f32) (-14.8f + sp88.y);
                }
                if ((4.3f + sp88.x) < cursor->xC) {
                    cursor->xC = 4.3f + sp88.x;
                }
                if ((-5.3f + sp88.x) > cursor->xC) {
                    cursor->xC = -5.3f + sp88.x;
                }
            } else {
                if (25.0f < cursor->x10) {
                    cursor->x10 = 25.0f;
                }
                if (-22.0f > cursor->x10) {
                    cursor->x10 = -22.0f;
                }
                if (26.0f < cursor->xC) {
                    cursor->xC = 26.0f;
                }
                if (-35.0f > cursor->xC) {
                    cursor->xC = -35.0f;
                }
            }
        }

        {
            u8 port = cursor->x4;
            CSSTagData* tag = all_data->tags[port].data;
            if (tag->state == 0) {
                if (cursor->x5 == 1) {
                    door = cursor->x6;
                    switch (door) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        if (cursor->x10 < 0.2f) {
                            if ((s32) port != (s32) door ||
                                ((s32) port == (s32) door &&
                                 all_data->doors_data.doors[door].p_kind == 3))
                            {
                                mnCharSel_8025FDEC(door);
                                lbAudioAx_800237A8(0xB8, 0x7F, 0x40);
                            } else {
                                mnCharSel_804A0BD0[door]->x5 = 0;
                                all_data->doors_data.doors[door].sel_icon =
                                    0x19;
                                {
                                    s32 player_idx;
                                    if (mnCharSel_804D6CF5 == 1) {
                                        if ((s32) door != 0) {
                                            player_idx = mnCharSel_804D6CF1;
                                        } else {
                                            player_idx = mnCharSel_804D6CF0;
                                        }
                                    } else {
                                        player_idx = door;
                                    }
                                    mnCharSel_804D6CB0->data.data
                                        .players[player_idx]
                                        .c_kind = CHKIND_NONE;
                                }
                            }
                            mnCharSel_8025DB34(door);
                            cursor->x5 = 2;
                        } else {
                            a_press = trigger & HSD_PAD_A;
                            if (a_press != 0) {
                                struct CSSCharModel* m =
                                    mnCharSel_804A0BD0[door];
                                if (m->xC < 6.0f && m->xC > -1.0f &&
                                    ((m->x8 > -30.0f && m->x8 < -24.4f) ||
                                     (m->x8 > 24.4f && m->x8 < 30.2f)))
                                {
                                    s32 icon_count;
                                    for (icon_count = 0; icon_count < 25;
                                         icon_count++)
                                    {
                                        if (icons[icon_count].state < 2) {
                                            break;
                                        }
                                    }
                                    if (icon_count == 0x19) {
                                        mnCharSel_8025FB50(door, 0);
                                        while (true) {
                                            mnCharSel_803F0DFC.doors[door]
                                                .costume =
                                                HSD_Randi((s32) gm_80169238(
                                                    icons[mnCharSel_803F0DFC
                                                              .doors[door]
                                                              .sel_icon]
                                                        .char_kind));
                                            if (!isDuplicateCostume(door)) {
                                                break;
                                            }
                                        }
                                        mnCharSel_8025DB34(door);
                                        cursor->x5 = 2;
                                        lbAudioAx_800237A8(0xB8, 0x7F, 0x40);
                                        goto update_display;
                                    }
                                }
                            }

                            {
                                struct CSSCharModel* m2 =
                                    mnCharSel_804A0BD0[door];
                                s32 i;
                                for (i = 0; i < 0x19; i++) {
                                    if (m2->x8 > icons[i].bound_l &&
                                        m2->x8 < icons[i].bound_r &&
                                        m2->xC < icons[i].bound_u &&
                                        m2->xC > icons[i].bound_d &&
                                        icons[i].state >= 1)
                                    {
                                        all_data->doors_data.doors[door]
                                            .sel_icon = (u8) i;
                                        mnCharSel_8025DB34(door);
                                        if (trigger & HSD_PAD_A) {
                                            s32 player_idx;
                                            if (mnCharSel_804D6CF5 == 1) {
                                                if ((s32) door != 0) {
                                                    player_idx =
                                                        mnCharSel_804D6CF1;
                                                } else {
                                                    player_idx =
                                                        mnCharSel_804D6CF0;
                                                }
                                            } else {
                                                player_idx = door;
                                            }
                                            mnCharSel_804D6CB0->data.data
                                                .players[player_idx]
                                                .c_kind =
                                                (s8) icons[all_data->doors_data
                                                               .doors[door]
                                                               .sel_icon]
                                                    .char_kind;
                                            if (mnCharSel_804D6CF5 == 1) {
                                                lb_80011E24(
                                                    mnCharSel_804D6CC0, &sp98,
                                                    icons[i].joint_id_1p, -1);
                                            } else {
                                                lb_80011E24(
                                                    mnCharSel_804D6CC0, &sp98,
                                                    icons[i].joint_id_vs, -1);
                                            }
                                            HSD_ForeachAnim(sp98, JOBJ_TYPE,
                                                            TOBJ_MASK,
                                                            HSD_AObjReqAnim,
                                                            AOBJ_ARG_AF, 10.0);
                                            icons[i].anim_timer = 0xC;
                                            mnCharSel_804A0BD0[door]->x5 = 0;
                                            HSD_GObjGXLink_803909D8(
                                                mnCharSel_804A0BD0[door]->gobj,
                                                mnCharSel_804A0BC0
                                                    [mnCharSel_804D6CF5 - 1]
                                                        ->gobj);
                                            all_data->doors_data.doors[door]
                                                .selected_since_load = 1;
                                            cursor->x5 = 2;
                                            {
                                                u8 sel =
                                                    all_data->doors_data
                                                        .doors[door & 0xFF]
                                                        .sel_icon;
                                                lbAudioAx_80023870(
                                                    all_data->icons[sel].sfx,
                                                    0x7F, 0x40, sel + 0x8A);
                                                gm_80168C5C(
                                                    (u32) all_data->icons[sel]
                                                        .char_kind);
                                            }
                                            lbAudioAx_800237A8(0xB8, 0x7F,
                                                               0x40);
                                            goto update_display;
                                        }
                                        goto cancel_or_costume;
                                    }
                                }

                                mnCharSel_8025D5AC((s32) door, 0, 1);
                                {
                                    CSSTagData* td = all_data->tags[door].data;
                                    if (td->use_tag == 0) {
                                        td->text->hidden = 1;
                                    }
                                }
                                all_data->doors_data.doors[door]
                                    .sel_icon_prev = 0x19;
                                if (trigger & HSD_PAD_A) {
                                    lbAudioAx_80024030(3);
                                } else {
                                cancel_or_costume:
                                    if (trigger & HSD_PAD_B) {
                                        if (mnCharSel_8025FDEC(door) == 0) {
                                            mnCharSel_8025DB34(door);
                                            cursor->x5 = 2;
                                        }
                                    } else {
                                        mnCharSel_CostumeChange((s32) door,
                                                                trigger);
                                    }
                                }
                            }
                        }
                        break;
                    case 4:
                    case 5:
                    case 6:
                    case 7: {
                        s32 slider_door = door - 4;
                        updateGrabbedSlider(
                            cursor, &all_data->doors_data.doors[slider_door],
                            slider_door, trigger, &sp98, &sp88, false);
                    } break;
                    case 8:
                    case 9:
                    case 0xA:
                    case 0xB: {
                        s32 hc_door = door - 8;
                        updateGrabbedSlider(
                            cursor, &all_data->doors_data.doors[hc_door],
                            hc_door, trigger, &sp98, &sp88, true);
                    } break;
                    }
                    goto update_display;
                }

                if ((cursor->xC > 17.3f) && (cursor->x10 > 22.0f)) {
                    cursor->x8 = 1;
                    if (trigger & HSD_PAD_A) {
                        mnCharSel_804D6CF6 = 2;
                        goto update_display;
                    }
                }

                if (mnCharSel_804D6CF5 == 1) {
                    if (mnCharSel_804A0BD0[cursor->x4]->x5 == 0) {
                        mnCharSel_CostumeChange(0, trigger);
                    }

                    if (mnCharSel_804D6CB0->match_type < 0xDU) {
                        f32 cy = cursor->x10;
                        if (cy < data2.x108 && cy > data2.x10c) {
                            f32 cx = cursor->xC;
                            if (cx > data2.xf8 && cx < data2.xfc) {
                                cursor->x8 = 1;
                                if ((trigger & HSD_PAD_A) && data2.stocks > 1U)
                                {
                                    data2.stocks = (u8) (data2.stocks - 1);
                                    updateStockIcons(&data2, &sp54, 1);
                                    mnCharSel_804D6CB0->data.data
                                        .players[mnCharSel_804D6CF0]
                                        .stocks = (s8) data2.stocks;
                                    sfxMove();
                                } else {
                                    goto cpu_level_widget;
                                }
                            } else if (cx > data2.x100 && cx < data2.x104) {
                                cursor->x8 = 1;
                                if ((trigger & HSD_PAD_A) && data2.stocks < 5U)
                                {
                                    data2.stocks = (u8) (data2.stocks + 1);
                                    updateStockIcons(&data2, &sp50, 1);
                                    mnCharSel_804D6CB0->data.data
                                        .players[mnCharSel_804D6CF0]
                                        .stocks = (s8) data2.stocks;
                                    sfxMove();
                                } else {
                                    goto cpu_level_widget;
                                }
                            } else {
                                goto cpu_level_widget;
                            }
                        } else {
                            goto cpu_level_widget;
                        }
                    } else {
                    cpu_level_widget:
                        if (mnCharSel_804D6CB0->match_type <= 0xDU) {
                            f32 cy2 = cursor->x10;
                            if (cy2 < all_data->misc.cpubtn_top &&
                                cy2 > all_data->misc.cpubtn_btm)
                            {
                                f32 cx2 = cursor->xC;
                                if (cx2 > all_data->misc.cpudown_left &&
                                    cx2 < all_data->misc.cpudown_right)
                                {
                                    cursor->x8 = 1;
                                    if (trigger & HSD_PAD_A) {
                                        u8* level;
                                        u8 current_level;
                                        if ((current_level =
                                                 *(level = &all_data->misc
                                                                .cpu_level)) !=
                                            0)
                                        {
                                            *level = (u8) (current_level - 1);
                                            all_data->misc.scroll_flag = 1;
                                            mnCharSel_804D6CB0->data.data
                                                .players
                                                    [(s8) (u8)
                                                         mnCharSel_804D6CF0]
                                                .cpu_level = *level;
                                            sfxMove();
                                        } else {
                                            goto door_clicks;
                                        }
                                    } else {
                                        goto door_clicks;
                                    }
                                } else if (cx2 > all_data->misc.cpuup_left &&
                                           cx2 < all_data->misc.cpuup_right)
                                {
                                    cursor->x8 = 1;
                                    if (trigger & HSD_PAD_A) {
                                        u8* level;
                                        u8 current_level;
                                        if ((current_level =
                                                 *(level = &all_data->misc
                                                                .cpu_level)) <
                                            4U)
                                        {
                                            *level = (u8) (current_level + 1);
                                            all_data->misc.scroll_flag = 1;
                                            mnCharSel_804D6CB0->data.data
                                                .players
                                                    [(s8) (u8)
                                                         mnCharSel_804D6CF0]
                                                .cpu_level = *level;
                                            sfxMove();
                                        } else {
                                            goto door_clicks;
                                        }
                                    } else {
                                        goto door_clicks;
                                    }
                                } else {
                                    goto door_clicks;
                                }
                            } else {
                                goto door_clicks;
                            }
                        } else {
                            goto door_clicks;
                        }
                    }
                    goto update_display;
                }

                if (mnCharSel_804D6CB0->match_type != 2) {
                    f32 cx3 = cursor->xC;
                    if (cx3 > -17.0f && cx3 < 15.0f && cursor->x10 > 22.0f) {
                        cursor->x8 = 1;
                        if (trigger & HSD_PAD_A) {
                            s32 loop_i;
                            mnCharSel_804D6CF6 = 3;
                            for (loop_i = 0; loop_i < (s32) mnCharSel_804D6CF5;
                                 loop_i++)
                            {
                                if (mnCharSel_804A0BC0[loop_i]->x5 == 1 &&
                                    mnCharSel_8025FDEC((u8) loop_i) == 0)
                                {
                                    mnCharSel_8025DB34((u8) loop_i);
                                    mnCharSel_804A0BC0[loop_i]->x5 = 2;
                                }
                            }
                            return;
                        }
                    }
                }

                if (cursor->xC < -25.5f && cursor->x10 > 22.0f) {
                    switch ((s32) mnCharSel_804D6CB0->match_type) {
                    case VS_MELEE:
                    case VS_CAMERA:
                    case VS_STAMINA:
                    case VS_SUDDEN_DEATH:
                    case VS_GIANT:
                    case VS_TINY:
                    case VS_INVISIBLE:
                    case VS_FIXED_CAMERA:
                    case VS_SINGLE_BUTTON:
                    case VS_LIGHTNING:
                    case VS_SLOWMO:
                        cursor->x8 = 1;
                        if (trigger & HSD_PAD_A) {
                            sfxMove();
                            {
                                u8* is_teams = &mnCharSel_804D6CB0->data.data
                                                    .rules.is_teams;
                                *is_teams = (*is_teams + 1) & 1;
                            }
                            if (mnCharSel_804D6CB0->data.data.rules.is_teams ==
                                0)
                            {
                                int k;
                                for (k = 0; k < (s32) mnCharSel_804D6CF5; k++)
                                {
                                    if (isDuplicateCostumeCached(k)) {
                                        mnCharSel_803F0DFC.doors[k].costume =
                                            0;
                                        current_tag =
                                            (CSSTagData*) loadCSSValue(
                                                &mnCharSel_804D6CB0);
                                        for (;;) {
                                            if (!isDuplicateCostumeWith(
                                                    k, (CSSData*) current_tag,
                                                    mnCharSel_804D6CF5))
                                            {
                                                break;
                                            }
                                            mnCharSel_803F0DFC.doors[k]
                                                .costume =
                                                (u8) (mnCharSel_803F0DFC
                                                          .doors[k]
                                                          .costume +
                                                      1);
                                        }
                                    }
                                }
                            }
                            mnCharSel_8025EE8C(mnCharSel_804D6CB0->match_type);
                        } else {
                            goto try_costume_change;
                        }
                        break;
                    default:
                        goto try_costume_change;
                    }
                } else {
                try_costume_change: {
                    u8 cport2 = cursor->x4;
                    if (mnCharSel_804A0BD0[cport2]->x5 == 0 &&
                        mnCharSel_804D6CB0->data.data.rules.is_teams == 0 &&
                        all_data->doors_data.doors[cport2].p_kind != 3)
                    {
                        mnCharSel_CostumeChange((s32) cport2, trigger);
                    }
                }
                door_clicks: {
                    u32 a_press2 = trigger & HSD_PAD_A;
                    if (a_press2 != 0) {
                        if (mnCharSel_804D6CF5 != 1) {
                            for (door = 0; door < (s32) mnCharSel_804D6CF5;
                                 door++)
                            {
                                CSSTagData* tag_data;
                                f32 cx4;

                                if (door == 3 &&
                                    mnCharSel_804D6CB0->match_type == 1)
                                {
                                    continue;
                                }
                                if ((mnCharSel_803F0DFC.doors[door]
                                         .is_hold_cpu_slider |
                                     mnCharSel_803F0DFC.doors[door]
                                         .is_hold_handicap_slider) == 0 &&
                                    mnCharSel_804A0BD0[door]->x5 == 0 &&
                                    mnCharSel_804A0BC0[door]->x5 != 1)
                                {
                                    tag_data = mnCharSel_803F0E8C[door].data;
                                    if (tag_data->state != 0) {
                                        continue;
                                    }
                                    cx4 = cursor->xC;
                                    if (cx4 > mnCharSel_803F0DFC.doors[door]
                                                  .togglebtn_left &&
                                        cx4 < mnCharSel_803F0DFC.doors[door]
                                                  .togglebtn_right)
                                    {
                                        f32 cy4 = cursor->x10;
                                        /* Retail nudges both toggle-box
                                         * bounds outward by 1/10485760. */
                                        if (cy4 < 0.20000009536743146 &&
                                            cy4 > -4.600000095367432)
                                        {
                                            cursor->x10 = -2.2f;
                                            {
                                                u8 new_kind;
                                                new_kind = mnCharSel_803F0DFC
                                                               .doors[door]
                                                               .p_kind +
                                                           1;
                                                mnCharSel_803F0DFC.doors[door]
                                                    .p_kind = new_kind;
                                                switch ((s32) new_kind) {
                                                case 3:
                                                    break;
                                                case 2:
                                                    mnCharSel_803F0DFC
                                                        .doors[door]
                                                        .p_kind = 3;
                                                    break;
                                                case 4:
                                                    if (HSD_PadCopyStatus
                                                            [(u8) door]
                                                                .err != 0)
                                                    {
                                                        mnCharSel_803F0DFC
                                                            .doors[door]
                                                            .p_kind = 1;
                                                    } else {
                                                        mnCharSel_803F0DFC
                                                            .doors[door]
                                                            .p_kind = 0;
                                                    }
                                                    break;
                                                }
                                            }
                                            mnCharSel_804D6CB0->data.data
                                                .players[door]
                                                .slot_type =
                                                mnCharSel_803F0DFC.doors[door]
                                                    .p_kind;
                                            if (mnCharSel_803F0DFC.doors[door]
                                                    .p_kind == 1)
                                            {
                                                mnCharSel_804D6CB0->data.data
                                                    .players[door]
                                                    .xA = 0x78;
                                                mnCharSel_803F0E8C[door]
                                                    .data->use_tag = 0;
                                                if (mnCharSel_803F0DFC
                                                            .doors[door]
                                                            .selected_since_load ==
                                                        0 &&
                                                    (s32) cursor->x4 != door)
                                                {
                                                    mnCharSel_8025FB50(
                                                        (u8) door, 1);
                                                }
                                            }
                                            mnCharSel_8025DB34((u8) door);
                                            sfxMove();
                                            break;
                                        }
                                    }
                                }

                                if (mnCharSel_804D6CB0->data.data.rules
                                            .is_teams == 1 &&
                                    mnCharSel_803F0DFC.doors[door].p_kind != 3)
                                {
                                    cycleTeam(cursor,
                                              &mnCharSel_803F0DFC.doors[door],
                                              door);
                                }
                                if (a_press2 != 0) {
                                    if (mnCharSel_803F0DFC.doors[door]
                                                .is_hold_cpu_slider == 0 &&
                                        mnCharSel_803F0DFC.doors[door]
                                                .p_kind == 1)
                                    {
                                        GameRules* rules2 =
                                            gmMainLib_GetGameRules();
                                        if (rules2->handicap != 0) {
                                            lb_80011E24(
                                                mnCharSel_804D6CC0, &sp98,
                                                mnCharSel_803F0DFC.doors[door]
                                                    .cpuslider2_joint,
                                                -1);
                                        } else {
                                            lb_80011E24(
                                                mnCharSel_804D6CC0, &sp98,
                                                mnCharSel_803F0DFC.doors[door]
                                                    .cpuslider_joint,
                                                -1);
                                        }
                                        lb_8000B1CC(sp98, NULL, (&sp88));
                                        {
                                            f32 dx =
                                                cursor->xC - (-2.9f + sp88.x);
                                            f32 dy =
                                                cursor->x10 - (1.7f + sp88.y);
                                            if ((dx * dx + dy * dy) < 5.0f) {
                                                cursor->x5 = 1;
                                                cursor->x6 = (u8) (door + 4);
                                                cursor->xC =
                                                    (f32) (-2.9f + sp88.x);
                                                cursor->x10 =
                                                    (f32) (1.7f + sp88.y);
                                                mnCharSel_803F0DFC.doors[door]
                                                    .is_hold_cpu_slider = 1;
                                                lbAudioAx_800237A8(0xB7, 0x7F,
                                                                   0x40);
                                            }
                                        }
                                    }

                                    if (mnCharSel_803F0DFC.doors[door]
                                            .is_hold_handicap_slider == 0)
                                    {
                                        GameRules* rules3 =
                                            gmMainLib_GetGameRules();
                                        if (rules3->handicap == 2) {
                                            u8 pk =
                                                mnCharSel_803F0DFC.doors[door]
                                                    .p_kind;
                                            if (pk != 3 &&
                                                (pk == 1 ||
                                                 door == (s32) cursor->x4))
                                            {
                                                lb_80011E24(
                                                    mnCharSel_804D6CC0, &sp98,
                                                    mnCharSel_803F0DFC
                                                        .doors[door]
                                                        .cpuslider_joint,
                                                    -1);
                                                lb_8000B1CC(sp98, NULL,
                                                            (&sp88));
                                                {
                                                    f32 hdx = cursor->xC -
                                                              (-2.9f + sp88.x);
                                                    f32 hdy = cursor->x10 -
                                                              (1.7f + sp88.y);
                                                    if ((hdx * hdx +
                                                         hdy * hdy) < 5.0f)
                                                    {
                                                        cursor->x5 = 1;
                                                        cursor->x6 =
                                                            (u8) (door + 8);
                                                        cursor->xC =
                                                            (f32) (-2.9f +
                                                                   sp88.x);
                                                        cursor->x10 =
                                                            (f32) (1.7f +
                                                                   sp88.y);
                                                        mnCharSel_803F0DFC
                                                            .doors[door]
                                                            .is_hold_handicap_slider =
                                                            1;
                                                        lbAudioAx_800237A8(
                                                            0xB7, 0x7F, 0x40);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        {
                            if ((cursor->x4 != 3 ||
                                 mnCharSel_804D6CB0->match_type != 1) &&
                                all_data->doors_data.doors[cursor->x4]
                                        .p_kind == 0)
                            {
                                if (mnCharSel_804D6CF5 == 1) {
                                    lb_80011E24(mnCharSel_804D6CC0, &sp98,
                                                all_data->misc.tag_box_joint,
                                                -1);
                                } else {
                                    lb_80011E24(
                                        mnCharSel_804D6CC0, &sp98,
                                        all_data
                                            ->tags[*(volatile u8*) &cursor->x4]
                                            .name_jointl,
                                        -1);
                                }
                                lb_8000B1CC(sp98, NULL, (&sp88));
                                {
                                    if (cursor->xC > (sp88.x - 4.7f) &&
                                        cursor->xC < (5.2f + sp88.x))
                                    {
                                        if (cursor->x10 < (2.0f + sp88.y) &&
                                            cursor->x10 > (sp88.y - 1.0f))
                                        {
                                            if (mnCharSel_804D6CF5 == 1) {
                                                lb_80011E24(
                                                    mnCharSel_804D6CC0, &sp74,
                                                    all_data->misc
                                                        .name_list_joint,
                                                    -1);
                                            } else {
                                                lb_80011E24(
                                                    mnCharSel_804D6CC0, &sp74,
                                                    all_data->tags[cursor->x4]
                                                        .list_joint,
                                                    -1);
                                            }
                                            lb_8000B1CC(sp74, NULL, (&sp88));
                                            cursor->xC = sp88.x;
                                            cursor->x10 =
                                                (f32) (sp88.y - 5.0f);
                                            all_data->tags[cursor->x4]
                                                .data->state = 1;
                                        }
                                    }
                                }
                            }
                        }

                        {
                            s32 closest;
                            f32 closest_dist = 9.0f;
                            s32 ci;
                            for (ci = 0, closest = -1; ci < (s32) n_doors;
                                 ci++)
                            {
                                f32 cy7 = cursor->x10;
                                if (!(cy7 < 0.2f) && !(cy7 > 22.0f)) {
                                    u8 pk2 =
                                        mnCharSel_803F0DFC.doors[ci].p_kind;
                                    if (pk2 != 3 &&
                                        mnCharSel_803F0DFC.doors[ci].sel_icon <
                                            0x19U &&
                                        (pk2 != 0 || (s32) cursor->x4 == ci))
                                    {
                                        struct CSSCharModel* mc =
                                            mnCharSel_804A0BD0[ci];
                                        if (mc->x5 == 0) {
                                            f32 ddx =
                                                3.8f + (cursor->xC - mc->x8);
                                            f32 ddy = -2.6f + (cy7 - mc->xC);
                                            f32 dist =
                                                (ddx * ddx) + (ddy * ddy);
                                            if (dist < closest_dist) {
                                                closest_dist = dist;
                                                closest = ci;
                                            }
                                        }
                                    }
                                }
                            }

                            if (closest >= 0) {
                                u8 cport4 = cursor->x4;
                                s32 closest_door = (u8) closest;
                                mnCharSel_804A0BD0[(u8) closest]->x5 =
                                    (s8) (cport4 + 1);
                                mnCharSel_804A0BC0[cport4]->x5 = 1;
                                mnCharSel_804A0BC0[cport4]->x6 = closest_door;
                                mnCharSel_803F0DFC.doors[closest_door]
                                    .sel_icon = 0xD;
                                HSD_GObjGXLink_803909D8(
                                    mnCharSel_804A0BD0[(u8) closest]->gobj,
                                    mnCharSel_804A0BC0[cport4]->gobj);
                                lbAudioAx_800237A8(0xB7, 0x7F, 0x40);
                                cursor->xC =
                                    (f32) (mnCharSel_804A0BD0[closest]->x8 -
                                           2.7f);
                                cursor->x10 =
                                    (f32) (mnCharSel_804A0BD0[closest]->xC -
                                           -2.0f);
                            }
                        }
                    } else if (trigger & HSD_PAD_B) {
                        u8 cport5;
                        (void) mnCharSel_803F0DFC.doors[cport5 = cursor->x4];
                        if (mnCharSel_803F0DFC.doors[cursor->x4].p_kind != 3 &&
                            mnCharSel_803F0DFC.doors[cursor->x4].sel_icon <
                                0x19U)
                        {
                            f32 cy8 = cursor->x10;
                            if (cy8 > 0.2f && cy8 < 22.0f) {
                                if (mnCharSel_804A0BD0[cursor->x4]->x5 == 0) {
                                    mnCharSel_804A0BD0[cport5]->x5 =
                                        (u8) (cport5 + 1);
                                    mnCharSel_804A0BC0[cport5]->x5 = 1;
                                    mnCharSel_804A0BC0[cport5]->x6 = cport5;
                                    mnCharSel_803F0DFC.doors[cport5].sel_icon =
                                        0xD;
                                    HSD_GObjGXLink_803909D8(
                                        mnCharSel_804A0BD0[cport5]->gobj,
                                        mnCharSel_804A0BC0[cport5]->gobj);
                                    lbAudioAx_800237A8(0xB7, 0x7F, 0x40);
                                }
                            }
                        }
                    }

                    {
                        f32 cy9 = cursor->x10;
                        if (cy9 > 0.2f && cy9 < 22.0f) {
                            u8 cport6 = cursor->x4;
                            if (cport6 != 3 ||
                                mnCharSel_804D6CB0->match_type != 1)
                            {
                                if (all_data->doors_data.doors[cport6]
                                        .p_kind == 3)
                                {
                                    all_data->doors_data.doors[cport6].p_kind =
                                        0;
                                    mnCharSel_804D6CB0->data.data
                                        .players[cursor->x4]
                                        .slot_type = 0;
                                    mnCharSel_8025DB34(cursor->x4);
                                    sfxMove();
                                }

                                {
                                    u8 cport7 = cursor->x4;
                                    if (mnCharSel_803F0DFC.doors[cport7]
                                            .sel_icon >= 0x19U)
                                    {
                                        mnCharSel_804A0BD0[cport7]->x5 =
                                            (u8) (next_port = cport7 + 1);
                                        mnCharSel_804A0BC0[cport7]->x5 = 1;
                                        mnCharSel_804A0BC0[cport7]->x6 =
                                            cport7;
                                        mnCharSel_803F0DFC.doors[cport7]
                                            .sel_icon = 0xD;
                                        HSD_GObjGXLink_803909D8(
                                            mnCharSel_804A0BD0[cport7]->gobj,
                                            mnCharSel_804A0BC0[cport7]->gobj);
                                        lbAudioAx_800237A8(0xB7, 0x7F, 0x40);
                                        {
                                            f32 val_x = 2.7f + cursor->xC;
                                            mnCharSel_804A0BD0[cursor->x4]
                                                ->x10 = val_x;
                                            mnCharSel_804A0BD0[cursor->x4]
                                                ->x8 = val_x;
                                        }
                                        {
                                            f32 val_y = -2.0f + cursor->x10;
                                            mnCharSel_804A0BD0[cursor->x4]
                                                ->x14 = val_y;
                                            mnCharSel_804A0BD0[cursor->x4]
                                                ->xC = val_y;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                }
            }
            goto update_display;
        }
        goto update_display;
    }

update_display:
    updateCursorDisplay(jobj, cursor, &state_jobj, &color_jobj);
}
static inline int getDoorCount(CSSData* css)
{
    if (css->match_type == TRAINING_MODE) {
        return 2;
    }
    return mnCharSel_804D6CF5;
}

static inline void animateCharModel(HSD_JObj* jobj, f32 frame)
{
    HSD_JObj* child;

    lb_80011E24(jobj, &child, 4, -1);
    {
        HSD_JObj* anim_jobj = child;
        HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, frame);
    }
    HSD_JObjAnimAll(child);
    HSD_ForeachAnim(child, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                    AOBJ_ARG_AOV, 0, 0);
}

void fn_80262648(HSD_GObj* gobj)
{
    HSD_JObj* sp24;
    union {
        CSSData* css;
        struct CSSCharModel** bd0;
        struct CSSCharModel* model;
    } carrier;
    struct CSSCharModel* model;
    HSD_JObj* jobj = (carrier.model = gobj->user_data, model = carrier.model,
                      GET_JOBJ(gobj));
    u8 prev_port = model->x6;
    int n_doors;

    carrier.css = mnCharSel_804D6CB0;
    n_doors = getDoorCount(carrier.css);

    {
        u8 p_kind;
        u8 door = model->x4;

        if ((p_kind = mnCharSel_803F0DFC.doors[door].p_kind) == 3 ||
            mnCharSel_803F0DFC.doors[door].sel_icon >= 0x19U)
        {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            return;
        }

        if (mnCharSel_804D6CF5 == 1) {
            if (door != 0) {
                model->x6 = 8;
            } else {
                model->x6 = (u8) mnCharSel_804D6CF0;
            }
        } else if (carrier.css->data.data.rules.is_teams == 0) {
            if (p_kind == 1) {
                model->x6 = 8;
            } else {
                model->x6 = door;
            }
        } else if (p_kind == 1) {
            model->x6 =
                (u8) (mnCharSel_804D50E0[mnCharSel_803F0DFC.doors[door].team] +
                      4);
        } else {
            model->x6 =
                mnCharSel_804D50E0[mnCharSel_803F0DFC.doors[door].team];
        }
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    model->x7 = (u8) (model->x7 + 1);

    {
        u8 port = model->x6;
        if (prev_port != port || model->x7 > 0x27U) {
            if (port < 4U) {
                if (mnCharSel_804D6CF5 == 1) {
                    animateCharModel(jobj, (f32) (mnCharSel_804D6CF0 * 4));
                } else {
                    animateCharModel(jobj, (f32) (model->x4 * 4));
                }
            } else {
                animateCharModel(jobj, 16.0f);
            }
            lb_80011E24(jobj, &sp24, 3, -1);
            {
                HSD_JObj* anim_jobj = sp24;
                HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, MOBJ_MASK,
                                HSD_AObjReqAnim, AOBJ_ARG_AF,
                                (f32) (model->x6 * 0x28));
            }
            model->x7 = 0;
        }
    }

    {
        u8 status = model->x5;
        if (status == 0) {
            s32 iter;
            carrier.bd0 = mnCharSel_804A0BD0;
            for (iter = 0; iter < 0x14; iter++) {
                struct CSSCharModel** bdp = carrier.bd0;
                CSSDoor* dp = mnCharSel_803F0DFC.doors;
                s32 j;

                for (j = 0; j < (s32) n_doors; j++) {
                    if (j != (s32) model->x4 && (*bdp)->x5 == 0 &&
                        dp->p_kind != 3 && dp->sel_icon < 0x19U)
                    {
                        f32 dx;
                        f32 dy;
                        f32 angle;
                        do {
                            dx = (0.1f * (HSD_Randf() - 0.5f)) +
                                 (model->x8 - (*bdp)->x8);
                        } while (dx == 0.0f);

                        do {
                            f32 rand = HSD_Randf();
                            dy = (0.1f * (rand - 0.5f)) +
                                 (model->xC - (*bdp)->xC);
                        } while (dy == 0.0f);

                        if ((dx * dx + dy * dy) < 8.0f) {
                            if (dy < 0.01f && dy > -0.01f) {
                                angle =
                                    (f32) (dx < 0.0f ? 1.5707963267948966
                                                     : -1.5707963267948966);
                            } else {
                                angle =
                                    (f32) ((dy < 0.0f ? 0.0
                                                      : 3.141592653589793) +
                                           atanf(dx / dy));
                            }
                            model->x8 = -((0.01f * sinf(angle)) - model->x8);
                            model->xC = -((0.01f * cosf(angle)) - model->xC);
                        }
                    }
                    bdp++;
                    dp++;
                }

                {
                    f32 x;

                    x = model->x8;
                    if (x <
                        1.5f +
                            icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon]
                                .bound_l)
                    {
                        model->x8 += 0.02f;
                        if (model->x8 <
                            icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon]
                                .bound_l)
                        {
                            model->x8 =
                                icons[mnCharSel_803F0DFC.doors[model->x4]
                                          .sel_icon]
                                    .bound_l;
                        }
                    }

                    x = model->x8;
                    if (x > icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon]
                                    .bound_r -
                                1.5f)
                    {
                        model->x8 = x - 0.02f;
                        if (model->x8 >
                            icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon]
                                .bound_r)
                        {
                            model->x8 =
                                icons[mnCharSel_803F0DFC.doors[model->x4]
                                          .sel_icon]
                                    .bound_r;
                        }
                    }

                    x = model->xC;
                    if (x > icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon]
                                    .bound_u -
                                1.5f)
                    {
                        model->xC = x - 0.02f;
                        if (model->xC >
                            icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon]
                                .bound_u)
                        {
                            model->xC =
                                icons[mnCharSel_803F0DFC.doors[model->x4]
                                          .sel_icon]
                                    .bound_u;
                        }
                    }

                    x = model->xC;
                    if (x <
                        1.5f +
                            icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon]
                                .bound_d)
                    {
                        model->xC += 0.02f;
                        if (model->xC <
                            icons[mnCharSel_803F0DFC.doors[model->x4].sel_icon]
                                .bound_d)
                        {
                            model->xC =
                                icons[mnCharSel_803F0DFC.doors[model->x4]
                                          .sel_icon]
                                    .bound_d;
                        }
                    }
                }
            }
        } else {
            model->x8 = 2.7f + mnCharSel_804A0BC0[status - 1]->xC;
            model->xC = -2.0f + mnCharSel_804A0BC0[model->x5 - 1]->x10;
        }
    }

    {
        f32 dx;
        f32 tx;
        f32 dy;

        dx = model->x10 - (tx = model->x8);
        dy = model->x14 - model->xC;

        if ((dx * dx + dy * dy) < 4.0f) {
            model->x10 = tx;
            model->x14 = model->xC;
        } else {
            f32 angle;
            if (dy < 0.01f && dy > -0.01f) {
                angle = (f32) (dx < 0.0f ? 1.5707963267948966
                                         : -1.5707963267948966);
            } else {
                angle = (f32) ((dy < 0.0f ? 0.0 : 3.141592653589793) +
                               atanf(dx / dy));
            }
            model->x10 = (3.0f * sinf(angle)) + model->x10;
            model->x14 = (3.0f * cosf(angle)) + model->x14;
        }
    }

    HSD_JObjSetTranslateX(jobj, model->x10);
    HSD_JObjSetTranslateY(jobj, model->x14);
    HSD_JObjSetTranslateZ(jobj, 1.0f);
    HSD_JObjAnimAll(jobj);
}

void fn_80262F44(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int i;
    PAD_STACK(0x8);

    if (mnCharSel_804D6CB0->match_type == VS_CAMERA) {
        if (HSD_PadCopyStatus[3].err != 0) {
            HSD_JObjClearFlagsAll(
                mnCharSel_804D6CCC == NULL ? NULL : mnCharSel_804D6CCC->child,
                JOBJ_HIDDEN);
            goto hide;
        }
        HSD_JObjSetFlagsAll(
            mnCharSel_804D6CCC == NULL ? NULL : mnCharSel_804D6CCC->child,
            JOBJ_HIDDEN);
    }

    if (mnCharSel_804D6CF5 == 1) {
        if (mnCharSel_804A0BC0[0]->x5 == 1 ||
            mnCharSel_803F0DFC.doors[0].sel_icon >= 0x19)
        {
            mnCharSel_804D6CF7 = 0;
        } else {
            mnCharSel_804D6CF7 = 1;
        }
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    } else {
        s32 valid_count = 0;

        for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
            if (mnCharSel_803F0DFC.doors[i].p_kind != 3) {
                if (mnCharSel_803F0DFC.doors[i].sel_icon >= 0x19) {
                    goto hide;
                }
                valid_count++;
            }
        }

        if (valid_count >= 2) {
            if (mnCharSel_804D6CB0->data.data.rules.is_teams == 1) {
                for (i = 0; i < (s32) (mnCharSel_804D6CF5 - 1); i++) {
                    s32 j;
                    if (mnCharSel_803F0DFC.doors[i].p_kind == 3) {
                        continue;
                    }
                    for (j = i; j < (s32) mnCharSel_804D6CF5; j++) {
                        if (mnCharSel_803F0DFC.doors[j].p_kind != 3 &&
                            mnCharSel_803F0DFC.doors[i].team !=
                                mnCharSel_803F0DFC.doors[j].team)
                        {
                            goto teams_ok;
                        }
                    }
                }
                goto hide;
            }
        teams_ok: {
            CSSTag* tag = mnCharSel_803F0E8C;
            for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
                if (mnCharSel_804A0BC0[i]->x5 == 1 || tag[i].data->state != 0)
                {
                    goto hide;
                }
            }
        }

            if (mnCharSel_804D6CF7 == 0) {
                HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjReqAnim, AOBJ_ARG_AF, 0.0);
            } else if (mnCharSel_804D6CF7 > 100) {
                HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjReqAnim, AOBJ_ARG_AF, 10.0);
                mnCharSel_804D6CF7 = 10;
            }
            mnCharSel_804D6CF7++;
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            HSD_JObjAnimAll(jobj);
        } else {
        hide:
            mnCharSel_804D6CF7 = 0;
            mnCharSel_804D6CF2 = 10;
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }

    {
        u32 p;
        u32 trigger;
        if (mnCharSel_804D6CF5 == 1) {
            trigger = HSD_PadCopyStatus[(u8) mnCharSel_804D6CF0].trigger;
        } else {
            trigger = (p = 0);
            for (trigger, i = 0; i < ((s32) mnCharSel_804D6CF5); i++, p++) {
                if (mnCharSel_804A0BC0[i]->x5 != 3) {
                    u8 tmp = p;
                    trigger |= HSD_PadCopyStatus[tmp].trigger;
                }
            }
        }

        if (mnCharSel_804D6CF2 == 0 && (trigger & HSD_PAD_START)) {
            if (mnCharSel_804D6CF7 != 0) {
                mnCharSel_804D6CF6 = 1;
                mnCharSel_804D6CF2 = 0xFF;
                if (mnCharSel_804D6CF5 == 1) {
                    if (gm_801677F8(mnCharSel_804D6CF0,
                                    mnCharSel_804D6CB0->data.data
                                        .players[mnCharSel_804D6CF0]
                                        .xA))
                    {
                        lb_80014574(mnCharSel_804D6CF0, 0, 0xB, 0x1E);
                    }
                } else {
                    for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
                        if (mnCharSel_803F0DFC.doors[i].p_kind == 0 &&
                            gm_801677F8(
                                i,
                                mnCharSel_804D6CB0->data.data.players[i].xA))
                        {
                            lb_80014574(i, 0, 0xB, 0x1E);
                        }
                    }
                }
            } else {
                lbAudioAx_80024030(3);
            }
        }
    }
}

void fn_80263354(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (mnCharSel_804D6CEC % 200 == 0) {
        HSD_JObjReqAnimAll(jobj, 0.0F);
    }
    HSD_JObjAnimAll(jobj);
}

/// Nametag list think callback - handles scrolling through nametag list

static const GXColor mnCharSel_804DC560 = { 255, 255, 255, 255 };
static const GXColor mnCharSel_804DC564 = { 100, 100, 100, 255 };

void fn_802633B0(HSD_GObj* gobj)
{
    HSD_JObj* list_jobj;
    HSD_JObj* arrow_jobj;
    UNUSED u8 unk7C[4];
    GXColor white;
    GXColor gray;
    HSD_JObj* list_origin_jobj;
    Point3d list_origin;
    GXColor gray_copy;
    GXColor row_color;
    GXColor used_row_color;
    GXColor white_copy;
    UNUSED u8 unk34[32];
    HSD_JObj* handicap_slider_jobj;
    CSSTagData* tag;
    int port;
    GXColor* name_color;
    s32 page;
    s32 new_page;
    GXColor* used_name_color;
    s32 val;
    s32 row;
    s32 j;
    s32 page_off;
    u8 match_type;
    u32 trigger;
    s32 num_entries;
    s32 i;
    f32 cursor_row;
    f32 vel;
    f32 scroll_pos;
    f32 new_pos;

    tag = gobj->user_data;
    port = tag->port;

    if (mnCharSel_804D6CF5 == 1) {
        if ((s32) port != 0) {
            port = mnCharSel_804D6CF1;
        } else {
            port = mnCharSel_804D6CF0;
        }
    }

    white = mnCharSel_804DC560;
    gray = mnCharSel_804DC564;
    num_entries = tag->next_tag;

    if (num_entries > 0x78U) {
        num_entries = num_entries - 8;
    } else {
        num_entries = num_entries - 7;
    }

    if (mnCharSel_804D6CF5 == 1) {
        lb_80011E24(mnCharSel_804D6CC0, &list_jobj, mnCharSel_803F0EBC.xc4,
                    -1);
        trigger = HSD_PadCopyStatus[(u8) mnCharSel_804D6CF0].trigger;
    } else {
        lb_80011E24(mnCharSel_804D6CC0, &list_jobj,
                    mnCharSel_803F0E8C[tag->port].x4, -1);
        trigger = HSD_PadCopyStatus[tag->port].trigger;
    }

    switch ((s32) tag->state) {
    case 1:
        mnCharSel_8025D1C4((s32) tag->port, 1);
        if (mnCharSel_803F0DFC.doors[tag->port].sel_icon < 0x19U) {
            if (lbLang_IsSavedLanguageUS() != 0 &&
                mnCharSel_803F0DFC.doors[tag->port].sel_icon == 0x16)
            {
                HSD_SisLib_803A70A0(tag->name_ls, 0,
                                    (char*) mnCharSel_803F0A48.gnw_name);
            } else {
                HSD_SisLib_803A70A0(
                    tag->name_ls, 0,
                    (char*) gm_80160980(
                        icons[mnCharSel_803F0DFC.doors[tag->port].sel_icon]
                            .char_kind));
            }
        } else {
            HSD_SisLib_803A70A0(tag->name_ls, 0,
                                "\x82\x6d\x82\x60\x82\x6c\x82\x64\x81\x40"
                                "\x82\x62\x82\x60\x82\x6d\x82\x62\x82\x64"
                                "\x82\x6b");
        }
        gray_copy = gray;
        HSD_SisLib_803A74F0(tag->text, 0, &gray_copy);
        HSD_ForeachAnim(list_jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, 0.0f);
        tag->state = 2;
        tag->timer = 0;
        sfxMove();
        return;

    case 2: {
        u32 t;
        t = tag->timer + 1;
        tag->timer = t;
        if (t > 0xAU) {
            HSD_ForeachAnim(list_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                            HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
            tag->name_ls->hidden = 0;
            tag->state = 3;
        }
        return;
    }
    case 3:
        vel = tag->scroll_amt;
        if (vel) {
            tag->scroll_force = (10.0f * vel) + (vel < 0.0f ? -1.0f : 1.0f);
        }
        if (tag->scroll_force) {
            scroll_pos = tag->x8;
            new_pos = scroll_pos + tag->scroll_force;
            page = (s32) (scroll_pos / 32.0f);
            tag->x8 = new_pos;
            new_page = (s32) (tag->x8 / 32.0f);
            if (tag->x8 > 0.0f) {
                tag->x8 = 0.0f;
            }
            if (tag->next_tag > 7U) {
                if (tag->x8 < -32.0f * (f32) num_entries) {
                    tag->x8 = -32.0f * (f32) num_entries;
                }
            } else {
                tag->x8 = 0.0f;
            }
            if (tag->scroll_amt == 0.0f) {
                if (page < new_page) {
                    tag->x8 = 32.0f * (f32) page;
                    tag->scroll_force = 0.0f;
                } else if (page > new_page) {
                    tag->x8 = 32.0f * (f32) new_page;
                    tag->scroll_force = 0.0f;
                }
            }
        }

        if (mnCharSel_804D6CF5 == 1) {
            lb_80011E24(mnCharSel_804D6CC0, &arrow_jobj,
                        mnCharSel_803F0EBC.xc7, -1);
        } else {
            lb_80011E24(mnCharSel_804D6CC0, &arrow_jobj,
                        mnCharSel_803F0E8C[tag->port].x7, -1);
        }

        if (tag->x8 == 0.0f) {
            HSD_JObjSetFlags(arrow_jobj, JOBJ_HIDDEN);
        } else {
            HSD_JObjClearFlags(arrow_jobj, JOBJ_HIDDEN);
        }

        if (mnCharSel_804D6CF5 == 1) {
            lb_80011E24(mnCharSel_804D6CC0, &arrow_jobj,
                        mnCharSel_803F0EBC.xc8, -1);
        } else {
            lb_80011E24(mnCharSel_804D6CC0, &arrow_jobj,
                        mnCharSel_803F0E8C[tag->port].kostar_text_joint, -1);
        }

        if (tag->next_tag > 7U) {
            if (tag->x8 == (-32.0f * (f32) num_entries)) {
                HSD_JObjSetFlags(arrow_jobj, JOBJ_HIDDEN);
            } else {
                HSD_JObjClearFlags(arrow_jobj, JOBJ_HIDDEN);
            }
        } else {
            HSD_JObjSetFlags(arrow_jobj, JOBJ_HIDDEN);
        }

        HSD_SisLib_803A746C(tag->name_ls, 0, 0.0f, tag->x8);
        HSD_SisLib_803A746C(tag->name_ls, 1, 0.0f,
                            (32.0f * (f32) tag->next_tag) + tag->x8);
        {
            int row_idx;
            name_color = &row_color;
            used_name_color = &used_row_color;
            page_off = ((s32) tag->x8 / 32) + 1;
            for (j = 0; j < 9; j++) {
                row_idx = j - page_off;
                if (row_idx < 0) {
                    HSD_SisLib_803A70A0(tag->name_ls, j + 2, NULL);
                } else {
                    HSD_SisLib_803A70A0(tag->name_ls, j + 2,
                                        GetNameText((s32) (u8) row_idx));
                    row_color = white;
                    HSD_SisLib_803A74F0(tag->name_ls, j + 2, name_color);
                    {
                        s32 p2;
                        for (p2 = 0; p2 < (s32) mnCharSel_804D6CF5; p2++) {
                            if (p2 != (s32) tag->port &&
                                (s32) mnCharSel_804D6CB0->data.data.players[p2]
                                        .xA == row_idx)
                            {
                                used_row_color = gray;
                                HSD_SisLib_803A74F0(tag->name_ls, j + 2,
                                                    used_name_color);
                                break;
                            }
                        }
                    }
                }
                HSD_SisLib_803A746C(tag->name_ls, j + 2, 10.0f,
                                    (32.0f * (f32) (j + 1)) +
                                        (f32) (((s32) tag->x8 % 32) - 0x20));
            }
        }

        if (trigger & HSD_PAD_A) {
            if (mnCharSel_804D6CF5 == 1) {
                lb_80011E24(mnCharSel_804D6CC0, &list_origin_jobj,
                            mnCharSel_803F0EBC.name_list_joint, -1);
            } else {
                lb_80011E24(mnCharSel_804D6CC0, &list_origin_jobj,
                            mnCharSel_803F0E8C[tag->port].list_joint, -1);
            }
            lb_8000B1CC(list_origin_jobj, NULL, &list_origin);
            cursor_row = 0.5f * (0.8f + (list_origin.y -
                                         mnCharSel_804A0BC0[tag->port]->x10)) -
                         (tag->x8 / 32.0f);
            row = (s32) cursor_row;

            if ((s32) cursor_row == 0) {
                if (lbLang_IsSavedLanguageUS() != 0 &&
                    mnCharSel_803F0DFC.doors[tag->port].sel_icon == 0x16)
                {
                    HSD_SisLib_803A70A0(tag->text, 0,
                                        (char*) mnCharSel_803F0A48.gnw_name);
                } else {
                    HSD_SisLib_803A70A0(
                        tag->text, 0,
                        (char*) gm_80160980(
                            icons[mnCharSel_803F0DFC.doors[tag->port].sel_icon]
                                .char_kind));
                }
                tag->text->default_kerning = 1;
                if (mnCharSel_803F0DFC.doors[tag->port].sel_icon < 0x19U) {
                    tag->text->hidden = 0;
                } else {
                    tag->text->hidden = 1;
                }
                {
                    if (mnCharSel_804D6CB0->data.data.players[port].xA != 0x78)
                    {
                        match_type = mnCharSel_804D6CB0->match_type;
                        if ((s32) match_type < 3) {
                            if ((s32) match_type == 0) {
                                goto clear;
                            }
                            goto no_clear;
                        }
                        if ((s32) match_type < 0xB) {
                        clear:
                            val = 1;
                        } else {
                        no_clear:
                            val = 0;
                        }
                        if (val != 0) {
                            mnCharSel_804D6CB0->ko_star_counts[tag->port] = 0;
                        }
                    }
                }
                mnCharSel_804D6CB0->data.data.players[port].xA = 0x78;
                tag->use_tag = 0;
                tag->state = 4;
                sfxMove();
                goto check_cancel;
            }

            if ((s32) tag->next_tag == row) {
                if (IsNameListFull() == 0) {
                    if (mnCharSel_804D6CF5 == 1) {
                        mnCharSel_804D6CF9 = mnCharSel_804D6CF0;
                    } else {
                        mnCharSel_804D6CF9 = (s8) tag->port;
                    }
                    mnCharSel_804D6CF6 = 4;
                    {
                        s32 k;
                        for (k = 0; k < (s32) mnCharSel_804D6CF5; k++) {
                            if ((mnCharSel_804A0BC0[k]->x5 == 1) &&
                                (mnCharSel_8025FDEC((u8) k) == 0))
                            {
                                mnCharSel_8025DB34((u8) k);
                                mnCharSel_804A0BC0[k]->x5 = 2;
                            }
                        }
                    }
                    return;
                }
                goto check_cancel;
            }

            if ((s32) tag->next_tag > row) {
                {
                    s32 p;
                    for (p = 0; p < (s32) mnCharSel_804D6CF5; p++) {
                        if (p != (s32) port &&
                            (s32) mnCharSel_804D6CB0->data.data.players[p]
                                    .xA == (s32) (row - 1))
                        {
                            goto check_cancel;
                        }
                    }
                    {
                        HSD_SisLib_803A70A0(tag->text, 0,
                                            GetNameText(row - 1));
                        tag->text->default_kerning = 0;
                        tag->text->hidden = 0;
                        {
                            if ((s32) mnCharSel_804D6CB0->data.data
                                    .players[port]
                                    .xA != (s32) (row - 1))
                            {
                                match_type = mnCharSel_804D6CB0->match_type;
                                if ((s32) match_type < 3) {
                                    if ((s32) match_type == 0) {
                                        goto clear2;
                                    }
                                    goto no_clear2;
                                }
                                if ((s32) match_type < 0xB) {
                                clear2:
                                    val = 1;
                                } else {
                                no_clear2:
                                    val = 0;
                                }
                                if (val != 0) {
                                    mnCharSel_804D6CB0
                                        ->ko_star_counts[tag->port] = 0;
                                }
                            }
                        }
                        mnCharSel_804D6CB0->data.data.players[port].xA =
                            row - 1;
                        tag->use_tag = 1;
                        tag->state = 4;
                        sfxMove();
                    }
                }
            }
        }
    check_cancel:
        if (trigger & HSD_PAD_B) {
            tag->state = 4;
            sfxBack();
            return;
        }
        break;

    case 4:
        HSD_ForeachAnim(list_jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjReqAnim,
                        AOBJ_ARG_AF, 20.0f);
        tag->name_ls->hidden = 1;
        if (gmMainLib_GetGameRules()->handicap != 0 && mnCharSel_804D6CF5 == 4)
        {
            {
                s32 hval;
                f32 hval_f;
                hval = getHandicapValue((int) tag->port);
                hval_f = (f32) hval;
                lb_80011E24(mnCharSel_804D6CC0, &handicap_slider_jobj,
                            mnCharSel_803F0DFC.doors[port].cpuslider_joint,
                            -1);
                {
                    HSD_JObj* anim_jobj = handicap_slider_jobj;
                    HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjReqAnim, AOBJ_ARG_AF, hval_f);
                }
                HSD_JObjAnimAll(handicap_slider_jobj);
                HSD_ForeachAnim(handicap_slider_jobj, JOBJ_TYPE, TOBJ_MASK,
                                HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                list_jobj = handicap_slider_jobj;
                hval = getHandicapValue((int) tag->port);
                hval_f = 1.25f * (f32) (hval - 1);
                HSD_JObjSetTranslateX(list_jobj, hval_f);
            }
        }
        tag->state = 5;
        tag->timer = 0;
        return;

    case 5: {
        u32 t2;
        t2 = tag->timer + 1;
        tag->timer = t2;
        if (t2 > 0xAU) {
            mnCharSel_8025D1C4((s32) tag->port, 2);
            white_copy = white;
            HSD_SisLib_803A74F0(tag->text, 0, &white_copy);
            tag->state = 0;
        }
        break;
    }
    }
    PAD_STACK(16);
}
void mnCharSel_80264070(void)
{
    mnCharSel_804D6CF4 = 1;
}

void fn_8026407C(HSD_GObj* gobj)
{
    HSD_FogSet(GET_FOG(gobj));
}

static const GXColor mnCharSel_804DC580 = { 255, 255, 0, 255 };
static const GXColor mnCharSel_804DC584 = { 20, 80, 160, 255 };
static const GXColor mnCharSel_804DC588 = { 60, 140, 80, 255 };
static const GXColor mnCharSel_804DC58C = { 160, 160, 0, 255 };
static const GXColor mnCharSel_804DC590 = { 180, 80, 0, 255 };
static const GXColor mnCharSel_804DC594 = { 220, 0, 0, 255 };

#define MODELS ((CSSSceneModels*) mnCharSel_804D6CB4)
#define ANIM ((CSSAnimSet*) mnCharSel_804D6CD8)

s32 mnCharSel_802640A0(void)
{
    HSD_JObj* sp108;
    UNUSED u8 unkF8[16];
    Point3d spEC;
    GXColor spE8;
    GXColor spE4;
    GXColor spE0;
    GXColor spDC;
    GXColor hard_color;
    GXColor spD4;
    GXColor color;
    GXColor color2;
    GXColor color3;
    GXColor color4;
    GXColor color5;
    GXColor color6;
    GXColor color7;
    UNUSED u8 unkA8[0x10];
    s32 row_b;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_Text* text;
    s32 ctx;
    s32 found;
    s32 num_players;
    s32 row_a;
    GXColor* color_ptr;
    GXColor* color2_ptr;
    s32 i;
    s32 slot;
    s32 icon;
    u8 match_type = mnCharSel_804D6CB0->match_type;

    if (match_type != 0) {
        lbAudioAx_800237A8(mnCharSel_803F0A48.mode_info[match_type].enter_sfx,
                           0x7F, 0x40);
    } else {
        switch (gmMainLib_GetGameRules()->mode) {
        case 0:
            lbAudioAx_800237A8(0x7535, 0x7F, 0x40);
            break;
        case 1:
            lbAudioAx_800237A8(0x7538, 0x7F, 0x40);
            break;
        case 2:
            lbAudioAx_800237A8(0x7537, 0x7F, 0x40);
            break;
        case 3:
            lbAudioAx_800237A8(0x7536, 0x7F, 0x40);
            break;
        }
    }

    mnCharSel_804D6CE0 = NULL;
    mnCharSel_804D6CDC = NULL;
    mnCharSel_804D6CE8 = NULL;
    mnCharSel_804D6CE4 = NULL;
    mnCharSel_804D6CF2 = 0x1E;
    mnCharSel_804D6CF3 = 0;
    {
        u8* mt_p = &mnCharSel_804D6CB0->match_type;

        if (*mt_p >= 0xBU) {
            mnCharSel_804D6CF5 = 1;
            num_players = 1;
        } else {
            mnCharSel_804D6CF5 = 4;
            num_players = 4;
        }
        if (*mt_p == TRAINING_MODE) {
            num_players = 2;
        }
    }
    mnCharSel_804D6CF6 = 0;
    if (mnCharSel_804D6CF5 == 1 && mnCharSel_804D6CF0 < 0) {
        mnCharSel_804D6CF0 = 0;
    }
    if (mnCharSel_804D6CF0 == 0) {
        mnCharSel_804D6CF1 = 1;
    } else {
        mnCharSel_804D6CF1 = 0;
    }

    if ((u8) mnCharSel_804D6CF4 != 0) {
        mnCharSel_804D6CF4 = 0;
        for (i = 0; i < num_players; i++) {
            mnCharSel_804D6CB0->data.data.players[i].handicap = 9;
        }
    }

    gobj = mnCharSel_804D6CB8 = GObj_Create(2, 3, 0x80);
    {
        HSD_CObj* cobj;
        cobj = HSD_CObjLoadDesc(MenMain_cam = MODELS->cam);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, cobj);
    }
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
    gobj->gxlink_prios = 0x1F;
    HSD_GObj_SetupProc(gobj, mn_8022BA1C, 5);
    ctx = HSD_SisLib_803A611C(0, gobj, 7, 8, 0x80, 1, 0x80, 0);

    gobj = GObj_Create(3, 4, 0x80);
    {
        HSD_LObj* lobj0 = HSD_LObjLoadDesc(MODELS->light0);
        HSD_LObj* lobj1 = HSD_LObjLoadDesc(MODELS->light1);
        HSD_LObjSetNext(lobj0, lobj1);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_LightKind, lobj0);
    }
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0x80);

    gobj = GObj_Create(0xE, 2, 0);
    {
        HSD_Fog* fog = HSD_FogLoadDesc(MODELS->fog);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_FogKind, fog);
    }
    GObj_SetupGXLink(gobj, (GObj_RenderFunc) (Event) fn_8026407C, 0, 0x80);

    gobj = GObj_Create(4, 5, 0x80);
    jobj = HSD_JObjLoadJoint(ANIM[0].joint);
    HSD_JObjAddAnimAll(jobj, ANIM[0].anim, ANIM[0].matanim, ANIM[0].shapeanim);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 1, 0x80);
    HSD_GObj_SetupProc(gobj, fn_80263354, 4);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);

    mnCharSel_804D6CBC = GObj_Create(4, 5, 0x80);
    if (mnCharSel_804D6CF5 == 1) {
        mnCharSel_804D6CC0 = HSD_JObjLoadJoint(ANIM[6].joint);
        HSD_JObjAddAnimAll(mnCharSel_804D6CC0, ANIM[6].anim, ANIM[6].matanim,
                           ANIM[6].shapeanim);
    } else {
        mnCharSel_804D6CC0 = HSD_JObjLoadJoint(ANIM[3].joint);
        HSD_JObjAddAnimAll(mnCharSel_804D6CC0, ANIM[3].anim, ANIM[3].matanim,
                           ANIM[3].shapeanim);
    }
    {
        u8 obj_kind = HSD_GObj_JObjKind;
        HSD_GObjObject_80390A70(mnCharSel_804D6CBC, obj_kind,
                                mnCharSel_804D6CC0);
    }
    GObj_SetupGXLink(mnCharSel_804D6CBC, HSD_GObj_JObjCallback, 1, 0x80);
    HSD_GObj_SetupProc(mnCharSel_804D6CBC, fn_8025F0E0, 4);
    HSD_JObjReqAnimAll(mnCharSel_804D6CC0, 0.0f);
    HSD_JObjAnimAll(mnCharSel_804D6CC0);
    HSD_ForeachAnim(mnCharSel_804D6CC0, JOBJ_TYPE, ALL_TYPE_MASK,
                    HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);

    if (gm_IsCKindUnlocked(CKIND_LUIGI) == 0) {
        row_a = 2;
        row_b = 0x13;
    } else {
        row_a = 0x13;
        row_b = 2;
    }
    if (mnCharSel_804D6CF5 == 1) {
        lb_80011E24(mnCharSel_804D6CC0, &sp108, icons[row_a].joint_id_1p, -1);
    } else {
        lb_80011E24(mnCharSel_804D6CC0, &sp108, icons[row_a].joint_id_vs, -1);
    }
    HSD_JObjSetTranslateY(sp108, ICONROWY_BTM);
    icons[row_a].bound_u = ICONROWHT_BTM_TOP;
    icons[row_a].bound_d = ICONROWHT_BTM_BTM;
    if (mnCharSel_804D6CF5 == 1) {
        lb_80011E24(mnCharSel_804D6CC0, &sp108, icons[row_b].joint_id_1p, -1);
    } else {
        lb_80011E24(mnCharSel_804D6CC0, &sp108, icons[row_b].joint_id_vs, -1);
    }
    HSD_JObjSetTranslateY(sp108, ICONROWY_TOP);
    icons[row_b].bound_u = ICONROWHT_TOP_TOP;
    icons[row_b].bound_d = ICONROWHT_MID_TOP;

    for (icon = 0; icon < 0x19; icon++) {
        icons[icon].state = gm_IsCKindUnlocked(icons[icon].char_kind);
        icons[icon].anim_timer = 0;
        if (mnCharSel_804D6CF5 == 1) {
            lb_80011E24(mnCharSel_804D6CC0, &sp108, icons[icon].joint_id_1p,
                        -1);
        } else {
            lb_80011E24(mnCharSel_804D6CC0, &sp108, icons[icon].joint_id_vs,
                        -1);
        }
        switch (icon) {
        case 0:
        case 8:
        case 9:
        case 17:
        case 18:
        case 24:
            if (icons[icon].state == 0) {
                HSD_JObjSetFlags(sp108, JOBJ_HIDDEN);
            } else {
                sp108 = HSD_JObjGetParent(sp108);
                icons[icon].state = 2;
                {
                    HSD_JObj* anim_jobj = sp108;
                    HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                    HSD_AObjReqAnim, AOBJ_ARG_AF, 20.0);
                }
                HSD_JObjAnimAll(sp108);
            }
            break;
        default:
            if (icons[icon].state == 0) {
                HSD_ForeachAnim(sp108, JOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjReqAnim, AOBJ_ARG_AF, 30.0);
                HSD_JObjAnimAll(sp108);
            } else {
                icons[icon].state = 2;
            }
            break;
        }
    }

    {
        u8 mt = mnCharSel_804D6CB0->match_type;
        if (mt >= 0xFU && mt <= 0x16U) {
            gobj = GObj_Create(4, 5, 0x80);
            mnCharSel_804D6CC8 = HSD_JObjLoadJoint(ANIM[7].joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind,
                                    mnCharSel_804D6CC8);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 1, 0x80);
            HSD_GObj_SetupProc(gobj, fn_8025FB2C, 4);
            HSD_JObjAddAnimAll(mnCharSel_804D6CC8, ANIM[7].anim,
                               ANIM[7].matanim, ANIM[7].shapeanim);
            HSD_JObjReqAnimAll(mnCharSel_804D6CC8, 0.0f);
            HSD_ForeachAnim(mnCharSel_804D6CC8, JOBJ_TYPE, ALL_TYPE_MASK,
                            HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
        }
    }

    if (mnCharSel_804D6CB0->match_type == 0x17) {
        u8 ck;
        gobj = GObj_Create(4, 5, 0x80);
        mnCharSel_804D6CC4 = HSD_JObjLoadJoint(ANIM[8].joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, mnCharSel_804D6CC4);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 1, 0x80);
        HSD_GObj_SetupProc(gobj, fn_8025FB2C, 4);
        HSD_JObjAddAnimAll(mnCharSel_804D6CC4, ANIM[8].anim, ANIM[8].matanim,
                           ANIM[8].shapeanim);
        HSD_JObjReqAnimAll(mnCharSel_804D6CC4, 0.0f);
        HSD_ForeachAnim(mnCharSel_804D6CC4, JOBJ_TYPE, ALL_TYPE_MASK,
                        HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
        ck = mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF1].c_kind;
        if ((s8) ck >= CKIND_PLAYABLE_COUNT || gm_IsCKindUnlocked(ck) == 0) {
            u8* char_kinds;
            s32 icon_off;
            do {
                i = HSD_Randi(0x19);
            } while (icons[i].state == 0);
            char_kinds = &icons[0].char_kind;
            icon_off = getIconOffset(i);
            mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF1].c_kind =
                char_kinds[icon_off];
            mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF1].color =
                HSD_Randi((s32) gm_80169238(char_kinds[icon_off]));
        }
    }

    if (mnCharSel_804D6CB0->match_type == 1) {
        gobj = GObj_Create(4, 5, 0x80);
        mnCharSel_804D6CCC = HSD_JObjLoadJoint(ANIM[5].joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, mnCharSel_804D6CCC);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
        HSD_GObj_SetupProc(gobj, fn_8025FAC0, 4);
        HSD_JObjAddAnimAll(mnCharSel_804D6CCC, ANIM[5].anim, ANIM[5].matanim,
                           ANIM[5].shapeanim);
        HSD_JObjReqAnimAll(mnCharSel_804D6CCC, 0.0f);
    }

    for (i = mnCharSel_804D6CF5 - 1; i >= 0; i--) {
        HSD_GObj* cursor_gobj;
        struct CSSCursorData* cursor;
        cursor_gobj = GObj_Create(4, 5, 0x80);
        jobj = HSD_JObjLoadJoint(ANIM[1].joint);
        cursor = HSD_MemAlloc(sizeof(*cursor));
        HSD_GObjObject_80390A70(cursor_gobj, HSD_GObj_JObjKind, jobj);
        GObj_SetupGXLink(cursor_gobj, HSD_GObj_JObjCallback, 3, 0x80);
        HSD_GObj_SetupProc(cursor_gobj, mnCharSel_CursorThink, 1);
        GObj_InitUserData(cursor_gobj, 4, HSD_Free, cursor);
        HSD_JObjAddAnimAll(jobj, ANIM[1].anim, ANIM[1].matanim,
                           ANIM[1].shapeanim);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjStopAnim,
                        AOBJ_ARG_AOV, 0, 0);
        mnCharSel_804A0BC0[i] = cursor;
        cursor->gobj = cursor_gobj;
        cursor->x4 = i;
        cursor->x8 = 0;
        cursor->xA = 0;
        cursor->x7 = 0;
        cursor->x6 = 0;
        cursor->x5 = 2;
        cursor->xC = (f32) ((15.0f * (f32) i) - 31.0f);
        cursor->x10 = -21.5f;
    }

    for (i = 0, slot = 0; i < num_players; i++, slot++) {
        {
            HSD_GObj* model_gobj = GObj_Create(4, 5, 0x80);
            jobj = HSD_JObjLoadJoint(ANIM[2].joint);
            {
                int player;
                struct CSSCharModel* model = HSD_MemAlloc(sizeof(*model));
                HSD_GObjObject_80390A70(model_gobj, HSD_GObj_JObjKind, jobj);
                GObj_InitUserData(model_gobj, 4, HSD_Free, model);
                GObj_SetupGXLink(model_gobj, HSD_GObj_JObjCallback, 2, 0x80);
                HSD_GObj_SetupProc(model_gobj, fn_80262648, 2);
                HSD_JObjAddAnimAll(jobj, ANIM[2].anim, ANIM[2].matanim,
                                   ANIM[2].shapeanim);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                {
                    HSD_JObj* anim_jobj = jobj;
                    HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                }
                mnCharSel_804A0BD0[slot] = model;
                model->gobj = model_gobj;
                model->x4 = i;
                model->x5 = 0;
                model->x6 = 0xFF;
                model->x7 = 0;
                if (mnCharSel_804D6CF5 == 1) {
                    if (i != 0) {
                        player = mnCharSel_804D6CF1;
                    } else {
                        player = mnCharSel_804D6CF0;
                    }
                } else {
                    player = i;
                }
                for (found = 0; found < 0x19; found++) {
                    if (mnCharSel_804D6CB0->data.data.players[player].c_kind ==
                            icons[found].char_kind &&
                        gm_IsCKindUnlocked(
                            mnCharSel_804D6CB0->data.data.players[player]
                                .c_kind) != 0)
                    {
                        break;
                    }
                }
                if (found >= 0x19) {
                    u8* slot_type;
                    mnCharSel_804D6CB0->data.data.players[player].c_kind =
                        CKIND_PLAYABLE_COUNT;
                    slot_type = &mnCharSel_804D6CB0->data.data.players[player]
                                     .slot_type;
                    if (*slot_type == 1) {
                        *slot_type = 3;
                    }
                }
                mnCharSel_803F0DFC.doors[slot].sel_icon = found;
                model->x8 = model->x10 = 3.4f + icons[found].bound_l;
                model->xC = model->x14 = -3.0f + icons[found].bound_u;
            }
        }
    }

    spE8 = mnCharSel_804DC580;
    for (i = 0; i < num_players; i++) {
        CSSTagData* td;
        int player;
        s32 found;
        gobj = GObj_Create(4, 5, 0x80);
        td = HSD_MemAlloc(sizeof(*td));
        mnCharSel_803F0E8C[i].data = td;
        GObj_InitUserData(gobj, 4, HSD_Free, td);
        HSD_GObj_SetupProc(gobj, fn_802633B0, 4);
        td->use_tag = 0;
        td->timer = 0;
        td->state = 0;
        td->x8 = 0.0f;
        td->scroll_amt = 0.0f;
        td->scroll_force = 0.0f;
        td->port = i;
        td->text = HSD_SisLib_803A6754(0, ctx);
        td->text->x4C = 1;
        td->text->default_fitting = 1;
        td->text->default_alignment = 1;
        text = td->text;
        text->font_size.x = 0.058f;
        text->font_size.y = 0.055f;
        if (mnCharSel_804D6CF5 == 1) {
            if (i != 0) {
                text = td->text;
                text->pos_x = 15.6f;
                text->pos_y = 20.2f;
                text->pos_z = 0.0f;
            } else {
                HSD_JObj* spA4;
                u8 tag_box_joint = mnCharSel_803F0EBC.tag_box_joint;
                lb_80011E24(mnCharSel_804D6CC0, &spA4, tag_box_joint, -1);
                {
                    HSD_JObj* anim_jobj = spA4;
                    HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, JOBJ_MASK,
                                    HSD_AObjReqAnim, AOBJ_ARG_AF, 2.0);
                }
                HSD_JObjAnimAll(spA4);
                {
                    HSD_JObj* anim_jobj = spA4;
                    HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, JOBJ_MASK,
                                    HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                }
                sp108 = spA4;
                lb_8000B1CC(sp108, NULL, &spEC);
                text = td->text;
                text->pos_x = spEC.x - 0.1f;
                text->pos_y = 20.2f;
                text->pos_z = 0.0f;
            }
            text = td->text;
            text->box_size_x = 200.0f;
            text->box_size_y = 32.0f;
            HSD_SisLib_803A6B98(td->text, 100.0f, 0.0f,
                                "\x81\x45\x81\x45\x81\x45\x81\x45");
        } else {
            UNUSED u8 unkA0[4];
            HSD_JObj* tag_name_jobj;
            u8 name_joint = mnCharSel_803F0E8C[i].name_jointl;
            lb_80011E24(mnCharSel_804D6CC0, &tag_name_jobj, name_joint, -1);
            {
                HSD_JObj* anim_jobj = tag_name_jobj;
                HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, JOBJ_MASK,
                                HSD_AObjReqAnim, AOBJ_ARG_AF, 2.0);
            }
            HSD_JObjAnimAll(tag_name_jobj);
            {
                HSD_JObj* anim_jobj = tag_name_jobj;
                HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, JOBJ_MASK,
                                HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
            }
            sp108 = tag_name_jobj;
            lb_8000B1CC(sp108, NULL, &spEC);
            {
                f32 sx, sy, sz;
                sx = 0.5f + spEC.x;
                sy = -0.4f - spEC.y;
                sz = spEC.z;
                text = td->text;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text = td->text;
            text->box_size_x = 160.0f;
            text->box_size_y = 32.0f;
            HSD_SisLib_803A6B98(td->text, 80.0f, 0.0f,
                                "\x81\x45\x81\x45\x81\x45\x81\x45");
        }
        if (mnCharSel_804D6CF5 == 1) {
            lb_80011E24(mnCharSel_804D6CC0, &sp108,
                        mnCharSel_803F0EBC.name_list_joint, -1);
        } else {
            lb_80011E24(mnCharSel_804D6CC0, &sp108,
                        mnCharSel_803F0E8C[i].list_joint, -1);
            if (i == 3) {
                HSD_JObjSetTranslateX(sp108, 16.7f);
            }
        }
        lb_8000B1CC(sp108, NULL, &spEC);
        td->name_ls = HSD_SisLib_803A6754(0, ctx);
        td->name_ls->default_fitting = 1;
        text = td->name_ls;
        text->box_size_x = 154.0f;
        text->box_size_y = 256.0f;
        {
            f32 sx, sy, sz;
            sy = (0.8f - spEC.y) - 1.0f;
            sx = spEC.x - 0.6f;
            sz = spEC.z;
            text = td->name_ls;
            text->pos_x = sx;
            text->pos_y = sy;
            text->pos_z = sz;
        }
        text = td->name_ls;
        text->font_size.x = 0.065f;
        text->font_size.y = 0.065f;
        td->name_ls->x4E = 1;
        td->name_ls->hidden = 1;
        HSD_SisLib_803A6B98(td->name_ls, 0.0f, 0.0f,
                            "\x81\x45\x81\x45\x81\x45\x81\x45\x81\x45\x81\x45"
                            "\x81\x45\x81\x45\x81\x45\x81\x45\x81\x45");
        color_ptr = &color;
        *color_ptr = spE8;
        HSD_SisLib_803A74F0(td->name_ls, 0, color_ptr);
        HSD_SisLib_803A6B98(td->name_ls, 0.0f, 0.0f,
                            "\x82\x6d\x82\x60\x82\x6c\x82\x64\x20\x82\x64\x82"
                            "\x6d\x82\x73\x82\x71\x82\x78");
        color2_ptr = &color2;
        *color2_ptr = spE8;
        HSD_SisLib_803A74F0(td->name_ls, 1, color2_ptr);
        for (found = 0; found < 9; found++) {
            HSD_SisLib_803A6B98(td->name_ls, 10.0f, 0.0f,
                                "\x81\x45\x81\x45\x81\x45\x81\x45");
        }
        for (found = 0; found < 0x78; found++) {
            if (GetNameText((u8) found) == NULL) {
                break;
            }
        }
        td->next_tag = (u8) (found + 1);
        lb_80011E24(mnCharSel_804D6CC0, &sp108, mnCharSel_803F0E8C[i].x7, -1);
        HSD_JObjSetFlags(sp108, JOBJ_HIDDEN);
        lb_80011E24(mnCharSel_804D6CC0, &sp108,
                    mnCharSel_803F0E8C[i].kostar_text_joint, -1);
        if (td->next_tag > 7U) {
            HSD_JObjClearFlags(sp108, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlags(sp108, JOBJ_HIDDEN);
        }
        if (mnCharSel_804D6CF5 == 1) {
            if (i != 0) {
                player = mnCharSel_804D6CF1;
            } else {
                player = mnCharSel_804D6CF0;
            }
        } else {
            player = i;
        }
        if (player == mnCharSel_804D6CF9 && mnCharSel_804D6CF8 < td->next_tag)
        {
            u8 mt = mnCharSel_804D6CB0->match_type;
            s32 clear;
            if ((s32) mt < 3) {
                if ((s32) mt == 0) {
                    goto clear_tag_overflow;
                }
                goto no_clear_tag_overflow;
            }
            if ((s32) mt < 0xB) {
            clear_tag_overflow:
                clear = 1;
            } else {
            no_clear_tag_overflow:
                clear = 0;
            }
            if (clear != 0) {
                mnCharSel_804D6CB0->ko_star_counts[player] = 0;
            }
            mnCharSel_804D6CB0->data.data.players[player].xA =
                mnCharSel_804D6CF8 - 1;
            mnCharSel_804D6CF8 = td->next_tag;
        }
        if (((u8*)
                 mnCharSel_804D6CB0)[0x7A + player * sizeof(PlayerInitData)] !=
            0x78)
        {
            td->use_tag = 1;
            HSD_SisLib_803A70A0(
                td->text, 0,
                GetNameText(mnCharSel_804D6CB0->data.data.players[player].xA));
            td->text->default_kerning = 0;
        }
    }

    if (mnCharSel_804D6CF5 == 1) {
        switch (mnCharSel_804D6CB0->match_type) {
        case REG_CLASSIC:
        case REG_ADVENTURE:
        case REG_ALLSTAR:
            spE4 = mnCharSel_804DC584;
            spE0 = mnCharSel_804DC588;
            spDC = mnCharSel_804DC58C;
            hard_color = mnCharSel_804DC590;
            spD4 = mnCharSel_804DC594;
            {
                u8 cpu_level =
                    mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF0]
                        .cpu_level;
                mnCharSel_803F0EBC.cpu_level_shown = cpu_level;
                mnCharSel_803F0EBC.cpu_level = cpu_level;
            }
            mnCharSel_803F0EBC.cpu_slider_x = 124.0f;
            mnCharSel_803F0EBC.xd3 = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_803F0EBC.scroll_flag = 1;
            text = mnCharSel_803F0EBC.xd3;
            text->pos_x = -0.5f;
            text->pos_y = 9.0f;
            text->pos_z = 0.0f;
            text = mnCharSel_803F0EBC.xd3;
            text->box_size_x = 248.0f;
            text->box_size_y = 32.0f;
            text = mnCharSel_803F0EBC.xd3;
            text->font_size.x = 0.08f;
            text->font_size.y = 0.09f;
            mnCharSel_803F0EBC.xd3->x4E = 1;
            mnCharSel_803F0EBC.xd3->default_kerning = 1;
            mnCharSel_803F0EBC.xd3->default_alignment = 1;
            mnCharSel_803F0EBC.xd3->x4C = 1;
            HSD_SisLib_803A6B98(mnCharSel_803F0EBC.xd3, 0.0f, 0.0f,
                                "\x82\x75\x82\x64\x82\x71\x82\x78\x20\x82\x64"
                                "\x82\x60\x82\x72\x82\x78");
            color3 = spE4;
            HSD_SisLib_803A74F0(mnCharSel_803F0EBC.xd3, 0, &color3);
            HSD_SisLib_803A6B98(mnCharSel_803F0EBC.xd3, 0.0f, 0.0f,
                                "\x82\x64\x82\x60\x82\x72\x82\x78");
            color4 = spE0;
            HSD_SisLib_803A74F0(mnCharSel_803F0EBC.xd3, 1, &color4);
            HSD_SisLib_803A6B98(mnCharSel_803F0EBC.xd3, 0.0f, 0.0f,
                                "\x82\x6d\x82\x6e\x82\x71\x82\x6c\x82\x60\x82"
                                "\x6b");
            color5 = spDC;
            HSD_SisLib_803A74F0(mnCharSel_803F0EBC.xd3, 2, &color5);
            HSD_SisLib_803A6B98(mnCharSel_803F0EBC.xd3, 0.0f, 0.0f,
                                "\x82\x67\x82\x60\x82\x71\x82\x63");
            color6 = hard_color;
            HSD_SisLib_803A74F0(mnCharSel_803F0EBC.xd3, 3, &color6);
            HSD_SisLib_803A6B98(mnCharSel_803F0EBC.xd3, 0.0f, 0.0f,
                                "\x82\x75\x82\x64\x82\x71\x82\x78\x20\x82\x67"
                                "\x82\x60\x82\x71\x82\x63");
            color7 = spD4;
            HSD_SisLib_803A74F0(mnCharSel_803F0EBC.xd3, 4, &color7);
            HSD_GObjGXLink_803909D8(mnCharSel_803F0EBC.xd3->entity,
                                    mnCharSel_804D6CBC);
            {
                CSSData* css = mnCharSel_804D6CB0;
                if (css->match_type == 0xD) {
                    lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x34, -1);
                    HSD_JObjSetFlagsAll(sp108, JOBJ_HIDDEN);
                    lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x3D, -1);
                    HSD_JObjSetFlagsAll(sp108, JOBJ_HIDDEN);
                    lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x45, -1);
                    HSD_JObjSetFlagsAll(sp108, JOBJ_HIDDEN);
                    lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x46, -1);
                    {
                        HSD_JObj* hide_jobj = sp108;
                        HSD_JObjSetFlagsAll(hide_jobj, JOBJ_HIDDEN);
                    }
                    (void) ((u8*) mnCharSel_803F0EBC.xd3)[data2.stocks];
                } else {
                    UNUSED u8 unk74[0x20];
                    HSD_JObj* sp70;
                    data2.stocks =
                        css->data.data.players[mnCharSel_804D6CF0].stocks;
                    updateStockIcons(&data2, &sp70, 1);
                    num_players = data2.stocks;
                    mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF0]
                        .stocks = data2.stocks;
                }
            }
            lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x40, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CDC = text;
            {
                f32 sx, sy, sz;
                sx = 13.5f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            text->default_alignment = 2;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x42, -1);
            HSD_JObjSetFlags(sp108, JOBJ_HIDDEN);
            lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x41, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CE4 = text;
            {
                f32 sx, sy, sz;
                sx = 13.5f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            text->default_alignment = 2;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            {
                HSD_JObj* jobj43;
                lb_80011E24(mnCharSel_804D6CC0, &jobj43, 0x43, -1);
                HSD_ForeachAnim(jobj43, JOBJ_TYPE, TOBJ_MASK, HSD_AObjReqAnim,
                                AOBJ_ARG_AF, 0.0);
                HSD_JObjAnimAll(jobj43);
                HSD_ForeachAnim(jobj43, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                                AOBJ_ARG_AOV, 0, 0);
                sp108 = jobj43;
            }
            HSD_JObjSetFlags(sp108, JOBJ_HIDDEN);
            break;
        case STADIUM_TARGET:
            lb_80011E24(mnCharSel_804D6CC8, &sp108, 4, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CDC = text;
            {
                f32 sx, sy, sz;
                sx = 10.9f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->default_alignment = 2;
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CE0 = text;
            {
                f32 sx, sy, sz;
                sx = 11.6f + spEC.x;
                sz = spEC.z;
                sy = 0.3f - spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.06f;
            text->font_size.y = 0.045f;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            lb_80011E24(mnCharSel_804D6CC8, &sp108, 5, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CE4 = text;
            {
                f32 sx, sy, sz;
                sx = 10.9f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            text->default_alignment = 2;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CE8 = text;
            {
                f32 sx, sy, sz;
                sx = 11.6f + spEC.x;
                sz = spEC.z;
                sy = 0.3f - spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.06f;
            text->font_size.y = 0.045f;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            lb_80011E24(mnCharSel_804D6CC8, &sp108, 3, -1);
            HSD_JObjSetFlagsAll(sp108, JOBJ_HIDDEN);
            goto hide_extra;
        case STADIUM_HOMERUN:
            lb_80011E24(mnCharSel_804D6CC8, &sp108, 4, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CDC = text;
            {
                f32 sx, sy, sz;
                sx = 11.0f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            text->default_alignment = 2;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            text = HSD_SisLib_803A6754(0, ctx);
            {
                f32 sx, sy, sz;
                sx = 12.0f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            text->default_kerning = 1;
            if (lbLang_IsSavedLanguageJP() != 0) {
                HSD_SisLib_803A6B98(text, 0.0f, 0.0f, "\x82\x8d");
                HSD_SisLib_803A6B98(text, 0.0f, 35.0f, "\x82\x8d");
            } else {
                HSD_SisLib_803A6B98(text, 0.0f, 0.0f,
                                    "\x82\x65\x82\x94\x81\x44");
                HSD_SisLib_803A6B98(text, 0.0f, 35.0f,
                                    "\x82\x65\x82\x94\x81\x44");
            }
            lb_80011E24(mnCharSel_804D6CC8, &sp108, 5, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CE4 = text;
            {
                f32 sx, sy, sz;
                sx = 11.0f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            text->default_alignment = 2;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            goto hide_extra;
        case STADIUM_MULTIMAN_10:
        case STADIUM_MULTIMAN_100:
            lb_80011E24(mnCharSel_804D6CC8, &sp108, 4, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CDC = text;
            {
                f32 sx, sy, sz;
                sx = 10.9f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            text->default_alignment = 2;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CE0 = text;
            {
                f32 sx, sy, sz;
                sx = 11.6f + spEC.x;
                sz = spEC.z;
                sy = 0.3f - spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.06f;
            text->font_size.y = 0.045f;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            lb_80011E24(mnCharSel_804D6CC8, &sp108, 5, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CE4 = text;
            {
                f32 sx, sy, sz;
                sx = 10.9f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            text->default_alignment = 2;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CE8 = text;
            {
                f32 sx, sy, sz;
                sx = 11.6f + spEC.x;
                sz = spEC.z;
                sy = 0.3f - spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.06f;
            text->font_size.y = 0.045f;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            lb_80011E24(mnCharSel_804D6CC8, &sp108, 3, -1);
            HSD_JObjSetFlagsAll(sp108, JOBJ_HIDDEN);
            goto hide_extra;
        case STADIUM_3_MIN_MELEE:
        case STADIUM_15_MIN_MELEE:
        case STADIUM_ENDLESS_MELEE:
        case STADIUM_CRUEL_MELEE:
            lb_80011E24(mnCharSel_804D6CC8, &sp108, 4, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CDC = text;
            {
                f32 sx, sy, sz;
                sx = 16.0f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            text->default_alignment = 2;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            lb_80011E24(mnCharSel_804D6CC8, &sp108, 5, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CE4 = text;
            {
                f32 sx, sy, sz;
                sx = 16.0f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.07f;
            text->font_size.y = 0.055f;
            text->default_alignment = 2;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            goto hide_extra;
        case TRAINING_MODE:
            lb_80011E24(mnCharSel_804D6CC4, &sp108, 9, -1);
            lb_8000B1CC(sp108, NULL, &spEC);
            text = HSD_SisLib_803A6754(0, ctx);
            mnCharSel_804D6CDC = text;
            {
                f32 sx, sy, sz;
                sx = 10.0f + spEC.x;
                sz = spEC.z;
                sy = -spEC.y;
                text->pos_x = sx;
                text->pos_y = sy;
                text->pos_z = sz;
            }
            text->font_size.x = 0.13f;
            text->font_size.y = 0.055f;
            text->default_alignment = 2;
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, NULL);
            /* fallthrough */
        case EVENT_MATCH:
        hide_extra:
            lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x2E, -1);
            HSD_JObjSetFlagsAll(sp108, JOBJ_HIDDEN);
            lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x34, -1);
            HSD_JObjSetFlagsAll(sp108, JOBJ_HIDDEN);
            lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x3A, -1);
            HSD_JObjSetFlagsAll(sp108, JOBJ_HIDDEN);
            lb_80011E24(mnCharSel_804D6CC0, &sp108, 0x44, -1);
            HSD_JObjSetFlagsAll(sp108, JOBJ_HIDDEN);
            break;
        }
    } else {
        u8 mt;
        s32 clear;
        mnCharSel_803F0EBC.scroll_flag = 0;
        text =
            HSD_SisLib_803A5ACC(0, ctx, -12.0f, -23.3f, 0.0f, 450.0f, 32.0f);
        text->default_alignment = 1;
        text->default_kerning = 1;
        text->default_fitting = 1;
        text->font_size.x = 0.07f;
        text->font_size.y = 0.07f;
        HSD_SisLib_803A6368(text, 0x4A);
        mnCharSel_8025BD30();
        mt = mnCharSel_804D6CB0->match_type;
        if ((s32) mt < 3) {
            if ((s32) mt == 0) {
                goto clear_ko_stars;
            }
            goto no_clear_ko_stars;
        }
        if ((s32) mt < 0xB) {
        clear_ko_stars:
            clear = 1;
        } else {
        no_clear_ko_stars:
            clear = 0;
        }
        if (clear != 0) {
            for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
                lb_80011E24(mnCharSel_804D6CC0, &sp108,
                            ((CSSKOStar*) &data2.ko_stars)[i].joint, -1);
                lb_8000B1CC(sp108, NULL, &spEC);
                text = HSD_SisLib_803A5ACC(0, ctx, spEC.x, -spEC.y - 0.9f,
                                           spEC.z, 32.0f, 32.0f);
                ((CSSKOStar*) &data2.ko_stars)[i].text = text;
                text->font_size.x = 0.07f;
                text->font_size.y = 0.07f;
                mnCharSel_8025D1C4(i, 0);
            }
        } else {
            for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
                lb_80011E24(mnCharSel_804D6CC0, &sp108,
                            ((CSSKOStar*) &data2.ko_stars)[i].joint, -1);
                HSD_JObjSetFlagsAll(sp108, JOBJ_HIDDEN);
            }
        }
    }

    (void) ((u8*) text)[num_players];
    (void) icons[num_players];
    gobj = GObj_Create(4, 5, 0x80);
    jobj = HSD_JObjLoadJoint(ANIM[4].joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_GObj_SetupProc(gobj, fn_80262F44, 3);
    HSD_JObjAddAnimAll(jobj, ANIM[4].anim, ANIM[4].matanim, ANIM[4].shapeanim);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjStopAnim,
                    AOBJ_ARG_AOV, 0, 0);

    mnCharSel_804D6CF7 = 0;
    if (mnCharSel_804D6CF5 == 1) {
        mnCharSel_804D6CB0->data.data.players[3].slot_type = 3;
        mnCharSel_804D6CB0->data.data.players[2].slot_type = 3;
        mnCharSel_804D6CB0->data.data.players[1].slot_type = 3;
        mnCharSel_804D6CB0->data.data.players[0].slot_type = 3;
        mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF0].slot_type =
            0;
        mnCharSel_803F0DFC.doors[0].p_kind = 0;
        {
            CSSData* css = mnCharSel_804D6CB0;
            mnCharSel_803F0DFC.doors[0].costume =
                css->data.data.players[mnCharSel_804D6CF0].color;
            mnCharSel_803F0DFC.doors[0].sel_icon_prev =
                mnCharSel_803F0DFC.doors[0].sel_icon;
            if (css->match_type != 0x17) {
                goto doors_done;
            }
            css->data.data.players[mnCharSel_804D6CF1].slot_type = 1;
        }
        mnCharSel_803F0DFC.doors[1].p_kind = 1;
        mnCharSel_803F0DFC.doors[1].costume =
            mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF1].color;
        mnCharSel_803F0DFC.doors[1].sel_icon_prev =
            mnCharSel_803F0DFC.doors[1].sel_icon;
    doors_done:;
    } else {
        for (i = 0; i < (s32) mnCharSel_804D6CF5; i++) {
            GameRules* rules;
            mnCharSel_803F0DFC.doors[i].p_kind =
                mnCharSel_804D6CB0->data.data.players[i].slot_type;
            mnCharSel_803F0DFC.doors[i].costume =
                mnCharSel_804D6CB0->data.data.players[i].color;
            mnCharSel_803F0DFC.doors[i].p_kind_prev = 3;
            mnCharSel_803F0DFC.doors[i].slideranim_timer = 0;
            mnCharSel_803F0DFC.doors[i].dooranim_timer = 0;
            mnCharSel_803F0DFC.doors[i].is_hold_handicap_slider = 0;
            mnCharSel_803F0DFC.doors[i].is_hold_cpu_slider = 0;
            mnCharSel_803F0DFC.doors[i].sel_icon_prev =
                mnCharSel_803F0DFC.doors[i].sel_icon;
            rules = gmMainLib_GetGameRules();
            if (rules->handicap != 0) {
                s32 hval;
                lb_80011E24(mnCharSel_804D6CC0, &sp108,
                            mnCharSel_803F0DFC.doors[i].cpuslider_joint, -1);
                if (gmMainLib_GetGameRules()->handicap == 1) {
                    hval = (u8) gm_801685D4(
                        (u8) i, mnCharSel_804D6CB0->data.data.players[i].xA);
                } else {
                    hval =
                        (u8) mnCharSel_804D6CB0->data.data.players[i].handicap;
                }
                /* switch forces MWCC beq/b double-branch (not bne) */
                switch (hval) {
                case 0:
                    hval = 1;
                }
                {
                    f32 slider_x = 1.25f * (f32) (hval - 1);
                    HSD_JObjSetTranslateX(sp108, slider_x);
                }
                lb_80011E24(mnCharSel_804D6CC0, &sp108,
                            mnCharSel_803F0DFC.doors[i].cpuslider2_joint, -1);
            } else {
                lb_80011E24(mnCharSel_804D6CC0, &sp108,
                            mnCharSel_803F0DFC.doors[i].cpuslider_joint, -1);
            }
            {
                u8* cpu_level =
                    &mnCharSel_804D6CB0->data.data.players[i].cpu_level;
                if (*cpu_level == 0) {
                    *cpu_level = 1;
                }
            }
            HSD_JObjSetTranslateX(
                sp108,
                1.25f *
                    (f32) (mnCharSel_804D6CB0->data.data.players[i].cpu_level -
                           1));
        }
    }

    mnCharSel_8025EE8C(mnCharSel_804D6CB0->match_type);
    PAD_STACK(0x20);
    return lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

#undef MODELS
#undef ANIM

void mnCharSel_Scene_OnEnter(void* arg0)
{
    PAD_STACK(8);

    lb_8001C550();
    lb_8001D164(0);
    mnCharSel_804D6CB0 = (CSSData*) arg0;

    mnCharSel_804D6CF0 = mnCharSel_804D6CB0->unk_0x0 - 1;

    for (mnCharSel_804D6CF8 = 0; mnCharSel_804D6CF8 < 0x78;
         mnCharSel_804D6CF8++)
    {
        if (GetNameText(mnCharSel_804D6CF8) == NULL) {
            break;
        }
    }
    mnCharSel_804D6CF9 = -1;
    mnCharSel_804D6CF8++;

    mnCharSel_803F0DFC.doors[0].selected_since_load = 0;
    mnCharSel_803F0DFC.doors[1].selected_since_load = 0;
    mnCharSel_803F0DFC.doors[2].selected_since_load = 0;
    mnCharSel_803F0DFC.doors[3].selected_since_load = 0;

    lbAudioAx_80026F2C(0x12);

    lbAudioAx_8002702C(2, 8);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    if (lbLang_IsSavedLanguageJP() != 0) {
        mnCharSel_804D6CD0 = lbArchive_LoadArchive("MnSlChr.dat");
        mnCharSel_804D6CD4 = lbArchive_LoadArchive("MnExtAll.dat");
    } else {
        mnCharSel_804D6CD0 = lbArchive_LoadArchive("MnSlChr.usd");
        mnCharSel_804D6CD4 = lbArchive_LoadArchive("MnExtAll.usd");
    }
    mnCharSel_804D6CB4 = HSD_ArchiveGetPublicAddress(mnCharSel_804D6CD0,
                                                     "MnSelectChrDataTable");
    mnCharSel_804D6CD8 = (u8*) mnCharSel_804D6CB4 + 0x10;
    if (lbLang_IsSavedLanguageJP() != 0) {
        HSD_SisLib_803A62A0(0, "SdSlChr.dat", "SIS_SelCharData");
    } else {
        HSD_SisLib_803A62A0(0, "SdSlChr.usd", "SIS_SelCharData");
    }
    mnCharSel_804D6CF4 = 0;
    mnCharSel_802640A0();
}

void mnCharSel_Scene_OnFrame(void)
{
    int num_slots;
    u8 slot_type;
    struct GameCache* cache;
    int i;

    PAD_STACK(8);

    mnCharSel_804D6CEC += 1;
    if (mnCharSel_804D6CF6 <= 1) {
        cache = &lbDvd_GetPreloadCacheScene()->game_cache;
        if (mnCharSel_804D6CF5 == 1) {
            slot_type =
                mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF0]
                    .slot_type;
            if (!(slot_type != 0 && slot_type != 1) &&
                mnCharSel_804A0BD0[0]->x5 == 0)
            {
                cache->entries[0].char_id =
                    mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF0]
                        .c_kind;
                cache->entries[0].color =
                    mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF0]
                        .color;
            } else {
                cache->entries[0].char_id = CHKIND_NONE;
            }
            slot_type =
                mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF1]
                    .slot_type;
            if (!(slot_type != 0 && slot_type != 1)) {
                if (mnCharSel_804A0BD0[1]->x5 == 0) {
                    cache->entries[1].char_id =
                        mnCharSel_804D6CB0->data.data
                            .players[mnCharSel_804D6CF1]
                            .c_kind;
                    cache->entries[1].color = mnCharSel_804D6CB0->data.data
                                                  .players[mnCharSel_804D6CF1]
                                                  .color;
                } else {
                    cache->entries[1].char_id = CHKIND_NONE;
                }
            }
        } else {
            if (mnCharSel_804D6CB0->match_type == VS_CAMERA) {
                num_slots = 3;
            } else {
                num_slots = 4;
            }

            for (i = 0; i < num_slots; i++) {
                slot_type = mnCharSel_804D6CB0->data.data.players[i].slot_type;
                if (!(slot_type != 0 && slot_type != 1) &&
                    mnCharSel_804A0BD0[i]->x5 == 0)
                {
                    cache->entries[i].char_id =
                        mnCharSel_804D6CB0->data.data.players[i].c_kind;
                    cache->entries[i].color =
                        mnCharSel_804D6CB0->data.data.players[i].color;
                } else {
                    cache->entries[i].char_id = CHKIND_NONE;
                }
            }
        }
        lbDvd_80018254();
    }
    if (mn_8022F218() != 0) {
        sfxBack();
        lb_800145F4();
        mn_8022F138(1, 8);
        HSD_SisLib_803A5E70();
        mn_8022F268();
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
        return;
    }
    if (mnCharSel_804D6CF2 != 0) {
        mnCharSel_804D6CF2--;
    }
    switch (mnCharSel_804D6CF6) {
    case 1:
        for (i = 0; i < 4; i++) {
            if (mnCharSel_803F0DFC.doors[i].p_kind != 3 &&
                mnCharSel_804A0BD0[0]->x5 != 0)
            {
                mnCharSel_804D6CF6 = 0;
            }
        }
        if (mnCharSel_804D6CF6 != 0) {
            gm_801A4B60();
            if (mnCharSel_804D6CF5 == 4) {
                lbAudioAx_8002411C(0x147);
            }
            sfxForward();
        }
        break;
    case 2:
        gm_801A4B60();
        sfxBack();
        break;
    case 3:
        mn_8022F138(1, 8);
        HSD_SisLib_803A5E70();
        mn_80231804(mnCharSel_804D6CD4, 1);
        mnCharSel_804D6CF6 = 5;
        sfxForward();
        break;
    case 4:
        mn_8022F138(1, 8);
        HSD_SisLib_803A5E70();
        mnNameNew_EnterFromMnCharSel(mnCharSel_804D6CD4, mnCharSel_804D6CF9);
        mnCharSel_804D6CF6 = 5;
        sfxForward();
        break;
    }
}

void mnCharSel_Scene_OnExit(void* unused)
{
    int num_slots;
    u64 tmp;
    int i;
    u8 type;

    HSD_SisLib_803A5FBC();
    if (mnCharSel_804D6CD0 != NULL) {
        lbArchive_80016EFC(mnCharSel_804D6CD0);
        mnCharSel_804D6CD0 = NULL;
    }
    if (mnCharSel_804D6CD4 != NULL) {
        lbArchive_80016EFC(mnCharSel_804D6CD4);
        mnCharSel_804D6CD4 = NULL;
    }
    mnCharSel_804D6CB0->pending_scene_change = mnCharSel_804D6CF6;
    if (mnCharSel_804D6CF6 != 0) {
        return;
    }

    tmp = 0;
    if (mnCharSel_804D6CF5 == 1) {
        type = mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF0]
                   .slot_type;
        if ((type == Gm_PKind_Human || type == Gm_PKind_Cpu) &&
            mnCharSel_804A0BD0[0]->x5 == 0)
        {
            tmp |= lbAudioAx_80026E84(
                mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF0]
                    .c_kind);
        }
        type = mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF1]
                   .slot_type;
        if ((type == Gm_PKind_Human || type == Gm_PKind_Cpu) &&
            mnCharSel_804A0BD0[1]->x5 == 0)
        {
            tmp |= lbAudioAx_80026E84(
                mnCharSel_804D6CB0->data.data.players[mnCharSel_804D6CF1]
                    .c_kind);
        }
    } else {
        num_slots = mnCharSel_804D6CB0->match_type == VS_CAMERA ? 3 : 4;
        for (i = 0; i < num_slots; i++) {
            type = mnCharSel_804D6CB0->data.data.players[i].slot_type;
            if ((type == Gm_PKind_Human || type == Gm_PKind_Cpu) &&
                mnCharSel_804A0BD0[i]->x5 == 0)
            {
                tmp |= lbAudioAx_80026E84(
                    mnCharSel_804D6CB0->data.data.players[i].c_kind);
            }
        }
    }

    lbAudioAx_80026F2C(0x14);
    lbAudioAx_8002702C(4, tmp);
    lbAudioAx_80027168();
}

#include <melee/ft/forward.h>
#include <melee/mn/types.h>

extern u8 mnCharSel_804D5100;
extern u8 mnCharSel_804D5108;

static CSSData* volatile mnCharSel_804D6CB0;
static void* mnCharSel_804D6CB4;
static HSD_JObj* mnCharSel_804D6CC0;
static HSD_JObj* mnCharSel_804D6CC4;
static HSD_JObj* mnCharSel_804D6CC8;
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
static s8 mnCharSel_804D6CF4;
static u8 mnCharSel_804D6CF5; ///< number of (open? valid?) CSS doors
static u8 mnCharSel_804D6CF6;
static u8 mnCharSel_804D6CF8;
static s8 mnCharSel_804D6CF9;

// Can't be enum bc float, but reused values
#define ICONROWHT_TOP_TOP 20.0F
#define ICONROWHT_MID_TOP 13.0F
#define ICONROWHT_BTM_TOP 6.0F
#define ICONROWHT_BTM_BTM (-1.0F)

// Can't be enum bc float, but reused values
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
        ICONHUD_CAPTAIN, CKIND_CAPTAIN, ICONSTATE_TEMP, 0x00,
        ICONJOINT_CAPTAIN, ICONJOINT_CAPTAIN, 0x000000C2, ICONBNDS_COL7_L,
        ICONBNDS_COL8_L, ICONROWHT_TOP_TOP, ICONROWHT_MID_TOP },
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
        ICONJOINT_PICHU, 0x000000D2, -23.4, ICONBNDS_COL2_L,
        ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
      { // Pikachu -                        0x803F0D38
        ICONHUD_PIKACHU, CKIND_PIKACHU, ICONSTATE_TEMP, 0x00,
        ICONJOINT_PIKACHU, ICONJOINT_PIKACHU, 0x000000D3, ICONBNDS_COL2_L,
        ICONBNDS_COL3_L, ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM },
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
        ICONHUD_EMBLEM, CKIND_EMBLEM, ICONSTATE_UNLOCKED, 0x00,
        ICONJOINT_EMBLEM, ICONJOINT_EMBLEM, 0x000000DA, ICONBNDS_COL7_L,
        23.6, ICONROWHT_BTM_TOP, ICONROWHT_BTM_BTM }
};

static CSSDoorsData mnCharSel_803F0DFC = {
    { { 0x2E,
        0x33,
        0x38,
        0x85,
        0x29,
        0xA6,
        0x3D,
        0x41,
        0x40,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        -35.6,
        -28.6,
        -26.8,
        -21.0F },
      { 0x2F,
        0x34,
        0x39,
        0x8D,
        0x2A,
        0xA8,
        0x43,
        0x47,
        0x46,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        -19.4,
        -13.4,
        -11.4,
        -6.0F },
      { 0x30,
        0x35,
        0x3A,
        0x95,
        0x2B,
        0xAA,
        0x49,
        0x4D,
        0x4C,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        -4.2,
        2.2,
        3.5,
        9.4 },
      { 0x31, 0x36, 0x3B, 0x9D, 0x2C,  0xAC,  0x4F,  0x53,
        0x52, 0x00, 0x00, 0x00, 0x00,  0x00,  0x00,  0x00,
        0x00, 0x00, 0x00, 0x00, 11.0F, 17.0F, 19.0F, 24.6 } },
    { { NULL, 0x70, 0x73, 0x74, 0x72, 0x71 },
      { NULL, 0x75, 0x78, 0x79, 0x77, 0x76 },
      { NULL, 0x7A, 0x7D, 0x7E, 0x7C, 0x7B },
      { NULL, 0x7F, 0x82, 0x83, 0x81, 0x80 } },
    0,
    0,
    0,
    0,
    0x4A,
    0x4D,
    0x4E,
    0x4C,
    0x4B,
    0,
    0,
    0,
    0x2F,
    0x01,
    0,
    0,
    0.0F,
    -10.9,
    -4.2,
    12.5,
    19.6,
    -6.8,
    -12.1,
};

static struct CSSDoorsData2 data2 = {
    { 0x35, 0x39, 0x36, 0x38, 0x37 },
    -2.2,
    3.7,
    13.7,
    19.3,
    -12.4,
    -16.6,
    {
        { NULL, -22.5, 0x57 },
        { NULL,  -7.1, 0x5D },
        { NULL,   8.3, 0x63 },
        { NULL,  23.7, 0x69 },
    },
};

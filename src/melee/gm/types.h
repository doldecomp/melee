#ifndef MELEE_GM_TYPES_H
#define MELEE_GM_TYPES_H

#include <platform.h>
#include <placeholder.h>

#include "gm/forward.h" // IWYU pragma: export

#include <common_structs.h>

struct MinorScene {
    u8 idx;
    u8 preload;
    u16 flags;

    void (*Prep)(MinorScene*);
    void (*Decide)(MinorScene*);

    struct MinorSceneInfo {
        u8 class_id;
        void* unk_struct_0; // data passed to OnLoad callback
        void* unk_struct_1; // data passed to OnLeave callback
    } info;
};

struct MajorScene {
    u8 preload;
    u8 idx;

    void (*Load)(void);
    void (*Unload)(void);
    void (*Init)(void);

    MinorScene* minor_scenes;
}; // 803DACA4

struct MinorSceneHandler {
    u8 class_id;

    void (*OnFrame)(void);
    void (*OnLoad)(void*);
    void (*OnLeave)(void*);
    void (*unk_func)(void);
}; // 803DA920

typedef struct {
    u8 curr_major;
    u8 pending_major;
    u8 prev_major;
    u8 curr_minor;
    u8 prev_minor;
    u8 pending_minor;
} SceneNums;

typedef struct {
    SceneNums nums;
    SceneNums nums2;
    u8 pending;
    u8 x0D;
    u8 x0E;
    u8 x0F;
    u8 (*data)(void);
} GameState;
STATIC_ASSERT(sizeof(GameState) == 0x14);

struct sceneData {
    u32 a;
    u8 scene_id;
};

struct gmm_x1CB0 {
    u8 padding_x0[0x10 - 0x0];
    u8 x10[0x16 - 0x10];
    /* 0x1CC6 0x16 */ u8 saved_language;
    int unk;
    u8 padding_x16[0x1];
};

typedef union _UnkFlagStruct2 {
    struct {
        u16 b0 : 1;
        u16 b1 : 1;
        u16 b2 : 1;
        u16 b3 : 1;
        u16 b4 : 1;
        u16 b5 : 1;
        u16 b6 : 1;
        u16 b789 : 3;
        u16 b10_to_12 : 3;
        u16 b13_to_15 : 3;
    };
    u16 flags;
} UnkFlagStruct2;

struct gmm_x1F2C {
    u8 padding_x0[0x78];
    s8 x78;
    s8 x79;
    UnkFlagStruct x7A;
    s8 x7B;
    UnkFlagStruct2 x7C;
    s16 x7E;
    s8 x80;
    s8 x81;
    s8 x82;
    s8 x83;
    s32 x84;
    s32 x88;
    s32 x8C;
    s32 x90;
    s32 x94;
    s32 x98;
    s32 x9C;
    s16 xA0;
    s16 xA2;
    s32 xA4;
    s32 xA8;
};

struct gmm_x2FF8_inner {
    u8 padding[0x1A2];
    s8 x1A2;
    u8 padding_x1A2;
};

struct gmm_x2FF8 {
    struct gmm_x2FF8_inner inner[19];
};

struct GameRules {
    /* 0x00 */ u8 unk_x0;
    /* 0x01 */ u8 unk_x1;
    /* 0x02 */ u8 mode;
    /* 0x03 */ u8 time_limit;
    /* 0x04 */ u8 stock_count;
    /* 0x05 */ u8 handicap;
    /* 0x06 */ u8 damage_ratio;
    /* 0x07 */ u8 unk_x7;
    /* 0x08 */ u8 stock_time_limit;
    /* 0x09 */ u8 friendly_fire;
    /* 0x0A */ u8 pause;
    /* 0x0B */ u8 score_display;
    /* 0x0C */ u8 unk_xc;
    /* 0x0D */ char pad_D[3]; /* maybe part of unk_xc[4]? */
    /* 0x10 */ u8 unk_x10;
    /* 0x11 */ char pad_11[3]; /* maybe part of unk_x10[4]? */
    /* 0x14 */ s32 unk_14;     /* inferred */
}; /* size = 0x18 */
STATIC_ASSERT(sizeof(struct GameRules) == 0x18);

struct gmm_retval_ED98 {
    u8 padding[0xC];
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
};

struct gmm_retval_EDB0 {
    s32 x0;
    s32 x4;
};

struct gmm_retval_EDBC {
    s32 x0;
    s32 x4;
    s32 x8;
    u8 padding[0x4C - 0x8 - 4];
    s32 x4C[4];
    u8 padding_x4C[0xB0 - 0x4C - 4 * 4];
    s32 xB0[4];
    char pad_F0[0xB8];
};

struct gmm_x1868 {
    /* 0x0000 */ s32 x1868;
    /* 0x0004 */ u8 unk_4;
    /* 0x0005 */ char pad_5[3]; /* maybe part of unk_4[4]? */
    /* 0x0008 */ struct gmm_retval_ED98 unk_8;
    /* 0x0028 */ struct gmm_retval_EDB0 unk_28;
    /* 0x0030 */ struct gmm_retval_EDBC unk_30;
    /* 0x01A8 */ u8 unk_1A8;      /* inferred */
    /* 0x01A9 */ char pad_1A9[7]; /* maybe part of unk_1A8[8]? */
    /* 0x01B0 */ s32 x1A18;
    /* 0x01B4 */ s32 x1A1C;
    /* 0x01B8 */ s32 x1A20;
    /* 0x01BC */ s32 x1A24;
    /* 0x01C0 */ s32 x1A28;
    /* 0x01C4 */ s32 x1A2C;
    /* 0x01C8 */ s32 x1A30;
    /* 0x01CC */ s32 x1A34;
    /* 0x01D0 */ s32 x1A38;
    /* 0x01D4 */ s32 x1A3C;
    /* 0x01D8 */ s32 x1A40;
    /* 0x01DC */ s32 x1A44;
    /* 0x01E0 */ s32 x1A48;
    /* 0x01E4 */ s32 x1A4C;
    /* 0x01E8 */ s32 x1A50;
    /* 0x01EC */ s32 x1A54;
    /* 0x01F0 */ s32 x1A58;
    /* 0x01F4 */ s32 x1A5C;
    /* 0x01F8 */ s32 x1A60;
    /* 0x01FC */ s32 x1A64;
    /* 0x0200 */ s64 x1A68;
    /* 0x0208 */ s32 x1A70[4];
    /* 0x0218 */ u8 padding_x1A70[0xBC];
    /* 0x02D4 */ u8 x1B3C;
    /* 0x02D5 */ char pad_2D5[3]; /* maybe part of x1B3C[4]? */
    /* 0x02D8 */ u32 x1B40[3];
    /* 0x02E4 */ u32 x1B4C[3];
    /* 0x02F0 */ u32 x1B58[3];
    /* 0x02FC */ u8 padding_x1B58[0x1C];
    /* 0x0318 */ u32 x1B80[4];
    /* 0x0328 */ u8 padding_x1B80[0xF8];
    /* 0x0420 */ u32 x1C88[3];
    /* 0x042C */ u8 padding_x1C88[0x1C];
    /* 0x0448 */ struct gmm_x1CB0 x1CB0;
    /* 0x0468 */ s16 x1CD0;
    /* 0x046A */ s16 x1CD2;
    /* 0x046C */ s32 x1CD4;
    /* 0x0470 */ u8 padding_x1CD4[0x254];
    /* 0x06C4 */ struct gmm_x1F2C x1F2C[0x19];
    /* 0x1790 */ struct gmm_x2FF8 x2FF8[2];
}; /* size = 0x55E8 */

struct gmm_x0 {
    /* 0x0000 */ u8 language;
    /* 0x0001 */ u8 unk_1;
    /* 0x0002 */ char pad_2[0x37]; /* maybe part of x1[0x38]? */
    /* 0x0039 */ u8 x39[0xB];
    /* 0x0044 */ s32 unk_44;
    /* 0x0048 */ char pad_48[0x24]; /* maybe part of x44[0xA]? */
    /* 0x006C */ u32 unk_6C[4];
    /* 0x007C */ char pad_7C[0x4A0]; /* maybe part of x6C[0x4B]? */
    /* 0x051C */ s32 unk_51C;
    /* 0x0520 */ s16 unk_520;
    /* 0x0522 */ s16 unk_522;
    /* 0x0524 */ s16 unk_524;
    /* 0x0526 */ s16 unk_526;
    /* 0x0528 */ s32 unk_528;
    /* 0x052C */ s32 unk_52C;
    /* 0x0530 */ char pad_530[5]; /* maybe part of x52C[2]? */
    /* 0x0535 */ u8 unk_535;
    /* 0x0536 */ char pad_536[0x46]; /* maybe part of unk_535[0x47]? */
    /* 0x057C */ s32 unk_57C;
    /* 0x0580 */ char pad_580[4];
    /* 0x0584 */ M2C_UNK unk_584; /* inferred */
    /* 0x0588 */ s8 unk_588[4];   /* inferred */
    /* 0x0590 */ char pad_58B[4]; /* inferred */
    /* 0x0590 */ s8 unk_590;      /* inferred */
    /* 0x0591 */ char pad_591[3]; /* maybe part of unk_590[4]? */
    /* 0x0594 */ char unk_594;
    /* 0x0595 */ char pad_595[3]; /* maybe part of unk_594[4]? */
    /* 0x0598 */ char unk_598;
    /* 0x0599 */ char pad_599[1];
    /* 0x059A */ s16 unk_59A;
    /* 0x05A0 */ char pad_59C[0x12B4]; /* maybe part of x588[0x4B0]? */
    /* 0x1850 */ GameRules x1850;
    /* 0x1898 */ struct gmm_x1868 thing;
}; /* size = 0x6E80 */

struct Placeholder_8016AE38_flags_2 {
    /* +0:0 */ u8 x0_b0_b2 : 3;
    /* +0:3 */ u8 x0_b3 : 1;
    /* +0:4 */ u8 x0_b4 : 1;
    /* +0:5 */ u8 x0_b5 : 1;
    /* +0:6 */ u8 x0_b6 : 1;
    /* +0:7 */ u8 x0_b7 : 1;
    /* +1:0 */ u8 x1_b0 : 1;
    /* +1:1 */ u8 x1_b1 : 1;
    /* +1:2 */ u8 x1_b2 : 1;
    /* +1:3 */ u8 x1_b3 : 1;
    /* +1:4 */ u8 x1_b4 : 1;
    /* +1:5 */ u8 x1_b5 : 1;
    /* +1:6 */ u8 x1_b6 : 1;
    /* +1:7 */ u8 x1_b7 : 1;
    /* +2:0 */ u8 x2_b0 : 1;
    /* +2:1 */ u8 x2_b1 : 1;
    /* +2:2 */ u8 x2_b2 : 1;
    /* +2:3 */ u8 x2_b3 : 1;
    /* +2:4 */ u8 x2_b4 : 1;
    /* +2:5 */ u8 x2_b5 : 1;
    /* +2:6 */ u8 x2_b6 : 1;
    /* +2:7 */ u8 x2_b7 : 1;
};

struct lbl_8046B6A0_t {
    /* 0x0000 */ u8 unk_0;
    /* 0x0001 */ u8 unk_1;
    /* 0x0002 */ u8 unk_2;
    /* 0x0003 */ u8 unk_3;
    /* 0x0004 */ u32 unk_4;
    /* 0x0008 */ u32 unk_8;
    /* 0x000C */ u8 unk_C;
    /* 0x000D */ u8 unk_D;
    /* 0x000E */ u8 unk_E;
    /* 0x000F */ u8 unk_F;
    /* 0x0010 */ s32 unk_10;
    /* 0x0014 */ s32 unk_14;
    /* 0x0018 */ char pad_18[0xC]; /* maybe part of unk_14[4]? */
    /* 0x0024 */ s32 unk_24;
    /* 0x0028 */ s32 unk_28;
    /* 0x002C */ u16 unk_2C;
    /* 0x002E */ char pad_2E[6]; /* maybe part of unk_2C[4]? */
    /* 0x0034 */ f32 unk_34;
    /* 0x0038 */ char pad_38[0x2490]; /* maybe part of unk_34[0x925]? */
    /* 0x24C8 */ Placeholder_8016AE38_flags_2 unk24C8;
    /* 0x24CB */ char pad_24CB[1];
    /* 0x24CC:0 */ u8 unk_24CC_b0 : 1;
    /* 0x24CC:1 */ u8 unk_24CC_b1 : 1;
    /* 0x24CC:2 */ u8 unk_24CC_b2 : 1;
    /* 0x24CC:3 */ u8 unk_24CC_b3 : 1;
    /* 0x24CC:4 */ u8 unk_24CC_b4 : 1;
    /* 0x24CC:5 */ u8 unk_24CC_b5 : 1;
    /* 0x24CC:6 */ u8 unk_24CC_b6 : 1;
    /* 0x24CC:7 */ u8 unk_24CC_b7 : 1;
    /* 0x24CD:0 */ u8 unk_24CD_b0 : 1;
    /* 0x24CD:1 */ u8 unk_24CD_b1 : 1;
    /* 0x24CD:2 */ u8 unk_24CD_b2 : 1;
    /* 0x24CD:3 */ u8 unk_24CD_b3 : 1;
    /* 0x24CD:4 */ u8 unk_24CD_b4 : 1;
    /* 0x24CD:5 */ u8 unk_24CD_b5 : 1;
    /* 0x24CD:6 */ u8 unk_24CD_b6 : 1;
    /* 0x24CD:7 */ u8 unk_24CD_b7 : 1;
    /* 0x24CE */ u8 unk_24CE;
    /* 0x24CF */ char pad_24CF[1];
    /* 0x24D0 */ s8 unk_24D0;
    /* 0x24D1 */ char pad_24D1[2]; /* maybe part of unk_24D0[3]? */
    /* 0x24D3 */ s8 unk_24D3;
    /* 0x24D4 */ s8 unk_24D4;
    /* 0x24D5 */ char pad_24D5[1];
    /* 0x24D6 */ u16 unk_24D6;
    /* 0x24D8 */ char pad_24D8[0x10]; /* maybe part of unk_24D6[9]? */
    /* 0x24E8 */ u64 unk_24E8;
    /* 0x24F0 */ s32 unk_24F0;
    /* 0x24F4 */ char pad_24F4[4];
    /* 0x24F8 */ f32 unk_24F8;        /* inferred */
    /* 0x24FC */ char pad_24FC[0x2C]; /* maybe part of unk_24F8[0xC]? */
}; /* size = 0x2528 */
STATIC_ASSERT(sizeof(struct lbl_8046B6A0_t) == 0x2528);

struct datetime {
    u16 year;
    u8 month, day, hour, minute, second;
};

struct gmMainLib_8015ED8C_arg0_t {
    u8 pad[0x2ac];
    u8 id[0x24];
    struct {
        u8 unk0, unk1;
        u8 unkpad[4];
    } thing[11];
};

struct gm_8017DB6C_arg0_t {
    /* +0 */ u8 x0;
    /* +1 */ u8 x1;
    /* +2 */ u8 _1[0xC - 0x2];
};
STATIC_ASSERT(sizeof(struct gm_8017DB6C_arg0_t) == 0xC);

struct gmMainLib_8046B0F0_t {
    bool x0;
    bool x4; // reset switch pressed
    bool x8; // true = progressive, false = interlaced
    int xC, x10, x14;
};

extern struct gmMainLib_8046B0F0_t gmMainLib_8046B0F0;

struct gm_8016A92C_arg0_t {
    char pad_0[0x58];
    struct lbl_8046B668_t* x58;
};

#endif

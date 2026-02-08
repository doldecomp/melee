#ifndef MELEE_GM_TYPES_H
#define MELEE_GM_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "dolphin/types.h"

#include <melee/ft/forward.h>
#include <melee/gm/forward.h> // IWYU pragma: export
#include <melee/gr/forward.h>
#include <melee/pl/forward.h>
#include <melee/sc/forward.h>

#include <common_structs.h>
#include <melee/mn/types.h>

struct UnkMultimanData {
    u16 x0_0 : 1;
    u16 x2;
    int x4;
};

struct DebugGameOverData {
    /* 00 */ u32 x0;
    /* 04 */ int x4;
    /* 08 */ u32 x8;
    /* 0C */ int xC;
    /* 10 */ u32 ckind;
    /* 14 */ u8 slot;
    /* 15 */ u8 x15;
    /* 16 */ u16 x16;
    /* 18 */ u16 x18;
};

struct MinorScene {
    /* 00 */ u8 idx;
    /* 01 */ u8 preload;
    /* 02 */ u16 flags;

    /* 04 */ void (*Prep)(MinorScene*);
    /* 08 */ void (*Decide)(MinorScene*);

    struct MinorSceneInfo {
        /* 0C */ u8 class_id;
        /* 10 */ void* load_data;  ///< data passed to OnLoad callback
        /* 14 */ void* leave_data; ///< data passed to OnLeave callback
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
    /* +0 */ u8 item_freq;
    /* +1 */ u8 pad_x1[0x8 - 0x1];
    /* +8 */ u64 item_mask;
    /* +10 */ u8 rumble[4];
    /* +14 */ u8 sound_balance;
    /* +15 */ u8 deflicker;
    /* +16 */ u8 saved_language; /* 0x1CC6 */
    /* +18 */ u32 stage_mask;
    /* +1C */ u8 padding_x16[0x1];
};

struct FighterData {
    /* 0x00 */ u16 fighter_kos[25];
    /* 0x32 */ u8 padding_0x32[2];
    /* 0x34 */ u16 sd_count;
    /* 0x36 */ u8 padding_0x36[2];
    /* 0x38 */ u32 attacks_hit;
    /* 0x3C */ u32 attacks_total;
    /* 0x40 */ s32 damage_dealt;
    /* 0x44 */ s32 damage_taken;
    /* 0x48 */ s32 damage_recovered;
    /* 0x4C */ u16 peak_damage;
    /* 0x4E */ u16 match_count;
    /* 0x50 */ u16 victories;
    /* 0x52 */ u16 losses;
    /* 0x54 */ u32 play_time;
    /* 0x58 */ u32 total_player_count;
    /* 0x5C */ s32 walk_distance;
    /* 0x60 */ s32 run_distance;
    /* 0x64 */ s32 fall_distance;
    /* 0x68 */ s32 peak_height;
    /* 0x6C */ s32 coins_collected;
    /* 0x70 */ s32 coins_swiped;
    /* 0x74 */ s32 coins_lost;
    /* 0x78 */ s8 x78;
    /* 0x79 */ s8 x79;
    /* 0x7A */ UnkFlagStruct x7A;
    /* 0x7B */ s8 x7B;
    /* 0x7C */ struct {
        u16 b0 : 1;
        u16 b1 : 1;
        u16 b2 : 1;
        u16 b3 : 1;
        u16 b4 : 1;
        u16 b5 : 1;
        u16 b6 : 1;
        u16 b789 : 3;      ///< stocks
        u16 b10_to_12 : 3; ///< stocks
        u16 b13_to_15 : 3; ///< stocks
        s16 x7E;
        u8 x80;
        u8 x81;
        u8 x82;
        s8 x83;
        s32 x84;
        s32 x88;
        s32 x8C;
        s32 x90;
        u32 x94;
        s32 x98;
        s32 x9C;
        u16 xA0;
        u16 xA2;
        s32 xA4;
        s32 xA8;
    } x7C;
};

struct NameTagData {
    /* 0x000 */ u16 vs_kos[120];
    /* 0x0F0 */ u16 sd_count;
    /* 0x0F2 */ u8 padding_0xF2[2];
    /* 0x0F4 */ u32 attacks_hit;
    /* 0x0F8 */ u32 attacks_total;
    /* 0x0FC */ s32 damage_dealt;
    /* 0x100 */ s32 damage_taken;
    /* 0x104 */ s32 damage_recovered;
    /* 0x108 */ u16 peak_damage;
    /* 0x10A */ u16 match_count;
    /* 0x10C */ u16 victories;
    /* 0x10E */ u16 losses;
    /* 0x110 */ u32 play_time;
    /* 0x114 */ u32 total_player_count;
    /* 0x118 */ s32 walk_distance;
    /* 0x11C */ s32 run_distance;
    /* 0x120 */ s32 fall_distance;
    /* 0x124 */ s32 peak_height;
    /* 0x128 */ s32 coins_collected;
    /* 0x12C */ s32 coins_swiped;
    /* 0x130 */ s32 coins_lost;
    /* 0x134 */ u32 play_time_by_fighter[25];
    /* 0x198 */ char namedata[8];
    /* 0x1A0 */ s8 x1A0;
    /* 0x1A1 */ u8 x1A1;
    /* 0x1A2 */ s8 x1A2;
    /* 0x1A3 */ u8 padding_x1A2;
};

struct NameTagDataBank {
    struct NameTagData inner[19];
};

struct GameRules {
    /* 0x00 */ u8 force_main_menu;
    /* 0x01 */ u8 bgm;
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
    /* 0x0D */ u8 xD;
    /* 0x0E */ u8 xE;
    /* 0x0F */ u8 xF;
    /* 0x10 */ u8 unk_x10;
    /* 0x11 */ u8 x11;
    /* 0x12 */ u8 x12;
    /* 0x13 */ u8 x13;
    /* 0x14 */ s32 unk_14; /* inferred */
}; /* size = 0x18 */
STATIC_ASSERT(sizeof(struct GameRules) == 0x18);

struct gmm_retval_ED98 {
    u32 x0;
    u32 x4;
    u8 padding[0x4];
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
    u32 x4;
    s32 x8;
    u32 xC;
    int x10;
    u32 x14;
    u16 x18[2];
    u8 pad_x1C[0x4C - 0x1C];
    s32 x4C[4];
    u8 padding_x4C[0xB0 - 0x4C - 4 * 4];
    s32 xB0[0x19];
    int x114[0x19];
};

struct gmm_x1868 {
    /* 0x0000 */ u16 x1868; ///< unlocked characters bitmask
    /* 0x0002 */ u16 x186A; ///< unlocked stages bitmask
    /* 0x0004 */ u8 x186C;  ///< unlocked features bitmask - score
                            ///< display/random stage etc...
    /// @remarks this would make sense to be apart of x186C, but seems unused.
    // perhaps features got removed from the unlock system? item switch comes
    // to mind as plausible
    /* 0x0005 */ char pad_5[3];
    /* 0x0008 */ struct gmm_retval_ED98 unk_8;
    /* 0x0028 */ struct gmm_retval_EDB0 unk_28;
    /* 0x0030 */ struct gmm_retval_EDBC unk_30;
    struct gmm_x1868_1A8_t {
        /* 0x01A8 +0 */ u32 x0;
        /* 0x01AC +4 */ u8 x4; ///< true/false
        /* 0x01AD +5 */ u8 x5;
        /* 0x01AE +6 */ u8 x6;
    } unk_1A8;
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
    /* 0x01EC */ int x1A54;
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
    /* 0x06C4 */ struct FighterData x1F2C[0x19];
    /* 0x1760 */ struct NameTagDataBank x2FF8[2];
}; /* size = 0x55E8 */

struct gmm_x0 {
    /* 0x0000 */ u8 language;
    /* 0x0001 */ u8 unk_1;
    /* 0x0002 */ u8 unk_2;
    /* 0x0003 */ char pad_3[0x36]; /* maybe part of x1[0x38]? */
    /* 0x0039 */ u8 x39[0xB];
    /* 0x0044 */ s32 unk_44;
    /* 0x0048 */ char pad_48[0x24]; /* maybe part of x44[0xA]? */
    /* 0x006C */ u32 unk_6C[4];
    /* 0x007C */ char pad_7C[0x4A0]; /* maybe part of x6C[0x4B]? */
    struct gmm_x0_528_t {
        /* 0x0528 */ s8 c_kind;
        /* 0x0529 */ u8 stocks;
        /* 0x052A */ u8 color;
        /* 0x052B */ u8 cpu_level;
        /* 0x052C */ u8 x4; ///< nametag ID
        /* 0x052D */ u8 x5;
    } unk_51C, unk_522, unk_528;
    struct EventData {
        /* 0x0530 */ u8 x0;
        /* 0x0531 */ u8 x1;
        /* 0x0532 */ s8 x2;
        /* 0x0533 */ u8 x3;
        /* 0x0534 */ u8 x4;
        /* 0x0535 */ u8 unk_535;
        /* 0x0536 */ u8 x6;
        /* 0x0537 */ u8 x7;
        /* 0x0538 */ s8 x8;
        /* 0x0539 */ s8 x9;
        /* 0x053A */ s8 xA;
        /* 0x053B */ u8 xB_0 : 1;
        /* 0x053B */ u8 xB_1 : 1;
        /* 0x053B */ u8 xB_2 : 1;
        /* 0x053B */ u8 xB_3 : 1;
        /* 0x053B */ u8 xB_4 : 1;
        /* 0x053B */ u8 xB_5 : 1;
        /* 0x053B */ u8 xB_6 : 1;
        /* 0x053B */ u8 xB_7 : 1;
        /* 0x053C */ int xC;
        /* 0x0540 */ int x10;
        /* 0x0544 */ int x14;
        /* 0x0548 */ int x18;
        /* 0x054C */ float x1C;
        /* 0x0550 */ int x20;
        /* 0x0554 */ int x24;
        /* 0x0558 */ int x28;
        /* 0x055C */ int x2C; // timer seconds
        /* 0x0560 */ int x30;
        /* 0x0564 */ int x34;
        /* 0x0568 */ u8 x38;
        /* 0x056C */ int x3C;
        /* 0x0570 */ int x40;
        /* 0x0574 */ s8 x44;
        /* 0x0575 */ u8 x45;
        /* 0x0578 */ InternalStageId x48;
        /* 0x057C */ s8 x4C[4]; ///< CharacterKind
        /* 0x0580 */ u8 x50[4]; ///< character color
        struct gmm_x0_584_t {
            /* 0x0584 */ s8 unk_584;
            /* 0x0585 */ u8 unk_585;
            /* 0x0586 */ u8 unk_586;
            /* 0x0587 */ s8 unk_587;
        } unk_584;
        /* 0x0588 */ s8 unk_588[4];   /* inferred */
        /* 0x0590 */ char pad_58B[4]; /* inferred */
    } unk_530;
    /* 0x0590 */ VsModeData unk_590; ///< VS melee
    /* 0x06D0 */ VsModeData unk_6D0; ///< super sudden death
    /* 0x0810 */ VsModeData unk_810; ///< invisible melee
    /* 0x0950 */ VsModeData unk_950;
    /* 0x0A90 */ VsModeData unk_A90;  ///< fixed camera mode
    /* 0x0BD0 */ VsModeData unk_BD0;  ///< single button melee
    /* 0x0D10 */ VsModeData unk_D10;  ///< training mode
    /* 0x0E50 */ VsModeData unk_E50;  ///< tiny melee
    /* 0x0F90 */ VsModeData unk_F90;  ///< giant melee
    /* 0x10D0 */ VsModeData unk_10D0; ///< stamina melee
    /* 0x1210 */ VsModeData unk_1210; ///< slowmo melee
    /* 0x1350 */ VsModeData unk_1350; ///< lightning melee
    /* 0x1490 */ VsModeData unk_1490; ///< multiman, 3/15 min, endless, cruel
    /* 0x15D0 */ char pad_15D0[0x1710 - 0x15D0];
    /* 0x17C0 */ VsModeData unk_1710; ///< opening movie?
    /* 0x1850 */ GameRules x1850;
    /* 0x1898 */ struct gmm_x1868 thing;
}; /* size = 0x6E80 */

struct lbl_8046B6A0_24C_t {
    UNK_T x0;
    u8 x4;
    u8 x5; ///< match mode
    u8 is_teams;
    u32 x8;
    u8 xC;
    u8 xD;
    u8 xE;
    u8 padF[0x16 - 0xF];
    u8 x16;
    u8 pad17[0x24 - 0x17];
    struct {
        u8 x0;
        u8 pad_x1[0xB];
    } x24[1];
    u8 pad30[0x58 - 0x30];
    struct lbl_8046B6A0_24C_58_t {
        u8 x0;
        u8 x1;
        u8 x2;
        u8 x3;
        u8 x4;
        u8 x5;
        u8 x6;
        u8 x7;
        u8 pad8[0x20 - 8];
        u32 x20;
        u32 x24;
        u32 x28;
        u32 x2C;
        u8 pad60[0xA8 - 0x30];
    } x58[6];
    u8 pad3F0[0x44C - 0x3F0 - 0x58];
    struct lbl_8046B6A0_24C_44C_t {
        u8 x0[0x101];
        int x104[0x101];
    } x44C[6];
};

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
    /* 0x0001 */ s8 pauser;
    /* 0x0002 */ u8 pause_timer;
    /* 0x0003 */ u8 unk_3;
    /* 0x0004 */ u8 unk_4;
    /* 0x0005 */ u8 hud_enabled;
    /* 0x0006 */ u8 terminate_match;
    /* 0x0007 */ u8 is_singleplayer;
    /* 0x0008 */ u8 match_result;
    /* 0x0009 */ u8 unk_9;
    /* 0x000A */ u8 unk_A;
    /* 0x000B */ u8 unk_B; // end graphic / SFX type
    /* 0x000C */ u8 unk_C;
    /* 0x000D */ u8 unk_D;
    /* 0x000E */ u8 match_over;
    /* 0x000F */ u8 unk_F;
    /* 0x0010 */ s32 unk_10;
    /* 0x0014 */ s32 unk_14;
    /* 0x0018 */ u8 unk_18; /* maybe part of unk_14[4]? */
    /* 0x001C */ u32* unk_1C;
    /* 0x0020 */ u32* unk_20;
    /* 0x0024 */ u32 frame_count;
    /* 0x0028 */ u32 timer_seconds;
    /* 0x002C */ u16 unk_2C; ///< timer frames
    /* 0x002E */ u16 unk_2E;
    /* 0x0030 */ u8 unk_30;
    /* 0x0034 */ f32 unk_34;
    /* 0x0038 */ struct {
        u8 x0; ///< CharacterKind
        u8 x1;
        u8 slot_type;
        s8 spawn_point;
        u8 x4_b0 : 1; ///< metal
        u8 x4_b1 : 1;
        u8 x4_b2 : 1; ///< invisible
        u8 x4_b3 : 1;
        u8 x4_b4 : 1; ///< Zelda/Sheik transforming on load
        u8 x4_b5 : 1;
        u8 x4_b6 : 1;
        u8 x4_b7 : 1;
        u8 x5;
        u16 x6;
        u16 x8;
        u8 respawn_timer;
        u8 xB;
        u16 xC;
    } FighterMatchInfo[6];
    /* 0x0038 */ char pad_8C[0x24C - 0x8C]; /* maybe part of unk_34[0x925]? */
    /* 0x024C */ struct lbl_8046B6A0_24C_t x24C;
    /* 0x24C8 */ struct StartMeleeRules x24C8;
}; /* size = 0x2528 */
STATIC_ASSERT(sizeof(struct lbl_8046B6A0_t) == 0x2528);

struct datetime {
    u16 year;
    u8 month, day, hour, minute, second;
};

struct gmMainLib_8015EF30_s {
    /*  +0 */ s16 x0;
    /*  +2 */ s16 x2;
    /*  +4 */ s32 x4;
    /*  +8 */ s32 x8;
    /*  +C */ s32 xC;
    /*  +10 */ s32 x10;
    /*  +14 */ s32 x14;
    /*  +18 */ s16 x18;
    /*  +1A */ s16 x1A;
    /*  +1C */ s16 x1C;
    /*  +1E */ s16 x1E;
    /*  +20 */ s32 x20;
    /*  +24 */ s32 x24;
    /*  +28 */ s32 x28;
    /*  +2C */ s32 x2C;
    /*  +30 */ s32 x30;
    /*  +34 */ s32 x34;
    /*  +38 */ s32 x38;
    /*  +3C */ s32 x3C;
    /*  +40 */ s32 x40;
};

struct gm_8017DB6C_arg0_t {
    /* +0 */ u8 x0;
    /* +1 */ u8 x1;
    /* +2 */ u8 _1[0xC - 0x2];
};
STATIC_ASSERT(sizeof(struct gm_8017DB6C_arg0_t) == 0xC);

struct gmMainLib_8046B0F0_t {
    /* 00 */ bool x0;
    /* 04 */ bool resetting;   ///< reset switch pressed
    /* 08 */ bool progressive; ///< true = progressive, false = interlaced
    /* 0C */ bool xC;          // movie playback done, maybe?
    /* 10 */ int x10, x14;
};

extern struct gmMainLib_8046B0F0_t gmMainLib_8046B0F0;

typedef struct gm_803DF94C_t {
    void (*x0)(HSD_GObj*);
    void (*x4)(int);
} gm_803DF94C_t;

struct MatchTeamData {
    int score;
    int subscore;
    u8 is_big_loser;
    u8 is_small_loser;
    u8 active;
};

struct MatchPlayerData {
    u8 slot_type;
    s8 character_kind;
    s8 character_id;
    u8 x3 : 6;
    u8 x3_6 : 1;
    u8 x3_7 : 1;
    u8 x4;
    u8 is_big_loser;
    u8 is_small_loser;
    u8 team;
    s8 stocks;
    u8 x9;
    u16 self_destructs;
    u16 percent;
    u16 xE;
    u16 kills[4];
    u16 x18;
    s32 x1C;
    s32 x20;
    int x24;
    u32 x28;
    int score;
    u8 pad_x30[0x40 - 0x30];
    u32 x40;
    u32 x44;
    u32 x48;
    u32 x4C;
    u32 x50;
    u32 x54;
    u32 x58;
    u32 x5C;
    u32 x60;
    u32 x64;
    u32 x68;
    u32 x6C;
    u32 x70;
    u32 x74;
    u32 x78;
    u32 x7C;
    u32 x80;
    u32 x84;
    u32 x88;
    u32 x8C;
    u32 x90;
    u32 x94;
    u32 x98;
    int x9C;
    int xA0;
    u32 xA4;
};

struct MatchEnd {
    u32 x0; ///< timer
    u8 result;
    u8 x5;
    u8 is_teams;
    u8 x7;
    u32 frame_count;
    u8 xC;
    u8 n_winners;
    u8 n_team_winners;
    u8 loser;
    u8 winners[6];
    u8 team_winners[5];
    struct MatchTeamData team_standings[5];
    struct MatchPlayerData player_standings[6];
    u8 _x448[4];
    struct UnkResultPlayerData {
        u8 x0[0x100];
        char pad_x100[0x508 - 0x100];
    } x44C[4];
    u8 pad_x186C[0x227C - 0x186C];
};

struct MatchExitInfo {
    int x0;
    u32 x4; ///< remaining time shown on timer, in frames
    int x8;
    MatchEnd match_end;
};

struct ResultsMatchInfo {
    u8 x0_0 : 1;
    u8 x0_1 : 1;
    u8 x1;
    int x4;
    MatchEnd match_end;
};

struct Unk1PData {
    /* 00 */ s8 ckind;
    /* 01 */ u8 color;
    /* 02 */ u8 cpu_level;
    /* 03 */ u8 slot;
    /* 04 */ u8 x4;  //EntryName Slot
    /* 05 */ u8 stocks;
    /* 06 */ u8 x6;
    /* 07 */ u8 x7;
    /* 08 */ u8 x8;
    /* 09 */ u8 x9;
    /* 0A */ u8 xA;
    /* 0B */ u8 xB;
    /* 0C */ struct Unk1PData_xC {
        /* 0C */ u8 xC;
        /* 0D */ u8 xD;
        /* 0E */ u8 xE;
        /* 0F */ u8 xF;
        /* 10 */ u8 x10;
        /* 11 */ u8 x11;
        /* 12 */ u8 x12;
        /* 13 */ u8 x13;
        /* 14 */ u16 x14;
        /* 18 */ int x18;
        /* 1C */ int x1C;
        /* 20 */ u32 x20;
        struct Unk1PData_x24 {
            /* 24 */ s8 ckind;
            /* 28 */ int x4;
            /* 2C */ int x8;
        } x24[3];
    } xC;
};

struct UnkAdventureData {
    /* 00 */ Unk1PData x0;
    /* 48 */ UNK_T x48;
    /* 4C */ u8 (*x4C)(u8, u8, u8);
    /* 50 */ UNK_T x50;
    /* 54 */ UNK_T x54;
    /* 58 */ UNK_T x58;
    /* 5C */ UNK_T x5C;
    /* 60 */ UNK_T x60;
    /* 64 */ float (*x64)(u8, u8);
    /* 68 */ float (*x68)(u8, u8);
    /* 6C */ UNK_T x6C;
    /* 70 */ UNK_T x70;
    /* 74 */ u8 x74;
    /* 75 */ u8 x75;
    /* 76 */ u8 x76;
    /* 77 */ u8 x77;
    /* 78 */ u8 x78;
    /* 79 */ s8 pad_x79[0x7C - 0x79];
    /* 7C */ u8 x7C; ///< CharacterKind
    /* 7D */ s8 pad_x7D[0x80 - 0x7D];
};

struct UnkAllstarData {
    /*  +0 */ Unk1PData x0;
    /* +48*/ UNK_T x48;
    /* +4C*/ UNK_T x4C;
    /* +50*/ UNK_T x50;
    /* +54*/ UNK_T x54;
    /* +58*/ u32 x58;
    /* +5C*/ u32 _5C;
    /* +60*/ u32 _60;
    /* +64*/ UNK_T x64;
    /* +68*/ UNK_T x68;
    /* +6C*/ u32 _6C;
    /* +70*/ u32 _70;
    /* +74*/ u16 x74; ///< current percent
    /* +76*/ u8 x76[24]; ///< character id array
    /* +8E*/ u8 x8E[2];
    /* +90*/ u8 x90[4];
    /* +94*/ u8 _94[0x9C - 0x94];
    /* +9C*/ u32 x9C; ///< current time (frames)
};

struct TmData {
    int cur_option;
    int match_type;
    int combatants;
    int entrants;
    int hmn_cpu_count;
    int stage_selection_type;
    int cpu_level;
    u8 _x1C[0x20 - 0x1C];
    int x20;
    int x24;
    u32 x28; ///< stage id
    u8 x2C;
    u8 x2D;
    u8 x2E;
    u8 x2F;
    u8 x30;
    u8 x31;
    u8 x32;
    u8 x33;
    u8 pad_x34[0x37 - 0x34];
    struct TmUnkMenuData {
        u8 x0;
        u8 x1;
        u8 x2;
        u8 x3;
        u8 x4;
        u8 x5;
        u8 x6;
        u8 x7;
        u8 x8;
        u16 x9;
        u8 xB;
        u8 xC;
        u8 xD;
        u8 pad_xE[0x11 - 0xE];
    } x37[16]; ///< @todo needs to be larger, see gm_80190EA4
    u8 pad_x158[0x4B8 - 0x158];
    struct UnkSelections {
        u8 x0; ///< slot type
        u8 x1; ///< CSSIconHud
        u8 x2;
        u8 x3; ///< color
        u8 x4; ///< CPU level
        u8 x5;
        u16 x6;
        u8 pad_x4[0xA - 0x8];
    } x4B8[4];
    HSD_Text* x4E0;
    HSD_Text* x4E4;
    HSD_Text* x4E8[6];
    HSD_Text* x500[6];
    HSD_Text* x518[3];
    u8 pad_x524[0x534 - 0x524];
    HSD_Text* x534[3];
    u8 pad_x540[0x56B - 0x540];
};

struct NameData {
    // a lot of this is shared with a struct for character stats as well
    /* x0F0 */ s32 self_destructs;
    /* x0F4 */ s32 attacks_hit;
    /* x0F8 */ s32 attacks_total;
    /* x0FC */ s32 damage_given;
    /* x100 */ s32 damage_taken;
    /* x104 */ s32 damage_recovered;
    /* x108 */ s16 peak_damage;
    /* x10A */ s16 matches;
    /* x10C */ s16 victories;
    /* x10E */ s16 losses;
    /* x110 */ s32 play_time; // in minutes
    /* x114 */ s32 x114;
    /* x118 */ s32 ground_distance; // in meters
    /* x11C */ s32 jump_distance;
    /* x120 */ s32 drop_distance;
    /* x124 */ s32 flight_distance;
    /* x128 */ s32 coin_points;
    /* x12C */ s32 swiped_coins;
    /* x130 */ s32 lost_coins;

    /* x1A1 */ bool rumble_toggle;
    /* x198 */ void* x198; // some kind of text representation of the name
};

struct CameraVsData {
    u32* x0; ///< state? gets set on button presses in OnFrame
    union {
        struct {
            HSD_Text* slot_a;
            HSD_Text* slot_b;
            HSD_Text* bottom_text;
        };
        HSD_Text* text[3];
    };
};

struct TmVsData {
    u32 stage_id;
    Gm_PKind slot_type[4];
    u32 char_id[4];
    u32 color[4];
};

struct gm_801677C0_s {
    /*  +1 */ u8 x0;
    /*  +2 */ u8 x1;
    /*  +3 */ u8 x2;
    /*  +4 */ u8 x3;
    /*  +4 */ bool (*x4[2])(void);
    /*  +C */ UNK_T xC;
    /* +20 */ u64 unk_20;
    /* +28 */ u64 unk_28;
    /* +30 */ void (*unk_30)(void);
    /* +34 */ int unk_34;
    /* +38 */ u8 unk_38_0 : 1;
    /* +38 */ u8 unk_38_1 : 1;
};
STATIC_ASSERT(sizeof(struct gm_801677C0_s) == 0x30);

struct gm_80479D58_t {
    /*  +0 */ u32 unk_0;
    /*  +4 */ u32 unk_4;
    /*  +8 */ u32 unk_8;
    /*  +C */ int unk_C;
    /* +10 */ struct gm_801677C0_s unk_10;
};
STATIC_ASSERT(sizeof(struct gm_80479D58_t) == 0x40);

struct ResultsPlayerData {
    /* +00 */ u8 x0; ///< flags
    /* +01 */ u8 page;
    /* +02 */ u16 x2;
    /* +04 */ f32 scroll_offset;
    /* +08 */ HSD_GObj* fighter_gobj;
    /* +0C */ HSD_GObj* camera;
    /* +10 */ HSD_Text* stats_text[3][10]; ///< 3 pages with 10 entries?
    // /* +10 */ HSD_Text* stats_x10[10]; ///< these text arrays are the
    // scrollable stats
    // /* +3C */ HSD_Text* stats_x3C[10];
    // /* +60 */ HSD_Text* stats_x60[10];
    /* +88 */ HSD_Text* ko_count;
    /* +8C */ HSD_Text* ko_time;
    /* +90 */ HSD_JObj* jobjs[15];
    /* +CC */ Vec3 stats_position;
};

struct ResultsData {
    /* +00 */ u8 x0_0 : 1;
    /* +00 */ u8 x0_1 : 1;
    /* +00 */ u8 x0_2 : 1;
    /* +00 */ u8 x0_3 : 1;
    /* +00 */ u8 x0_4 : 1;
    /* +00 */ u8 x0_5 : 1;
    /* +00 */ u8 x0_6 : 1;
    /* +00 */ u8 x0_7 : 1;

    /* +01 */ u8 x1; ///< some sort of state
    /* +02 */ u8 num_pages;
    /* +03 */ char pad_03[0x4 - 0x3];
    /* +04 */ u8 x4; ///< winner?
    /* +05 */ u8 x5; ///< team winner?
    /* +06 */ u8 x6; ///< also winner?
    /* +08 */ s32 x8;
    /* +0C */ f32 xC;
    /* +10 */ SceneDesc* pnlsce;
    /* +14 */ SceneDesc* flmsce;
    /* +18 */ HSD_GObj* x18; ///< main proc?
    /* +1C */ HSD_CObj* cobj;
    /* +20 */ HSD_JObj* x20; ///< winner logo?
    /* +24 */ HSD_JObj* x24;
    /* +28 */ HSD_JObj* x28;
    /* +2C */ HSD_Text* x2C;
    /* +30 */ HSD_JObj* x30;
    /* +34 */ HSD_JObj* x34[6];
    /* +4C */ Vec3 x4C[6];
    /* +94 */ MatchEnd* x94;
    /* +98 */ struct ResultsPlayerData player_data[6];
};
STATIC_ASSERT(sizeof(struct ResultsData) == 0x5A8);

struct gm_803DE650_t {
    u8 x0;
    u8 x1; // rule flags?
    u16 x2;
    u16 x4;
    u16 x6;
    u8 x8;
    u8 x9;
    s8 xA[3]; ///< CharacterKind (opponents?)
    u8 xD;
    u8 xE;
    u8 xF;
};

struct lbl_8046DBD8_t {
    u8 x0; // c_kind
    u8 x1; // color
    u8 x2; // stocks
    u8 x3;
    u8 x4; // c_kind
    u8 x5;
    u8 x6;
    u16 x8;
};

struct VsApproachData {
    u8 x0;
    u8 x1;
};

/// @brief data passed to OnLoad callback for MJ_MENU
struct MenuEnterData {
    /* +00 */ u8 menu_kind;         ///< will set the next menu kind
    /* +01 */ u8 hovered_selection; ///< will set the next hovered selection
    /* +02 */ u8
        load_assets; ///< checks if the assets need to be loaded or not
    /* +03 */ s8 x3;
};
STATIC_ASSERT(sizeof(struct MenuEnterData) == 0x4);

/// @brief data passed to OnLeave callback for MJ_MENU
struct MenuExitData {
    /* +00 */ s8 pending_major; ///< will set the next major scene
    /* +01 */ u8 _1[0x3];
};
STATIC_ASSERT(sizeof(struct MenuExitData) == 0x4);

typedef struct gm_803DDEC8Struct{
    u8 x0;
    u8 x1_b0 : 1;
    u8 x1_b1 : 1;
    u8 x1_b2 : 1;
    u8 x1_b3 : 1;
    u8 x1_b4 : 1;
    u8 x1_b5 : 1;
    u8 x1_b6 : 1;
    u8 x1_b7 : 1;
    u8 x2[0xC - 0x2];
    void* xC;
}gm_803DDEC8Struct;

#endif

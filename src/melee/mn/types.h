#ifndef MELEE_MN_TYPES_H
#define MELEE_MN_TYPES_H

#include "platform.h"

#include <placeholder.h>

#include "mn/forward.h" // IWYU pragma: export

#include <baselib/sislib.h>

typedef struct {
    u8 cursor;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    HSD_Text* text;
} Menu;
// size 0x8

struct CountEntry {
    u8 id;
    u8 pad[3];
    u32 val;
};

#ifdef M2C
typedef struct Menu_GObj Menu_GObj;
struct Menu_GObj {
    /*  +0 */ u16 classifier;
    /*  +2 */ u8 p_link;
    /*  +3 */ u8 gx_link;
    /*  +4 */ u8 p_priority;
    /*  +5 */ u8 render_priority;
    /*  +6 */ u8 obj_kind;
    /*  +7 */ u8 user_data_kind;
    /*  +8 */ Menu_GObj* next;
    /*  +C */ Menu_GObj* prev;
    /* +10 */ Menu_GObj* next_gx;
    /* +14 */ Menu_GObj* prev_gx;
    /* +18 */ HSD_GObjProc* proc;
    /* +1C */ void (*rendered)(Menu_GObj* gobj, s32 code);
    /* +20 */ u64 gxlink_prios;
    /* +28 */ HSD_JObj* hsd_obj;
    /* +2C */ Menu* user_data;
    /* +30 */ void (*user_data_remove_func)(Fighter* data);
    /* +34 */ void* x34_unk;
};
#else
typedef struct HSD_GObj Menu_GObj;
#endif

struct PlayerInitData {
    /*0x00*/ s8 c_kind;    ///< uses CharacterKind (CKIND_*) values
    /*0x01*/ u8 slot_type; ///< uses Gm_PKind values
    /*0x02*/ s8 stocks;    // stocks
    /*0x03*/ u8 color;     // color
    /*0x04*/ u8 slot;      // port
    /*0x05*/ s8 x5;        // spawnpos32
    /*0x06*/ s8 spawn_dir; // spawn direction
    /*0x07*/ u8 sub_color; // subcolor
    /*0x08*/ s8 handicap;  // handicap
    /*0x09*/ u8 team;      // team
    /*0x0A*/ u8 xA;        // nametag
    /*0x0B*/ u8 xB;
    /*0x0C*/ u8 xC_b0 : 1; ///< rumble enabled
    u8 xC_b1 : 1;
    u8 xC_b2 : 1; ///< metal
    u8 xC_b3 : 1;
    u8 xC_b4 : 1; ///< invisible
    u8 xC_b5 : 1;
    u8 xC_b6 : 1;
    u8 xC_b7 : 1;
    /*0x0D*/ u8 xD_b0 : 1;
    u8 xD_b1 : 1;
    u8 xD_b2 : 1;
    u8 xD_b3 : 1;
    u8 xD_b4 : 1;
    u8 xD_b5 : 1;
    u8 xD_b6 : 1;
    u8 xD_b7 : 1;
    /*0x0E*/ u8 xE;        ///< CPU type
    /*0x0F*/ u8 cpu_level; // CPU level
    /*0x10*/ u16 x10;
    /*0x12*/ u16 x12;
    /*0x14*/ u16 hp;    ///< hit points, for stamina mode
    /*0x18*/ float x18; ///< offense ratio
    /*0x1C*/ float x1C; ///< defense ratio
    /*0x20*/ float x20;
};

struct StartMeleeRules {
    u32 x0_0 : 3; // match mode? 1 = stock mode, 2 = coin mode?
    u32 x0_3 : 3;
    u32 x0_6 : 1;
    u32 x0_7 : 1; ///< timer counts up

    u32 x1_0 : 1;
    u32 x1_1 : 1;
    u32 x1_2 : 1;
    u32 x1_3 : 1;
    u32 x1_4 : 1;
    u32 x1_5 : 1;
    u32 timer_shows_hours : 1; // false=65:00.00, true=1:05:00.00

    u32 x1_7 : 1; ///< friendly fire on

    u32 x2_0 : 1;
    u32 x2_1 : 1;
    u32 x2_2 : 1;
    u32 x2_3 : 1; ///< single-button mode enabled
    u32 x2_4 : 1;
    u32 x2_5 : 1;
    u32 x2_6 : 1;
    u32 x2_7 : 1;

    u32 x3_0 : 1;
    u32 x3_1 : 1;
    u32 x3_2 : 1;
    u32 x3_3 : 1;
    u32 x3_4 : 1;
    u32 x3_5 : 1;
    u32 x3_6 : 1;
    u32 x3_7 : 1;

    u32 x4_0 : 1;
    u32 x4_1 : 1;
    u32 x4_2 : 1;
    u32 x4_3 : 1;
    u32 x4_4 : 1;
    u32 x4_5 : 1;
    u32 x4_6 : 1;
    u32 x4_7 : 1;

    u32 x5_0 : 1;
    u32 x5_1 : 1;
    u32 x5_2 : 1;
    u32 x5_3 : 1;
    u32 x5_4 : 1;
    u32 x5_5 : 1;
    u32 x5_6 : 1;
    u32 x5_7 : 1;

    u8 x6;
    u8 x7; // end graphic / SFX type
    u8 is_teams;
    u8 x9;
    u8 xA;
    s8 xB; // item frequency
    s8 xC; // SD penalty
    u8 xD;
    u16 xE; // InternalStageId

    u32 x10; // time limit
    u8 x14;
    u32 x18;
    u32 x1C_pad[(0x20 - 0x1C) / 4];

    u64 x20; // item mask
    int x28;
    float x2C;
    float x30;         // damage ratio
    float x34;         // game speed
    void (*x38)(int);  // on unpause callback
    void (*x3C)(int);  // on pause callback (conditional?)
    int (*x40)(void);  // on pause callback
    void (*x44)(void); // on VS match start callback
    void (*x48)(void); // ingame pre-frame callback
    void (*x4C)(void); // ingame post-frame callback
    void (*x50)(int);  // on VS match end callback
    struct {
        u8 pad_x0[0x10];
        u8 x10_b0 : 1;
        u8 x10_b1 : 1;
    }* x54;
    int x58;
    u8 pad_x5C[0x60 - 0x5C];
};

struct StartMeleeData {
    StartMeleeRules rules;
    PlayerInitData players[6];
};

struct VsModeData {
    /* +0 */ s8 loser;
    /* +1 */ s8 ordered_stage_index;
    /* +2 */ s8 winner;
    /* +3 */ u8 unk_0x3;
    /* +4 */ u8 unk_0x4;
    /* +5 */ u8 unk_0x5;
    /* +6 */ u8 unk_0x6;
    /* +7 */ u8 unk_0x7;
    /* +8 */ StartMeleeData data;
};

typedef enum CSSMatchType {
    VS_MELEE = 0x0,
    VS_CAMERA = 0x1,
    VS_STAMINA = 0x2,
    VS_SUDDEN_DEATH = 0x3,
    VS_GIANT = 0x4,
    VS_TINY = 0x5,
    VS_INVISIBLE = 0x6,
    VS_FIXED_CAMERA = 0x7,
    VS_SINGLE_BUTTON = 0x8,
    VS_LIGHTNING = 0x9,
    VS_SLOWMO = 0xA,
    REG_CLASSIC = 0xB,
    REG_ADVENTURE = 0xC,
    REG_ALLSTAR = 0xD,
    EVENT_MATCH = 0xE,
    STADIUM_TARGET = 0xF,
    STADIUM_HOMERUN = 0x10,
    STADIUM_MULTIMAN_10 = 0x11,
    STADIUM_MULTIMAN_100 = 0x12,
    STADIUM_3_MIN_MELEE = 0x13,
    STADIUM_15_MIN_MELEE = 0x14,
    STADIUM_ENDLESS_MELEE = 0x15,
    STADIUM_CRUEL_MELEE = 0x16,
    TRAINING_MODE = 0x17
} CSSMatchType;

struct CSSData {
    u16 unk_0x0; ///< 1p port?
    u8 match_type;
    u8 pending_scene_change;
    u8* ko_star_counts;
    VsModeData data;
};

struct CSSModeInfo {
    u16 mode_ffa_frame;   // 0x00 - Anim frame used for top-left mode texture
    u16 mode_teams_frame; // 0x02 - Anim frame used for top-left mode texture
    int enter_sfx;        // 0x04 - Announcer sfx when entering CSS
};

typedef enum CSSIconState {
    ICONSTATE_LOCKED,
    ICONSTATE_TEMP,
    ICONSTATE_UNLOCKED
} CSSIconState;

typedef enum CSSIconJointId {
    ICONJOINT_DRMARIO = 0x04,
    ICONJOINT_FALCO = 0x08,
    ICONJOINT_GANON = 0x06,
    ICONJOINT_CLINK = 0x0A,
    ICONJOINT_PICHU = 0x0C,
    ICONJOINT_EMBLEM = 0x0E,
    ICONJOINT_MARIO = 0x10,
    ICONJOINT_LUIGI = 0x11,
    ICONJOINT_KOOPA = 0x12,
    ICONJOINT_PEACH = 0x13,
    ICONJOINT_YOSHI = 0x14,
    ICONJOINT_DONKEY = 0x15,
    ICONJOINT_CAPTAIN = 0x16,
    ICONJOINT_FOX = 0x17,
    ICONJOINT_NESS = 0x18,
    ICONJOINT_POPONANA = 0x19,
    ICONJOINT_KIRBY = 0x1A,
    ICONJOINT_SAMUS = 0x1B,
    ICONJOINT_ZELDA = 0x1C,
    ICONJOINT_LINK = 0x1D,
    ICONJOINT_PIKACHU = 0x1E,
    ICONJOINT_PURIN = 0x1F,
    ICONJOINT_MEWTWO = 0x20,
    ICONJOINT_GAMEWATCH = 0x21,
    ICONJOINT_MARS = 0x22
} CSSIconJointId;

struct CSSIcon {
    u8 ft_hudindex; // 0x00 - used for getting combo count @ 8025C0C4
    u8 char_kind;   // 0x01 - icons external ID
    u8 state; // 0x02 - 0x0 Not Unlocked, 0x01 Unlocked, 0x02 Unlocked and disp
    u8 anim_timer;  // 0x03 - 0xC when char is chosen
    u8 joint_id_vs; // 0x04 - Vs Icon Bg Jobj ID
    u8 joint_id_1p; // 0x05 - Vs Icon Bg Jobj ID
    int sfx;        // 0x08
    float bound_l;  // 0x0C
    float bound_r;  // 0x10
    float bound_u;  // 0x14
    float bound_d;  // 0x18
};

struct CSSIconsData {
    u8 gnw_name[0x1C];         // 0x0
    CSSModeInfo mode_info[24]; // 0x1c
};

struct CSSDoor {
    u8 emblem_joint;           // 0x00
    u8 costume_joint;          // 0x01
    u8 team_joint;             // 0x02
    u8 door_joint;             // 0x03
    u8 bg_joint;               // 0x04
    u8 player_indicator_joint; // 0x05 - Nametag window joint id (to scroll and
                               // choose a name)
    u8 slidername_joint;       // 0x06 - Slider name joint
    u8 cpuslider_joint;        // 0x07 - Used when only CPU is showing
    u8 cpuslider2_joint;       // 0x08 - Used when handicap is also showing
    u8 selected_since_load; // 0x09 - Determines when player selected since the
                            // CSS loaded

    u8 team;           // 0x0A
    u8 p_kind;         // 0x0B - PlayerKind, 0x0 = HMN, 0x1 = CPU, 0x3 = Closed
    u8 p_kind_prev;    // 0x0C
    u8 costume;        // 0x0D
    u8 sel_icon;       // 0x0E - Icon this player has selected
    u8 sel_icon_prev;  // 0x0F
    u8 dooranim_timer; // 0x10
    u8 slideranim_timer;        // 0x11
    u8 is_hold_cpu_slider;      // 0x12
    u8 is_hold_handicap_slider; // 0x13

    float togglebtn_left;  // 0x14 - HMN button bound
    float togglebtn_right; // 0x18 - HMN button bound
    float teambtn_left;    // 0x1C - Team button bound
    float teambtn_right;   // 0x20 - Team button bound
};

struct CSSTagData {
    TextGlyphTexture* text;    // 0x00
    TextGlyphTexture* name_ls; // 0x04
    float x8;                  // 0x08
    float scroll_amt;          // 0x0C
    float scroll_force;        // 0x10
    int timer;                 // 0x14
    u8 next_tag;               // 0x18
    u8 port;                   // 0x19
    u8 state;                  // 0x1A
    u8 use_tag;                // 0x1B
};

struct CSSTag {
    CSSTagData* data;     // 0x00
    u8 x4;                // 0x04
    u8 list_joint;        // 0x05
    u8 name_jointl;       // 0x06
    u8 x7;                // 0x07
    u8 kostar_text_joint; // 0x08
    u8 x9;                // 0x09
    u8 xa;                // 0x0A
    u8 xb;                // 0x0B
};

struct CSSKOStar {
    HSD_Text* text; // 0x00
    float x4;       // 0x04
    u8 joint;       // 0x08
    u8 joint2;      // 0x09
    int xc;         // 0x0C
    int x10;        // 0x10
    int x14;        // 0x14
    int x18;        // 0x18
    int x1c;        // 0x1C
};

struct CSSDoorsData {
    CSSDoor doors[4]; // 0x00
    CSSTag tags[4];   // 0x90
    u8 xc0;
    u8 xc1;
    u8 xc2;
    u8 xc3;
    u8 xc4;
    u8 name_list_joint;
    u8 tag_box_joint;
    u8 xc7;
    u8 xc8;
    u8 xc9;
    u8 xca;
    u8 xcb;
    u8 xcc;
    u8 xcd;
    u8 xce;
    int xcf;
    int xd3;
    float xd7;
    float xdb;
    float xdf;
    float xe3;
    float xe7;
    float xeb;
};

struct CSSDoorsData2 {
    u8 xf0[5];
    float xf8;
    float xfc;
    float x100;
    float x104;
    float x108;
    float x10c;
    CSSKOStar ko_stars[4]; // 0x110
};

struct mnGallery_804A0B90_t {
    char pad_0[0x96000];
};
STATIC_ASSERT(sizeof(struct mnGallery_804A0B90_t) == 0x96000);

struct SSSData {
    /* +00 */ u8 unk_stage;
    /* +01 */ u8 x1;
    /* +02 */ u8 no_lras;
    /* +03 */ s8 force_stage_id;
    /* +04 */ u8 start_game;
    /* +08 */ VsModeData data;
};

struct AnimLoopSettings {
    /* +00 */ f32 start_frame;
    /* +04 */ f32 end_frame;
    /* +08 */ f32 loop_frame; ///< if this is -0.1f, dont loop
};

/// User data for VS Records diagram screen (mnDiagram)
struct Diagram {
    /* 0x00 */ u8 saved_menu; ///< Saved menu ID on entry
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 saved_selection; ///< Saved hovered selection on entry
    /* 0x04 */ u8 anim_state;       ///< 0 = idle, 1 = intro anim playing
    /* 0x05 */ u8 pad_5[3];
    /* 0x08 */ HSD_JObj* jobjs[13]; ///< JObj references, filled by lb_80011E24
    /* 0x3C */ u16
        fighter_cursor_pos;          ///< Fighter mode scroll offset (col << 8 | row)
    /* 0x3E */ u16 name_cursor_pos;  ///< Name mode scroll offset (col << 8 | row)
    /* 0x40 */ HSD_GObj* popup_gobj; ///< Popup window GObj (or NULL)
    /* 0x44 */ u8 is_name_mode;      ///< 0 = fighter mode, 1 = name mode
    /* 0x45 */ u8 pad_45[3];
    /* 0x48 */ HSD_Text* col_header_text; ///< Column header text object
    /* 0x4C */ HSD_Text* row_header_text; ///< Row header text object
};

struct MenuKindData {
    AnimLoopSettings* anim_loop;
    float start_frame;
    u16* description_indices; ///< array of sis idx's for each selection
    u8 selection_count;       ///< number of options/cursors in the menu
    void (*think)(HSD_GObj*);
};

/// User data for VS Records page 2 (character details screen)
/// Total size: 0xC8 bytes
struct Diagram2 {
    /* 0x00 */ u8 saved_menu; ///< Saved menu ID on entry
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 saved_selection; ///< Saved hovered selection on entry
    /* 0x04 */ u8 anim_state;       ///< 0 = idle, 1 = intro anim playing
    /* 0x05 */ u8 pad_5[3];
    /* 0x08 */ HSD_JObj* x8;
    /* 0x0C */ HSD_JObj* xC;
    /* 0x10 */ HSD_JObj* x10;
    /* 0x14 */ HSD_JObj* fighter_mode_header; ///< shown in fighter mode
    /* 0x18 */ HSD_JObj* x18;
    /* 0x1C */ HSD_JObj* x1C;
    /* 0x20 */ HSD_JObj* name_mode_header; ///< shown in name mode
    /* 0x24 */ HSD_JObj* x24;
    /* 0x28 */ HSD_JObj* icon_parent;   ///< parent for character icons
    /* 0x2C */ HSD_JObj* row0_ref;      ///< row 0 position reference
    /* 0x30 */ HSD_JObj* row1_ref;      ///< row 1 position reference
    /* 0x34 */ HSD_JObj* down_arrow;    ///< hidden when at bottom
    /* 0x38 */ HSD_JObj* up_arrow;      ///< hidden when scroll_offset == 0
    /* 0x3C */ HSD_JObj* left_arrow;    ///< hidden at first selection
    /* 0x40 */ HSD_JObj* right_arrow;   ///< hidden at last selection
    /* 0x44 */ u16 scroll_offset;       ///< current scroll position
    /* 0x46 */ u8 selected_fighter_idx; ///< fighter mode selection
    /* 0x47 */ u8 selected_name_idx;    ///< name mode selection
    /* 0x48 */ u8 is_name_mode;         ///< 0 = fighter, 1 = name mode
    /* 0x49 */ u8 pad_49[3];
    /* 0x4C */ HSD_Text* row_labels[10]; ///< stat category label text
    /* 0x74 */ HSD_Text* row_values[10]; ///< stat value text
    /* 0x9C */ HSD_Text* row_icons[10];  ///< optional stat icons
    /* 0xC4 */ HSD_Text* header_text;    ///< entity name header
};

/// VS Records stat types for mnDiagram2 (page 2 of VS Records menu).
/// Fighter mode shows stats 0x00-0x14 (21 types).
/// Name mode shows stats 0x00-0x17 (24 types, including character icon stats).
typedef enum VSRecordsStatType {
    /* 0x00 */ VSSTAT_TOTAL_KOS,      ///< Total KOs across all opponents
    /* 0x01 */ VSSTAT_TOTAL_FALLS,    ///< Total falls (deaths)
    /* 0x02 */ VSSTAT_SD_COUNT,       ///< Self-destructs (FD+0x34 / ND+0xF0)
    /* 0x03 */ VSSTAT_HIT_PERCENTAGE, ///< Attack accuracy % (calculated)
    /* 0x04 */ VSSTAT_DAMAGE_DEALT, ///< Total damage dealt (FD+0x40 / ND+0xFC)
    /* 0x05 */ VSSTAT_DAMAGE_TAKEN, ///< Total damage received (FD+0x44 /
                                    ///< ND+0x100)
    /* 0x06 */ VSSTAT_DAMAGE_RECOVERED, ///< Damage healed (FD+0x48 / ND+0x104)
    /* 0x07 */ VSSTAT_PEAK_DAMAGE, ///< Highest % survived (FD+0x4C / ND+0x108)
    /* 0x08 */ VSSTAT_MATCH_COUNT, ///< Total matches played (FD+0x4E /
                                   ///< ND+0x10A)
    /* 0x09 */ VSSTAT_VICTORIES,   ///< Total wins (FD+0x50 / ND+0x10C)
    /* 0x0A */ VSSTAT_LOSSES,      ///< Total losses (FD+0x52 / ND+0x10E)
    /* 0x0B */ VSSTAT_PLAY_TIME,   ///< Total play time in frames (FD+0x54 /
                                   ///< ND+0x110)
    /* 0x0C */ VSSTAT_PLAY_PERCENTAGE, ///< % of total VS play time
                                       ///< (calculated)
    /* 0x0D */ VSSTAT_AVG_PLAYERS,     ///< Average player count (calculated)
    /* 0x0E */ VSSTAT_WALK_DISTANCE,   ///< Distance walked in ft (FD+0x5C /
                                       ///< ND+0x118)
    /* 0x0F */ VSSTAT_RUN_DISTANCE,    ///< Distance run in ft (FD+0x60 /
                                       ///< ND+0x11C)
    /* 0x10 */ VSSTAT_FALL_DISTANCE,   ///< Distance fallen in ft (FD+0x64 /
                                       ///< ND+0x120)
    /* 0x11 */ VSSTAT_PEAK_HEIGHT,     ///< Max height reached in ft (FD+0x68 /
                                       ///< ND+0x124)
    /* 0x12 */ VSSTAT_COINS_COLLECTED, ///< Coins picked up (FD+0x6C /
                                       ///< ND+0x128)
    /* 0x13 */ VSSTAT_COINS_SWIPED, ///< Coins stolen from opponents (FD+0x70 /
                                    ///< ND+0x12C)
    /* 0x14 */ VSSTAT_COINS_LOST,   ///< Coins lost to opponents (FD+0x74 /
                                    ///< ND+0x130)
    /* 0x15 */ VSSTAT_MOST_PLAYED,  ///< Most played fighter (Name mode only,
                                    ///< icon)
    /* 0x16 */ VSSTAT_SECOND_PLAYED, ///< 2nd most played fighter (Name mode
                                     ///< only, icon)
    /* 0x17 */ VSSTAT_LEAST_PLAYED,  ///< Least played fighter (Name mode only,
                                     ///< icon)

    VSSTAT_COUNT_FIGHTER = 0x15, ///< Number of stats in fighter mode
    VSSTAT_COUNT_NAME = 0x18,    ///< Number of stats in name mode
} VSRecordsStatType;

#endif

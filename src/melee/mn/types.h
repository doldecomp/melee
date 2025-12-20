#ifndef MELEE_MN_TYPES_H
#define MELEE_MN_TYPES_H

#include "platform.h"

#include <placeholder.h>

#include "mn/forward.h" // IWYU pragma: export

#include <baselib/sislib.h>

typedef unsigned char MenuKind8;
typedef unsigned char MenuState8;
typedef unsigned long MenuButtons; ///< set in mn_80229624 and used in MenuFlow

typedef struct {
    u8 cursor; // @todo are these arbitrary variables the menus can use in any
               // way?
    u8 unk1;
    u8 unk2;
    u8 unk3;
    HSD_Text* text;
} Menu;
// size 0x8

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
    float x30; // damage ratio
    float x34; // game speed
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
    HSD_Text* text;         // 0x00
    float x4;               // 0x04
    u8 joint;               // 0x08
    u8 joint2;              // 0x09
    int xc;                 // 0x0C
    int x10;                // 0x10
    int x14;                // 0x14
    int x18;                // 0x18
    int x1c;                // 0x1C
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
    /* +08 */ f32 loop_frame; ///< if -1.0f, dont loop
};

struct MenuFlow {
    u8 cur_menu;
    u8 prev_menu;
    u16 hovered_option;
    u32 confirmed_option;
    u32 x8;
    u32 buttons;
    u8 x10;
    u8 entering_menu; ///< bool
    u8 light_lerp_frames;
    GXColor* light_color; ///< used for the main panel color
};

struct MenuInputState {
    u16 cooldown;
    u16 x2;
    s32 x4;
};

#endif

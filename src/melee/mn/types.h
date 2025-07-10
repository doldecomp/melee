#ifndef MELEE_MN_TYPES_H
#define MELEE_MN_TYPES_H

#include <placeholder.h>

#include "mn/forward.h" // IWYU pragma: export

#include "platform.h"

#include <baselib/sislib.h>

typedef struct {
    u8 cursor; // @todo are these arbitrary variables the menus can use in any
               // way?
    u8 unk1;
    u8 unk2;
    u8 unk3;
    HSD_Text* text;
} Menu;
// size 0x8

#ifdef M2CTX
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
    /*0x00*/ u8 character_kind;
    /*0x01*/ u8 slot_type;
    /*0x02*/ u8 stocks;
    /*0x03*/ u8 color;
    /*0x04*/ u8 port;
    /*0x05*/ s8 spawnpos32;
    /*0x06*/ u8 spawn_direction;
    /*0x07*/ u8 subcolor;
    /*0x08*/ u8 handicap;
    /*0x09*/ u8 team;
    /*0x0A*/ u8 nametag;
    /*0x0B*/ u8 unk_0xb;
    /*0x0C*/ u8 unk_0xc;
    /*0x0D*/ u8 unk_0xd;
    /*0x0E*/ u8 unk_0xe;
    /*0x0F*/ u8 cpu_level;
    /*0x10*/ u8 unk_0x10;
    /*0x11*/ u8 unk_0x11;
    /*0x12*/ u16 unk_0x12;
    /*0x14*/ u8 unk_0x14;
    /*0x15*/ u8 unk_0x15;
    /*0x16*/ u8 unk_0x16;
    /*0x17*/ u8 unk_0x17;
    /*0x18*/ f32 offense_ratio;
    /*0x1C*/ f32 defense_ratio;
    /*0x20*/ u8 unk_0x20;
    /*0x21*/ u8 unk_0x21;
    /*0x22*/ u8 unk_0x22;
    /*0x23*/ u8 unk_0x23;
};

struct StartMeleeRules {
    u8 flags1;
    u8 flags2;
    u8 flags3;
    u8 flags4;
    u8 flags5;
    u8 flags6;
    u8 unk_0x6;
    u8 unk_0x7;
    u8 is_teams;
    u8 unk_0x9;
    u8 unk_0xa;
    s8 item_frequency;
    s8 sd_penalty;
    u8 unk_0xd;
    u32 stage_id;
    s32 time_limit;
    u8 unk_0x14;
    u8 unk_0x15;
    u8 unk_0x16;
    u8 unk_0x17;
    u8 unk_0x18;
    u8 unk_0x19;
    u8 unk_0x1a;
    u8 unk_0x1b;
    u8 unk_0x1c;
    u8 unk_0x1d;
    u8 unk_0x1e;
    u8 unk_0x1f;
    u64 item_mask;
    u8 unk_0x28;
    u8 unk_0x29;
    u8 unk_0x2a;
    u8 unk_0x2b;
    u8 unk_0x2c;
    u8 unk_0x2d;
    u8 unk_0x2e;
    u8 unk_0x2f;
    f32 damage_ratio;
    f32 game_speed;
    u8 unk_0x38;
    u8 unk_0x39;
    u8 unk_0x3a;
    u8 unk_0x3b;
    u8 unk_0x3c;
    u8 unk_0x3d;
    u8 unk_0x3e;
    u8 unk_0x3f;
    void* pause_check_callback;
    u8 unk_0x44;
    u8 unk_0x45;
    u8 unk_0x46;
    u8 unk_0x47;
    u8 unk_0x48;
    u8 unk_0x49;
    u8 unk_0x4a;
    u8 unk_0x4b;
    u8 unk_0x4c;
    u8 unk_0x4d;
    u8 unk_0x4e;
    u8 unk_0x4f;
    void* match_end_callback;
    s32 unk_0x54;
    u8 unk_0x58;
    u8 unk_0x59;
    u8 unk_0x5a;
    u8 unk_0x5b;
    u8 unk_0x5c;
    u8 unk_0x5d;
    u8 unk_0x5e;
    u8 unk_0x5f;
};

struct StartMeleeData {
    StartMeleeRules rules;
    PlayerInitData players[6];
};

struct VsModeData {
    s8 loser;
    u32 ordered_stage_index;
    s8 winner;
    u8 unk_0x3;
    u8 unk_0x4;
    u8 unk_0x5;
    u8 unk_0x6;
    u8 unk_0x7;
    StartMeleeData data;
};

struct CSSData {
    u16 unk_0x0;
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

// Not same as CharacterKind bc not as many characters as icons (missing Sheik,
// Master Hand, etc)
typedef enum CSSIconHud {
    ICONHUD_CAPTAIN = 0x00,
    ICONHUD_DONKEY = 0x01,
    ICONHUD_FOX = 0x02,
    ICONHUD_GAMEWATCH = 0x03,
    ICONHUD_KIRBY = 0x04,
    ICONHUD_KOOPA = 0x05,
    ICONHUD_LINK = 0x06,
    ICONHUD_LUIGI = 0x07,
    ICONHUD_MARIO = 0x08,
    ICONHUD_MARS = 0x09,
    ICONHUD_MEWTWO = 0x0A,
    ICONHUD_NESS = 0x0B,
    ICONHUD_PEACH = 0x0C,
    ICONHUD_PIKACHU = 0x0D,
    ICONHUD_POPONANA = 0x0E,
    ICONHUD_PURIN = 0x0F,
    ICONHUD_SAMUS = 0x10,
    ICONHUD_YOSHI = 0x11,
    ICONHUD_ZELDA = 0x12,
    ICONHUD_FALCO = 0x13,
    ICONHUD_CLINK = 0x14,
    ICONHUD_DRMARIO = 0x15,
    ICONHUD_EMBLEM = 0x16,
    ICONHUD_PICHU = 0x17,
    ICONHUD_GANON = 0x18
} CSSIconHud;

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
    CSSIcon icons[25 + 1];     // 0xDC
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
    TextGlyphTexture* text; // 0x00
    float x4;               // 0x04
    u8 joint;               // 0x08
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
    u8 xf1[5];
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

#endif

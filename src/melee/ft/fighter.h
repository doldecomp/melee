#ifndef _fighter_h_
#define _fighter_h_

#include <dolphin/types.h>
#include "sysdolphin/baselib/gobj.h"

typedef void (*fn_ptr_t)();

typedef struct _Vec2 { float x, y;    } Vec2;
typedef struct _Vec3 { float x, y, z; } Vec3;
typedef struct _Quat { float x, y, z, w; } Quat; // @TODO: xyzw order correct?

// TODO: put this in jobj.h or somewhere. Also fix missing void* only types
typedef float Mtx[3][4];

typedef struct _JOBJDesc
{
    char *class_name;       //0x00
    u32 flags;              //0x04
    struct _JOBJDesc *child; //0x08
    struct _JOBJDesc *next;  //0x0C
    void* p_union;  //0x10 TODO: define this union
    Vec3 rotation;                  //0x14 - 0x1C
    Vec3 scale;                     //0x20 - 0x28
    Vec3 position;                  //0x2C - 0x34
    Mtx mtx;                        //0x38
    void *robjdesc; //0x3C
} JOBJDesc;

typedef struct _JOBJ
{
    int hsd_info;     // 0x0
    int class_parent; // 0x4
    struct _JOBJ *sibling;    // 0x08
    struct _JOBJ *parent;     // 0x0C
    struct _JOBJ *child;      // 0x10
    int x14_flags;        // 0x14
    void *dobj;       // 0x18 TODO: define DOBJ struct
    Quat rot;         // 0x1C 0x20 0x24 0x28
    Vec3 x2C_scale;       // 0x2C
    Vec3 trans;       // 0x38
    Mtx rotMtx;       // 0x44
    Vec3 *VEC;        // 0x6C
    Mtx *MTX;         // 0x78
    void *aobj;       // 0x7C TODO: define AOBJ struct
    int *RObj;
    JOBJDesc *desc;
} JOBJ;

typedef struct _ColorOverlay
{
    int timer;                      // 0x0
    int pri;                        // 0x4  this colanims priority, lower = will persist
    int *ptr1;                      // 0x8
    int loop;                       // 0xc
    int *ptr2;                      // 0x10
    int x14;                        // 0x14
    int *alloc;                     // 0x18
    int x1c;                        // 0x1c
    int x20;                        // 0x20
    int x24;                        // 0x24
    int colanim;                    // 0x28, id for the color animation in effect
    GXColor hex;                    // 0x2C
    float color_red;                // 0x30
    float color_green;              // 0x34
    float color_blue;               // 0x38
    float color_alpha;              // 0x3C
    float colorblend_red;           // 0x40
    float colorblend_green;         // 0x44
    float colorblend_blue;          // 0x48
    float colorblend_alpha;         // 0x4C
    GXColor light_color;            //0x50
    float light_red;                // 0x54
    float light_green;              // 0x58
    float light_blue;               // 0x5C
    float light_alpha;              // 0x60
    float lightblend_red;           // 0x64
    float lightblend_green;         // 0x68
    float lightblend_blue;          // 0x6c
    float lightblend_alpha;         // 0x70
    float light_angle;              // 0x74
    float light_unk;                // 0x78
    unsigned char color_enable : 1; // 0x7c
    unsigned char flag2 : 1;        // 0x7c
    unsigned char light_enable : 1; // 0x7c
    unsigned char flag4 : 1;        // 0x7c
    unsigned char flag5 : 1;        // 0x7c
    unsigned char flag6 : 1;        // 0x7c
    unsigned char flag7 : 1;        // 0x7c
    unsigned char flag8 : 1;        // 0x7c
} ColorOverlay;

typedef struct _CollData
{
    HSD_GObj *gobj;            // 0x0
    Vec3 topN_Curr;            // 0x4
    Vec3 topN_CurrCorrect;     // 0x10
    Vec3 topN_Prev;            // 0x1c
    Vec3 topN_Proj;            // 0x28
    int flags1;                // 0x34
    int coll_test;             // 0x38, is the ID of the most recent collision test for this object
    int ignore_line;           // 0x3c, ignores this line ID during collision
    int ledge_left;            // 0x40, ledge ID in contact with
    int ledge_right;           // 0x44, ledge ID in contact with
    int ignore_group;          // 0x48  ignores this line group during collision
    int check_group;           // 0x4c  checks only this line group during collision
    int x50;                   // 0x50
    int x54;                   // 0x54
    int x58;                   // 0x58
    int x5c;                   // 0x5c
    int x60;                   // 0x60
    int x64;                   // 0x64
    int x68;                   // 0x68
    int x6c;                   // 0x6c
    int x70;                   // 0x70
    int x74;                   // 0x74
    int x78;                   // 0x78
    int x7c;                   // 0x7c
    int x80;                   // 0x80
    Vec2 ecbCurr_top;          // 0x84
    Vec2 ecbCurr_bot;          // 0x8C
    Vec2 ecbCurr_right;        // 0x94
    Vec2 ecbCurr_left;         // 0x9C
    Vec2 ecbCurrCorrect_top;   // 0xA4
    Vec2 ecbCurrCorrect_bot;   // 0xAC
    Vec2 ecbCurrCorrect_right; // 0xB4
    Vec2 ecbCurrCorrect_left;  // 0xBC
    Vec2 ecbPrev_top;          // 0xC4
    Vec2 ecbPrev_bot;          // 0xCC
    Vec2 ecbPrev_right;        // 0xD4
    Vec2 ecbPrev_left;         // 0xDC
    Vec2 ecbProj_top;          // 0xE4
    Vec2 ecbProj_bot;          // 0xEC
    Vec2 ecbProj_right;        // 0xF4
    Vec2 ecbProj_left;         // 0xFC
    int x104;                  // 0x104
    void *joint_1;             // 0x108
    void *joint_2;             // 0x10c
    void *joint_3;             // 0x110
    void *joint_4;             // 0x114
    void *joint_5;             // 0x118
    void *joint_6;             // 0x11c
    void *joint_7;             // 0x120
    int x124;                  // 0x124
    int x128;                  // 0x128
    int x12c;                  // 0x12c
    int flags;                 // 0x130
    int envFlags;              // 0x134
    int envFlags_prev;         // 0x138
    int x13c;                  // 0x13c
    int x140;                  // 0x140
    int x144;                  // 0x144
    int x148;                  // 0x148
    int x83c_ground_index;     // 0x14c used
    u8 ground_info;            // 0x150
    u8 ground_unk;             // 0x151
    u8 ground_type;            // 0x152, platform/ledgegrab
    u8 ground_mat;             // 0x153, grass/ice etc
    Vec3 ground_normal;         // 0x154, points out of the ground surface
    int rightwall_index;       // 0x160
    u8 rightwall_info;         // 0x164
    u8 rightwall_unk;          // 0x165
    u8 rightwall_type;         // 0x166, platform/ledgegrab
    u8 rightwall_mat;          // 0x167, grass/ice etc
    Vec3 rightwall_slope;      // 0x168
    int leftwall_index;        // 0x174
    u8 leftwall_info;          // 0x178
    u8 leftwall_unk;           // 0x179
    u8 leftwall_type;          // 0x17A, platform/ledgegrab
    u8 leftwall_mat;           // 0x17B, grass/ice etc
    Vec3 leftwall_slope;       // 0x17C
    int ceil_index;            // 0x188
    u8 ceil_info;              // 0x18C
    u8 ceil_unk;               // 0x18D
    u8 ceil_type;              // 0x18E, platform/ledgegrab
    u8 ceil_mat;               // 0x18F, grass/ice etc
    Vec3 ceil_slope;           // 0x190
    int ecb_lock;              // 0x19c
} CollData;

typedef struct _FtMultiJumpDesc // exists in fighters special attributes
{
	int turn_frames;                    // turn frame length
	float turn_stick_x_min;             // min x value on left stick to trigger aerial turn
	float vel_stick_x_mult;             // jump x velocity = left stick x * this
	float aerial_drift_stick_mult_mult; // 0xC, multipler for the value in the fighter attribute
	float aerial_drift_max_mult;        // 0x10, multipler for the value in the fighter attribute
	float jump_vel_y[5];                // 0x14 subsequemt jumps Y velocities
	int jump_num;                       // 0x28, number of total aerial jumps
	int jump_state_start;               // 0x2C, state index for first aerial jump
	int x30;                            // 0x30,
} FtMultiJumpDesc;

typedef struct _FtState
{
    int action_id;
    int flags;
    char move_id;
    char bitflags1;
    void *animation_callback;
    void *iasa_callback;
    void *physics_callback;
    void *collision_callback;
    void *camera_callback;
} FtState;

typedef struct _ftData
{
    /* 0x00 */ s32* common_attr;
    /* 0x04 */ s32* ext_attr;
    u8* x08;
    void* x0C;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    void* x2C;
    s32 x30;
    void* x34;
    s32 x38;
    s32 x3C;
    s32 x40;
    void* x44;
    /* 0x48 */ void* items;
    void* x4C;
    s32 x50;
    s32 x54;
    void* x58;
} ftData;

typedef struct _FighterBone
{
    u32 *x0_joint; // 0x00
    u32 *x4_joint2; // 0x04 used for interpolation
    u32 data_filler[2];
} FighterBone;

typedef struct _FtAction
{
    char *anim_symbol; // ptr to the symbol name for this animation
    int anim_offset;   // offset of the anim data in plxxaj
    int anim_size;     // size of the animation data
    void *script;      // pointer to the script data for this action
    int flags;
    void *anim_data; // pointer to the animation data in ARAM
} FtAction;

typedef struct _FtDynamicBoneset
{
    int apply_phys_num;     // if this is 256, dyanmics are not processed
    //DynamicBoneset boneset; // 0x4
	u8 filler[20];
} FtDynamicBoneset;

typedef struct _FtDynamicHit
{
    Vec3 offset;    // 0x1670, 0x0
    float size;     // 0x167C, 0xC
    JOBJ *bone;     // 0x1680, 0x10
    int x14;        // 0x1684, 0x14
    Vec3 pos;       // 0x1688, 0x18
    int bone_index; // 0x1694, 0x24
} FtDynamicHit;

typedef struct _HitVictim
{
    void *data; // userdata of the object that was hit
    int timer;  // items use this to wait until hitting this gobj again
} HitVictim;

typedef struct _ftHit
{
    int active;                   // 0x0
    int x4;                       // 0x4
    int dmg;                      // 0x8
    float dmg_f;                  // 0xc
    Vec3 offset;                  // 0x10
    float size;                   // 0x1c
    int angle;                    // 0x20
    int kb_growth;                // 0x24
    int wdsk;                     // 0x28
    int kb;                       // 0x2c
    int attribute;                // 0x30
    int shield_dmg;               // 0x34
    int hitsound_severity;        // 0x38. hurtbox interaction. 0 = none, 1 = grounded, 2 = aerial, 3 = both
    int hitsound_kind;            // 0x3c
    char x40;                     // 0x40
    char x41;                     // 0x41
    unsigned char x421 : 1;       // 0x42 0x80
    unsigned char x422 : 1;       // 0x42 0x40
    unsigned char x423 : 1;       // 0x42 0x20
    unsigned char x424 : 1;       // 0x42 0x10
    unsigned char no_hurt : 1;    // 0x42 0x08      ignore hurtbox
    unsigned char no_reflect : 1; // 0x42 0x04      ignore reflect?
    unsigned char x427 : 1;       // 0x42 0x02
    unsigned char x428 : 1;       // 0x42 0x01
    unsigned char x431 : 1;       // 0x43 0x80
    unsigned char x432 : 1;       // 0x43 0x40
    unsigned char hit_all : 1;    // 0x43 0x20
    unsigned char x434 : 1;       // 0x43 0x10
    unsigned char x435 : 1;       // 0x43 0x08
    unsigned char x436 : 1;       // 0x43 0x04
    unsigned char x437 : 1;       // 0x43 0x02
    unsigned char x438 : 1;       // 0x43 0x01
    u8 x44;                       // 0x44
    u8 victim_num;                // 0x45
    JOBJ *bone;                   // 0x48
    Vec3 pos;                     // 0x4c
    Vec3 pos_prev;                // 0x58
    Vec3 pos_coll;                // 0x64   position of hurt collision
    float coll_distance;          // 0x70   Distance From Collding FtHurt (Used for phantom hit collision calculation)
    HitVictim victims[24];        // 0x74
    int x134;                     // 0x134, flags of some sort
} ftHit;

typedef struct _FtHurt
{
    int state;                    // 0x0, whether or not this hurtbox can be hit
    Vec3 hurt1_offset;            // 0x4
    Vec3 hurt2_offset;            // 0x10
    float scale;                  // 0x1c
    JOBJ *jobj;                   // 0x20
    unsigned char is_updated : 1; // 0x24, if enabled, wont update position
    unsigned char x24_2 : 1;      // 0x24 0x40
    unsigned char x24_3 : 1;      // 0x24 0x20
    unsigned char x24_4 : 1;      // 0x24 0x10
    unsigned char x24_5 : 1;      // 0x24 0x08
    unsigned char x24_6 : 1;      // 0x24 0x04
    unsigned char x24_7 : 1;      // 0x24 0x02
    unsigned char x24_8 : 1;      // 0x24 0x01
    Vec3 hurt1_pos;               // 0x28
    Vec3 hurt2_pos;               // 0x34
    int bone_index;               // 0x40
    int hurt_kind;                // 0x44. 0 = low, 1 = mid, 2 = high
    int is_grabbable;             // 0x48
} FtHurt;

typedef struct _FtAfterImageKey
{
    Vec3 pos;
    Vec3 rot;
} FtAfterImageKey;

typedef struct _CPULeaderLog
{
    int x0;                 // 0x0, 0xfc
    u8 x4;                  // 0x4, 0x100
    u8 x5;                  // 0x3, 0x101
    u8 x6;                  // 0x6, 0x102
    u8 x7;                  // 0x7, 0x103
    int x8;                 // 0x8, 0x104
    Vec3 pos;               // 0xc, 0x108
    float facing_direction; // 0x18, 0x114
} CPULeaderLog;

typedef struct _CPU
{
    int held;                    // 0x0
    s8 lstickX;                  // 0x4
    s8 lstickY;                  // 0x5
    s8 cstickX;                  // 0x6
    s8 cstickY;                  // 0x7
    s8 ltrigger;                 // 0x8
    s8 rtrigger;                 // 0x9
    int ai;                      // 0xc, 25 of these, function table at 800a1090
    int level;                   // 0x10
    int x14;                     // 0x14
    int scenario_id;             // 0x18
    int x1c;                     // 0x1c
    int x20;                     // 0x20
    int x24;                     // 0x24
    int x28;                     // 0x28
    int x2c;                     // 0x2c
    int x30;                     // 0x30
    int x34;                     // 0x34
    float x38;                   // 0x38
    float x3c;                   // 0x3c
    float x40;                   // 0x40
    void *x44;                   // 0x44
    void *x48;                   // 0x48
    int x4c;                     // 0x4c
    int x50;                     // 0x50
    float x54;                   // 0x54
    float x58;                   // 0x58
    float x5c;                   // 0x5c
    int x60;                     // 0x60
    int x64;                     // 0x64
    int x68;                     // 0x68
    int x6c;                     // 0x6c
    int x70;                     // 0x70
    int x74;                     // 0x74
    int proc_num;                // 0x78, number of times it updated CPU logic in any capacity
    int scenario_check_num;      // 0x7c, number of times it tried to update CPU scenario
    int x80;                     // 0x80
    int x84;                     // 0x84
    int x88;                     // 0x88
    int x8c;                     // 0x8c
    int x90;                     // 0x90
    int x94;                     // 0x94
    int x98;                     // 0x98
    int x9c;                     // 0x9c
    int xa0;                     // 0xa0
    int xa4;                     // 0xa4
    int xa8;                     // 0xa8
    int xac;                     // 0xac
    int xb0;                     // 0xb0
    int xb4;                     // 0xb4
    int xb8;                     // 0xb8
    int xbc;                     // 0xbc
    int xc0;                     // 0xc0
    int xc4;                     // 0xc4
    u8 xc8;                      // 0xc8
    int xcc;                     // 0xcc
    int xd0;                     // 0xd0
    int xd4;                     // 0xd4
    int xd8;                     // 0xd8
    int xdc;                     // 0xdc
    int xe0;                     // 0xe0
    int xe4;                     // 0xe4
    int xe8;                     // 0xe8
    u8 xec;                      // 0xec
    int xf0;                     // 0xf0
    int xf4;                     // 0xf4
    int xf8;                     // 0xf8, flags
    CPULeaderLog leader_log[30]; // 0xfc, contains a log of per frame data about the followers leader
    void *unk_curr;              // 0x444
    void *scenario_curr;         // 0x448, cpu scenario not updated if this contains a pointer @ 800b27b8
    void *scenario_curr2;        // 0x44c, cpu scenario not updated if this contains a pointer @ 800b27c4
    void *x450;                  // 0x450
    u8 cmdscript_queue[256];     // 0x454, list of command ids for the follower to execute
    void *cmdscript_curr;        // 0x554, points to a command in the cmdscript queue
} CPU;

typedef struct _Fighter
{
	HSD_GObj *x0_fighter;
    int kind;                                                  // 0x4
    int x8_spawn_num;                                          // 0x8
    u8 xC_playerID;                                                  // 0xC
    char xd;                                                   // 0xD
    char xe;                                                   // 0xE
    char xf;                                                   // 0xF
    int state_id;                                              // 0x10
    int action_id;                                             // 0x14
    int common_state_num;                                      // 0x18
    FtState *ftstates_common;                                  // 0x1C
    FtState *ftstates_special;                                 // 0x20
    FtAction *ftaction;                                        // 0x24
    u16 *dynamics_data;                                        // 0x28
    float x2C_facing_direction;                                    // 0x2C
    float x30_facing_direction_repeated;                           // 0x30
    Vec3 x34_scale;                                                // 0x34
    int pointer_to_next_linked_list;                           // 0x40 TODO: This can't be a pointer, func_80067C98(Fighter*) calls func_800804EC(Fighter*) which returns fighter->x34*fighter->x40 as a float multiplication, so this must be a float
    int pointer_to_0x40__pointer_to_prev_linked_list;          // 0x44
    int length_of_linked_list;                                 // 0x48
    int x4c;                                                   // 0x4C
    int x50;                                                   // 0x50
    int x54;                                                   // 0x54
    int x58;                                                   // 0x58
    int x5C;                                                   // 0x5C
    int x60;                                                   // 0x60
    int x64;                                                   // 0x64
    int x68;                                                   // 0x68
    int x6C;                                                   // 0x6C
    int x70;                                                   // 0x70
	// physics struct
	Vec3 x74_anim_vel;
	Vec3 x80_self_vel;
	Vec3 x8c_kb_vel;
	Vec3 x98_atk_shield_kb;
	Vec3 xa4_unk_vel;
	Vec3 xB0_pos;
	Vec3 xBC_pos_prev;
	Vec3 xc8_pos_delta;
	Vec3 xd4_unk_vel;
	u32 xE0_airState;
	float xe4_ground_accel_1;
	float xe8_ground_accel_2;
	float xec_ground_vel;
	float xf0_ground_kb_vel;
	float xf4_ground_attacker_shield_kb_vel;
	Vec2 xF8_player_nudge_vel;
	float x100;
	// end physics struct

	int *x104_costume_JObjDesc;
	int *x108_costume_archive;

	ftData* x10C_ftData;

    struct attr
    {
        float x110_walk_initial_velocity;
        float x114_walk_acceleration;
        float x118_walk_maximum_velocity;
        float x11c_slow_walk_max;
        float x120_mid_walk_point;
        float x124_fast_walk_min;
        float x128_ground_friction; // used
        float x12c_dash_initial_velocity;
        float x130_dashrun_acceleration_a;
        float x134_dashrun_acceleration_b;
        float x138_dashrun_terminal_velocity;
        float x13c_run_animation_scaling;
        float x140_max_runbrake_frames;
        float x144_grounded_max_horizontal_velocity;
        float x148_jump_startup_time;
        float x14c_jump_h_initial_velocity;
        float x150_jump_v_initial_velocity;
        float x154_ground_to_air_jump_momentum_multiplier;
        float x158_jump_h_max_velocity;
        float x15c_hop_v_initial_velocity;
        float x160_air_jump_v_multiplier;
        float x164_air_jump_h_multiplier;
        int   x168_max_jumps;
        float x16c_gravity;
        float x170_terminal_velocity;
        float x174_aerialDriftStickMult;
        float x178_aerialDriftBase;
        float x17c_aerialDriftMax;
        float x180_aerialFriction;
        float x184_fastfall_velocity;
        float x188_horizontal_air_mobility_constant;
        int   x18c_jab_2_input_window;
        int   x190_jab_3_input_window;
        int   x194_frames_to_change_direction_on_standing_turn;
        float x198_weight;
        float x19c_model_scaling;
        float x1a0_initial_shield_size;
        float x1a4_shield_break_initial_velocity;
        int   x1a8_rapid_jab_window;
        int   x1ac_unk;
        int   x1b0_unk;
        int   x1b4_unk;
        float x1b8_ledge_jump_horizontal_velocity;
        float x1bc_ledge_jump_vertical_velocity;
        float x1c0_item_throw_velocity_multiplier;
        int   x1c4_unk;
        int   x1c8_unk;
        int   x1cc_unk;
        int   x1d0_unk;
        int   x1d4_unk;
        int   x1d8_unk;
        int   x1dc_unk;
        int   x1e0_unk;
        int   x1e4_unk;
        int   x1e8_unk;
        int   x1ec_unk;
        float x1f0_kirby_b_star_damage;
        float x1f4_normal_landing_lag;
        float x1f8_n_air_landing_lag;
        float x1fc_f_air_landing_lag;
        float x200_b_air_landing_lag;
        float x204_u_air_landing_lag;
        float x208_d_air_landing_lag;
        float x20c_nametag_height;
        int   x210_unk;
        float x214_wall_jump_horizontal_velocity;
        float x218_wall_jump_vertical_velocity;
        int   x21c_unknown21C;
        float x220_trophy_scale;
        int   x224_unk;
        int   x228_unk;
        int   x22c_unk;
        int   x230_unk;
        int   x234_unk;
        int   x238_unk;
        int   x23c_unk;
        int   x240_unk;
        int   x244_unk;
        int   x248_unk;
        int   x24c_unk;
        int   x250_unk;
        int   x254_unk;
        int   x258_unk;
        float x25c_bubble_ratio;
        int   x260_unk;
        int   x264_unk;
        int   x268_unk;
        int   x26c_unk;
        float x270_respawn_platform_scale;
        int   x274_unk;
        int   x278_unk;
        int   x27c_camera_zoom_target_bone;
        int   x280_unk;
        int   x284_unk;
        int   x288_unk;
        int   x28c_special_jump_action___1;
        int   x290_weight_dependent_throw_speed_flags;
    } attr;

	struct
    {
        Vec2 ground_light_offset; // 0x294
        Vec2 ground_light_size;   // 0x29C
        Vec2 ground_heavy_offset; // 0x2A4
        Vec2 ground_heavy_size;   // 0x2AC
        Vec2 air_light_offset;    // 0x2B4
        Vec2 air_light_size;      // 0x2BC
    } itpickup;
    float jostle_offset;                   // 0x2C4
    float jostle_range;                    // 0x2C8
    int x2CC;                              // 0x2CC
    FtMultiJumpDesc* x2D0_multi_jump_desc;      // 0x2D0
    void* x2D4_specialAttributes;
    void* x2D8_specialAttributes2;
    int x2DC;                              // 0x2DC
    int x2E0;                              // 0x2E0
    int x2E4;                              // 0x2E4
    int x2E8;                              // 0x2E8
    int x2EC;                              // 0x2EC
    FtDynamicBoneset dynamics_boneset[10]; // 0x2f0
    int dynamics_num;                      // 0x3E0
    struct script                          //  0x3E4
    {                                      //
        float script_event_timer;          // 0x3E4
        float script_frame_timer;          // 0x3E8
        int *script_current;               // 0x3EC
        int script_loop_num;               // 0x3F0
        int *script_return;                // 0x3F4
    } script;                              //
    int unk;                               // 0x3F8
    int unk3FC;                            // 0x3FC
    int pointer_to_0x460;                  // 0x400
    int pointer_to_0x3c0;                  // 0x404
    ColorOverlay color[3];                 // 0x408
    void *LObj;                            // 0x588
    int anim_num;                          // 0x58C
    void *anim_curr_flags_ptr;             // 0x590
	u8 x594_anim_curr_flags_1; // used
	u8 x594_anim_curr_flags_2; // used
	u8 x594_anim_curr_flags_3; // used
	u8 x594_anim_curr_flags_4; // used
	void *anim_requested;                     // 0x598
    void *anim_cache_curr;                    // 0x59C
    void *anim_cache_persist;                 // 0x5A0
    void *anim_curr_ARAM;                     // 0x5A4
    void *anim_persist_ARAM;                  // 0x5A8
    int dobj_toggle_num;                      // 0x5AC
    int x5B0;                                 // 0x5B0
    int x5B4;                                 // 0x5B4
    int x5B8;                                 // 0x5B8
    int x5BC;                                 // 0x5BC
    int x5C0;                                 // 0x5C0
    int x5C4;                                 // 0x5C4
    int x5C8;                                 // 0x5C8
    int x5CC;                                 // 0x5CC
    int x5D0;                                 // 0x5D0
    int x5D4;                                 // 0x5D4
    int x5D8;                                 // 0x5D8
    int x5DC;                                 // 0x5DC
    int x5E0;                                 // 0x5E0
    int x5E4;                                 // 0x5E4
    FighterBone* x5E8_fighterBones;
    int bone_num;                             // 0x5EC
    int bone_arr;                             // 0x5F0
    u16 dobj_toggle[12];                      // 0x5f4
    void *gfx;                              // 0x60C
    int x610;                                 // 0x610
    int x614;                                 // 0x614
    s8 x618_playerControllerNumber;            // 0x618
    s8 x619_costumeID;                          // 0x619
    char color_overlay_id;                    // 0x61A
    u8 team;                                  // 0x61B
    u8 x61C;
    char x61D;                                // 0x61E
    char x61F;                                // 0x61F
    struct input                              // input data
    {                                         //
        Vec2 lstick;                          // 0x620
        Vec2 lstick_prev;                     // 0x628
        int x630;                             // 0x630
        int x634;                             // 0x634
        Vec2 cstick;                          // 0x638
        int x640;                             // 0x640
        int x644;                             // 0x644
        int x648;                             // 0x648
        int x64C;                             // 0x64C
        float trigger;                        // 0x650
        int x654;                             // 0x654
        int x658;                             // 0x658
        int held;                             // 0x65C
        int held_prev;                        // 0x660
        int x664;                             // 0x664
        int down;                             // 0x668
        int x66C;                             // 0x66C
        char timer_lstick_tilt_x;             // 0x670
        char timer_lstick_tilt_y;             // 0x671
        char timer_trigger_analog;            // 0x672
        char timer_lstick_smash_x;            // 0x673
        char timer_lstick_smash_y;            // 0x674
        char timer_trigger_digital;           // 0x675
        char timer_lstick_any_x;              // 0x676
        char timer_lstick_any_y;              // 0x677
        char timer_trigger_any;               // 0x678
        char x679;                            // 0x679
        char x67A;                            // 0x67A
        char x67B;                            // 0x67B
        char timer_a;                         // 0x67C
        char timer_b;                         // 0x67D
        char timer_xy;                        // 0x67E
        char timer_trigger_any_ignore_hitlag; // 0x67F
        char timer_LR;                        // 0x680
        char timer_padup;                     // 0x681
        char timer_paddown;                   // 0x682
        char timer_item_release;              // 0x683
        char since_rapid_lr;                  // 0x684
        char timer_jump;                      // 0x685
        char timer_specialhi;                 // 0x686
        char timer_speciallw;                 // 0x687
        char timer_specials;                  // 0x688
        char timer_specialn;                  // 0x689
        char timer_jump_lockout;              // 0x68A
        char timer_specialhi_lockout;         // 0x68B
    } input;                                  //
    Vec3 x68C_transN_pos;                          // x68c
    Vec3 transN_pos_prev;                     // 0x698
    Vec3 x6A4_transN_offset;                       // 0x6A4
    Vec3 transN_offset_prev;                  // 0x6B0
    float x6BC_input_stickangle;                   // 0x6BC
    f32 x6C0;                                 // 0x6C0
    f32 x6C4;                                 // 0x6C4
    f32 x6C8;                                 // 0x6C8
    int x6CC;                                 // 0x6CC
    int x6D0;                                 // 0x6D0
    int x6D4;                                 // 0x6D4
    f32 x6D8;                                 // 0x6D8
    f32 x6DC;                                 // 0x6DC
    f32 x6E0;                                 // 0x6E0
    int x6E4;                                 // 0x6E4
    int x6E8;                                 // 0x6E8
    int x6EC;    
	CollData coll_data; // 0x6F0

	void *cameraBox;                     // 0x890

    // animation
    float x894_anim_frame; // 0x894, current frame of the animation
    float x898;    // 0x898
    float x89C_anim_rate;  // 0x89C, current speed rate of the animation
    float x8A0;    // 0x8a0
    float x8A4_anim_blend; // 0x8a4, current interpolation value of the animation
    int x8A8;    // 0x8a8
        
    JOBJ *anim_skeleton;           // 0x8ac
    int x8b0;                      // 0x8b0
    int x8b4;                      // 0x8b4
    int x8b8;                      // 0x8b8
    int x8bc;                      // 0x8bc
    int curr_hold_anim;            // 0x8c0
    int x8c4;                      // 0x8c4
    int x8c8;                      // 0x8c8
    int x8cc;                      // 0x8cc
    int x8d0;                      // 0x8d0
    int x8d4;                      // 0x8d4
    int x8d8;                      // 0x8d8
    int x8dc;                      // 0x8dc
    int x8e0;                      // 0x8e0
    int x8e4;                      // 0x8e4
    int x8e8;                      // 0x8e8
    int x8ec;                      // 0x8ec
    int x8f0;                      // 0x8f0
    int x8f4;                      // 0x8f4
    int x8f8;                      // 0x8f8
    int x8fc;                      // 0x8fc
    int x900;                      // 0x900
    int x904;                      // 0x904
    int x908;                      // 0x908
    int x90c;                      // 0x90c
    int x910;                      // 0x910
    ftHit hitbox[4];               // 0x914
    ftHit throw_hitbox[2];         // 0xdf4
    ftHit x1064_thrown_hitbox;           // 0x1064
    u8 team_unk;                   // 0x119c, friendly fire related
    u8 grabber_ply;                // 0x119D, slot ID of the person grabbing this fighter
    u8 hurt_num;                   // 0x119E, number of hurtboxes
    FtHurt hurtbox[15];            // 0x11A0
    int x1614;                     // 0x1614
    int x1618;                     // 0x1618
    int x161c;                     // 0x161c
    int x1620;                     // 0x1620
    int x1624;                     // 0x1624
    int x1628;                     // 0x1628
    int x162c;                     // 0x162c
    int x1630;                     // 0x1630
    int x1634;                     // 0x1634
    int x1638;                     // 0x1638
    int x163c;                     // 0x163c
    int x1640;                     // 0x1640
    int x1644;                     // 0x1644
    int x1648;                     // 0x1648
    int x164c;                     // 0x164c
    int x1650;                     // 0x1650
    int x1654;                     // 0x1654
    int x1658;                     // 0x1658
    int x165c;                     // 0x165c
    int x1660;                     // 0x1660
    int x1664;                     // 0x1664
    int x1668;                     // 0x1668
    int dynamics_hit_num;          // 0x166c
    FtDynamicHit dynamics_hit[11]; // 0x1670
    int x1828;                     // 0x1828

	// damage struct
	int x182c_behavior;
	float x1830_percent;
	f32 x1834;
	float x1838_percent_temp;
	s32 x183C;
	int x1840;
	float x1844_direction;
	int x1848_kb_angle;
	int x184c_damaged_hurtbox;
	float x1850_force_applied;
	Vec3 x1854_collpos;
	int x1860_dealt;
	int x1864;
	HSD_GObj *x1868_source;
	int x186c;
	int x1870;
	int x1874;
	int x1878;
	int x187c;
	int x1880;
	int x1884;
	int x1888;
	int x188c;
	int x1890;
	int x1894;
	int x1898;
	f32 x189C;
	f32 x18A0;
	f32 x18A4_knockbackMagnitude; // used
	f32 x18A8;
	int x18ac_time_since_hit;
	f32 x18B0;
	f32 x18b4_armor;
	f32 x18B8;
	f32 x18BC;
	int x18C0;
	int x18C4_source_playerID;
	int x18C8;
	int x18CC;
	int x18D0;
	int x18d4;
	int x18d8;
	int x18dc;
	int x18e0;
	int x18e4;
	int x18e8;
	u16 x18ec_instancehitby; // Last Move Instance This Player Was Hit by
	int x18F0;
	int x18F4;
	u8 x18F8;
	u8 x18f9;
	u16 x18FA_model_shift_frames;
	u8 x18FC;
	u8 x18FD;
	int x1900;
	int x1904;
	int x1908;
	int x190C;
	int x1910;
	int x1914;
	int x1918;
	f32 x191C;
	int x1920;
	int x1924;
	f32 x1928;
	int x192c;
	int x1930;
	int x1934;
	int x1938;
	int x193c;
	int x1940;
	int x1944;
	int x1948; // used
	int x194C; // used
	int x1950;
	f32 x1954;
	f32 x1958;
	float x195C_hitlag_frames;
	float x1960_vibrate_mult;
	float x1964;
	// end damage struct
	
    u8 x1968_jumps_used;           // 0x1968
    u8 x1969_walljumps_used;       // 0x1969
    float x196C_hitlag_mult;             // 0x196c
    int x1970;                     // 0x1970
    HSD_GObj* x1974_heldItem;
    HSD_GObj* x1978;
    int x197C;                     // 0x197c
    HSD_GObj *x1980_item_head;               // 0x1980
    HSD_GObj *x1984_item_held_spec;          // 0x1984, special held item
    struct hurtstatus              // 0x1988
    {                              //
        int x1988_script;                // 0x1988
        int x198C_game;                  // 0x198c
        int x1990_ledge_intang_left;     // 0x1990
        int x1994_respawn_intang_left;   // 0x1994
    } x1988_hurtstatus;                  //
    struct shield
    {
        float x1998_health;          // 0x1998
        float x199C_lightshield_amt; // 0x199c
        int x19A0_dmg_taken;         // 0x19a0, seems to be all damage taken during the frame, is reset at the end of the frame
        int x19A4_dmg_taken2;        // 0x19A4, idk there so many of these
        HSD_GObj *x19A8_dmg_source;      // 0x19a8, points to the entity that hit the shield
        float hit_direction;   // 0x19ac
        int hit_attr;          // 0x19b0, attribute of the hitbox that collided
        float x19B4;           // 0x19b4
        float x19B8;           // 0x19b8
        int x19BC_dmg_taken3;        // 0x19bc, seems to be the most recent amount of damage taken
    } shield;
    struct shield_bubble // 0x19c0
    {
        JOBJ *bone;                   // 0x19c0
        unsigned char is_checked : 1; // 0x19d0 0x80. is checked for collision when 0
        Vec3 pos;                     // 19d4
        Vec3 offset;                  // 0x19d4
        float size_mult;              // 0x19e0
    } shield_bubble;
    struct reflect_bubble // 0x19e4
    {
        JOBJ *bone;                   // 0x19e4
        unsigned char is_checked : 1; // 0x19d0 0x80. is checked for collision when 0
        Vec3 pos;                     // 0x19d4
        Vec3 offset;                  // 0x19f8
        float size_mult;              // 0x1a04
    } reflect_bubble;
    struct absorb_bubble // 0x1a08
    {
        JOBJ *bone;                   // 0x1a08
        unsigned char is_checked : 1; // 0x1a0c 0x80. is checked for collision when 0
        Vec3 pos;                     // 0x1a10
        Vec3 offset;                  // 0x1a1c
        float size_mult;              // 0x1a28
    } absorb_bubble;
    struct reflect_hit                    // 0x1A2C
    {                                     //
        float x1A2C_hit_direction;              // 0x1A2C
        int max_dmg;                      // 0x1a30
        float dmg_mult;                   // 0x1a34
        int is_break;                     // 0x1a38
    } reflect_hit;                        //
    struct absorb_hit                     
    {                                     //
        int x1A3C;                        // 0x1A3C
        float x1A40_hit_direction;              // 0x1A40
        int x1A44_dmg_taken;                    // 0x1A44
        int x1A48_hits_taken;                   // 0x1A48
    } absorb_hit;                         //
    struct grab                           // 0x1a4c
    {                                     //
        float grab_timer;                 // 0x1a4c
        s8 x1A50, x1A51, x1A52, x1A53;
        int x1a54;                        // 0x1a54
        HSD_GObj *x1A58_attacker;                   // 0x1a58
        HSD_GObj *x1A5C_victim;                     // 0x1a5c
        int x1A60;                        // 0x1a60
        int x1A64;                        // 0x1a64
        u16 x1A68;                        // 0x1a68
        u16 vuln;                         // 0x1a6a
        int x1a6c;                        // 0x1a6c
        int x1a70;                        // 0x1a70
        Vec2 release_pos;                 // 0x1a74, this is determined when instantiating the player, its actually the offset of XRotN from TopN (800690d0)
        int x1a7c;                        // 0x1a7c
        int x1a80;                        // 0x1a80
        int x1a84;                        // 0x1a84
    } grab;                               //
    CPU cpu;                              // 0x1a88
	int x1fe0;
    int x1fe4;
    int x1fe8;
    int x1fec;
    int x1ff0;
    int x1ff4;
    int x1ff8;
    int x1ffc;
    int x2000;
    int x2004;
    int x2008;
    int x200C;
    int x2010;
    int x2014;
    int x2018;
    int x201c;
    int x2020;
    int x2024;
    int x2028;
    int x202C;
    int x2030;
    int x2034;
    int x2038;
    int x203c;
    int x2040;
    int x2044;
    int x2048;
    int x204c;
    int x2050;
    int x2054;
    int x2058;
    int x205c;
    int x2060;
	s32 x2064_ledge_cooldown; // used
	int atk_kind;                         // 0x2068, non attacks have id 1
    int x206c;                            // 0x206c
    u8 x2070;                             // 0x2070
    u8 x2071_xf0 : 4;                     // 0x2071, 0xf0
    u8 x2071_x0f : 4;                     // 0x2071, 0x0f
    u8 x2072;                             // 0x2072
    u8 x2073;                             // 0x2073
    int x2074;                            // 0x2074, this is the start of some struct... present in items as well @ 0xd94
    int x2078;                            // 0x2078
    int x207c;                            // 0x207c
    int x2080;                            // 0x2080
    int x2084;                            // 0x2084
    u16 x2088_atk_instance;                     // 0x2088, Contains an ID unique to the current move instance. e.g, if two dairs are done back to back, this ID will differ to tell them apart from each other. It is stored to 0x18EC of the victim upon colliding with someone.
    int x208C;
    s16 x2090;
    s16 x2092;
    HSD_GObj* x2094_victim;                         // 0x2094
    s16 x2098;
    s16 x209A;
    s16 x209C;
    s16 x209E;
    JOBJ* x20A0_accessory;                      // 0x20a0
    int x20a4;                            // 0x20a4
    void* x20A8_shadow;                         // 0x20a8, ASSERTS @ 8037f7b8, describes multiple struct members
    int x20AC;                            // 0x20ac
    struct afterimage                     //
    {                                     //
        FtAfterImageKey key[3];    // 0x20b0
        float afterimage_bottom;          // 0x20f8
        float afterimage_top;             // 0x20fc
        s8 x2100_afterimage_state;              // 0x2100
        //unsigned char x2101_afterimage_num : 7; // 0x2101
        u8 x2101_1_to_7 : 7;
        u8 x2101_8 : 1;
    } afterimage;                         //
    int x2104;                            // 0x2104
	s32 x2108;
	u8 x210C, x210D, x210E, x210F;
    int x2110;                            // 0x2110
    struct smash                          // 0x2114
    {                                     //
        int state;                        // 0x2114 0 = none, 1 = pre-charge, 2 = charging, 3 = release
        int frame;                        // 0x2118 number of frames fighter has charged for
        float hold_frame;                 // 0x211c frame that charge begins/ends
        float dmg_mult;                   // 0x2120 damage multiplier
        float speed_mult;                 // 0x2124 speed multiplier?
        int x2128;                        // 0x2128
        int x212c;                        // 0x212c
        int is_sfx_played;                // 0x2130 bool for smash sfx?
        u8 x2134_vibrate_frame;                 // 0x2134
        u8 x2135;                        // 0x2135
        float x2138_since_hitbox;               // 0x2138
    } smash;                              //
    int x213C;                            // 0x213c
    f32 x2140;                            // 0x2140
    int x2144;                            // 0x2144
    int x2148;                            // 0x2148
    int x214C;                            // 0x214c
    int x2150;                            // 0x2150
    int x2154;                            // 0x2154
    int x2158;                            // 0x2158
    int x215C;                            // 0x215c
    int x2160;                            // 0x2160
    int x2164;                            // 0x2164
    int x2168;                            // 0x2168
    int x216C;                            // 0x216c
    f32 x2170;                            // 0x2170
    Vec3 x2174_thrown_origin;                   // 0x2174, offset of child from parent, used for placing the child when the grab breaks
    int x2180;                            // 0x2180
    int x2184;                            // 0x2184
    int x2188;                            // 0x2188
    int x218C;                            // 0x218c
	// callback struct
	void (*x2190_callback_OnGrabFighter_Self)(HSD_GObj *fighter);
	void (*x2194_callback_x2194)(HSD_GObj *fighter);
	void (*x2198_callback_OnGrabFighter_Victim)(HSD_GObj *fighter);
	void (*x219c_callback_IASA)(HSD_GObj *fighter);
	void (*x21a0_callback_Anim)(HSD_GObj *fighter);
	void (*x21a4_callback_Phys)(HSD_GObj *fighter); // used
	void (*x21a8_callback_Coll)(HSD_GObj *fighter);
	void (*x21ac_callback_Cam)(HSD_GObj *fighter);
	void (*x21b0_callback_Accessory1)(HSD_GObj *fighter);
	void (*x21B4_callback_Accessory2)(HSD_GObj *fighter);
	void (*x21B8_callback_Accessory3)(HSD_GObj *fighter);
	void (*x21BC_callback_Accessory4)(HSD_GObj *fighter);
	void (*x21C0_callback_OnGiveDamage)(HSD_GObj *fighter);
	void (*x21C4_callback_OnShieldHit)(HSD_GObj *fighter);
	void (*x21C8_callback_OnReflectHit)(HSD_GObj *fighter);
	void (*x21CC_callback_x21cc)(HSD_GObj *fighter);
	void (*x21d0_callback_EveryHitlag)(HSD_GObj *fighter); // used
	void (*x21d4_callback_EnterHitlag)(HSD_GObj *fighter);
	void (*x21d8_callback_ExitHitlag)(HSD_GObj *fighter);
	void (*x21dc_callback_OnTakeDamage)(HSD_GObj *fighter);
	void (*x21E0_callback_OnDeath)(HSD_GObj *fighter);
	void (*x21E4_callback_OnDeath2)(HSD_GObj *fighter); // internally Dead_Proc as evidenced by 800f5430
	void (*x21E8_callback_OnDeath3)(HSD_GObj *fighter);
	void (*x21ec_callback_OnActionStateChange)(HSD_GObj *fighter);
	void (*x21f0_callback_OnTakeDamage2)(HSD_GObj *fighter);
	void (*x21f4_callback_OnHurtboxDetect)(HSD_GObj *fighter);
	void (*x21f8_callback_OnSpin)(HSD_GObj *fighter);
	// end callback struct
	
	u8 filler_2210[0x2210-0x21fc];

	// flags struct:
    union
    {
        struct
        {
            u8 x2210_1 : 1;
            u8 x2210_2 : 1;
            u8 x2210_3_throw : 1;
            u8 x2210_4_throw_release : 1; // also used to change users direction during aerial attacks
            u8 x2210_5_throw_turn : 1;
            u8 x2210_6_throw : 1;
            u8 x2210_7 : 1;
            u8 x2210_8 : 1;
        };
        s32 x2210;
    };

	float x2214_throw_timerval;                    // equal to script_event_timer of the attacker

	u8 x2218_1 : 1;
	u8 x2218_2 : 1;
	u8 x2218_3 : 1;
	u8 x2218_4 : 1;
	u8 x2218_5 : 1;
	u8 x2218_6 : 1;
	u8 x2218_7 : 1;
	u8 x2218_8 : 1;

	u8 x2219_1 : 1;
	u8 x2219_2 : 1;
	u8 x2219_3 : 1;
	u8 x2219_4 : 1;
	u8 x2219_5 : 1;
	u8 x2219_6_freeze : 1;
	u8 x2219_7 : 1;
	u8 x2219_8 : 1;

	u8 x221A_1 : 1;
	u8 x221A_2 : 1;
	u8 x221A_3 : 1; // hitlag
	u8 x221A_4 : 1;
	u8 x221A_5 : 1; // fastfall
	u8 x221A_6 : 1; // no_hurt_script
	u8 x221A_7 : 1;
	u8 x221A_8 : 1; // gfx_persist

	u8 x221B_1 : 1; // shield enable
	u8 x221B_2 : 1;
	u8 x221B_3 : 1;
	u8 x221B_4 : 1;
	u8 x221B_5 : 1;
	u8 x221B_6 : 1;
	u8 x221B_7 : 1;
	u8 x221B_8 : 1;

    union
    {
        struct
        {
        u8 x221C_1 : 1;
        u8 x221C_2 : 1;
        u8 x221C_3 : 1;
        u8 x221C_4 : 1;
        u8 x221C_5 : 1;
        u8 x221C_6 : 1;
        u8 x221C_7_hitstun : 1; // used
        u8 x221C_8 : 1;

        u8 x221D_1 : 1;
        u8 x221D_2 : 1;
        u8 x221D_3 : 1;
        u8 x221D_4 : 1; // input enable
        u8 x221D_5 : 1;
        u8 x221D_6 : 1; // nudge disable
        u8 x221D_7 : 1; // ground ignore
        u8 x221D_8 : 1;
        };
        struct
        {
        u16 x221C_u16_x : 7;
        u16 x221C_u16_y : 3;
        u16 x221C_u16_z : 6;
        };
    };

	u8 x221E_1 : 1; // invisible
	u8 x221E_2 : 1;
	u8 x221E_3 : 1;
	u8 x221E_4 : 1; // is item visible
	u8 x221E_5 : 1;
	u8 x221E_6 : 1;
	u8 x221E_7 : 1;
	u8 x221E_8 : 1;
	u8 x221F_1 : 1; // is offscreen
	u8 x221F_2 : 1; // dead
	u8 x221F_3 : 1;
	u8 x221F_4_sleep : 1;
	u8 x221F_5 : 1; // slave
	u8 x221F_6 : 1;
	u8 x221F_7 : 1;
	u8 x221F_8 : 1;
	u8 x2220_1 : 1;
	u8 x2220_2 : 1;
	u8 x2220_3 : 1;
	u8 x2220_4 : 1;
	u8 x2220_5 : 1;
	u8 x2220_6 : 1;
	u8 x2220_7 : 1;
	u8 x2220_8 : 1;
	u8 x2221_1 : 1;
	u8 x2221_2 : 1;
	u8 x2221_3 : 1;
	u8 x2221_4 : 1;
	u8 x2221_5 : 1;
	u8 x2221_6 : 1;
	u8 x2221_7 : 1;
	u8 x2221_8 : 1;
	u8 x2222_1 : 1;
	u8 x2222_2 : 1;
	u8 x2222_3 : 1;
	u8 x2222_4 : 1;
	u8 x2222_5 : 1;
	u8 x2222_6 : 1;
	u8 x2222_7 : 1;
	u8 x2222_8 : 1;
	u8 x2223_1 : 1;
    u8 x2223_2 : 1;
    u8 x2223_3 : 1;
    u8 x2223_4 : 1;
    u8 x2223_5 : 1;
    u8 x2223_6 : 1;
    u8 x2223_7 : 1;
    u8 x2223_8 : 1;
	union
	{
		u8 x2224;
		struct{
			u8 x2224_1 : 1;
			u8 x2224_2 : 1;
			u8 x2224_3 : 1;
			u8 x2224_4 : 1;
			u8 x2224_5 : 1;
			u8 x2224_6 : 1;
			u8 x2224_7 : 1;
			u8 x2224_8 : 1;
		};
	};
	u8 x2225_1 : 1;
	u8 x2225_2 : 1;
	u8 x2225_3 : 1;
	u8 x2225_4 : 1;
	u8 x2225_5 : 1;
	u8 x2225_6 : 1;
	u8 x2225_7 : 1;
	u8 x2225_8 : 1;
	u8 x2226_1 : 1;
	u8 x2226_2 : 1;
	u8 x2226_3 : 1;
	u8 x2226_4 : 1;
	u8 x2226_5 : 1;
	u8 x2226_6 : 1;
	u8 x2226_7 : 1;
	u8 x2226_8 : 1;
	u8 x2227_1 : 1;
	u8 x2227_2 : 1;
	u8 x2227_3 : 1;
	u8 x2227_4 : 1;
	u8 x2227_5 : 1;
	u8 x2227_6 : 1;
	u8 x2227_7 : 1;
	u8 x2227_8 : 1;
	u8 x2228_1 : 1;
	u8 x2228_2 : 1;
	u8 x2228_3 : 1;
	u8 x2228_4 : 1;
	u8 x2228_5 : 1;
	u8 x2228_6 : 1;
	u8 x2228_7 : 1;
	u8 x2228_8 : 1;
	u8 x2229_1 : 1;
	u8 x2229_2 : 1;
	u8 x2229_3 : 1;
	u8 x2229_4 : 1;
	u8 x2229_5 : 1;
	u8 x2229_6 : 1;
	u8 x2229_7 : 1;
	u8 x2229_8 : 1;
	u8 x222a_1 : 1;
	u8 x222a_2 : 1;
	u8 x222a_3 : 1;
	u8 x222a_4 : 1;
	u8 x222a_5 : 1;
	u8 x222a_6 : 1;
	u8 x222a_7 : 1;
	u8 x222a_8 : 1;
	u8 x222b;
	struct //fighter_var
	{
		u32 x222C;
		u32 x2230;
		u32 x2234;
		u32 x2238;
		u32 x223C;
		u32 x2240;
		u32 x2244;
		u32 x2248;
		u32 x224C;
		u32 x2250;
		u32 x2254;
		u32 x2258;
		u32 x225C;
		u32 x2260;
		u32 x2264;
		u32 x2268;
		u32 x226C;
		u32 x2270;
		u32 x2274;
		u32 x2278;
		u32 x227C;
		u32 x2280;
		u32 x2284;
		u32 x2288;
		u32 x228C;
		u32 x2290;
		u32 x2294;
		u32 x2298;
		u32 x229C;
		u32 x22A0;
		u32 x22A4;
		u32 x22A8;
		u32 x22AC;
		u32 x22B0;
		u32 x22B4;
		u32 x22B8;
		u32 x22BC;
		u32 x22C0;
		u32 x22C4;
		u32 x22C8;
		u32 x22CC;
		u32 x22D0;
		u32 x22D4;
		u32 x22D8;
		u32 x22DC;
		u32 x22E0;
		u32 x22E4;
		u32 x22E8;
		u32 x22EC;
		u32 x22F0;
		u32 x22F4;
		u32 x22F8;
	}; //fighter_var;
} Fighter;

typedef struct ftCommonData
{
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20_lstick_tilt;
    float x24;
    float x28;
    float x2C;
    float x30;
    float x34;
    float x38;
    float x3C;
    float x40;
    float x44;
    float x48;
    float x4C;
    float x50;
    float x54;
    float x58;
    float x5C;
    float x60;
    float x64;
    float x68;
    float x6C_friction_mult;
    float x70_jumpaerial_lsticky;
    float x74_jumpaerial_lsticktimer;
    float x78;
    float x7C;
    float x80;
    float x84;
    float x88;
    float x8C;
    float x90_lstick_rebirthfall;
    float x94;
    float x98;
    float x9C;
    float xA0;
    float xA4;
    float xA8;
    float xAC;
    float xB0;
    float xB4;
    float xB8;
    float xBC;
    float xC0;
    float xC4;
    float xC8;
    float xCC;
    float xD0;
    float xD4;
    float xD8;
    float xDC;
    float xE0;
    float xE4;
    float xE8;
    float xEC;
    float xF0;
    float xF4;
    float xF8;
    float xFC;
    float x100_kb_mult;
    float x104;
    float x108;
    float x10C;
    float x110;
    float x114;
    float x118;
    float x11C;
    float x120;
    float x124;
    float x128;
    float x12C;
    float x130;
    float x134;
    float x138;
    float x13C;
    float x140;
    float x144;
    float x148;
    float x14C;
    float x150;
    float x154;
    float x158;
    float x15C;
    float x160;
    float x164;
    float x168;
    float x16C_kb_maxVelX;
    float x170;
    float x174;
    float x178;
    float x17C;
    float x180;
    float x184;
    float x188;
    float x18C;
    float x190;
    float x194;
    float x198;
    float x19C;
    float x1A0;
    float x1A4;
    float x1A8_tdi_maxAngle;
    float x1AC;
    float x1B0;
    float x1B4;
    float x1B8;
    float x1BC_kb_bounceDecay;
    float x1C0;
    float x1C4;
    float x1C8;
    float x1CC;
    float x1D0;
    float x1D4;
    float x1D8;
    float x1DC;
    float x1E0;
    float x1E4;
    float x1E8;
    float x1EC;
    float x1F0;
    float x1F4;
    float x1F8;
    float x1FC;
    float x200;
    float x204_kb_frameDecay;
    float x208;
    float x20C;
    float x210;
    float x214;
    float x218;
    float x21C;
    float x220;
    float x224;
    float x228;
    float x22C;
    float x230;
    float x234;
    float x238;
    float x23C;
    float x240;
    float x244;
    float x248;
    float x24C;
    float x250;
    float x254;
    float x258;
    float x25C;
    float x260;
    float x264;
    float x268;
    float x26C;
    float x270;
    float x274;
    float x278;
    float x27C;
    float x280;
    float x284;
    float x288;
    float x28C;
    float x290;
    float x294;
    float x298;
    float x29C;
    float x2A0;
    float x2A4;
    float x2A8;
    float x2AC;
    float x2B0;
    float x2B4;
    float x2B8;
    float x2BC;
    float x2C0;
    float x2C4;
    float x2C8;
    float x2CC;
    float x2D0;
    float x2D4;
    float x2D8;
    float x2DC;
    float x2E0;
    float x2E4;
    float x2E8;
    float x2EC;
    float x2F0;
    float x2F4;
    float x2F8;
    float x2FC;
    float x300;
    float x304;
    float x308;
    float x30C;
    float x310;
    float x314;
    float x318;
    float x31C;
    float x320;
    float x324;
    float x328;
    float x32C;
    float x330;
    float x334;
    float x338_escapeair_vel;
    float x33C_escapeair_veldecaymult;
    float x340;
    float x344;
    float x348;
    float x34C;
    float x350;
    float x354;
    float x358;
    float x35C;
    float x360;
    float x364;
    float x368;
    float x36C;
    float x370;
    float x374;
    float x378;
    float x37C;
    float x380;
    float x384;
    float x388;
    float x38C;
    float x390;
    float x394;
    float x398;
    float x39C;
    float x3A0;
    float x3A4;
    float x3A8;
    float x3AC;
    float x3B0;
    float x3B4;
    float x3B8;
    float x3BC;
    float x3C0;
    float x3C4;
    float x3C8;
    float x3CC;
    float x3D0;
    float x3D4;
    float x3D8;
    float x3DC;
    float x3E0;
    float x3E4;
    float x3E8_shield_kb_frameDecay;
    float x3EC;
    float x3F0;
    float x3F4;
    float x3F8;
    float x3FC;
    float x400;
    float x404;
    float x408;
    float x40C;
    float x410;
    float x414;
    float x418;
    float x41C;
    float x420;
    float x424;
    float x428;
    float x42C;
    float x430;
    float x434;
    float x438;
    float x43C;
    float x440;
    float x444;
    float x448;
    float x44C;
    float x450;
    float x45C_zjostle_frame;
    float x460_zjostle_max;
    float x45C_ms_zjostle_frame;
    float x460_ms_zjostle_max;
    float x464;
    float x468;
    float x46C;
    float x470;
    float x474;
    float x478;
    float x47C;
    float x480;
    float x484;
    float x488;
    float x48C;
    float x490;
    float x494;
    float x498;
    int x49C_cliff_invuln_time;
    float x4A0;
    float x4A4;
    float x4A8;
    float x4AC;
    float x4B0_asdi_mag;
    float x4B4;
    float x4B8;
    float x4BC_asdi_units;
    float x4C0;
    float x4C4;
    float x4C8;
    float x4CC;
    float x4D0;
    float x4D4;
    float x4D8;
    float x4DC;
    float x4E0;
    float x4E4;
    float x4E8;
    float x4EC;
    float x4F0;
    float x4F4;
    float x4F8;
    float x4FC;
    float x500;
    float x504;
    float x508;
    float x50C;
    float x510;
    float x514;
    float x518;
    float x51C;
    float x520;
    float x524;
    float x528;
    float x52C;
    float x530;
    float x534;
    float x538;
    float x53C;
    float x540;
    float x544;
    float x548;
    float x54C;
    float x550;
    float x554;
    float x558;
    float x55C;
    float x560;
    float x564;
    float x568;
    float x56C;
    float x570;
    float x574;
    float x578;
    float x57C;
    float x580;
    float x584;
    float x588;
    float x58C;
    float x590;
    float x594;
    float x598;
    float x59C;
    float x5A0;
    float x5A4;
    float x5A8;
    float x5AC;
    float x5B0;
    float x5B4;
    float x5B8;
    float x5BC;
    float x5C0;
    float x5C4;
    float x5C8;
    float x5CC;
    float x5D0;
    float x5D4;
    float x5D8;
    float x5DC;
    float x5E0;
    float x5E4;
    float x5E8;
    float x5EC;
    float x5F0;
    float x5F4;
    float x5F8;
    float x5FC;
    float x600;
    float x604;
    float x608;
    float x60C;
    float x610;
    float x614;
    float x618;
    float x61C;
    float x620;
    float x624;
    float x628;
    float x62C;
    float x630;
    float x634;
    float x638;
    float x63C;
    float x640;
    float x644;
    float x648;
    float x64C;
    float x650;
    float x654;
    float x658;
    float x65C;
    float x660;
    float x664;
    float x668;
    float x66C;
    float x670;
    float x674;
    float x678;
    float x67C;
    float x680;
    float x684;
    float x688;
    float x68C;
    float x690;
    float x694;
    float x698;
    float x69C;
    float x6A0;
    float x6A4;
    float x6A8;
    float x6AC;
    float x6B0;
    float x6B4;
    float x6B8;
    float x6BC;
    float x6C0;
    float x6C4;
    float x6C8;
    float x6CC;
    float x6D0;
    float x6D4;
    float x6D8;
    float x6DC;
    float x6E0;
    float x6E4;
    float x6E8;
    float x6EC;
    float x6F0;
    float x6F4;
    float x6F8;
    float x6FC;
    float x700;
    float x704;
    float x708;
    float x70C;
    float x710;
    float x714;
    float x718;
    float x71C;
    float x720;
    float x724;
    float x728;
    float x72C;
    float x730;
    float x734;
    float x738;
    float x73C;
    float x740;
    float x744;
    float x748;
    float x74C;
    float x750;
    float x754;
    float x758;
    float x75C;
    float x760;
    float x764;
    float x768;
    float x76C;
    float x770;
    float x774;
    float x778;
    float x77C;
    float x780;
    float x784;
    float x788;
    float x78C;
    float x790;
    float x794;
    float x798;
    float x79C;
    float x7A0;
    float x7A4;
    float x7A8;
    float x7AC;
    float x7B0;
    float x7B4;
    float x7B8;
    float x7BC;
    float x7C0;
    float x7C4;
    float x7C8;
    float x7CC;
    float x7D0;
    float x7D4;
    float x7D8;
    float x7DC;
    float x7E0;
    float x7E4;
    float x7E8;
    float x7EC;
    float x7F0;
    float x7F4;
    float x7F8;
    float x7FC;
    float x800;
    float x804;
    float x808;
    float x80C;
    float x810;
} ftCommonData;

#endif

#ifndef _mncharsel_h_
#define _mncharsel_h_

#include <platform.h>
#include <baselib/forward.h>

#include <common_structs.h>

typedef enum _Mode {
    Mode_Time,
    Mode_Stock,
    Mode_Coin,
    Mode_Bonus
} Mode;

typedef enum _StageSelectMode {
    StageSelectMode_On,
    StageSelectMode_Random,
    StageSelectMode_Ordered,
    StageSelectMode_Turns,
    StageSelectMode_Loser
} StageSelectMode;

typedef struct _PlayerInitData {
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
} PlayerInitData;

typedef struct _StartMeleeRules {
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
} StartMeleeRules;

typedef struct _StartMeleeData {
    StartMeleeRules rules;
    PlayerInitData players[6];
} StartMeleeData;

typedef struct _VsModeData {
    s8 loser;
    u32 ordered_stage_index;
    s8 winner;
    u8 unk_0x3;
    u8 unk_0x4;
    u8 unk_0x5;
    u8 unk_0x6;
    u8 unk_0x7;
    StartMeleeData data;
} VsModeData;

typedef struct _CSSData {
    u8 unk_0x0;
    u8 unk_0x1;
    u8 match_type;
    u8 pending_scene_change;
    u8* ko_star_counts;
    VsModeData data;
} CSSData;

TextKerning* mnCharSel_8025BC20(TextKerning* arg0, u32 arg1);
void mnCharSel_8025BD30(void);

#endif

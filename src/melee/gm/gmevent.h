#ifndef GALE01_1BA8FC
#define GALE01_1BA8FC

#include <melee/ft/forward.h>
#include <melee/it/forward.h>

#include <dat_macros.h>

#include <melee/gm/types.h>

/// @todo ::PlayerInitData
typedef struct gm_801BAB40_src {
    /* 0x00 */ s8 c_kind;
    /* 0x01 */ u8 slot_type;
    /* 0x02 */ u8 stocks;
    /* 0x03 */ u8 color;
    /* 0x04 */ u8 x5;
    /* 0x05 */ u8 sub_color;
    /* 0x06 */ u8 team;
    /* 0x07 */ u8 xB;
    /* 0x08 */ u8 flags;
    /* 0x09 */ u8 xE;
    /* 0x0A */ u8 cpu_level;
    /* 0x0B */ u8 pad;
    /* 0x0C */ u16 x12;
    /* 0x0E */ u16 hp;
    /* 0x10 */ f32 x18;
    /* 0x14 */ f32 x1C;
    /* 0x18 */ f32 x20;
} gm_801BAB40_src;

struct gm_event_char_list {
    u8 c_kind[33];
};

/// Per-level match init data; shares its first two bytes' bitfield layout
/// with #StartMeleeRules.
struct gm_evinit {
    /* 0x00 */ u32 x0_0 : 3;
    /* 0x00 */ u32 x0_3 : 3;
    /* 0x00 */ u32 x0_6 : 1;
    /* 0x00 */ u32 x0_7 : 1;
    /* 0x01 */ u32 x1_0 : 1;
    /* 0x01 */ u32 x1_1 : 1;
    /* 0x01 */ u32 x1_2 : 1;
    /* 0x01 */ u32 x1_3 : 1;
    /* 0x01 */ u32 x1_4 : 1;
    /* 0x01 */ u32 x1_5 : 3;
    /* 0x02 */ u8 is_teams;
    /* 0x03 */ s8 item_freq;
    /* 0x04 */ s8 sd_penalty;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u16 stkind;
    /* 0x08 */ u32 time_limit;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ u64 x10;
    /* 0x18 */ s32 x18; // ItemKind?
    /* 0x1C */ f32 x1C;
    /* 0x20 */ f32 game_speed;
    /* 0x24 */ f32 unk24;
};

/// Per-round stage and opponent table, for levels with multiple rounds.
struct gm_evstage_table {
    /* 0x00 */ u8 count;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ u16 stage[7];
    /* 0x10 */ struct gm_801BAB40_src* entries[GM_MAX_PLAYERS];
};

struct gm_evbonus {
    /* 0x00 */ s8 c_kind;
    /* 0x01 */ u8 x1;
    /* 0x02 */ u8 x2;
    /* 0x03 */ u8 x3;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 color;
    /* 0x07 */ u8 pad7;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ u8 flags;
    /* 0x15 */ u8 x15;
    /* 0x16 */ u8 x16;
    /* 0x17 */ u8 x17;
};

struct gm_804D6900_x4_t {
    int x0;
    intptr_t x4 DAT_TYPE(gm_801BAB40_src);
};

struct gm_804D6900_t {
    /* 0x00 */ u8 kind;
    /* 0x01 */ u8 flags; ///< top 3 bits: player count
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ struct gm_804D6900_x4_t* x4;
    /* 0x08 */ struct gm_evinit* evinit;
    /* 0x0C */ struct gm_evbonus* evbonus;
    /* 0x10 */ struct gm_evstage_table* evstage_table;
    /* 0x14 */ struct gm_801BAB40_src* player_init[GM_MAX_PLAYERS];
};

/* 1BA8FC */ void gm_801BA8FC(void);
/* 1BBA60 */ void gm_Mode_Event_OnInit(void);
/* 1BBEA8 */ void gm_Mode_Event_OnLoad(void);
/* 1BBFE4 */ void gm_Mode_Event_OnUnload(void);
/* 1BEB68 */ void gm_801BEB68(int);
/* 1BEB74 */ void gm_801BEB74(u8);
/* 1BEB80 */ u8 gm_801BEB80(void);
/* 1BEB8C */ bool gm_801BEB8C(u8);
/* 1BEBA8 */ u8 gm_801BEBA8(u8);
/* 1BEBC0 */ u8 gm_801BEBC0(u8);
/* 1BEBF8 */ u8 gm_801BEBF8(u8 arg0);
/* 1BEC54 */ ItemKind* gm_801BEC54(void);
/* 1BEFA4 */ void gm_801BEFA4(int ckind);
/* 1BEFB0 */ CharacterKind gm_801BEFB0(void);
/* 1BEFC0 */ void gm_801BEFC0(int);
/* 1BEFD0 */ int gm_801BEFD0(void);
/* 1BEFE0 */ void gm_801BEFE0(s8);
/* 1BF000 */ void gm_801BF000(s8);
/* 1BF010 */ int gm_801BF010(void);
/* 1BF020 */ void gm_801BF020(s8);
/* 1BF040 */ void gm_801BF040(s8);
/* 1BF050 */ int gm_801BF050(void);
/* 1BF128 */ void gm_SetupTitleDemo(void);
/* 1BF3F8 */ void gm_PreloadTitleDemo(void);
/* 1BF6D8 */ int gm_801BF6D8(void);
/* 1BF6F8 */ int gm_801BF6F8(void);
/* 1BF708 */ void gm_801BF708(s8);
/* 1BF718 */ u8 gm_801BF718(void);
/* 3DF94C */ extern gm_803DF94C_t* gm_803DF94C[];

#endif

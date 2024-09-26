#ifndef MELEE_GM_TYPES_H
#define MELEE_GM_TYPES_H

#include "gm/forward.h" // IWYU pragma: export

#include <common_structs.h>
#include <placeholder.h>

struct gmm_x1CB0 {
    u8 padding_x0[0x16 - 0x0];
    /* 0x1CC6 0x16 */ u8 saved_language;
    u8 padding_x16[0x20 - 0x16 - 1];
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
    } bits;
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
    /*0x00*/ u8 unk_x0;
    /*0x01*/ u8 unk_x1;
    /*0x02*/ u8 mode;
    /*0x03*/ u8 time_limit;
    /*0x04*/ u8 stock_count;
    /*0x05*/ u8 handicap;
    /*0x06*/ u8 damage_ratio;
    /*0x07*/ u8 unk_x7;
    /*0x08*/ u8 stock_time_limit;
    /*0x09*/ u8 friendly_fire;
    /*0x0A*/ u8 pause;
    /*0x0B*/ u8 score_display;
    /*0x0C*/ u8 unk_xc;
    /*0x0D*/ u8 unk_xd[3];
    /*0x10*/ u8 unk_x10;
    /*0x11*/ u8 unk_x11[7];
};

struct gmm_x1868 {
    /* 0x1868 */ s32 x1868;
    u8 padding_x1868[0x1A18 - 0x1868 - 4];
    /* 0x1A18 */ s32 x1A18;
    /* 0x1A1C */ s32 x1A1C;
    /* 0x1A20 */ s32 x1A20;
    /* 0x1A24 */ s32 x1A24;
    /* 0x1A28 */ s32 x1A28;
    /* 0x1A2C */ s32 x1A2C;
    /* 0x1A30 */ s32 x1A30;
    /* 0x1A34 */ s32 x1A34;
    /* 0x1A38 */ s32 x1A38;
    /* 0x1A3C */ s32 x1A3C;
    /* 0x1A40 */ s32 x1A40;
    /* 0x1A44 */ s32 x1A44;
    /* 0x1A48 */ s32 x1A48;
    /* 0x1A4C */ s32 x1A4C;
    /* 0x1A50 */ s32 x1A50;
    /* 0x1A54 */ s32 x1A54;
    /* 0x1A58 */ s32 x1A58;
    /* 0x1A5C */ s32 x1A5C;
    /* 0x1A60 */ s32 x1A60;
    /* 0x1A64 */ s32 x1A64;
    /* 0x1A68 */ s64 x1A68;
    /* 0x1A70 */ s32 x1A70[4];
    u8 padding_x1A70[0x1B3C - 0x1A70 - 16];
    /* 0x1B3C */ u8 x1B3C;
    /* 0x1B40 */ u32 x1B40[3];
    /* 0x1B4C */ u32 x1B4C[3];
    /* 0x1B58 */ u32 x1B58[3];
    u8 padding_x1B58[0x1B80 - 0x1B58 - 3 * 4];
    /* 0x1B80 */ u32 x1B80[4];
    u8 padding_x1B80[0x1C88 - 0x1B80 - 4 * 4];
    /* 0x1C88 */ u32 x1C88[3];
    u8 padding_x1C88[0x1CB0 - 0x1C88 - 3 * 4];
    /* 0x1CB0 */ struct gmm_x1CB0 x1CB0;
    /* 0x1CD0 */ s16 x1CD0;
    /* 0x1CD2 */ s16 x1CD2;
    /* 0x1CD4 */ s32 x1CD4;
    u8 padding_x1CD4[0x1F2C - 0x1CD4 - 4];
    /* 0x1F2C */ struct gmm_x1F2C x1F2C[25];
    /* 0x2FF8 */ struct gmm_x2FF8 x2FF8[2];
    //  u8 padding_x2FF8[0x7000 - 0x2FF8 - 0x1A4*19*2];
};

struct gmm_x0 {
    /* 0x0000 */ u8 language;
    /* 0x0001 */ u8 x1;
    u8 padding_x1[0x39 - 0x1 - 1];
    /* 0x0039 */ u8 x39[11];
    /* 0x0044 */ s32 x44;
    u8 padding_x44[0x6C - 0x44 - 4];
    /* 0x006C */ u32 x6C[4];
    u8 padding_x6C[0x51C - 0x6C - 4 * 4];
    /* 0x051C */ s32 x51C;
    /* 0x0520 */ s16 x520;
    /* 0x0522 */ s16 x522;
    /* 0x0524 */ s16 x524;
    /* 0x0526 */ s16 x526;
    /* 0x0528 */ s32 x528;
    /* 0x052C */ s32 x52C;
    u8 padding_x52C[0x57C - 0x52C - 4];
    /* 0x057C */ s32 x57C;
    u8 padding_x57C[0x586 - 0x57C - 4];
    /* 0x0586 */ s16 x586;
    /* 0x0588 */ s8 x588[4];
    u8 padding_x588[0x1850 - 0x588 - 4];
    /* 0x1850 */ GameRules x1850;
    struct gmm_x1868 thing;
};

struct gmm_retval_ED98 {
    u8 padding[0xC];
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
};

struct gmm_retval_EDBC {
    s32 x0;
    s32 x4;
    s32 x8;
    u8 padding[0x4C - 0x8 - 4];
    s32 x4C[4];
    u8 padding_x4C[0xB0 - 0x4C - 4 * 4];
    s32 xB0[4];
};

struct gmm_retval_EDB0 {
    s32 x0;
    s32 x4;
};

struct Placeholder_8016AE38_flags {
    u8 unk80 : 1;
    u8 unk40 : 1;
    u8 unk20 : 1;
    u8 unk10 : 1;
    u8 unk8 : 1;
    u8 unk4 : 1;
    u8 unk2 : 1;
    u8 unk1 : 1;
};

struct Placeholder_8016AE38_flags_2 {
    u8 top3 : 3;
    u8 bot5 : 5;
};

struct Placeholder_8016AE38_ret_val {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u32 padding[0x931 - 3];
    Placeholder_8016AE38_flags_2 unk24C8;
    u8 unk24C9;
    Placeholder_8016AE38_flags unk24CA;
};

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
    /* +1 */ u8 _1[0xC - 0x1];
};
STATIC_ASSERT(sizeof(struct gm_8017DB6C_arg0_t) == 0xC);

#endif

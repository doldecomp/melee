#ifndef MELEE_PL_TYPES_H
#define MELEE_PL_TYPES_H

#include <platform.h>
#include <placeholder.h>

/// @todo Probably the same struct as #plAllocInfo, figure out how to make them
///       work as one.
struct plAllocInfo2 {
    s32 internal_id;
    u8 slot;
    enum_t unk8;
    struct {
        u8 b0 : 1;
        u8 has_transformation : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
};

struct pl_800386D8_t {
    /*   +0 */ u8 _0[0x3E8];
    /* +3E8 */ UNK_T x3E8 UNK_SIZE_ARRAY;
};

typedef struct StaleMoveTable {
    /*   +0 */ int current_index;
    /*   +4 */ struct {
        u16 move_id;
        u16 attack_instance;
    } StaleMoves[10];
    /// @todo #pl_800386D8_t starts at +2C
    /*  +2C */ int total_attack_count;
    /*  +30 */ u8 x30[0x5EC - 0x30];
    /* +5EC */ int x5EC;
    /* +5F0 */ u8 x5F0[0xC60 - 0x5F0];
    /* +C60 */ f32 xC60;
    /* +C64 */ f32 xC64;
    /* +C68 */ s32 xC68;
    /* +C6C */ f32 xC6C;
    /* +C70 */ u8 xC70[0xC90 - 0xC70];
    /* +C90 */ u32 xC90;
    /* +C94 */ u8 xC94[0xC98 - 0xC94];
    /* +C98 */ float xC98;
    /* +C9C */ u8 xC9C[0xCA8 - 0xC9C];
    /* +CA8 */ u32 xCA8;
    /* +CAC */ s32 xCAC;
    /* +CB0 */ s32 xCB0;
    /* +CB4 */ s32 xCB4;
    /* +CB8 */ u8 xCB8[0xCD8 - 0xCB8];
    /* +CD8 */ s32 xCD8;
    /* +CDC */ f32 xCDC;
    /* +CE0 */ f32 xCE0;
    /* +CE4 */ u8 xCE4[0xCEC - 0xCE4];
    /* +CEC */ int xCEC;
    /* +CF0 */ int xCF0;
} StaleMoveTable;
STATIC_ASSERT(sizeof(struct StaleMoveTable) == 0xCF4);

typedef struct pl_StaleMoveTableExt_t {
    /*   +0 */ StaleMoveTable x0_staleMoveTable;
    /* +CF4 */ s32 xCF4;
    /* +CF8 */ u8 xCF8[0xCFC - 0xCF8];
    /* +CFC */ s32 xCFC;
    /* +D00 */ u8 xD00[0xD04 - 0xD00];
    /* +D04 */ u32 xD04;
    /* +D08 */ u32 xD08;
    /* +D0C */ u32 xD0C;
    /* +D10 */ s32 xD10;
    /* +D14 */ s32 xD14;
    /* +D18 */ u32 xD18;
    /* +D1C */ s32 xD1C;
    /* +D20 */ s32 xD20;
    /* +D24 */ s32 xD24;
    /* +D28 */ s32 xD28;
    /* +D2C */ s32 xD2C;
    /* +D30 */ s32 xD30;
    /* +D34 */ s32 xD34;
    /* +D38 */ s32 xD38;
    /* +D3C */ s32 xD3C;
    /* +D40 */ u32 xD40;
    /* +D44 */ u32 xD44;
    /* +D48 */ u32 xD48;
    /* +D4C */ u32 xD4C;
    /* +D50 */ u32 xD50;
    /* +D54 */ u32 xD54;
    /* +D58 */ s32 xD58;
    /* +D5C */ u32 xD5C;
    /* +D60 */ u32 xD60;
    /* +D64 */ u8 xD64[0xD68 - 0xD64];
    /* +D68 */ s32 xD68;
    /* +D6C */ u8 xD6C[0xDD0 - 0xD6C];
    /* +DD0 */ u8 xDD0;
    /* +DD1 */ u8 xDD1_Padding[0x3];
} pl_StaleMoveTableExt_t;

struct pl_800386E8_arg0_t {
    /* 0x000 */ char pad_0[0x190];
    /* 0x190 */ int unk_190;         /* inferred */
    /* 0x194 */ char pad_194[0x418]; /* maybe part of unk_190[0x107]? */
    /* 0x5AC */ int unk_5AC;         /* inferred */
    /* 0x5B0 */ int unk_5B0;         /* inferred */
}; /* size = 0x5B4 */

typedef struct pl_804D6470_t {
    /*   +0 */ u8 x0[0x58];
    /*  +58 */ f32 x58;
    /*  +5C */ u8 x5C[0x64 - 0x5C];
    /*  +64 */ f32 x64;
} pl_804D6470_t;

#endif

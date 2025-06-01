#ifndef MELEE_PL_TYPES_H
#define MELEE_PL_TYPES_H

#include <platform.h>
#include <placeholder.h>

#include "forward.h"

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
    /*   +0 */ int total_attack_count;
    /*   +4 */ u8 x4[0xD0 - 0x4];
    /*  +D0 */ s32 xD0;
    /*  +D4 */ u8 xD4[0x194 - 0xD4];
    /* +194 */ s32 x194;
    /* +198 */ s32 x198;
    /* +19C */ s32 x19C;
    /* +1A0 */ u8 x1A0[0x358 - 0x1A0];
    /* +358 */ s32 x358;
    /* +35C */ u8 x35C[0x3E8 - 0x35C];
    /* +3E8 */ UNK_T x3E8 UNK_SIZE_ARRAY;
};

typedef struct StaleMoveTable {
    /*   +0 */ int current_index;
    /*   +4 */ struct {
        u16 move_id;
        u16 attack_instance;
    } StaleMoves[10];
    /*  +2C */ pl_800386D8_t total_attack_count_struct;
    /* +414 */ u8 x414[0x5C4 - 0x414];
    /* +5C4 */ s32 x5C4[0xA]; // UNKNOWN SIZE
    /* +5EC */ int x5EC;
    /* +5F0 */ u8 x5F0[0x674 - 0x5F0];
    /* +674 */ s32 x674[39];
    /* +710 */ s32 x710[39];
    /* +7AC */ u8 x7AC[0xC60 - 0x7AC];
    /* +C60 */ f32 xC60;
    /* +C64 */ f32 xC64;
    /* +C68 */ s32 xC68;
    /* +C6C */ f32 xC6C;
    /* +C70 */ u8 xC70[0xC90 - 0xC70];
    /* +C90 */ u32 xC90;
    /* +C94 */ u8 xC94[0xC98 - 0xC94];
    /* +C98 */ float xC98;
    /* +C9C */ float xC9C;
    /* +CA0 */ u8 xCA0[0xCA8 - 0xCA0];
    /* +CA8 */ u32 xCA8;
    /* +CAC */ s32 xCAC;
    /* +CB0 */ s32 xCB0;
    /* +CB4 */ s32 xCB4;
    /* +CB8 */ u8 xCB8[0xCD8 - 0xCB8];
    /* +CD8 */ s32 xCD8;
    /* +CDC */ f32 xCDC;
    /* +CE0 */ f32 xCE0;
    /* +CE4 */ s32 xCE4;
    /* +CE8 */ u8 xCE8[0xCEC - 0xCE8];
    /* +CEC */ int xCEC;
    /* +CF0 */ int xCF0;
} StaleMoveTable;
STATIC_ASSERT(sizeof(struct StaleMoveTable) == 0xCF4);

typedef struct pl_StaleMoveTableExt_t {
    /*   +0 */ StaleMoveTable x0_staleMoveTable;
    /* +CF4 */ s32 xCF4;
    /* +CF8 */ f32 xCF8;
    /* +CFC */ s32 xCFC;
    /* +D00 */ s32 xD00;
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
    /* +D64 */ s32 xD64;
    /* +D68 */ s32 xD68;
    /* +D6C */ u8 xD6C[0xD70 - 0xD6C];
    /* +D70 */ s32 xD70;
    /* +D74 */ f32 xD74;
    /* +D78 */ f32 xD78;
    /* +D7C */ f32 xD7C;
    /* +D80 */ f32 xD80;
    /* +D84 */ f32 xD84;
    /* +D88 */ f32 xD88;
    /* +D8C */ u8 xD8C[0xDD0 - 0xD8C];
    /* +DD0 */ union {
        u8 xDD0_value;
        struct {
            u8 bit0 : 1;
            u8 bit1 : 1;
            u8 bit2 : 1;
            u8 bit3 : 1;
            u8 bit4 : 1;
            u8 bit5 : 1;
            u8 bit6 : 1;
            u8 bit7 : 1;
        };
    } xDD0;
    /* +DD1 */ union {
        u8 xDD1_value;
        struct {
            u8 bit0 : 1;
            u8 bit1 : 1;
            u8 bit2 : 1;
            u8 bit3 : 1;
            u8 bit4 : 1;
            u8 bit5 : 1;
            u8 bit6 : 1;
            u8 bit7 : 1;
        };
    } xDD1;
    /* +DD2 */ UNK_T xDD2 UNK_SIZE_ARRAY;
} pl_StaleMoveTableExt_t;

struct pl_800386E8_arg0_t {
    /* 0x000 */ char pad_0[0x190];
    /* 0x190 */ int unk_190;         /* inferred */
    /* 0x194 */ char pad_194[0x418]; /* maybe part of unk_190[0x107]? */
    /* 0x5AC */ int unk_5AC;         /* inferred */
    /* 0x5B0 */ int unk_5B0;         /* inferred */
}; /* size = 0x5B4 */

typedef struct pl_804D6470_t {
    /*   +0 */ u8 x0[0x38];
    /*  +38 */ float x38;
    /*  +3C */ u8 x3C[0x58 - 0x3C];
    /*  +58 */ f32 x58;
    /*  +5C */ u8 x5C[0x64 - 0x5C];
    /*  +64 */ f32 x64;
    /*  +68 */ u8 x68[0x84 - 0x68];
    /*  +84 */ f32 x84;
    /*  +88 */ u8 x88[0x98 - 0x88];
    /*  +98 */ f32 x98;
    /*  +9C */ u8 x9C[0xA4 - 0x9C];
    /*  +A4 */ u32 xA4;
    /*  +A8 */ u8 xA8[0xB0 - 0xA8];
    /*  +B0 */ u32 xB0;
    /*  +B4 */ u32 xB4;
    /*  +B8 */ u8 xB8[0x124 - 0xB8];
    /* +124 */ u32 x124;
    /* +128 */ UNK_T x128 UNK_SIZE_ARRAY;
} pl_804D6470_t;

#endif

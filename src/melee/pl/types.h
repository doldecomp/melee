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
    /*  +D0 */ int xD0;
    /*  +D4 */ u8 xD4[0x194 - 0xD4];
    /* +194 */ int x194;
    /* +198 */ int x198;
    /* +19C */ int x19C;
    /* +1A0 */ u8 x1A0[0x358 - 0x1A0];
    /* +358 */ int x358;
    /* +35C */ u8 x35C[0x3E8 - 0x35C];
    /* +3E8 */ UNK_T x3E8 UNK_SIZE_ARRAY;
};

struct StaleMoveTable {
    /*   +0 */ int current_index;
    /*   +4 */ struct {
        u16 move_id;
        u16 attack_instance;
    } StaleMoves[10];
    /*  +2C */ pl_800386D8_t total_attack_count_struct;
    /* +414 */ u8 x414[0x5C4 - 0x414];
    /* +5C4 */ int x5C4[0xA]; // UNKNOWN SIZE
    /* +5EC */ int x5EC;
    /* +5F0 */ u8 x5F0[0x674 - 0x5F0];
    /* +674 */ int x674[39];
    /* +710 */ int x710[39];
    /* +7AC */ u8 x7AC[0xC60 - 0x7AC];
    /* +C60 */ float xC60;
    /* +C64 */ float xC64;
    /* +C68 */ int xC68;
    /* +C6C */ float xC6C;
    /* +C70 */ u8 xC70[0xC90 - 0xC70];
    /* +C90 */ unsigned int xC90;
    /* +C94 */ u8 xC94[0xC98 - 0xC94];
    /* +C98 */ float xC98;
    /* +C9C */ float xC9C;
    /* +CA0 */ u8 xCA0[0xCA8 - 0xCA0];
    /* +CA8 */ unsigned int xCA8;
    /* +CAC */ int xCAC;
    /* +CB0 */ int xCB0;
    /* +CB4 */ int xCB4;
    /* +CB8 */ u8 xCB8[0xCD8 - 0xCB8];
    /* +CD8 */ int xCD8;
    /* +CDC */ float xCDC;
    /* +CE0 */ float xCE0;
    /* +CE4 */ int xCE4;
    /* +CE8 */ int xCE8;
    /* +CEC */ int xCEC;
    /* +CF0 */ int xCF0;
};
STATIC_ASSERT(sizeof(struct StaleMoveTable) == 0xCF4);

struct pl_StaleMoveTableExt_t {
    /*   +0 */ StaleMoveTable x0_staleMoveTable;
    /* +CF4 */ int xCF4;
    /* +CF8 */ float xCF8;
    /* +CFC */ int xCFC;
    /* +D00 */ int xD00;
    /* +D04 */ unsigned int xD04;
    /* +D08 */ unsigned int xD08;
    /* +D0C */ unsigned int xD0C;
    /* +D10 */ int xD10;
    /* +D14 */ int xD14;
    /* +D18 */ unsigned int xD18;
    /* +D1C */ int xD1C;
    /* +D20 */ int xD20;
    /* +D24 */ int xD24;
    /* +D28 */ int xD28;
    /* +D2C */ int xD2C;
    /* +D30 */ int xD30;
    /* +D34 */ int xD34;
    /* +D38 */ int xD38;
    /* +D3C */ int xD3C;
    /* +D40 */ unsigned int xD40;
    /* +D44 */ unsigned int xD44;
    /* +D48 */ unsigned int xD48;
    /* +D4C */ unsigned int xD4C;
    /* +D50 */ unsigned int xD50;
    /* +D54 */ unsigned int xD54;
    /* +D58 */ unsigned int xD58;
    /* +D5C */ unsigned int xD5C;
    /* +D60 */ unsigned long xD60;
    /* +D64 */ int xD64;
    /* +D68 */ int xD68;
    /* +D6C */ int xD6C;
    /* +D70 */ int xD70;
    /* +D74 */ float xD74;
    /* +D78 */ float xD78;
    /* +D7C */ float xD7C;
    /* +D80 */ float xD80;
    /* +D84 */ float xD84;
    /* +D88 */ float xD88;
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
};

struct pl_800386E8_arg0_t {
    /* 0x000 */ char pad_0[0x190];
    /* 0x190 */ int unk_190;         /* inferred */
    /* 0x194 */ char pad_194[0x418]; /* maybe part of unk_190[0x107]? */
    /* 0x5AC */ int unk_5AC;         /* inferred */
    /* 0x5B0 */ int unk_5B0;         /* inferred */
}; /* size = 0x5B4 */

struct pl_804D6470_t {
    /*   +0 */ u8 x0[0x38];
    /*  +38 */ float x38;
    /*  +3C */ u8 x3C[0x58 - 0x3C];
    /*  +58 */ float x58;
    /*  +5C */ u8 x5C[0x64 - 0x5C];
    /*  +64 */ float x64;
    /*  +68 */ u8 x68[0x84 - 0x68];
    /*  +84 */ float x84;
    /*  +88 */ u8 x88[0x98 - 0x88];
    /*  +98 */ float x98;
    /*  +9C */ u8 x9C[0xA0 - 0x9C];
    /*  +A0 */ float xA0;
    /*  +A4 */ unsigned int xA4;
    /*  +A8 */ u8 xA8[0xB0 - 0xA8];
    /*  +B0 */ unsigned int xB0;
    /*  +B4 */ unsigned int xB4;
    /*  +B8 */ u8 xB8[0x124 - 0xB8];
    /* +124 */ unsigned int x124;
    /* +128 */ u8 x128[0x180 - 0x128];
    /* +180 */ float x180;
    /* +184 */ UNK_T x184 UNK_SIZE_ARRAY;
};

#endif

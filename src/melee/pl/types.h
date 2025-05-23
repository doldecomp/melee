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
    /* +5F0 */ u8 x5F0[0xCEC - 0x5F0];
    /* +CEC */ int xCEC;
    /* +CF0 */ int xCF0;
} StaleMoveTable;

struct pl_800386E8_arg0_t {
    /* 0x000 */ char pad_0[0x190];
    /* 0x190 */ int unk_190;         /* inferred */
    /* 0x194 */ char pad_194[0x418]; /* maybe part of unk_190[0x107]? */
    /* 0x5AC */ int unk_5AC;         /* inferred */
    /* 0x5B0 */ int unk_5B0;         /* inferred */
}; /* size = 0x5B4 */

#endif

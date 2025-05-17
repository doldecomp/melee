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
    /* +5F0 */ u8 x5F0[0xC90 - 0x5F0];
    /* +C90 */ s32 xC90;
    /* +C94 */ u8 xC94[0xC98 - 0xC94];
    /* +C98 */ float xC98;
    /* +C9C */ u8 xC9C[0xCD8 - 0xC9C];
    /* +CD8 */ s32 xCD8;
    /* +CDC */ u8 xCDC[0xCEC - 0xCDC];
    /* +CEC */ int xCEC;
    /* +CF0 */ int xCF0;
} StaleMoveTable;
STATIC_ASSERT(sizeof(struct StaleMoveTable) == 0xCF4);

#endif

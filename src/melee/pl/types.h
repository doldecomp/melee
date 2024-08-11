#ifndef MELEE_PL_TYPES_H
#define MELEE_PL_TYPES_H

#include <platform.h>

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
    } bits;
};

typedef struct StaleMoveTable {
    /*   +0 */ int current_index;
    /*   +4 */ struct {
        u16 move_id;
        u16 num_action_states;
    } StaleMoves[10];
    /*  +2C */ int total_attack_count;
    /*  +30 */ u8 x30[0x5EC - 0x30];
    /* +5EC */ int x5EC;
    /* +5F0 */ u8 x5F0[0xCEC - 0x5F0];
    /* +CEC */ int xCEC;
    /* +CF0 */ int xCF0;
} StaleMoveTable;

#endif

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

typedef struct _StaleMoveTable {
    s32 current_index; // Zero-Indexed. Rolls over
                       // after 9. Increments after
                       // each write.
    struct {
        s16 move_id;
        s16 num_action_states;
    } StaleMoves[10];
} StaleMoveTable;

#endif

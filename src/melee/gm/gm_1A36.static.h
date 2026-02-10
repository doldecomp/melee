/// @@todo Move to C file
#ifndef __GALE01_1A3680
#define __GALE01_1A3680

#include <platform.h>

#include <dolphin/pad.h>

struct gm_controller_map {
    /* 00 */ u64 button;
    /* 08 */ u64 trigger; ///< buttons pressed this frame, maybe rename?
    /* 10 */ u64 repeat;
    /* 18 */ u64 release;
    /* 20 */ u64 repeat2;
    /* 28 */ s32 repeat_timer;
    /* 2C */ s32 x2C;
};

static struct controller_map {
    struct gm_controller_map x0[PAD_MAX_CONTROLLERS + 1];
    /* F0 */ void (*xF0)(int);
    /* F4 */ u16 xF4;
    /* F6 */ u8 xF6;
    /* F8 */ u16 xF8;
    /* FA */ u8 xFA;
    /* FC */ u16 xFC;
    /* FE */ u8 xFE;
} controller_map;

#endif

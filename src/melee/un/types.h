#ifndef MELEE_UN_TYPES_H
#define MELEE_UN_TYPES_H

#include <platform.h>

#include "baselib/forward.h"
#include "un/forward.h" // IWYU pragma: export

#include <dolphin/gx.h>

#define DEVTEXT_FLAG_HIDETEXT (0x80)
#define DEVTEXT_FLAG_HIDEBACKGROUND (0x40)
#define DEVTEXT_FLAG_NOWRAP (0x20)
#define DEVTEXT_FLAG_SHOWCURSOR (0x10)

struct DevText {
    /*  +0 */ s16 x;
    /*  +2 */ s16 y;
    /*  +4 */ u8 w;
    /*  +5 */ u8 h;
    /*  +6 */ u8 cursor_x;
    /*  +7 */ u8 cursor_y;
    /*  +8 */ f32 scale_x;
    /*  +C */ f32 scale_y;
    /* +10 */ GXColor bg_color;
    /* +14 */ GXColor text_colors[4];
    /* +24 */ s8 id;
    /* +25 */ u8 line_width;
    /* +26 */ u8 flags;
    /* +27 */ u8 unk : 6;
    /* +27 */ u8 current_color : 2;
    /* +28 */ char* buf;
    /* +2C */ struct DevText* prev;
    /* +30 */ struct DevText* next;
};

struct un_80302DF8_t {
    /* +0 */ char pad_0[0xC];
    /* +C */ int xC;
};

struct un_80304334_t {
    /* +0 */ char pad_0[1];
    /* +1 */ u8 x1;
};

struct un_804D6EF4_t {
    /* +0 */ char pad_0[0x18];
    /* +14 */ HSD_JObj* x14;
    /* +18 */ HSD_JObj* x18;
    /* +1C */ char pad_1C[0x54 - 0x20];
    /* +54 */ short x54;
    /* +56 */ short x56;
};

#endif

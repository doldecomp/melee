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

struct un_804D6EF4_t {
    /* +0 */ char pad_0[0x18];
    /* +14 */ HSD_JObj* x14;
    /* +18 */ HSD_JObj* x18;
    /* +1C */ char pad_1C[0x50 - 0x20];
    /* +50 */ HSD_Archive* archive;
    /* +54 */ short x54;
    /* +56 */ short x56;
};

struct un_80304138_objalloc_t_x8 {
    int x0;
    int (*x4)(int);
    char* x8;
    char** xC;
    void* x10;
    float x14;
    float x18;
    float x1C;
};
STATIC_ASSERT(sizeof(struct un_80304138_objalloc_t_x8) == 0x20);

struct un_80304138_objalloc_t {
    unsigned char x0;
    unsigned char x1;
    DevText* x4;
    struct un_80304138_objalloc_t_x8* x8;
    int (*xC)(int);
    HSD_GObj* x10;
    HSD_GObjProc* x14;
    struct un_80304138_objalloc_t* prev;
    struct un_80304138_objalloc_t* next;
};
STATIC_ASSERT(sizeof(struct un_80304138_objalloc_t) == 0x20);

#endif

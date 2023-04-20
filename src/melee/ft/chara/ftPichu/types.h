#ifndef MELEE_FT_CHARA_FTPICHU_TYPES_H
#define MELEE_FT_CHARA_FTPICHU_TYPES_H

#include <platform.h>

typedef struct _ftPichuAttributes {
    /* 0x00 */ u32 x0_padding[(0x14 - 0x0) / 4];
    /* 0x14 */ u32 x14;
    /* 0x14 */ u32 x18;
    /* 0x18 */ u32 x18_padding[(0xDC - 0x1C) / 4];
    /* 0xDC */ u32 xDC;
} ftPichuAttributes;

#endif

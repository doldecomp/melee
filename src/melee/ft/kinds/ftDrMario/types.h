#ifndef MELEE_FT_CHARA_FTDRMARIO_TYPES_H
#define MELEE_FT_CHARA_FTDRMARIO_TYPES_H

#include <Runtime/platform.h>

#include <melee/it/forward.h>

/// @todo: Should this be longer like ftMario_DatAttrs? That struct seems to
/// get pushed to this one in ftMr_Init_OnLoadForDrMario
typedef struct _ftDrMarioAttributes {
    u8 pad_x0[4];
    u32 x4;
    u8 pad_x8[4];
    u32 xC;
    u8 pad_x10[4];
    ItemKind cape_kind; // It_Kind_DrMario_Cape
} ftDrMarioAttributes;

#endif

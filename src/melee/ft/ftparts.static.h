#ifndef MELEE_FT_FTPARTS_STATIC_H
#define MELEE_FT_FTPARTS_STATIC_H

#include <dolphin/mtx.h>

/// .bss
struct {
    Mtx mtx;
    u8 has_z_scale : 1;
    char unk_31[7];
} ft_jobj_scale;

#endif

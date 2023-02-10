#ifndef DOLPHIN_GX___GXINIT_H
#define DOLPHIN_GX___GXINIT_H

#include <dolphin/gx/__types.h>

/* 004D2788 */ extern GXContexts __GXContexts;

static inline void set_x2(GXBool value)
{
    __GXContexts.main->x0.u16[1] = value;
}

#endif

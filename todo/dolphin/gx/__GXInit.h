#ifndef DOLPHIN_GX___GXINIT_H
#define DOLPHIN_GX___GXINIT_H

#include <platform.h>

#include <dolphin/gx.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXEnum.h>

/* 004D2788 */ extern GXContexts __GXContexts;

static inline void set_x2(GXBool value)
{
    __GXContexts.main->x0.u16[1] = value;
}

#endif

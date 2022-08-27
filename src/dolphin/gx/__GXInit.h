#ifndef DOLPHIN_GX___GXINIT_H
#define DOLPHIN_GX___GXINIT_H

#include <dolphin/gx/__types.h>

extern volatile u32 *__piReg; // todo: OSPhysicalToUncached (0x0C003000)
extern volatile u16 *__cpReg; // todo: OSPhysicalToUncached (0x0C000000)
extern volatile u16 *__peReg; // todo: OSPhysicalToUncached (0x0C001000)

/* 004D2788 */ extern GXContexts __GXContexts;

static void set_x2(GXBool value)
{
    __GXContexts.main->x0.u16[1] = value;
}

#endif

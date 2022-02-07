#ifndef _OS_H__
#define _OS_H_

#include <dolphin/os/OSAlloc.h>
#include <dolphin/os/OSArena.h>
#include <dolphin/os/OSTime.h>

#define OSRoundUp32B(x)   (((u32)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((u32)(x)) & ~(32 - 1))

#endif

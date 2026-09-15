#ifndef _DOLPHIN_VI_H_
#define _DOLPHIN_VI_H_

// IWYU pragma: begin_exports
#include <dolphin/vi/vifuncs.h>
#include <dolphin/vi/vitypes.h>
// IWYU pragma: end_exports

#define VIPadFrameBufferWidth(width) ((u16) (((u16) (width) + 15) & ~15))

#endif

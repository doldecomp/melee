#ifndef DOLPHIN_GX_FORWARD_H
#define DOLPHIN_GX_FORWARD_H

#include <platform.h>

#include <dolphin/gx/GXEnum.h>

typedef struct GXTexObj GXTexObj;
typedef struct GXTlutObj GXTlutObj;
typedef struct GXColor GXColor;
typedef struct GXColorS10 GXColorS10;
typedef struct GXRenderModeObj GXRenderModeObj;
typedef struct GXContexts GXContexts;
typedef struct GXGPFifo GXGPFifo;
typedef struct GXSettings GXSettings;
typedef struct GXContext GXContext;
typedef struct GXFifoObj GXFifoObj;

typedef void (*GXDrawDoneCallback)(void);

/// @todo Signature unknown.
typedef void* (*GXTexRegionCallback)(void);

static inline void GXEnd(void) {}

#endif

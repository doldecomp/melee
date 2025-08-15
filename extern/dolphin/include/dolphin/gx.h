#ifndef _DOLPHIN_GX_H_
#define _DOLPHIN_GX_H_

#include <dolphin/gx/GXBump.h>        // IWYU pragma: export
#include <dolphin/gx/GXCommandList.h> // IWYU pragma: export
#include <dolphin/gx/GXCpu2Efb.h>     // IWYU pragma: export
#include <dolphin/gx/GXCull.h>        // IWYU pragma: export
#include <dolphin/gx/GXDispList.h>    // IWYU pragma: export
#include <dolphin/gx/GXDraw.h>        // IWYU pragma: export
#include <dolphin/gx/GXFifo.h>        // IWYU pragma: export
#include <dolphin/gx/GXFrameBuffer.h> // IWYU pragma: export
#include <dolphin/gx/GXGeometry.h>    // IWYU pragma: export
#include <dolphin/gx/GXGet.h>         // IWYU pragma: export
#include <dolphin/gx/GXLighting.h>    // IWYU pragma: export
#include <dolphin/gx/GXManage.h>      // IWYU pragma: export
#include <dolphin/gx/GXPerf.h>        // IWYU pragma: export
#include <dolphin/gx/GXPixel.h>       // IWYU pragma: export
#include <dolphin/gx/GXStruct.h>      // IWYU pragma: export
#include <dolphin/gx/GXTev.h>         // IWYU pragma: export
#include <dolphin/gx/GXTexture.h>     // IWYU pragma: export
#include <dolphin/gx/GXTransform.h>   // IWYU pragma: export
#include <dolphin/gx/GXVerify.h>      // IWYU pragma: export
#include <dolphin/gx/GXVert.h>        // IWYU pragma: export

// unsorted GX externs

#ifdef __cplusplus
extern "C" {
#endif

// GXMisc
void (*GXSetDrawSyncCallback(void (*cb)(unsigned short)))(unsigned short);
void GXSetDrawSync(unsigned short token);

#ifdef __cplusplus
}
#endif

#endif

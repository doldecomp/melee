#ifndef DOLPHIN_GX_GXBUMP_H
#define DOLPHIN_GX_GXBUMP_H

#include <Runtime/platform.h>

void __GXUpdateBPMask(void);
void GXSetIndTexCoordScale(s32, s32, s32);
void GXSetIndTexMtx(s32, unk_t, s32);
void XSetIndTexCoordScale(void);
void GXSetIndTexOrder(s32, s32, s32);
void GXSetNumIndStages(s32 arg0);
void GXSetTevDirect(void);
void __GXUpdateBPMask(void);
void __GXFlushTextureState(void);
void GXSetTevIndirect(s32, s32, u8, s32, s32, s32, s32, s32);

#endif

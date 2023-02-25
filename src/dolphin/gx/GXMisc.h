#ifndef DOLPHIN_GX_GXMISC_H
#define DOLPHIN_GX_GXMISC_H

#include <dolphin/gx/forward.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/os/OSThread.h>

void GXPixModeSync(void);
void GXWaitDrawDone(void);
void GXSetDrawDone(void);
void GXSetMisc(s32, u32);

void GXPokeAlphaMode(GXCompare func, u8 threshold);
void GXPokeAlphaRead(s32 mode);
void GXPokeAlphaUpdate(bool update_enable);
void GXPokeColorUpdate(bool update_enable);
void GXPokeDstAlpha(bool enable, u8 alpha);
void GXPokeDither(s32 dither);
void GXPokeZMode(bool compare_enable, GXCompare func, bool update_enable);
void GXTokenInterruptHandler(__OSInterrupt unused, OSContext* current_ctx);
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb);
void GXFinishInterruptHandler(__OSInterrupt unused, OSContext* current_ctx);
void __GXPEInit(void);
void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_factor,
                     GXBlendFactor dst_factor, GXLogicOp op);

#endif

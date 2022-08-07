#ifndef _GXFIFO_H_
#define _GXFIFO_H_

#include <dolphin/types.h>
#include <dolphin/gx/gxprivate.h>
#include <dolphin/os/OSThread.h>
#include <functions.h>

void GXCPInterruptHandler();
void GXSetCPUFifo(GXFifoObj *fifo);
void GXInitFifoLimits(void *, s32, s32);
void GXInitFifoBase(void *, void *, u32);
void __GXFifoLink(s8);
void GXSetGPFifo(__GXGPFifo *gp_fifo);
void __GXFifoReadEnable();
void __GXFifoReadDisable();
void __GXFifoInit();

extern __GXFifoLinkObj lbl_804A76C8;
extern __GXGPFifo *lbl_804D72F4;

extern void *lbl_804D7300;
extern void *lbl_804D7304;
extern u32 lbl_804D7308;
extern void *lbl_804D7310;
extern __GXFifoUnknown *lbl_804D72F8;
extern f32 lbl_804DE2F8;
extern f32 lbl_804DE308;
extern f32 lbl_804DE30C;

#endif
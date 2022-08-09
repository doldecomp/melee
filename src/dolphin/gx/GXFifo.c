#include <dolphin/gx/gxprivate.h>
#include <dolphin/os/OSThread.h>

#pragma region variables unordered
extern void *lbl_804D7300;
extern void *lbl_804D7304;
extern OSThread *lbl_804D7308;
extern void *lbl_804D7310;
extern void (*lbl_804D7314)();
extern s32 lbl_804D7318;
#pragma endregion

extern void GXCPInterruptHandler(OSContext *);
extern void GXInitFifoBase(void *, void *, u32);
extern void GXInitFifoPtrs(void *, s32, s32);
extern void GXInitFifoLimits(void *, s32, s32);
extern void GXSetCPUFifo(GXFifoObj *fifo);
extern void GXSetGPFifo(__GXGPFifo *gp_fifo);
extern void __GXFifoInit();
extern void __GXFifoReadEnable();
extern void __GXFifoReadDisable();
extern void __GXFifoLink(s8);
extern void __GXWriteFifoIntEnable(s32, s32);
extern void __GXWriteFifoIntReset(s8 arg0, s32 arg1);
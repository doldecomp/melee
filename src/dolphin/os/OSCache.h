#ifndef _OSCACHE_H_
#define _OSCACHE_H_

#include <dolphin/os/forward.h>
#include <Runtime/platform.h>

void DCFlushRange(void* addr, size_t nbytes);
void DCStoreRange(void* addr, size_t nbytes);
void DCInvalidateRange(void* addr, size_t nbytes);
void DCFlushRangeNoSync(void* addr, size_t nbytes);
void ICFlashInvalidate(void);
void ICInvalidateRange(void* addr, size_t nbytes);
void LCDisable(void);
void __OSCacheInit(void);

void DCZeroRange(register void* addr, register size_t nbytes);
void ICEnable(void);
void __LCEnable(void);
void DCEnable(void);
void LCEnable(void);
u32 LCStoreData(void* destAddr, void* srcAddr, u32 nBytes);
void LCQueueWait(register u32 len);
void L2GlobalInvalidate(void);
void L2Enable(void);
void DMAErrorHandler(OSError error, OSContext* context, ...);
void LCStoreBlocks(any_t dst, any_t src, u32 nblocks);

#endif

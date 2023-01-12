#ifndef _OSCACHE_H_
#define _OSCACHE_H_

#include <Runtime/platform.h>

void DCFlushRange(void* addr, size_t nbytes);
void DCStoreRange(void* addr, size_t nbytes);
void DCInvalidateRange(void* addr, size_t nbytes);
void DCFlushRangeNoSync(void* addr, size_t nbytes);
void ICFlashInvalidate(void);
void ICInvalidateRange(void* addr, size_t nbytes);
void LCDisable(void);

#endif

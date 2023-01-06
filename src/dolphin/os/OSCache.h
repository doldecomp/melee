#ifndef _OSCACHE_H_
#define _OSCACHE_H_

#include <dolphin/types.h>

void DCFlushRange(u8*, s32);
void DCStoreRange(register void* addr, register size_t nbytes);

#endif

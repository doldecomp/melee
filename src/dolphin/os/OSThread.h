#ifndef _OSTHREAD_H_
#define _OSTHREAD_H_

#include <dolphin/types.h>
#include <dolphin/os/OSContext.h>

s32 OSGetCurrentThread();
void OSWakeupThread(void*);

#endif
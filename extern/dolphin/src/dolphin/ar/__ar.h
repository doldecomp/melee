#ifndef _DOLPHIN_AR_INTERNAL_H_
#define _DOLPHIN_AR_INTERNAL_H_

#include <dolphin/ar.h>

void __ARQPopTaskQueueHi(void);
void __ARQServiceQueueLo(void);
void __ARQCallbackHack(u32 pointerToARQRequest);
void __ARQInterruptServiceRoutine(void);
void __ARQInitTempQueue(void);
void __ARQPushTempQueue(struct ARQRequest * task);

#endif // _DOLPHIN_AR_INTERNAL_H_

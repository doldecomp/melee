#ifndef DOLPHIN_AR_AR_H
#define DOLPHIN_AR_AR_H

#include <Runtime/platform.h>

void ARStartDMA(u32 type, u32 source, u32 dest, u32 length);
void ARRegisterDMACallback(Event callback);

#endif

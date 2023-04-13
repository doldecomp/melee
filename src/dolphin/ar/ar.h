#ifndef DOLPHIN_AR_AR_H
#define DOLPHIN_AR_AR_H

#include <platform.h>

void ARStartDMA(u32 type, u32 source, u32 dest, u32 length);
Event ARRegisterDMACallback(Event callback);
void __ARChecksize(void);
u32 ARGetBaseAddress(void);
u32 ARGetSize(void);
u32 ARGetDMAStatus(void);
u32 ARAlloc(u32 length);
u32 ARFree(u32* length);
bool ARCheckInit(void);
u32 ARInit(u32* stack_index_addr, u32 num_entries);

#endif

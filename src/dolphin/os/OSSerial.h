#ifndef DOLPHIN_OS_OSSERIAL_H
#define DOLPHIN_OS_OSSERIAL_H

#include <dolphin/os/OSExi.h>

void SIGetResponse(EXIChannel chan, u32 data[2]);
void SISetCommand(s32 index, u32 value);

#endif

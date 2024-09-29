#ifndef DOLPHIN_DVD_FSTLOAD_H
#define DOLPHIN_DVD_FSTLOAD_H

#include <platform.h>

#include <dolphin/dvd/forward.h>

void __fstLoad(void);

void cb(s32 param_1, DVDCommandBlock* block);

#endif

#ifndef DOLPHIN_DVD_FORWARD_H
#define DOLPHIN_DVD_FORWARD_H

#include <platform.h>

typedef struct DVDCommandBlock DVDCommandBlock;

typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock* block);

#endif

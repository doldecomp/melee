#ifndef DOLPHIN_DVD_FORWARD_H
#define DOLPHIN_DVD_FORWARD_H

#include <Runtime/platform.h>

typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct DVDNode DVDNode;

typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock* block);

#endif

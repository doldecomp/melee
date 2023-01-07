#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include <dolphin/os/os.h>

#define NOT_IMPLEMENTED                                                        \
    OSPanic(__FILE__, __LINE__, "%s is not implemented!", __func__)

#endif

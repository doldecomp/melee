#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include <dolphin/os/os.h>

#define NOT_IMPLEMENTED(name)                                                  \
    OSPanic(__FILE__, __LINE__, "#name is not implemented!");

#endif

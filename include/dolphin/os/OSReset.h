#ifndef DOLPHIN_OS_OSRESET_H
#define DOLPHIN_OS_OSRESET_H

#include <dolphin/types.h>

typedef BOOL (*OSResetFunction)(BOOL);

typedef struct OSResetFunctionInfo OSResetFunctionInfo;
struct OSResetFunctionInfo {
    OSResetFunction func;
    u32 priority;
    OSResetFunctionInfo* next;
    OSResetFunctionInfo* prev;
};

void OSResetSystem(BOOL reset, u32 resetCode, BOOL forceMenu);

#endif

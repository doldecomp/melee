#ifndef DOLPHIN_OS_OSRESET_H
#define DOLPHIN_OS_OSRESET_H

#include <platform.h>

#include <dolphin/os.h>

typedef bool (*OSResetFunction)(bool);

typedef struct OSResetFunctionInfo OSResetFunctionInfo;
struct OSResetFunctionInfo {
    OSResetFunction func;
    u32 priority;
    OSResetFunctionInfo* next;
    OSResetFunctionInfo* prev;
};

void OSResetSystem(int reset, u32 resetCode, bool forceMenu);
void OSRegisterResetFunction(OSResetFunctionInfo* func);
void __OSDoHotReset(s32 arg0);

/// @todo @c enum
#define OS_RESET_RESTART 0
#define OS_RESET_HOTRESET 1
#define OS_RESET_SHUTDOWN 2

bool __OSCallResetFunctions(bool funcs_arg);
u32 OSGetResetCode(void);

#endif

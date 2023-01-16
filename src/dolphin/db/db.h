#ifndef __DOLPHIN_DB_H__
#define __DOLPHIN_DB_H__

#include <Runtime/platform.h>

typedef struct {
    u32 bPresent;
    u32 exceptionMask;
    void (*ExceptionDestination)(void);
    void* exceptionReturn;
} DBInterface;

void DBInit(void);
bool DBIsDebuggerPresent(void);
void DBPrintf(const char* str, ...);

#endif

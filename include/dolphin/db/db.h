#ifndef __DOLPHIN_DB_H__
#define __DOLPHIN_DB_H__

#include <dolphin/types.h>

typedef struct
{
    u32 bPresent;
    u32 exceptionMask;
    void (*ExceptionDestination)(void);
    void* exceptionReturn;
} DBInterface;

void DBInit(void);
BOOL DBIsDebuggerPresent(void);

#endif

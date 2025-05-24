#ifndef SYSDOLPHIN_BASELIB_DEBUG_H
#define SYSDOLPHIN_BASELIB_DEBUG_H

#include <platform.h>

#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>

typedef void (*ReportCallback)(s32, s32);
typedef void (*PanicCallback)(OSContext*, ...);
typedef int (*LogFunc)(s32, s32, s32*, s32);

ATTRIBUTE_NORETURN void __assert(char*, u32, char*);

void HSD_LogInit(void);
ATTRIBUTE_NORETURN void HSD_Panic(char*, u32, char*);

/// @todo Take @c file as another arg, ignore it if @c BUGFIX.
#ifndef BUGFIX
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))
#define HSD_ASSERTMSG(line, cond, msg)                                        \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, msg))
#else
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, __LINE__, #cond))
#define HSD_ASSERTMSG(line, cond, msg)                                        \
    ((cond) ? ((void) 0) : __assert(__FILE__, __LINE__, #cond))
#endif

int report_func(s32 arg0, s32 arg1, s32* arg2, s32 arg3);

void HSD_SetReportCallback(ReportCallback cb);
void HSD_SetPanicCallback(PanicCallback cb);

#endif

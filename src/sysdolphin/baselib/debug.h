#ifndef SYSDOLPHIN_BASELIB_DEBUG_H
#define SYSDOLPHIN_BASELIB_DEBUG_H

#include <platform.h>

#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>

typedef void (*ReportCallback)(const unsigned char*, size_t);
typedef void (*PanicCallback)(OSContext*, ...);

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

int report_func(__file_handle arg0, unsigned char* arg1, size_t* arg2,
                __idle_proc arg3);

void HSD_SetReportCallback(ReportCallback cb);
void HSD_SetPanicCallback(PanicCallback cb);

#endif

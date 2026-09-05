#ifndef SYSDOLPHIN_BASELIB_DEBUG_H
#define SYSDOLPHIN_BASELIB_DEBUG_H

#include <dolphin/os.h> // IWYU pragma: keep
#include <Runtime/platform.h>

typedef void (*ReportCallback)(const unsigned char*, size_t);
typedef void (*PanicCallback)(OSContext*, ...);

ATTRIBUTE_NORETURN void __assert(char*, u32, char*);

void HSD_LogInit(void);
ATTRIBUTE_NORETURN void HSD_Panic(char*, u32, char*);

/// @todo Take @c file as another arg, ignore it if not `MUST_MATCH`.
#ifdef MUST_MATCH
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))
#define HSD_ASSERTMSG(line, cond, msg)                                        \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, msg))
#define HSD_ASSERTREPORT(line, cond, ...)                                     \
    ((cond) ? (void) 0                                                        \
            : (OSReport(__VA_ARGS__), __assert(__FILE__, line, #cond)))
#else
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, __LINE__, #cond))
#define HSD_ASSERTMSG(line, cond, msg)                                        \
    ((cond) ? ((void) 0) : __assert(__FILE__, __LINE__, #cond))
#define HSD_ASSERTREPORT(line, cond, ...)                                     \
    ((cond) ? (void) 0                                                        \
            : (OSReport(__VA_ARGS__), __assert(__FILE__, __LINE__, #cond)))
#endif

void HSD_SetReportCallback(ReportCallback cb);
void HSD_SetPanicCallback(PanicCallback cb);

#endif

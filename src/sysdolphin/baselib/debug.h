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
#define HSD_ASSERTREPORT(line, cond, ...)                                     \
    ((cond) ? (void) 0                                                        \
            : (OSReport(__VA_ARGS__), __assert(__FILE__, line, #cond)))
/// HSD_ASSERTREPORT for code split out of a larger retail TU: the retail
/// __FILE__ string and stringized condition belong to the original TU's
/// data, so they are taken as explicit arguments (see @todo above).
#define HSD_ASSERTREPORTFILE(file, line, cond, msg, ...)                      \
    ((cond) ? (void) 0 : (OSReport(__VA_ARGS__), __assert(file, line, msg)))
/// HSD_ASSERTMSG with the retail __FILE__ string and message taken as
/// explicit arguments, for asserts whose strings live in the TU's own
/// not-yet-decompiled merged .data (see HSD_ASSERTREPORTFILE above).
#define HSD_ASSERTMSGFILE(file, line, cond, msg)                              \
    ((cond) ? ((void) 0) : __assert(file, line, msg))
#else
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, __LINE__, #cond))
#define HSD_ASSERTMSG(line, cond, msg)                                        \
    ((cond) ? ((void) 0) : __assert(__FILE__, __LINE__, #cond))
#define HSD_ASSERTREPORT(line, cond, ...)                                     \
    ((cond) ? (void) 0                                                        \
            : (OSReport(__VA_ARGS__), __assert(__FILE__, __LINE__, #cond)))
#define HSD_ASSERTREPORTFILE(file, line, cond, msg, ...)                      \
    ((cond) ? (void) 0                                                        \
            : (OSReport(__VA_ARGS__), __assert(__FILE__, __LINE__, #cond)))
#define HSD_ASSERTMSGFILE(file, line, cond, msg)                              \
    ((cond) ? ((void) 0) : __assert(__FILE__, __LINE__, #cond))
#endif

int report_func(__file_handle arg0, unsigned char* arg1, size_t* arg2,
                __idle_proc arg3);

void HSD_SetReportCallback(ReportCallback cb);
void HSD_SetPanicCallback(PanicCallback cb);

#endif

#include <platform.h>

#include <dolphin/os/init/__ppc_eabi_init.h>
#include <MSL/abort_exit.h>

void __destroy_global_chain(void);
void __kill_critical_regions(void);
extern void __fini_cpp_exceptions(void);

extern void (*_dtors[])(void);

static void (*atexit_funcs[64])(void);
static void (*__atexit_funcs[64])(void);

static int __aborting;
static int atexit_curr_func;
static int __atexit_curr_func;
static void (*__stdio_exit)(void);
static void (*__console_exit)(void);

void exit(int code)
{
    void (**dtor)(void);

    if (__aborting == 0) {
        while (atexit_curr_func > 0) {
            atexit_funcs[--atexit_curr_func]();
        }
        __destroy_global_chain();
        dtor = _dtors;
        while (*dtor != NULL) {
            (*dtor)();
            dtor++;
        }
        if (__stdio_exit != NULL) {
            __stdio_exit();
            __stdio_exit = NULL;
        }
    }
    while (__atexit_curr_func > 0) {
        __atexit_funcs[--__atexit_curr_func]();
    }
    __kill_critical_regions();
    if (__console_exit != NULL) {
        __console_exit();
        __console_exit = NULL;
    }
    _ExitProcess();
}
